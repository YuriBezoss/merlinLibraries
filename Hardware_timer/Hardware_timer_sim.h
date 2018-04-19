#ifndef Hardware_timer_dummy_H
#define Hardware_timer_dummy_H

#include <Hardware_timer.h>


class Hardware_timer_sim: public Hardware_timer {
public:

    uint32_t getMillis() override {
        return getMicros()/1000;
    }

    uint32_t getMicros() override {
        return (microSeconds++);
    }

    void delayMillis(uint32_t ms) override {
        microSeconds += ms*1000;
    }

    void delayMicros(uint32_t us) override {
        microSeconds += us;
    }

protected:

    uint32_t microSeconds = 0;

};


#endif //Hardware_timer_dummy_H

