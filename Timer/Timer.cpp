#include "Timer.h"

///////////////////////////////////////////////////////////////////////////
// timer
///////////////////////////////////////////////////////////////////////////
float Timer::getSystemTime() {
    return hardwareTimer->getMicros()*1e-6f;
}

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
void Timer::startClock(){
    startTimeUs = hardwareTimer->getMicros();
    clockRunning = true;
}

float Timer::stopClock(){
    if (!clockRunning) {
        return 0;
    }
    clockTime = calculateDeltaTime(hardwareTimer->getMicros(), startTimeUs) * 1e-6f;
    clockRunning = false;
    return clockTime;
}

float Timer::getClockTime(){
    if (!clockRunning) {
        return 0;
    }
    newStartTimeUs = hardwareTimer->getMicros();
    clockTime = calculateDeltaTime(newStartTimeUs, startTimeUs) * 1e-6f;
    return clockTime;
}

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

