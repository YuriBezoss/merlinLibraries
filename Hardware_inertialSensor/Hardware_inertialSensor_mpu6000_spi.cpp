#include "Hardware_inertialSensor_mpu6000_spi.h"

void Hardware_inertialSensor_mpu6000_spi::init() {

    if(hardwareSpi) {

        writeRegister(MPU6000_PWR_MGMT_1, 0x80); // chip reset entire device 0x80
        timer->delayMillis(100); // Startup time delay

        // Wake Up device and select GyroZ clock (better performance)
        writeRegister(MPU6000_PWR_MGMT_1, MPU6000_CLKSEL_3);

        writeRegister(MPU6000_USER_CTRL, I2C_IF_DIS);

        writeRegister(MPU6000_PWR_MGMT_2, 0); // only used for wake-up in accelerometer only low power mode

        // SAMPLE RATE
        if(dlpf == 0) { // Unterscheidung notwending, damit Sample Frequzenz immer 1 kHz bleibt. Wird fuer IMU-STM Kopplung benoetigt.
            writeRegister(MPU6000_SMPLRT_DIV, 0x07); // Sample rate = 8000Hz  -> Fsample= 1Khz/(1+SMPLRT_DIV) = 1000Hz, if MPU6000_CONFIG = 0,7 Fsample= 8Khz/(1+SMPLRT_DIV) = 8000Hz
        } else {
            writeRegister(MPU6000_SMPLRT_DIV, 0x00); // Sample rate = 8000Hz  -> Fsample= 1Khz/(1+SMPLRT_DIV) = 1000Hz, if MPU6000_CONFIG = 0,7 Fsample= 8Khz/(1+SMPLRT_DIV) = 8000Hz
        }

        writeRegister(MPU6000_CONFIG, dlpf); // low pass filter
        writeRegister(MPU6000_GYRO_CONFIG, gyroRange); //
        writeRegister(MPU6000_ACCEL_CONFIG, accelRange);

        lpf = readDLPF();
        gyroScaling = readGyroScaling();
        accelScaling = readAccelScaling();
    }
}


void Hardware_inertialSensor_mpu6000_spi::update(){

    hardwareSpi->setBaudrate(SPI_BAUDRATE_SENSOR_REGISTERS);

    DataUnion data = DataUnion();
    readRegisters(MPU6000_ACCEL_XOUT_H, (uint8_t*) &data, sizeof(data));

    uint8_t swap;

    swap = data.reg.accel_x_h; data.reg.accel_x_h = data.reg.accel_x_l; data.reg.accel_x_l = swap;
    swap = data.reg.accel_y_h; data.reg.accel_y_h = data.reg.accel_y_l; data.reg.accel_y_l = swap;
    swap = data.reg.accel_z_h; data.reg.accel_z_h = data.reg.accel_z_l; data.reg.accel_z_l = swap;

    swap = data.reg.gyro_x_h; data.reg.gyro_x_h = data.reg.gyro_x_l; data.reg.gyro_x_l = swap;
    swap = data.reg.gyro_y_h; data.reg.gyro_y_h = data.reg.gyro_y_l; data.reg.gyro_y_l = swap;
    swap = data.reg.gyro_z_h; data.reg.gyro_z_h = data.reg.gyro_z_l; data.reg.gyro_z_l = swap;

    swap = data.reg.temp_h; data.reg.temp_h = data.reg.temp_l; data.reg.temp_l = swap;

    accelRaw = Vector3f(data.value.accel_x, data.value.accel_y, data.value.accel_z);
    accel = accelRaw / accelScaling  * Math_basic::GRAVITY_CONSTANT / 1000.0f;; // in m/s^2 gebracht

    gyroRaw = Vector3f(data.value.gyro_x, data.value.gyro_y, data.value.gyro_z);
    gyro = (gyroRaw/gyroScaling).toRad(); // in rad/s

    tempRaw =  data.value.temp;
    temp = tempRaw / 340.f + 36.5f;

}

uint16_t Hardware_inertialSensor_mpu6000_spi::readDLPF(){

    hardwareSpi->setBaudrate(SPI_BAUDRATE_ALL_REGISTERS);

    uint8_t a = 0;
    readRegisters(MPU6000_CONFIG, &a, 1);

    switch (a) {
        case MPU6000_DLPF_260HZ: return 260;
        case MPU6000_DLPF_184HZ: return 184;
        case MPU6000_DLPF_94HZ: return 94;
        case MPU6000_DLPF_44HZ: return 44;
        case MPU6000_DLPF_21HZ: return 21;
        case MPU6000_DLPF_10HZ: return 10;
        case MPU6000_DLPF_5HZ: return 5;
        default: return 0;
    }
}

float Hardware_inertialSensor_mpu6000_spi::readGyroScaling(){

    hardwareSpi->setBaudrate(SPI_BAUDRATE_ALL_REGISTERS);

    uint8_t a = 0;
    readRegisters(MPU6000_GYRO_CONFIG, &a, 1);

    switch (a) {
        case MPU6000_FS_SEL_250: return 131.0f;
        case MPU6000_FS_SEL_500: return 65.5f;
        case MPU6000_FS_SEL_1000: return 32.8f;
        case MPU6000_FS_SEL_2000: return 16.4f;
        default: return 0;
    }
}


float Hardware_inertialSensor_mpu6000_spi::readAccelScaling(){

    hardwareSpi->setBaudrate(SPI_BAUDRATE_ALL_REGISTERS);

    uint8_t a = 0;
    readRegisters(MPU6000_ACCEL_CONFIG, &a, 1);

    switch (a) {
        case MPU6000_AFS_SEL_2G: return 16.384f;
        case MPU6000_AFS_SEL_4G: return 8.192f;
        case MPU6000_AFS_SEL_8G: return 4.096;
        case MPU6000_AFS_SEL_16G: return 2.048;
        default: return 0;
    }
}


void Hardware_inertialSensor_mpu6000_spi::readRegisters(uint8_t registerAddr, uint8_t *data, uint8_t dataSize){

    uint8_t msgSize = dataSize+(uint8_t)1;

    uint8_t txMsg[msgSize];
    uint8_t rxMsg[msgSize];
    for (int j = 0; j < msgSize; ++j) {
        txMsg[j] = 0;
        rxMsg[j] = 0;
    }

    txMsg[0] = (uint8_t) (registerAddr | 0x80);

    hardwareSpi->beginTransaction();
    hardwareSpi->transfer(txMsg, rxMsg, msgSize); // write start address
    hardwareSpi->endTransaction();

    for(uint8_t i = 0; i < dataSize; i++) {
        data[i] = rxMsg[i+1];
    }
}

void Hardware_inertialSensor_mpu6000_spi::writeRegister(uint8_t registerAddr, uint8_t dataByte){
    uint8_t txData[] = {registerAddr, dataByte};
    uint8_t rxData[] = {0,0};

    hardwareSpi->setBaudrate(SPI_BAUDRATE_ALL_REGISTERS);
    timer->delayMicros(1);

    hardwareSpi->beginTransaction();
    hardwareSpi->transfer(txData, rxData, 2);
    hardwareSpi->endTransaction();
}