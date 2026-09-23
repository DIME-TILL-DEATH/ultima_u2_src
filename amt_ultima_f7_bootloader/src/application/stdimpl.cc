#include "appdefs.h"
#include "mmgr.h"

void _init(void)
{
  // включение отладочного таймера DWT CYCCNT
  core_debug.debug_and_trace_enable();
  dwt.unlock();
  dwt.cyc_counter=0 ;
  dwt.cyc_counter_enable();
  dwt.cpi_counter_enable();

  heap_init();
}

namespace stm32f7
{
  const rcc_t::system_init_profile_t system_init_profile_t_216MHz =
  {
    .regulator_voltage_scale = pwr_t::power_control_1_t::regulator_voltage_scale_t::scale1,
    .overdrive = true,

    .f_osc=F_OSC,
    .sys_clock_source = rcc_t::system_init_profile_t::sys_clock_source_t::hse_pll,
    .pll_m = F_OSC / 1000000 ,
    .pll_n = 432  ,
    .pll_p = rcc_t::pll_config_t::p_t::enum_t::div2,
    .pll_q = 9,

    .hpre = rcc_t::clock_config_t::ahb_prescaler_t::enum_t::no_div,
    .ppre1 = rcc_t::clock_config_t::apb1_prescaler_t::enum_t::div4,
    .ppre2 = rcc_t::clock_config_t::apb2_prescaler_t::enum_t::div2,

    .prefetch = flash_t::access_control_t::prefetch_t::enable,
    .latency = flash_t::access_control_t::latency_t::wait_7,
    .art_accelerator = flash_t::access_control_t::art_accelerator_t::enable,


    .l1_instruction_cache_active = true,
    .l1_data_cache_active = true,
  };

  const rcc_t::system_init_profile_t& system_init_profile = system_init_profile_t_216MHz ;

  uint32_t get_f_osc()
   {
     return system_init_profile.f_osc ;
   }
}


// функции необходимые для FreeRTSOS
extern "C" void vApplicationTickHook()
{
  nop() ;
}

extern "C" void vApplicationIdleHook()
{
  nop() ;
}


extern "C" void vApplicationMallocFailedHook( void )
{
  nop_loop() ;
}

extern "C" void vApplicationStackOverflowHook( TaskHandle_t *task, char *task_name )
{
  (void)task ;
  (void)task_name;
  nop_loop() ;
}


//TSemaphoreBinary heap_sync ;
static void heap_take()
   {
     taskENTER_CRITICAL();
     //heap_sync.Take();
   }
static void heap_give()
   {
     taskEXIT_CRITICAL();
     //heap_sync.Give();
   }


// переключение кучи в thread-safe режим (только один поток может иметь доступ к куче)
extern "C" void freertos_tasks_c_additions_init()
{
  nop_rep(10);
  heap_sync_set (heap_take,heap_give) ;
  nop_rep(10);
}

extern "C" inline __attribute__((used)) uint32_t sys_clock_freq_c()
    {
      return rcc.sys_clock_freq() ;
    }
