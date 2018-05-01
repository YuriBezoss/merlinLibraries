#include "Math_basic.h"
#include <math.h>


////////////////////
// check numbers
////////////////////
float Math_basic::isInf(float a) {
    return !isfinite(a);
}

float Math_basic::isNan(float a) {
    return __isnanf(a);
}

float Math_basic::fmodSafe(float a, float denom){
    if(denom == 0.f) {
        return 0;
    }
    return fmodf(a,denom);
}


////////////////////
// map and constrain
////////////////////
float Math_basic::mapNumber(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float Math_basic::constrainNumber(float amt, float low, float high) {
    return  ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

uint32_t Math_basic::constrainNumber(uint32_t amt, uint32_t low, uint32_t high) {
    return  ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

int32_t Math_basic::constrainNumber(int32_t amt, int32_t low, int32_t high) {
    return  ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

float Math_basic::getAbs(float a){
    return fabsf(a);
}

float Math_basic::getMax(float a, float b) {
    return fmaxf(a,b);
}

float Math_basic::getMin(float a, float b) {
    return fminf(a,b);
}

float Math_basic::getSign(float a) {
    return a > 0.f ? 1.f : a < 0.f ? -1.f : 0.f;
}

float Math_basic::toRad(float a) {
    return a*0.01745329252f; // *pi/180
}

float Math_basic::toDeg(float a) {
    return a*57.2957795131f; // *180/pi
}


////////////////////
// sqrt
////////////////////
// checks input ranges and ensures valid value as output. If a negative number is given 0 is returned. The reasoning is
// that a negative number for sqrt() is usually caused by small numerical rounding errors, and the real input should
// have been zero.
float Math_basic::sqrtSafe(float v) {
    float ret = sqrtf(v);
    if (isNan(ret)) { return 0; }
    return ret;
}

float Math_basic::square(float v) {
    return v*v;
}

////////////////////
// trigonometric formulas
////////////////////
float Math_basic::sin(float a){
    return sinf(a);
}

float Math_basic::cos(float a){
    return cosf(a);
}

float Math_basic::tan(float a){
    return tanf(a);
}

float Math_basic::asinSafe(float a){
    a = Math_basic::constrainNumber(a, -1.f, 1.f);
    return asinf(a);
}

float Math_basic::acosSafe(float a){
    a = Math_basic::constrainNumber(a, -1.f, 1.f);
    return acosf(a);
}

float Math_basic::atan(float a) {
    return atanf(a);
}

float Math_basic::atan2Safe(float a, float b){
    if(a == 0 && b == 0){
        return 0;
    } else {
        return atan2f(a,b);
    }

}

////////////////////
// more functions
////////////////////
float Math_basic::pow10(float e) {
    return powf(10,e);
}

float Math_basic::pow(float b, float e) {
    return powf(b,e);
}

float Math_basic::logSafe(float a) {
    a = Math_basic::getMax(a, 0);
    return logf(a);
}

float Math_basic::exp(float a) {
    return expf(a);
}
