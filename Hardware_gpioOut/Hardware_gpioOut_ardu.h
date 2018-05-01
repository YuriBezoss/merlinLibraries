#ifndef Hardware_gpioOut_ardu_H
#define Hardware_gpioOut_ardu_H

#include <Arduino.h>
#include <Hardware_gpioOut.h>

class Hardware_gpioOut_ardu: public Hardware_gpioOut {
public:

    explicit Hardware_gpioOut_ardu(uint16_t pin): Hardware_gpioOut(pin){
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    };

    bool getState() override {
        return state;
    }

    void setState(bool s) override {
        state = s;
        digitalWrite(pin, state);
    }

};


#endif //Hardware_gpioOut_ardu_H
