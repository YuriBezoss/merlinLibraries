#ifndef Hardware_inertialSensor_h
#define Hardware_inertialSensor_h


#include <stdint-gcc.h>
#include <Math_vector3f.h>

class Hardware_inertialSensor {

public:

    virtual void update() = 0;
    virtual bool isDataAvailable() = 0;

    virtual Vector3f getAccel() = 0;
    virtual Vector3f getAccelRaw() = 0;

    virtual Vector3f getGyro() = 0;
    virtual Vector3f getGyroRaw() = 0;

    virtual float getTemp() = 0;
    virtual float getTempRaw() = 0;

};


#endif //Hardware_inertialSensor_h
