#ifndef Schedulable_h
#define Schedulable_h

#include <stdint-gcc.h>

/**
 * Abstract Schedulable class that has to be implemented by any classes that should by added as a Schedulable to the Scheduler
 */
class Schedulable {
public:
    virtual void update(float deltaTime) = 0;

	uint8_t getSchedulingPeriod() {
		return schedulingPeriod;
	}

protected:
	uint8_t schedulingPeriod = 1; // if 1, this Schedulable is called every Scheduler-cycle; if 2, it is called every second cycle; and so on

};

#endif //Schedulable_h
