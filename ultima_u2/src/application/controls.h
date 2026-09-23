/*
 * controls.cc
 *
 *  Created on: 9 мар. 2019 г.
 *      Author: klen
 */


#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "sdk.h"


class controls_t
{
  public:
     inline controls_t()
        {
          gpioa.pin(gpio_t::mode_t::pin9_t::input,
                    gpio_t::pull_t::pin9_t::down
                   );


                       syscfg.clock_enable();
                       syscfg_usb_vbus();
                       exti.pin9_interrupt_masked();
                       exti.pin9_rising_trigger_enable();
                       nvic.exti9_5_priority(configMAX_SYSCALL_INTERRUPT_PRIORITY);
                       nvic.exti9_5_enable();
        }

     inline ~controls_t() {}

     inline void syscfg_usb_vbus() {syscfg.exti9_pa();}

     inline void usb_vbus_irq_enable() { exti.pin9_interrupt_unmasked(); }
     inline void usb_vbus_irq_disable() { exti.pin9_interrupt_masked(); }

     inline bool usb_vbus() { return gpioa.input & gpio_t::b9; }

  protected:

  private:
} ;

extern controls_t controls ;

#endif /*__CONTROLS_H__*/
