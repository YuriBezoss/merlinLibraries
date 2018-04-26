#include "Action_demoMerlin.h"

void Action_demoMerlin::update(float deltaTime) {

    if(inStartCmdReceived->available) {
        actionRunning = inStartCmdReceived->value;
    }

    if(actionRunning) {
        if(inTiltingAngle->available) {
            tiltingLed->setState(inTiltingAngle->value > 45.f/180.f * Math_basic::PI_CONSTANT);
        }

        if(inMotion->available) {
            motionLed->setState(inMotion->value);
        }
    } else {
        tiltingLed->setState(false);
        motionLed->setState(false);
    }

}
