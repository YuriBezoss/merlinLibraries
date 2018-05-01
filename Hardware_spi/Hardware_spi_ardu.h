#ifndef Hardware_spi_ardu_h
#define Hardware_spi_ardu_h


#include <Arduino.h>
#include <SPI.h>
#include <Hardware_spi.h>

class Hardware_spi_ardu : public Hardware_spi{
public:

    Hardware_spi_ardu() {
        init();
    }

	Hardware_spi_ardu(uint8_t cs, uint8_t clock, uint8_t mosi, uint8_t miso):
            cs(cs),
            clock(clock),
            mosi(mosi),
            miso(miso) {
        init();
	}

	void setBaudrate(uint32_t baudrate) override {
		Hardware_spi_ardu::baudrate = baudrate;
	};
	
	void beginTransaction() override {
		SPI.beginTransaction(SPISettings(baudrate, MSBFIRST, SPI_MODE0));
		setCSstate(false);
	}

	uint8_t transfer(uint8_t data) override {
		uint8_t newdata = SPI.transfer(data);
		return newdata;
	}

	void transfer(uint8_t *txData, uint8_t *rxData, uint8_t size) override {
		SPI.transfer(txData, rxData, size);
	};

	void endTransaction() override {
		SPI.endTransaction();
		setCSstate(true);
	}

private:

	void init() {
		SPI.setSCK(clock);
		SPI.setMOSI(mosi);
		SPI.setMISO(miso);
		pinMode(cs, OUTPUT);
		setCSstate(true);
		SPI.begin();
	}

    void setCSstate(bool state) {
		digitalWrite(cs, state);
	}

	uint8_t cs = 10; // cs pin
	uint8_t clock = 14; // clock pin
	uint8_t mosi = 11; // master out pin
	uint8_t miso = 12; // master in pin

	uint32_t baudrate = 1000000;
};

#endif //Hardware_spi_ardu_h
