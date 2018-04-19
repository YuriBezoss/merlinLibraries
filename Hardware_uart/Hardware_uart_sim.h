#ifndef Hardware_uart_sim_H
#define Hardware_uart_sim_H


#include <Hardware_uart.h>
#include <cstdint>
#include <stdint-gcc.h>

class Hardware_uart_sim: public Hardware_uart {

public:

    explicit Hardware_uart_sim(uint16_t serialCmdLength, const char serialCmdPrefix[], uint8_t serialCmdPrefixLength) {
        Hardware_uart_sim::serialCmdPrefix = serialCmdPrefix;
        Hardware_uart_sim::serialCmdPrefixLength = serialCmdPrefixLength;
        bufferLength = serialCmdLength + serialCmdPrefixLength + (uint16_t)1;
        dataArray = new uint8_t[bufferLength];
        createDummyData();
    }

    ~Hardware_uart_sim() {
        delete [] dataArray;
    }

    void setBaudrate(uint32_t baudrate) override {};

    uint32_t getBaudrate() override {
        return 115200;
    };

    uint16_t available() override {
        return bufferLength-bufferOffset;
    }

    uint8_t read() override {
        if(bufferLength-bufferOffset > 0) {
            uint8_t newData = dataArray[bufferOffset];
            bufferOffset++;
            return newData;
        }
        return 0;
    }

    void write(uint8_t byte) override {};

protected:

    void createDummyData() {
        for (int j = 0; j < serialCmdPrefixLength; ++j) {
            dataArray[j] = (uint8_t)serialCmdPrefix[j];
        }

        dataArray[serialCmdPrefixLength] = 'l';
        dataArray[serialCmdPrefixLength + 1] = 'c';
        dataArray[serialCmdPrefixLength + 2] = 'c';

        for (uint16_t i = serialCmdPrefixLength+(uint16_t)3; i < bufferLength-1; i+=3) {
            dataArray[i] = 1;
            dataArray[i+1] = 25;
            dataArray[i+2] = 37;
        }

        uint8_t checkSum = 0;
        for (uint16_t i = serialCmdPrefixLength; i < bufferLength-1; ++i) {
            checkSum += dataArray[i];
        }
        dataArray[bufferLength-1] = checkSum;

        bufferOffset = 0;
    }

    const char *serialCmdPrefix;
    uint8_t serialCmdPrefixLength;

    uint16_t bufferLength;
    uint16_t bufferOffset = 0;
    uint8_t *dataArray;


};


#endif //Hardware_uart_sim_H
