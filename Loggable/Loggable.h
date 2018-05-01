#ifndef Loggable_H
#define Loggable_H

#include <Logger.h>

/**
 * Abstract Loggable class that has to be implemented by any classes that should by added as a Loggable to the LoggingManager
 */
class Loggable {

public:

    /**
     * Defines which data is logged via LoggingManager. It is called via the update function of the LoggingManager.
     * For example, if we want to log the system time, we call printData(logger, true) first to get the header.
     * Then we call printData(logger, false) once every code cycle (all of that is done by the LoggingManager).
     * The output looks something like:
     *
     * systemTime,
     * 0,
     * 1,
     * 2,
     * ...
     *
     * @param logger defines the logger we use for logging
     * @param printHeader if true, header information is printed, otherwise current data is printed
     * @return true if data was logged
     */
    virtual bool printData(Logger *logger, bool printHeader) = 0;

    // activates logging if set to true
    void setLoggingActive(bool b) {
        loggingActive = b;
    }

protected:

    bool loggingActive = false;

};

#endif //Loggable_H
