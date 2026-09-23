/*
 * tim++.h
 *
 *  Created on: 23 дек. 2017 г.
 *      Author: klen
 */

#ifndef __TIM++_H__
#define __TIM++_H__

#include "tim_f4_f7++.h"

namespace stm32f4
{


struct tim6_t : public basic_tim_t
{
   inline void clock_enable() {  rcc.tim6_enable() ; }
   inline void clock_disable() {  rcc.tim6_disable() ; }
   inline void reset() {  rcc.tim6_reset() ; }
};

struct tim7_t : public basic_tim_t
{
   inline void clock_enable() {  rcc.tim7_enable() ; }
   inline void clock_disable() {  rcc.tim7_disable() ; }
   inline void reset() {  rcc.tim7_reset() ; }
};




struct tim10_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim10_enable() ; }
   inline void clock_disable() {  rcc.tim10_disable() ; }
   inline void reset() {  rcc.tim10_reset() ; }

   // переопределенна (таймер имеет 2x внутренний клок)
   inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }
};

struct tim11_t : public gp1_tim_t
{
  tim11_t () {}

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

  // переопределенна (таймер имеет 2x внутренний клок)
  inline auto internal_clock_freq() { return rcc.sys_clock_freq(); }

};
struct tim13_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim13_enable() ; }
   inline void clock_disable() {  rcc.tim13_disable() ; }
   inline void reset() {  rcc.tim13_reset() ; }
};

struct tim14_t : public gp1_tim_t
{
   inline void clock_enable() {  rcc.tim14_enable() ; }
   inline void clock_disable() {  rcc.tim14_disable() ; }
   inline void reset() {  rcc.tim14_reset() ; }
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

  // переопределенна (таймер имеет 2x внутренний клок)
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
};



struct tim2_t : public gp4_tim_t
{
  struct trigger_tim_t  { enum enum_t { offset=4, mask=0b111, tim1=0, tim8, tim3, tim4}; } ;

  inline void trigger_tim(const trigger_tim_t::enum_t val) {  slave_mode_control.rmw( val );}
  inline void trigger_tim1() { slave_mode_control.rmw( trigger_tim_t::tim1 );}
  inline void trigger_tim8() { slave_mode_control.rmw( trigger_tim_t::tim8 );}
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
};


struct tim1_t : public adv_tim_t
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
} ;

struct tim8_t : public adv_tim_t
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

using namespace stm32f4 ;

#endif /* __TIM++_H__ */
