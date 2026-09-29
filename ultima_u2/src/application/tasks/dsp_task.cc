#include "dsp_task.h"

#include "init.h"
#include "preset.h"

dsp_task_t *dsp_task;


//------------------------------------------------------------------------------
void dsp_task_t::code()
{
	while(1)
	{
		block_request->take_from_task();

		for(int i=0; i<currentPreset.moduleCount; i++)
		{
			if(currentPreset.module[i].needUpdateParameters && currentPreset.module[i].updateParameters != nullptr)
			{
				currentPreset.module[i].updateParameters();
				currentPreset.module[i].needUpdateParameters = false;
			}
		}
	}
}
//------------------------------------------------------------------------------
