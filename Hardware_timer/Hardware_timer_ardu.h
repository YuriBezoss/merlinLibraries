#ifndef Hardware_timer_ardu_H
#define Hardware_timer_ardu_H

#include <Arduino.h>
#include <Hardware_timer.h>


class Hardware_timer_ardu: public Hardware_timer {

public:

    uint32_t getMillis() override {
        return millis();
    }

    uint32_t getMicros() override {
        return micros();
    }

    void delayMillis(uint32_t ms) override {
        delay(ms);
    }

    void delayMicros(uint32_t us) override {
        delayMicroseconds(us);
    }

};


#endif //Hardware_timer_ardu_H

