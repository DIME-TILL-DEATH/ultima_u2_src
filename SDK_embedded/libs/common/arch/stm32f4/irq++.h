/*
 * irq++.h
 *
 *  Created on: 11 авг. 2017 г.
 *      Author: klen
 */

#ifndef __IRQ++_H__
#define __IRQ++_H__


extern "C" void __attribute__((weak,noinline)) default_exception_handler(void)
{
  volatile stm32f4::nvic_t::irq_num_t irq ;
  irq = stm32f4::cpu_irq_num();
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
IRQ_HANDLER_WEAK(mem_manage_exception) ;
IRQ_HANDLER_WEAK(bus_fault_exception);
IRQ_HANDLER_WEAK(usage_fault_exception);

// crt2 реализует совместное использование системных вызовов состороны FreeRTOS и пользователя
// поэтому явно определяется в crt2.cc
// *** #if defined __USE_FREERTOS__
// ***	IRQ_HANDLER_LINK(extern "C", vPortSVCHandler);
// *** #else
// ***  IRQ_HANDLER_WEAK(svc);
// *** #endif

	IRQ_HANDLER_WEAK(debug_monitor);
#if defined __USE_FREERTOS__
	IRQ_HANDLER_LINK(extern "C", xPortPendSVHandler);
	IRQ_HANDLER_LINK(extern "C", xPortSysTickHandler);
#else
        IRQ_HANDLER_WEAK(pend_svc);
        IRQ_HANDLER_WEAK(sys_tick);
#endif
        IRQ_HANDLER_WEAK(wwdg);
        IRQ_HANDLER_WEAK(pvd);
        IRQ_HANDLER_WEAK(tamper);
        IRQ_HANDLER_WEAK(rtc);
        IRQ_HANDLER_WEAK(flash);
        IRQ_HANDLER_WEAK(rcc);
        IRQ_HANDLER_WEAK(exti0);
        IRQ_HANDLER_WEAK(exti1);
        IRQ_HANDLER_WEAK(exti2);
        IRQ_HANDLER_WEAK(exti3);
        IRQ_HANDLER_WEAK(exti4);
        IRQ_HANDLER_WEAK(dma1_stream0);
        IRQ_HANDLER_WEAK(dma1_stream1);
        IRQ_HANDLER_WEAK(dma1_stream2);
        IRQ_HANDLER_WEAK(dma1_stream3);
        IRQ_HANDLER_WEAK(dma1_stream4);
        IRQ_HANDLER_WEAK(dma1_stream5);
        IRQ_HANDLER_WEAK(dma1_stream6);
        IRQ_HANDLER_WEAK(adc);
        IRQ_HANDLER_WEAK(can1_tx);
        IRQ_HANDLER_WEAK(can1_rx0);
        IRQ_HANDLER_WEAK(can1_rx1);
        IRQ_HANDLER_WEAK(can1_sce);
        IRQ_HANDLER_WEAK(exti9_5);
        IRQ_HANDLER_WEAK(tim1_brk_tim9);
        IRQ_HANDLER_WEAK(tim1_up_tim10);
        IRQ_HANDLER_WEAK(tim1_trg_com_tim11);
        IRQ_HANDLER_WEAK(tim1_cc);
        IRQ_HANDLER_WEAK(tim2);
        IRQ_HANDLER_WEAK(tim3);
        IRQ_HANDLER_WEAK(tim4);
        IRQ_HANDLER_WEAK(i2c1_ev);
        IRQ_HANDLER_WEAK(i2c1_er);
        IRQ_HANDLER_WEAK(i2c2_ev);
        IRQ_HANDLER_WEAK(i2c2_er);
        IRQ_HANDLER_WEAK(spi1);
        IRQ_HANDLER_WEAK(spi2);
        IRQ_HANDLER_WEAK(usart1);
        IRQ_HANDLER_WEAK(usart2);
        IRQ_HANDLER_WEAK(usart3);
        IRQ_HANDLER_WEAK(exti15_10);
        IRQ_HANDLER_WEAK(rtc_alarm);
        IRQ_HANDLER_WEAK(otg_fs_wkup);
        IRQ_HANDLER_WEAK(tim8_brk_tim12);
        IRQ_HANDLER_WEAK(tim8_up_tim13);
        IRQ_HANDLER_WEAK(tim8_trg_com_tim14);
        IRQ_HANDLER_WEAK(tim8_cc);
        IRQ_HANDLER_WEAK(dma1_stream7);
        IRQ_HANDLER_WEAK(fsmc);
        IRQ_HANDLER_WEAK(sdio);
        IRQ_HANDLER_WEAK(tim5);
        IRQ_HANDLER_WEAK(spi3);
        IRQ_HANDLER_WEAK(uart4);
        IRQ_HANDLER_WEAK(uart5);
        IRQ_HANDLER_WEAK(tim6_dac);
        IRQ_HANDLER_WEAK(tim7);
        IRQ_HANDLER_WEAK(dma2_stream0);
        IRQ_HANDLER_WEAK(dma2_stream1);
        IRQ_HANDLER_WEAK(dma2_stream2);
        IRQ_HANDLER_WEAK(dma2_stream3);
        IRQ_HANDLER_WEAK(dma2_stream4);
        IRQ_HANDLER_WEAK(eth);
        IRQ_HANDLER_WEAK(eth_wkup);
        IRQ_HANDLER_WEAK(can2_tx);
        IRQ_HANDLER_WEAK(can2_rx0);
        IRQ_HANDLER_WEAK(can2_rx1);
        IRQ_HANDLER_WEAK(can2_sce);
        IRQ_HANDLER_WEAK(otg_fs);
        IRQ_HANDLER_WEAK(dma2_stream5);
        IRQ_HANDLER_WEAK(dma2_stream6);
        IRQ_HANDLER_WEAK(dma2_stream7);
        IRQ_HANDLER_WEAK(usart6);
        IRQ_HANDLER_WEAK(i2c3_ev);
        IRQ_HANDLER_WEAK(i2c3_er);
        IRQ_HANDLER_WEAK(otg_hs_ep1_out);
        IRQ_HANDLER_WEAK(otg_hs_ep1_in);
        IRQ_HANDLER_WEAK(otg_hs_wkup);
        IRQ_HANDLER_WEAK(otg_hs);
        IRQ_HANDLER_WEAK(dcmi);
        IRQ_HANDLER_WEAK(cryp);
        IRQ_HANDLER_WEAK(hash_rng);
        IRQ_HANDLER_WEAK(fpu);
        IRQ_HANDLER_WEAK(uart7);
        IRQ_HANDLER_WEAK(uart8);
        IRQ_HANDLER_WEAK(spi4);
        IRQ_HANDLER_WEAK(spi5);
        IRQ_HANDLER_WEAK(spi6);
        IRQ_HANDLER_WEAK(sai1);
        IRQ_HANDLER_WEAK(ltdc);
        IRQ_HANDLER_WEAK(ltdc_er);
        IRQ_HANDLER_WEAK(dma2d);

const __attribute__ (( section(".flash_irq_vec_table"))) volatile irq_handler_t irq_vector_table[] =
    {
	/*0x000*/ (irq_handler_t)&__stack_end__,      // The initial stack pointer
	/*0x04*/  IRQ_VECTOR(reset),                  // The reset handler
	/*0x08*/  IRQ_VECTOR(nmi_exception),          // Non maskable interrupt. The RCC Clock Security System (CSS) is linked to the NMI vector
	/*0x0C*/  IRQ_VECTOR(hard_fault_exception),   // All class of fault
	/*0x10*/  IRQ_VECTOR(mem_manage_exception),   // Memory management
	/*0x14*/  IRQ_VECTOR(bus_fault_exception),    // Pre-fetch fault, memory access fault
	/*0x000*/ IRQ_VECTOR(usage_fault_exception),  // Undefined instruction or illegal state
	/*0x1C*/  0,0,0,0,/* Reserved */
	/*0x2C*/  IRQ_VECTOR(svc),                    // System service call via SVC instruction (All user and FreeRTOS syscall dispatch over svc)
	                                              // FreeRTOS has svc arg=0, user arg=[1..255], see crt2.cc
	/*0x30*/  IRQ_VECTOR(debug_monitor),          // Debug Monitor
	/*0x34*/  0,                                  // Reserved
	          #if defined __USE_FREERTOS__
	/*0x000*/    IRQ_VECTOR_EXTERN(xPortPendSVHandler),
	/*0x000*/    IRQ_VECTOR_EXTERN(xPortSysTickHandler),
	            #else
	/*0x38*/     IRQ_VECTOR(pend_svc),            //Pendable request for system service
	/*0x3C*/     IRQ_VECTOR(sys_tick),            //System tick timer
	          #endif
	/*0x40*/  IRQ_VECTOR(wwdg),
	/*0x44*/  IRQ_VECTOR(pvd),
	/*0x48*/  IRQ_VECTOR(tamper),
	/*0x4C*/  IRQ_VECTOR(rtc),
	/*0x50*/  IRQ_VECTOR(flash),
	/*0x54*/  IRQ_VECTOR(rcc),
	/*0x58*/  IRQ_VECTOR(exti0),
	/*0x5C*/  IRQ_VECTOR(exti1),
	/*0x60*/  IRQ_VECTOR(exti2),
	/*0x64*/  IRQ_VECTOR(exti3),
	/*0x68*/  IRQ_VECTOR(exti4),
	/*0x6C*/  IRQ_VECTOR(dma1_stream0),
	/*0x70*/  IRQ_VECTOR(dma1_stream1),
	/*0x74*/  IRQ_VECTOR(dma1_stream2),
	/*0x78*/  IRQ_VECTOR(dma1_stream3),
	/*0x7C*/  IRQ_VECTOR(dma1_stream4),
	/*0x80*/  IRQ_VECTOR(dma1_stream5),
	/*0x84*/  IRQ_VECTOR(dma1_stream6),
	/*0x88*/  IRQ_VECTOR(adc),
	          #ifndef STM32F401xx
	/*0x8C*/  IRQ_VECTOR(can1_tx),
	/*0x90*/  IRQ_VECTOR(can1_rx0),
	/*0x94*/  IRQ_VECTOR(can1_rx1),
	/*0x98*/  IRQ_VECTOR(can1_sce),
	          #else
	/*0x8C*/   0,0,0,0, // stm32f401 has no can1 module
	          #endif
	/*0x9C*/  IRQ_VECTOR(exti9_5),
	/*0xA0*/  IRQ_VECTOR(tim1_brk_tim9),
	/*0xA4*/  IRQ_VECTOR(tim1_up_tim10),
	/*0xA8*/  IRQ_VECTOR(tim1_trg_com_tim11),
	/*0xAC*/  IRQ_VECTOR(tim1_cc),
	/*0xB0*/  IRQ_VECTOR(tim2),
	/*0xB4*/  IRQ_VECTOR(tim3),
	/*0xB8*/  IRQ_VECTOR(tim4),
	/*0xBC*/  IRQ_VECTOR(i2c1_ev),
	/*0xC0*/  IRQ_VECTOR(i2c1_er),
	/*0xC4*/  IRQ_VECTOR(i2c2_ev),
	/*0xC8*/  IRQ_VECTOR(i2c2_er),
	/*0xCC*/  IRQ_VECTOR(spi1),
	/*0xD0*/  IRQ_VECTOR(spi2),
	/*0xD4*/  IRQ_VECTOR(usart1),
	/*0xD8*/  IRQ_VECTOR(usart2),
	          #ifndef STM32F401xx
	/*0xDC*/     IRQ_VECTOR(usart3),
	            #else
	/*0xDC*/     irq_handler_t reserve2 = 0;  // stm32f401 has no usart3 module
	          #endif
	/*0xE0*/  IRQ_VECTOR(exti15_10),
	/*0xE4*/  IRQ_VECTOR(rtc_alarm),
	/*0xE8*/  IRQ_VECTOR(otg_fs_wkup),
	          #ifndef STM32F401xx
	/*0xEC*/     IRQ_VECTOR(tim8_brk_tim12),
	/*0xF0*/     IRQ_VECTOR(tim8_up_tim13),
	/*0xF4*/     IRQ_VECTOR(tim8_trg_com_tim14),
	/*0xF8*/     IRQ_VECTOR(tim8_cc),
	          #else
	/*0xEC*/     0,0,0,0,  // stm32f401 has no tim8 module
	          #endif
	/*0xFC*/  IRQ_VECTOR(dma1_stream7),
	          #ifndef STM32F401xx
	/*0x100*/    IRQ_VECTOR(fsmc),
	            #else
	/*0x100*/    0,  // stm32f401 has no FSMC/FMS module
	          #endif
	/*0x104*/ IRQ_VECTOR(sdio),
	/*0x108*/ IRQ_VECTOR(tim5),
	/*0x10C*/ IRQ_VECTOR(spi3),
	        #ifndef STM32F401xx
	/*0x110*/ IRQ_VECTOR(uart4),
	/*0x114*/ IRQ_VECTOR(uart5),
	/*0x118*/ IRQ_VECTOR(tim6_dac),
	/*0x11C*/ IRQ_VECTOR(tim7),
	        #else
	/*0x110*/ 0,0,0,0,  // stm32f401 has no uart4/uart5/tim6/tim7 module
	        #endif
	/*0x120*/ IRQ_VECTOR(dma2_stream0),
	/*0x124*/ IRQ_VECTOR(dma2_stream1),
	/*0x128*/ IRQ_VECTOR(dma2_stream2),
	/*0x12C*/ IRQ_VECTOR(dma2_stream3),
	/*0x130*/ IRQ_VECTOR(dma2_stream4),
	        #ifndef STM32F401xx
	/*0x134*/ IRQ_VECTOR(eth),
	/*0x138*/ IRQ_VECTOR(eth_wkup),
	/*0x13C*/ IRQ_VECTOR(can2_tx),
	/*0x140*/ IRQ_VECTOR(can2_rx0),
	/*0x144*/ IRQ_VECTOR(can2_rx1),
	/*0x148*/ IRQ_VECTOR(can2_sce),
	        #else
	/*0x134*/ 0,0,0,0,0,0,  // stm32f401 has no ETH/can2 module
	        #endif
	/*0x14C*/ IRQ_VECTOR(otg_fs),
	/*0x150*/ IRQ_VECTOR(dma2_stream5),
	/*0x154*/ IRQ_VECTOR(dma2_stream6),
	/*0x158*/ IRQ_VECTOR(dma2_stream7),
	/*0x15C*/ IRQ_VECTOR(usart6),
	/*0x160*/ IRQ_VECTOR(i2c3_ev),
	/*0x164*/ IRQ_VECTOR(i2c3_er),
	        #ifndef STM32F401xx
	/*0x168*/ IRQ_VECTOR(otg_hs_ep1_out),
	/*0x16C*/ IRQ_VECTOR(otg_hs_ep1_in),
	/*0x170*/ IRQ_VECTOR(otg_hs_wkup),
	/*0x174*/ IRQ_VECTOR(otg_hs),
	/*0x178*/ IRQ_VECTOR(dcmi),
	              #if defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx) || defined (STM32F429_439xx)
	/*0x17C*/ IRQ_VECTOR(cryp),
	              #else
	/*0x180*/ 0,
	              #endif
	/*0x184*/ IRQ_VECTOR(hash_rng),
	        #else
	/*0x168*/ 0,0,0,0,0,0,0,  // stm32f401 has no OTG_HS/DCMI/CRYP/HASH_RNG module
	        #endif
	/*0x184*/ IRQ_VECTOR(fpu),

	        #if defined STM32F401xx
	/*0x000*/ 0,0,
		        /*0x000*/ IRQ_VECTOR(spi4),
	        #endif

	        #if defined(STM32F427_437xx) || defined(STM32F429_439xx)
	/*0x000*/ IRQ_VECTOR(uart7),
	/*0x000*/ IRQ_VECTOR(uart8),
	/*0x000*/ IRQ_VECTOR(spi4),
	/*0x000*/ IRQ_VECTOR(spi5),
	/*0x000*/ IRQ_VECTOR(spi6),
	/*0x000*/ IRQ_VECTOR(sai1),
	                #if defined (STM32F429_439xx)
	/*0x000*/ IRQ_VECTOR(ltdc),
	/*0x000*/ IRQ_VECTOR(ltdc_er),
	                #else
	/*0x000*/ 0,0; // STM32F427_437xx has no LTDC module
	                #endif
	/*0x000*/ IRQ_VECTOR(dma2d),
	        #endif
    };


#endif /*__IRQ++_H__*/
