#ifndef __RT_COUNTER_H__
#define __RT_COUNTER_H__



#include "arch.h"
#include "FreeRTOS++.h"
#include "platform_config.h"

#if ( configGENERATE_RUN_TIME_STATS == 1 )




extern "C" void run_time_init();
extern "C" TickType_t run_time_counter();
//-----------------------------------------------------------
extern "C" float  run_time_uS(const TickType_t time);
extern "C" float  run_time_S(const TickType_t time);

#endif


#endif /*__RT_COUNTER_H__*/
