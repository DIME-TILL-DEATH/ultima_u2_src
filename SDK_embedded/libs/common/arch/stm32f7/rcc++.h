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
#include "pwr++.h"

// TODO переделать до конца линейный доступ как inline void state_enable(const ahb1_peripheral_clock_t::peripheral_t val) { ahb1_peripheral_clock.rmw_bit_set( val ) ; }

namespace stm32f7
{





struct rcc_t
{

  // необходимая задержка перед использованием переферии после включения тактирования
	// Cortex-M7 (reference manual):
	// AHB: 2 AHB cycles
	// APB: 2 * (AHB/APB prescaler) AHB cycles
  // Cortex-M7 is dual issue, so we need 2 nop's per cycle
  inline void ahb_clock_enable_delay() { nop_rep(2); };
  inline void apb1_clock_enable_delay(){ uint32_t delay_cycles = 2 * ahb_prescaler() / apb1_prescaler() ; while(delay_cycles--) nop_rep(2);  }
  inline void apb2_clock_enable_delay(){ uint32_t delay_cycles = 2 * ahb_prescaler() / apb2_prescaler() ; while(delay_cycles--) nop_rep(2);  }


 struct clock_control_t : public read_write_32_t
  {
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

  inline  void hsi(const clock_control_t::hsi_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hsi_off(){  clock_control.rmw( clock_control_t::hsi_t::off) ;}
  inline  void hsi_on() {  clock_control.rmw( clock_control_t::hsi_t::on) ;}
  inline  clock_control_t::hsi_t::enum_t hsi() const {  return clock_control.rd<clock_control_t::hsi_t> ();}

  inline  clock_control_t::hsi_ready_t::enum_t hsi_ready() const {  return clock_control.rd<clock_control_t::hsi_ready_t> ();}
  inline void hsi_ready_wait() const { while ( hsi_ready() == clock_control_t::hsi_ready_t::not_ready)  {} ; }

  inline  void hsi_trim(const uint8_t val){  clock_control.rmw( (clock_control_t::hsi_trim_t::enum_t)val) ;}
  inline  uint8_t hsi_trim() const { return (clock_control_t::hsi_trim_t::enum_t) clock_control.rd<clock_control_t::hsi_trim_t> ();}

  inline  void hsi_cal(const uint8_t val){  clock_control.rmw( (clock_control_t::hsi_cal_t::enum_t)val) ;}
  inline  uint8_t hsi_cal() const {  return (clock_control_t::hsi_cal_t::enum_t) clock_control.rd<clock_control_t::hsi_cal_t> ();}

  inline  void hse(const clock_control_t::hse_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_off(){  clock_control.rmw( clock_control_t::hse_t::off) ;}
  inline  void hse_on() {  clock_control.rmw( clock_control_t::hse_t::on) ;}
  inline  clock_control_t::hse_t::enum_t hse() const {  return clock_control.rd<clock_control_t::hse_t> ();}

  inline  clock_control_t::hse_ready_t::enum_t hse_ready(){  return clock_control.rd<clock_control_t::hse_ready_t> ();}
  inline void hse_ready_wait() { while ( hse_ready() == clock_control_t::hse_ready_t::not_ready)  {} ; }

  inline  void hse_clock_bypass(const clock_control_t::hse_clock_bypass_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_clock_bypass_off(){  clock_control.rmw(clock_control_t::hse_clock_bypass_t::off) ;}
  inline  void hse_clock_bypass_on() {  clock_control.rmw(clock_control_t::hse_clock_bypass_t::on) ;}
  inline  clock_control_t::hse_clock_bypass_t::enum_t hse_clock_bypass() const {  return clock_control.rd<clock_control_t::hse_clock_bypass_t> ();}

  inline  void clock_security_system(const clock_control_t::clock_security_system_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void clock_security_system_disable(){  clock_control.rmw( clock_control_t::clock_security_system_t::disable) ;}
  inline  void clock_security_system_enable() {  clock_control.rmw( clock_control_t::clock_security_system_t::enable) ;}
  inline  clock_control_t::clock_security_system_t::enum_t clock_security_system() const {  return clock_control.rd<clock_control_t::clock_security_system_t> ();}

  inline  void pll(const clock_control_t::pll_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_off(){  clock_control.rmw( clock_control_t::pll_t::off) ;}
  inline  void pll_on() {  clock_control.rmw( clock_control_t::pll_t::on) ;}
  inline  clock_control_t::pll_t::enum_t pll() const {  return clock_control.rd<clock_control_t::pll_t> ();}

  inline  clock_control_t::pll_ready_t::enum_t pll_ready(){  return clock_control.rd<clock_control_t::pll_ready_t> ();}
  inline void pll_ready_wait() { while ( pll_ready() == clock_control_t::pll_ready_t::not_ready)  {} ; }

  inline  void pll_i2s( const clock_control_t::pll_i2s_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_i2s_off(){  clock_control.rmw( clock_control_t::pll_i2s_t::off) ;}
  inline  void pll_i2s_on() {  clock_control.rmw( clock_control_t::pll_i2s_t::on) ;}
  inline  clock_control_t::pll_i2s_t::enum_t pll_i2s() const {  return clock_control.rd<clock_control_t::pll_i2s_t> ();}

  inline  clock_control_t::pll_i2s_ready_t::enum_t pll_i2s_ready(){  return clock_control.rd<clock_control_t::pll_i2s_ready_t> ();}
  inline void pll_i2s_ready_wait() { while ( pll_i2s_ready() == clock_control_t::pll_i2s_ready_t::not_ready)  {} ; }

  inline  void pll_sai( const clock_control_t::pll_sai_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_sai_off(){  clock_control.rmw( clock_control_t::pll_sai_t::off) ;}
  inline  void pll_sai_on() {  clock_control.rmw( clock_control_t::pll_sai_t::on) ;}
  inline  clock_control_t::pll_sai_t::enum_t pll_sai() const {  return clock_control.rd<clock_control_t::pll_sai_t> ();}

  inline  clock_control_t::pll_sai_ready_t::enum_t pll_sai_ready() const {  return clock_control.rd<clock_control_t::pll_sai_ready_t> ();}
  inline void pll_sai_ready_wait() const  { while ( pll_sai_ready() == clock_control_t::pll_sai_ready_t::not_ready)  {} ; }

  struct pll_config_t : public read_write_32_t
  {
    struct m_t                { enum enum_t { offset=0,  mask=0b111111 } ; } ;
    struct n_t                { enum enum_t { offset=6,  mask=0b111111111 } ; } ;
    struct p_t                { enum enum_t { offset=16, mask=0b11, div2=0 , div4, div6, div8 } ; } ;
    struct source_t           { enum enum_t { offset=22, mask=1, hsi=0 , hse } ; } ;
    struct q_t                { enum enum_t { offset=24, mask=0b1111 } ; } ;
    struct r_t                { enum enum_t { offset=28, mask=0b111 } ; } ;
  }   ;

  inline  void pll_m( const uint8_t val){  pll_config.rmw( (pll_config_t::m_t::enum_t)val) ;}
  inline  uint8_t pll_m() const {  return (pll_config_t::m_t::enum_t) pll_config.rd<pll_config_t::m_t> ();}

  inline  void pll_n( const uint16_t val){  pll_config.rmw( (pll_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_n() const {  return (pll_config_t::n_t::enum_t) pll_config.rd<pll_config_t::n_t> ();}

  inline  void pll_p( const pll_config_t::p_t::enum_t val){ pll_config.rmw(val) ;}
  inline  pll_config_t::p_t::enum_t pll_p() const {  return pll_config.rd<pll_config_t::p_t> ();}
  inline  uint8_t pll_p2v() const {  const uint8_t map[] = {2,4,6,8} ; return map[(size_t)pll_p()] ;}


  inline  void pll_source( const pll_config_t::source_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll_source_hsi(){  pll_config.rmw(pll_config_t::source_t::hsi) ;}
  inline  void pll_source_hse(){  pll_config.rmw(pll_config_t::source_t::hse) ;}
  inline  pll_config_t::source_t::enum_t pll_source() const {  return  pll_config.rd<pll_config_t::source_t> ();}

  inline  void pll_q( const uint8_t val){  pll_config.rmw( (pll_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_q() const {  return (pll_config_t::q_t::enum_t) pll_config.rd<pll_config_t::q_t> ();}

  inline  void pll_r( const uint8_t val){  pll_config.rmw( (pll_config_t::r_t::enum_t)val) ;}
  inline  uint8_t pll_r() const {  return (pll_config_t::r_t::enum_t) pll_config.rd<pll_config_t::r_t> ();}

  struct clock_config_t : public read_write_32_t
  {
    struct sys_clock_t                     { enum enum_t { offset=0,  mask=0b11, hsi=0, hse, pll } ; } ;
    struct sys_clock_state_t               { enum enum_t { offset=2,  mask=0b11, hsi=0, hse, pll } ; } ;
    struct ahb_prescaler_t                 { enum enum_t { offset=4,  mask=0b1111, no_div=0b0000, div2=0b1000, div4=0b1001, div8=0b1010, div16=0b1011, div64=0b1100, div128=0b1101, div256=0b1110, div512=0b1111 } ; } ;
    struct apb1_prescaler_t                { enum enum_t { offset=10, mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct apb2_prescaler_t                { enum enum_t { offset=13, mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct hse_div_factor_for_rtc_clock_t  { enum enum_t { offset=16, mask=0b11111 } ; } ;
    struct mco1_clock_output_t             { enum enum_t { offset=21, mask=0b11, hsi=0, lse, hse, pll } ; } ;
    struct i2s_clock_selection_t           { enum enum_t { offset=23, mask=0b1, pll_i2s=0, external } ; } ;
    struct mco1_prescaler_t                { enum enum_t { offset=24, mask=0b111, no_div=0b00, div2=0b100, div3, div4, div5 } ; } ;
    struct mco2_prescaler_t                { enum enum_t { offset=27, mask=0b111, no_div=0b00, div2=0b100, div3, div4, div5 } ; } ;
    struct mco2_clock_output_t             { enum enum_t { offset=30, mask=0b11, sysclk=0, pll_i2s, hse, pll } ; } ;

  } ;

  inline void sys_clock( const clock_config_t::sys_clock_t::enum_t val) { clock_config.rmw(val) ; }
  inline void sys_clock_hsi() { clock_config.rmw(clock_config_t::sys_clock_t::hsi) ; }
  inline void sys_clock_hse() { clock_config.rmw(clock_config_t::sys_clock_t::hse) ; }
  inline void sys_clock_pll() { clock_config.rmw(clock_config_t::sys_clock_t::pll) ; }
  inline clock_config_t::sys_clock_t::enum_t sys_clock() const { return clock_config.rd<clock_config_t::sys_clock_t>() ; }

  inline clock_config_t::sys_clock_state_t::enum_t sys_clock_state()  const { return clock_config.rd<clock_config_t::sys_clock_state_t>() ; }
  inline void sys_clock_state_hsi_wait() const  { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::hsi ){}; }
  inline void sys_clock_state_hse_wait() const  { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::hse ){}; }
  inline void sys_clock_state_pll_wait() const  { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::pll ){}; }

  inline void ahb_prescaler( const clock_config_t::ahb_prescaler_t::enum_t val) { clock_config.rmw (val) ; }
  inline void ahb_prescaler_no_div(){ clock_config.rmw (clock_config_t::ahb_prescaler_t::no_div); }
  inline void ahb_prescaler_div2()  { clock_config.rmw (clock_config_t::ahb_prescaler_t::div2)  ; }
  inline void ahb_prescaler_div4()  { clock_config.rmw (clock_config_t::ahb_prescaler_t::div4)  ; }
  inline void ahb_prescaler_div8()  { clock_config.rmw (clock_config_t::ahb_prescaler_t::div8)  ; }
  inline void ahb_prescaler_div16() { clock_config.rmw (clock_config_t::ahb_prescaler_t::div16) ; }
  inline void ahb_prescaler_div64() { clock_config.rmw (clock_config_t::ahb_prescaler_t::div64) ; }
  inline void ahb_prescaler_div128(){ clock_config.rmw (clock_config_t::ahb_prescaler_t::div128); }
  inline void ahb_prescaler_div256(){ clock_config.rmw (clock_config_t::ahb_prescaler_t::div256); }
  inline void ahb_prescaler_div512(){ clock_config.rmw (clock_config_t::ahb_prescaler_t::div512); }
  inline clock_config_t::ahb_prescaler_t::enum_t ahb_prescaler() const  { return clock_config.rd<clock_config_t::ahb_prescaler_t>() ; }

  inline void apb1_prescaler( const clock_config_t::apb1_prescaler_t::enum_t val) { clock_config.rmw (val) ; }
  inline void apb1_prescaler_no_div(){ clock_config.rmw (clock_config_t::apb1_prescaler_t::no_div) ; }
  inline void apb1_prescaler_div2()  { clock_config.rmw (clock_config_t::apb1_prescaler_t::div2) ; }
  inline void apb1_prescaler_div4()  { clock_config.rmw (clock_config_t::apb1_prescaler_t::div4) ; }
  inline void apb1_prescaler_div8()  { clock_config.rmw (clock_config_t::apb1_prescaler_t::div8) ; }
  inline void apb1_prescaler_div16() { clock_config.rmw (clock_config_t::apb1_prescaler_t::div16) ; }
  inline clock_config_t::apb1_prescaler_t::enum_t apb1_prescaler()  const { return clock_config.rd<clock_config_t::apb1_prescaler_t> () ; }

  inline void apb2_prescaler( const clock_config_t::apb2_prescaler_t::enum_t val) { clock_config.rmw(val) ; }
  inline void apb2_prescaler_no_div(){ clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::no_div) ; }
  inline void apb2_prescaler_div2()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div2) ; }
  inline void apb2_prescaler_div4()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div4) ; }
  inline void apb2_prescaler_div8()  { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div8) ; }
  inline void apb2_prescaler_div16() { clock_config.rmw(clock_config_t::apb2_prescaler_t::enum_t::div16) ; }
  inline clock_config_t::apb2_prescaler_t::enum_t apb2_prescaler() const  { return clock_config.rd<clock_config_t::apb2_prescaler_t> () ; }


  inline void hse_divider_for_rtc_clock( const uint8_t val) { clock_config.rmw( (clock_config_t::hse_div_factor_for_rtc_clock_t::enum_t) val );  }
  inline uint8_t hse_divider_for_rtc_clock()  const { return (uint8_t) clock_config.rd<clock_config_t::hse_div_factor_for_rtc_clock_t> () ; }


  inline void mco1_clock_output( const clock_config_t::mco1_clock_output_t::enum_t val ) { clock_config.rmw(val) ; }
  inline void mco1_clock_output_hsi() { clock_config.rmw(clock_config_t::mco1_clock_output_t::hsi) ; }
  inline void mco1_clock_output_lse() { clock_config.rmw(clock_config_t::mco1_clock_output_t::lse) ; }
  inline void mco1_clock_output_hse() { clock_config.rmw(clock_config_t::mco1_clock_output_t::hse) ; }
  inline void mco1_clock_output_pll() { clock_config.rmw(clock_config_t::mco1_clock_output_t::pll) ; }
  inline clock_config_t::mco1_clock_output_t::enum_t mco1_clock_output()  const { return clock_config.rd<clock_config_t::mco1_clock_output_t> (); }

  inline void i2s_clock_selection( const clock_config_t::i2s_clock_selection_t::enum_t val) { clock_config.rmw(val) ; }
  inline void i2s_clock_selection_pll_i2s() { clock_config.rmw(clock_config_t::i2s_clock_selection_t::pll_i2s) ; }
  inline void i2s_clock_selection_external_ckin() { clock_config.rmw(clock_config_t::i2s_clock_selection_t::external) ; }
  inline clock_config_t::i2s_clock_selection_t::enum_t i2s_clock_selection() { return clock_config.rd<clock_config_t::i2s_clock_selection_t>() ; }

  inline void mco1_prescaler( const clock_config_t::mco1_prescaler_t::enum_t val) { clock_config.rmw(val); }
  inline void mco1_prescaler_no_div(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::no_div); }
  inline void mco1_prescaler_div2(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div2); }
  inline void mco1_prescaler_div3(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div3);}
  inline void mco1_prescaler_div4(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div4);}
  inline void mco1_prescaler_div5(){ clock_config.rmw(clock_config_t::mco1_prescaler_t::div5);}
  inline clock_config_t::mco1_prescaler_t::enum_t mco1_prescaler() { return clock_config.rd<clock_config_t::mco1_prescaler_t>() ; }

  inline void mco2_prescaler( const clock_config_t::mco2_prescaler_t::enum_t val) { clock_config.rmw(val); }
  inline void mco2_prescaler_no_div(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::no_div); }
  inline void mco2_prescaler_div2(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div2); }
  inline void mco2_prescaler_div3(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div3);}
  inline void mco2_prescaler_div4(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div4);}
  inline void mco2_prescaler_div5(){ clock_config.rmw(clock_config_t::mco2_prescaler_t::div5);}
  inline clock_config_t::mco2_prescaler_t::enum_t mco2_prescaler() const { return clock_config.rd<clock_config_t::mco2_prescaler_t>() ; }

  inline void mco2_clock_output( const clock_config_t::mco2_clock_output_t::enum_t val ) { clock_config.rmw(val) ; }
  inline void mco2_clock_output_sys_clk() { clock_config.rmw(clock_config_t::mco2_clock_output_t::sysclk) ; }
  inline void mco2_clock_output_pll_i2s() { clock_config.rmw(clock_config_t::mco2_clock_output_t::pll_i2s) ; }
  inline void mco2_clock_output_hse() { clock_config.rmw(clock_config_t::mco2_clock_output_t::hse) ; }
  inline void mco2_clock_output_pll() { clock_config.rmw(clock_config_t::mco2_clock_output_t::pll) ; }
  inline clock_config_t::mco2_clock_output_t::enum_t mco2_clock_output()  const { return clock_config.rd<clock_config_t::mco2_clock_output_t> (); }


  struct clock_interrupt_t : public read_write_32_t
  {
    struct lsi_ready_interupt_flag_t  { enum enum_t { offset=0,  mask=0b1, no_caused=0, caused } ; } ;
    struct lse_ready_interupt_flag_t  { enum enum_t { offset=1,  mask=0b1, no_caused=0, caused } ; } ;
    struct hsi_ready_interupt_flag_t  { enum enum_t { offset=2,  mask=0b1, no_caused=0, caused } ; } ;
    struct hse_ready_interupt_flag_t  { enum enum_t { offset=3,  mask=0b1, no_caused=0, caused } ; } ;
    struct pll_interupt_flag_t        { enum enum_t { offset=4,  mask=0b1, no_caused=0, caused } ; } ;
    struct pll_i2s_interupt_flag_t    { enum enum_t { offset=5,  mask=0b1, no_caused=0, caused } ; } ;
    struct pll_sai_interupt_flag_t    { enum enum_t { offset=6,  mask=0b1, no_caused=0, caused } ; } ;
    struct security_system_interupt_flag_t  { enum enum_t { offset=7,  mask=0b1, no_caused=0, caused } ; } ;

    struct lsi_ready_interupt_t  { enum enum_t { offset=8,  mask=0b1, disable=0, enable } ; } ;
    struct lse_ready_interupt_t  { enum enum_t { offset=9,  mask=0b1, disable=0, enable } ; } ;
    struct hsi_ready_interupt_t  { enum enum_t { offset=10, mask=0b1, disable=0, enable } ; } ;
    struct hse_ready_interupt_t  { enum enum_t { offset=11, mask=0b1, disable=0, enable } ; } ;
    struct pll_interupt_t        { enum enum_t { offset=12, mask=0b1, disable=0, enable } ; } ;
    struct pll_i2s_interupt_t    { enum enum_t { offset=13, mask=0b1, disable=0, enable } ; } ;
    struct pll_sai_interupt_t    { enum enum_t { offset=14,  mask=0b1, disable=0, enable } ; } ;

    struct lsi_ready_interupt_clear_t  { enum enum_t { offset=16, mask=0b1, no_effect=0, perform } ; } ;
    struct lse_ready_interupt_clear_t  { enum enum_t { offset=17, mask=0b1, no_effect=0, perform } ; } ;
    struct hsi_ready_interupt_clear_t  { enum enum_t { offset=18, mask=0b1, no_effect=0, perform } ; } ;
    struct hse_ready_interupt_clear_t  { enum enum_t { offset=19, mask=0b1, no_effect=0, perform } ; } ;
    struct pll_interupt_clear_t        { enum enum_t { offset=20, mask=0b1, no_effect=0, perform } ; } ;
    struct pll_i2s_interupt_clear_t    { enum enum_t { offset=21, mask=0b1, no_effect=0, perform } ; } ;
    struct pll_sai_interupt_clear_t  { enum enum_t { offset=22,  mask=0b1, no_effect=0, perform } ; } ;
    struct security_system_interupt_clear_t  { enum enum_t { offset=23,  mask=0b1, no_effect=0, perform } ; } ;
  }   ;

  inline clock_interrupt_t::lsi_ready_interupt_flag_t::enum_t lsi_ready_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::lsi_ready_interupt_flag_t>() ; }
  inline clock_interrupt_t::lse_ready_interupt_flag_t::enum_t lse_ready_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::lse_ready_interupt_flag_t>() ; }
  inline clock_interrupt_t::hsi_ready_interupt_flag_t::enum_t hsi_ready_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::hsi_ready_interupt_flag_t>() ; }
  inline clock_interrupt_t::hse_ready_interupt_flag_t::enum_t hse_ready_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::hse_ready_interupt_flag_t>() ; }
  inline clock_interrupt_t::pll_interupt_flag_t::enum_t pll_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::pll_interupt_flag_t>() ; }
  inline clock_interrupt_t::pll_i2s_interupt_flag_t::enum_t pll_i2s_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::pll_i2s_interupt_flag_t>() ; }
  inline clock_interrupt_t::pll_sai_interupt_flag_t::enum_t pll_sai_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::pll_sai_interupt_flag_t>() ; }
  inline clock_interrupt_t::security_system_interupt_flag_t::enum_t security_system_interupt_flag() { return clock_interrupt.rd<clock_interrupt_t::security_system_interupt_flag_t>() ; }

  inline void lsi_ready_interupt( const clock_interrupt_t::lsi_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void lsi_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_t::disable) ; }
  inline void lsi_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_t::enable) ; }
  inline clock_interrupt_t::lsi_ready_interupt_t::enum_t lsi_ready_interupt() const { return clock_interrupt.rd<clock_interrupt_t::lsi_ready_interupt_t>() ; }

  inline void lse_ready_interupt( const clock_interrupt_t::lse_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void lse_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_t::disable) ; }
  inline void lse_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_t::enable) ; }
  inline clock_interrupt_t::lse_ready_interupt_t::enum_t lse_ready_interupt() const { return clock_interrupt.rd<clock_interrupt_t::lse_ready_interupt_t>() ; }

  inline void hsi_ready_interupt( const clock_interrupt_t::hsi_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void hsi_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_t::disable) ; }
  inline void hsi_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_t::enable) ; }
  inline clock_interrupt_t::hsi_ready_interupt_t::enum_t hsi_ready_interupt() const { return clock_interrupt.rd<clock_interrupt_t::hsi_ready_interupt_t>() ; }

  inline void hse_ready_interupt( const clock_interrupt_t::hse_ready_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void hse_ready_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_t::disable) ; }
  inline void hse_ready_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_t::enable) ; }
  inline clock_interrupt_t::hse_ready_interupt_t::enum_t hse_ready_interupt() const { return clock_interrupt.rd<clock_interrupt_t::hse_ready_interupt_t>() ; }

  inline void pll_interupt( const clock_interrupt_t::pll_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void pll_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::pll_interupt_t::disable) ; }
  inline void pll_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::pll_interupt_t::enable) ; }
  inline clock_interrupt_t::pll_interupt_t::enum_t pll_interupt() const { return clock_interrupt.rd<clock_interrupt_t::pll_interupt_t>() ; }

  inline void pll_i2s_interupt( const clock_interrupt_t::pll_i2s_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void pll_i2s_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::pll_i2s_interupt_t::disable) ; }
  inline void pll_i2s_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::pll_i2s_interupt_t::enable) ; }
  inline clock_interrupt_t::pll_i2s_interupt_t::enum_t pll_i2s_interupt() const { return clock_interrupt.rd<clock_interrupt_t::pll_i2s_interupt_t>() ; }

  inline void pll_sai_interupt( const clock_interrupt_t::pll_sai_interupt_t::enum_t val) { clock_interrupt.rmw(val) ; }
  inline void pll_sai_interupt_disable() { clock_interrupt.rmw(clock_interrupt_t::pll_sai_interupt_t::disable) ; }
  inline void pll_sai_interupt_enable() { clock_interrupt.rmw(clock_interrupt_t::pll_sai_interupt_t::enable) ; }
  inline clock_interrupt_t::pll_sai_interupt_t::enum_t pll_sai_interupt() const { return clock_interrupt.rd<clock_interrupt_t::pll_sai_interupt_t>() ; }

  inline void lsi_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::lsi_ready_interupt_clear_t::perform) ; }
  inline void lse_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::lse_ready_interupt_clear_t::perform) ; }
  inline void hsi_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::hsi_ready_interupt_clear_t::perform) ; }
  inline void hse_ready_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::hse_ready_interupt_clear_t::perform) ; }
  inline void pll_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::pll_interupt_clear_t::perform) ; }
  inline void pll_i2s_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::pll_i2s_interupt_clear_t::perform) ; }
  inline void pll_sai_interupt_clear() { clock_interrupt.rmw(clock_interrupt_t::pll_sai_interupt_clear_t::perform) ; }
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
    struct eth_reset_state_t { enum enum_t { offset=25,mask=0b1, no_reset=0, reset } ; } ;
    struct usbhs_reset_state_t  { enum enum_t { offset=29,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { gpioa=gpioa_reset_state_t::offset ,
                        gpiob=gpiob_reset_state_t::offset ,
  		        gpioc=gpioc_reset_state_t::offset ,
  		        gpiod=gpiod_reset_state_t::offset ,
  		        gpioe=gpioe_reset_state_t::offset ,
  		        gpiof=gpiof_reset_state_t::offset ,
  		        gpiog=gpiog_reset_state_t::offset ,
  		        gpioh=gpioh_reset_state_t::offset ,
  		        gpioi=gpioj_reset_state_t::offset ,
  		        gpioj=gpioh_reset_state_t::offset ,
  		        gpiok=gpiok_reset_state_t::offset ,
  		        crc=crc_reset_state_t::offset,
  		        dma1=dma1_reset_state_t::offset,
  		        dma2=dma2_reset_state_t::offset,
  		        dma2d=dma2d_reset_state_t::offset,
  		        eth=eth_reset_state_t::offset,
  		        usbhs=usbhs_reset_state_t::offset,
                      } ;
  }  ;

  inline void gpioa_reset_state( const ahb1_peripheral_reset_t::gpioa_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioa_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioa_reset_state_t::no_reset) ; }
  inline void gpioa_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioa_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioa_reset_state_t::enum_t gpioa_reset_state() const  { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioa_reset_state_t>() ; }
  inline void gpioa_reset() { gpioa_reset_state_reset() ; gpioa_reset_state_no_reset(); }

  inline void gpiob_reset_state( const ahb1_peripheral_reset_t::gpiob_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiob_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiob_reset_state_t::no_reset) ; }
  inline void gpiob_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiob_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpiob_reset_state_t::enum_t gpiob_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiob_reset_state_t>() ; }
  inline void gpiob_reset() { gpiob_reset_state_reset() ; gpiob_reset_state_no_reset(); }

  inline void gpioc_reset_state( const ahb1_peripheral_reset_t::gpioc_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioc_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioc_reset_state_t::no_reset) ; }
  inline void gpioc_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioc_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioc_reset_state_t::enum_t gpioc_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioc_reset_state_t>() ; }
  inline void gpioc_reset() { gpioc_reset_state_reset() ; gpioc_reset_state_no_reset(); }

  inline void gpiod_reset_state( const ahb1_peripheral_reset_t::gpiod_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiod_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiod_reset_state_t::no_reset) ; }
  inline void gpiod_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiod_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpiod_reset_state_t::enum_t gpiod_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiod_reset_state_t>() ; }
  inline void gpiod_reset() { gpiod_reset_state_reset() ; gpiod_reset_state_no_reset(); }

  inline void gpioe_reset_state( const ahb1_peripheral_reset_t::gpioe_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioe_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioe_reset_state_t::no_reset) ; }
  inline void gpioe_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioe_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioe_reset_state_t::enum_t gpioe_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioe_reset_state_t>() ; }
  inline void gpioe_reset() { gpioe_reset_state_reset() ; gpioe_reset_state_no_reset(); }

  inline void gpiof_reset_state( const ahb1_peripheral_reset_t::gpiof_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiof_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiof_reset_state_t::no_reset) ; }
  inline void gpiof_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiof_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpiof_reset_state_t::enum_t gpiof_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiof_reset_state_t>() ; }
  inline void gpiof_reset() { gpiof_reset_state_reset() ; gpiof_reset_state_no_reset(); }

  inline void gpiog_reset_state( const ahb1_peripheral_reset_t::gpiog_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiog_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiog_reset_state_t::no_reset) ; }
  inline void gpiog_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiog_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpiog_reset_state_t::enum_t gpiog_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiog_reset_state_t>() ; }
  inline void gpiog_reset() { gpiog_reset_state_reset() ; gpiog_reset_state_no_reset(); }

  inline void gpioh_reset_state( const ahb1_peripheral_reset_t::gpioh_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioh_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioh_reset_state_t::no_reset) ; }
  inline void gpioh_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioh_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioh_reset_state_t::enum_t gpioh_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioh_reset_state_t>() ; }
  inline void gpioh_reset() { gpioh_reset_state_reset() ; gpioh_reset_state_no_reset(); }

  inline void gpioi_reset_state( const ahb1_peripheral_reset_t::gpioi_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioi_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioi_reset_state_t::no_reset) ; }
  inline void gpioi_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioi_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioi_reset_state_t::enum_t gpioi_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioi_reset_state_t>() ; }
  inline void gpioi_reset() { gpioi_reset_state_reset() ; gpioi_reset_state_no_reset(); }

  inline void gpioj_reset_state( const ahb1_peripheral_reset_t::gpioj_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpioj_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioj_reset_state_t::no_reset) ; }
  inline void gpioj_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpioj_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpioj_reset_state_t::enum_t gpioj_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpioj_reset_state_t>() ; }
  inline void gpioj_reset() { gpioj_reset_state_reset() ; gpioj_reset_state_no_reset(); }

  inline void gpiok_reset_state( const ahb1_peripheral_reset_t::gpiok_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void gpiok_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiok_reset_state_t::no_reset) ; }
  inline void gpiok_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::gpiok_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::gpiok_reset_state_t::enum_t gpiok_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::gpiok_reset_state_t>() ; }
  inline void gpiok_reset() { gpiok_reset_state_reset() ; gpiok_reset_state_no_reset(); }

  inline void crc_reset_state( const ahb1_peripheral_reset_t::crc_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void crc_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::crc_reset_state_t::no_reset) ; }
  inline void crc_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::crc_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::crc_reset_state_t::enum_t crc_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::crc_reset_state_t>() ; }
  inline void crc_reset() { crc_reset_state_reset() ; crc_reset_state_no_reset(); }

  inline void dma1_reset_state( const ahb1_peripheral_reset_t::dma1_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma1_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma1_reset_state_t::no_reset) ; }
  inline void dma1_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma1_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::dma1_reset_state_t::enum_t dma1_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma1_reset_state_t>() ; }
  inline void dma1_reset() { dma1_reset_state_reset() ; dma1_reset_state_no_reset(); }

  inline void dma2_reset_state( const ahb1_peripheral_reset_t::dma2_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma2_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2_reset_state_t::no_reset) ; }
  inline void dma2_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::dma2_reset_state_t::enum_t dma2_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma2_reset_state_t>() ; }
  inline void dma2_reset() { dma2_reset_state_reset() ; dma2_reset_state_no_reset(); }

  inline void dma2d_reset_state( const ahb1_peripheral_reset_t::dma2d_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void dma2d_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2d_reset_state_t::no_reset) ; }
  inline void dma2d_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::dma2d_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::dma2d_reset_state_t::enum_t dma2d_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::dma2d_reset_state_t>() ; }
  inline void dma2d_reset() { dma2d_reset_state_reset() ; dma2d_reset_state_no_reset(); }

  inline void eth_reset_state( const ahb1_peripheral_reset_t::eth_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void eth_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::eth_reset_state_t::no_reset) ; }
  inline void eth_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::eth_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::eth_reset_state_t::enum_t eth_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::eth_reset_state_t>() ; }
  inline void eth_reset() { eth_reset_state_reset() ; eth_reset_state_no_reset(); }

  inline void usbhs_reset_state( const ahb1_peripheral_reset_t::usbhs_reset_state_t::enum_t val) { ahb1_peripheral_reset.rmw(val) ; }
  inline void usbhs_reset_state_no_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::usbhs_reset_state_t::no_reset) ; }
  inline void usbhs_reset_state_reset() { ahb1_peripheral_reset.rmw(ahb1_peripheral_reset_t::usbhs_reset_state_t::reset) ; }
  inline ahb1_peripheral_reset_t::usbhs_reset_state_t::enum_t usbhs_reset_state() const { return ahb1_peripheral_reset.rd<ahb1_peripheral_reset_t::usbhs_reset_state_t>() ; }
  inline void usbhs_reset() { usbhs_reset_state_reset() ; usbhs_reset_state_no_reset(); }

  inline void state_reset(const ahb1_peripheral_reset_t::peripheral_t val) { ahb1_peripheral_reset.rmw( ahb1_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const ahb1_peripheral_reset_t::peripheral_t val){ ahb1_peripheral_reset.rmw( ahb1_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const ahb1_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct ahb2_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct dcmi_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct jpeg_reset_state_t  { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;
    struct crypt_reset_state_t { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct hash_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct rng_reset_state_t   { enum enum_t { offset=6, mask=0b1, no_reset=0, reset } ; } ;
    struct usbfs_reset_state_t { enum enum_t { offset=7, mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { dcmi=dcmi_reset_state_t::offset ,
                        jpeg=dcmi_reset_state_t::offset ,
    	                crypt=crypt_reset_state_t::offset ,
    	                hash=hash_reset_state_t::offset ,
    		        rng=rng_reset_state_t::offset ,
    		        usbfs=usbfs_reset_state_t::offset ,
                      } ;
  } ;


  inline void dcmi_reset_state( const ahb2_peripheral_reset_t::dcmi_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void dcmi_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::dcmi_reset_state_t::no_reset) ; }
  inline void dcmi_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::dcmi_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::dcmi_reset_state_t::enum_t dcmi_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::dcmi_reset_state_t>() ; }
  inline void dcmi_reset() { dcmi_reset_state_reset() ; dcmi_reset_state_no_reset(); }

  inline void jpeg_reset_state( const ahb2_peripheral_reset_t::jpeg_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void jpeg_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::jpeg_reset_state_t::no_reset) ; }
  inline void jpeg_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::jpeg_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::jpeg_reset_state_t::enum_t jpeg_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::jpeg_reset_state_t>() ; }
  inline void jpeg_reset() { jpeg_reset_state_reset() ; jpeg_reset_state_no_reset(); }

  inline void crypt_reset_state( const ahb2_peripheral_reset_t::crypt_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void crypt_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::crypt_reset_state_t::no_reset) ; }
  inline void crypt_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::crypt_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::crypt_reset_state_t::enum_t crypt_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::crypt_reset_state_t>() ; }
  inline void crypt_reset() { crypt_reset_state_reset() ; crypt_reset_state_no_reset(); }

  inline void hash_reset_state( const ahb2_peripheral_reset_t::hash_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void hash_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::hash_reset_state_t::no_reset) ; }
  inline void hash_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::hash_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::hash_reset_state_t::enum_t hash_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::hash_reset_state_t>() ; }
  inline void hash_reset() { hash_reset_state_reset() ; hash_reset_state_no_reset(); }

  inline void rng_reset_state( const ahb2_peripheral_reset_t::rng_reset_state_t::enum_t val) { ahb2_peripheral_reset.rmw(val) ; }
  inline void rng_reset_state_no_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::rng_reset_state_t::no_reset) ; }
  inline void rng_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::rng_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::rng_reset_state_t::enum_t rng_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::rng_reset_state_t>() ; }
  inline void rng_reset() { rng_reset_state_reset() ; rng_reset_state_no_reset(); }

  inline void usbfs_reset_state( const ahb2_peripheral_reset_t::usbfs_reset_state_t::enum_t val){ ahb2_peripheral_reset.rmw(val) ; }
  inline void usbfs_reset_state_no_reset(){ ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::usbfs_reset_state_t::no_reset) ; }
  inline void usbfs_reset_state_reset() { ahb2_peripheral_reset.rmw(ahb2_peripheral_reset_t::usbfs_reset_state_t::reset) ; }
  inline ahb2_peripheral_reset_t::usbfs_reset_state_t::enum_t usbfs_reset_state() const { return ahb2_peripheral_reset.rd<ahb2_peripheral_reset_t::usbfs_reset_state_t>() ; }
  inline void usbfs_reset() { usbfs_reset_state_reset() ; usbfs_reset_state_no_reset(); }

  inline void state_reset(const ahb2_peripheral_reset_t::peripheral_t val) { ahb2_peripheral_reset.rmw( ahb2_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const ahb2_peripheral_reset_t::peripheral_t val){ ahb2_peripheral_reset.rmw( ahb2_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const ahb2_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct ahb3_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct fmc_reset_state_t  { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct qspi_reset_state_t  { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t {
                       fmc=fmc_reset_state_t::offset,
		       qspi=qspi_reset_state_t::offset,
                      } ;
  }   ;

  inline void fmc_reset_state( const ahb3_peripheral_reset_t::fmc_reset_state_t::enum_t val){ ahb3_peripheral_reset.rmw(val) ; }
  inline void fmc_reset_state_no_reset(){ ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t::fmc_reset_state_t::no_reset) ; }
  inline void fmc_reset_state_reset() { ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t::fmc_reset_state_t::reset) ; }
  inline ahb3_peripheral_reset_t::fmc_reset_state_t::enum_t fmc_reset_state() const { return ahb3_peripheral_reset.rd<ahb3_peripheral_reset_t::fmc_reset_state_t>() ; }
  inline void fmc_reset() { fmc_reset_state_reset() ; fmc_reset_state_no_reset(); }

  inline void  qspi_reset_state( const ahb3_peripheral_reset_t:: qspi_reset_state_t::enum_t val){ ahb3_peripheral_reset.rmw(val) ; }
  inline void  qspi_reset_state_no_reset(){ ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t:: qspi_reset_state_t::no_reset) ; }
  inline void  qspi_reset_state_reset() { ahb3_peripheral_reset.rmw(ahb3_peripheral_reset_t:: qspi_reset_state_t::reset) ; }
  inline ahb3_peripheral_reset_t:: qspi_reset_state_t::enum_t  qspi_reset_state() const { return ahb3_peripheral_reset.rd<ahb3_peripheral_reset_t:: qspi_reset_state_t>() ; }
  inline void qspi_reset() { qspi_reset_state_reset() ; qspi_reset_state_no_reset(); }

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
    struct lptim1_reset_state_t{ enum enum_t { offset=9, mask=0b1, no_reset=0, reset } ; } ;
    struct wwdg_reset_state_t  { enum enum_t { offset=11,mask=0b1, no_reset=0, reset } ; } ;
    struct can3_reset_state_t  { enum enum_t { offset=13,mask=0b1, no_reset=0, reset } ; } ;
    struct spi2_reset_state_t  { enum enum_t { offset=14,mask=0b1, no_reset=0, reset } ; } ;
    struct spi3_reset_state_t  { enum enum_t { offset=15,mask=0b1, no_reset=0, reset } ; } ;
    struct spdif_reset_state_t { enum enum_t { offset=16,mask=0b1, no_reset=0, reset } ; } ;
    struct uart2_reset_state_t { enum enum_t { offset=17,mask=0b1, no_reset=0, reset } ; } ;
    struct uart3_reset_state_t { enum enum_t { offset=18,mask=0b1, no_reset=0, reset } ; } ;
    struct uart4_reset_state_t { enum enum_t { offset=19,mask=0b1, no_reset=0, reset } ; } ;
    struct uart5_reset_state_t { enum enum_t { offset=20,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c1_reset_state_t  { enum enum_t { offset=21,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c2_reset_state_t  { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c3_reset_state_t  { enum enum_t { offset=23,mask=0b1, no_reset=0, reset } ; } ;
    struct i2c4_reset_state_t  { enum enum_t { offset=24,mask=0b1, no_reset=0, reset } ; } ;
    struct can1_reset_state_t  { enum enum_t { offset=25,mask=0b1, no_reset=0, reset } ; } ;
    struct can2_reset_state_t  { enum enum_t { offset=26,mask=0b1, no_reset=0, reset } ; } ;
    struct cec_reset_state_t   { enum enum_t { offset=27,mask=0b1, no_reset=0, reset } ; } ;
    struct pwr_reset_state_t   { enum enum_t { offset=28,mask=0b1, no_reset=0, reset } ; } ;
    struct dac_reset_state_t   { enum enum_t { offset=29,mask=0b1, no_reset=0, reset } ; } ;
    struct uart7_reset_state_t { enum enum_t { offset=19,mask=0b1, no_reset=0, reset } ; } ;
    struct uart8_reset_state_t { enum enum_t { offset=20,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { tim2=tim2_reset_state_t::offset,
                        tim3=tim3_reset_state_t::offset,
  			tim4=tim4_reset_state_t::offset,
  			tim5=tim5_reset_state_t::offset,
  			tim6=tim6_reset_state_t::offset,
  			tim7=tim7_reset_state_t::offset,
  			tim12=tim12_reset_state_t::offset,
  			tim13=tim13_reset_state_t::offset,
  			tim14=tim14_reset_state_t::offset,
  			lptim1=lptim1_reset_state_t::offset,
  			wwdg=wwdg_reset_state_t::offset,
  			can3=can3_reset_state_t::offset,
  			spi2=spi2_reset_state_t::offset,
  			spi3=spi3_reset_state_t::offset,
  			spdif=spdif_reset_state_t::offset,
  			uart2=uart2_reset_state_t::offset,
  			uart3=uart3_reset_state_t::offset,
  			uart4=uart4_reset_state_t::offset,
  			uart5=uart5_reset_state_t::offset,
  			i2c1=i2c1_reset_state_t::offset,
  			i2c2=i2c2_reset_state_t::offset,
  			i2c3=i2c3_reset_state_t::offset,
  			i2c4=i2c4_reset_state_t::offset,
  			can1=can1_reset_state_t::offset,
  			can2=can2_reset_state_t::offset,
  			cec=cec_reset_state_t::offset,
  			pwr=pwr_reset_state_t::offset,
  			dac=dac_reset_state_t::offset,
  			uart7=uart7_reset_state_t::offset,
  			uart8=uart8_reset_state_t::offset
                      } ;

  } ;



  inline void tim2_reset_state( const apb1_peripheral_reset_t::tim2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::no_reset) ; }
  inline void tim2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim2_reset_state_t::enum_t tim2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim2_reset_state_t>() ; }
  inline void tim2_reset() { tim2_reset_state_reset() ; tim2_reset_state_no_reset(); }

  inline void tim3_reset_state( const apb1_peripheral_reset_t::tim3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::no_reset) ; }
  inline void tim3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim3_reset_state_t::enum_t tim3_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim3_reset_state_t>() ; }
  inline void tim3_reset() { tim3_reset_state_reset() ; tim3_reset_state_no_reset(); }

  inline void tim4_reset_state( const apb1_peripheral_reset_t::tim4_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim4_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim4_reset_state_t::no_reset) ; }
  inline void tim4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim4_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim4_reset_state_t::enum_t tim4_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim4_reset_state_t>() ; }
  inline void tim4_reset() { tim4_reset_state_reset() ; tim4_reset_state_no_reset(); }

  inline void tim5_reset_state( const apb1_peripheral_reset_t::tim5_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim5_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim5_reset_state_t::no_reset) ; }
  inline void tim5_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim5_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim5_reset_state_t::enum_t tim5_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim5_reset_state_t>() ; }
  inline void tim5_reset() { tim5_reset_state_reset() ; tim5_reset_state_no_reset(); }

  inline void tim6_reset_state( const apb1_peripheral_reset_t::tim6_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim6_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::no_reset) ; }
  inline void tim6_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim6_reset_state_t::enum_t tim6_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim6_reset_state_t>() ; }
  inline void tim6_reset() { tim6_reset_state_reset() ; tim6_reset_state_no_reset(); }

  inline void tim7_reset_state( const apb1_peripheral_reset_t::tim7_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim7_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::no_reset) ; }
  inline void tim7_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim7_reset_state_t::enum_t tim7_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim7_reset_state_t>() ; }
  inline void tim7_reset() { tim7_reset_state_reset() ; tim7_reset_state_no_reset(); }

  inline void tim12_reset_state( const apb1_peripheral_reset_t::tim12_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim12_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim12_reset_state_t::no_reset) ; }
  inline void tim12_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim12_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim12_reset_state_t::enum_t tim12_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim12_reset_state_t>() ; }
  inline void tim12_reset() { tim12_reset_state_reset() ; tim12_reset_state_no_reset(); }

  inline void tim13_reset_state( const apb1_peripheral_reset_t::tim13_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim13_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim13_reset_state_t::no_reset) ; }
  inline void tim13_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim13_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim13_reset_state_t::enum_t tim13_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim13_reset_state_t>() ; }
  inline void tim13_reset() { tim13_reset_state_reset() ; tim13_reset_state_no_reset(); }

  inline void tim14_reset_state( const apb1_peripheral_reset_t::tim14_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void tim14_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim14_reset_state_t::no_reset) ; }
  inline void tim14_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim14_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::tim14_reset_state_t::enum_t tim14_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim14_reset_state_t>() ; }
  inline void tim14_reset() { tim14_reset_state_reset() ; tim14_reset_state_no_reset(); }

  inline void lptim1_reset_state( const apb1_peripheral_reset_t::lptim1_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void lptim1_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lptim1_reset_state_t::no_reset) ; }
  inline void lptim1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lptim1_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::lptim1_reset_state_t::enum_t lptim1_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::lptim1_reset_state_t>() ; }
  inline void lptim1_reset() { lptim1_reset_state_reset() ; lptim1_reset_state_no_reset(); }

  inline void wwdg_reset_state( const apb1_peripheral_reset_t::wwdg_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void wwdg_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::no_reset) ; }
  inline void wwdg_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::wwdg_reset_state_t::enum_t wwdg_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::wwdg_reset_state_t>() ; }
  inline void wwdt_reset() { wwdg_reset_state_reset() ; wwdg_reset_state_no_reset(); }

  inline void spi2_reset_state( const apb1_peripheral_reset_t::spi2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void spi2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::no_reset) ; }
  inline void spi2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::spi2_reset_state_t::enum_t spi2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spi2_reset_state_t>() ; }
  inline void spi2_reset() { spi2_reset_state_reset() ; spi2_reset_state_no_reset(); }

  inline void spi3_reset_state( const apb1_peripheral_reset_t::spi3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void spi3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi3_reset_state_t::no_reset) ; }
  inline void spi3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi3_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::spi3_reset_state_t::enum_t spi3_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spi3_reset_state_t>() ; }
  inline void spi3_reset() { spi3_reset_state_reset() ; spi3_reset_state_no_reset(); }

  inline void spdif_reset_state( const apb1_peripheral_reset_t::spdif_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void spdif_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spdif_reset_state_t::no_reset) ; }
  inline void spdif_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spdif_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::spdif_reset_state_t::enum_t spdif_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spdif_reset_state_t>() ; }
  inline void spdif_reset() { spdif_reset_state_reset() ; spdif_reset_state_no_reset(); }

  inline void uart2_reset_state( const apb1_peripheral_reset_t::uart2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart2_reset_state_t::no_reset) ; }
  inline void uart2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart2_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart2_reset_state_t::enum_t uart2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart2_reset_state_t>() ; }
  inline void uart2_reset() { uart2_reset_state_reset() ; uart2_reset_state_no_reset(); }

  inline void uart3_reset_state( const apb1_peripheral_reset_t::uart3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart3_reset_state_t::no_reset) ; }
  inline void uart3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart3_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart3_reset_state_t::enum_t uart3_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart3_reset_state_t>() ; }
  inline void uart3_reset() { uart3_reset_state_reset() ; uart3_reset_state_no_reset(); }

  inline void uart4_reset_state( const apb1_peripheral_reset_t::uart4_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart4_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::no_reset) ; }
  inline void uart4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart4_reset_state_t::enum_t uart4_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart4_reset_state_t>() ; }
  inline void uart4_reset() { uart4_reset_state_reset() ; uart4_reset_state_no_reset(); }

  inline void uart5_reset_state( const apb1_peripheral_reset_t::uart5_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart5_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart5_reset_state_t::no_reset) ; }
  inline void uart5_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart5_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart5_reset_state_t::enum_t uart5_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart5_reset_state_t>() ; }
  inline void uart5_reset() { uart5_reset_state_reset() ; uart5_reset_state_no_reset(); }

  inline void i2c1_reset_state( const apb1_peripheral_reset_t::i2c1_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c1_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::no_reset) ; }
  inline void i2c1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::i2c1_reset_state_t::enum_t i2c1_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c1_reset_state_t>() ; }
  inline void i2c1_reset() { i2c1_reset_state_reset() ; i2c1_reset_state_no_reset(); }

  inline void i2c2_reset_state( const apb1_peripheral_reset_t::i2c2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::no_reset) ; }
  inline void i2c2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::i2c2_reset_state_t::enum_t i2c2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c2_reset_state_t>() ; }
  inline void i2c2_reset() { i2c2_reset_state_reset() ; i2c2_reset_state_no_reset(); }

  inline void i2c3_reset_state( const apb1_peripheral_reset_t::i2c3_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c3_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::no_reset) ; }
  inline void i2c3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::i2c3_reset_state_t::enum_t i2c3_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c3_reset_state_t>() ; }
  inline void i2c3_reset() { i2c3_reset_state_reset() ; i2c3_reset_state_no_reset(); }

  inline void i2c4_reset_state( const apb1_peripheral_reset_t::i2c4_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void i2c4_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c4_reset_state_t::no_reset) ; }
  inline void i2c4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c4_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::i2c4_reset_state_t::enum_t i2c4_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c4_reset_state_t>() ; }
  inline void i2c4_reset() { i2c4_reset_state_reset() ; i2c4_reset_state_no_reset(); }

  inline void cec_reset_state( const apb1_peripheral_reset_t::cec_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void cec_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::cec_reset_state_t::no_reset) ; }
  inline void cec_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::cec_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::cec_reset_state_t::enum_t cec_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::cec_reset_state_t>() ; }
  inline void cec_reset() { cec_reset_state_reset() ; cec_reset_state_no_reset(); }

  inline void can1_reset_state( const apb1_peripheral_reset_t::can1_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void can1_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can1_reset_state_t::no_reset) ; }
  inline void can1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can1_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::can1_reset_state_t::enum_t can1_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::can1_reset_state_t>() ; }
  inline void can1_reset() { can1_reset_state_reset() ; can1_reset_state_no_reset(); }

  inline void can2_reset_state( const apb1_peripheral_reset_t::can2_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void can2_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can2_reset_state_t::no_reset) ; }
  inline void can2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::can2_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::can2_reset_state_t::enum_t can2_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::can2_reset_state_t>() ; }
  inline void can2_reset() { can2_reset_state_reset() ; can2_reset_state_no_reset(); }

  inline void pwr_reset_state( const apb1_peripheral_reset_t::pwr_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void pwr_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::no_reset) ; }
  inline void pwr_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::pwr_reset_state_t::enum_t pwr_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::pwr_reset_state_t>() ; }
  inline void pwr_reset() { pwr_reset_state_reset() ; pwr_reset_state_no_reset(); }

  inline void dac_reset_state( const apb1_peripheral_reset_t::dac_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void dac_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::dac_reset_state_t::no_reset) ; }
  inline void dac_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::dac_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::dac_reset_state_t::enum_t dac_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::dac_reset_state_t>() ; }
  inline void dac_reset() { dac_reset_state_reset() ; dac_reset_state_no_reset(); }

  inline void uart7_reset_state( const apb1_peripheral_reset_t::uart7_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart7_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart7_reset_state_t::no_reset) ; }
  inline void uart7_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart7_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart7_reset_state_t::enum_t uart7_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart7_reset_state_t>() ; }
  inline void uart7_reset() { uart7_reset_state_reset() ; uart7_reset_state_no_reset(); }

  inline void uart8_reset_state( const apb1_peripheral_reset_t::uart8_reset_state_t::enum_t val){ apb1_peripheral_reset.rmw(val) ; }
  inline void uart8_reset_state_no_reset(){ apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart8_reset_state_t::no_reset) ; }
  inline void uart8_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart8_reset_state_t::reset) ; }
  inline apb1_peripheral_reset_t::uart8_reset_state_t::enum_t uart8_reset_state() const { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart8_reset_state_t>() ; }
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
    struct sdmmc2_reset_state_t  { enum enum_t { offset=7, mask=0b1, no_reset=0, reset } ; } ;
    struct adc_reset_state_t     { enum enum_t { offset=8, mask=0b1, no_reset=0, reset } ; } ;
    struct sdmmc1_reset_state_t  { enum enum_t { offset=11,mask=0b1, no_reset=0, reset } ; } ;
    struct spi1_reset_state_t    { enum enum_t { offset=12,mask=0b1, no_reset=0, reset } ; } ;
    struct spi4_reset_state_t    { enum enum_t { offset=13,mask=0b1, no_reset=0, reset } ; } ;
    struct syscfg_reset_state_t  { enum enum_t { offset=14,mask=0b1, no_reset=0, reset } ; } ;
    struct tim9_reset_state_t    { enum enum_t { offset=16,mask=0b1, no_reset=0, reset } ; } ;
    struct tim10_reset_state_t   { enum enum_t { offset=17,mask=0b1, no_reset=0, reset } ; } ;
    struct tim11_reset_state_t   { enum enum_t { offset=18,mask=0b1, no_reset=0, reset } ; } ;
    struct spi5_reset_state_t    { enum enum_t { offset=20,mask=0b1, no_reset=0, reset } ; } ;
    struct spi6_reset_state_t    { enum enum_t { offset=21,mask=0b1, no_reset=0, reset } ; } ;
    struct sai1_reset_state_t    { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;
    struct sai2_reset_state_t    { enum enum_t { offset=23,mask=0b1, no_reset=0, reset } ; } ;
    struct ltdc_reset_state_t    { enum enum_t { offset=26,mask=0b1, no_reset=0, reset } ; } ;
    struct dsi_reset_state_t     { enum enum_t { offset=27,mask=0b1, no_reset=0, reset } ; } ;
    struct dfsdm1_reset_state_t  { enum enum_t { offset=29,mask=0b1, no_reset=0, reset } ; } ;
    struct mdio_reset_state_t    { enum enum_t { offset=30,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t {   tim1=tim1_reset_state_t::offset,
                          tim8=tim8_reset_state_t::offset,
  			  usart1=usart1_reset_state_t::offset,
  			  usart6=usart6_reset_state_t::offset,
  			  sdmmc2=sdmmc2_reset_state_t::offset,
  			  adc=adc_reset_state_t::offset,
  			  sdmmc1=sdmmc1_reset_state_t::offset,
  			  spi1=spi1_reset_state_t::offset,
  			  spi4=spi4_reset_state_t::offset,
  			  syscfg=syscfg_reset_state_t::offset,
  			  tim9=tim9_reset_state_t::offset,
  			  tim10=tim10_reset_state_t::offset,
  			  tim11=tim11_reset_state_t::offset,
  			  spi5=spi5_reset_state_t::offset,
  			  spi6=spi6_reset_state_t::offset,
  			  sai1=sai1_reset_state_t::offset,
  			  sai2=sai2_reset_state_t::offset,
  			  ltdc=ltdc_reset_state_t::offset,
  			  dsi=dsi_reset_state_t::offset,
  			  dfsdm1=dfsdm1_reset_state_t::offset,
  			  mdio=mdio_reset_state_t::offset,
                      };
  } ;



  inline void tim1_reset_state(const apb2_peripheral_reset_t::tim1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim1_reset_state_t::no_reset) ; }
  inline void tim1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::tim1_reset_state_t::enum_t tim1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim1_reset_state_t>() ; }
  inline void tim1_reset() { tim1_reset_state_reset() ; tim1_reset_state_no_reset(); }

  inline void tim8_reset_state(const apb2_peripheral_reset_t::tim8_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw (val) ; }
  inline void tim8_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim8_reset_state_t::no_reset) ; }
  inline void tim8_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim8_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::tim8_reset_state_t::enum_t tim8_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim8_reset_state_t>() ; }
  inline void tim8_reset() { tim8_reset_state_reset() ; tim8_reset_state_no_reset(); }

  inline void usart1_reset_state(const apb2_peripheral_reset_t::usart1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void usart1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::no_reset) ; }
  inline void usart1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::usart1_reset_state_t::enum_t usart1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::usart1_reset_state_t>() ; }
  inline void usart1_reset() { usart1_reset_state_reset() ; usart1_reset_state_no_reset(); }

  inline void usart6_reset_state(const apb2_peripheral_reset_t::usart6_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void usart6_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart6_reset_state_t::no_reset) ; }
  inline void usart6_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart6_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::usart6_reset_state_t::enum_t usart6_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::usart6_reset_state_t>() ; }
  inline void usart6_reset() { usart6_reset_state_reset() ; usart6_reset_state_no_reset(); }

  inline void sdmmc2_reset_state(const apb2_peripheral_reset_t::sdmmc2_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sdmmc2_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdmmc2_reset_state_t::no_reset) ; }
  inline void sdmmc2_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdmmc2_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::sdmmc2_reset_state_t::enum_t sdmmc2_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sdmmc2_reset_state_t>() ; }
  inline void sdmmc2_reset() { sdmmc2_reset_state_reset() ; sdmmc2_reset_state_no_reset(); }

  inline void adc_reset_state(const apb2_peripheral_reset_t::adc_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void adc_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::no_reset) ; }
  inline void adc_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::adc_reset_state_t::enum_t adc_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::adc_reset_state_t>() ; }
  inline void adc_reset() { adc_reset_state_reset() ; adc_reset_state_no_reset(); }

  inline void sdmmc1_reset_state(const apb2_peripheral_reset_t::sdmmc1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sdmmc1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdmmc1_reset_state_t::no_reset) ; }
  inline void sdmmc1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sdmmc1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::sdmmc1_reset_state_t::enum_t sdmmc1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sdmmc1_reset_state_t>() ; }
  inline void sdmmc1_reset() { sdmmc1_reset_state_reset() ; sdmmc1_reset_state_no_reset(); }

  inline void spi1_reset_state(const apb2_peripheral_reset_t::spi1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::no_reset) ; }
  inline void spi1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::spi1_reset_state_t::enum_t spi1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi1_reset_state_t>() ; }
  inline void spi1_reset() { spi1_reset_state_reset() ; spi1_reset_state_no_reset(); }

  inline void spi4_reset_state(const apb2_peripheral_reset_t::spi4_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi4_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi4_reset_state_t::no_reset) ; }
  inline void spi4_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi4_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::spi4_reset_state_t::enum_t spi4_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi4_reset_state_t>() ; }
  inline void spi4_reset() { spi4_reset_state_reset() ; spi4_reset_state_no_reset(); }

  inline void syscfg_reset_state(const apb2_peripheral_reset_t::syscfg_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void syscfg_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::no_reset) ; }
  inline void syscfg_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::syscfg_reset_state_t::enum_t syscfg_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::syscfg_reset_state_t>() ; }
  inline void syscfg_reset() { syscfg_reset_state_reset() ; syscfg_reset_state_no_reset(); }

  inline void tim9_reset_state(const apb2_peripheral_reset_t::tim9_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim9_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim9_reset_state_t::no_reset) ; }
  inline void tim9_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim9_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::tim9_reset_state_t::enum_t tim9_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim9_reset_state_t>() ; }
  inline void tim9_reset() { tim9_reset_state_reset() ; tim9_reset_state_no_reset(); }

  inline void tim10_reset_state(const apb2_peripheral_reset_t::tim10_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim10_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim10_reset_state_t::no_reset) ; }
  inline void tim10_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim10_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::tim10_reset_state_t::enum_t tim10_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim10_reset_state_t>() ; }
  inline void tim10_reset() { tim10_reset_state_reset() ; tim10_reset_state_no_reset(); }

  inline void tim11_reset_state(const apb2_peripheral_reset_t::tim11_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void tim11_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim11_reset_state_t::no_reset) ; }
  inline void tim11_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim11_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::tim11_reset_state_t::enum_t tim11_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim11_reset_state_t>() ; }
  inline void tim11_reset() { tim11_reset_state_reset() ; tim11_reset_state_no_reset(); }

  inline void spi5_reset_state(const apb2_peripheral_reset_t::spi5_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi5_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi5_reset_state_t::no_reset) ; }
  inline void spi5_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi5_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::spi5_reset_state_t::enum_t spi5_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi5_reset_state_t>() ; }
  inline void spi5_reset() { spi5_reset_state_reset() ; spi5_reset_state_no_reset(); }

  inline void spi6_reset_state(const apb2_peripheral_reset_t::spi6_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void spi6_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi6_reset_state_t::no_reset) ; }
  inline void spi6_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi6_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::spi6_reset_state_t::enum_t spi6_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi6_reset_state_t>() ; }
  inline void spi6_reset() { spi6_reset_state_reset() ; spi6_reset_state_no_reset(); }

  inline void sai1_reset_state(const apb2_peripheral_reset_t::sai1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sai1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai1_reset_state_t::no_reset) ; }
  inline void sai1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::sai1_reset_state_t::enum_t sai1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sai1_reset_state_t>() ; }
  inline void sai1_reset() { sai1_reset_state_reset() ; sai1_reset_state_no_reset(); }

  inline void sai2_reset_state(const apb2_peripheral_reset_t::sai2_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void sai2_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai2_reset_state_t::no_reset) ; }
  inline void sai2_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::sai2_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::sai2_reset_state_t::enum_t sai2_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::sai2_reset_state_t>() ; }
  inline void sai2_reset() { sai2_reset_state_reset() ; sai2_reset_state_no_reset(); }

  inline void ltdc_reset_state(const apb2_peripheral_reset_t::ltdc_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void ltdc_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::ltdc_reset_state_t::no_reset) ; }
  inline void ltdc_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::ltdc_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::ltdc_reset_state_t::enum_t ltdc_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::ltdc_reset_state_t>() ; }
  inline void ltdc_reset() { ltdc_reset_state_reset() ; ltdc_reset_state_no_reset(); }

  inline void dsi_reset_state(const apb2_peripheral_reset_t::dsi_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void dsi_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dsi_reset_state_t::no_reset) ; }
  inline void dsi_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dsi_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::dsi_reset_state_t::enum_t dsi_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::dsi_reset_state_t>() ; }
  inline void dsi_reset() { dsi_reset_state_reset() ; dsi_reset_state_no_reset(); }

  inline void dfsdm1_reset_state(const apb2_peripheral_reset_t::dfsdm1_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void dfsdm1_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dfsdm1_reset_state_t::no_reset) ; }
  inline void dfsdm1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dfsdm1_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::dfsdm1_reset_state_t::enum_t dfsdm1_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::dfsdm1_reset_state_t>() ; }
  inline void dfsdm1_reset() { dfsdm1_reset_state_reset() ; dfsdm1_reset_state_no_reset(); }

  inline void mdio_reset_state(const apb2_peripheral_reset_t::mdio_reset_state_t::enum_t val){ apb2_peripheral_reset.rmw(val) ; }
  inline void mdio_reset_state_no_reset(){ apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::mdio_reset_state_t::no_reset) ; }
  inline void mdio_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::mdio_reset_state_t::reset) ; }
  inline apb2_peripheral_reset_t::mdio_reset_state_t::enum_t mdio_reset_state() const { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::mdio_reset_state_t>() ; }
  inline void mdio_reset() { mdio_reset_state_reset() ; mdio_reset_state_no_reset(); }

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
    struct eth_t      { enum enum_t { offset=25,mask=0b1, disable=0, enable } ; } ;
    struct eth_tx_t   { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;
    struct eth_rx_t   { enum enum_t { offset=27,mask=0b1, disable=0, enable } ; } ;
    struct eth_ptp_t  { enum enum_t { offset=28,mask=0b1, disable=0, enable } ; } ;
    struct usbhs_t       { enum enum_t { offset=29,mask=0b1, disable=0, enable } ; } ;
    struct usbhs_ulpi_t  { enum enum_t { offset=30,mask=0b1, disable=0, enable } ; } ;

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
			dma2d=dma2d_t::offset,
			eth=eth_t::offset,
			eth_tx=eth_tx_t::offset,
			eth_rx=eth_rx_t::offset,
			eth_ptp=eth_ptp_t::offset,
			usbhs=usbhs_t::offset,
			usbhs_ulpi=usbhs_ulpi_t::offset
                      } ;
  } ;

  inline void gpioa_state(const ahb1_peripheral_clock_t::gpioa_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioa_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioa_t::disable) ; }
  inline void gpioa_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioa_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioa_t::enum_t gpioa_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioa_t>() ; }

  inline void gpiob_state(const ahb1_peripheral_clock_t::gpiob_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpiob_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiob_t::disable) ; }
  inline void gpiob_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiob_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpiob_t::enum_t gpiob_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiob_t>() ; }

  inline void gpioc_state(const ahb1_peripheral_clock_t::gpioc_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioc_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioc_t::disable) ; }
  inline void gpioc_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioc_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioc_t::enum_t gpioc_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioc_t>() ; }

  inline void gpiod_state(const ahb1_peripheral_clock_t::gpiod_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpiod_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiod_t::disable) ; }
  inline void gpiod_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiod_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpiod_t::enum_t gpiod_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiod_t>() ; }

  inline void gpioe_state(const ahb1_peripheral_clock_t::gpioe_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioe_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioe_t::disable) ; }
  inline void gpioe_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioe_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioe_t::enum_t gpioe_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioe_t>() ; }

  inline void gpiof_state(const ahb1_peripheral_clock_t::gpiof_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpiof_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiof_t::disable) ; }
  inline void gpiof_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiof_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpiof_t::enum_t gpiof_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiof_t>() ; }

  inline void gpiog_state(const ahb1_peripheral_clock_t::gpiog_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpiog_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiog_t::disable) ; }
  inline void gpiog_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiog_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpiog_t::enum_t gpiog_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiog_t>() ; }

  inline void gpioh_state(const ahb1_peripheral_clock_t::gpioh_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioh_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioh_t::disable) ; }
  inline void gpioh_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioh_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioh_t::enum_t gpioh_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioh_t>() ; }

  inline void gpioi_state(const ahb1_peripheral_clock_t::gpioi_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioi_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioi_t::disable) ; }
  inline void gpioi_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioi_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioi_t::enum_t gpioi_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioi_t>() ; }

  inline void gpioj_state(const ahb1_peripheral_clock_t::gpioj_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpioj_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioj_t::disable) ; }
  inline void gpioj_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpioj_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpioj_t::enum_t gpioj_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpioj_t>() ; }

  inline void gpiok_state(const ahb1_peripheral_clock_t::gpiok_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void gpiok_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiok_t::disable) ; }
  inline void gpiok_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::gpiok_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::gpiok_t::enum_t gpiok_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::gpiok_t>() ; }

  inline void crc_state(const ahb1_peripheral_clock_t::crc_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void crc_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::crc_t::disable) ; }
  inline void crc_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::crc_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::crc_t::enum_t crc_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::crc_t>() ; }

  inline void backup_sram_state(const ahb1_peripheral_clock_t::backup_sram_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void backup_sram_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::backup_sram_t::disable) ; }
  inline void backup_sram_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::backup_sram_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::backup_sram_t::enum_t backup_sram_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::backup_sram_t>() ; }

  inline void ccm_state(const ahb1_peripheral_clock_t::ccm_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void ccm_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ccm_t::disable) ; }
  inline void ccm_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::ccm_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::ccm_t::enum_t ccm_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::ccm_t>() ; }

  inline void dma1_state(const ahb1_peripheral_clock_t::dma1_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void dma1_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma1_t::disable) ; }
  inline void dma1_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma1_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::dma1_t::enum_t dma1_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma1_t>() ; }

  inline void dma2_state(const ahb1_peripheral_clock_t::dma2_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void dma2_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2_t::disable) ; }
  inline void dma2_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::dma2_t::enum_t dma2_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma2_t>() ; }

  inline void dma2d_state(const ahb1_peripheral_clock_t::dma2d_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void dma2d_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2d_t::disable) ; }
  inline void dma2d_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::dma2d_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::dma2d_t::enum_t dma2d_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::dma2d_t>() ; }

  inline void eth_state(const ahb1_peripheral_clock_t::eth_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void eth_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_t::disable) ; }
  inline void eth_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::eth_t::enum_t eth_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::eth_t>() ; }

  inline void eth_tx_state(const ahb1_peripheral_clock_t::eth_tx_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void eth_tx_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_tx_t::disable) ; }
  inline void eth_tx_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_tx_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::eth_tx_t::enum_t eth_tx_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::eth_tx_t>() ; }

  inline void eth_rx_state(const ahb1_peripheral_clock_t::eth_rx_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void eth_rx_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_rx_t::disable) ; }
  inline void eth_rx_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_rx_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::eth_rx_t::enum_t eth_rx_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::eth_rx_t>() ; }

  inline void eth_ptp_state(const ahb1_peripheral_clock_t::eth_ptp_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void eth_ptp_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_ptp_t::disable) ; }
  inline void eth_ptp_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::eth_ptp_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::eth_ptp_t::enum_t eth_ptp_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::eth_ptp_t>() ; }

  inline void usbhs_state(const ahb1_peripheral_clock_t::usbhs_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void usbhs_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::usbhs_t::disable) ; }
  inline void usbhs_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::usbhs_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::usbhs_t::enum_t usbhs_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::usbhs_t>() ; }

  inline void usbhs_ulpi_state(const ahb1_peripheral_clock_t::usbhs_ulpi_t::enum_t val){ ahb1_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void usbhs_ulpi_disable(){ ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::usbhs_ulpi_t::disable) ; }
  inline void usbhs_ulpi_enable() { ahb1_peripheral_clock.rmw(ahb1_peripheral_clock_t::usbhs_ulpi_t::enable) ; ahb_clock_enable_delay();}
  inline ahb1_peripheral_clock_t::usbhs_ulpi_t::enum_t usbhs_ulpi_state() const { return ahb1_peripheral_clock.rd<ahb1_peripheral_clock_t::usbhs_ulpi_t>() ; }

  inline void state_enable(const ahb1_peripheral_clock_t::peripheral_t val) { ahb1_peripheral_clock.rmw( ahb1_peripheral_clock_t::enable,  val ) ; ahb_clock_enable_delay();}
  inline void state_disable(const ahb1_peripheral_clock_t::peripheral_t val){ ahb1_peripheral_clock.rmw( ahb1_peripheral_clock_t::disable, val ) ; }

  struct ahb2_peripheral_clock_t : public read_write_32_t
    {
	  enum enum_t       {  mask=0b1, disable=0, enable } ;
      struct dcmi_t    { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
      struct jpeg_t    { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
      struct crypt_t   { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
      struct hash_t    { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
      struct rng_t     { enum enum_t { offset=6, mask=0b1, disable=0, enable } ; } ;
      struct usbfs_t   { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;

      enum peripheral_t { dcmi=dcmi_t::offset ,
	                  crypt=crypt_t::offset ,
			  hash=hash_t::offset ,
			  rng=rng_t::offset ,
			  usbfs=usbfs_t::offset ,
                        } ;
    };

  inline void dcmi_state(const ahb2_peripheral_clock_t::dcmi_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void dcmi_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::dcmi_t::disable) ; }
  inline void dcmi_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::dcmi_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::dcmi_t::enum_t dcmi_state() const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::dcmi_t>() ; }

  inline void jpeg_state(const ahb2_peripheral_clock_t::jpeg_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void jpeg_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::jpeg_t::disable) ; }
  inline void jpeg_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::jpeg_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::jpeg_t::enum_t jpeg_state() const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::jpeg_t>() ; }

  inline void crypt_state(const ahb2_peripheral_clock_t::crypt_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void crypt_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::crypt_t::disable) ; }
  inline void crypt_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::crypt_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::crypt_t::enum_t crypt_state() const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t:: crypt_t>() ; }

  inline void hash_state(const ahb2_peripheral_clock_t::hash_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void hash_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::hash_t::disable) ; }
  inline void hash_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::hash_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::hash_t::enum_t hash_state()const  { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::hash_t>() ; }

  inline void rng_state(const ahb2_peripheral_clock_t::rng_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void rng_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::rng_t::disable) ; }
  inline void rng_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::rng_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::rng_t::enum_t rng_state() const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::rng_t>() ; }

  inline void usbfs_state(const ahb2_peripheral_clock_t::usbfs_t::enum_t val){ ahb2_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void usbfs_disable(){ ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::usbfs_t::disable) ; }
  inline void usbfs_enable() { ahb2_peripheral_clock.rmw(ahb2_peripheral_clock_t::usbfs_t::enable) ; ahb_clock_enable_delay();}
  inline ahb2_peripheral_clock_t::usbfs_t::enum_t usbfs_state() const { return ahb2_peripheral_clock.rd<ahb2_peripheral_clock_t::usbfs_t>() ; }

  inline void state_enable(const ahb2_peripheral_clock_t::peripheral_t val) { ahb2_peripheral_clock.rmw( ahb2_peripheral_clock_t::enable, val ) ; ahb_clock_enable_delay();}
  inline void state_disable(const ahb2_peripheral_clock_t::peripheral_t val){ ahb2_peripheral_clock.rmw( ahb2_peripheral_clock_t::disable, val ) ; }

  struct ahb3_peripheral_clock_t : public read_write_32_t
  {
	enum enum_t       {  mask=0b1, disable=0, enable } ;
    struct fmc_t    { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct qspi_t   { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
    enum peripheral_t { fmc=fmc_t::offset } ;
  };

  inline void fmc_state(const ahb3_peripheral_clock_t::fmc_t::enum_t val){ ahb3_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void fmc_disable(){ ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::fmc_t::disable) ; }
  inline void fmc_enable() { ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::fmc_t::enable) ; ahb_clock_enable_delay();}
  inline ahb3_peripheral_clock_t::fmc_t::enum_t fmc_state() const { return ahb3_peripheral_clock.rd<ahb3_peripheral_clock_t::fmc_t>() ; }

  inline void qspi_state(const ahb3_peripheral_clock_t::qspi_t::enum_t val){ ahb3_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void qspi_disable(){ ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::qspi_t::disable) ; }
  inline void qspi_enable() { ahb3_peripheral_clock.rmw(ahb3_peripheral_clock_t::qspi_t::enable) ; ahb_clock_enable_delay();}
  inline ahb3_peripheral_clock_t::qspi_t::enum_t qspi_state() const { return ahb3_peripheral_clock.rd<ahb3_peripheral_clock_t::qspi_t>() ; }

  inline void state_enable(const ahb3_peripheral_clock_t::peripheral_t val) { ahb3_peripheral_clock.rmw( ahb3_peripheral_clock_t::enable, val ) ; ahb_clock_enable_delay();}
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
    struct lptim1_t{ enum enum_t { offset=9, mask=0b1, disable=0, enable } ; } ;
    struct wwdg_t  { enum enum_t { offset=11,mask=0b1, disable=0, enable } ; } ;
    struct can3_t  { enum enum_t { offset=13,mask=0b1, disable=0, enable } ; } ;
    struct spi2_t  { enum enum_t { offset=14,mask=0b1, disable=0, enable } ; } ;
    struct spi3_t  { enum enum_t { offset=15,mask=0b1, disable=0, enable } ; } ;
    struct spdif_t { enum enum_t { offset=16,mask=0b1, disable=0, enable } ; } ;
    struct uart2_t { enum enum_t { offset=17,mask=0b1, disable=0, enable } ; } ;
    struct uart3_t { enum enum_t { offset=18,mask=0b1, disable=0, enable } ; } ;
    struct uart4_t { enum enum_t { offset=19,mask=0b1, disable=0, enable } ; } ;
    struct uart5_t { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;
    struct i2c1_t  { enum enum_t { offset=21,mask=0b1, disable=0, enable } ; } ;
    struct i2c2_t  { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;
    struct i2c3_t  { enum enum_t { offset=23,mask=0b1, disable=0, enable } ; } ;
    struct i2c4_t  { enum enum_t { offset=24,mask=0b1, disable=0, enable } ; } ;
    struct can1_t  { enum enum_t { offset=25,mask=0b1, disable=0, enable } ; } ;
    struct can2_t  { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;
    struct cec_t   { enum enum_t { offset=27,mask=0b1, disable=0, enable } ; } ;
    struct pwr_t   { enum enum_t { offset=28,mask=0b1, disable=0, enable } ; } ;
    struct dac_t   { enum enum_t { offset=29,mask=0b1, disable=0, enable } ; } ;
    struct uart7_t { enum enum_t { offset=19,mask=0b1, disable=0, enable } ; } ;
    struct uart8_t { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t { tim2=tim2_t::offset,
                        tim3=tim3_t::offset,
			tim4=tim4_t::offset,
			tim5=tim5_t::offset,
			tim6=tim6_t::offset,
			tim7=tim7_t::offset,
			tim12=tim12_t::offset,
			tim13=tim13_t::offset,
			tim14=tim14_t::offset,
			lptim1=lptim1_t::offset,
			wwdg=wwdg_t::offset,
			can3=can3_t::offset,
			spi2=spi2_t::offset,
			spi3=spi3_t::offset,
			spdif=spdif_t::offset,
			uart2=uart2_t::offset,
			uart3=uart3_t::offset,
			uart4=uart4_t::offset,
			uart5=uart5_t::offset,
			i2c1=i2c1_t::offset,
			i2c2=i2c2_t::offset,
			i2c3=i2c3_t::offset,
			i2c4=i2c4_t::offset,
			can1=can1_t::offset,
			can2=can2_t::offset,
			cec=cec_t::offset,
			pwr=pwr_t::offset,
			dac=dac_t::offset,
			uart7=uart7_t::offset,
			uart8=uart8_t::offset
                      } ;
  } ;

  inline void tim2_state( const apb1_peripheral_clock_t::tim2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::disable) ; }
  inline void tim2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim2_t::enum_t tim2_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim2_t>() ; }

  inline void tim3_state( const apb1_peripheral_clock_t::tim3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::disable) ; }
  inline void tim3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim3_t::enum_t tim3_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim3_t>() ; }

  inline void tim4_state( const apb1_peripheral_clock_t::tim4_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim4_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim4_t::disable) ; }
  inline void tim4_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim4_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim4_t::enum_t tim4_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim4_t>() ; }

  inline void tim5_state( const apb1_peripheral_clock_t::tim5_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim5_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim5_t::disable) ; }
  inline void tim5_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim5_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim5_t::enum_t tim5_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim5_t>() ; }

  inline void tim6_state( const apb1_peripheral_clock_t::tim6_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim6_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::disable) ; }
  inline void tim6_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim6_t::enum_t tim6_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim6_t>() ; }

  inline void tim7_state( const apb1_peripheral_clock_t::tim7_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim7_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::disable) ; }
  inline void tim7_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim7_t::enum_t tim7_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim7_t>() ; }

  inline void tim12_state( const apb1_peripheral_clock_t::tim12_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim12_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim12_t::disable) ; }
  inline void tim12_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim12_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim12_t::enum_t tim12_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim12_t>() ; }

  inline void tim13_state( const apb1_peripheral_clock_t::tim13_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim13_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim13_t::disable) ; }
  inline void tim13_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim13_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim13_t::enum_t tim13_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim13_t>() ; }

  inline void tim14_state( const apb1_peripheral_clock_t::tim14_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void tim14_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim14_t::disable) ; }
  inline void tim14_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim14_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::tim14_t::enum_t tim14_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim14_t>() ; }

  inline void lptim1_state( const apb1_peripheral_clock_t::lptim1_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void lptim1_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lptim1_t::disable) ; }
  inline void lptim1_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lptim1_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::lptim1_t::enum_t lptim1_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::lptim1_t>() ; }

  inline void wwdg_state( const apb1_peripheral_clock_t::wwdg_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void wwdg_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::disable) ; }
  inline void wwdg_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::wwdg_t::enum_t wwdg_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::wwdg_t>() ; }

  inline void can3_state( const apb1_peripheral_clock_t::can3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void can3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can3_t::disable) ; }
  inline void can3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can3_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::can3_t::enum_t can3_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::can3_t>() ; }

  inline void spi2_state( const apb1_peripheral_clock_t::spi2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void spi2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::disable) ; }
  inline void spi2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::spi2_t::enum_t spi2_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spi2_t>() ; }

  inline void spi3_state( const apb1_peripheral_clock_t::spi3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void spi3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi3_t::disable) ; }
  inline void spi3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi3_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::spi3_t::enum_t spi3_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spi3_t>() ; }

  inline void spdif_state( const apb1_peripheral_clock_t::spdif_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void spdif_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spdif_t::disable) ; }
  inline void spdif_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spdif_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::spdif_t::enum_t spdif_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spdif_t>() ; }

  inline void uart2_state( const apb1_peripheral_clock_t::uart2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart2_t::disable) ; }
  inline void uart2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart2_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart2_t::enum_t uart2_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart2_t>() ; }

  inline void uart3_state( const apb1_peripheral_clock_t::uart3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart3_t::disable) ; }
  inline void uart3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart3_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart3_t::enum_t uart3_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart3_t>() ; }

  inline void uart4_state( const apb1_peripheral_clock_t::uart4_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart4_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::disable) ; }
  inline void uart4_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart4_t::enum_t uart4_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart4_t>() ; }

  inline void uart5_state( const apb1_peripheral_clock_t::uart5_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart5_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart5_t::disable) ; }
  inline void uart5_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart5_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart5_t::enum_t uart5_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart5_t>() ; }

  inline void i2c1_state( const apb1_peripheral_clock_t::i2c1_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void i2c1_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::disable) ; }
  inline void i2c1_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::i2c1_t::enum_t i2c1_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c1_t>() ; }

  inline void i2c2_state( const apb1_peripheral_clock_t::i2c2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void i2c2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::disable) ; }
  inline void i2c2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::i2c2_t::enum_t i2c2_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c2_t>() ; }

  inline void i2c3_state( const apb1_peripheral_clock_t::i2c3_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void i2c3_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::disable) ; }
  inline void i2c3_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::i2c3_t::enum_t i2c3_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c3_t>() ; }

  inline void i2c4_state( const apb1_peripheral_clock_t::i2c4_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void i2c4_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c4_t::disable) ; }
  inline void i2c4_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c4_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::i2c4_t::enum_t i2c4_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c4_t>() ; }

  inline void can1_state( const apb1_peripheral_clock_t::can1_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void can1_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can1_t::disable) ; }
  inline void can1_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can1_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::can1_t::enum_t can1_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::can1_t>() ; }

  inline void can2_state( const apb1_peripheral_clock_t::can2_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void can2_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can2_t::disable) ; }
  inline void can2_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::can2_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::can2_t::enum_t can2_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::can2_t>() ; }

  inline void cec_state( const apb1_peripheral_clock_t::cec_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void cec_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::cec_t::disable) ; }
  inline void cec_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::cec_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::cec_t::enum_t cec_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::cec_t>() ; }

  inline void pwr_state( const apb1_peripheral_clock_t::pwr_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void pwr_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::disable) ; }
  inline void pwr_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::pwr_t::enum_t pwr_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::pwr_t>() ; }

  inline void dac_state( const apb1_peripheral_clock_t::dac_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void dac_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::dac_t::disable) ; }
  inline void dac_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::dac_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::dac_t::enum_t dac_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::dac_t>() ; }

  inline void uart7_state( const apb1_peripheral_clock_t::uart7_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart7_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart7_t::disable) ; }
  inline void uart7_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart7_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart7_t::enum_t uart7_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart7_t>() ; }

  inline void uart8_state( const apb1_peripheral_clock_t::uart8_t::enum_t val){ apb1_peripheral_clock.rmw(val) ; apb1_clock_enable_delay();}
  inline void uart8_disable(){ apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart8_t::disable) ; }
  inline void uart8_enable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart8_t::enable) ; apb1_clock_enable_delay();}
  inline apb1_peripheral_clock_t::uart8_t::enum_t uart8_state() const { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart8_t>() ; }

  inline void state_enable(const apb1_peripheral_clock_t::peripheral_t val) { apb1_peripheral_clock.rmw( apb1_peripheral_clock_t::enable, val ) ; apb1_clock_enable_delay();}
  inline void state_disable(const apb1_peripheral_clock_t::peripheral_t val){ apb1_peripheral_clock.rmw( apb1_peripheral_clock_t::disable, val ) ; }

  struct apb2_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, disable=0, enable } ;
    struct tim1_t    { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct tim8_t    { enum enum_t { offset=1, mask=0b1, disable=0, enable } ; } ;
    struct usart1_t  { enum enum_t { offset=4, mask=0b1, disable=0, enable } ; } ;
    struct usart6_t  { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
    struct sdmmc2_t  { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_1_t    { enum enum_t { offset=8, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_2_t    { enum enum_t { offset=9, mask=0b1, disable=0, enable } ; } ;
    struct adc_converter_3_t    { enum enum_t { offset=10,mask=0b1, disable=0, enable } ; } ;
    struct sdmmc1_t  { enum enum_t { offset=11,mask=0b1, disable=0, enable } ; } ;
    struct spi1_t    { enum enum_t { offset=12,mask=0b1, disable=0, enable } ; } ;
    struct spi4_t    { enum enum_t { offset=13,mask=0b1, disable=0, enable } ; } ;
    struct syscfg_t  { enum enum_t { offset=14,mask=0b1, disable=0, enable } ; } ;
    struct tim9_t    { enum enum_t { offset=16,mask=0b1, disable=0, enable } ; } ;
    struct tim10_t   { enum enum_t { offset=17,mask=0b1, disable=0, enable } ; } ;
    struct tim11_t   { enum enum_t { offset=18,mask=0b1, disable=0, enable } ; } ;
    struct spi5_t    { enum enum_t { offset=20,mask=0b1, disable=0, enable } ; } ;
    struct spi6_t    { enum enum_t { offset=21,mask=0b1, disable=0, enable } ; } ;
    struct sai1_t    { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;
    struct sai2_t    { enum enum_t { offset=23,mask=0b1, disable=0, enable } ; } ;
    struct ltdc_t    { enum enum_t { offset=26,mask=0b1, disable=0, enable } ; } ;
    struct dsi_t     { enum enum_t { offset=27,mask=0b1, disable=0, enable } ; } ;
    struct dfsdm1_t  { enum enum_t { offset=29,mask=0b1, disable=0, enable } ; } ;
    struct mdio_t    { enum enum_t { offset=30,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t {
    	                tim1=tim1_t::offset,
                        tim8=tim8_t::offset,
			usart1=usart1_t::offset,
			usart6=usart6_t::offset,
			sdmmc2=sdmmc2_t::offset,
			adc_converter_1=adc_converter_1_t::offset,
			adc_converter_2=adc_converter_2_t::offset,
			adc_converter_3=adc_converter_3_t::offset,
			sdmmc1=sdmmc1_t::offset,
			spi1=spi1_t::offset,
			spi4=spi4_t::offset,
			syscfg=syscfg_t::offset,
			tim9=tim9_t::offset,
			tim10=tim10_t::offset,
			tim11=tim11_t::offset,
			spi5=spi5_t::offset,
			spi6=spi6_t::offset,
			sai1=sai1_t::offset,
			sai2=sai2_t::offset,
			ltdc=ltdc_t::offset,
			dsi=dsi_t::offset,
			dfsdm1=dfsdm1_t::offset,
			mdio=mdio_t::offset,
                      };
  } ;

  inline void tim1_state( const apb2_peripheral_clock_t::tim1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void tim1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim1_t::disable) ; }
  inline void tim1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::tim1_t::enum_t tim1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim1_t>() ; }

  inline void tim8_state( const apb2_peripheral_clock_t::tim8_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void tim8_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim8_t::disable) ; }
  inline void tim8_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim8_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::tim8_t::enum_t tim8_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim8_t>() ; }

  inline void usart1_state( const apb2_peripheral_clock_t::usart1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void usart1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::disable) ; }
  inline void usart1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::usart1_t::enum_t usart1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::usart1_t>() ; }

  inline void usart6_state( const apb2_peripheral_clock_t::usart6_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void usart6_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart6_t::disable) ; }
  inline void usart6_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart6_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::usart6_t::enum_t usart6_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::usart6_t>() ; }

  inline void sdmmc2_state( const apb2_peripheral_clock_t::sdmmc2_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void sdmmc2_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdmmc2_t::disable) ; }
  inline void sdmmc2_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdmmc2_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::sdmmc2_t::enum_t sdmmc2_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sdmmc2_t>() ; }

  inline void adc_converter_1_state( const apb2_peripheral_clock_t::adc_converter_1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void adc_converter_1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_1_t::disable) ; }
  inline void adc_converter_1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_1_t::enable) ; apb2_clock_enable_delay();}
  inline auto adc_converter_1_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_1_t>() ; }

  inline void adc_converter_2_state( const apb2_peripheral_clock_t::adc_converter_2_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void adc_converter_2_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_2_t::disable) ; }
  inline void adc_converter_2_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_2_t::enable) ; apb2_clock_enable_delay();}
  inline auto adc_converter_2_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_2_t>() ; }

  inline void adc_converter_3_state( const apb2_peripheral_clock_t::adc_converter_3_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void adc_converter_3_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_3_t::disable) ; }
  inline void adc_converter_3_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_converter_3_t::enable) ; apb2_clock_enable_delay();}
  inline auto adc_converter_3_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_converter_3_t>() ; }

  inline void sdmmc1_state( const apb2_peripheral_clock_t::sdmmc1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void sdmmc1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdmmc1_t::disable) ; }
  inline void sdmmc1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sdmmc1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::sdmmc1_t::enum_t sdmmc1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sdmmc1_t>() ; }

  inline void spi1_state( const apb2_peripheral_clock_t::spi1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void spi1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::disable) ; }
  inline void spi1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::spi1_t::enum_t spi1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi1_t>() ; }

  inline void spi4_state( const apb2_peripheral_clock_t::spi4_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void spi4_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi4_t::disable) ; }
  inline void spi4_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi4_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::spi4_t::enum_t spi4_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi4_t>() ; }

  inline void syscfg_state( const apb2_peripheral_clock_t::syscfg_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void syscfg_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::disable) ; }
  inline void syscfg_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::syscfg_t::enum_t syscfg_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::syscfg_t>() ; }

  inline void tim9_state( const apb2_peripheral_clock_t::tim9_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void tim9_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim9_t::disable) ; }
  inline void tim9_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim9_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::tim9_t::enum_t tim9_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim9_t>() ; }

  inline void tim10_state( const apb2_peripheral_clock_t::tim10_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void tim10_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim10_t::disable) ; }
  inline void tim10_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim10_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::tim10_t::enum_t tim10_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim10_t>() ; }

  inline void tim11_state( const apb2_peripheral_clock_t::tim11_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void tim11_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim11_t::disable) ; }
  inline void tim11_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim11_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::tim11_t::enum_t tim11_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim11_t>() ; }

  inline void spi5_state( const apb2_peripheral_clock_t::spi5_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void spi5_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi5_t::disable) ; }
  inline void spi5_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi5_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::spi5_t::enum_t spi5_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi5_t>() ; }

  inline void spi6_state( const apb2_peripheral_clock_t::spi6_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void spi6_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi6_t::disable) ; }
  inline void spi6_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi6_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::spi6_t::enum_t spi6_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi6_t>() ; }

  inline void sai1_state( const apb2_peripheral_clock_t::sai1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void sai1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai1_t::disable) ; }
  inline void sai1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::sai1_t::enum_t sai1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sai1_t>() ; }

  inline void sai2_state( const apb2_peripheral_clock_t::sai2_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void sai2_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai2_t::disable) ; }
  inline void sai2_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::sai2_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::sai2_t::enum_t sai2_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::sai2_t>() ; }

  inline void ltdc_state( const apb2_peripheral_clock_t::ltdc_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void ltdc_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::ltdc_t::disable) ; }
  inline void ltdc_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::ltdc_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::ltdc_t::enum_t ltdc_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::ltdc_t>() ; }

  inline void dsi_state( const apb2_peripheral_clock_t::dsi_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void dsi_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dsi_t::disable) ; }
  inline void dsi_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dsi_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::dsi_t::enum_t dsi_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::dsi_t>() ; }

  inline void dfsdm1_state( const apb2_peripheral_clock_t::dfsdm1_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void dfsdm1_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dfsdm1_t::disable) ; }
  inline void dfsdm1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dfsdm1_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::dfsdm1_t::enum_t dfsdm1_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::dfsdm1_t>() ; }

  inline void mdio_state( const apb2_peripheral_clock_t::mdio_t::enum_t val){ apb2_peripheral_clock.rmw(val) ; apb2_clock_enable_delay();}
  inline void mdio_disable(){ apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::mdio_t::disable) ; }
  inline void mdio_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::mdio_t::enable) ; apb2_clock_enable_delay();}
  inline apb2_peripheral_clock_t::mdio_t::enum_t mdio_state() const { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::mdio_t>() ; }

  inline void state_enable(const apb2_peripheral_clock_t::peripheral_t val) { apb2_peripheral_clock.rmw( apb2_peripheral_clock_t::enable, val ) ; apb2_clock_enable_delay();}
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
  inline clock_control_status_t::lsi_t::enum_t lsi_state() const { return clock_control_status.rd<clock_control_status_t::lsi_t>() ; }

  inline  clock_control_status_t::lsi_ready_t::enum_t lsi_ready() const {  return clock_control_status.rd<clock_control_status_t::lsi_ready_t> ();}
  inline void lsi_ready_wait() const { while ( lsi_ready() == clock_control_status_t::lsi_ready_t::not_ready)  {} ; }

  inline void remove_reset_clear(){clock_control_status.rmw(clock_control_status_t::remove_reset_clear_t::perform) ;}

  inline void bor_reset_clear(){ clock_control_status.rmw(clock_control_status_t::bor_reset_t::occured) ; }
  inline clock_control_status_t::bor_reset_t::enum_t bor_reset() const { return clock_control_status.rd<clock_control_status_t::bor_reset_t>() ; }

  inline void nrst_reset_clear(){ clock_control_status.rmw(clock_control_status_t::nrst_reset_t::occured) ; }
  inline clock_control_status_t::nrst_reset_t::enum_t nrst_reset() const { return clock_control_status.rd<clock_control_status_t::nrst_reset_t>() ; }

  inline void por_pdr_reset_clear(){ clock_control_status.rmw(clock_control_status_t::por_pdr_reset_t::occured) ; }
  inline clock_control_status_t::por_pdr_reset_t::enum_t por_pdr_reset() const { return clock_control_status.rd<clock_control_status_t::por_pdr_reset_t>() ; }

  inline void software_reset_clear(){ clock_control_status.rmw(clock_control_status_t::software_reset_t::occured) ; }
  inline clock_control_status_t::software_reset_t::enum_t software_reset() const { return clock_control_status.rd<clock_control_status_t::software_reset_t>() ; }

  inline void iwdg_reset_clear(){ clock_control_status.rmw(clock_control_status_t::iwdg_reset_t::occured) ; }
  inline clock_control_status_t::iwdg_reset_t::enum_t iwdg_reset() const { return clock_control_status.rd<clock_control_status_t::iwdg_reset_t>() ; }

  inline void wwdg_reset_clear(){ clock_control_status.rmw(clock_control_status_t::wwdg_reset_t::occured) ; }
  inline clock_control_status_t::wwdg_reset_t::enum_t wwdg_reset() const { return clock_control_status.rd<clock_control_status_t::wwdg_reset_t>() ; }

  inline void lpmr_reset_clear(){ clock_control_status.rmw(clock_control_status_t::lpmr_reset_t::occured) ; }
  inline clock_control_status_t::lpmr_reset_t::enum_t lpmr_reset() const { return clock_control_status.rd<clock_control_status_t::lpmr_reset_t>() ; }

  struct spread_spectrum_clock_generation_t : public read_write_32_t
  {
    // TODO
  } ;

  struct pll_i2s_config_t : public read_write_32_t
  {
    struct n_t    { enum enum_t { offset=6, mask=0b111111111 } ; } ;
    struct p_t    { enum enum_t { offset=16, mask=0b11 } ; } ;
    struct q_t    { enum enum_t { offset=24, mask=0b1111 } ; } ;
    struct r_t    { enum enum_t { offset=28, mask=0b111 } ; } ;
  }  ;

  inline  void pll_i2s_n( const uint16_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_i2s_n() const {  return (pll_i2s_config_t::n_t::enum_t) pll_config.rd<pll_i2s_config_t::n_t> ();}

  inline  void pll_i2s_p( const uint8_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::p_t::enum_t)val) ;}
  inline  uint8_t pll_i2s_p() const {  return (pll_i2s_config_t::p_t::enum_t) pll_config.rd<pll_i2s_config_t::p_t> ();}

  inline  void pll_i2s_q( const uint8_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_i2s_q() const {  return (pll_i2s_config_t::q_t::enum_t) pll_config.rd<pll_i2s_config_t::q_t> ();}

  inline  void pll_i2s_r( const uint8_t val){  pll_i2s_config.rmw( (pll_i2s_config_t::r_t::enum_t)val) ;}
  inline  uint8_t pll_i2s_r() const {  return (pll_i2s_config_t::r_t::enum_t) pll_config.rd<pll_i2s_config_t::r_t> ();}


  struct pll_sai_config_t : public read_write_32_t
  {
	    struct n_t    { enum enum_t { offset=6, mask=0b111111111 } ; } ;
	    struct p_t    { enum enum_t { offset=16, mask=0b11 } ; } ;
	    struct q_t    { enum enum_t { offset=24, mask=0b1111 } ; } ;
	    struct r_t    { enum enum_t { offset=28, mask=0b111 } ; } ;
  };

  inline  void pll_sai_n( const uint16_t val){  pll_sai_config.rmw( (pll_sai_config_t::n_t::enum_t)val) ;}
  inline  uint16_t pll_sai_n() const {  return (pll_sai_config_t::n_t::enum_t) pll_config.rd<pll_sai_config_t::n_t> ();}

  inline  void pll_sai_p( const uint8_t val){  pll_sai_config.rmw( (pll_sai_config_t::p_t::enum_t)val) ;}
  inline  uint8_t pll_sai_p() const {  return (pll_sai_config_t::p_t::enum_t) pll_config.rd<pll_sai_config_t::p_t> ();}

  inline  void pll_sai_q( const uint8_t val){  pll_sai_config.rmw( (pll_sai_config_t::q_t::enum_t)val) ;}
  inline  uint8_t pll_sai_q() const {  return (pll_sai_config_t::q_t::enum_t) pll_config.rd<pll_sai_config_t::q_t> ();}

  inline  void pll_sai_r( const uint8_t val){  pll_sai_config.rmw( (pll_sai_config_t::r_t::enum_t)val) ;}
  inline  uint8_t pll_sai_r() const {  return (pll_sai_config_t::r_t::enum_t) pll_config.rd<pll_sai_config_t::r_t> ();}

  struct dedicated_clocks_config_1_t : public read_write_32_t
  {
    struct pll_i2s_q_div_t           { enum enum_t { offset=0, mask=0b11111, div1=0, div2, div3, div4, div5, div6, div7, div8, div9, div10, div11, div12, div13, div14, div15, div16,
                                                                            div17, div18, div19, div20, div21, div22, div23, div24, div25, div26, div27, div28, div29, div30, div31, div32 } ; } ;
    struct pll_sai_q_div_t           { enum enum_t { offset=8, mask=0b11111, div1=0, div2, div3, div4, div5, div6, div7, div8, div9, div10, div11, div12, div13, div14, div15, div16,
                                                                            div17, div18, div19, div20, div21, div22, div23, div24, div25, div26, div27, div28, div29, div30, div31, div32 } ; } ;
    struct pll_sai_r_div_t           { enum enum_t { offset=16, mask=0b11, div2=0, div4, div8, div16 } ; } ;
    struct sai1_clock_selection_t    { enum enum_t { offset=20, mask=0b11, pllsai=0, plli2s, alternate_input_freq, hsi_hse} ; } ;
    struct sai2_clock_selection_t    { enum enum_t { offset=22, mask=0b11, pllsai=0, plli2s, alternate_input_freq, hsi_hse} ; } ;
    struct timers_clock_prescaler_t  { enum enum_t { offset=24, mask=0b1, pclk_double=0, pclk_quadruple  } ; } ;
    struct dfsdm1_clock_source_selection_t  { enum enum_t { offset=25, mask=0b1, apb2=0, sys  } ; } ;
    struct dfsdm1_audio_clock_source_selection_t  { enum enum_t { offset=26, mask=0b1, sai1=0, sai2  } ; } ;
  };

  inline  void pll_i2s_q_div( const dedicated_clocks_config_1_t::pll_i2s_q_div_t::enum_t val){  dedicated_clocks_config_1.rmw(val) ;}
  inline  void pll_i2s_q_div1(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div1) ;}
  inline  void pll_i2s_q_div2(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div2) ;}
  inline  void pll_i2s_q_div3(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div3) ;}
  inline  void pll_i2s_q_div4(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div4) ;}
  inline  void pll_i2s_q_div5(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div5) ;}
  inline  void pll_i2s_q_div6(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div6) ;}
  inline  void pll_i2s_q_div7(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div7) ;}
  inline  void pll_i2s_q_div8(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div8) ;}
  inline  void pll_i2s_q_div9(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div9) ;}
  inline  void pll_i2s_q_div10(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div10) ;}
  inline  void pll_i2s_q_div11(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div11) ;}
  inline  void pll_i2s_q_div12(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div12) ;}
  inline  void pll_i2s_q_div13(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div13) ;}
  inline  void pll_i2s_q_div14(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div14) ;}
  inline  void pll_i2s_q_div15(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div15) ;}
  inline  void pll_i2s_q_div16(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div16) ;}
  inline  void pll_i2s_q_div17(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div17) ;}
  inline  void pll_i2s_q_div18(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div18) ;}
  inline  void pll_i2s_q_div19(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div19) ;}
  inline  void pll_i2s_q_div20(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div20) ;}
  inline  void pll_i2s_q_div21(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div21) ;}
  inline  void pll_i2s_q_div22(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div22) ;}
  inline  void pll_i2s_q_div23(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div23) ;}
  inline  void pll_i2s_q_div24(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div24) ;}
  inline  void pll_i2s_q_div25(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div25) ;}
  inline  void pll_i2s_q_div26(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div26) ;}
  inline  void pll_i2s_q_div27(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div27) ;}
  inline  void pll_i2s_q_div28(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div28) ;}
  inline  void pll_i2s_q_div29(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div29) ;}
  inline  void pll_i2s_q_div30(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div30) ;}
  inline  void pll_i2s_q_div31(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div31) ;}
  inline  void pll_i2s_q_div32(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_i2s_q_div_t::div32) ;}
  inline  auto pll_i2s_q_div() const {  return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::pll_i2s_q_div_t> ();}

  inline  void pll_sai_q_div( const dedicated_clocks_config_1_t::pll_sai_q_div_t::enum_t val){  dedicated_clocks_config_1.rmw(val) ;}
  inline  void pll_sai_q_div1(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div1) ;}
  inline  void pll_sai_q_div2(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div2) ;}
  inline  void pll_sai_q_div3(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div3) ;}
  inline  void pll_sai_q_div4(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div4) ;}
  inline  void pll_sai_q_div5(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div5) ;}
  inline  void pll_sai_q_div6(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div6) ;}
  inline  void pll_sai_q_div7(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div7) ;}
  inline  void pll_sai_q_div8(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div8) ;}
  inline  void pll_sai_q_div9(){   dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div9) ;}
  inline  void pll_sai_q_div10(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div10) ;}
  inline  void pll_sai_q_div11(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div11) ;}
  inline  void pll_sai_q_div12(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div12) ;}
  inline  void pll_sai_q_div13(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div13) ;}
  inline  void pll_sai_q_div14(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div14) ;}
  inline  void pll_sai_q_div15(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div15) ;}
  inline  void pll_sai_q_div16(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div16) ;}
  inline  void pll_sai_q_div17(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div17) ;}
  inline  void pll_sai_q_div18(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div18) ;}
  inline  void pll_sai_q_div19(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div19) ;}
  inline  void pll_sai_q_div20(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div20) ;}
  inline  void pll_sai_q_div21(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div21) ;}
  inline  void pll_sai_q_div22(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div22) ;}
  inline  void pll_sai_q_div23(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div23) ;}
  inline  void pll_sai_q_div24(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div24) ;}
  inline  void pll_sai_q_div25(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div25) ;}
  inline  void pll_sai_q_div26(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div26) ;}
  inline  void pll_sai_q_div27(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div27) ;}
  inline  void pll_sai_q_div28(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div28) ;}
  inline  void pll_sai_q_div29(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div29) ;}
  inline  void pll_sai_q_div30(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div30) ;}
  inline  void pll_sai_q_div31(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div31) ;}
  inline  void pll_sai_q_div32(){  dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_q_div_t::div32) ;}
  inline  auto pll_sai_q_div() const {  return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::pll_sai_q_div_t> ();}

  inline  void pll_sai_r_div( const dedicated_clocks_config_1_t::pll_sai_r_div_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ;}
  inline  void pll_sai_r_div2(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_r_div_t::div2) ;}
  inline  void pll_sai_r_div4(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_r_div_t::div4) ;}
  inline  void pll_sai_r_div8(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_r_div_t::div8) ;}
  inline  void pll_sai_r_div16(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::pll_sai_r_div_t::div16) ;}
  inline  auto pll_sai_r_div() const {  return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::pll_sai_r_div_t> ();}

  inline void sai1_clock_selection( const dedicated_clocks_config_1_t::sai1_clock_selection_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ; }
  inline void sai1_clock_selection_pllsai(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai1_clock_selection_t::pllsai) ; }
  inline void sai1_clock_selection_plli2s() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai1_clock_selection_t::plli2s) ; }
  inline void sai1_clock_selection_alternate_input_freq(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai1_clock_selection_t::alternate_input_freq) ; }
  inline void sai1_clock_selection_hsi_hse() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai1_clock_selection_t::hsi_hse) ; }
  inline auto sai1_clock_selection() const { return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::sai1_clock_selection_t>() ; }

  inline void sai2_clock_selection( const dedicated_clocks_config_1_t::sai2_clock_selection_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ; }
  inline void sai2_clock_selection_pllsai(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai2_clock_selection_t::pllsai) ; }
  inline void sai2_clock_selection_plli2s() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai2_clock_selection_t::plli2s) ; }
  inline void sai2_clock_selection_alternate_input_freq(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai2_clock_selection_t::alternate_input_freq) ; }
  inline void sai2_clock_selection_hsi_hse() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::sai2_clock_selection_t::hsi_hse) ; }
  inline auto sai2_clock_selection() const { return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::sai2_clock_selection_t>() ; }

  inline void timers_clock( const dedicated_clocks_config_1_t::timers_clock_prescaler_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ; }
  inline void timers_clock_pclk_double(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::timers_clock_prescaler_t::pclk_double) ; }
  inline void timers_clock_pclk_quadruple() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::timers_clock_prescaler_t::pclk_quadruple) ; }
  inline auto timers_clock_prescaler() const { return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::timers_clock_prescaler_t>() ; }

  inline void dfsdm1_clock_source_selection( const dedicated_clocks_config_1_t::dfsdm1_clock_source_selection_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ; }
  inline void dfsdm1_clock_source_selection_apb2(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::dfsdm1_clock_source_selection_t::apb2) ; }
  inline void dfsdm1_clock_source_selection_sys() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::dfsdm1_clock_source_selection_t::sys) ; }
  inline auto dfsdm1_clock_source_selection() const { return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::dfsdm1_clock_source_selection_t>() ; }

  inline void dfsdm1_audio_clock_source_selection( const dedicated_clocks_config_1_t::dfsdm1_audio_clock_source_selection_t::enum_t val){ dedicated_clocks_config_1.rmw(val) ; }
  inline void dfsdm1_audio_clock_source_selection_sai1(){ dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::dfsdm1_audio_clock_source_selection_t::sai1) ; }
  inline void dfsdm1_audio_clock_source_selection_sai2() { dedicated_clocks_config_1.rmw(dedicated_clocks_config_1_t::dfsdm1_audio_clock_source_selection_t::sai2) ; }
  inline auto dfsdm1_audio_clock_source_selection() const { return dedicated_clocks_config_1.rd<dedicated_clocks_config_1_t::dfsdm1_audio_clock_source_selection_t>() ; }


  struct dedicated_clocks_config_2_t : public read_write_32_t
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
  dedicated_clocks_config_2_t          dedicated_clocks_config_2; // DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,               Address offset: 0x90 */



  struct system_init_profile_t // pwr, clocs, etc
     {
        enum sys_clock_source_t { hsi, hse, hse_bypass, hsi_pll, hse_pll, hse_bypass_pll};
        pwr_t::power_control_1_t::regulator_voltage_scale_t::enum_t regulator_voltage_scale ;
        bool overdrive ;

        uint32_t f_osc;
        sys_clock_source_t sys_clock_source ;
        // тактовая частотота pll_clk  = (hse_hsi / m) * n / p
        uint8_t pll_m;
        uint16_t pll_n;
        rcc_t::pll_config_t::p_t::enum_t pll_p;
        // тактовая частотота usb_48_clk  = (hse_hsi / m) * n / q
        uint8_t pll_q;

        clock_config_t::ahb_prescaler_t::enum_t hpre;
        clock_config_t::apb1_prescaler_t::enum_t ppre1;
        clock_config_t::apb2_prescaler_t::enum_t ppre2;

        flash_t::access_control_t::prefetch_t::enum_t prefetch ;
        flash_t::access_control_t::latency_t::enum_t latency ;
        flash_t::access_control_t::art_accelerator_t::enum_t art_accelerator ;

        bool l1_instruction_cache_active ;
        bool l1_data_cache_active ;
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


  inline uint32_t sys_clock_freq() const
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



   inline uint32_t ahb_clock_freq()
      {
        return ahb_prescaler() == clock_config_t::ahb_prescaler_t::no_div ?
                            sys_clock_freq() :
                            ahb_prescaler() > clock_config_t::ahb_prescaler_t::div16 ?
                                      sys_clock_freq() >> ((ahb_prescaler() & 0b111) + 1) :
        	                      sys_clock_freq() >> ((ahb_prescaler() & 0b111) + 2) ;
      }

   inline uint32_t apb1_clock_freq()
      {
        return apb1_prescaler() == clock_config_t::apb1_prescaler_t::no_div ?
                            sys_clock_freq() :
			    sys_clock_freq() >> ((apb1_prescaler() & 0b11) + 1);
      }
   inline uint32_t apb2_clock_freq()
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

}  // stm32f7

using namespace stm32f7 ;

#endif /* __RCC++_H__ */
