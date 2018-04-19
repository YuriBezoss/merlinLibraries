#include "LoggingManager.h"


void LoggingManager::addLoggable(Loggable *loggable, bool showData){
    if(numLoggables >= LOGGABLES_MAX){ Logger::hardFault("ERROR in LoggingManager: Too many loggables added. Increase LOGGABLES_MAX."); };

    loggable->setLoggingActive(showData);
    loggables[numLoggables] = loggable;
    numLoggables++;
}


void LoggingManager::update(float deltaTime){

    // print headers
    if(!headersPrinted) {
        headersPrinted = true;
        for (uint8_t i = 0; i < numLoggables; ++i) {
            loggables[i]->printData(logger, true);
        }
        logger->newLine();
    }


    bool dataPrinted = false;
    for (uint8_t i = 0; i < numLoggables; ++i) {
        if(loggables[i]->printData(logger, false)){
            dataPrinted = true;
        }
    }

    if(dataPrinted){
        logger->newLine();
    }
}


