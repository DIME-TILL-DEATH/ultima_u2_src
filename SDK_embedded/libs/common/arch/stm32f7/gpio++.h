/*
 * gpio++.h
 *
 *  Created on: 2 ноября 2017 г.
 *      Author: klen
 */

#ifndef __GPIO++_H__
#define __GPIO++_H__

#include "gpio_v2++.h"

namespace stm32f7
{

struct gpio_t : public stm32::gpio_v2_t
{
  inline bool clock_state()
   {
      switch((uint32_t)this)
        {
           case gpioa_addr : return rcc.gpioa_state();
           case gpiob_addr : return rcc.gpiob_state();
           case gpioc_addr : return rcc.gpioc_state();
           case gpiod_addr : return rcc.gpiod_state();
           case gpioe_addr : return rcc.gpioe_state();
           case gpiof_addr : return rcc.gpiof_state();
           case gpiog_addr : return rcc.gpiog_state();
           case gpioh_addr : return rcc.gpioh_state();
           case gpioi_addr : return rcc.gpioi_state();
           case gpioj_addr : return rcc.gpioj_state();
           case gpiok_addr : return rcc.gpiok_state();

           default: { std::__throw_invalid_argument("invalid GPIO object") ; }
        }
   }

  inline void clock_enable()
     {
        switch((uint32_t)this)
          {
             case gpioa_addr : rcc.gpioa_enable(); break ;
             case gpiob_addr : rcc.gpiob_enable(); break ;
             case gpioc_addr : rcc.gpioc_enable(); break ;
             case gpiod_addr : rcc.gpiod_enable(); break ;
             case gpioe_addr : rcc.gpioe_enable(); break ;
             case gpiof_addr : rcc.gpiof_enable(); break ;
             case gpiog_addr : rcc.gpiog_enable(); break ;
             case gpioh_addr : rcc.gpioh_enable(); break ;
             case gpioi_addr : rcc.gpioi_enable(); break ;
             case gpioj_addr : rcc.gpioj_enable(); break ;
             case gpiok_addr : rcc.gpiok_enable(); break ;

             default: { std::__throw_invalid_argument("invalid GPIO object") ; }
          }
     }

  inline void clock_disable()
     {
        switch((uint32_t)this)
          {
             case gpioa_addr : rcc.gpioa_disable(); break ;
             case gpiob_addr : rcc.gpiob_disable(); break ;
             case gpioc_addr : rcc.gpioc_disable(); break ;
             case gpiod_addr : rcc.gpiod_disable(); break ;
             case gpioe_addr : rcc.gpioe_disable(); break ;
             case gpiof_addr : rcc.gpiof_disable(); break ;
             case gpiog_addr : rcc.gpiog_disable(); break ;
             case gpioh_addr : rcc.gpioh_disable(); break ;
             case gpioi_addr : rcc.gpioi_disable(); break ;
             case gpioj_addr : rcc.gpioj_disable(); break ;
             case gpiok_addr : rcc.gpiok_disable(); break ;

             default: {  std::__throw_invalid_argument("invalid GPIO object") ; }
          }
     }

  inline void reset()
    {
        switch((uint32_t)this)
          {
             case gpioa_addr : rcc.gpioa_reset(); break ;
             case gpiob_addr : rcc.gpiob_reset(); break ;
             case gpioc_addr : rcc.gpioc_reset(); break ;
             case gpiod_addr : rcc.gpiod_reset(); break ;
             case gpioe_addr : rcc.gpioe_reset(); break ;
             case gpiof_addr : rcc.gpiof_reset(); break ;
             case gpiog_addr : rcc.gpiog_reset(); break ;
             case gpioh_addr : rcc.gpioh_reset(); break ;
             case gpioi_addr : rcc.gpioi_reset(); break ;
             case gpioj_addr : rcc.gpioj_reset(); break ;
             case gpiok_addr : rcc.gpiok_reset(); break ;
             default: {  std::__throw_invalid_argument("invalid GPIO object") ; }
          }
    };

  struct pin_config_t
    {
      gpio_t& port;
      const mode_t::enum_t mode;
      const output_type_t::enum_t output_type;
      const output_speed_t::enum_t output_speed ;
      const pull_t::enum_t pull ;
      const af_t::enum_t afio ;
      const pin_index_t pin;
      const bit_t bit;
      const output_t::enum_t state ;
    }  ;

  static inline void pin_configure(const pin_config_t& val, bool clock_enable=true)
    {
	  if (clock_enable)
	    val.port.clock_enable();
	  val.port.pin(val.pin, val.mode );
	  val.port.pin(val.pin, val.output_type);
	  val.port.pin(val.pin, val.output_speed );
	  val.port.pin(val.pin, val.pull );
	  val.port.pin(val.pin, val.afio);
	  val.port.pin(val.pin, val.state );
    }

  static inline void pin_default_state(const pin_config_t& val)
    {
	  val.port.pin(val.pin, mode_t::enum_t::input );
	  val.port.pin(val.pin, output_type_t::pull_push);
	  val.port.pin(val.pin, output_speed_t::low );
	  val.port.pin(val.pin, pull_t::no );
	  val.port.pin(val.pin, af_t::af0);
	  val.port.pin(val.pin, output_t::enum_t::reset );
    }

  static inline void pin_set  (const pin_config_t& val) { val.port.pin(val.pin, output_t::enum_t::set ); }
  static inline void pin_reset(const pin_config_t& val) { val.port.pin(val.pin, output_t::enum_t::reset ); }

  inline void pin_set  (const gpio_v2_t::pin_index_t index) { gpio_v2_t::pin_set(index); }
  inline void pin_reset(const gpio_v2_t::pin_index_t index) { gpio_v2_t::pin_reset(index); }

  inline void pin_set  (const gpio_v2_t::bit_t bit) { gpio_v2_t::pin_set(bit); }
  inline void pin_reset(const gpio_v2_t::bit_t bit) { gpio_v2_t::pin_reset(bit); }

};

struct gpioa_t : public gpio_t
{
  using gpio_t::pin ;
  template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
  template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

     struct af_t
	           {
	             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, sys=0, tim2_ch1_tim2_etr, tim5_ch1,  tim8_etr, usart2_cts=7, uart4_tx, sai2_sdb=10, eth_mii_crs, evemt_out=15} ; } ;
	             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, sys=0, tim2_ch2, tim5_ch2, usart2_rts=7, uart4_rx, quadspi_bk1_io3, mckb, eth_mii_rx_clk_eth_rmii_ref_clk, lcd_r2=14, evemt_out} ; } ;
	             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, sys=0, tim2_ch3, tim5_ch3, tim9_ch1, usart2_tx=7, sai2_sckb, eth_mdio=11, mdios_mdio, lcd_r1=14, evemt_out} ; } ;
	             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, sys=0, tim2_ch4, tim5_ch4, tim9_ch2, usart2_rx=7, lcd_b2=9, otghs_ulpi_d0, eth_mii_col, lcd_b5=14, evemt_out} ; } ;
	             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, sys=0, spi1_nss_i2s1_ws=5, spi3_nss_i2s3_ws, usart2_ck, spi6_nss, otghs_sof=12, dcmi_hsync, lcd_vsync, evemt_out} ; } ;
	             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, sys=0, tim2_ch1_tim2_etr, tim2_ch1n=3, spi1_sck_i2s1_ck=5, spi6_sck=8, otghs_ulpi_ck=10, lcd_r4=14, evemt_out} ; } ;
	             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, sys=0, tim1_bkin=1, tim3_ch1, tim8_bkin, spi1_miso=5, spi6_miso=8, tim13_ch1, mdioas_mdc=12, dcmi_pixclk, lcd_g2, evemt_out} ; } ;
	             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, sys=0, tim1_ch1n, tim3_ch2, tim8_ch1n, spi1_mosi_i2s1_sd=5, spi6_mosi=8, tim14_ch1, eth_mii_rx_dv_eth_rmii_crs_dv=11, fms_sd_nwe, evemt_out=15} ; } ;
	             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, mco1=0, tim1_ch1, tim8_bkin2=3, i2c3_scl, usart1_ck=7, otgfs_sof=10, can3_rx, uart7_rx, lcd_b3, lcd_r6, evemt_out} ; } ;
	             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, sys=0,tim1_ch2=1,i2c3_smba=4,spi2_sck_i2s2_ck=5,usart1_tx=7,dcmi_d0=13,lcd_r5, evemt_out} ; } ;
	             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, sys=0, tim1_ch3=1, usart1_rx=7, lcd_b4=9, otgfs_id, mdios_mdio=12, lcd_b1=14, evemt_out} ; } ;
	             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, sys=0, tim1_ch4=1, spi2_nss_i2s2_ws=5, uart4_rx, usart1_cts, can1_rx=9, otgfs_dm, lcd_r4=14, evemt_out} ; } ;
	             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, sys=0, tim1_etr=1, spi2_sck_i2s2_ck=5, uart4_tx, usart1_rts, sai2_fsb, can1_tx, otgfs_dp, lcd_r5=14, evemt_out} ; } ;
	             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, jtms_swdio=0, evemt_out=15} ; } ;
	             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, jtck_swclk=0, evemt_out=15} ; } ;
	             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, jtdi=0, tim2_ch1_tim2_etr=1, hdmi_cec=4, spi1_nss_i2s1_ws, spi3_nss_i2s3_ws, spi6_nss, uart4_rts, can3_tx=11, uart7_tx, evemt_out=15} ; } ;
	           };

          inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
          inline void pin0_af_sys()         { af.rmw( af_t::pin0_t::enum_t::sys ); }
          inline void pin0_af_tim2_ch1_tim2_etr() { af.rmw( af_t::pin0_t::enum_t::tim2_ch1_tim2_etr) ; }
          inline void pin0_af_tim5_ch1()    { af.rmw( af_t::pin0_t::enum_t::tim5_ch1) ; }
          inline void pin0_af_tim8_etr()    { af.rmw( af_t::pin0_t::enum_t::tim8_etr) ; }
          inline void pin0_af_usart2_cts()  { af.rmw( af_t::pin0_t::enum_t::usart2_cts) ; }
          inline void pin0_af_uart4_tx()    { af.rmw( af_t::pin0_t::enum_t::uart4_tx) ; }
          inline void pin0_af_eth_mii_crs() { af.rmw( af_t::pin0_t::enum_t::eth_mii_crs) ; }
          inline void pin0_af_evemt_out()   { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
          inline auto pin0_af()  const  { return af.rd<af_t::pin0_t>() ; }

          inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
          inline void pin1_af_sys()         { af.rmw( af_t::pin1_t::enum_t::sys) ; }
          inline void pin1_af_tim2_ch2()    { af.rmw( af_t::pin1_t::enum_t::tim2_ch2) ; }
          inline void pin1_af_tim5_ch2()    { af.rmw( af_t::pin1_t::enum_t::tim5_ch2) ; }
          inline void pin1_af_usart2_rts()  { af.rmw( af_t::pin1_t::enum_t::usart2_rts) ; }
          inline void pin1_af_uart4_rx()    { af.rmw( af_t::pin1_t::enum_t::uart4_rx) ; }
          inline void pin1_af_quadspi_bk1_io3() { af.rmw( af_t::pin1_t::enum_t::quadspi_bk1_io3) ; }
          inline void pin1_af_eth_mii_rx_clk_eth_rmii_ref_clk()  { af.rmw( af_t::pin1_t::enum_t::eth_mii_rx_clk_eth_rmii_ref_clk) ; }
          inline void pin1_af_lcd_r2()      { af.rmw( af_t::pin1_t::enum_t::lcd_r2) ; }
          inline void pin1_af_evemt_out()   { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
          inline auto pin1_af()  const  { return af.rd<af_t::pin1_t>() ; }

          inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
          inline void pin2_af_sys()         { af.rmw( af_t::pin2_t::enum_t::sys) ; }
          inline void pin2_af_tim2_ch3()    { af.rmw( af_t::pin2_t::enum_t::tim2_ch3) ; }
          inline void pin2_af_tim5_ch3()    { af.rmw( af_t::pin2_t::enum_t::tim5_ch3) ; }
          inline void pin2_af_tim9_ch1()    { af.rmw( af_t::pin2_t::enum_t::tim9_ch1) ; }
          inline void pin2_af_usart2_tx()   { af.rmw( af_t::pin2_t::enum_t::usart2_tx) ; }
          inline void pin2_af_eth_mdio()    { af.rmw( af_t::pin2_t::enum_t::eth_mdio) ; }
          inline void pin2_af_lcd_r1()      { af.rmw( af_t::pin2_t::enum_t::lcd_r1) ;}
          inline auto pin2_af()  const  { return af.rd<af_t::pin2_t>() ; }

          inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
          inline void pin3_af_sys()         { af.rmw( af_t::pin3_t::enum_t::sys) ; }
          inline void pin3_af_tim2_ch4()    { af.rmw( af_t::pin3_t::enum_t::tim2_ch4) ; }
          inline void pin3_af_tim5_ch4()    { af.rmw( af_t::pin3_t::enum_t::tim5_ch4) ; }
          inline void pin3_af_tim9_ch2()    { af.rmw( af_t::pin3_t::enum_t::tim9_ch2) ; }
          inline void pin3_af_usart2_rx()   { af.rmw( af_t::pin3_t::enum_t::usart2_rx) ; }
          inline void pin3_af_lcd_b2()      { af.rmw( af_t::pin3_t::enum_t::lcd_b2) ; }
          inline void pin3_af_otghs_ulpi_d0() { af.rmw( af_t::pin3_t::enum_t::otghs_ulpi_d0) ; }
          inline void pin3_af_eth_mii_col() { af.rmw( af_t::pin3_t::enum_t::eth_mii_col) ; }
          inline void pin3_af_lcd_b5()      { af.rmw( af_t::pin3_t::enum_t::lcd_b5) ;}
          inline void pin3_af_evemt_out()   { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
          inline auto pin3_af()  const  { return af.rd<af_t::pin3_t>() ; }

          inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
          inline void pin4_af_spi1_nss_i2s1_ws()    { af.rmw( af_t::pin4_t::enum_t::spi1_nss_i2s1_ws) ; }
          inline void pin4_af_spi3_nss_i2s3_ws()    { af.rmw( af_t::pin4_t::enum_t::spi3_nss_i2s3_ws) ; }
          inline void pin4_af_usart2_ck() { af.rmw( af_t::pin4_t::enum_t::usart2_ck) ; }
          inline void pin4_af_spi6_nss()  { af.rmw( af_t::pin4_t::enum_t::spi6_nss) ; }
          inline void pin4_af_otghs_sof() { af.rmw( af_t::pin4_t::enum_t::otghs_sof) ; }
          inline void pin4_af_dcmi_hsync(){ af.rmw( af_t::pin4_t::enum_t::dcmi_hsync) ; }
          inline void pin4_af_lcd_vsync() { af.rmw( af_t::pin4_t::enum_t::lcd_vsync) ; }
          inline void pin4_af_evemt_out() { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
          inline auto pin4_af()  const  { return af.rd<af_t::pin4_t>() ; }

          inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
          inline void pin5_af_sys()       { af.rmw( af_t::pin5_t::enum_t::sys) ; }
          inline void pin5_af_tim2_ch1_tim2_etr()    { af.rmw( af_t::pin5_t::tim2_ch1_tim2_etr) ; }
          inline void pin5_af_tim2_ch1n() { af.rmw( af_t::pin5_t::tim2_ch1n) ; }
          inline void pin5_af_spi1_sck_i2s1_ck() { af.rmw( af_t::pin5_t::spi1_sck_i2s1_ck) ; }
          inline void pin5_af_spi6_sck()  { af.rmw( af_t::pin5_t::spi6_sck) ; }
          inline void pin5_af_otghs_ulpi_ck() { af.rmw( af_t::pin5_t::otghs_ulpi_ck) ; }
          inline void pin5_af_lcd_r4()    { af.rmw( af_t::pin5_t::lcd_r4) ; }
          inline void pin5_af_evemt_out() { af.rmw( af_t::pin5_t::evemt_out) ; }
          inline auto pin5_af()  const  { return af.rd<af_t::pin5_t>() ; }

          inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
          inline void pin6_af_sys()       { af.rmw( af_t::pin6_t::enum_t::sys) ; }
          inline void pin6_af_spi1_tim1_bkin(){ af.rmw( af_t::pin6_t::enum_t::tim1_bkin) ; }
          inline void pin6_af_tim3_ch1()  { af.rmw( af_t::pin6_t::enum_t::tim3_ch1) ; }
          inline void pin6_af_tim8_bkin() { af.rmw( af_t::pin6_t::enum_t::tim8_bkin) ; }
          inline void pin6_af_spi1_miso() { af.rmw( af_t::pin6_t::enum_t::spi1_miso) ; }
          inline void pin6_af_spi6_miso() { af.rmw( af_t::pin6_t::enum_t::spi6_miso) ; }
          inline void pin6_af_tim13_ch1() { af.rmw( af_t::pin6_t::enum_t::tim13_ch1) ; }
          inline void pin6_af_mdioas_mdc(){ af.rmw( af_t::pin6_t::enum_t::mdioas_mdc) ; }
          inline void pin6_af_dcmi_pixclk(){ af.rmw( af_t::pin6_t::enum_t::dcmi_pixclk) ; }
          inline void pin6_af_lcd_g2()    { af.rmw( af_t::pin6_t::enum_t::lcd_g2) ; }
          inline void pin6_af_evemt_out() { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
          inline auto pin6_af_af()  const  { return af.rd<af_t::pin6_t>() ; }

          inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
          inline void pin7_af_sys()       { af.rmw( af_t::pin7_t::enum_t::sys) ; }
          inline void pin7_af_tim1_ch1n() { af.rmw( af_t::pin7_t::enum_t::tim1_ch1n) ; }
          inline void pin7_af_tim3_ch2()  { af.rmw( af_t::pin7_t::enum_t::tim3_ch2) ; }
          inline void pin7_af_tim8_ch1n() { af.rmw( af_t::pin7_t::enum_t::tim8_ch1n) ; }
          inline void pin7_af_spi1_mosi_i2s1_sd()  { af.rmw( af_t::pin7_t::enum_t::spi1_mosi_i2s1_sd) ; }
          inline void pin7_af_spi6_mosi() { af.rmw( af_t::pin7_t::enum_t::spi6_mosi) ; }
          inline void pin7_af_tim14_ch1() { af.rmw( af_t::pin7_t::enum_t::tim14_ch1) ; }
          inline void pin7_af_eth_mii_rx_dv_eth_rmii_crs_dv() { af.rmw( af_t::pin7_t::enum_t::eth_mii_rx_dv_eth_rmii_crs_dv) ; }
          inline void pin7_af_fms_sd_nwe(){ af.rmw( af_t::pin7_t::enum_t::fms_sd_nwe) ; }
          inline void pin7_af_evemt_out() { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
          inline auto pin7_af() const   { return af.rd<af_t::pin7_t>() ; }

          inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
          inline void pin8_af_mco1()      { af.rmw( af_t::pin8_t::enum_t::mco1) ; }
          inline void pin8_af_tim1_ch1() { af.rmw( af_t::pin8_t::enum_t::tim1_ch1) ; }
          inline void pin8_af_tim8_bkin2() { af.rmw( af_t::pin8_t::enum_t::tim8_bkin2) ; }
          inline void pin8_af_i2c3_scl() { af.rmw( af_t::pin8_t::enum_t::i2c3_scl) ; }
          inline void pin8_af_usart1_ck(){ af.rmw( af_t::pin8_t::enum_t::usart1_ck) ; }
          inline void pin8_af_otgfs_sof(){ af.rmw( af_t::pin8_t::enum_t::otgfs_sof) ; }
          inline void pin8_af_can3_rx(){ af.rmw( af_t::pin8_t::enum_t::can3_rx) ; }
          inline void pin8_af_uart7_rx() { af.rmw( af_t::pin8_t::enum_t::uart7_rx) ; }
          inline void pin8_af_lcd_b3()   { af.rmw( af_t::pin8_t::enum_t::lcd_b3) ; }
          inline void pin8_af_lcd_r6()   { af.rmw( af_t::pin8_t::enum_t::lcd_r6) ; }
          inline void pin8_af_evemt_out(){ af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
          inline auto pin8_af()  const  { return af.rd<af_t::pin8_t>() ; }

          inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
          inline void pin9_af_sys()      { af.rmw( af_t::pin9_t::enum_t::sys) ; }
          inline void pin9_af_tim1_ch2() { af.rmw( af_t::pin9_t::enum_t::tim1_ch2) ; }
          inline void pin9_af_i2c3_smba(){ af.rmw( af_t::pin9_t::enum_t::i2c3_smba) ; }
          inline void pin9_af_spi2_sck_i2s2_ck() { af.rmw( af_t::pin9_t::enum_t::spi2_sck_i2s2_ck) ; }
          inline void pin9_af_usart1_tx(){ af.rmw( af_t::pin9_t::enum_t::usart1_tx) ; }
          inline void pin9_af_dcmi_d0()  { af.rmw( af_t::pin9_t::enum_t::dcmi_d0) ; }
          inline void pin9_af_lcd_r5()   { af.rmw( af_t::pin9_t::enum_t::lcd_r5) ; }
          inline void pin9_af_evemt_out(){ af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
          inline auto pin9_af()  const  { return af.rd<af_t::pin9_t>() ; }

          inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
          inline void pin10_af_sys()           { af.rmw( af_t::pin10_t::enum_t::sys) ; }
          inline void pin10_af_tim1_ch3(){ af.rmw( af_t::pin10_t::enum_t::tim1_ch3) ; }
          inline void pin10_af_usart1_rx() { af.rmw( af_t::pin10_t::enum_t::usart1_rx) ; }
          inline void pin10_af_lcd_b4() { af.rmw( af_t::pin10_t::enum_t::lcd_b4) ; }
          inline void pin10_af_otgfs_id(){ af.rmw( af_t::pin10_t::enum_t::otgfs_id) ; }
          inline void pin10_af_mdios_mdio() { af.rmw( af_t::pin10_t::enum_t::mdios_mdio) ; }
          inline void pin10_af_lcd_b1(){ af.rmw( af_t::pin10_t::enum_t::lcd_b1) ; }
          inline void pin10_af_evemt_out() { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
          inline auto pin10_af() const   { return af.rd<af_t::pin10_t>() ; }

          inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
          inline void pin11_af_sys()       { af.rmw( af_t::pin11_t::enum_t::sys) ; }
          inline void pin11_af_tim1_ch4()  { af.rmw( af_t::pin11_t::enum_t::tim1_ch4) ; }
          inline void pin11_af_spi2_nss_i2s2_ws() { af.rmw( af_t::pin11_t::enum_t::spi2_nss_i2s2_ws) ; }
          inline void pin11_af_uart4_rx()  { af.rmw( af_t::pin11_t::enum_t::uart4_rx) ; }
          inline void pin11_af_usart1_cts()  { af.rmw( af_t::pin11_t::enum_t::usart1_cts) ; }
          inline void pin11_af_can1_rx()   { af.rmw( af_t::pin11_t::enum_t::can1_rx) ; }
          inline void pin11_af_otgfs_dm()  { af.rmw( af_t::pin11_t::enum_t::otgfs_dm) ; }
          inline void pin11_af_evemt_out() { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
          inline auto pin11_af()  const  { return af.rd<af_t::pin11_t>() ; }

          inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
          inline void pin12_af_sys()       { af.rmw( af_t::pin12_t::enum_t::sys) ; }
          inline void pin12_af_tim1_etr()  { af.rmw( af_t::pin12_t::enum_t::tim1_etr) ; }
          inline void pin12_af_spi2_sck_i2s2_ck() { af.rmw( af_t::pin12_t::enum_t::spi2_sck_i2s2_ck) ; }
          inline void pin12_af_uart4_tx()  { af.rmw( af_t::pin12_t::enum_t::uart4_tx) ; }
          inline void pin12_af_usart1_rts(){ af.rmw( af_t::pin12_t::enum_t::usart1_rts) ; }
          inline void pin12_af_sai2_fsb()  { af.rmw( af_t::pin12_t::enum_t::sai2_fsb) ; }
          inline void pin12_af_can1_tx()   { af.rmw( af_t::pin12_t::enum_t::can1_tx) ; }
          inline void pin12_af_otgfs_dp()  { af.rmw( af_t::pin12_t::enum_t::otgfs_dp) ; }
          inline void pin12_af_lcd_r5()    { af.rmw( af_t::pin12_t::enum_t::lcd_r5) ; }
          inline void pin12_af_evemt_out() { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
          inline auto pin12_af()  const  { return af.rd<af_t::pin12_t>() ; }


          inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
          inline void pin13_af_jtms_swdio() { af.rmw( af_t::pin13_t::enum_t::jtms_swdio) ; }
          inline void pin13_af_evemt_out()  { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
          inline auto pin13_af()  const  { return af.rd<af_t::pin13_t>() ; }


          inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
          inline void pin14_af_jtms_swdio(){ af.rmw( af_t::pin14_t::enum_t::jtck_swclk) ; }
          inline void pin14_af_evemt_out() { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
          inline auto pin14_af()  const  { return af.rd<af_t::pin14_t>() ; }

          inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
          inline void pin15_af_jtdi()      { af.rmw( af_t::pin15_t::enum_t::jtdi) ; }
          inline void pin15_af_tim2_ch1_tim2_etr()    { af.rmw( af_t::pin15_t::enum_t::tim2_ch1_tim2_etr) ; }
          inline void pin15_af_hdmi_cec()  { af.rmw( af_t::pin15_t::enum_t::hdmi_cec) ; }
          inline void pin15_af_spi1_nss_i2s1_ws() { af.rmw( af_t::pin15_t::enum_t::spi1_nss_i2s1_ws) ; }
          inline void pin15_af_spi3_nss_i2s3_ws()  { af.rmw( af_t::pin15_t::enum_t::spi3_nss_i2s3_ws) ; }
          inline void pin15_af_spi6_nss()  { af.rmw( af_t::pin15_t::enum_t::spi6_nss) ; }
          inline void pin15_af_uart4_rts() { af.rmw( af_t::pin15_t::enum_t::uart4_rts) ; }
          inline void pin15_af_can3_tx()   { af.rmw( af_t::pin15_t::enum_t::can3_tx) ; }
          inline void pin15_af_uart7_tx()  { af.rmw( af_t::pin15_t::enum_t::uart7_tx) ; }
          inline void pin15_af_evemt_out() { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
          inline auto pin15_af()  const  { return af.rd<af_t::pin15_t>() ; }

          inline void clock_enable() {  rcc.gpioa_enable() ; }
          inline void clock_disable() {  rcc.gpioa_disable() ; }
          inline void clock_reset() {  rcc.gpioa_reset() ; }

          inline static gpioa_t& ref() { return *((gpioa_t*) gpioa_addr); };

} ;

struct gpiob_t : public gpio_t
{

  using gpio_t::pin ;
  template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
  template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

  struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, sys=0, tim1_ch2n, tim3_ch3, tim8_ch2n, dfsdm1_ckout, usart4_cts=8, lcd_r3, otghs_ulpi_d1, eth_mii_rxd2, lcd_g1=14, evemt_out } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, sys=0, tim1_ch3n, tim3_ch4, tim8_ch3n, dfsdm1_datain1=6, lcd_r6=9, otghs_ulpi_d2, eth_mii_rxd3, lcd_g0=14, evemt_out } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, sys=0, sai1_sda=6, spi3_mosi_i2s3_sd, quadspi_clk=9, dfsdm1_ckin1, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, jtdo_traceswo=0, tim2_ch2, spi1_sck_i2s1_ck=5, spi3_sck_i2s3_ck, spi6_sck=8, sdmmc_d2=10, can3_rx, uart7_rx, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, njtrst=0, tim3_ch1=2, spi1_miso=5, spi3_miso, spi2_nss_i2s2_ws, spi6_miso, sdmmc2_d3=10, can3_tx, uart7_tx, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, sys=0, uart5_rx, tim3_ch2, hdmi_cec, i2c1_scl, spi3_mosi_i2s3_sd=6, spi6_mosi=8, can2_rx, otg_hs_ulpi_d7, eth_ops_out, fmc_sd_cke1, dcmi_d10, lcd_g7, evemt_out } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, sys=0, uart5_tx, tim4_ch1, hdmi_cec, i2c1_scl, dfsdm1_datain5, usart1_tx, can2_tx=9, quadspi_bk1_ncs, i2c4_scl, fmc_sd_ne1, dcmi_d5, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, sys=0, tim4_ch2=2, i2c1_sda=4, dfsdm1_ckin5=6, usart1_rx=7, i2s4_sda=11, fmc_nl=12, dcmi_vsync=13, evemt_out=15, } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, sys=0, i2c4_scl=1, tim4_ch3=2, tim10_ch1=3, i2c1_scl=4, dfsdm_ckin7=6, uart5_rx=7, can1_rx=9, sdmmc2_d4=10, eth_mii_txd3=11, sdmmc_d4=12, dcmi_d6=13, lcd_b6=14, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, sys=0, i2s4_sda=1, tim4_ch4=2, tim11_ch1=3, i2c1_sda=4, spi2_nss_i2s2_ws=5, dfsdm1_datain7=6, uart5_tx=7, can1_tx=9, sdmmc2=10, i2c4_smba=11, sdmmc_d5=12, dcmi_d7=13, lcd_b7=14, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, sys=0, tim2_ch3=1, i2c2_scl=4, spi2_sck_i2s2_ck, dfsdm_datain7, usart3_tx, quadspi_bk1_ncs=9, otghs_ulpi_d3, eth_mii_rxer, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, sys=0, tim2_ch4, i2c2_sda=4, dfsdm_ckin7=6, usart3_rx, otghs_ulpi_d4=10, eth_mii_txen_eth_rmii_txen, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, sys=0, tim1_bkin, i2s2_smba=4, spi2_nss_i2s2_ws, dfsdm1_datain1, usart3_ck, uart5_rx, can2_rx, otghs_ulpi_d5, eth_mii_txd0_eth_rmii_txd0, otghs_id, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, sys=0, tim1_ch1n, spi2_sck=5, dfsdm1_ckin1, usart3_cts, uart5_tx, can2_tx, otghs_ulpi_d6, eth_mii_txd1_eth_rmii_txd1, otghs_vbus=12, evemt_out=15} ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, sys=0, tim1_ch2n, tim8_ch2n=3, usart1_tx, spi2_miso, dfsdm1_datain2, usart3_rts, uart4_rts, tim12_ch1, sdmmc2_d0, otghs_dm=12, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, rtc_refin=0, tim1_ch3n,  tim8_ch3n=3, usart1_rx, spi2_mosi, dfsdm1_clin2, uart4_cts=8, tim12_ch2, sdmmc2_d1, otghs_dp=12, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_sys()           { af.rmw( af_t::pin0_t::enum_t::sys); }
        inline void pin0_af_tim1_ch2n()     { af.rmw( af_t::pin0_t::enum_t::tim1_ch2n); }
        inline void pin0_af_tim3_ch3()      { af.rmw( af_t::pin0_t::enum_t::tim3_ch3); }
        inline void pin0_af_tim8_ch2n()     { af.rmw( af_t::pin0_t::enum_t::tim8_ch2n); }
        inline void pin0_af_dfsdm1_ckout()  { af.rmw( af_t::pin0_t::enum_t::dfsdm1_ckout); }
        inline void pin0_af_usart4_cts()    { af.rmw( af_t::pin0_t::enum_t::usart4_cts); }
        inline void pin0_af_lcd_r3()        { af.rmw( af_t::pin0_t::enum_t::lcd_r3); }
        inline void pin0_af_otghs_ulpi_d1() { af.rmw( af_t::pin0_t::enum_t::otghs_ulpi_d1); }
        inline void pin0_af_eth_mii_rxd2()  { af.rmw( af_t::pin0_t::enum_t::eth_mii_rxd2); }
        inline void pin0_af_lcd_g1()        { af.rmw( af_t::pin0_t::enum_t::lcd_g1); }
        inline void pin0_af_evemt_out()     { af.rmw( af_t::pin0_t::enum_t::evemt_out); }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_sys()           { af.rmw( af_t::pin1_t::enum_t::sys); }
        inline void pin1_af_tim1_ch3n()     { af.rmw( af_t::pin1_t::enum_t::tim1_ch3n); }
        inline void pin1_af_tim3_ch4()      { af.rmw( af_t::pin1_t::enum_t::tim3_ch4); }
        inline void pin1_af_tim8_ch3n()     { af.rmw( af_t::pin1_t::enum_t::tim8_ch3n); }
        inline void pin1_af_dfsdm1_datain1(){ af.rmw( af_t::pin1_t::enum_t::dfsdm1_datain1); }
        inline void pin1_af_lcd_r6()        { af.rmw( af_t::pin1_t::enum_t::lcd_r6); }
        inline void pin1_af_otghs_ulpi_d2() { af.rmw( af_t::pin1_t::enum_t::otghs_ulpi_d2); }
        inline void pin1_af_eth_mii_rxd3()  { af.rmw( af_t::pin1_t::enum_t::eth_mii_rxd3); }
        inline void pin1_af_lcd_g0()        { af.rmw( af_t::pin1_t::enum_t::lcd_g0); }
        inline void pin1_af_evemt_out()     { af.rmw( af_t::pin1_t::enum_t::evemt_out); }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_sys()           { af.rmw( af_t::pin2_t::enum_t::sys); }
        inline void pin2_af_sai1_sda()      { af.rmw( af_t::pin2_t::enum_t::sai1_sda); }
        inline void pin2_af_spi3_mosi_i2s3_sd(){ af.rmw( af_t::pin2_t::enum_t::spi3_mosi_i2s3_sd); }
        inline void pin2_af_quadspi_clk()   { af.rmw( af_t::pin2_t::enum_t::quadspi_clk); }
        inline void pin2_af_dfsdm1_ckin1()  { af.rmw( af_t::pin2_t::enum_t::dfsdm1_ckin1); }
        inline void pin2_af_evemt_out()     { af.rmw( af_t::pin2_t::enum_t::evemt_out); }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_jtdo_traceswo() { af.rmw( af_t::pin3_t::enum_t::jtdo_traceswo); }
        inline void pin3_af_tim2_ch2()      { af.rmw( af_t::pin3_t::enum_t::tim2_ch2); }
        inline void pin3_af_spi1_sck_i2s1_ck(){ af.rmw( af_t::pin3_t::enum_t::spi1_sck_i2s1_ck); }
        inline void pin3_af_spi3_sck_i2s3_ck(){ af.rmw( af_t::pin3_t::enum_t::spi3_sck_i2s3_ck); }
        inline void pin3_af_spi6_sck()      { af.rmw( af_t::pin3_t::enum_t::spi6_sck); }
        inline void pin3_af_sdmmc_d2()      { af.rmw( af_t::pin3_t::enum_t::sdmmc_d2); }
        inline void pin3_af_can3_rx()       { af.rmw( af_t::pin3_t::enum_t::can3_rx); }
        inline void pin3_af_uart7_rx()      { af.rmw( af_t::pin3_t::enum_t::uart7_rx); }
        inline void pin3_af_evemt_out()     { af.rmw( af_t::pin3_t::enum_t::evemt_out); }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_njtrst()        { af.rmw( af_t::pin4_t::enum_t::njtrst); }
        inline void pin4_af_tim3_ch1()      { af.rmw( af_t::pin4_t::enum_t::tim3_ch1); }
        inline void pin4_af_spi1_miso()     { af.rmw( af_t::pin4_t::enum_t::spi1_miso); }
        inline void pin4_af_spi3_miso()     { af.rmw( af_t::pin4_t::enum_t::spi3_miso); }
        inline void pin4_af_spi2_nss_i2s2_ws(){ af.rmw( af_t::pin4_t::enum_t::spi2_nss_i2s2_ws); }
        inline void pin4_af_spi6_miso()     { af.rmw( af_t::pin4_t::enum_t::spi6_miso); }
        inline void pin4_af_sdmmc2_d3()     { af.rmw( af_t::pin4_t::enum_t::sdmmc2_d3); }
        inline void pin4_af_can3_tx()       { af.rmw( af_t::pin4_t::enum_t::can3_tx); }
        inline void pin4_af_uart7_tx()      { af.rmw( af_t::pin4_t::enum_t::uart7_tx); }
        inline void pin4_af_evemt_out()     { af.rmw( af_t::pin4_t::enum_t::evemt_out); }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_sys()           { af.rmw( af_t::pin5_t::enum_t::sys); }
        inline void pin5_af_uart5_rx()      { af.rmw( af_t::pin5_t::enum_t::uart5_rx); }
        inline void pin5_af_tim3_ch2()      { af.rmw( af_t::pin5_t::enum_t::tim3_ch2); }
        inline void pin5_af_hdmi_cec()      { af.rmw( af_t::pin5_t::enum_t::hdmi_cec); }
        inline void pin5_af_i2c1_scl()      { af.rmw( af_t::pin5_t::enum_t::i2c1_scl); }
        inline void pin5_af_spi3_mosi_i2s3_sd(){ af.rmw( af_t::pin5_t::enum_t::spi3_mosi_i2s3_sd); }
        inline void pin5_af_spi6_mosi()     { af.rmw( af_t::pin5_t::enum_t::spi6_mosi); }
        inline void pin5_af_can2_rx()       { af.rmw( af_t::pin5_t::enum_t::can2_rx); }
        inline void pin5_af_otg_hs_ulpi_d7(){ af.rmw( af_t::pin5_t::enum_t::otg_hs_ulpi_d7); }
        inline void pin5_af_eth_ops_out()   { af.rmw( af_t::pin5_t::enum_t::eth_ops_out); }
        inline void pin5_af_fmc_sd_cke1()   { af.rmw( af_t::pin5_t::enum_t::fmc_sd_cke1); }
        inline void pin5_af_dcmi_d10()      { af.rmw( af_t::pin5_t::enum_t::dcmi_d10); }
        inline void pin5_af_lcd_g7()        { af.rmw( af_t::pin5_t::enum_t::lcd_g7); }
        inline void pin5_af_evemt_out()     { af.rmw( af_t::pin5_t::enum_t::evemt_out); }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_sys()           { af.rmw( af_t::pin6_t::enum_t::sys); }
        inline void pin6_af_uart5_tx()      { af.rmw( af_t::pin6_t::enum_t::uart5_tx); }
        inline void pin6_af_tim4_ch1()      { af.rmw( af_t::pin6_t::enum_t::tim4_ch1); }
        inline void pin6_af_hdmi_cec()      { af.rmw( af_t::pin6_t::enum_t::hdmi_cec); }
        inline void pin6_af_i2c1_scl()      { af.rmw( af_t::pin6_t::enum_t::i2c1_scl); }
        inline void pin6_af_dfsdm1_datain5(){ af.rmw( af_t::pin6_t::enum_t::dfsdm1_datain5); }
        inline void pin6_af_usart1_tx()     { af.rmw( af_t::pin6_t::enum_t::usart1_tx); }
        inline void pin6_af_can2_tx()       { af.rmw( af_t::pin6_t::enum_t::can2_tx); }
        inline void pin6_af_quadspi_bk1_ncs(){ af.rmw( af_t::pin6_t::enum_t::quadspi_bk1_ncs); }
        inline void pin6_af_i2c4_scl()      { af.rmw( af_t::pin6_t::enum_t::i2c4_scl); }
        inline void pin6_af_fmc_sd_ne1()    { af.rmw( af_t::pin6_t::enum_t::fmc_sd_ne1); }
        inline void pin6_af_dcmi_d5()       { af.rmw( af_t::pin6_t::enum_t::dcmi_d5); }
        inline void pin6_af_evemt_out()     { af.rmw( af_t::pin6_t::enum_t::evemt_out); }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_sys()           { af.rmw( af_t::pin7_t::enum_t::sys); }
        inline void pin7_af_tim4_ch2()      { af.rmw( af_t::pin7_t::enum_t::tim4_ch2); }
        inline void pin7_af_i2c1_sda()      { af.rmw( af_t::pin7_t::enum_t::i2c1_sda); }
        inline void pin7_af_dfsdm1_ckin5()  { af.rmw( af_t::pin7_t::enum_t::dfsdm1_ckin5); }
        inline void pin7_af_usart1_rx()     { af.rmw( af_t::pin7_t::enum_t::usart1_rx); }
        inline void pin7_af_i2s4_sda()      { af.rmw( af_t::pin7_t::enum_t::i2s4_sda); }
        inline void pin7_af_fmc_nl()        { af.rmw( af_t::pin7_t::enum_t::fmc_nl); }
        inline void pin7_af_dcmi_vsync()    { af.rmw( af_t::pin7_t::enum_t::dcmi_vsync); }
        inline void pin7_af_evemt_out()     { af.rmw( af_t::pin7_t::enum_t::evemt_out); }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_sys()           { af.rmw( af_t::pin8_t::enum_t::sys); }
        inline void pin8_af_i2c4_scl()      { af.rmw( af_t::pin8_t::enum_t::i2c4_scl); }
        inline void pin8_af_tim4_ch3()      { af.rmw( af_t::pin8_t::enum_t::tim4_ch3); }
        inline void pin8_af_tim10_ch1()     { af.rmw( af_t::pin8_t::enum_t::tim10_ch1); }
        inline void pin8_af_i2c1_scl()      { af.rmw( af_t::pin8_t::enum_t::i2c1_scl); }
        inline void pin8_af_dfsdm_ckin7()   { af.rmw( af_t::pin8_t::enum_t::dfsdm_ckin7); }
        inline void pin8_af_uart5_rx()      { af.rmw( af_t::pin8_t::enum_t::uart5_rx); }
        inline void pin8_af_can1_rx()       { af.rmw( af_t::pin8_t::enum_t::can1_rx); }
        inline void pin8_af_sdmmc2_d4()     { af.rmw( af_t::pin8_t::enum_t::sdmmc2_d4); }
        inline void pin8_af_eth_mii_txd3()  { af.rmw( af_t::pin8_t::enum_t::eth_mii_txd3); }
        inline void pin8_af_sdmmc_d4()      { af.rmw( af_t::pin8_t::enum_t::sdmmc_d4); }
        inline void pin8_af_dcmi_d6()       { af.rmw( af_t::pin8_t::enum_t::dcmi_d6); }
        inline void pin8_af_lcd_b6()        { af.rmw( af_t::pin8_t::enum_t::lcd_b6); }
        inline void pin8_af_evemt_out()     { af.rmw( af_t::pin8_t::enum_t::evemt_out); }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_sys()           { af.rmw( af_t::pin9_t::enum_t::sys); }
        inline void pin9_af_i2s4_sda()      { af.rmw( af_t::pin9_t::enum_t::i2s4_sda); }
        inline void pin9_af_tim4_ch4()      { af.rmw( af_t::pin9_t::enum_t::tim4_ch4); }
        inline void pin9_af_tim11_ch1()     { af.rmw( af_t::pin9_t::enum_t::tim11_ch1); }
        inline void pin9_af_i2c1_sda()      { af.rmw( af_t::pin9_t::enum_t::i2c1_sda); }
        inline void pin9_af_spi2_nss_i2s2_ws(){ af.rmw( af_t::pin9_t::enum_t::spi2_nss_i2s2_ws); }
        inline void pin9_af_dfsdm1_datain7(){ af.rmw( af_t::pin9_t::enum_t::dfsdm1_datain7); }
        inline void pin9_af_uart5_tx()      { af.rmw( af_t::pin9_t::enum_t::uart5_tx); }
        inline void pin9_af_can1_tx()       { af.rmw( af_t::pin9_t::enum_t::can1_tx); }
        inline void pin9_af_sdmmc2()        { af.rmw( af_t::pin9_t::enum_t::sdmmc2); }
        inline void pin9_af_i2c4_smba()     { af.rmw( af_t::pin9_t::enum_t::i2c4_smba); }
        inline void pin9_af_sdmmc_d5()      { af.rmw( af_t::pin9_t::enum_t::sdmmc_d5); }
        inline void pin9_af_dcmi_d7()       { af.rmw( af_t::pin9_t::enum_t::dcmi_d7); }
        inline void pin9_af_lcd_b7()        { af.rmw( af_t::pin9_t::enum_t::lcd_b7); }
        inline void pin9_af_evemt_out()     { af.rmw( af_t::pin9_t::enum_t::evemt_out); }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_sys()          { af.rmw( af_t::pin10_t::enum_t::sys); }
        inline void pin10_af_tim2_ch3()     { af.rmw( af_t::pin10_t::enum_t::tim2_ch3); }
        inline void pin10_af_i2c2_scl()     { af.rmw( af_t::pin10_t::enum_t::i2c2_scl); }
        inline void pin10_af_spi2_sck_i2s2_ck() { af.rmw( af_t::pin10_t::enum_t::spi2_sck_i2s2_ck); }
        inline void pin10_af_dfsdm_datain7(){ af.rmw( af_t::pin10_t::enum_t::dfsdm_datain7); }
        inline void pin10_af_usart3_tx()    { af.rmw( af_t::pin10_t::enum_t::usart3_tx); }
        inline void pin10_af_quadspi_bk1_ncs() { af.rmw( af_t::pin10_t::enum_t::quadspi_bk1_ncs); }
        inline void pin10_af_otghs_ulpi_d3(){ af.rmw( af_t::pin10_t::enum_t::otghs_ulpi_d3); }
        inline void pin10_af_eth_mii_rxer() { af.rmw( af_t::pin10_t::enum_t::eth_mii_rxer); }
        inline void pin10_af_evemt_out()    { af.rmw( af_t::pin10_t::enum_t::evemt_out); }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_sys()          { af.rmw( af_t::pin11_t::enum_t::sys); }
        inline void pin11_af_tim2_ch4()     { af.rmw( af_t::pin11_t::enum_t::tim2_ch4); }
        inline void pin11_af_i2c2_sda()     { af.rmw( af_t::pin11_t::enum_t::i2c2_sda); }
        inline void pin11_af_dfsdm_ckin7()  { af.rmw( af_t::pin11_t::enum_t::dfsdm_ckin7); }
        inline void pin11_af_usart3_rx()    { af.rmw( af_t::pin11_t::enum_t::usart3_rx); }
        inline void pin11_af_otghs_ulpi_d4(){ af.rmw( af_t::pin11_t::enum_t::otghs_ulpi_d4); }
        inline void pin11_af_eth_mii_txen_eth_rmii_txen() { af.rmw( af_t::pin11_t::enum_t::eth_mii_txen_eth_rmii_txen); }
        inline void pin11_af_evemt_out()    { af.rmw( af_t::pin11_t::enum_t::evemt_out); }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_sys()          { af.rmw( af_t::pin12_t::enum_t::sys); }
        inline void pin12_af_tim1_bkin()    { af.rmw( af_t::pin12_t::enum_t::tim1_bkin); }
        inline void pin12_af_i2s2_smba()    { af.rmw( af_t::pin12_t::enum_t::i2s2_smba); }
        inline void pin12_af_spi2_nss_i2s2_ws() { af.rmw( af_t::pin12_t::enum_t::spi2_nss_i2s2_ws); }
        inline void pin12_af_dfsdm1_datain1() { af.rmw( af_t::pin12_t::enum_t::dfsdm1_datain1); }
        inline void pin12_af_usart3_ck()    { af.rmw( af_t::pin12_t::enum_t::usart3_ck); }
        inline void pin12_af_uart5_rx()     { af.rmw( af_t::pin12_t::enum_t::uart5_rx); }
        inline void pin12_af_can2_rx()      { af.rmw( af_t::pin12_t::enum_t::can2_rx); }
        inline void pin12_af_otghs_ulpi_d5() { af.rmw( af_t::pin12_t::enum_t::otghs_ulpi_d5); }
        inline void pin12_af_eth_mii_txd0_eth_rmii_txd0() { af.rmw( af_t::pin12_t::enum_t::eth_mii_txd0_eth_rmii_txd0); }
        inline void pin12_af_otghs_id()     { af.rmw( af_t::pin12_t::enum_t::otghs_id); }
        inline void pin12_af_evemt_out()    { af.rmw( af_t::pin12_t::enum_t::evemt_out); }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_sys()          { af.rmw( af_t::pin13_t::enum_t::sys); }
        inline void pin13_af_tim1_ch1n()    { af.rmw( af_t::pin13_t::enum_t::tim1_ch1n);}
        inline void pin13_af_spi2_sck()     { af.rmw( af_t::pin13_t::enum_t::spi2_sck);}
        inline void pin13_af_dfsdm1_ckin1() { af.rmw( af_t::pin13_t::enum_t::dfsdm1_ckin1);}
        inline void pin13_af_usart3_cts()   { af.rmw( af_t::pin13_t::enum_t::usart3_cts);}
        inline void pin13_af_uart5_tx()     { af.rmw( af_t::pin13_t::enum_t::uart5_tx);}
        inline void pin13_af_can2_tx()      { af.rmw( af_t::pin13_t::enum_t::can2_tx);}
        inline void pin13_af_otghs_ulpi_d6(){ af.rmw( af_t::pin13_t::enum_t::otghs_ulpi_d6);}
        inline void pin13_af_eth_mii_txd1_eth_rmii_txd1() { af.rmw( af_t::pin13_t::enum_t::eth_mii_txd1_eth_rmii_txd1);}
        inline void pin13_af_evemt_out()    { af.rmw( af_t::pin13_t::enum_t::evemt_out); }
        inline auto pin13_af() const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_sys()           { af.rmw( af_t::pin14_t::enum_t::sys); }
        inline void pin14_af_tim1_ch2n()     { af.rmw( af_t::pin14_t::enum_t::tim1_ch2n); }
        inline void pin14_af_tim8_ch2n()     { af.rmw( af_t::pin14_t::enum_t::tim8_ch2n); }
        inline void pin14_af_usart1_tx()     { af.rmw( af_t::pin14_t::enum_t::usart1_tx); }
        inline void pin14_af_spi2_miso()     { af.rmw( af_t::pin14_t::enum_t::spi2_miso); }
        inline void pin14_af_dfsdm1_datain2(){ af.rmw( af_t::pin14_t::enum_t::dfsdm1_datain2); }
        inline void pin14_af_usart3_rts()    { af.rmw( af_t::pin14_t::enum_t::usart3_rts); }
        inline void pin14_af_uart4_rts()     { af.rmw( af_t::pin14_t::enum_t::uart4_rts); }
        inline void pin14_af_tim12_ch1()     { af.rmw( af_t::pin14_t::enum_t::tim12_ch1); }
        inline void pin14_af_sdmmc2_d0()     { af.rmw( af_t::pin14_t::enum_t::sdmmc2_d0); }
        inline void pin14_af_otghs_dm()      { af.rmw( af_t::pin14_t::enum_t::otghs_dm); }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out); }
        inline auto pin14_af() const  { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_rtc_refin()     { af.rmw( af_t::pin15_t::enum_t::rtc_refin); }
        inline void pin15_af_tim1_ch3n()     { af.rmw( af_t::pin15_t::enum_t::tim1_ch3n); }
        inline void pin15_af_tim8_ch3n()     { af.rmw( af_t::pin15_t::enum_t::tim8_ch3n); }
        inline void pin15_af_usart1_rx()     { af.rmw( af_t::pin15_t::enum_t::usart1_rx); }
        inline void pin15_af_spi2_mosi()     { af.rmw( af_t::pin15_t::enum_t::spi2_mosi); }
        inline void pin15_af_dfsdm1_clin2()  { af.rmw( af_t::pin15_t::enum_t::dfsdm1_clin2); }
        inline void pin15_af_uart4_cts()     { af.rmw( af_t::pin15_t::enum_t::uart4_cts); }
        inline void pin15_af_tim12_ch2()     { af.rmw( af_t::pin15_t::enum_t::tim12_ch2); }
        inline void pin15_af_sdmmc2_d1()     { af.rmw( af_t::pin15_t::enum_t::sdmmc2_d1); }
        inline void pin15_af_otghs_dp()      { af.rmw( af_t::pin15_t::enum_t::otghs_dp ); }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out); }
        inline auto pin15_af() const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiob_enable() ; }
        inline void clock_disable() {  rcc.gpiob_disable() ; }
        inline void clock_reset() {  rcc.gpiob_reset() ; }

        inline static gpiob_t& ref() { return *((gpiob_t*) gpiob_addr); };
} ;

struct gpioc_t : public gpio_t
{
  using gpio_t::pin ;
  template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
  template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

  struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, sys=0, dfsdm1_ckin0=3, dfsdm1_datain4=6, sai2_fsb=8, otg_hs_ulpi_stp=10, fmc_sd_nwe=12, lcd_r5=14, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, traced0=0, dfsdm1_datain0=3, spi2_mosi_i2s2_sd=5, sai1_sda, dfsdm1_ckin4=10, eth_mdc, mdios_mdc, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, sys=0, dfsdm1_ckin1=3, spi2_miso=5, dfsdm1_ckout, otg_hs_ulpi_dir=10, eth_mii_txd2, fmc_sd_ne0, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, sys=0, dfsdm1_datain1=3, spi2_mosi_i2s2_sd=5, otg_hs_ulpi_nxt=10, eth_mii_tx_clk, fmc_sd_cke0, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, sys=0, dfsdm1_ckin2=3, i2s1_mck=5, spdif_rx2=8, eth_mii_rxd0_eth_rmii_rxd0=11, fmc_sd_ne0=12, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, sys=0, dfsdm1_datain2=3, spdif_rx3=8, eth_mii_rxd1_eth_rmii_rxd1=11, fmc_sd_cke0, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, sys=0, tim3_ch1=2, tim8_ch1, i2s2_mck=5, dfsdm1_ckin3=7, usart6_tx, fmc_nw_ait, sdmmc2_d6, sdmmc_d6=12, dcmi_d0, lcd_hsync, evemt_out } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, sys=0, tim3_ch2=2, tim8_ch2, i2s3_mck=6, dfsdm1_datain3, usart6_tx, fmc_ne1, sdmmc2_d7, sdmmc_d7=12, dcmi_d1, lcd_g6, evemt_out } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, traced1=0, tim3_ch3=2, tim8_ch3, uart5_rts=7, usart6_ck, fmc_ne2_fmc_nce, sdmmc_d0=12, dcmi_d2, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, mco2=0, tim3_ch4=2, tim8_ch4, i2c3_sda, i2s_ckin, usart5_cts=7, quadspi_bk1_io0=9, lcd_g3, sdmmc_d1=12, dcmi_d3, lcd_b2, evemt_out } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, sys=0, dfsdm1_ckin5=3, spi3_sck_i2s3_ck=6, usart3_tx, uart4_tx, quadspi_bk1_io1, sdmmc_d2=12, dcmi_d8, lcd_r2, evemt_out } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, sys=0, dfsdm1_datain5=3, spi3_miso=6, usart3_rx, uart4_rx, quadspi_bk2_ncs, sdmmc_d3=12, dcmi_d4, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, traced3=0, spi3_mosi_i2s3_sd=6, usart3_ck, uart5_tx, sdmmc_ck=12, dcmi_d9, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, sys=0, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, sys=0, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, sys=0, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_sys()            { af.rmw( af_t::pin0_t::enum_t::sys); }
        inline void pin0_af_dfsdm1_ckin0()   { af.rmw( af_t::pin0_t::enum_t::dfsdm1_ckin0); }
        inline void pin0_af_dfsdm1_datain4( ){ af.rmw( af_t::pin0_t::enum_t::dfsdm1_datain4); }
        inline void pin0_af_sai2_fsb()       { af.rmw( af_t::pin0_t::enum_t::sai2_fsb); }
        inline void pin0_af_otg_hs_ulpi_stp(){ af.rmw( af_t::pin0_t::enum_t::otg_hs_ulpi_stp); }
        inline void pin0_af_fmc_sd_nwe()     { af.rmw( af_t::pin0_t::enum_t::fmc_sd_nwe); }
        inline void pin0_af_lcd_r5()         { af.rmw( af_t::pin0_t::enum_t::lcd_r5); }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out); }
        inline auto pin0_af() const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_traced0()        { af.rmw( af_t::pin1_t::enum_t::traced0); }
        inline void pin1_af_dfsdm1_datain0() { af.rmw( af_t::pin1_t::enum_t::dfsdm1_datain0); }
        inline void pin1_af_spi2_mosi_i2s2_sd(){ af.rmw( af_t::pin1_t::enum_t::spi2_mosi_i2s2_sd); }
        inline void pin1_af_sai1_sda()       { af.rmw( af_t::pin1_t::enum_t::sai1_sda); }
        inline void pin1_af_dfsdm1_ckin4()   { af.rmw( af_t::pin1_t::enum_t::dfsdm1_ckin4); }
        inline void pin1_af_eth_mdc()        { af.rmw( af_t::pin1_t::enum_t::eth_mdc); }
        inline void pin1_af_mdios_mdc()      { af.rmw( af_t::pin1_t::enum_t::mdios_mdc); }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out); }
        inline auto pin1_af() const{ return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_sys()            { af.rmw( af_t::pin2_t::enum_t::sys); }
        inline void pin2_af_dfsdm1_ckin1()   { af.rmw( af_t::pin2_t::enum_t::dfsdm1_ckin1); }
        inline void pin2_af_spi2_miso()      { af.rmw( af_t::pin2_t::enum_t::spi2_miso); }
        inline void pin2_af_dfsdm1_ckout()   { af.rmw( af_t::pin2_t::enum_t::dfsdm1_ckout); }
        inline void pin2_af_otg_hs_ulpi_dir(){ af.rmw( af_t::pin2_t::enum_t::otg_hs_ulpi_dir); }
        inline void pin2_af_eth_mii_txd2()   { af.rmw( af_t::pin2_t::enum_t::eth_mii_txd2); }
        inline void pin2_af_fmc_sd_ne0()     { af.rmw( af_t::pin2_t::enum_t::fmc_sd_ne0); }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out); }
        inline auto pin2_af() const{ return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_sys()            { af.rmw( af_t::pin3_t::enum_t::sys); }
        inline void pin3_af_dfsdm1_datain1() { af.rmw( af_t::pin3_t::enum_t::dfsdm1_datain1); }
        inline void pin3_af_spi2_mosi_i2s2_sd() { af.rmw( af_t::pin3_t::enum_t::spi2_mosi_i2s2_sd); }
        inline void pin3_af_otg_hs_ulpi_nxt(){ af.rmw( af_t::pin3_t::enum_t::otg_hs_ulpi_nxt); }
        inline void pin3_af_eth_mii_tx_clk() { af.rmw( af_t::pin3_t::enum_t::eth_mii_tx_clk); }
        inline void pin3_af_fmc_sd_cke0()    { af.rmw( af_t::pin3_t::enum_t::fmc_sd_cke0); }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out); }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_sys()            { af.rmw( af_t::pin4_t::enum_t::sys); }
        inline void pin4_af_dfsdm1_ckin2()   { af.rmw( af_t::pin4_t::enum_t::dfsdm1_ckin2); }
        inline void pin4_af_spdif_rx2()      { af.rmw( af_t::pin4_t::enum_t::spdif_rx2); }
        inline void pin4_af_eth_mii_rxd0_eth_rmii_rxd0(){ af.rmw( af_t::pin4_t::enum_t::eth_mii_rxd0_eth_rmii_rxd0); }
        inline void pin4_af_fmc_sd_ne0()     { af.rmw( af_t::pin4_t::enum_t::fmc_sd_ne0); }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out); }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_sys()            { af.rmw( af_t::pin5_t::enum_t::sys); }
        inline void pin5_af_dfsdm1_datain2() { af.rmw( af_t::pin5_t::enum_t::dfsdm1_datain2); }
        inline void pin5_af_spdif_rx3()      { af.rmw( af_t::pin5_t::enum_t::spdif_rx3); }
        inline void pin5_af_eth_mii_rxd1_eth_rmii_rxd1(){ af.rmw( af_t::pin5_t::enum_t::eth_mii_rxd1_eth_rmii_rxd1); }
        inline void pin5_af_fmc_sd_cke0()    { af.rmw( af_t::pin5_t::enum_t::fmc_sd_cke0 ); }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out); }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_sys()            { af.rmw( af_t::pin6_t::enum_t::sys); }
        inline void pin6_af_tim3_ch1()       { af.rmw( af_t::pin6_t::enum_t::tim3_ch1); }
        inline void pin6_af_tim8_ch1()       { af.rmw( af_t::pin6_t::enum_t::tim8_ch1); }
        inline void pin6_af_i2s2_mck()       { af.rmw( af_t::pin6_t::enum_t::i2s2_mck); }
        inline void pin6_af_dfsdm1_ckin3()   { af.rmw( af_t::pin6_t::enum_t::dfsdm1_ckin3 ); }
        inline void pin6_af_usart6_tx()      { af.rmw( af_t::pin6_t::enum_t::usart6_tx ); }
        inline void pin6_af_fmc_nw_ait()     { af.rmw( af_t::pin6_t::enum_t::fmc_nw_ait ); }
        inline void pin6_af_sdmmc2_d6()      { af.rmw( af_t::pin6_t::enum_t::sdmmc2_d6 ); }
        inline void pin6_af_sdmmc_d6()       { af.rmw( af_t::pin6_t::enum_t::sdmmc_d6 ); }
        inline void pin6_af_dcmi_d0()        { af.rmw( af_t::pin6_t::enum_t::dcmi_d0 ); }
        inline void pin6_af_lcd_hsync()      { af.rmw( af_t::pin6_t::enum_t::lcd_hsync ); }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out); }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_sys()            { af.rmw( af_t::pin7_t::enum_t::sys); }
        inline void pin7_af_tim3_ch2()       { af.rmw( af_t::pin7_t::enum_t::tim3_ch2); }
        inline void pin7_af_tim8_ch2()       { af.rmw( af_t::pin7_t::enum_t::tim8_ch2); }
        inline void pin7_af_i2s3_mck()       { af.rmw( af_t::pin7_t::enum_t::i2s3_mck); }
        inline void pin7_af_dfsdm1_datain3() { af.rmw( af_t::pin7_t::enum_t::dfsdm1_datain3 ); }
        inline void pin7_af_usart6_tx()      { af.rmw( af_t::pin7_t::enum_t::usart6_tx ); }
        inline void pin7_af_fmc_ne1()        { af.rmw( af_t::pin7_t::enum_t::fmc_ne1); }
        inline void pin7_af_sdmmc2_d7()      { af.rmw( af_t::pin7_t::enum_t::sdmmc2_d7 ); }
        inline void pin7_af_sdmmc_d7()       { af.rmw( af_t::pin7_t::enum_t::sdmmc_d7 ); }
        inline void pin7_af_dcmi_d1()        { af.rmw( af_t::pin7_t::enum_t::dcmi_d1  ); }
        inline void pin7_af_lcd_g6()         { af.rmw( af_t::pin7_t::enum_t::lcd_g6 ); }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out); }
        inline auto pin7_af() const{ return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_traced1()         { af.rmw( af_t::pin8_t::enum_t::traced1); }
        inline void pin8_af_tim3_ch3()       { af.rmw( af_t::pin8_t::enum_t::tim3_ch3); }
        inline void pin8_af_tim8_ch3()       { af.rmw( af_t::pin8_t::enum_t::tim8_ch3); }
        inline void pin8_af_uart5_rts()      { af.rmw( af_t::pin8_t::enum_t::uart5_rts); }
        inline void pin8_af_usart6_ck()      { af.rmw( af_t::pin8_t::enum_t::usart6_ck); }
        inline void pin8_af_fmc_ne2_fmc_nce(){ af.rmw( af_t::pin8_t::enum_t::fmc_ne2_fmc_nce); }
        inline void pin8_af_sdmmc_d0()       { af.rmw( af_t::pin8_t::enum_t::sdmmc_d0); }
        inline void pin8_af_dcmi_d2()        { af.rmw( af_t::pin8_t::enum_t::dcmi_d2); }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out); }
        inline auto pin8_af() const{ return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_mco2()           { af.rmw( af_t::pin9_t::enum_t::mco2); }
        inline void pin9_af_tim3_ch4()       { af.rmw( af_t::pin9_t::enum_t::tim3_ch4); }
        inline void pin9_af_tim8_ch4()       { af.rmw( af_t::pin9_t::enum_t::tim8_ch4); }
        inline void pin9_af_i2c3_sda()       { af.rmw( af_t::pin9_t::enum_t::i2c3_sda); }
        inline void pin9_af_i2s_ckin()       { af.rmw( af_t::pin9_t::enum_t::i2s_ckin); }
        inline void pin9_af_usart5_cts()     { af.rmw( af_t::pin9_t::enum_t::usart5_cts); }
        inline void pin9_af_quadspi_bk1_io0(){ af.rmw( af_t::pin9_t::enum_t::quadspi_bk1_io0); }
        inline void pin9_af_lcd_g3()         { af.rmw( af_t::pin9_t::enum_t::lcd_g3); }
        inline void pin9_af_sdmmc_d1()       { af.rmw( af_t::pin9_t::enum_t::sdmmc_d1); }
        inline void pin9_af_dcmi_d3()        { af.rmw( af_t::pin9_t::enum_t::dcmi_d3); }
        inline void pin9_af_lcd_b2()         { af.rmw( af_t::pin9_t::enum_t::lcd_b2); }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out); }
        inline auto pin9_af() const{ return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_sys()           { af.rmw( af_t::pin10_t::enum_t::sys); }
        inline void pin10_af_dfsdm1_ckin5()  { af.rmw( af_t::pin10_t::enum_t::dfsdm1_ckin5); }
        inline void pin10_af_spi3_sck_i2s3_ck() { af.rmw( af_t::pin10_t::enum_t::spi3_sck_i2s3_ck); }
        inline void pin10_af_usart3_tx()     { af.rmw( af_t::pin10_t::enum_t::usart3_tx); }
        inline void pin10_af_uart4_tx()      { af.rmw( af_t::pin10_t::enum_t::uart4_tx); }
        inline void pin10_af_quadspi_bk1_io1(){ af.rmw( af_t::pin10_t::enum_t::quadspi_bk1_io1); }
        inline void pin10_af_sdmmc_d2()      { af.rmw( af_t::pin10_t::enum_t::sdmmc_d2); }
        inline void pin10_af_dcmi_d8()       { af.rmw( af_t::pin10_t::enum_t::dcmi_d8); }
        inline void pin10_af_lcd_r2()        { af.rmw( af_t::pin10_t::enum_t::lcd_r2); }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out); }
        inline auto pin10_af() const{return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_sys()           { af.rmw( af_t::pin11_t::enum_t::sys); }
        inline void pin11_af_dfsdm1_datain5(){ af.rmw( af_t::pin11_t::enum_t::dfsdm1_datain5); }
        inline void pin11_af_spi3_miso()     { af.rmw( af_t::pin11_t::enum_t::spi3_miso); }
        inline void pin11_af_usart3_rx()     { af.rmw( af_t::pin11_t::enum_t::usart3_rx); }
        inline void pin11_af_uart4_rx()      { af.rmw( af_t::pin11_t::enum_t::uart4_rx); }
        inline void pin11_af_quadspi_bk2_ncs(){ af.rmw( af_t::pin11_t::enum_t::quadspi_bk2_ncs); }
        inline void pin11_af_sdmmc_d3()      { af.rmw( af_t::pin11_t::enum_t::sdmmc_d3); }
        inline void pin11_af_dcmi_d4()       { af.rmw( af_t::pin11_t::enum_t::dcmi_d4); }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out); }
        inline auto pin11_af() const{ return af.rd<af_t::pin11_t>() ;}

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_traced3()       { af.rmw( af_t::pin12_t::enum_t::traced3); }
        inline void pin12_af_spi3_mosi_i2s3_sd(){ af.rmw( af_t::pin12_t::enum_t::spi3_mosi_i2s3_sd); }
        inline void pin12_af_usart3_ck()     { af.rmw( af_t::pin12_t::enum_t::usart3_ck); }
        inline void pin12_af_uart5_tx()      { af.rmw( af_t::pin12_t::enum_t::uart5_tx); }
        inline void pin12_af_sdmmc_ck()      { af.rmw( af_t::pin12_t::enum_t::sdmmc_ck); }
        inline void pin12_af_dcmi_d9()       { af.rmw( af_t::pin12_t::enum_t::dcmi_d9); }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out); }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }


        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_sys()           { af.rmw( af_t::pin13_t::enum_t::sys); }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out); }
        inline auto pin13_af() const{ return af.rd<af_t::pin13_t>() ; }


        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_sys()           { af.rmw( af_t::pin14_t::enum_t::sys); }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out); }
        inline auto pin14_af() const{ return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_sys()           { af.rmw( af_t::pin15_t::enum_t::sys); }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out); }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpioc_enable() ; }
        inline void clock_disable() {  rcc.gpioc_disable() ; }
        inline void clock_reset() {  rcc.gpioc_reset() ; }

        inline static gpioc_t& ref() { return *((gpioc_t*) gpioc_addr); };
};


struct gpiod_t : public gpio_t
{
  using gpio_t::pin ;
  template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
  template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

  struct af_t
                 {
                   struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, sys=0, dfsdm1_ckin6=3, dfsdm1_datain7=6, uart4_rx=8, can1_rx, fmc_d2=12, evemt_out=15 } ;} ;
                   struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, sys=0, dfsdm1_datain6=3, dfsdm1_ckin7=6, uart4_tx=8, can1_tx, fmc_d3=12, evemt_out=15 } ;} ;
                   struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, traced2=0, tim3_eth=2, uart3_rx=8, sdmmc_cmd=12, dcmi_d11, evemt_out=15 } ;} ;
                   struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, sys=0, dfsdm1_ckout=3, spi2_sck_i2s2_ck=5, dfsdm1_datain0, usart2_cts, fmc_clk=12, dcmi_d5, lcd_g7, evemt_out } ;} ;
                   struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, sys=0, dfsdm1_ckin0=6, usart2_rts, fmc_noe=12, evemt_out=15 } ;} ;
                   struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, sys=0, usart2_tx=7, fmc_nwe=12, evemt_out=15 } ;} ;
                   struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, sys=0, dfsdm1_ckin4=3, spi3_mosi_i2s1_sd=5, sai1_sda, usart2_rx, dfsdm1_datain1=10, sdmmc2_ck, fmc_nwait, dcmi_d10, lcd_b2, evemt_out } ;} ;
                   struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, sys=0, dfsdm1_datain4=3, spi1_mosi_i2s1_sd=5, dfsdm1_ckin1, usart2_ck, spdif_rx0, sdmmc2_cmd=11, fmc_ne1, evemt_out=15 } ;} ;
                   struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, sys=0, dfsdm1_ckin3=3, usart3_tx=7, spdif_rx1, fmc_d13=12, evemt_out=15 } ;} ;
                   struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, sys=0, dfsdm1_datain3=3, usart3_rx=7, fmc_d14=12, evemt_out=15 } ;} ;
                   struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, sys=0, dfsdm1_ckout=3, usart3_ck=7, fmc_d15=12, lcd_b3=14, evemt_out=15 } ;} ;
                   struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, sys=0, i2c4_smba=4, usart3_cts=7, quadspi_bk1_io0=9, sai2_sda_a, fmc_a16_fmc_cle=12, evemt_out=15 } ;} ;
                   struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, sys=0, tim4_ch1=2, lptim1_in, i2c4_sda, usart3_rts=7, quadspi_bk1_io1=9, sai2_fs_a, fmc_a17_fmc_ale=12, evemt_out=15 } ;} ;
                   struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, sys=0, tim4_ch2=2, lptim1_out, i2c4_sda, quadspi_bk1_io3=9, sai2_sck_a, fmc_a18=12, evemt_out=15 } ;} ;
                   struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, sys=0, tim4_ch3=2, uart8_cts=8, fmc_d0=12, evemt_out=15 } ;} ;
                   struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, sys=0, tim4_ch4=2, uart8_rts=8, fmc_d1=12, evemt_out=15 } ;} ;
                 };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_sys()            { af.rmw( af_t::pin0_t::enum_t::sys); }
        inline void pin0_af_dfsdm1_ckin6()   { af.rmw( af_t::pin0_t::enum_t::dfsdm1_ckin6 ); }
        inline void pin0_af_dfsdm1_datain7() { af.rmw( af_t::pin0_t::enum_t::dfsdm1_datain7); }
        inline void pin0_af_uart4_rx()       { af.rmw( af_t::pin0_t::enum_t::uart4_rx); }
        inline void pin0_af_can1_rx()        { af.rmw( af_t::pin0_t::enum_t::can1_rx); }
        inline void pin0_af_fmc_d2()         { af.rmw( af_t::pin0_t::enum_t::fmc_d2); }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out); }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_sys()            { af.rmw( af_t::pin1_t::enum_t::sys); }
        inline void pin1_af_dfsdm1_datain6() { af.rmw( af_t::pin1_t::enum_t::dfsdm1_datain6); }
        inline void pin1_af_dfsdm1_ckin7()   { af.rmw( af_t::pin1_t::enum_t::dfsdm1_ckin7); }
        inline void pin1_af_uart4_tx()       { af.rmw( af_t::pin1_t::enum_t::uart4_tx); }
        inline void pin1_af_can1_tx()        { af.rmw( af_t::pin1_t::enum_t::can1_tx); }
        inline void pin1_af_fmc_d3()         { af.rmw( af_t::pin1_t::enum_t::fmc_d3); }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out); }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_traced2()        { af.rmw( af_t::pin2_t::enum_t::traced2); }
        inline void pin2_af_tim3_eth()       { af.rmw( af_t::pin2_t::enum_t::tim3_eth); }
        inline void pin2_af_uart3_rx()       { af.rmw( af_t::pin2_t::enum_t::uart3_rx); }
        inline void pin2_af_sdmmc_cmd()      { af.rmw( af_t::pin2_t::enum_t::sdmmc_cmd); }
        inline void pin2_af_dcmi_d11()       { af.rmw( af_t::pin2_t::enum_t::dcmi_d11); }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out); }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_sys()            { af.rmw( af_t::pin3_t::enum_t::sys); }
        inline void pin3_af_dfsdm1_ckout()   { af.rmw( af_t::pin3_t::enum_t::dfsdm1_ckout); }
        inline void pin3_af_spi2_sck_i2s2_ck() { af.rmw( af_t::pin3_t::enum_t::spi2_sck_i2s2_ck); }
        inline void pin3_af_dfsdm1_datain0() { af.rmw( af_t::pin3_t::enum_t::dfsdm1_datain0); }
        inline void pin3_af_usart2_cts()     { af.rmw( af_t::pin3_t::enum_t::usart2_cts); }
        inline void pin3_af_fmc_clk()        { af.rmw( af_t::pin3_t::enum_t::fmc_clk); }
        inline void pin3_af_dcmi_d5()        { af.rmw( af_t::pin3_t::enum_t::dcmi_d5); }
        inline void pin3_af_lcd_g7()         { af.rmw( af_t::pin3_t::enum_t::lcd_g7); }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out); }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_sys()            { af.rmw( af_t::pin4_t::enum_t::sys); }
        inline void pin4_af_dfsdm1_ckin0()   { af.rmw( af_t::pin4_t::enum_t::dfsdm1_ckin0); }
        inline void pin4_af_usart2_rts()     { af.rmw( af_t::pin4_t::enum_t::usart2_rts); }
        inline void pin4_af_fmc_noe()        { af.rmw( af_t::pin4_t::enum_t::fmc_noe); }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out); }
        inline auto pin4_af() { return af.rd<af_t::pin4_t>() ;}

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_sys()            { af.rmw( af_t::pin5_t::enum_t::sys); }
        inline void pin5_af_usart2_tx()      { af.rmw( af_t::pin5_t::enum_t::usart2_tx); }
        inline void pin5_af_fmc_nwe()        { af.rmw( af_t::pin5_t::enum_t::fmc_nwe); }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out); }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_sys()            { af.rmw( af_t::pin6_t::enum_t::sys); }
        inline void pin6_af_dfsdm1_ckin4()   { af.rmw( af_t::pin6_t::enum_t::dfsdm1_ckin4); }
        inline void pin6_af_spi3_mosi_i2s1_sd(){ af.rmw( af_t::pin6_t::enum_t::spi3_mosi_i2s1_sd); }
        inline void pin6_af_sai1_sda()       { af.rmw( af_t::pin6_t::enum_t::sai1_sda); }
        inline void pin6_af_usart2_rx()      { af.rmw( af_t::pin6_t::enum_t::usart2_rx); }
        inline void pin6_af_dfsdm1_datain1() { af.rmw( af_t::pin6_t::enum_t::dfsdm1_datain1); }
        inline void pin6_af_sdmmc2_ck()      { af.rmw( af_t::pin6_t::enum_t::sdmmc2_ck); }
        inline void pin6_af_fmc_nwait()      { af.rmw( af_t::pin6_t::enum_t::fmc_nwait); }
        inline void pin6_af_dcmi_d10()       { af.rmw( af_t::pin6_t::enum_t::dcmi_d10); }
        inline void pin6_af_lcd_b2()         { af.rmw( af_t::pin6_t::enum_t::lcd_b2); }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out); }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_sys()            { af.rmw( af_t::pin7_t::enum_t::sys); }
        inline void pin7_af_dfsdm1_datain4() { af.rmw( af_t::pin7_t::enum_t::dfsdm1_datain4); }
        inline void pin7_af_spi1_mosi_i2s1_sd(){ af.rmw( af_t::pin7_t::enum_t::spi1_mosi_i2s1_sd); }
        inline void pin7_af_dfsdm1_ckin1()   { af.rmw( af_t::pin7_t::enum_t::dfsdm1_ckin1); }
        inline void pin7_af_usart2_ck()      { af.rmw( af_t::pin7_t::enum_t::usart2_ck); }
        inline void pin7_af_spdif_rx0()      { af.rmw( af_t::pin7_t::enum_t::spdif_rx0); }
        inline void pin7_af_sdmmc2_cmd()     { af.rmw( af_t::pin7_t::enum_t::sdmmc2_cmd); }
        inline void pin7_af_fmc_ne1()        { af.rmw( af_t::pin7_t::enum_t::fmc_ne1); }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out); }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_sys()            { af.rmw( af_t::pin8_t::enum_t::sys); }
        inline void pin8_af_dfsdm1_ckin3()   { af.rmw( af_t::pin8_t::enum_t::dfsdm1_ckin3); }
        inline void pin8_af_usart3_tx()      { af.rmw( af_t::pin8_t::enum_t::usart3_tx); }
        inline void pin8_af_spdif_rx1()      { af.rmw( af_t::pin8_t::enum_t::spdif_rx1); }
        inline void pin8_af_fmc_d13()        { af.rmw( af_t::pin8_t::enum_t::fmc_d13); }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out); }
        inline auto pin8_af() const{ return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_sys()            { af.rmw( af_t::pin9_t::enum_t::sys); }
        inline void pin9_af_dfsdm1_datain3() { af.rmw( af_t::pin9_t::enum_t::dfsdm1_datain3); }
        inline void pin9_af_usart3_rx()      { af.rmw( af_t::pin9_t::enum_t::usart3_rx); }
        inline void pin9_af_fmc_d14()        { af.rmw( af_t::pin9_t::enum_t::fmc_d14); }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out); }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ;}

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_sys()           { af.rmw( af_t::pin10_t::enum_t::sys); }
        inline void pin10_af_dfsdm1_ckout()  { af.rmw( af_t::pin10_t::enum_t::dfsdm1_ckout); }
        inline void pin10_af_usart3_ck()     { af.rmw( af_t::pin10_t::enum_t::usart3_ck); }
        inline void pin10_af_fmc_d15()       { af.rmw( af_t::pin10_t::enum_t::fmc_d15); }
        inline void pin10_af_lcd_b3()        { af.rmw( af_t::pin10_t::enum_t::lcd_b3); }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out); }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_sys()           { af.rmw( af_t::pin11_t::enum_t::sys); }
        inline void pin11_af_i2c4_smba()     { af.rmw( af_t::pin11_t::enum_t::i2c4_smba); }
        inline void pin11_af_usart3_cts()    { af.rmw( af_t::pin11_t::enum_t::usart3_cts); }
        inline void pin11_af_quadspi_bk1_io0(){ af.rmw( af_t::pin11_t::enum_t::quadspi_bk1_io0); }
        inline void pin11_af_sai2_sda_a()      { af.rmw( af_t::pin11_t::enum_t::sai2_sda_a); }
        inline void pin11_af_fmc_a16_fmc_cle(){ af.rmw( af_t::pin11_t::enum_t::fmc_a16_fmc_cle); }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out); }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_sys()           { af.rmw( af_t::pin12_t::enum_t::sys); }
        inline void pin12_af_tim4_ch1()      { af.rmw( af_t::pin12_t::enum_t::tim4_ch1); }
        inline void pin12_af_lptim1_in()     { af.rmw( af_t::pin12_t::enum_t::lptim1_in); }
        inline void pin12_af_i2c4_sda()      { af.rmw( af_t::pin12_t::enum_t::i2c4_sda); }
        inline void pin12_af_usart3_rts()    { af.rmw( af_t::pin12_t::enum_t::usart3_rts); }
        inline void pin12_af_quadspi_bk1_io1(){ af.rmw( af_t::pin12_t::enum_t::quadspi_bk1_io1); }
        inline void pin12_af_sai2_fs_a()     { af.rmw( af_t::pin12_t::enum_t::sai2_fs_a); }
        inline void pin12_af_fmc_a17_fmc_ale(){ af.rmw( af_t::pin12_t::enum_t::fmc_a17_fmc_ale); }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out); }
        inline auto pin12_af() const{ return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_sys()           { af.rmw( af_t::pin13_t::enum_t::sys); }
        inline void pin13_af_tim4_ch2()      { af.rmw( af_t::pin13_t::enum_t::tim4_ch2); }
        inline void pin13_af_lptim1_out()    { af.rmw( af_t::pin13_t::enum_t::lptim1_out); }
        inline void pin13_af_i2c4_sda()      { af.rmw( af_t::pin13_t::enum_t::i2c4_sda); }
        inline void pin13_af_quadspi_bk1_io3() { af.rmw( af_t::pin13_t::enum_t::quadspi_bk1_io3); }
        inline void pin13_af_sai2_sck_a()    { af.rmw( af_t::pin13_t::enum_t::sai2_sck_a); }
        inline void pin13_af_fmc_a18()       { af.rmw( af_t::pin13_t::enum_t::fmc_a18); }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out); }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_sys()           { af.rmw( af_t::pin14_t::enum_t::sys); }
        inline void pin14_af_tim4_ch3()      { af.rmw( af_t::pin14_t::enum_t::tim4_ch3); }
        inline void pin14_af_uart8_cts()     { af.rmw( af_t::pin14_t::enum_t::uart8_cts); }
        inline void pin14_af_fmc_d0()        { af.rmw( af_t::pin14_t::enum_t::fmc_d0); }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out); }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_sys()           { af.rmw( af_t::pin15_t::enum_t::sys); }
        inline void pin15_af_tim4_ch4()      { af.rmw( af_t::pin15_t::enum_t::tim4_ch4); }
        inline void pin15_af_uart8_rts()     { af.rmw( af_t::pin15_t::enum_t::uart8_rts); }
        inline void pin15_af_fmc_d1()        { af.rmw( af_t::pin15_t::enum_t::fmc_d1); }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out); }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiod_enable() ; }
        inline void clock_disable() {  rcc.gpiod_disable() ; }
        inline void clock_reset() {  rcc.gpiod_reset() ; }

        inline static gpiod_t& ref() { return *((gpiod_t*) gpiod_addr); };
} ;


struct gpioe_t : public gpio_t
{

   using gpio_t::pin ;
   template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
   template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

   struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, tim4_etr=2, lptim1_etr, uart8_rx=8, sai2_mck_a=10, fmc_nbl0=12, dcmi_d2, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, lptim1_in2=3, uart8_tx=8, fmc_nbl1=12, dcmi_d3, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, trace_clk=0, spi4_sck=5, sai1_mclk_a, quadspi_bk1_io2=9, eth_mii_tcd3=11, fmc_a23=12, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, trace_d0=0, sai1_sd_b=6, fmc_a19=12, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, trace_d1=0, spi4_nss=5, sai1_fs_a, dfsdm1_datain3=10, fmc_a20=12, dcmi_d4, lcd_b0, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, trace_d2=0, tim9_ch1=3, spi4_miso=5, sai1_sck_a, dfsdm1_ckin3=10,  fmc_a21=12, dcmi_d6, lcd_g0, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, trace_d3=0, tim1_bkin2, tim9_ch2=3, spi4_mosi=5, sai1_sd_a, sai2_mck_b=10,  fmc_a22=12, dcmi_d7, lcd_g1, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, tim1_etr=1, dfsdm1_datain2=6, uart7_rx=8, quadspi_bk2_io0=10, fmc_d4=12, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, tim1_ch1n=1, dfsdm1_ckin2=6, uart7_tx=8, quadspi_bk2_io1=10, fmc_d5=12, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, tim1_ch1=1, dfsdm1_ckout=6, uart7_rts=8, quadspi_bk2_io2=10, fmc_d6=12, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, tim1_ch2n=1, dfsdm1_datain4=6, uart7_cts=8, quadspi_bk2_io3=10, fmc_d7=12, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, tim1_ch2=1, spi4_nss=5, dfsdm1_clin4=6, sai2_sd_b=10, fmc_d8=12, lcd_g3=14, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, tim1_ch3n=1, spi4_sck=5, dfsdm1_datain5=6, sai2_sck_b=10, fmc_d9=12, lcd_b4=14, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, tim1_ch3=1, spi4_miso=5, dfsdm1_ckin5=6, sai2_fs_b=10, fmc_d10=12, lcd_de=14, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, tim1_ch4=1, spi4_mosi=5, sai2_mck_b=10, fmc_d11=12, lcd_clk=14, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, tim1_bkin=1, fmc_d12=12, lcd_r7=14, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_tim4_etr()       { af.rmw( af_t::pin0_t::enum_t::tim4_etr); }
        inline void pin0_af_lptim1_etr()     { af.rmw( af_t::pin0_t::enum_t::lptim1_etr); }
        inline void pin0_af_uart8_rx()       { af.rmw( af_t::pin0_t::enum_t::uart8_rx); }
        inline void pin0_af_sai2_mck_a()     { af.rmw( af_t::pin0_t::enum_t::sai2_mck_a); }
        inline void pin0_af_fmc_nbl0()       { af.rmw( af_t::pin0_t::enum_t::fmc_nbl0); }
        inline void pin0_af_dcmi_d2()        { af.rmw( af_t::pin0_t::enum_t::dcmi_d2); }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out); }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_lptim1_in2()     { af.rmw( af_t::pin1_t::enum_t::lptim1_in2) ; }
        inline void pin1_af_uart8_tx()       { af.rmw( af_t::pin1_t::enum_t::uart8_tx) ; }
        inline void pin1_af_fmc_nbl1()       { af.rmw( af_t::pin1_t::enum_t::fmc_nbl1) ; }
        inline void pin1_af_dcmi_d3()        { af.rmw( af_t::pin1_t::enum_t::dcmi_d3) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_trace_clk()      { af.rmw( af_t::pin2_t::enum_t::trace_clk) ; }
        inline void pin2_af_spi4_sck()       { af.rmw( af_t::pin2_t::enum_t::spi4_sck) ; }
        inline void pin2_af_sai1_mclk_a()    { af.rmw( af_t::pin2_t::enum_t::sai1_mclk_a) ; }
        inline void pin2_af_quadspi_bk1_io2(){ af.rmw( af_t::pin2_t::enum_t::quadspi_bk1_io2) ; }
        inline void pin2_af_eth_mii_tcd3()   { af.rmw( af_t::pin2_t::enum_t::eth_mii_tcd3) ; }
        inline void pin2_af_fmc_a23()        { af.rmw( af_t::pin2_t::enum_t::fmc_a23) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_trace_d0()       { af.rmw( af_t::pin3_t::enum_t::trace_d0) ; }
        inline void pin3_af_sai1_sd_b()      { af.rmw( af_t::pin3_t::enum_t::sai1_sd_b) ; }
        inline void pin3_af_fmc_a19()        { af.rmw( af_t::pin3_t::enum_t::fmc_a19) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_trace_d1()       { af.rmw( af_t::pin4_t::enum_t::trace_d1) ; }
        inline void pin4_af_spi4_nss()       { af.rmw( af_t::pin4_t::enum_t::spi4_nss) ; }
        inline void pin4_af_sai1_fs_a()      { af.rmw( af_t::pin4_t::enum_t::sai1_fs_a) ; }
        inline void pin4_af_dfsdm1_datain3() { af.rmw( af_t::pin4_t::enum_t::dfsdm1_datain3) ; }
        inline void pin4_af_fmc_a20()        { af.rmw( af_t::pin4_t::enum_t::fmc_a20) ; }
        inline void pin4_af_dcmi_d4()        { af.rmw( af_t::pin4_t::enum_t::dcmi_d4) ; }
        inline void pin4_af_lcd_b0()         { af.rmw( af_t::pin4_t::enum_t::lcd_b0) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_trace_d2()       { af.rmw( af_t::pin5_t::enum_t::trace_d2) ; }
        inline void pin5_af_tim9_ch1()       { af.rmw( af_t::pin5_t::enum_t::tim9_ch1) ; }
        inline void pin5_af_spi4_miso()      { af.rmw( af_t::pin5_t::enum_t::spi4_miso) ; }
        inline void pin5_af_sai1_sck_a()     { af.rmw( af_t::pin5_t::enum_t::sai1_sck_a) ; }
        inline void pin5_af_dfsdm1_ckin3()   { af.rmw( af_t::pin5_t::enum_t::dfsdm1_ckin3) ; }
        inline void pin5_af_fmc_a21()        { af.rmw( af_t::pin5_t::enum_t::fmc_a21) ; }
        inline void pin5_af_dcmi_d6()        { af.rmw( af_t::pin5_t::enum_t::dcmi_d6) ; }
        inline void pin5_af_lcd_g0()         { af.rmw( af_t::pin5_t::enum_t::lcd_g0) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_trace_d3()       { af.rmw( af_t::pin6_t::enum_t::trace_d3) ; }
        inline void pin6_af_tim1_bkin2()     { af.rmw( af_t::pin6_t::enum_t::tim1_bkin2) ; }
        inline void pin6_af_tim9_ch2()       { af.rmw( af_t::pin6_t::enum_t::tim9_ch2) ; }
        inline void pin6_af_spi4_mosi()      { af.rmw( af_t::pin6_t::enum_t::spi4_mosi) ; }
        inline void pin6_af_sai1_sd_a()      { af.rmw( af_t::pin6_t::enum_t::sai1_sd_a) ; }
        inline void pin6_af_sai2_mck_b()     { af.rmw( af_t::pin6_t::enum_t::sai2_mck_b) ; }
        inline void pin6_af_fmc_a22()        { af.rmw( af_t::pin6_t::enum_t::fmc_a22) ; }
        inline void pin6_af_dcmi_d7()        { af.rmw( af_t::pin6_t::enum_t::dcmi_d7) ; }
        inline void pin6_af_lcd_g1()         { af.rmw( af_t::pin6_t::enum_t::lcd_g1) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_tim1_etr()       { af.rmw( af_t::pin7_t::enum_t::tim1_etr); }
        inline void pin7_af_dfsdm1_datain2() { af.rmw( af_t::pin7_t::enum_t::dfsdm1_datain2); }
        inline void pin7_af_uart7_rx()       { af.rmw( af_t::pin7_t::enum_t::uart7_rx); }
        inline void pin7_af_quadspi_bk2_io0(){ af.rmw( af_t::pin7_t::enum_t::quadspi_bk2_io0); }
        inline void pin7_af_fmc_d4()         { af.rmw( af_t::pin7_t::enum_t::fmc_d4); }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out); }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_tim1_ch1n()      { af.rmw( af_t::pin8_t::enum_t::tim1_ch1n) ; }
        inline void pin8_af_dfsdm1_ckin2()   { af.rmw( af_t::pin8_t::enum_t::dfsdm1_ckin2) ; }
        inline void pin8_af_uart7_tx()       { af.rmw( af_t::pin8_t::enum_t::uart7_tx) ; }
        inline void pin8_af_quadspi_bk2_io1(){ af.rmw( af_t::pin8_t::enum_t::quadspi_bk2_io1) ; }
        inline void pin8_af_fmc_d5()         { af.rmw( af_t::pin8_t::enum_t::fmc_d5) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_tim1_ch1()       { af.rmw( af_t::pin9_t::enum_t::tim1_ch1) ; }
        inline void pin9_af_dfsdm1_ckout()   { af.rmw( af_t::pin9_t::enum_t::dfsdm1_ckout) ; }
        inline void pin9_af_uart7_rts()      { af.rmw( af_t::pin9_t::enum_t::uart7_rts) ; }
        inline void pin9_af_quadspi_bk2_io2(){ af.rmw( af_t::pin9_t::enum_t::quadspi_bk2_io2) ; }
        inline void pin9_af_fmc_d6()         { af.rmw( af_t::pin9_t::enum_t::fmc_d6) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_tim1_ch2n()     { af.rmw( af_t::pin10_t::enum_t::tim1_ch2n) ; }
        inline void pin10_af_dfsdm1_datain4(){ af.rmw( af_t::pin10_t::enum_t::dfsdm1_datain4) ; }
        inline void pin10_af_uart7_cts()     { af.rmw( af_t::pin10_t::enum_t::uart7_cts) ; }
        inline void pin10_af_quadspi_bk2_io3(){ af.rmw( af_t::pin10_t::enum_t::quadspi_bk2_io3) ; }
        inline void pin10_af_fmc_d7()        { af.rmw( af_t::pin10_t::enum_t::fmc_d7) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_tim1_ch2()      { af.rmw( af_t::pin11_t::enum_t::tim1_ch2) ; }
        inline void pin11_af_spi4_nss()      { af.rmw( af_t::pin11_t::enum_t::spi4_nss) ; }
        inline void pin11_af_dfsdm1_clin4()  { af.rmw( af_t::pin11_t::enum_t::dfsdm1_clin4) ; }
        inline void pin11_af_sai2_sd_b()     { af.rmw( af_t::pin11_t::enum_t::sai2_sd_b) ; }
        inline void pin11_af_fmc_d8()        { af.rmw( af_t::pin11_t::enum_t::fmc_d8) ; }
        inline void pin11_af_lcd_g3()        { af.rmw( af_t::pin11_t::enum_t::lcd_g3) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_tim1_ch3n()     { af.rmw( af_t::pin12_t::enum_t::tim1_ch3n) ; }
        inline void pin12_af_spi4_sck()      { af.rmw( af_t::pin12_t::enum_t::spi4_sck) ; }
        inline void pin12_af_dfsdm1_datain5(){ af.rmw( af_t::pin12_t::enum_t::dfsdm1_datain5) ; }
        inline void pin12_af_sai2_sck_b()    { af.rmw( af_t::pin12_t::enum_t::sai2_sck_b) ; }
        inline void pin12_af_fmc_d9()        { af.rmw( af_t::pin12_t::enum_t::fmc_d9) ; }
        inline void pin12_af_lcd_b4()        { af.rmw( af_t::pin12_t::enum_t::lcd_b4) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_tim1_ch3()      { af.rmw( af_t::pin13_t::enum_t::tim1_ch3) ; }
        inline void pin13_af_spi4_miso()     { af.rmw( af_t::pin13_t::enum_t::spi4_miso) ; }
        inline void pin13_af_dfsdm1_ckin5()  { af.rmw( af_t::pin13_t::enum_t::dfsdm1_ckin5) ; }
        inline void pin13_af_sai2_fs_b()     { af.rmw( af_t::pin13_t::enum_t::sai2_fs_b) ; }
        inline void pin13_af_fmc_d10()       { af.rmw( af_t::pin13_t::enum_t::fmc_d10) ; }
        inline void pin13_af_lcd_de()        { af.rmw( af_t::pin13_t::enum_t::lcd_de) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }



        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_tim1_ch4()      { af.rmw( af_t::pin14_t::enum_t::tim1_ch4) ; }
        inline void pin14_af_spi4_mosi()     { af.rmw( af_t::pin14_t::enum_t::spi4_mosi) ; }
        inline void pin14_af_sai2_mck_b()    { af.rmw( af_t::pin14_t::enum_t::sai2_mck_b) ; }
        inline void pin14_af_fmc_d11()       { af.rmw( af_t::pin14_t::enum_t::fmc_d11) ; }
        inline void pin14_af_lcd_clk()       { af.rmw( af_t::pin14_t::enum_t::lcd_clk) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_tim1_bkin()     { af.rmw( af_t::pin15_t::enum_t::tim1_bkin) ; }
        inline void pin15_af_fmc_d12()       { af.rmw( af_t::pin15_t::enum_t::fmc_d12) ; }
        inline void pin15_af_lcd_r7()        { af.rmw( af_t::pin15_t::enum_t::lcd_r7) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpioe_enable() ; }
        inline void clock_disable() {  rcc.gpioe_disable() ; }
        inline void clock_reset() {  rcc.gpioe_reset() ; }

        inline static gpioe_t& ref() { return *((gpioe_t*) gpioe_addr); };
} ;


struct gpiof_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, i2c2_sda=4, fmc_a0=12, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, i2c2_scl=4, fmc_a1=12, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, i2c2_smba=4, fmc_a2=12, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, fmc_a3=12, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, fmc_a4=12, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, fmc_a5=12, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, tim10_ch1=3, spi5_nss=5, uart7_rx=8, quadspi_bk1_io3, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, tim11_ch1=3, spi5_sck=5, sai1_mclk_b, uart7_tx=8, quadspi_bk1_io2, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, spi5_miso=5, sai1_sck_b, uart7_rts=8, tim13_ch1, quadspi_bk1_io0, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, spi5_mosi=5, sai1_fs_b, uart7_cts=8, tim14_ch1, quadspi_bk1_io1, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, quadspi_clk=9, dcmi_d11=13, lcd_de, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, spi5_mosi=5, sai2_sdb=10, fmc_sdnras=12, dcmi_d12, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, fmc_a6=12, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, i2c4_smba=4, dfsdm1_datain6=6, fmc_a7=12, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, i2c4_scl=4, dfsdm1_ckin6=6, fmc_a8=12, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, i2c4_sda=4, fmc_a9=12, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
	inline void pin0_af_i2c2_sda()       { af.rmw( af_t::pin0_t::enum_t::i2c2_sda) ; }
	inline void pin0_af_fmc_a0()         { af.rmw( af_t::pin0_t::enum_t::fmc_a0) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
	inline void pin1_af_i2c2_scl()       { af.rmw( af_t::pin1_t::enum_t::i2c2_scl) ; }
 	inline void pin1_af_fmc_a1()         { af.rmw( af_t::pin1_t::enum_t::fmc_a1) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
	inline void pin2_af_i2c2_smba()      { af.rmw( af_t::pin2_t::enum_t::i2c2_smba) ; }
	inline void pin2_af_fmc_a2()         { af.rmw( af_t::pin2_t::enum_t::fmc_a2) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_fmc_a3()         { af.rmw( af_t::pin3_t::enum_t::fmc_a3) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_fmc_a4()         { af.rmw( af_t::pin4_t::enum_t::fmc_a4) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_fmc_a5()         { af.rmw( af_t::pin5_t::enum_t::fmc_a5) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_tim10_ch1()      { af.rmw( af_t::pin6_t::enum_t::tim10_ch1) ; }
        inline void pin6_af_spi5_nss()       { af.rmw( af_t::pin6_t::enum_t::spi5_nss) ; }
        inline void pin6_af_uart7_rx()       { af.rmw( af_t::pin6_t::enum_t::uart7_rx) ; }
        inline void pin6_af_quadspi_bk1_io3(){ af.rmw( af_t::pin6_t::enum_t::quadspi_bk1_io3) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_tim11_ch1()      { af.rmw( af_t::pin7_t::enum_t::tim11_ch1) ; }
        inline void pin7_af_spi5_sck()       { af.rmw( af_t::pin7_t::enum_t::spi5_sck) ; }
        inline void pin7_af_sai1_mclk_b()    { af.rmw( af_t::pin7_t::enum_t::sai1_mclk_b) ; }
        inline void pin7_af_uart7_tx()       { af.rmw( af_t::pin7_t::enum_t::uart7_tx) ; }
        inline void pin7_af_quadspi_bk1_io2(){ af.rmw( af_t::pin7_t::enum_t::quadspi_bk1_io2) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_spi5_miso()      { af.rmw( af_t::pin8_t::enum_t::spi5_miso) ; }
        inline void pin8_af_sai1_sck_b()     { af.rmw( af_t::pin8_t::enum_t::sai1_sck_b) ; }
        inline void pin8_af_uart7_rts()      { af.rmw( af_t::pin8_t::enum_t::uart7_rts) ; }
        inline void pin8_af_tim13_ch1()      { af.rmw( af_t::pin8_t::enum_t::tim13_ch1) ; }
        inline void pin8_af_quadspi_bk1_io0(){ af.rmw( af_t::pin8_t::enum_t::quadspi_bk1_io0) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_spi5_mosi()      { af.rmw( af_t::pin9_t::enum_t::spi5_mosi) ; }
        inline void pin9_af_sai1_fs_b()      { af.rmw( af_t::pin9_t::enum_t::sai1_fs_b) ; }
        inline void pin9_af_uart7_cts()      { af.rmw( af_t::pin9_t::enum_t::uart7_cts) ; }
        inline void pin9_af_tim14_ch1()      { af.rmw( af_t::pin9_t::enum_t::tim14_ch1) ; }
        inline void pin9_af_quadspi_bk1_io1(){ af.rmw( af_t::pin9_t::enum_t::quadspi_bk1_io1) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin_af(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_quadspi_clk()      { af.rmw( af_t::pin10_t::enum_t::quadspi_clk) ; }
        inline void pin10_af_dcmi_d11()      { af.rmw( af_t::pin10_t::enum_t::dcmi_d11) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
	inline void pin11_af_spi5_mosi()     { af.rmw( af_t::pin11_t::enum_t::spi5_mosi) ; }
   	inline void pin11_af_fmc_sdnras()    { af.rmw( af_t::pin11_t::enum_t::fmc_sdnras) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_fmc_a6()        { af.rmw( af_t::pin12_t::enum_t::fmc_a6) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_i2c4_smba()     { af.rmw( af_t::pin13_t::enum_t::i2c4_smba) ; }
        inline void pin13_af_dfsdm1_datain6(){ af.rmw( af_t::pin13_t::enum_t::dfsdm1_datain6) ; }
        inline void pin13_af_fmc_a7()        { af.rmw( af_t::pin13_t::enum_t::fmc_a7) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_i2c4_scl()      { af.rmw( af_t::pin14_t::enum_t::i2c4_scl) ; }
        inline void pin14_af_dfsdm1_ckin6()  { af.rmw( af_t::pin14_t::enum_t::dfsdm1_ckin6) ; }
        inline void pin14_af_fmc_a8()        { af.rmw( af_t::pin14_t::enum_t::fmc_a8) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_i2c4_sda()      { af.rmw( af_t::pin15_t::enum_t::i2c4_sda) ; }
        inline void pin15_af_fmc_a9()        { af.rmw( af_t::pin15_t::enum_t::fmc_a9) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiof_enable() ; }
        inline void clock_disable() {  rcc.gpiof_disable() ; }
        inline void clock_reset() {  rcc.gpiof_reset() ; }

        inline static gpiof_t& ref() { return *((gpiof_t*) gpiof_addr); };

} ;

struct gpiog_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, fmc_a10=12, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, fmc_a11=12, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, fmc_a12=12, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, fmc_a13=12, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, fmc_a14_ba0=12, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, fmc_a15_ba1=12, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, fmc_ne3=12, dcmi_d12, lcd_r7, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, sai1_mclk_a=6, usart6_ck=8, fmc_int=12, dcmi_d13, lcd_clk, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, spi1_nss=5, spdif_rx2=7, usart6_rts, eth_pps_out=11, fmc_sdclk=12, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, spi1_miso=5, spdif_rx3=7, usart6_rx, quadspi_bk2_io2, sai2_fsb, sdmmc2_d0, fmc_ne2_nce=12, dcmi_vsync, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, spi1_nss_i2s1_ws=5, lcd_g3=9, sai2_sd_b, sdmmc1_d1, fmc_ne3=12, dcmi_d2, lcd_b2, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, spi1_sck_i2s1_ck=5, spdif_rx0=7, sdmmc2_d2=10, eth_mii_tx_en_eth_rmii_tx_en=11, dcmi_d3=13, lcd_b3, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, lptim1_in1=3, spi6_miso=5, spdif_rx1=7, usart6_rts=8, lcd_b4, sdmmc2_d3=11, fmc_ne4=12, lcd_b1, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, traced_0=0, lptim1_out=3, spi6_sck=5, usart6_cts=8, eth_mii_txd0_eth_rmii_txd0=11, fmc_a24=12, lcd_r0, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, traced_1=0, lptim1_etr=3, spi6_mosi=5, usart6_tx=8, quadspi_bk2_io3, eth_mii_txd1_eth_rmii_txd1=11, fmc_a25=12, lcd_b0, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, usart6_cts=8, fmc_sdncas=12, dcmi_d13, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
	inline void pin0_af_fmc_a10()        { af.rmw( af_t::pin0_t::enum_t::fmc_a10) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
	inline void pin1_af_fmc_a11()        { af.rmw( af_t::pin1_t::enum_t::fmc_a11) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
	inline void pin2_af_fmc_a12()        { af.rmw( af_t::pin2_t::enum_t::fmc_a12) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_fmc_a13()        { af.rmw( af_t::pin3_t::enum_t::fmc_a13) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_fmc_a14_ba0()    { af.rmw( af_t::pin4_t::enum_t::fmc_a14_ba0) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_fmc_a15_ba1()    { af.rmw( af_t::pin5_t::enum_t::fmc_a15_ba1) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_fmc_ne3()        { af.rmw( af_t::pin6_t::enum_t::fmc_ne3) ; }
        inline void pin6_af_dcmi_d12()       { af.rmw( af_t::pin6_t::enum_t::dcmi_d12) ; }
        inline void pin6_af_lcd_r7()         { af.rmw( af_t::pin6_t::enum_t::lcd_r7) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_sai1_mclk_a()    { af.rmw( af_t::pin7_t::enum_t::sai1_mclk_a) ; }
        inline void pin7_usart6_ckaf_()      { af.rmw( af_t::pin7_t::enum_t::usart6_ck) ; }
        inline void pin7_af_fmc_int()        { af.rmw( af_t::pin7_t::enum_t::fmc_int) ; }
        inline void pin7_af_dcmi_d13()       { af.rmw( af_t::pin7_t::enum_t::dcmi_d13) ; }
        inline void pin7_af_lcd_clk()        { af.rmw( af_t::pin7_t::enum_t::lcd_clk) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_spi1_nss()       { af.rmw( af_t::pin8_t::enum_t::spi1_nss) ; }
        inline void pin8_af_spdif_rx2()      { af.rmw( af_t::pin8_t::enum_t::spdif_rx2) ; }
        inline void pin8_af_usart6_rts()     { af.rmw( af_t::pin8_t::enum_t::usart6_rts) ; }
        inline void pin8_af_eth_pps_out()    { af.rmw( af_t::pin8_t::enum_t::eth_pps_out) ; }
        inline void pin8_af_fmc_sdclk()      { af.rmw( af_t::pin8_t::enum_t::fmc_sdclk) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_spi1_miso()      { af.rmw( af_t::pin9_t::enum_t::spi1_miso) ; }
        inline void pin9_af_spdif_rx3()      { af.rmw( af_t::pin9_t::enum_t::spdif_rx3) ; }
        inline void pin9_af_usart6_rx()      { af.rmw( af_t::pin9_t::enum_t::usart6_rx) ; }
        inline void pin9_af_quadspi_bk2_io2(){ af.rmw( af_t::pin9_t::enum_t::quadspi_bk2_io2) ; }
        inline void pin9_af_sai2_fsb()       { af.rmw( af_t::pin9_t::enum_t::sai2_fsb) ; }
        inline void pin9_af_sdmmc2_d0()      { af.rmw( af_t::pin9_t::enum_t::sdmmc2_d0) ; }
        inline void pin9_af_fmc_ne2_nce()    { af.rmw( af_t::pin9_t::enum_t::fmc_ne2_nce) ; }
        inline void pin9_af_dcmi_vsync()     { af.rmw( af_t::pin9_t::enum_t::dcmi_vsync) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_spi1_nss_i2s1_ws(){ af.rmw( af_t::pin10_t::enum_t::spi1_nss_i2s1_ws) ; }
        inline void pin10_af_lcd_g3()        { af.rmw( af_t::pin10_t::enum_t::lcd_g3) ; }
        inline void pin10_af_sai2_sd_b()     { af.rmw( af_t::pin10_t::enum_t::sai2_sd_b) ; }
        inline void pin10_af_sdmmc1_d1()     { af.rmw( af_t::pin10_t::enum_t::sdmmc1_d1) ; }
        inline void pin10_af_fmc_ne3()       { af.rmw( af_t::pin10_t::enum_t::fmc_ne3) ; }
        inline void pin10_af_dcmi_d2()       { af.rmw( af_t::pin10_t::enum_t::dcmi_d2) ; }
        inline void pin10_af_lcd_b2()        { af.rmw( af_t::pin10_t::enum_t::lcd_b2) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_spi1_sck_i2s1_ck(){ af.rmw( af_t::pin11_t::enum_t::spi1_sck_i2s1_ck) ; }
        inline void pin11_af_spdif_rx0()     { af.rmw( af_t::pin11_t::enum_t::spdif_rx0) ; }
        inline void pin11_af_sdmmc2_d2()     { af.rmw( af_t::pin11_t::enum_t::sdmmc2_d2) ; }
        inline void pin11_af_eth_mii_tx_en_eth_rmii_tx_en(){ af.rmw( af_t::pin11_t::enum_t::eth_mii_tx_en_eth_rmii_tx_en) ; }
        inline void pin11_af_dcmi_d3()       { af.rmw( af_t::pin11_t::enum_t::dcmi_d3) ; }
        inline void pin11_af_lcd_b3()        { af.rmw( af_t::pin11_t::enum_t::lcd_b3) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_lptim1_in1()    { af.rmw( af_t::pin12_t::enum_t::lptim1_in1) ; }
        inline void pin12_af_spi6_miso()     { af.rmw( af_t::pin12_t::enum_t::spi6_miso) ; }
        inline void pin12_af_spdif_rx1()     { af.rmw( af_t::pin12_t::enum_t::spdif_rx1) ; }
        inline void pin12_af_usart6_rts()    { af.rmw( af_t::pin12_t::enum_t::usart6_rts) ; }
        inline void pin12_af_lcd_b4()        { af.rmw( af_t::pin12_t::enum_t::lcd_b4) ; }
        inline void pin12_af_sdmmc2_d3()     { af.rmw( af_t::pin12_t::enum_t::sdmmc2_d3) ; }
        inline void pin12_af_fmc_ne4()       { af.rmw( af_t::pin12_t::enum_t::fmc_ne4) ; }
        inline void pin12_af_lcd_b1()        { af.rmw( af_t::pin12_t::enum_t::lcd_b1) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_traced_0()      { af.rmw( af_t::pin13_t::enum_t::traced_0) ; }
        inline void pin13_af_lptim1_out()    { af.rmw( af_t::pin13_t::enum_t::lptim1_out) ; }
        inline void pin13_af_spi6_sck()      { af.rmw( af_t::pin13_t::enum_t::spi6_sck) ; }
        inline void pin13_af_usart6_cts()    { af.rmw( af_t::pin13_t::enum_t::usart6_cts) ; }
        inline void pin13_af_eth_mii_txd0_eth_rmii_txd0()       { af.rmw( af_t::pin13_t::enum_t::eth_mii_txd0_eth_rmii_txd0) ; }
        inline void pin13_af_fmc_a24()       { af.rmw( af_t::pin13_t::enum_t::fmc_a24) ; }
        inline void pin13_af_lcd_r0()        { af.rmw( af_t::pin13_t::enum_t::lcd_r0) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_traced_1()      { af.rmw( af_t::pin14_t::enum_t::traced_1) ; }
        inline void pin14_af_lptim1_etr()    { af.rmw( af_t::pin14_t::enum_t::lptim1_etr) ; }
        inline void pin14_af_spi6_mosi()     { af.rmw( af_t::pin14_t::enum_t::spi6_mosi) ; }
        inline void pin14_af_usart6_tx()     { af.rmw( af_t::pin14_t::enum_t::usart6_tx) ; }
        inline void pin14_af_quadspi_bk2_io3(){ af.rmw( af_t::pin14_t::enum_t::quadspi_bk2_io3) ; }
        inline void pin14_af_eth_mii_txd1_eth_rmii_txd1()       { af.rmw( af_t::pin14_t::enum_t::eth_mii_txd1_eth_rmii_txd1) ; }
        inline void pin14_af_fmc_a25()       { af.rmw( af_t::pin14_t::enum_t::fmc_a25) ; }
        inline void pin14_af_lcd_b0()        { af.rmw( af_t::pin14_t::enum_t::lcd_b0) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_usart6_cts()    { af.rmw( af_t::pin15_t::enum_t::usart6_cts) ; }
        inline void pin15_af_fmc_sdncas()    { af.rmw( af_t::pin15_t::enum_t::fmc_sdncas) ; }
        inline void pin15_af_dcmi_d13()      { af.rmw( af_t::pin15_t::enum_t::dcmi_d13) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiog_enable() ; }
        inline void clock_disable() {  rcc.gpiog_disable() ; }
        inline void clock_reset() {  rcc.gpiog_reset() ; }

        inline static gpiog_t& ref() { return *((gpiog_t*) gpiog_addr); };
} ;

struct gpioh_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpioh_enable() ; }
        inline void clock_disable() {  rcc.gpioh_disable() ; }
        inline void clock_reset()   {  rcc.gpioh_reset() ; }

        inline static gpioh_t& ref() { return *((gpioh_t*) gpioh_addr); };
} ;

struct gpioi_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpioi_enable() ; }
        inline void clock_disable() {  rcc.gpioi_disable() ; }
        inline void clock_reset()   {  rcc.gpioi_reset() ; }

        inline static gpioi_t& ref() { return *((gpioi_t*) gpioi_addr); };
} ;

struct gpioj_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpioj_enable() ; }
        inline void clock_disable() {  rcc.gpioj_disable() ; }
        inline void clock_reset()   {  rcc.gpioj_reset() ; }

        inline static gpioj_t& ref() { return *((gpioj_t*) gpioj_addr); };
} ;

struct gpiok_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, evemt_out=15 } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, evemt_out=15 } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, evemt_out=15 } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, evemt_out=15 } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, evemt_out=15 } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, evemt_out=15 } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, evemt_out=15 } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, evemt_out=15 } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, evemt_out=15 } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, evemt_out=15 } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, evemt_out=15 } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, evemt_out=15 } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, evemt_out=15 } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, evemt_out=15 } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_evemt_out()      { af.rmw( af_t::pin0_t::enum_t::evemt_out) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline void pin1_af_evemt_out()      { af.rmw( af_t::pin1_t::enum_t::evemt_out) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline void pin2_af_evemt_out()      { af.rmw( af_t::pin2_t::enum_t::evemt_out) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline void pin3_af_evemt_out()      { af.rmw( af_t::pin3_t::enum_t::evemt_out) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline void pin4_af_evemt_out()      { af.rmw( af_t::pin4_t::enum_t::evemt_out) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline void pin5_af_evemt_out()      { af.rmw( af_t::pin5_t::enum_t::evemt_out) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline void pin6_af_evemt_out()      { af.rmw( af_t::pin6_t::enum_t::evemt_out) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline void pin7_af_evemt_out()      { af.rmw( af_t::pin7_t::enum_t::evemt_out) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline void pin8_af_evemt_out()      { af.rmw( af_t::pin8_t::enum_t::evemt_out) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline void pin9_af_evemt_out()      { af.rmw( af_t::pin9_t::enum_t::evemt_out) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline void pin10_af_evemt_out()     { af.rmw( af_t::pin10_t::enum_t::evemt_out) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline void pin11_af_evemt_out()     { af.rmw( af_t::pin11_t::enum_t::evemt_out) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline void pin12_af_evemt_out()     { af.rmw( af_t::pin12_t::enum_t::evemt_out) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline void pin13_af_evemt_out()     { af.rmw( af_t::pin13_t::enum_t::evemt_out) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline void pin14_af_evemt_out()     { af.rmw( af_t::pin14_t::enum_t::evemt_out) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline void pin15_af_evemt_out()     { af.rmw( af_t::pin15_t::enum_t::evemt_out) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpiok_enable() ; }
        inline void clock_disable() {  rcc.gpiok_disable() ; }
        inline void clock_reset()   {  rcc.gpiok_reset() ; }

        inline static gpiok_t& ref() { return *((gpiok_t*) gpiok_addr); };
} ;

static gpioa_t& gpioa = *((gpioa_t*) gpioa_addr);
static gpiob_t& gpiob = *((gpiob_t*) gpiob_addr);
static gpioc_t& gpioc = *((gpioc_t*) gpioc_addr);
static gpiod_t& gpiod = *((gpiod_t*) gpiod_addr);
static gpioe_t& gpioe = *((gpioe_t*) gpioe_addr);
static gpiof_t& gpiof = *((gpiof_t*) gpiof_addr);
static gpiog_t& gpiog = *((gpiog_t*) gpiog_addr);
static gpioh_t& gpioh = *((gpioh_t*) gpioh_addr);
static gpioi_t& gpioi = *((gpioi_t*) gpioi_addr);
static gpioj_t& gpioj = *((gpioj_t*) gpioj_addr);
static gpiok_t& gpiok = *((gpiok_t*) gpiok_addr);

}

using namespace stm32f7 ;

#endif /* __GPIO++_H__ */
