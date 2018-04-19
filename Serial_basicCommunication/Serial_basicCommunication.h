#ifndef Serial_simpleReader_H
#define Serial_simpleReader_H

#include <Hardware_uart.h>
#include <Hardware_usbSerial.h>
#include <Timer.h>

class Serial_basicCommunication {

public:

    struct Message {
        static const uint16_t MSG_LENGTH_MAX = 500;
        uint8_t msg[MSG_LENGTH_MAX] = {};
        uint32_t msgLength = 0;
        uint32_t bytesLostCounter = 0;

        void reset() {
            msgLength = 0;
            bytesLostCounter = 0;
        }
    };

    explicit Serial_basicCommunication(Hardware_uart *uart, Hardware_timer *hardwareTimer) {
        Serial_basicCommunication::uart = uart;
        timer = new Timer(hardwareTimer);
        useUart = true;
    }

    explicit Serial_basicCommunication(Hardware_usbSerial *usbSerial, Hardware_timer *hardwareTimer) {
        Serial_basicCommunication::usbSerial = usbSerial;
        timer = new Timer(hardwareTimer);
        useUart = false;
    }

    bool readoutRxBuffer();

    bool isNewMessageAvailable();

    Message getMessage();

    void sendMessage(Message message);

protected:

    uint32_t dataAvailable();

    Hardware_uart *uart = nullptr;
    Hardware_usbSerial *usbSerial = nullptr;
    Timer *timer = nullptr;
    bool useUart = true;

    Message message;

    bool newMessageAvailable = true;

};


#endif //Serial_simpleReader_H
