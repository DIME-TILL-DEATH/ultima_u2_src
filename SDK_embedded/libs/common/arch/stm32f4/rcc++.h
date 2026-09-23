/*
 * rcc++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __RCC++_H__
#define __RCC++_H__

#include "types++.h"
#include "flash++.h"

// TODO переделать до конца линейный доступ как inline void state_enable(const ahb1_peripheral_clock_t::peripheral_t val) { ahb1_peripheral_clock.rmw_bit_set( val ) ; }

namespace stm32f4
{
/**
  * @brief Reset and Clock Control
  */
struct rcc_t
{

  // необходимая задержка перед использованием переферии после включения тактирования
        // Cortex-M3/4 (errata):
  	// AHB: 2 AHB cycles (or DSB instruction)
  	// APB: 1 + (AHB/APB prescaler) AHB cycles (or DSB instruction)
  inline void clock_enable_delay()  { dsb(); }

  static const uint32_t hsi_freq = 16000000 ;

  struct clock_control_t : public read_write_32_t
  {
    enum osc_t { hsi=0, hse} ;


    struct hsi_t                     { enum enum_t { offset=0,  mask=1, off=0 , on } ; } ;
    struct hsi_ready_t               { enum enum_t { offset=1,  mask=1, not_ready=0 , ready } ; } ;
    struct hsi_trim_t                { enum enum_t { offset=3,  mask=0b11111 } ; } ;
    struct hsi_cal_t                 { enum enum_t { offset=8,  mask=0xff } ; } ;
    struct hse_t                     { enum enum_t { offset=16, mask=1, off=0 , on } ; } ;
    struct hse_ready_t               { enum enum_t { offset=17, mask=1, not_ready=0 , ready } ; } ;
    struct hse_clock_bypass_t        { enum enum_t { offset=18, mask=1, off=0 , on } ; } ;
    struct clock_security_system_t   { enum enum_t { offset=19, mask=1, disable=0 , enable} ; } ;
    struct pll_t                     { enum enum_t { offset=24, mask=1, off=0 , on } ; } ;
    struct pll_ready_t               { enum enum_t { offset=25, mask=1, not_ready=0 , ready } ; } ;
    struct pll_i2s_t                 { enum enum_t { offset=26, mask=1, off=0 , on } ; } ;
    struct pll_i2s_ready_t           { enum enum_t { offset=27, mask=1, not_ready=0 , ready } ; } ;
    struct pll_sai_t                 { enum enum_t { offset=28, mask=1, off=0 , on } ; } ;
    struct pll_sai_ready_t           { enum enum_t { offset=29, mask=1, not_ready=0 , ready } ; } ;
  };

  inline  void hsi( const clock_control_t::hsi_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hsi_off(){  clock_control.rmw( clock_control_t::hsi_t::off) ;}
  inline  void hsi_on() {  clock_control.rmw( clock_control_t::hsi_t::on) ;}
  inline  auto hsi() const {  return clock_control.rd<clock_control_t::hsi_t> ();}

  inline  auto hsi_ready() const {  return clock_control.rd<clock_control_t::hsi_ready_t> ();}
  inline  void hsi_ready_wait() const  { while ( hsi_ready() == clock_control_t::hsi_ready_t::not_ready)  {} ; }

  inline  void hsi_trim(uint8_t val){  clock_control.rmw( (clock_control_t::hsi_trim_t::enum_t)val) ;}
  inline  uint8_t hsi_trim(){  return (clock_control_t::hsi_trim_t::enum_t) clock_control.rd<clock_control_t::hsi_trim_t> ();}

  inline  void hsi_cal( const uint8_t val){  clock_control.rmw( (clock_control_t::hsi_cal_t::enum_t)val) ;}
  inline  uint8_t hsi_cal() const {  return (clock_control_t::hsi_cal_t::enum_t) clock_control.rd<clock_control_t::hsi_cal_t> ();}

  inline  void hse( const clock_control_t::hse_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_off(){  clock_control.rmw( clock_control_t::hse_t::off) ;}
  inline  void hse_on() {  clock_control.rmw( clock_control_t::hse_t::on) ;}
  inline  auto hse() const {  return clock_control.rd<clock_control_t::hse_t> ();}

  inline  auto hse_ready() const {  return clock_control.rd<clock_control_t::hse_ready_t> ();}
  inline  void hse_ready_wait() const  { while ( hse_ready() == clock_control_t::hse_ready_t::not_ready)  {} ; }

  inline  void hse_clock_bypass( const clock_control_t::hse_clock_bypass_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_clock_bypass_off(){  clock_control.rmw( clock_control_t::hse_clock_bypass_t::off) ;}
  inline  void hse_clock_bypass_on() {  clock_control.rmw( clock_control_t::hse_clock_bypass_t::on) ;}
  inline  auto hse_clock_bypass() const {  return clock_control.rd<clock_control_t::hse_clock_bypass_t> ();}

  inline  void clock_security_system( const clock_control_t::clock_security_system_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void clock_security_system_disable(){  clock_control.rmw( clock_control_t::clock_security_system_t::disable) ;}
  inline  void clock_security_system_enable() {  clock_control.rmw( clock_control_t::clock_security_system_t::enable) ;}
  inline  auto clock_security_system() const {  return clock_control.rd<clock_control_t::clock_security_system_t> ();}

  inline  void pll( const clock_control_t::pll_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_off(){  clock_control.rmw( clock_control_t::pll_t::off) ;}
  inline  void pll_on() {  clock_control.rmw( clock_control_t::pll_t::on) ;}
  inline  auto pll() const {  return clock_control.rd<clock_control_t::pll_t> ();}

  inline  auto pll_ready() const {  return clock_control.rd<clock_control_t::pll_ready_t> ();}
  inline  void pll_ready_wait() const { while ( pll_ready() == clock_control_t::pll_ready_t::not_ready)  {} ; }

  inline  void pll_i2s( const clock_control_t::pll_i2s_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_i2s_off(){  clock_control.rmw( clock_control_t::pll_i2s_t::off) ;}
  inline  void pll_i2s_on() {  clock_control.rmw( clock_control_t::pll_i2s_t::on) ;}
  inline  auto pll_i2s() const {  return clock_control.rd<clock_control_t::pll_i2s_t> ();}

  inline  auto pll_i2s_ready() const {  return clock_control.rd<clock_control_t::pll_i2s_ready_t> ();}
  inline  void pll_i2s_ready_wait() const  { while ( pll_i2s_ready() == clock_control_t::pll_i2s_ready_t::not_ready)  {} ; }

  inline  void pll_sai( const clock_control_t::pll_sai_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_sai_off(){  clock_control.rmw( clock_control_t::pll_sai_t::off) ;}
  inline  void pll_sai_on() {  clock_control.rmw( clock_control_t::pll_sai_t::on) ;}
  inline  auto pll_sai() const {  return clock_control.rd<clock_control_t::pll_sai_t> ();}

  inline  auto pll_sai_ready() const {  return clock_control.rd<clock_control_t::pll_sai_ready_t> ();}
  inline  void pll_sai_ready_wait() const  { while ( pll_sai_ready() == clock_control_t::pll_sai_ready_t::not_ready)  {} ; }


  struct pll_config_t : public read_write_32_t
  {
    struct m_t                { enum enum_t { offset=0,  mask=0b111111 } ; } ;
    struct n_t                { enum enum_t { offset=6,  mask=0b111111111 } ; } ;
    struct p_t                { enum enum_t { offset=16, mask=0b11, div2=0 , div4, div6, div8 } ; } ;
    struct source_t           { enum enum_t { offset=22, mask=1, /*hsi=0 , hse*/ /* используется тип clock_control_t::osc_t */ } ; } ;
    struct q_t                { enum enum_t { offset=24, mask=0b1111 } ; } ;
  }   ;

  inline  void pll_m( const uint8_t val){  pll_config.rmw( (pll_config_t::m_t::enum_t)val) ;}
  inline  uint8_t pll_m() const {  return (pll_config_t::m_t::enum_t) pll_config.rd<pll_config_t::m_t> ();}

  inline  void pll_n( const uint16_t val){  pll_config.rmw( (pll_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_n() const {  return (pll_config_t::n_t::enum_t) pll_config.rd<pll_config_t::n_t> ();}

  inline  void pll_p( const pll_config_t::p_t::enum_t val){ pll_config.rmw(val) ;}
  inline  auto pll_p() const {  return pll_config.rd<pll_config_t::p_t> ();}
  inline  uint8_t pll_p2v() const {  const uint8_t map[] = {2,4,6,8} ; return map[(size_t)pll_p()] ;}


  inline  void pll_source( const pll_config_t::source_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll_source_hsi(){  pll_config.rmw( (pll_config_t::source_t::enum_t) clock_control_t::osc_t::hsi) ;}
  inline  void pll_source_hse(){  pll_config.rmw( (pll_config_t::source_t::enum_t) clock_control_t::osc_t::hse) ;}
  inline  auto pll_source() const {  return  pll_config.rd<pll_config_t::source_t> ();}

  inline  void pll_q( const uint8_t val){  pll_config.rmw( (pll_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_q() const {  return (pll_config_t::q_t::enum_t) pll_config.rd<pll_config_t::q_t> ();}

  struct clock_config_t : public read_write_32_t
  {
    struct sys_clock_t                    { enum enum_t { offset=0,  mask=0b11, hsi=0, hse, pll } ; } ;
    struct sys_clock_state_t              { enum enum_t { offset=2,  mask=0b11, hsi=0, hse, pll } ; } ;
    struct ahb_prescaler_t                { enum enum_t { offset=4,  mask=0b1111, no_div=0b0000, div2=0b1000, div4=0b1001, div8=0b1010, div16=0b1011, div64=0b1100, div128=0b1101, div256=0b1110, div512=0b1111 } ; } ;
    struct apb1_prescaler_t               { enum enum_t { offset=10, mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct apb2_prescaler_t               { enum enum_t { offset=13, mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct hse_div_factor_for_rtc_clock_t { enum enum_t { offset=16, mask=0b11111 } ; } ;
    struct mco1_clock_output_t            { enum enum_t { offset=21, mask=0b11, hsi=0, lse, hse, pll } ; } ;
    struct i2s_clock_selection_t          { enum enum_t { offset=23, mask=0b1, pll_i2s=0, external } ; } ;
    struct mco1_prescaler_t               { enum enum_t { offset=24, mask=0b111, no_div=0b00, div2=0b100, div3, div4, div5 } ; } ;
    struct mco2_prescaler_t               { enum enum_t { offset=27, mask=0b111, no_div=0b00, div2=0b100, div3, div4, div5 } ; } ;
    struct mco2_clock_output_t            { enum enum_t { offset=30, mask=0b11, sysclk=0, pll_i2s, hse, pll } ; } ;

  } ;

  inline void sys_clock( const clock_config_t::sys_clock_t::enum_t val) { clock_config.rmw(val) ; }
  inline void sys_clock_hsi() { clock_config.rmw(clock_config_t::sys_clock_t::hsi) ; }
  inline void sys_clock_hse() { clock_config.rmw(clock_config_t::sys_clock_t::hse) ; }
  inline void sys_clock_pll() { clock_config.rmw(clock_config_t::sys_clock_t::pll) ; }
  inline auto sys_clock() const { return clock_config.rd<clock_config_t::sys_clock_t>() ; }

  inline auto sys_clock_state()  const { return clock_config.rd<clock_config_t::sys_clock_state_t>() ; }
  inline void sys_clock_state_hsi_wait() const { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::hsi ){ nop(); }; }
  inline void sys_clock_state_hse_wait() const { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::hse ){ nop(); }; }
  inline void sys_clock_state_pll_wait() const { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::pll ){ nop(); }; }

  inline void ahb_prescaler( const clock_config_t::ahb_prescaler_t::enum_t val) { clock_config.rmw(val) ; }
  inline void ahb_prescaler_no_div(){ clock_config.rmw(clock_config_t::ahb_prescaler_t::no_div); }
  inline void ahb_prescaler_div2()  { clock_config.rmw(clock_config_t::ahb_prescaler_t::div2)  ; }
  inline void ahb_prescaler_div4()  { clock_config.rmw(clock_config_t::ahb_prescaler_t::div4)  ; }
  inline void ahb_prescaler_div8()  { clock_config.rmw(clock_config_t::ahb_prescaler_t::div8)  ; }
  inline void ahb_prescaler_div16() { clock_config.rmw(clock_config_t::ahb_prescaler_t::div16) ; }
  inline void ahb_prescaler_div64() { clock_config.rmw(clock_config_t::ahb_prescaler_t::div64) ; }
  inline void ahb_prescaler_div128(){ clock_config.rmw(clock_config_t::ahb_prescaler_t::div128); }
  inline void ahb_prescaler_div256(){ clock_config.rmw(clock_config_t::ahb_prescaler_t::div256); }
  inline void ahb_prescaler_div512(){ clock_config.rmw(clock_config_t::ahb_prescaler_t::div512); }
  inline auto ahb_prescaler()  const { return clock_config.rd<clock_config_t::ahb_prescaler_t>() ; }

  inline void apb1_prescaler( const clock_config_t::apb1_prescaler_t::enum_t val) { clock_config.rmw(val) ; }
  inline void apb1_prescaler_no_div(){ clock_config.rmw(clock_config_t::apb1_prescaler_t::no_div) ; }
  inline void apb1_prescaler_div2()  { clock_config.rmw(clock_config_t::apb1_prescaler_t::div2) ; }
  inline void apb1_prescaler_div4()  { clock_config.rmw(clock_config_t::apb1_prescaler_t::div4) ; }
  inline void apb1_prescaler_div8()  { clock_config.rmw(clock_config_t::apb1_prescaler_t::div8) ; }
  inline void apb1_prescaler_div16() { clock_config.rmw(clock_config_t::apb1_prescaler_t::div16) ; }
  inline auto apb1_prescaler() const  { return clock_config.rd<clock_config_t::apb1_prescaler_t> () ; }

  inline void apb2_prescaler( const clock_config_t::apb2_prescaler_t::enum_t val) { clock_config.rmw(val) ; }
  inline void apb2_prescaler_no_div(){ clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::no_div) ; }
  inline void apb2_prescaler_div2()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div2) ; }
  inline void apb2_prescaler_div4()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div4) ; }
  inline void apb2_prescaler_div8()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div8) ; }
  inline void apb2_prescaler_div16() { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div16) ; }
  inline auto apb2_prescaler() const  { return clock_config.rd<clock_config_t::apb2_prescaler_t> () ; }


  inline void hse_divider_for_rtc_clock( const uint8_t val) { clock_config.rmw( (clock_config_t::hse_div_factor_for_rtc_clock_t::enum_t) val );  }
  inline uint8_t hse_divider_for_rtc_clock()  const { return (uint8_t) clock_config.rd<clock_config_t::hse_div_factor_for_rtc_clock_t> () ; }


  inline void mco1_clock_output( const clock_config_t::mco1_clock_output_t::enum_t val ) { clock_config.rmw(val) ; }
  inline void mco1_clock_output_hsi() { clock_config.rmw(clock_config_t::mco1_clock_output_t::hsi) ; }
  inline void mco1_clock_output_lse() { clock_config.rmw(clock_config_t::mco1_clock_output_t::lse) ; }
  inline void mco1_clock_output_hse() { clock_config.rmw(clock_config_t::mco1_clock_output_t::hse) ; }
  inline void mco1_clock_output_pll() { clock_config.rmw(clock_config_t::mco1_clock_output_t::pll) ; }
  inline auto mco1_clock_output()  const { return clock_config.rd<clock_config_t::mco1_clock_output_t> (); }

  inline void i2s_clock_selection( const clock_config_t::i2s_clock_selection_t::enum_t val) { clock_config.rmw(val) ; }
  inline void i2s_clock_selection_pll_i2s() { clock_config.rmw(clock_config_t::i2s_clock_selection_t::pll_i2s) ; }
  inline void i2s_clock_selection_external_ckin() { clock_config.rmw(clock_config_t::i2s_clock_selection_t::external) ; }
  inline auto i2s_clock_selection() const  { return clock_config.rd<clock_config_t::i2s_clock_selection_t>() ; }

  inline void mco1_prescaler( const clock_config_t::mco1_prescaler_t::enum_t val) { clock_config.rmw(val); }
  inline void mco1_prescaler_no_div(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::no_div); }
  inline void mco1_prescaler_div2(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div2); }
  inline void mco1_prescaler_div3(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div3);}
  inline void mco1_prescaler_div4(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div4);}
  inline void mco1_prescaler_div5(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div5);}
  inline auto mco1_prescaler()  const { return clock_config.rd<clock_config_t::mco1_prescaler_t>() ; }

  inline void mco2_prescaler( const clock_config_t::mco2_prescaler_t::enum_t val) { clock_config.rmw(val); }
  inline void mco2_prescaler_no_div(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::no_div); }
  inline void mco2_prescaler_div2(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div2); }
  inline void mco2_prescaler_div3(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div3);}
  inline void mco2_prescaler_div4(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div4);}
  inline void mco2_prescaler_div5(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div5);}
  inline auto mco2_prescaler()  const { return clock_config.rd<clock_config_t::mco2_prescaler_t>() ; }

  inline void mco2_clock_output( const clock_config_t::mco2_clock_output_t::enum_t val ) { clock_config.rmw(val) ; }
  inline void mco2_clock_output_sys_clk() { clock_config.rmw(clock_config_t::mco2_clock_output_t::sysclk) ; }
  inline void mco2_clock_output_pll_i2s() { clock_config.rmw(clock_config_t::mco2_clock_output_t::pll_i2s) ; }
  inline void mco2_clock_output_hse() { clock_config.rmw(clock_config_t::mco2_clock_output_t::hse) ; }
  inline void mco2_clock_output_pll() { clock_config.rmw(clock_config_t::mco2_clock_output_t::pll) ; }
  inline auto mco2_clock_output()  const { return clock_config.rd<clock_config_t::mco2_clock_output_t> (); }

  struct clock_interrupt_t : public read_write_32_t
  {
    struct lsi_ready_interupt_flag_t  { enum enum_t { offset=0,  mask=0b1, no_caused=0, caused } ; } ;
    struct lse_ready_interupt_flag_t  { enum enum_t { offset=1,  mask=0b1, no_caused=0, caused } ; } ;
    struct hsi_ready_interupt_flag_t  { enum enum_t { offset=2,  mask=0b1, no_caused=0, caused } ; } ;
    struct hse_ready_interupt_flag_t  { enum enum_t { offset=3,  mask=0b1, no_caused=0, caused } ; } ;
    struct pll_ready_interupt_flag_t  { enum enum_t { offset=4,  mask=0b1, no_caused=0, caused } ; } ;
    struct i2s_pll_ready_interupt_flag_t    { enum enum_t { offset=5,  mask=0b1, no_caused=0, caused } ; } ;
    struct sai_pll_ready_interupt_flag_t    { enum enum_t { offset=6,  mask=0b1, no_caused=0, caused } ; } ;
    struct security_system_interupt_flag_t  { enum enum_t { offset=7,  mask=0b1, no_caused=0, caused } ; } ;

    struct lsi_ready_interupt_t  { enum enum_t { offset=8,  mask=0b1, disable=0, enable } ; } ;
    struct lse_ready_interupt_t  { enum enum_t { offset=9,  mask=0b1, disable=0, enable } ; } ;
    struct hsi_ready_interupt_t  { enum enum_t { offset=10, mask=0b1, disable=0, enable } ; } ;
    struct hse_ready_interupt_t  { enum enum_t { offset=11, mask=0b1, disable=0, enable } ; } ;
    struct pll_ready_interupt_t        { enum enum_t { offset=12, mask=0b1, disable=0, enable } ; } ;
    struct i2s_pll_ready_interupt_t    { enum enum_t { offset=13, mask=0b1, disable=0, enable } ; } ;
    struct sai_pll_ready_interupt_t    { enum enum_t { offset=14, mask=0b1, disable=0, enable } ; } ;

    struct lsi_ready_interupt_clear_t  { enum enum_t { offset=16, mask=0b1, no_effect=0, perform } ; } ;
    struct lse_ready_interupt_clear_t  { enum enum_t { offset=17, mask=0b1, no_effect=0, perform } ; } ;
    struct hsi_ready_interupt_clear_t  { enum enum_t { offset=18, mask=0b1, no_effect=0, perform } ; } ;
    struct hse_ready_interupt_clear_t  { enum enum_t { offset=19, mask=0b1, no_effect=0, perform } ; } ;
    struct pll_ready_interupt_clear_t        { enum enum_t { offset=20, mask=0b1, no_effect=0, perform } ; } ;
    struct i2s_pll_ready_interupt_clear_t    { enum enum_t { offset=21, mask=0b1, no_effect=0, perform } ; } ;
    struct sai_pll_ready_interupt_clear_t    { enum enum_t { offset=22, mask=0b1, no_effect=0, perform } ; } ;
    struct security_system_interupt_clear_t  { enum enum_t { offset=23,  mask=0b1, no_effect=0, perform } ; } ;
  }   ;

  inline auto lsi_ready_interupt_flag() const { return clock_interrupt.rd<clock_interrupt_t::lsi_ready_interupt_flag_t>() ; }
  inline auto lse_ready_interupt_flag() const { return clock_interrupt.rd<clock_interrupt_t::lse_ready_interupt_flag_t>() ; }
  inline auto hsi_ready_interupt_flag() const { return clock_interrupt.rd<clock_interrupt_t::hsi_ready_interupt_flag_t>() ; }
  inline auto hse_ready_interupt_flag() const { return clock_interrupt.rd<clock_interrupt_t::hse_ready_interupt_flag_t>() ; }
  inline auto pll_ready_interupt_flag()  const { return clock_interrupt.rd<clock_interrupt_t::pll_ready_interupt_flag_t>() ; }
  inline auto i2s_pll_ready_interupt_flag()  const { return clock_interrupt.rd<clock_interrupt_t::i2s_pll_ready_interupt_flag_t>() ; }
  inline auto sai_pll_ready_interupt_flag()  const { return clock_interrupt.rd<clock_interrupt_t::sai_pll_ready_interupt_flag_t>() ; }
  inline auto security_system_interupt_flag() const  { return clock_interrupt.rd<clock_interrupt_t::security_system_interupt_flag_t>() ; }

  inline void lsi_ready_interupt( const clock_interrupt_t::lsi_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void lsi_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_t::disable) ; }
  inline void lsi_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_t::enable) ; }
  inline auto lsi_ready_interupt() const  { return clock_interrupt.rd<clock_interrupt_t::lsi_ready_interupt_t>() ; }

  inline void lse_ready_interupt( const clock_interrupt_t::lse_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void lse_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_t::disable) ; }
  inline void lse_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_t::enable) ; }
  inline auto lse_ready_interupt()  const { return clock_interrupt.rd<clock_interrupt_t::lse_ready_interupt_t>() ; }

  inline void hsi_ready_interupt( const clock_interrupt_t::hsi_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void hsi_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_t::disable) ; }
  inline void hsi_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_t::enable) ; }
  inline auto hsi_ready_interupt()  const { return clock_interrupt.rd<clock_interrupt_t::hsi_ready_interupt_t>() ; }

  inline void hse_ready_interupt( const clock_interrupt_t::hse_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void hse_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_t::disable) ; }
  inline void hse_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_t::enable) ; }
  inline auto hse_ready_interupt() const  { return clock_interrupt.rd<clock_interrupt_t::hse_ready_interupt_t>() ; }

  inline void pll_ready_interupt( const clock_interrupt_t::pll_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void pll_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::pll_ready_interupt_t::disable) ; }
  inline void pll_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::pll_ready_interupt_t::enable) ; }
  inline auto pll_ready_interupt()  const { return clock_interrupt.rd<clock_interrupt_t::pll_ready_interupt_t>() ; }

  inline void i2s_pll_ready_interupt( const clock_interrupt_t::i2s_pll_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void i2s_pll_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::i2s_pll_ready_interupt_t::disable) ; }
  inline void i2s_pll_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::i2s_pll_ready_interupt_t::enable) ; }
  inline auto i2s_pll_ready_interupt()  const { return clock_interrupt.rd<clock_interrupt_t::i2s_pll_ready_interupt_t>() ; }

  inline void sai_pll_ready_interupt( const clock_interrupt_t::sai_pll_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void sai_pll_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::sai_pll_ready_interupt_t::disable) ; }
  inline void sai_pll_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::sai_pll_ready_interupt_t::enable) ; }
  inline auto sai_pll_ready_interupt()  const { return clock_interrupt.rd<clock_interrupt_t::sai_pll_ready_interupt_t>() ; }

  inline void lsi_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_clear_t::perform) ; }
  inline void lse_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_clear_t::perform) ; }
  inline void hsi_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_clear_t::perform) ; }
  inline void hse_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_clear_t::perform) ; }
  inline void pll_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::pll_ready_interupt_clear_t::perform) ; }
  inline void i2s_pll_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::i2s_pll_ready_interupt_clear_t::perform) ; }
  inline void sai_pll_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::sai_pll_ready_interupt_clear_t::perform) ; }
  inline void security_system_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::security_system_interupt_clear_t::perform) ; }


  struct ahb1_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct gpioa_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct gpiob_reset_state_t  { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;
    struct gpioc_reset_state_t  { enum enum_t { offset=2, mask=0b1, no_reset=0, reset } ; } ;
    struct gpiod_reset_state_t  { enum enum_t { offset=3, mask=0b1, no_reset=0, reset } ; } ;
    struct gpioe_reset_state_t  { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct gpiof_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct gpiog_reset_state_t  { enum enum_t { offset=6, mask=0b1, no_reset=0, reset } ; } ;
    struct gpioh_reset_state_t  { enum enum_t { offset=7, mask=0b1, no_reset=0, reset } ; } ;
    struct gpioi_reset_state_t  { enum enum_t { offset=8, mask=0b1, no_reset=0, reset } ; } ;
    struct gpioj_reset_state_t  { enum enum_t { offset=9, mask=0b1, no_reset=0, reset } ; } ;
    struct gpiok_reset_state_t  { enum enum_t { offset=10,mask=0b1, no_reset=0, reset } ; } ;
    struct crc_reset_state_t    { enum enum_t { offset=12,mask=0b1, no_reset=0, reset } ; } ;
    struct dma1_reset_state_t   { enum enum_t { offset=21,mask=0b1, no_reset=0, reset } ; } ;
    struct dma2_reset_state_t   { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;
    struct dma2d_reset_state_t  { enum enum_t { offset=23,mask=0b1, no_reset=0, reset } ; } ;
    struct ethmac_reset_state_t { enum enum_t { offset=25,mask=0b1, no_reset=0, reset } ; } ;
    struct usbhs_reset_state_t  { enum enum_t { offset=29,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { gpioa=gpioa_reset_state_t::offset ,
                        gpiob=gpiob_reset_state_t::offset ,
			gpioc=gpioc_reset_state_t::offset ,
			gpiod=gpiod_reset_state_t::offset ,
			gpioe=gpioe_reset_state_t::offset ,
			gpiof=gpiof_reset_state_t::offset ,
			gpiog=gpiog_reset_state_t::offset ,
			gpioh=gpioh_reset_state_t::offset ,
			gpioi=gpioi_reset_state_t::offset ,
			crc=crc_reset_state_t::offset,
			dma1=dma1_reset_state_t::offset,
			dma2=dma2_reset_state_t::offset,
			ethmac=ethmac_reset_state_t::offset,
			usbhs=usbhs_reset_state_t::offset,
                      } ;
  }  ;

  inline void gpioa_reset_state( const ahb1_peripheral_reset_t::gpioa_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioa_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioa_reset_state_t::no_reset) ; }
  inline void gpioa_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioa_reset_state_t::reset) ; }
  inline auto gpioa_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioa_reset_state_t>() ; }
  inline void gpioa_reset() { gpioa_reset_state_reset() ; gpioa_reset_state_no_reset(); }

  inline void gpiob_reset_state( const ahb1_peripheral_reset_t::gpiob_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiob_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiob_reset_state_t::no_reset) ; }
  inline void gpiob_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiob_reset_state_t::reset) ; }
  inline auto gpiob_reset_state()  const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiob_reset_state_t>() ; }
  inline void gpiob_reset() { gpiob_reset_state_reset() ; gpiob_reset_state_no_reset(); }

  inline void gpioc_reset_state( const ahb1_peripheral_reset_t::gpioc_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioc_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioc_reset_state_t::no_reset) ; }
  inline void gpioc_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioc_reset_state_t::reset) ; }
  inline auto gpioc_reset_state()  const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioc_reset_state_t>() ; }
  inline void gpioc_reset() { gpioc_reset_state_reset() ; gpioc_reset_state_no_reset(); }

  inline void gpiod_reset_state( const ahb1_peripheral_reset_t::gpiod_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiod_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiod_reset_state_t::no_reset) ; }
  inline void gpiod_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiod_reset_state_t::reset) ; }
  inline auto gpiod_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiod_reset_state_t>() ; }
  inline void gpiod_reset() { gpiod_reset_state_reset() ; gpiod_reset_state_no_reset(); }

  inline void gpioe_reset_state( const ahb1_peripheral_reset_t::gpioe_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioe_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioe_reset_state_t::no_reset) ; }
  inline void gpioe_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioe_reset_state_t::reset) ; }
  inline auto gpioe_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioe_reset_state_t>() ; }
  inline void gpioe_reset() { gpioe_reset_state_reset() ; gpioe_reset_state_no_reset(); }

  inline void gpiof_reset_state( const ahb1_peripheral_reset_t::gpiof_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiof_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiof_reset_state_t::no_reset) ; }
  inline void gpiof_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiof_reset_state_t::reset) ; }
  inline auto gpiof_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiof_reset_state_t>() ; }
  inline void gpiof_reset() { gpiof_reset_state_reset() ; gpiof_reset_state_no_reset(); }

  inline void gpiog_reset_state( const ahb1_peripheral_reset_t::gpiog_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiog_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiog_reset_state_t::no_reset) ; }
  inline void gpiog_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiog_reset_state_t::reset) ; }
  inline auto gpiog_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiog_reset_state_t>() ; }
  inline void gpiog_reset() { gpiog_reset_state_reset() ; gpiog_reset_state_no_reset(); }

  inline void gpioh_reset_state( const ahb1_peripheral_reset_t::gpioh_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioh_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioh_reset_state_t::no_reset) ; }
  inline void gpioh_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioh_reset_state_t::reset) ; }
  inline auto gpioh_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioh_reset_state_t>() ; }
  inline void gpioh_reset() { gpioh_reset_state_reset() ; gpioh_reset_state_no_reset(); }

  inline void gpioi_reset_state( const ahb1_peripheral_reset_t::gpioi_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioi_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioi_reset_state_t::no_reset) ; }
  inline void gpioi_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioi_reset_state_t::reset) ; }
  inline auto gpioi_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioi_reset_state_t>() ; }
  inline void gpioi_reset() { gpioi_reset_state_reset() ; gpioi_reset_state_no_reset(); }

  inline void gpioj_reset_state( const ahb1_peripheral_reset_t::gpioj_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioj_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioj_reset_state_t::no_reset) ; }
  inline void gpioj_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioj_reset_state_t::reset) ; }
  inline auto gpioj_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioj_reset_state_t>() ; }
  inline void gpioj_reset() { gpioj_reset_state_reset() ; gpioj_reset_state_no_reset(); }

  inline void gpiok_reset_state( const ahb1_peripheral_reset_t::gpiok_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiok_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiok_reset_state_t::no_reset) ; }
  inline void gpiok_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiok_reset_state_t::reset) ; }
  inline auto gpiok_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiok_reset_state_t>() ; }
  inline void gpiok_reset() { gpiok_reset_state_reset() ; gpiok_reset_state_no_reset(); }

  inline void crc_reset_state( const ahb1_peripheral_reset_t::crc_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void crc_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::crc_reset_state_t::no_reset) ; }
  inline void crc_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::crc_reset_state_t::reset) ; }
  inline auto crc_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::crc_reset_state_t>() ; }
  inline void crc_reset() { crc_reset_state_reset() ; crc_reset_state_no_reset(); }

  inline void dma1_reset_state( const ahb1_peripheral_reset_t::dma1_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma1_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma1_reset_state_t::no_reset) ; }
  inline void dma1_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma1_reset_state_t::reset) ; }
  inline auto dma1_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma1_reset_state_t>() ; }
  inline void dma1_reset() { dma1_reset_state_reset() ; dma1_reset_state_no_reset(); }

  inline void dma2_reset_state( const ahb1_peripheral_reset_t::dma2_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma2_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2_reset_state_t::no_reset) ; }
  inline void dma2_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2_reset_state_t::reset) ; }
  inline auto dma2_reset_state()  const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma2_reset_state_t>() ; }
  inline void dma2_reset() { dma2_reset_state_reset() ; dma2_reset_state_no_reset(); }

  inline void dma2d_reset_state( const ahb1_peripheral_reset_t::dma2d_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma2d_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2d_reset_state_t::no_reset) ; }
  inline void dma2d_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2d_reset_state_t::reset) ; }
  inline auto dma2d_reset_state()  const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma2d_reset_state_t>() ; }
  inline void dma2d_reset() { dma2d_reset_state_reset() ; dma2d_reset_state_no_reset(); }

  inline void ethmac_reset_state( const ahb1_peripheral_reset_t::ethmac_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void ethmac_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::ethmac_reset_state_t::no_reset) ; }
  inline void ethmac_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::ethmac_reset_state_t::reset) ; }
  inline auto ethmac_reset_state()  const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::ethmac_reset_state_t>() ; }
  inline void ethmac_reset() { ethmac_reset_state_reset() ; ethmac_reset_state_no_reset(); }

  inline void usbhs_reset_state( const ahb1_peripheral_reset_t::usbhs_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void usbhs_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::usbhs_reset_state_t::no_reset) ; }
  inline void usbhs_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::usbhs_reset_state_t::reset) ; }
  inline auto usbhs_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::usbhs_reset_state_t>() ; }
  inline void usbhs_reset() { usbhs_reset_state_reset() ; usbhs_reset_state_no_reset(); }

  inline void state_reset(const ahb1_peripheral_reset_t::peripheral_t val) { ahb1_peripheral_reset.rmw( ahb1_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const ahb1_peripheral_reset_t::peripheral_t val){ ahb1_peripheral_reset.rmw( ahb1_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const ahb1_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }


  struct ahb2_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct dcmi_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct crypt_reset_state_t { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct hash_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct rng_reset_state_t   { enum enum_t { offset=6, mask=0b1, no_reset=0, reset } ; } ;
    struct otgfs_reset_state_t { enum enum_t { offset=7, mask=0b1, no_reset=0, reset } ; } ;
    enum peripheral_t { dcmi=dcmi_reset_state_t::offset ,
	                  crypt=crypt_reset_state_t::offset ,
			  hash=hash_reset_state_t::offset ,
			  rng=rng_reset_state_t::offset ,
			  otgfs=otgfs_reset_state_t::offset ,
                      } ;
  } ;

  inline void dcmi_reset_state( const ahb2_peripheral_reset_t::dcmi_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void dcmi_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::dcmi_reset_state_t::no_reset) ; }
  inline void dcmi_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::dcmi_reset_state_t::reset) ; }
  inline auto dcmi_reset_state() const  { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::dcmi_reset_state_t>() ; }
  inline void dcmi_reset() { dcmi_reset_state_reset() ; dcmi_reset_state_no_reset(); }

  inline void crypt_reset_state( const ahb2_peripheral_reset_t::crypt_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void crypt_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::crypt_reset_state_t::no_reset) ; }
  inline void crypt_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::crypt_reset_state_t::reset) ; }
  inline auto crypt_reset_state() const  { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::crypt_reset_state_t>() ; }
  inline void crypt_reset() { crypt_reset_state_reset() ; crypt_reset_state_no_reset(); }

  inline void hash_reset_state( const ahb2_peripheral_reset_t::hash_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void hash_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::hash_reset_state_t::no_reset) ; }
  inline void hash_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::hash_reset_state_t::reset) ; }
  inline auto hash_reset_state()  const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::hash_reset_state_t>() ; }
  inline void hash_reset() { hash_reset_state_reset() ; hash_reset_state_no_reset(); }

  inline void rng_reset_state( const ahb2_peripheral_reset_t::rng_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void rng_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::rng_reset_state_t::no_reset) ; }
  inline void rng_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::rng_reset_state_t::reset) ; }
  inline auto rng_reset_state() const  { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::rng_reset_state_t>() ; }
  inline void rng_reset() { rng_reset_state_reset() ; rng_reset_state_no_reset(); }

  inline void otgfs_reset_state( const ahb2_peripheral_reset_t::otgfs_reset_state_t::enum_t val){ ahb2_peripheral_reset.rmw(val) ; }
  inline void otgfs_reset_state_no_reset(){ ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::otgfs_reset_state_t::no_reset) ; }
  inline void otgfs_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::otgfs_reset_state_t::reset) ; }
  inline auto otgfs_reset_state() const  { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::otgfs_reset_state_t>() ; }
  inline void otgfs_reset() { otgfs_reset_state_reset() ; otgfs_reset_state_no_reset(); }

  inline void state_reset(const ahb2_peripheral_reset_t::peripheral_t val) { ahb2_peripheral_reset.rmw( ahb2_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const ahb2_peripheral_reset_t::peripheral_t val){ ahb2_peripheral_reset.rmw( ahb2_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const ahb2_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct ahb3_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct fmc_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    //struct qspi_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    enum peripheral_t { fmc=fmc_reset_state_t::offset } ;
  }   ;

  inline void fmc_reset_state( const ahb3_peripheral_reset_t::fmc_reset_state_t::enum_t val){ ahb3_peripheral_reset.rmw(val) ; }
  inline void fmc_reset_state_no_reset(){ ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t::fmc_reset_state_t::no_reset) ; }
  inline void fmc_reset_state_reset() { ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t::fmc_reset_state_t::reset) ; }
  inline auto fmc_reset_state()  const { return ahb3_peripheral_reset.rd<ahb3_peripheral_reset_t::fmc_reset_state_t>() ; }
  inline void fmc_reset() { fmc_reset_state_reset() ; fmc_reset_state_no_reset(); }

  inline void state_reset(const ahb3_peripheral_reset_t::peripheral_t val) { ahb3_peripheral_reset.rmw( ahb3_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const ahb3_peripheral_reset_t::peripheral_t val){ ahb3_peripheral_reset.rmw( ahb3_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const ahb3_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }


  struct apb1_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct tim2_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct tim3_reset_state_t  { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;
    struct tim4_reset_state_t  { enum enum_t { offset=2, mask=0b1, no_reset=0, reset } ; } ;
    struct tim5_reset_state_t  { enum enum_t { offset=3, mask=0b1, no_reset=0, reset } ; } ;
    struct tim6_reset_state_t  { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct tim7_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct tim12_reset_state_t { enum enum_t { offset=6, mask=0b1, no_reset=0, reset } ; } ;
    struct tim13_reset_state_t { enum enum_t { offset=7, mask=0b1, no_reset=0, reset } ; } ;
    struct tim14_reset_state_t { enum enum_t { offset=8, mask=0b1, no_reset=0, reset } ; } ;
    struct wwdg_reset_state_t  { enum enum_t { offset=11,mask=0b1, no_reset=0, reset } ; } ;
    struct spi2_reset_state_t  { enum enum_t { offset=14,mask=0b1, no_reset=0, reset } ; } ;
    struct spi3_reset_state_t  { enum enum_t { offset=15,mask=0b1, no_reset=0, reset } ; } ;
    struct usart2_reset_state_t{ enum enum_t { offset=17,mask=0b1, no_reset=0, reset } ; } ;
    struct usart3_reset_state_t{ enum enum_t { offset=18,mask=0b1, no_reset=0, reset } ; } ;
    struct uart4_reset_state_t { enum enum_t { offset=19,mask=0b1, no_reset=0, reset } ; } ;
    struct uart5_reset_state_t { enum enum_t { offset=20,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c1_reset_state_t  { enum enum_t { offset=21,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c2_reset_state_t  { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c3_reset_state_t  { enum enum_t { offset=23,mask=0b1, no_reset=0, reset } ; } ;
    struct can1_reset_state_t  { enum enum_t { offset=25,mask=0b1, no_reset=0, reset } ; } ;
    struct can2_reset_state_t  { enum enum_t { offset=26,mask=0b1, no_reset=0, reset } ; } ;
    struct pwr_reset_state_t   { enum enum_t { offset=28,mask=0b1, no_reset=0, reset } ; } ;
    struct dac_reset_state_t   { enum enum_t { offset=29,mask=0b1, no_reset=0, reset } ; } ;
    struct uart7_reset_state_t { enum enum_t { offset=30,mask=0b1, no_reset=0, reset } ; } ;
    struct uart8_reset_state_t { enum enum_t { offset=31,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { tim2=tim2_reset_state_t::offset,
                        tim3=tim3_reset_state_t::offset,
			tim4=tim4_reset_state_t::offset,
			tim5=tim5_reset_state_t::offset,
			tim6=tim6_reset_state_t::offset,
			tim7=tim7_reset_state_t::offset,
			tim12=tim12_reset_state_t::offset,
			tim13=tim13_reset_state_t::offset,
			tim14=tim14_reset_state_t::offset,
			wwdg=wwdg_reset_state_t::offset,
			spi2=spi2_reset_state_t::offset,
			spi3=spi3_reset_state_t::offset,
			usart2=usart2_reset_state_t::offset,
			usart3=usart3_reset_state_t::offset,
			uart4=uart4_reset_state_t::offset,
			uart5=uart5_reset_state_t::offset,
			i2c1=i2c1_reset_state_t::offset,
			i2c2=i2c2_reset_state_t::offset,
			i2c3=i2c3_reset_state_t::offset,
			can1=can1_reset_state_t::offset,
			can2=can2_reset_state_t::offset,
			pwr=pwr_reset_state_t::offset,
			dac=dac_reset_state_t::offset,
			uart7=uart7_reset_state_t::offset,
			uart8=uart8_reset_state_t::offset,
                      } ;
  } ;

  inline void tim2_reset_state( const apb1_peripheral_reset_t::tim2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::no_reset) ; }
  inline void tim2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::reset) ; }
  inline auto tim2_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim2_reset_state_t>() ; }
  inline void tim2_reset() { tim2_reset_state_reset() ; tim2_reset_state_no_reset(); }

  inline void tim3_reset_state( const apb1_peripheral_reset_t::tim3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw (val) ; }
  inline void tim3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::no_reset) ; }
  inline void tim3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::reset) ; }
  inline auto tim3_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim3_reset_state_t>() ; }
  inline void tim3_reset() { tim3_reset_state_reset() ; tim3_reset_state_no_reset(); }

  inline void tim4_reset_state( const apb1_peripheral_reset_t::tim4_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim4_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim4_reset_state_t::no_reset) ; }
  inline void tim4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim4_reset_state_t::reset) ; }
  inline auto tim4_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim4_reset_state_t>() ; }
  inline void tim4_reset() { tim4_reset_state_reset() ; tim4_reset_state_no_reset(); }

  inline void tim5_reset_state( const apb1_peripheral_reset_t::tim5_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim5_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim5_reset_state_t::no_reset) ; }
  inline void tim5_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim5_reset_state_t::reset) ; }
  inline auto tim5_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim5_reset_state_t>() ; }
  inline void tim5_reset() { tim5_reset_state_reset() ; tim5_reset_state_no_reset(); }

  inline void tim6_reset_state( const apb1_peripheral_reset_t::tim6_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim6_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::no_reset) ; }
  inline void tim6_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::reset) ; }
  inline auto tim6_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim6_reset_state_t>() ; }
  inline void tim6_reset() { tim6_reset_state_reset() ; tim6_reset_state_no_reset(); }

  inline void tim7_reset_state( const apb1_peripheral_reset_t::tim7_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim7_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::no_reset) ; }
  inline void tim7_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::reset) ; }
  inline auto tim7_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim7_reset_state_t>() ; }
  inline void tim7_reset() { tim7_reset_state_reset() ; tim7_reset_state_no_reset(); }

  inline void tim12_reset_state( const apb1_peripheral_reset_t::tim12_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim12_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim12_reset_state_t::no_reset) ; }
  inline void tim12_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim12_reset_state_t::reset) ; }
  inline auto tim12_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim12_reset_state_t>() ; }
  inline void tim12_reset() { tim12_reset_state_reset() ; tim12_reset_state_no_reset(); }

  inline void tim13_reset_state( const apb1_peripheral_reset_t::tim13_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim13_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim13_reset_state_t::no_reset) ; }
  inline void tim13_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim13_reset_state_t::reset) ; }
  inline auto tim13_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim13_reset_state_t>() ; }
  inline void tim13_reset() { tim13_reset_state_reset() ; tim13_reset_state_no_reset(); }

  inline void tim14_reset_state( const apb1_peripheral_reset_t::tim14_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim14_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim14_reset_state_t::no_reset) ; }
  inline void tim14_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim14_reset_state_t::reset) ; }
  inline auto tim14_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim14_reset_state_t>() ; }
  inline void tim14_reset() { tim14_reset_state_reset() ; tim14_reset_state_no_reset(); }

  inline void wwdg_reset_state( const apb1_peripheral_reset_t::wwdg_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void wwdg_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::no_reset) ; }
  inline void wwdg_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::reset) ; }
  inline auto wwdg_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::wwdg_reset_state_t>() ; }
  inline void wwdt_reset() { wwdg_reset_state_reset() ; wwdg_reset_state_no_reset(); }

  inline void spi2_reset_state( const apb1_peripheral_reset_t::spi2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void spi2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::no_reset) ; }
  inline void spi2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::reset) ; }
  inline auto spi2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spi2_reset_state_t>() ; }
  inline void spi2_reset() { spi2_reset_state_reset() ; spi2_reset_state_no_reset(); }

  inline void spi3_reset_state( const apb1_peripheral_reset_t::spi3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void spi3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi3_reset_state_t::no_reset) ; }
  inline void spi3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi3_reset_state_t::reset) ; }
  inline auto spi3_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spi3_reset_state_t>() ; }
  inline void spi3_reset() { spi3_reset_state_reset() ; spi3_reset_state_no_reset(); }

  inline void usart2_reset_state( const apb1_peripheral_reset_t::usart2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void usart2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart2_reset_state_t::no_reset) ; }
  inline void usart2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart2_reset_state_t::reset) ; }
  inline auto usart2_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::usart2_reset_state_t>() ; }
  inline void usart2_reset() { usart2_reset_state_reset() ; usart2_reset_state_no_reset(); }

  inline void usart3_reset_state( const apb1_peripheral_reset_t::usart3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void usart3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart3_reset_state_t::no_reset) ; }
  inline void usart3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart3_reset_state_t::reset) ; }
  inline auto usart3_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::usart3_reset_state_t>() ; }
  inline void usart3_reset() { usart3_reset_state_reset() ; usart3_reset_state_no_reset(); }

  inline void uart4_reset_state( const apb1_peripheral_reset_t::uart4_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart4_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::no_reset) ; }
  inline void uart4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::reset) ; }
  inline auto uart4_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart4_reset_state_t>() ; }
  inline void uart4_reset() { uart4_reset_state_reset() ; uart4_reset_state_no_reset(); }

  inline void uart5_reset_state( const apb1_peripheral_reset_t::uart5_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart5_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart5_reset_state_t::no_reset) ; }
  inline void uart5_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart5_reset_state_t::reset) ; }
  inline auto uart5_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart5_reset_state_t>() ; }
  inline void uart5_reset() { uart5_reset_state_reset() ; uart5_reset_state_no_reset(); }

  inline void i2c1_reset_state( const apb1_peripheral_reset_t::i2c1_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c1_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::no_reset) ; }
  inline void i2c1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::reset) ; }
  inline auto i2c1_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c1_reset_state_t>() ; }
  inline void i2c1_reset() { i2c1_reset_state_reset() ; i2c1_reset_state_no_reset(); }

  inline void i2c2_reset_state( const apb1_peripheral_reset_t::i2c2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::no_reset) ; }
  inline void i2c2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::reset) ; }
  inline auto i2c2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c2_reset_state_t>() ; }
  inline void i2c2_reset() { i2c2_reset_state_reset() ; i2c2_reset_state_no_reset(); }

  inline void i2c3_reset_state( const apb1_peripheral_reset_t::i2c3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::no_reset) ; }
  inline void i2c3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::reset) ; }
  inline auto i2c3_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c3_reset_state_t>() ; }
  inline void i2c3_reset() { i2c3_reset_state_reset() ; i2c3_reset_state_no_reset(); }

  inline void can1_reset_state( const apb1_peripheral_reset_t::can1_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void can1_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can1_reset_state_t::no_reset) ; }
  inline void can1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can1_reset_state_t::reset) ; }
  inline auto can1_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::can1_reset_state_t>() ; }
  inline void can1_reset() { can1_reset_state_reset() ; can1_reset_state_no_reset(); }

  inline void can2_reset_state( const apb1_peripheral_reset_t::can2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void can2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can2_reset_state_t::no_reset) ; }
  inline void can2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can2_reset_state_t::reset) ; }
  inline auto can2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::can2_reset_state_t>() ; }
  inline void can2_reset() { can2_reset_state_reset() ; can2_reset_state_no_reset(); }

  inline void pwr_reset_state( const apb1_peripheral_reset_t::pwr_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void pwr_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::no_reset) ; }
  inline void pwr_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::reset) ; }
  inline auto pwr_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::pwr_reset_state_t>() ; }
  inline void pwr_reset() { pwr_reset_state_reset() ; pwr_reset_state_no_reset(); }

  inline void dac_reset_state( const apb1_peripheral_reset_t::dac_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void dac_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::dac_reset_state_t::no_reset) ; }
  inline void dac_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::dac_reset_state_t::reset) ; }
  inline auto dac_reset_state()  const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::dac_reset_state_t>() ; }
  inline void dac_reset() { dac_reset_state_reset() ; dac_reset_state_no_reset(); }

  inline void uart7_reset_state( const apb1_peripheral_reset_t::uart7_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart7_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart7_reset_state_t::no_reset) ; }
  inline void uart7_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart7_reset_state_t::reset) ; }
  inline auto uart7_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart7_reset_state_t>() ; }
  inline void uart7_reset() { uart7_reset_state_reset() ; uart7_reset_state_no_reset(); }


  inline void uart8_reset_state( const apb1_peripheral_reset_t::uart8_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart8_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart8_reset_state_t::no_reset) ; }
  inline void uart8_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart8_reset_state_t::reset) ; }
  inline auto uart8_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart8_reset_state_t>() ; }
  inline void uart8_reset() { uart8_reset_state_reset() ; uart8_reset_state_no_reset(); }


  inline void state_reset(const apb1_peripheral_reset_t::peripheral_t val) { apb1_peripheral_reset.rmw( apb1_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const apb1_peripheral_reset_t::peripheral_t val){ apb1_peripheral_reset.rmw( apb1_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const apb1_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct apb2_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct tim1_reset_state_t    { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct tim8_reset_state_t    { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;
    struct usart1_reset_state_t  { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct usart6_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct adc_reset_state_t     { enum enum_t { offset=8, mask=0b1, no_reset=0, reset } ; } ;
    struct sdio_reset_state_t    { enum enum_t { offset=11,mask=0b1, no_reset=0, reset } ; } ;
    struct spi1_reset_state_t    { enum enum_t { offset=12,mask=0b1, no_reset=0, reset } ; } ;
    struct syscfg_reset_state_t  { enum enum_t { offset=14,mask=0b1, no_reset=0, reset } ; } ;
    struct tim9_reset_state_t    { enum enum_t { offset=16,mask=0b1, no_reset=0, reset } ; } ;
    struct tim10_reset_state_t   { enum enum_t { offset=17,mask=0b1, no_reset=0, reset } ; } ;
    struct tim11_reset_state_t   { enum enum_t { offset=18,mask=0b1, no_reset=0, reset } ; } ;
    struct spi5_reset_state_t    { enum enum_t { offset=20,mask=0b1, no_reset=0, reset } ; } ;
    struct spi6_reset_state_t    { enum enum_t { offset=21,mask=0b1, no_reset=0, reset } ; } ;
    struct sai_reset_state_t     { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;
    struct ltdc_reset_state_t    { enum enum_t { offset=26,mask=0b1, no_reset=0, reset } ; } ;
    enum peripheral_t { tim1=tim1_reset_state_t::offset,
                        tim8=tim8_reset_state_t::offset,
			usart1=usart1_reset_state_t::offset,
			usart6=usart6_reset_state_t::offset,
			adc=adc_reset_state_t::offset,
			sdio=sdio_reset_state_t::offset,
			spi1=spi1_reset_state_t::offset,
			syscfg=syscfg_reset_state_t::offset,
			tim9=tim9_reset_state_t::offset,
			tim10=tim10_reset_state_t::offset,
			tim11=tim11_reset_state_t::offset,
			spi5=spi5_reset_state_t::offset,
			spi6=spi6_reset_state_t::offset,
			sai=sai_reset_state_t::offset,
			ltdc=ltdc_reset_state_t::offset,
                      };
  } ;

  inline void tim1_reset_state( const apb2_peripheral_reset_t::tim1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim1_reset_state_t::no_reset) ; }
  inline void tim1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim1_reset_state_t::reset) ; }
  inline auto tim1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim1_reset_state_t>() ; }
  inline void tim1_reset() { tim1_reset_state_reset() ; tim1_reset_state_no_reset(); }

  inline void tim8_reset_state( const apb2_peripheral_reset_t::tim8_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim8_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim8_reset_state_t::no_reset) ; }
  inline void tim8_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim8_reset_state_t::reset) ; }
  inline auto tim8_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim8_reset_state_t>() ; }
  inline void tim8_reset() { tim8_reset_state_reset() ; tim8_reset_state_no_reset(); }

  inline void usart1_reset_state( const apb2_peripheral_reset_t::usart1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void usart1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::no_reset) ; }
  inline void usart1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::reset) ; }
  inline auto usart1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::usart1_reset_state_t>() ; }
  inline void usart1_reset() { usart1_reset_state_reset() ; usart1_reset_state_no_reset(); }

  inline void usart6_reset_state( const apb2_peripheral_reset_t::usart6_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void usart6_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart6_reset_state_t::no_reset) ; }
  inline void usart6_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart6_reset_state_t::reset) ; }
  inline auto usart6_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::usart6_reset_state_t>() ; }
  inline void usart6_reset() { usart6_reset_state_reset() ; usart6_reset_state_no_reset(); }

  inline void adc_reset_state( const apb2_peripheral_reset_t::adc_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void adc_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::no_reset) ; }
  inline void adc_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::reset) ; }
  inline auto adc_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::adc_reset_state_t>() ; }
  inline void adc_reset() { adc_reset_state_reset() ; adc_reset_state_no_reset(); }

  inline void sdio_reset_state( const apb2_peripheral_reset_t::sdio_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sdio_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdio_reset_state_t::no_reset) ; }
  inline void sdio_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdio_reset_state_t::reset) ; }
  inline auto sdio_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sdio_reset_state_t>() ; }
  inline void sdio_reset() { sdio_reset_state_reset() ; sdio_reset_state_no_reset(); }

  inline void spi1_reset_state( const apb2_peripheral_reset_t::spi1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::no_reset) ; }
  inline void spi1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::reset) ; }
  inline auto spi1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi1_reset_state_t>() ; }
  inline void spi1_reset() { spi1_reset_state_reset() ; spi1_reset_state_no_reset(); }

  inline void syscfg_reset_state( const apb2_peripheral_reset_t::syscfg_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void syscfg_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::no_reset) ; }
  inline void syscfg_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::reset) ; }
  inline auto syscfg_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::syscfg_reset_state_t>() ; }
  inline void syscfg_reset() { syscfg_reset_state_reset() ; syscfg_reset_state_no_reset(); }

  inline void tim9_reset_state( const apb2_peripheral_reset_t::tim9_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim9_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim9_reset_state_t::no_reset) ; }
  inline void tim9_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim9_reset_state_t::reset) ; }
  inline auto tim9_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim9_reset_state_t>() ; }
  inline void tim9_reset() { tim9_reset_state_reset() ; tim9_reset_state_no_reset(); }

  inline void tim10_reset_state( const apb2_peripheral_reset_t::tim10_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim10_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim10_reset_state_t::no_reset) ; }
  inline void tim10_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim10_reset_state_t::reset) ; }
  inline auto tim10_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim10_reset_state_t>() ; }
  inline void tim10_reset() { tim10_reset_state_reset() ; tim10_reset_state_no_reset(); }

  inline void tim11_reset_state( const apb2_peripheral_reset_t::tim11_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim11_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim11_reset_state_t::no_reset) ; }
  inline void tim11_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim11_reset_state_t::reset) ; }
  inline auto tim11_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim11_reset_state_t>() ; }
  inline void tim11_reset() { tim11_reset_state_reset() ; tim11_reset_state_no_reset(); }

  inline void spi5_reset_state( const apb2_peripheral_reset_t::spi5_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi5_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi5_reset_state_t::no_reset) ; }
  inline void spi5_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi5_reset_state_t::reset) ; }
  inline auto spi5_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi5_reset_state_t>() ; }
  inline void spi5_reset() { spi5_reset_state_reset() ; spi5_reset_state_no_reset(); }

  inline void spi6_reset_state( const apb2_peripheral_reset_t::spi6_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi6_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi6_reset_state_t::no_reset) ; }
  inline void spi6_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi6_reset_state_t::reset) ; }
  inline auto spi6_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi6_reset_state_t>() ; }
  inline void spi6_reset() { spi6_reset_state_reset() ; spi6_reset_state_no_reset(); }

  inline void sai_reset_state( const apb2_peripheral_reset_t::sai_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sai_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai_reset_state_t::no_reset) ; }
  inline void sai_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai_reset_state_t::reset) ; }
  inline auto sai_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sai_reset_state_t>() ; }
  inline void sai_reset() { sai_reset_state_reset() ; sai_reset_state_no_reset(); }

  inline void ltdc_reset_state( const apb2_peripheral_reset_t::ltdc_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void ltdc_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::ltdc_reset_state_t::no_reset) ; }
  inline void ltdc_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::ltdc_reset_state_t::reset) ; }
  inline auto ltdc_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::ltdc_reset_state_t>() ; }
  inline void ltdc_reset() { ltdc_reset_state_reset() ; ltdc_reset_state_no_reset(); }


  inline void state_reset(const apb2_peripheral_reset_t::peripheral_t val) { apb2_peripheral_reset.rmw( apb2_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const apb2_peripheral_reset_t::peripheral_t val){ apb2_peripheral_reset.rmw( apb2_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const apb2_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct ahb1_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, disable=0, enable } ;
    struct gpioa_t       { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct gpiob_t       { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
    struct gpioc_t       { enum enum_t { offset=2, mask=0b1, disable=0, enable } ; } ;
    struct gpiod_t       { enum enum_t { offset=3, mask=0b1, disable=0, enable } ; } ;
    struct gpioe_t       { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
    struct gpiof_t       { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
    struct gpiog_t       { enum enum_t { offset=6, mask=0b1, disable=0, enable } ; } ;
    struct gpioh_t       { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;
    struct gpioi_t       { enum enum_t { offset=8, mask=0b1, disable=0, enable } ; } ;
    struct gpioj_t       { enum enum_t { offset=9, mask=0b1, disable=0, enable } ; } ;
    struct gpiok_t       { enum enum_t { offset=10,mask=0b1, disable=0, enable } ; } ;
    struct crc_t         { enum enum_t { offset=12,mask=0b1, disable=0, enable } ; } ;
    struct backup_sram_t { enum enum_t { offset=18,mask=0b1, disable=0, enable } ; } ;
    struct ccm_t         { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;
    struct dma1_t        { enum enum_t { offset=21,mask=0b1, disable=0, enable } ; } ;
    struct dma2_t        { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;
    struct dma2d_t       { enum enum_t { offset=23,mask=0b1, disable=0, enable } ; } ;
    struct ethmac_t      { enum enum_t { offset=25,mask=0b1, disable=0, enable } ; } ;
    struct ethmac_tx_t   { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;
    struct ethmac_rx_t   { enum enum_t { offset=27,mask=0b1, disable=0, enable } ; } ;
    struct ethmac_ptp_t  { enum enum_t { offset=28,mask=0b1, disable=0, enable } ; } ;
    struct otghs_t       { enum enum_t { offset=29,mask=0b1, disable=0, enable } ; } ;
    struct otghs_ulpi_t  { enum enum_t { offset=30,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t { gpioa=gpioa_t::offset ,
                        gpiob=gpiob_t::offset ,
			gpioc=gpioc_t::offset ,
			gpiod=gpiod_t::offset ,
			gpioe=gpioe_t::offset ,
			gpiof=gpiof_t::offset ,
			gpiog=gpiog_t::offset ,
			gpioh=gpioh_t::offset ,
			gpioi=gpioi_t::offset ,
			gpioj=gpioj_t::offset ,
			gpiok=gpiok_t::offset ,
			crc=crc_t::offset,
			backup_sram= backup_sram_t::offset,
			ccm=ccm_t::offset,
			dma1=dma1_t::offset,
			dma2=dma2_t::offset,
			ethmac=ethmac_t::offset,
			ethmac_tx=ethmac_tx_t::offset,
			ethmac_rx=ethmac_rx_t::offset,
			ethmac_ptp=ethmac_ptp_t::offset,
			otgbhs=otghs_t::offset,
			otghs_ulpi=otghs_ulpi_t::offset
                      } ;
  } ;

  inline void gpioa_state( const ahb1_peripheral_clock_t::gpioa_t::enum_t val){ ahb1_peripheral_clock.rmw (val) ; clock_enable_delay(); }
  inline void gpioa_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioa_t::disable) ; }
  inline void gpioa_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioa_t::enable) ; clock_enable_delay(); }
  inline auto gpioa_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioa_t>() ; }

  inline void gpiob_state( const ahb1_peripheral_clock_t::gpiob_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpiob_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiob_t::disable) ; }
  inline void gpiob_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiob_t::enable) ; clock_enable_delay(); }
  inline auto gpiob_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiob_t>() ; }

  inline void gpioc_state( const ahb1_peripheral_clock_t::gpioc_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpioc_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioc_t::disable) ; }
  inline void gpioc_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioc_t::enable) ; clock_enable_delay(); }
  inline auto gpioc_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioc_t>() ; }

  inline void gpiod_state(ahb1_peripheral_clock_t::gpiod_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpiod_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiod_t::disable) ; }
  inline void gpiod_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiod_t::enable) ; clock_enable_delay(); }
  inline auto gpiod_state() { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiod_t>() ; }

  inline void gpioe_state( const ahb1_peripheral_clock_t::gpioe_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpioe_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioe_t::disable) ; }
  inline void gpioe_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioe_t::enable) ; clock_enable_delay(); }
  inline auto gpioe_state()  const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioe_t>() ; }

  inline void gpiof_state( const ahb1_peripheral_clock_t::gpiof_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpiof_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiof_t::disable) ; }
  inline void gpiof_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiof_t::enable) ; clock_enable_delay(); }
  inline auto gpiof_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiof_t>() ; }

  inline void gpiog_state( const ahb1_peripheral_clock_t::gpiog_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpiog_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiog_t::disable) ; }
  inline void gpiog_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiog_t::enable) ; clock_enable_delay(); }
  inline auto gpiog_state()  const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiog_t>() ; }

  inline void gpioh_state( const ahb1_peripheral_clock_t::gpioh_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpioh_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioh_t::disable) ; }
  inline void gpioh_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioh_t::enable) ; clock_enable_delay(); }
  inline auto gpioh_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioh_t>() ; }

  inline void gpioi_state(ahb1_peripheral_clock_t::gpioi_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpioi_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioi_t::disable) ; }
  inline void gpioi_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioi_t::enable) ; clock_enable_delay(); }
  inline auto gpioi_state() { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioi_t>() ; }

  inline void gpioj_state(ahb1_peripheral_clock_t::gpioj_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpioj_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioj_t::disable) ; }
  inline void gpioj_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioj_t::enable) ; clock_enable_delay(); }
  inline auto gpioj_state() { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioj_t>() ; }

  inline void gpiok_state(ahb1_peripheral_clock_t::gpiok_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void gpiok_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiok_t::disable) ; }
  inline void gpiok_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiok_t::enable) ; clock_enable_delay(); }
  inline auto gpiok_state() { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiok_t>() ; }

  inline void crc_state( const ahb1_peripheral_clock_t::crc_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void crc_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::crc_t::disable) ; }
  inline void crc_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::crc_t::enable) ; clock_enable_delay(); }
  inline auto crc_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::crc_t>() ; }

  inline void backup_sram_state( const ahb1_peripheral_clock_t::backup_sram_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void backup_sram_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::backup_sram_t::disable) ; }
  inline void backup_sram_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::backup_sram_t::enable) ; clock_enable_delay(); }
  inline auto backup_sram_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::backup_sram_t>() ; }

  inline void ccm_state( const ahb1_peripheral_clock_t::ccm_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ccm_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ccm_t::disable) ; }
  inline void ccm_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ccm_t::enable) ; clock_enable_delay(); }
  inline auto ccm_state()  const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ccm_t>() ; }

  inline void dma1_state( const ahb1_peripheral_clock_t::dma1_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void dma1_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma1_t::disable) ; }
  inline void dma1_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma1_t::enable) ; clock_enable_delay(); }
  inline auto dma1_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma1_t>() ; }

  inline void dma2_state( const ahb1_peripheral_clock_t::dma2_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void dma2_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2_t::disable) ; }
  inline void dma2_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2_t::enable) ; clock_enable_delay(); }
  inline auto dma2_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma2_t>() ; }

  inline void dma2d_state( const ahb1_peripheral_clock_t::dma2d_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void dma2d_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2d_t::disable) ; }
  inline void dma2d_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2d_t::enable) ; clock_enable_delay(); }
  inline auto dma2d_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma2d_t>() ; }

  inline void ethmac_state( const ahb1_peripheral_clock_t::ethmac_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ethmac_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_t::disable) ; }
  inline void ethmac_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_t::enable) ; clock_enable_delay(); }
  inline auto ethmac_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ethmac_t>() ; }

  inline void ethmac_tx_state( const ahb1_peripheral_clock_t::ethmac_tx_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ethmac_tx_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_tx_t::disable) ; }
  inline void ethmac_tx_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_tx_t::enable) ; clock_enable_delay(); }
  inline auto ethmac_tx_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ethmac_tx_t>() ; }

  inline void ethmac_rx_state( const ahb1_peripheral_clock_t::ethmac_rx_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ethmac_rx_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_rx_t::disable) ; }
  inline void ethmac_rx_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_rx_t::enable) ; clock_enable_delay(); }
  inline auto ethmac_rx_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ethmac_rx_t>() ; }

  inline void ethmac_ptp_state( const ahb1_peripheral_clock_t::ethmac_ptp_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ethmac_ptp_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_ptp_t::disable) ; }
  inline void ethmac_ptp_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ethmac_ptp_t::enable) ; clock_enable_delay(); }
  inline auto ethmac_ptp_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ethmac_ptp_t>() ; }

  inline void otghs_state( const ahb1_peripheral_clock_t::otghs_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void otghs_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::otghs_t::disable) ; }
  inline void otghs_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::otghs_t::enable) ; clock_enable_delay(); }
  inline auto otghs_state() const  { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::otghs_t>() ; }

  inline void otghs_ulpi_state( const ahb1_peripheral_clock_t::otghs_ulpi_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void otghs_ulpi_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::otghs_ulpi_t::disable) ; }
  inline void otghs_ulpi_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::otghs_ulpi_t::enable) ; clock_enable_delay(); }
  inline auto otghs_ulpi_state()  const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::otghs_ulpi_t>() ; }

  inline void state_enable(const ahb1_peripheral_clock_t::peripheral_t val) { ahb1_peripheral_clock.rmw( ahb1_peripheral_clock_t::enable,  val ) ; clock_enable_delay(); }
  inline void state_disable(const ahb1_peripheral_clock_t::peripheral_t val){ ahb1_peripheral_clock.rmw( ahb1_peripheral_clock_t::disable, val ) ; }

  struct ahb2_peripheral_clock_t : public read_write_32_t
    {
      enum enum_t       {  mask=0b1, disable=0, enable } ;
      struct dcmi_t    { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
      struct crypt_t   { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
      struct hash_t    { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
      struct rng_t     { enum enum_t { offset=6, mask=0b1, disable=0, enable } ; } ;
      struct otgfs_t   { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;

      enum peripheral_t { dcmi=dcmi_t::offset ,
	                  crypt=crypt_t::offset ,
			  hash=hash_t::offset ,
			  rng=rng_t::offset ,
			  otgfs=otgfs_t::offset ,
                        } ;
    };

  inline void dcmi_state( const ahb2_peripheral_clock_t::dcmi_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void dcmi_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::dcmi_t::disable) ; }
  inline void dcmi_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::dcmi_t::enable) ; clock_enable_delay(); }
  inline auto dcmi_state() const  { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::dcmi_t>() ; }

  inline void crypt_state( const ahb2_peripheral_clock_t::crypt_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void crypt_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::crypt_t::disable) ; }
  inline void crypt_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::crypt_t::enable) ; clock_enable_delay(); }
  inline auto crypt_state()  const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t:: crypt_t>() ; }

  inline void hash_state( const ahb2_peripheral_clock_t::hash_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void hash_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::hash_t::disable) ; }
  inline void hash_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::hash_t::enable) ; clock_enable_delay(); }
  inline auto hash_state() const  { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::hash_t>() ; }

  inline void rng_state( const ahb2_peripheral_clock_t::rng_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void rng_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::rng_t::disable) ; }
  inline void rng_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::rng_t::enable) ; clock_enable_delay(); }
  inline auto rng_state()  const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::rng_t>() ; }

  inline void otgfs_state( const ahb2_peripheral_clock_t::otgfs_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void otgfs_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::otgfs_t::disable) ; }
  inline void otgfs_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::otgfs_t::enable) ; clock_enable_delay(); }
  inline auto otgfs_state()  const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::otgfs_t>() ; }

  inline void state_enable(const ahb2_peripheral_clock_t::peripheral_t val) { ahb2_peripheral_clock.rmw( ahb2_peripheral_clock_t::enable,  val ) ; clock_enable_delay(); }
  inline void state_disable(const ahb2_peripheral_clock_t::peripheral_t val){ ahb2_peripheral_clock.rmw( ahb2_peripheral_clock_t::disable, val ) ; }

  struct ahb3_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, disable=0, enable } ;
    struct fmc_t    { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    enum peripheral_t { fmc=fmc_t::offset } ;
  };

  inline void fmc_state( const ahb3_peripheral_clock_t::fmc_t::enum_t val){ ahb3_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void fmc_disable(){ ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::fmc_t::disable) ; }
  inline void fmc_enable() { ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::fmc_t::enable) ; clock_enable_delay(); }
  inline auto fmc_state() const  { return ahb3_peripheral_clock.rd<ahb3_peripheral_clock_t::fmc_t>() ; }

  inline void state_enable(const ahb3_peripheral_clock_t::peripheral_t val) { ahb3_peripheral_clock.rmw( ahb3_peripheral_clock_t::enable,  val ) ; clock_enable_delay(); }
  inline void state_disable(const ahb3_peripheral_clock_t::peripheral_t val){ ahb3_peripheral_clock.rmw( ahb3_peripheral_clock_t::disable, val ) ; }

  struct apb1_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, disable=0, enable } ;
    struct tim2_t  { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct tim3_t  { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
    struct tim4_t  { enum enum_t { offset=2, mask=0b1, disable=0, enable } ; } ;
    struct tim5_t  { enum enum_t { offset=3, mask=0b1, disable=0, enable } ; } ;
    struct tim6_t  { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
    struct tim7_t  { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
    struct tim12_t { enum enum_t { offset=6, mask=0b1, disable=0, enable } ; } ;
    struct tim13_t { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;
    struct tim14_t { enum enum_t { offset=8, mask=0b1, disable=0, enable } ; } ;
    struct wwdg_t  { enum enum_t { offset=11,mask=0b1, disable=0, enable } ; } ;
    struct spi2_t  { enum enum_t { offset=14,mask=0b1, disable=0, enable } ; } ;
    struct spi3_t  { enum enum_t { offset=15,mask=0b1, disable=0, enable } ; } ;
    struct usart2_t { enum enum_t { offset=17,mask=0b1, disable=0, enable } ; } ;
    struct usart3_t { enum enum_t { offset=18,mask=0b1, disable=0, enable } ; } ;
    struct uart4_t { enum enum_t { offset=19,mask=0b1, disable=0, enable } ; } ;
    struct uart5_t { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;
    struct i2c1_t  { enum enum_t { offset=21,mask=0b1, disable=0, enable } ; } ;
    struct i2c2_t  { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;
    struct i2c3_t  { enum enum_t { offset=23,mask=0b1, disable=0, enable } ; } ;
    struct can1_t  { enum enum_t { offset=25,mask=0b1, disable=0, enable } ; } ;
    struct can2_t  { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;
    struct pwr_t   { enum enum_t { offset=28,mask=0b1, disable=0, enable } ; } ;
    struct dac_t   { enum enum_t { offset=29,mask=0b1, disable=0, enable } ; } ;
    struct uart7_t { enum enum_t { offset=30,mask=0b1, disable=0, enable } ; } ;
    struct uart8_t { enum enum_t { offset=31,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t { tim2=tim2_t::offset,
                        tim3=tim3_t::offset,
			tim4=tim4_t::offset,
			tim5=tim5_t::offset,
			tim6=tim6_t::offset,
			tim7=tim7_t::offset,
			tim12=tim12_t::offset,
			tim13=tim13_t::offset,
			tim14=tim14_t::offset,
			wwdg=wwdg_t::offset,
			spi2=spi2_t::offset,
			spi3=spi3_t::offset,
			usart2=usart2_t::offset,
			usart3=usart3_t::offset,
			uart4=uart4_t::offset,
			uart5=uart5_t::offset,
			i2c1=i2c1_t::offset,
			i2c2=i2c2_t::offset,
			i2c3=i2c3_t::offset,
			can1=can1_t::offset,
			can2=can2_t::offset,
			pwr=pwr_t::offset,
			dac=dac_t::offset
                      } ;
  } ;

  inline void tim2_state( const apb1_peripheral_clock_t::tim2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::disable) ; }
  inline void tim2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::enable) ; clock_enable_delay(); }
  inline auto tim2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim2_t>() ; }

  inline void tim3_state( const apb1_peripheral_clock_t::tim3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::disable) ; }
  inline void tim3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::enable) ; clock_enable_delay(); }
  inline auto tim3_state()  const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim3_t>() ; }

  inline void tim4_state( const apb1_peripheral_clock_t::tim4_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim4_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim4_t::disable) ; }
  inline void tim4_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim4_t::enable) ; clock_enable_delay(); }
  inline auto tim4_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim4_t>() ; }

  inline void tim5_state( const apb1_peripheral_clock_t::tim5_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim5_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim5_t::disable) ; }
  inline void tim5_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim5_t::enable) ; clock_enable_delay(); }
  inline auto tim5_state()  const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim5_t>() ; }

  inline void tim6_state( const apb1_peripheral_clock_t::tim6_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim6_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::disable) ; }
  inline void tim6_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::enable) ; clock_enable_delay(); }
  inline auto tim6_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim6_t>() ; }

  inline void tim7_state( const apb1_peripheral_clock_t::tim7_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim7_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::disable) ; }
  inline void tim7_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::enable) ; clock_enable_delay(); }
  inline auto tim7_state()  const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim7_t>() ; }

  inline void tim12_state( const apb1_peripheral_clock_t::tim12_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim12_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim12_t::disable) ; }
  inline void tim12_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim12_t::enable) ; clock_enable_delay(); }
  inline auto tim12_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim12_t>() ; }

  inline void tim13_state( const apb1_peripheral_clock_t::tim13_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim13_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim13_t::disable) ; }
  inline void tim13_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim13_t::enable) ; clock_enable_delay(); }
  inline auto tim13_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim13_t>() ; }

  inline void tim14_state( const apb1_peripheral_clock_t::tim14_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim14_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim14_t::disable) ; }
  inline void tim14_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim14_t::enable) ; clock_enable_delay(); }
  inline auto tim14_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim14_t>() ; }

  inline void wwdg_state(const apb1_peripheral_clock_t::wwdg_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void wwdg_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::disable) ; }
  inline void wwdg_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::enable) ; clock_enable_delay(); }
  inline auto wwdg_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::wwdg_t>() ; }

  inline void spi2_state( const apb1_peripheral_clock_t::spi2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void spi2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::disable) ; }
  inline void spi2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::enable) ; clock_enable_delay(); }
  inline auto spi2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spi2_t>() ; }

  inline void spi3_state( const apb1_peripheral_clock_t::spi3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void spi3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi3_t::disable) ; }
  inline void spi3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi3_t::enable) ; clock_enable_delay(); }
  inline auto spi3_state()  const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spi3_t>() ; }

  inline void usart2_state( const apb1_peripheral_clock_t::usart2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void usart2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart2_t::disable) ; }
  inline void usart2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart2_t::enable) ; clock_enable_delay(); }
  inline auto usart2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::usart2_t>() ; }

  inline void usart3_state( const apb1_peripheral_clock_t::usart3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void usart3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart3_t::disable) ; }
  inline void usart3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart3_t::enable) ; clock_enable_delay(); }
  inline auto usart3_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::usart3_t>() ; }

  inline void uart4_state( const apb1_peripheral_clock_t::uart4_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void uart4_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::disable) ; }
  inline void uart4_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::enable) ; clock_enable_delay(); }
  inline auto uart4_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart4_t>() ; }

  inline void uart5_state( const apb1_peripheral_clock_t::uart5_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void uart5_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart5_t::disable) ; }
  inline void uart5_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart5_t::enable) ; clock_enable_delay(); }
  inline auto uart5_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart5_t>() ; }

  inline void i2c1_state( const apb1_peripheral_clock_t::i2c1_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void i2c1_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::disable) ; }
  inline void i2c1_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::enable) ; clock_enable_delay(); }
  inline auto i2c1_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c1_t>() ; }

  inline void i2c2_state( const apb1_peripheral_clock_t::i2c2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void i2c2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::disable) ; }
  inline void i2c2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::enable) ; clock_enable_delay(); }
  inline auto i2c2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c2_t>() ; }

  inline void i2c3_state( const apb1_peripheral_clock_t::i2c3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void i2c3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::disable) ; }
  inline void i2c3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::enable) ; clock_enable_delay(); }
  inline auto i2c3_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c3_t>() ; }

  inline void can1_state( const apb1_peripheral_clock_t::can1_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void can1_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can1_t::disable) ; }
  inline void can1_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can1_t::enable) ; clock_enable_delay(); }
  inline auto can1_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::can1_t>() ; }

  inline void can2_state( const apb1_peripheral_clock_t::can2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void can2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can2_t::disable) ; }
  inline void can2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can2_t::enable) ; clock_enable_delay(); }
  inline auto can2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::can2_t>() ; }

  inline void pwr_state( const apb1_peripheral_clock_t::pwr_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void pwr_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::disable) ; }
  inline void pwr_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::enable) ; clock_enable_delay(); }
  inline auto pwr_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::pwr_t>() ; }

  inline void dac_state( const apb1_peripheral_clock_t::dac_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void dac_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::dac_t::disable) ; }
  inline void dac_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::dac_t::enable) ; clock_enable_delay(); }
  inline auto dac_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::dac_t>() ; }

  inline void uart7_state( const apb1_peripheral_clock_t::uart7_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void uart7_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart7_t::disable) ; }
  inline void uart7_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart7_t::enable) ; clock_enable_delay(); }
  inline auto uart7_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart7_t>() ; }

  inline void uart8_state( const apb1_peripheral_clock_t::uart8_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void uart8_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart8_t::disable) ; }
  inline void uart8_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart8_t::enable) ; clock_enable_delay(); }
  inline auto uart8_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart8_t>() ; }

  inline void state_enable(const apb1_peripheral_clock_t::peripheral_t val) { apb1_peripheral_clock.rmw( apb1_peripheral_clock_t::enable,  val ) ; clock_enable_delay(); }
  inline void state_disable(const apb1_peripheral_clock_t::peripheral_t val){ apb1_peripheral_clock.rmw( apb1_peripheral_clock_t::disable, val ) ; }

  struct apb2_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t                  {  mask=0b1, disable=0, enable } ;
    struct tim1_t                { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct tim8_t                { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
    struct usart1_t              { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
    struct usart6_t              { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_1_t     { enum enum_t { offset=8, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_2_t     { enum enum_t { offset=9, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_3_t     { enum enum_t { offset=10,mask=0b1, disable=0, enable } ; } ;
    struct sdio_t                { enum enum_t { offset=11,mask=0b1, disable=0, enable } ; } ;
    struct spi1_t                { enum enum_t { offset=12,mask=0b1, disable=0, enable } ; } ;
    struct syscfg_t              { enum enum_t { offset=14,mask=0b1, disable=0, enable } ; } ;
    struct tim9_t                { enum enum_t { offset=16,mask=0b1, disable=0, enable } ; } ;
    struct tim10_t               { enum enum_t { offset=17,mask=0b1, disable=0, enable } ; } ;
    struct tim11_t               { enum enum_t { offset=18,mask=0b1, disable=0, enable } ; } ;
    struct spi5_t                { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;
    struct spi6_t                { enum enum_t { offset=21,mask=0b1, disable=0, enable } ; } ;
    struct sai_t                 { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;
    struct ltdc_t                { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t { tim1=tim1_t::offset,
                        tim8=tim8_t::offset,
			usart1=usart1_t::offset,
			usart6=usart6_t::offset,
			adc_converter_1=adc_converter_1_t::offset,
			adc_converter_2=adc_converter_2_t::offset,
			adc_converter_3=adc_converter_3_t::offset,
			sdio=sdio_t::offset,
			spi1=spi1_t::offset,
			syscfg=syscfg_t::offset,
			tim9=tim9_t::offset,
			tim10=tim10_t::offset,
			tim11=tim11_t::offset,
			spi5=spi1_t::offset,
			spi6=spi1_t::offset,
			sai=spi1_t::offset,
			ltdc=spi1_t::offset,
                      };
  } ;

  inline void tim1_state( const apb2_peripheral_clock_t::tim1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim1_t::disable) ; }
  inline void tim1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim1_t::enable) ; clock_enable_delay(); }
  inline auto tim1_state()  const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim1_t>() ; }

  inline void tim8_state( const apb2_peripheral_clock_t::tim8_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim8_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim8_t::disable) ; }
  inline void tim8_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim8_t::enable) ; clock_enable_delay(); }
  inline auto tim8_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim8_t>() ; }

  inline void usart1_state( const apb2_peripheral_clock_t::usart1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void usart1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::disable) ; }
  inline void usart1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::enable) ; clock_enable_delay(); }
  inline auto usart1_state()  const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::usart1_t>() ; }

  inline void usart6_state( const apb2_peripheral_clock_t::usart6_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void usart6_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart6_t::disable) ; }
  inline void usart6_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart6_t::enable) ; clock_enable_delay(); }
  inline auto usart6_state()  const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::usart6_t>() ; }

  inline void adc_converter_1_state( const apb2_peripheral_clock_t::adc_converter_1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void adc_converter_1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_1_t::disable) ; }
  inline void adc_converter_1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_1_t::enable) ; clock_enable_delay(); }
  inline auto adc_converter_1_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_1_t>() ; }

  inline void adc_converter_2_state( const apb2_peripheral_clock_t::adc_converter_2_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void adc_converter_2_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_2_t::disable) ; }
  inline void adc_converter_2_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_2_t::enable) ; clock_enable_delay(); }
  inline auto adc_converter_2_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_2_t>() ; }

  inline void adc_converter_3_state( const apb2_peripheral_clock_t::adc_converter_3_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void adc_converter_3_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_3_t::disable) ; }
  inline void adc_converter_3_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_3_t::enable) ; clock_enable_delay(); }
  inline auto adc_converter_3_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_3_t>() ; }

  inline void sdio_state( const apb2_peripheral_clock_t::sdio_t::enum_t val){ apb2_peripheral_clock.rmw(val) ;clock_enable_delay(); }
  inline void sdio_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdio_t::disable) ; }
  inline void sdio_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdio_t::enable) ; clock_enable_delay(); }
  inline auto sdio_state()  const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sdio_t>() ; }

  inline void spi1_state( const apb2_peripheral_clock_t::spi1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void spi1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::disable) ; }
  inline void spi1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::enable) ; clock_enable_delay(); }
  inline auto spi1_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi1_t>() ; }

  inline void syscfg_state( const apb2_peripheral_clock_t::syscfg_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void syscfg_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::disable) ; }
  inline void syscfg_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::enable) ; clock_enable_delay(); }
  inline auto syscfg_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::syscfg_t>() ; }

  inline void tim9_state( const apb2_peripheral_clock_t::tim9_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim9_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim9_t::disable) ; }
  inline void tim9_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim9_t::enable) ; clock_enable_delay(); }
  inline auto tim9_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim9_t>() ; }

  inline void tim10_state( const apb2_peripheral_clock_t::tim10_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim10_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim10_t::disable) ; }
  inline void tim10_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim10_t::enable) ; clock_enable_delay(); }
  inline auto tim10_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim10_t>() ; }

  inline void tim11_state( const apb2_peripheral_clock_t::tim11_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void tim11_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim11_t::disable) ; }
  inline void tim11_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim11_t::enable) ; clock_enable_delay(); }
  inline auto tim11_state()  const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim11_t>() ; }

  inline void spi5_state( const apb2_peripheral_clock_t::spi5_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void spi5_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi5_t::disable) ; }
  inline void spi5_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi5_t::enable) ; clock_enable_delay(); }
  inline auto spi5_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi5_t>() ; }

  inline void spi6_state( const apb2_peripheral_clock_t::spi6_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void spi6_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi6_t::disable) ; }
  inline void spi6_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi6_t::enable) ; clock_enable_delay(); }
  inline auto spi6_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi6_t>() ; }

  inline void sai_state( const apb2_peripheral_clock_t::sai_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void sai_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai_t::disable) ; }
  inline void sai_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai_t::enable) ; clock_enable_delay(); }
  inline auto sai_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sai_t>() ; }

  inline void ltdc_state( const apb2_peripheral_clock_t::ltdc_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; clock_enable_delay(); }
  inline void ltdc_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::ltdc_t::disable) ; }
  inline void ltdc_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::ltdc_t::enable) ; clock_enable_delay(); }
  inline auto ltdc_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::ltdc_t>() ; }

  inline void state_enable(const apb2_peripheral_clock_t::peripheral_t val) { apb2_peripheral_clock.rmw( apb2_peripheral_clock_t::enable,  val ) ; clock_enable_delay(); }
  inline void state_disable(const apb2_peripheral_clock_t::peripheral_t val){ apb2_peripheral_clock.rmw( apb2_peripheral_clock_t::disable, val ) ; }


  struct ahb1_lp_peripheral_clock_t : public read_write_32_t
  {
    // TODO
  } ;

  struct ahb2_lp_peripheral_clock_t : public read_write_32_t
  {
    // TODO
  } ;

  struct ahb3_lp_peripheral_clock_t : public read_write_32_t
  {
    // TODO
  }  ;

  struct apb1_lp_peripheral_clock_t : public read_write_32_t
  {
    // TODO
  } ;

  struct apb2_lp_peripheral_clock_t : public read_write_32_t
  {
    // TODO
  } ;

  struct backup_domain_control_t : public read_write_32_t
  {
    // TODO
  } ;

  struct clock_control_status_t : public read_write_32_t
  {
    struct lsi_t            { enum enum_t { offset=0, mask=0b1, off=0, on } ; } ;
    struct lsi_ready_t      { enum enum_t { offset=1, mask=0b1, not_ready=0, ready } ; } ;

    struct remove_reset_clear_t    { enum enum_t { offset=24, mask=0b1, not_effect=0, perform } ; } ;
    struct bor_reset_t      { enum enum_t { offset=25, mask=0b1, not_occured=0, occured } ; } ;
    struct nrst_reset_t     { enum enum_t { offset=26, mask=0b1, not_occured=0, occured } ; } ;
    struct por_pdr_reset_t  { enum enum_t { offset=27, mask=0b1, not_occured=0, occured } ; } ;
    struct software_reset_t { enum enum_t { offset=28, mask=0b1, not_occured=0, occured } ; } ;
    struct iwdg_reset_t     { enum enum_t { offset=29, mask=0b1, not_occured=0, occured } ; } ;
    struct wwdg_reset_t     { enum enum_t { offset=30, mask=0b1, not_occured=0, occured } ; } ;
    struct lpmr_reset_t     { enum enum_t { offset=31, mask=0b1, not_occured=0, occured } ; } ;
  } ;

  inline void lsi_state( const clock_control_status_t::lsi_t::enum_t val){ clock_control_status.rmw(val) ; }
  inline void lsi_on(){ clock_control_status.rmw(clock_control_status_t::lsi_t::on) ; }
  inline void lsi_off() { clock_control_status.rmw(clock_control_status_t::lsi_t::off) ; }
  inline auto lsi_state() const  { return clock_control_status.rd<clock_control_status_t::lsi_t>() ; }

  inline auto lsi_ready() const {  return clock_control_status.rd<clock_control_status_t::lsi_ready_t> ();}
  inline void lsi_ready_wait()  const { while ( lsi_ready() == clock_control_status_t::lsi_ready_t::not_ready)  {} ; }

  inline void remove_reset_clear(){clock_control_status.rmw(clock_control_status_t::remove_reset_clear_t::perform) ;}

  inline void bor_reset_clear(){ clock_control_status.rmw(clock_control_status_t::bor_reset_t::occured) ; }
  inline auto bor_reset()  const { return clock_control_status.rd<clock_control_status_t::bor_reset_t>() ; }

  inline void nrst_reset_clear(){ clock_control_status.rmw(clock_control_status_t::nrst_reset_t::occured) ; }
  inline auto nrst_reset()  const { return clock_control_status.rd<clock_control_status_t::nrst_reset_t>() ; }

  inline void por_pdr_reset_clear(){ clock_control_status.rmw(clock_control_status_t::por_pdr_reset_t::occured) ; }
  inline auto por_pdr_reset() const  { return clock_control_status.rd<clock_control_status_t::por_pdr_reset_t>() ; }

  inline void software_reset_clear(){ clock_control_status.rmw(clock_control_status_t::software_reset_t::occured) ; }
  inline auto software_reset()  const { return clock_control_status.rd<clock_control_status_t::software_reset_t>() ; }

  inline void iwdg_reset_clear(){ clock_control_status.rmw(clock_control_status_t::iwdg_reset_t::occured) ; }
  inline auto iwdg_reset()  const { return clock_control_status.rd<clock_control_status_t::iwdg_reset_t>() ; }

  inline void wwdg_reset_clear(){ clock_control_status.rmw(clock_control_status_t::wwdg_reset_t::occured) ; }
  inline auto wwdg_reset() const  { return clock_control_status.rd<clock_control_status_t::wwdg_reset_t>() ; }

  inline void lpmr_reset_clear(){ clock_control_status.rmw(clock_control_status_t::lpmr_reset_t::occured) ; }
  inline auto lpmr_reset() const  { return clock_control_status.rd<clock_control_status_t::lpmr_reset_t>() ; }

  struct spread_spectrum_clock_generation_t : public read_write_32_t
  {
    // TODO
  } ;

  struct pll_i2s_config_t : public read_write_32_t
  {
    struct n_t    { enum enum_t { offset=6, mask=0b111111111 } ; } ;
    struct q_t    { enum enum_t { offset=24, mask=0b1111 } ; } ;
    struct r_t    { enum enum_t { offset=28, mask=0b111 } ; } ;
  }  ;

  inline  void pll_i2s_n( const uint16_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_i2s_n() const {  return (pll_i2s_config_t::n_t::enum_t) pll_config.rd<pll_i2s_config_t::n_t> ();}

  inline  void pll_i2s_q( const uint8_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_i2s_q() const {  return (pll_i2s_config_t::q_t::enum_t) pll_config.rd<pll_i2s_config_t::q_t> ();}

  inline  void pll_i2s_r( const uint8_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::r_t::enum_t)val) ;}
  inline  uint8_t pll_i2s_r() const {  return (pll_i2s_config_t::r_t::enum_t) pll_config.rd<pll_i2s_config_t::r_t> ();}

  struct pll_sai_config_t : public read_write_32_t
  {
	    struct n_t    { enum enum_t { offset=6, mask=0b111111111 } ; } ;
	    struct q_t    { enum enum_t { offset=24, mask=0b1111 } ; } ;
	    struct r_t    { enum enum_t { offset=28, mask=0b111 } ; } ;
  };

  inline  void pll_sai_n( const uint16_t val){  pll_sai_config.rmw( (pll_sai_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_sai_n() const {  return (pll_sai_config_t::n_t::enum_t) pll_config.rd<pll_sai_config_t::n_t> ();}

  inline  void pll_sai_q( const uint8_t val){  pll_sai_config.rmw( (pll_sai_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_sai_q() const {  return (pll_sai_config_t::q_t::enum_t) pll_config.rd<pll_sai_config_t::q_t> ();}

  inline  void pll_sai_r( const uint8_t val){  pll_sai_config.rmw( (pll_sai_config_t::r_t::enum_t)val) ;}
  inline  uint8_t pll_sai_r() const {  return (pll_sai_config_t::r_t::enum_t) pll_config.rd<pll_sai_config_t::r_t> ();}

  struct dedicated_clocks_config_1_t : public read_write_32_t
  {
	  // TODO
  };


  clock_control_t                    clock_control;       //CR        /*!< RCC clock control register,          Address offset: 0x00 */
  pll_config_t                       pll_config;         //PLLCFGR   /*!< RCC PLL configuration register,      Address offset: 0x04 */
  clock_config_t                     clock_config;       //CFGR;     /*!< RCC clock configuration register,    Address offset: 0x08 */
  clock_interrupt_t                  clock_interrupt;  //CIR;           /*!< RCC clock interrupt register,  Address offset: 0x0C */
  ahb1_peripheral_reset_t            ahb1_peripheral_reset; // AHB1RSTR;      /*!< RCC AHB1 peripheral reset register, Address offset: 0x10 */
  ahb2_peripheral_reset_t            ahb2_peripheral_reset; // AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  ahb3_peripheral_reset_t            ahb3_peripheral_reset; // AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  const uint32_t                         reserved0;     /*!< Reserved, 0x1C                                                                    */
  apb1_peripheral_reset_t            apb1_peripheral_reset; // APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  apb2_peripheral_reset_t            apb2_peripheral_reset; // APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  const uint32_t                         reserved1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  ahb1_peripheral_clock_t            ahb1_peripheral_clock;       /*!< RCC AHB1 peripheral clock register, Address offset: 0x30 */
  ahb2_peripheral_clock_t            ahb2_peripheral_clock;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  ahb3_peripheral_clock_t            ahb3_peripheral_clock; // AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  const uint32_t                         reserved2;     /*!< Reserved, 0x3C                                                                    */
  apb1_peripheral_clock_t            apb1_peripheral_clock; // APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  apb2_peripheral_clock_t            apb2_peripheral_clock; // APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  const uint32_t                         reserved3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  ahb1_lp_peripheral_clock_t         ahb1_lp_peripheral_clock; // AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  ahb2_lp_peripheral_clock_t         ahb2_lp_peripheral_clock; // AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  ahb3_lp_peripheral_clock_t         ahb3_lp_peripheral_clock; // AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  const uint32_t                         reserved4;     /*!< Reserved, 0x5C                                                                    */
  apb1_lp_peripheral_clock_t         apb1_lp_peripheral_clock; // APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  apb2_lp_peripheral_clock_t         apb2_lp_peripheral_clock; // APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  const uint32_t                         reserved5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  backup_domain_control_t            backup_domain_control; // BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  clock_control_status_t             clock_control_status ; // CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  const uint32_t                         reserved6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  spread_spectrum_clock_generation_t spread_spectrum_clock_generation ; // SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  pll_i2s_config_t                   pll_i2s_config; // PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,
  pll_sai_config_t                   pll_sai_config; // PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
  dedicated_clocks_config_1_t          dedicated_clocks_config_1; //DCKCFGR1;      /*!< RCC Dedicated Clocks configuration register1,                 Address offset: 0x8C */

  struct system_init_profile_t // pwr, clocs, etc
  {
        enum sys_clock_source_t { hsi, hse, hse_bypass, hsi_pll, hse_pll, hse_bypass_pll};

        uint32_t f_osc;
        sys_clock_source_t sys_clock_source ;
        // тактовая частотота pll_clk  = (hse_hsi / m) * n / p
        uint8_t pll_m;
        uint16_t pll_n;
  	rcc_t::pll_config_t::p_t::enum_t pll_p;
  	// тактовая частотота usb_48_clk  = (hse_hsi / m) * n / q
  	uint8_t pll_q;

  	// тактовая частотота pll_i2s_clk = (hse_hsi / m) * n / r
  	/*uint16_t pll_i2s_n;
  	uint8_t pll_i2s_q;
  	uint8_t pll_i2s_r;

  	uint16_t pll_sai_n;
  	uint8_t pll_sai_q;
  	uint8_t pll_sai_r;*/

  	flash_t::access_control_t::icache_t::enum_t icache ;
  	flash_t::access_control_t::dcache_t::enum_t dcache ;
  	flash_t::access_control_t::prefetch_t::enum_t prefetch ;
  	flash_t::access_control_t::latency_t::enum_t latency ;

  	clock_config_t::ahb_prescaler_t::enum_t hpre;
  	clock_config_t::apb1_prescaler_t::enum_t ppre1;
  	clock_config_t::apb2_prescaler_t::enum_t ppre2;
  	uint8_t power_save;
  };


  inline void sys_clock_select_hsi() { 	hsi_on(); hsi_ready_wait(); sys_clock_hsi(); sys_clock_state_hsi_wait(); pll_off(); hse_off(); }
  inline void sys_clock_select_hse() { 	hse_on(); hse_ready_wait(); sys_clock_hse(); sys_clock_state_hse_wait(); pll_off(); hsi_off(); }
  inline void sys_clock_select_hsi_pll(const uint8_t m, const uint16_t n, const rcc_t::pll_config_t::p_t::enum_t p, const uint8_t q)
    {
       sys_clock_select_hsi();
       pll_m(m);
       pll_n(n) ;
       pll_p(p) ;
       pll_q(q) ;
       pll_source_hsi();
       pll_on();
       pll_ready_wait();
       sys_clock_pll();
       sys_clock_state_pll_wait();
    }
   inline void sys_clock_select_hse_pll(const uint8_t m, const uint16_t n, const rcc_t::pll_config_t::p_t::enum_t p, const uint8_t q)
    {
       sys_clock_select_hse();
       pll_m(m);
       pll_n(n) ;
       pll_p(p) ;
       pll_q(q) ;
       pll_source_hse();
       pll_on();
       pll_ready_wait();
       sys_clock_pll();
       sys_clock_state_pll_wait();
     }

   inline void sys_clock_select( const system_init_profile_t::sys_clock_source_t val, const uint8_t m, const uint16_t n, const rcc_t::pll_config_t::p_t::enum_t p, const uint8_t q)
     {
 	   switch( val )
 	   {
 	      case system_init_profile_t::sys_clock_source_t::hsi :
 	    	 sys_clock_select_hsi();
 	    	 break;
 	      case system_init_profile_t::sys_clock_source_t::hse :
 	    	 sys_clock_select_hse();
 	    	 break;
 	      case system_init_profile_t::sys_clock_source_t::hse_bypass :
 	    	 hse_clock_bypass_on();
 		 sys_clock_select_hse();
 	    	 break;
 	      case system_init_profile_t::sys_clock_source_t::hsi_pll :
 	    	 sys_clock_select_hsi_pll(m, n, p, q);
 	    	 break;
 	      case system_init_profile_t::sys_clock_source_t::hse_pll :
 	    	 sys_clock_select_hse_pll(m, n, p, q);
 	    	 break;
 	      case system_init_profile_t::sys_clock_source_t::hse_bypass_pll :
 		 hse_clock_bypass_on();
 		 sys_clock_select_hse_pll(m, n, p, q);
 	    	 break;

             break;
 	      default:
 	    	 std::__throw_invalid_argument(0);
 	   }
     }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // дополнительные функции более высокого уровня чем обращение к регистрам


  inline uint32_t sys_clock_freq()  const
    {  NRO
       uint32_t get_f_osc();
       switch ( sys_clock())
         {
           case clock_config_t::sys_clock_t::enum_t::pll:
	      return get_f_osc() / pll_m() * pll_n() / pll_p2v();
           case clock_config_t::sys_clock_t::enum_t::hse:
	      return get_f_osc() ;
           case clock_config_t::sys_clock_t::enum_t::hsi:
	      return 16000000 ;
           default :
              return 0 ;
         }
    }

   inline uint32_t ahb_clock_freq()  const
      {
        return ahb_prescaler() == clock_config_t::ahb_prescaler_t::no_div ?
                            sys_clock_freq() :
                            ahb_prescaler() > clock_config_t::ahb_prescaler_t::div16 ?
                                      sys_clock_freq() >> ((ahb_prescaler() & 0b111) + 1) :
        	                      sys_clock_freq() >> ((ahb_prescaler() & 0b111) + 2) ;
      }

   inline uint32_t apb1_clock_freq()  const
      {
        return apb1_prescaler() == clock_config_t::apb1_prescaler_t::no_div ?
                            sys_clock_freq() :
			    sys_clock_freq() >> ((apb1_prescaler() & 0b11) + 1);
      }
   inline uint32_t apb2_clock_freq()  const
      {
        return apb2_prescaler() == clock_config_t::apb2_prescaler_t::no_div ?
                            sys_clock_freq() :
			    sys_clock_freq() >> ((apb2_prescaler() & 0b11) + 1);
      }

   inline uint32_t cyc2us(const uint32_t cycles , const uint32_t scf)  const { NRO return cycles * 1000000.0f / scf; }
   inline uint32_t cyc2us(const uint32_t cycles )  const { NRO return cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2hz(const uint32_t cycles )  const { NRO return 1000000.0f / cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2khz(const uint32_t cycles )  const { NRO return 1000.0f / cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2mhz(const uint32_t cycles )  const { NRO return 1.0f / cyc2us(cycles , sys_clock_freq()); }


   inline uint64_t cyc2ns(const uint32_t cycles , const uint32_t scf) const  {  NRO return ((uint64_t)cycles * (uint64_t)1000000000) / scf; }
   inline uint64_t cyc2ns(const uint32_t cycles )  const { NRO return cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2khz(const uint32_t cycles ) { NRO return 1000000.0d / cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2mhz(const uint32_t cycles ) { NRO return 1000.0d / cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2ghz(const uint32_t cycles ) { NRO return 1.0d / cyc2ns(cycles , sys_clock_freq()); }


   inline uint32_t us_cnt_start()  const { return dwt.cyc_counter; }
   inline uint32_t us_cnt_stop(const uint32_t start_counter)   const { return cyc2us(dwt.cyc_counter - start_counter); }
   inline uint32_t us_cnt_stop(const uint32_t start_counter ,  const uint32_t scf)  const  { return cyc2us(dwt.cyc_counter - start_counter,scf); }

   inline uint32_t ns_cnt_start() const { return dwt.cyc_counter; }
   inline uint64_t ns_cnt_stop(const uint32_t start_counter)   const { return cyc2ns(dwt.cyc_counter - start_counter); }
   inline uint64_t ns_cnt_stop(const uint32_t start_counter ,  const uint32_t scf)  const  { return cyc2ns(dwt.cyc_counter - start_counter,scf); }






} ;

static rcc_t  &rcc   = *((rcc_t*) rcc_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __RCC++_H__ */
