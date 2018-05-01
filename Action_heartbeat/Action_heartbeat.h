#ifndef Action_heartbeatLed_H
#define Action_heartbeatLed_H


#include <Filter.h>
#include <Indicator_led.h>


/**
 * The hearbeat library changes the state of an led every time its update function is called.
 */
class Action_heartbeat : public Filter {
///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    uint8_t getNumberOfInputItems() override {
        return 0;
    }

    uint8_t getNumberOfOutputItems() override {
        return 0;
    }

    void setInputItem(uint8_t itemId, FilterItem *item) override {

    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        return nullptr;//nop
    };

    void update(float deltaTime) override;

protected:

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Action_heartbeat(Indicator_led *led) {
        Action_heartbeat::led = led;
    }

protected:

    Indicator_led *led = nullptr;

};


#endif //Action_heartbeatLed_H
