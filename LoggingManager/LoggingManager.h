#ifndef LoggingManager_h
#define LoggingManager_h


#include <Schedulable.h>
#include <Logger.h>
#include <Loggable.h>

class LoggingManager: public Schedulable {
///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit LoggingManager(Logger *logger, uint8_t taskExecutionInterval) {
        LoggingManager::executionPeriod = taskExecutionInterval;
        LoggingManager::logger = logger;
    }

    void addLoggable(Loggable *loggable, bool showData);

    void update(float deltaTime) override;

protected:

    static const uint8_t LOGGABLES_MAX = 60;

    Logger *logger;
    Loggable *loggables[LOGGABLES_MAX] = {}; // array of elements that are executed when update is called

    uint16_t numLoggables = 0;

    bool headersPrinted = false;

};

#endif //LoggingManager_h
