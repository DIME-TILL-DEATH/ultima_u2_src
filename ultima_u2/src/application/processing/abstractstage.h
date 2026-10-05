#ifndef ABSTRACTSTAGE_H_
#define ABSTRACTSTAGE_H_

#include "appdefs.h"

#include "module.h"

class AbstractStage{

public:
	AbstractStage() {};
	virtual ~AbstractStage() {};

	virtual void updateParams(const TModuleDescriptor* module) {};
	virtual void process(float* sampleL, float* sampleR) {};

	static constexpr uint8_t blockSize = 32;
};

#endif /* ABSTRACTSTAGE_H_ */
