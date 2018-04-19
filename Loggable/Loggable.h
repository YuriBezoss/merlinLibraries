#ifndef Loggable_H
#define Loggable_H

#include <Logger.h>

class Loggable {

public:

    virtual bool printData(Logger *logger, bool printHeader) = 0;

    void setLoggingActive(bool b) {
        loggingActive = b;
    }

protected:

    bool loggingActive = false;


};

#endif //Loggable_H
