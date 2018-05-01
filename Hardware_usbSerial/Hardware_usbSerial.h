#ifndef Hardware_usbSerial_H
#define Hardware_usbSerial_H


#include <stdint-gcc.h>

/**
 * Hardware usb serial interface
 * For example, usb serial can be used to establish a serial communication between a computer and an arduino board via usb
 */
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
