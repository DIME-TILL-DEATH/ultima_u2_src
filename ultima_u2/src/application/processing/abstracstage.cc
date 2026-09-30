#include "abstractstage.h"

void AbstractStage::process(float* inL, float* inR, float* outL, float* outR)
{
	memcpy(outL, inL, blockSize);
	memcpy(outR, outL, blockSize);
}
