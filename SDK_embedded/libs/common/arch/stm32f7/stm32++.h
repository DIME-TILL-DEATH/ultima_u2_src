#ifndef __STM32++_H__
#define __STM32++_H__

#include "gnu_linker.h"  // необходим для crt_init()
#include "supc++.h" // для std::__throw_invalid_argument

#include "arch/cortex-m/cortex_m7++.h"

namespace stm32f7
{

  constexpr uint32_t  ram_itcm_addr =        0x00000000; /*!< Base address of : 16KB RAM reserved for CPU execution/instruction accessible over ITCM  */
  constexpr uint32_t  flash_itcm_addr =      0x00200000; /*!< Base address of : (up to 2 MB) embedded FLASH memory  accessible over ITCM              */
  constexpr uint32_t  flash_axi_addr =       0x08000000; /*!< Base address of : (up to 2 MB) embedded FLASH memory accessible over AXI                */
  constexpr uint32_t  flash_axi_end_addr  =  0x081FFFFF; /*!< FLASH end address */
  constexpr uint32_t  ram_dtcm_addr =        0x20000000; /*!< Base address of : 128KB system data RAM accessible over DTCM                            */
  constexpr uint32_t  periph_addr =          0x40000000; /*!< Base address of : AHB/ABP Peripherals                                                   */
  constexpr uint32_t  bkp_sram_addr =        0x40024000; /*!< Base address of : Backup SRAM(4 KB)                                                     */
  constexpr uint32_t  qspi_axi_addr =        0x90000000; /*!< Base address of : QSPI memories  accessible over AXI                                    */
  constexpr uint32_t  fmc_addr =             0xA0000000; /*!< Base address of : FMC Control registers                                                 */
  constexpr uint32_t  qspi_addr =            0xA0001000; /*!< Base address of : QSPI Control  registers                                               */
  constexpr uint32_t  sram1_addr  =          0x20020000; /*!< Base address of : 368KB RAM1 accessible over AXI/AHB                                    */
  constexpr uint32_t  sram2_addr =           0x2007C000; /*!< Base address of : 16KB RAM2 accessible over AXI/AHB                                     */
  constexpr uint32_t  flash_otp_addr =       0x1FF0F000; /*!< Base address of : (up to 1024 Bytes) embedded FLASH OTP Area                            */
  constexpr uint32_t  flash_otp_end_addr =   0x1FF0F41F; /*!< End address of : (up to 1024 Bytes) embedded FLASH OTP Area*/


  /*!< Peripheral memory map */
  constexpr uint32_t  apb1_periph_addr =      periph_addr;
  constexpr uint32_t  apb2_periph_addr =     (periph_addr + 0x00010000U);
  constexpr uint32_t  ahb1_periph_addr =     (periph_addr + 0x00020000U);
  constexpr uint32_t  ahb2_periph_addr =     (periph_addr + 0x10000000U);

  /*!< APB1 periph_addrerals */
  constexpr uint32_t  tim2_addr =           (apb1_periph_addr + 0x0000U);
  constexpr uint32_t  tim3_addr =           (apb1_periph_addr + 0x0400U);
  constexpr uint32_t  tim4_addr =           (apb1_periph_addr + 0x0800U);
  constexpr uint32_t  tim5_addr =           (apb1_periph_addr + 0x0C00U);
  constexpr uint32_t  tim6_addr =           (apb1_periph_addr + 0x1000U);
  constexpr uint32_t  tim7_addr =           (apb1_periph_addr + 0x1400U);
  constexpr uint32_t  tim12_addr =          (apb1_periph_addr + 0x1800U);
  constexpr uint32_t  tim13_addr =          (apb1_periph_addr + 0x1C00U);
  constexpr uint32_t  tim14_addr =          (apb1_periph_addr + 0x2000U);
  constexpr uint32_t  lp_tim1_addr =         (apb1_periph_addr + 0x2400U);
  constexpr uint32_t  rtc_addr =            (apb1_periph_addr + 0x2800U);
  constexpr uint32_t  wwdg_addr =           (apb1_periph_addr + 0x2C00U);
  constexpr uint32_t  iwdg_addr =           (apb1_periph_addr + 0x3000U);
  constexpr uint32_t  can3_addr =           (apb1_periph_addr + 0x3400U);
  constexpr uint32_t  spi2_addr =           (apb1_periph_addr + 0x3800U);
  constexpr uint32_t  spi3_addr =           (apb1_periph_addr + 0x3C00U);
  constexpr uint32_t  spdif_rx_addr =        (apb1_periph_addr + 0x4000U);
  constexpr uint32_t  usart2_addr =         (apb1_periph_addr + 0x4400U);
  constexpr uint32_t  usart3_addr =         (apb1_periph_addr + 0x4800U);
  constexpr uint32_t  uart4_addr =          (apb1_periph_addr + 0x4C00U);
  constexpr uint32_t  uart5_addr =          (apb1_periph_addr + 0x5000U);
  constexpr uint32_t  i2c1_addr =           (apb1_periph_addr + 0x5400U);
  constexpr uint32_t  i2c2_addr =           (apb1_periph_addr + 0x5800U);
  constexpr uint32_t  i2c3_addr =           (apb1_periph_addr + 0x5C00U);
  constexpr uint32_t  i2c4_addr =           (apb1_periph_addr + 0x6000U);
  constexpr uint32_t  can1_addr =           (apb1_periph_addr + 0x6400U);
  constexpr uint32_t  can2_addr =           (apb1_periph_addr + 0x6800U);
  constexpr uint32_t  cec_addr =            (apb1_periph_addr + 0x6C00U);
  constexpr uint32_t  pwr_addr =            (apb1_periph_addr + 0x7000U);
  constexpr uint32_t  dac_addr =            (apb1_periph_addr + 0x7400U);
  constexpr uint32_t  uart7_addr =          (apb1_periph_addr + 0x7800U);
  constexpr uint32_t  uart8_addr =          (apb1_periph_addr + 0x7C00U);

  /*!< APB2 periph_addrerals */
  constexpr uint32_t  tim1_addr =           (apb2_periph_addr + 0x0000U);
  constexpr uint32_t  tim8_addr =           (apb2_periph_addr + 0x0400U);
  constexpr uint32_t  usart1_addr =         (apb2_periph_addr + 0x1000U);
  constexpr uint32_t  usart6_addr =         (apb2_periph_addr + 0x1400U);
  constexpr uint32_t  sdmmc2_addr =         (apb2_periph_addr + 0x1C00U);

  //constexpr uint32_t  adc1_addr =           (apb2_periph_addr + 0x2000U);
  //constexpr uint32_t  adc2_addr =           (apb2_periph_addr + 0x2100U);
  //constexpr uint32_t  adc3_addr =           (apb2_periph_addr + 0x2200U);
  //constexpr uint32_t  adc_addr =            (apb2_periph_addr + 0x2300U);
  constexpr uint32_t adc_addr =             (apb2_periph_addr + 0x2000U);
  constexpr uint32_t adc_converter_size = 0x100;

  constexpr uint32_t  sdmmc1_addr =         (apb2_periph_addr + 0x2C00U);
  constexpr uint32_t  spi1_addr =           (apb2_periph_addr + 0x3000U);
  constexpr uint32_t  spi4_addr =           (apb2_periph_addr + 0x3400U);
  constexpr uint32_t  syscfg_addr =         (apb2_periph_addr + 0x3800U);
  constexpr uint32_t  exti_addr =           (apb2_periph_addr + 0x3C00U);
  constexpr uint32_t  tim9_addr =           (apb2_periph_addr + 0x4000U);
  constexpr uint32_t  tim10_addr =          (apb2_periph_addr + 0x4400U);
  constexpr uint32_t  tim11_addr =          (apb2_periph_addr + 0x4800U);
  constexpr uint32_t  spi5_addr =           (apb2_periph_addr + 0x5000U);
  constexpr uint32_t  spi6_addr =           (apb2_periph_addr + 0x5400U);
  constexpr uint32_t  sai1_addr =           (apb2_periph_addr + 0x5800U);
  constexpr uint32_t  sai2_addr =           (apb2_periph_addr + 0x5C00U);
  constexpr uint32_t  ltdc_addr =           (apb2_periph_addr + 0x6800U);
  constexpr uint32_t  ltdc_layer1_addr =    (ltdc_addr + 0x84U);
  constexpr uint32_t  ltdc_layer2_addr =    (ltdc_addr + 0x104U);
  constexpr uint32_t  dfsdm1_addr =         (apb2_periph_addr + 0x7400U);
  constexpr uint32_t  dfsdm1_channel0_addr  (dfsdm1_addr + 0x00U);
  constexpr uint32_t  dfsdm1_channel1_addr  (dfsdm1_addr + 0x20U);
  constexpr uint32_t  dfsdm1_channel2_addr  (dfsdm1_addr + 0x40U);
  constexpr uint32_t  dfsdm1_channel3_addr  (dfsdm1_addr + 0x60U);
  constexpr uint32_t  dfsdm1_channel4_addr  (dfsdm1_addr + 0x80U);
  constexpr uint32_t  dfsdm1_channel5_addr  (dfsdm1_addr + 0xA0U);
  constexpr uint32_t  dfsdm1_channel6_addr  (dfsdm1_addr + 0xC0U);
  constexpr uint32_t  dfsdm1_channel7_addr  (dfsdm1_addr + 0xE0U);
  constexpr uint32_t  dfsdm1_filter0_addr   (dfsdm1_addr + 0x100U);
  constexpr uint32_t  dfsdm1_fFilter1_addr   (dfsdm1_addr + 0x180U);
  constexpr uint32_t  dfsdm1_filter2_addr   (dfsdm1_addr + 0x200U);
  constexpr uint32_t  dfsdm1_filter3_addr   (dfsdm1_addr + 0x280U);
  constexpr uint32_t  mdios_addr =          (apb2_periph_addr + 0x7800U);
  /*!< AHB1 periph_addrerals */
  constexpr uint32_t  gpioa_addr =          (ahb1_periph_addr + 0x0000U);
  constexpr uint32_t  gpiob_addr =          (ahb1_periph_addr + 0x0400U);
  constexpr uint32_t  gpioc_addr =          (ahb1_periph_addr + 0x0800U);
  constexpr uint32_t  gpiod_addr =          (ahb1_periph_addr + 0x0C00U);
  constexpr uint32_t  gpioe_addr =          (ahb1_periph_addr + 0x1000U);
  constexpr uint32_t  gpiof_addr =          (ahb1_periph_addr + 0x1400U);
  constexpr uint32_t  gpiog_addr =          (ahb1_periph_addr + 0x1800U);
  constexpr uint32_t  gpioh_addr =          (ahb1_periph_addr + 0x1C00U);
  constexpr uint32_t  gpioi_addr =          (ahb1_periph_addr + 0x2000U);
  constexpr uint32_t  gpioj_addr =          (ahb1_periph_addr + 0x2400U);
  constexpr uint32_t  gpiok_addr =          (ahb1_periph_addr + 0x2800U);
  constexpr uint32_t  crc_addr =            (ahb1_periph_addr + 0x3000U);
  constexpr uint32_t  rcc_addr =            (ahb1_periph_addr + 0x3800U);
  constexpr uint32_t  flash_addr =          (ahb1_periph_addr + 0x3C00U);
  constexpr uint32_t  devsign_addr =        0x1FF0F420U;                  /*!< Unique device ID register base address */
  constexpr uint32_t  flash_size_addr =     0x1FF0F442U;                 /*!< FLASH Size register base address */
  constexpr uint32_t  package_addr =        0x1FFF7BF0U;                   /*!< Package size register base address */

  constexpr uint32_t  dma1_addr =           (ahb1_periph_addr + 0x6000U);
  constexpr uint32_t  dma1_stream0_addr =   (dma1_addr + 0x010U);
  constexpr uint32_t  dma1_stream1_addr =   (dma1_addr + 0x028U);
  constexpr uint32_t  dma1_stream2_addr =   (dma1_addr + 0x040U);
  constexpr uint32_t  dma1_stream3_addr =   (dma1_addr + 0x058U);
  constexpr uint32_t  dma1_stream4_addr =   (dma1_addr + 0x070U);
  constexpr uint32_t  dma1_stream5_addr =   (dma1_addr + 0x088U);
  constexpr uint32_t  dma1_stream6_addr =   (dma1_addr + 0x0A0U);
  constexpr uint32_t  dma1_stream7_addr =   (dma1_addr + 0x0B8U);
  constexpr uint32_t  dma2_addr =           (ahb1_periph_addr + 0x6400U);
  constexpr uint32_t  dma2_stream0_addr =   (dma2_addr + 0x010U);
  constexpr uint32_t  dma2_stream1_addr =   (dma2_addr + 0x028U);
  constexpr uint32_t  dma2_stream2_addr =   (dma2_addr + 0x040U);
  constexpr uint32_t  dma2_stream3_addr =   (dma2_addr + 0x058U);
  constexpr uint32_t  dma2_stream4_addr =   (dma2_addr + 0x070U);
  constexpr uint32_t  dma2_stream5_addr =   (dma2_addr + 0x088U);
  constexpr uint32_t  dma2_stream6_addr =   (dma2_addr + 0x0A0U);
  constexpr uint32_t  dma2_stream7_addr =   (dma2_addr + 0x0B8U);
  constexpr uint32_t  eth_addr =         (ahb1_periph_addr + 0x8000U);
  constexpr uint32_t  dma2d_addr =          (ahb1_periph_addr + 0xB000U);
  /*!< AHB2 peripherals */
  constexpr uint32_t  dcmi_addr =           (ahb2_periph_addr + 0x50000U);
  constexpr uint32_t  jpeg_addr =         (ahb2_periph_addr + 0x51000U);
  constexpr uint32_t  rng_addr =            (ahb2_periph_addr + 0x60800U);

  /* Debug MCU registers base address */
  constexpr uint32_t  dbgmcu_addr =         0xE0042000;

  /*!< USB registers base address */
  constexpr uint32_t  usb_otg_hs_periph_addr =             0x40040000U;
  constexpr uint32_t  usb_otg_fs_periph_addr =             0x50000000U;

  constexpr uint32_t  usb_otg_global_addr =                0x000U;
  constexpr uint32_t  usb_otg_device_addr =                0x800U;
  constexpr uint32_t  usb_otg_in_endpoint_addr =           0x900U;
  constexpr uint32_t  usb_otg_out_endpoint_addr =          0xB00U;
  constexpr uint32_t  usb_otg_ep_reg_size =                0x20U;
  constexpr uint32_t  usb_otg_host_addr =                  0x400U;
  constexpr uint32_t  usb_otg_host_port_addr =             0x440U;
  constexpr uint32_t  usb_otg_host_channel_addr =          0x500U;
  constexpr uint32_t  usb_otg_host_channel_size =          0x20U;
  constexpr uint32_t  usb_otg_pcgcctl_addr =               0xE00U;
  constexpr uint32_t  usb_otg_fifo_addr =                  0x1000U;
  constexpr uint32_t  usb_otg_fifo_size =                  0x1000U;



struct nvic_t : public core_nvic_t
{
 // TODO придумать как красиво развести по подтипам микросхем
 // в данный момент только для STM32F76x and STM32F77x
  enum class irq_num_t : int16_t
   {
     thread =           -16,
     reset =            -15,
     non_maskable_int = -14,
     hard_fault =       -13,
     memory_management =-12,
     bus_fault =        -11,
     usage_fault =      -10,
     svc =              -5,
     debug_monitor =    -4,
     pend_svc =         -2,
     sys_tick =         -1,
    //http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Babefdjc.html
    // stm32 specific interrupt numbers
        wwdg = 0 ,
        pvd,
        tamp_stamp,
        rtc_wkup,
        flash,
        rcc,
        exti0,
        exti1,
        exti2,
        exti3,
        exti4,
        dma1_stream0,
        dma1_stream1,
        dma1_stream2,
        dma1_stream3,
        dma1_stream4,
        dma1_stream5,
        dma1_stream6,
        adc,
        can1_tx,
        can1_rx0,
        can1_rx1,
        can1_sce,
        exti9_5,
        tim1_brk_tim9,
        tim1_up_tim10,
        tim1_trg_com_tim11,
        tim1_cc,
        tim2,
        tim3,
        tim4,
        i2c1_ev,
        i2c1_er,
        i2c2_ev,
        i2c2_er,
        spi1,
        spi2,
        usart1,
        usart2,
        usart3,
        exti15_10,
        rtc_alarm,
        otg_fs_wkup,
        tim8_brk_tim12,
        tim8_up_tim13,
        tim8_trg_com_tim14,
        tim8_cc,
        dma1_stream7,
        fmc,
        sdmmc1,
        tim5,
        spi3,
        uart4,
        uart5,
        tim6_dac,
        tim7,
        dma2_stream0,
        dma2_stream1,
        dma2_stream2,
        dma2_stream3,
        dma2_stream4,
        eth,
        eth_wkup,
        can2_tx,
        can2_rx0,
        can2_rx1,
        can2_sce,
        otg_fs,
        dma2_stream5,
        dma2_stream6,
        dma2_stream7,
        usart6,
        i2c3_ev,
        i2c3_er,
        otg_hs_ep1_out,
        otg_hs_ep1_in,
        otg_hs_wkup,
        otg_hs,
        dcmi,
        crypt,
        hash_rng,
        fpu,
        uart7,
        uart8,
        spi4,
        spi5,
        spi6,
        sai1,
        ltdc,
        ltdc_er,
        dma2d,
        sai2,
        qspi,
        lptim1,
        hdmi_cec,
        i2c4_ev,
        i2c4_er,
        spdif_rx,
        dsi_host,
        dfsdm1_flt0,
        dfsdm1_flt1,
        dfsdm1_flt2,
        dfsdm1_flt3,
        sdmmc2,
        can3_tx,
        can3_rx0,
        can3_rx1,
        can3_cse,
        jpeg,
        mdio
  }  ;

  struct state_t { enum enum_t{ disable=0 , enable };};
  struct pending_t { enum enum_t{ not_pending=0 , pending };};
  struct active_t { enum enum_t{ not_active=0 , active };};

  inline void enable( const irq_num_t irq ) {NRO set_enable_vec[(int16_t)irq/32] = 1 << ((int16_t)irq%32); }
  inline void disable( const irq_num_t irq ){NRO clear_enable_vec[(int16_t)irq/32] = 1<<((int16_t)irq%32); }
  inline auto state( const irq_num_t irq ) const {NRO return (state_t::enum_t)(set_enable_vec[(int16_t)irq/32] & 1<<((int16_t)irq%32)); }
  inline void pending_set( const irq_num_t irq ) {NRO set_pending_vec[(int16_t)irq/32] = 1 << ((int16_t)irq%32); }
  inline void pending_clear( const irq_num_t irq ) {NRO clear_pending_vec[(int16_t)irq/32] = 1<<((int16_t)irq%32); }
  inline auto pending( const irq_num_t irq ) const {NRO return (pending_t::enum_t)(set_pending_vec[(int16_t)irq/32] & 1<<((int16_t)irq%32)); }
  inline auto active( const irq_num_t irq ) const {NRO return (active_t::enum_t)(active_vec[(int16_t)irq/32] & 1<<((int16_t)irq%32)); }
  inline void priority( const irq_num_t irq, const uint8_t priority ) { NRO priority_vec[(int16_t)irq] = priority ; }
  inline uint8_t priority( const irq_num_t irq) const { NRO return priority_vec[(int16_t)irq] ; }
  inline void set_software_trigger( const irq_num_t val ) { core_nvic_t::set_software_trigger( (uint8_t)val ) ; }

  MAKE_NVIC_IRQ_ITEM(wwdg)
  MAKE_NVIC_IRQ_ITEM(pvd)
  MAKE_NVIC_IRQ_ITEM(tamp_stamp)
  MAKE_NVIC_IRQ_ITEM(rtc_wkup)
  MAKE_NVIC_IRQ_ITEM(flash)
  MAKE_NVIC_IRQ_ITEM(rcc)
  MAKE_NVIC_IRQ_ITEM(exti0)
  MAKE_NVIC_IRQ_ITEM(exti1)
  MAKE_NVIC_IRQ_ITEM(exti2)
  MAKE_NVIC_IRQ_ITEM(exti3)
  MAKE_NVIC_IRQ_ITEM(exti4)
  MAKE_NVIC_IRQ_ITEM(dma1_stream0)
  MAKE_NVIC_IRQ_ITEM(dma1_stream1)
  MAKE_NVIC_IRQ_ITEM(dma1_stream2)
  MAKE_NVIC_IRQ_ITEM(dma1_stream3)
  MAKE_NVIC_IRQ_ITEM(dma1_stream4)
  MAKE_NVIC_IRQ_ITEM(dma1_stream5)
  MAKE_NVIC_IRQ_ITEM(dma1_stream6)
  MAKE_NVIC_IRQ_ITEM(adc)
  MAKE_NVIC_IRQ_ITEM(can1_tx)
  MAKE_NVIC_IRQ_ITEM(can1_rx0)
  MAKE_NVIC_IRQ_ITEM(can1_rx1)
  MAKE_NVIC_IRQ_ITEM(can1_sce)
  MAKE_NVIC_IRQ_ITEM(exti9_5)
  MAKE_NVIC_IRQ_ITEM(tim1_brk_tim9)
  MAKE_NVIC_IRQ_ITEM(tim1_up_tim10)
  MAKE_NVIC_IRQ_ITEM(tim1_trg_com_tim11)
  MAKE_NVIC_IRQ_ITEM(tim1_cc)
  MAKE_NVIC_IRQ_ITEM(tim2)
  MAKE_NVIC_IRQ_ITEM(tim3)
  MAKE_NVIC_IRQ_ITEM(tim4)
  MAKE_NVIC_IRQ_ITEM(i2c1_ev)
  MAKE_NVIC_IRQ_ITEM(i2c1_er)
  MAKE_NVIC_IRQ_ITEM(i2c2_ev)
  MAKE_NVIC_IRQ_ITEM(i2c2_er)
  MAKE_NVIC_IRQ_ITEM(spi1)
  MAKE_NVIC_IRQ_ITEM(spi2)
  MAKE_NVIC_IRQ_ITEM(usart1)
  MAKE_NVIC_IRQ_ITEM(usart2)
  MAKE_NVIC_IRQ_ITEM(usart3)
  MAKE_NVIC_IRQ_ITEM(exti15_10)
  MAKE_NVIC_IRQ_ITEM(rtc_alarm)
  MAKE_NVIC_IRQ_ITEM(otg_fs_wkup)
  MAKE_NVIC_IRQ_ITEM(tim8_brk_tim12)
  MAKE_NVIC_IRQ_ITEM(tim8_up_tim13)
  MAKE_NVIC_IRQ_ITEM(tim8_trg_com_tim14)
  MAKE_NVIC_IRQ_ITEM(tim8_cc)
  MAKE_NVIC_IRQ_ITEM(dma1_stream7)
  MAKE_NVIC_IRQ_ITEM(fmc)
  MAKE_NVIC_IRQ_ITEM(sdmmc1)
  MAKE_NVIC_IRQ_ITEM(tim5)
  MAKE_NVIC_IRQ_ITEM(spi3)
  MAKE_NVIC_IRQ_ITEM(uart4)
  MAKE_NVIC_IRQ_ITEM(uart5)
  MAKE_NVIC_IRQ_ITEM(tim6_dac)
  MAKE_NVIC_IRQ_ITEM(tim7)
  MAKE_NVIC_IRQ_ITEM(dma2_stream0)
  MAKE_NVIC_IRQ_ITEM(dma2_stream1)
  MAKE_NVIC_IRQ_ITEM(dma2_stream2)
  MAKE_NVIC_IRQ_ITEM(dma2_stream3)
  MAKE_NVIC_IRQ_ITEM(dma2_stream4)
  MAKE_NVIC_IRQ_ITEM(eth)
  MAKE_NVIC_IRQ_ITEM(eth_wkup)
  MAKE_NVIC_IRQ_ITEM(can2_tx)
  MAKE_NVIC_IRQ_ITEM(can2_rx0)
  MAKE_NVIC_IRQ_ITEM(can2_rx1)
  MAKE_NVIC_IRQ_ITEM(can2_sce)
  MAKE_NVIC_IRQ_ITEM(otg_fs)
  MAKE_NVIC_IRQ_ITEM(dma2_stream5)
  MAKE_NVIC_IRQ_ITEM(dma2_stream6)
  MAKE_NVIC_IRQ_ITEM(dma2_stream7)
  MAKE_NVIC_IRQ_ITEM(usart6)
  MAKE_NVIC_IRQ_ITEM(i2c3_ev)
  MAKE_NVIC_IRQ_ITEM(i2c3_er)
  MAKE_NVIC_IRQ_ITEM(otg_hs_ep1_out)
  MAKE_NVIC_IRQ_ITEM(otg_hs_ep1_in)
  MAKE_NVIC_IRQ_ITEM(otg_hs_wkup)
  MAKE_NVIC_IRQ_ITEM(otg_hs)
  MAKE_NVIC_IRQ_ITEM(dcmi)
  MAKE_NVIC_IRQ_ITEM(crypt)
  MAKE_NVIC_IRQ_ITEM(hash_rng)
  MAKE_NVIC_IRQ_ITEM(fpu)
  MAKE_NVIC_IRQ_ITEM(uart7)
  MAKE_NVIC_IRQ_ITEM(uart8)
  MAKE_NVIC_IRQ_ITEM(spi4)
  MAKE_NVIC_IRQ_ITEM(spi5)
  MAKE_NVIC_IRQ_ITEM(spi6)
  MAKE_NVIC_IRQ_ITEM(sai1)
  MAKE_NVIC_IRQ_ITEM(ltdc)
  MAKE_NVIC_IRQ_ITEM(ltdc_er)
  MAKE_NVIC_IRQ_ITEM(dma2d)
  MAKE_NVIC_IRQ_ITEM(sai2)
  MAKE_NVIC_IRQ_ITEM(qspi)
  MAKE_NVIC_IRQ_ITEM(lptim1)
  MAKE_NVIC_IRQ_ITEM(hdmi_cec)
  MAKE_NVIC_IRQ_ITEM(i2c4_ev)
  MAKE_NVIC_IRQ_ITEM(i2c4_er)
  MAKE_NVIC_IRQ_ITEM(spdif_rx)
  MAKE_NVIC_IRQ_ITEM(dsi_host)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt0)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt1)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt2)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt3)
  MAKE_NVIC_IRQ_ITEM(sdmmc2)
  MAKE_NVIC_IRQ_ITEM(can3_tx)
  MAKE_NVIC_IRQ_ITEM(can3_rx0)
  MAKE_NVIC_IRQ_ITEM(can3_rx1)
  MAKE_NVIC_IRQ_ITEM(can3_cse)
  MAKE_NVIC_IRQ_ITEM(jpeg)
  MAKE_NVIC_IRQ_ITEM(mdio)

};

static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало c уровня ниже(cm7_core) для биндинга в stm32f7::nvic_t
}


#include "rcc++.h"

#include "adc++.h"
#include "dac++.h"
#include "gpio++.h"
#include "devsign++.h"
#include "dma_f4_f7++.h"
#include "dma_stream++.h"
#include "exti++.h"
#include "flash++.h"
#include "fmc++.h"
#include "iwdg++.h"
#include "pwr++.h"
#include "rng++.h"
#include "sai++.h"
#include "syscfg++.h"
#include "tim++.h"
#include "eth_f4_f7++.h"
#include "dbgmcu++.h"
#include "spi++.h"
#include "qspi_f4_f7++.h"
#include "dcmi_f4_f7++.h"
//#include "usart++.h"
#include "uart++.h"

namespace stm32f7
{

  extern const rcc_t::system_init_profile_t& system_init_profile ;

#if 0


typedef struct
{
  __IO uint32_t SR;     /*!< ADC status register,                         Address offset: 0x00 */
  __IO uint32_t CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
  __IO uint32_t CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
  __IO uint32_t SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
  __IO uint32_t SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
  __IO uint32_t JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
  __IO uint32_t JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
  __IO uint32_t JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
  __IO uint32_t JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
  __IO uint32_t HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
  __IO uint32_t LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
  __IO uint32_t SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
  __IO uint32_t SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
  __IO uint32_t SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
  __IO uint32_t JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
  __IO uint32_t JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
  __IO uint32_t JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
  __IO uint32_t JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
  __IO uint32_t JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
  __IO uint32_t DR;     /*!< ADC regular data register,                   Address offset: 0x4C */
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;    /*!< ADC Common status register,                  Address offset: ADC1 base address + 0x300 */
  __IO uint32_t CCR;    /*!< ADC common control register,                 Address offset: ADC1 base address + 0x304 */
  __IO uint32_t CDR;    /*!< ADC common regular data register for dual
                             AND triple modes,                            Address offset: ADC1 base address + 0x308 */
} ADC_Common_TypeDef;




/**
  * @brief CRC calculation unit
  */

typedef struct
{
  __IO uint32_t DR;         /*!< CRC Data register,             Address offset: 0x00 */
  __IO uint8_t  IDR;        /*!< CRC Independent data register, Address offset: 0x04 */
  uint8_t       RESERVED0;  /*!< Reserved, 0x05                                      */
  uint16_t      RESERVED1;  /*!< Reserved, 0x06                                      */
  __IO uint32_t CR;         /*!< CRC Control register,          Address offset: 0x08 */
} CRC_TypeDef;




/**
  * @brief DMA2D Controller
  */

typedef struct
{
  __IO uint32_t CR;            /*!< DMA2D Control Register,                         Address offset: 0x00 */
  __IO uint32_t ISR;           /*!< DMA2D Interrupt Status Register,                Address offset: 0x04 */
  __IO uint32_t IFCR;          /*!< DMA2D Interrupt Flag Clear Register,            Address offset: 0x08 */
  __IO uint32_t FGMAR;         /*!< DMA2D Foreground Memory Address Register,       Address offset: 0x0C */
  __IO uint32_t FGOR;          /*!< DMA2D Foreground Offset Register,               Address offset: 0x10 */
  __IO uint32_t BGMAR;         /*!< DMA2D Background Memory Address Register,       Address offset: 0x14 */
  __IO uint32_t BGOR;          /*!< DMA2D Background Offset Register,               Address offset: 0x18 */
  __IO uint32_t FGPFCCR;       /*!< DMA2D Foreground PFC Control Register,          Address offset: 0x1C */
  __IO uint32_t FGCOLR;        /*!< DMA2D Foreground Color Register,                Address offset: 0x20 */
  __IO uint32_t BGPFCCR;       /*!< DMA2D Background PFC Control Register,          Address offset: 0x24 */
  __IO uint32_t BGCOLR;        /*!< DMA2D Background Color Register,                Address offset: 0x28 */
  __IO uint32_t FGCMAR;        /*!< DMA2D Foreground CLUT Memory Address Register,  Address offset: 0x2C */
  __IO uint32_t BGCMAR;        /*!< DMA2D Background CLUT Memory Address Register,  Address offset: 0x30 */
  __IO uint32_t OPFCCR;        /*!< DMA2D Output PFC Control Register,              Address offset: 0x34 */
  __IO uint32_t OCOLR;         /*!< DMA2D Output Color Register,                    Address offset: 0x38 */
  __IO uint32_t OMAR;          /*!< DMA2D Output Memory Address Register,           Address offset: 0x3C */
  __IO uint32_t OOR;           /*!< DMA2D Output Offset Register,                   Address offset: 0x40 */
  __IO uint32_t NLR;           /*!< DMA2D Number of Line Register,                  Address offset: 0x44 */
  __IO uint32_t LWR;           /*!< DMA2D Line Watermark Register,                  Address offset: 0x48 */
  __IO uint32_t AMTCR;         /*!< DMA2D AHB Master Timer Configuration Register,  Address offset: 0x4C */
  uint32_t      RESERVED[236]; /*!< Reserved, 0x50-0x3FF */
  __IO uint32_t FGCLUT[256];   /*!< DMA2D Foreground CLUT,                          Address offset:400-7FF */
  __IO uint32_t BGCLUT[256];   /*!< DMA2D Background CLUT,                          Address offset:800-BFF */
} DMA2D_TypeDef;

/**
  * @brief DSI Controller
  */

typedef struct
{
  __IO uint32_t VR;            /*!< DSI Host Version Register,                                 Address offset: 0x00      */
  __IO uint32_t CR;            /*!< DSI Host Control Register,                                 Address offset: 0x04      */
  __IO uint32_t CCR;           /*!< DSI HOST Clock Control Register,                           Address offset: 0x08      */
  __IO uint32_t LVCIDR;        /*!< DSI Host LTDC VCID Register,                               Address offset: 0x0C      */
  __IO uint32_t LCOLCR;        /*!< DSI Host LTDC Color Coding Register,                       Address offset: 0x10      */
  __IO uint32_t LPCR;          /*!< DSI Host LTDC Polarity Configuration Register,             Address offset: 0x14      */
  __IO uint32_t LPMCR;         /*!< DSI Host Low-Power Mode Configuration Register,            Address offset: 0x18      */
  uint32_t      RESERVED0[4];  /*!< Reserved, 0x1C - 0x2B                                                                */
  __IO uint32_t PCR;           /*!< DSI Host Protocol Configuration Register,                  Address offset: 0x2C      */
  __IO uint32_t GVCIDR;        /*!< DSI Host Generic VCID Register,                            Address offset: 0x30      */
  __IO uint32_t MCR;           /*!< DSI Host Mode Configuration Register,                      Address offset: 0x34      */
  __IO uint32_t VMCR;          /*!< DSI Host Video Mode Configuration Register,                Address offset: 0x38      */
  __IO uint32_t VPCR;          /*!< DSI Host Video Packet Configuration Register,              Address offset: 0x3C      */
  __IO uint32_t VCCR;          /*!< DSI Host Video Chunks Configuration Register,              Address offset: 0x40      */
  __IO uint32_t VNPCR;         /*!< DSI Host Video Null Packet Configuration Register,         Address offset: 0x44      */
  __IO uint32_t VHSACR;        /*!< DSI Host Video HSA Configuration Register,                 Address offset: 0x48      */
  __IO uint32_t VHBPCR;        /*!< DSI Host Video HBP Configuration Register,                 Address offset: 0x4C      */
  __IO uint32_t VLCR;          /*!< DSI Host Video Line Configuration Register,                Address offset: 0x50      */
  __IO uint32_t VVSACR;        /*!< DSI Host Video VSA Configuration Register,                 Address offset: 0x54      */
  __IO uint32_t VVBPCR;        /*!< DSI Host Video VBP Configuration Register,                 Address offset: 0x58      */
  __IO uint32_t VVFPCR;        /*!< DSI Host Video VFP Configuration Register,                 Address offset: 0x5C      */
  __IO uint32_t VVACR;         /*!< DSI Host Video VA Configuration Register,                  Address offset: 0x60      */
  __IO uint32_t LCCR;          /*!< DSI Host LTDC Command Configuration Register,              Address offset: 0x64      */
  __IO uint32_t CMCR;          /*!< DSI Host Command Mode Configuration Register,              Address offset: 0x68      */
  __IO uint32_t GHCR;          /*!< DSI Host Generic Header Configuration Register,            Address offset: 0x6C      */
  __IO uint32_t GPDR;          /*!< DSI Host Generic Payload Data Register,                    Address offset: 0x70      */
  __IO uint32_t GPSR;          /*!< DSI Host Generic Packet Status Register,                   Address offset: 0x74      */
  __IO uint32_t TCCR[6];       /*!< DSI Host Timeout Counter Configuration Register,           Address offset: 0x78-0x8F */
  __IO uint32_t TDCR;          /*!< DSI Host 3D Configuration Register,                        Address offset: 0x90      */
  __IO uint32_t CLCR;          /*!< DSI Host Clock Lane Configuration Register,                Address offset: 0x94      */
  __IO uint32_t CLTCR;         /*!< DSI Host Clock Lane Timer Configuration Register,          Address offset: 0x98      */
  __IO uint32_t DLTCR;         /*!< DSI Host Data Lane Timer Configuration Register,           Address offset: 0x9C      */
  __IO uint32_t PCTLR;         /*!< DSI Host PHY Control Register,                             Address offset: 0xA0      */
  __IO uint32_t PCONFR;        /*!< DSI Host PHY Configuration Register,                       Address offset: 0xA4      */
  __IO uint32_t PUCR;          /*!< DSI Host PHY ULPS Control Register,                        Address offset: 0xA8      */
  __IO uint32_t PTTCR;         /*!< DSI Host PHY TX Triggers Configuration Register,           Address offset: 0xAC      */
  __IO uint32_t PSR;           /*!< DSI Host PHY Status Register,                              Address offset: 0xB0      */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0xB4 - 0xBB                                                                */
  __IO uint32_t ISR[2];        /*!< DSI Host Interrupt & Status Register,                      Address offset: 0xBC-0xC3 */
  __IO uint32_t IER[2];        /*!< DSI Host Interrupt Enable Register,                        Address offset: 0xC4-0xCB */
  uint32_t      RESERVED2[3];  /*!< Reserved, 0xD0 - 0xD7                                                                */
  __IO uint32_t FIR[2];        /*!< DSI Host Force Interrupt Register,                         Address offset: 0xD8-0xDF */
  uint32_t      RESERVED3[8];  /*!< Reserved, 0xE0 - 0xFF                                                                */
  __IO uint32_t VSCR;          /*!< DSI Host Video Shadow Control Register,                    Address offset: 0x100     */
  uint32_t      RESERVED4[2];  /*!< Reserved, 0x104 - 0x10B                                                              */
  __IO uint32_t LCVCIDR;       /*!< DSI Host LTDC Current VCID Register,                       Address offset: 0x10C     */
  __IO uint32_t LCCCR;         /*!< DSI Host LTDC Current Color Coding Register,               Address offset: 0x110     */
  uint32_t      RESERVED5;     /*!< Reserved, 0x114                                                                      */
  __IO uint32_t LPMCCR;        /*!< DSI Host Low-power Mode Current Configuration Register,    Address offset: 0x118     */
  uint32_t      RESERVED6[7];  /*!< Reserved, 0x11C - 0x137                                                              */
  __IO uint32_t VMCCR;         /*!< DSI Host Video Mode Current Configuration Register,        Address offset: 0x138     */
  __IO uint32_t VPCCR;         /*!< DSI Host Video Packet Current Configuration Register,      Address offset: 0x13C     */
  __IO uint32_t VCCCR;         /*!< DSI Host Video Chuncks Current Configuration Register,     Address offset: 0x140     */
  __IO uint32_t VNPCCR;        /*!< DSI Host Video Null Packet Current Configuration Register, Address offset: 0x144     */
  __IO uint32_t VHSACCR;       /*!< DSI Host Video HSA Current Configuration Register,         Address offset: 0x148     */
  __IO uint32_t VHBPCCR;       /*!< DSI Host Video HBP Current Configuration Register,         Address offset: 0x14C     */
  __IO uint32_t VLCCR;         /*!< DSI Host Video Line Current Configuration Register,        Address offset: 0x150     */
  __IO uint32_t VVSACCR;       /*!< DSI Host Video VSA Current Configuration Register,         Address offset: 0x154     */
  __IO uint32_t VVBPCCR;       /*!< DSI Host Video VBP Current Configuration Register,         Address offset: 0x158     */
  __IO uint32_t VVFPCCR;       /*!< DSI Host Video VFP Current Configuration Register,         Address offset: 0x15C     */
  __IO uint32_t VVACCR;        /*!< DSI Host Video VA Current Configuration Register,          Address offset: 0x160     */
  uint32_t      RESERVED7[11]; /*!< Reserved, 0x164 - 0x18F                                                              */
  __IO uint32_t TDCCR;         /*!< DSI Host 3D Current Configuration Register,                Address offset: 0x190     */
  uint32_t      RESERVED8[155]; /*!< Reserved, 0x194 - 0x3FF                                                               */
  __IO uint32_t WCFGR;          /*!< DSI Wrapper Configuration Register,                       Address offset: 0x400       */
  __IO uint32_t WCR;            /*!< DSI Wrapper Control Register,                             Address offset: 0x404       */
  __IO uint32_t WIER;           /*!< DSI Wrapper Interrupt Enable Register,                    Address offset: 0x408       */
  __IO uint32_t WISR;           /*!< DSI Wrapper Interrupt and Status Register,                Address offset: 0x40C       */
  __IO uint32_t WIFCR;          /*!< DSI Wrapper Interrupt Flag Clear Register,                Address offset: 0x410       */
  uint32_t      RESERVED9;      /*!< Reserved, 0x414                                                                       */
  __IO uint32_t WPCR[5];        /*!< DSI Wrapper PHY Configuration Register,                   Address offset: 0x418-0x42B */
  uint32_t      RESERVED10;     /*!< Reserved, 0x42C                                                                       */
  __IO uint32_t WRPCR;          /*!< DSI Wrapper Regulator and PLL Control Register, Address offset: 0x430                 */
} DSI_TypeDef;


typedef struct
{
  __IO uint32_t CR1;        /*!< I2C Control register 1,     Address offset: 0x00 */
  __IO uint32_t CR2;        /*!< I2C Control register 2,     Address offset: 0x04 */
  __IO uint32_t OAR1;       /*!< I2C Own address register 1, Address offset: 0x08 */
  __IO uint32_t OAR2;       /*!< I2C Own address register 2, Address offset: 0x0C */
  __IO uint32_t DR;         /*!< I2C Data register,          Address offset: 0x10 */
  __IO uint32_t SR1;        /*!< I2C Status register 1,      Address offset: 0x14 */
  __IO uint32_t SR2;        /*!< I2C Status register 2,      Address offset: 0x18 */
  __IO uint32_t CCR;        /*!< I2C Clock control register, Address offset: 0x1C */
  __IO uint32_t TRISE;      /*!< I2C TRISE register,         Address offset: 0x20 */
  __IO uint32_t FLTR;       /*!< I2C FLTR register,          Address offset: 0x24 */
} I2C_TypeDef;




/**
  * @brief LCD-TFT Display Controller
  */

typedef struct
{
  uint32_t      RESERVED0[2];  /*!< Reserved, 0x00-0x04 */
  __IO uint32_t SSCR;          /*!< LTDC Synchronization Size Configuration Register,    Address offset: 0x08 */
  __IO uint32_t BPCR;          /*!< LTDC Back Porch Configuration Register,              Address offset: 0x0C */
  __IO uint32_t AWCR;          /*!< LTDC Active Width Configuration Register,            Address offset: 0x10 */
  __IO uint32_t TWCR;          /*!< LTDC Total Width Configuration Register,             Address offset: 0x14 */
  __IO uint32_t GCR;           /*!< LTDC Global Control Register,                        Address offset: 0x18 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x1C-0x20 */
  __IO uint32_t SRCR;          /*!< LTDC Shadow Reload Configuration Register,           Address offset: 0x24 */
  uint32_t      RESERVED2[1];  /*!< Reserved, 0x28 */
  __IO uint32_t BCCR;          /*!< LTDC Background Color Configuration Register,        Address offset: 0x2C */
  uint32_t      RESERVED3[1];  /*!< Reserved, 0x30 */
  __IO uint32_t IER;           /*!< LTDC Interrupt Enable Register,                      Address offset: 0x34 */
  __IO uint32_t ISR;           /*!< LTDC Interrupt Status Register,                      Address offset: 0x38 */
  __IO uint32_t ICR;           /*!< LTDC Interrupt Clear Register,                       Address offset: 0x3C */
  __IO uint32_t LIPCR;         /*!< LTDC Line Interrupt Position Configuration Register, Address offset: 0x40 */
  __IO uint32_t CPSR;          /*!< LTDC Current Position Status Register,               Address offset: 0x44 */
  __IO uint32_t CDSR;         /*!< LTDC Current Display Status Register,                       Address offset: 0x48 */
} LTDC_TypeDef;

/**
  * @brief LCD-TFT Display layer x Controller
  */

typedef struct
{
  __IO uint32_t CR;            /*!< LTDC Layerx Control Register                                  Address offset: 0x84 */
  __IO uint32_t WHPCR;         /*!< LTDC Layerx Window Horizontal Position Configuration Register Address offset: 0x88 */
  __IO uint32_t WVPCR;         /*!< LTDC Layerx Window Vertical Position Configuration Register   Address offset: 0x8C */
  __IO uint32_t CKCR;          /*!< LTDC Layerx Color Keying Configuration Register               Address offset: 0x90 */
  __IO uint32_t PFCR;          /*!< LTDC Layerx Pixel Format Configuration Register               Address offset: 0x94 */
  __IO uint32_t CACR;          /*!< LTDC Layerx Constant Alpha Configuration Register             Address offset: 0x98 */
  __IO uint32_t DCCR;          /*!< LTDC Layerx Default Color Configuration Register              Address offset: 0x9C */
  __IO uint32_t BFCR;          /*!< LTDC Layerx Blending Factors Configuration Register           Address offset: 0xA0 */
  uint32_t      RESERVED0[2];  /*!< Reserved */
  __IO uint32_t CFBAR;         /*!< LTDC Layerx Color Frame Buffer Address Register               Address offset: 0xAC */
  __IO uint32_t CFBLR;         /*!< LTDC Layerx Color Frame Buffer Length Register                Address offset: 0xB0 */
  __IO uint32_t CFBLNR;        /*!< LTDC Layerx ColorFrame Buffer Line Number Register            Address offset: 0xB4 */
  uint32_t      RESERVED1[3];  /*!< Reserved */
  __IO uint32_t CLUTWR;         /*!< LTDC Layerx CLUT Write Register                               Address offset: 0x144 */

} LTDC_Layer_TypeDef;



/**
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t TR;      /*!< RTC time register,                                        Address offset: 0x00 */
  __IO uint32_t DR;      /*!< RTC date register,                                        Address offset: 0x04 */
  __IO uint32_t CR;      /*!< RTC control register,                                     Address offset: 0x08 */
  __IO uint32_t ISR;     /*!< RTC initialization and status register,                   Address offset: 0x0C */
  __IO uint32_t PRER;    /*!< RTC prescaler register,                                   Address offset: 0x10 */
  __IO uint32_t WUTR;    /*!< RTC wakeup timer register,                                Address offset: 0x14 */
  __IO uint32_t CALIBR;  /*!< RTC calibration register,                                 Address offset: 0x18 */
  __IO uint32_t ALRMAR;  /*!< RTC alarm A register,                                     Address offset: 0x1C */
  __IO uint32_t ALRMBR;  /*!< RTC alarm B register,                                     Address offset: 0x20 */
  __IO uint32_t WPR;     /*!< RTC write protection register,                            Address offset: 0x24 */
  __IO uint32_t SSR;     /*!< RTC sub second register,                                  Address offset: 0x28 */
  __IO uint32_t SHIFTR;  /*!< RTC shift control register,                               Address offset: 0x2C */
  __IO uint32_t TSTR;    /*!< RTC time stamp time register,                             Address offset: 0x30 */
  __IO uint32_t TSDR;    /*!< RTC time stamp date register,                             Address offset: 0x34 */
  __IO uint32_t TSSSR;   /*!< RTC time-stamp sub second register,                       Address offset: 0x38 */
  __IO uint32_t CALR;    /*!< RTC calibration register,                                 Address offset: 0x3C */
  __IO uint32_t TAFCR;   /*!< RTC tamper and alternate function configuration register, Address offset: 0x40 */
  __IO uint32_t ALRMASSR;/*!< RTC alarm A sub second register,                          Address offset: 0x44 */
  __IO uint32_t ALRMBSSR;/*!< RTC alarm B sub second register,                          Address offset: 0x48 */
  uint32_t RESERVED7;    /*!< Reserved, 0x4C                                                                 */
  __IO uint32_t BKP0R;   /*!< RTC backup register 1,                                    Address offset: 0x50 */
  __IO uint32_t BKP1R;   /*!< RTC backup register 1,                                    Address offset: 0x54 */
  __IO uint32_t BKP2R;   /*!< RTC backup register 2,                                    Address offset: 0x58 */
  __IO uint32_t BKP3R;   /*!< RTC backup register 3,                                    Address offset: 0x5C */
  __IO uint32_t BKP4R;   /*!< RTC backup register 4,                                    Address offset: 0x60 */
  __IO uint32_t BKP5R;   /*!< RTC backup register 5,                                    Address offset: 0x64 */
  __IO uint32_t BKP6R;   /*!< RTC backup register 6,                                    Address offset: 0x68 */
  __IO uint32_t BKP7R;   /*!< RTC backup register 7,                                    Address offset: 0x6C */
  __IO uint32_t BKP8R;   /*!< RTC backup register 8,                                    Address offset: 0x70 */
  __IO uint32_t BKP9R;   /*!< RTC backup register 9,                                    Address offset: 0x74 */
  __IO uint32_t BKP10R;  /*!< RTC backup register 10,                                   Address offset: 0x78 */
  __IO uint32_t BKP11R;  /*!< RTC backup register 11,                                   Address offset: 0x7C */
  __IO uint32_t BKP12R;  /*!< RTC backup register 12,                                   Address offset: 0x80 */
  __IO uint32_t BKP13R;  /*!< RTC backup register 13,                                   Address offset: 0x84 */
  __IO uint32_t BKP14R;  /*!< RTC backup register 14,                                   Address offset: 0x88 */
  __IO uint32_t BKP15R;  /*!< RTC backup register 15,                                   Address offset: 0x8C */
  __IO uint32_t BKP16R;  /*!< RTC backup register 16,                                   Address offset: 0x90 */
  __IO uint32_t BKP17R;  /*!< RTC backup register 17,                                   Address offset: 0x94 */
  __IO uint32_t BKP18R;  /*!< RTC backup register 18,                                   Address offset: 0x98 */
  __IO uint32_t BKP19R;  /*!< RTC backup register 19,                                   Address offset: 0x9C */
} RTC_TypeDef;



/**
  * @brief Crypto Processor
  */

typedef struct
{
  __IO uint32_t CR;         /*!< CRYP control register,                                    Address offset: 0x00 */
  __IO uint32_t SR;         /*!< CRYP status register,                                     Address offset: 0x04 */
  __IO uint32_t DR;         /*!< CRYP data input register,                                 Address offset: 0x08 */
  __IO uint32_t DOUT;       /*!< CRYP data output register,                                Address offset: 0x0C */
  __IO uint32_t DMACR;      /*!< CRYP DMA control register,                                Address offset: 0x10 */
  __IO uint32_t IMSCR;      /*!< CRYP interrupt mask set/clear register,                   Address offset: 0x14 */
  __IO uint32_t RISR;       /*!< CRYP raw interrupt status register,                       Address offset: 0x18 */
  __IO uint32_t MISR;       /*!< CRYP masked interrupt status register,                    Address offset: 0x1C */
  __IO uint32_t K0LR;       /*!< CRYP key left  register 0,                                Address offset: 0x20 */
  __IO uint32_t K0RR;       /*!< CRYP key right register 0,                                Address offset: 0x24 */
  __IO uint32_t K1LR;       /*!< CRYP key left  register 1,                                Address offset: 0x28 */
  __IO uint32_t K1RR;       /*!< CRYP key right register 1,                                Address offset: 0x2C */
  __IO uint32_t K2LR;       /*!< CRYP key left  register 2,                                Address offset: 0x30 */
  __IO uint32_t K2RR;       /*!< CRYP key right register 2,                                Address offset: 0x34 */
  __IO uint32_t K3LR;       /*!< CRYP key left  register 3,                                Address offset: 0x38 */
  __IO uint32_t K3RR;       /*!< CRYP key right register 3,                                Address offset: 0x3C */
  __IO uint32_t IV0LR;      /*!< CRYP initialization vector left-word  register 0,         Address offset: 0x40 */
  __IO uint32_t IV0RR;      /*!< CRYP initialization vector right-word register 0,         Address offset: 0x44 */
  __IO uint32_t IV1LR;      /*!< CRYP initialization vector left-word  register 1,         Address offset: 0x48 */
  __IO uint32_t IV1RR;      /*!< CRYP initialization vector right-word register 1,         Address offset: 0x4C */
  __IO uint32_t CSGCMCCM0R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 0,        Address offset: 0x50 */
  __IO uint32_t CSGCMCCM1R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 1,        Address offset: 0x54 */
  __IO uint32_t CSGCMCCM2R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 2,        Address offset: 0x58 */
  __IO uint32_t CSGCMCCM3R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 3,        Address offset: 0x5C */
  __IO uint32_t CSGCMCCM4R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 4,        Address offset: 0x60 */
  __IO uint32_t CSGCMCCM5R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 5,        Address offset: 0x64 */
  __IO uint32_t CSGCMCCM6R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 6,        Address offset: 0x68 */
  __IO uint32_t CSGCMCCM7R; /*!< CRYP GCM/GMAC or CCM/CMAC context swap register 7,        Address offset: 0x6C */
  __IO uint32_t CSGCM0R;    /*!< CRYP GCM/GMAC context swap register 0,                    Address offset: 0x70 */
  __IO uint32_t CSGCM1R;    /*!< CRYP GCM/GMAC context swap register 1,                    Address offset: 0x74 */
  __IO uint32_t CSGCM2R;    /*!< CRYP GCM/GMAC context swap register 2,                    Address offset: 0x78 */
  __IO uint32_t CSGCM3R;    /*!< CRYP GCM/GMAC context swap register 3,                    Address offset: 0x7C */
  __IO uint32_t CSGCM4R;    /*!< CRYP GCM/GMAC context swap register 4,                    Address offset: 0x80 */
  __IO uint32_t CSGCM5R;    /*!< CRYP GCM/GMAC context swap register 5,                    Address offset: 0x84 */
  __IO uint32_t CSGCM6R;    /*!< CRYP GCM/GMAC context swap register 6,                    Address offset: 0x88 */
  __IO uint32_t CSGCM7R;    /*!< CRYP GCM/GMAC context swap register 7,                    Address offset: 0x8C */
} CRYP_TypeDef;

/**
  * @brief HASH
  */

typedef struct
{
  __IO uint32_t CR;               /*!< HASH control register,          Address offset: 0x00        */
  __IO uint32_t DIN;              /*!< HASH data input register,       Address offset: 0x04        */
  __IO uint32_t STR;              /*!< HASH start register,            Address offset: 0x08        */
  __IO uint32_t HR[5];            /*!< HASH digest registers,          Address offset: 0x0C-0x1C   */
  __IO uint32_t IMR;              /*!< HASH interrupt enable register, Address offset: 0x20        */
  __IO uint32_t SR;               /*!< HASH status register,           Address offset: 0x24        */
       uint32_t RESERVED[52];     /*!< Reserved, 0x28-0xF4                                         */
  __IO uint32_t CSR[54];          /*!< HASH context swap registers,    Address offset: 0x0F8-0x1CC */
} HASH_TypeDef;

/**
  * @brief HASH_DIGEST
  */

typedef struct
{
  __IO uint32_t HR[8];     /*!< HASH digest registers,          Address offset: 0x310-0x32C */
} HASH_DIGEST_TypeDef;


/**
  * @brief USB_OTG_Core_Registers
  */
typedef struct
{
 __IO uint32_t GOTGCTL;               /*!< USB_OTG Control and Status Register          000h */
  __IO uint32_t GOTGINT;              /*!< USB_OTG Interrupt Register                   004h */
  __IO uint32_t GAHBCFG;              /*!< Core AHB Configuration Register              008h */
  __IO uint32_t GUSBCFG;              /*!< Core USB Configuration Register              00Ch */
  __IO uint32_t GRSTCTL;              /*!< Core Reset Register                          010h */
  __IO uint32_t GINTSTS;              /*!< Core Interrupt Register                      014h */
  __IO uint32_t GINTMSK;              /*!< Core Interrupt Mask Register                 018h */
  __IO uint32_t GRXSTSR;              /*!< Receive Sts Q Read Register                  01Ch */
  __IO uint32_t GRXSTSP;              /*!< Receive Sts Q Read & POP Register            020h */
  __IO uint32_t GRXFSIZ;              /*!< Receive FIFO Size Register                   024h */
  __IO uint32_t DIEPTXF0_HNPTXFSIZ;   /*!< EP0 / Non Periodic Tx FIFO Size Register     028h */
  __IO uint32_t HNPTXSTS;             /*!< Non Periodic Tx FIFO/Queue Sts reg           02Ch */
  uint32_t Reserved30[2];             /*!< Reserved                                     030h */
  __IO uint32_t GCCFG;                /*!< General Purpose IO Register                  038h */
  __IO uint32_t CID;                  /*!< User ID Register                             03Ch */
  uint32_t  Reserved5[3];             /*!< Reserved                                040h-048h */
  __IO uint32_t GHWCFG3;              /*!< User HW config3                              04Ch */
  uint32_t  Reserved6;                /*!< Reserved                                     050h */
  __IO uint32_t GLPMCFG;              /*!< LPM Register                                 054h */
  __IO uint32_t GPWRDN;               /*!< Power Down Register                          058h */
  __IO uint32_t GDFIFOCFG;            /*!< DFIFO Software Config Register               05Ch */
   __IO uint32_t GADPCTL;             /*!< ADP Timer, Control and Status Register       60Ch */
    uint32_t  Reserved43[39];         /*!< Reserved                                058h-0FFh */
  __IO uint32_t HPTXFSIZ;             /*!< Host Periodic Tx FIFO Size Reg               100h */
  __IO uint32_t DIEPTXF[0x0F];        /*!< dev Periodic Transmit FIFO */
} USB_OTG_GlobalTypeDef;

/**
  * @brief USB_OTG_device_Registers
  */
typedef struct
{
  __IO uint32_t DCFG;            /*!< dev Configuration Register   800h */
  __IO uint32_t DCTL;            /*!< dev Control Register         804h */
  __IO uint32_t DSTS;            /*!< dev Status Register (RO)     808h */
  uint32_t Reserved0C;           /*!< Reserved                     80Ch */
  __IO uint32_t DIEPMSK;         /*!< dev IN Endpoint Mask         810h */
  __IO uint32_t DOEPMSK;         /*!< dev OUT Endpoint Mask        814h */
  __IO uint32_t DAINT;           /*!< dev All Endpoints Itr Reg    818h */
  __IO uint32_t DAINTMSK;        /*!< dev All Endpoints Itr Mask   81Ch */
  uint32_t  Reserved20;          /*!< Reserved                     820h */
  uint32_t Reserved9;            /*!< Reserved                     824h */
  __IO uint32_t DVBUSDIS;        /*!< dev VBUS discharge Register  828h */
  __IO uint32_t DVBUSPULSE;      /*!< dev VBUS Pulse Register      82Ch */
  __IO uint32_t DTHRCTL;         /*!< dev threshold                830h */
  __IO uint32_t DIEPEMPMSK;      /*!< dev empty msk                834h */
  __IO uint32_t DEACHINT;        /*!< dedicated EP interrupt       838h */
  __IO uint32_t DEACHMSK;        /*!< dedicated EP msk             83Ch */
  uint32_t Reserved40;           /*!< dedicated EP mask            840h */
  __IO uint32_t DINEP1MSK;       /*!< dedicated EP mask            844h */
  uint32_t  Reserved44[15];      /*!< Reserved                 844-87Ch */
  __IO uint32_t DOUTEP1MSK;      /*!< dedicated EP msk             884h */
} USB_OTG_DeviceTypeDef;

/**
  * @brief USB_OTG_IN_Endpoint-Specific_Register
  */
typedef struct
{
  __IO uint32_t DIEPCTL;           /*!< dev IN Endpoint Control Reg    900h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;             /*!< Reserved                       900h + (ep_num * 20h) + 04h */
  __IO uint32_t DIEPINT;           /*!< dev IN Endpoint Itr Reg        900h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;             /*!< Reserved                       900h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DIEPTSIZ;          /*!< IN Endpoint Txfer Size         900h + (ep_num * 20h) + 10h */
  __IO uint32_t DIEPDMA;           /*!< IN Endpoint DMA Address Reg    900h + (ep_num * 20h) + 14h */
  __IO uint32_t DTXFSTS;           /*!< IN Endpoint Tx FIFO Status Reg 900h + (ep_num * 20h) + 18h */
  uint32_t Reserved18;             /*!< Reserved  900h+(ep_num*20h)+1Ch-900h+ (ep_num * 20h) + 1Ch */
} USB_OTG_INEndpointTypeDef;

/**
  * @brief USB_OTG_OUT_Endpoint-Specific_Registers
  */
typedef struct
{
  __IO uint32_t DOEPCTL;       /*!< dev OUT Endpoint Control Reg           B00h + (ep_num * 20h) + 00h */
  uint32_t Reserved04;         /*!< Reserved                               B00h + (ep_num * 20h) + 04h */
  __IO uint32_t DOEPINT;       /*!< dev OUT Endpoint Itr Reg               B00h + (ep_num * 20h) + 08h */
  uint32_t Reserved0C;         /*!< Reserved                               B00h + (ep_num * 20h) + 0Ch */
  __IO uint32_t DOEPTSIZ;      /*!< dev OUT Endpoint Txfer Size            B00h + (ep_num * 20h) + 10h */
  __IO uint32_t DOEPDMA;       /*!< dev OUT Endpoint DMA Address           B00h + (ep_num * 20h) + 14h */
  uint32_t Reserved18[2];      /*!< Reserved B00h + (ep_num * 20h) + 18h - B00h + (ep_num * 20h) + 1Ch */
} USB_OTG_OUTEndpointTypeDef;

/**
  * @brief USB_OTG_Host_Mode_Register_Structures
  */
typedef struct
{
  __IO uint32_t HCFG;             /*!< Host Configuration Register          400h */
  __IO uint32_t HFIR;             /*!< Host Frame Interval Register         404h */
  __IO uint32_t HFNUM;            /*!< Host Frame Nbr/Frame Remaining       408h */
  uint32_t Reserved40C;           /*!< Reserved                             40Ch */
  __IO uint32_t HPTXSTS;          /*!< Host Periodic Tx FIFO/ Queue Status  410h */
  __IO uint32_t HAINT;            /*!< Host All Channels Interrupt Register 414h */
  __IO uint32_t HAINTMSK;         /*!< Host All Channels Interrupt Mask     418h */
} USB_OTG_HostTypeDef;

/**
  * @brief USB_OTG_Host_Channel_Specific_Registers
  */
typedef struct
{
  __IO uint32_t HCCHAR;           /*!< Host Channel Characteristics Register    500h */
  __IO uint32_t HCSPLT;           /*!< Host Channel Split Control Register      504h */
  __IO uint32_t HCINT;            /*!< Host Channel Interrupt Register          508h */
  __IO uint32_t HCINTMSK;         /*!< Host Channel Interrupt Mask Register     50Ch */
  __IO uint32_t HCTSIZ;           /*!< Host Channel Transfer Size Register      510h */
  __IO uint32_t HCDMA;            /*!< Host Channel DMA Address Register        514h */
  uint32_t Reserved[2];           /*!< Reserved                                      */
} USB_OTG_HostChannelTypeDef;

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
       NVIC_SetVectorTable(NVIC_VectTab_RAM, (unsigned)(vec_table - sram_addr) ) ;
     }
   //-------------------------------------------------------------------
   inline void vec_map2flash ( unsigned* vec_table )
     {
       // TODO
       NVIC_SetVectorTable(NVIC_VectTab_FLASH, (unsigned)(vec_table - flash_axi_addr) ) ;
     }
//-------------------------------------------------------------------

#endif //__USE_RAM_VEC_TABLE__




inline __attribute__((always_inline)) void system_init(const uint32_t vec_tab_offset, const stm32f7::rcc_t::system_init_profile_t& system_init_profile)
{
    // установка доступа к FPU
    scb.coprocessor_10_access_full();
    scb.coprocessor_11_access_full();

    rcc.hsi_on();
    rcc.hsi_ready_wait();
    rcc.sys_clock_hsi();
    rcc.sys_clock_state_hsi_wait();

    rcc.pwr_enable();

    pwr.regulator_voltage_scale(system_init_profile.regulator_voltage_scale);
    //pwr.wait_regulator_voltage_scale_output_selection_ready();

    if (system_init_profile.overdrive)
      {
        pwr.over_drive_enable();
	pwr.wait_over_drive_mode_ready();

        pwr.over_drive_switching_enable();
        pwr.wait_over_drive_mode_switching_active();
      }

    rcc.ahb_prescaler(system_init_profile.hpre);
    rcc.apb1_prescaler(system_init_profile.ppre1);
    rcc.apb2_prescaler(system_init_profile.ppre2);

    flash.latency(system_init_profile.latency);
    flash.prefetch(system_init_profile.prefetch);
    flash.art_accelerator(system_init_profile.art_accelerator);

    rcc.sys_clock_select( system_init_profile.sys_clock_source, system_init_profile.pll_m, system_init_profile.pll_n, system_init_profile.pll_p, system_init_profile.pll_q);

    // Ensure 8-byte alignment of stack pointer on interrupts
    // Enabled by default on most Cortex-M parts, but not M3 r1
    //
    // in cortex-m7 8-byte alignment strongly fixed in hardware


    scb.vector_table_offset(vec_tab_offset);// установка смещения таблицы векторов прерываний

    if( system_init_profile.l1_instruction_cache_active)
      {
        scb.instruction_cache_activated();
        scb.instruction_cache_invalidate();
      }
    if( system_init_profile.l1_data_cache_active)
      {
        scb.data_cache_activated();
        scb.data_cache_clean_invalidate();
      }
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

   volatile unsigned long* data_load  ;
   volatile unsigned long* data  ;
   volatile unsigned long* data_end ;

  #ifdef __CCM_RAM__
    // init .ccm_data section
    data_load = (unsigned long*)gnu_linker_ccm_data_load_start() ;
    data = (unsigned long*)gnu_linker_ccm_data_start() ;
    data_end = (unsigned long*)gnu_linker_ccm_data_end();
    while( data < data_end )
         {
          *(data++) = *(data_load++);
         }
  #endif

  #ifdef __ITCM_RAM__
    // init .itcm_data section
    data_load = (unsigned long*)gnu_linker_itcm_data_load_start() ;
    data = (unsigned long*)gnu_linker_itcm_data_start() ;
    data_end = (unsigned long*)gnu_linker_itcm_data_end();
    while( data < data_end )
         {
          *(data++) = *(data_load++);
         }
  #endif

  #ifdef __DTCM_RAM__
    // init .dtcm_data section
    data_load = (unsigned long*)gnu_linker_dtcm_data_load_start() ;
    data = (unsigned long*)gnu_linker_dtcm_data_start() ;
    data_end = (unsigned long*)gnu_linker_dtcm_data_end();
    while( data < data_end )
         {
          *(data++) = *(data_load++);
         }
  #endif


  // init .data section
  data_load = (unsigned long*)gnu_linker_data_load_start();
  data = (unsigned long*)gnu_linker_data_start();
  data_end = (unsigned long*)gnu_linker_data_end();
  while( data < data_end )
         {
          *(data++) = *(data_load++);
         }
  volatile unsigned long* bss ;
  volatile unsigned long* bss_end;

  #ifdef __CCM_RAM__
    // init .ccm_bss section
    bss = (unsigned long*)gnu_linker_ccm_bss_start() ;
    bss_end = (unsigned long*)gnu_linker_ccm_bss_end() ;
    while(bss < bss_end )
       {
          *(bss++) =  0 ;
       }
  #endif

  #ifdef __ITCM_RAM__
    // init .itcm_bss section
    bss = (unsigned long*)gnu_linker_itcm_bss_start() ;
    bss_end = (unsigned long*)gnu_linker_itcm_bss_end() ;
    while(bss < bss_end )
      {
        *(bss++) =  0 ;
      }
  #endif

  #ifdef __DTCM_RAM__
    // init .dtcm_bss section
    bss = (unsigned long*)gnu_linker_dtcm_bss_start() ;
    bss_end = (unsigned long*)gnu_linker_dtcm_bss_end() ;
    while(bss < bss_end )
      {
        *(bss++) =  0 ;
      }
  #endif

  // init .bss section
  bss = (unsigned long*)gnu_linker_bss_start() ;
  bss_end = (unsigned long*)gnu_linker_bss_end() ;
  while(bss < bss_end )
   {
     *(bss++) =  0 ;
   }


#ifdef __EXT_MEM_BANK0__

  // init external memory bank0 interface and device, user defined code
  void ext_mem_bank0_init();
  ext_mem_bank0_init();

  // init .data section on ext_mem_bank0
  extern unsigned long  __ext_mem_bank0_data_load_start__ ;
  extern unsigned long  __ext_mem_bank0_data_start__ ;
  extern unsigned long  __ext_mem_bank0_data_end__ ;
  unsigned long* ext_mem_bank0_data_load = &__ext_mem_bank0_data_load_start__ ;
  unsigned long* ext_mem_bank0_data = &__ext_mem_bank0_data_start__ ;
  unsigned long* ext_mem_bank0_data_end = &__ext_mem_bank0_data_end__ ;
  while( ext_mem_bank0_data < ext_mem_bank0_data_end )
    {
      *(ext_mem_bank0_data++) = *(ext_mem_bank0_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank0_bss_start__ ;
  extern unsigned long  __ext_mem_bank0_bss_end__   ;
  unsigned long* ext_mem_bank0_bss = &__ext_mem_bank0_bss_start__ ;
  unsigned long* ext_mem_bank0_bss_end = &__ext_mem_bank0_bss_end__ ;
  while(ext_mem_bank0_bss < ext_mem_bank0_bss_end )
    {
      *(ext_mem_bank0_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK1__

  // init external memory bank1 interface and device, user defined code
  void ext_mem_bank1_init();
  ext_mem_bank1_init();

  // init .data section on ext_mem_bank1
  extern unsigned long  __ext_mem_bank1_data_load_start_ ;
  extern unsigned long  __ext_mem_bank1_data_start__ ;
  extern unsigned long  __ext_mem_bank1_data_end__ ;
  unsigned long* ext_mem_bank1_data_load = &__ext_mem_bank1_data_load_start__ ;
  unsigned long* ext_mem_bank1_data = &__ext_mem_bank1_data_start__ ;
  unsigned long* ext_mem_bank1_data_end = &__ext_mem_bank1_data_end__ ;
  while( ext_mem_bank1_data < ext_mem_bank1_data_end )
    {
      *(ext_mem_bank1_data++) = *(ext_mem_bank1_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank1_bss_start__ ;
  extern unsigned long  __ext_mem_bank1_bss_end__   ;
  unsigned long* ext_mem_bank1_bss = &__ext_mem_bank1_bss_start__ ;
  unsigned long* ext_mem_bank1_bss_end = &__ext_mem_bank1_bss_end__ ;
  while(ext_mem_bank1_bss < ext_mem_bank1_bss_end )
    {
      *(ext_mem_bank1_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK2__

  // init external memory bank2 interface and device, user defined code
  void ext_mem_bank2_init();
  ext_mem_bank2_init();

  // init .data section on ext_mem_bank2
  extern unsigned long  __ext_mem_bank2_data_load_start__ ;
  extern unsigned long  __ext_mem_bank2_data_start__ ;
  extern unsigned long  __ext_mem_bank2_data_end__ ;
  unsigned long* ext_mem_bank2_data_load = &__ext_mem_bank2_data_load_start__ ;
  unsigned long* ext_mem_bank2_data = &__ext_mem_bank2_data_start__ ;
  unsigned long* ext_mem_bank2_data_end = &__ext_mem_bank2_data_end__ ;
  while( ext_mem_bank2_data < ext_mem_bank2_data_end )
    {
      *(ext_mem_bank2_data++) = *(ext_mem_bank2_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank2_bss_start__ ;
  extern unsigned long  __ext_mem_bank2_bss_end__   ;
  unsigned long* ext_mem_bank2_bss = &__ext_mem_bank2_bss_start__ ;
  unsigned long* ext_mem_bank2_bss_end = &__ext_mem_bank2_bss_end__ ;
  while(ext_mem_bank2_bss < ext_mem_bank2_bss_end )
    {
      *(ext_mem_bank2_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK3__

  // init external memory bank3 interface and device, user defined code
  void ext_mem_bank3_init();
  ext_mem_bank3_init();

  // init .data section on ext_mem_bank3
  extern unsigned long  __ext_mem_bank3_data_load_start__ ;
  extern unsigned long  __ext_mem_bank3_data_start__ ;
  extern unsigned long  __ext_mem_bank3_data_end__ ;
  unsigned long* ext_mem_bank3_data_load = &__ext_mem_bank3_data_load_start__ ;
  unsigned long* ext_mem_bank3_data = &__ext_mem_bank3_data_start__ ;
  unsigned long* ext_mem_bank3_data_end = &__ext_mem_bank3_data_end__ ;
  while( ext_mem_bank3_data < ext_mem_bank3_data_end )
    {
      *(ext_mem_bank3_data++) = *(ext_mem_bank3_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank3_bss_start__ ;
  extern unsigned long  __ext_mem_bank3_bss_end__   ;
  unsigned long* ext_mem_bank3_bss = &__ext_mem_bank3_bss_start__ ;
  unsigned long* ext_mem_bank3_bss_end = &__ext_mem_bank3_bss_end__ ;
  while(ext_mem_bank3_bss < ext_mem_bank3_bss_end )
    {
      *(ext_mem_bank3_bss++) = 0 ;
    }
#endif

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
extern "C" void __attribute__((noreturn)) __main_exit_handler(int retval);

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

} // stm32f7



using namespace stm32f7 ;

#endif /* __STM32++_H__ */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
