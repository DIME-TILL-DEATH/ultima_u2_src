/*
 * adc_converter_v1++.h
 *
 *  Created on: 23 матра 2018 г.
 *      Author: klen
 */

#ifndef __ADC_CONVERTER_V1++_H__
#define __ADC_CONVERTER_V1++_H__

#include "types++.h"


namespace stm32
{

struct adc_converter_v1_t
{
  struct status_t : public read_write_32_t
  {
    struct analog_watchdog_flag_t               { enum enum_t { offset=0, mask=1, no_occured=0, occured    }; } ;
    struct regular_channel_end_of_conversion_t  { enum enum_t { offset=1, mask=1, not_complete=0, complete }; } ;
    struct injected_channel_end_of_conversion_t { enum enum_t { offset=2, mask=1, not_complete=0, complete }; } ;
    struct injected_channel_start_flag_t        { enum enum_t { offset=3, mask=1, not_started=0, started   }; } ;
    struct regular_channel_start_flag_t         { enum enum_t { offset=4, mask=1, not_started=0, started   }; } ;
    struct overrun_t                            { enum enum_t { offset=5, mask=1, no_occured=0, occurred   }; } ;
  } ;

  inline void analog_watchdog_flag_clear() { status.rmw( status_t::analog_watchdog_flag_t::no_occured );}
  inline auto analog_watchdog_flag() const { return status.rd<status_t::analog_watchdog_flag_t>();}

  inline void regular_channel_eoc_clear() { status.rmw( status_t::regular_channel_end_of_conversion_t::not_complete );}
  inline auto regular_channel_eoc() const { return status.rd<status_t::regular_channel_end_of_conversion_t>();}

  inline void injected_channel_eoc_clear() { status.rmw( status_t::injected_channel_end_of_conversion_t::not_complete );}
  inline auto injected_channel_eoc() const { return status.rd<status_t::injected_channel_end_of_conversion_t>();}

  inline void injected_channel_start_flag_clear() { status.rmw( status_t::injected_channel_start_flag_t::not_started );}
  inline auto injected_channel_start_flag() const { return status.rd<status_t::injected_channel_start_flag_t>();}

  inline void regular_channel_start_flag_clear() { status.rmw( status_t::regular_channel_start_flag_t::not_started );}
  inline auto regular_channel_start_flag() const { return status.rd<status_t::regular_channel_start_flag_t>();}

  inline void overrun_clear() { status.rmw( status_t::overrun_t::no_occured );}
  inline auto overrun() const { return status.rd<status_t::overrun_t>();}

  struct control_1_t : public read_write_32_t
  {
    struct analog_watchdog_channel_select_t { enum enum_t { offset=0, mask=0b11111,  channel_0=0, channel_1, channel_2, channel_3, channel_4, channel_5, channel_6,
                                                                                          channel_7, channel_8, channel_9, channel_10, channel_11,channel_12, channel_13,
											  channel_14, channel_15, channel_16, channel_17, channel_18 }; } ;

    struct eoc_interrupt_t                   { enum enum_t { offset=5, mask=1, disable=0, enable }; } ;
    struct analog_watchdog_interrupt_t       { enum enum_t { offset=6, mask=1, disable=0, enable }; } ;
    struct injected_channels_interrupt_t     { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
    struct scan_mode_t                       { enum enum_t { offset=8, mask=1, disable=0, enable }; } ;
    struct analog_watchdog_scan_modet_t      { enum enum_t { offset=9, mask=1, all_channel=0, single_channel   }; } ;
    struct auto_injected_group_conversion_t  { enum enum_t { offset=10, mask=1, disable=0, enable   }; } ;
    struct discontinuous_mode_regular_channels_t { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
    struct discontinuous_mode_injected_channels_t { enum enum_t { offset=12, mask=1, disable=0, enable }; } ;
    struct discontinuous_mode_channel_count_t { enum enum_t { offset=13, mask=0b111 }; } ;
    struct analog_watchdog_on_injected_channels_t { enum enum_t { offset=22, mask=1, disable=0, enable }; } ;
    struct analog_watchdog_on_regular_channels_t { enum enum_t { offset=23, mask=1, disable=0, enable }; } ;
    struct resolution_t                      { enum enum_t { offset=24, mask=0b11, cycle15_bit12=0, cycle13_bit10, cycle11_bit8, cycle9_bit6 }; } ;
    struct overrun_interrupt_t               { enum enum_t { offset=26, mask=1, disable=0, enable }; } ;
  } ;

  inline  void analog_watchdog_channel_select( const control_1_t::analog_watchdog_channel_select_t::enum_t val){  control_1.rmw(val) ;}
  inline  void analog_watchdog_channel_select_channel_0() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_0) ;}
  inline  void analog_watchdog_channel_select_channel_1() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_1) ;}
  inline  void analog_watchdog_channel_select_channel_2() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_2) ;}
  inline  void analog_watchdog_channel_select_channel_3() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_3) ;}
  inline  void analog_watchdog_channel_select_channel_4() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_4) ;}
  inline  void analog_watchdog_channel_select_channel_5() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_5) ;}
  inline  void analog_watchdog_channel_select_channel_6() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_6) ;}
  inline  void analog_watchdog_channel_select_channel_7() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_7) ;}
  inline  void analog_watchdog_channel_select_channel_8() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_8) ;}
  inline  void analog_watchdog_channel_select_channel_9() {  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_9) ;}
  inline  void analog_watchdog_channel_select_channel_10(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_10) ;}
  inline  void analog_watchdog_channel_select_channel_11(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_11) ;}
  inline  void analog_watchdog_channel_select_channel_12(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_12) ;}
  inline  void analog_watchdog_channel_select_channel_13(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_13) ;}
  inline  void analog_watchdog_channel_select_channel_14(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_14) ;}
  inline  void analog_watchdog_channel_select_channel_15(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_15) ;}
  inline  void analog_watchdog_channel_select_channel_16(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_16) ;}
  inline  void analog_watchdog_channel_select_channel_17(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_17) ;}
  inline  void analog_watchdog_channel_select_channel_18(){  control_1.rmw( control_1_t::analog_watchdog_channel_select_t::channel_18) ;}
  inline  auto analog_watchdog_channel_select() const {  return control_1.rd<control_1_t::analog_watchdog_channel_select_t> ();}

  inline  void eoc_interrupt( const control_1_t::eoc_interrupt_t::enum_t val){  control_1.rmw(val) ;}
  inline  void eoc_interrupt_enable()   {  control_1.rmw( control_1_t::eoc_interrupt_t::enable) ;}
  inline  void eoc_interrupt_disable() {  control_1.rmw( control_1_t::eoc_interrupt_t::disable) ;}
  inline  auto eoc_interrupt() const {  return control_1.rd<control_1_t::eoc_interrupt_t> ();}

  inline  void analog_watchdog_interrupt( const control_1_t::analog_watchdog_interrupt_t::enum_t val){  control_1.rmw(val) ;}
  inline  void analog_watchdog_interrupt_enable()   {  control_1.rmw( control_1_t::analog_watchdog_interrupt_t::enable) ;}
  inline  void analog_watchdog_interrupt_disable() {  control_1.rmw( control_1_t::analog_watchdog_interrupt_t::disable) ;}
  inline  auto analog_watchdog_interrupt() const {  return control_1.rd<control_1_t::analog_watchdog_interrupt_t> ();}

  inline  void injected_channels_interrupt( const control_1_t::injected_channels_interrupt_t::enum_t val){  control_1.rmw(val) ;}
  inline  void injected_channels_interrupt_enable()   {  control_1.rmw( control_1_t::injected_channels_interrupt_t::enable) ;}
  inline  void injected_channels_interrupt_disable() {  control_1.rmw( control_1_t::injected_channels_interrupt_t::disable) ;}
  inline  auto injected_channels_interrupt() const {  return control_1.rd<control_1_t::injected_channels_interrupt_t> ();}

  inline  void scan_mode( const control_1_t::scan_mode_t::enum_t val){  control_1.rmw(val) ;}
  inline  void scan_mode_enable()   {  control_1.rmw( control_1_t::scan_mode_t::enable) ;}
  inline  void scan_mode_disable() {  control_1.rmw( control_1_t::scan_mode_t::disable) ;}
  inline  auto scan_mode() const {  return control_1.rd<control_1_t::scan_mode_t> ();}

  inline  void analog_watchdog_scan_mode( const control_1_t::analog_watchdog_scan_modet_t::enum_t val){  control_1.rmw(val) ;}
  inline  void analog_watchdog_scan_mode_all_channel()   {  control_1.rmw( control_1_t::analog_watchdog_scan_modet_t::all_channel) ;}
  inline  void analog_watchdog_scan_mode_single_channel() {  control_1.rmw( control_1_t::analog_watchdog_scan_modet_t::single_channel) ;}
  inline  auto analog_watchdog_scan_mode() const {  return control_1.rd<control_1_t::analog_watchdog_scan_modet_t> ();}

  inline  void auto_injected_group_conversion( const control_1_t::auto_injected_group_conversion_t::enum_t val){  control_1.rmw(val) ;}
  inline  void auto_injected_group_conversion_enable()   {  control_1.rmw( control_1_t::auto_injected_group_conversion_t::enable) ;}
  inline  void auto_injected_group_conversion_disable() {  control_1.rmw( control_1_t::auto_injected_group_conversion_t::disable) ;}
  inline  auto auto_injected_group_conversion() const {  return control_1.rd<control_1_t::auto_injected_group_conversion_t> ();}

  inline  void discontinuous_mode_regular_channels( const control_1_t::discontinuous_mode_regular_channels_t::enum_t val){  control_1.rmw(val) ;}
  inline  void discontinuous_mode_regular_channels_enable()   {  control_1.rmw( control_1_t::discontinuous_mode_regular_channels_t::enable) ;}
  inline  void discontinuous_mode_regular_channels_disable() {  control_1.rmw( control_1_t::discontinuous_mode_regular_channels_t::disable) ;}
  inline  auto discontinuous_mode_regular_channels() const {  return control_1.rd<control_1_t::discontinuous_mode_regular_channels_t> ();}

  inline  void discontinuous_mode_injected_channels( const control_1_t::discontinuous_mode_injected_channels_t::enum_t val){  control_1.rmw(val) ;}
  inline  void discontinuous_mode_injected_channels_enable()   {  control_1.rmw( control_1_t::discontinuous_mode_injected_channels_t::enable) ;}
  inline  void discontinuous_mode_injected_channels_disable() {  control_1.rmw( control_1_t::discontinuous_mode_injected_channels_t::disable) ;}
  inline  auto discontinuous_mode_injected_channels() const {  return control_1.rd<control_1_t::discontinuous_mode_injected_channels_t> ();}

  inline  void discontinuous_mode_channel_count( const uint8_t val){  control_1.rmw((control_1_t::discontinuous_mode_channel_count_t::enum_t)(val-1)) ;}
  inline  auto discontinuous_mode_channel_count() const {  return ((uint8_t)control_1.rd<control_1_t::discontinuous_mode_channel_count_t> ())+1 ;}

  inline  void analog_watchdog_on_injected_channels( const control_1_t::analog_watchdog_on_injected_channels_t::enum_t val){  control_1.rmw(val) ;}
  inline  void analog_watchdog_on_injected_channels_enable()   {  control_1.rmw( control_1_t::analog_watchdog_on_injected_channels_t::enable) ;}
  inline  void analog_watchdog_on_injected_channels_disable() {  control_1.rmw( control_1_t::analog_watchdog_on_injected_channels_t::disable) ;}
  inline  auto analog_watchdog_on_injected_channels() const {  return control_1.rd<control_1_t::analog_watchdog_on_injected_channels_t> ();}

  inline  void analog_watchdog_on_regular_channels( const control_1_t::analog_watchdog_on_regular_channels_t::enum_t val){  control_1.rmw(val) ;}
  inline  void analog_watchdog_on_regular_channels_enable()   {  control_1.rmw( control_1_t::analog_watchdog_on_regular_channels_t::enable) ;}
  inline  void analog_watchdog_on_regular_channels_disable() {  control_1.rmw( control_1_t::analog_watchdog_on_regular_channels_t::disable) ;}
  inline  auto analog_watchdog_on_regular_channels() const {  return control_1.rd<control_1_t::analog_watchdog_on_regular_channels_t> ();}

  inline  void resolution( const control_1_t::resolution_t::enum_t val){  control_1.rmw(val) ;}
  inline  void resolution_cycle15_bit12() {  control_1.rmw( control_1_t::resolution_t::cycle15_bit12) ;}
  inline  void resolution_cycle13_bit10() {  control_1.rmw( control_1_t::resolution_t::cycle13_bit10) ;}
  inline  void resolution_cycle11_bit8()  {  control_1.rmw( control_1_t::resolution_t::cycle11_bit8) ;}
  inline  void resolution_cycle9_bit6()   {  control_1.rmw( control_1_t::resolution_t::cycle9_bit6) ;}
  inline  auto resolution() const {  return control_1.rd<control_1_t::resolution_t> ();}

  inline  void overrun_interrupt( const control_1_t::overrun_interrupt_t::enum_t val){  control_1.rmw(val) ;}
  inline  void overrun_interrupt_enable()   {  control_1.rmw( control_1_t::overrun_interrupt_t::enable) ;}
  inline  void overrun_interrupt_disable() {  control_1.rmw( control_1_t::overrun_interrupt_t::disable) ;}
  inline  auto overrun_interrupt() const {  return control_1.rd<control_1_t::overrun_interrupt_t> ();}

  struct control_2_t : public read_write_32_t
  {
    struct power_t                   { enum enum_t { offset=0, mask=1, off=0, on }; } ;
    struct continuous_conversion_t   { enum enum_t { offset=1, mask=1, disable=0, enable }; } ;
    struct dma_mode_t                { enum enum_t { offset=8, mask=1, disable=0, enable }; } ;
    struct dma_disable_selection_t   { enum enum_t { offset=9, mask=1, disable=0, enable }; } ;
    struct eoc_selection_t           { enum enum_t { offset=10, mask=1, sequence_regular=0, each_regular }; } ;
    struct data_align_t              { enum enum_t { offset=11, mask=1, right=0, left }; } ;

    //   переопределеяется в наследнике в связи с различиями в между семействами мкросхем
    //   struct external_event_select_for_injected_group_t { enum enum_t { offset=16, mask=0b1111 }; } ;

    struct external_trigger_for_injected_channels_t { enum enum_t { offset=20, mask=0b11, disable=0, rising, fallingm , rising_and_falling}; } ;
    struct conversion_injected_channels_state_t     { enum enum_t { offset=22, mask=1, reset=0, start }; } ;

    //   переопределеяется в наследнике в связи с различиями в между семействами мкросхем
    //   struct external_event_select_for_regular_group_t  { enum enum_t { offset=24, mask=0b1111, }; } ;

    struct external_trigger_for_regular_channels_t { enum enum_t { offset=28, mask=0b11, disable=0, rising, fallingm , rising_and_falling}; } ;
    struct conversion_regular_channels_state_t     { enum enum_t { offset=30, mask=1, reset=0, start }; } ;
  } ;

  inline  void power( const control_2_t::power_t::enum_t val){  control_2.rmw(val) ;}
  inline  void power_on()  {  control_2.rmw( control_2_t::power_t::on) ;}
  inline  void power_off() {  control_2.rmw( control_2_t::power_t::off) ;}
  inline  auto power() const {  return control_2.rd<control_2_t::power_t> ();}

  inline  void continuous_conversion( const control_2_t::continuous_conversion_t::enum_t val){  control_2.rmw(val) ;}
  inline  void continuous_conversion_enable()  {  control_2.rmw( control_2_t::continuous_conversion_t::enable) ;}
  inline  void continuous_conversion_disable() {  control_2.rmw( control_2_t::continuous_conversion_t::disable) ;}
  inline  auto continuous_conversion() const {  return control_2.rd<control_2_t::continuous_conversion_t> ();}

  inline  void dma_mode( const control_2_t::dma_mode_t::enum_t val){  control_2.rmw(val) ;}
  inline  void dma_mode_enable()  {  control_2.rmw( control_2_t::dma_mode_t::enable) ;}
  inline  void dma_mode_disable() {  control_2.rmw( control_2_t::dma_mode_t::disable) ;}
  inline  auto dma_mode() const {  return control_2.rd<control_2_t::dma_mode_t> ();}

  inline  void dma_disable_selection( const control_2_t::dma_disable_selection_t::enum_t val){  control_2.rmw(val) ;}
  inline  void dma_disable_selection_enable()  {  control_2.rmw( control_2_t::dma_disable_selection_t::enable) ;}
  inline  void dma_disable_selection_disable() {  control_2.rmw( control_2_t::dma_disable_selection_t::disable) ;}
  inline  auto dma_disable_selection() const {  return control_2.rd<control_2_t::dma_disable_selection_t> ();}

  inline  void eoc_selection( const control_2_t::eoc_selection_t::enum_t val){  control_2.rmw(val) ;}
  inline  void eoc_selection_sequence_regular()  {  control_2.rmw( control_2_t::eoc_selection_t::sequence_regular) ;}
  inline  void eoc_selection_each_regular() {  control_2.rmw( control_2_t::eoc_selection_t::each_regular) ;}
  inline  auto eoc_selection() const {  return control_2.rd<control_2_t::eoc_selection_t> ();}

  inline  void data_align( const control_2_t::data_align_t::enum_t val){  control_2.rmw(val) ;}
  inline  void data_align_right()  {  control_2.rmw( control_2_t::data_align_t::right) ;}
  inline  void data_align_left() {  control_2.rmw( control_2_t::data_align_t::left) ;}
  inline  auto data_align() const {  return control_2.rd<control_2_t::data_align_t> ();}

  inline  void external_trigger_for_injected_channels( const control_2_t::external_trigger_for_injected_channels_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_trigger_for_injected_channels_disable()  {  control_2.rmw( control_2_t::external_trigger_for_injected_channels_t::disable) ;}
  inline  void external_trigger_for_injected_channels_rising() {  control_2.rmw( control_2_t::external_trigger_for_injected_channels_t::rising) ;}
  inline  void external_trigger_for_injected_channels_fallingm()  {  control_2.rmw( control_2_t::external_trigger_for_injected_channels_t::fallingm) ;}
  inline  void external_trigger_for_injected_channels_rising_and_falling() {  control_2.rmw( control_2_t::external_trigger_for_injected_channels_t::rising_and_falling) ;}
  inline  auto external_trigger_for_injected_channels() const {  return control_2.rd<control_2_t::external_trigger_for_injected_channels_t> ();}

  inline  void conversion_injected_channels_state( const control_2_t::conversion_injected_channels_state_t::enum_t val){  control_2.rmw(val) ;}
  inline  void conversion_injected_channels_reset()  {  control_2.rmw( control_2_t::conversion_injected_channels_state_t::reset) ;}
  inline  void conversion_injected_channels_start()  {  control_2.rmw( control_2_t::conversion_injected_channels_state_t::start) ;}
  inline  auto conversion_injected_channels_state() const {  return control_2.rd<control_2_t::conversion_injected_channels_state_t> ();}

  inline  void external_trigger_for_regular_channels( const control_2_t::external_trigger_for_regular_channels_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_trigger_for_regular_channels_disable()  {  control_2.rmw( control_2_t::external_trigger_for_regular_channels_t::disable) ;}
  inline  void external_trigger_for_regular_channels_rising() {  control_2.rmw( control_2_t::external_trigger_for_regular_channels_t::rising) ;}
  inline  void external_trigger_for_regular_channels_fallingm()  {  control_2.rmw( control_2_t::external_trigger_for_regular_channels_t::fallingm) ;}
  inline  void external_trigger_for_regular_channels_rising_and_falling() {  control_2.rmw( control_2_t::external_trigger_for_regular_channels_t::rising_and_falling) ;}
  inline  auto external_trigger_for_regular_channels() const {  return control_2.rd<control_2_t::external_trigger_for_regular_channels_t> ();}

  inline  void conversion_regular_channels_state( const control_2_t::conversion_regular_channels_state_t::enum_t val){  control_2.rmw(val) ;}
  inline  void conversion_regular_channels_reset()  {  control_2.rmw( control_2_t::conversion_regular_channels_state_t::reset) ;}
  inline  void conversion_regular_channels_start()  {  control_2.rmw( control_2_t::conversion_regular_channels_state_t::start) ;}
  inline  auto conversion_regular_channels_state() const {  return control_2.rd<control_2_t::conversion_regular_channels_state_t> ();}

  inline  void conversion_regular_channels_start_wait() const {  while ( conversion_regular_channels_state() == control_2_t::conversion_regular_channels_state_t::start) {} }
  inline  void conversion_regular_channels_start_and_wait()
      {
         conversion_regular_channels_start();
         while ( conversion_regular_channels_state() == control_2_t::conversion_regular_channels_state_t::start) {}
      }


  enum sampling_time_t { cycles_3=0, cycles_15, cycles_28, cycles_56, cycles_84, cycles_112, cycles_144, cycles_480 };
  struct sample_time_1_t : public read_write_32_t
  {
    struct channel_10_t { enum enum_t { offset=0, mask=0b111, };};
    struct channel_11_t { enum enum_t { offset=3, mask=0b111, };};
    struct channel_12_t { enum enum_t { offset=6, mask=0b111, };};
    struct channel_13_t { enum enum_t { offset=9, mask=0b111, };};
    struct channel_14_t { enum enum_t { offset=12,mask=0b111, };};
    struct channel_15_t { enum enum_t { offset=15,mask=0b111, };};
    struct channel_16_t { enum enum_t { offset=18,mask=0b111, };};
    struct channel_17_t { enum enum_t { offset=21,mask=0b111, };};
    struct channel_18_t { enum enum_t { offset=24,mask=0b111, };};
  } ;

  inline  void channel_10_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t)val) ;}
  inline  void channel_10_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_3  ) ;}
  inline  void channel_10_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_15 ) ;}
  inline  void channel_10_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_28 ) ;}
  inline  void channel_10_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_56 ) ;}
  inline  void channel_10_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_84 ) ;}
  inline  void channel_10_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_112) ;}
  inline  void channel_10_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_144) ;}
  inline  void channel_10_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_10_t::enum_t) cycles_480) ;}
  inline  auto channel_10_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_10_t> ();}

  inline  void channel_11_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t)val) ;}
  inline  void channel_11_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_3  ) ;}
  inline  void channel_11_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_15 ) ;}
  inline  void channel_11_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_28 ) ;}
  inline  void channel_11_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_56 ) ;}
  inline  void channel_11_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_84 ) ;}
  inline  void channel_11_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_112) ;}
  inline  void channel_11_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_144) ;}
  inline  void channel_11_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_11_t::enum_t) cycles_480) ;}
  inline  auto channel_11_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_11_t> ();}

  inline  void channel_12_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t)val) ;}
  inline  void channel_12_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_3  ) ;}
  inline  void channel_12_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_15 ) ;}
  inline  void channel_12_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_28 ) ;}
  inline  void channel_12_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_56 ) ;}
  inline  void channel_12_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_84 ) ;}
  inline  void channel_12_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_112) ;}
  inline  void channel_12_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_144) ;}
  inline  void channel_12_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_12_t::enum_t) cycles_480) ;}
  inline  auto channel_12_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_12_t> ();}

  inline  void channel_13_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t)val) ;}
  inline  void channel_13_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_3  ) ;}
  inline  void channel_13_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_15 ) ;}
  inline  void channel_13_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_28 ) ;}
  inline  void channel_13_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_56 ) ;}
  inline  void channel_13_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_84 ) ;}
  inline  void channel_13_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_112) ;}
  inline  void channel_13_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_144) ;}
  inline  void channel_13_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_13_t::enum_t) cycles_480) ;}
  inline  auto channel_13_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_13_t> ();}

  inline  void channel_14_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t)val) ;}
  inline  void channel_14_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_3  ) ;}
  inline  void channel_14_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_15 ) ;}
  inline  void channel_14_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_28 ) ;}
  inline  void channel_14_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_56 ) ;}
  inline  void channel_14_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_84 ) ;}
  inline  void channel_14_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_112) ;}
  inline  void channel_14_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_144) ;}
  inline  void channel_14_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_14_t::enum_t) cycles_480) ;}
  inline  auto channel_14_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_14_t> ();}

  inline  void channel_15_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t)val) ;}
  inline  void channel_15_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_3  ) ;}
  inline  void channel_15_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_15 ) ;}
  inline  void channel_15_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_28 ) ;}
  inline  void channel_15_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_56 ) ;}
  inline  void channel_15_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_84 ) ;}
  inline  void channel_15_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_112) ;}
  inline  void channel_15_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_144) ;}
  inline  void channel_15_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_15_t::enum_t) cycles_480) ;}
  inline  auto channel_15_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_15_t> ();}

  inline  void channel_16_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t)val) ;}
  inline  void channel_16_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_3  ) ;}
  inline  void channel_16_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_15 ) ;}
  inline  void channel_16_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_28 ) ;}
  inline  void channel_16_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_56 ) ;}
  inline  void channel_16_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_84 ) ;}
  inline  void channel_16_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_112) ;}
  inline  void channel_16_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_144) ;}
  inline  void channel_16_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_16_t::enum_t) cycles_480) ;}
  inline  auto channel_16_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_16_t> ();}

  inline  void channel_17_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t)val) ;}
  inline  void channel_17_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_3  ) ;}
  inline  void channel_17_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_15 ) ;}
  inline  void channel_17_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_28 ) ;}
  inline  void channel_17_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_56 ) ;}
  inline  void channel_17_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_84 ) ;}
  inline  void channel_17_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_112) ;}
  inline  void channel_17_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_144) ;}
  inline  void channel_17_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_17_t::enum_t) cycles_480) ;}
  inline  auto channel_17_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_17_t> ();}

  inline  void channel_18_sampling_time( const sampling_time_t val){  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t)val) ;}
  inline  void channel_18_sampling_time_cycles_3()  {  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_3  ) ;}
  inline  void channel_18_sampling_time_cycles_15() {  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_15 ) ;}
  inline  void channel_18_sampling_time_cycles_28() {  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_28 ) ;}
  inline  void channel_18_sampling_time_cycles_56() {  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_56 ) ;}
  inline  void channel_18_sampling_time_cycles_84() {  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_84 ) ;}
  inline  void channel_18_sampling_time_cycles_112(){  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_112) ;}
  inline  void channel_18_sampling_time_cycles_144(){  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_144) ;}
  inline  void channel_18_sampling_time_cycles_480(){  sample_time_1.rmw( (sample_time_1_t::channel_18_t::enum_t) cycles_480) ;}
  inline  auto channel_18_sampling_time() const {  return (sampling_time_t) sample_time_1.rd<sample_time_1_t::channel_18_t> ();}

  struct sample_time_2_t : public read_write_32_t
  {

    struct channel_0_t { enum enum_t { offset=0, mask=0b111, };};
    struct channel_1_t { enum enum_t { offset=3, mask=0b111, };};
    struct channel_2_t { enum enum_t { offset=6, mask=0b111, };};
    struct channel_3_t { enum enum_t { offset=9, mask=0b111, };};
    struct channel_4_t { enum enum_t { offset=12,mask=0b111, };};
    struct channel_5_t { enum enum_t { offset=15,mask=0b111, };};
    struct channel_6_t { enum enum_t { offset=18,mask=0b111, };};
    struct channel_7_t { enum enum_t { offset=21,mask=0b111, };};
    struct channel_8_t { enum enum_t { offset=24,mask=0b111, };};
    struct channel_9_t { enum enum_t { offset=27,mask=0b111, };};
  } ;

  inline  void channel_0_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t)val) ;}
  inline  void channel_0_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_3  ) ;}
  inline  void channel_0_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_15 ) ;}
  inline  void channel_0_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_28 ) ;}
  inline  void channel_0_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_56 ) ;}
  inline  void channel_0_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_84 ) ;}
  inline  void channel_0_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_112) ;}
  inline  void channel_0_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_144) ;}
  inline  void channel_0_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_0_t::enum_t) cycles_480) ;}
  inline  auto channel_0_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_0_t> ();}

  inline  void channel_1_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t)val) ;}
  inline  void channel_1_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_3  ) ;}
  inline  void channel_1_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_15 ) ;}
  inline  void channel_1_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_28 ) ;}
  inline  void channel_1_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_56 ) ;}
  inline  void channel_1_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_84 ) ;}
  inline  void channel_1_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_112) ;}
  inline  void channel_1_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_144) ;}
  inline  void channel_1_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_1_t::enum_t) cycles_480) ;}
  inline  auto channel_1_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_1_t> ();}

  inline  void channel_2_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t)val) ;}
  inline  void channel_2_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_3  ) ;}
  inline  void channel_2_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_15 ) ;}
  inline  void channel_2_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_28 ) ;}
  inline  void channel_2_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_56 ) ;}
  inline  void channel_2_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_84 ) ;}
  inline  void channel_2_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_112) ;}
  inline  void channel_2_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_144) ;}
  inline  void channel_2_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_2_t::enum_t) cycles_480) ;}
  inline  auto channel_2_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_2_t> ();}

  inline  void channel_3_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t)val) ;}
  inline  void channel_3_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_3  ) ;}
  inline  void channel_3_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_15 ) ;}
  inline  void channel_3_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_28 ) ;}
  inline  void channel_3_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_56 ) ;}
  inline  void channel_3_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_84 ) ;}
  inline  void channel_3_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_112) ;}
  inline  void channel_3_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_144) ;}
  inline  void channel_3_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_3_t::enum_t) cycles_480) ;}
  inline  auto channel_3_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_3_t> ();}

  inline  void channel_4_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t)val) ;}
  inline  void channel_4_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_3  ) ;}
  inline  void channel_4_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_15 ) ;}
  inline  void channel_4_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_28 ) ;}
  inline  void channel_4_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_56 ) ;}
  inline  void channel_4_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_84 ) ;}
  inline  void channel_4_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_112) ;}
  inline  void channel_4_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_144) ;}
  inline  void channel_4_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_4_t::enum_t) cycles_480) ;}
  inline  auto channel_4_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_4_t> ();}

  inline  void channel_5_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t)val) ;}
  inline  void channel_5_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_3  ) ;}
  inline  void channel_5_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_15 ) ;}
  inline  void channel_5_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_28 ) ;}
  inline  void channel_5_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_56 ) ;}
  inline  void channel_5_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_84 ) ;}
  inline  void channel_5_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_112) ;}
  inline  void channel_5_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_144) ;}
  inline  void channel_5_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_5_t::enum_t) cycles_480) ;}
  inline  auto channel_5_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_5_t> ();}

  inline  void channel_6_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t)val) ;}
  inline  void channel_6_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_3  ) ;}
  inline  void channel_6_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_15 ) ;}
  inline  void channel_6_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_28 ) ;}
  inline  void channel_6_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_56 ) ;}
  inline  void channel_6_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_84 ) ;}
  inline  void channel_6_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_112) ;}
  inline  void channel_6_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_144) ;}
  inline  void channel_6_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_6_t::enum_t) cycles_480) ;}
  inline  auto channel_6_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_6_t> ();}

  inline  void channel_7_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t)val) ;}
  inline  void channel_7_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_3  ) ;}
  inline  void channel_7_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_15 ) ;}
  inline  void channel_7_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_28 ) ;}
  inline  void channel_7_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_56 ) ;}
  inline  void channel_7_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_84 ) ;}
  inline  void channel_7_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_112) ;}
  inline  void channel_7_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_144) ;}
  inline  void channel_7_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_7_t::enum_t) cycles_480) ;}
  inline  auto channel_7_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_7_t> ();}

  inline  void channel_8_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t)val) ;}
  inline  void channel_8_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_3  ) ;}
  inline  void channel_8_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_15 ) ;}
  inline  void channel_8_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_28 ) ;}
  inline  void channel_8_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_56 ) ;}
  inline  void channel_8_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_84 ) ;}
  inline  void channel_8_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_112) ;}
  inline  void channel_8_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_144) ;}
  inline  void channel_8_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_8_t::enum_t) cycles_480) ;}
  inline  auto channel_8_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_8_t> ();}

  inline  void channel_9_sampling_time( const sampling_time_t val){  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t)val) ;}
  inline  void channel_9_sampling_time_cycles_3()  {  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_3  ) ;}
  inline  void channel_9_sampling_time_cycles_15() {  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_15 ) ;}
  inline  void channel_9_sampling_time_cycles_28() {  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_28 ) ;}
  inline  void channel_9_sampling_time_cycles_56() {  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_56 ) ;}
  inline  void channel_9_sampling_time_cycles_84() {  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_84 ) ;}
  inline  void channel_9_sampling_time_cycles_112(){  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_112) ;}
  inline  void channel_9_sampling_time_cycles_144(){  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_144) ;}
  inline  void channel_9_sampling_time_cycles_480(){  sample_time_2.rmw( (sample_time_2_t::channel_9_t::enum_t) cycles_480) ;}
  inline  auto channel_9_sampling_time() const {  return (sampling_time_t) sample_time_2.rd<sample_time_2_t::channel_9_t> ();}



  struct regular_sequence_1_t : public read_write_32_t
   {
     struct conversion_13_t { enum enum_t { offset=0, mask=0b11111 };};
     struct conversion_14_t { enum enum_t { offset=5, mask=0b11111 };};
     struct conversion_15_t { enum enum_t { offset=10,mask=0b11111 };};
     struct conversion_16_t { enum enum_t { offset=15,mask=0b11111 };};
     struct length_t        { enum enum_t { offset=20,mask=0b1111  };};
   };
  struct regular_sequence_2_t : public read_write_32_t
   {
     struct conversion_7_t  { enum enum_t { offset=0, mask=0b11111 };};
     struct conversion_8_t  { enum enum_t { offset=5, mask=0b11111 };};
     struct conversion_9_t  { enum enum_t { offset=10,mask=0b11111 };};
     struct conversion_10_t { enum enum_t { offset=15,mask=0b11111 };};
     struct conversion_11_t { enum enum_t { offset=20,mask=0b11111 };};
     struct conversion_12_t { enum enum_t { offset=25,mask=0b11111 };};
   };
  struct regular_sequence_3_t : public read_write_32_t
   {
     struct conversion_1_t  { enum enum_t { offset=0, mask=0b11111 };};
     struct conversion_2_t  { enum enum_t { offset=5, mask=0b11111 };};
     struct conversion_3_t  { enum enum_t { offset=10,mask=0b11111 };};
     struct conversion_4_t  { enum enum_t { offset=15,mask=0b11111 };};
     struct conversion_5_t  { enum enum_t { offset=20,mask=0b11111 };};
     struct conversion_6_t  { enum enum_t { offset=25,mask=0b11111 };};
   };

  inline  void regular_sequence_length( const uint8_t val){  regular_sequence_1.rmw( (regular_sequence_1_t::length_t::enum_t)(val - 1)) ;}
  inline  auto regular_sequence_length() const {  return ((uint8_t)regular_sequence_1.rd<regular_sequence_1_t::length_t> ()) + 1 ;}

  inline  void regular_sequence_1_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_1_t::enum_t)val) ;}
  inline  auto regular_sequence_1_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_1_t> ();}

  inline  void regular_sequence_2_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_2_t::enum_t)val) ;}
  inline  auto regular_sequence_2_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_2_t> ();}

  inline  void regular_sequence_3_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_3_t::enum_t)val) ;}
  inline  auto regular_sequence_3_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_3_t> ();}

  inline  void regular_sequence_4_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_4_t::enum_t)val) ;}
  inline  auto regular_sequence_4_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_4_t> ();}

  inline  void regular_sequence_5_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_5_t::enum_t)val) ;}
  inline  auto regular_sequence_5_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_5_t> ();}

  inline  void regular_sequence_6_converion_channel( const uint8_t val){  regular_sequence_3.rmw( (regular_sequence_3_t::conversion_6_t::enum_t)val) ;}
  inline  auto regular_sequence_6_converion_channel() const {  return (uint8_t)regular_sequence_3.rd<regular_sequence_3_t::conversion_6_t> ();}

  inline  void regular_sequence_7_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_7_t::enum_t)val) ;}
  inline  auto regular_sequence_7_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_7_t> ();}

  inline  void regular_sequence_8_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_8_t::enum_t)val) ;}
  inline  auto regular_sequence_8_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_8_t> ();}

  inline  void regular_sequence_9_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_9_t::enum_t)val) ;}
  inline  auto regular_sequence_9_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_9_t> ();}

  inline  void regular_sequence_10_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_10_t::enum_t)val) ;}
  inline  auto regular_sequence_10_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_10_t> ();}

  inline  void regular_sequence_11_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_11_t::enum_t)val) ;}
  inline  auto regular_sequence_11_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_11_t> ();}

  inline  void regular_sequence_12_converion_channel( const uint8_t val){  regular_sequence_2.rmw( (regular_sequence_2_t::conversion_12_t::enum_t)val) ;}
  inline  auto regular_sequence_12_converion_channel() const {  return (uint8_t)regular_sequence_2.rd<regular_sequence_2_t::conversion_12_t> ();}

  inline  void regular_sequence_13_converion_channel( const uint8_t val){  regular_sequence_1.rmw( (regular_sequence_1_t::conversion_13_t::enum_t)val) ;}
  inline  auto regular_sequence_13_converion_channel() const {  return (uint8_t)regular_sequence_1.rd<regular_sequence_1_t::conversion_13_t> ();}

  inline  void regular_sequence_14_converion_channel( const uint8_t val){  regular_sequence_1.rmw( (regular_sequence_1_t::conversion_14_t::enum_t)val) ;}
  inline  auto regular_sequence_14_converion_channel() const {  return (uint8_t)regular_sequence_1.rd<regular_sequence_1_t::conversion_14_t> ();}

  inline  void regular_sequence_15_converion_channel( const uint8_t val){  regular_sequence_1.rmw( (regular_sequence_1_t::conversion_15_t::enum_t)val) ;}
  inline  auto regular_sequence_15_converion_channel() const {  return (uint8_t)regular_sequence_1.rd<regular_sequence_1_t::conversion_15_t> ();}

  inline  void regular_sequence_16_converion_channel( const uint8_t val){  regular_sequence_1.rmw( (regular_sequence_1_t::conversion_16_t::enum_t)val) ;}
  inline  auto regular_sequence_16_converion_channel() const {  return (uint8_t)regular_sequence_1.rd<regular_sequence_1_t::conversion_16_t> ();}

  struct injected_sequence_t : public read_write_32_t
   {
      struct conversion_1_t { enum enum_t { offset=0, mask=0b11111 };};
      struct conversion_2_t { enum enum_t { offset=5, mask=0b11111 };};
      struct conversion_3_t { enum enum_t { offset=10,mask=0b11111 };};
      struct conversion_4_t { enum enum_t { offset=15,mask=0b11111 };};
      struct length_t       { enum enum_t { offset=20,mask=0b11  };};
   };

  inline  void injected_sequence_length( const uint8_t val){  injected_sequence.rmw( (injected_sequence_t::length_t::enum_t)(val - 1)) ;}
  inline  auto injected_sequence_length() const {  return (uint8_t)injected_sequence.rd<injected_sequence_t::length_t> () + 1;}

  inline  void injected_sequence_1_converion_channel( const uint8_t val){  injected_sequence.rmw( (injected_sequence_t::conversion_1_t::enum_t)val) ;}
  inline  auto injected_sequence_1_converion_channel() const {  return (uint8_t)injected_sequence.rd<injected_sequence_t::conversion_1_t> ();}

  inline  void injected_sequence_2_converion_channel( const uint8_t val){  injected_sequence.rmw( (injected_sequence_t::conversion_2_t::enum_t)val) ;}
  inline  auto injected_sequence_2_converion_channel() const {  return (uint8_t)injected_sequence.rd<injected_sequence_t::conversion_2_t> ();}

  inline  void injected_sequence_3_converion_channel( const uint8_t val){  injected_sequence.rmw( (injected_sequence_t::conversion_3_t::enum_t)val) ;}
  inline  auto injected_sequence_3_converion_channel() const {  return (uint8_t)injected_sequence.rd<injected_sequence_t::conversion_3_t> ();}

  inline  void injected_sequence_4_converion_channel( const uint8_t val){  injected_sequence.rmw( (injected_sequence_t::conversion_4_t::enum_t)val) ;}
  inline  auto injected_sequence_4_converion_channel() const {  return (uint8_t)injected_sequence.rd<injected_sequence_t::conversion_4_t> ();}

  status_t             status ;                        //SR;     /*!< ADC status register,                         Address offset: 0x00 */
  control_1_t          control_1 ;                     //CR1;    /*!< ADC control register 1,                      Address offset: 0x04 */
  control_2_t          control_2 ;                     //CR2;    /*!< ADC control register 2,                      Address offset: 0x08 */
  sample_time_1_t      sample_time_1;                  //SMPR1;  /*!< ADC sample time register 1,                  Address offset: 0x0C */
  sample_time_2_t      sample_time_2;                  //SMPR2;  /*!< ADC sample time register 2,                  Address offset: 0x10 */
  volatile uint32_t    injected_channel_data_offset_1; //JOFR1;  /*!< ADC injected channel data offset register 1, Address offset: 0x14 */
  volatile uint32_t    injected_channel_data_offset_2; //JOFR2;  /*!< ADC injected channel data offset register 2, Address offset: 0x18 */
  volatile uint32_t    injected_channel_data_offset_3; //JOFR3;  /*!< ADC injected channel data offset register 3, Address offset: 0x1C */
  volatile uint32_t    injected_channel_data_offset_4; //JOFR4;  /*!< ADC injected channel data offset register 4, Address offset: 0x20 */
  volatile uint32_t    watchdog_higher_threshold;      //HTR;    /*!< ADC watchdog higher threshold register,      Address offset: 0x24 */
  volatile uint32_t    watchdog_low_threshold;         //LTR;    /*!< ADC watchdog lower threshold register,       Address offset: 0x28 */
  regular_sequence_1_t regular_sequence_1;             //SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x2C */
  regular_sequence_2_t regular_sequence_2;             //SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x30 */
  regular_sequence_3_t regular_sequence_3;             //SQR3;   /*!< ADC regular sequence register 3,             Address offset: 0x34 */
  injected_sequence_t  injected_sequence;              //JSQR;   /*!< ADC injected sequence register,              Address offset: 0x38*/
  volatile uint32_t    injected_data_1;                //JDR1;   /*!< ADC injected data register 1,                Address offset: 0x3C */
  volatile uint32_t    injected_data_2;                //JDR2;   /*!< ADC injected data register 2,                Address offset: 0x40 */
  volatile uint32_t    injected_data_3;                //JDR3;   /*!< ADC injected data register 3,                Address offset: 0x44 */
  volatile uint32_t    injected_data_4;                //JDR4;   /*!< ADC injected data register 4,                Address offset: 0x48 */
  volatile uint32_t    regular_data;                   //DR;     /*!< ADC regular data register,                   Address offset: 0x4C */

  inline void clock_enable() {  rcc.state_enable ( (rcc_t::apb2_peripheral_clock_t::peripheral_t) ( rcc_t::apb2_peripheral_clock_t::peripheral_t::adc_converter_1 + ((uint32_t)this - adc_addr) / adc_converter_size)  ) ; }
  inline void clock_disable(){  rcc.state_disable( (rcc_t::apb2_peripheral_clock_t::peripheral_t) ( rcc_t::apb2_peripheral_clock_t::peripheral_t::adc_converter_1 + ((uint32_t)this - adc_addr) / adc_converter_size)  ) ; }

} ;

}

// доопределение особенностей adc_converter_v1_t + 'options' -> adc_converter_t в рамках семейства
#include "adc_converter++.h"

// определение adc_t:   adc_converter_t >> adc_t
#include "adc_v1++.h"

#endif /* __ADC_CONVERTER_V1++_H__ */
