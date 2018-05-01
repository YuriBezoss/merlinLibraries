#ifndef Hardware_uart_H
#define Hardware_uart_H

#include <stdint-gcc.h>

/**
 * Hardware uart interface
 */
class Hardware_uart {

public:

    virtual void setBaudrate(uint32_t baudrate) = 0;
    virtual uint32_t getBaudrate() = 0;

    virtual uint32_t available() = 0; // return the number of bytes available in the buffer
    virtual uint8_t read() = 0; // read the next byte in the buffer
    virtual void write(uint8_t byte) = 0; // send a byte via TX line
    virtual void write(const uint8_t *byte, uint32_t size) = 0; // send several bytes via TX line

};


#endif //Hardware_uart
