#ifndef ABSTRACTSTAGE_H_
#define ABSTRACTSTAGE_H_

#include "appdefs.h"

class AbstractStage{

public:
	AbstractStage() {};
	virtual ~AbstractStage() {};

	virtual void updateParams() {};
	virtual void process(float* inL, float* inR, float* outL, float* outR);

	static constexpr uint8_t blockSize = 32;
};

#endif /* ABSTRACTSTAGE_H_ */
