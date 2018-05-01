#ifndef Hardware_gpioOut_H
#define Hardware_gpioOut_H


#include <stdint-gcc.h>

/**
 * Controls a gpio output pin
 */
class Hardware_gpioOut {

public:

    explicit Hardware_gpioOut(uint16_t pin) : pin(pin){}

    virtual bool getState() = 0 ; // return current state of the gpio pin
    virtual void setState(bool s) = 0 ; // set the current state of the gpio pin, true == HIGH, false == LOW

protected:

    uint16_t pin = 0;
    bool state = false;
};


#endif //Hardware_gpioOut_H
