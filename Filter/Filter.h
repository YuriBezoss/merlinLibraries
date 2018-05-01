#ifndef Filter_H
#define Filter_H

#include <stdint-gcc.h>
#include <Vector3f.h>


///////////////////////////////////////////////////////////////////////////
// basic filter items
///////////////////////////////////////////////////////////////////////////
struct FilterItem{
    bool available = false;
    float deltaTime = 0.f;
};

template<typename T>
struct FilterItem_generic: FilterItem{ T value; };
struct FilterItem_float: FilterItem{ float value = 0.f; };
struct FilterItem_uint32: FilterItem{ uint32_t value = 0; };
struct FilterItem_bool: FilterItem{ bool value = false; };
struct FilterItem_vector3f: FilterItem{ Vector3f value = Vector3f(0,0,0); };

struct FilterItem_array1D_uint8_t: FilterItem{
    explicit FilterItem_array1D_uint8_t(uint16_t length) : arrayLength(length), value(new uint8_t[arrayLength]) {};
    uint16_t arrayLength = 0;
    uint8_t *value = nullptr;
};

struct FilterItem_array1D_float: FilterItem{
    explicit FilterItem_array1D_float(uint16_t length) : arrayLength(length), value(new float[arrayLength]) {};
    uint16_t arrayLength = 0;
    float *value = nullptr;
};

struct FilterItem_array2D_uint8_t: FilterItem{
    explicit FilterItem_array2D_uint8_t(uint16_t size_x, uint16_t size_y) : arraySize_x(size_x), arraySize_y(size_y), value(new uint8_t*[arraySize_x]) {
        for(int i = 0; i < arraySize_x; ++i) {
            value[i] = new uint8_t[arraySize_y];
        }
    };

    uint16_t arraySize_x = 0;
    uint16_t arraySize_y = 0;
    uint8_t* *value = nullptr;
};

struct FilterItem_array2D_float: FilterItem{
    explicit FilterItem_array2D_float(uint16_t size_x, uint16_t size_y) : arraySize_x(size_x), arraySize_y(size_y), value(new float*[arraySize_x]) {
        for(int i = 0; i < arraySize_x; ++i) {
            value[i] = new float[arraySize_y];
        }
    };

    uint16_t arraySize_x = 0;
    uint16_t arraySize_y = 0;
    float* *value = nullptr;
};

///////////////////////////////////////////////////////////////////////////
// Filter interface
///////////////////////////////////////////////////////////////////////////
/**
 * Filter interface has to be implemented by any classes that should by added as a Filter to the FiltersAndPipesManager
 */
class Filter {
public:

    virtual void update(float deltaTime) = 0;

    virtual uint8_t getNumberOfInputItems() = 0;

    virtual uint8_t getNumberOfOutputItems() = 0;

    virtual void setInputItem(uint8_t itemId, FilterItem *item) = 0;

    virtual FilterItem *getOutputItem(uint8_t itemId) = 0;

};


#endif //Filter_H
