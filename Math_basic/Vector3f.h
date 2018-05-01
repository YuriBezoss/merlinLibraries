#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <Math_basic.h>

class Vector3f {
public:
    float x, y, z;

    // trivial constructor
    Vector3f() {
        x = y = z = 0;
    }

    // setting constructor
    Vector3f(const float x0, const float y0, const float z0) : x(x0), y(y0), z(z0) {}

    // function call operator
    void operator ()(const float x0, const float y0, const float z0) {
        x = x0; y = y0; z = z0;
    }

    // function call operator
    void operator ()(const Vector3f &v) {
        x = v.x; y = v.y; z = v.z;
    }

    void clone(Vector3f *v){
        v->x=x;
        v->y=y;
        v->z=z;
    }

    Vector3f *clone(){
        return new Vector3f(x,y,z);
    }

    float getAt(int i){
        if(i==0) return x;
        if(i==1) return y;
        if(i==2) return z;
        return 0;
    }
    void setAt(int i, float v){
        if(i==0) x=v;
        if(i==1) y=v;
        if(i==2) z=v;
    }

    // check if any element is NAN
    bool isNan() {
        return Math_basic::isNan(x) || Math_basic::isNan(y) || Math_basic::isNan(z);
    }

    // check if any element is infinity
    bool isInf() {
        return Math_basic::isInf(x) || Math_basic::isInf(y) || Math_basic::isInf(z);
    }


    ///////////////////////////
    // compare operators
    ///////////////////////////
    // test for equality
    bool operator ==(const Vector3f &v) {
        return (x==v.x && y==v.y && z==v.z);
    }

    // test for inequality
    bool operator !=(const Vector3f &v) {
        return (x!=v.x || y!=v.y || z!=v.z);
    }


    ///////////////////////////
    // basic arithmetic operators
    ///////////////////////////
    // negation
    Vector3f operator - () const { return Vector3f(-x,-y,-z); }

    // addition
    Vector3f operator + (const Vector3f &v) const { return Vector3f(x+v.x, y+v.y, z+v.z); }

    // subtraction
    Vector3f operator - (const Vector3f &v) const { return Vector3f(x-v.x, y-v.y, z-v.z); }

    // addition
    Vector3f &operator += (const Vector3f &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }

    // subtraction
    Vector3f &operator -= (const Vector3f &v) { x-=v.x; y-=v.y; z-=v.z;return *this; }

    // uniform scaling
    Vector3f &operator *= (const float num) { x*=num; y*=num; z*=num;return *this; }

    // uniform scaling
    Vector3f &operator /= (const float num) { x/=num; y/=num; z/=num;return *this; }

    // multiply element by element
    Vector3f &operator ^= (const Vector3f &v) { x*=v.x; y*=v.y; z*=v.z;return *this; }

    // uniform scaling
    Vector3f operator * (const float num) const { Vector3f temp(*this);return temp*=num; }

    // uniform scaling
    Vector3f operator / (const float num) const { Vector3f temp(*this);return temp/=num; }

    // uniform scaling
    Vector3f operator ^ (const Vector3f &v) const { Vector3f temp(*this);return temp^=v; }


    ///////////////////////////
    // vector arithmetic operators
    ///////////////////////////
    // dot product
    float operator * (const Vector3f &v) const { return x*v.x + y*v.y + z*v.z; }

    // cross product
    Vector3f operator %(const Vector3f &v) const { Vector3f temp(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);return temp; }


    ///////////////////////////
    // vector functions
    ///////////////////////////
    // gets the norm of this vector squared
    float normSquared() const { return (float)(*this * *this); }

    // gets the norm of this vector
    float norm() const { return Math_basic::sqrtSafe(normSquared()); }

    // zero the vector
    void zero() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    // normalizes this vector
    bool normalize() {
        float n = norm();
        if(n == 0){
            zero();
            return false;
        } else {
            *this/= norm();
            return true;
        }
    }

    // return the normalized version of this vector
    Vector3f normalized() {
        float n = norm();
        if(n == 0){
            zero();
            return *this;
        } else {
            return *this/= norm();
        }
    }

    // compute the angle between this vector and another vector
    float angle(const Vector3f &v2) {
        float n = norm();
        if(n == 0 || v2.norm() == 0){
            return 0;
        } else {
            return (float)Math_basic::acosSafe(((*this)*v2) / (this->norm() * v2.norm()));
        }
    }

    Vector3f toRad() {
        Vector3f temp(*this);
        return temp*0.01745329252f; // *pi/180
    }

    Vector3f toDeg() {
        Vector3f temp(*this);
        return temp*57.2957795131f; // *180/pi
    }

};


#endif // VECTOR3F_H
