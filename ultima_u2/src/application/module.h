#ifndef _MODULE_H_
#define _MODULE_H_

//#include "appdefs.h"
#include "processing/param_descriptor.h"

enum TModuleType
{
	UNKNOWN_MODULE = 0,
	NG_MODULE,
	CM_MODULE,
	PH_MODULE,
	FL_MODULE,
	PR_MODULE,
	PA_MODULE,
	IR_MODULE,
	EQ_MODULE,
	FT_MODULE,
	RV_MODULE,
	DL_MODULE,
	WH_MODULE,
	TR_MODULE,
	CH_MODULE
};

enum TModuleChannel
{
	UNKNOWN_CHANNEL = 0,
	MONO_CHANNEL,
	STEREO_CHANNEL
};

typedef void (*updateModuleParametersHandler)(void);

typedef struct{
	TModuleType type;
	TModuleChannel channel;
	TParamDescriptor parameter[16];
	uint8_t parameterCount;
	uint8_t moduleId;	// number of module in the preset, for example: 0 - first module, 1 - second module, etc.
	uint8_t instaceId;	// number of module type instance in the preset

	bool needUpdateParameters;
	updateModuleParametersHandler updateParameters;
}TModule;

TModule makeEmptyModule(TModuleType type, TModuleChannel channel, uint8_t moduleId, uint8_t instanceId);

TModule makeNoiseGateModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeCompressorModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makePreampModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeAmpModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeCabModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeEqModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makePhaserModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeFlangerModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeReverbModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);
TModule makeDelayModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel = MONO_CHANNEL);

typedef struct
{
	uint8_t gain_clean;
	uint8_t gain_crunch;
	uint8_t gain_lead;
	uint8_t volume_clean;
	uint8_t volume_crunch;
	uint8_t volume_lead;
	uint8_t low_clean;
	uint8_t mid_clean;
	uint8_t high_clean;
	uint8_t low_crunch;
	uint8_t mid_crunch;
	uint8_t high_crunch;
	uint8_t low_lead;
	uint8_t mid_lead;
	uint8_t high_lead;
}TPreampModule;

TPreampModule makePreampModuleState(void);

void preampChangeType(TModule& module, const TPreampModule& state, uint8_t type);

#endif /* _MODULE_H_ */
