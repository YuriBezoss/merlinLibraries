#include <Indicator_led.h>
#include <Action_heartbeat.h>
#include <Sensor_ins.h>
#include <Filter_motionDetection_ins.h>
#include <Filter_tiltingAngle.h>
#include <Action_demoMerlin.h>
#include <Remote_serialCmdsDecoder_demoMerlin.h>
#include "Builder_demoMerlin.h"


///////////////////////////////////////////////////////////////////////////
// Scheduler
///////////////////////////////////////////////////////////////////////////
#define CYCLE_PERIOD 0.1f

///////////////////////////////////////////////////////////////////////////
// Loop times
///////////////////////////////////////////////////////////////////////////
#define FILTER_MANAGER_INTERVAL   1
#define LOGGER_SCHEDULER_INTERVAL 1

///////////////////////////////////////////////////////////////////////////
// PRINT DATA
///////////////////////////////////////////////////////////////////////////
#define PRINT_SCHEDULER              1
#define PRINT_SENSOR_INS             1
#define PRINT_MOTION_DETECTION       1
#define PRINT_TILTING_ANGLE          1


Scheduler *Builder_demoMerlin::build() {

    setupHardware();

    // logging manager
    setupLogger();
    loggingManager = new LoggingManager(logger, LOGGER_SCHEDULER_INTERVAL);

    // scheduler
    scheduler = new Scheduler(hardwareTimer, CYCLE_PERIOD);
    loggingManager->addLoggable(scheduler, PRINT_SCHEDULER);

    // filters and pips
    PipelineManager *filtersManager = setupFiltersManager();

    // add tasks
    scheduler->addTask(filtersManager);
    scheduler->addTask(loggingManager);
    return scheduler;
}


///////////////////////////////////////////////////////////////////////////
// FilterManager
///////////////////////////////////////////////////////////////////////////
PipelineManager *Builder_demoMerlin::setupFiltersManager() {
    auto *filtersManager = new PipelineManager(FILTER_MANAGER_INTERVAL);

    ///////////////////////////////////////////////////////////////////////////
    // REMOTE CONTROL
    ///////////////////////////////////////////////////////////////////////////
    // serial cmds
    auto *serialCmdsDecoder = new Remote_serialCmdsDecoder_demoMerlin(serialBasicCommunication);
    filtersManager->addFilter(SerialCmdsDecoder, serialCmdsDecoder);

    ///////////////////////////////////////////////////////////////////////////
    // SENSORS AND FILTERS
    ///////////////////////////////////////////////////////////////////////////
    // sensors and filters
    auto *insSensor = new Sensor_ins(hardwareInertialSensor);
    filtersManager->addFilter(Ins, insSensor);
    loggingManager->addLoggable(insSensor, PRINT_SENSOR_INS);

    // motion detection
    auto *motionDetection = new Filter_motionDetection_ins();
    filtersManager->addFilter(MotionDetection, motionDetection);
    filtersManager->addPipe(Ins, Sensor_ins::OutAccel, MotionDetection, Filter_motionDetection_ins::InAccel);
    filtersManager->addPipe(Ins, Sensor_ins::OutGyro, MotionDetection, Filter_motionDetection_ins::InGyro);
    loggingManager->addLoggable(motionDetection, PRINT_MOTION_DETECTION);

    // tilting angle
    auto *tiltingAngle = new Filter_tiltingAngle();
    filtersManager->addFilter(TiltingAngle, tiltingAngle);
    filtersManager->addPipe(Ins, Sensor_ins::OutAccel, TiltingAngle, Filter_tiltingAngle::InAccel);
    loggingManager->addLoggable(tiltingAngle, PRINT_TILTING_ANGLE);


    ///////////////////////////////////////////////////////////////////////////
    // ACTIONS
    ///////////////////////////////////////////////////////////////////////////
    auto *heartbeatLed = new Indicator_led(hardwareGpio_heartbeatLed);
    auto *heartbeatAction = new Action_heartbeat(heartbeatLed);
    filtersManager->addFilter(HeartbeatAction, heartbeatAction);

    auto *tiltingLed = new Indicator_led(hardwareGpio_tiltedLed);
    auto *motionLed = new Indicator_led(hardwareGpio_motionLed);
    auto *demoAction = new Action_demoMerlin(tiltingLed, motionLed);
    filtersManager->addFilter(DemoAction, demoAction);
    filtersManager->addPipe(SerialCmdsDecoder, Remote_serialCmdsDecoder_demoMerlin::OutStartCmdReceived, DemoAction, Action_demoMerlin::InStartCmdReceived);
    filtersManager->addPipe(MotionDetection, Filter_motionDetection_ins::OutMotion, DemoAction, Action_demoMerlin::InMotion);
    filtersManager->addPipe(TiltingAngle, Filter_tiltingAngle::OutTiltingAngle, DemoAction, Action_demoMerlin::InTiltingAngle);

    return filtersManager;
}



