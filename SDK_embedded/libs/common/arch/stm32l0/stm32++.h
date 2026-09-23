#ifndef __STM32++_H__
#define __STM32++_H__

#include "gnu_linker.h"  // необходим для crt_init()
#include "supc++.h" // для std::__throw_invalid_argument

#include "arch/cortex-m/cortex_m0plus++.h"

namespace stm32l0
{
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

    dma1_channel1=9,
    dma1_channel2_3,
    dma1_channel4_5,
    adc1_comp,
    lptim1,
    tim2=15,
    tim21=20,
    i2c1=23,
    usart2=28,
    lpuart1
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
   MAKE_NVIC_IRQ_ITEM(dma1_channel1)
   MAKE_NVIC_IRQ_ITEM(dma1_channel2_3)
   MAKE_NVIC_IRQ_ITEM(dma1_channel4_5)
   MAKE_NVIC_IRQ_ITEM(adc1_comp)
   MAKE_NVIC_IRQ_ITEM(lptim1)
   MAKE_NVIC_IRQ_ITEM(tim2)
   MAKE_NVIC_IRQ_ITEM(tim21)
   MAKE_NVIC_IRQ_ITEM(i2c1)
   MAKE_NVIC_IRQ_ITEM(usart2)
   MAKE_NVIC_IRQ_ITEM(lpuart1)
};

static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало c уровня ниже(cm4_core) для биндинга в stm32f4::nvic_t

}


#include "rcc++.h"    // TODO сделать высокоуровневые вызовы rcc.apb1_peripheral_clock.can1_enable(); -> rcc.can1_enable();
#include "pwr++.h"
#include "gpio++.h"
#if 0

#include "exti++.h"
#include "flash++.h"
#include "gpio++.h"   // TODO
#include "iwdg++.h"

#include "rng++.h"
#include "spi++.h"  // TODO все доделать
#include "syscfg++.h"


#endif

namespace stm32l0
{

  extern const rcc_t::system_init_profile_t& system_init_profile ;

#if 0
  /** @addtogroup Peripheral_registers_structures
    * @{
    */

  /**
    * @brief Analog to Digital Converter
    */

  typedef struct
  {
    __IO uint32_t ISR;          /*!< ADC Interrupt and Status register,                          Address offset:0x00 */
    __IO uint32_t IER;          /*!< ADC Interrupt Enable register,                              Address offset:0x04 */
    __IO uint32_t CR;           /*!< ADC Control register,                                       Address offset:0x08 */
    __IO uint32_t CFGR1;        /*!< ADC Configuration register 1,                               Address offset:0x0C */
    __IO uint32_t CFGR2;        /*!< ADC Configuration register 2,                               Address offset:0x10 */
    __IO uint32_t SMPR;         /*!< ADC Sampling time register,                                 Address offset:0x14 */
    uint32_t   RESERVED1;       /*!< Reserved,                                                                  0x18 */
    uint32_t   RESERVED2;       /*!< Reserved,                                                                  0x1C */
    __IO uint32_t TR;           /*!< ADC watchdog threshold register,                            Address offset:0x20 */
    uint32_t   RESERVED3;       /*!< Reserved,                                                                  0x24 */
    __IO uint32_t CHSELR;       /*!< ADC channel selection register,                             Address offset:0x28 */
    uint32_t   RESERVED4[5];    /*!< Reserved,                                                                  0x2C */
    __IO uint32_t DR;           /*!< ADC data register,                                          Address offset:0x40 */
    uint32_t   RESERVED5[28];   /*!< Reserved,                                                           0x44 - 0xB0 */
    __IO uint32_t CALFACT;      /*!< ADC data register,                                          Address offset:0xB4 */
  } ADC_TypeDef;

  typedef struct
  {
    __IO uint32_t CCR;
  } ADC_Common_TypeDef;


  /**
    * @brief Comparator
    */

  typedef struct
  {
    __IO uint32_t CSR;     /*!< COMP comparator control and status register, Address offset: 0x18 */
  } COMP_TypeDef;

  typedef struct
  {
    __IO uint32_t CSR;         /*!< COMP control and status register, used for bits common to several COMP instances, Address offset: 0x00 */
  } COMP_Common_TypeDef;


  /**
  * @brief CRC calculation unit
  */

  typedef struct
  {
  __IO uint32_t DR;            /*!< CRC Data register,                            Address offset: 0x00 */
  __IO uint8_t IDR;            /*!< CRC Independent data register,                Address offset: 0x04 */
  uint8_t RESERVED0;           /*!< Reserved,                                                     0x05 */
  uint16_t RESERVED1;          /*!< Reserved,                                                     0x06 */
  __IO uint32_t CR;            /*!< CRC Control register,                         Address offset: 0x08 */
  uint32_t RESERVED2;          /*!< Reserved,                                                     0x0C */
  __IO uint32_t INIT;          /*!< Initial CRC value register,                   Address offset: 0x10 */
  __IO uint32_t POL;           /*!< CRC polynomial register,                      Address offset: 0x14 */
  } CRC_TypeDef;

  /**
    * @brief Debug MCU
    */

  typedef struct
  {
    __IO uint32_t IDCODE;       /*!< MCU device ID code,                          Address offset: 0x00 */
    __IO uint32_t CR;           /*!< Debug MCU configuration register,            Address offset: 0x04 */
    __IO uint32_t APB1FZ;       /*!< Debug MCU APB1 freeze register,              Address offset: 0x08 */
    __IO uint32_t APB2FZ;       /*!< Debug MCU APB2 freeze register,              Address offset: 0x0C */
  }DBGMCU_TypeDef;

  /**
    * @brief DMA Controller
    */

  typedef struct
  {
    __IO uint32_t CCR;          /*!< DMA channel x configuration register */
    __IO uint32_t CNDTR;        /*!< DMA channel x number of data register */
    __IO uint32_t CPAR;         /*!< DMA channel x peripheral address register */
    __IO uint32_t CMAR;         /*!< DMA channel x memory address register */
  } DMA_Channel_TypeDef;

  typedef struct
  {
    __IO uint32_t ISR;          /*!< DMA interrupt status register,               Address offset: 0x00 */
    __IO uint32_t IFCR;         /*!< DMA interrupt flag clear register,           Address offset: 0x04 */
  } DMA_TypeDef;

  typedef struct
  {
    __IO uint32_t CSELR;        /*!< DMA channel selection register,              Address offset: 0xA8 */
  } DMA_Request_TypeDef;

  /**
    * @brief External Interrupt/Event Controller
    */

  typedef struct
  {
    __IO uint32_t IMR;          /*!<EXTI Interrupt mask register,                 Address offset: 0x00 */
    __IO uint32_t EMR;          /*!<EXTI Event mask register,                     Address offset: 0x04 */
    __IO uint32_t RTSR;         /*!<EXTI Rising trigger selection register ,      Address offset: 0x08 */
    __IO uint32_t FTSR;         /*!<EXTI Falling trigger selection register,      Address offset: 0x0C */
    __IO uint32_t SWIER;        /*!<EXTI Software interrupt event register,       Address offset: 0x10 */
    __IO uint32_t PR;           /*!<EXTI Pending register,                        Address offset: 0x14 */
  }EXTI_TypeDef;

  /**
    * @brief FLASH Registers
    */
  typedef struct
  {
    __IO uint32_t ACR;           /*!< Access control register,                     Address offset: 0x00 */
    __IO uint32_t PECR;          /*!< Program/erase control register,              Address offset: 0x04 */
    __IO uint32_t PDKEYR;        /*!< Power down key register,                     Address offset: 0x08 */
    __IO uint32_t PEKEYR;        /*!< Program/erase key register,                  Address offset: 0x0c */
    __IO uint32_t PRGKEYR;       /*!< Program memory key register,                 Address offset: 0x10 */
    __IO uint32_t OPTKEYR;       /*!< Option byte key register,                    Address offset: 0x14 */
    __IO uint32_t SR;            /*!< Status register,                             Address offset: 0x18 */
    __IO uint32_t OPTR;          /*!< Option byte register,                        Address offset: 0x1c */
    __IO uint32_t WRPR;          /*!< Write protection register,                   Address offset: 0x20 */
  } FLASH_TypeDef;


  /**
    * @brief Option Bytes Registers
    */
  typedef struct
  {
    __IO uint32_t RDP;               /*!< Read protection register,               Address offset: 0x00 */
    __IO uint32_t USER;              /*!< user register,                          Address offset: 0x04 */
    __IO uint32_t WRP01;             /*!< write protection Bytes 0 and 1          Address offset: 0x08 */
  } OB_TypeDef;


  /**
    * @brief General Purpose IO
    */

  typedef struct
  {
    __IO uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00 */
    __IO uint32_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04 */
    __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08 */
    __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C */
    __IO uint32_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10 */
    __IO uint32_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14 */
    __IO uint32_t BSRR;         /*!< GPIO port bit set/reset registerBSRR,        Address offset: 0x18 */
    __IO uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C */
    __IO uint32_t AFR[2];       /*!< GPIO alternate function register,            Address offset: 0x20-0x24 */
    __IO uint32_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28 */
  }GPIO_TypeDef;

  /**
    * @brief LPTIMIMER
    */
  typedef struct
  {
    __IO uint32_t ISR;      /*!< LPTIM Interrupt and Status register,             Address offset: 0x00 */
    __IO uint32_t ICR;      /*!< LPTIM Interrupt Clear register,                  Address offset: 0x04 */
    __IO uint32_t IER;      /*!< LPTIM Interrupt Enable register,                 Address offset: 0x08 */
    __IO uint32_t CFGR;     /*!< LPTIM Configuration register,                    Address offset: 0x0C */
    __IO uint32_t CR;       /*!< LPTIM Control register,                          Address offset: 0x10 */
    __IO uint32_t CMP;      /*!< LPTIM Compare register,                          Address offset: 0x14 */
    __IO uint32_t ARR;      /*!< LPTIM Autoreload register,                       Address offset: 0x18 */
    __IO uint32_t CNT;      /*!< LPTIM Counter register,                          Address offset: 0x1C */
  } LPTIM_TypeDef;

  /**
    * @brief SysTem Configuration
    */

  typedef struct
  {
    __IO uint32_t CFGR1;         /*!< SYSCFG configuration register 1,                    Address offset: 0x00 */
    __IO uint32_t CFGR2;         /*!< SYSCFG configuration register 2,                    Address offset: 0x04 */
    __IO uint32_t EXTICR[4];     /*!< SYSCFG external interrupt configuration register,   Address offset: 0x14-0x08 */
         uint32_t RESERVED[2];   /*!< Reserved,                                           0x18-0x1C */
    __IO uint32_t CFGR3;         /*!< SYSCFG configuration register 3,                    Address offset: 0x20 */
  } SYSCFG_TypeDef;



  /**
    * @brief Inter-integrated Circuit Interface
    */

  typedef struct
  {
    __IO uint32_t CR1;      /*!< I2C Control register 1,            Address offset: 0x00 */
    __IO uint32_t CR2;      /*!< I2C Control register 2,            Address offset: 0x04 */
    __IO uint32_t OAR1;     /*!< I2C Own address 1 register,        Address offset: 0x08 */
    __IO uint32_t OAR2;     /*!< I2C Own address 2 register,        Address offset: 0x0C */
    __IO uint32_t TIMINGR;  /*!< I2C Timing register,               Address offset: 0x10 */
    __IO uint32_t TIMEOUTR; /*!< I2C Timeout register,              Address offset: 0x14 */
    __IO uint32_t ISR;      /*!< I2C Interrupt and status register, Address offset: 0x18 */
    __IO uint32_t ICR;      /*!< I2C Interrupt clear register,      Address offset: 0x1C */
    __IO uint32_t PECR;     /*!< I2C PEC register,                  Address offset: 0x20 */
    __IO uint32_t RXDR;     /*!< I2C Receive data register,         Address offset: 0x24 */
    __IO uint32_t TXDR;     /*!< I2C Transmit data register,        Address offset: 0x28 */
  }I2C_TypeDef;


  /**
    * @brief Independent WATCHDOG
    */
  typedef struct
  {
    __IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
    __IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
    __IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
    __IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
    __IO uint32_t WINR; /*!< IWDG Window register,    Address offset: 0x10 */
  } IWDG_TypeDef;

  /**
    * @brief Power Control
    */
  typedef struct
  {
    __IO uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
    __IO uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
  } PWR_TypeDef;

  /**
    * @brief Reset and Clock Control
    */
  typedef struct
  {
    __IO uint32_t CR;            /*!< RCC clock control register,                                   Address offset: 0x00 */
    __IO uint32_t ICSCR;         /*!< RCC Internal clock sources calibration register,              Address offset: 0x04 */
    __IO uint32_t CRRCR;         /*!< RCC Clock recovery RC register,                               Address offset: 0x08 */
    __IO uint32_t CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x0C */
    __IO uint32_t CIER;          /*!< RCC Clock interrupt enable register,                          Address offset: 0x10 */
    __IO uint32_t CIFR;          /*!< RCC Clock interrupt flag register,                            Address offset: 0x14 */
    __IO uint32_t CICR;          /*!< RCC Clock interrupt clear register,                           Address offset: 0x18 */
    __IO uint32_t IOPRSTR;       /*!< RCC IO port reset register,                                   Address offset: 0x1C */
    __IO uint32_t AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x20 */
    __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x24 */
    __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x28 */
    __IO uint32_t IOPENR;        /*!< RCC Clock IO port enable register,                            Address offset: 0x2C */
    __IO uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x30 */
    __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral enable register,                          Address offset: 0x34 */
    __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral enable register,                          Address offset: 0x38 */
    __IO uint32_t IOPSMENR;      /*!< RCC IO port clock enable in sleep mode register,              Address offset: 0x3C */
    __IO uint32_t AHBSMENR;      /*!< RCC AHB peripheral clock enable in sleep mode register,       Address offset: 0x40 */
    __IO uint32_t APB2SMENR;     /*!< RCC APB2 peripheral clock enable in sleep mode register,      Address offset: 0x44 */
    __IO uint32_t APB1SMENR;     /*!< RCC APB1 peripheral clock enable in sleep mode register,      Address offset: 0x48 */
    __IO uint32_t CCIPR;         /*!< RCC clock configuration register,                             Address offset: 0x4C */
    __IO uint32_t CSR;           /*!< RCC Control/status register,                                  Address offset: 0x50 */
  } RCC_TypeDef;

  /**
    * @brief Real-Time Clock
    */
  typedef struct
  {
    __IO uint32_t TR;         /*!< RTC time register,                                         Address offset: 0x00 */
    __IO uint32_t DR;         /*!< RTC date register,                                         Address offset: 0x04 */
    __IO uint32_t CR;         /*!< RTC control register,                                      Address offset: 0x08 */
    __IO uint32_t ISR;        /*!< RTC initialization and status register,                    Address offset: 0x0C */
    __IO uint32_t PRER;       /*!< RTC prescaler register,                                    Address offset: 0x10 */
    __IO uint32_t WUTR;       /*!< RTC wakeup timer register,                                 Address offset: 0x14 */
         uint32_t RESERVED;   /*!< Reserved,                                                  Address offset: 0x18 */
    __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                      Address offset: 0x1C */
    __IO uint32_t ALRMBR;     /*!< RTC alarm B register,                                      Address offset: 0x20 */
    __IO uint32_t WPR;        /*!< RTC write protection register,                             Address offset: 0x24 */
    __IO uint32_t SSR;        /*!< RTC sub second register,                                   Address offset: 0x28 */
    __IO uint32_t SHIFTR;     /*!< RTC shift control register,                                Address offset: 0x2C */
    __IO uint32_t TSTR;       /*!< RTC time stamp time register,                              Address offset: 0x30 */
    __IO uint32_t TSDR;       /*!< RTC time stamp date register,                              Address offset: 0x34 */
    __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
    __IO uint32_t CALR;       /*!< RTC calibration register,                                  Address offset: 0x3C */
    __IO uint32_t TAMPCR;     /*!< RTC tamper configuration register,                         Address offset: 0x40 */
    __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
    __IO uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
    __IO uint32_t OR;         /*!< RTC option register,                                       Address offset  0x4C */
    __IO uint32_t BKP0R;      /*!< RTC backup register 0,                                     Address offset: 0x50 */
    __IO uint32_t BKP1R;      /*!< RTC backup register 1,                                     Address offset: 0x54 */
    __IO uint32_t BKP2R;      /*!< RTC backup register 2,                                     Address offset: 0x58 */
    __IO uint32_t BKP3R;      /*!< RTC backup register 3,                                     Address offset: 0x5C */
    __IO uint32_t BKP4R;      /*!< RTC backup register 4,                                     Address offset: 0x60 */
  } RTC_TypeDef;


  /**
    * @brief Serial Peripheral Interface
    */
  typedef struct
  {
    __IO uint32_t CR1;      /*!< SPI Control register 1,                              Address offset: 0x00 */
    __IO uint32_t CR2;      /*!< SPI Control register 2,                              Address offset: 0x04 */
    __IO uint32_t SR;       /*!< SPI Status register,                                 Address offset: 0x08 */
    __IO uint32_t DR;       /*!< SPI data register,                                   Address offset: 0x0C */
    __IO uint32_t CRCPR;    /*!< SPI CRC polynomial register,                         Address offset: 0x10 */
    __IO uint32_t RXCRCR;   /*!< SPI Rx CRC register,                                 Address offset: 0x14 */
    __IO uint32_t TXCRCR;   /*!< SPI Tx CRC register,                                 Address offset: 0x18 */
  } SPI_TypeDef;

  /**
    * @brief TIM
    */
  typedef struct
  {
    __IO uint32_t CR1;       /*!< TIM control register 1,                       Address offset: 0x00 */
    __IO uint32_t CR2;       /*!< TIM control register 2,                       Address offset: 0x04 */
    __IO uint32_t SMCR;      /*!< TIM slave Mode Control register,              Address offset: 0x08 */
    __IO uint32_t DIER;      /*!< TIM DMA/interrupt enable register,            Address offset: 0x0C */
    __IO uint32_t SR;        /*!< TIM status register,                          Address offset: 0x10 */
    __IO uint32_t EGR;       /*!< TIM event generation register,                Address offset: 0x14 */
    __IO uint32_t CCMR1;     /*!< TIM  capture/compare mode register 1,         Address offset: 0x18 */
    __IO uint32_t CCMR2;     /*!< TIM  capture/compare mode register 2,         Address offset: 0x1C */
    __IO uint32_t CCER;      /*!< TIM capture/compare enable register,          Address offset: 0x20 */
    __IO uint32_t CNT;       /*!< TIM counter register,                         Address offset: 0x24 */
    __IO uint32_t PSC;       /*!< TIM prescaler register,                       Address offset: 0x28 */
    __IO uint32_t ARR;       /*!< TIM auto-reload register,                     Address offset: 0x2C */
    uint32_t      RESERVED12;/*!< Reserved                                      Address offset: 0x30 */
    __IO uint32_t CCR1;      /*!< TIM capture/compare register 1,               Address offset: 0x34 */
    __IO uint32_t CCR2;      /*!< TIM capture/compare register 2,               Address offset: 0x38 */
    __IO uint32_t CCR3;      /*!< TIM capture/compare register 3,               Address offset: 0x3C */
    __IO uint32_t CCR4;      /*!< TIM capture/compare register 4,               Address offset: 0x40 */
    uint32_t      RESERVED17;/*!< Reserved,                                     Address offset: 0x44 */
    __IO uint32_t DCR;       /*!< TIM DMA control register,                     Address offset: 0x48 */
    __IO uint32_t DMAR;      /*!< TIM DMA address for full transfer register,   Address offset: 0x4C */
    __IO uint32_t OR;        /*!< TIM option register,                          Address offset: 0x50 */
  } TIM_TypeDef;

  /**
    * @brief Universal Synchronous Asynchronous Receiver Transmitter
    */
  typedef struct
  {
    __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
    __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
    __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
    __IO uint32_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
    __IO uint32_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
    __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
    __IO uint32_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
    __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
    __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
    __IO uint32_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
    __IO uint32_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
  } USART_TypeDef;

  /**
    * @brief Window WATCHDOG
    */
  typedef struct
  {
    __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
    __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
    __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
  } WWDG_TypeDef;

#endif


//--------------------------------------------------------------------------------------------------
#if defined __USE_RAM_VEC_TABLE__

   IrqHandlerFunc __attribute__ ((externally_visible,section(".ram_vec_table")))
   ram_vec_table [ sizeof(flash_vec_table) / sizeof(IrqHandlerFunc)] ;

   void vec_table_copy2ram(unsigned map_needed )
     {
        for (uint32_t vec_index = 0 ; vec_index <  sizeof(flash_vec_table) / sizeof(IrqHandlerFunc) ; vec_index++ )
        ram_vec_table[vec_index] = flash_vec_table[vec_index] ;

        if ( map_needed )
        vec_map2ram (0) ;
     }
   //---------------------------------------------------------------------
   void vec_set (  VectorType vec_type  , void* handler )
     {
        ram_vec_table[vec_type] =  (IrqHandlerFunc)handler ;
     }

   void vec_map2ram ( unsigned* vec_table )
     {
       // TODO
       NVIC_SetVectorTable(NVIC_VectTab_RAM, (unsigned)(vec_table - SRAM_BASE) ) ;
     }
   //-------------------------------------------------------------------
   inline void vec_map2flash ( unsigned* vec_table )
     {
       // TODO
       NVIC_SetVectorTable(NVIC_VectTab_FLASH, (unsigned)(vec_table - FLASH_BASE) ) ;
     }
//-------------------------------------------------------------------

#endif //__USE_RAM_VEC_TABLE__





inline __attribute__((always_inline)) void system_init(const uint32_t vec_tab_offset, const rcc_t::system_init_profile_t& system_init_profile)
{
                  /*!< Set MSION bit */
    rcc.msi_on(); //RCC->CR |= (uint32_t)0x00000100U;

    /*!< Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0] and MCOPRE[2:0] bits */
    //RCC->CFGR &= (uint32_t) 0x88FF400CU;
    rcc.sys_clock_msi();
    rcc.msi_ready_wait();
    rcc.ahb_prescaler_no_div();
    rcc.apb2_prescaler_no_div();
    rcc.apb1_prescaler_no_div();
    rcc.mco_clock_output_no_source();
    rcc.mco_clock_prescaler_no_div();

                          /*!< Reset HSION, HSIDIVEN, HSEON, CSSON and PLLON bits */
                          //RCC->CR &= (uint32_t)0xFEF6FFF6U;
    rcc.hsi_off();
    rcc.hsi_div4_disable();
    rcc.hse_off();
    rcc.hse_clock_bypass_off();
    rcc.clock_security_system_disable();
    rcc.pll_off();

    /*!< Reset HSI48ON  bit */
    //RCC->CRRCR &= (uint32_t)0xFFFFFFFEU;

                                /*!< Reset PLLSRC, PLLMUL[3:0] and PLLDIV[1:0] bits */
    rcc.pll_source_hsi();       //RCC->CFGR &= (uint32_t)0xFF02FFFFU;
    rcc.pll_mul3();
    rcc.pll_div2();

                                    /*!< Disable all interrupts */
    rcc.clock_interrupt_state.write(0) ; //RCC->CIER = 0x00000000U;

    /* Configure the Vector Table location add offset address ------------------*/
    scb.vector_table_offset(vec_tab_offset);

    pwr.clock_enable();
    pwr.regulator_voltage_scaling_range_1();
    pwr.voltage_scaling_select_ready_wait();

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
        system_init((uint32_t)gnu_linker_vec_start(),system_init_profile);

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


} // stm32l0

using namespace stm32l0 ;

#endif /* __STM32++_H__ */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
