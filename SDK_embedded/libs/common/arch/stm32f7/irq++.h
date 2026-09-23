/*
 * irq++.h
 *
 *  Created on: 15 окт. 2017 г.
 *      Author: klen
 */

#ifndef __IRQ++_H__
#define __IRQ++_H__


extern "C" void __attribute__((weak,noinline)) default_exception_handler(void)
{
  volatile stm32f7::nvic_t::irq_num_t irq ;
  irq = stm32f7::cpu_irq_num();
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
        IRQ_HANDLER_WEAK(fmc);
        IRQ_HANDLER_WEAK(sdmmc1);
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
        IRQ_HANDLER_WEAK(crypt);
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
        IRQ_HANDLER_WEAK(sai2);
        IRQ_HANDLER_WEAK(qspi);
        IRQ_HANDLER_WEAK(lptim1);
        IRQ_HANDLER_WEAK(hdmi_cec);
        IRQ_HANDLER_WEAK(i2c4_ev);
        IRQ_HANDLER_WEAK(i2c4_er);
        IRQ_HANDLER_WEAK(spdif_rx);
        IRQ_HANDLER_WEAK(dsi_host);
        IRQ_HANDLER_WEAK(dfsdm1_flt0);
        IRQ_HANDLER_WEAK(dfsdm1_flt1);
        IRQ_HANDLER_WEAK(dfsdm1_flt2);
        IRQ_HANDLER_WEAK(dfsdm1_flt3);
        IRQ_HANDLER_WEAK(sdmmc2);
        IRQ_HANDLER_WEAK(can3_tx);
        IRQ_HANDLER_WEAK(can3_rx0);
        IRQ_HANDLER_WEAK(can3_rx1);
        IRQ_HANDLER_WEAK(can3_cse);
        IRQ_HANDLER_WEAK(jpeg);
        IRQ_HANDLER_WEAK(mdio);

// RM0410  Reference manual STM32F76xxx and STM32F77xxx
// Table 46. STM32F76xxx and STM32F77xxx vector table
const __attribute__ (( section(".flash_irq_vec_table"))) volatile irq_handler_t irq_vector_table[] =
    {
	/*0x000*/ (irq_handler_t)&__stack_end__,            // The initial stack pointer
	/*0x04*/  IRQ_VECTOR(reset),                  // The reset handler
	/*0x08*/  IRQ_VECTOR(nmi_exception),          // Non maskable interrupt. The RCC Clock Security System (CSS) is linked to the NMI vector
	/*0x0C*/  IRQ_VECTOR(hard_fault_exception),   // All class of fault
	/*0x10*/  IRQ_VECTOR(mem_manage_exception),   // Memory management
	/*0x14*/  IRQ_VECTOR(bus_fault_exception),    // Pre-fetch fault, memory access fault
	/*0x000*/ IRQ_VECTOR(usage_fault_exception),  // Undefined instruction or illegal state
	/*0x1C*/  0,0,0,0,/* Reserved */
	/*0x2C*/  IRQ_VECTOR(svc),                    // System service call via SVC instruction (All user and FreeRTOS syscall dispatch over svc)
	                                              // FreeRTOS has 0 svs arg, user above, see crt2.cc
	/*0x30*/  IRQ_VECTOR(debug_monitor),          // Debug Monitor
	/*0x34*/   0,         // Reserved
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
	/*0x8C*/  IRQ_VECTOR(can1_tx),
	/*0x90*/  IRQ_VECTOR(can1_rx0),
	/*0x94*/  IRQ_VECTOR(can1_rx1),
	/*0x98*/  IRQ_VECTOR(can1_sce),
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
	/*0xDC*/  IRQ_VECTOR(usart3),
	/*0xE0*/  IRQ_VECTOR(exti15_10),
	/*0xE4*/  IRQ_VECTOR(rtc_alarm),
	/*0xE8*/  IRQ_VECTOR(otg_fs_wkup),
	/*0xEC*/  IRQ_VECTOR(tim8_brk_tim12),
	/*0xF0*/  IRQ_VECTOR(tim8_up_tim13),
	/*0xF4*/  IRQ_VECTOR(tim8_trg_com_tim14),
	/*0xF8*/  IRQ_VECTOR(tim8_cc),
	/*0xFC*/  IRQ_VECTOR(dma1_stream7),
	/*0x100*/ IRQ_VECTOR(fmc),
	/*0x104*/ IRQ_VECTOR(sdmmc1),
	/*0x108*/ IRQ_VECTOR(tim5),
	/*0x10C*/ IRQ_VECTOR(spi3),
	/*0x110*/ IRQ_VECTOR(uart4),
	/*0x114*/ IRQ_VECTOR(uart5),
	/*0x118*/ IRQ_VECTOR(tim6_dac),
	/*0x11C*/ IRQ_VECTOR(tim7),
	/*0x120*/ IRQ_VECTOR(dma2_stream0),
	/*0x124*/ IRQ_VECTOR(dma2_stream1),
	/*0x128*/ IRQ_VECTOR(dma2_stream2),
	/*0x12C*/ IRQ_VECTOR(dma2_stream3),
	/*0x130*/ IRQ_VECTOR(dma2_stream4),
	/*0x134*/ IRQ_VECTOR(eth),
	/*0x138*/ IRQ_VECTOR(eth_wkup),
	/*0x13C*/ IRQ_VECTOR(can2_tx),
	/*0x140*/ IRQ_VECTOR(can2_rx0),
	/*0x144*/ IRQ_VECTOR(can2_rx1),
	/*0x148*/ IRQ_VECTOR(can2_sce),
	/*0x14C*/ IRQ_VECTOR(otg_fs),
	/*0x150*/ IRQ_VECTOR(dma2_stream5),
	/*0x154*/ IRQ_VECTOR(dma2_stream6),
	/*0x158*/ IRQ_VECTOR(dma2_stream7),
	/*0x15C*/ IRQ_VECTOR(usart6),
	/*0x160*/ IRQ_VECTOR(i2c3_ev),
	/*0x164*/ IRQ_VECTOR(i2c3_er),
	/*0x168*/ IRQ_VECTOR(otg_hs_ep1_out),
	/*0x16C*/ IRQ_VECTOR(otg_hs_ep1_in),
	/*0x170*/ IRQ_VECTOR(otg_hs_wkup),
	/*0x174*/ IRQ_VECTOR(otg_hs),
	/*0x178*/ IRQ_VECTOR(dcmi),
	/*0x17C*/ IRQ_VECTOR(crypt),
	/*0x180*/ IRQ_VECTOR(hash_rng),
	/*0x184*/ IRQ_VECTOR(fpu),
	/*0x188*/ IRQ_VECTOR(uart7),
	/*0x18C*/ IRQ_VECTOR(uart8),
	/*0x190*/ IRQ_VECTOR(spi4),
	/*0x194*/ IRQ_VECTOR(spi5),
	/*0x198*/ IRQ_VECTOR(spi6),
	/*0x19C*/ IRQ_VECTOR(sai1),
	/*0x1A0*/ IRQ_VECTOR(ltdc),
	/*0x1A4*/ IRQ_VECTOR(ltdc_er),
	/*0x1A8*/ IRQ_VECTOR(dma2d),
	/*0x1AC*/ IRQ_VECTOR(sai2),
	/*0x1B0*/ IRQ_VECTOR(qspi),
	/*0x1B4*/ IRQ_VECTOR(lptim1),
	/*0x1B8*/ IRQ_VECTOR(hdmi_cec),
	/*0x1BC*/ IRQ_VECTOR(i2c4_ev),
	/*0x1C0*/ IRQ_VECTOR(i2c4_er),
	/*0x1C4*/ IRQ_VECTOR(spdif_rx),
	/*0x1C8*/ IRQ_VECTOR(dsi_host),
	/*0x1CC*/ IRQ_VECTOR(dfsdm1_flt0),
	/*0x1D0*/ IRQ_VECTOR(dfsdm1_flt1),
	/*0x1D4*/ IRQ_VECTOR(dfsdm1_flt2),
	/*0x1D8*/ IRQ_VECTOR(dfsdm1_flt3),
	/*0x1DC*/ IRQ_VECTOR(sdmmc2),
	/*0x1E0*/ IRQ_VECTOR(can3_tx),
	/*0x1E4*/ IRQ_VECTOR(can3_rx0),
	/*0x1E8*/ IRQ_VECTOR(can3_rx1),
	/*0x1EC*/ IRQ_VECTOR(can3_cse),
	/*0x1F0*/ IRQ_VECTOR(jpeg),
	/*0x1F4*/ IRQ_VECTOR(mdio),
    };



#endif /*__IRQ++_H__*/
