#include "Timer.h"

///////////////////////////////////////////////////////////////////////////
// timer
///////////////////////////////////////////////////////////////////////////
/**
 * return system time in s (time since MCU was started)
 * @return system time in s
 */
float Timer::getSystemTime() {
    return hardwareTimer->getMicros()*1e-6f;
}

/**
 * return system time in us (time since MCU was started)
 * @return system time in us
 */
uint32_t Timer::getSystemTimeUs() {
    return hardwareTimer->getMicros();
}

void Timer::delaySeconds(float seconds) {
    auto us = (uint32_t)(seconds*1e6f);
    delayMicros(us);
}

void Timer::delayMillis(uint32_t ms) {
    hardwareTimer->delayMillis(ms);
}

void Timer::delayMicros(uint32_t us) {
    hardwareTimer->delayMicros(us);
}


///////////////////////////////////////////////////////////////////////////
// clock
///////////////////////////////////////////////////////////////////////////
/**
 * start stopwatch
 */
void Timer::startClock(){
    startTimeUs = hardwareTimer->getMicros();
    clockRunning = true;
}

/**
 * stop stopwatch
 * @return current clock time in s
 */
float Timer::stopClock(){
    if (!clockRunning) {
        return 0;
    }
    clockTime = calculateDeltaTime(hardwareTimer->getMicros(), startTimeUs) * 1e-6f;
    clockRunning = false;
    return clockTime;
}

/**
 * @return current clock time in s
 */
float Timer::getClockTime(){
    if (!clockRunning) {
        return 0;
    }
    newStartTimeUs = hardwareTimer->getMicros();
    clockTime = calculateDeltaTime(newStartTimeUs, startTimeUs) * 1e-6f;
    return clockTime;
}

/**
 * restart the clock
 * @return clock time in s which was also returned when getClockTime() was called the last time
 */
float Timer::getLastClockTimeAndRestartClock(){
    if (!clockRunning) {
        return 0;
    }
    startTimeUs = newStartTimeUs;
    return clockTime;
}

bool Timer::isClockRunning(){
    return clockRunning;
}

void Timer::resetClock(){
    clockRunning = false;
}

uint32_t Timer::calculateDeltaTime(uint32_t newTime, uint32_t oldTime) {
    if(newTime > oldTime) {
        return (newTime - oldTime);
    } else {
        return (UINT32_MAX - oldTime) + newTime; // overflow protection
    }
}

