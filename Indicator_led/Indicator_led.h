#ifndef Indicator_singleLed_h
#define Indicator_singleLed_h


#include <Hardware_gpioOut.h>

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
