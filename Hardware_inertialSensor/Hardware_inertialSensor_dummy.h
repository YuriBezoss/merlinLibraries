#ifndef Hardware_inertialSensor_dummy_H
#define Hardware_inertialSensor_dummy_H


#include <Hardware_inertialSensor.h>

class Hardware_inertialSensor_dummy: public Hardware_inertialSensor {
public:

    explicit Hardware_inertialSensor_dummy() = default;

    void update() override {};

    bool isDataAvailable() override { return true; };

    Vector3f getAccel()override { return accel; };
    Vector3f getAccelRaw() override{ return accelRaw; };

    Vector3f getGyro() override { return gyro; };
    Vector3f getGyroRaw() override { return gyroRaw; };

    float getTemp() override { return temp; };
    float getTempRaw() override { return tempRaw; };

protected:

    Vector3f accel = Vector3f(0,0,0);
    Vector3f gyro = Vector3f(0,0,0);
    Vector3f accelRaw = Vector3f(0,0,0);
    Vector3f gyroRaw = Vector3f(0,0,0);

    float temp = 0;
    float tempRaw = 0;

};


#endif //Hardware_inertialSensor_dummy_H
