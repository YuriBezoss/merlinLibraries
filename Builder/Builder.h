#ifndef Builder_H
#define Builder_H


#include <Scheduler.h>

/**
 * Builder interface
 */
class Builder {

public:

    virtual Scheduler *build() = 0;

};


#endif //Builder_H
