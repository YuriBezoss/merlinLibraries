#ifndef Math_lpf1_H
#define Math_lpf1_H

#include <Math_basic.h>

template<typename T>
class Math_lowPassFilter1 {

public:

	Math_lowPassFilter1(float cutoffFreq, float sampleDeltaTime, bool filterActive) {
		setFilterParameters(cutoffFreq, sampleDeltaTime);
		setFilterActive(filterActive);
	}

	T applyFilter(T sample) {
		T output;

		if(firstRun || !filterActive){
			firstRun = false;
			output = sample;
		} else {
			output = sample*alpha + lastOutput*(1-alpha);
		}
		lastOutput = output;
		return output;
	}

	void setFilterParameters(float cutoffFreq, float sampleDeltaTime) {
		if(cutoffFreq == 0.f)
			alpha = 1.f;
		else {
			float rc = 1.f / (2.f * Math_basic::PI_CONSTANT * cutoffFreq);
			alpha = sampleDeltaTime / (sampleDeltaTime + rc);
		}
	}

	void reset() {
		firstRun = true;
	}

	bool isFilterActive() const {
		return filterActive;
	}

	void setFilterActive(bool filterActive) {
		if(!Math_lowPassFilter1::filterActive && filterActive) {
			reset();
		}
		Math_lowPassFilter1::filterActive = filterActive;
	}


protected:

	bool filterActive = false;
	float alpha = 1.0f;
    T lastOutput;
    bool firstRun = true;

};

#endif // Math_lpf1_H
