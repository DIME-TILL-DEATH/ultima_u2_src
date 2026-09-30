#ifndef _PRESET_H_
#define _PRESET_H_

#include "processing/param_descriptor.h"
#include "module.h"

typedef struct
{
	char name[16];
	char author[16];
	uint8_t moduleCount;
	TModuleDescriptor module[10];
} TPreset;

extern TPreset currentPreset;

#endif /* _PRESET_H_ */
