#ifndef Hardware_timer_H
#define Hardware_timer_H

#include <stdint-gcc.h>


class Hardware_timer{

public:
    virtual uint32_t getMillis() = 0;
    virtual uint32_t getMicros() = 0;
    virtual void delayMillis(uint32_t ms) = 0;
    virtual void delayMicros(uint32_t us) = 0;

};

#endif //Hardware_timer_H
