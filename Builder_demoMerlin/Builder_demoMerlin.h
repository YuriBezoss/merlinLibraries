#ifndef Builder_demoMerlin_H
#define Builder_demoMerlin_H


#include <Builder.h>
#include <Hardware_timer.h>
#include <Hardware_gpioOut.h>
#include <Hardware_spi.h>
#include <Serial_basicCommunication.h>
#include <Logger.h>
#include <LoggingManager.h>
#include <PipelineManager.h>



class Builder_demoMerlin: public Builder {

public:

    // Build
    Scheduler *build() override;

protected:

    enum Filters{
        SerialCmdsDecoder, RemoteManagerOutput,
        Ins, MotionDetection, TiltingAngle, FilterManagerOutput,
        HeartbeatAction, DemoAction, TiltingAction, ActionManagerOutput
    };

    // hardware
    virtual void setupHardware() = 0;
    Hardware_timer *hardwareTimer = nullptr;
    Hardware_gpioOut *hardwareGpio_heartbeatLed = nullptr;
    Hardware_gpioOut *hardwareGpio_motionLed = nullptr;
    Hardware_gpioOut *hardwareGpio_tiltedLed = nullptr;
    Hardware_spi *hardwareSpi = nullptr;
    Hardware_inertialSensor *hardwareInertialSensor = nullptr;
    Serial_basicCommunication *serialBasicCommunication = nullptr;


    // logging
    virtual void setupLogger() = 0;
    Logger *logger = nullptr;
    LoggingManager *loggingManager = nullptr;

    // scheduler
    Scheduler *scheduler = nullptr;

    // filters and pipes
    PipelineManager *setupFiltersManager();

};


#endif //Builder_demoMerlin_H
