#ifndef DSP_TASK_H_
#define DSP_TASK_H_

#include "appdefs.h"

class dsp_task_t: public task_t
{
public:
	inline dsp_task_t(const char *name, const int stack_size, const int priority) :
			task_t(name, stack_size, priority, false)
	{
		block_request = new semaphore_counting_t(1, 0);
	}

	inline void trigger()
	{
		block_request->give();
	}

	virtual ~dsp_task_t(){};
private:
	void code();
	semaphore_counting_t *block_request;
};

extern dsp_task_t *dsp_task;

#endif /* DSP_TASK_H_ */