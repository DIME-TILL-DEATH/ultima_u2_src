/*
 * rcc++.h
 *
 *  Created on: 20 март. 2019 г.
 *      Author: klen
 */

#ifndef __RCC++_H__
#define __RCC++_H__

#include "types++.h"
//#include "flash++.h"
//#include "pwr++.h"

namespace stm32h7
{


struct rcc_t
{

  // необходимая задержка перед использованием переферии после включения тактирования
	// Cortex-M7 (reference manual):
	// AHB: 2 AHB cycles
	// APB: 2 * (AHB/APB prescaler) AHB cycles
  // Cortex-M7 is dual issue, so we need 2 nop's per cycle
  inline void ahb_clock_enable_delay() { nop_rep(2); };
//  inline void apb1_clock_enable_delay(){ uint32_t delay_cycles = 2 * ahb_prescaler() / apb1_prescaler() ; while(delay_cycles--) nop_rep(2);  }
//  inline void apb2_clock_enable_delay(){ uint32_t delay_cycles = 2 * ahb_prescaler() / apb2_prescaler() ; while(delay_cycles--) nop_rep(2);  }


 struct clock_control_t : public read_write_32_t
  {
    struct hsi_t                     { enum enum_t { offset=0,  mask=1, off=0 , on } ; } ;
    struct hsi_operate_in_stop_mode_t{ enum enum_t { offset=1,  mask=1, disable=0 , enable } ; } ;
    struct hsi_ready_t               { enum enum_t { offset=2,  mask=1, not_ready=0 , ready } ; } ;
    struct hsi_div_t                 { enum enum_t { offset=3,  mask=0b11, div1=0, div2, div3, div4 } ; } ;
    struct hsi_div_perform_t         { enum enum_t { offset=5,  mask=1, not_perform=0 , perform } ; } ;
    struct csi_t                     { enum enum_t { offset=7,  mask=1, off=0 , on } ; } ;
    struct csi_ready_t               { enum enum_t { offset=8,  mask=1, not_ready=0 , ready } ; } ;
    struct csi_operate_in_stop_mode_t{ enum enum_t { offset=9,  mask=1, disable=0 , enable } ; } ;
    struct hsi48_t                   { enum enum_t { offset=12,  mask=1, off=0 , on } ; } ;
    struct hsi48_ready_t             { enum enum_t { offset=13,  mask=1, not_ready=0 , ready } ; } ;

    struct d1_clock_ready_t          { enum enum_t { offset=14,  mask=1, not_ready=0 , ready } ; } ;
    struct d2_clock_ready_t          { enum enum_t { offset=15,  mask=1, not_ready=0 , ready } ; } ;

    struct hse_t                     { enum enum_t { offset=16, mask=1, off=0 , on } ; } ;
    struct hse_ready_t               { enum enum_t { offset=17, mask=1, not_ready=0 , ready } ; } ;
    struct hse_clock_bypass_t        { enum enum_t { offset=18, mask=1, off=0 , on } ; } ;
    struct hse_clock_security_system_t   { enum enum_t { offset=19, mask=1, disable=0 , enable} ; } ;
    struct pll1_t                     { enum enum_t { offset=24, mask=1, off=0 , on } ; } ;
    struct pll1_ready_t               { enum enum_t { offset=25, mask=1, not_ready=0 , ready } ; } ;
    struct pll2_t                     { enum enum_t { offset=26, mask=1, off=0 , on } ; } ;
    struct pll2_ready_t               { enum enum_t { offset=27, mask=1, not_ready=0 , ready } ; } ;
    struct pll3_t                     { enum enum_t { offset=28, mask=1, off=0 , on } ; } ;
    struct pll3_ready_t               { enum enum_t { offset=29, mask=1, not_ready=0 , ready } ; } ;
  };

  inline void hsi(const clock_control_t::hsi_t::enum_t val){  clock_control.rmw(val) ;}
  inline void hsi_off(){  clock_control.rmw( clock_control_t::hsi_t::off) ;}
  inline void hsi_on() {  clock_control.rmw( clock_control_t::hsi_t::on) ;}
  inline auto hsi() const {  return clock_control.rd<clock_control_t::hsi_t> ();}

  inline void hsi_operate_in_stop_mode(const clock_control_t::hsi_operate_in_stop_mode_t::enum_t val){  clock_control.rmw(val) ;}
  inline void hsi_operate_in_stop_mode_disable(){  clock_control.rmw( clock_control_t::hsi_operate_in_stop_mode_t::disable) ;}
  inline void hsi_operate_in_stop_mode_enable() {  clock_control.rmw( clock_control_t::hsi_operate_in_stop_mode_t::enable) ;}
  inline auto hsi_operate_in_stop_mode() const {  return clock_control.rd<clock_control_t::hsi_operate_in_stop_mode_t> ();}

  inline auto hsi_ready() const {  return clock_control.rd<clock_control_t::hsi_ready_t> ();}
  inline void hsi_ready_wait() const { while ( hsi_ready() == clock_control_t::hsi_ready_t::not_ready)  {} ; }


  inline void hsi_div(const clock_control_t::hsi_div_t::enum_t val){  clock_control.rmw(val) ;}
  inline void hsi_div1(){  clock_control.rmw( clock_control_t::hsi_div_t::div1) ;}
  inline void hsi_div2(){  clock_control.rmw( clock_control_t::hsi_div_t::div2) ;}
  inline void hsi_div3(){  clock_control.rmw( clock_control_t::hsi_div_t::div3) ;}
  inline void hsi_div4(){  clock_control.rmw( clock_control_t::hsi_div_t::div4) ;}
  inline auto hsi_div_t() const {  return clock_control.rd<clock_control_t::hsi_div_t> ();}

  inline auto hsi_div_perform() const {  return clock_control.rd<clock_control_t::hsi_div_perform_t> ();}
  inline void hsi_div_perform_wait() const { while ( hsi_div_perform() == clock_control_t::hsi_div_perform_t::not_perform)  {} ; }



  inline void csi(const clock_control_t::csi_t::enum_t val){  clock_control.rmw(val) ;}
  inline void csi_off(){  clock_control.rmw( clock_control_t::csi_t::off) ;}
  inline void csi_on() {  clock_control.rmw( clock_control_t::csi_t::on) ;}
  inline auto csi() const {  return clock_control.rd<clock_control_t::csi_t> ();}

  inline void csi_operate_in_stop_mode(const clock_control_t::csi_operate_in_stop_mode_t::enum_t val){  clock_control.rmw(val) ;}
  inline void csi_operate_in_stop_mode_disable(){  clock_control.rmw( clock_control_t::csi_operate_in_stop_mode_t::disable) ;}
  inline void csi_operate_in_stop_mode_enable() {  clock_control.rmw( clock_control_t::csi_operate_in_stop_mode_t::enable) ;}
  inline auto csi_operate_in_stop_mode() const {  return clock_control.rd<clock_control_t::csi_operate_in_stop_mode_t> ();}

  inline auto csi_ready() const {  return clock_control.rd<clock_control_t::csi_ready_t> ();}
  inline void csi_ready_wait() const { while ( csi_ready() == clock_control_t::csi_ready_t::not_ready)  {} ; }


  inline void hsi48(const clock_control_t::hsi48_t::enum_t val){  clock_control.rmw(val) ;}
  inline void hsi48_off(){  clock_control.rmw( clock_control_t::hsi48_t::off) ;}
  inline void hsi48_on() {  clock_control.rmw( clock_control_t::hsi48_t::on) ;}
  inline auto hsi48() const {  return clock_control.rd<clock_control_t::hsi48_t> ();}

  inline auto hsi48_ready() const {  return clock_control.rd<clock_control_t::hsi48_ready_t> ();}
  inline void hsi48_ready_wait() const { while ( hsi48_ready() == clock_control_t::hsi48_ready_t::not_ready)  {} ; }

  inline auto d1_ready() const {  return clock_control.rd<clock_control_t::d1_clock_ready_t> ();}
  inline void d1_ready_wait() const { while ( d1_ready() == clock_control_t::d1_clock_ready_t::not_ready)  {} ; }


  inline auto d2_ready() const {  return clock_control.rd<clock_control_t::d2_clock_ready_t> ();}
  inline void d2_ready_wait() const { while ( d2_ready() == clock_control_t::d2_clock_ready_t::not_ready)  {} ; }



  inline void hse(const clock_control_t::hse_t::enum_t val){  clock_control.rmw(val) ;}
  inline void hse_off(){  clock_control.rmw( clock_control_t::hse_t::off) ;}
  inline void hse_on() {  clock_control.rmw( clock_control_t::hse_t::on) ;}
  inline auto hse() const {  return clock_control.rd<clock_control_t::hse_t> ();}

  inline auto hse_ready() const {  return clock_control.rd<clock_control_t::hse_ready_t> ();}
  inline void hse_ready_wait() const { while ( hse_ready() == clock_control_t::hse_ready_t::not_ready)  {} ; }

  inline  void hse_clock_bypass(const clock_control_t::hse_clock_bypass_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_clock_bypass_off(){  clock_control.rmw(clock_control_t::hse_clock_bypass_t::off) ;}
  inline  void hse_clock_bypass_on() {  clock_control.rmw(clock_control_t::hse_clock_bypass_t::on) ;}
  inline  auto hse_clock_bypass() const {  return clock_control.rd<clock_control_t::hse_clock_bypass_t> ();}

  inline  void hse_clock_security_system(const clock_control_t::hse_clock_security_system_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hse_clock_security_system_disable(){  clock_control.rmw( clock_control_t::hse_clock_security_system_t::disable) ;}
  inline  void hse_clock_security_system_enable() {  clock_control.rmw( clock_control_t::hse_clock_security_system_t::enable) ;}
  inline  auto hse_clock_security_system() const {  return clock_control.rd<clock_control_t::hse_clock_security_system_t> ();}

  inline  void pll1(const clock_control_t::pll1_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll1_off(){  clock_control.rmw( clock_control_t::pll1_t::off) ;}
  inline  void pll1_on() {  clock_control.rmw( clock_control_t::pll1_t::on) ;}
  inline  auto pll1() const {  return clock_control.rd<clock_control_t::pll1_t> ();}

  inline auto pll1_ready() const {  return clock_control.rd<clock_control_t::pll1_ready_t> ();}
  inline void pll1pll11ady_wait() const { while ( pll1_ready() == clock_control_t::pll1_ready_t::not_ready)  {} ; }

  inline  void pll2(const clock_control_t::pll2_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll2_off(){  clock_control.rmw( clock_control_t::pll2_t::off) ;}
  inline  void pll2_on() {  clock_control.rmw( clock_control_t::pll2_t::on) ;}
  inline  auto pll2() const {  return clock_control.rd<clock_control_t::pll2_t> ();}

  inline auto pll2_ready(){  return clock_control.rd<clock_control_t::pll2_ready_t> ();}
  inline void pll2_ready_wait() { while ( pll2_ready() == clock_control_t::pll2_ready_t::not_ready)  {} ; }

  inline  void pll3(const clock_control_t::pll3_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll3_off(){  clock_control.rmw( clock_control_t::pll3_t::off) ;}
  inline  void pll3_on() {  clock_control.rmw( clock_control_t::pll3_t::on) ;}
  inline  auto pll3() const {  return clock_control.rd<clock_control_t::pll3_t> ();}

  inline auto pll3_ready() const {  return clock_control.rd<clock_control_t::pll3_ready_t> ();}
  inline void pll3_ready_wait() const { while ( pll3_ready() == clock_control_t::pll3_ready_t::not_ready)  {} ; }

  struct internal_clock_sources_calibration_t : public read_write_32_t
  {
    struct hsi_clock_calibration_t { enum enum_t { offset=0,  mask=0b111111111111 } ; } ;
    struct hsi_clock_trimming_t    { enum enum_t { offset=12, mask=0b111111 } ; } ;
    struct csi_clock_calibration_t { enum enum_t { offset=18, mask=0b11111111 } ; } ;
    struct csi_clock_trimming_t    { enum enum_t { offset=26, mask=0b11111 } ; } ;
  };

  inline  auto hsi_clock_calibration() const {  return (uint16_t) internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::hsi_clock_calibration_t> ();}
  inline  auto hsi_clock_trimming() const {  return (uint8_t) internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::hsi_clock_trimming_t> ();}
  inline  auto csi_clock_calibration() const {  return (uint16_t) internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::csi_clock_calibration_t> ();}
  inline  auto csi_clock_trimming() const {  return (uint8_t) internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::csi_clock_trimming_t> ();}


  struct clock_recovery_rc_t : public read_write_32_t
  {
     struct rc48_clock_calibration_t { enum enum_t { offset=0,  mask=0b1111111111 } ; } ;
  };

  inline  auto rc48_clock_calibration() const {  return (uint16_t) clock_recovery_rc.rd<clock_recovery_rc_t::rc48_clock_calibration_t> ();}

  struct clock_config_t : public read_write_32_t
  {
     struct system_clock_t        { enum enum_t { offset=0,  mask=0b111, hsi=0, csi, hse, pll1  } ; } ;
     struct system_clock_state_t  { enum enum_t { offset=3,  mask=0b111, hsi=0, csi, hse, pll1  } ; } ;
     struct system_clock_after_wakeup_from_stop_t  { enum enum_t { offset=6,  mask=1, hsi=0, csi } ;} ;
     struct kernel_clock_after_wakeup_from_stop_t  { enum enum_t { offset=7,  mask=1, hsi=0, csi } ;} ;
  };

  inline  void system_clock(const clock_config_t::system_clock_t::enum_t val){  clock_config.rmw(val) ;}
  inline  void system_clock_hsi(){  clock_config.rmw(clock_config_t::system_clock_t::hsi) ;}
  inline  void system_clock_csi(){  clock_config.rmw(clock_config_t::system_clock_t::csi) ;}
  inline  void system_clock_hse(){  clock_config.rmw(clock_config_t::system_clock_t::hse) ;}
  inline  void system_clock_pll1(){ clock_config.rmw(clock_config_t::system_clock_t::pll1) ;}
  inline  auto system_clock() const {  return clock_config.rd<clock_config_t::system_clock_t> ();}

  inline auto system_clock_state() const {  return clock_config.rd<clock_config_t::system_clock_state_t> ();}
  inline void system_clock_state_hsi_wait() const  { while ( system_clock_state() != clock_config_t::system_clock_state_t::hsi ){}; }
  inline void system_clock_state_csi_wait() const  { while ( system_clock_state() != clock_config_t::system_clock_state_t::csi ){}; }
  inline void system_clock_state_hse_wait() const  { while ( system_clock_state() != clock_config_t::system_clock_state_t::hse ){}; }
  inline void system_clock_state_pll1_wait() const  { while ( system_clock_state() != clock_config_t::system_clock_state_t::pll1 ){}; }

  inline void system_clock_after_wakeup_from_stop(const clock_config_t::system_clock_after_wakeup_from_stop_t::enum_t val){  clock_config.rmw(val) ;}
  inline void system_clock_after_wakeup_from_stop_hsi(){  clock_config.rmw(clock_config_t::system_clock_after_wakeup_from_stop_t::hsi) ;}
  inline void system_clock_after_wakeup_from_stop_csi(){  clock_config.rmw(clock_config_t::system_clock_after_wakeup_from_stop_t::csi) ;}
  inline auto system_clock_after_wakeup_from_stop() const {  return clock_config.rd<clock_config_t::system_clock_after_wakeup_from_stop_t> ();}

  inline void kernel_clock_after_wakeup_from_stop(const clock_config_t::kernel_clock_after_wakeup_from_stop_t::enum_t val){  clock_config.rmw(val) ;}
  inline void kernel_clock_after_wakeup_from_stop_hsi(){  clock_config.rmw(clock_config_t::kernel_clock_after_wakeup_from_stop_t::hsi) ;}
  inline void kernel_clock_after_wakeup_from_stop_csi(){  clock_config.rmw(clock_config_t::kernel_clock_after_wakeup_from_stop_t::csi) ;}
  inline auto kernel_clock_after_wakeup_from_stop() const {  return clock_config.rd<clock_config_t::kernel_clock_after_wakeup_from_stop_t> ();}


  struct domain1_config_t : public read_write_32_t
  {
      struct d1_ahb_prescaler_t { enum enum_t { offset=0,  mask=0b1111, div1=0, div2=8, div4, div8, div16, div64, div128, div256, div512  } ; } ;
      struct d1_apb3_prescaler_t { enum enum_t { offset=4,  mask=0b111, div1=0, div2=4, div4, div8, div16 } ; } ;
      struct d1_core_prescaler_t { enum enum_t { offset=8,  mask=0b1111, div1=0, div2=8, div4, div8, div16, div64, div128, div256, div512  } ; } ;
  };

  inline void d1_ahb_prescaler(const domain1_config_t::d1_ahb_prescaler_t::enum_t val){  domain1_config.rmw(val) ;}
  inline void d1_ahb_prescaler_div1(){  domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div1) ;}
  inline void d1_ahb_prescaler_div2(){  domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div2) ;}
  inline void d1_ahb_prescaler_div4(){  domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div4) ;}
  inline void d1_ahb_prescaler_div8(){  domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div8) ;}
  inline void d1_ahb_prescaler_div16(){ domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div16) ;}
  inline void d1_ahb_prescaler_div64(){ domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div64) ;}
  inline void d1_ahb_prescaler_div128(){domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div128) ;}
  inline void d1_ahb_prescaler_div256(){domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div256) ;}
  inline void d1_ahb_prescaler_div512(){domain1_config.rmw(domain1_config_t::d1_ahb_prescaler_t::div512) ;}
  inline auto d1_ahb_prescaler() const {  return domain1_config.rd<domain1_config_t::d1_ahb_prescaler_t> ();}

  inline void d1_apb3_prescaler(const domain1_config_t::d1_apb3_prescaler_t::enum_t val){  domain1_config.rmw(val) ;}
  inline void d1_apb3_prescaler_div1(){  domain1_config.rmw(domain1_config_t::d1_apb3_prescaler_t::div1) ;}
  inline void d1_apb3_prescaler_div2(){  domain1_config.rmw(domain1_config_t::d1_apb3_prescaler_t::div2) ;}
  inline void d1_apb3_prescaler_div4(){  domain1_config.rmw(domain1_config_t::d1_apb3_prescaler_t::div4) ;}
  inline void d1_apb3_prescaler_div8(){  domain1_config.rmw(domain1_config_t::d1_apb3_prescaler_t::div8) ;}
  inline void d1_apb3_prescaler_div16(){ domain1_config.rmw(domain1_config_t::d1_apb3_prescaler_t::div16) ;}
  inline auto d1_apb3_prescaler() const {  return domain1_config.rd<domain1_config_t::d1_apb3_prescaler_t> ();}

  inline void d1_core_prescaler(const domain1_config_t::d1_core_prescaler_t::enum_t val){  domain1_config.rmw(val) ;}
  inline void d1_core_prescaler_div1(){  domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div1) ;}
  inline void d1_core_prescaler_div2(){  domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div2) ;}
  inline void d1_core_prescaler_div4(){  domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div4) ;}
  inline void d1_core_prescaler_div8(){  domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div8) ;}
  inline void d1_core_prescaler_div16(){ domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div16) ;}
  inline void d1_core_prescaler_div64(){ domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div64) ;}
  inline void d1_core_prescaler_div128(){domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div128) ;}
  inline void d1_core_prescaler_div256(){domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div256) ;}
  inline void d1_core_prescaler_div512(){domain1_config.rmw(domain1_config_t::d1_core_prescaler_t::div512) ;}
  inline auto d1_core_prescaler() const {  return domain1_config.rd<domain1_config_t::d1_core_prescaler_t> ();}

  struct domain2_config_t : public read_write_32_t
  {
     struct d2_apb1_prescaler_t { enum enum_t { offset=4,  mask=0b111, div1=0, div2=4, div4, div8, div16 } ; } ;
     struct d2_apb2_prescaler_t { enum enum_t { offset=8,  mask=0b111, div1=0, div2=4, div4, div8, div16 } ; } ;
  };

  inline void d2_apb1_prescaler(const domain2_config_t::d2_apb1_prescaler_t::enum_t val){  domain2_config.rmw(val) ;}
  inline void d2_apb1_prescaler_div1(){  domain2_config.rmw(domain2_config_t::d2_apb1_prescaler_t::div1) ;}
  inline void d2_apb1_prescaler_div2(){  domain2_config.rmw(domain2_config_t::d2_apb1_prescaler_t::div2) ;}
  inline void d2_apb1_prescaler_div4(){  domain2_config.rmw(domain2_config_t::d2_apb1_prescaler_t::div4) ;}
  inline void d2_apb1_prescaler_div8(){  domain2_config.rmw(domain2_config_t::d2_apb1_prescaler_t::div8) ;}
  inline void d2_apb1_prescaler_div16(){ domain2_config.rmw(domain2_config_t::d2_apb1_prescaler_t::div16) ;}
  inline auto d2_apb1_prescaler() const {  return domain2_config.rd<domain2_config_t::d2_apb1_prescaler_t> ();}

  inline void d2_apb2_prescaler(const domain2_config_t::d2_apb2_prescaler_t::enum_t val){  domain2_config.rmw(val) ;}
  inline void d2_apb2_prescaler_div1(){  domain2_config.rmw(domain2_config_t::d2_apb2_prescaler_t::div1) ;}
  inline void d2_apb2_prescaler_div2(){  domain2_config.rmw(domain2_config_t::d2_apb2_prescaler_t::div2) ;}
  inline void d2_apb2_prescaler_div4(){  domain2_config.rmw(domain2_config_t::d2_apb2_prescaler_t::div4) ;}
  inline void d2_apb2_prescaler_div8(){  domain2_config.rmw(domain2_config_t::d2_apb2_prescaler_t::div8) ;}
  inline void d2_apb2_prescaler_div16(){ domain2_config.rmw(domain2_config_t::d2_apb2_prescaler_t::div16) ;}
  inline auto d2_apb2_prescaler() const {  return domain2_config.rd<domain2_config_t::d2_apb2_prescaler_t> ();}

  struct domain3_config_t : public read_write_32_t
  {
     struct d3_apb4_prescaler_t { enum enum_t { offset=4,  mask=0b111, div1=0, div2=4, div4, div8, div16 } ; } ;
  };

  inline void d3_apb4_prescaler(const domain3_config_t::d3_apb4_prescaler_t::enum_t val){  domain3_config.rmw(val) ;}
  inline void d3_apb4_prescaler_div1(){  domain3_config.rmw(domain3_config_t::d3_apb4_prescaler_t::div1) ;}
  inline void d3_apb4_prescaler_div2(){  domain3_config.rmw(domain3_config_t::d3_apb4_prescaler_t::div2) ;}
  inline void d3_apb4_prescaler_div4(){  domain3_config.rmw(domain3_config_t::d3_apb4_prescaler_t::div4) ;}
  inline void d3_apb4_prescaler_div8(){  domain3_config.rmw(domain3_config_t::d3_apb4_prescaler_t::div8) ;}
  inline void d3_apb4_prescaler_div16(){ domain3_config.rmw(domain3_config_t::d3_apb4_prescaler_t::div16) ;}
  inline auto d3_apb4_prescaler() const {  return domain3_config.rd<domain3_config_t::d3_apb4_prescaler_t> ();}

  struct pll_clock_source_selection_t : public read_write_32_t
    {
       struct pll_clock_source_t { enum enum_t { offset=0,  mask=0b11, hsi=0, csi, hse, no_clocks } ; } ;
       struct pll1_m_t { enum enum_t { offset=4,  mask=0b111111 } ; } ;
       struct pll2_m_t { enum enum_t { offset=12, mask=0b111111 } ; } ;
       struct pll3_m_t { enum enum_t { offset=20, mask=0b111111 } ; } ;
    };

  inline  void pll_clock_source(const pll_clock_source_selection_t::pll_clock_source_t::enum_t val){  pll_clock_source_selection.rmw(val) ;}
  inline  void pll_clock_source_hsi(){ pll_clock_source_selection.rmw(pll_clock_source_selection_t::pll_clock_source_t::hsi) ;}
  inline  void pll_clock_source_csi(){ pll_clock_source_selection.rmw(pll_clock_source_selection_t::pll_clock_source_t::csi) ;}
  inline  void pll_clock_source_hse(){ pll_clock_source_selection.rmw(pll_clock_source_selection_t::pll_clock_source_t::hse) ;}
  inline  void pll_clock_source_no_clocks(){ pll_clock_source_selection.rmw(pll_clock_source_selection_t::pll_clock_source_t::no_clocks) ;}
  inline  auto pll_clock_source() const {  return pll_clock_source_selection.rd<pll_clock_source_selection_t::pll_clock_source_t> ();}

  inline  void pll1_m( const uint8_t val){  pll_clock_source_selection.rmw( (pll_clock_source_selection_t::pll1_m_t::enum_t)val) ;}
  inline  auto pll1_m() const {  return (uint8_t) pll_clock_source_selection.rd<pll_clock_source_selection_t::pll1_m_t> ();}

  inline  void pll2_m( const uint8_t val){  pll_clock_source_selection.rmw( (pll_clock_source_selection_t::pll2_m_t::enum_t)val) ;}
  inline  auto pll2_m() const {  return (uint8_t) pll_clock_source_selection.rd<pll_clock_source_selection_t::pll2_m_t> ();}

  inline  void pll3_m( const uint8_t val){  pll_clock_source_selection.rmw( (pll_clock_source_selection_t::pll3_m_t::enum_t)val) ;}
  inline  auto pll3_m() const {  return (uint8_t) pll_clock_source_selection.rd<pll_clock_source_selection_t::pll3_m_t> ();}

  struct pll_config_t : public read_write_32_t
    {
       struct pll1_frac_latch_t       { enum enum_t { offset=0,  mask=1, disable=0, enable } ; } ;
       struct pll1_vco_selection_t    { enum enum_t { offset=1,  mask=1, wide_192_836Mhz=0, narrow_150_420Mhz } ; } ;
       struct pll1_input_freq_t       { enum enum_t { offset=2,  mask=0b11, range_1_2Mhz=0, range_2_4Mhz, range_4_8Mhz, range_8_16Mhz } ; } ;
       struct pll2_frac_latch_t       { enum enum_t { offset=4,  mask=1, disable=0, enable } ; } ;
       struct pll2_vco_selection_t    { enum enum_t { offset=5,  mask=1, wide_192_836Mhz=0, narrow_150_420Mhz } ; } ;
       struct pll2_input_freq_t       { enum enum_t { offset=6,  mask=0b11, range_1_2Mhz=0, range_2_4Mhz, range_4_8Mhz, range_8_16Mhz } ; } ;
       struct pll3_frac_latch_t       { enum enum_t { offset=8,  mask=1, disable=0, enable } ; } ;
       struct pll3_vco_selection_t    { enum enum_t { offset=9,  mask=1, wide_192_836Mhz=0, narrow_150_420Mhz } ; } ;
       struct pll3_input_freq_t       { enum enum_t { offset=10,  mask=0b11, range_1_2Mhz=0, range_2_4Mhz, range_4_8Mhz, range_8_16Mhz } ; } ;

       struct pll1_p_state_t          { enum enum_t { offset=16,  mask=1, disable=0, enable } ; } ;
       struct pll1_q_state_t          { enum enum_t { offset=17,  mask=1, disable=0, enable } ; } ;
       struct pll1_r_state_t          { enum enum_t { offset=18,  mask=1, disable=0, enable } ; } ;
       struct pll2_p_state_t          { enum enum_t { offset=19,  mask=1, disable=0, enable } ; } ;
       struct pll2_q_state_t          { enum enum_t { offset=20,  mask=1, disable=0, enable } ; } ;
       struct pll2_r_state_t          { enum enum_t { offset=21,  mask=1, disable=0, enable } ; } ;
       struct pll3_p_state_t          { enum enum_t { offset=22,  mask=1, disable=0, enable } ; } ;
       struct pll3_q_state_t          { enum enum_t { offset=23,  mask=1, disable=0, enable } ; } ;
       struct pll3_r_state_t          { enum enum_t { offset=24,  mask=1, disable=0, enable } ; } ;
    };

  inline  void pll1_frac_latch(const pll_config_t::pll1_frac_latch_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_frac_latch_disable(){ pll_config.rmw(pll_config_t::pll1_frac_latch_t::disable) ;}
  inline  void pll1_frac_latch_enable(){ pll_config.rmw(pll_config_t::pll1_frac_latch_t::enable) ;}
  inline  auto pll1_frac_latch() const {  return pll_config.rd<pll_config_t::pll1_frac_latch_t> ();}

  inline  void pll1_vco_selection(const pll_config_t::pll1_vco_selection_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_vco_selection_wide_192_836Mhz(){ pll_config.rmw(pll_config_t::pll1_vco_selection_t::wide_192_836Mhz) ;}
  inline  void pll1_vco_selection_narrow_150_420Mhz(){ pll_config.rmw(pll_config_t::pll1_vco_selection_t::narrow_150_420Mhz) ;}
  inline  auto pll1_vco_selection() const {  return pll_config.rd<pll_config_t::pll1_vco_selection_t> ();}

  inline  void pll1_input_freq(const pll_config_t::pll1_input_freq_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_input_freq_range_1_2Mhz(){ pll_config.rmw(pll_config_t::pll1_input_freq_t::range_1_2Mhz) ;}
  inline  void pll1_input_freq_range_2_4Mhz(){ pll_config.rmw(pll_config_t::pll1_input_freq_t::range_2_4Mhz) ;}
  inline  void pll1_input_freq_range_4_8Mhz(){ pll_config.rmw(pll_config_t::pll1_input_freq_t::range_4_8Mhz) ;}
  inline  void pll1_input_freq_range_8_16Mhz(){ pll_config.rmw(pll_config_t::pll1_input_freq_t::range_8_16Mhz) ;}
  inline  auto pll1_input_freq() const {  return pll_config.rd<pll_config_t::pll1_input_freq_t> ();}

  inline  void pll2_frac_latch(const pll_config_t::pll2_frac_latch_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_frac_latch_disable(){ pll_config.rmw(pll_config_t::pll2_frac_latch_t::disable) ;}
  inline  void pll2_frac_latch_enable(){ pll_config.rmw(pll_config_t::pll2_frac_latch_t::enable) ;}
  inline  auto pll2_frac_latch() const {  return pll_config.rd<pll_config_t::pll2_frac_latch_t> ();}

  inline  void pll2_vco_selection(const pll_config_t::pll2_vco_selection_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_vco_selection_wide_192_836Mhz(){ pll_config.rmw(pll_config_t::pll2_vco_selection_t::wide_192_836Mhz) ;}
  inline  void pll2_vco_selection_narrow_150_420Mhz(){ pll_config.rmw(pll_config_t::pll2_vco_selection_t::narrow_150_420Mhz) ;}
  inline  auto pll2_vco_selection() const {  return pll_config.rd<pll_config_t::pll2_vco_selection_t> ();}

  inline  void pll2_input_freq(const pll_config_t::pll2_input_freq_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_input_freq_range_1_2Mhz(){ pll_config.rmw(pll_config_t::pll2_input_freq_t::range_1_2Mhz) ;}
  inline  void pll2_input_freq_range_2_4Mhz(){ pll_config.rmw(pll_config_t::pll2_input_freq_t::range_2_4Mhz) ;}
  inline  void pll2_input_freq_range_4_8Mhz(){ pll_config.rmw(pll_config_t::pll2_input_freq_t::range_4_8Mhz) ;}
  inline  void pll2_input_freq_range_8_16Mhz(){ pll_config.rmw(pll_config_t::pll2_input_freq_t::range_8_16Mhz) ;}
  inline  auto pll2_input_freq() const {  return pll_config.rd<pll_config_t::pll2_input_freq_t> ();}

  inline  void pll3_frac_latch(const pll_config_t::pll3_frac_latch_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_frac_latch_disable(){ pll_config.rmw(pll_config_t::pll3_frac_latch_t::disable) ;}
  inline  void pll3_frac_latch_enable(){ pll_config.rmw(pll_config_t::pll3_frac_latch_t::enable) ;}
  inline  auto pll3_frac_latch() const {  return pll_config.rd<pll_config_t::pll3_frac_latch_t> ();}

  inline  void pll3_vco_selection(const pll_config_t::pll3_vco_selection_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_vco_selection_wide_192_836Mhz(){ pll_config.rmw(pll_config_t::pll3_vco_selection_t::wide_192_836Mhz) ;}
  inline  void pll3_vco_selection_narrow_150_420Mhz(){ pll_config.rmw(pll_config_t::pll3_vco_selection_t::narrow_150_420Mhz) ;}
  inline  auto pll3_vco_selection() const {  return pll_config.rd<pll_config_t::pll3_vco_selection_t> ();}

  inline  void pll3_input_freq(const pll_config_t::pll3_input_freq_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_input_freq_range_1_2Mhz(){ pll_config.rmw(pll_config_t::pll3_input_freq_t::range_1_2Mhz) ;}
  inline  void pll3_input_freq_range_2_4Mhz(){ pll_config.rmw(pll_config_t::pll3_input_freq_t::range_2_4Mhz) ;}
  inline  void pll3_input_freq_range_4_8Mhz(){ pll_config.rmw(pll_config_t::pll3_input_freq_t::range_4_8Mhz) ;}
  inline  void pll3_input_freq_range_8_16Mhz(){ pll_config.rmw(pll_config_t::pll3_input_freq_t::range_8_16Mhz) ;}
  inline  auto pll3_input_freq() const {  return pll_config.rd<pll_config_t::pll3_input_freq_t> ();}


  inline  void pll1_p_state(const pll_config_t::pll1_p_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_p_disable(){ pll_config.rmw(pll_config_t::pll1_p_state_t::disable) ;}
  inline  void pll1_p_enable(){ pll_config.rmw(pll_config_t::pll1_p_state_t::enable) ;}
  inline  auto pll1_p_state() const {  return pll_config.rd<pll_config_t::pll1_p_state_t> ();}

  inline  void pll1_q_state(const pll_config_t::pll1_q_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_q_disable(){ pll_config.rmw(pll_config_t::pll1_q_state_t::disable) ;}
  inline  void pll1_q_enable(){ pll_config.rmw(pll_config_t::pll1_q_state_t::enable) ;}
  inline  auto pll1_q_state() const {  return pll_config.rd<pll_config_t::pll1_r_state_t> ();}

  inline  void pll1_r_state(const pll_config_t::pll1_r_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll1_r_disable(){ pll_config.rmw(pll_config_t::pll1_r_state_t::disable) ;}
  inline  void pll1_r_enable(){ pll_config.rmw(pll_config_t::pll1_r_state_t::enable) ;}
  inline  auto pll1_r_state() const {  return pll_config.rd<pll_config_t::pll1_r_state_t> ();}

  inline  void pll2_p_state(const pll_config_t::pll2_p_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_p_disable(){ pll_config.rmw(pll_config_t::pll2_p_state_t::disable) ;}
  inline  void pll2_p_enable(){ pll_config.rmw(pll_config_t::pll2_p_state_t::enable) ;}
  inline  auto pll2_p_state() const {  return pll_config.rd<pll_config_t::pll2_p_state_t> ();}

  inline  void pll2_q_state(const pll_config_t::pll2_q_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_q_disable(){ pll_config.rmw(pll_config_t::pll2_q_state_t::disable) ;}
  inline  void pll2_q_enable(){ pll_config.rmw(pll_config_t::pll2_q_state_t::enable) ;}
  inline  auto pll2_q_state() const {  return pll_config.rd<pll_config_t::pll2_r_state_t> ();}

  inline  void pll2_r_state(const pll_config_t::pll2_r_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll2_r_disable(){ pll_config.rmw(pll_config_t::pll2_r_state_t::disable) ;}
  inline  void pll2_r_enable(){ pll_config.rmw(pll_config_t::pll2_r_state_t::enable) ;}
  inline  auto pll2_r_state() const {  return pll_config.rd<pll_config_t::pll2_r_state_t> ();}

  inline  void pll3_p_state(const pll_config_t::pll3_p_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_p_disable(){ pll_config.rmw(pll_config_t::pll3_p_state_t::disable) ;}
  inline  void pll3_p_enable(){ pll_config.rmw(pll_config_t::pll3_p_state_t::enable) ;}
  inline  auto pll3_p_state() const {  return pll_config.rd<pll_config_t::pll3_p_state_t> ();}

  inline  void pll3_q_state(const pll_config_t::pll3_q_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_q_disable(){ pll_config.rmw(pll_config_t::pll3_q_state_t::disable) ;}
  inline  void pll3_q_enable(){ pll_config.rmw(pll_config_t::pll3_q_state_t::enable) ;}
  inline  auto pll3_q_state() const {  return pll_config.rd<pll_config_t::pll3_r_state_t> ();}

  inline  void pll3_r_state(const pll_config_t::pll3_r_state_t::enum_t val){  pll_config.rmw(val) ;}
  inline  void pll3_r_disable(){ pll_config.rmw(pll_config_t::pll3_r_state_t::disable) ;}
  inline  void pll3_r_enable(){ pll_config.rmw(pll_config_t::pll3_r_state_t::enable) ;}
  inline  auto pll3_r_state() const {  return pll_config.rd<pll_config_t::pll3_r_state_t> ();}

  struct pll1_divs_t : public read_write_32_t
    {
      struct n_t       { enum enum_t { offset=0,  mask=0b111111111 } ; } ;
      struct p_t       { enum enum_t { offset=9,  mask=0b1111111 } ; } ;
      struct q_t       { enum enum_t { offset=16, mask=0b1111111 } ; } ;
      struct r_t       { enum enum_t { offset=24, mask=0b1111111 } ; } ;
    };

  inline  void pll1_n( const uint16_t val){  pll1_divs.rmw( (pll1_divs_t::n_t::enum_t)val) ;}
  inline  auto pll1_n() const {  return (uint16_t) pll1_divs.rd<pll1_divs_t::n_t> ();}

  inline  void pll1_p( const uint16_t val){  pll1_divs.rmw( (pll1_divs_t::p_t::enum_t)(val - 1)) ;}
  inline  auto pll1_p() const {  return (uint16_t) pll1_divs.rd<pll1_divs_t::p_t> () + 1;}

  inline  void pll1_q( const uint16_t val){  pll1_divs.rmw( (pll1_divs_t::q_t::enum_t)(val - 1)) ;}
  inline  auto pll1_q() const {  return (uint16_t) pll1_divs.rd<pll1_divs_t::q_t> () + 1 ;}

  inline  void pll1_r( const uint16_t val){  pll1_divs.rmw( (pll1_divs_t::r_t::enum_t)(val - 1)) ;}
  inline  auto pll1_r() const {  return (uint16_t) pll1_divs.rd<pll1_divs_t::r_t> () + 1 ;}


  struct pll1_fract_div_t : public read_write_32_t
    {
       struct fract_t    { enum enum_t { offset=3,  mask=0b1111111111111 } ; } ;
    };

  inline  void pll1_fract( const uint16_t val){  pll1_fract_div.rmw( (pll1_fract_div_t::fract_t::enum_t)val ) ;}
  inline  auto pll1_fract() const {  return (uint16_t) pll1_fract_div.rd<pll1_fract_div_t::fract_t> () ;}


  struct pll2_divs_t : public read_write_32_t
    {
      struct n_t       { enum enum_t { offset=0,  mask=0b111111111 } ; } ;
      struct p_t       { enum enum_t { offset=9,  mask=0b1111111 } ; } ;
      struct q_t       { enum enum_t { offset=16, mask=0b1111111 } ; } ;
      struct r_t       { enum enum_t { offset=24, mask=0b1111111 } ; } ;
    };

  inline  void pll2_n( const uint16_t val){  pll2_divs.rmw( (pll2_divs_t::n_t::enum_t)val) ;}
  inline  auto pll2_n() const {  return (uint16_t) pll2_divs.rd<pll2_divs_t::n_t> ();}

  inline  void pll2_p( const uint16_t val){  pll2_divs.rmw( (pll2_divs_t::p_t::enum_t)(val - 1)) ;}
  inline  auto pll2_p() const {  return (uint16_t) pll2_divs.rd<pll2_divs_t::p_t> () + 1;}

  inline  void pll2_q( const uint16_t val){  pll2_divs.rmw( (pll2_divs_t::q_t::enum_t)(val - 1)) ;}
  inline  auto pll2_q() const {  return (uint16_t) pll2_divs.rd<pll2_divs_t::q_t> () + 1 ;}

  inline  void pll2_r( const uint16_t val){  pll2_divs.rmw( (pll2_divs_t::r_t::enum_t)(val - 1)) ;}
  inline  auto pll2_r() const {  return (uint16_t) pll2_divs.rd<pll2_divs_t::r_t> () + 1 ;}


  struct pll2_fract_div_t : public read_write_32_t
    {
       struct fract_t    { enum enum_t { offset=3,  mask=0b1111111111111 } ; } ;
    };

  inline  void pll2_fract( const uint16_t val){  pll2_fract_div.rmw( (pll2_fract_div_t::fract_t::enum_t)val ) ;}
  inline  auto pll2_fract() const {  return (uint16_t) pll2_fract_div.rd<pll2_fract_div_t::fract_t> () ;}

  struct pll3_divs_t : public read_write_32_t
    {
      struct n_t       { enum enum_t { offset=0,  mask=0b111111111 } ; } ;
      struct p_t       { enum enum_t { offset=9,  mask=0b1111111 } ; } ;
      struct q_t       { enum enum_t { offset=16, mask=0b1111111 } ; } ;
      struct r_t       { enum enum_t { offset=24, mask=0b1111111 } ; } ;
    };

  inline  void pll3_n( const uint16_t val){  pll3_divs.rmw( (pll3_divs_t::n_t::enum_t)val) ;}
  inline  auto pll3_n() const {  return (uint16_t) pll3_divs.rd<pll3_divs_t::n_t> ();}

  inline  void pll3_p( const uint16_t val){  pll3_divs.rmw( (pll3_divs_t::p_t::enum_t)(val - 1)) ;}
  inline  auto pll3_p() const {  return (uint16_t) pll3_divs.rd<pll3_divs_t::p_t> () + 1;}

  inline  void pll3_q( const uint16_t val){  pll3_divs.rmw( (pll3_divs_t::q_t::enum_t)(val - 1)) ;}
  inline  auto pll3_q() const {  return (uint16_t) pll3_divs.rd<pll3_divs_t::q_t> () + 1 ;}

  inline  void pll3_r( const uint16_t val){  pll3_divs.rmw( (pll3_divs_t::r_t::enum_t)(val - 1)) ;}
  inline  auto pll3_r() const {  return (uint16_t) pll3_divs.rd<pll3_divs_t::r_t> () + 1 ;}


  struct pll3_fract_div_t : public read_write_32_t
    {
       struct fract_t    { enum enum_t { offset=3,  mask=0b1111111111111 } ; } ;
    };

  inline  void pll3_fract( const uint16_t val){  pll3_fract_div.rmw( (pll3_fract_div_t::fract_t::enum_t)val ) ;}
  inline  auto pll3_fract() const {  return (uint16_t) pll3_fract_div.rd<pll3_fract_div_t::fract_t> () ;}

  struct d1_kernel_clock_config_t : public read_write_32_t
    {
       struct fmc_clock_selection_t    { enum enum_t { offset=0,  mask=0b11, hclk3=0, pll1_q, pll2_r, kernel_peripheral } ; } ;
       struct qspi_clock_selection_t   { enum enum_t { offset=4,  mask=0b11, hclk3=0, pll1_q, pll2_r, kernel_peripheral } ; } ;
       struct sdmmc_clock_selection_t  { enum enum_t { offset=16, mask=0b1,  pll1_q=0, pll2_r } ; } ;
       struct kernel_peripheral_clock_selection_t  { enum enum_t { offset=28, mask=0b11,  hsi=0, csi, hse } ; } ;
    };

  inline  void fmc_clock_selection(const d1_kernel_clock_config_t::fmc_clock_selection_t::enum_t val){  d1_kernel_clock_config.rmw(val) ;}
  inline  void fmc_clock_selection_hclk3(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::fmc_clock_selection_t::hclk3) ;}
  inline  void fmc_clock_selection_pll1_q(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::fmc_clock_selection_t::pll1_q) ;}
  inline  void fmc_clock_selection_pll2_r(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::fmc_clock_selection_t::pll2_r) ;}
  inline  void fmc_clock_selection_kernel_peripheral(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::fmc_clock_selection_t::kernel_peripheral) ;}
  inline  auto fmc_clock_selection() const {  return d1_kernel_clock_config.rd<d1_kernel_clock_config_t::fmc_clock_selection_t> ();}

  inline  void qspi_clock_selection(const d1_kernel_clock_config_t::qspi_clock_selection_t::enum_t val){  d1_kernel_clock_config.rmw(val) ;}
  inline  void qspi_clock_selection_hclk3(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::qspi_clock_selection_t::hclk3) ;}
  inline  void qspi_clock_selection_pll1_q(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::qspi_clock_selection_t::pll1_q) ;}
  inline  void qspi_clock_selection_pll2_r(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::qspi_clock_selection_t::pll2_r) ;}
  inline  void qspi_clock_selection_kernel_peripheral(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::qspi_clock_selection_t::kernel_peripheral) ;}
  inline  auto qspi_clock_selection() const {  return d1_kernel_clock_config.rd<d1_kernel_clock_config_t::qspi_clock_selection_t> ();}

  inline  void sdmmc_clock_selection(const d1_kernel_clock_config_t::sdmmc_clock_selection_t::enum_t val){  d1_kernel_clock_config.rmw(val) ;}
  inline  void sdmmc_clock_selection_pll1_q(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::sdmmc_clock_selection_t::pll1_q) ;}
  inline  void sdmmc_clock_selection_pll2_r(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::sdmmc_clock_selection_t::pll2_r) ;}
  inline  auto sdmmc_clock_selection() const {  return d1_kernel_clock_config.rd<d1_kernel_clock_config_t::sdmmc_clock_selection_t> ();}

  inline  void kernel_peripheral_clock_selection(const d1_kernel_clock_config_t::kernel_peripheral_clock_selection_t::enum_t val){  d1_kernel_clock_config.rmw(val) ;}
  inline  void kernel_peripheral_clock_selection_hsi(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::kernel_peripheral_clock_selection_t::hsi) ;}
  inline  void kernel_peripheral_clock_selection_csi(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::kernel_peripheral_clock_selection_t::csi) ;}
  inline  void kernel_peripheral_clock_selection_hse(){ d1_kernel_clock_config.rmw(d1_kernel_clock_config_t::kernel_peripheral_clock_selection_t::hse) ;}
  inline  auto kernel_peripheral_clock_selection() const {  return d1_kernel_clock_config.rd<d1_kernel_clock_config_t::kernel_peripheral_clock_selection_t> ();}

  struct d2_kernel_clock_config_1_t : public read_write_32_t
    {
       struct sai1_dfsdm1_aclk_clock_selection_t  { enum enum_t { offset=0,  mask=0b111, pll1_q=0, pll2_p, pll3_p, i2s, kernel_peripheral } ; } ;
       struct sai2_sai3_clock_selection_t         { enum enum_t { offset=6,  mask=0b111, pll1_q=0, pll2_p, pll3_p, i2s, kernel_peripheral } ; } ;
       struct spi123_clock_selection_t            { enum enum_t { offset=12, mask=0b111, pll1_q=0, pll2_p, pll3_p, i2s, kernel_peripheral } ; } ;
       struct spi45_clock_selection_t             { enum enum_t { offset=12, mask=0b111, pll1_q=0, pll2_p, pll3_p, i2s, kernel_peripheral } ; } ;
       struct spdif_clock_selection_t        { enum enum_t { offset=20, mask=0b11, pll1_q=0, pll2_r, pll3_r, i2s, hsi } ; } ;
       struct dfsdm1_clock_selection_t       { enum enum_t { offset=24, mask=0b1, pclk2=0, sys } ; } ;
       struct fdcan_clock_selection_t        { enum enum_t { offset=28, mask=0b11, hsr=0, pll1_q, pll2_q } ; } ;
       struct swpmi_clock_selection_t        { enum enum_t { offset=31, mask=0b1, pclk=0, hsi } ; } ;
    };

  inline  void sai1_dfsdm1_aclk_clock_selection(const d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void sai1_dfsdm1_aclk_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::pll1_q) ;}
  inline  void sai1_dfsdm1_aclk_clock_selection_pll2_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::pll2_p) ;}
  inline  void sai1_dfsdm1_aclk_clock_selection_pll3_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::pll3_p) ;}
  inline  void sai1_dfsdm1_aclk_clock_selection_i2s(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::i2s) ;}
  inline  void sai1_dfsdm1_aclk_clock_selection_kernel_peripheral(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t::kernel_peripheral) ;}
  inline  auto sai1_dfsdm1_aclk_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::sai1_dfsdm1_aclk_clock_selection_t> ();}

  inline  void sai2_sai3_clock_selection(const d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void sai2_sai3_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::pll1_q) ;}
  inline  void sai2_sai3_clock_selection_pll2_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::pll2_p) ;}
  inline  void sai2_sai3_clock_selection_pll3_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::pll3_p) ;}
  inline  void sai2_sai3_clock_selection_i2s(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::i2s) ;}
  inline  void sai2_sai3_clock_selection_kernel_peripheral(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t::kernel_peripheral) ;}
  inline  auto sai2_sai3_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::sai2_sai3_clock_selection_t> ();}

  inline  void spi123_clock_selection(const d2_kernel_clock_config_1_t::spi123_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void spi123_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi123_clock_selection_t::pll1_q) ;}
  inline  void spi123_clock_selection_pll2_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi123_clock_selection_t::pll2_p) ;}
  inline  void spi123_clock_selection_pll3_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi123_clock_selection_t::pll3_p) ;}
  inline  void spi123_clock_selection_i2s(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi123_clock_selection_t::i2s) ;}
  inline  void spi123_clock_selection_kernel_peripheral(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi123_clock_selection_t::kernel_peripheral) ;}
  inline  auto spi123_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::spi123_clock_selection_t> ();}

  inline  void spi45_clock_selection(const d2_kernel_clock_config_1_t::spi45_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void spi45_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi45_clock_selection_t::pll1_q) ;}
  inline  void spi45_clock_selection_pll2_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi45_clock_selection_t::pll2_p) ;}
  inline  void spi45_clock_selection_pll3_p(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi45_clock_selection_t::pll3_p) ;}
  inline  void spi45_clock_selection_i2s(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi45_clock_selection_t::i2s) ;}
  inline  void spi45_clock_selection_kernel_peripheral(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spi45_clock_selection_t::kernel_peripheral) ;}
  inline  auto spi45_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::spi45_clock_selection_t> ();}

  inline  void spdif_clock_selection(const d2_kernel_clock_config_1_t::spdif_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void spdif_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spdif_clock_selection_t::pll1_q) ;}
  inline  void spdif_clock_selection_pll2_r(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spdif_clock_selection_t::pll2_r) ;}
  inline  void spdif_clock_selection_pll3_r(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spdif_clock_selection_t::pll3_r) ;}
  inline  void spdif_clock_selection_i2s(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spdif_clock_selection_t::i2s) ;}
  inline  void spdif_clock_selection_hsi(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::spdif_clock_selection_t::hsi) ;}
  inline  auto spdif_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::spdif_clock_selection_t> ();}

  inline  void dfsdm1_clock_selection(const d2_kernel_clock_config_1_t::dfsdm1_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void dfsdm1_clock_selection_pclk2(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::dfsdm1_clock_selection_t::pclk2) ;}
  inline  void dfsdm1_clock_selection_sys(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::dfsdm1_clock_selection_t::sys) ;}
  inline  auto dfsdm1_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::dfsdm1_clock_selection_t> ();}

  inline  void fdcan_clock_selection(const d2_kernel_clock_config_1_t::fdcan_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void fdcan_clock_selection_hsr(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::fdcan_clock_selection_t::hsr) ;}
  inline  void fdcan_clock_selection_pll1_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::fdcan_clock_selection_t::pll1_q) ;}
  inline  void fdcan_clock_selection_pll2_q(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::fdcan_clock_selection_t::pll2_q) ;}
  inline  auto fdcan_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::fdcan_clock_selection_t> ();}

  inline  void swpmi_clock_selection(const d2_kernel_clock_config_1_t::swpmi_clock_selection_t::enum_t val){  d2_kernel_clock_config_1.rmw(val) ;}
  inline  void swpmi_clock_selection_pclk(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::swpmi_clock_selection_t::pclk) ;}
  inline  void swpmi_clock_selection_hsi(){ d2_kernel_clock_config_1.rmw(d2_kernel_clock_config_1_t::swpmi_clock_selection_t::hsi) ;}
  inline  auto swpmi_clock_selection() const {  return d2_kernel_clock_config_1.rd<d2_kernel_clock_config_1_t::swpmi_clock_selection_t> ();}

  struct d2_kernel_clock_config_2_t : public read_write_32_t
    {
       struct usart234578_clock_selection_t  { enum enum_t { offset=0,  mask=0b111, pckl1=0, pll2_p, pll3_p, hsi, csi, lsi } ; } ;
       struct usart16_clock_selection_t  { enum enum_t { offset=3,  mask=0b111, pckl2=0, pll2_q, pll3_q, hsi, csi, lsi } ; } ;
       struct rng_clock_selection_t  { enum enum_t { offset=8,  mask=0b11, hsi8=0, pll1_q, lse, lsi } ; } ;
       struct i2c123_clock_selection_t  { enum enum_t { offset=12,  mask=0b11, pckl1=0, pll3_r, hsi, csi } ; } ;
       struct usb_clock_selection_t  { enum enum_t { offset=20,  mask=0b11, disable=0, pll1_q, pll3_q, hsi48 } ; } ;
       struct cec_clock_selection_t  { enum enum_t { offset=22,  mask=0b11, lse=0, lsi, csi, disable } ; } ;
       struct tptim1_clock_selection_t  { enum enum_t { offset=0,  mask=0b111, pckl1=0, pll2_p, pll3_r, lse, lsi, kernel_peripheral } ; } ;
    };

  struct d3_kernel_clock_config_t : public read_write_32_t
    {

    };

#if 0



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
#endif

  clock_control_t                       clock_control;                       //CR;            /*!< RCC clock control register,                                              Address offset: 0x00  */
  internal_clock_sources_calibration_t  internal_clock_sources_calibration;  //ICSCR;         /*!< RCC Internal Clock Sources Calibration Register,                         Address offset: 0x04  */
  clock_recovery_rc_t                   clock_recovery_rc;                   //CRRCR;         /*!< Clock Recovery RC  Register,                                             Address offset: 0x08  */

  const uint32_t                        reserved0;                                            /*!< Reserved,                                                                Address offset: 0x0C  */
  clock_config_t                        clock_config;                        //CFGR;           /*!< RCC clock configuration register,                                        Address offset: 0x10  */

  const uint32_t                        reserved1;                                             /*!< Reserved,                                                                Address offset: 0x14  */
  domain1_config_t                      domain1_config;                      //D1CFGR;         /*!< RCC Domain 1 configuration register,                                     Address offset: 0x18  */
  domain2_config_t                      domain2_config;                      //D2CFGR;         /*!< RCC Domain 2 configuration register,                                     Address offset: 0x1C  */
  domain3_config_t                      domain3_config;                      //D3CFGR;         /*!< RCC Domain 3 configuration register,                                     Address offset: 0x20  */
  const uint32_t                        reserved2;                                             /*!< Reserved,                                                                Address offset: 0x24  */
  pll_clock_source_selection_t          pll_clock_source_selection;          //PLLCKSELR;      /*!< RCC PLLs Clock Source Selection Register,                                Address offset: 0x28  */
  pll_config_t                          pll_config;                          //PLLCFGR;        /*!< RCC PLLs  Configuration Register,                                        Address offset: 0x2C  */
  pll1_divs_t                           pll1_divs;                           //PLL1DIVR;       /*!< RCC PLL1 Dividers Configuration Register,                                Address offset: 0x30  */
  pll1_fract_div_t                      pll1_fract_div;                      //PLL1FRACR;      /*!< RCC PLL1 Fractional Divider Configuration Register,                      Address offset: 0x34  */
  pll2_divs_t                           pll2_divs;                           //PLL2DIVR;       /*!< RCC PLL2 Dividers Configuration Register,                                Address offset: 0x38  */
  pll2_fract_div_t                      pll2_fract_div;                      //PLL2FRACR;      /*!< RCC PLL2 Fractional Divider Configuration Register,                      Address offset: 0x3C  */
  pll3_divs_t                           pll3_divs;                           //PLL3DIVR;       /*!< RCC PLL3 Dividers Configuration Register,                                Address offset: 0x40  */
  pll3_fract_div_t                      pll3_fract_div;                      //PLL3FRACR;      /*!< RCC PLL3 Fractional Divider Configuration Register,                      Address offset: 0x44  */
  const uint32_t                        reserved3;                                             /*!< Reserved,                                                                Address offset: 0x48  */

  d1_kernel_clock_config_t              d1_kernel_clock_config;              //D1CCIPR;       /*!< RCC Domain 1 Kernel Clock Configuration Register                         Address offset: 0x4C  */
  d2_kernel_clock_config_1_t            d2_kernel_clock_config_1;            //D2CCIP1R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x50  */
  d2_kernel_clock_config_2_t            d2_kernel_clock_config_2;            //D2CCIP2R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x54  */
  d3_kernel_clock_config_t              d3_kernel_clock_config;              //D3CCIPR;       /*!< RCC Domain 3 Kernel Clock Configuration Register                         Address offset: 0x58  */
  const uint32_t                        reserved4;                                             /*!< Reserved,                                                                Address offset: 0x5C  */
#if 0
  clock_source_interrupt_enable_t       clock_source_interrupt_enable;       //CIER;          /*!< RCC Clock Source Interrupt Enable Register                               Address offset: 0x60  */
  clock_source_interrupt_flag_t         clock_source_interrupt_flag;         //CIFR;          /*!< RCC Clock Source Interrupt Flag Register                                 Address offset: 0x64  */
  clock_source_interrupt_clear_t        clock_source_interrupt_clear;        //CICR;          /*!< RCC Clock Source Interrupt Clear Register                                Address offset: 0x68  */
  const uint32_t                        reserved5;                                            /*!< Reserved,                                                                Address offset: 0x6C  */
  vswitch_backup_domain_control_t       vswitch_backup_domain_control;       //BDCR;          /*!< RCC Vswitch Backup Domain Control Register,                              Address offset: 0x70  */
  clock_control_status_t                clock_control_status;                //CSR;           /*!< RCC clock control & status register,                                     Address offset: 0x74  */
  const uint32_t                        reserved6;                                            /*!< Reserved,                                                                Address offset: 0x78  */
  ahb3_peripheral_reset_t               ahb3_peripheral_reset;               //AHB3RSTR;       /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x7C  */
  ahb1_peripheral_reset_t               ahb1_peripheral_reset;               //AHB1RSTR;       /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x80  */
  ahb2_peripheral_reset_t               ahb2_peripheral_reset;               //AHB2RSTR;       /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x84  */
  ahb4_peripheral_reset_t               ahb4_peripheral_reset;               //AHB4RSTR;       /*!< RCC AHB4 peripheral reset register,                                      Address offset: 0x88  */
  apb3_peripheral_reset_t               apb3_peripheral_reset;               //APB3RSTR;       /*!< RCC APB3 peripheral reset register,                                      Address offset: 0x8C  */
  apb1_low_peripheral_reset_t           apb1_low_peripheral_reset;           //APB1LRSTR;      /*!< RCC APB1 peripheral reset Low Word register,                             Address offset: 0x90  */
  apb1_high_peripheral_reset_t          apb1_high_peripheral_reset;          //APB1HRSTR;      /*!< RCC APB1 peripheral reset High Word register,                            Address offset: 0x94  */
  apb2_peripheral_reset_t               apb2_peripheral_reset;               //APB2RSTR;       /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x98  */
  apb4_peripheral_reset_t               apb4_peripheral_reset;               //APB4RSTR;       /*!< RCC APB4 peripheral reset register,                                      Address offset: 0x9C  */
  global_control_t                      global_control;                      //GCR;            /*!< RCC RCC Global Control  Register,                                        Address offset: 0xA0  */
  const uint32_t                        reserved7;                                            //*!< Reserved,                                                                Address offset: 0xA4  */
  d3_autonomous_mode_t                  d3_autonomous_mode;                  //D3AMR;          /*!< RCC Domain 3 Autonomous Mode Register,                                   Address offset: 0xA8  */
  const uint32_t                        reserved8[9];                                          /*!< Reserved, 0xAC-0xCC                                                      Address offset: 0xAC  */
  reset_status_t                        reset_status;                        //RSR;            /*!< RCC Reset status register,                                               Address offset: 0xD0  */
  ahb3_peripheral_clock_t               ahb3_peripheral_clock;               //AHB3ENR;        /*!< RCC AHB3 peripheral clock  register,                                     Address offset: 0xD4  */
  ahb1_peripheral_clock_t               ahb1_peripheral_clock;               //AHB1ENR;        /*!< RCC AHB1 peripheral clock  register,                                     Address offset: 0xD8  */
  ahb2_peripheral_clock_t               ahb2_peripheral_clock;               //AHB2ENR;        /*!< RCC AHB2 peripheral clock  register,                                     Address offset: 0xDC  */
  ahb4_peripheral_clock_t               ahb4_peripheral_clock;               //AHB4ENR;        /*!< RCC AHB4 peripheral clock  register,                                     Address offset: 0xE0  */
  apb3_peripheral_clock_t               apb3_peripheral_clock;               //APB3ENR;        /*!< RCC APB3 peripheral clock  register,                                     Address offset: 0xE4  */
  apb1_low_peripheral_clock_t           apb1_low_peripheral_clock;           //APB1LENR;       /*!< RCC APB1 peripheral clock  Low Word register,                            Address offset: 0xE8  */
  apb1_high_peripheral_clock_t          apb1_high_peripheral_clock;          //APB1HENR;       /*!< RCC APB1 peripheral clock  High Word register,                           Address offset: 0xEC  */
  apb2_peripheral_clock_t               apb2_peripheral_clock;               //APB2ENR;        /*!< RCC APB2 peripheral clock  register,                                     Address offset: 0xF0  */
  apb4_peripheral_clock_t               apb4_peripheral_clock;               //APB4ENR;        /*!< RCC APB4 peripheral clock  register,                                     Address offset: 0xF4  */
  const uint32_t                        reserved9                                              /*!< Reserved,                                                                Address offset: 0xF8  */
  ahb3_peripheral_sleep_clock_t         ahb3_peripheral_sleep_clock;         //AHB3LPENR;      /*!< RCC AHB3 peripheral sleep clock  register,                               Address offset: 0xFC  */
  ahb1_peripheral_sleep_clock_t         ahb1_peripheral_sleep_clock;         //AHB1LPENR;      /*!< RCC AHB1 peripheral sleep clock  register,                               Address offset: 0x100 */
  ahb2_peripheral_sleep_clock_t         ahb2_peripheral_sleep_clock;         //AHB2LPENR;      /*!< RCC AHB2 peripheral sleep clock  register,                               Address offset: 0x104 */
  ahb4_peripheral_sleep_clock_t         ahb4_peripheral_sleep_clock;         //AHB4LPENR;      /*!< RCC AHB4 peripheral sleep clock  register,                               Address offset: 0x108 */
  apb3_peripheral_sleep_clock_t         apb3_peripheral_sleep_clock;         //APB3LPENR;      /*!< RCC APB3 peripheral sleep clock  register,                               Address offset: 0x10C */
  apb1_low_peripheral_sleep_clock_t     apb1_low_peripheral_sleep_clock;     //APB1LLPENR;     /*!< RCC APB1 peripheral sleep clock  Low Word register,                      Address offset: 0x110 */
  apb1_high_peripheral_sleep_clock_t    apb1_high_peripheral_sleep_clock;    //APB1HLPENR;     /*!< RCC APB1 peripheral sleep clock  High Word register,                     Address offset: 0x114 */
  apb2_peripheral_sleep_clock_t         apb2_peripheral_sleep_clock;         //APB2LPENR;      /*!< RCC APB2 peripheral sleep clock  register,                               Address offset: 0x118 */
  apb4_peripheral_sleep_clock_t         apb4_peripheral_sleep_clock;         //APB4LPENR;      /*!< RCC APB4 peripheral sleep clock  register,                               Address offset: 0x11C */
  const uint32_t                        reserved10[4];                                         /*!< Reserved, 0x120-0x12C                                                    Address offset: 0x120 */

#endif

  struct system_init_profile_t // pwr, clocs, etc
     {
#if 0
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
#endif
  };


#if 0

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


  inline uint32_t sys_clock_freq()
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

   inline uint32_t cyc2us(const uint32_t cycles , const uint32_t scf) { NRO return cycles * 1000000.0f / scf; }
   inline uint32_t cyc2us(const uint32_t cycles ) { NRO return cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2hz(const uint32_t cycles ) { NRO return 1000000.0f / cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2khz(const uint32_t cycles ) { NRO return 1000.0f / cyc2us(cycles , sys_clock_freq()); }
   inline float    cyc2mhz(const uint32_t cycles ) { NRO return 1.0f / cyc2us(cycles , sys_clock_freq()); }


   inline uint64_t cyc2ns(const uint32_t cycles , const uint32_t scf) {  NRO return ((uint64_t)cycles * (uint64_t)1000000000) / scf; }
   inline uint64_t cyc2ns(const uint32_t cycles ) { NRO return cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2khz(const uint32_t cycles ) { NRO return 1000000.0d / cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2mhz(const uint32_t cycles ) { NRO return 1000.0d / cyc2ns(cycles , sys_clock_freq()); }
   //inline double   cyc2ghz(const uint32_t cycles ) { NRO return 1.0d / cyc2ns(cycles , sys_clock_freq()); }


   inline void     us_cnt_start() { dwt.cyc_counter_start(); }
   inline uint32_t us_cnt_stop()  { return cyc2us(dwt.cyc_counter_stop()); }
   inline uint32_t us_cnt_stop(const uint32_t scf)  { return cyc2us(dwt.cyc_counter_stop(),scf); }

   inline void     ns_cnt_start() { dwt.cyc_counter_start(); }
   inline uint64_t ns_cnt_stop()  { return cyc2ns(dwt.cyc_counter_stop()); }
   inline uint64_t ns_cnt_stop(const uint32_t scf)  { return cyc2ns(dwt.cyc_counter_stop(),scf); }
#endif

} ;

static rcc_t  &rcc   = *((rcc_t*) rcc_addr);

}  // stm32h7

using namespace stm32h7 ;

#endif /* __RCC++_H__ */
