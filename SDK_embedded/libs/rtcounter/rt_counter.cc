#include "rt_counter.h"


#if ( configGENERATE_RUN_TIME_STATS == 1 )

/*-----------------------------------------------------------*/
static TickType_t run_time_cnt = (TickType_t)0;
static float      run_time_period_uS ;

/*-----------------------------------------------------------*/
extern "C" void run_time_init()
{
    dbgmcu.state_stop(run_time_counter_dbg) ;
    run_time_counter_tim.clock_enable();
    run_time_counter_tim.reset();
    nvic.priority(run_time_counter_irq, run_time_counter_priority) ;
    nvic.enable(run_time_counter_irq);

    run_time_period_uS = 1000000.0 / RUN_TIME_STATS_INTERRUPT_FREQUENCY ;

    run_time_counter_tim.prescaler = 0 ;
    run_time_counter_tim.auto_reload = (2.0f * rcc.apb1_clock_freq()) / (RUN_TIME_STATS_INTERRUPT_FREQUENCY);
    run_time_counter_tim.update_interrupt_enable();
    run_time_counter_tim.enable();
}
//-----------------------------------------------------------
extern "C" float  run_time_uS(const TickType_t time)
{
  return time * run_time_period_uS ;
}
//-----------------------------------------------------------
extern "C" float  run_time_S(const TickType_t time)
{
  return time * run_time_period_uS / 1000000.0f ;
}
//-----------------------------------------------------------
extern "C" TickType_t  run_time_counter()
{
  return run_time_cnt  ;
}

extern "C" void __attribute__((noinline)) run_time_timer_irq_handler()
{
  run_time_counter_tim.update_interrupt_flag_clear();
  run_time_cnt++;
}
#endif
