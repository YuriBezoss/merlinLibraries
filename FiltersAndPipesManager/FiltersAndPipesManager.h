#ifndef FiltersAndPipesManager_H
#define FiltersAndPipesManager_H


#include <Schedulable.h>
#include <Filter.h>

class FiltersAndPipesManager: public Schedulable {
///////////////////////////////////////////////////////////////////////////
// Custom
///////////////////////////////////////////////////////////////////////////
public:

    explicit FiltersAndPipesManager(uint8_t schedulingPeriod) {
        FiltersAndPipesManager::schedulingPeriod = schedulingPeriod;
    }

    void addFilter(uint16_t id, Filter *filter, bool ignoreInputItems = false);
    void addPipe(uint16_t sourceFilterId, uint16_t sourceItemId, uint16_t targetFilterId, uint16_t targetItemId);

    void update(float deltaTime) override;

protected:

    static const uint8_t FILTERS_MAX = 40;
    static const uint8_t PIPES_PER_FILER_MAX = 8;

    struct PipeStructInternal{
        uint16_t sourceFilterId = 0;
        uint16_t sourceItemId = 0;
        bool initialized = false;
    };

    struct FilterStructInternal{
        Filter *filter = nullptr;
        uint16_t allFilterItemOutputsOffset = 0;
        bool initialized = false;
        bool ignoreInputItems = false;
        PipeStructInternal incomingPipes[PIPES_PER_FILER_MAX];
    } filterStructs[FILTERS_MAX];

    uint16_t filterOrder[FILTERS_MAX] = {};
    uint16_t numFilters = 0;

    FilterItem *allFilterItemOutputs[FILTERS_MAX  *PIPES_PER_FILER_MAX] = {};
    uint16_t numAllFilterItemOutputs = 0;

    bool firstRun = true;

};


#endif //FiltersAndPipesManager_H
