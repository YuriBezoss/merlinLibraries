#ifndef Hardware_inertialSensor_h
#define Hardware_inertialSensor_h


#include <stdint-gcc.h>
#include <Math_vector3f.h>

/**
 * Interface for inertial sensors (accel and gyro sensors)
 */
class Hardware_inertialSensor {

public:

    virtual void update() = 0; // read out new data from sensor if available
    virtual bool isDataAvailable() = 0; // is new data available

    virtual Vector3f getAccel() = 0; // accel vector in m/s^2
    virtual Vector3f getAccelRaw() = 0; // raw accel vector provided by the sensor

    virtual Vector3f getGyro() = 0; // gyro vector in m/s^2
    virtual Vector3f getGyroRaw() = 0; // raw gyro vector provided by the sensor

    virtual float getTemp() = 0; // temperature in celsius
    virtual float getTempRaw() = 0; // raw temperature provided by the sensor

};


#endif //Hardware_inertialSensor_h
