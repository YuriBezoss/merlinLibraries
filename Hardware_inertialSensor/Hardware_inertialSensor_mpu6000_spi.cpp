#include "Hardware_inertialSensor_mpu6000_spi.h"

void Hardware_inertialSensor_mpu6000_spi::init() {

    if(hardwareSpi) {

        writeRegister(MPU6000_PWR_MGMT_1, 0x80); // chip reset
        timer->delayMillis(100); // startup time delay


        writeRegister(MPU6000_PWR_MGMT_1, MPU6000_CLKSEL_3); // wake Up MPU and use GyroZ clock
        writeRegister(MPU6000_USER_CTRL, MPU6000_I2C_IF_DIS); // disable I2C
        writeRegister(MPU6000_PWR_MGMT_2, 0);

        // Gyroscope Output Rate = 8kHz when the DLPF is disabled (targetLPF = 0 or 7), and 1kHz when the DLPF is enabled (see Register Map paage 12)
        // This means if targetLPF == 0 -> Sample rate = 8 khz/(1+MPU6000_SMPLRT_DIV) and otherwise Sample rate = 1 khz/(1+MPU6000_SMPLRT_DIV)
        // We want a sample rate of 1 kHz, so we have to set MPU6000_SMPLRT_DIV to 7 or 0 respectively.
        if(targetLPF == 0) {
            writeRegister(MPU6000_SMPLRT_DIV, 0x07);
        } else {
            writeRegister(MPU6000_SMPLRT_DIV, 0x00);
        }

        writeRegister(MPU6000_CONFIG, targetLPF); // set low pass filter
        usedLPF = readDLPF();

        writeRegister(MPU6000_GYRO_CONFIG, gyroRange); // set gyro range
        gyroScaling = readGyroScaling();

        writeRegister(MPU6000_ACCEL_CONFIG, accelRange); // set accel range
        accelScaling = readAccelScaling();
    }
}

/**
 * Reads the current accel, gyro and temp data
 */
void Hardware_inertialSensor_mpu6000_spi::update(){

    hardwareSpi->setBaudrate(SPI_BAUDRATE_SENSOR_REGISTERS);

    DataUnion data = DataUnion();
    readRegisters(MPU6000_ACCEL_XOUT_H, (uint8_t*) &data, sizeof(data));

    uint8_t temp;

    temp = data.reg.accel_x_h; data.reg.accel_x_h = data.reg.accel_x_l; data.reg.accel_x_l = temp;
    temp = data.reg.accel_y_h; data.reg.accel_y_h = data.reg.accel_y_l; data.reg.accel_y_l = temp;
    temp = data.reg.accel_z_h; data.reg.accel_z_h = data.reg.accel_z_l; data.reg.accel_z_l = temp;

    temp = data.reg.gyro_x_h; data.reg.gyro_x_h = data.reg.gyro_x_l; data.reg.gyro_x_l = temp;
    temp = data.reg.gyro_y_h; data.reg.gyro_y_h = data.reg.gyro_y_l; data.reg.gyro_y_l = temp;
    temp = data.reg.gyro_z_h; data.reg.gyro_z_h = data.reg.gyro_z_l; data.reg.gyro_z_l = temp;

    temp = data.reg.temperature_h; data.reg.temperature_h = data.reg.temperature_l; data.reg.temperature_l = temp;

    accelRaw = Vector3f(data.value.accel_x, data.value.accel_y, data.value.accel_z);
    accel = accelRaw / accelScaling  * Math_basic::GRAVITY_CONSTANT / 1000.0f; // in m/s^2

    gyroRaw = Vector3f(data.value.gyro_x, data.value.gyro_y, data.value.gyro_z);
    gyro = (gyroRaw/gyroScaling).toRad(); // in rad/s

    temperatureRaw =  data.value.temperature;
    temperature = temperatureRaw / 340.f + 36.5f; // in celsius

}

/**
 * Reads the low pass filter cutoff-frequency that is used in the MPU
 * @return low pass filter cut off frequency
 */
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

/**
 * Reads the gyro scaling factor that is used in the MPU
 * @return gyro scaling factor
 */
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

/**
 * Reads the accel scaling factor that is used in the MPU
 * @return accel scaling factor
 */
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

/**
 * Reads the n registers in the MPU6000 starting at the register address
 * @param registerAddr register address
 * @param data array that returns the register data that was read
 * @param dataSize number of registers (n) that are read
 */
void Hardware_inertialSensor_mpu6000_spi::readRegisters(uint8_t registerAddr, uint8_t *data, uint8_t dataSize){

    uint8_t msgSize = dataSize+(uint8_t)1; // msgSize is the register address (1 byte) plus the length of the data array we expect.

    uint8_t txMsg[msgSize]; // data transmitted
    uint8_t rxMsg[msgSize]; // data received
    for (int j = 0; j < msgSize; ++j) {
        txMsg[j] = 0;
        rxMsg[j] = 0;
    }

    txMsg[0] = (uint8_t) (registerAddr | 0x80); // set the register address

    hardwareSpi->beginTransaction();
    hardwareSpi->transfer(txMsg, rxMsg, msgSize);
    hardwareSpi->endTransaction();

    // write the received data to the data array
    for(uint8_t i = 0; i < dataSize; i++) {
        data[i] = rxMsg[i+1];
    }
}

/**
 * Writes a single data byte to a register
 * @param registerAddr
 * @param dataByte
 */
void Hardware_inertialSensor_mpu6000_spi::writeRegister(uint8_t registerAddr, uint8_t dataByte){
    uint8_t txData[] = {registerAddr, dataByte};
    uint8_t rxData[] = {0,0};

    hardwareSpi->setBaudrate(SPI_BAUDRATE_ALL_REGISTERS);
    timer->delayMicros(1);

    hardwareSpi->beginTransaction();
    hardwareSpi->transfer(txData, rxData, 2);
    hardwareSpi->endTransaction();
}