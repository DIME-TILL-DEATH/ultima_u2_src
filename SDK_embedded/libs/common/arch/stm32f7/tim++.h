/*
 * tim++.h
 *
 *  Created on: 23 дек. 2017 г.
 *      Author: klen
 */

#ifndef __TIM++_H__
#define __TIM++_H__

#include "tim_f4_f7++.h"

namespace stm32f7
{

struct tim6_t : public basic_tim_t
{
   inline void clock_enable() {  rcc.tim6_enable() ; }
   inline void clock_disable() {  rcc.tim6_disable() ; }
   inline void reset() {  rcc.tim6_reset() ; }
   inline static tim6_t& ref() { return *((tim6_t *) tim6_addr) ; }
};
struct tim7_t : public basic_tim_t
{
   inline void clock_enable() {  rcc.tim7_enable() ; }
   inline void clock_disable() {  rcc.tim7_disable() ; }
   inline void reset() {  rcc.tim7_reset() ; }
   inline static tim7_t& ref() { return *((tim7_t *) tim7_addr) ; }
};

struct tim10_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim10_enable() ; }
   inline void clock_disable() {  rcc.tim10_disable() ; }
   inline void reset() {  rcc.tim10_reset() ; }
   inline static tim10_t& ref() { return *((tim10_t *) tim10_addr) ; }

   inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
};
struct tim11_t : public gp1_tim_t
{
  //tim11_t () {}

  struct option_t : public read_write_32_t
    {
      struct  input_1_remapping_capability_t   { enum enum_t { offset=0, mask=0b11, hse_rtc=0b10 }; } ;
    } ;

  // как output compare
  inline void input_1_remapping_capability_t(const option_t::input_1_remapping_capability_t::enum_t val) {  option.rmw( val );}
  inline void input_1_remapping_hse_rtc() { option.rmw( option_t::input_1_remapping_capability_t::hse_rtc );}
  inline auto input_1_remapping() const { return option.rd<option_t::input_1_remapping_capability_t>();}

  const uint32_t : 32;
  const uint32_t : 32;
  const uint32_t : 32;
  const uint32_t : 32;
  const uint32_t : 32;
  const uint32_t : 32;
  option_t option ;

  inline void clock_enable() {  rcc.tim11_enable() ; }
  inline void clock_disable() {  rcc.tim11_disable() ; }
  inline void reset() {  rcc.tim11_reset() ; }
  inline static tim11_t& ref() { return *((tim11_t *) tim11_addr) ; }

  inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
};

struct tim13_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim13_enable() ; }
   inline void clock_disable() {  rcc.tim13_disable() ; }
   inline void reset() {  rcc.tim13_reset() ; }
   inline static tim13_t& ref() { return *((tim13_t *) tim13_addr) ; }
};
struct tim14_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim14_enable() ; }
   inline void clock_disable() {  rcc.tim14_disable() ; }
   inline void reset() {  rcc.tim14_reset() ; }
   inline static tim14_t& ref() { return *((tim14_t *) tim14_addr) ; }
};

struct tim9_t : public gp2_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim2=0, tim3, tim10_oc, tim11_oc}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim3() { slave_mode_control.rmw( trigger_tim_t::tim3 );}
  inline void trigger_tim10_oc() { slave_mode_control.rmw( trigger_tim_t::tim10_oc );}
  inline void trigger_tim11_oc() { slave_mode_control.rmw( trigger_tim_t::tim11_oc );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() {  rcc.tim9_enable() ; }
  inline void clock_disable() {  rcc.tim9_disable() ; }
  inline void reset() {  rcc.tim9_reset() ; }
  inline static tim9_t& ref() { return *((tim9_t *) tim9_addr) ; }

  inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
};
struct tim12_t : public gp2_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim4=0, tim5, tim13_oc, tim14_oc}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline void trigger_tim5() { slave_mode_control.rmw( trigger_tim_t::tim5 );}
  inline void trigger_tim13_oc() { slave_mode_control.rmw( trigger_tim_t::tim13_oc );}
  inline void trigger_tim14_oc() { slave_mode_control.rmw( trigger_tim_t::tim14_oc );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() {  rcc.tim12_enable() ; }
  inline void clock_disable() {  rcc.tim12_disable() ; }
  inline void reset() {  rcc.tim12_reset() ; }
  inline static tim12_t& ref() { return *((tim12_t *) tim12_addr) ; }
};

struct tim3_t : public gp3_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim1=0, tim2, tim5, tim4}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim1() { slave_mode_control.rmw( trigger_tim_t::tim1 );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim5() { slave_mode_control.rmw( trigger_tim_t::tim5 );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() {  rcc.tim3_enable() ; }
  inline void clock_disable() {  rcc.tim3_disable() ; }
  inline void reset() {  rcc.tim3_reset() ; }
  inline static tim3_t& ref() { return *((tim3_t *) tim3_addr) ; }
};
struct tim4_t : public gp3_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim1=0, tim2, tim3, tim8}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim1() { slave_mode_control.rmw( trigger_tim_t::tim1 );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim3() { slave_mode_control.rmw( trigger_tim_t::tim3 );}
  inline void trigger_tim8() { slave_mode_control.rmw( trigger_tim_t::tim8 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() {  rcc.tim4_enable() ; }
  inline void clock_disable() {  rcc.tim4_disable() ; }
  inline void reset() {  rcc.tim4_reset() ; }
  inline static tim4_t& ref() { return *((tim4_t *) tim4_addr) ; }
};

struct tim2_t : public gp4_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim1=0, tim8_eth_ptp_otg_sof, tim3, tim4}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim1() { slave_mode_control.rmw( trigger_tim_t::tim1 );}
  inline void trigger_tim8_eth_ptp_otg_sof() { slave_mode_control.rmw( trigger_tim_t::tim8_eth_ptp_otg_sof );}
  inline void trigger_tim3() { slave_mode_control.rmw( trigger_tim_t::tim3 );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  struct option_t : public read_write_32_t
    {
      struct  internal_trigger_1_remap_t   { enum enum_t { offset=10, mask=0b11, tim8_trigger_out=0, ptp, otg_fs_sof, otg_hs_sof  }; } ;
    } ;

  inline void internal_trigger_1_remap(const option_t::internal_trigger_1_remap_t::enum_t val) {  option.rmw( val );}
  inline void internal_trigger_1_remap_tim8_trigger_out() { option.rmw( option_t::internal_trigger_1_remap_t::tim8_trigger_out );}
  inline void internal_trigger_1_remap_ptp()              { option.rmw( option_t::internal_trigger_1_remap_t::ptp );}
  inline void internal_trigger_1_remap_otg_fs_sof()       { option.rmw( option_t::internal_trigger_1_remap_t::otg_fs_sof );}
  inline void internal_trigger_1_remap_otg_hs_sof()       { option.rmw( option_t::internal_trigger_1_remap_t::otg_hs_sof );}
  inline auto internal_trigger_1_remap() const { return option.rd<option_t::internal_trigger_1_remap_t>();}

  option_t option ;

  inline void clock_enable() { rcc.tim2_enable() ; }
  inline void clock_disable() { rcc.tim2_disable() ; }
  inline void reset() { rcc.tim2_reset() ; }
  inline static tim2_t& ref() { return *((tim2_t *) tim2_addr) ; }
};
struct tim5_t : public gp4_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim2=0, tim3, tim4, tim8}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim3() { slave_mode_control.rmw( trigger_tim_t::tim3 );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline void trigger_tim8() { slave_mode_control.rmw( trigger_tim_t::tim8 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  struct option_t : public read_write_32_t
    {
      struct  internal_trigger_4_remap_t   { enum enum_t { offset=6, mask=0b11, gpio=0, lsi, lse, rtc  }; } ;
    } ;

  inline void internal_trigger_4_remap(const option_t::internal_trigger_4_remap_t::enum_t val) {  option.rmw( val );}
  inline void internal_trigger_4_remap_gpio() { option.rmw( option_t::internal_trigger_4_remap_t::gpio );}
  inline void internal_trigger_4_remap_lsi()  { option.rmw( option_t::internal_trigger_4_remap_t::lsi );}
  inline void internal_trigger_4_remap_lse()  { option.rmw( option_t::internal_trigger_4_remap_t::lse );}
  inline void internal_trigger_4_remap_rtc()  { option.rmw( option_t::internal_trigger_4_remap_t::rtc );}
  inline auto internal_trigger_4_remap() const { return option.rd<option_t::internal_trigger_4_remap_t>();}

  option_t option ;

  inline void clock_enable() {  rcc.tim5_enable() ; }
  inline void clock_disable() {  rcc.tim5_disable() ; }
  inline void reset() {  rcc.tim5_reset() ; }
  inline static tim5_t& ref() { return *((tim5_t *) tim5_addr) ; }

};

struct adv_tim_f7_t : public adv_tim_t
{

  struct control_2_t
  {
    struct oc5_output_idle_state_t { enum enum_t { offset=16, mask=1, low=0, high };} ;
    struct oc6_output_idle_state_t { enum enum_t { offset=18, mask=1, low=0, high };} ;
    struct master_mode_selection_trgo2_t { enum enum_t { offset=20, mask=0b1111, reset=0, enable, update, cc1if_pulse,
                                                         oc1ref, oc2ref, oc3ref, oc4ref, oc5ref, oc6ref,
							 oc4ref_rise_fall_pulse,
							 oc6ref_rise_fall_pulse,
							 oc4ref_oc6ref_fall_pulse ,
							 oc4ref_rise_oc6ref_fall_pulse ,
							 oc5ref_oc6ref_fall_pulse ,
							 oc5ref_rise_oc6ref_fall_pulse
                                          };} ;
  };

  inline void oc5_output_idle_state(const control_2_t::oc5_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
  inline void oc5_output_idle_state_low()  { control_2.rmw( control_2_t::oc5_output_idle_state_t::low );}
  inline void oc5_output_idle_state_high() { control_2.rmw( control_2_t::oc5_output_idle_state_t::high );}
  inline auto oc5_output_idle_state() const { return control_2.rd<control_2_t::oc5_output_idle_state_t>();}

  inline void oc6_output_idle_state(const control_2_t::oc6_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
  inline void oc6_output_idle_state_low()  { control_2.rmw( control_2_t::oc6_output_idle_state_t::low );}
  inline void oc6_output_idle_state_high() { control_2.rmw( control_2_t::oc6_output_idle_state_t::high );}
  inline auto oc6_output_idle_state() const { return control_2.rd<control_2_t::oc6_output_idle_state_t>();}

  inline void master_mode_selection_trgo2(const control_2_t::master_mode_selection_trgo2_t::enum_t val) {  control_2.rmw( val );}
  inline void master_mode_selection_trgo2_reset() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::reset );}
  inline void master_mode_selection_trgo2_enable() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::enable );}
  inline void master_mode_selection_trgo2_update() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::update );}
  inline void master_mode_selection_trgo2_cc1if_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::cc1if_pulse );}
  inline void master_mode_selection_trgo2_oc1ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc1ref );}
  inline void master_mode_selection_trgo2_oc2ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc2ref  );}
  inline void master_mode_selection_trgo2_oc3ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc3ref  );}
  inline void master_mode_selection_trgo2_oc4ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc4ref  );}
  inline void master_mode_selection_trgo2_oc5ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc5ref  );}
  inline void master_mode_selection_trgo2_oc6ref() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc6ref  );}
  inline void master_mode_selection_trgo2_oc4ref_rise_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc4ref_rise_fall_pulse );}
  inline void master_mode_selection_trgo2_oc6ref_rise_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc6ref_rise_fall_pulse  );}
  inline void master_mode_selection_trgo2_oc4ref_oc6ref_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc4ref_oc6ref_fall_pulse  );}
  inline void master_mode_selection_trgo2_oc4ref_rise_oc6ref_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc4ref_rise_oc6ref_fall_pulse  );}
  inline void master_mode_selection_trgo2_oc5ref_oc6ref_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc5ref_oc6ref_fall_pulse  );}
  inline void master_mode_selection_trgo2_oc5ref_rise_oc6ref_fall_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo2_t::oc5ref_rise_oc6ref_fall_pulse  );}
  inline auto master_mode_selection_trgo2() const { return control_2.rd<control_2_t::master_mode_selection_trgo2_t>();}


// TODO

  struct option_t : public read_write_32_t
     {

     } ;

  struct control_3_t : public read_write_32_t
     {

     } ;

  struct afo_1_t : public read_write_32_t
     {

     } ;

  struct afo_2_t : public read_write_32_t
     {

     } ;

  option_t                  option    ;          //OR;          /*!< TIM option register,                 Address offset: 0x50 */
  control_3_t               control_1 ;          //CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */

  volatile uint16_t capture_compare_5 ;          //CCR5;        /*!< TIM capture/compare mode register5,       Address offset: 0x58 */
  const    uint16_t : 16 ;

  volatile uint16_t capture_compare_6 ;          //CCR6;        /*!< TIM capture/compare mode register6,       Address offset: 0x5C */
  const    uint16_t : 16 ;

  afo_1_t            afo_1;                      //AF1;         /*!< TIM Alternate function option register 1, Address offset: 0x60 */
  afo_2_t            afo_2;                      //AF2;         /*!< TIM Alternate function option register 2, Address offset: 0x64 */

} ;

struct tim1_t : public adv_tim_f7_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim5=0, tim2, tim3, tim4}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim5() { slave_mode_control.rmw( trigger_tim_t::tim5 );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim3() { slave_mode_control.rmw( trigger_tim_t::tim3 );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() { rcc.tim1_enable() ; }
  inline void clock_disable() { rcc.tim1_disable() ; }
  inline void reset() { rcc.tim1_reset() ; }
  inline static tim1_t& ref() { return *((tim1_t *) tim1_addr) ; }

  inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
  //TODO учесть прескалер и источник тактового сигнала
  inline auto freq(uint32_t val) { auto_reload = internal_clock_freq() / val - 1 ; }
  inline auto freq() { return internal_clock_freq() / ( auto_reload + 1 ) ; }
  inline auto period(double val) { auto_reload = val * internal_clock_freq() - 1 ; }
  inline auto period() { return 1.0*( auto_reload + 1 ) / internal_clock_freq() ; }

} ;
struct tim8_t : public adv_tim_f7_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim1=0, tim2, tim4, tim5}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim1() { slave_mode_control.rmw( trigger_tim_t::tim1 );}
  inline void trigger_tim2() { slave_mode_control.rmw( trigger_tim_t::tim2 );}
  inline void trigger_tim4() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline void trigger_tim5() { slave_mode_control.rmw( trigger_tim_t::tim4 );}
  inline auto trigger_tim() const { return slave_mode_control.rd<trigger_tim_t>();}

  inline void clock_enable() { rcc.tim8_enable() ; }
  inline void clock_disable() { rcc.tim8_disable() ; }
  inline void reset() { rcc.tim8_reset() ; }
  inline static tim8_t& ref() { return *((tim8_t *) tim8_addr) ; }

  inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
  //TODO учесть прескалер и источник тактового сигнала
  inline auto freq(uint32_t val) { auto_reload = internal_clock_freq() / val - 1 ; }
  inline auto freq() { return internal_clock_freq() / ( auto_reload + 1 ) ; }
  inline auto period(double val) { auto_reload = val * internal_clock_freq() - 1 ; }
  inline auto period() { return 1.0*( auto_reload + 1 ) / internal_clock_freq() ; }
} ;


  static tim1_t&  tim1  = *((tim1_t *)  tim1_addr);
  static tim2_t&  tim2  = *((tim2_t*)   tim2_addr);
  static tim3_t&  tim3  = *((tim3_t*)   tim3_addr);
  static tim4_t&  tim4  = *((tim4_t*)   tim4_addr);
  static tim5_t&  tim5  = *((tim5_t*)   tim5_addr);
  static tim6_t&  tim6  = *((tim6_t*)   tim6_addr);
  static tim7_t&  tim7  = *((tim7_t*)   tim7_addr);
  static tim8_t&  tim8  = *((tim8_t *)  tim8_addr);
  static tim9_t&  tim9  = *((tim9_t *)  tim9_addr);
  static tim10_t& tim10 = *((tim10_t *) tim10_addr);
  static tim11_t& tim11 = *((tim11_t *) tim11_addr);
  static tim12_t& tim12 = *((tim12_t *) tim12_addr);
  static tim13_t& tim13 = *((tim13_t *) tim13_addr);
  static tim14_t& tim14 = *((tim14_t *) tim14_addr);

}

using namespace stm32f7 ;

#endif /* __TIM++_H__ */
