#ifndef Indicator_singleLed_h
#define Indicator_singleLed_h


#include <Hardware_gpioOut.h>

/**
 * Simple led library
 * Use case:
 *      1. Led is connected to a gpio pin of the MCU (do not forget the series resistance for the Led)
 *      2. Hardware_gpioOut object is created that controls this gpio
 *      3. This object is passed to Indicator_led constructor
 */
class Indicator_led {

public:

    explicit Indicator_led(Hardware_gpioOut *gpioOut) {
        Indicator_led::gpioOut = gpioOut;
    }

    bool getState() const { return gpioOut->getState(); };

    void setState(bool s){
        gpioOut->setState(s);
    };

    void flipState(){
        gpioOut->setState(!gpioOut->getState());
    };

protected:

    Hardware_gpioOut *gpioOut = nullptr;

};


#endif //Indicator_singleLed_h
