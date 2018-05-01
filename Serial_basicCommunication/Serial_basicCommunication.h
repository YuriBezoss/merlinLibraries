#ifndef Serial_basicCommunication_H
#define Serial_basicCommunication_H

#include <Hardware_uart.h>
#include <Hardware_usbSerial.h>
#include <Timer.h>

/**
 * Handles serial communication. Supports uart and usbSerial.
 *
 */
class Serial_basicCommunication {

public:

    /**
     * Message struct is used to temporarily store a message received on the rx line or to send a message via the tx line
     */
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

    /**
     * Read out rx buffer. Returns true if new message has been received and no additional data has been sent within a certain
     * amount of time. That means that the data transfer has finished.
     * @return
     */
    bool readoutRxBuffer();

    /**
     * @return if a new rx message is available
     */
    bool isNewMessageAvailable();

    /**
     * @return newest rx message
     */
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


#endif //Serial_basicCommunication_H
