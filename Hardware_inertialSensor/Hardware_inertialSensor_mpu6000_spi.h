#ifndef Hardware_inertialSensor_mpu6000_spi_h
#define Hardware_inertialSensor_mpu6000_spi_h

#include <Hardware_spi.h>
#include <Hardware_timer.h>
#include <Hardware_inertialSensor.h>

#define MPU6000_SMPLRT_DIV   0x19
#define MPU6000_CONFIG       0x1A
#define MPU6000_GYRO_CONFIG  0x1B
#define MPU6000_ACCEL_CONFIG 0x1C

#define MPU6000_ACCEL_XOUT_H 0x3B

#define MPU6000_USER_CTRL   0x6A
#define MPU6000_PWR_MGMT_1  0x6B
#define MPU6000_PWR_MGMT_2  0x6C
#define MPU6000_CLKSEL_3    3

#define MPU6000_I2C_IF_DIS  0x10

#define MPU6000_DLPF_260HZ  0
#define MPU6000_DLPF_184HZ  1
#define MPU6000_DLPF_94HZ   2
#define MPU6000_DLPF_44HZ   3
#define MPU6000_DLPF_21HZ   4
#define MPU6000_DLPF_10HZ   5
#define MPU6000_DLPF_5HZ    6

#define MPU6000_FS_SEL_250  0
#define MPU6000_FS_SEL_500  8
#define MPU6000_FS_SEL_1000 16
#define MPU6000_FS_SEL_2000 24

#define MPU6000_AFS_SEL_2G  0
#define MPU6000_AFS_SEL_4G  8
#define MPU6000_AFS_SEL_8G  16
#define MPU6000_AFS_SEL_16G 24


class Hardware_inertialSensor_mpu6000_spi : public Hardware_inertialSensor {

public:

	explicit Hardware_inertialSensor_mpu6000_spi(Hardware_timer *timer, Hardware_spi *hardwareSpi) {
		Hardware_inertialSensor_mpu6000_spi::timer = timer;
		Hardware_inertialSensor_mpu6000_spi::hardwareSpi = hardwareSpi;
		init();
	}

    void update() override;

	bool isDataAvailable() override { return true; };

	Vector3f getAccel() override { return accel; };
    Vector3f getAccelRaw() override { return accelRaw; };

    Vector3f getGyro() override { return gyro; };
    Vector3f getGyroRaw() override { return gyroRaw; };

	float getTemp() override { return temperature; };
	float getTempRaw() override { return temperatureRaw; };

protected:

	static const uint32_t SPI_BAUDRATE_ALL_REGISTERS = 1000000;  // 1MHz SPI serial interface for communicating with all registers
	static const uint32_t SPI_BAUDRATE_SENSOR_REGISTERS = 20000000; // 20MHz SPI serial interface for reading sensor and interrupt registers

	void init();
	uint16_t readDLPF();
    float readGyroScaling();
    float readAccelScaling();

	void readRegisters(uint8_t registerAddr, uint8_t *data, uint8_t dataSize);
	void writeRegister(uint8_t registerAddr, uint8_t dataByte);

	union DataUnion{
		struct{
			uint8_t accel_x_h;
			uint8_t accel_x_l;
			uint8_t accel_y_h;
			uint8_t accel_y_l;
			uint8_t accel_z_h;
			uint8_t accel_z_l;
			uint8_t temperature_h;
			uint8_t temperature_l;
			uint8_t gyro_x_h;
			uint8_t gyro_x_l;
			uint8_t gyro_y_h;
			uint8_t gyro_y_l;
			uint8_t gyro_z_h;
			uint8_t gyro_z_l;
		} reg;
		struct{
			int16_t accel_x;
			int16_t accel_y;
			int16_t accel_z;
			int16_t temperature;
			int16_t gyro_x;
			int16_t gyro_y;
			int16_t gyro_z;
		} value;
	};


	Hardware_spi *hardwareSpi = nullptr;
    Hardware_timer *timer = nullptr;

	uint8_t targetLPF = MPU6000_DLPF_44HZ; // low pass filter cutoff-frequency
	uint8_t gyroRange = MPU6000_FS_SEL_2000; // gyro range in deg/s
	uint8_t accelRange = MPU6000_AFS_SEL_4G; // accel range in g

    Vector3f accel = Vector3f(0,0,0); // in m/s^2
    Vector3f gyro = Vector3f(0,0,0); // in rad/s
    Vector3f accelRaw = Vector3f(0,0,0);
    Vector3f gyroRaw = Vector3f(0,0,0);

    float temperature = 0; // in celsius
    float temperatureRaw = 0;

	float usedLPF = 0;
    float gyroScaling = 0;
    float accelScaling = 0;

};

#endif //Hardware_inertialSensor_mpu6000_spi_h
