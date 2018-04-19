#include "Filter_tiltingAngle.h"

void Filter_tiltingAngle::update(float deltaTime) {

    if(inAccel->available) {
        Vector3f z(0,0,1);
        outTiltingAngle.value = z.angle(inAccel->value);
        outTiltingAngle.available = true;
    } else {
        outTiltingAngle.available = false;
    }

}
