#ifndef Hardware_usbSerial_H
#define Hardware_usbSerial_H


#include <stdint-gcc.h>

class Hardware_usbSerial {

public:

    virtual void setBaudrate(uint32_t baudrate) = 0;
    virtual uint32_t getBaudrate() = 0;

    virtual uint8_t read() = 0;
    virtual uint16_t available() = 0;
    virtual void write(uint8_t byte) = 0;
    virtual void write(const uint8_t *byte, uint32_t size) = 0;

};


#endif //Hardware_usbSerial
