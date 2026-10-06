#ifndef ABSTRACTSTAGE_H_
#define ABSTRACTSTAGE_H_

#include "module.h"

class AbstractStage{

public:
	AbstractStage() {};
	virtual ~AbstractStage() {};

	virtual void updateParams(const TModuleDescriptor* module) {};
	virtual void process(float* sampleL, float* sampleR) {};

	static constexpr uint8_t blockSize = 32;
protected:
	bool m_enabled{false};
};

#endif /* ABSTRACTSTAGE_H_ */
