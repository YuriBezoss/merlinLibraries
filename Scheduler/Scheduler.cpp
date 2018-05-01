#include <Math_basic.h>
#include "Scheduler.h"

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
void Scheduler::addTask(Schedulable *schedulable){
    // if too many tasks were added, a hardFault error is thrown.
    if(numTasks >= SCHEDULABLES_MAX){ Logger::hardFault("ERROR in Scheduler: Too many tasks added. Increase SCHEDULABLES_MAX."); };

    schedulables[numTasks] = schedulable;
    numTasks++;
}

void Scheduler::update(){

    // If the clockTime is larger than or equal to the cyclePeriod, all tasks are updated.
    // deltaTimeOffset ensures that the actual cycle period equals the defined one (cyclePeriod). We use here a very simple
    // control loop similar to a P-control (see https://en.wikipedia.org/wiki/Proportional_control)
    if(cycleTimer.getClockTime() >= (cyclePeriod - Math_basic::constrainNumber(deltaTimeOffset, -8e-6f, 8e-6f))){

        deltaTime = cycleTimer.getLastClockTimeAndRestartClock();
        deltaTimeOffset += (deltaTime - cyclePeriod);

        loopCounter++;

        // skip first run since deltaTime has not a proper value yet
        if(firstRun) {
            firstRun = false;
            deltaTimeOffset = 0.f;
            return;
        }

        for (uint16_t i = 0; i < numTasks; ++i) {
            taskDeltaTimes[i] += deltaTime;
            if(loopCounter % schedulables[i]->getSchedulingPeriod() == 0){
                runTask(i);
            }
        }
	}

}


void Scheduler::runTask(uint16_t i) {
    taskTimer.startClock();
    schedulables[i]->update(taskDeltaTimes[i]);
    taskExecutionTimes[i] = taskTimer.stopClock();
    taskDeltaTimes[i] = 0.f;
}



