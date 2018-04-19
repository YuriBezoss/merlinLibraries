#ifndef Logger_h
#define Logger_h

#include <stdint-gcc.h>
#include <Hardware_timer.h>
#include <Hardware_usbSerial.h>
#include <Hardware_uart.h>
#include <Math_vector3f.h>


class Logger {

///////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////
public:

    explicit Logger(Hardware_uart *uart, Hardware_timer *hardwareTimer) {
        Logger::uart = uart;
        Logger::hardwareTimer = hardwareTimer;
        Logger::instance = this;
        Logger::started = true;
        useUart = true;
    }

    explicit Logger(Hardware_usbSerial *usbSerial, Hardware_timer *hardwareTimer) {
        Logger::usbSerial = usbSerial;
        Logger::hardwareTimer = hardwareTimer;
        Logger::instance = this;
        Logger::started = true;
        useUart = false;
    }


protected:
    static Hardware_timer *hardwareTimer; // static has to be defined in cpp-file
    static Hardware_uart *uart; // static has to be defined in cpp-file
    static Hardware_usbSerial *usbSerial; // static has to be defined in cpp-file
    static Logger *instance; // static has to be defined in cpp-file
    static bool started; // static has to be defined in cpp-file
    static bool useUart; // static has to be defined in cpp-file

///////////////////////////////////////////////////////////////////////////
// Basic printing functions
///////////////////////////////////////////////////////////////////////////
public:
    void print(const char characters[]);
    void print(char character);
    void print(int8_t   number);
    void print(uint8_t  number);
    void print(int16_t  number);
    void print(uint16_t number);
    void print(int32_t  number);
    void print(uint32_t number);
    void print(float    number, uint8_t digits = 2);
    void print(double   number, uint8_t digits = 2);

    void println(const char characters[]);
    void println(char character);
    void println(int8_t   number);
    void println(uint8_t  number);
    void println(int16_t  number);
    void println(uint16_t number);
    void println(int32_t  number);
    void println(uint32_t number);
    void println(float    number, uint8_t digits = 2);
    void println(double   number, uint8_t digits = 2);

    void newLine();

protected:

    void printInteger(uint32_t number, bool isNegative);

    void write(uint8_t c);
    void write(const uint8_t *bytes, uint32_t size);

///////////////////////////////////////////////////////////////////////////
// Logging Manager
///////////////////////////////////////////////////////////////////////////
public:

    void printLoggable(const char *label, const char value[], bool printHeader);
    void printLoggable(const char *label, char value, bool printHeader);
    void printLoggable(const char *label, bool     value, bool printHeader);
    void printLoggable(const char *label, int8_t   value, bool printHeader);
    void printLoggable(const char *label, uint8_t  value, bool printHeader);
    void printLoggable(const char *label, int16_t  value, bool printHeader);
    void printLoggable(const char *label, uint16_t value, bool printHeader);
    void printLoggable(const char *label, int32_t  value, bool printHeader);
    void printLoggable(const char *label, uint32_t value, bool printHeader);
    void printLoggable(const char *label, float    value, bool printHeader);
    void printLoggable(const char *label, double   value, bool printHeader);
    void printLoggable(const char *label, Vector3f value, bool printHeader);

///////////////////////////////////////////////////////////////////////////
// Debugger and HardFault
///////////////////////////////////////////////////////////////////////////
public:

    static bool isLogging() {
        return Logger::started;
    };

    static void hardFault(const char *fault){
        if(Logger::started) {
            while(true) {
                instance->println(fault);
                hardwareTimer->delayMillis(100);
            }
        }
    };

    static Logger *debugger(){
        if(Logger::started) {
            return instance;
        }
        return nullptr;
    };

};

#endif //Logger_h


