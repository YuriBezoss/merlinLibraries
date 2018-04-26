#ifndef Remote_serialCmdsDecoder_demoMerlin_H
#define Remote_serialCmdsDecoder_demoMerlin_H


#include <Filter.h>
#include <Serial_basicCommunication.h>

class Remote_serialCmdsDecoder_demoMerlin: public Filter {
///////////////////////////////////////////////////////////////////////////
// Filter
///////////////////////////////////////////////////////////////////////////
public:
    enum InputDataTypes{
        NUM_INPUT_TYPES
    };

    enum OutputDataTypes{
        OutStartCmdReceived, NUM_OUTPUT_TYPES
    };

    uint8_t getNumberOfInputItems() override {
        return NUM_INPUT_TYPES;
    }

    uint8_t getNumberOfOutputItems() override {
        return NUM_OUTPUT_TYPES;
    }

    void setInputItem(uint8_t itemId, FilterItem *item) override {
        switch(itemId){
            default:break;
        }
    };

    FilterItem *getOutputItem(uint8_t itemId) override {
        switch(itemId){
            case OutStartCmdReceived: return &outStartCmdReceived;
            default: return nullptr;
        }
    };

    void update(float deltaTime) override;

protected:

    FilterItem_bool outStartCmdReceived = FilterItem_bool();


///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit Remote_serialCmdsDecoder_demoMerlin(Serial_basicCommunication *serialCommunication)  {
        Remote_serialCmdsDecoder_demoMerlin::serialCommunication = serialCommunication;
    }

protected:

    Serial_basicCommunication *serialCommunication;

    bool compareCharArrays(const char array1[], const char array2[], uint32_t arrayLength);



};


#endif //Remote_serialCmdsDecoder_demoMerlin
