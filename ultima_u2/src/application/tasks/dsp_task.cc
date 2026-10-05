#include "dsp_task.h"

#include "init.h"
#include "preset.h"

#include "processing/audio_process.h"

dsp_task_t *dsp_task;


//------------------------------------------------------------------------------
void dsp_task_t::code()
{
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
	}
}
//------------------------------------------------------------------------------
