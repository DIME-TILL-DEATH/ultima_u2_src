#ifndef VOLUMESTAGE_H_
#define VOLUMESTAGE_H_

#include "abstractstage.h"

class VolumeStage : public AbstractStage
{
public:
	VolumeStage();
	~VolumeStage() {};

	enum Parameters{
		ENABLED = 0,
		LEVEL
	};

	void process(float* sampleL, float* sampleR) override;
	void updateParams(const TModuleDescriptor* module) override;

private:

	float m_volumeLevel{1.0f};
};

#endif /* VOLUMESTAGE_H_ */
