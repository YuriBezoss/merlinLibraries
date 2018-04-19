#include "Filter_motionDetection_ins.h"

void Filter_motionDetection_ins::update(float deltaTime) {

    if(inGyro->available) {
        outMotion.value = (inGyro->value.normSquared() > 0.1);
        outMotion.available = true;
    } else {
        outMotion.available = false;
    }
}