#ifndef __STM32++_H__
#define __STM32++_H__

#include "gnu_linker.h"  // необходим для crt_init()
#include "supc++.h" // для std::__throw_invalid_argument

#include "arch/cortex-m/cortex_m7++.h"

namespace stm32h7
{

  static const uint32_t  d1_itcm_ram_addr =    0x00000000; /*!< Base address of : 64KB RAM reserved for CPU execution/instruction accessible over ITCM  */
  static const uint32_t  d1_itcm_icp_addr =    0x00100000; /*!< Base address of : (up to 128KB) embedded Test FLASH memory accessible over ITCM         */
  static const uint32_t  d1_dcm_ram_addr  =    0x20000000; /*!< Base address of : 128KB system data RAM accessible over DTCM                            */
  static const uint32_t  d1_axi_flash_addr =   0x08000000; /*!< Base address of : (up to 2 MB) embedded FLASH memory accessible over AXI                */
  static const uint32_t  d1_axi_icp_addr =     0x1FF00000; /*!< Base address of : (up to 128KB) embedded Test FLASH memory accessible over AXI          */
  static const uint32_t  d1_axi_sram_addr =    0x24000000; /*!< Base address of : (up to 512KB) system data RAM accessible over over AXI                */

  static const uint32_t  d2_axi_sram_addr  =   0x10000000; /*!< Base address of : (up to 288KB) system data RAM accessible over over AXI                */
  static const uint32_t  d2_ahb_sram_addr  =   0x30000000; /*!< Base address of : (up to 288KB) system data RAM accessible over over AXI->AHB Bridge    */

  static const uint32_t  d3_bkp_sram_addr =    0x38800000; /*!< Base address of : Backup SRAM(4 KB) over AXI->AHB Bridge                                */
  static const uint32_t  d3_sram_addr  =       0x38000000; /*!< Base address of : Backup SRAM(64 KB) over AXI->AHB Bridge                               */

  static const uint32_t  periph_addr =         0x40000000; /*!< Base address of : AHB/ABP Peripherals                                                   */
  static const uint32_t  qspi_axi_addr =       0x90000000; /*!< Base address of : Qspi memories  accessible over AXI                                    */

  static const uint32_t  flash_bank1_addr =    0x08000000; /*!< Base address of : (up to 1 MB) Flash Bank1 accessible over AXI                          */
  static const uint32_t  flash_bank2_addr =    0x08100000; /*!< Base address of : (up to 1 MB) Flash Bank2 accessible over AXI                          */
  static const uint32_t  flash_end_addr =      0x081FFFFF; /*!< FLASH end address                                                                       */

  static const uint32_t  flash_otp_bank1_addr =0x1FF00000; /*!< Base address of : (up to 128KB) embedded FLASH Bank1 OTP Area                           */
  static const uint32_t  flash_otp_bank1_end_addr =0x1FF1FFFF; /*!< End address of : (up to 128KB) embedded FLASH Bank1 OTP Area                        */
  static const uint32_t  flash_otp_bank2_addr =0x1FF40000; /*!< Base address of : (up to 128KB) embedded FLASH Bank2 OTP Area                           */
  static const uint32_t  flash_otp_bank2_end_addr =0x1FF5FFFF; /*!< End address of : (up to 128KB) embedded FLASH Bank2 OTP Area                        */

  static const uint32_t  uid_addr =            0x1FF1E800;         /*!< Unique device ID register base address */

  /*!< Peripheral memory map */
  static const uint32_t  d2_apb1_periph_addr =      periph_addr;
  static const uint32_t  d2_apb2_periph_addr =     (periph_addr + 0x00010000U);
  static const uint32_t  d2_ahb1_periph_addr =     (periph_addr + 0x00020000U);
  static const uint32_t  d2_ahb2_periph_addr =     (periph_addr + 0x08020000U);

  static const uint32_t  d1_apb1_periph_addr =     (periph_addr + 0x10000000);
  static const uint32_t  d1_ahb1_periph_addr =     (periph_addr + 0x12000000);

  static const uint32_t  d3_apb1_periph_addr =     (periph_addr + 0x18000000);
  static const uint32_t  d3_ahb1_periph_addr =     (periph_addr + 0x18020000);


  /*!< d1_AHB1PERIPH peripherals */

  static const uint32_t  mdma_addr =             (d1_ahb1_periph_addr + 0x0000);
  static const uint32_t  dma2d_addr =            (d1_ahb1_periph_addr + 0x1000);
  static const uint32_t  jpgdec_addr =           (d1_ahb1_periph_addr + 0x3000);
  static const uint32_t  flash_r_addr =          (d1_ahb1_periph_addr + 0x2000);
  static const uint32_t  fmc_r_addr =            (d1_ahb1_periph_addr + 0x4000);
  static const uint32_t  qspi_r_addr =           (d1_ahb1_periph_addr + 0x5000);
  static const uint32_t  dlyb_qspi_addr =        (d1_ahb1_periph_addr + 0x6000);
  static const uint32_t  sdmmc1_addr =           (d1_ahb1_periph_addr + 0x7000);
  static const uint32_t  dlyb_sdmmc1_addr =      (d1_ahb1_periph_addr + 0x8000);

  /*!< d2_AHB1PERIPH peripherals */

  static const uint32_t  dma1_addr =               (d2_ahb1_periph_addr + 0x0000);
  static const uint32_t  dma2_addr =               (d2_ahb1_periph_addr + 0x0400);
  static const uint32_t  dmamux1_addr =            (d2_ahb1_periph_addr + 0x0800);
  static const uint32_t  adc1_addr =               (d2_ahb1_periph_addr + 0x2000);
  static const uint32_t  adc2_addr =               (d2_ahb1_periph_addr + 0x2100);
  static const uint32_t  adc12_common_addr =       (d2_ahb1_periph_addr + 0x2300);
  static const uint32_t  art_addr =                (d2_ahb1_periph_addr + 0x4400);
  static const uint32_t  eth_addr =                (d2_ahb1_periph_addr + 0x8000);
  static const uint32_t  eth_mac_addr =            eth_addr;

  /*!< USB registers base address */
  static const uint32_t  usb1_otg_hs_periph_addr =              ((uint32_t )0x40040000);
  static const uint32_t  usb2_otg_fs_periph_addr =              ((uint32_t )0x40080000);
  static const uint32_t  usb_otg_global_addr =                  ((uint32_t )0x000);
  static const uint32_t  usb_otg_device_addr =                  ((uint32_t )0x800);
  static const uint32_t  usb_otg_in_endpoint_addr =             ((uint32_t )0x900);
  static const uint32_t  usb_otg_out_endpoint_addr =            ((uint32_t )0xB00);
  static const uint32_t  usb_otg_ep_reg_size =                  ((uint32_t )0x20);
  static const uint32_t  usb_otg_host_addr =                    ((uint32_t )0x400);
  static const uint32_t  usb_otg_host_port_addr =               ((uint32_t )0x440);
  static const uint32_t  usb_otg_host_channel_addr =            ((uint32_t )0x500);
  static const uint32_t  usb_otg_host_channel_size              ((uint32_t )0x20);
  static const uint32_t  usb_otg_pcgcctl_addr =                 ((uint32_t )0xE00);
  static const uint32_t  usb_otg_fifo_addr =                    ((uint32_t )0x1000);
  static const uint32_t  usb_otg_fifo_size =                    ((uint32_t )0x1000);

  /*!< d2_AHB2PERIPH peripherals */

  static const uint32_t  dcmi_addr =              (d2_ahb2_periph_addr + 0x0000);
  static const uint32_t  rng_addr =               (d2_ahb2_periph_addr + 0x1800);
  static const uint32_t  sdmmc2_addr =            (d2_ahb2_periph_addr + 0x2400);
  static const uint32_t  dlyb_sdmmc2_addr =       (d2_ahb2_periph_addr + 0x2800);


  /*!< d3_ahb1_periph peripherals */
  static const uint32_t  gpioa_addr =            (d3_ahb1_periph_addr + 0x0000);
  static const uint32_t  gpiob_addr =            (d3_ahb1_periph_addr + 0x0400);
  static const uint32_t  gpioc_addr =            (d3_ahb1_periph_addr + 0x0800);
  static const uint32_t  gpiod_addr =            (d3_ahb1_periph_addr + 0x0C00);
  static const uint32_t  gpioe_addr =            (d3_ahb1_periph_addr + 0x1000);
  static const uint32_t  gpiof_addr =            (d3_ahb1_periph_addr + 0x1400);
  static const uint32_t  gpiog_addr =            (d3_ahb1_periph_addr + 0x1800);
  static const uint32_t  gpioh_addr =            (d3_ahb1_periph_addr + 0x1C00);
  static const uint32_t  gpioi_addr =            (d3_ahb1_periph_addr + 0x2000);
  static const uint32_t  gpioj_addr =            (d3_ahb1_periph_addr + 0x2400);
  static const uint32_t  gpiok_addr =            (d3_ahb1_periph_addr + 0x2800);
  static const uint32_t  rcc_addr =              (d3_ahb1_periph_addr + 0x4400);
  static const uint32_t  rcc_c1_addr =           (rcc_addr + 0x130);
  static const uint32_t  pwr_addr =              (d3_ahb1_periph_addr + 0x4800);
  static const uint32_t  crc_addr =              (d3_ahb1_periph_addr + 0x4C00);
  static const uint32_t  bdma_addr =             (d3_ahb1_periph_addr + 0x5400);
  static const uint32_t  dmamux2_addr =          (d3_ahb1_periph_addr + 0x5800);
  static const uint32_t  adc3_addr =             (d3_ahb1_periph_addr + 0x6000);
  static const uint32_t  adc3_common_addr =      (d3_ahb1_periph_addr + 0x6300);
  static const uint32_t  hsem_addr =             (d3_ahb1_periph_addr + 0x6400);

  /*!< d1_apb1_periph peripherals */
  static const uint32_t  ltdc_addr =             (d1_apb1_periph_addr + 0x1000);
  static const uint32_t  ltdc_layer1_addr =      (ltdc_addr + 0x84);
  static const uint32_t  ltdc_layer2_addr =      (ltdc_addr + 0x104);
  static const uint32_t  wwdg1_addr =            (d1_apb1_periph_addr + 0x3000);

  /*!< d2_apb1_periph peripherals */
  static const uint32_t  tim2_addr =             (d2_apb1_periph_addr + 0x0000);
  static const uint32_t  tim3_addr =             (d2_apb1_periph_addr + 0x0400);
  static const uint32_t  tim4_addr =             (d2_apb1_periph_addr + 0x0800);
  static const uint32_t  tim5_addr =             (d2_apb1_periph_addr + 0x0C00);
  static const uint32_t  tim6_addr =             (d2_apb1_periph_addr + 0x1000);
  static const uint32_t  tim7_addr =             (d2_apb1_periph_addr + 0x1400);
  static const uint32_t  tim12_addr =            (d2_apb1_periph_addr + 0x1800);
  static const uint32_t  tim13_addr =            (d2_apb1_periph_addr + 0x1C00);
  static const uint32_t  tim14_addr =            (d2_apb1_periph_addr + 0x2000);
  static const uint32_t  lptim1_addr =           (d2_apb1_periph_addr + 0x2400);


  static const uint32_t  spi2_addr =             (d2_apb1_periph_addr + 0x3800);
  static const uint32_t  spi3_addr =             (d2_apb1_periph_addr + 0x3C00);
  static const uint32_t  spdifrx_addr =          (d2_apb1_periph_addr + 0x4000);
  static const uint32_t  usart2_addr =           (d2_apb1_periph_addr + 0x4400);
  static const uint32_t  usart3_addr =           (d2_apb1_periph_addr + 0x4800);
  static const uint32_t  uart4_addr =            (d2_apb1_periph_addr + 0x4C00);
  static const uint32_t  uart5_addr =            (d2_apb1_periph_addr + 0x5000);
  static const uint32_t  i2c1_addr =             (d2_apb1_periph_addr + 0x5400);
  static const uint32_t  i2c2_addr =             (d2_apb1_periph_addr + 0x5800);
  static const uint32_t  i2c3_addr =             (d2_apb1_periph_addr + 0x5C00);
  static const uint32_t  cec_addr =              (d2_apb1_periph_addr + 0x6C00);
  static const uint32_t  dac1_addr =             (d2_apb1_periph_addr + 0x7400);
  static const uint32_t  uart7_addr =            (d2_apb1_periph_addr + 0x7800);
  static const uint32_t  uart8_addr =            (d2_apb1_periph_addr + 0x7C00);
  static const uint32_t  csr_addr =              (d2_apb1_periph_addr + 0x8400);
  static const uint32_t  swpmi1_addr =           (d2_apb1_periph_addr + 0x8800);
  static const uint32_t  opamp_addr =            (d2_apb1_periph_addr + 0x9000);
  static const uint32_t  opamp1_addr =           (d2_apb1_periph_addr + 0x9000);
  static const uint32_t  opemp2_addr =           (d2_apb1_periph_addr + 0x9010);
  static const uint32_t  mdios_addr =            (d2_apb1_periph_addr + 0x9400);
  static const uint32_t  fdcan1_addr =           (d2_apb1_periph_addr + 0xA000);
  static const uint32_t  fdcan2_addr =           (d2_apb1_periph_addr + 0xA400);
  static const uint32_t  fdcan_ccu_addr =        (d2_apb1_periph_addr + 0xA800);
  static const uint32_t  sramcan_addr =          (d2_apb1_periph_addr + 0xAC00);

  /*!< d2_apb2_periph peripherals */

  static const uint32_t  tim1_addr =             (d2_apb2_periph_addr + 0x0000);
  static const uint32_t  tim8_addr =             (d2_apb2_periph_addr + 0x0400);
  static const uint32_t  usart1_addr =           (d2_apb2_periph_addr + 0x1000);
  static const uint32_t  usart6_addr =           (d2_apb2_periph_addr + 0x1400);
  static const uint32_t  spi1_addr =             (d2_apb2_periph_addr + 0x3000);
  static const uint32_t  spi4_addr =             (d2_apb2_periph_addr + 0x3400);
  static const uint32_t  tim15_addr =            (d2_apb2_periph_addr + 0x4000);
  static const uint32_t  tim16_addr =            (d2_apb2_periph_addr + 0x4400);
  static const uint32_t  tim17_addr =            (d2_apb2_periph_addr + 0x4800);
  static const uint32_t  spi5_addr =             (d2_apb2_periph_addr + 0x5000);
  static const uint32_t  sai1_addr =             (d2_apb2_periph_addr + 0x5800);
  static const uint32_t  sai1_block_a_addr =     (sai1_addr + 0x004);
  static const uint32_t  sai1_block_b_addr =     (sai1_addr + 0x024);
  static const uint32_t  sai2_addr =             (d2_apb2_periph_addr + 0x5C00);
  static const uint32_t  sai2_block_a_addr =     (sai2_addr + 0x004);
  static const uint32_t  sai2_block_b_addr =     (sai2_addr + 0x024);
  static const uint32_t  sai3_addr =             (d2_apb2_periph_addr + 0x6000);
  static const uint32_t  sai3_block_a_addr =     (sai3_addr + 0x004);
  static const uint32_t  sai3_block_b_addr =     (sai3_addr + 0x024);
  static const uint32_t  dfsdm1_addr =           (d2_apb2_periph_addr + 0x7000);
  static const uint32_t  dfsdm1_channel0_addr =  (dfsdm1_addr + 0x00);
  static const uint32_t  dfsdm1_channel1_addr =  (dfsdm1_addr + 0x20);
  static const uint32_t  dfsdm1_channel2_addr =  (dfsdm1_addr + 0x40);
  static const uint32_t  dfsdm1_channel3_addr =  (dfsdm1_addr + 0x60);
  static const uint32_t  dfsdm1_channel4_addr =  (dfsdm1_addr + 0x80);
  static const uint32_t  dfsdm1_channel5_addr =  (dfsdm1_addr + 0xA0);
  static const uint32_t  dfsdm1_channel6_addr =  (dfsdm1_addr + 0xC0);
  static const uint32_t  dfsdm1_channel7_addr =  (dfsdm1_addr + 0xE0);
  static const uint32_t  dfsdm1_Filter0_addr =   (dfsdm1_addr + 0x100);
  static const uint32_t  dfsdm1_Filter1_addr =   (dfsdm1_addr + 0x180);
  static const uint32_t  dfsdm1_Filter2_addr =   (dfsdm1_addr + 0x200);
  static const uint32_t  dfsdm1_Filter3_addr =   (dfsdm1_addr + 0x280);
  static const uint32_t  hrtim1_addr =           (d2_apb2_periph_addr + 0x7400);
  static const uint32_t  hrtim1_tima_addr =      (hrtim1_addr + 0x00000080);
  static const uint32_t  hrtim1_timb_addr =      (hrtim1_addr + 0x00000100);
  static const uint32_t  hrtim1_timc_addr =      (hrtim1_addr + 0x00000180);
  static const uint32_t  hrtim1_timd_addr =      (hrtim1_addr + 0x00000200);
  static const uint32_t  hrtim1_time_addr =      (hrtim1_addr + 0x00000280);
  static const uint32_t  hrtim1_common_addr =    (hrtim1_addr + 0x00000380);


  /*!< d3_apb1_periph peripherals */
  static const uint32_t  exti_addr =             (d3_apb1_periph_addr + 0x0000);
  static const uint32_t  exti_d1_addr =          (exti_addr + 0x0080);
  static const uint32_t  exti_d2_addr =          (exti_addr + 0x00C0);
  static const uint32_t  syscfg_addr =           (d3_apb1_periph_addr + 0x0400);
  static const uint32_t  lpuart1_addr =          (d3_apb1_periph_addr + 0x0C00);
  static const uint32_t  spi6_addr =             (d3_apb1_periph_addr + 0x1400);
  static const uint32_t  i2c4_addr =             (d3_apb1_periph_addr + 0x1C00);
  static const uint32_t  lptim2_addr =           (d3_apb1_periph_addr + 0x2400);
  static const uint32_t  lptim3_addr =           (d3_apb1_periph_addr + 0x2800);
  static const uint32_t  lptim4_addr =           (d3_apb1_periph_addr + 0x2C00);
  static const uint32_t  lptim5_addr =           (d3_apb1_periph_addr + 0x3000);
  static const uint32_t  comp12_addr =           (d3_apb1_periph_addr + 0x3800);
  static const uint32_t  comp1_addr =            (comp12_addr + 0x0C);
  static const uint32_t  comp2_addr =            (comp12_addr + 0x10);
  static const uint32_t  vrefbuf_addr =          (d3_apb1_periph_addr + 0x3C00);
  static const uint32_t  rtc_addr =              (d3_apb1_periph_addr + 0x4000);
  static const uint32_t  iwdg1_addr =            (d3_apb1_periph_addr + 0x4800);


  static const uint32_t  sai4_addr =             (d3_apb1_periph_addr + 0x5400);
  static const uint32_t  sai4_block_a_addr =     (sai4_addr + 0x004);
  static const uint32_t  sai4_block_b_addr =     (sai4_addr + 0x024);


  static const uint32_t  bdma_channel0_addr =    (bdma_addr + 0x0008);
  static const uint32_t  bdma_channel1_addr =    (bdma_addr + 0x001C);
  static const uint32_t  bdma_channel2_addr =    (bdma_addr + 0x0030);
  static const uint32_t  bdma_channel3_addr =    (bdma_addr + 0x0044);
  static const uint32_t  bdma_channel4_addr =    (bdma_addr + 0x0058);
  static const uint32_t  bdma_channel5_addr =    (bdma_addr + 0x006C);
  static const uint32_t  bdma_channel6_addr =    (bdma_addr + 0x0080);
  static const uint32_t  bdma_channel7_addr =    (bdma_addr + 0x0094);

  static const uint32_t  dmamux2_channel0_addr =    (dmamux2_addr);
  static const uint32_t  dmamux2_channel1_addr =    (dmamux2_addr + 0x0004);
  static const uint32_t  dmamux2_channel2_addr =    (dmamux2_addr + 0x0008);
  static const uint32_t  dmamux2_channel3_addr =    (dmamux2_addr + 0x000C);
  static const uint32_t  dmamux2_channel4_addr =    (dmamux2_addr + 0x0010);
  static const uint32_t  dmamux2_channel5_addr =    (dmamux2_addr + 0x0014);
  static const uint32_t  dmamux2_channel6_addr =    (dmamux2_addr + 0x0018);
  static const uint32_t  dmamux2_channel7_addr =    (dmamux2_addr + 0x001C);

  static const uint32_t  dmamux2_request_generator0_addr =  (dmamux2_addr + 0x0100);
  static const uint32_t  dmamux2_request_generator1_addr =  (dmamux2_addr + 0x0104);
  static const uint32_t  dmamux2_request_generator2_addr =  (dmamux2_addr + 0x0108);
  static const uint32_t  dmamux2_request_generator3_addr =  (dmamux2_addr + 0x010C);
  static const uint32_t  dmamux2_request_generator4_addr =  (dmamux2_addr + 0x0110);
  static const uint32_t  dmamux2_request_generator5_addr =  (dmamux2_addr + 0x0114);
  static const uint32_t  dmamux2_request_generator6_addr =  (dmamux2_addr + 0x0118);
  static const uint32_t  dmamux2_request_generator7_addr =  (dmamux2_addr + 0x011C);

  static const uint32_t  dmamux2_channel_status_addr =      (dmamux2_addr + 0x0080);
  static const uint32_t  dmamux2_request_generator_status_addr =   (dmamux2_addr + 0x0140);

  static const uint32_t  dma1_Stream0_addr =     (dma1_addr + 0x010);
  static const uint32_t  dma1_Stream1_addr =     (dma1_addr + 0x028);
  static const uint32_t  dma1_Stream2_addr =     (dma1_addr + 0x040);
  static const uint32_t  dma1_Stream3_addr =     (dma1_addr + 0x058);
  static const uint32_t  dma1_Stream4_addr =     (dma1_addr + 0x070);
  static const uint32_t  dma1_Stream5_addr =     (dma1_addr + 0x088);
  static const uint32_t  dma1_Stream6_addr =     (dma1_addr + 0x0A0);
  static const uint32_t  dma1_Stream7_addr =     (dma1_addr + 0x0B8);

  static const uint32_t  dma2_Stream0_addr =     (dma2_addr + 0x010);
  static const uint32_t  dma2_Stream1_addr =     (dma2_addr + 0x028);
  static const uint32_t  dma2_Stream2_addr =     (dma2_addr + 0x040);
  static const uint32_t  dma2_Stream3_addr =     (dma2_addr + 0x058);
  static const uint32_t  dma2_Stream4_addr =     (dma2_addr + 0x070);
  static const uint32_t  dma2_Stream5_addr =     (dma2_addr + 0x088);
  static const uint32_t  dma2_Stream6_addr =     (dma2_addr + 0x0A0);
  static const uint32_t  dma2_Stream7_addr =     (dma2_addr + 0x0B8);

  static const uint32_t  dmamux1_channel0_addr =    (dmamux1_addr);
  static const uint32_t  dmamux1_channel1_addr =    (dmamux1_addr + 0x0004);
  static const uint32_t  dmamux1_channel2_addr =    (dmamux1_addr + 0x0008);
  static const uint32_t  dmamux1_channel3_addr =    (dmamux1_addr + 0x000C);
  static const uint32_t  dmamux1_channel4_addr =    (dmamux1_addr + 0x0010);
  static const uint32_t  dmamux1_channel5_addr =    (dmamux1_addr + 0x0014);
  static const uint32_t  dmamux1_channel6_addr =    (dmamux1_addr + 0x0018);
  static const uint32_t  dmamux1_channel7_addr =    (dmamux1_addr + 0x001C);
  static const uint32_t  dmamux1_channel8_addr =    (dmamux1_addr + 0x0020);
  static const uint32_t  dmamux1_channel9_addr =    (dmamux1_addr + 0x0024);
  static const uint32_t  dmamux1_channel10_addr =   (dmamux1_addr + 0x0028);
  static const uint32_t  dmamux1_channel11_addr =   (dmamux1_addr + 0x002C);
  static const uint32_t  dmamux1_channel12_addr =   (dmamux1_addr + 0x0030);
  static const uint32_t  dmamux1_channel13_addr =   (dmamux1_addr + 0x0034);
  static const uint32_t  dmamux1_channel14_addr =   (dmamux1_addr + 0x0038);
  static const uint32_t  dmamux1_channel15_addr =   (dmamux1_addr + 0x003C);

  static const uint32_t  dmamux1_request_generator0_addr =  (dmamux1_addr + 0x0100);
  static const uint32_t  dmamux1_request_generator1_addr =  (dmamux1_addr + 0x0104);
  static const uint32_t  dmamux1_request_generator2_addr =  (dmamux1_addr + 0x0108);
  static const uint32_t  dmamux1_request_generator3_addr =  (dmamux1_addr + 0x010C);
  static const uint32_t  dmamux1_request_generator4_addr =  (dmamux1_addr + 0x0110);
  static const uint32_t  dmamux1_request_generator5_addr =  (dmamux1_addr + 0x0114);
  static const uint32_t  dmamux1_request_generator6_addr =  (dmamux1_addr + 0x0118);
  static const uint32_t  dmamux1_request_generator7_addr =  (dmamux1_addr + 0x011C);

  static const uint32_t  dmamux1_channel_status_addr =      (dmamux1_addr + 0x0080);
  static const uint32_t  dmamux1_request_generator_status_addr =   (dmamux1_addr + 0x0140);

  /*!< FMC Banks registers base  address */
  static const uint32_t  fmc_bank1_r_addr =      (fmc_r_addr + 0x0000);
  static const uint32_t  fmc_bank1E_r_addr =     (fmc_r_addr + 0x0104);
  static const uint32_t  fmc_bank2_r_addr =      (fmc_r_addr + 0x0060);
  static const uint32_t  fmc_bank3_r_addr =      (fmc_r_addr + 0x0080);
  static const uint32_t  fmc_bank5_6_r_addr =    (fmc_r_addr + 0x0140);

  /* Debug MCU registers base address */
  static const uint32_t  dbgmcu_addr =           ((uint32_t )0x5C001000);

  static const uint32_t  mdma_channel0_addr =    (mdma_addr + 0x00000040);
  static const uint32_t  mdma_channel1_addr =    (mdma_addr + 0x00000080);
  static const uint32_t  mdma_channel2_addr =    (mdma_addr + 0x000000C0);
  static const uint32_t  mdma_channel3_addr =    (mdma_addr + 0x00000100);
  static const uint32_t  mdma_channel4_addr =    (mdma_addr + 0x00000140);
  static const uint32_t  mdma_channel5_addr =    (mdma_addr + 0x00000180);
  static const uint32_t  mdma_channel6_addr =    (mdma_addr + 0x000001C0);
  static const uint32_t  mdma_channel7_addr =    (mdma_addr + 0x00000200);
  static const uint32_t  mdma_channel8_addr =    (mdma_addr + 0x00000240);
  static const uint32_t  mdma_channel9_addr =    (mdma_addr + 0x00000280);
  static const uint32_t  mdma_channel10_addr =   (mdma_addr + 0x000002C0);
  static const uint32_t  mdma_channel11_addr =   (mdma_addr + 0x00000300);
  static const uint32_t  mdma_channel12_addr =   (mdma_addr + 0x00000340);
  static const uint32_t  mdma_channel13_addr =   (mdma_addr + 0x00000380);
  static const uint32_t  mdma_channel14_addr =   (mdma_addr + 0x000003C0);
  static const uint32_t  mdma_channel15_addr =   (mdma_addr + 0x00000400);





struct nvic_t : public core_nvic_t
{
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
     fdcan1_it0,
     fdcan2_it0,
     fdcan1_it1,
     fdcan2_it1,
     exti9_5,
     tim1_brk,
     tim1_up,
     tim1_trg_com,
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

     tim8_brk_tim12=43,
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
     fdcan_cal,

     dma2_stream5=68,
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
     otg_fs_ep1_out,
     otg_fs_ep1_in,
     otg_fs_wkup,
     otg_fs,
     dmamux1_ovr,
     hrtim1_master,
     hrtim1_tima,
     hrtim1_timb,
     hrtim1_timc,
     hrtim1_timd,
     hrtim1_time,
     hrtim1_flt,
     dfsdm1_flt0,
     dfsdm1_flt1,
     dfsdm1_flt2,
     dfsdm1_flt3,
     sai3,
     swpmi1,
     tim15,
     tim16,
     tim17,
     msios_wkup,
     mdios,
     jpeg,
     mdma,

     sdmmc2=124,
     hsem1,

     adc3=127,
     dmamux2_ovr,
     bdma_channel0,
     bdma_channel1,
     bdma_channel2,
     bdma_channel3,
     bdma_channel4,
     bdma_channel5,
     bdma_channel6,
     bdma_channel7,
     comp,
     lptim2,
     lptim3,
     lptim4,
     lptim5,
     lpuart1,
     wwdg_reset,
     crs,
     ramecc,
     sai4,
     wkup_pin=149
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
  MAKE_NVIC_IRQ_ITEM(fdcan1_it0)
  MAKE_NVIC_IRQ_ITEM(fdcan2_it0)
  MAKE_NVIC_IRQ_ITEM(fdcan1_it1)
  MAKE_NVIC_IRQ_ITEM(fdcan2_it1)
  MAKE_NVIC_IRQ_ITEM(exti9_5)
  MAKE_NVIC_IRQ_ITEM(tim1_brk)
  MAKE_NVIC_IRQ_ITEM(tim1_up)
  MAKE_NVIC_IRQ_ITEM(tim1_trg_com)
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
  MAKE_NVIC_IRQ_ITEM(fdcan_cal)
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
  MAKE_NVIC_IRQ_ITEM(otg_fs_ep1_out)
  MAKE_NVIC_IRQ_ITEM(otg_fs_ep1_in)
  MAKE_NVIC_IRQ_ITEM(otg_fs_wkup)
  MAKE_NVIC_IRQ_ITEM(otg_fs)
  MAKE_NVIC_IRQ_ITEM(dmamux1_ovr)
  MAKE_NVIC_IRQ_ITEM(hrtim1_master)
  MAKE_NVIC_IRQ_ITEM(hrtim1_tima)
  MAKE_NVIC_IRQ_ITEM(hrtim1_timb)
  MAKE_NVIC_IRQ_ITEM(hrtim1_timc)
  MAKE_NVIC_IRQ_ITEM(hrtim1_timd)
  MAKE_NVIC_IRQ_ITEM(hrtim1_time)
  MAKE_NVIC_IRQ_ITEM(hrtim1_flt)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt0)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt1)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt2)
  MAKE_NVIC_IRQ_ITEM(dfsdm1_flt3)
  MAKE_NVIC_IRQ_ITEM(sai3)
  MAKE_NVIC_IRQ_ITEM(swpmi1)
  MAKE_NVIC_IRQ_ITEM(tim15)
  MAKE_NVIC_IRQ_ITEM(tim16)
  MAKE_NVIC_IRQ_ITEM(tim17)
  MAKE_NVIC_IRQ_ITEM(msios_wkup)
  MAKE_NVIC_IRQ_ITEM(mdios)
  MAKE_NVIC_IRQ_ITEM(jpeg)
  MAKE_NVIC_IRQ_ITEM(mdma)
  MAKE_NVIC_IRQ_ITEM(sdmmc2)
  MAKE_NVIC_IRQ_ITEM(hsem1)
  MAKE_NVIC_IRQ_ITEM(adc3)
  MAKE_NVIC_IRQ_ITEM(dmamux2_ovr)
  MAKE_NVIC_IRQ_ITEM(bdma_channel0)
  MAKE_NVIC_IRQ_ITEM(bdma_channel1)
  MAKE_NVIC_IRQ_ITEM(bdma_channel2)
  MAKE_NVIC_IRQ_ITEM(bdma_channel3)
  MAKE_NVIC_IRQ_ITEM(bdma_channel4)
  MAKE_NVIC_IRQ_ITEM(bdma_channel5)
  MAKE_NVIC_IRQ_ITEM(bdma_channel6)
  MAKE_NVIC_IRQ_ITEM(bdma_channel7)
  MAKE_NVIC_IRQ_ITEM(comp)
  MAKE_NVIC_IRQ_ITEM(lptim2)
  MAKE_NVIC_IRQ_ITEM(lptim3)
  MAKE_NVIC_IRQ_ITEM(lptim4)
  MAKE_NVIC_IRQ_ITEM(lptim5)
  MAKE_NVIC_IRQ_ITEM(lpuart1)
  MAKE_NVIC_IRQ_ITEM(wwdg_reset)
  MAKE_NVIC_IRQ_ITEM(crs)
  MAKE_NVIC_IRQ_ITEM(ramecc)
  MAKE_NVIC_IRQ_ITEM(sai4)
  MAKE_NVIC_IRQ_ITEM(wkup_pin)
};

static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало c уровня ниже(cm7_core) для биндинга в stm32h7::nvic_t
}


#include "rcc++.h"
/*
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
*/
namespace stm32h7
{

  extern const rcc_t::system_init_profile_t& system_init_profile ;

#if 0
  typedef struct
  {
    __IO uint32_t ISR;              /*!< ADC Interrupt and Status Register,                 Address offset: 0x00 */
    __IO uint32_t IER;              /*!< ADC Interrupt Enable Register,                     Address offset: 0x04 */
    __IO uint32_t CR;               /*!< ADC control register,                              Address offset: 0x08 */
    __IO uint32_t CFGR;             /*!< ADC Configuration register,                        Address offset: 0x0C */
    __IO uint32_t CFGR2;            /*!< ADC Configuration register 2,                      Address offset: 0x10 */
    __IO uint32_t SMPR1;            /*!< ADC sample time register 1,                        Address offset: 0x14 */
    __IO uint32_t SMPR2;            /*!< ADC sample time register 2,                        Address offset: 0x18 */
    __IO uint32_t PCSEL;            /*!< ADC pre-channel selection,                         Address offset: 0x1C */
    __IO uint32_t LTR1;             /*!< ADC watchdog Lower threshold register 1,           Address offset: 0x20 */
    __IO uint32_t HTR1;             /*!< ADC watchdog higher threshold register 1,          Address offset: 0x24 */
    uint32_t      RESERVED1;        /*!< Reserved, 0x028                                                         */
    uint32_t      RESERVED2;        /*!< Reserved, 0x02C                                                         */
    __IO uint32_t SQR1;             /*!< ADC regular sequence register 1,                   Address offset: 0x30 */
    __IO uint32_t SQR2;             /*!< ADC regular sequence register 2,                   Address offset: 0x34 */
    __IO uint32_t SQR3;             /*!< ADC regular sequence register 3,                   Address offset: 0x38 */
    __IO uint32_t SQR4;             /*!< ADC regular sequence register 4,                   Address offset: 0x3C */
    __IO uint32_t DR;               /*!< ADC regular data register,                         Address offset: 0x40 */
    uint32_t      RESERVED3;        /*!< Reserved, 0x044                                                         */
    uint32_t      RESERVED4;        /*!< Reserved, 0x048                                                         */
    __IO uint32_t JSQR;             /*!< ADC injected sequence register,                    Address offset: 0x4C */
    uint32_t      RESERVED5[4];     /*!< Reserved, 0x050 - 0x05C                                                 */
    __IO uint32_t OFR1;             /*!< ADC offset register 1,                             Address offset: 0x60 */
    __IO uint32_t OFR2;             /*!< ADC offset register 2,                             Address offset: 0x64 */
    __IO uint32_t OFR3;             /*!< ADC offset register 3,                             Address offset: 0x68 */
    __IO uint32_t OFR4;             /*!< ADC offset register 4,                             Address offset: 0x6C */
    uint32_t      RESERVED6[4];     /*!< Reserved, 0x070 - 0x07C                                                 */
    __IO uint32_t JDR1;             /*!< ADC injected data register 1,                      Address offset: 0x80 */
    __IO uint32_t JDR2;             /*!< ADC injected data register 2,                      Address offset: 0x84 */
    __IO uint32_t JDR3;             /*!< ADC injected data register 3,                      Address offset: 0x88 */
    __IO uint32_t JDR4;             /*!< ADC injected data register 4,                      Address offset: 0x8C */
    uint32_t      RESERVED7[4];     /*!< Reserved, 0x090 - 0x09C                                                 */
    __IO uint32_t AWD2CR;           /*!< ADC  Analog Watchdog 2 Configuration Register,     Address offset: 0xA0 */
    __IO uint32_t AWD3CR;           /*!< ADC  Analog Watchdog 3 Configuration Register,     Address offset: 0xA4 */
    uint32_t      RESERVED8;        /*!< Reserved, 0x0A8                                                         */
    uint32_t      RESERVED9;        /*!< Reserved, 0x0AC                                                         */
    __IO uint32_t LTR2;             /*!< ADC watchdog Lower threshold register 2,           Address offset: 0xB0 */
    __IO uint32_t HTR2;             /*!< ADC watchdog Higher threshold register 2,          Address offset: 0xB4 */
    __IO uint32_t LTR3;             /*!< ADC watchdog Lower threshold register 3,           Address offset: 0xB8 */
    __IO uint32_t HTR3;             /*!< ADC watchdog Higher threshold register 3,          Address offset: 0xBC */
    __IO uint32_t DIFSEL;           /*!< ADC  Differential Mode Selection Register,         Address offset: 0xC0 */
    __IO uint32_t CALFACT;          /*!< ADC  Calibration Factors,                          Address offset: 0xC4 */
    __IO uint32_t CALFACT2;         /*!< ADC  Linearity Calibration Factors,                Address offset: 0xC8 */
  } ADC_TypeDef;


  typedef struct
  {
  __IO uint32_t CSR; /*!< ADC Common status register, Address offset: ADC1/3 base address + 0x300 */
  uint32_t RESERVED; /*!< Reserved, ADC1/3 base address + 0x304 */
  __IO uint32_t CCR; /*!< ADC common control register, Address offset: ADC1/3 base address + 0x308 */
  __IO uint32_t CDR; /*!< ADC common regular data register for dual Address offset: ADC1/3 base address + 0x30C */
  __IO uint32_t CDR2; /*!< ADC common regular data register for 32-bit dual mode Address offset: ADC1/3 base address + 0x310 */

  } ADC_Common_TypeDef;

  /**
    * @brief VREFBUF
    */

  typedef struct
  {
    __IO uint32_t CSR;         /*!< VREFBUF control and status register,         Address offset: 0x00 */
    __IO uint32_t CCR;         /*!< VREFBUF calibration and control register,    Address offset: 0x04 */
  } VREFBUF_TypeDef;


  /**
    * @brief FD Controller Area Network
    */

  typedef struct
  {
    __IO uint32_t CREL;         /*!< FDCAN Core Release register,                                     Address offset: 0x000 */
    __IO uint32_t ENDN;         /*!< FDCAN Endian register,                                           Address offset: 0x004 */
    __IO uint32_t RESERVED1;    /*!< Reserved,                                                                        0x008 */
    __IO uint32_t DBTP;         /*!< FDCAN Data Bit Timing & Prescaler register,                      Address offset: 0x00C */
    __IO uint32_t TEST;         /*!< FDCAN Test register,                                             Address offset: 0x010 */
    __IO uint32_t RWD;          /*!< FDCAN RAM Watchdog register,                                     Address offset: 0x014 */
    __IO uint32_t CCCR;         /*!< FDCAN CC Control register,                                       Address offset: 0x018 */
    __IO uint32_t NBTP;         /*!< FDCAN Nominal Bit Timing & Prescaler register,                   Address offset: 0x01C */
    __IO uint32_t TSCC;         /*!< FDCAN Timestamp Counter Configuration register,                  Address offset: 0x020 */
    __IO uint32_t TSCV;         /*!< FDCAN Timestamp Counter Value register,                          Address offset: 0x024 */
    __IO uint32_t TOCC;         /*!< FDCAN Timeout Counter Configuration register,                    Address offset: 0x028 */
    __IO uint32_t TOCV;         /*!< FDCAN Timeout Counter Value register,                            Address offset: 0x02C */
    __IO uint32_t RESERVED2[4]; /*!< Reserved,                                                                0x030 - 0x03C */
    __IO uint32_t ECR;          /*!< FDCAN Error Counter register,                                    Address offset: 0x040 */
    __IO uint32_t PSR;          /*!< FDCAN Protocol Status register,                                  Address offset: 0x044 */
    __IO uint32_t TDCR;         /*!< FDCAN Transmitter Delay Compensation register,                   Address offset: 0x048 */
    __IO uint32_t RESERVED3;    /*!< Reserved,                                                                        0x04C */
    __IO uint32_t IR;           /*!< FDCAN Interrupt register,                                        Address offset: 0x050 */
    __IO uint32_t IE;           /*!< FDCAN Interrupt Enable register,                                 Address offset: 0x054 */
    __IO uint32_t ILS;          /*!< FDCAN Interrupt Line Select register,                            Address offset: 0x058 */
    __IO uint32_t ILE;          /*!< FDCAN Interrupt Line Enable register,                            Address offset: 0x05C */
    __IO uint32_t RESERVED4[8]; /*!< Reserved,                                                                0x060 - 0x07C */
    __IO uint32_t GFC;          /*!< FDCAN Global Filter Configuration register,                      Address offset: 0x080 */
    __IO uint32_t SIDFC;        /*!< FDCAN Standard ID Filter Configuration register,                 Address offset: 0x084 */
    __IO uint32_t XIDFC;        /*!< FDCAN Extended ID Filter Configuration register,                 Address offset: 0x088 */
    __IO uint32_t RESERVED5;    /*!< Reserved,                                                                        0x08C */
    __IO uint32_t XIDAM;        /*!< FDCAN Extended ID AND Mask register,                             Address offset: 0x090 */
    __IO uint32_t HPMS;         /*!< FDCAN High Priority Message Status register,                     Address offset: 0x094 */
    __IO uint32_t NDAT1;        /*!< FDCAN New Data 1 register,                                       Address offset: 0x098 */
    __IO uint32_t NDAT2;        /*!< FDCAN New Data 2 register,                                       Address offset: 0x09C */
    __IO uint32_t RXF0C;        /*!< FDCAN Rx FIFO 0 Configuration register,                          Address offset: 0x0A0 */
    __IO uint32_t RXF0S;        /*!< FDCAN Rx FIFO 0 Status register,                                 Address offset: 0x0A4 */
    __IO uint32_t RXF0A;        /*!< FDCAN Rx FIFO 0 Acknowledge register,                            Address offset: 0x0A8 */
    __IO uint32_t RXBC;         /*!< FDCAN Rx Buffer Configuration register,                          Address offset: 0x0AC */
    __IO uint32_t RXF1C;        /*!< FDCAN Rx FIFO 1 Configuration register,                          Address offset: 0x0B0 */
    __IO uint32_t RXF1S;        /*!< FDCAN Rx FIFO 1 Status register,                                 Address offset: 0x0B4 */
    __IO uint32_t RXF1A;        /*!< FDCAN Rx FIFO 1 Acknowledge register,                            Address offset: 0x0B8 */
    __IO uint32_t RXESC;        /*!< FDCAN Rx Buffer/FIFO Element Size Configuration register,        Address offset: 0x0BC */
    __IO uint32_t TXBC;         /*!< FDCAN Tx Buffer Configuration register,                          Address offset: 0x0C0 */
    __IO uint32_t TXFQS;        /*!< FDCAN Tx FIFO/Queue Status register,                             Address offset: 0x0C4 */
    __IO uint32_t TXESC;        /*!< FDCAN Tx Buffer Element Size Configuration register,             Address offset: 0x0C8 */
    __IO uint32_t TXBRP;        /*!< FDCAN Tx Buffer Request Pending register,                        Address offset: 0x0CC */
    __IO uint32_t TXBAR;        /*!< FDCAN Tx Buffer Add Request register,                            Address offset: 0x0D0 */
    __IO uint32_t TXBCR;        /*!< FDCAN Tx Buffer Cancellation Request register,                   Address offset: 0x0D4 */
    __IO uint32_t TXBTO;        /*!< FDCAN Tx Buffer Transmission Occurred register,                  Address offset: 0x0D8 */
    __IO uint32_t TXBCF;        /*!< FDCAN Tx Buffer Cancellation Finished register,                  Address offset: 0x0DC */
    __IO uint32_t TXBTIE;       /*!< FDCAN Tx Buffer Transmission Interrupt Enable register,          Address offset: 0x0E0 */
    __IO uint32_t TXBCIE;       /*!< FDCAN Tx Buffer Cancellation Finished Interrupt Enable register, Address offset: 0x0E4 */
    __IO uint32_t RESERVED6[2]; /*!< Reserved,                                                                0x0E8 - 0x0EC */
    __IO uint32_t TXEFC;        /*!< FDCAN Tx Event FIFO Configuration register,                      Address offset: 0x0F0 */
    __IO uint32_t TXEFS;        /*!< FDCAN Tx Event FIFO Status register,                             Address offset: 0x0F4 */
    __IO uint32_t TXEFA;        /*!< FDCAN Tx Event FIFO Acknowledge register,                        Address offset: 0x0F8 */
    __IO uint32_t RESERVED7;    /*!< Reserved,                                                                        0x0FC */
  } FDCAN_GlobalTypeDef;

  /**
    * @brief TTFD Controller Area Network
    */

  typedef struct
  {
    __IO uint32_t TTTMC;          /*!< TT Trigger Memory Configuration register,    Address offset: 0x100 */
    __IO uint32_t TTRMC;          /*!< TT Reference Message Configuration register, Address offset: 0x104 */
    __IO uint32_t TTOCF;          /*!< TT Operation Configuration register,         Address offset: 0x108 */
    __IO uint32_t TTMLM;          /*!< TT Matrix Limits register,                   Address offset: 0x10C */
    __IO uint32_t TURCF;          /*!< TUR Configuration register,                  Address offset: 0x110 */
    __IO uint32_t TTOCN;          /*!< TT Operation Control register,               Address offset: 0x114 */
    __IO uint32_t TTGTP;          /*!< TT Global Time Preset register,              Address offset: 0x118 */
    __IO uint32_t TTTMK;          /*!< TT Time Mark register,                       Address offset: 0x11C */
    __IO uint32_t TTIR;           /*!< TT Interrupt register,                       Address offset: 0x120 */
    __IO uint32_t TTIE;           /*!< TT Interrupt Enable register,                Address offset: 0x124 */
    __IO uint32_t TTILS;          /*!< TT Interrupt Line Select register,           Address offset: 0x128 */
    __IO uint32_t TTOST;          /*!< TT Operation Status register,                Address offset: 0x12C */
    __IO uint32_t TURNA;          /*!< TT TUR Numerator Actual register,            Address offset: 0x130 */
    __IO uint32_t TTLGT;          /*!< TT Local and Global Time register,           Address offset: 0x134 */
    __IO uint32_t TTCTC;          /*!< TT Cycle Time and Count register,            Address offset: 0x138 */
    __IO uint32_t TTCPT;          /*!< TT Capture Time register,                    Address offset: 0x13C */
    __IO uint32_t TTCSM;          /*!< TT Cycle Sync Mark register,                 Address offset: 0x140 */
    __IO uint32_t RESERVED1[111]; /*!< Reserved,                                            0x144 - 0x2FC */
    __IO uint32_t TTTS;           /*!< TT Trigger Select register,                  Address offset: 0x300 */
  } TTCAN_TypeDef;

  /**
    * @brief FD Controller Area Network
    */

  typedef struct
  {
    __IO uint32_t CREL;  /*!< Clock Calibration Unit Core Release register, Address offset: 0x00 */
    __IO uint32_t CCFG;  /*!< Calibration Configuration register,           Address offset: 0x04 */
    __IO uint32_t CSTAT; /*!< Calibration Status register,                  Address offset: 0x08 */
    __IO uint32_t CWD;   /*!< Calibration Watchdog register,                Address offset: 0x0C */
    __IO uint32_t IR;    /*!< CCU Interrupt register,                       Address offset: 0x10 */
    __IO uint32_t IE;    /*!< CCU Interrupt Enable register,                Address offset: 0x14 */
  } FDCAN_ClockCalibrationUnit_TypeDef;


  /**
    * @brief Consumer Electronics Control
    */

  typedef struct
  {
    __IO uint32_t CR;           /*!< CEC control register,              Address offset:0x00 */
    __IO uint32_t CFGR;         /*!< CEC configuration register,        Address offset:0x04 */
    __IO uint32_t TXDR;         /*!< CEC Tx data register ,             Address offset:0x08 */
    __IO uint32_t RXDR;         /*!< CEC Rx Data Register,              Address offset:0x0C */
    __IO uint32_t ISR;          /*!< CEC Interrupt and Status Register, Address offset:0x10 */
    __IO uint32_t IER;          /*!< CEC interrupt enable register,     Address offset:0x14 */
  }CEC_TypeDef;

  /**
    * @brief CRC calculation unit
    */

  typedef struct
  {
    __IO uint32_t DR;          /*!< CRC Data register,                           Address offset: 0x00 */
    __IO uint32_t IDR;         /*!< CRC Independent data register,               Address offset: 0x04 */
    __IO uint32_t CR;          /*!< CRC Control register,                        Address offset: 0x08 */
    uint32_t      RESERVED2;   /*!< Reserved,                                                    0x0C */
    __IO uint32_t INIT;        /*!< Initial CRC value register,                  Address offset: 0x10 */
    __IO uint32_t POL;         /*!< CRC polynomial register,                     Address offset: 0x14 */
  } CRC_TypeDef;


  /**
    * @brief Clock Recovery System
    */
  typedef struct
  {
  __IO uint32_t CR;            /*!< CRS ccontrol register,              Address offset: 0x00 */
  __IO uint32_t CFGR;          /*!< CRS configuration register,         Address offset: 0x04 */
  __IO uint32_t ISR;           /*!< CRS interrupt and status register,  Address offset: 0x08 */
  __IO uint32_t ICR;           /*!< CRS interrupt flag clear register,  Address offset: 0x0C */
  } CRS_TypeDef;


  /**
    * @brief Digital to Analog Converter
    */

  typedef struct
  {
    __IO uint32_t CR;       /*!< DAC control register,                                    Address offset: 0x00 */
    __IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
    __IO uint32_t DHR12R1;  /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
    __IO uint32_t DHR12L1;  /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
    __IO uint32_t DHR8R1;   /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
    __IO uint32_t DHR12R2;  /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
    __IO uint32_t DHR12L2;  /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
    __IO uint32_t DHR8R2;   /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
    __IO uint32_t DHR12RD;  /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
    __IO uint32_t DHR12LD;  /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
    __IO uint32_t DHR8RD;   /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
    __IO uint32_t DOR1;     /*!< DAC channel1 data output register,                       Address offset: 0x2C */
    __IO uint32_t DOR2;     /*!< DAC channel2 data output register,                       Address offset: 0x30 */
    __IO uint32_t SR;       /*!< DAC status register,                                     Address offset: 0x34 */
    __IO uint32_t CCR;      /*!< DAC calibration control register,                        Address offset: 0x38 */
    __IO uint32_t MCR;      /*!< DAC mode control register,                               Address offset: 0x3C */
    __IO uint32_t SHSR1;    /*!< DAC Sample and Hold sample time register 1,              Address offset: 0x40 */
    __IO uint32_t SHSR2;    /*!< DAC Sample and Hold sample time register 2,              Address offset: 0x44 */
    __IO uint32_t SHHR;     /*!< DAC Sample and Hold hold time register,                  Address offset: 0x48 */
    __IO uint32_t SHRR;     /*!< DAC Sample and Hold refresh time register,               Address offset: 0x4C */
  } DAC_TypeDef;

  /**
    * @brief DFSDM module registers
    */
  typedef struct
  {
    __IO uint32_t FLTCR1;          /*!< DFSDM control register1,                          Address offset: 0x100 */
    __IO uint32_t FLTCR2;          /*!< DFSDM control register2,                          Address offset: 0x104 */
    __IO uint32_t FLTISR;          /*!< DFSDM interrupt and status register,              Address offset: 0x108 */
    __IO uint32_t FLTICR;          /*!< DFSDM interrupt flag clear register,              Address offset: 0x10C */
    __IO uint32_t FLTJCHGR;        /*!< DFSDM injected channel group selection register,  Address offset: 0x110 */
    __IO uint32_t FLTFCR;          /*!< DFSDM filter control register,                    Address offset: 0x114 */
    __IO uint32_t FLTJDATAR;       /*!< DFSDM data register for injected group,           Address offset: 0x118 */
    __IO uint32_t FLTRDATAR;       /*!< DFSDM data register for regular group,            Address offset: 0x11C */
    __IO uint32_t FLTAWHTR;        /*!< DFSDM analog watchdog high threshold register,    Address offset: 0x120 */
    __IO uint32_t FLTAWLTR;        /*!< DFSDM analog watchdog low threshold register,     Address offset: 0x124 */
    __IO uint32_t FLTAWSR;         /*!< DFSDM analog watchdog status register             Address offset: 0x128 */
    __IO uint32_t FLTAWCFR;        /*!< DFSDM analog watchdog clear flag register         Address offset: 0x12C */
    __IO uint32_t FLTEXMAX;        /*!< DFSDM extreme detector maximum register,          Address offset: 0x130 */
    __IO uint32_t FLTEXMIN;        /*!< DFSDM extreme detector minimum register           Address offset: 0x134 */
    __IO uint32_t FLTCNVTIMR;      /*!< DFSDM conversion timer,                           Address offset: 0x138 */
  } DFSDM_Filter_TypeDef;

  /**
    * @brief DFSDM channel configuration registers
    */
  typedef struct
  {
    __IO uint32_t CHCFGR1;      /*!< DFSDM channel configuration register1,            Address offset: 0x00 */
    __IO uint32_t CHCFGR2;      /*!< DFSDM channel configuration register2,            Address offset: 0x04 */
    __IO uint32_t CHAWSCDR;     /*!< DFSDM channel analog watchdog and
                                     short circuit detector register,                  Address offset: 0x08 */
    __IO uint32_t CHWDATAR;     /*!< DFSDM channel watchdog filter data register,      Address offset: 0x0C */
    __IO uint32_t CHDATINR;     /*!< DFSDM channel data input register,                Address offset: 0x10 */
  } DFSDM_Channel_TypeDef;

  /**
    * @brief Debug MCU
    */

  typedef struct
  {
    __IO uint32_t IDCODE;        /*!< MCU device ID code,                     Address offset: 0x00 */
    __IO uint32_t CR;            /*!< Debug MCU configuration register,       Address offset: 0x04 */
    uint32_t RESERVED4[11];      /*!< Reserved,                             Address offset: 0x08 */
    __IO uint32_t APB3FZ1;     /*!< Debug MCU APB3FZ1 freeze register,    Address offset: 0x34 */
    uint32_t RESERVED5;          /*!< Reserved,                             Address offset: 0x38 */
    __IO uint32_t APB1LFZ1;    /*!< Debug MCU APB1LFZ1 freeze register,   Address offset: 0x3C */
    uint32_t RESERVED6;          /*!< Reserved,                             Address offset: 0x40 */
    __IO uint32_t APB1HFZ1;    /*!< Debug MCU APB1LFZ1 freeze register,   Address offset: 0x44 */
    uint32_t RESERVED7;          /*!< Reserved,                             Address offset: 0x48 */
    __IO uint32_t APB2FZ1;     /*!< Debug MCU APB2FZ1 freeze register,    Address offset: 0x4C */
    uint32_t RESERVED8;          /*!< Reserved,                             Address offset: 0x50 */
    __IO uint32_t APB4FZ1;     /*!< Debug MCU APB4FZ1 freeze register,    Address offset: 0x54 */
  }DBGMCU_TypeDef;

  /**
    * @brief DCMI
    */

  typedef struct
  {
    __IO uint32_t CR;       /*!< DCMI control register 1,                       Address offset: 0x00 */
    __IO uint32_t SR;       /*!< DCMI status register,                          Address offset: 0x04 */
    __IO uint32_t RISR;     /*!< DCMI raw interrupt status register,            Address offset: 0x08 */
    __IO uint32_t IER;      /*!< DCMI interrupt enable register,                Address offset: 0x0C */
    __IO uint32_t MISR;     /*!< DCMI masked interrupt status register,         Address offset: 0x10 */
    __IO uint32_t ICR;      /*!< DCMI interrupt clear register,                 Address offset: 0x14 */
    __IO uint32_t ESCR;     /*!< DCMI embedded synchronization code register,   Address offset: 0x18 */
    __IO uint32_t ESUR;     /*!< DCMI embedded synchronization unmask register, Address offset: 0x1C */
    __IO uint32_t CWSTRTR;  /*!< DCMI crop window start,                        Address offset: 0x20 */
    __IO uint32_t CWSIZER;  /*!< DCMI crop window size,                         Address offset: 0x24 */
    __IO uint32_t DR;       /*!< DCMI data register,                            Address offset: 0x28 */
  } DCMI_TypeDef;

  /**
    * @brief dma Controller
    */

  typedef struct
  {
    __IO uint32_t CR;     /*!< dma stream x configuration register      */
    __IO uint32_t NDTR;   /*!< dma stream x number of data register     */
    __IO uint32_t PAR;    /*!< dma stream x peripheral address register */
    __IO uint32_t M0AR;   /*!< dma stream x memory 0 address register   */
    __IO uint32_t M1AR;   /*!< dma stream x memory 1 address register   */
    __IO uint32_t FCR;    /*!< dma stream x FIFO control register       */
  } dma_Stream_TypeDef;

  typedef struct
  {
    __IO uint32_t LISR;   /*!< dma low interrupt status register,      Address offset: 0x00 */
    __IO uint32_t HISR;   /*!< dma high interrupt status register,     Address offset: 0x04 */
    __IO uint32_t LIFCR;  /*!< dma low interrupt flag clear register,  Address offset: 0x08 */
    __IO uint32_t HIFCR;  /*!< dma high interrupt flag clear register, Address offset: 0x0C */
  } dma_TypeDef;

  typedef struct
  {
    __IO uint32_t CCR;          /*!< dma channel x configuration register        */
    __IO uint32_t CNDTR;        /*!< dma channel x number of data register       */
    __IO uint32_t CPAR;         /*!< dma channel x peripheral address register   */
    __IO uint32_t CMAR;         /*!< dma channel x memory address register       */
  } Bdma_Channel_TypeDef;

  typedef struct
  {
    __IO uint32_t ISR;          /*!< dma interrupt status register,               Address offset: 0x00 */
    __IO uint32_t IFCR;         /*!< dma interrupt flag clear register,           Address offset: 0x04 */
  } Bdma_TypeDef;

  typedef struct
  {
    __IO uint32_t  CCR;        /*!< dma Multiplexer Channel x Control Register   */
  }dmaMUX_Channel_TypeDef;

  typedef struct
  {
    __IO uint32_t  CSR;      /*!< dma Channel Status Register     */
    __IO uint32_t  CFR;      /*!< dma Channel Clear Flag Register */
  }dmaMUX_ChannelStatus_TypeDef;

  typedef struct
  {
    __IO uint32_t  RGCR;        /*!< dma Request Generator x Control Register   */
  }dmaMUX_RequestGen_TypeDef;

  typedef struct
  {
    __IO uint32_t  RGSR;        /*!< dma Request Generator Status Register       */
    __IO uint32_t  RGCFR;       /*!< dma Request Generator Clear Flag Register   */
  }dmaMUX_RequestGenStatus_TypeDef;

  /**
    * @brief Mdma Controller
    */
  typedef struct
  {
    __IO uint32_t  GISR0;   /*!< Mdma Global Interrupt/Status Register 0,          Address offset: 0x00 */
  }Mdma_TypeDef;

  typedef struct
  {
    __IO uint32_t  CISR;      /*!< Mdma channel x interrupt/status register,             Address offset: 0x40 */
    __IO uint32_t  CIFCR;     /*!< Mdma channel x interrupt flag clear register,         Address offset: 0x44 */
    __IO uint32_t  CESR;      /*!< Mdma Channel x error status register,                 Address offset: 0x48 */
    __IO uint32_t  CCR;       /*!< Mdma channel x control register,                      Address offset: 0x4C */
    __IO uint32_t  CTCR;      /*!< Mdma channel x Transfer Configuration register,       Address offset: 0x50 */
    __IO uint32_t  CBNDTR;    /*!< Mdma Channel x block number of data register,         Address offset: 0x54 */
    __IO uint32_t  CSAR;      /*!< Mdma channel x source address register,               Address offset: 0x58 */
    __IO uint32_t  CDAR;      /*!< Mdma channel x destination address register,          Address offset: 0x5C */
    __IO uint32_t  CBRUR;     /*!< Mdma channel x Block Repeat address Update register,  Address offset: 0x60 */
    __IO uint32_t  CLAR;      /*!< Mdma channel x Link Address register,                 Address offset: 0x64 */
    __IO uint32_t  CTBR;      /*!< Mdma channel x Trigger and Bus selection Register,    Address offset: 0x68 */
    uint32_t       RESERVED0; /*!< Reserved, 0x68                                                             */
   __IO uint32_t    CMAR;      /*!< Mdma channel x Mask address register,                Address offset: 0x70 */
   __IO uint32_t   CMDR;       /*!< Mdma channel x Mask Data register,                   Address offset: 0x74 */
  }Mdma_Channel_TypeDef;
  /**
    * @brief dma2D Controller
    */

  typedef struct
  {
    __IO uint32_t CR;            /*!< dma2D Control Register,                         Address offset: 0x00 */
    __IO uint32_t ISR;           /*!< dma2D Interrupt Status Register,                Address offset: 0x04 */
    __IO uint32_t IFCR;          /*!< dma2D Interrupt Flag Clear Register,            Address offset: 0x08 */
    __IO uint32_t FGMAR;         /*!< dma2D Foreground Memory Address Register,       Address offset: 0x0C */
    __IO uint32_t FGOR;          /*!< dma2D Foreground Offset Register,               Address offset: 0x10 */
    __IO uint32_t BGMAR;         /*!< dma2D Background Memory Address Register,       Address offset: 0x14 */
    __IO uint32_t BGOR;          /*!< dma2D Background Offset Register,               Address offset: 0x18 */
    __IO uint32_t FGPFCCR;       /*!< dma2D Foreground PFC Control Register,          Address offset: 0x1C */
    __IO uint32_t FGCOLR;        /*!< dma2D Foreground Color Register,                Address offset: 0x20 */
    __IO uint32_t BGPFCCR;       /*!< dma2D Background PFC Control Register,          Address offset: 0x24 */
    __IO uint32_t BGCOLR;        /*!< dma2D Background Color Register,                Address offset: 0x28 */
    __IO uint32_t FGCMAR;        /*!< dma2D Foreground CLUT Memory Address Register,  Address offset: 0x2C */
    __IO uint32_t BGCMAR;        /*!< dma2D Background CLUT Memory Address Register,  Address offset: 0x30 */
    __IO uint32_t OPFCCR;        /*!< dma2D Output PFC Control Register,              Address offset: 0x34 */
    __IO uint32_t OCOLR;         /*!< dma2D Output Color Register,                    Address offset: 0x38 */
    __IO uint32_t OMAR;          /*!< dma2D Output Memory Address Register,           Address offset: 0x3C */
    __IO uint32_t OOR;           /*!< dma2D Output Offset Register,                   Address offset: 0x40 */
    __IO uint32_t NLR;           /*!< dma2D Number of Line Register,                  Address offset: 0x44 */
    __IO uint32_t LWR;           /*!< dma2D Line Watermark Register,                  Address offset: 0x48 */
    __IO uint32_t AMTCR;         /*!< dma2D AHB Master Timer Configuration Register,  Address offset: 0x4C */
    uint32_t      RESERVED[236]; /*!< Reserved, 0x50-0x3FF */
    __IO uint32_t FGCLUT[256];   /*!< dma2D Foreground CLUT,                          Address offset:400-7FF */
    __IO uint32_t BGCLUT[256];   /*!< dma2D Background CLUT,                          Address offset:800-BFF */
  } dma2D_TypeDef;

  /**
    * @brief Ethernet MAC
    */
  typedef struct
  {
    __IO uint32_t MACCR;
    __IO uint32_t MACECR;
    __IO uint32_t MACPFR;
    __IO uint32_t MACWTR;
    __IO uint32_t MACHT0R;
    __IO uint32_t MACHT1R;
    uint32_t      RESERVED1[14];
    __IO uint32_t MACVTR;
    uint32_t      RESERVED2;
    __IO uint32_t MACVHTR;
    uint32_t      RESERVED3;
    __IO uint32_t MACVIR;
    __IO uint32_t MACIVIR;
    uint32_t      RESERVED4[2];
    __IO uint32_t MACTFCR;
    uint32_t      RESERVED5[7];
    __IO uint32_t MACRFCR;
    uint32_t      RESERVED6[7];
    __IO uint32_t MACISR;
    __IO uint32_t MACIER;
    __IO uint32_t MACRXTXSR;
    uint32_t      RESERVED7;
    __IO uint32_t MACPCSR;
    __IO uint32_t MACRWKPFR;
    uint32_t      RESERVED8[2];
    __IO uint32_t MACLCSR;
    __IO uint32_t MACLTCR;
    __IO uint32_t MACLETR;
    __IO uint32_t MAC1USTCR;
    uint32_t      RESERVED9[12];
    __IO uint32_t MACVR;
    __IO uint32_t MACDR;
    uint32_t      RESERVED10;
    __IO uint32_t MACHWF0R;
    __IO uint32_t MACHWF1R;
    __IO uint32_t MACHWF2R;
    uint32_t      RESERVED11[54];
    __IO uint32_t MACMDIOAR;
    __IO uint32_t MACMDIODR;
    uint32_t      RESERVED12[2];
    __IO uint32_t MACARPAR;
    uint32_t      RESERVED13[59];
    __IO uint32_t MACA0HR;
    __IO uint32_t MACA0LR;
    __IO uint32_t MACA1HR;
    __IO uint32_t MACA1LR;
    __IO uint32_t MACA2HR;
    __IO uint32_t MACA2LR;
    __IO uint32_t MACA3HR;
    __IO uint32_t MACA3LR;
    uint32_t      RESERVED14[248];
    __IO uint32_t MMCCR;
    __IO uint32_t MMCRIR;
    __IO uint32_t MMCTIR;
    __IO uint32_t MMCRIMR;
    __IO uint32_t MMCTIMR;
    uint32_t      RESERVED15[14];
    __IO uint32_t MMCTSCGPR;
    __IO uint32_t MMCTMCGPR;
    int32_t       RESERVED16[5];
    __IO uint32_t MMCTPCGR;
    uint32_t      RESERVED17[10];
    __IO uint32_t MMCRCRCEPR;
    __IO uint32_t MMCRAEPR;
    uint32_t      RESERVED18[10];
    __IO uint32_t MMCRUPGR;
    uint32_t      RESERVED19[9];
    __IO uint32_t MMCTLPIMSTR;
    __IO uint32_t MMCTLPITCR;
    __IO uint32_t MMCRLPIMSTR;
    __IO uint32_t MMCRLPITCR;
    uint32_t      RESERVED20[65];
    __IO uint32_t MACL3L4C0R;
    __IO uint32_t MACL4A0R;
    uint32_t      RESERVED21[2];
    __IO uint32_t MACL3A0R0R;
    __IO uint32_t MACL3A1R0R;
    __IO uint32_t MACL3A2R0R;
    __IO uint32_t MACL3A3R0R;
    uint32_t      RESERVED22[4];
    __IO uint32_t MACL3L4C1R;
    __IO uint32_t MACL4A1R;
    uint32_t      RESERVED23[2];
    __IO uint32_t MACL3A0R1R;
    __IO uint32_t MACL3A1R1R;
    __IO uint32_t MACL3A2R1R;
    __IO uint32_t MACL3A3R1R;
    uint32_t      RESERVED24[108];
    __IO uint32_t MACTSCR;
    __IO uint32_t MACSSIR;
    __IO uint32_t MACSTSR;
    __IO uint32_t MACSTNR;
    __IO uint32_t MACSTSUR;
    __IO uint32_t MACSTNUR;
    __IO uint32_t MACTSAR;
    uint32_t      RESERVED25;
    __IO uint32_t MACTSSR;
    uint32_t      RESERVED26[3];
    __IO uint32_t MACTTSSNR;
    __IO uint32_t MACTTSSSR;
    uint32_t      RESERVED27[2];
    __IO uint32_t MACACR;
    uint32_t      RESERVED28;
    __IO uint32_t MACATSNR;
    __IO uint32_t MACATSSR;
    __IO uint32_t MACTSIACR;
    __IO uint32_t MACTSEACR;
    __IO uint32_t MACTSICNR;
    __IO uint32_t MACTSECNR;
    uint32_t      RESERVED29[4];
    __IO uint32_t MACPPSCR;
    uint32_t      RESERVED30[3];
    __IO uint32_t MACPPSTTSR;
    __IO uint32_t MACPPSTTNR;
    __IO uint32_t MACPPSIR;
    __IO uint32_t MACPPSWR;
    uint32_t      RESERVED31[12];
    __IO uint32_t MACPOCR;
    __IO uint32_t MACSPI0R;
    __IO uint32_t MACSPI1R;
    __IO uint32_t MACSPI2R;
    __IO uint32_t MACLMIR;
    uint32_t      RESERVED32[11];
    __IO uint32_t MTLOMR;
    uint32_t      RESERVED33[7];
    __IO uint32_t MTLISR;
    uint32_t      RESERVED34[55];
    __IO uint32_t MTLTQOMR;
    __IO uint32_t MTLTQUR;
    __IO uint32_t MTLTQDR;
    uint32_t      RESERVED35[8];
    __IO uint32_t MTLQICSR;
    __IO uint32_t MTLRQOMR;
    __IO uint32_t MTLRQMPOCR;
    __IO uint32_t MTLRQDR;
    uint32_t      RESERVED36[177];
    __IO uint32_t dmaMR;
    __IO uint32_t dmaSBMR;
    __IO uint32_t dmaISR;
    __IO uint32_t dmaDSR;
    uint32_t      RESERVED37[60];
    __IO uint32_t dmaCCR;
    __IO uint32_t dmaCTCR;
    __IO uint32_t dmaCRCR;
    uint32_t      RESERVED38[2];
    __IO uint32_t dmaCTDLAR;
    uint32_t      RESERVED39;
    __IO uint32_t dmaCRDLAR;
    __IO uint32_t dmaCTDTPR;
    uint32_t      RESERVED40;
    __IO uint32_t dmaCRDTPR;
    __IO uint32_t dmaCTDRLR;
    __IO uint32_t dmaCRDRLR;
    __IO uint32_t dmaCIER;
    __IO uint32_t dmaCRIWTR;
  __IO uint32_t dmaCSFCSR;
    uint32_t      RESERVED41;
    __IO uint32_t dmaCCATDR;
    uint32_t      RESERVED42;
    __IO uint32_t dmaCCARDR;
    uint32_t      RESERVED43;
    __IO uint32_t dmaCCATBR;
    uint32_t      RESERVED44;
    __IO uint32_t dmaCCARBR;
    __IO uint32_t dmaCSR;
  uint32_t      RESERVED45[2];
  __IO uint32_t dmaCMFCR;
  }ETH_TypeDef;

  /**
    * @brief External Interrupt/Event Controller
    */

  typedef struct
  {
  __IO uint32_t RTSR1;               /*!< EXTI Rising trigger selection register,       Address offset: 0x00 */
  __IO uint32_t FTSR1;               /*!< EXTI Falling trigger selection register,      Address offset: 0x04 */
  __IO uint32_t SWIER1;              /*!< EXTI Software interrupt event register,       Address offset: 0x08 */
  __IO uint32_t D3PMR1;              /*!< EXTI D3 Pending mask register,                Address offset: 0x0C */
  __IO uint32_t D3PCR1L;             /*!< EXTI D3 Pending clear selection register low, Address offset: 0x10 */
  __IO uint32_t D3PCR1H;             /*!< EXTI D3 Pending clear selection register High,Address offset: 0x14 */
  uint32_t      RESERVED1;           /*!< Reserved, 0x18                                                     */
  uint32_t      RESERVED2;           /*!< Reserved, 0x1C                                                     */
  __IO uint32_t RTSR2;               /*!< EXTI Rising trigger selection register,       Address offset: 0x20 */
  __IO uint32_t FTSR2;               /*!< EXTI Falling trigger selection register,      Address offset: 0x24 */
  __IO uint32_t SWIER2;              /*!< EXTI Software interrupt event register,       Address offset: 0x28 */
  __IO uint32_t D3PMR2;              /*!< EXTI D3 Pending mask register,                Address offset: 0x2C */
  __IO uint32_t D3PCR2L;             /*!< EXTI D3 Pending clear selection register low, Address offset: 0x30 */
  __IO uint32_t D3PCR2H;             /*!< EXTI D3 Pending clear selection register High,Address offset: 0x34 */
  uint32_t      RESERVED3;           /*!< Reserved, 0x38                                                     */
  uint32_t      RESERVED4;           /*!< Reserved, 0x3C                                                     */
  __IO uint32_t RTSR3;               /*!< EXTI Rising trigger selection register,       Address offset: 0x40 */
  __IO uint32_t FTSR3;               /*!< EXTI Falling trigger selection register,      Address offset: 0x44 */
  __IO uint32_t SWIER3;              /*!< EXTI Software interrupt event register,       Address offset: 0x48 */
  __IO uint32_t D3PMR3;              /*!< EXTI D3 Pending mask register,                Address offset: 0x4C */
  __IO uint32_t D3PCR3L;             /*!< EXTI D3 Pending clear selection register low, Address offset: 0x50 */
  __IO uint32_t D3PCR3H;             /*!< EXTI D3 Pending clear selection register High,Address offset: 0x54 */
  }EXTI_TypeDef;

  typedef struct
  {
  __IO uint32_t IMR1;                /*!< EXTI Interrupt mask register,                Address offset: 0x00 */
  __IO uint32_t EMR1;                /*!< EXTI Event mask register,                    Address offset: 0x04 */
  __IO uint32_t PR1;                 /*!< EXTI Pending register,                       Address offset: 0x08 */
  uint32_t      RESERVED1;           /*!< Reserved, 0x0C                                                    */
  __IO uint32_t IMR2;                /*!< EXTI Interrupt mask register,                Address offset: 0x10 */
  __IO uint32_t EMR2;                /*!< EXTI Event mask register,                    Address offset: 0x14 */
  __IO uint32_t PR2;                 /*!< EXTI Pending register,                       Address offset: 0x18 */
  uint32_t      RESERVED2;           /*!< Reserved, 0x1C                                                    */
  __IO uint32_t IMR3;                /*!< EXTI Interrupt mask register,                Address offset: 0x20 */
  __IO uint32_t EMR3;                /*!< EXTI Event mask register,                    Address offset: 0x24 */
  __IO uint32_t PR3;                 /*!< EXTI Pending register,                       Address offset: 0x28 */
  }EXTI_Core_TypeDef;


  /**
    * @brief FLASH Registers
    */

  typedef struct
  {
    __IO uint32_t ACR;             /*!< FLASH access control register,                           Address offset: 0x00 */
    __IO uint32_t KEYR1;           /*!< Flash Key Register for bank1,                            Address offset: 0x04 */
    __IO uint32_t OPTKEYR;         /*!< Flash Option Key Register,                                Address offset: 0x08 */
    __IO uint32_t CR1;             /*!< Flash Control Register for bank1,                        Address offset: 0x0C */
    __IO uint32_t SR1;             /*!< Flash Status Register for bank1,                         Address offset: 0x10 */
    __IO uint32_t CCR1;            /*!< Flash Control Register for bank1,                        Address offset: 0x14 */
    __IO uint32_t OPTCR;           /*!< Flash Option Control Register,                            Address offset: 0x18 */
    __IO uint32_t OPTSR_CUR;       /*!< Flash Option Status Current Register,                     Address offset: 0x1C */
    __IO uint32_t OPTSR_PRG;       /*!< Flash Option Status Current Register,                     Address offset: 0x20 */
    __IO uint32_t OPTCCR;          /*!< Flash Option Clear Control Register,                      Address offset: 0x24 */
    __IO uint32_t PRAR_CUR1;       /*!< Flash Current Protection Address Register for bank1,     Address offset: 0x28 */
    __IO uint32_t PRAR_PRG1;       /*!< Flash Protection Address to Program Register for bank1,  Address offset: 0x2C */
    __IO uint32_t SCAR_CUR1;       /*!< Flash Current Secure Address Register for bank1,         Address offset: 0x30 */
    __IO uint32_t SCAR_PRG1;       /*!< Flash Secure Address Register for bank1,                 Address offset: 0x34 */
    __IO uint32_t WPSN_CUR1;       /*!< Flash Current Write Protection Register on bank1,        Address offset: 0x38 */
    __IO uint32_t WPSN_PRG1;       /*!< Flash Write Protection to Program Register on bank1,     Address offset: 0x3C */
    __IO uint32_t BOOT_CUR;        /*!< Flash Current Boot Address for Pelican Core Register,     Address offset: 0x40 */
    __IO uint32_t BOOT_PRG;        /*!< Flash Boot Address to Program for Pelican Core Register,  Address offset: 0x44 */
    uint32_t      RESERVED0[2];    /*!< Reserved, 0x48 to 0x4C                                                        */
    __IO uint32_t CRCCR1;          /*!< Flash CRC Control register For Bank1 Register ,          Address offset: 0x50 */
    __IO uint32_t CRCSADD1;        /*!< Flash CRC Start Address Register for Bank1 ,             Address offset: 0x54 */
    __IO uint32_t CRCEADD1;        /*!< Flash CRC End Address Register for Bank1 ,               Address offset: 0x58 */
    __IO uint32_t CRCDATA;         /*!< Flash CRC Data Register for Bank1 ,                      Address offset: 0x5C */
    __IO uint32_t ECC_FA1;         /*!< Flash ECC Fail Address For Bank1 Register ,              Address offset: 0x60 */
    uint32_t      RESERVED1[40];   /*!< Reserved, 0x64 to 0x100                                                       */
    __IO uint32_t KEYR2;           /*!< Flash Key Register for bank2,                           Address offset: 0x104 */
    uint32_t      RESERVED2;       /*!< Reserved, 0x108                                                               */
    __IO uint32_t CR2;             /*!< Flash Control Register for bank2,                       Address offset: 0x10C */
    __IO uint32_t SR2;             /*!< Flash Status Register for bank2,                        Address offset: 0x110 */
    __IO uint32_t CCR2;            /*!< Flash Status Register for bank2,                        Address offset: 0x114 */
    uint32_t      RESERVED3[4];    /*!< Reserved, 0x118 to 0x124                                                      */
    __IO uint32_t PRAR_CUR2;       /*!< Flash Current Protection Address Register for bank2,    Address offset: 0x128 */
    __IO uint32_t PRAR_PRG2;       /*!< Flash Protection Address to Program Register for bank2, Address offset: 0x12C */
    __IO uint32_t SCAR_CUR2;       /*!< Flash Current Secure Address Register for bank2,        Address offset: 0x130 */
    __IO uint32_t SCAR_PRG2;       /*!< Flash Secure Address Register for bank2,                Address offset: 0x134 */
    __IO uint32_t WPSN_CUR2;       /*!< Flash Current Write Protection Register on bank2,       Address offset: 0x138 */
    __IO uint32_t WPSN_PRG2;       /*!< Flash Write Protection to Program Register on bank2,    Address offset: 0x13C */
    uint32_t      RESERVED4[4];    /*!< Reserved, 0x140 to 0x14C                                                      */
    __IO uint32_t CRCCR2;          /*!< Flash CRC Control register For Bank2 Register ,         Address offset: 0x150 */
    __IO uint32_t CRCSADD2;        /*!< Flash CRC Start Address Register for Bank2 ,            Address offset: 0x154 */
    __IO uint32_t CRCEADD2;        /*!< Flash CRC End Address Register for Bank2 ,              Address offset: 0x158 */
    __IO uint32_t CRCDATA2;        /*!< Flash CRC Data Register for Bank2 ,                     Address offset: 0x15C */
    __IO uint32_t ECC_FA2;         /*!< Flash ECC Fail Address For Bank2 Register ,             Address offset: 0x160 */
  } FLASH_TypeDef;

  /**
    * @brief Flexible Memory Controller
    */

  typedef struct
  {
    __IO uint32_t BTCR[8];    /*!< NOR/PSRAM chip-select control register(BCR) and chip-select timing register(BTR), Address offset: 0x00-1C */
  } FMC_Bank1_TypeDef;

  /**
    * @brief Flexible Memory Controller Bank1E
    */

  typedef struct
  {
    __IO uint32_t BWTR[7];    /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
  } FMC_Bank1E_TypeDef;

  /**
    * @brief Flexible Memory Controller Bank2
    */

  typedef struct
  {
    __IO uint32_t PCR2;       /*!< NAND Flash control register 2,                       Address offset: 0x60 */
    __IO uint32_t SR2;        /*!< NAND Flash FIFO status and interrupt register 2,     Address offset: 0x64 */
    __IO uint32_t PMEM2;      /*!< NAND Flash Common memory space timing register 2,    Address offset: 0x68 */
    __IO uint32_t PATT2;      /*!< NAND Flash Attribute memory space timing register 2, Address offset: 0x6C */
    uint32_t      RESERVED0;  /*!< Reserved, 0x70                                                            */
    __IO uint32_t ECCR2;      /*!< NAND Flash ECC result registers 2,                   Address offset: 0x74 */
  } FMC_Bank2_TypeDef;

  /**
    * @brief Flexible Memory Controller Bank3
    */

  typedef struct
  {
    __IO uint32_t PCR;       /*!< NAND Flash control register 3,                       Address offset: 0x80 */
    __IO uint32_t SR;        /*!< NAND Flash FIFO status and interrupt register 3,     Address offset: 0x84 */
    __IO uint32_t PMEM;      /*!< NAND Flash Common memory space timing register 3,    Address offset: 0x88 */
    __IO uint32_t PATT;      /*!< NAND Flash Attribute memory space timing register 3, Address offset: 0x8C */
    uint32_t      RESERVED;  /*!< Reserved, 0x90                                                            */
    __IO uint32_t ECCR;      /*!< NAND Flash ECC result registers 3,                   Address offset: 0x94 */
  } FMC_Bank3_TypeDef;

  /**
    * @brief Flexible Memory Controller Bank5 and 6
    */


  typedef struct
  {
    __IO uint32_t SDCR[2];        /*!< SDRAM Control registers ,      Address offset: 0x140-0x144  */
    __IO uint32_t SDTR[2];        /*!< SDRAM Timing registers ,       Address offset: 0x148-0x14C  */
    __IO uint32_t SDCMR;       /*!< SDRAM Command Mode register,    Address offset: 0x150  */
    __IO uint32_t SDRTR;       /*!< SDRAM Refresh Timer register,   Address offset: 0x154  */
    __IO uint32_t SDSR;        /*!< SDRAM Status register,          Address offset: 0x158  */
  } FMC_Bank5_6_TypeDef;

  /**
    * @brief General Purpose I/O
    */

  typedef struct
  {
    __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
    __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
    __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
    __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
    __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
    __IO uint16_t BSRRL;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
    __IO uint16_t BSRRH;    /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
    __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  } GPIO_TypeDef;

  /**
    * @brief Operational Amplifier (OPAMP)
    */

  typedef struct
  {
    __IO uint32_t CSR;          /*!< OPAMP control/status register,                     Address offset: 0x00 */
    __IO uint32_t OTR;          /*!< OPAMP offset trimming register for normal mode,    Address offset: 0x04 */
    __IO uint32_t HSOTR;        /*!< OPAMP offset trimming register for high speed mode, Address offset: 0x08 */
  } OPAMP_TypeDef;

  /**
    * @brief System configuration controller
    */

  typedef struct
  {
   uint32_t RESERVED1;           /*!< Reserved,                                           Address offset: 0x00        */
   __IO uint32_t PMCR;           /*!< SYSCFG peripheral mode configuration register,      Address offset: 0x04        */
   __IO uint32_t EXTICR[4];      /*!< SYSCFG external interrupt configuration registers,  Address offset: 0x08-0x14   */
   uint32_t RESERVED2[2];        /*!< Reserved,                                            Address offset: 0x18-0x1C  */
   __IO uint32_t CCCSR;          /*!< SYSCFG compensation cell control/status register,   Address offset: 0x20        */
   __IO uint32_t CCVR;           /*!< SYSCFG compensation cell value register,            Address offset: 0x24        */
   __IO uint32_t CCCR;           /*!< SYSCFG compensation cell code register,             Address offset: 0x28        */
    uint32_t     RESERVED3[62];  /*!< Reserved, 0x2C-0x120                                                            */
   __IO uint32_t PKGR;           /*!< SYSCFG package register,                            Address offset: 0x124       */
    uint32_t     RESERVED4[118]; /*!< Reserved, 0x128-0x2FC                                                           */
   __IO uint32_t UR0;            /*!< SYSCFG user register 0,                             Address offset: 0x300       */
   __IO uint32_t UR1;            /*!< SYSCFG user register 1,                             Address offset: 0x304       */
   __IO uint32_t UR2;            /*!< SYSCFG user register 2,                             Address offset: 0x308       */
   __IO uint32_t UR3;            /*!< SYSCFG user register 3,                             Address offset: 0x30C       */
   __IO uint32_t UR4;            /*!< SYSCFG user register 4,                             Address offset: 0x310       */
   __IO uint32_t UR5;            /*!< SYSCFG user register 5,                             Address offset: 0x314       */
   __IO uint32_t UR6;            /*!< SYSCFG user register 6,                             Address offset: 0x318       */
   __IO uint32_t UR7;            /*!< SYSCFG user register 7,                             Address offset: 0x31C       */
   __IO uint32_t UR8;            /*!< SYSCFG user register 8,                             Address offset: 0x320       */
   __IO uint32_t UR9;            /*!< SYSCFG user register 9,                             Address offset: 0x324       */
   __IO uint32_t UR10;           /*!< SYSCFG user register 10,                            Address offset: 0x328       */
   __IO uint32_t UR11;           /*!< SYSCFG user register 11,                            Address offset: 0x32C       */
   __IO uint32_t UR12;           /*!< SYSCFG user register 12,                            Address offset: 0x330       */
   __IO uint32_t UR13;           /*!< SYSCFG user register 13,                            Address offset: 0x334       */
   __IO uint32_t UR14;           /*!< SYSCFG user register 14,                            Address offset: 0x338       */
   __IO uint32_t UR15;           /*!< SYSCFG user register 15,                            Address offset: 0x33C       */
   __IO uint32_t UR16;           /*!< SYSCFG user register 16,                            Address offset: 0x340       */
   __IO uint32_t UR17;           /*!< SYSCFG user register 17,                            Address offset: 0x344       */

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
  } I2C_TypeDef;

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
    * @brief JPEG Codec
    */
  typedef struct
  {
    __IO uint32_t CONFR0;          /*!< JPEG Codec Control Register (JPEG_CONFR0),        Address offset: 00h       */
    __IO uint32_t CONFR1;          /*!< JPEG Codec Control Register (JPEG_CONFR1),        Address offset: 04h       */
    __IO uint32_t CONFR2;          /*!< JPEG Codec Control Register (JPEG_CONFR2),        Address offset: 08h       */
    __IO uint32_t CONFR3;          /*!< JPEG Codec Control Register (JPEG_CONFR3),        Address offset: 0Ch       */
    __IO uint32_t CONFR4;          /*!< JPEG Codec Control Register (JPEG_CONFR4),        Address offset: 10h       */
    __IO uint32_t CONFR5;          /*!< JPEG Codec Control Register (JPEG_CONFR5),        Address offset: 14h       */
    __IO uint32_t CONFR6;          /*!< JPEG Codec Control Register (JPEG_CONFR6),        Address offset: 18h       */
    __IO uint32_t CONFR7;          /*!< JPEG Codec Control Register (JPEG_CONFR7),        Address offset: 1Ch       */
    uint32_t  Reserved20[4];       /* Reserved                                            Address offset: 20h-2Ch   */
    __IO uint32_t CR;              /*!< JPEG Control Register (JPEG_CR),                  Address offset: 30h       */
    __IO uint32_t SR;              /*!< JPEG Status Register (JPEG_SR),                   Address offset: 34h       */
    __IO uint32_t CFR;             /*!< JPEG Clear Flag Register (JPEG_CFR),              Address offset: 38h       */
    uint32_t  Reserved3c;          /* Reserved                                            Address offset: 3Ch       */
    __IO uint32_t DIR;             /*!< JPEG Data Input Register (JPEG_DIR),              Address offset: 40h       */
    __IO uint32_t DOR;             /*!< JPEG Data Output Register (JPEG_DOR),             Address offset: 44h       */
    uint32_t  Reserved48[2];       /* Reserved                                            Address offset: 48h-4Ch   */
    __IO uint32_t QMEM0[16];       /*!< JPEG quantization tables 0,                       Address offset: 50h-8Ch   */
    __IO uint32_t QMEM1[16];       /*!< JPEG quantization tables 1,                       Address offset: 90h-CCh   */
    __IO uint32_t QMEM2[16];       /*!< JPEG quantization tables 2,                       Address offset: D0h-10Ch  */
    __IO uint32_t QMEM3[16];       /*!< JPEG quantization tables 3,                       Address offset: 110h-14Ch */
    __IO uint32_t HUFFMIN[16];     /*!< JPEG HuffMin tables,                              Address offset: 150h-18Ch */
    __IO uint32_t HUFFBASE[32];    /*!< JPEG HuffSymb tables,                             Address offset: 190h-20Ch */
    __IO uint32_t HUFFSYMB[84];    /*!< JPEG HUFFSYMB tables,                             Address offset: 210h-35Ch */
    __IO uint32_t DHTMEM[103];     /*!< JPEG DHTMem tables,                               Address offset: 360h-4F8h */
    uint32_t  Reserved4FC;         /* Reserved                                            Address offset: 4FCh      */
    __IO uint32_t HUFFENC_AC0[88]; /*!< JPEG encodor, AC Huffman table 0,                 Address offset: 500h-65Ch */
    __IO uint32_t HUFFENC_AC1[88]; /*!< JPEG encodor, AC Huffman table 1,                 Address offset: 660h-7BCh */
    __IO uint32_t HUFFENC_DC0[8];  /*!< JPEG encodor, DC Huffman table 0,                 Address offset: 7C0h-7DCh */
    __IO uint32_t HUFFENC_DC1[8];  /*!< JPEG encodor, DC Huffman table 1,                 Address offset: 7E0h-7FCh */

  } JPEG_TypeDef;


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
    * @brief Power Control
    */

  typedef struct
  {
    __IO uint32_t CR1;          /*!< PWR power control register 1,        Address offset: 0x00 */
    __IO uint32_t CSR1;      /*!< PWR power control status register 1,     Address offset: 0x04 */
    __IO uint32_t CR2;       /*!< PWR power control register 2,            Address offset: 0x08 */
    __IO uint32_t CR3;       /*!< PWR power control register 3,            Address offset: 0x0C */
    __IO uint32_t CPUCR;     /*!< PWR CPU control register,                Address offset: 0x10 */
         uint32_t RESERVED0; /*!< Reserved,                                Address offset: 0x14 */
    __IO uint32_t D3CR;      /*!< PWR D3 domain control register,          Address offset: 0x18 */
         uint32_t RESERVED1; /*!< Reserved,                                Address offset: 0x1C */
    __IO uint32_t WKUPCR;    /*!< PWR wakeup clear register,               Address offset: 0x20 */
    __IO uint32_t WKUPFR;    /*!< PWR wakeup flag register,                Address offset: 0x24 */
    __IO uint32_t WKUPEPR;   /*!< PWR wakeup enable and polarity register, Address offset: 0x28 */
  } PWR_TypeDef;

  /**
    * @brief Reset and Clock Control
    */

  typedef struct
  {
   __IO uint32_t CR;             /*!< RCC clock control register,                                              Address offset: 0x00  */
   __IO uint32_t ICSCR;          /*!< RCC Internal Clock Sources Calibration Register,                         Address offset: 0x04  */
   __IO uint32_t CRRCR;          /*!< Clock Recovery RC  Register,                                             Address offset: 0x08  */
   uint32_t     RESERVED0;       /*!< Reserved,                                                                Address offset: 0x0C  */
   __IO uint32_t CFGR;           /*!< RCC clock configuration register,                                        Address offset: 0x10  */
   uint32_t     RESERVED1;       /*!< Reserved,                                                                Address offset: 0x14  */
   __IO uint32_t D1CFGR;         /*!< RCC Domain 1 configuration register,                                     Address offset: 0x18  */
   __IO uint32_t D2CFGR;         /*!< RCC Domain 2 configuration register,                                     Address offset: 0x1C  */
   __IO uint32_t D3CFGR;         /*!< RCC Domain 3 configuration register,                                     Address offset: 0x20  */
   uint32_t     RESERVED2;       /*!< Reserved,                                                                Address offset: 0x24  */
   __IO uint32_t PLLCKSELR;      /*!< RCC PLLs Clock Source Selection Register,                                Address offset: 0x28  */
   __IO uint32_t PLLCFGR;        /*!< RCC PLLs  Configuration Register,                                        Address offset: 0x2C  */
   __IO uint32_t PLL1DIVR;       /*!< RCC PLL1 Dividers Configuration Register,                                Address offset: 0x30  */
   __IO uint32_t PLL1FRACR;      /*!< RCC PLL1 Fractional Divider Configuration Register,                      Address offset: 0x34  */
   __IO uint32_t PLL2DIVR;       /*!< RCC PLL2 Dividers Configuration Register,                                Address offset: 0x38  */
   __IO uint32_t PLL2FRACR;      /*!< RCC PLL2 Fractional Divider Configuration Register,                      Address offset: 0x3C  */
   __IO uint32_t PLL3DIVR;       /*!< RCC PLL3 Dividers Configuration Register,                                Address offset: 0x40  */
   __IO uint32_t PLL3FRACR;      /*!< RCC PLL3 Fractional Divider Configuration Register,                      Address offset: 0x44  */
   uint32_t      RESERVED3;      /*!< Reserved,                                                                Address offset: 0x48  */
   __IO uint32_t  D1CCIPR;       /*!< RCC Domain 1 Kernel Clock Configuration Register                         Address offset: 0x4C  */
   __IO uint32_t  D2CCIP1R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x50  */
   __IO uint32_t  D2CCIP2R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x54  */
   __IO uint32_t  D3CCIPR;       /*!< RCC Domain 3 Kernel Clock Configuration Register                         Address offset: 0x58  */
   uint32_t      RESERVED4;      /*!< Reserved,                                                                Address offset: 0x5C  */
   __IO uint32_t  CIER;          /*!< RCC Clock Source Interrupt Enable Register                               Address offset: 0x60  */
   __IO uint32_t  CIFR;          /*!< RCC Clock Source Interrupt Flag Register                                 Address offset: 0x64  */
   __IO uint32_t  CICR;          /*!< RCC Clock Source Interrupt Clear Register                                Address offset: 0x68  */
   uint32_t     RESERVED5;       /*!< Reserved,                                                                Address offset: 0x6C  */
   __IO uint32_t  BDCR;          /*!< RCC Vswitch Backup Domain Control Register,                              Address offset: 0x70  */
   __IO uint32_t  CSR;           /*!< RCC clock control & status register,                                     Address offset: 0x74  */
   uint32_t     RESERVED6;       /*!< Reserved,                                                                Address offset: 0x78  */
   __IO uint32_t AHB3RSTR;       /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x7C  */
   __IO uint32_t AHB1RSTR;       /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x80  */
   __IO uint32_t AHB2RSTR;       /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x84  */
   __IO uint32_t AHB4RSTR;       /*!< RCC AHB4 peripheral reset register,                                      Address offset: 0x88  */
   __IO uint32_t APB3RSTR;       /*!< RCC APB3 peripheral reset register,                                      Address offset: 0x8C  */
   __IO uint32_t APB1LRSTR;      /*!< RCC APB1 peripheral reset Low Word register,                             Address offset: 0x90  */
   __IO uint32_t APB1HRSTR;      /*!< RCC APB1 peripheral reset High Word register,                            Address offset: 0x94  */
   __IO uint32_t APB2RSTR;       /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x98  */
   __IO uint32_t APB4RSTR;       /*!< RCC APB4 peripheral reset register,                                      Address offset: 0x9C  */
   __IO uint32_t GCR;            /*!< RCC RCC Global Control  Register,                                        Address offset: 0xA0  */
   uint32_t     RESERVED7;       /*!< Reserved,                                                                Address offset: 0xA4  */
   __IO uint32_t D3AMR;          /*!< RCC Domain 3 Autonomous Mode Register,                                   Address offset: 0xA8  */
   uint32_t     RESERVED8[9];    /*!< Reserved, 0xAC-0xCC                                                      Address offset: 0xAC  */
   __IO uint32_t RSR;            /*!< RCC Reset status register,                                               Address offset: 0xD0  */
   __IO uint32_t AHB3ENR;        /*!< RCC AHB3 peripheral clock  register,                                     Address offset: 0xD4  */
   __IO uint32_t AHB1ENR;        /*!< RCC AHB1 peripheral clock  register,                                     Address offset: 0xD8  */
   __IO uint32_t AHB2ENR;        /*!< RCC AHB2 peripheral clock  register,                                     Address offset: 0xDC  */
   __IO uint32_t AHB4ENR;        /*!< RCC AHB4 peripheral clock  register,                                     Address offset: 0xE0  */
   __IO uint32_t APB3ENR;        /*!< RCC APB3 peripheral clock  register,                                     Address offset: 0xE4  */
   __IO uint32_t APB1LENR;       /*!< RCC APB1 peripheral clock  Low Word register,                            Address offset: 0xE8  */
   __IO uint32_t APB1HENR;       /*!< RCC APB1 peripheral clock  High Word register,                           Address offset: 0xEC  */
   __IO uint32_t APB2ENR;        /*!< RCC APB2 peripheral clock  register,                                     Address offset: 0xF0  */
   __IO uint32_t APB4ENR;        /*!< RCC APB4 peripheral clock  register,                                     Address offset: 0xF4  */
   uint32_t      RESERVED9;      /*!< Reserved,                                                                Address offset: 0xF8  */
   __IO uint32_t AHB3LPENR;      /*!< RCC AHB3 peripheral sleep clock  register,                               Address offset: 0xFC  */
   __IO uint32_t AHB1LPENR;      /*!< RCC AHB1 peripheral sleep clock  register,                               Address offset: 0x100 */
   __IO uint32_t AHB2LPENR;      /*!< RCC AHB2 peripheral sleep clock  register,                               Address offset: 0x104 */
   __IO uint32_t AHB4LPENR;      /*!< RCC AHB4 peripheral sleep clock  register,                               Address offset: 0x108 */
   __IO uint32_t APB3LPENR;      /*!< RCC APB3 peripheral sleep clock  register,                               Address offset: 0x10C */
   __IO uint32_t APB1LLPENR;     /*!< RCC APB1 peripheral sleep clock  Low Word register,                      Address offset: 0x110 */
   __IO uint32_t APB1HLPENR;     /*!< RCC APB1 peripheral sleep clock  High Word register,                     Address offset: 0x114 */
   __IO uint32_t APB2LPENR;      /*!< RCC APB2 peripheral sleep clock  register,                               Address offset: 0x118 */
   __IO uint32_t APB4LPENR;      /*!< RCC APB4 peripheral sleep clock  register,                               Address offset: 0x11C */
   uint32_t     RESERVED10[4];   /*!< Reserved, 0x120-0x12C                                                    Address offset: 0x120 */

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
         uint32_t reserved;   /*!< Reserved  */
    __IO uint32_t ALRMAR;     /*!< RTC alarm A register,                                      Address offset: 0x1C */
    __IO uint32_t ALRMBR;     /*!< RTC alarm B register,                                      Address offset: 0x20 */
    __IO uint32_t WPR;        /*!< RTC write protection register,                             Address offset: 0x24 */
    __IO uint32_t SSR;        /*!< RTC sub second register,                                   Address offset: 0x28 */
    __IO uint32_t SHIFTR;     /*!< RTC shift control register,                                Address offset: 0x2C */
    __IO uint32_t TSTR;       /*!< RTC time stamp time register,                              Address offset: 0x30 */
    __IO uint32_t TSDR;       /*!< RTC time stamp date register,                              Address offset: 0x34 */
    __IO uint32_t TSSSR;      /*!< RTC time-stamp sub second register,                        Address offset: 0x38 */
    __IO uint32_t CALR;       /*!< RTC calibration register,                                  Address offset: 0x3C */
    __IO uint32_t TAMPCR;     /*!< RTC tamper and alternate function configuration register,  Address offset: 0x40 */
    __IO uint32_t ALRMASSR;   /*!< RTC alarm A sub second register,                           Address offset: 0x44 */
    __IO uint32_t ALRMBSSR;   /*!< RTC alarm B sub second register,                           Address offset: 0x48 */
    __IO uint32_t OR;         /*!< RTC option register,                                       Address offset: 0x4C */
    __IO uint32_t BKP0R;      /*!< RTC backup register 0,                                     Address offset: 0x50 */
    __IO uint32_t BKP1R;      /*!< RTC backup register 1,                                     Address offset: 0x54 */
    __IO uint32_t BKP2R;      /*!< RTC backup register 2,                                     Address offset: 0x58 */
    __IO uint32_t BKP3R;      /*!< RTC backup register 3,                                     Address offset: 0x5C */
    __IO uint32_t BKP4R;      /*!< RTC backup register 4,                                     Address offset: 0x60 */
    __IO uint32_t BKP5R;      /*!< RTC backup register 5,                                     Address offset: 0x64 */
    __IO uint32_t BKP6R;      /*!< RTC backup register 6,                                     Address offset: 0x68 */
    __IO uint32_t BKP7R;      /*!< RTC backup register 7,                                     Address offset: 0x6C */
    __IO uint32_t BKP8R;      /*!< RTC backup register 8,                                     Address offset: 0x70 */
    __IO uint32_t BKP9R;      /*!< RTC backup register 9,                                     Address offset: 0x74 */
    __IO uint32_t BKP10R;     /*!< RTC backup register 10,                                    Address offset: 0x78 */
    __IO uint32_t BKP11R;     /*!< RTC backup register 11,                                    Address offset: 0x7C */
    __IO uint32_t BKP12R;     /*!< RTC backup register 12,                                    Address offset: 0x80 */
    __IO uint32_t BKP13R;     /*!< RTC backup register 13,                                    Address offset: 0x84 */
    __IO uint32_t BKP14R;     /*!< RTC backup register 14,                                    Address offset: 0x88 */
    __IO uint32_t BKP15R;     /*!< RTC backup register 15,                                    Address offset: 0x8C */
    __IO uint32_t BKP16R;     /*!< RTC backup register 16,                                    Address offset: 0x90 */
    __IO uint32_t BKP17R;     /*!< RTC backup register 17,                                    Address offset: 0x94 */
    __IO uint32_t BKP18R;     /*!< RTC backup register 18,                                    Address offset: 0x98 */
    __IO uint32_t BKP19R;     /*!< RTC backup register 19,                                    Address offset: 0x9C */
    __IO uint32_t BKP20R;     /*!< RTC backup register 20,                                    Address offset: 0xA0 */
    __IO uint32_t BKP21R;     /*!< RTC backup register 21,                                    Address offset: 0xA4 */
    __IO uint32_t BKP22R;     /*!< RTC backup register 22,                                    Address offset: 0xA8 */
    __IO uint32_t BKP23R;     /*!< RTC backup register 23,                                    Address offset: 0xAC */
    __IO uint32_t BKP24R;     /*!< RTC backup register 24,                                    Address offset: 0xB0 */
    __IO uint32_t BKP25R;     /*!< RTC backup register 25,                                    Address offset: 0xB4 */
    __IO uint32_t BKP26R;     /*!< RTC backup register 26,                                    Address offset: 0xB8 */
    __IO uint32_t BKP27R;     /*!< RTC backup register 27,                                    Address offset: 0xBC */
    __IO uint32_t BKP28R;     /*!< RTC backup register 28,                                    Address offset: 0xC0 */
    __IO uint32_t BKP29R;     /*!< RTC backup register 29,                                    Address offset: 0xC4 */
    __IO uint32_t BKP30R;     /*!< RTC backup register 30,                                    Address offset: 0xC8 */
    __IO uint32_t BKP31R;     /*!< RTC backup register 31,                                    Address offset: 0xCC */
  } RTC_TypeDef;


  /**
    * @brief Serial Audio Interface
    */

  typedef struct
  {
    __IO uint32_t GCR;           /*!< SAI global configuration register, Address offset: 0x00 */
    uint32_t      RESERVED0[16]; /*!< Reserved, 0x04 - 0x43                                   */
    __IO uint32_t PDMCR;         /*!< SAI PDM control register,          Address offset: 0x44 */
    __IO uint32_t PDMDLY;        /*!< SAI PDM delay register,            Address offset: 0x48 */
  } SAI_TypeDef;

  typedef struct
  {
    __IO uint32_t CR1;      /*!< SAI block x configuration register 1,     Address offset: 0x04 */
    __IO uint32_t CR2;      /*!< SAI block x configuration register 2,     Address offset: 0x08 */
    __IO uint32_t FRCR;     /*!< SAI block x frame configuration register, Address offset: 0x0C */
    __IO uint32_t SLOTR;    /*!< SAI block x slot register,                Address offset: 0x10 */
    __IO uint32_t IMR;      /*!< SAI block x interrupt mask register,      Address offset: 0x14 */
    __IO uint32_t SR;       /*!< SAI block x status register,              Address offset: 0x18 */
    __IO uint32_t CLRFR;    /*!< SAI block x clear flag register,          Address offset: 0x1C */
    __IO uint32_t DR;       /*!< SAI block x data register,                Address offset: 0x20 */
  } SAI_Block_TypeDef;

  /**
    * @brief SPDIF-RX Interface
    */

  typedef struct
  {
    __IO uint32_t   CR;           /*!< Control register,                   Address offset: 0x00 */
    __IO uint32_t   IMR;          /*!< Interrupt mask register,            Address offset: 0x04 */
    __IO uint32_t   SR;           /*!< Status register,                    Address offset: 0x08 */
    __IO uint32_t   IFCR;         /*!< Interrupt Flag Clear register,      Address offset: 0x0C */
    __IO uint32_t   DR;           /*!< Data input register,                Address offset: 0x10 */
    __IO uint32_t   CSR;          /*!< Channel Status register,            Address offset: 0x14 */
    __IO uint32_t   DIR;          /*!< Debug Information register,         Address offset: 0x18 */
    uint32_t        RESERVED2;    /*!< Reserved,  0x1A                                          */
  } SPDIFRX_TypeDef;


  /**
    * @brief Secure digital input/output Interface
    */

  typedef struct
  {
    __IO uint32_t POWER;          /*!< SDMMC power control register,             Address offset: 0x00 */
    __IO uint32_t CLKCR;          /*!< SDMMC clock control register,             Address offset: 0x04 */
    __IO uint32_t ARG;            /*!< SDMMC argument register,                  Address offset: 0x08 */
    __IO uint32_t CMD;            /*!< SDMMC command register,                   Address offset: 0x0C */
    __I uint32_t  RESPCMD;        /*!< SDMMC command response register,          Address offset: 0x10 */
    __I uint32_t  RESP1;          /*!< SDMMC response 1 register,                Address offset: 0x14 */
    __I uint32_t  RESP2;          /*!< SDMMC response 2 register,                Address offset: 0x18 */
    __I uint32_t  RESP3;          /*!< SDMMC response 3 register,                Address offset: 0x1C */
    __I uint32_t  RESP4;          /*!< SDMMC response 4 register,                Address offset: 0x20 */
    __IO uint32_t DTIMER;         /*!< SDMMC data timer register,                Address offset: 0x24 */
    __IO uint32_t DLEN;           /*!< SDMMC data length register,               Address offset: 0x28 */
    __IO uint32_t DCTRL;          /*!< SDMMC data control register,              Address offset: 0x2C */
    __I uint32_t  DCOUNT;         /*!< SDMMC data counter register,              Address offset: 0x30 */
    __I uint32_t  STA;            /*!< SDMMC status register,                    Address offset: 0x34 */
    __IO uint32_t ICR;            /*!< SDMMC interrupt clear register,           Address offset: 0x38 */
    __IO uint32_t MASK;           /*!< SDMMC mask register,                      Address offset: 0x3C */
    __IO uint32_t ACKTIME;        /*!< SDMMC Acknowledgement timer register,     Address offset: 0x40 */
    uint32_t      RESERVED0[3];   /*!< Reserved, 0x44 - 0x4C - 0x4C                                   */
    __IO uint32_t IdmaCTRL;       /*!< SDMMC dma control register,               Address offset: 0x50 */
    __IO uint32_t IdmaBSIZE;      /*!< SDMMC dma buffer size register,           Address offset: 0x54 */
    __IO uint32_t IdmaBASE0;      /*!< SDMMC dma buffer 0 base address register, Address offset: 0x58 */
    __IO uint32_t IdmaBASE1;      /*!< SDMMC dma buffer 1 base address register, Address offset: 0x5C */
    uint32_t      RESERVED1[8];   /*!< Reserved, 0x60-0x7C                                            */
    __IO uint32_t FIFO;           /*!< SDMMC data FIFO register,                 Address offset: 0x80 */
    uint32_t      RESERVED2[222]; /*!< Reserved, 0x84-0x3F8                                           */
    __IO uint32_t IPVR;           /*!< SDMMC data FIFO register,                Address offset: 0x3FC */
  } SDMMC_TypeDef;


  /**
    * @brief Delay Block DLYB
    */

  typedef struct
  {
    __IO uint32_t CR;          /*!< DELAY BLOCK control register,  Address offset: 0x00 */
    __IO uint32_t CFGR;        /*!< DELAY BLOCK configuration register,  Address offset: 0x04 */
  } DLYB_TypeDef;

  /**
    * @brief HW Semaphore HSEM
    */

  typedef struct
  {
    __IO uint32_t R[32];      /*!< 2-step write lock and read back registers,     Address offset: 00h-7Ch  */
    __IO uint32_t RLR[32];    /*!< 1-step read lock registers,                    Address offset: 80h-FCh  */
    __IO uint32_t IER;        /*!< HSEM Interrupt enable register ,             Address offset: 100h     */
    __IO uint32_t ICR;        /*!< HSEM Interrupt clear register ,              Address offset: 104h     */
    __IO uint32_t ISR;        /*!< HSEM Interrupt Status register ,             Address offset: 108h     */
    __IO uint32_t MISR;       /*!< HSEM Interrupt Masked Status register ,      Address offset: 10Ch     */
    uint32_t  Reserved[12];   /* Reserved                                       Address offset: 110h-13Ch*/
    __IO uint32_t CR;         /*!< HSEM Semaphore clear register ,               Address offset: 140h      */
    __IO uint32_t KEYR;       /*!< HSEM Semaphore clear key register ,           Address offset: 144h      */

  } HSEM_TypeDef;

  /**
    * @brief Serial Peripheral Interface
    */

  typedef struct
  {
    __IO uint32_t CR1;          /*!< SPI Control register 1,                             Address offset: 0x00 */
    __IO uint32_t CR2;          /*!< SPI Control register 2,                             Address offset: 0x04 */
    __IO uint32_t CFG1;         /*!< SPI Status register,                                Address offset: 0x08 */
    __IO uint32_t CFG2;         /*!< SPI Status register,                                Address offset: 0x0C */
    __IO uint32_t IER;          /*!< SPI data register,                                  Address offset: 0x10 */
    __IO uint32_t SR;           /*!< SPI data register,                                  Address offset: 0x14 */
    __IO uint32_t IFCR;         /*!< SPI data register,                                  Address offset: 0x18 */
    uint32_t      RESERVED0;    /*!< SPI data register,                                  Address offset: 0x1C */
    __IO uint32_t TXDR;         /*!< SPI data register,                                  Address offset: 0x20 */
    uint32_t      RESERVED1[3]; /*!< Reserved, 0x24-0x2C                                                      */
    __IO uint32_t RXDR;         /*!< SPI data register,                                  Address offset: 0x30 */
    uint32_t      RESERVED2[3]; /*!< Reserved, 0x34-0x3C                                                      */
    __IO uint32_t CRCPOLY;     /*!< SPI data register,                                   Address offset: 0x40 */
    __IO uint32_t TXCRC;       /*!< SPI data register,                                   Address offset: 0x44 */
    __IO uint32_t RXCRC;       /*!< SPI data register,                                   Address offset: 0x48 */
    __IO uint32_t UDRDR;       /*!< SPI data register,                                   Address offset: 0x4C */
    __IO uint32_t I2SCFGR;      /*!< SPI data register,                                  Address offset: 0x50 */

  } SPI_TypeDef;

  /**
    * @brief QUAD Serial Peripheral Interface
    */

  typedef struct
  {
    __IO uint32_t CR;       /*!< QUADSPI Control register,                           Address offset: 0x00 */
    __IO uint32_t DCR;      /*!< QUADSPI Device Configuration register,              Address offset: 0x04 */
    __IO uint32_t SR;       /*!< QUADSPI Status register,                            Address offset: 0x08 */
    __IO uint32_t FCR;      /*!< QUADSPI Flag Clear register,                        Address offset: 0x0C */
    __IO uint32_t DLR;      /*!< QUADSPI Data Length register,                       Address offset: 0x10 */
    __IO uint32_t CCR;      /*!< QUADSPI Communication Configuration register,       Address offset: 0x14 */
    __IO uint32_t AR;       /*!< QUADSPI Address register,                           Address offset: 0x18 */
    __IO uint32_t ABR;      /*!< QUADSPI Alternate Bytes register,                   Address offset: 0x1C */
    __IO uint32_t DR;       /*!< QUADSPI Data register,                              Address offset: 0x20 */
    __IO uint32_t PSMKR;    /*!< QUADSPI Polling Status Mask register,               Address offset: 0x24 */
    __IO uint32_t PSMAR;    /*!< QUADSPI Polling Status Match register,              Address offset: 0x28 */
    __IO uint32_t PIR;      /*!< QUADSPI Polling Interval register,                  Address offset: 0x2C */
    __IO uint32_t LPTR;     /*!< QUADSPI Low Power Timeout register,                 Address offset: 0x30 */
  } QUADSPI_TypeDef;


  /**
    * @brief TIM
    */

  typedef struct
  {
    __IO uint16_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
    uint16_t      RESERVED0;   /*!< Reserved, 0x02                                                 */
    __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
    __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
    __IO uint32_t DIER;        /*!< TIM dma/interrupt enable register,        Address offset: 0x0C */
    __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
    __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
    __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
    __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
    __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
    __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
    __IO uint16_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
    uint16_t      RESERVED9;   /*!< Reserved, 0x2A                                                 */
    __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
    __IO uint16_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
    uint16_t      RESERVED10;  /*!< Reserved, 0x32                                                 */
    __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
    __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
    __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
    __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
    __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
    __IO uint16_t DCR;         /*!< TIM dma control register,                 Address offset: 0x48 */
    uint16_t      RESERVED12;  /*!< Reserved, 0x4A                                                 */
    __IO uint16_t dmaR;        /*!< TIM dma address for full transfer,        Address offset: 0x4C */
    uint16_t      RESERVED13;  /*!< Reserved, 0x4E                                                 */
    uint16_t      RESERVED14;  /*!< Reserved, 0x50                                                 */
    __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
    __IO uint32_t CCR5;        /*!< TIM capture/compare register5,            Address offset: 0x58 */
    __IO uint32_t CCR6;        /*!< TIM capture/compare register6,            Address offset: 0x5C */
    __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
    __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
    __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x68 */
  } TIM_TypeDef;

  /**
    * @brief LPTIMIMER
    */
  typedef struct
  {
    __IO uint32_t ISR;      /*!< LPTIM Interrupt and Status register,                Address offset: 0x00 */
    __IO uint32_t ICR;      /*!< LPTIM Interrupt Clear register,                     Address offset: 0x04 */
    __IO uint32_t IER;      /*!< LPTIM Interrupt Enable register,                    Address offset: 0x08 */
    __IO uint32_t CFGR;     /*!< LPTIM Configuration register,                       Address offset: 0x0C */
    __IO uint32_t CR;       /*!< LPTIM Control register,                             Address offset: 0x10 */
    __IO uint32_t CMP;      /*!< LPTIM Compare register,                             Address offset: 0x14 */
    __IO uint32_t ARR;      /*!< LPTIM Autoreload register,                          Address offset: 0x18 */
    __IO uint32_t CNT;      /*!< LPTIM Counter register,                             Address offset: 0x1C */
    uint16_t  RESERVED1;    /*!< Reserved, 0x20                                                 */
    __IO uint32_t CFGR2;     /*!< LPTIM Option register,                              Address offset: 0x24 */
  } LPTIM_TypeDef;

  /**
    * @brief Comparator
    */
  typedef struct
  {
    __IO uint32_t SR;        /*!< Comparator status register,                    Address offset: 0x00 */
   __IO uint32_t ICFR;      /*!< Comparator interrupt clear flag register,      Address offset: 0x04 */
  	__IO uint32_t OR;        /*!< Comparator option register,                    Address offset: 0x08 */
  } COMPOPT_TypeDef;

  typedef struct
  {
  	__IO uint32_t CFGR;      /*!< Comparator configuration register  ,           Address offset: 0x00 */
  } COMP_TypeDef;

  typedef struct
  {
    __IO uint32_t CFGR;       /*!< COMP control and status register, used for bits common to several COMP instances, Address offset: 0x00 */
  } COMP_Common_TypeDef;
  /**
    * @brief Universal Synchronous Asynchronous Receiver Transmitter
    */

  typedef struct
  {
    __IO uint32_t CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
    __IO uint32_t CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
    __IO uint32_t CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
    __IO uint32_t BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
    __IO uint16_t GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
    uint16_t  RESERVED2;  /*!< Reserved, 0x12                                                 */
    __IO uint32_t RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
    __IO uint16_t RQR;    /*!< USART Request register,                   Address offset: 0x18 */
    uint16_t  RESERVED3;  /*!< Reserved, 0x1A                                                 */
    __IO uint32_t ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
    __IO uint32_t ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
    __IO uint16_t RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
    uint16_t  RESERVED4;  /*!< Reserved, 0x26                                                 */
    __IO uint16_t TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */
    uint16_t  RESERVED5;  /*!< Reserved, 0x2A                                                 */
    __IO uint32_t PRESC;  /*!< USART clock Prescaler register,           Address offset: 0x2C */
  } USART_TypeDef;

  /**
    * @brief Single Wire Protocol Master Interface SPWMI
    */
  typedef struct
  {
    __IO uint32_t CR;          /*!< SWPMI Configuration/Control register,     Address offset: 0x00 */
    __IO uint32_t BRR;         /*!< SWPMI bitrate register,                   Address offset: 0x04 */
      uint32_t  RESERVED1;     /*!< Reserved, 0x08                                                 */
    __IO uint32_t ISR;         /*!< SWPMI Interrupt and Status register,      Address offset: 0x0C */
    __IO uint32_t ICR;         /*!< SWPMI Interrupt Flag Clear register,      Address offset: 0x10 */
    __IO uint32_t IER;         /*!< SWPMI Interrupt Enable register,          Address offset: 0x14 */
    __IO uint32_t RFL;         /*!< SWPMI Receive Frame Length register,      Address offset: 0x18 */
    __IO uint32_t TDR;         /*!< SWPMI Transmit data register,             Address offset: 0x1C */
    __IO uint32_t RDR;         /*!< SWPMI Receive data register,              Address offset: 0x20 */
    __IO uint32_t OR;          /*!< SWPMI Option register,                    Address offset: 0x24 */
  } SWPMI_TypeDef;

  /**
    * @brief Window WATCHDOG
    */

  typedef struct
  {
    __IO uint32_t CR;   /*!< WWDG Control register,       Address offset: 0x00 */
    __IO uint32_t CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
    __IO uint32_t SR;   /*!< WWDG Status register,        Address offset: 0x08 */
  } WWDG_TypeDef;

  /**
    * @brief Crypto Processor
    */

  typedef struct
  {
    __IO uint32_t CR;         /*!< CRYP control register,                                    Address offset: 0x00 */
    __IO uint32_t SR;         /*!< CRYP status register,                                     Address offset: 0x04 */
    __IO uint32_t DIN;         /*!< CRYP data input register,                                 Address offset: 0x08 */
    __IO uint32_t DOUT;       /*!< CRYP data output register,                                Address offset: 0x0C */
    __IO uint32_t dmaCR;      /*!< CRYP dma control register,                                Address offset: 0x10 */
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
    * @brief High resolution Timer (HRTIM)
    */
  /* HRTIM master registers definition */
  typedef struct
  {
    __IO uint32_t MCR;            /*!< HRTIM Master Timer control register,                     Address offset: 0x00 */
    __IO uint32_t MISR;           /*!< HRTIM Master Timer interrupt status register,            Address offset: 0x04 */
    __IO uint32_t MICR;           /*!< HRTIM Master Timer interupt clear register,              Address offset: 0x08 */
    __IO uint32_t MDIER;          /*!< HRTIM Master Timer dma/interrupt enable register         Address offset: 0x0C */
    __IO uint32_t MCNTR;          /*!< HRTIM Master Timer counter register,                     Address offset: 0x10 */
    __IO uint32_t MPER;           /*!< HRTIM Master Timer period register,                      Address offset: 0x14 */
    __IO uint32_t MREP;           /*!< HRTIM Master Timer repetition register,                  Address offset: 0x18 */
    __IO uint32_t MCMP1R;         /*!< HRTIM Master Timer compare 1 register,                   Address offset: 0x1C */
    uint32_t      RESERVED0;     /*!< Reserved,                                                                0x20 */
    __IO uint32_t MCMP2R;         /*!< HRTIM Master Timer compare 2 register,                   Address offset: 0x24 */
    __IO uint32_t MCMP3R;         /*!< HRTIM Master Timer compare 3 register,                   Address offset: 0x28 */
    __IO uint32_t MCMP4R;         /*!< HRTIM Master Timer compare 4 register,                   Address offset: 0x2C */
    uint32_t      RESERVED1[20];  /*!< Reserved,                                                          0x30..0x7C */
  }HRTIM_Master_TypeDef;

  /* HRTIM Timer A to E registers definition */
  typedef struct
  {
    __IO uint32_t TIMxCR;     /*!< HRTIM Timerx control register,                              Address offset: 0x00  */
    __IO uint32_t TIMxISR;    /*!< HRTIM Timerx interrupt status register,                     Address offset: 0x04  */
    __IO uint32_t TIMxICR;    /*!< HRTIM Timerx interrupt clear register,                      Address offset: 0x08  */
    __IO uint32_t TIMxDIER;   /*!< HRTIM Timerx dma/interrupt enable register,                 Address offset: 0x0C  */
    __IO uint32_t CNTxR;      /*!< HRTIM Timerx counter register,                              Address offset: 0x10  */
    __IO uint32_t PERxR;      /*!< HRTIM Timerx period register,                               Address offset: 0x14  */
    __IO uint32_t REPxR;      /*!< HRTIM Timerx repetition register,                           Address offset: 0x18  */
    __IO uint32_t CMP1xR;     /*!< HRTIM Timerx compare 1 register,                            Address offset: 0x1C  */
    __IO uint32_t CMP1CxR;    /*!< HRTIM Timerx compare 1 compound register,                   Address offset: 0x20  */
    __IO uint32_t CMP2xR;     /*!< HRTIM Timerx compare 2 register,                            Address offset: 0x24  */
    __IO uint32_t CMP3xR;     /*!< HRTIM Timerx compare 3 register,                            Address offset: 0x28  */
    __IO uint32_t CMP4xR;     /*!< HRTIM Timerx compare 4 register,                            Address offset: 0x2C  */
    __IO uint32_t CPT1xR;     /*!< HRTIM Timerx capture 1 register,                            Address offset: 0x30  */
    __IO uint32_t CPT2xR;     /*!< HRTIM Timerx capture 2 register,                            Address offset: 0x34 */
    __IO uint32_t DTxR;       /*!< HRTIM Timerx dead time register,                            Address offset: 0x38 */
    __IO uint32_t SETx1R;     /*!< HRTIM Timerx output 1 set register,                         Address offset: 0x3C */
    __IO uint32_t RSTx1R;     /*!< HRTIM Timerx output 1 reset register,                       Address offset: 0x40 */
    __IO uint32_t SETx2R;     /*!< HRTIM Timerx output 2 set register,                         Address offset: 0x44 */
    __IO uint32_t RSTx2R;     /*!< HRTIM Timerx output 2 reset register,                       Address offset: 0x48 */
    __IO uint32_t EEFxR1;     /*!< HRTIM Timerx external event filtering 1 register,           Address offset: 0x4C */
    __IO uint32_t EEFxR2;     /*!< HRTIM Timerx external event filtering 2 register,           Address offset: 0x50 */
    __IO uint32_t RSTxR;      /*!< HRTIM Timerx Reset register,                                Address offset: 0x54 */
    __IO uint32_t CHPxR;      /*!< HRTIM Timerx Chopper register,                              Address offset: 0x58 */
    __IO uint32_t CPT1xCR;    /*!< HRTIM Timerx Capture 1 register,                            Address offset: 0x5C */
    __IO uint32_t CPT2xCR;    /*!< HRTIM Timerx Capture 2 register,                            Address offset: 0x60 */
    __IO uint32_t OUTxR;      /*!< HRTIM Timerx Output register,                               Address offset: 0x64 */
    __IO uint32_t FLTxR;      /*!< HRTIM Timerx Fault register,                                Address offset: 0x68 */
    uint32_t      RESERVED0[5];  /*!< Reserved,                                                              0x6C..0x7C */
  }HRTIM_Timerx_TypeDef;

  /* HRTIM common register definition */
  typedef struct
  {
    __IO uint32_t CR1;        /*!< HRTIM control register1,                                    Address offset: 0x00 */
    __IO uint32_t CR2;        /*!< HRTIM control register2,                                    Address offset: 0x04 */
    __IO uint32_t ISR;        /*!< HRTIM interrupt status register,                            Address offset: 0x08 */
    __IO uint32_t ICR;        /*!< HRTIM interrupt clear register,                             Address offset: 0x0C */
    __IO uint32_t IER;        /*!< HRTIM interrupt enable register,                            Address offset: 0x10 */
    __IO uint32_t OENR;       /*!< HRTIM Output enable register,                               Address offset: 0x14 */
    __IO uint32_t ODISR;      /*!< HRTIM Output disable register,                              Address offset: 0x18 */
    __IO uint32_t ODSR;       /*!< HRTIM Output disable status register,                       Address offset: 0x1C */
    __IO uint32_t BMCR;       /*!< HRTIM Burst mode control register,                          Address offset: 0x20 */
    __IO uint32_t BMTRGR;     /*!< HRTIM Busrt mode trigger register,                          Address offset: 0x24 */
    __IO uint32_t BMCMPR;     /*!< HRTIM Burst mode compare register,                          Address offset: 0x28 */
    __IO uint32_t BMPER;      /*!< HRTIM Burst mode period register,                           Address offset: 0x2C */
    __IO uint32_t EECR1;      /*!< HRTIM Timer external event control register1,               Address offset: 0x30 */
    __IO uint32_t EECR2;      /*!< HRTIM Timer external event control register2,               Address offset: 0x34 */
    __IO uint32_t EECR3;      /*!< HRTIM Timer external event control register3,               Address offset: 0x38 */
    __IO uint32_t ADC1R;      /*!< HRTIM ADC Trigger 1 register,                               Address offset: 0x3C */
    __IO uint32_t ADC2R;      /*!< HRTIM ADC Trigger 2 register,                               Address offset: 0x40 */
    __IO uint32_t ADC3R;      /*!< HRTIM ADC Trigger 3 register,                               Address offset: 0x44 */
    __IO uint32_t ADC4R;      /*!< HRTIM ADC Trigger 4 register,                               Address offset: 0x48 */
    __IO uint32_t DLLCR;      /*!< HRTIM DLL control register,                                 Address offset: 0x4C */
    __IO uint32_t FLTINR1;    /*!< HRTIM Fault input register1,                                Address offset: 0x50 */
    __IO uint32_t FLTINR2;    /*!< HRTIM Fault input register2,                                Address offset: 0x54 */
    __IO uint32_t BDMUPR;     /*!< HRTIM Burst dma Master Timer update register,               Address offset: 0x58 */
    __IO uint32_t BDTAUPR;    /*!< HRTIM Burst dma Timerx update register,                     Address offset: 0x5C */
    __IO uint32_t BDTBUPR;    /*!< HRTIM Burst dma Timerx update register,                     Address offset: 0x60 */
    __IO uint32_t BDTCUPR;    /*!< HRTIM Burst dma Timerx update register,                     Address offset: 0x64 */
    __IO uint32_t BDTDUPR;    /*!< HRTIM Burst dma Timerx update register,                     Address offset: 0x68 */
    __IO uint32_t BDTEUPR;    /*!< HRTIM Burst dma Timerx update register,                     Address offset: 0x6C */
    __IO uint32_t BdmaDR;     /*!< HRTIM Burst dma Master Data register,                       Address offset: 0x70 */
  }HRTIM_Common_TypeDef;

  /* HRTIM  register definition */
  typedef struct {
    HRTIM_Master_TypeDef sMasterRegs;
    HRTIM_Timerx_TypeDef sTimerxRegs[5];
    uint32_t             RESERVED0[32];
    HRTIM_Common_TypeDef sCommonRegs;
  }HRTIM_TypeDef;

  /**
    * @brief RNG
    */

  typedef struct
  {
    __IO uint32_t CR;  /*!< RNG control register, Address offset: 0x00 */
    __IO uint32_t SR;  /*!< RNG status register,  Address offset: 0x04 */
    __IO uint32_t DR;  /*!< RNG data register,    Address offset: 0x08 */
  } RNG_TypeDef;

  /**
    * @brief MDIOS
    */

  typedef struct
  {
    __IO uint32_t CR;
    __IO uint32_t WRFR;
    __IO uint32_t CWRFR;
    __IO uint32_t RDFR;
    __IO uint32_t CRDFR;
    __IO uint32_t SR;
    __IO uint32_t CLRFR;
    uint32_t RESERVED[57];
    __IO uint32_t DINR0;
    __IO uint32_t DINR1;
    __IO uint32_t DINR2;
    __IO uint32_t DINR3;
    __IO uint32_t DINR4;
    __IO uint32_t DINR5;
    __IO uint32_t DINR6;
    __IO uint32_t DINR7;
    __IO uint32_t DINR8;
    __IO uint32_t DINR9;
    __IO uint32_t DINR10;
    __IO uint32_t DINR11;
    __IO uint32_t DINR12;
    __IO uint32_t DINR13;
    __IO uint32_t DINR14;
    __IO uint32_t DINR15;
    __IO uint32_t DINR16;
    __IO uint32_t DINR17;
    __IO uint32_t DINR18;
    __IO uint32_t DINR19;
    __IO uint32_t DINR20;
    __IO uint32_t DINR21;
    __IO uint32_t DINR22;
    __IO uint32_t DINR23;
    __IO uint32_t DINR24;
    __IO uint32_t DINR25;
    __IO uint32_t DINR26;
    __IO uint32_t DINR27;
    __IO uint32_t DINR28;
    __IO uint32_t DINR29;
    __IO uint32_t DINR30;
    __IO uint32_t DINR31;
    __IO uint32_t DOUTR0;
    __IO uint32_t DOUTR1;
    __IO uint32_t DOUTR2;
    __IO uint32_t DOUTR3;
    __IO uint32_t DOUTR4;
    __IO uint32_t DOUTR5;
    __IO uint32_t DOUTR6;
    __IO uint32_t DOUTR7;
    __IO uint32_t DOUTR8;
    __IO uint32_t DOUTR9;
    __IO uint32_t DOUTR10;
    __IO uint32_t DOUTR11;
    __IO uint32_t DOUTR12;
    __IO uint32_t DOUTR13;
    __IO uint32_t DOUTR14;
    __IO uint32_t DOUTR15;
    __IO uint32_t DOUTR16;
    __IO uint32_t DOUTR17;
    __IO uint32_t DOUTR18;
    __IO uint32_t DOUTR19;
    __IO uint32_t DOUTR20;
    __IO uint32_t DOUTR21;
    __IO uint32_t DOUTR22;
    __IO uint32_t DOUTR23;
    __IO uint32_t DOUTR24;
    __IO uint32_t DOUTR25;
    __IO uint32_t DOUTR26;
    __IO uint32_t DOUTR27;
    __IO uint32_t DOUTR28;
    __IO uint32_t DOUTR29;
    __IO uint32_t DOUTR30;
    __IO uint32_t DOUTR31;
  } MDIOS_TypeDef;


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
    __IO uint32_t GSNPSID;              /* USB_OTG core ID                                 040h*/
    __IO uint32_t GHWCFG1;              /* User HW config1                                 044h*/
    __IO uint32_t GHWCFG2;              /* User HW config2                                 048h*/
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
    __IO uint32_t DIEPdma;           /*!< IN Endpoint dma Address Reg    900h + (ep_num * 20h) + 14h */
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
    __IO uint32_t DOEPdma;       /*!< dev OUT Endpoint dma Address           B00h + (ep_num * 20h) + 14h */
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
    __IO uint32_t HCdma;            /*!< Host Channel dma Address Register        514h */
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

inline __attribute__((always_inline)) void system_init(const uint32_t vec_tab_offset, const stm32h7::rcc_t::system_init_profile_t& system_init_profile)
{
    // установка доступа к FPU
    scb.coprocessor_10_access_full();
    scb.coprocessor_11_access_full();
#if 0
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
#endif
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

} // stm32h7



using namespace stm32h7 ;

#endif /* __STM32++_H__ */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
