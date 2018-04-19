#ifndef Filter_tiltingAngle_H
#define Filter_tiltingAngle_H


#include <Filter.h>
#include <Loggable.h>

class Filter_tiltingAngle: public Filter, public Loggable {
///////////////////////////////////////////////////////////////////////////
// Loggable
///////////////////////////////////////////////////////////////////////////
public:
    bool printData(Logger *logger, bool printHeader) override {
        if (loggingActive) {
            logger->printLoggable("tiltingAngle", outTiltingAngle.value, printHeader);
            return true;
        }
        return false;
    }

///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes {
        InAccel, NUM_INPUT_TYPES
    };

    enum OutputDataTypes {
        OutTiltingAngle, NUM_OUTPUT_TYPES
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
            default: break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        switch (itemId) {
            case OutTiltingAngle:return &outTiltingAngle;
            default: return nullptr;//nop
        }
    };

    void update(float deltaTime) override;

protected:

    FilterItem_vector3f *inAccel = nullptr;

    FilterItem_float outTiltingAngle;
};


#endif //Filter_tiltingAngle
