#ifndef Action_demoMerlin_H
#define Action_demoMerlin_H


#include <Filter.h>
#include <Indicator_led.h>

class Action_demoMerlin : public Filter {
///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes {
        InStartCmdReceived, InTiltingAngle, InMotion, NUM_INPUT_TYPES
    };

    enum OutputDataTypes {
        NUM_OUTPUT_TYPES
    };

    uint8_t getNumberOfInputItems() override {
        return NUM_INPUT_TYPES;
    }

    uint8_t getNumberOfOutputItems() override {
        return NUM_OUTPUT_TYPES;
    }

    void setInputItem(uint8_t itemId, FilterItem *item) override {
        switch (itemId) {
            case InStartCmdReceived: inStartCmdReceived = (FilterItem_bool*) item; break;
            case InTiltingAngle: inTiltingAngle = (FilterItem_float*) item; break;
            case InMotion: inMotion = (FilterItem_bool*) item; break;
            default: break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        return nullptr;//nop
    };

    void update(float deltaTime) override;

protected:
    FilterItem_bool *inStartCmdReceived = nullptr;
    FilterItem_float *inTiltingAngle = nullptr;
    FilterItem_bool *inMotion = nullptr;

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Action_demoMerlin(Indicator_led *tiltingLed, Indicator_led *motionLed) {
        Action_demoMerlin::tiltingLed = tiltingLed;
        Action_demoMerlin::motionLed = motionLed;
    }

protected:

    bool actionRunning = true;
    Indicator_led *tiltingLed = nullptr;
    Indicator_led *motionLed = nullptr;

};


#endif //Action_demoMerlin_H
