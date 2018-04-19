////
//// Created by luggi on 08.07.15.
////
//#include <DC_hardware_SPI_STM32F4.h>
//#include <Hardware_inertialSensor_mpu6000_spi.h>
//#include <DC_hardware_BaroSensor_MS5611_SPI.h>
//#include <DC_hardware_compass_HMC5983.h>
//#include <DC_Logger_Serial_STM32F4.h>
//#include <DC_hardware_UART_STM32.h>
//#include <DC_sensor_INS.h>
//#include <DC_Timer_STM32F4.h>
//#include <cmath>
//#include <DC_hardware_UART_STM32.h>
//#include <DC_sensor_baro.h>
//#include <DC_sensor_Compass.h>
//
//#ifndef M_PI
//#define M_PI 3.14159265358979323846f
//#endif
//
//int main() {
//
//    uint32_t currentTime = 0;
//    uint32_t previousTime = 0;
//    float dTime = 0;
//
//    DC_Logger_Serial_STM32F4* logger = new DC_Logger_Serial_STM32F4();
//    DC_hardware_UART_STM32* uart = new DC_hardware_UART_STM32();
//    DC_Timer_STM32F4* timer = new DC_Timer_STM32F4();
//    Hardware_inertialSensor_mpu6000_spi* inertialSensor = new Hardware_inertialSensor_mpu6000_spi();
//    DC_hardware_compass_HMC5983 *compassSensor = new DC_hardware_compass_HMC5983();
//    DC_hardware_BaroSensor_MS5611_SPI *baroSensor = new DC_hardware_BaroSensor_MS5611_SPI();
//    DC_sensor_INS *ins = new DC_sensor_INS();
//    DC_sensor_baro *baro = new DC_sensor_baro();
//    DC_sensor_Compass *compass = new DC_sensor_Compass();
//
//    DC_hardware_SPI_STM32F4* SPI_Ins_MPU6000 = new DC_hardware_SPI_STM32F4();
//
//    DC_hardware_SPI_STM32F4* SPI_Baro_MS5611 = new DC_hardware_SPI_STM32F4();
//
//    DC_hardware_SPI_STM32F4* SPI_Compass_HMC5983 = new DC_hardware_SPI_STM32F4();
//
//    DC_hardware_SPI_STM32F4 *SPI_Ins_ICM = new DC_hardware_SPI_STM32F4();
//
//    int16_t gyro_x;
//    int16_t gyro_y;
//    int16_t gyro_z;
//
//    int16_t temperature;
//
//    timer->init();
//    uart->set_uartType(DC_hardware_UART_STM32::UART1_PA9PA10);
//    logger->setPort(uart);
//    logger->setBaudRate(921600);
//    logger->init();
//
//    SPI_Ins_MPU6000->setCS(PIN_C4);
//    SPI_Ins_MPU6000->set_spiType(DC_hardware_SPI_STM32F4::SPI1_PA5PA6PA7);
//    SPI_Ins_MPU6000->setBaudrate(1000000);
//    SPI_Ins_MPU6000->init();
//
//    SPI_Ins_ICM->setCS(PIN_A15);
//    SPI_Ins_ICM->set_spiType(DC_hardware_SPI_STM32F4::SPI1_PA5PA6PA7);
//    SPI_Ins_ICM->setBaudrate(1000000);
//    SPI_Ins_ICM->init();
//
//    SPI_Baro_MS5611->setCS(PIN_D2);
//    SPI_Baro_MS5611->set_spiType(DC_hardware_SPI_STM32F4::SPI1_PA5PA6PA7);
//    SPI_Baro_MS5611->setBaudrate(1000000);
//    SPI_Baro_MS5611->init();
//
//    SPI_Compass_HMC5983->setCS(PIN_C8);
//    SPI_Compass_HMC5983->set_spiType(DC_hardware_SPI_STM32F4::SPI1_PA5PA6PA7);
//    SPI_Compass_HMC5983->setBaudrate(1000000);
//    SPI_Compass_HMC5983->init();
//
//
//    // Baro
//    baroSensor->setSpi(SPI_Baro_MS5611);
//    baroSensor->setTimer(timer);
//    baroSensor->newDataAvailable();
//    baro->setTimer(timer);
//    baro->setBaro(baroSensor);
//    baro->init();
//    baro->calibrate(); // calibration time in s
//
//    // Compass
//    compassSensor->setTimer(timer);
//    compassSensor->setSpi(SPI_Compass_HMC5983);
//    compass->setCompass(compassSensor);
//    compass->init();
//
//
//    inertialSensor->setSpi(SPI_Ins_MPU6000);
//    inertialSensor->set_timer(timer);
//    inertialSensor->set_dlpf(MPU6000_DLPF_21HZ);
//    inertialSensor->set_gyro_range(MPU6000_FS_SEL_2000);
//    inertialSensor->set_accel_range(MPU6000_AFS_SEL_4G);
//    inertialSensor->init();
//
//    int16_t gyrodata[3];
//    int16_t acceldata[3];
//
//    while (1) {
//
//        uint32_t lastTime = timer->micros();
//        // read imu
//        inertialSensor->update();
//        compass->update(1000);
//        baroSensor->update();
//        uint32_t currentTime = timer->micros();
//
//        inertialSensor->getGyroData(&gyrodata[0], &gyrodata[1], &gyrodata[2]);
//        inertialSensor->getAccelData(&acceldata[0], &acceldata[1], &acceldata[2]);
//
//
//        if(baroSensor->newDataAvailable()){ // every second update call new data is available
//            dTime = (currentTime - previousTime) / 1000000.0;
//            previousTime = currentTime;
//
//            logger->print(dTime,4);
//            logger->print("\t");
//            logger->print(baroSensor->getTemperature(),2);
//            logger->print("\t");
//            logger->print(baroSensor->getPressure(),2);
//            logger->print("\t");
//            logger->print(baroSensor->getConversionTimeD1(),3);
//            logger->print("\t");
//            logger->println(baroSensor->getConversionTimeD2(),3);
//            logger->print(gyrodata[0],10);
//            logger->print("\t");
//            logger->print(gyrodata[1],10);
//            logger->print("\t");
//            logger->print(gyrodata[2],10);
//            logger->print("\t");
//            logger->print(acceldata[0],10);
//            logger->print("\t");
//            logger->print(acceldata[1],10);
//            logger->print("\t");
//            logger->print(acceldata[2],10);
//            logger->print("\t");
//            logger->print("\n\r");
//            compass->printSerialData(logger);
//        }
//
//        timer->delay(10);
//
//
//    }
//
//}
