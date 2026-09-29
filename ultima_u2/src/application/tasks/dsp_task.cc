#include "dsp_task.h"

#include "init.h"
#include "tasks/display_task.h"

dsp_task_t *dsp_task;


//------------------------------------------------------------------------------
void dsp_task_t::code()
{
	while(1)
	{
		block_request->take_from_task();
		// one block of I2S samples has been received; process it here
	}
}
//------------------------------------------------------------------------------