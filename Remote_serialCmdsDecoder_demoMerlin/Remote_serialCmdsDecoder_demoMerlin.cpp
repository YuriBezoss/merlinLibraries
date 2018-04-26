#include "Remote_serialCmdsDecoder_demoMerlin.h"

void Remote_serialCmdsDecoder_demoMerlin::update(float deltaTime) {

    const char startString[] = "start";
    const char stopString[] = "stop";
    const char cmdPrefix[] = "cmd:";

    uint32_t cmdPrefixLength = 0;
    while(cmdPrefix[cmdPrefixLength] != '\0') { cmdPrefixLength++; }

    uint32_t startStringLength = 0;
    while(startString[startStringLength] != '\0') { startStringLength++; }

    uint32_t stopStringLength = 0;
    while(stopString[stopStringLength] != '\0') { stopStringLength++; }


    outStartCmdReceived.available = false;

    serialCommunication->readoutRxBuffer();
    if(serialCommunication->isNewMessageAvailable()) {

        Serial_basicCommunication::Message serialMessage = serialCommunication->getMessage();

        if(serialMessage.msgLength >= cmdPrefixLength) {

            bool startCharactersFound = true;
            for (uint32_t k = 0; k < cmdPrefixLength; ++k) {
                if(serialMessage.msg[k] != cmdPrefix[k]) {
                    startCharactersFound = false;
                }
            }

            if (startCharactersFound) {
                char inputString[serialMessage.msgLength - cmdPrefixLength];
                for (uint32_t i = 0; i < serialMessage.msgLength - cmdPrefixLength; ++i) {
                    inputString[i] = serialMessage.msg[i+cmdPrefixLength];
                }

                if(compareCharArrays(startString, inputString, startStringLength)) {
                    outStartCmdReceived.available = true;
                    outStartCmdReceived.value = true;

                } else if(compareCharArrays(stopString, inputString, stopStringLength)) {
                    outStartCmdReceived.available = true;
                    outStartCmdReceived.value = false;
                }
            }
        }
    }
}


bool Remote_serialCmdsDecoder_demoMerlin::compareCharArrays(const char array1[], const char array2[], uint32_t arrayLength) {
    for (uint32_t j = 0; j < arrayLength; ++j) {
        if(array1[j] != array2[j]) {
            return false;
        }
    }
    return true;
}