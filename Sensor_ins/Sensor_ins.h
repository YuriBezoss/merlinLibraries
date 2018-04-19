#ifndef Sensor_ins_H
#define Sensor_ins_H


#include <Hardware_inertialSensor.h>
#include <Filter.h>
#include <Loggable.h>

class Sensor_ins: public Filter, public Loggable {
///////////////////////////////////////////////////////////////////////////
// Loggable
///////////////////////////////////////////////////////////////////////////
public:
    bool printData(Logger *logger, bool printHeader) override {
        if (loggingActive) {
            logger->printLoggable("accel", outAccel.value, printHeader);
            logger->printLoggable("gyro", outGyro.value, printHeader);
            return true;
        }
        return false;
    }

///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum outputDataTypes{
        OutAccel, OutGyro, NUM_OUTPUT_TYPES
    };

    uint8_t getNumberOfInputItems() override {
        return 0;
    }

    uint8_t getNumberOfOutputItems() override {
        return NUM_OUTPUT_TYPES;
    }

    void setInputItem(uint8_t itemId, FilterItem *item) override {
        // nop
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        switch(itemId){
            case OutAccel: return &outAccel;
            case OutGyro: return &outGyro;
            default:;//nop
        }
        return nullptr;
    };

    void update(float deltaTime) override;

protected:
    FilterItem_vector3f outAccel;
    FilterItem_vector3f outGyro;


///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Sensor_ins(Hardware_inertialSensor *inertialSensor) {
        Sensor_ins::inertialHardwareSensor = inertialSensor;
    }


protected:

    Hardware_inertialSensor *inertialHardwareSensor;

};


#endif //Sensor_ins_H
