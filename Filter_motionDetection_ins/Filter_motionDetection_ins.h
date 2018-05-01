#ifndef Filter_motionDetection_ins_H
#define Filter_motionDetection_ins_H


#include <Filter.h>
#include <Loggable.h>


/**
 * This library uses gyroscope and accelerometer data provided by an inertial sensor to determine whether the sensor is moved or not.
 */
class Filter_motionDetection_ins: public Filter, public Loggable {
///////////////////////////////////////////////////////////////////////////
// Loggable
///////////////////////////////////////////////////////////////////////////
public:
    bool printData(Logger *logger, bool printHeader) override {
        if (loggingActive) {
            logger->printLoggable("motion", outMotion.value, printHeader);
            return true;
        }
        return false;
    }

///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes {
        InAccel, InGyro, NUM_INPUT_TYPES
    };

    enum OutputDataTypes {
        OutMotion, NUM_OUTPUT_TYPES
    };

    uint8_t getNumberOfInputItems() override {
        return NUM_INPUT_TYPES;
    }

    uint8_t getNumberOfOutputItems() override {
        return NUM_OUTPUT_TYPES;
    }

    void setInputItem(uint8_t itemId, FilterItem *item) override {
        switch (itemId) {
            case InAccel: inAccel = (FilterItem_vector3f*) item;break;
            case InGyro: inGyro = (FilterItem_vector3f*) item;break;
            default: break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        switch (itemId) {
            case OutMotion:return &outMotion;
            default: return nullptr;//nop
        }
    };

    void update(float deltaTime) override;

protected:

    FilterItem_vector3f *inAccel = nullptr;
    FilterItem_vector3f *inGyro = nullptr;

    FilterItem_bool outMotion;

};


#endif //Filter_motionDetection_ins_H
