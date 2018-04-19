#ifndef Action_motionDetected_H
#define Action_motionDetected_H


#include <Filter.h>
#include <Indicator_led.h>

class Action_motionDetected : public Filter {
///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes {
        InMotion, NUM_INPUT_TYPES
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
            case InMotion: inMotion = (FilterItem_bool*) item; break;
            default: break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        return nullptr;//nop
    };

    void update(float deltaTime) override;

protected:

    FilterItem_bool *inMotion = nullptr;

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Action_motionDetected(Indicator_led *led) {
        Action_motionDetected::led = led;
    }

protected:

    Indicator_led *led = nullptr;

};


#endif //MERLINDEMO_ACTION_MOTIONDETECTED_H
