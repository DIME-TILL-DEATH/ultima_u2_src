/*
 * irq++.h
 *
 *  Created on: 2 дек. 2018 г.
 *      Author: klen
 */

#ifndef __IRQ++_H__
#define __IRQ++_H__


extern "C" void __attribute__((weak,noinline)) default_exception_handler(void)
{
  volatile stm32l0::nvic_t::irq_num_t irq ;
  irq = stm32l0::cpu_irq_num();
  while(1)
    {
      asm volatile  ("nop");
    }
  (void)irq ;
}

extern "C" void __attribute__((noinline)) svc_irq_handler(void);

//------------------------------------------------------------------------------------

// *** IRQ_HANDLER_WEAK(reset) ;   // определяется явно
IRQ_HANDLER_WEAK(nmi_exception) ;
// *** IRQ_HANDLER_WEAK(hard_fault_exception_irq_handler) ;  // определяется явно

// crt2 реализует совместное использование системных вызовов состороны FreeRTOS и пользователя
// поэтому явно определяется в crt2.cc
// *** #if defined __USE_FREERTOS__
// ***	IRQ_HANDLER_LINK(extern "C", vPortSVCHandler);
// *** #else
// ***  IRQ_HANDLER_WEAK(svc);
// *** #endif


#if defined __USE_FREERTOS__
	IRQ_HANDLER_LINK(extern "C", xPortPendSVHandler);
	IRQ_HANDLER_LINK(extern "C", xPortSysTickHandler);
#else
        IRQ_HANDLER_WEAK(pend_svc);
        IRQ_HANDLER_WEAK(sys_tick);
#endif
        IRQ_HANDLER_WEAK(wwdg);
        IRQ_HANDLER_WEAK(pvd);
        IRQ_HANDLER_WEAK(rtc);
        IRQ_HANDLER_WEAK(flash);
        IRQ_HANDLER_WEAK(rcc);
        IRQ_HANDLER_WEAK(exti0_1);
        IRQ_HANDLER_WEAK(exti2_3);
        IRQ_HANDLER_WEAK(exti4_15);
        IRQ_HANDLER_WEAK(dma1_channel1);
        IRQ_HANDLER_WEAK(dma1_channel2_3);
        IRQ_HANDLER_WEAK(dma1_channel4_5);
        IRQ_HANDLER_WEAK(adc1_comp);
        IRQ_HANDLER_WEAK(lptim1);
        IRQ_HANDLER_WEAK(tim2);
        IRQ_HANDLER_WEAK(tim21);
        IRQ_HANDLER_WEAK(i2c1);
        IRQ_HANDLER_WEAK(spi1);
        IRQ_HANDLER_WEAK(usart2);
        IRQ_HANDLER_WEAK(lpuart1);

constexpr __attribute__ (( section(".flash_irq_vec_table"))) volatile irq_handler_t irq_vector_table[] =
    {
	/*0x000*/ (irq_handler_t)&__stack_end__,      // The initial stack pointer
	/*0x04*/  IRQ_VECTOR(reset),                  // The reset handler
	/*0x08*/  IRQ_VECTOR(nmi_exception),          // Non maskable interrupt. The RCC Clock Security System (CSS) is linked to the NMI vector
	/*0x0C*/  IRQ_VECTOR(hard_fault_exception),   // All class of fault
	/*0x10*/  0,                                  // Memory management not implement
	/*0x14*/  0,                                  // Pre-fetch fault, memory access fault not implement
	/*0x000*/ 0,                                  // Undefined instruction or illegal state not implement
	/*0x1C*/  0,0,0,0,/* Reserved */
	/*0x2C*/  IRQ_VECTOR(svc),                    // System service call via SVC instruction (All user and FreeRTOS syscall dispatch over svc)
	                                              // FreeRTOS has svc arg=0, user arg=[1..255], see crt2.cc
	/*0x30*/  0,                                  // Debug Monitor not implement
	/*0x34*/  0,                                  // Reserved
	          #if defined __USE_FREERTOS__
	/*0x000*/    IRQ_VECTOR_EXTERN(xPortPendSVHandler),
	/*0x000*/    IRQ_VECTOR_EXTERN(xPortSysTickHandler),
	            #else
	/*0x38*/     IRQ_VECTOR(pend_svc),            //Pendable request for system service
	/*0x3C*/     IRQ_VECTOR(sys_tick),            //System tick timer
	          #endif


	/*0x40*/ IRQ_VECTOR(wwdg),
	/*0x44*/ IRQ_VECTOR(pvd),
	/*0x48*/ IRQ_VECTOR(rtc),
	/*0x4C*/ IRQ_VECTOR(flash),
	/*0x50*/ IRQ_VECTOR(rcc),
	/*0x54*/ IRQ_VECTOR(exti0_1),
	/*0x58*/ IRQ_VECTOR(exti2_3),
	/*0x5C*/ IRQ_VECTOR(exti4_15),
        0,
	/*0x64*/ IRQ_VECTOR(dma1_channel1),
	/*0x68*/ IRQ_VECTOR(dma1_channel2_3),
	/*0x6C*/ IRQ_VECTOR(dma1_channel4_5),
	/*0x70*/ IRQ_VECTOR(adc1_comp),
	/*0x74*/ IRQ_VECTOR(lptim1),
        0,
	/*0x7C*/ IRQ_VECTOR(tim2),
        0,0,0,0,
	/*0x90*/ IRQ_VECTOR(tim21),
        0,0,
	/*0x9C*/ IRQ_VECTOR(i2c1),
	0,
	/*0xA4*/ IRQ_VECTOR(spi1),
        0,0,
	/*0xB0*/ IRQ_VECTOR(usart2),
	/*0xB4*/ IRQ_VECTOR(lpuart1),

    };


#endif /*__IRQ++_H__*/
