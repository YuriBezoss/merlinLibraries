#include "Serial_basicCommunication.h"

bool Serial_basicCommunication::readoutRxBuffer() {

    newMessageAvailable = false;

    // if new data is available we transfer the data to the message struct
    if(dataAvailable()) {
        while(dataAvailable()) {
            if(message.msgLength < message.MSG_LENGTH_MAX) {
                if(useUart) {
                    message.msg[message.msgLength++] = uart->read();
                } else {
                    message.msg[message.msgLength++] = usbSerial->read();
                }
            } else {
                message.bytesLostCounter++;
            }
        }
        timer->startClock();

    } else {

        // Transferring one byte via uart requires 10 bits (incl. start and stop bit). So we wait at least 12 bits or 12
        // bauds. If no data was received within this time, we can assume that the message transfer has finished.
        float baudrate;
        if(useUart) {
            baudrate = uart->getBaudrate();
        } else {
            baudrate = usbSerial->getBaudrate();
        }

        if(message.msgLength > 0 && timer->getClockTime() > (12.f*1.f/(baudrate)) ) {
            newMessageAvailable = true;
        }
    }

    return newMessageAvailable;
}

bool Serial_basicCommunication::isNewMessageAvailable() {
    return newMessageAvailable;
}

Serial_basicCommunication::Message Serial_basicCommunication::getMessage() {
    Message newMessage = message;
    message.reset();
    return newMessage;
}

void Serial_basicCommunication::sendMessage(Message newMessage) {
    for (uint32_t i = 0; i < newMessage.msgLength; ++i) {
        if(useUart) {
            uart->write(newMessage.msg[i]);
        } else {
            usbSerial->write(newMessage.msg[i]);
        }
    }
}

uint32_t Serial_basicCommunication::dataAvailable() {
    if(useUart) {
        return uart->available();
    } else {
        return usbSerial->available();
    }
}
