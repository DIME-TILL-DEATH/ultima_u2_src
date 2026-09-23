/*
 * uart++.h
 *
 *  Created on: 21 авг. 2017 г.
 *      Author: klen
 */

#ifndef __UART++_H__
#define __UART++_H__


#include "types++.h"
#include "rcc++.h"

namespace stm32f4
{
  struct uart_t
  {
    struct status_t : public read_write_32_t
      {
       struct parity_error_t                    { enum enum_t { offset=0, mask=1, reset=0, set} ; } ;
       struct framing_error_t                   { enum enum_t { offset=1, mask=1, reset=0, set} ; } ;
       struct noise_detect_t                    { enum enum_t { offset=2, mask=1, reset=0, set} ; } ;
       struct overrun_error_t                   { enum enum_t { offset=3, mask=1, reset=0, set} ; } ;
       struct idle_line_detect_t                { enum enum_t { offset=4, mask=1, reset=0, set} ; } ;
       struct receive_data_register_not_empty_t { enum enum_t { offset=5, mask=1, reset=0, set} ; } ;
       struct transmission_complete_t           { enum enum_t { offset=6, mask=1, reset=0, set} ; } ;
       struct transmit_data_register_empty_t    { enum enum_t { offset=7, mask=1, reset=0, set} ; } ;
       struct lin_break_detection_t             { enum enum_t { offset=8, mask=1, reset=0, set} ; } ;
       struct cts_toggles_t                     { enum enum_t { offset=9, mask=1, reset=0, set} ; } ;
      };

    inline auto parity_error() const {  return status.rd<status_t::parity_error_t> ();}
    inline auto framing_error() const {  return status.rd<status_t::framing_error_t> ();}
    inline auto noise_detect() const {  return status.rd<status_t::noise_detect_t> ();}
    inline auto overrun_error() const {  return status.rd<status_t::overrun_error_t> ();}
    inline auto idle_line_detect() const {  return status.rd<status_t::idle_line_detect_t> ();}

    inline void receive_data_register_not_empty_clear() { status.rmw(status_t::receive_data_register_not_empty_t::reset);}
    inline auto receive_data_register_not_empty() const { return status.rd<status_t::receive_data_register_not_empty_t> ();}

    inline void transmission_complete_clear() { status.rmw(status_t::transmission_complete_t::reset);}
    inline auto transmission_complete() const { return status.rd<status_t::transmission_complete_t> ();}

    inline auto transmit_data_register_empty() const { return status.rd<status_t::transmit_data_register_empty_t> ();}

    inline void lin_break_detection_clear() { status.rmw(status_t::lin_break_detection_t::reset);}
    inline auto lin_break_detection() const { return status.rd<status_t::lin_break_detection_t> ();}

    inline void cts_toggles_clear() { status.rmw(status_t::cts_toggles_t::reset);}
    inline auto cts_toggles() const { return status.rd<status_t::cts_toggles_t> ();}

    struct baud_rate_t : public read_write_32_t
      {
         struct div_fraction_t  { enum enum_t { offset=0, mask=0xf} ; } ;
         struct div_mantissa_t  { enum enum_t { offset=4, mask=0xfff} ; } ;
      };

    inline void div_fraction(const uint8_t val) { baud_rate.rmw( (baud_rate_t::div_fraction_t::enum_t)val );}
    inline auto div_fraction() const {  return (uint8_t)baud_rate.rd<baud_rate_t::div_fraction_t> ();}

    inline void div_mantissa(const uint16_t val) { baud_rate.rmw( (baud_rate_t::div_mantissa_t::enum_t)val );}
    inline auto div_mantissa() const {  return (uint8_t)baud_rate.rd<baud_rate_t::div_mantissa_t> ();}

    struct control_1_t : public read_write_32_t
      {
         struct send_brake_t              { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
         struct receiver_wakeup_t         { enum enum_t { offset=1, mask=1, active=0, mute} ; } ;
         struct receiver_t                { enum enum_t { offset=2, mask=1, disable=0, enable} ; } ;
         struct transmitter_t             { enum enum_t { offset=3, mask=1, disable=0, enable} ; } ;
         struct idle_interupt_t           { enum enum_t { offset=4, mask=1, disable=0, enable} ; } ;
         struct rx_not_empty_interupt_t   { enum enum_t { offset=5, mask=1, disable=0, enable} ; } ;
         struct tx_complete_interrupt_t   { enum enum_t { offset=6, mask=1, disable=0, enable} ; } ;
         struct tx_empty_interrupt_t      { enum enum_t { offset=7, mask=1, disable=0, enable} ; } ;
         struct parity_error_interrupt_t  { enum enum_t { offset=8, mask=1, disable=0, enable} ; } ;
         struct parity_selection_t        { enum enum_t { offset=9, mask=1, even=0, odd} ; } ;
         struct parity_control_t          { enum enum_t { offset=10,mask=1, disable=0, enable} ; } ;
         struct wakeup_method_t           { enum enum_t { offset=11,mask=1, idle_line=0, address_mark } ; } ;
         struct word_length_t             { enum enum_t { offset=12,mask=1, bits8=0, bits9} ; } ;
         struct usart_t                   { enum enum_t { offset=13,mask=1, disable=0, enable} ; } ;
         struct oversampling_mode_t       { enum enum_t { offset=15,mask=1, x8=0, x16} ; } ;
      };

    inline void send_brake(const control_1_t::send_brake_t::enum_t val) { control_1.rmw(val);}
    inline void send_brake_disable() { control_1.rmw(control_1_t::send_brake_t::disable);}
    inline void send_brake_enable() { control_1.rmw(control_1_t::send_brake_t::enable);}
    inline auto send_brake() const {  return control_1.rd<control_1_t::send_brake_t> ();}

    inline void receiver_wakeup(const control_1_t::receiver_wakeup_t::enum_t val) { control_1.rmw(val);}
    inline void receiver_wakeup_active() { control_1.rmw(control_1_t::receiver_wakeup_t::active);}
    inline void receiver_wakeup_mute() { control_1.rmw(control_1_t::receiver_wakeup_t::mute);}
    inline auto receiver_wakeup() const {  return control_1.rd<control_1_t::receiver_wakeup_t> ();}

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

    inline void word_length(const control_1_t::word_length_t::enum_t val) { control_1.rmw(val);}
    inline void word_length_bits8() { control_1.rmw(control_1_t::word_length_t::bits8);}
    inline void word_length_bits9() { control_1.rmw(control_1_t::word_length_t::bits9);}
    inline auto word_length() const {  return control_1.rd<control_1_t::word_length_t> ();}

    inline void usart(const control_1_t::usart_t::enum_t val) { control_1.rmw(val);}
    inline void usart_disable() { control_1.rmw(control_1_t::usart_t::disable);}
    inline void usart_enable() { control_1.rmw(control_1_t::usart_t::enable);}
    inline auto usart() const {  return control_1.rd<control_1_t::usart_t> ();}

    inline void oversampling_mode(const control_1_t::oversampling_mode_t::enum_t val) { control_1.rmw(val);}
    inline void oversampling_mode_x8() { control_1.rmw(control_1_t::oversampling_mode_t::x8);}
    inline void oversampling_mode_x16() { control_1.rmw(control_1_t::oversampling_mode_t::x16);}
    inline auto oversampling_mode() const {  return control_1.rd<control_1_t::oversampling_mode_t> ();}

    struct control_2_t : public read_write_32_t
      {
         struct address_of_node_t              { enum enum_t { offset=0, mask=0b1111} ; } ;
         struct lin_break_detection_length_t   { enum enum_t { offset=5, mask=1, bits10=0, bits11 } ; } ;
         struct lin_break_detection_inerrup_t  { enum enum_t { offset=6, mask=1, disable=0, enable } ; } ;
         struct stop_bits_t                    { enum enum_t { offset=12,mask=1, stop_bit_1=0 , stop_bit_0_5, stop_bit_2, stop_bit_1_5 } ; } ;
         struct lin_mode_t                     { enum enum_t { offset=14,mask=1, disable=0, enable } ; } ;
      };

    inline void address_of_node (const uint8_t val) { control_2.rmw((control_2_t::address_of_node_t::enum_t)val); }
    inline uint8_t address_of_node () const { return (uint8_t) control_2.rd<control_2_t::address_of_node_t>();}

    inline void lin_break_detection_length(const control_2_t::lin_break_detection_length_t::enum_t val) { control_2.rmw(val);}
    inline void lin_break_detection_length_bits10() { control_2.rmw(control_2_t::lin_break_detection_length_t::bits10);}
    inline void lin_break_detection_length_bits11() { control_2.rmw(control_2_t::lin_break_detection_length_t::bits11);}
    inline auto lin_break_detection_length() const {  return control_2.rd<control_2_t::lin_break_detection_length_t> ();}

    inline void lin_break_detection_inerrup(const control_2_t::lin_break_detection_inerrup_t::enum_t val) { control_2.rmw(val);}
    inline void lin_break_detection_inerrup_disable() { control_2.rmw(control_2_t::lin_break_detection_inerrup_t::disable);}
    inline void lin_break_detection_inerrup_enable() { control_2.rmw(control_2_t::lin_break_detection_inerrup_t::enable);}
    inline auto lin_break_detection_inerrup() const {  return control_2.rd<control_2_t::lin_break_detection_inerrup_t> ();}

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

    struct control_3_t : public read_write_32_t
      {
         struct error_interrupt_t { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
         struct irda_mode_t       { enum enum_t { offset=1, mask=1, disable=0, enable} ; } ;
         struct irda_low_power_t  { enum enum_t { offset=2, mask=1, disable=0, enable} ; } ;
         struct half_duplex_t     { enum enum_t { offset=3, mask=1, disable=0, enable} ; } ;
         struct rx_dma_t          { enum enum_t { offset=6, mask=1, disable=0, enable} ; } ;
         struct tx_dma_t          { enum enum_t { offset=7, mask=1, disable=0, enable} ; } ;
         struct one_sample_bit_method_t { enum enum_t { offset=11, mask=1, disable=0, enable} ; } ;
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

    inline void rx_dma(const control_3_t::rx_dma_t::enum_t val) { control_3.rmw(val);}
    inline void rx_dma_disable() { control_3.rmw(control_3_t::rx_dma_t::disable);}
    inline void rx_dma_enable() { control_3.rmw(control_3_t::rx_dma_t::enable);}
    inline auto rx_dma() const {  return control_3.rd<control_3_t::rx_dma_t> ();}

    inline void tx_dma(const control_3_t::tx_dma_t::enum_t val) { control_3.rmw(val);}
    inline void tx_dma_disable() { control_3.rmw(control_3_t::tx_dma_t::disable);}
    inline void tx_dma_enable() { control_3.rmw(control_3_t::tx_dma_t::enable);}
    inline auto tx_dma() const {  return control_3.rd<control_3_t::tx_dma_t> ();}

    inline void one_sample_bit_method(const control_3_t::one_sample_bit_method_t::enum_t val) { control_3.rmw(val);}
    inline void one_sample_bit_method_disable() { control_3.rmw(control_3_t::one_sample_bit_method_t::disable);}
    inline void one_sample_bit_method_enable() { control_3.rmw(control_3_t::one_sample_bit_method_t::enable);}
    inline auto one_sample_bit_method() const {  return control_3.rd<control_3_t::one_sample_bit_method_t> ();}

    status_t status ; //  SR;         /*!< USART Status register,                   Address offset: 0x00 */
    volatile uint32_t data ;  // DR;         /*!< USART Data register,                     Address offset: 0x04 */
    baud_rate_t baud_rate ; // BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
    control_1_t control_1 ; // CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
    control_2_t control_2 ; // CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
    control_3_t control_3 ; // CR3;        /*!< USART Control register 3,                Address offset: 0x14 */

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case uart4_addr : rcc.uart4_enable(); break ;
               case uart5_addr : rcc.uart5_enable(); break ;
               default: { std::__throw_invalid_argument("invalid UART object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case uart4_addr : rcc.uart4_disable(); break ;
               case uart5_addr : rcc.uart5_disable(); break ;
               default: { std::__throw_invalid_argument("invalid UART object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case uart4_addr : rcc.uart4_reset(); break ;
               case uart5_addr : rcc.uart5_reset(); break ;
               default: { std::__throw_invalid_argument("invalid UART object") ; }
            }
       }

    inline void baud(uint32_t val) { baud_rate.write( ( 2 * rcc.apb1_clock_freq() + val ) / (2 * val) ); }
    inline uint32_t baud() { return rcc.apb1_clock_freq() / baud_rate.read(); }

    inline void wait_send_ready() {  while (transmit_data_register_empty()==status_t::transmit_data_register_empty_t::reset) {}}
    inline void wait_recv_ready() {  while (receive_data_register_not_empty()==status_t::receive_data_register_not_empty_t::reset) {}}
    inline uint32_t recv_blocking() { wait_recv_ready(); return data ; }
    inline void     recv_blocking( uint8_t* buf , size_t len ) { while ( len-- ) *buf++ = recv_blocking() ; }
    void            send_blocking(uint16_t val) { wait_send_ready(); data = val ; }
    inline void     send_blocking( uint8_t* buf , size_t len ) { while ( len-- ) send_blocking(*buf++) ;  }




  } ;


struct uart4_t : public uart_t
    {
      inline void clock_enable() {  rcc.uart4_enable() ; }
      inline void clock_disable(){  rcc.uart4_disable(); }
      inline void clock_reset()  {  rcc.uart4_reset() ; }
    };

struct uart5_t : public uart_t
    {
      inline void clock_enable() {  rcc.uart5_enable() ; }
      inline void clock_disable(){  rcc.uart5_disable(); }
      inline void clock_reset()  {  rcc.uart5_reset() ; }
    };

static uart4_t& uart4 = *((uart4_t*) uart4_addr);
static uart5_t& uart5 = *((uart5_t*) uart5_addr);

}

using namespace stm32f4 ;

#endif /* __UART++_H__ */
