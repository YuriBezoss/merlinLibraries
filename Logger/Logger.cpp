#include "Logger.h"

///////////////////////////////////////////////////////////////////////////
// Debugger and HardFault
///////////////////////////////////////////////////////////////////////////
Hardware_timer *Logger::hardwareTimer = nullptr;
Hardware_uart *Logger::uart = nullptr;
Hardware_usbSerial *Logger::usbSerial = nullptr;
Logger *Logger::instance = nullptr;
bool Logger::started = false;
bool Logger::useUart = false;

///////////////////////////////////////////////////////////////////////////
// Basic printing functions
///////////////////////////////////////////////////////////////////////////
void Logger::print(const char* characters) {
    uint32_t i = 0;
    while(characters[i] != '\0') {
        i++;
    }
    write((uint8_t*)characters, i);
}

void Logger::print(char character) {
    write((uint8_t)character);
}

void Logger::print(int8_t number) {
    print((int32_t)number);
}

void Logger::print(uint8_t number) {
    print((uint32_t)number);
}

void Logger::print(int16_t number) {
    print((int32_t)number);
}

void Logger::print(uint16_t number) {
    print((uint32_t)number);
}

void Logger::print(int32_t number) {
    if(number < 0) {
        printInteger((uint32_t)(-number), true);
    } else {
        printInteger((uint32_t)number, false);
    }
}

void Logger::print(uint32_t number) {
    printInteger(number, false);
}

void Logger::printInteger(uint32_t number, bool isNegative) {
    if(number == 0) {
        write(('0'));
        return;
    }

    uint8_t bufferLength = 12;
    uint8_t buffer[bufferLength];
    uint8_t bufferPosition = bufferLength;
    do {
        buffer[--bufferPosition] = (uint8_t)(number % 10) + '0';
        number /= 10;
    } while(number);

    if(isNegative) {
        buffer[--bufferPosition] = '-';
    }

    write(&buffer[bufferPosition], bufferLength-bufferPosition);
}

void Logger::print(float number, uint8_t digits) {
    print((double)number, digits);
}

void Logger::print(double number, uint8_t digits) {

    if(Math_basic::isInf((float)number)) {
        return print("inf");
    }
    if(Math_basic::isNan((float)number)) {
        return print("nan");
    }

    // print sign
    bool isNegative = false;
    if(number < 0) {
        isNegative = true;
        number = -number;
    }

    // round up number
    float roundUp = 0.5;
    for (int k = 0; k < digits; ++k) {
        roundUp *= 0.1;
    }
    number += roundUp;

    // print integer part
    auto integerPart = (uint32_t)number;
    printInteger(integerPart, isNegative);

    if(digits == 0) {
        return;
    }

    // print dot
    write('.');

    // get decimal part
    double decimalPart_double = number - integerPart;
    for (uint8_t i = 0; i < digits; ++i) {
        decimalPart_double *= 10;
    }

    // print decimalPart
    auto decimalPart_int = (uint32_t)decimalPart_double;
    uint8_t buffer[digits] = {};
    for (int j = 0; j < digits; ++j) {
        buffer[digits-1-j] = (uint8_t)(decimalPart_int % 10) +'0';
        decimalPart_int /= 10;
    }
    write(buffer, digits);
}


void Logger::println(const char *characters) {
    print(characters);
    newLine();
}

void Logger::println(char character) {
    print(character);
    newLine();
}

void Logger::println(int8_t number) {
    print(number);
    newLine();
}

void Logger::println(uint8_t number) {
    print(number);
    newLine();
}

void Logger::println(int16_t number) {
    print(number);
    newLine();
}

void Logger::println(uint16_t number) {
    print(number);
    newLine();
}

void Logger::println(int32_t number) {
    print(number);
    newLine();
}

void Logger::println(uint32_t number) {
    print(number);
    newLine();
}

void Logger::println(float number, uint8_t digits) {
    print(number, digits);
    newLine();
}

void Logger::println(double number, uint8_t digits) {
    print(number, digits);
    newLine();
}

void Logger::newLine() {
    write('\n');
}

void Logger::write(uint8_t c) {
    if(useUart) {
        uart->write((uint8_t)c);
    } else {
        usbSerial->write(c);
    }
}

void Logger::write(const uint8_t *bytes, uint32_t size) {
    if(useUart) {
        uart->write(bytes, size);
    } else {
        usbSerial->write(bytes, size);
    }
};


///////////////////////////////////////////////////////////////////////////
// Logging Manager
///////////////////////////////////////////////////////////////////////////
void Logger::printLoggable(const char *label, const char *value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, char value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, bool value, bool printHeader) {
    if(!printHeader) {
        print((uint8_t)value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, int8_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, uint8_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, int16_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, uint16_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, int32_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, uint32_t value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, float value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, double value, bool printHeader) {
    if(!printHeader) {
        print(value);
    } else {
        print(label);
    }
    print(",");
}

void Logger::printLoggable(const char *label, Vector3f value, bool printHeader) {
    if(!printHeader) {
        print(value.x); print(",");
        print(value.y); print(",");
        print(value.z); print(",");
    } else {
        print(label);  print("_x,");
        print(label);  print("_y,");
        print(label);  print("_z,");
    }
}






