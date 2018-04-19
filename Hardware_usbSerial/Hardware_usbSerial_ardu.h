#ifndef Hardware_usbSerial_ardu_H
#define Hardware_usbSerial_ardu_H


#include <Arduino.h>
#include <Hardware_usbSerial.h>

class Hardware_usbSerial_ardu: public Hardware_usbSerial {

public:

    explicit Hardware_usbSerial_ardu(usb_serial_class *port) {
        Hardware_usbSerial_ardu::port = port;
        port->begin(baudRate);
    }

    Hardware_usbSerial_ardu(usb_serial_class *port, uint32_t baudRate) {
        Hardware_usbSerial_ardu::port = port;
        Hardware_usbSerial_ardu::baudRate = baudRate;
        port->begin(baudRate);
    }

    usb_serial_class *getPort() const {
        return port;
    }

    void setPort(usb_serial_class *port) {
        Hardware_usbSerial_ardu::port = port;
    }

    uint32_t getBaudrate() override {
        return baudRate;
    }

    void setBaudrate(uint32_t baudRate) {
        Hardware_usbSerial_ardu::baudRate = baudRate;
    }

    uint8_t read() override {
        return port->read();
    };

    uint16_t available() override {
        return port->available();
    };

    void write(uint8_t byte) override {
        port->write((char)byte);
    };

    void write(const uint8_t *byte, uint32_t size) override {
        port->write(byte, size);
    };

protected:
    uint32_t baudRate = 115200;
    usb_serial_class *port = nullptr;

};


#endif //Hardware_usbSerial_ardu_H
