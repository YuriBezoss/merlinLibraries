#ifndef Math_medianFilter_H
#define Math_medianFilter_H

#include <stdint-gcc.h>
#include <cstring>

/**
 * Median filter (see https://en.wikipedia.org/wiki/Median_filter)
 */
class Math_medianFilter {

public:

	/**
	 * @param bufferLength length of the median filter
	 * @param filterActive true if filter is active
	 */
	explicit Math_medianFilter(uint8_t bufferLength, bool filterActive) :
            sampleBuffer(new float[bufferLength]),
            bufferLength(bufferLength),
            filterActive(filterActive) {
    }

	/**
	 * applies the filter to the new sample value
	 * @param sample new input value
	 * @return new filtered value
	 */
	float applyFilter(float sample) {

        if(!filterActive) {
            return sample;
        }

		float output = sample;
		sampleBuffer[bufferIndex] = sample;

		if(bufferFilled){
			float dataSorted[bufferLength];
			memcpy(dataSorted, sampleBuffer, bufferLength * sizeof(float));

			for (uint8_t j = 0; j < (bufferLength/2+1); ++j) {
				for (uint8_t k = j; k < bufferLength; ++k) {
					if (dataSorted[k] < dataSorted[j]) {
						float tmp = dataSorted[j];
						dataSorted[j] = dataSorted[k];
						dataSorted[k] = tmp;
					}
				}
			}
			output = dataSorted[bufferLength/2];
		}

		bufferIndex++;
		if(!bufferFilled && bufferIndex == bufferLength){ bufferFilled = true; }
		bufferIndex %= bufferLength;

		return output;
	}

	void reset(){
		bufferIndex = 0;
		bufferFilled = false;
	}

    bool isFilterActive() const {
        return filterActive;
    }

    void setFilterActive(bool filterActive) {
        if(!Math_medianFilter::filterActive && filterActive) {
            reset();
        }
        Math_medianFilter::filterActive = filterActive;
    }

protected:

    bool filterActive = false;
    uint8_t bufferLength = 3;
    float *sampleBuffer = nullptr;
    uint8_t bufferIndex = 0;
    bool bufferFilled = false;

};

#endif //Math_medianFilter_H
