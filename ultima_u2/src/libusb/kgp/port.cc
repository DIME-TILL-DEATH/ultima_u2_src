#include "stm32++.h"
#include "gnu_linker.h"

extern "C" void port_delay(volatile uint32_t Delay)
{
  nop_while(10000*Delay) ;
}

extern "C" void port_system_init(void)
{
  stm32f7::system_init((uint32_t)gnu_linker_vec_start(),system_init_profile);
}

extern "C" void port_rcc_pcd_enable()
    {
       rcc.usbfs_enable();
       syscfg.clock_enable();
    }

extern "C" void port_rcc_pcd_disable()
    {
       rcc.usbfs_disable();
    }

extern "C" void port_rcc_syscfg_enable()
    {
       rcc.syscfg_enable();
    }

extern "C" void port_gpioa_usbfs_pins_init()
{
  /**USB_OTG_FS GPIO Configuration
  PA8     ------> USB_OTG_FS_SOF
  PA9     ------> USB_OTG_FS_VBUS
  PA10     ------> USB_OTG_FS_ID
  PA11     ------> USB_OTG_FS_DM
  PA12     ------> USB_OTG_FS_DP
  */
  gpioa.clock_enable();
  gpioa.pin(gpio_t::mode_t::pin11_t::alternate_function,
            gpio_t::mode_t::pin12_t::alternate_function,
	    gpio_t::output_speed_t::pin11_t::very_high,
	    gpio_t::output_speed_t::pin12_t::very_high,
	    gpioa_t::af_t::pin11_t::otgfs_dm,
	    gpioa_t::af_t::pin12_t::otgfs_dp);


  gpioa.pin(gpio_t::mode_t::pin9_t::input,
  	    gpio_t::pull_t::pin9_t::no
           );


}

extern "C" void port_gpioa_usbfs_pins_deinit()
{
  gpioa.pin(gpio_t::mode_t::pin9_t::output);
  nop_while(10000); // разряд конденсатора
  gpioa.pin(gpio_t::mode_t::pin9_t::input);
}

extern "C" void port_enable_nvic_otgfs_irq()
{
  nvic.otg_fs_priority(0);
  nvic.otg_fs_enable();

}

extern "C" void port_disable_nvic_otgfs_irq()
{
  nvic.otg_fs_disable();
}

#include "stm32f7xx_hal_pcd.h"
extern "C" void port_usbfs_init(pcd_t* pcd)
{
  //GPIO_InitTypeDef GPIO_InitStruct;
  if(pcd->Instance==USB_OTG_FS)
  {

    port_gpioa_usbfs_pins_init();
    port_rcc_pcd_enable();


    if ( pcd->handler_mode == irq )
      {
	port_enable_nvic_otgfs_irq();
      }
  }
}

extern "C" void port_usbfs_deinit(pcd_t* pcd)
{
  if(pcd->Instance==USB_OTG_FS)
  {

      port_rcc_pcd_disable();
      port_gpioa_usbfs_pins_deinit();

      if ( pcd->handler_mode == irq )
        {
	  port_disable_nvic_otgfs_irq();
        }
  }
}

extern "C" void port_error()
{
   nop_loop();
}




extern "C" void port_reset_sleep_deep()
{
   scb.sleep_deep_disable() ;
   scb.sleep_on_exit_do_not_sleep();

   /* Reset SLEEPDEEP bit of Cortex System Control Register */
   //SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
}

extern "C" void port_set_sleep_deep()
{
   scb.sleep_deep_enable() ;
   scb.sleep_on_exit_enter_sleep();

   /* Set SLEEPDEEP bit and SleepOnExit of Cortex System Control Register */
   //SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
}

