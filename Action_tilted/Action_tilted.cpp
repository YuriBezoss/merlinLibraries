#include "Action_tilted.h"

void Action_tilted::update(float deltaTime) {
    if(inTiltingAngle->available) {
        led->setState(inTiltingAngle->value > 45.f/180.f * Math_basic::PI_CONSTANT);
    }
}