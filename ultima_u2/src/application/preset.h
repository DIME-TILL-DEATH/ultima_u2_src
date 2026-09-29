#ifndef _PRESET_H_
#define _PRESET_H_

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

typedef struct{
	TModuleType type;
	TModuleChannel channel;
	TParamDescriptor parameter[32];
	uint8_t parameterCount;
	uint8_t moduleId;	// number of module in the preset, for example: 0 - first module, 1 - second module, etc.
	uint8_t instaceId;	// number of module type instance in the preset
}TModule;

typedef struct{
	char name[16];
	char author[16];
	uint8_t moduleCount;
	TModule module[16];
}TPreset;

extern TPreset currentPreset;

#endif /* _PRESET_H_ */