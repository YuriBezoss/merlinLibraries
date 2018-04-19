#ifndef Hardware_spi_H
#define Hardware_spi_H


#include <stdint-gcc.h>

class Hardware_spi {

public:

    virtual void beginTransaction() = 0;
    virtual uint8_t transfer(uint8_t data) = 0;
    virtual void transfer(uint8_t *txData, uint8_t *rxData, uint8_t size) = 0;
    virtual void endTransaction() = 0;

    virtual void setBaudrate(uint32_t baudrate) = 0;

};


#endif //Hardware_spi
