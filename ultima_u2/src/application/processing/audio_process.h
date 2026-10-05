#ifndef AUDIO_PROCESS_H_
#define AUDIO_PROCESS_H_

#include "appdefs.h"

#include "module.h"
#include "abstractstage.h"

#define AUDIO_BLOCK_SIZE 16
#define MAX_PRESET_MODULES 10

struct TModuleRuntime
{
    TModuleDescriptor* descriptor;
    AbstractStage* stage;
    bool dirty = false;
};

void audioProcessInit();
void audioCaptureBlock();
void audioProcessBlock();


extern TModuleRuntime moduleRuntime[MAX_PRESET_MODULES];
extern TModuleRuntime metronomeRuntime;

#endif /* AUDIO_PROCESS_H_ */
