#ifndef Timer_H
#define Timer_H

#include <stdint-gcc.h>
#include <Hardware_timer.h>
#include <Logger.h>

/**
 * Timer provides the basic timer functions (e.g. getSystemTime, delayMillis) and a stopwatch.
 */
class Timer {

public:

	explicit Timer(Hardware_timer *hardwareTimer) {
		Timer::hardwareTimer = hardwareTimer;
	}

    float getSystemTime(); // return system time in s (time since MCU was started)
    uint32_t getSystemTimeUs(); // return system time in us (time since MCU was started)

	// pauses the code execution for the defined time
    void delaySeconds(float seconds);
    void delayMillis(uint32_t ms);
    void delayMicros(uint32_t us);

	// stopwatch functions
    void startClock();
    float stopClock();
    float getClockTime(); // returns the current clock time
    float getLastClockTimeAndRestartClock(); // restart the clock and return that clock time which was also returned when getClockTime() was called the last time.
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
