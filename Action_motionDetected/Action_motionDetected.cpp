#include "Action_motionDetected.h"

void Action_motionDetected::update(float deltaTime) {
    if(inMotion->available) {
        led->setState(inMotion->value);
    }
}
