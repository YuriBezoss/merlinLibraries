#ifndef Hardware_gpioOut_dummy_H
#define Hardware_gpioOut_dummy_H

#include <Hardware_gpioOut.h>

class Hardware_gpioOut_dummy: public Hardware_gpioOut {
public:

    explicit Hardware_gpioOut_dummy(uint16_t pin): Hardware_gpioOut(pin){};

    bool getState() override {
        return state;
    }

    void setState(bool s) override {
        state = s;
    }

};


#endif //Hardware_gpioOut_dummy_H
