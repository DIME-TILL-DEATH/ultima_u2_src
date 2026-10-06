#ifndef ABSTRACTSTAGE_H_
#define ABSTRACTSTAGE_H_

#include "module.h"

class AbstractStage{

public:
	AbstractStage() {};
	virtual ~AbstractStage() {};

	virtual void updateParams(const TModuleDescriptor* module) {};
	virtual void process(float* sampleL, float* sampleR) {};

	static constexpr uint8_t audioBlockSize = 16;
	static constexpr float fs = 48000.0f;
	static float dsp_scratch[audioBlockSize];

	float dcBlock(float in);
protected:
	bool m_enabled{false};

	float in_dc_old{0};
	float out_dc_old{0};
};

#endif /* ABSTRACTSTAGE_H_ */