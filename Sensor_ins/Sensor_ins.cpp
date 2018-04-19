#include "Sensor_ins.h"

void Sensor_ins::update(float deltaTime) {

    inertialHardwareSensor->update();

    if(inertialHardwareSensor->isDataAvailable()) {
        outAccel.available = true;
        outAccel.value = inertialHardwareSensor->getAccel();

        outGyro.available = true;
        outGyro.value = inertialHardwareSensor->getGyro();

    } else {
        outAccel.available = false;
        outGyro.available = false;
    }

}

