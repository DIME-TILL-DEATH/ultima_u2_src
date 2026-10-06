#include "volumestage.h"

#include "processing/audio_process.h"

void VolumeStage::process(float* sampleL, float* sampleR)
{
	for(uint8_t i = 0; i < audioBlockSize; i++)
	{
		sampleL[i] *= m_volumeLevel;
		sampleR[i] *= m_volumeLevel;
	}
}

void VolumeStage::updateParams(const TModuleDescriptor* module)
{

}
