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

namespace stm32l0
{

  // необходимая задержка перед использованием переферии после включения тактирования
	// Cortex-M0/0+ (errata):
	// AHB: 1 AHB cycle
	// APB: No delay
  inline void ahb_clock_enable_delay()  { nop(); }


struct rcc_t
{
  struct clock_control_t : public read_write_32_t
  {
    struct hsi_t                     { enum enum_t { offset=0,  mask=1, off=0 , on } ; } ;
    struct hsi_kernel_t              { enum enum_t { offset=1,  mask=1, off=0 , on } ; } ;
    struct hsi_ready_t               { enum enum_t { offset=2,  mask=1, not_ready=0 , ready } ; } ;
    struct hsi_div4_t                { enum enum_t { offset=3,  mask=1, disable=0 , enable } ; } ;
    struct hsi_div4_ready_t          { enum enum_t { offset=4,  mask=1, not_ready=0 , ready } ; } ;
    struct hsi_output_t              { enum enum_t { offset=5,  mask=1, disable=0 , enable } ; } ;
    struct msi_t                     { enum enum_t { offset=8,  mask=1, off=0 , on } ; } ;
    struct msi_ready_t               { enum enum_t { offset=9,  mask=1, not_ready=0 , ready } ; } ;
    struct hse_t                     { enum enum_t { offset=16, mask=1, off=0 , on } ; } ;
    struct hse_ready_t               {nop enum enum_t { offset=17, mask=1, not_ready=0 , ready } ; } ;
    struct hse_clock_bypass_t        { enum enum_t { offset=18, mask=1, off=0 , on } ; } ;
    struct clock_security_system_t   { enum enum_t { offset=19, mask=1, disable=0 , enable} ; } ;
    struct rtc_prescaler_t           { enum enum_t { offset=20, mask=0b11, div2=0, div4, div8, div16} ; } ;
    struct pll_t                     { enum enum_t { offset=24, mask=1, off=0 , on } ; } ;
    struct pll_ready_t               { enum enum_t { offset=25, mask=1, not_ready=0 , ready } ; } ;
  };

  inline  void hsi( const clock_control_t::hsi_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hsi_off(){  clock_control.rmw( clock_control_t::hsi_t::off) ;}
  inline  void hsi_on() {  clock_control.rmw( clock_control_t::hsi_t::on) ;}
  inline  auto hsi() const {  return clock_control.rd<clock_control_t::hsi_t> ();}

  inline  void hsi_kernel( const clock_control_t::hsi_kernel_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void hsi_kernel_off(){  clock_control.rmw( clock_control_t::hsi_kernel_t::off) ;}
  inline  void hsi_kernel_on() {  clock_control.rmw( clock_control_t::hsi_kernel_t::on) ;}
  inline  auto hsi_kernel() const {  return clock_control.rd<clock_control_t::hsi_kernel_t> ();}

  inline  auto hsi_ready() const {  return clock_control.rd<clock_control_t::hsi_ready_t> ();}
  inline  void hsi_ready_wait() const  { while ( hsi_ready() == clock_control_t::hsi_ready_t::not_ready)  {} ; }

  inline  void hsi_div4(const clock_control_t::hsi_div4_t::enum_t val){  clock_control.rmw( (clock_control_t::hsi_div4_t::enum_t)val) ;}
  inline  void hsi_div4_disable(){  clock_control.rmw( clock_control_t::hsi_div4_t::disable) ;}
  inline  void hsi_div4_enable() {  clock_control.rmw( clock_control_t::hsi_div4_t::enable) ;}
  inline  auto hsi_div4(){  return clock_control.rd<clock_control_t::hsi_div4_t> ();}

  inline  auto hsi_div4_ready() const {  return clock_control.rd<clock_control_t::hsi_div4_ready_t> ();}
  inline  void hsi_div4_ready_wait() const  { while ( hsi_div4_ready() == clock_control_t::hsi_div4_ready_t::not_ready)  {} ; }

  inline  void hsi_output(const clock_control_t::hsi_output_t::enum_t val){  clock_control.rmw( (clock_control_t::hsi_output_t::enum_t)val) ;}
  inline  void hsi_output_disable(){  clock_control.rmw( clock_control_t::hsi_output_t::disable) ;}
  inline  void hsi_output_enable() {  clock_control.rmw( clock_control_t::hsi_output_t::enable) ;}
  inline  auto hsi_output(){  return clock_control.rd<clock_control_t::hsi_output_t> ();}

  inline  void msi( const clock_control_t::msi_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void msi_off(){  clock_control.rmw( clock_control_t::msi_t::off) ;}
  inline  void msi_on() {  clock_control.rmw( clock_control_t::msi_t::on) ;}
  inline  auto msi() const {  return clock_control.rd<clock_control_t::msi_t> ();}

  inline  auto msi_ready() const {  return clock_control.rd<clock_control_t::msi_ready_t> ();}
  inline  void msi_ready_wait() const  { while ( msi_ready() == clock_control_t::msi_ready_t::not_ready)  {} ; }

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

  inline  void rtc_prescaler( const clock_control_t::rtc_prescaler_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void rtc_prescaler_div2() {  clock_control.rmw( clock_control_t::rtc_prescaler_t::div2) ;}
  inline  void rtc_prescaler_div4() {  clock_control.rmw( clock_control_t::rtc_prescaler_t::div4) ;}
  inline  void rtc_prescaler_div8() {  clock_control.rmw( clock_control_t::rtc_prescaler_t::div8) ;}
  inline  void rtc_prescaler_div16() {  clock_control.rmw( clock_control_t::rtc_prescaler_t::div16) ;}
  inline  auto rtc_prescaler() const {  return clock_control.rd<clock_control_t::rtc_prescaler_t> ();}

  inline  void pll( const clock_control_t::pll_t::enum_t val){  clock_control.rmw(val) ;}
  inline  void pll_off(){  clock_control.rmw( clock_control_t::pll_t::off) ;}
  inline  void pll_on() {  clock_control.rmw( clock_control_t::pll_t::on) ;}
  inline  auto pll() const {  return clock_control.rd<clock_control_t::pll_t> ();}

  inline  auto pll_ready() const {  return clock_control.rd<clock_control_t::pll_ready_t> ();}
  inline  void pll_ready_wait() const { while ( pll_ready() == clock_control_t::pll_ready_t::not_ready)  {} ; }

  struct internal_clock_sources_calibration_t : public read_write_32_t
  {
    struct hsi_calibration_t   { enum enum_t { offset=0,  mask=0xff } ; } ;
    struct hsi_trim_t          { enum enum_t { offset=8,  mask=0b11111 } ; } ;
    struct msi_clock_range_t   { enum enum_t { offset=13, mask=0b111, range_0_to_65khz=0, range_65khz_to_131khz,  range_131khz_to_264khz, range_264khz_to_524khz, range_524khz_to_1mhz, range_1mhz_to_2mhz, range_2mhz_to_4mhz } ; } ;
    struct msi_calibration_t   { enum enum_t { offset=16, mask=0xff } ; } ;
    struct msi_trim_t          { enum enum_t { offset=24, mask=0xff } ; } ;
  };

  inline  auto hsi_calibration() const {  return internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::hsi_calibration_t> ();}

  inline  void hsi_trim( const uint8_t val){  internal_clock_sources_calibration.rmw((internal_clock_sources_calibration_t::hsi_trim_t::enum_t)val) ;}
  inline  auto hsi_trim() const {  return (uint8_t)internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::hsi_trim_t> ();}

  inline  void msi_clock_range_t( const internal_clock_sources_calibration_t::msi_clock_range_t::enum_t val){  internal_clock_sources_calibration.rmw(val) ;}
  inline  void msi_clock_range_0_to_65khz()      {  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_0_to_65khz) ;}
  inline  void msi_clock_range_65khz_to_131khz() {  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_65khz_to_131khz) ;}
  inline  void msi_clock_range_131khz_to_264khz(){  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_131khz_to_264khz) ;}
  inline  void msi_clock_range_264khz_to_524khz(){  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_264khz_to_524khz) ;}
  inline  void msi_clock_range_524khz_to_1mhz()  {  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_524khz_to_1mhz) ;}
  inline  void msi_clock_range_1mhz_to_2mhz()    {  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_1mhz_to_2mhz) ;}
  inline  void msi_clock_range_2mhz_to_4mhz()    {  internal_clock_sources_calibration.rmw( internal_clock_sources_calibration_t::msi_clock_range_t::range_2mhz_to_4mhz) ;}
  inline  auto msi_clock_range_t() const {  return internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::msi_clock_range_t> ();}

  inline  auto msi_calibration() const {  return internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::msi_calibration_t> ();}

  inline  void msi_tri( const uint8_t val){  internal_clock_sources_calibration.rmw((internal_clock_sources_calibration_t::msi_trim_t::enum_t)val) ;}
  inline  auto msi_trim() const {  return (uint8_t)internal_clock_sources_calibration.rd<internal_clock_sources_calibration_t::msi_trim_t> ();}

  struct clock_config_t : public read_write_32_t
  {
    struct sys_clock_t                     { enum enum_t { offset=0,  mask=0b11, msi=0, hsi, hse, pll } ; } ;
    struct sys_clock_state_t               { enum enum_t { offset=2,  mask=0b11, msi=0, hsi, hse, pll } ; } ;
    struct ahb_prescaler_t                 { enum enum_t { offset=4,  mask=0b1111, no_div=0b0000, div2=0b1000, div4=0b1001, div8=0b1010, div16=0b1011, div64=0b1100, div128=0b1101, div256=0b1110, div512=0b1111 } ; } ;
    struct apb1_prescaler_t                { enum enum_t { offset=8,  mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct apb2_prescaler_t                { enum enum_t { offset=11, mask=0b111,  no_div=0b00, div2=0b100, div4=0b101, div8=0b110, div16=0b111 } ; } ;
    struct wake_up_from_stop_clock_t       { enum enum_t { offset=15, mask=1, msi=0, hsi } ; } ;
    struct pll_source_t                    { enum enum_t { offset=16, mask=1, hsi=0, hse } ; } ;
    struct pll_mul_t                       { enum enum_t { offset=18, mask=0b1111, mul3=0, mul4, mul6, mul8, mul12, mul16, mul24, mul32, mul48 } ; } ;
    struct pll_div_t                       { enum enum_t { offset=22, mask=0b11, div2=1, div3, div4 } ; } ;
    struct mco_clock_output_t              { enum enum_t { offset=24, mask=0b1111, no_source=0, sysclk, hsi, msi, hse, pll, lsi, lse } ; } ;
    struct mco_clock_prescaler_t           { enum enum_t { offset=28, mask=0b1111, no_div=0, div2, div4, div8, div16 } ; } ;
  } ;

  inline void sys_clock( const clock_config_t::sys_clock_t::enum_t val) { clock_config.rmw(val) ; }
  inline void sys_clock_msi() { clock_config.rmw(clock_config_t::sys_clock_t::msi) ; }
  inline void sys_clock_hsi() { clock_config.rmw(clock_config_t::sys_clock_t::hsi) ; }
  inline void sys_clock_hse() { clock_config.rmw(clock_config_t::sys_clock_t::hse) ; }
  inline void sys_clock_pll() { clock_config.rmw(clock_config_t::sys_clock_t::pll) ; }
  inline auto sys_clock() const { return clock_config.rd<clock_config_t::sys_clock_t>() ; }

  inline auto sys_clock_state()  const { return clock_config.rd<clock_config_t::sys_clock_state_t>() ; }
  inline void sys_clock_state_msi_wait() const { while ( sys_clock_state() != clock_config_t::sys_clock_state_t::msi ){ nop(); }; }
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

  inline void wake_up_from_stop_clock( const clock_config_t::wake_up_from_stop_clock_t::enum_t val) { clock_config.rmw(val) ; }
  inline void wake_up_from_stop_clock_msi() { clock_config.rmw(clock_config_t::wake_up_from_stop_clock_t::msi) ; }
  inline void wake_up_from_stop_clock_hsi() { clock_config.rmw(clock_config_t::wake_up_from_stop_clock_t::hsi) ; }
  inline auto wake_up_from_stop_clock() const { return clock_config.rd<clock_config_t::wake_up_from_stop_clock_t>() ; }

  inline void pll_source( const clock_config_t::pll_source_t::enum_t val){  clock_config.rmw(val) ;}
  inline void pll_source_hsi(){  clock_config.rmw(clock_config_t::pll_source_t::hsi) ;}
  inline void pll_source_hse(){  clock_config.rmw(clock_config_t::pll_source_t::hse) ;}
  inline auto pll_source() const {  return  clock_config.rd<clock_config_t::pll_source_t> ();}

  inline void pll_mul( const clock_config_t::pll_mul_t::enum_t val){  clock_config.rmw(val) ;}
  inline void pll_mul3(){ clock_config.rmw(clock_config_t::pll_mul_t::mul3) ;}
  inline void pll_mul4(){ clock_config.rmw(clock_config_t::pll_mul_t::mul4) ;}
  inline void pll_mul6(){ clock_config.rmw(clock_config_t::pll_mul_t::mul6) ;}
  inline void pll_mul8(){ clock_config.rmw(clock_config_t::pll_mul_t::mul8) ;}
  inline void pll_mul12(){ clock_config.rmw(clock_config_t::pll_mul_t::mul12) ;}
  inline void pll_mul16(){ clock_config.rmw(clock_config_t::pll_mul_t::mul16) ;}
  inline void pll_mul24(){ clock_config.rmw(clock_config_t::pll_mul_t::mul24) ;}
  inline void pll_mul32(){ clock_config.rmw(clock_config_t::pll_mul_t::mul32) ;}
  inline void pll_mul48(){ clock_config.rmw(clock_config_t::pll_mul_t::mul48) ;}
  inline auto pll_mul() const {  return  clock_config.rd<clock_config_t::pll_mul_t> ();}

  inline void pll_div( const clock_config_t::pll_div_t::enum_t val){  clock_config.rmw(val) ;}
  inline void pll_div2(){ clock_config.rmw(clock_config_t::pll_div_t::div2) ;}
  inline void pll_div3(){ clock_config.rmw(clock_config_t::pll_div_t::div3) ;}
  inline void pll_div4(){ clock_config.rmw(clock_config_t::pll_div_t::div4) ;}
  inline auto pll_div() const {  return  clock_config.rd<clock_config_t::pll_div_t> ();}

  inline void mco_clock_output( const clock_config_t::mco_clock_output_t::enum_t val){  clock_config.rmw(val) ;}
  inline void mco_clock_output_no_source(){ clock_config.rmw(clock_config_t::mco_clock_output_t::no_source) ;}
  inline void mco_clock_output_sysclk(){ clock_config.rmw(clock_config_t::mco_clock_output_t::sysclk) ;}
  inline void mco_clock_output_hsi(){ clock_config.rmw(clock_config_t::mco_clock_output_t::hsi) ;}
  inline void mco_clock_output_msi(){ clock_config.rmw(clock_config_t::mco_clock_output_t::msi) ;}
  inline void mco_clock_output_hse(){ clock_config.rmw(clock_config_t::mco_clock_output_t::hse) ;}
  inline void mco_clock_output_pll(){ clock_config.rmw(clock_config_t::mco_clock_output_t::pll) ;}
  inline void mco_clock_output_lsi(){ clock_config.rmw(clock_config_t::mco_clock_output_t::lsi) ;}
  inline void mco_clock_output_lse(){ clock_config.rmw(clock_config_t::mco_clock_output_t::lse) ;}
  inline auto mco_clock_output() const {  return  clock_config.rd<clock_config_t::mco_clock_output_t> ();}

  inline void mco_clock_prescaler( const clock_config_t::mco_clock_prescaler_t::enum_t val){  clock_config.rmw(val) ;}
  inline void mco_clock_prescaler_no_div(){ clock_config.rmw(clock_config_t::mco_clock_prescaler_t::no_div) ;}
  inline void mco_clock_prescaler_div2(){ clock_config.rmw(clock_config_t::mco_clock_prescaler_t::div2) ;}
  inline void mco_clock_prescaler_div4(){ clock_config.rmw(clock_config_t::mco_clock_prescaler_t::div4) ;}
  inline void mco_clock_prescaler_div8(){ clock_config.rmw(clock_config_t::mco_clock_prescaler_t::div8) ;}
  inline void mco_clock_prescaler_div16(){ clock_config.rmw(clock_config_t::mco_clock_prescaler_t::div16) ;}
  inline auto mco_clock_prescaler() const {  return  clock_config.rd<clock_config_t::mco_clock_prescaler_t> ();}

  struct clock_interrupt_state_t : public read_write_32_t
    {
      struct lsi_ready_interupt_t  { enum enum_t { offset=0,  mask=0b1, disable=0, enable } ; } ;
      struct lse_ready_interupt_t  { enum enum_t { offset=1,  mask=0b1, disable=0, enable } ; } ;
      struct hsi_ready_interupt_t  { enum enum_t { offset=2,  mask=0b1, disable=0, enable } ; } ;
      struct hse_ready_interupt_t  { enum enum_t { offset=3,  mask=0b1, disable=0, enable } ; } ;
      struct pll_ready_interupt_t  { enum enum_t { offset=4,  mask=0b1, disable=0, enable } ; } ;
      struct msi_ready_interupt_t  { enum enum_t { offset=5,  mask=0b1, disable=0, enable } ; } ;
      struct security_system_interupt_t  { enum enum_t { offset=7,  mask=0b1, disable=0, enable } ; } ;
    }   ;

  inline void lsi_ready_interupt( const clock_interrupt_state_t::lsi_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void lsi_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::lsi_ready_interupt_t::disable) ; }
  inline void lsi_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::lsi_ready_interupt_t::enable) ; }
  inline auto lsi_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::lsi_ready_interupt_t>() ; }

  inline void lse_ready_interupt( const clock_interrupt_state_t::lse_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void lse_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::lse_ready_interupt_t::disable) ; }
  inline void lse_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::lse_ready_interupt_t::enable) ; }
  inline auto lse_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::lse_ready_interupt_t>() ; }

  inline void hsi_ready_interupt( const clock_interrupt_state_t::hsi_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void hsi_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::hsi_ready_interupt_t::disable) ; }
  inline void hsi_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::hsi_ready_interupt_t::enable) ; }
  inline auto hsi_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::hsi_ready_interupt_t>() ; }

  inline void hse_ready_interupt( const clock_interrupt_state_t::hse_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void hse_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::hse_ready_interupt_t::disable) ; }
  inline void hse_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::hse_ready_interupt_t::enable) ; }
  inline auto hse_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::hse_ready_interupt_t>() ; }

  inline void pll_ready_interupt( const clock_interrupt_state_t::pll_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void pll_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::pll_ready_interupt_t::disable) ; }
  inline void pll_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::pll_ready_interupt_t::enable) ; }
  inline auto pll_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::pll_ready_interupt_t>() ; }

  inline void msi_ready_interupt( const clock_interrupt_state_t::msi_ready_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void msi_ready_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::msi_ready_interupt_t::disable) ; }
  inline void msi_ready_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::msi_ready_interupt_t::enable) ; }
  inline auto msi_ready_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::msi_ready_interupt_t>() ; }

  inline void security_system_interupt( const clock_interrupt_state_t::security_system_interupt_t::enum_t val) { clock_interrupt_state.rmw(val) ; }
  inline void security_system_interupt_disable() { clock_interrupt_state.rmw(clock_interrupt_state_t::security_system_interupt_t::disable) ; }
  inline void security_system_interupt_enable() { clock_interrupt_state.rmw(clock_interrupt_state_t::security_system_interupt_t::enable) ; }
  inline auto security_system_interupt() const  { return clock_interrupt_state.rd<clock_interrupt_state_t::security_system_interupt_t>() ; }


  struct clock_interrupt_flag_t : public read_write_32_t
  {
    struct lsi_ready_interupt_flag_t  { enum enum_t { offset=0,  mask=0b1, no_caused=0, caused } ; } ;
    struct lse_ready_interupt_flag_t  { enum enum_t { offset=1,  mask=0b1, no_caused=0, caused } ; } ;
    struct hsi_ready_interupt_flag_t  { enum enum_t { offset=2,  mask=0b1, no_caused=0, caused } ; } ;
    struct hse_ready_interupt_flag_t  { enum enum_t { offset=3,  mask=0b1, no_caused=0, caused } ; } ;
    struct pll_ready_interupt_flag_t  { enum enum_t { offset=4,  mask=0b1, no_caused=0, caused } ; } ;
    struct msi_ready_interupt_flag_t  { enum enum_t { offset=5,  mask=0b1, no_caused=0, caused } ; } ;
    struct security_system_lse_interupt_flag_t  { enum enum_t { offset=7,  mask=0b1, no_caused=0, caused } ; } ;
    struct security_system_hse_interupt_flag_t  { enum enum_t { offset=8,  mask=0b1, no_caused=0, caused } ; } ;
  };

  inline auto lsi_ready_interupt_flag() const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::lsi_ready_interupt_flag_t>() ; }
  inline auto lse_ready_interupt_flag() const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::lse_ready_interupt_flag_t>() ; }
  inline auto hsi_ready_interupt_flag() const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::hsi_ready_interupt_flag_t>() ; }
  inline auto hse_ready_interupt_flag() const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::hse_ready_interupt_flag_t>() ; }
  inline auto pll_ready_interupt_flag()  const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::pll_ready_interupt_flag_t>() ; }
  inline auto msi_ready_interupt_flag() const { return clock_interrupt_flag.rd<clock_interrupt_flag_t::msi_ready_interupt_flag_t>() ; }
  inline auto security_system_lse_interupt_flag() const  { return clock_interrupt_flag.rd<clock_interrupt_flag_t::security_system_lse_interupt_flag_t>() ; }
  inline auto security_system_hse_interupt_flag() const  { return clock_interrupt_flag.rd<clock_interrupt_flag_t::security_system_hse_interupt_flag_t>() ; }

  struct clock_interrupt_clear_t : public read_write_32_t
  {
    struct lsi_ready_interupt_clear_t  { enum enum_t { offset=0,  mask=0b1, no_effect=0, perform } ; } ;
    struct lse_ready_interupt_clear_t  { enum enum_t { offset=1,  mask=0b1, no_effect=0, perform } ; } ;
    struct hsi_ready_interupt_clear_t  { enum enum_t { offset=2,  mask=0b1, no_effect=0, perform } ; } ;
    struct hse_ready_interupt_clear_t  { enum enum_t { offset=3,  mask=0b1, no_effect=0, perform } ; } ;
    struct pll_ready_interupt_clear_t  { enum enum_t { offset=4,  mask=0b1, no_effect=0, perform } ; } ;
    struct msi_ready_interupt_clear_t  { enum enum_t { offset=5,  mask=0b1, no_effect=0, perform } ; } ;
    struct security_system_lse_interupt_clear_t  { enum enum_t { offset=7,  mask=0b1, no_effect=0, perform } ; } ;
    struct security_system_hse_interupt_clear_t  { enum enum_t { offset=8,  mask=0b1, no_effect=0, perform } ; } ;
  };

  inline void lsi_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::lsi_ready_interupt_clear_t::perform) ; }
  inline void lse_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::lse_ready_interupt_clear_t::perform) ; }
  inline void hsi_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::hsi_ready_interupt_clear_t::perform) ; }
  inline void hse_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::hse_ready_interupt_clear_t::perform) ; }
  inline void pll_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::pll_ready_interupt_clear_t::perform) ; }
  inline void msi_ready_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::msi_ready_interupt_clear_t::perform) ; }
  inline void security_system_lse_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::security_system_lse_interupt_clear_t::perform) ; }
  inline void security_system_hse_interupt_clear() { clock_interrupt_clear.rmw(clock_interrupt_clear_t::security_system_hse_interupt_clear_t::perform) ; }


  struct gpio_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;

    struct gpioa_reset_state_t  { enum enum_t { offset=0,  mask=0b1, no_reset=0, reset } ; } ;
    struct gpiob_reset_state_t  { enum enum_t { offset=1,  mask=0b1, no_reset=0, reset } ; } ;
    struct gpioc_reset_state_t  { enum enum_t { offset=2,  mask=0b1, no_reset=0, reset } ; } ;
    struct gpiod_reset_state_t  { enum enum_t { offset=3,  mask=0b1, no_reset=0, reset } ; } ;
    struct gpioe_reset_state_t  { enum enum_t { offset=4,  mask=0b1, no_reset=0, reset } ; } ;
    struct gpioh_reset_state_t  { enum enum_t { offset=7,  mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t { gpioa=gpioa_reset_state_t::offset ,
                        gpiob=gpiob_reset_state_t::offset ,
    			gpioc=gpioc_reset_state_t::offset ,
    			gpiod=gpiod_reset_state_t::offset ,
    			gpioe=gpioe_reset_state_t::offset ,
    			gpioh=gpioh_reset_state_t::offset ,
                      } ;
  };

  inline void gpioa_reset_state( const gpio_reset_t::gpioa_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpioa_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpioa_reset_state_t::no_reset) ; }
  inline void gpioa_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpioa_reset_state_t::reset) ; }
  inline auto gpioa_reset_state() const  { return gpio_reset.rd<gpio_reset_t::gpioa_reset_state_t>() ; }
  inline void gpioa_reset() { gpioa_reset_state_reset() ; gpioa_reset_state_no_reset(); }

  inline void gpiob_reset_state( const gpio_reset_t::gpiob_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpiob_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpiob_reset_state_t::no_reset) ; }
  inline void gpiob_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpiob_reset_state_t::reset) ; }
  inline auto gpiob_reset_state()  const { return gpio_reset.rd<gpio_reset_t::gpiob_reset_state_t>() ; }
  inline void gpiob_reset() { gpiob_reset_state_reset() ; gpiob_reset_state_no_reset(); }

  inline void gpioc_reset_state( const gpio_reset_t::gpioc_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpioc_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpioc_reset_state_t::no_reset) ; }
  inline void gpioc_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpioc_reset_state_t::reset) ; }
  inline auto gpioc_reset_state()  const { return gpio_reset.rd<gpio_reset_t::gpioc_reset_state_t>() ; }
  inline void gpioc_reset() { gpioc_reset_state_reset() ; gpioc_reset_state_no_reset(); }

  inline void gpiod_reset_state( const gpio_reset_t::gpiod_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpiod_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpiod_reset_state_t::no_reset) ; }
  inline void gpiod_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpiod_reset_state_t::reset) ; }
  inline auto gpiod_reset_state() const  { return gpio_reset.rd<gpio_reset_t::gpiod_reset_state_t>() ; }
  inline void gpiod_reset() { gpiod_reset_state_reset() ; gpiod_reset_state_no_reset(); }

  inline void gpioe_reset_state( const gpio_reset_t::gpioe_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpioe_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpioe_reset_state_t::no_reset) ; }
  inline void gpioe_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpioe_reset_state_t::reset) ; }
  inline auto gpioe_reset_state() const  { return gpio_reset.rd<gpio_reset_t::gpioe_reset_state_t>() ; }
  inline void gpioe_reset() { gpioe_reset_state_reset() ; gpioe_reset_state_no_reset(); }

  inline void gpioh_reset_state( const gpio_reset_t::gpioh_reset_state_t::enum_t val) { gpio_reset.rmw(val) ; }
  inline void gpioh_reset_state_no_reset() { gpio_reset.rmw(gpio_reset_t::gpioh_reset_state_t::no_reset) ; }
  inline void gpioh_reset_state_reset() { gpio_reset.rmw(gpio_reset_t::gpioh_reset_state_t::reset) ; }
  inline auto gpioh_reset_state() const  { return gpio_reset.rd<gpio_reset_t::gpioh_reset_state_t>() ; }
  inline void gpioh_reset() { gpioh_reset_state_reset() ; gpioh_reset_state_no_reset(); }

  inline void state_reset(const gpio_reset_t::peripheral_t val) { gpio_reset.rmw( gpio_reset_t::reset,  val ) ; }
  inline void state_no_reset(const gpio_reset_t::peripheral_t val){ gpio_reset.rmw( gpio_reset_t::no_reset, val ) ; }
  inline void reset(const gpio_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct ahb_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct dma_reset_state_t              { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct memory_interface_reset_state_t { enum enum_t { offset=8, mask=0b1, no_reset=0, reset } ; } ;
    struct crc_reset_state_t              { enum enum_t { offset=12,mask=0b1, no_reset=0, reset } ; } ;
    struct crypt_reset_state_t            { enum enum_t { offset=24,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t {
			dma=dma_reset_state_t::offset,
			memory_interface=memory_interface_reset_state_t::offset,
			crc=crc_reset_state_t::offset,
			crypt=crypt_reset_state_t::offset,
                      } ;
  }  ;

  inline void dma_reset_state( const ahb_peripheral_reset_t::dma_reset_state_t::enum_t val) { ahb_peripheral_reset.rmw(val) ; }
  inline void dma_reset_state_no_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::dma_reset_state_t::no_reset) ; }
  inline void dma_reset_state_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::dma_reset_state_t::reset) ; }
  inline auto dma_reset_state() const  { return ahb_peripheral_reset.rd<ahb_peripheral_reset_t::dma_reset_state_t>() ; }
  inline void dma_reset() { dma_reset_state_reset() ; dma_reset_state_no_reset(); }

  inline void memory_interface_reset_state( const ahb_peripheral_reset_t::memory_interface_reset_state_t::enum_t val) { ahb_peripheral_reset.rmw(val) ; }
  inline void memory_interface_reset_state_no_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::memory_interface_reset_state_t::no_reset) ; }
  inline void memory_interface_reset_state_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::memory_interface_reset_state_t::reset) ; }
  inline auto memory_interface_reset_state() const  { return ahb_peripheral_reset.rd<ahb_peripheral_reset_t::memory_interface_reset_state_t>() ; }
  inline void memory_interface_reset() { memory_interface_reset_state_reset() ; memory_interface_reset_state_no_reset(); }

  inline void crc_reset_state( const ahb_peripheral_reset_t::crc_reset_state_t::enum_t val) { ahb_peripheral_reset.rmw(val) ; }
  inline void crc_reset_state_no_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::crc_reset_state_t::no_reset) ; }
  inline void crc_reset_state_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::crc_reset_state_t::reset) ; }
  inline auto crc_reset_state() const  { return ahb_peripheral_reset.rd<ahb_peripheral_reset_t::crc_reset_state_t>() ; }
  inline void crc_reset() { crc_reset_state_reset() ; crc_reset_state_no_reset(); }

  inline void crypt_reset_state( const ahb_peripheral_reset_t::crypt_reset_state_t::enum_t val) { ahb_peripheral_reset.rmw(val) ; }
  inline void crypt_reset_state_no_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::crypt_reset_state_t::no_reset) ; }
  inline void crypt_reset_state_reset() { ahb_peripheral_reset.rmw(ahb_peripheral_reset_t::crypt_reset_state_t::reset) ; }
  inline auto crypt_reset_state() const  { return ahb_peripheral_reset.rd<ahb_peripheral_reset_t::crypt_reset_state_t>() ; }
  inline void crypt_reset() { crypt_reset_state_reset() ; crypt_reset_state_no_reset(); }


  struct apb2_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct syscfg_reset_state_t { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct tim21_reset_state_t  { enum enum_t { offset=2, mask=0b1, no_reset=0, reset } ; } ;
    struct tim22_reset_state_t  { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct adc_reset_state_t    { enum enum_t { offset=9, mask=0b1, no_reset=0, reset } ; } ;
    struct spi1_reset_state_t   { enum enum_t { offset=12,mask=0b1, no_reset=0, reset } ; } ;
    struct usart1_reset_state_t { enum enum_t { offset=14,mask=0b1, no_reset=0, reset } ; } ;
    struct dbg_reset_state_t    { enum enum_t { offset=22,mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t {
                        syscfg=syscfg_reset_state_t::offset,
			tim21=tim21_reset_state_t::offset,
			tim22=tim22_reset_state_t::offset,
			adc=adc_reset_state_t::offset,
			spi1=spi1_reset_state_t::offset,
			usart1=usart1_reset_state_t::offset,
			dbg=dbg_reset_state_t::offset,
                      } ;
  }  ;

  inline void syscfg_reset_state( const apb2_peripheral_reset_t::syscfg_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void syscfg_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::no_reset) ; }
  inline void syscfg_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::syscfg_reset_state_t::reset) ; }
  inline auto syscfg_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::syscfg_reset_state_t>() ; }
  inline void syscfg_reset() { syscfg_reset_state_reset() ; syscfg_reset_state_no_reset(); }

  inline void tim21_reset_state( const apb2_peripheral_reset_t::tim21_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void tim21_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim21_reset_state_t::no_reset) ; }
  inline void tim21_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim21_reset_state_t::reset) ; }
  inline auto tim21_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim21_reset_state_t>() ; }
  inline void tim21_reset() { tim21_reset_state_reset() ; tim21_reset_state_no_reset(); }

  inline void tim22_reset_state( const apb2_peripheral_reset_t::tim22_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void tim22_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim22_reset_state_t::no_reset) ; }
  inline void tim22_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::tim22_reset_state_t::reset) ; }
  inline auto tim22_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::tim22_reset_state_t>() ; }
  inline void tim22_reset() { tim22_reset_state_reset() ; tim22_reset_state_no_reset(); }

  inline void adc_reset_state( const apb2_peripheral_reset_t::adc_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void adc_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::no_reset) ; }
  inline void adc_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::adc_reset_state_t::reset) ; }
  inline auto adc_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::adc_reset_state_t>() ; }
  inline void adc_reset() { adc_reset_state_reset() ; adc_reset_state_no_reset(); }

  inline void spi1_reset_state( const apb2_peripheral_reset_t::spi1_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void spi1_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::no_reset) ; }
  inline void spi1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::spi1_reset_state_t::reset) ; }
  inline auto spi1_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::spi1_reset_state_t>() ; }
  inline void spi1_reset() { spi1_reset_state_reset() ; spi1_reset_state_no_reset(); }

  inline void usart1_reset_state( const apb2_peripheral_reset_t::usart1_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void usart1_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::no_reset) ; }
  inline void usart1_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::usart1_reset_state_t::reset) ; }
  inline auto usart1_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::usart1_reset_state_t>() ; }
  inline void usart1_reset() { usart1_reset_state_reset() ; usart1_reset_state_no_reset(); }

  inline void dbg_reset_state( const apb2_peripheral_reset_t::dbg_reset_state_t::enum_t val) { apb2_peripheral_reset.rmw(val) ; }
  inline void dbg_reset_state_no_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dbg_reset_state_t::no_reset) ; }
  inline void dbg_reset_state_reset() { apb2_peripheral_reset.rmw(apb2_peripheral_reset_t::dbg_reset_state_t::reset) ; }
  inline auto dbg_reset_state() const  { return apb2_peripheral_reset.rd<apb2_peripheral_reset_t::dbg_reset_state_t>() ; }
  inline void dbg_reset() { dbg_reset_state_reset() ; dbg_reset_state_no_reset(); }

  struct apb1_peripheral_reset_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct tim2_reset_state_t { enum enum_t { offset=0, mask=0b1, no_reset=0, reset } ; } ;
    struct tim3_reset_state_t { enum enum_t { offset=1, mask=0b1, no_reset=0, reset } ; } ;
    struct tim6_reset_state_t { enum enum_t { offset=4, mask=0b1, no_reset=0, reset } ; } ;
    struct tim7_reset_state_t { enum enum_t { offset=5, mask=0b1, no_reset=0, reset } ; } ;
    struct wwdg_reset_state_t { enum enum_t { offset=11, mask=0b1, no_reset=0, reset } ; } ;
    struct spi2_reset_state_t { enum enum_t { offset=14, mask=0b1, no_reset=0, reset } ; } ;
    struct usart2_reset_state_t { enum enum_t { offset=17, mask=0b1, no_reset=0, reset } ; } ;
    struct lpuart1_reset_state_t { enum enum_t { offset=18, mask=0b1, no_reset=0, reset } ; } ;
    struct uart4_reset_state_t { enum enum_t { offset=19, mask=0b1, no_reset=0, reset } ; } ;
    struct usart5_reset_state_t { enum enum_t { offset=20, mask=0b1, no_reset=0, reset } ; } ;
    struct i2c1_reset_state_t { enum enum_t { offset=21, mask=0b1, no_reset=0, reset } ; } ;
    struct i2c2_reset_state_t { enum enum_t { offset=22, mask=0b1, no_reset=0, reset } ; } ;
    struct pwr_reset_state_t { enum enum_t { offset=28, mask=0b1, no_reset=0, reset } ; } ;
    struct i2c3_reset_state_t { enum enum_t { offset=30, mask=0b1, no_reset=0, reset } ; } ;
    struct lptim1_reset_state_t { enum enum_t { offset=31, mask=0b1, no_reset=0, reset } ; } ;

    enum peripheral_t {
                         tim2=tim2_reset_state_t::offset,
			 tim3=tim3_reset_state_t::offset,
                         tim6=tim6_reset_state_t::offset,
			 tim7=tim7_reset_state_t::offset,
			 wwdg=wwdg_reset_state_t::offset,
			 spi2=spi2_reset_state_t::offset,
			 usart2=usart2_reset_state_t::offset,
			 lpuart1=lpuart1_reset_state_t::offset,
			 uart4=uart4_reset_state_t::offset,
			 usart5=usart5_reset_state_t::offset,
			 i2c1=i2c1_reset_state_t::offset,
			 i2c2=i2c2_reset_state_t::offset,
			 pwr=pwr_reset_state_t::offset,
			 i2c3=i2c3_reset_state_t::offset,
			 lptim1=lptim1_reset_state_t::offset,
                      } ;
  }  ;

  inline void tim2_reset_state( const apb1_peripheral_reset_t::tim2_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void tim2_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::no_reset) ; }
  inline void tim2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim2_reset_state_t::reset) ; }
  inline auto tim2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim2_reset_state_t>() ; }
  inline void tim2_reset() { tim2_reset_state_reset() ; tim2_reset_state_no_reset(); }

  inline void tim3_reset_state( const apb1_peripheral_reset_t::tim3_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void tim3_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::no_reset) ; }
  inline void tim3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim3_reset_state_t::reset) ; }
  inline auto tim3_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim3_reset_state_t>() ; }
  inline void tim3_reset() { tim3_reset_state_reset() ; tim3_reset_state_no_reset(); }

  inline void tim6_reset_state( const apb1_peripheral_reset_t::tim6_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void tim6_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::no_reset) ; }
  inline void tim6_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim6_reset_state_t::reset) ; }
  inline auto tim6_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim6_reset_state_t>() ; }
  inline void tim6_reset() { tim6_reset_state_reset() ; tim6_reset_state_no_reset(); }

  inline void tim7_reset_state( const apb1_peripheral_reset_t::tim7_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void tim7_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::no_reset) ; }
  inline void tim7_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::tim7_reset_state_t::reset) ; }
  inline auto tim7_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::tim7_reset_state_t>() ; }
  inline void tim7_reset() { tim7_reset_state_reset() ; tim7_reset_state_no_reset(); }

  inline void wwdg_reset_state( const apb1_peripheral_reset_t::wwdg_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void wwdg_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::no_reset) ; }
  inline void wwdg_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::wwdg_reset_state_t::reset) ; }
  inline auto wwdg_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::wwdg_reset_state_t>() ; }
  inline void wwdg_reset() { wwdg_reset_state_reset() ; wwdg_reset_state_no_reset(); }

  inline void spi2_reset_state( const apb1_peripheral_reset_t::spi2_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void spi2_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::no_reset) ; }
  inline void spi2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::spi2_reset_state_t::reset) ; }
  inline auto spi2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::spi2_reset_state_t>() ; }
  inline void spi2_reset() { spi2_reset_state_reset() ; spi2_reset_state_no_reset(); }

  inline void usart2_reset_state( const apb1_peripheral_reset_t::usart2_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void usart2_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart2_reset_state_t::no_reset) ; }
  inline void usart2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart2_reset_state_t::reset) ; }
  inline auto usart2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::usart2_reset_state_t>() ; }
  inline void usart2_reset() { usart2_reset_state_reset() ; usart2_reset_state_no_reset(); }

  inline void lpuart1_reset_state( const apb1_peripheral_reset_t::lpuart1_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void lpuart1_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lpuart1_reset_state_t::no_reset) ; }
  inline void lpuart1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lpuart1_reset_state_t::reset) ; }
  inline auto lpuart1_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::lpuart1_reset_state_t>() ; }
  inline void lpuart1_reset() { lpuart1_reset_state_reset() ; lpuart1_reset_state_no_reset(); }

  inline void uart4_reset_state( const apb1_peripheral_reset_t::uart4_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void uart4_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::no_reset) ; }
  inline void uart4_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::uart4_reset_state_t::reset) ; }
  inline auto uart4_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::uart4_reset_state_t>() ; }
  inline void uart4_reset() { uart4_reset_state_reset() ; uart4_reset_state_no_reset(); }

  inline void usart5_reset_state( const apb1_peripheral_reset_t::usart5_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void usart5_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart5_reset_state_t::no_reset) ; }
  inline void usart5_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::usart5_reset_state_t::reset) ; }
  inline auto usart5_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::usart5_reset_state_t>() ; }
  inline void usart5_reset() { usart5_reset_state_reset() ; usart5_reset_state_no_reset(); }

  inline void i2c1_reset_state( const apb1_peripheral_reset_t::i2c1_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void i2c1_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::no_reset) ; }
  inline void i2c1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c1_reset_state_t::reset) ; }
  inline auto i2c1_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c1_reset_state_t>() ; }
  inline void i2c1_reset() { i2c1_reset_state_reset() ; i2c1_reset_state_no_reset(); }

  inline void i2c2_reset_state( const apb1_peripheral_reset_t::i2c2_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void i2c2_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::no_reset) ; }
  inline void i2c2_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c2_reset_state_t::reset) ; }
  inline auto i2c2_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c2_reset_state_t>() ; }
  inline void i2c2_reset() { i2c2_reset_state_reset() ; i2c2_reset_state_no_reset(); }

  inline void pwr_reset_state( const apb1_peripheral_reset_t::pwr_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void pwr_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::no_reset) ; }
  inline void pwr_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::pwr_reset_state_t::reset) ; }
  inline auto pwr_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::pwr_reset_state_t>() ; }
  inline void pwr_reset() { pwr_reset_state_reset() ; pwr_reset_state_no_reset(); }

  inline void i2c3_reset_state( const apb1_peripheral_reset_t::i2c3_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void i2c3_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::no_reset) ; }
  inline void i2c3_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::i2c3_reset_state_t::reset) ; }
  inline auto i2c3_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::i2c3_reset_state_t>() ; }
  inline void i2c3_reset() { i2c3_reset_state_reset() ; i2c3_reset_state_no_reset(); }

  inline void lptim1_reset_state( const apb1_peripheral_reset_t::lptim1_reset_state_t::enum_t val) { apb1_peripheral_reset.rmw(val) ; }
  inline void lptim1_reset_state_no_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lptim1_reset_state_t::no_reset) ; }
  inline void lptim1_reset_state_reset() { apb1_peripheral_reset.rmw(apb1_peripheral_reset_t::lptim1_reset_state_t::reset) ; }
  inline auto lptim1_reset_state() const  { return apb1_peripheral_reset.rd<apb1_peripheral_reset_t::lptim1_reset_state_t>() ; }
  inline void lptim1_reset() { lptim1_reset_state_reset() ; lptim1_reset_state_no_reset(); }

  inline void state_reset(const apb1_peripheral_reset_t::peripheral_t val) { apb1_peripheral_reset.rmw( apb1_peripheral_reset_t::reset,  val ) ; }
  inline void state_no_reset(const apb1_peripheral_reset_t::peripheral_t val){ apb1_peripheral_reset.rmw( apb1_peripheral_reset_t::no_reset, val ) ; }
  inline void reset(const apb1_peripheral_reset_t::peripheral_t val){ state_reset(val); state_no_reset(val);  }

  struct gpio_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, disable=0, enable } ;

    struct gpioa_t  { enum enum_t { offset=0,  mask=0b1, disable=0, enable } ; } ;
    struct gpiob_t  { enum enum_t { offset=1,  mask=0b1, disable=0, enable } ; } ;
    struct gpioc_t  { enum enum_t { offset=2,  mask=0b1, disable=0, enable } ; } ;
    struct gpiod_t  { enum enum_t { offset=3,  mask=0b1, disable=0, enable } ; } ;
    struct gpioe_t  { enum enum_t { offset=4,  mask=0b1, disable=0, enable } ; } ;
    struct gpioh_t  { enum enum_t { offset=7,  mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t { gpioa=gpioa_t::offset ,
                        gpiob=gpiob_t::offset ,
    			gpioc=gpioc_t::offset ,
    			gpiod=gpiod_t::offset ,
    			gpioe=gpioe_t::offset ,
    			gpioh=gpioh_t::offset ,
                      } ;
  };

  inline void gpioa_state( const gpio_clock_t::gpioa_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpioa_disable() { gpio_clock.rmw(gpio_clock_t::gpioa_t::disable) ; }
  inline void gpioa_enable()  { gpio_clock.rmw(gpio_clock_t::gpioa_t::enable) ; }
  inline auto gpioa_state() const  { return gpio_clock.rd<gpio_clock_t::gpioa_t>() ; }

  inline void gpiob_state( const gpio_clock_t::gpiob_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpiob_disable() { gpio_clock.rmw(gpio_clock_t::gpiob_t::disable) ; }
  inline void gpiob_enable()  { gpio_clock.rmw(gpio_clock_t::gpiob_t::enable) ; }
  inline auto gpiob_state() const  { return gpio_clock.rd<gpio_clock_t::gpiob_t>() ; }

  inline void gpioc_state( const gpio_clock_t::gpioc_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpioc_disable() { gpio_clock.rmw(gpio_clock_t::gpioc_t::disable) ; }
  inline void gpioc_enable()  { gpio_clock.rmw(gpio_clock_t::gpioc_t::enable) ; }
  inline auto gpioc_state() const  { return gpio_clock.rd<gpio_clock_t::gpioc_t>() ; }

  inline void gpiod_state( const gpio_clock_t::gpiod_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpiod_disable() { gpio_clock.rmw(gpio_clock_t::gpiod_t::disable) ; }
  inline void gpiod_enable()  { gpio_clock.rmw(gpio_clock_t::gpiod_t::enable) ; }
  inline auto gpiod_state() const  { return gpio_clock.rd<gpio_clock_t::gpiod_t>() ; }

  inline void gpioe_state( const gpio_clock_t::gpioe_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpioe_disable() { gpio_clock.rmw(gpio_clock_t::gpioe_t::disable) ; }
  inline void gpioe_enable()  { gpio_clock.rmw(gpio_clock_t::gpioe_t::enable) ; }
  inline auto gpioe_state() const  { return gpio_clock.rd<gpio_clock_t::gpioe_t>() ; }

  inline void gpioh_state( const gpio_clock_t::gpioh_t::enum_t val) { gpio_clock.rmw(val) ; }
  inline void gpioh_disable() { gpio_clock.rmw(gpio_clock_t::gpioh_t::disable) ; }
  inline void gpioh_enable()  { gpio_clock.rmw(gpio_clock_t::gpioh_t::enable) ; }
  inline auto gpioh_state() const  { return gpio_clock.rd<gpio_clock_t::gpioh_t>() ; }

  inline void state_disable(const gpio_clock_t::peripheral_t val) { gpio_clock.rmw( gpio_clock_t::disable,  val ) ; }
  inline void state_enable(const gpio_clock_t::peripheral_t val){ gpio_clock.rmw( gpio_clock_t::enable, val ) ; }

  struct ahb_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t               {  mask=0b1, disable=0, enable } ;
    struct dma_t              { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct memory_interface_t { enum enum_t { offset=8, mask=0b1, disable=0, enable } ; } ;
    struct crc_t              { enum enum_t { offset=12,mask=0b1, disable=0, enable } ; } ;
    struct crypt_t            { enum enum_t { offset=24,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t {
			dma=dma_t::offset,
			memory_interface=memory_interface_t::offset,
			crc=crc_t::offset,
			crypt=crypt_t::offset,
                      } ;
  }  ;

  inline void dma_state( const ahb_peripheral_clock_t::dma_t::enum_t val) { ahb_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void dma_disable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::dma_t::disable) ; }
  inline void dma_enable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::dma_t::enable) ; ahb_clock_enable_delay();}
  inline auto dma_state() const  { return ahb_peripheral_clock.rd<ahb_peripheral_clock_t::dma_t>() ; }

  inline void memory_interface_state( const ahb_peripheral_clock_t::memory_interface_t::enum_t val) { ahb_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void memory_interface_disable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::memory_interface_t::disable) ; }
  inline void memory_interface_enable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::memory_interface_t::enable) ; ahb_clock_enable_delay();}
  inline auto memory_interface_state() const  { return ahb_peripheral_clock.rd<ahb_peripheral_clock_t::memory_interface_t>() ; }

  inline void crc_state( const ahb_peripheral_clock_t::crc_t::enum_t val) { ahb_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void crc_disable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::crc_t::disable) ; }
  inline void crc_enable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::crc_t::enable) ; ahb_clock_enable_delay();}
  inline auto crc_state() const  { return ahb_peripheral_clock.rd<ahb_peripheral_clock_t::crc_t>() ; }

  inline void crypt_state( const ahb_peripheral_clock_t::crypt_t::enum_t val) { ahb_peripheral_clock.rmw(val) ; ahb_clock_enable_delay();}
  inline void crypt_disable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::crypt_t::disable) ; }
  inline void crypt_enable() { ahb_peripheral_clock.rmw(ahb_peripheral_clock_t::crypt_t::enable) ; ahb_clock_enable_delay();}
  inline auto crypt_state() const  { return ahb_peripheral_clock.rd<ahb_peripheral_clock_t::crypt_t>() ; }

  inline void state_disable(const ahb_peripheral_clock_t::peripheral_t val) { ahb_peripheral_clock.rmw( ahb_peripheral_clock_t::disable,  val ) ; ahb_clock_enable_delay();}
  inline void state_enable(const ahb_peripheral_clock_t::peripheral_t val){ ahb_peripheral_clock.rmw( ahb_peripheral_clock_t::enable, val ) ; }

  struct apb2_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct syscfg_t { enum enum_t { offset=0, mask=0b1, disable=0, enable } ; } ;
    struct tim21_t  { enum enum_t { offset=2, mask=0b1, disable=0, enable } ; } ;
    struct tim22_t  { enum enum_t { offset=5, mask=0b1, disable=0, enable } ; } ;
    struct fw_t     { enum enum_t { offset=7, mask=0b1, disable=0, enable } ; } ;
    struct adc_t    { enum enum_t { offset=9, mask=0b1, disable=0, enable } ; } ;
    struct spi1_t   { enum enum_t { offset=12,mask=0b1, disable=0, enable } ; } ;
    struct usart1_t { enum enum_t { offset=14,mask=0b1, disable=0, enable } ; } ;
    struct dbg_t    { enum enum_t { offset=22,mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t {
                        syscfg=syscfg_t::offset,
			tim21=tim21_t::offset,
			tim22=tim22_t::offset,
			adc=adc_t::offset,
			fw=fw_t::offset,
			spi1=spi1_t::offset,
			usart1=usart1_t::offset,
			dbg=dbg_t::offset,
                      } ;
  }  ;

  inline void syscfg_state( const apb2_peripheral_clock_t::syscfg_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void syscfg_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::disable) ; }
  inline void syscfg_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::syscfg_t::enable) ; }
  inline auto syscfg_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::syscfg_t>() ; }

  inline void tim21_state( const apb2_peripheral_clock_t::tim21_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void tim21_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim21_t::disable) ; }
  inline void tim21_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim21_t::enable) ; }
  inline auto tim21_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim21_t>() ; }

  inline void tim22_state( const apb2_peripheral_clock_t::tim22_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void tim22_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim22_t::disable) ; }
  inline void tim22_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::tim22_t::enable) ; }
  inline auto tim22_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::tim22_t>() ; }

  inline void adc_state( const apb2_peripheral_clock_t::adc_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void adc_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_t::disable) ; }
  inline void adc_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::adc_t::enable) ; }
  inline auto adc_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::adc_t>() ; }

  inline void fw_state( const apb2_peripheral_clock_t::fw_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void fw_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::fw_t::disable) ; }
  inline void fw_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::fw_t::enable) ; }
  inline auto fw_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::fw_t>() ; }

  inline void spi1_state( const apb2_peripheral_clock_t::spi1_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void spi1_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::disable) ; }
  inline void spi1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::spi1_t::enable) ; }
  inline auto spi1_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::spi1_t>() ; }

  inline void usart1_state( const apb2_peripheral_clock_t::usart1_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void usart1_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::disable) ; }
  inline void usart1_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::usart1_t::enable) ; }
  inline auto usart1_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::usart1_t>() ; }

  inline void dbg_state( const apb2_peripheral_clock_t::dbg_t::enum_t val) { apb2_peripheral_clock.rmw(val) ; }
  inline void dbg_disable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dbg_t::disable) ; }
  inline void dbg_enable() { apb2_peripheral_clock.rmw(apb2_peripheral_clock_t::dbg_t::enable) ; }
  inline auto dbg_state() const  { return apb2_peripheral_clock.rd<apb2_peripheral_clock_t::dbg_t>() ; }

  inline void state_disable(const apb2_peripheral_clock_t::peripheral_t val) { apb2_peripheral_clock.rmw( ahb_peripheral_clock_t::disable,  val ) ; }
  inline void state_enable(const apb2_peripheral_clock_t::peripheral_t val){ apb2_peripheral_clock.rmw( ahb_peripheral_clock_t::enable, val ) ; }

  struct apb1_peripheral_clock_t : public read_write_32_t
  {
    enum enum_t       {  mask=0b1, no_reset=0, reset } ;
    struct tim2_t    { enum enum_t { offset=0,  mask=0b1, disable=0, enable } ; } ;
    struct tim3_t    { enum enum_t { offset=1,  mask=0b1, disable=0, enable } ; } ;
    struct tim6_t    { enum enum_t { offset=4,  mask=0b1, disable=0, enable } ; } ;
    struct tim7_t    { enum enum_t { offset=5,  mask=0b1, disable=0, enable } ; } ;
    struct wwdg_t    { enum enum_t { offset=11, mask=0b1, disable=0, enable } ; } ;
    struct spi2_t    { enum enum_t { offset=14, mask=0b1, disable=0, enable } ; } ;
    struct usart2_t  { enum enum_t { offset=17, mask=0b1, disable=0, enable } ; } ;
    struct lpuart1_t { enum enum_t { offset=18, mask=0b1, disable=0, enable } ; } ;
    struct uart4_t   { enum enum_t { offset=19, mask=0b1, disable=0, enable } ; } ;
    struct usart5_t  { enum enum_t { offset=20, mask=0b1, disable=0, enable } ; } ;
    struct i2c1_t    { enum enum_t { offset=21, mask=0b1, disable=0, enable } ; } ;
    struct i2c2_t    { enum enum_t { offset=22, mask=0b1, disable=0, enable } ; } ;
    struct pwr_t     { enum enum_t { offset=28, mask=0b1, disable=0, enable } ; } ;
    struct i2c3_t    { enum enum_t { offset=30, mask=0b1, disable=0, enable } ; } ;
    struct lptim1_t  { enum enum_t { offset=31, mask=0b1, disable=0, enable } ; } ;

    enum peripheral_t {
                         tim2=tim2_t::offset,
			 tim3=tim3_t::offset,
                         tim6=tim6_t::offset,
			 tim7=tim7_t::offset,
			 wwdg=wwdg_t::offset,
			 spi2=spi2_t::offset,
			 usart2=usart2_t::offset,
			 lpuart1=lpuart1_t::offset,
			 uart4=uart4_t::offset,
			 usart5=usart5_t::offset,
			 i2c1=i2c1_t::offset,
			 i2c2=i2c2_t::offset,
			 pwr=pwr_t::offset,
			 i2c3=i2c3_t::offset,
			 lptim1=lptim1_t::offset,
                      } ;
  }  ;

  inline void tim2_state( const apb1_peripheral_clock_t::tim2_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void tim2_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::disable) ; }
  inline void tim2_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim2_t::enable) ; }
  inline auto tim2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim2_t>() ; }

  inline void tim3_state( const apb1_peripheral_clock_t::tim3_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void tim3_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::disable) ; }
  inline void tim3_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim3_t::enable) ; }
  inline auto tim3_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim3_t>() ; }

  inline void tim6_state( const apb1_peripheral_clock_t::tim6_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void tim6_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::disable) ; }
  inline void tim6_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim6_t::enable) ; }
  inline auto tim6_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim6_t>() ; }

  inline void tim7_state( const apb1_peripheral_clock_t::tim7_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void tim7_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::disable) ; }
  inline void tim7_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::tim7_t::enable) ; }
  inline auto tim7_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::tim7_t>() ; }

  inline void wwdg_state( const apb1_peripheral_clock_t::wwdg_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void wwdg_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::disable) ; }
  inline void wwdg_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::wwdg_t::enable) ; }
  inline auto wwdg_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::wwdg_t>() ; }

  inline void spi2_state( const apb1_peripheral_clock_t::spi2_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void spi2_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::disable) ; }
  inline void spi2_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::spi2_t::enable) ; }
  inline auto spi2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::spi2_t>() ; }

  inline void usart2_state( const apb1_peripheral_clock_t::usart2_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void usart2_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart2_t::disable) ; }
  inline void usart2_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart2_t::enable) ; }
  inline auto usart2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::usart2_t>() ; }

  inline void lpuart1_state( const apb1_peripheral_clock_t::lpuart1_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void lpuart1_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lpuart1_t::disable) ; }
  inline void lpuart1_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lpuart1_t::enable) ; }
  inline auto lpuart1_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::lpuart1_t>() ; }

  inline void uart4_state( const apb1_peripheral_clock_t::uart4_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void uart4_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::disable) ; }
  inline void uart4_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::uart4_t::enable) ; }
  inline auto uart4_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::uart4_t>() ; }

  inline void usart5_state( const apb1_peripheral_clock_t::usart5_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void usart5_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart5_t::disable) ; }
  inline void usart5_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::usart5_t::enable) ; }
  inline auto usart5_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::usart5_t>() ; }

  inline void i2c1_state( const apb1_peripheral_clock_t::i2c1_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void i2c1_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::disable) ; }
  inline void i2c1_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c1_t::enable) ; }
  inline auto i2c1_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c1_t>() ; }

  inline void i2c2_state( const apb1_peripheral_clock_t::i2c2_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void i2c2_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::disable) ; }
  inline void i2c2_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c2_t::enable) ; }
  inline auto i2c2_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c2_t>() ; }

  inline void pwr_state( const apb1_peripheral_clock_t::pwr_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void pwr_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::disable) ; }
  inline void pwr_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::pwr_t::enable) ; }
  inline auto pwr_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::pwr_t>() ; }

  inline void i2c3_state( const apb1_peripheral_clock_t::i2c3_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void i2c3_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::disable) ; }
  inline void i2c3_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::i2c3_t::enable) ; }
  inline auto i2c3_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::i2c3_t>() ; }

  inline void lptim1_state( const apb1_peripheral_clock_t::lptim1_t::enum_t val) { apb1_peripheral_clock.rmw(val) ; }
  inline void lptim1_disable() { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lptim1_t::disable) ; }
  inline void lptim1_enable()  { apb1_peripheral_clock.rmw(apb1_peripheral_clock_t::lptim1_t::enable) ; }
  inline auto lptim1_state() const  { return apb1_peripheral_clock.rd<apb1_peripheral_clock_t::lptim1_t>() ; }

  // TODO
  struct gpio_peripheral_sleep_mode_clock_t : public read_write_32_t
  {
  }  ;
  struct ahb_peripheral_sleep_mode_clock_t : public read_write_32_t
  {
  }  ;
  struct apb2_peripheral_sleep_mode_clock_t : public read_write_32_t
  {
  }  ;
  struct apb1_peripheral_sleep_mode_clock_t : public read_write_32_t
  {
  }  ;

  struct peripheral_clock_config_t : public read_write_32_t
  {
    struct usart1_t   { enum enum_t { offset=0,  mask=0b11, apb=0, sysclk, hsi, lse } ; } ;
    struct usart2_t   { enum enum_t { offset=2,  mask=0b11, apb=0, sysclk, hsi, lse } ; } ;
    struct lpuart1_t  { enum enum_t { offset=10, mask=0b11, apb=0, sysclk, hsi, lse } ; } ;
    struct i2c1_t     { enum enum_t { offset=12, mask=0b11, apb=0, sysclk, hsi } ; } ;
    struct i2c3_t     { enum enum_t { offset=12, mask=0b11, apb=0, sysclk, hsi } ; } ;
    struct lptim1_t   { enum enum_t { offset=16, mask=0b11, apb=0, sysclk, hsi, lse } ; } ;
  } ;

  inline void usart1_clock( const peripheral_clock_config_t:: usart1_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void usart1_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t:: usart1_t::apb) ; }
  inline void usart1_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t:: usart1_t::sysclk) ; }
  inline void usart1_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t:: usart1_t::hsi) ; }
  inline void usart1_clock_lse()    { peripheral_clock_config.rmw(peripheral_clock_config_t:: usart1_t::lse) ; }
  inline auto usart1_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t:: usart1_t>() ; }

  inline void usart2_clock( const peripheral_clock_config_t::usart2_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void usart2_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t::usart2_t::apb) ; }
  inline void usart2_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t::usart2_t::sysclk) ; }
  inline void usart2_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t::usart2_t::hsi) ; }
  inline void usart2_clock_lse()    { peripheral_clock_config.rmw(peripheral_clock_config_t::usart2_t::lse) ; }
  inline auto usart2_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t::usart2_t>() ; }

  inline void lpuart1_clock( const peripheral_clock_config_t::lpuart1_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void lpuart1_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lpuart1_t::apb) ; }
  inline void lpuart1_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t::lpuart1_t::sysclk) ; }
  inline void lpuart1_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lpuart1_t::hsi) ; }
  inline void lpuart1_clock_lse()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lpuart1_t::lse) ; }
  inline auto lpuart1_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t::lpuart1_t>() ; }

  inline void i2c1_clock( const peripheral_clock_config_t::i2c1_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void i2c1_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c1_t::apb) ; }
  inline void i2c1_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c1_t::sysclk) ; }
  inline void i2c1_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c1_t::hsi) ; }
  inline auto i2c1_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t::i2c1_t>() ; }

  inline void i2c3_clock( const peripheral_clock_config_t::i2c3_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void i2c3_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c3_t::apb) ; }
  inline void i2c3_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c3_t::sysclk) ; }
  inline void i2c3_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t::i2c3_t::hsi) ; }
  inline auto i2c3_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t::i2c3_t>() ; }

  inline void lptim1_clock( const peripheral_clock_config_t::lptim1_t::enum_t val) { peripheral_clock_config.rmw(val) ; }
  inline void lptim1_clock_apb()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lptim1_t::apb) ; }
  inline void lptim1_clock_sysclk() { peripheral_clock_config.rmw(peripheral_clock_config_t::lptim1_t::sysclk) ; }
  inline void lptim1_clock_hsi()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lptim1_t::hsi) ; }
  inline void lptim1_clock_lse()    { peripheral_clock_config.rmw(peripheral_clock_config_t::lptim1_t::lse) ; }
  inline auto lptim1_clock() const  { return peripheral_clock_config.rd<peripheral_clock_config_t::lptim1_t>() ; }

  // TODO
  struct control_status_t : public read_write_32_t
  {
  } ;


  clock_control_t                    clock_control;                        //CR             /*!< RCC clock control register,          Address offset: 0x00 */
  internal_clock_sources_calibration_t internal_clock_sources_calibration; //ICSCR;         /*!< RCC Internal clock sources calibration register,              Address offset: 0x04 */
  uint32_t : 32 ;                                                          //CRRCR;         /*!< RCC Clock recovery RC register,                               Address offset: 0x08 */
  clock_config_t                     clock_config;                         //CFGR;          /*!< RCC Clock configuration register,                             Address offset: 0x0C */
  clock_interrupt_state_t            clock_interrupt_state;                //CIER;          /*!< RCC Clock interrupt enable register,                          Address offset: 0x10 */
  clock_interrupt_flag_t             clock_interrupt_flag;                 //CIFR;          /*!< RCC Clock interrupt flag register,                            Address offset: 0x14 */
  clock_interrupt_clear_t            clock_interrupt_clear;                //CICR;          /*!< RCC Clock interrupt clear register,                           Address offset: 0x18 */
  gpio_reset_t                       gpio_reset;                           //IOPRSTR;       /*!< RCC IO port reset register,                                   Address offset: 0x1C */
  ahb_peripheral_reset_t             ahb_peripheral_reset;                 //AHBRSTR;       /*!< RCC AHB peripheral reset register,                            Address offset: 0x20 */
  apb2_peripheral_reset_t            apb2_peripheral_reset;                //APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           Address offset: 0x24 */
  apb1_peripheral_reset_t            apb1_peripheral_reset;                //APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           Address offset: 0x28 */
  gpio_clock_t                       gpio_clock;                           //IOPENR;        /*!< RCC Clock IO port enable register,                            Address offset: 0x2C */
  ahb_peripheral_clock_t             ahb_peripheral_clock;                 //AHBENR;        /*!< RCC AHB peripheral clock enable register,                     Address offset: 0x30 */
  apb2_peripheral_clock_t            apb2_peripheral_clock;                //APB2ENR;       /*!< RCC APB2 peripheral enable register,                          Address offset: 0x34 */
  apb1_peripheral_clock_t            apb1_peripheral_clock;                //APB1ENR;       /*!< RCC APB1 peripheral enable register,                          Address offset: 0x38 */
  gpio_peripheral_sleep_mode_clock_t gpio_peripheral_sleep_mode_clock;     //IOPSMENR;      /*!< RCC IO port clock enable in sleep mode register,              Address offset: 0x3C */
  ahb_peripheral_sleep_mode_clock_t  ahb_peripheral_sleep_mode_clock_t;    //AHBSMENR;      /*!< RCC AHB peripheral clock enable in sleep mode register,       Address offset: 0x40 */
  apb2_peripheral_sleep_mode_clock_t apb2_peripheral_sleep_mode_clock;     //APB2SMENR;     /*!< RCC APB2 peripheral clock enable in sleep mode register,      Address offset: 0x44 */
  apb1_peripheral_sleep_mode_clock_t apb1_peripheral_sleep_mode_clock;     //APB1SMENR;     /*!< RCC APB1 peripheral clock enable in sleep mode register,      Address offset: 0x48 */
  peripheral_clock_config_t          peripheral_clock_config;              //CCIPR;         /*!< RCC clock configuration register,                             Address offset: 0x4C */
  control_status_t                   control_status;                       //CSR;           /*!< RCC Control/status register,                                  Address offset: 0x50 */



  struct system_init_profile_t // pwr, clocs, etc
  {
        uint32_t f_osc;
        // тактовая частотота pll_clk  = pll_source * pll_mull / pll_div
        rcc_t::clock_config_t::sys_clock_t::enum_t sys_clock;

        rcc_t::clock_control_t::hsi_div4_t::enum_t  hsi_div4;

        rcc_t::clock_config_t::pll_mul_t::enum_t pll_mul;
  	rcc_t::clock_config_t::pll_div_t::enum_t pll_div;
  	rcc_t::clock_config_t::pll_source_t::enum_t pll_source ;

  	clock_config_t::ahb_prescaler_t::enum_t hpre;
  	clock_config_t::apb1_prescaler_t::enum_t ppre1;
  	clock_config_t::apb2_prescaler_t::enum_t ppre2;


  };


  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // дополнительные функции более высокого уровня чем обращение к регистрам

#if 0
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
        return apb_1_prescaler() == clock_config_t::apb_1_prescaler_t::no_div ?
                            sys_clock_freq() :
			    sys_clock_freq() >> ((apb_1_prescaler() & 0b11) + 1);
      }
   inline uint32_t apb2_clock_freq()  const
      {
        return apb_2_prescaler() == clock_config_t::apb_2_prescaler_t::no_div ?
                            sys_clock_freq() :
			    sys_clock_freq() >> ((apb_2_prescaler() & 0b11) + 1);
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

/*
   inline void     us_cnt_start()  const { dwt.cyc_counter_start(); }
   inline uint32_t us_cnt_stop()   const { return cyc2us(dwt.cyc_counter_stop()); }
   inline uint32_t us_cnt_stop(const uint32_t scf)  const  { return cyc2us(dwt.cyc_counter_stop(),scf); }

   inline void     ns_cnt_start()  const { dwt.cyc_counter_start(); }
   inline uint64_t ns_cnt_stop()   const { return cyc2ns(dwt.cyc_counter_stop()); }
   inline uint64_t ns_cnt_stop(const uint32_t scf)  const  { return cyc2ns(dwt.cyc_counter_stop(),scf); }
*/

#endif


} ;

static rcc_t  &rcc   = *((rcc_t*) rcc_addr);

}  // stm32l0

using namespace stm32l0 ;

#endif /* __RCC++_H__ */
