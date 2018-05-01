#include <Logger.h>
#include <cstdio>
#include "PipelineManager.h"

void PipelineManager::addFilter(uint16_t id, Filter *filter, bool ignoreInputItems) {
    // throw error if too many filters are added
    if(id >= FILTERS_MAX){ Logger::hardFault("ERROR in PipelineManager: Too many filters added. Increase FILTERS_MAX."); };

    filterStructs[id].initialized = true;
    filterStructs[id].ignoreInputItems = ignoreInputItems;
    filterStructs[id].filter = filter;
    filterStructs[id].allFilterItemOutputsOffset = numAllFilterItemOutputs;
    numAllFilterItemOutputs += filter->getNumberOfOutputItems();
    filterOrder[numFilters++] = id;
}


void PipelineManager::addPipe(uint16_t sourceFilterId, uint16_t sourceItemId, uint16_t targetFilterId, uint16_t targetItemId) {
    // throw error if there are too many inputs for an filter
    if(targetItemId > PIPES_PER_FILER_MAX){ Logger::hardFault("ERROR in PipelineManager: Too many pipes added. Increase PIPES_PER_FILER_MAX."); };

    filterStructs[targetFilterId].incomingPipes[targetItemId].initialized = true;
    filterStructs[targetFilterId].incomingPipes[targetItemId].sourceFilterId = sourceFilterId;
    filterStructs[targetFilterId].incomingPipes[targetItemId].sourceItemId = sourceItemId;
}


void PipelineManager::update(float deltaTime){

    // loop over all filterStructs
    for (uint16_t i = 0; i < numFilters; ++i) {

        FilterStructInternal *filterStruct = &filterStructs[filterOrder[i]];

        if(!filterStruct->ignoreInputItems) {
            // set all input items
            for (uint8_t j = 0; j < filterStruct->filter->getNumberOfInputItems(); ++j) {

                // get the incoming pipe
                PipeStructInternal incomingPipe = filterStruct->incomingPipes[j];

                // check if the incoming pipe is initialized
                if (!incomingPipe.initialized) {
                    const char m[128] = "";
                    sprintf((char *) m,
                            "ERROR in PipelineManager: input pipe %d of filter %d has not been initialized.\n",
                            j, i);
                    Logger::hardFault(m);
                }

                // check if source filter which is linked to the incoming pipe is initialized
                if (!filterStructs[incomingPipe.sourceFilterId].initialized) {
                    const char m[128] = "";
                    sprintf((char *) m,
                            "ERROR in PipelineManager: Item %d, which provides outputItem for filter %d, has not been initialized.\n",
                            incomingPipe.sourceFilterId, i);
                    Logger::hardFault(m);
                }

                // Set output item of source filter as input of target filter. If output item is null, throw error.
                FilterItem *outputItem = allFilterItemOutputs[
                        filterStructs[incomingPipe.sourceFilterId].allFilterItemOutputsOffset +
                        incomingPipe.sourceItemId];
                if (!outputItem) {
                    const char m[128] = "";
                    sprintf((char *) m,
                            "ERROR in PipelineManager: Output filterItem, which is used as input %d of filter %d, is null. Check builder.\n",
                            j, i);
                    Logger::hardFault(m);
                }
                filterStruct->filter->setInputItem(j, outputItem);
            }
        }

        // update filter
        filterStruct->filter->update(deltaTime);

        // store filter outputs in allFilterItemOutputs array;
        if(firstRun) {
            for (uint8_t k = 0; k < filterStruct->filter->getNumberOfOutputItems(); ++k) {
                uint32_t  offset = filterStruct->allFilterItemOutputsOffset+k;
                allFilterItemOutputs[offset] = filterStruct->filter->getOutputItem(k);
            }
        }
    }

    firstRun = false;

}

