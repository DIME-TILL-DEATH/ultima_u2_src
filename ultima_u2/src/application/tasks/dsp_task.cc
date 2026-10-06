#include "dsp_task.h"

#include "init.h"
#include "preset.h"

#include "processing/audio_process.h"
#include "processing/gatestage.h"
#include "processing/metronome.h"

dsp_task_t *dsp_task;

TModuleRuntime metronomeRuntime;

TModuleDescriptor globalGateDecriptor;
TModuleRuntime globalGateRuntime;

//------------------------------------------------------------------------------
void dsp_task_t::code()
{
	for(uint8_t i=0; i<MAX_PRESET_MODULES; i++)
	{
		moduleRuntime[i].stage = nullptr;
		moduleRuntime[i].descriptor = nullptr;
		moduleRuntime[i].dirty = false;
	}

	audioProcessInit();

	metronomeRuntime.stage = &metronome;
	metronomeRuntime.descriptor = &metronomeModuleDescriptor;
	metronomeRuntime.dirty = true;

	globalGateDecriptor = makeNoiseGateModule(-3, 0);

	extern GateStage gate_glob;
	globalGateRuntime.stage = &gate_glob;
	globalGateRuntime.descriptor = &globalGateDecriptor;
	globalGateRuntime.dirty = true;

	extern system_file_t system_file;
	globalGateDecriptor.parameter[GateStage::ENABLED].value = system_file.gat_on;
	globalGateDecriptor.parameter[GateStage::ATTACK].value = system_file.gat_att;
	globalGateDecriptor.parameter[GateStage::DECAY].value = system_file.gat_dec;
	globalGateDecriptor.parameter[GateStage::THRESHOLD].value = system_file.gat_thresh;

	while(1)
	{
		block_request->take_from_task();

		for(int i=0; i<currentPreset.moduleCount; i++)
		{
			if(moduleRuntime[i].dirty && moduleRuntime[i].stage != nullptr)
			{
				moduleRuntime[i].stage->updateParams(moduleRuntime[i].descriptor);
				moduleRuntime[i].dirty = false;
			}
		}

		if(metronomeRuntime.dirty)
		{
			metronome.updateParams(&metronomeModuleDescriptor);
			metronomeRuntime.dirty = false;
		}

		if(globalGateRuntime.dirty)
		{
			gate_glob.updateParams(&globalGateDecriptor);
			globalGateRuntime.dirty = false;
		}

		audioProcessBlock();
	}
}
//------------------------------------------------------------------------------
