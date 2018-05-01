#include <Math_basic.h>
#include "Scheduler.h"

///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
void Scheduler::addTask(Schedulable *schedulable){
    if(numTasks >= SCHEDULABLES_MAX){ Logger::hardFault("ERROR in Scheduler: Too many tasks added. Increase SCHEDULABLES_MAX."); };

    schedulables[numTasks] = schedulable;
    numTasks++;
}

void Scheduler::update(){

    if(cycleTimer.getClockTime() >= (cyclePeriod - Math_basic::constrainNumber(deltaTimeOffset, -8e-6f, 8e-6f))){

        deltaTime = cycleTimer.getLastClockTimeAndRestartClock();
        deltaTimeOffset += (deltaTime - cyclePeriod); // falls letzter Cycle zu lange gedauert hat, wird naechste dementsprechend verkuerzt.

        loopCounter++;

        // skip first run since dtime has not a proper value yet
        if(firstRun) {
            firstRun = false;
            deltaTimeOffset = 0.f;
            return;
        }

        for (uint16_t i = 0; i < numTasks; ++i) {
            taskCycleTimes[i] += deltaTime;
            if(loopCounter % schedulables[i]->getSchedulingPeriod() == 0){
                runTask(i);
            }
        }
	}

}


void Scheduler::runTask(uint16_t i) {
    taskTimer.startClock();
    schedulables[i]->update(taskCycleTimes[i]);
    taskExecutionTimes[i] = taskTimer.stopClock();
    taskCycleTimes[i] = 0.f;
}



