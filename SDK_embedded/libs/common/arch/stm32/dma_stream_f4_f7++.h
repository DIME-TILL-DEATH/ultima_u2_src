/*
 * dma++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __DMA_STREAM_F4_F7++_H__
#define __DMA_STREAM_F4_F7++_H__


#include "types++.h"

namespace stm32
{

struct dma_stream_t
{
  struct configuration_t : public read_write_32_t
  {
    struct state_t                             { enum enum_t { offset=0,  mask=1, disable=0 ,  enable } ; } ;
    struct ready_t                             { enum enum_t { offset=0,  mask=1, ready=0 ,  not_ready} ; } ;
    struct direct_mode_error_interrupt_state_t { enum enum_t { offset=1,  mask=1,    disable=0 , enable};} ;
    struct transfer_error_interrupt_state_t    { enum enum_t { offset=2,  mask=1,    disable=0 , enable};} ;
    struct half_transfer_interrupt_state_t     { enum enum_t { offset=3,  mask=1,    disable=0 , enable};} ;
    struct transfer_complete_interrupt_state_t { enum enum_t { offset=4,  mask=1,    disable=0 , enable};} ;
    struct flow_controller_t                   { enum enum_t { offset=5,  mask=1,    dma=0 ,  peripheral};} ;
    struct direction_t                         { enum enum_t { offset=6,  mask=0b11, peripheral_to_memory = 0 , memory_to_peripheral, memory_to_memory};};
    struct circular_mode_t                     { enum enum_t { offset=8,  mask=1,    disable=0, enable};};
    struct peripheral_increment_mode_t         { enum enum_t { offset=9,  mask=1,    disable=0 , enable};};
    struct memory_increment_mode_t             { enum enum_t { offset=10, mask=1,    disable=0 , enable};};
    struct peripheral_data_size_t              { enum enum_t { offset=11, mask=0b11, byte=0, half_word, word};} ;
    struct memory_data_size_t                  { enum enum_t { offset=13, mask=0b11, byte=0, half_word, word};} ;
    struct peripheral_increment_offset_size_t  { enum enum_t { offset=15, mask=1,    psize=0 , alignment};};
    struct priority_level_t                    { enum enum_t { offset=16, mask=0b11, low=0 , medium, high, very_high};};
    struct double_buffer_mode_t                { enum enum_t { offset=18, mask=1,    disable=0 , enable};};
    struct current_target_t                    { enum enum_t { offset=19, mask=1,    m0ar=0, m1ar};};
    struct peripheral_burst_transfer_t         { enum enum_t { offset=21, mask=0b11, single=0, incr4, incr8, incr16};};
    struct memory_burst_transfer_t             { enum enum_t { offset=23, mask=0b11, single=0, incr4, incr8, incr16};};
    struct channel_t                           { enum enum_t { offset=25, mask=0b1111, channel0=0, channel1, channel2, channel3, channel4, channel5, channel6, channel7, channel8,
                                                                                       channel9, channel10, channel11, channel12, channel13, channel14, channel15, };};
  } ;


  inline  void state( const configuration_t::state_t::enum_t val){  configuration.rmw(val) ;}
  inline  void enable() {  configuration.rmw( configuration_t::state_t::enable) ;}
  inline  void disable() {  configuration.rmw( configuration_t::state_t::disable) ;}
  inline  auto state() const {  return configuration.rd<configuration_t::ready_t> ();}
  inline  void wait_ready() const {  while (state() == configuration_t::ready_t::not_ready) { NRO } ;}

  inline  void direct_mode_error_interrupt( const configuration_t::direct_mode_error_interrupt_state_t::enum_t val){  configuration.rmw( val) ;}
  inline  void direct_mode_error_interrupt_enable(){  configuration.rmw(configuration_t::direct_mode_error_interrupt_state_t::enable ) ;}
  inline  void direct_mode_error_interrupt_disable(){  configuration.rmw(configuration_t::direct_mode_error_interrupt_state_t::disable ) ;}
  inline  auto direct_mode_error_interrupt() const {  return configuration.rd<configuration_t::direct_mode_error_interrupt_state_t> ();}

  inline  void transfer_error_interrupt( const configuration_t::transfer_error_interrupt_state_t::enum_t val){  configuration.rmw (val) ;}
  inline  void transfer_error_interrupt_enable(){  configuration.rmw(configuration_t::transfer_error_interrupt_state_t::enable ) ;}
  inline  void transfer_error_interrupt_disable(){  configuration.rmw(configuration_t::transfer_error_interrupt_state_t::disable ) ;}
  inline  auto transfer_error_interrupt() const {  return configuration.rd<configuration_t::transfer_error_interrupt_state_t> ();}

  inline  void half_transfer_interrupt( const configuration_t::half_transfer_interrupt_state_t::enum_t val){  configuration.rmw(val) ;}
  inline  void half_transfer_interrupt_enable(){  configuration.rmw(configuration_t::half_transfer_interrupt_state_t::enable ) ;}
  inline  void half_transfer_interrupt_disable(){  configuration.rmw(configuration_t::half_transfer_interrupt_state_t::disable ) ;}
  inline  auto half_transfer_interrupt() const {  return configuration.rd<configuration_t::half_transfer_interrupt_state_t> ();}

  inline  void transfer_complete_interrupt( const configuration_t::transfer_complete_interrupt_state_t::enum_t val){  configuration.rmw (val) ;}
  inline  void transfer_complete_interrupt_enable(){  configuration.rmw(configuration_t::transfer_complete_interrupt_state_t::enable ) ;}
  inline  void transfer_complete_interrupt_disable(){  configuration.rmw(configuration_t::transfer_complete_interrupt_state_t::disable ) ;}
  inline  auto transfer_complete_interrupt() const {  return configuration.rd<configuration_t::transfer_complete_interrupt_state_t> ();}


  inline void flow_controller( const configuration_t::flow_controller_t::enum_t val){  configuration.rmw(val) ;}
  inline void flow_controller_dma(){  configuration.rmw(configuration_t::flow_controller_t::dma ) ;}
  inline void flow_controller_peripheral(){  configuration.rmw(configuration_t::flow_controller_t::peripheral ) ;}
  inline auto flow_controller() const {  return configuration.rd<configuration_t::flow_controller_t> ();}

  inline  void direction( const configuration_t::direction_t::enum_t val) { configuration.rmw(val) ; }
  inline  void direction_peripheral_to_memory(){  configuration.rmw( configuration_t::direction_t::peripheral_to_memory) ;}
  inline  void direction_memory_to_peripheral(){  configuration.rmw( configuration_t::direction_t::memory_to_peripheral) ;}
  inline  void direction_memory_to_memory()    {  configuration.rmw( configuration_t::direction_t::memory_to_memory) ;}
  inline  auto direction() const {  return configuration.rd<configuration_t::direction_t> ();}

  inline void circular_mode( const configuration_t::circular_mode_t::enum_t val){ configuration.rmw( val) ;}
  inline void circular_mode_enable(){  configuration.rmw(configuration_t::circular_mode_t::enable) ;}
  inline void circular_mode_disable(){ configuration.rmw(configuration_t::circular_mode_t::disable) ;}
  inline auto circular_mode() const {  return configuration.rd<configuration_t::circular_mode_t> ();}

  inline void peripheral_increment_mode( const configuration_t::peripheral_increment_mode_t::enum_t val){  configuration.rmw (val) ;}
  inline void peripheral_increment_mode_enable(){  configuration.rmw (configuration_t::peripheral_increment_mode_t::enable) ;}
  inline void peripheral_increment_mode_disable(){  configuration.rmw (configuration_t::peripheral_increment_mode_t::disable) ;}
  inline auto peripheral_increment_mode() const {  return configuration.rd<configuration_t::peripheral_increment_mode_t> (); }

  inline void memory_increment_mode( const configuration_t::memory_increment_mode_t::enum_t val){  configuration.rmw(val) ;}
  inline void memory_increment_mode_enable(){  configuration.rmw(configuration_t::memory_increment_mode_t::enable) ;}
  inline void memory_increment_mode_disable(){  configuration.rmw(configuration_t::memory_increment_mode_t::disable) ;}
  inline auto memory_increment_mode() const {  return configuration.rd<configuration_t::memory_increment_mode_t> (); }


  inline void peripheral_data_size( const configuration_t::peripheral_data_size_t::enum_t val){  configuration.rmw(val) ;}
  inline void peripheral_data_size_byte(){  configuration.rmw(configuration_t::peripheral_data_size_t::byte) ;}
  inline void peripheral_data_size_half_word(){  configuration.rmw(configuration_t::peripheral_data_size_t::half_word) ;}
  inline void peripheral_data_size_word(){ configuration.rmw(configuration_t::peripheral_data_size_t::word) ;}
  inline auto peripheral_data_size() const {  return configuration.rd<configuration_t::peripheral_data_size_t> (); }

  inline void memory_data_size( const configuration_t::memory_data_size_t::enum_t val){  configuration.rmw(val) ;}
  inline void memory_data_size_byte(){  configuration.rmw(configuration_t::memory_data_size_t::byte) ;}
  inline void memory_data_size_half_word(){  configuration.rmw(configuration_t::memory_data_size_t::half_word) ;}
  inline void memory_data_size_word(){ configuration.rmw(configuration_t::memory_data_size_t::word) ;}
  inline auto memory_data_size() const {  return configuration.rd<configuration_t::memory_data_size_t> (); }

  inline void peripheral_increment_offset_size( const configuration_t::peripheral_increment_offset_size_t::enum_t val){  configuration.rmw(val) ;}
  inline void peripheral_increment_offset_size_psize(){  configuration.rmw(configuration_t::peripheral_increment_offset_size_t::psize) ;}
  inline void peripheral_increment_offset_size_alignment(){  configuration.rmw(configuration_t::peripheral_increment_offset_size_t::alignment) ;}
  inline auto peripheral_increment_offset_size() const {  return configuration.rd<configuration_t::peripheral_increment_offset_size_t> (); }

  inline void priority_level( const configuration_t::priority_level_t::enum_t val){  configuration.rmw(val) ;}
  inline void priority_level_low(){  configuration.rmw(configuration_t::priority_level_t::low);}
  inline void priority_level_medium(){   configuration.rmw(configuration_t::priority_level_t::medium);}
  inline void priority_level_high(){  configuration.rmw(configuration_t::priority_level_t::high);}
  inline void priority_level_very_high(){   configuration.rmw(configuration_t::priority_level_t::very_high);}
  inline auto priority_level() const {   return configuration.rd<configuration_t::priority_level_t> (); }

  inline void double_buffer_mode( const configuration_t::double_buffer_mode_t::enum_t val) {  configuration.rmw(val) ; }
  inline void double_buffer_mode_enable() {  configuration.rmw(configuration_t::double_buffer_mode_t::enable) ;}
  inline void double_buffer_mode_disable(){  configuration.rmw(configuration_t::double_buffer_mode_t::disable) ;}
  inline auto double_buffer_mode() const {  return configuration.rd<configuration_t::double_buffer_mode_t> (); }

  inline void current_target( const configuration_t::current_target_t::enum_t val) {  configuration.rmw(val) ; }
  inline void current_target_m0ar() {  configuration.rmw(configuration_t::current_target_t::m0ar) ;}
  inline void current_target_m1ar() {  configuration.rmw(configuration_t::current_target_t::m1ar) ;}
  inline auto current_target() const {  return configuration.rd<configuration_t::current_target_t> (); }


  inline void peripheral_burst_transfer( const configuration_t::peripheral_burst_transfer_t::enum_t val){  configuration.rmw(val) ; }
  inline void peripheral_burst_transfer_single(){  configuration.rmw(configuration_t::peripheral_burst_transfer_t::single) ; }
  inline void peripheral_burst_transfer_incr4() {  configuration.rmw(configuration_t::peripheral_burst_transfer_t::incr4 ) ; }
  inline void peripheral_burst_transfer_incr8() {  configuration.rmw(configuration_t::peripheral_burst_transfer_t::incr8 ) ; }
  inline void peripheral_burst_transfer_incr16(){  configuration.rmw(configuration_t::peripheral_burst_transfer_t::incr16) ; }
  inline auto peripheral_burst_transfer() const {  return configuration.rd<configuration_t::peripheral_burst_transfer_t> ();  }

  inline void memory_burst_transfer( const configuration_t::memory_burst_transfer_t::enum_t val){  configuration.rmw(val) ; }
  inline void memory_burst_transfer_single(){  configuration.rmw(configuration_t::memory_burst_transfer_t::single) ; }
  inline void memory_burst_transfer_incr4() {  configuration.rmw(configuration_t::memory_burst_transfer_t::incr4 ) ; }
  inline void memory_burst_transfer_incr8() {  configuration.rmw(configuration_t::memory_burst_transfer_t::incr8 ) ; }
  inline void memory_burst_transfer_incr16(){  configuration.rmw(configuration_t::memory_burst_transfer_t::incr16) ; }
  inline auto memory_burst_transfer() const {  return configuration.rd<configuration_t::memory_burst_transfer_t> ();  }

  inline void channel( const configuration_t::channel_t::enum_t val){  configuration.rmw(val) ; }
  inline void channel0(){  configuration.rmw(configuration_t::channel_t::channel0) ; }
  inline void channel1(){  configuration.rmw(configuration_t::channel_t::channel1) ; }
  inline void channel2(){  configuration.rmw(configuration_t::channel_t::channel2) ; }
  inline void channel3(){  configuration.rmw(configuration_t::channel_t::channel3) ; }
  inline void channel4(){  configuration.rmw(configuration_t::channel_t::channel4) ; }
  inline void channel5(){  configuration.rmw(configuration_t::channel_t::channel5) ; }
  inline void channel6(){  configuration.rmw(configuration_t::channel_t::channel6) ; }
  inline void channel7(){  configuration.rmw(configuration_t::channel_t::channel7) ; }
  inline void channel8(){  configuration.rmw(configuration_t::channel_t::channel8) ; }
  inline void channel9(){  configuration.rmw(configuration_t::channel_t::channel9) ; }
  inline void channel10(){  configuration.rmw(configuration_t::channel_t::channel10) ; }
  inline void channel11(){  configuration.rmw(configuration_t::channel_t::channel11) ; }
  inline void channel12(){  configuration.rmw(configuration_t::channel_t::channel12) ; }
  inline void channel13(){  configuration.rmw(configuration_t::channel_t::channel13) ; }
  inline void channel14(){  configuration.rmw(configuration_t::channel_t::channel14) ; }
  inline void channel15(){  configuration.rmw(configuration_t::channel_t::channel15) ; }
  inline auto channel() const {  return configuration.rd<configuration_t::channel_t> ();  }






  struct fifo_control_t : public read_write_32_t
    {
      struct threshold_selection_t   { enum enum_t { offset=0, mask =0b11, threshold_selection_1div4=0, threshold_selection_2div4, threshold_selection_3div4, threshold_selection_full };};
      struct direct_mode_t           { enum enum_t { offset=2, mask =1 ,   enable=0, disable };};
      struct status_t                { enum enum_t { offset=3, mask=0b11,  less_1div4=0, from_1div4_to_2div4, from_2div4_to_3div4, from_3div4_to_full, empty, full };};
      struct error_interrupt_t       { enum enum_t { offset=7, mask=1,     disable=0,  enable };};
    } ;


  inline void fifo_threshold_selection(  const fifo_control_t::threshold_selection_t::enum_t val ) {  fifo_control.rmw(val) ; }
  inline void fifo_threshold_selection_1div4(){  fifo_control.rmw( fifo_control_t::threshold_selection_t::threshold_selection_1div4) ; }
  inline void fifo_threshold_selection_2div4(){  fifo_control.rmw( fifo_control_t::threshold_selection_t::threshold_selection_2div4) ; }
  inline void fifo_threshold_selection_3div4(){  fifo_control.rmw( fifo_control_t::threshold_selection_t::threshold_selection_3div4) ; }
  inline void fifo_threshold_selection_full() {  fifo_control.rmw( fifo_control_t::threshold_selection_t::threshold_selection_full) ; }
  inline auto fifo_threshold_selection() const {  return fifo_control.rd<fifo_control_t::threshold_selection_t> ();  }

  inline void direct_mode( const fifo_control_t::direct_mode_t::enum_t val ) {  fifo_control.rmw(val) ; }
  inline void direct_mode_enable(){  fifo_control.rmw(fifo_control_t::direct_mode_t::enable) ; }
  inline void direct_mode_disable(){  fifo_control.rmw(fifo_control_t::direct_mode_t::disable) ; }
  inline auto direct_mode() const {  return fifo_control.rd<fifo_control_t::direct_mode_t> ();  }

  inline auto fifo_status() {  return fifo_control.rd<fifo_control_t::status_t> (); }

  inline void fifo_error_interrupt ( const fifo_control_t::error_interrupt_t::enum_t val) {  fifo_control.rmw(val) ; }
  inline void fifo_error_interrupt_enable(){  fifo_control.rmw(fifo_control_t::error_interrupt_t::enable) ; }
  inline void fifo_error_interrupt_disable(){  fifo_control.rmw(fifo_control_t::error_interrupt_t::disable) ; }
  inline auto fifo_error_interrupt () const {  return fifo_control.rd<fifo_control_t::error_interrupt_t> ();  }

  configuration_t    configuration ;       // CR;     /*!< DMA stream x configuration register      */
  volatile uint32_t  number_of_data ;      // NDTR;   /*!< DMA stream x number of data register     */
  volatile uint32_t  peripheral_address ;  // PAR;    /*!< DMA stream x peripheral address register */
  volatile uint32_t  memory0_address ;     // M0AR;   /*!< DMA stream x memory 0 address register   */
  volatile uint32_t  memory1_address ;     // M1AR;   /*!< DMA stream x memory 1 address register   */
  fifo_control_t fifo_control ;            // FCR;    /*!< DMA stream x FIFO control register       */

  inline void clear()
     {
        disable();
        configuration.write(0);
        number_of_data=0;
        peripheral_address=0;
        memory0_address=0;
        memory1_address=0;
        fifo_control.write(0x21);
     }

} ;


struct dma1_stream0_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream0_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream0_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream0_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream0_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream0_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream0_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream0_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream0_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream0_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream0_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream0_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream1_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream1_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream1_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream1_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream1_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream1_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream1_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream1_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream1_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream1_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream1_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream1_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;


struct dma1_stream2_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream2_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream2_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream2_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream2_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream2_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream2_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream2_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream2_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream2_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream2_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream2_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream3_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream3_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream3_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream3_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream3_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream3_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream3_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream3_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream3_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream3_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream3_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream3_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream4_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream4_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream4_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream4_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream4_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream4_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream4_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream4_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream4_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream4_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream4_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream4_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream5_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream5_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream5_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream5_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream5_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream5_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream5_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream5_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream5_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream5_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream5_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream5_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream6_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream6_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream6_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream6_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream6_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream6_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream6_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream6_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream6_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream6_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream6_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream6_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma1_stream7_t : public dma_stream_t
{

  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma1.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream7_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma1.stream7_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma1.stream7_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma1.stream7_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma1.stream7_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma1.stream7_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma1.stream7_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma1.stream7_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma1.stream7_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma1.stream7_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma1.stream7_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma1.clock_enable(); }
  inline void clock_disable() { dma1.clock_disable(); }
  inline void reset() { dma1.reset(); }

} ;

struct dma2_stream0_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream0_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream0_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream0_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream0_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream0_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream0_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream0_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream0_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream0_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream0_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream0_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream0_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream1_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream1_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream1_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream1_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream1_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream1_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream1_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream1_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream1_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream1_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream1_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream1_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream1_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream2_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream2_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream2_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream2_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream2_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream2_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream2_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream2_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream2_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream2_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream2_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream2_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream2_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream3_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::low_interrupt_clear_t::stream3_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::low_interrupt_clear_t::stream3_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream3_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream3_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream3_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream3_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream3_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream3_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream3_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream3_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream3_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream3_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream4_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream4_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream4_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream4_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream4_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream4_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream4_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream4_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream4_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream4_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream4_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream4_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream4_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream5_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream5_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream5_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream5_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream5_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream5_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream5_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream5_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream5_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream5_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream5_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream5_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream5_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream6_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream6_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream6_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream6_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream6_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream6_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream6_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream6_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream6_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream6_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream6_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream6_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream6_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

struct dma2_stream7_t : public dma_stream_t
{
  // сброс сотояния потока DMA
  inline void clear()
     {
       dma_stream_t::clear();
       dma2.low_interrupt_clear.modify(
	                               dma_t::high_interrupt_clear_t::stream7_fifo_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_direct_mode_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_transfer_error_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_half_transfer_interrupt_flag_clear_t::clear,
				       dma_t::high_interrupt_clear_t::stream7_transfer_complete_interrupt_flag_clear_t::clear
				      );
     }

  inline auto fifo_error_interrupt_flag        ()  { return dma2.stream7_fifo_error_interrupt_flag();        }
  inline auto direct_mode_error_interrupt_flag ()  { return dma2.stream7_direct_mode_error_interrupt_flag(); }
  inline auto transfer_error_interrupt_flag    ()  { return dma2.stream7_transfer_error_interrupt_flag();    }
  inline auto half_transfer_interrupt_flag     ()  { return dma2.stream7_half_transfer_interrupt_flag();     }
  inline auto transfer_complete_interrupt_flag ()  { return dma2.stream7_transfer_complete_interrupt_flag(); }

  inline void fifo_error_interrupt_clear       () { dma2.stream7_fifo_error_interrupt_clear();       }
  inline void direct_mode_error_interrupt_clear() { dma2.stream7_direct_mode_error_interrupt_clear();}
  inline void transfer_error_interrupt_clear   () { dma2.stream7_transfer_error_interrupt_clear();   }
  inline void half_transfer_interrupt_clear    () { dma2.stream7_half_transfer_interrupt_clear();    }
  inline void transfer_complete_interrupt_clear() { dma2.stream7_transfer_complete_interrupt_clear();}

  inline void clock_enable() { dma2.clock_enable(); }
  inline void clock_disable() { dma2.clock_disable(); }
  inline void reset() { dma2.reset(); }

} ;

}

using namespace stm32 ;

#endif /* __DMA_STREAM_F4_F7++_H__ */
