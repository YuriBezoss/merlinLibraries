#ifndef Hardware_timer_H
#define Hardware_timer_H

#include <stdint-gcc.h>

/**
 * Hardware timer interface
 */
class Hardware_timer{

public:
    virtual uint32_t getMillis() = 0; // get system time in ms
    virtual uint32_t getMicros() = 0; // get system time in us
    virtual void delayMillis(uint32_t ms) = 0; // pause code for ms milliseconds
    virtual void delayMicros(uint32_t us) = 0;// pause code for us microseconds

};

#endif //Hardware_timer_H
