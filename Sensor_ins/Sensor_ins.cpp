#include "Sensor_ins.h"

void Sensor_ins::update(float deltaTime) {

    // update hardware sensor
    inertialHardwareSensor->update();

    // read out data if new data is available
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

