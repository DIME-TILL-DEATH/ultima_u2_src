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
  volatile stm32h7::nvic_t::irq_num_t irq ;
  irq = stm32h7::cpu_irq_num();
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
        IRQ_HANDLER_WEAK(tamp_stamp);
        IRQ_HANDLER_WEAK(rtc_wkup);
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
        IRQ_HANDLER_WEAK(fdcan1_it0);
        IRQ_HANDLER_WEAK(fdcan2_it0);
        IRQ_HANDLER_WEAK(fdcan1_it1);
        IRQ_HANDLER_WEAK(fdcan2_it1);
        IRQ_HANDLER_WEAK(exti9_5);
        IRQ_HANDLER_WEAK(tim1_brk);
        IRQ_HANDLER_WEAK(tim1_up);
        IRQ_HANDLER_WEAK(tim1_trg_com);
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
        IRQ_HANDLER_WEAK(fdcan_cal);

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
        IRQ_HANDLER_WEAK(otg_fs_ep1_out);
        IRQ_HANDLER_WEAK(otg_fs_ep1_in);
        IRQ_HANDLER_WEAK(otg_fs_wkup);
        IRQ_HANDLER_WEAK(otg_fs);
        IRQ_HANDLER_WEAK(dmamux1_ovr);
        IRQ_HANDLER_WEAK(hrtim1_master);
        IRQ_HANDLER_WEAK(hrtim1_tima);
        IRQ_HANDLER_WEAK(hrtim1_timb);
        IRQ_HANDLER_WEAK(hrtim1_timc);
        IRQ_HANDLER_WEAK(hrtim1_timd);
        IRQ_HANDLER_WEAK(hrtim1_time);
        IRQ_HANDLER_WEAK(hrtim1_flt);
        IRQ_HANDLER_WEAK(dfsdm1_flt0);
        IRQ_HANDLER_WEAK(dfsdm1_flt1);
        IRQ_HANDLER_WEAK(dfsdm1_flt2);
        IRQ_HANDLER_WEAK(dfsdm1_flt3);
        IRQ_HANDLER_WEAK(sai3);
        IRQ_HANDLER_WEAK(swpmi1);
        IRQ_HANDLER_WEAK(tim15);
        IRQ_HANDLER_WEAK(tim16);
        IRQ_HANDLER_WEAK(tim17);
        IRQ_HANDLER_WEAK(msios_wkup);
        IRQ_HANDLER_WEAK(mdios);
        IRQ_HANDLER_WEAK(jpeg);
        IRQ_HANDLER_WEAK(mdma);
        IRQ_HANDLER_WEAK(sdmmc2);
        IRQ_HANDLER_WEAK(hsem1);
        IRQ_HANDLER_WEAK(adc3);
        IRQ_HANDLER_WEAK(dmamux2_ovr);
        IRQ_HANDLER_WEAK(bdma_channel0);
        IRQ_HANDLER_WEAK(bdma_channel1);
        IRQ_HANDLER_WEAK(bdma_channel2);
        IRQ_HANDLER_WEAK(bdma_channel3);
        IRQ_HANDLER_WEAK(bdma_channel4);
        IRQ_HANDLER_WEAK(bdma_channel5);
        IRQ_HANDLER_WEAK(bdma_channel6);
        IRQ_HANDLER_WEAK(bdma_channel7);
        IRQ_HANDLER_WEAK(comp);
        IRQ_HANDLER_WEAK(lptim2);
        IRQ_HANDLER_WEAK(lptim3);
        IRQ_HANDLER_WEAK(lptim4);
        IRQ_HANDLER_WEAK(lptim5);
        IRQ_HANDLER_WEAK(lpuart1);
        IRQ_HANDLER_WEAK(wwdg_reset);
        IRQ_HANDLER_WEAK(crs);
        IRQ_HANDLER_WEAK(ramecc);
        IRQ_HANDLER_WEAK(sai4);
	IRQ_HANDLER_WEAK(wkup_pin);

// RM0433  Reference manual STM32H743/753 and STM32H750
// Table 138. NVIC
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
	/*0x40*/     IRQ_VECTOR(wwdg),
	/*0x44*/     IRQ_VECTOR(pvd),
	/*0x48*/     IRQ_VECTOR(tamp_stamp),
	/*0x4c*/     IRQ_VECTOR(rtc_wkup),
	/*0x50*/     IRQ_VECTOR(flash),
	/*0x54*/     IRQ_VECTOR(rcc),
	/*0x58*/     IRQ_VECTOR(exti0),
	/*0x5c*/     IRQ_VECTOR(exti1),
	/*0x60*/     IRQ_VECTOR(exti2),
	/*0x64*/     IRQ_VECTOR(exti3),
	/*0x68*/     IRQ_VECTOR(exti4),
	/*0x6c*/     IRQ_VECTOR(dma1_stream0),
	/*0x70*/     IRQ_VECTOR(dma1_stream1),
	/*0x74*/     IRQ_VECTOR(dma1_stream2),
	/*0x78*/     IRQ_VECTOR(dma1_stream3),
	/*0x7c*/     IRQ_VECTOR(dma1_stream4),
	/*0x80*/     IRQ_VECTOR(dma1_stream5),
	/*0x84*/     IRQ_VECTOR(dma1_stream6),
	/*0x88*/     IRQ_VECTOR(adc),
	/*0x8c*/     IRQ_VECTOR(fdcan1_it0),
	/*0x90*/     IRQ_VECTOR(fdcan2_it0),
	/*0x94*/     IRQ_VECTOR(fdcan1_it1),
	/*0x98*/     IRQ_VECTOR(fdcan2_it1),
	/*0x9c*/     IRQ_VECTOR(exti9_5),
	/*0xa0*/     IRQ_VECTOR(tim1_brk),
	/*0xa4*/     IRQ_VECTOR(tim1_up),
	/*0xa8*/     IRQ_VECTOR(tim1_trg_com),
	/*0xac*/     IRQ_VECTOR(tim1_cc),
	/*0xb0*/     IRQ_VECTOR(tim2),
	/*0xb4*/     IRQ_VECTOR(tim3),
	/*0xb8*/     IRQ_VECTOR(tim4),
	/*0xbc*/     IRQ_VECTOR(i2c1_ev),
	/*0xc0*/     IRQ_VECTOR(i2c1_er),
	/*0xc4*/     IRQ_VECTOR(i2c2_ev),
	/*0xc8*/     IRQ_VECTOR(i2c2_er),
	/*0xcc*/     IRQ_VECTOR(spi1),
	/*0xd0*/     IRQ_VECTOR(spi2),
	/*0xd4*/     IRQ_VECTOR(usart1),
	/*0xd8*/     IRQ_VECTOR(usart2),
	/*0xdc*/     IRQ_VECTOR(usart3),
	/*0xe0*/     IRQ_VECTOR(exti15_10),
	/*0xe4*/     IRQ_VECTOR(rtc_alarm),
        0,
	/*0xec*/     IRQ_VECTOR(tim8_brk_tim12),
	/*0xf0*/     IRQ_VECTOR(tim8_up_tim13),
	/*0xf4*/     IRQ_VECTOR(tim8_trg_com_tim14),
	/*0xf8*/     IRQ_VECTOR(tim8_cc),
	/*0xfc*/     IRQ_VECTOR(dma1_stream7),
	/*0x100*/     IRQ_VECTOR(fmc),
	/*0x104*/     IRQ_VECTOR(sdmmc1),
	/*0x108*/     IRQ_VECTOR(tim5),
	/*0x10c*/     IRQ_VECTOR(spi3),
	/*0x110*/     IRQ_VECTOR(uart4),
	/*0x114*/     IRQ_VECTOR(uart5),
	/*0x118*/     IRQ_VECTOR(tim6_dac),
	/*0x11c*/     IRQ_VECTOR(tim7),
	/*0x120*/     IRQ_VECTOR(dma2_stream0),
	/*0x124*/     IRQ_VECTOR(dma2_stream1),
	/*0x128*/     IRQ_VECTOR(dma2_stream2),
	/*0x12c*/     IRQ_VECTOR(dma2_stream3),
	/*0x130*/     IRQ_VECTOR(dma2_stream4),
	/*0x134*/     IRQ_VECTOR(eth),
	/*0x138*/     IRQ_VECTOR(eth_wkup),
	/*0x13c*/     IRQ_VECTOR(fdcan_cal),
        0,0,0,0,
	/*0x150*/     IRQ_VECTOR(dma2_stream5),
	/*0x154*/     IRQ_VECTOR(dma2_stream6),
	/*0x158*/     IRQ_VECTOR(dma2_stream7),
	/*0x15c*/     IRQ_VECTOR(usart6),
	/*0x160*/     IRQ_VECTOR(i2c3_ev),
	/*0x164*/     IRQ_VECTOR(i2c3_er),
	/*0x168*/     IRQ_VECTOR(otg_hs_ep1_out),
	/*0x16c*/     IRQ_VECTOR(otg_hs_ep1_in),
	/*0x170*/     IRQ_VECTOR(otg_hs_wkup),
	/*0x174*/     IRQ_VECTOR(otg_hs),
	/*0x178*/     IRQ_VECTOR(dcmi),
	/*0x17c*/     IRQ_VECTOR(crypt),
	/*0x180*/     IRQ_VECTOR(hash_rng),
	/*0x184*/     IRQ_VECTOR(fpu),
	/*0x188*/     IRQ_VECTOR(uart7),
	/*0x18c*/     IRQ_VECTOR(uart8),
	/*0x190*/     IRQ_VECTOR(spi4),
	/*0x194*/     IRQ_VECTOR(spi5),
	/*0x198*/     IRQ_VECTOR(spi6),
	/*0x19c*/     IRQ_VECTOR(sai1),
	/*0x1a0*/     IRQ_VECTOR(ltdc),
	/*0x1a4*/     IRQ_VECTOR(ltdc_er),
	/*0x1a8*/     IRQ_VECTOR(dma2d),
	/*0x1ac*/     IRQ_VECTOR(sai2),
	/*0x1b0*/     IRQ_VECTOR(qspi),
	/*0x1b4*/     IRQ_VECTOR(lptim1),
	/*0x1b8*/     IRQ_VECTOR(hdmi_cec),
	/*0x1bc*/     IRQ_VECTOR(i2c4_ev),
	/*0x1c0*/     IRQ_VECTOR(i2c4_er),
	/*0x1c4*/     IRQ_VECTOR(spdif_rx),
	/*0x1c8*/     IRQ_VECTOR(otg_fs_ep1_out),
	/*0x1cc*/     IRQ_VECTOR(otg_fs_ep1_in),
	/*0x1d0*/     IRQ_VECTOR(otg_fs_wkup),
	/*0x1d4*/     IRQ_VECTOR(otg_fs),
	/*0x1d8*/     IRQ_VECTOR(dmamux1_ovr),
	/*0x1dc*/     IRQ_VECTOR(hrtim1_master),
	/*0x1e0*/     IRQ_VECTOR(hrtim1_tima),
	/*0x1e4*/     IRQ_VECTOR(hrtim1_timb),
	/*0x1e8*/     IRQ_VECTOR(hrtim1_timc),
	/*0x1ec*/     IRQ_VECTOR(hrtim1_timd),
	/*0x1f0*/     IRQ_VECTOR(hrtim1_time),
	/*0x1f4*/     IRQ_VECTOR(hrtim1_flt),
	/*0x1f8*/     IRQ_VECTOR(dfsdm1_flt0),
	/*0x1fc*/     IRQ_VECTOR(dfsdm1_flt1),
	/*0x200*/     IRQ_VECTOR(dfsdm1_flt2),
	/*0x204*/     IRQ_VECTOR(dfsdm1_flt3),
	/*0x208*/     IRQ_VECTOR(sai3),
	/*0x20c*/     IRQ_VECTOR(swpmi1),
	/*0x210*/     IRQ_VECTOR(tim15),
	/*0x214*/     IRQ_VECTOR(tim16),
	/*0x218*/     IRQ_VECTOR(tim17),
	/*0x21c*/     IRQ_VECTOR(msios_wkup),
	/*0x220*/     IRQ_VECTOR(mdios),
	/*0x224*/     IRQ_VECTOR(jpeg),
	/*0x228*/     IRQ_VECTOR(mdma),
	0,
	/*0x230*/     IRQ_VECTOR(sdmmc2),
	/*0x234*/     IRQ_VECTOR(hsem1),
	0,
	/*0x23c*/     IRQ_VECTOR(adc3),
	/*0x240*/     IRQ_VECTOR(dmamux2_ovr),
	/*0x244*/     IRQ_VECTOR(bdma_channel0),
	/*0x248*/     IRQ_VECTOR(bdma_channel1),
	/*0x24c*/     IRQ_VECTOR(bdma_channel2),
	/*0x250*/     IRQ_VECTOR(bdma_channel3),
	/*0x254*/     IRQ_VECTOR(bdma_channel4),
	/*0x258*/     IRQ_VECTOR(bdma_channel5),
	/*0x25c*/     IRQ_VECTOR(bdma_channel6),
	/*0x260*/     IRQ_VECTOR(bdma_channel7),
	/*0x264*/     IRQ_VECTOR(comp),
	/*0x268*/     IRQ_VECTOR(lptim2),
	/*0x26c*/     IRQ_VECTOR(lptim3),
	/*0x270*/     IRQ_VECTOR(lptim4),
	/*0x274*/     IRQ_VECTOR(lptim5),
	/*0x278*/     IRQ_VECTOR(lpuart1),
	/*0x27c*/     IRQ_VECTOR(wwdg_reset),
	/*0x280*/     IRQ_VECTOR(crs),
	/*0x284*/     IRQ_VECTOR(ramecc),
	/*0x288*/     IRQ_VECTOR(sai4),
	0,0,
	/*0x200*/     IRQ_VECTOR(wkup_pin),
    };



#endif /*__IRQ++_H__*/
