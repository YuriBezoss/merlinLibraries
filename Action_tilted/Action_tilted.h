#ifndef Action_tilted_H
#define Action_tilted_H

#include <Filter.h>
#include <Indicator_led.h>

class Action_tilted : public Filter {
///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes {
        InTiltingAngle, NUM_INPUT_TYPES
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
            case InTiltingAngle: inTiltingAngle = (FilterItem_float*) item; break;
            default: break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        return nullptr;//nop
    };

    void update(float deltaTime) override;

protected:

    FilterItem_float *inTiltingAngle = nullptr;

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Action_tilted(Indicator_led *led) {
        Action_tilted::led = led;
    }

protected:

    Indicator_led *led = nullptr;

};

#endif //Action_tilted_H
