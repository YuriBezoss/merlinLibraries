#ifndef Schedulable_h
#define Schedulable_h

#include <stdint-gcc.h>

class Schedulable {
public:
    virtual void update(float deltaTime) = 0;

	uint8_t getExecutionPeriod() {
		return executionPeriod;
	}

protected:
	uint8_t executionPeriod = 1;

};

#endif //Schedulable_h
