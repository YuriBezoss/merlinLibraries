//
// Created by Sparrow on 4/6/2018.
//

#ifndef ARDU_HARDWARE_UART_ARDU_H
#define ARDU_HARDWARE_UART_ARDU_H

#include <Hardware_uart.h>
#include <stdint-gcc.h>
#include <Arduino.h>

class Hardware_uart_ardu: public Hardware_uart {

public:

    explicit Hardware_uart_ardu(HardwareSerial *uart, uint32_t baudrate) {
        Hardware_uart_ardu::uart = uart;
        Hardware_uart_ardu::baudrate = baudrate;
        uart->begin(baudrate);
    }

    void setBaudrate(uint32_t baudrate) override {
        Hardware_uart_ardu::baudrate = baudrate;
    };

    uint32_t getBaudrate() override {
        return baudrate;
    };

    uint32_t available() override {
        return uart->available();
    };

    uint8_t read() override {
        return uart->read();
    };

    void write(uint8_t byte) override {
        uart->write(byte);
    };

    void write(const uint8_t *byte, uint32_t size) override {
        for (uint32_t i = 0; i < size; ++i) {
            uart->write(byte[i]);
        }
    };

protected:

    HardwareSerial *uart = nullptr;
    uint32_t baudrate;
};


#endif //ARDU_HARDWARE_UART_ARDU_H
