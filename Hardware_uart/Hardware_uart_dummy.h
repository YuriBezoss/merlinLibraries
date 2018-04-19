#ifndef Hardware_uart_dummy_H
#define Hardware_uart_dummy_H


#include <Hardware_uart.h>
#include <stdint-gcc.h>

class Hardware_uart_dummy: public Hardware_uart {

public:

    void setBaudrate(uint32_t baudrate) override {};

    uint32_t getBaudrate() override {
        return 115200;
    };

    uint16_t available() override {
        return 0;
    };

    uint8_t read() override {
        return 0;
    };

    void write(uint8_t byte) override {
    };

};


#endif //Hardware_uart_dummy_H
