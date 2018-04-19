#ifndef MATH_BASIC_H
#define MATH_BASIC_H

#include <stdint-gcc.h>

namespace Math_basic{

    const static float PI_CONSTANT = 3.1415927f;
    const static float GRAVITY_CONSTANT = 9.8066502f;
    const static float SQRT_2 = 1.4142135f;
    const static float HALF_SQRT_2 = 0.7071067f;

    // check numbers
    float isInf(float a);
    float isNan(float a);
    float fmodSafe(float a, float denom);

    // map and constrain
    float mapNumber(float x, float in_min, float in_max, float out_min, float out_max);
    float constrainNumber(float amt, float low, float high);
    uint32_t constrainNumber(uint32_t amt, uint32_t low, uint32_t high);
    int32_t constrainNumber(int32_t amt, int32_t low, int32_t high);
    float getAbs(float a);
    float getMax(float a, float b);
    float getMin(float a, float b);
    float getSign(float a);
    float toRad(float a);
    float toDeg(float a);

    // sqrt
    float sqrtSafe(float v);
    float square(float v);

    // trigonometric formulas
    float sin(float a);
    float cos(float a);
    float tan(float a);

    float asinSafe(float a);
    float acosSafe(float a);
    float atan(float a);
    float atan2Safe(float a, float b);

    // more functions
    float pow10( float e);
    float pow(float b, float e);

    float logSafe(float a);
    float exp(float a);

};


#endif //MATH_BASIC_H
