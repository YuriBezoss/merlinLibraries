#ifndef Timer_H
#define Timer_H

#include <stdint-gcc.h>
#include <Hardware_timer.h>
#include <Logger.h>

class Timer {

public:

	explicit Timer(Hardware_timer *hardwareTimer) {
		Timer::hardwareTimer = hardwareTimer;
	}

    float getSystemTime();
    uint32_t getSystemTimeUs();

    void delaySeconds(float seconds);
    void delayMillis(uint32_t ms);
    void delayMicros(uint32_t us);

    void startClock();
    float stopClock();
    float getClockTime();
    float getLastClockTimeAndRestartClock();
    bool isClockRunning();
    void resetClock();

protected:

    uint32_t calculateDeltaTime(uint32_t newTime, uint32_t oldTime);

	Hardware_timer *hardwareTimer = nullptr;

    bool clockRunning = false;
    float clockTime = 0.f;
    uint32_t startTimeUs = 0;
    uint32_t newStartTimeUs = 0;

};


#endif //Timer_H
