#ifndef LoggingManager_h
#define LoggingManager_h


#include <Schedulable.h>
#include <Logger.h>
#include <Loggable.h>

/**
 * LoggingManager provides a simple and flexible way to regularly log information of different components of the code.
 * LoggingManager is Schedulable. Thats means if the LoggingManager has been added as a task to the Scheduler, its update
 * function is called every cycle.
 * Each object that should be logged via the LoggingManager has to implement the Loggable-class. Then it can be added by
 * calling the addLoggable-function.
 * Every time the update-function is called, the printData-function of all Loggables are called.
 */
class LoggingManager: public Schedulable {
///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit LoggingManager(Logger *logger, uint8_t schedulingPeriod) {
        LoggingManager::schedulingPeriod = schedulingPeriod;
        LoggingManager::logger = logger;
    }

    void addLoggable(Loggable *loggable, bool showData);

    void update(float deltaTime) override;

protected:

    static const uint8_t LOGGABLES_MAX = 20;

    Logger *logger;
    Loggable *loggables[LOGGABLES_MAX] = {}; // array of elements that are executed when update is called

    uint16_t numLoggables = 0;

    bool headersPrinted = false;

};

#endif //LoggingManager_h
