#ifndef Schedulable_h
#define Schedulable_h

#include <stdint-gcc.h>

class Schedulable {
public:
    virtual void update(float deltaTime) = 0;

	uint8_t getSchedulingPeriod() {
		return schedulingPeriod;
	}

protected:
	uint8_t schedulingPeriod = 1;

};

#endif //Schedulable_h
