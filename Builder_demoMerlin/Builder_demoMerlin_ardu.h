#ifndef DemoBuilder_ardu_H
#define DemoBuilder_ardu_H

#include <Hardware_timer_ardu.h>
#include <Hardware_gpioOut_ardu.h>
#include <Hardware_inertialSensor_mpu6000_spi.h>
#include <Hardware_spi_ardu.h>
#include <Hardware_usbSerial_ardu.h>
#include <Logger.h>
#include <Serial_basicCommunication.h>
#include "Builder_demoMerlin.h"

class Builder_demoMerlin_ardu: public Builder_demoMerlin {
protected:
    void setupHardware() override {

        // timer
        hardwareTimer = new Hardware_timer_ardu();

        // gpio out
        hardwareGpio_heartbeatLed = new Hardware_gpioOut_ardu(16);
        hardwareGpio_motionLed = new Hardware_gpioOut_ardu(19);
        hardwareGpio_tiltedLed = new Hardware_gpioOut_ardu(20);

        // spi
        hardwareSpi = new Hardware_spi_ardu();

        // sensors
        hardwareInertialSensor = new Hardware_inertialSensor_mpu6000_spi(hardwareTimer, hardwareSpi);

        // serial communication
        Hardware_usbSerial *usbSerial = new Hardware_usbSerial_ardu(&Serial);
        serialBasicCommunication = new Serial_basicCommunication(usbSerial, hardwareTimer);
    }


    void setupLogger() override {
        Hardware_usbSerial *usbSerial = new Hardware_usbSerial_ardu(&Serial);
        logger = new Logger(usbSerial, hardwareTimer);
    }


};

#endif //DemoBuilder_ardu_H
