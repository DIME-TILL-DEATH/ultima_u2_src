#ifndef __STM32++_H__
#define __STM32++_H__

#include "gnu_linker.h"  // необходим для crt_init()
#include "supc++.h" // для std::__throw_invalid_argument

#include "arch/cortex-m/cortex_m0.h"

namespace stm32f0
{

#if 0
static const uint32_t flash_addr =            0x08000000; /*!< FLASH(up to 1 MB) base address in the alias region */
static const uint32_t data_eeprom_addr =      0x08080000; /*!< DATA_EEPROM base address in the alias region */
static const uint32_t sram_addr  =            0x20000000; /*!< SRAM1(160 KB) base address in the alias region    */
static const uint32_t periph_addr =           0x40000000; /*!< Peripheral base address in the alias region       */

/*!< Peripheral memory map */
static const uint32_t apb_periph_addr =      periph_addr;
static const uint32_t ahb_periph_addr =      periph_addr + 0x00020000;
static const uint32_t io_periph_addr  =      periph_addr + 0x10000000;

/*!< APB peripherals */
static const uint32_t tim2_addr     =     apb_periph_addr + 0x00000000;
static const uint32_t rtc_addr      =     apb_periph_addr + 0x00002800;
static const uint32_t wwdg_addr     =     apb_periph_addr + 0x00002C00;
static const uint32_t iwdg_addr     =     apb_periph_addr + 0x00003000;
static const uint32_t usart2_addr   =     apb_periph_addr + 0x00004400;
static const uint32_t lpuart1_addr  =     apb_periph_addr + 0x00004800;
static const uint32_t i2c_addr      =     apb_periph_addr + 0x00005400;
static const uint32_t pwr_addr      =     apb_periph_addr + 0x00007000;
static const uint32_t lptim1_addr   =     apb_periph_addr + 0x00007C00;

static const uint32_t syscfg_addr   =     apb_periph_addr + 0x00010000;
static const uint32_t comp_addr    =     apb_periph_addr + 0x00010018;
//static const uint32_t comp2_addr    =     apb_periph_addr + 0x0001001C;
static const uint32_t exti_addr     =     apb_periph_addr + 0x00010400;
static const uint32_t tim21_addr    =     apb_periph_addr + 0x00010800;
//static const uint32_t adc1_addr     =     apb_periph_addr + 0x00012400;
//static const uint32_t ADC_addr      =     apb_periph_addr + 0x00012708;
static const uint32_t spi1_addr     =     apb_periph_addr + 0x00013000;
static const uint32_t dbmcu_addr   =     apb_periph_addr + 0x00015800;

/*!< AHB peripherals */
static const uint32_t dma1_addr          = ahb_periph_addr + 0x00000000;
static const uint32_t dma1_channel1_addr = dma1_addr + 0x00000008;
static const uint32_t dma1_channel2_addr = dma1_addr + 0x0000001C;
static const uint32_t dma1_channel3_addr = dma1_addr + 0x00000030;
static const uint32_t dma1_channel4_addr = dma1_addr + 0x00000044;
static const uint32_t DMA1_channel5_addr = dma1_addr + 0x00000058;
static const uint32_t dma1_cselr_addr    = dma1_addr + 0x000000A8;
static const uint32_t rcc_addr           = ahb_periph_addr + 0x00001000;
static const uint32_t frach_r_addr       = ahb_periph_addr + 0x00002000; /*!< FLASH registers base address */
static const uint32_t crc_addr           = ahb_periph_addr + 0x00003000;

static const uint32_t ob_addr       =     0x1FF80000;        /*!< FLASH Option Bytes base address */
static const uint32_t flash_size_addr=    0x1FF8007C;        /*!< FLASH Size register base address */
static const uint32_t uid_addr      =     0x1FF80050;        /*!< Unique device ID register base address  */

/*!< IO peripherals */
static const uint32_t gpioa_addr    =     io_periph_addr + 0x00000000;
static const uint32_t gpiob_addr    =     io_periph_addr + 0x00000400;
static const uint32_t gpioc_addr    =     io_periph_addr + 0x00000800;
static const uint32_t gpiod_addr    =     io_periph_addr + 0x00000C00;
static const uint32_t gpioe_addr    =     io_periph_addr + 0x00001000;
static const uint32_t gpioh_addr    =     io_periph_addr + 0x00001C00;

#endif

struct nvic_t : public core_nvic_t
{
 enum class irq_num_t : int16_t
  {
    thread =           -16,
    reset =            -15,
    non_maskable_int = -14,
    hard_fault =       -13,
    svc =              -5,
    pend_svc =         -2,
    sys_tick =         -1,
    // stm32 specific interrupt numbers
    wwdg = 0 ,
    pvd,
    rtc,
    flash,
    rcc,
    exti0_1,
    exti2_3,
    exti4_15,
    touch_sense,
    dma_channel1,
    dma_channel2_3,
    dma_channel4_7,
    adc_comp,
    tim1_brk_up_trg_comm,
    tim1_cc,
    tim2,
    tim3,
    tim6_dac,
    tim7,
    tim14,
    tim15,
    tim16,
    tim17,
    i2c1,
    i2c2,
    spi1,
    spi2,
    usart1,
    usart2,
    cec=30
  }  ;


   struct state_t { enum enum_t{ disable=0 , enable };};
   struct pending_t { enum enum_t{ not_pending=0 , pending };};
   struct active_t { enum enum_t{ not_active=0 , active };};

   inline void enable( const irq_num_t irq_num )        {NRO set_enable_vec[0] = 1 << ((int16_t)irq_num); }
   inline void disable( const irq_num_t irq_num )       {NRO clear_enable_vec[0] = 1<<((int16_t)irq_num); }
   inline auto state( const irq_num_t irq_num )   const {NRO return (state_t::enum_t)(set_enable_vec[0] & 1<<((int16_t)irq_num)); }
   inline void pending_set( const irq_num_t irq_num )   {NRO set_pending_vec[0] = 1 << ((int16_t)irq_num); }
   inline void pending_clear( const irq_num_t irq_num ) {NRO clear_pending_vec[0] = 1<<((int16_t)irq_num); }
   inline auto pending( const irq_num_t irq_num ) const {NRO return (pending_t::enum_t)(set_pending_vec[0] & 1<<((int16_t)irq_num)); }

   //inline void priority( const irq_num_t irq_num, const uint8_t priority ) { NRO (int16_t)irq_num < 0 ? scb.system_handler_priority[ (int16_t)irq_num - 8] = priority :
   //                                                                                            priority_vec[(int16_t)irq_num]      = priority ; }
   //inline uint8_t priority( const irq_num_t irq_num) const { NRO return (int16_t)irq_num < 0 ? scb.system_handler_priority[ (int16_t)irq_num - 8] :
   //                                                                               priority_vec[(int16_t)irq_num] ; }


   MAKE_NVIC_IRQ_ITEM(wwdg)
   MAKE_NVIC_IRQ_ITEM(pvd)
   MAKE_NVIC_IRQ_ITEM(rtc)
   MAKE_NVIC_IRQ_ITEM(flash)
   MAKE_NVIC_IRQ_ITEM(rcc)
   MAKE_NVIC_IRQ_ITEM(exti0_1)
   MAKE_NVIC_IRQ_ITEM(exti2_3)
   MAKE_NVIC_IRQ_ITEM(exti4_15)
   MAKE_NVIC_IRQ_ITEM(touch_sense)
   MAKE_NVIC_IRQ_ITEM(dma_channel1)
   MAKE_NVIC_IRQ_ITEM(dma_channel2_3)
   MAKE_NVIC_IRQ_ITEM(dma_channel4_7)
   MAKE_NVIC_IRQ_ITEM(adc_comp)
   MAKE_NVIC_IRQ_ITEM(tim1_brk_up_trg_comm)
   MAKE_NVIC_IRQ_ITEM(tim1_cc)
   MAKE_NVIC_IRQ_ITEM(tim2)
   MAKE_NVIC_IRQ_ITEM(tim3)
   MAKE_NVIC_IRQ_ITEM(tim6_dac)
   MAKE_NVIC_IRQ_ITEM(tim7)
   MAKE_NVIC_IRQ_ITEM(tim14)
   MAKE_NVIC_IRQ_ITEM(tim15)
   MAKE_NVIC_IRQ_ITEM(tim16)
   MAKE_NVIC_IRQ_ITEM(tim17)
   MAKE_NVIC_IRQ_ITEM(i2c1)
   MAKE_NVIC_IRQ_ITEM(i2c2)
   MAKE_NVIC_IRQ_ITEM(spi1)
   MAKE_NVIC_IRQ_ITEM(spi2)
   MAKE_NVIC_IRQ_ITEM(usart1)
   MAKE_NVIC_IRQ_ITEM(usart2)
   MAKE_NVIC_IRQ_ITEM(cec)

};

static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало c уровня ниже(cm4_core) для биндинга в stm32f4::nvic_t

}

#if 0
#include "rcc++.h"    // TODO сделать высокоуровневые вызовы rcc.apb1_peripheral_clock.can1_enable(); -> rcc.can1_enable();
#include "pwr++.h"
#include "gpio++.h"


#include "exti++.h"
#include "flash++.h"
#include "gpio++.h"   // TODO
#include "iwdg++.h"

#include "rng++.h"
#include "spi++.h"  // TODO все доделать
#include "syscfg++.h"


#endif

namespace stm32f0
{

// extern const rcc_t::system_init_profile_t& system_init_profile ;

void system_init_xx();
inline __attribute__((always_inline)) void system_init(const uint32_t vec_tab_offset/*, const rcc_t::system_init_profile_t& system_init_profile*/)
{
  system_init_xx();
}


//---------------------------------------------------------------------
inline __attribute__((always_inline)) void crt_init()
{
   // fill  all internal memory for dummy pattern
   #ifndef FILL_RAM_PATTRERN
               #define FILL_RAM_PATTRERN 0x12345678
   #endif

   volatile unsigned long* ram = (unsigned long*)gnu_linker_sram_start() ;
   volatile unsigned long* ram_end  ;
   asm volatile ("mov %0 , sp \n" : "=r"(ram_end) : : );
   while( ram < ram_end )
          {
           *(ram++) = FILL_RAM_PATTRERN;
          }

  // init .data section
  volatile unsigned long* data_load = (unsigned long*)gnu_linker_data_load_start();
  volatile unsigned long* data = (unsigned long*)gnu_linker_data_start();
  volatile unsigned long* data_end = (unsigned long*)gnu_linker_data_end();
  while( data < data_end )
         {
          *(data++) = *(data_load++);
         }



  // init .bss section
  volatile unsigned long* bss = (unsigned long*)gnu_linker_bss_start() ;
  volatile unsigned long* bss_end = (unsigned long*)gnu_linker_bss_end() ;
  while(bss < bss_end )
   {
     *(bss++) =  0 ;
   }
}
//---------------------------------------------------------------------
//Поддержка обработки ELF секций .{pre_init,init,fini}_array sections.


// Iterate over all the init routines.
inline void __libc_init_array (void)
{
  size_t count;
  size_t i;

  count = __preinit_array_end__ - __preinit_array_start__ ;
  for (i = 0; i < count; i++)
    __preinit_array_start__[i] ();

  _init ();

  count = __init_array_end__ - __init_array_start__;
  for (i = 0; i < count; i++)
    __init_array_start__[i] ();

}

/* Run all the cleanup routines.  */
inline void __libc_fini_array (void)
{
  size_t count;
  size_t i;

  count = __fini_array_end__ - __fini_array_start__;
  for (i = count; i > 0; i--)
    __fini_array_start__[i-1] ();

  _fini ();
}
//---------------------------------------------------------------------

inline __attribute__((noreturn)) void reset_irq_handler()
{
        // delay for GDB connect
	#ifndef DELAY_FOR_GDB
		#define DELAY_FOR_GDB 10000
	#endif

	nop_while(DELAY_FOR_GDB);

        // reset PLLs, RCC , Vector Table Relocation in Internal FLASH, external RAM , other...
        system_init((uint32_t)gnu_linker_vec_start()/* TODO ,system_init_profile*/);

	// fill memory and initialize .bss , .data  sections
	crt_init();

	// switch vec table to ram
	#if defined __USE_RAM_VEC_TABLE__
		vec_table_copy2ram( 1 ) ;
	#endif //RAM_VEC_TABLE

	// вызов конструкторов глобальных объектов
	// и функций с атрибутом constructor

	__libc_init_array() ;

	// вызов основной функции
	int retval = main();

	// вызов деструкторов  глобальных объектов
	// и функций с атрибутом destructor
	__libc_fini_array() ;

	// call exit function
	__main_exit_handler(retval);
}

// get a number of IRQ
// result:
//      [-16...239] - Handler CPU mode, result val is ISR number
//      -16     Thread CPU Mode,
//      -15..-1 CPU core exception
//       0..239 Prepherial interrupt requst
static inline nvic_t::irq_num_t cpu_irq_num()
{
   return  (nvic_t::irq_num_t)(cpu_exception_num() - 16);
}


} // stm32f0

using namespace stm32f0 ;

#endif /* __STM32++_H__ */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
