#ifndef Hardware_gpioOut_H
#define Hardware_gpioOut_H


#include <stdint-gcc.h>

class Hardware_gpioOut {

public:

    explicit Hardware_gpioOut(uint16_t pin) : pin(pin){}

    virtual bool getState() = 0 ;
    virtual void setState(bool s) = 0 ;

protected:

    uint16_t pin = 0;
    bool state = false;
};


#endif //Hardware_gpioOut_H
