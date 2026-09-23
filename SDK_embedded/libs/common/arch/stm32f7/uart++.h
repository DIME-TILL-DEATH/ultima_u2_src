/*
 * uart++.h
 *
 *  Created on: дек. 2019 г.
 *      Author: klen
 */

#ifndef __UART++_H__
#define __UART++_H__


#include "types++.h"
#include "rcc++.h"

namespace stm32f7
{
  struct uart_t
  {

    struct control_1_t : public read_write_32_t
    {
       struct state_t                   { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
       struct state_in_stop_mode_t      { enum enum_t { offset=1, mask=1, disable=0, enable} ; } ;
       struct receiver_t                { enum enum_t { offset=2, mask=1, disable=0, enable} ; } ;
       struct transmitter_t             { enum enum_t { offset=3, mask=1, disable=0, enable} ; } ;
       struct idle_interupt_t           { enum enum_t { offset=4, mask=1, disable=0, enable} ; } ;
       struct rx_not_empty_interupt_t   { enum enum_t { offset=5, mask=1, disable=0, enable} ; } ;
       struct tx_complete_interrupt_t   { enum enum_t { offset=6, mask=1, disable=0, enable} ; } ;
       struct tx_empty_interrupt_t      { enum enum_t { offset=7, mask=1, disable=0, enable} ; } ;
       struct parity_error_interrupt_t  { enum enum_t { offset=8, mask=1, disable=0, enable} ; } ;
       struct parity_selection_t        { enum enum_t { offset=9, mask=1, even=0, odd} ; } ;
       struct parity_control_t          { enum enum_t { offset=10, mask=1, disable=0, enable} ; } ;
       struct wakeup_method_t           { enum enum_t { offset=11, mask=1, idle_line=0, address_mark } ; } ;
       struct word_length_1_t           { enum enum_t { offset=12, mask=1, bits8=0, bits9, bits7} ; } ;
       struct mute_mode_t               { enum enum_t { offset=13, mask=1, disable=0, enable} ; } ;
       struct character_match_interrupt_t { enum enum_t { offset=14, mask=1, disable=0, enable} ; } ;
       struct oversampling_mode_t       { enum enum_t { offset=15, mask=1, x16=0, x8} ; } ;
       struct driver_enable_deassertion_time_t { enum enum_t { offset=16, mask=0b11111, } ; } ;
       struct driver_enable_assertion_time_t { enum enum_t { offset=21, mask=0b11111, } ; } ;
       struct receiver_timeout_interrupt_t   { enum enum_t { offset=26, mask=1, disable=0, enable} ; } ;
       struct end_of_block_interrupt_t  { enum enum_t { offset=27, mask=1, disable=0, enable} ; } ;
       struct word_length_2_t           { enum enum_t { offset=28, mask=1, } ; } ;
    };

  inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
  inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
  inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
  inline auto state() const { return control_1.rd<control_1_t::state_t>();}

  inline void state_in_stop_mode(const control_1_t::state_in_stop_mode_t::enum_t val) {  control_1.rmw( val );}
  inline void enable_in_stop_mode() { control_1.rmw( control_1_t::state_in_stop_mode_t::enable );}
  inline void disable_in_stop_mode() { control_1.rmw( control_1_t::state_in_stop_mode_t::disable );}
  inline auto state_in_stop_mode() const { return control_1.rd<control_1_t::state_in_stop_mode_t>();}

  inline void receiver(const control_1_t::receiver_t::enum_t val) { control_1.rmw(val);}
  inline void receiver_disable() { control_1.rmw(control_1_t::receiver_t::disable);}
  inline void receiver_enable() { control_1.rmw(control_1_t::receiver_t::enable);}
  inline auto receiver() const {  return control_1.rd<control_1_t::receiver_t> ();}

  inline void transmitter(const control_1_t::transmitter_t::enum_t val) { control_1.rmw(val);}
  inline void transmitter_disable() { control_1.rmw(control_1_t::transmitter_t::disable);}
  inline void transmitter_enable() { control_1.rmw(control_1_t::transmitter_t::enable);}
  inline auto transmitter() const {  return control_1.rd<control_1_t::transmitter_t> ();}

  inline void idle_interupt(const control_1_t::idle_interupt_t::enum_t val) { control_1.rmw(val);}
  inline void idle_interupt_disable() { control_1.rmw(control_1_t::idle_interupt_t::disable);}
  inline void idle_interupt_enable() { control_1.rmw(control_1_t::idle_interupt_t::enable);}
  inline auto idle_interupt() const {  return control_1.rd<control_1_t::idle_interupt_t> ();}

  inline void rx_not_empty_interupt(const control_1_t::rx_not_empty_interupt_t::enum_t val) { control_1.rmw(val);}
  inline void rx_not_empty_interupt_disable() { control_1.rmw(control_1_t::rx_not_empty_interupt_t::disable);}
  inline void rx_not_empty_interupt_enable() { control_1.rmw(control_1_t::rx_not_empty_interupt_t::enable);}
  inline auto rx_not_empty_interupt() const {  return control_1.rd<control_1_t::rx_not_empty_interupt_t> ();}

  inline void tx_complete_interrupt(const control_1_t::tx_complete_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void tx_complete_interrupt_disable() { control_1.rmw(control_1_t::tx_complete_interrupt_t::disable);}
  inline void tx_complete_interrupt_enable() { control_1.rmw(control_1_t::tx_complete_interrupt_t::enable);}
  inline auto tx_complete_interrupt() const {  return control_1.rd<control_1_t::tx_complete_interrupt_t> ();}

  inline void tx_empty_interrupt(const control_1_t::tx_empty_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void tx_empty_interrupt_disable() { control_1.rmw(control_1_t::tx_empty_interrupt_t::disable);}
  inline void tx_empty_interrupt_enable() { control_1.rmw(control_1_t::tx_empty_interrupt_t::enable);}
  inline auto tx_empty_interrupt() const {  return control_1.rd<control_1_t::tx_empty_interrupt_t> ();}

  inline void parity_error_interrupt(const control_1_t::parity_error_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void parity_error_interrupt_disable() { control_1.rmw(control_1_t::parity_error_interrupt_t::disable);}
  inline void parity_error_interrupt_enable() { control_1.rmw(control_1_t::parity_error_interrupt_t::enable);}
  inline auto parity_error_interrupt() const {  return control_1.rd<control_1_t::parity_error_interrupt_t> ();}

  inline void parity_selection(const control_1_t::parity_selection_t::enum_t val) { control_1.rmw(val);}
  inline void parity_selection_even() { control_1.rmw(control_1_t::parity_selection_t::even);}
  inline void parity_selection_odd() { control_1.rmw(control_1_t::parity_selection_t::odd);}
  inline auto parity_selection() const {  return control_1.rd<control_1_t::parity_selection_t> ();}

  inline void parity_control(const control_1_t::parity_control_t::enum_t val) { control_1.rmw(val);}
  inline void parity_control_disable() { control_1.rmw(control_1_t::parity_control_t::disable);}
  inline void parity_control_enable() { control_1.rmw(control_1_t::parity_control_t::enable);}
  inline auto parity_control() const {  return control_1.rd<control_1_t::parity_control_t> ();}

  inline void wakeup_method(const control_1_t::wakeup_method_t::enum_t val) { control_1.rmw(val);}
  inline void wakeup_method_idle_line() { control_1.rmw(control_1_t::wakeup_method_t::idle_line);}
  inline void wakeup_method_address_mark() { control_1.rmw(control_1_t::wakeup_method_t::address_mark);}
  inline auto wakeup_method() const {  return control_1.rd<control_1_t::wakeup_method_t> ();}

  inline void word_length(const control_1_t::word_length_1_t::enum_t val)
     {
       switch ( val )
       {
	 case control_1_t::word_length_1_t::bits8 :
	   control_1.rmw((control_1_t::word_length_1_t::enum_t)0);
	   control_1.rmw((control_1_t::word_length_2_t::enum_t)0);
	   break;
	 case control_1_t::word_length_1_t::bits9 :
	   control_1.rmw((control_1_t::word_length_1_t::enum_t)0);
	   control_1.rmw((control_1_t::word_length_2_t::enum_t)1);
	   break;
	 case control_1_t::word_length_1_t::bits7 :
	   control_1.rmw((control_1_t::word_length_1_t::enum_t)1);
	   control_1.rmw((control_1_t::word_length_2_t::enum_t)0);
	   break;
	 default:
	   break;
       }
     }
  inline void word_length_bits8() { control_1.rmw((control_1_t::word_length_1_t::enum_t)0); control_1.rmw((control_1_t::word_length_2_t::enum_t)0);}
  inline void word_length_bits9() { control_1.rmw((control_1_t::word_length_1_t::enum_t)0); control_1.rmw((control_1_t::word_length_2_t::enum_t)1);}
  inline void word_length_bits7() { control_1.rmw((control_1_t::word_length_1_t::enum_t)1); control_1.rmw((control_1_t::word_length_2_t::enum_t)0);}
  inline auto word_length() const { return (control_1_t::word_length_1_t::enum_t)((uint8_t)control_1.rd<control_1_t::word_length_1_t>() | ((uint8_t)control_1.rd<control_1_t::word_length_2_t>())<<1 ) ; }


  inline void mute_mode(const control_1_t::mute_mode_t::enum_t val) { control_1.rmw(val);}
  inline void mute_mode_disable() { control_1.rmw(control_1_t::mute_mode_t::disable);}
  inline void mute_mode_enable() { control_1.rmw(control_1_t::mute_mode_t::enable);}
  inline auto mute_mode() const {  return control_1.rd<control_1_t::mute_mode_t> ();}

  inline void character_match_interrupt(const control_1_t::character_match_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void character_match_interrupt_disable() { control_1.rmw(control_1_t::character_match_interrupt_t::disable);}
  inline void character_match_interrupt_enable() { control_1.rmw(control_1_t::character_match_interrupt_t::enable);}
  inline auto character_match_interrupt() const {  return control_1.rd<control_1_t::character_match_interrupt_t> ();}

  inline void oversampling_mode(const control_1_t::oversampling_mode_t::enum_t val) { control_1.rmw(val);}
  inline void oversampling_mode_x8() { control_1.rmw(control_1_t::oversampling_mode_t::x8);}
  inline void oversampling_mode_x16() { control_1.rmw(control_1_t::oversampling_mode_t::x16);}
  inline auto oversampling_mode() const {  return control_1.rd<control_1_t::oversampling_mode_t> ();}

  inline void driver_enable_deassertion_time(const uint8_t val) { control_1.rmw((control_1_t::driver_enable_deassertion_time_t::enum_t)val);}
  inline auto driver_enable_deassertion_time() const {  return (uint8_t)control_1.rd<control_1_t::driver_enable_deassertion_time_t> ();}

  inline void driver_enable_assertion_time(const uint8_t val) { control_1.rmw((control_1_t::driver_enable_assertion_time_t::enum_t)val);}
  inline auto driver_enable_assertion_time() const {  return (uint8_t)control_1.rd<control_1_t::driver_enable_assertion_time_t> ();}

  inline void receiver_timeout_interrupt(const control_1_t::receiver_timeout_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void receiver_timeout_interrupt_disable() { control_1.rmw(control_1_t::receiver_timeout_interrupt_t::disable);}
  inline void receiver_timeout_interrupt_enable() { control_1.rmw(control_1_t::receiver_timeout_interrupt_t::enable);}
  inline auto receiver_timeout_interrupt() const {  return control_1.rd<control_1_t::receiver_timeout_interrupt_t> ();}

  inline void end_of_block_interrupt(const control_1_t::end_of_block_interrupt_t::enum_t val) { control_1.rmw(val);}
  inline void end_of_block_interrupt_disable() { control_1.rmw(control_1_t::end_of_block_interrupt_t::disable);}
  inline void end_of_block_interrupt_enable() { control_1.rmw(control_1_t::end_of_block_interrupt_t::enable);}
  inline auto end_of_block_interrupt() const {  return control_1.rd<control_1_t::end_of_block_interrupt_t> ();}



  struct control_2_t : public read_write_32_t
    {
       struct addres_detection_t             { enum enum_t { offset=4, mask=1, bits4=0, bits7 } ; } ;
       struct lin_break_detection_length_t   { enum enum_t { offset=5, mask=1, bits10=0, bits11 } ; } ;
       struct lin_break_detection_inerrup_t  { enum enum_t { offset=6, mask=1, disable=0, enable } ; } ;
       struct last_bit_clk_pulse_t           { enum enum_t { offset=8, mask=1, disable=0, enable } ; } ;
       struct clk_phase_t                    { enum enum_t { offset=9, mask=1, first_clk_transition=0, second_clk_transition } ; } ;
       struct clk_polarity_t                 { enum enum_t { offset=10,mask=1, steady_low=0, steady_high } ; } ;
       struct clk_t                          { enum enum_t { offset=11,mask=1, disable=0, enable } ; } ;
       struct stop_bits_t                    { enum enum_t { offset=12,mask=0b11, stop_bit_1=0 , stop_bit_0_5, stop_bit_2, stop_bit_1_5 } ; } ;
       struct lin_mode_t                     { enum enum_t { offset=14,mask=1, disable=0, enable } ; } ;
       struct swap_tx_rx_pins_t              { enum enum_t { offset=15,mask=1, disable=0, enable } ; } ;
       struct rx_pin_level_inverse_t         { enum enum_t { offset=16,mask=1, disable=0, enable } ; } ;
       struct tx_pin_level_inverse_t         { enum enum_t { offset=17,mask=1, disable=0, enable } ; } ;
       struct data_inverse_t                 { enum enum_t { offset=18,mask=1, disable=0, enable } ; } ;
       struct msb_first_t                    { enum enum_t { offset=19,mask=1, disable=0, enable } ; } ;
       struct auto_baud_rate_t               { enum enum_t { offset=20,mask=1, disable=0, enable } ; } ;
       struct auto_baud_rate_mode_t          { enum enum_t { offset=21,mask=0b11, start_bit=0, falling_edge, frame_0x75, frame_0x55 } ; } ;
       struct receiver_timeout_t             { enum enum_t { offset=23,mask=1, disable=0, enable } ; } ;
       struct address_t                      { enum enum_t { offset=24,mask=0xff, } ; } ;
    };

  inline void addres_detection(const control_2_t::addres_detection_t::enum_t val) { control_2.rmw(val);}
  inline void addres_detection_bits4() { control_2.rmw(control_2_t::addres_detection_t::bits4);}
  inline void addres_detection_bits7() { control_2.rmw(control_2_t::addres_detection_t::bits7);}
  inline auto addres_detection() const {  return control_2.rd<control_2_t::addres_detection_t> ();}

  inline void lin_break_detection_length(const control_2_t::lin_break_detection_length_t::enum_t val) { control_2.rmw(val);}
  inline void lin_break_detection_length_bits10() { control_2.rmw(control_2_t::lin_break_detection_length_t::bits10);}
  inline void lin_break_detection_length_bits11() { control_2.rmw(control_2_t::lin_break_detection_length_t::bits11);}
  inline auto lin_break_detection_length() const {  return control_2.rd<control_2_t::lin_break_detection_length_t> ();}

  inline void lin_break_detection_inerrup(const control_2_t::lin_break_detection_inerrup_t::enum_t val) { control_2.rmw(val);}
  inline void lin_break_detection_inerrup_disable() { control_2.rmw(control_2_t::lin_break_detection_inerrup_t::disable);}
  inline void lin_break_detection_inerrup_enable() { control_2.rmw(control_2_t::lin_break_detection_inerrup_t::enable);}
  inline auto lin_break_detection_inerrup() const {  return control_2.rd<control_2_t::lin_break_detection_inerrup_t> ();}

  inline void last_bit_clk_pulse(const control_2_t::last_bit_clk_pulse_t::enum_t val) { control_2.rmw(val);}
  inline void last_bit_clk_pulse_disable() { control_2.rmw(control_2_t::last_bit_clk_pulse_t::disable);}
  inline void last_bit_clk_pulse_enable() { control_2.rmw(control_2_t::last_bit_clk_pulse_t::enable);}
  inline auto last_bit_clk_pulse() const {  return control_2.rd<control_2_t::last_bit_clk_pulse_t> ();}

  inline void clk_phase(const control_2_t::clk_phase_t::enum_t val) { control_2.rmw(val);}
  inline void clk_phase_first_clock_transition() { control_2.rmw(control_2_t::clk_phase_t::first_clk_transition);}
  inline void clk_phase_second_clock_transition() { control_2.rmw(control_2_t::clk_phase_t::second_clk_transition);}
  inline auto clk_phase() const {  return control_2.rd<control_2_t::clk_phase_t> ();}

  inline void clk_polarity(const control_2_t::clk_polarity_t::enum_t val) { control_2.rmw(val);}
  inline void clk_polarity_steady_low() { control_2.rmw(control_2_t::clk_polarity_t::steady_low);}
  inline void clk_polarity_steady_high() { control_2.rmw(control_2_t::clk_polarity_t::steady_high);}
  inline auto clk_polarity() const {  return control_2.rd<control_2_t::clk_polarity_t> ();}

  inline void clk(const control_2_t::clk_t::enum_t val) { control_2.rmw(val);}
  inline void clk_disable() { control_2.rmw(control_2_t::clk_t::disable);}
  inline void clk_enable() { control_2.rmw(control_2_t::clk_t::enable);}
  inline auto clk() const {  return control_2.rd<control_2_t::clk_t> ();}

  inline void stop_bits(const control_2_t::stop_bits_t::enum_t val) { control_2.rmw(val);}
  inline void stop_bits_1() { control_2.rmw(control_2_t::stop_bits_t::stop_bit_1);}
  inline void stop_bits_0_5() { control_2.rmw(control_2_t::stop_bits_t::stop_bit_0_5);}
  inline void stop_bits_2() { control_2.rmw(control_2_t::stop_bits_t::stop_bit_2);}
  inline void stop_bits_1_5() { control_2.rmw(control_2_t::stop_bits_t::stop_bit_1_5);}
  inline auto stop_bits() const {  return control_2.rd<control_2_t::stop_bits_t> ();}

  inline void lin_mode(const control_2_t::lin_mode_t::enum_t val) { control_2.rmw(val);}
  inline void lin_mode_disable() { control_2.rmw(control_2_t::lin_mode_t::disable);}
  inline void lin_mode_enable() { control_2.rmw(control_2_t::lin_mode_t::enable);}
  inline auto lin_mode() const {  return control_2.rd<control_2_t::lin_mode_t> ();}

  inline void swap_tx_rx_pins(const control_2_t::swap_tx_rx_pins_t::enum_t val) { control_2.rmw(val);}
  inline void swap_tx_rx_pins_disable() { control_2.rmw(control_2_t::swap_tx_rx_pins_t::disable);}
  inline void swap_tx_rx_pins_enable() { control_2.rmw(control_2_t::swap_tx_rx_pins_t::enable);}
  inline auto swap_tx_rx_pins() const {  return control_2.rd<control_2_t::swap_tx_rx_pins_t> ();}

  inline void rx_pin_level_inverse(const control_2_t::rx_pin_level_inverse_t::enum_t val) { control_2.rmw(val);}
  inline void rx_pin_level_inverse_disable() { control_2.rmw(control_2_t::rx_pin_level_inverse_t::disable);}
  inline void rx_pin_level_inverse_enable() { control_2.rmw(control_2_t::rx_pin_level_inverse_t::enable);}
  inline auto rx_pin_level_inverse() const {  return control_2.rd<control_2_t::rx_pin_level_inverse_t> ();}

  inline void tx_pin_level_inverse(const control_2_t::tx_pin_level_inverse_t::enum_t val) { control_2.rmw(val);}
  inline void tx_pin_level_inverse_disable() { control_2.rmw(control_2_t::tx_pin_level_inverse_t::disable);}
  inline void tx_pin_level_inverse_enable() { control_2.rmw(control_2_t::tx_pin_level_inverse_t::enable);}
  inline auto tx_pin_level_inverse() const {  return control_2.rd<control_2_t::tx_pin_level_inverse_t> ();}

  inline void data_inverse(const control_2_t::data_inverse_t::enum_t val) { control_2.rmw(val);}
  inline void data_inverse_disable() { control_2.rmw(control_2_t::data_inverse_t::disable);}
  inline void data_inverse_enable() { control_2.rmw(control_2_t::data_inverse_t::enable);}
  inline auto data_inverse() const {  return control_2.rd<control_2_t::data_inverse_t> ();}

  inline void msb_first(const control_2_t::msb_first_t::enum_t val) { control_2.rmw(val);}
  inline void msb_first_disable() { control_2.rmw(control_2_t::msb_first_t::disable);}
  inline void msb_first_enable() { control_2.rmw(control_2_t::msb_first_t::enable);}
  inline auto msb_first() const {  return control_2.rd<control_2_t::msb_first_t> ();}

  inline void auto_baud_rate(const control_2_t::auto_baud_rate_t::enum_t val) { control_2.rmw(val);}
  inline void auto_baud_rate_disable() { control_2.rmw(control_2_t::auto_baud_rate_t::disable);}
  inline void auto_baud_rate_enable() { control_2.rmw(control_2_t::auto_baud_rate_t::enable);}
  inline auto auto_baud_rate() const {  return control_2.rd<control_2_t::auto_baud_rate_t> ();}

  inline void auto_baud_rate_mode(const control_2_t::auto_baud_rate_mode_t::enum_t val) { control_2.rmw(val);}
  inline void auto_baud_rate_mode_start_bit()    { control_2.rmw(control_2_t::auto_baud_rate_mode_t::start_bit);}
  inline void auto_baud_rate_mode_falling_edge() { control_2.rmw(control_2_t::auto_baud_rate_mode_t::falling_edge);}
  inline void auto_baud_rate_mode_frame_0x75()   { control_2.rmw(control_2_t::auto_baud_rate_mode_t::frame_0x75);}
  inline void auto_baud_rate_mode_frame_0x55()   { control_2.rmw(control_2_t::auto_baud_rate_mode_t::frame_0x55);}
  inline auto auto_baud_rate_mode() const {  return control_2.rd<control_2_t::auto_baud_rate_mode_t> ();}

  inline void receiver_timeout(const control_2_t::receiver_timeout_t::enum_t val) { control_2.rmw(val);}
  inline void receiver_timeout_disable() { control_2.rmw(control_2_t::receiver_timeout_t::disable);}
  inline void receiver_timeout_enable() { control_2.rmw(control_2_t::receiver_timeout_t::enable);}
  inline auto receiver_timeout() const {  return control_2.rd<control_2_t::receiver_timeout_t> ();}

  inline void address(const uint8_t val) { control_2.rmw((control_2_t::address_t::enum_t)val);}
  inline auto address() const {  return (uint8_t)control_1.rd<control_2_t::address_t> ();}



  struct control_3_t : public read_write_32_t
    {
       struct error_interrupt_t { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
       struct irda_mode_t       { enum enum_t { offset=1, mask=1, disable=0, enable} ; } ;
       struct irda_low_power_t  { enum enum_t { offset=2, mask=1, disable=0, enable} ; } ;
       struct half_duplex_t     { enum enum_t { offset=3, mask=1, disable=0, enable} ; } ;
       struct smartcard_nack_t  { enum enum_t { offset=4, mask=1, disable=0, enable} ; } ;
       struct smartcard_mode_t  { enum enum_t { offset=5, mask=1, disable=0, enable} ; } ;
       struct rx_dma_t          { enum enum_t { offset=6, mask=1, disable=0, enable} ; } ;
       struct tx_dma_t          { enum enum_t { offset=7, mask=1, disable=0, enable} ; } ;
       struct rts_t             { enum enum_t { offset=8, mask=1, disable=0, enable} ; } ;
       struct cts_t             { enum enum_t { offset=9, mask=1, disable=0, enable} ; } ;
       struct cts_interrupt_t   { enum enum_t { offset=10, mask=1, disable=0, enable} ; } ;
       struct one_sample_bit_method_t { enum enum_t { offset=11, mask=1, disable=0, enable} ; } ;
       struct overrun_t         { enum enum_t { offset=12, mask=1, enable=0, disable} ; } ;
       struct dma_on_rx_error_t { enum enum_t { offset=13, mask=1, enable=0, disable} ; } ;
       struct external_transceiver_control_t { enum enum_t { offset=14, mask=1, disable=0, enable} ; } ;
       struct external_transceiver_control_polarity_t { enum enum_t { offset=15, mask=1, active_high=0, active_low} ; } ;
       struct smartcard_autoretry_count_t { enum enum_t { offset=17,mask=0b111, } ; } ;
       struct wakeup_from_stop_mode_t { enum enum_t { offset=20, mask=0b11, address_match=0, start_bit_detection=2, rxne} ; } ;
       struct wakeup_from_stop_mode_interrupt_t { enum enum_t { offset=22, mask=1, disable=0, enable} ; } ;
       struct clock_in_stop_mode_t { enum enum_t { offset=23, mask=1, disable=0, enable} ; } ;
       struct tx_complete_before_guard_time_interrupt_t { enum enum_t { offset=24, mask=1, disable=0, enable} ; } ;
    };

  inline void error_interrupt(const control_3_t::error_interrupt_t::enum_t val) { control_3.rmw(val);}
  inline void error_interrupt_disable() { control_3.rmw(control_3_t::error_interrupt_t::disable);}
  inline void error_interrupt_enable() { control_3.rmw(control_3_t::error_interrupt_t::enable);}
  inline auto error_interrupt() const {  return control_3.rd<control_3_t::error_interrupt_t> ();}

  inline void irda_low_power(const control_3_t::irda_low_power_t::enum_t val) { control_3.rmw(val);}
  inline void irda_low_power_disable() { control_3.rmw(control_3_t::irda_low_power_t::disable);}
  inline void irda_low_power_enable() { control_3.rmw(control_3_t::irda_low_power_t::enable);}
  inline auto irda_low_power() const {  return control_3.rd<control_3_t::irda_low_power_t> ();}

  inline void half_duplex(const control_3_t::half_duplex_t::enum_t val) { control_3.rmw(val);}
  inline void half_duplex_disable() { control_3.rmw(control_3_t::half_duplex_t::disable);}
  inline void half_duplex_enable() { control_3.rmw(control_3_t::half_duplex_t::enable);}
  inline auto half_duplex() const {  return control_3.rd<control_3_t::half_duplex_t> ();}

  inline void smartcard_nack(const control_3_t::smartcard_nack_t::enum_t val) { control_3.rmw(val);}
  inline void smartcard_nack_disable() { control_3.rmw(control_3_t::smartcard_nack_t::disable);}
  inline void smartcard_nack_enable() { control_3.rmw(control_3_t::smartcard_nack_t::enable);}
  inline auto smartcard_nack() const {  return control_3.rd<control_3_t::smartcard_nack_t> ();}

  inline void smartcard_mode(const control_3_t::smartcard_mode_t::enum_t val) { control_3.rmw(val);}
  inline void smartcard_mode_disable() { control_3.rmw(control_3_t::smartcard_mode_t::disable);}
  inline void smartcard_mode_enable() { control_3.rmw(control_3_t::smartcard_mode_t::enable);}
  inline auto smartcard_mode() const {  return control_3.rd<control_3_t::smartcard_mode_t> ();}

  inline void rx_dma(const control_3_t::rx_dma_t::enum_t val) { control_3.rmw(val);}
  inline void rx_dma_disable() { control_3.rmw(control_3_t::rx_dma_t::disable);}
  inline void rx_dma_enable() { control_3.rmw(control_3_t::rx_dma_t::enable);}
  inline auto rx_dma() const {  return control_3.rd<control_3_t::rx_dma_t> ();}

  inline void tx_dma(const control_3_t::tx_dma_t::enum_t val) { control_3.rmw(val);}
  inline void tx_dma_disable() { control_3.rmw(control_3_t::tx_dma_t::disable);}
  inline void tx_dma_enable() { control_3.rmw(control_3_t::tx_dma_t::enable);}
  inline auto tx_dma() const {  return control_3.rd<control_3_t::tx_dma_t> ();}

  inline void rts(const control_3_t::rts_t::enum_t val) { control_3.rmw(val);}
  inline void rts_disable() { control_3.rmw(control_3_t::rts_t::disable);}
  inline void rts_enable() { control_3.rmw(control_3_t::rts_t::enable);}
  inline auto rts() const {  return control_3.rd<control_3_t::rts_t> ();}

  inline void cts(const control_3_t::cts_t::enum_t val) { control_3.rmw(val);}
  inline void cts_disable() { control_3.rmw(control_3_t::cts_t::disable);}
  inline void cts_enable() { control_3.rmw(control_3_t::cts_t::enable);}
  inline auto cts() const {  return control_3.rd<control_3_t::cts_t> ();}

  inline void cts_interrupt(const control_3_t::cts_interrupt_t::enum_t val) { control_3.rmw(val);}
  inline void cts_interrupt_disable() { control_3.rmw(control_3_t::cts_interrupt_t::disable);}
  inline void cts_interrupt_enable() { control_3.rmw(control_3_t::cts_interrupt_t::enable);}
  inline auto cts_interrupt() const {  return control_3.rd<control_3_t::cts_interrupt_t> ();}

  inline void one_sample_bit_method(const control_3_t::one_sample_bit_method_t::enum_t val) { control_3.rmw(val);}
  inline void one_sample_bit_method_disable() { control_3.rmw(control_3_t::one_sample_bit_method_t::disable);}
  inline void one_sample_bit_method_enable() { control_3.rmw(control_3_t::one_sample_bit_method_t::enable);}
  inline auto one_sample_bit_method() const {  return control_3.rd<control_3_t::one_sample_bit_method_t> ();}

  inline void overrun(const control_3_t::overrun_t::enum_t val) { control_3.rmw(val);}
  inline void overrun_disable() { control_3.rmw(control_3_t::overrun_t::disable);}
  inline void overrun_enable() { control_3.rmw(control_3_t::overrun_t::enable);}
  inline auto overrun() const {  return control_3.rd<control_3_t::overrun_t> ();}

  inline void dma_on_rx_error(const control_3_t::dma_on_rx_error_t::enum_t val) { control_3.rmw(val);}
  inline void dma_on_rx_error_disable() { control_3.rmw(control_3_t::dma_on_rx_error_t::disable);}
  inline void dma_on_rx_error_enable() { control_3.rmw(control_3_t::dma_on_rx_error_t::enable);}
  inline auto dma_on_rx_error() const {  return control_3.rd<control_3_t::dma_on_rx_error_t> ();}

  inline void external_transceiver_control(const control_3_t::external_transceiver_control_t::enum_t val) { control_3.rmw(val);}
  inline void external_transceiver_control_disable() { control_3.rmw(control_3_t::external_transceiver_control_t::disable);}
  inline void external_transceiver_control_enable() { control_3.rmw(control_3_t::external_transceiver_control_t::enable);}
  inline auto external_transceiver_control() const {  return control_3.rd<control_3_t::external_transceiver_control_t> ();}

  inline void external_transceiver_control_polarity(const control_3_t::external_transceiver_control_polarity_t::enum_t val) { control_3.rmw(val);}
  inline void external_transceiver_control_polarity_active_high() { control_3.rmw(control_3_t::external_transceiver_control_polarity_t::active_high);}
  inline void external_transceiver_control_polarity_active_low() { control_3.rmw(control_3_t::external_transceiver_control_polarity_t::active_low);}
  inline auto external_transceiver_control_polarity() const {  return control_3.rd<control_3_t::external_transceiver_control_polarity_t> ();}

  inline void smartcard_autoretry_count(const uint8_t val) { control_2.rmw((control_3_t::smartcard_autoretry_count_t::enum_t)val);}
  inline auto smartcard_autoretry_count() const {  return (uint8_t)control_1.rd<control_3_t::smartcard_autoretry_count_t> ();}

  inline void wakeup_from_stop_mode(const control_3_t::wakeup_from_stop_mode_t::enum_t val) { control_3.rmw(val);}
  inline void wakeup_from_stop_mode_address_match() { control_3.rmw(control_3_t::wakeup_from_stop_mode_t::address_match);}
  inline void wakeup_from_stop_mode_start_bit_detection() { control_3.rmw(control_3_t::wakeup_from_stop_mode_t::start_bit_detection);}
  inline void wakeup_from_stop_mode_rxne() { control_3.rmw(control_3_t::wakeup_from_stop_mode_t::rxne);}
  inline auto wakeup_from_stop_mode() const {  return control_3.rd<control_3_t::wakeup_from_stop_mode_t> ();}

  inline void wakeup_from_stop_mode_interrupt(const control_3_t::wakeup_from_stop_mode_interrupt_t::enum_t val) { control_3.rmw(val);}
  inline void wakeup_from_stop_mode_interrupt_disable() { control_3.rmw(control_3_t::wakeup_from_stop_mode_interrupt_t::disable);}
  inline void wakeup_from_stop_mode_interrupt_enable() { control_3.rmw(control_3_t::wakeup_from_stop_mode_interrupt_t::enable);}
  inline auto wakeup_from_stop_mode_interrupt() const {  return control_3.rd<control_3_t::wakeup_from_stop_mode_interrupt_t> ();}

  inline void clock_in_stop_mode(const control_3_t::clock_in_stop_mode_t::enum_t val) { control_3.rmw(val);}
  inline void clock_in_stop_mode_disable() { control_3.rmw(control_3_t::clock_in_stop_mode_t::disable);}
  inline void clock_in_stop_mode_enable() { control_3.rmw(control_3_t::clock_in_stop_mode_t::enable);}
  inline auto clock_in_stop_mode() const {  return control_3.rd<control_3_t::clock_in_stop_mode_t> ();}

  inline void tx_complete_before_guard_time_interrupt(const control_3_t::tx_complete_before_guard_time_interrupt_t::enum_t val) { control_3.rmw(val);}
  inline void tx_complete_before_guard_time_interrupt_disable() { control_3.rmw(control_3_t::tx_complete_before_guard_time_interrupt_t::disable);}
  inline void tx_complete_before_guard_time_interrupt_enable() { control_3.rmw(control_3_t::tx_complete_before_guard_time_interrupt_t::enable);}
  inline auto tx_complete_before_guard_time_interrupt() const {  return control_3.rd<control_3_t::tx_complete_before_guard_time_interrupt_t> ();}

  struct baud_rate_t : public read_write_32_t
    {
       //struct div_fraction_t  { enum enum_t { offset=0, mask=0xf} ; } ;
       //struct div_mantissa_t  { enum enum_t { offset=4, mask=0xfff} ; } ;
    };

  struct guard_time_and_prescaler_t : public read_write_32_t
    {
       struct prescaler_t  { enum enum_t { offset=0, mask=0xff} ; } ;
       struct guard_time_t { enum enum_t { offset=8, mask=0xff} ; } ;
    };

  inline void prescaler(const uint8_t val) { guard_time_and_prescaler.rmw((guard_time_and_prescaler_t::prescaler_t::enum_t)val);}
  inline auto prescaler() const {  return (uint8_t)guard_time_and_prescaler.rd<guard_time_and_prescaler_t::prescaler_t> ();}

  inline void guard_time(const uint8_t val) { guard_time_and_prescaler.rmw((guard_time_and_prescaler_t::guard_time_t::enum_t)val);}
  inline auto guard_time() const {  return (uint8_t)guard_time_and_prescaler.rd<guard_time_and_prescaler_t::guard_time_t> ();}

  struct rx_timeout_and_block_length_t : public read_write_32_t
    {
       struct rx_timeout_t  { enum enum_t { offset=0, mask=0xffffff} ; } ;
       struct block_length_t { enum enum_t { offset=24, mask=0xff} ; } ;
    };

  inline void rx_timeout(const uint16_t val) { rx_timeout_and_block_length.rmw((rx_timeout_and_block_length_t::rx_timeout_t::enum_t)val);}
  inline auto rx_timeout() const {  return (uint16_t)rx_timeout_and_block_length.rd<rx_timeout_and_block_length_t::rx_timeout_t> ();}

  inline void block_length(const uint8_t val) { rx_timeout_and_block_length.rmw((rx_timeout_and_block_length_t::block_length_t::enum_t)val);}
  inline auto block_length() const {  return (uint8_t)rx_timeout_and_block_length.rd<rx_timeout_and_block_length_t::block_length_t> ();}

  struct request_t : public read_write_32_t
    {
       struct auto_baud_rate_request_t  { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
       struct send_brake_request_t      { enum enum_t { offset=1, mask=1, disable=0, enable} ; } ;
       struct mute_mode_request_t       { enum enum_t { offset=2, mask=1, disable=0, enable} ; } ;
       struct rx_data_flush_request_t   { enum enum_t { offset=3, mask=1, disable=0, enable} ; } ;
       struct tx_data_flush_request_t   { enum enum_t { offset=4, mask=1, disable=0, enable} ; } ;
    };

  inline void auto_baud_rate_request(const request_t::auto_baud_rate_request_t::enum_t val) { request.rmw(val);}
  inline void auto_baud_rate_request_disable() { request.rmw(request_t::auto_baud_rate_request_t::disable);}
  inline void auto_baud_rate_request_enable() { request.rmw(request_t::auto_baud_rate_request_t::enable);}
  inline auto auto_baud_rate_request() const {  return request.rd<request_t::auto_baud_rate_request_t> ();}

  inline void send_brake_request(const request_t::send_brake_request_t::enum_t val) { request.rmw(val);}
  inline void send_brake_request_disable() { request.rmw(request_t::send_brake_request_t::disable);}
  inline void send_brake_request_enable() { request.rmw(request_t::send_brake_request_t::enable);}
  inline auto send_brake_request() const {  return request.rd<request_t::send_brake_request_t> ();}

  inline void mute_mode_request(const request_t::mute_mode_request_t::enum_t val) { request.rmw(val);}
  inline void mute_mode_request_disable() { request.rmw(request_t::mute_mode_request_t::disable);}
  inline void mute_mode_request_enable() { request.rmw(request_t::mute_mode_request_t::enable);}
  inline auto mute_mode_request() const {  return request.rd<request_t::mute_mode_request_t> ();}

  inline void rx_data_flush_request(const request_t::rx_data_flush_request_t::enum_t val) { request.rmw(val);}
  inline void rx_data_flush_request_disable() { request.rmw(request_t::rx_data_flush_request_t::disable);}
  inline void rx_data_flush_request_enable() { request.rmw(request_t::rx_data_flush_request_t::enable);}
  inline auto rx_data_flush_request() const {  return request.rd<request_t::rx_data_flush_request_t> ();}

  inline void tx_data_flush_request(const request_t::tx_data_flush_request_t::enum_t val) { request.rmw(val);}
  inline void tx_data_flush_request_disable() { request.rmw(request_t::tx_data_flush_request_t::disable);}
  inline void tx_data_flush_request_enable() { request.rmw(request_t::tx_data_flush_request_t::enable);}
  inline auto tx_data_flush_request() const {  return request.rd<request_t::tx_data_flush_request_t> ();}

  struct interrupt_and_status_t : public read_write_32_t
    {
     struct parity_error_flag_t                    { enum enum_t { offset=0, mask=1, reset=0, set} ; } ;
     struct framing_error_flag_t                   { enum enum_t { offset=1, mask=1, reset=0, set} ; } ;
     struct noise_detect_flag_t                    { enum enum_t { offset=2, mask=1, reset=0, set} ; } ;
     struct overrun_error_flag_t                   { enum enum_t { offset=3, mask=1, reset=0, set} ; } ;
     struct idle_line_detect_flag_t                { enum enum_t { offset=4, mask=1, reset=0, set} ; } ;
     struct rx_data_register_not_empty_flag_t      { enum enum_t { offset=5, mask=1, reset=0, set} ; } ;
     struct tx_complete_flag_t                     { enum enum_t { offset=6, mask=1, reset=0, set} ; } ;
     struct tx_data_register_empty_flag_t          { enum enum_t { offset=7, mask=1, reset=0, set} ; } ;
     struct lin_break_detection_flag_t             { enum enum_t { offset=8, mask=1, reset=0, set} ; } ;
     struct cts_toggles_flag_t                     { enum enum_t { offset=9, mask=1, reset=0, set} ; } ;
     struct cts_line_flag_t                        { enum enum_t { offset=10, mask=1, set=0, reset} ; } ;
     struct rx_timeout_flag_t                      { enum enum_t { offset=11, mask=1, reset=0, set} ; } ;
     struct end_of_block_flag_t                    { enum enum_t { offset=12, mask=1, reset=0, set} ; } ;
     struct auto_baud_rate_error_flag_t            { enum enum_t { offset=14, mask=1, reset=0, set} ; } ;
     struct auto_baud_rate_flag_t                  { enum enum_t { offset=15, mask=1, reset=0, set} ; } ;
     struct busy_flag_t                            { enum enum_t { offset=16, mask=1, reset=0, set} ; } ;
     struct character_match_flag_t                 { enum enum_t { offset=17, mask=1, reset=0, set} ; } ;
     struct send_break_flag_t                      { enum enum_t { offset=18, mask=1, reset=0, set} ; } ;
     struct rx_wakeup_from_mute_mode_flag_t        { enum enum_t { offset=19, mask=1, reset=0, set} ; } ;
     struct wakeup_from_stop_mode_flag_t           { enum enum_t { offset=20, mask=1, reset=0, set} ; } ;
     struct tx_enable_acknowledge_flag_t           { enum enum_t { offset=21, mask=1, reset=0, set} ; } ;
     struct rx_enable_acknowledge_flag_t           { enum enum_t { offset=22, mask=1, reset=0, set} ; } ;
     struct tx_complete_before_guard_time_completion_flag_t { enum enum_t { offset=25, mask=1, reset=0, set} ; } ;
    };

  inline auto parity_error_flag() const {  return interrupt_and_status.rd<interrupt_and_status_t::parity_error_flag_t> ();}
  inline auto framing_error_flag() const {  return interrupt_and_status.rd<interrupt_and_status_t::framing_error_flag_t> ();}
  inline auto noise_detect_flag() const {  return interrupt_and_status.rd<interrupt_and_status_t::noise_detect_flag_t> ();}
  inline auto overrun_error_flag() const {  return interrupt_and_status.rd<interrupt_and_status_t::overrun_error_flag_t> ();}
  inline auto idle_line_detect_flag() const {  return interrupt_and_status.rd<interrupt_and_status_t::idle_line_detect_flag_t> ();}
  inline auto rx_data_register_not_empty_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::rx_data_register_not_empty_flag_t> ();}
  inline auto tx_complete_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::tx_complete_flag_t> ();}
  inline auto tx_data_register_empty_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::tx_data_register_empty_flag_t> ();}
  inline auto lin_break_detection_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::lin_break_detection_flag_t> ();}
  inline auto cts_toggles_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::cts_toggles_flag_t> ();}
  inline auto cts_line_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::cts_line_flag_t> ();}
  inline auto rx_timeout_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::rx_timeout_flag_t> ();}
  inline auto end_of_block_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::end_of_block_flag_t> ();}
  inline auto auto_baud_rate_error_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::auto_baud_rate_error_flag_t> ();}
  inline auto auto_baud_rate_state_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::auto_baud_rate_flag_t> ();}
  inline auto busy_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::busy_flag_t> ();}
  inline auto character_match_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::character_match_flag_t> ();}
  inline auto send_break_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::send_break_flag_t> ();}
  inline auto rx_wakeup_from_mute_mode_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::rx_wakeup_from_mute_mode_flag_t> ();}
  inline auto wakeup_from_stop_mode_state_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::wakeup_from_stop_mode_flag_t> ();}
  inline auto tx_enable_acknowledge_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::tx_enable_acknowledge_flag_t> ();}
  inline auto rx_enable_acknowledge_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::rx_enable_acknowledge_flag_t> ();}
  inline auto tx_complete_before_guard_time_completion_flag() const { return interrupt_and_status.rd<interrupt_and_status_t::tx_complete_before_guard_time_completion_flag_t> ();}

  struct interrupt_flag_clear_t : public read_write_32_t
    {
         struct parity_error_clear_t                             { enum enum_t { offset=0, mask=1, no_effect=0, perform} ; } ;
         struct framing_error_clear_t                            { enum enum_t { offset=1, mask=1, no_effect=0, perform} ; } ;
         struct noise_detect_clear_t                             { enum enum_t { offset=2, mask=1, no_effect=0, perform} ; } ;
         struct overrun_error_clear_t                            { enum enum_t { offset=3, mask=1, no_effect=0, perform} ; } ;
         struct idle_line_detect_clear_t                         { enum enum_t { offset=4, mask=1, no_effect=0, perform} ; } ;

         struct transmission_complete_clear_t                    { enum enum_t { offset=6, mask=1, no_effect=0, perform} ; } ;
         struct transmit_completed_before_guard_time_clear_t     { enum enum_t { offset=7, mask=1, no_effect=0, perform} ; } ;
         struct lin_break_detection_clear_t                      { enum enum_t { offset=8, mask=1, no_effect=0, perform} ; } ;
         struct cts_clear_t                                      { enum enum_t { offset=9, mask=1, no_effect=0, perform} ; } ;

         struct rx_timeout_clear_t                               { enum enum_t { offset=11, mask=1, no_effect=0, perform} ; } ;
         struct end_of_block_clear_t                             { enum enum_t { offset=12, mask=1, no_effect=0, perform} ; } ;

         struct character_match_clear_t                          { enum enum_t { offset=17, mask=1, no_effect=0, perform} ; } ;

         struct wakeup_from_stop_mode_state_clear_t              { enum enum_t { offset=20, mask=1, no_effect=0, perform} ; } ;
    };

  inline void parity_error_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::parity_error_clear_t::perform);}
  inline void framing_error_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::framing_error_clear_t::perform);}
  inline void noise_detect_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::noise_detect_clear_t::perform);}
  inline void overrun_error_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::overrun_error_clear_t::perform);}
  inline void idle_line_detect_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::idle_line_detect_clear_t::perform);}
  inline void transmission_complete_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::transmission_complete_clear_t::perform);}
  inline void transmit_completed_before_guard_time_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::transmit_completed_before_guard_time_clear_t::perform);}
  inline void lin_break_detection_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::lin_break_detection_clear_t::perform);}
  inline void cts_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::cts_clear_t::perform);}
  inline void rx_timeout_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::rx_timeout_clear_t::perform);}
  inline void end_of_block_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::end_of_block_clear_t::perform);}
  inline void character_match_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::character_match_clear_t::perform);}
  inline void wakeup_from_stop_mode_state_clear() { interrupt_flag_clear.rmw(interrupt_flag_clear_t::wakeup_from_stop_mode_state_clear_t::perform);}

  control_1_t control_1 ; //CR1;    /*!< USART Control register 1,                 Address offset: 0x00 */
  control_2_t control_2 ; //CR2;    /*!< USART Control register 2,                 Address offset: 0x04 */
  control_3_t control_3 ; //CR3;    /*!< USART Control register 3,                 Address offset: 0x08 */
  baud_rate_t baud_rate ; //BRR;    /*!< USART Baud rate register,                 Address offset: 0x0C */
  guard_time_and_prescaler_t guard_time_and_prescaler ; // GTPR;   /*!< USART Guard time and prescaler register,  Address offset: 0x10 */
  rx_timeout_and_block_length_t rx_timeout_and_block_length; //RTOR;   /*!< USART Receiver Time Out register,         Address offset: 0x14 */
  request_t      request; //RQR;    /*!< USART Request register,                   Address offset: 0x18 */
  interrupt_and_status_t interrupt_and_status; //ISR;    /*!< USART Interrupt and status register,      Address offset: 0x1C */
  interrupt_flag_clear_t interrupt_flag_clear; //ICR;    /*!< USART Interrupt flag Clear register,      Address offset: 0x20 */
  volatile uint32_t rx_data ; //RDR;    /*!< USART Receive Data register,              Address offset: 0x24 */
  volatile uint32_t tx_data ; //TDR;    /*!< USART Transmit Data register,             Address offset: 0x28 */


  inline void clock_enable()
     {
        switch((uint32_t)this)
          {
             case usart1_addr : rcc.usart1_enable(); break ;
             default: { std::__throw_invalid_argument("invalid UART object") ; }
          }
     }

  inline void clock_disable()
     {
        switch((uint32_t)this)
          {
             case usart1_addr : rcc.usart1_disable(); break ;
             default: { std::__throw_invalid_argument("invalid UART object") ; }
          }
     }

  inline void reset()
     {
        switch((uint32_t)this)
          {
             case usart1_addr : rcc.usart1_reset(); break ;
             default: { std::__throw_invalid_argument("invalid UART object") ; }
          }
     }

    //inline void baud(uint32_t val) { baud_rate.write( ( 2 * rcc.apb1_clock_freq() + val ) / (2 * val) ); }
    //inline uint32_t baud() { return rcc.apb1_clock_freq() / baud_rate.read(); }

    inline void wait_not_busy() const { while ( busy_flag() == interrupt_and_status_t::busy_flag_t::set ) {} }
    inline void wait_send_ready() const {  while ( tx_data_register_empty_flag() == interrupt_and_status_t::tx_data_register_empty_flag_t::reset ) {} }
    inline void wait_recv_ready() const {  while ( rx_data_register_not_empty_flag() == interrupt_and_status_t::rx_data_register_not_empty_flag_t::reset ) {}}
    inline uint32_t recv_blocking() const { wait_recv_ready(); return rx_data ; }
    inline void     recv_blocking( uint8_t* buf , size_t len ) { while ( len-- ) *buf++ = recv_blocking() ; }
    void            send_blocking(const uint16_t val) { wait_send_ready(); tx_data = val ; }
    inline void     send_blocking( const uint8_t* buf , size_t len ) { while ( len-- ) send_blocking(*buf++) ;  }

} ;

struct uart5_t : public uart_t
  {
    inline void clock_enable() {  rcc.uart5_enable() ; }
    inline void clock_disable(){  rcc.uart5_disable(); }
    inline void clock_reset()  {  rcc.uart5_reset() ; }

  };

static uart5_t& uart5 = *((uart5_t*) uart5_addr);



} // stm32f7

using namespace stm32f7 ;

#endif /* __UART++_H__ */
