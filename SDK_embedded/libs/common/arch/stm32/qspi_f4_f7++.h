/*
 * qspi++.h
 *
 *  Created on: 26 дек. 2018 г.
 *      Author: klen
 */

#ifndef __QSPI++_H__
#define __QSPI++_H__

#include "types++.h"

namespace stm32
{

struct qspi_t
{

  struct control_t : public read_write_32_t
  {
    struct state_t                  { enum enum_t { offset=0, mask=1, disable=0 , enable }; } ;
    struct abort_t                  { enum enum_t { offset=1, mask=1, reset=0 , set }; } ;
    struct dma_t                    { enum enum_t { offset=2, mask=1, disable=0 , enable }; } ;
    struct timeout_counter_t        { enum enum_t { offset=3, mask=1, disable=0 , enable }; } ;
    struct sample_shift_t           { enum enum_t { offset=4, mask=1, no=0 , one_half_cycle }; } ;
    struct dual_flash_mode_t        { enum enum_t { offset=6, mask=1, disable=0 , enable }; } ;
    struct flash_memory_selection_t { enum enum_t { offset=7, mask=1, chip_1=0 , chip_2 }; } ;
    struct fifo_threshold_level_t   { enum enum_t { offset=8, mask=0b11111 }; } ;
    struct transfer_error_interrupt_t { enum enum_t { offset=16, mask=1, disable=0, enable }; } ;
    struct transfer_complete_interrupt_t { enum enum_t { offset=17, mask=1, disable=0, enable }; } ;
    struct fifo_threshold_interrupt_t { enum enum_t { offset=18, mask=1, disable=0, enable }; } ;
    struct status_match_interrupt_t { enum enum_t { offset=19, mask=1, disable=0, enable }; } ;
    struct timeout_interrupt_t      { enum enum_t { offset=20, mask=1, disable=0, enable }; } ;
    struct automatic_poll_mode_stop_t { enum enum_t { offset=22, mask=1, disable=0, enable }; } ;
    struct polling_match_mode_t     { enum enum_t { offset=23, mask=1, disable=0, enable }; } ;
    struct prescaler_t              { enum enum_t { offset=24, mask=0xff }; } ;
  } ;

  inline void state(const control_t::state_t::enum_t val) {  control.rmw( val );}
  inline void state_enable() { control.rmw( control_t::state_t::enable );}
  inline void state_disable() { control.rmw( control_t::state_t::disable );}
  inline auto state() const { return control.rd<control_t::state_t>();}

  inline void abort(const control_t::abort_t::enum_t val) {  control.rmw( val );}
  inline void abort_reset() { control.rmw( control_t::abort_t::reset );}
  inline void abort_set() { control.rmw( control_t::abort_t::set );}
  inline auto abort() const { return control.rd<control_t::abort_t>();}

  inline void dma(const control_t::dma_t::enum_t val) {  control.rmw( val );}
  inline void dma_enable() { control.rmw( control_t::dma_t::enable );}
  inline void dma_disable() { control.rmw( control_t::dma_t::disable );}
  inline auto dma() const { return control.rd<control_t::dma_t>();}

  inline void timeout_counter(const control_t::timeout_counter_t::enum_t val) {  control.rmw( val );}
  inline void timeout_counter_enable() { control.rmw( control_t::timeout_counter_t::enable );}
  inline void timeout_counter_disable() { control.rmw( control_t::timeout_counter_t::disable );}
  inline auto timeout_counter() const { return control.rd<control_t::timeout_counter_t>();}

  inline void sample_shift(const control_t::sample_shift_t::enum_t val) {  control.rmw( val );}
  inline void sample_shift_no() { control.rmw( control_t::sample_shift_t::no );}
  inline void sample_shift_one_half_cycle() { control.rmw( control_t::sample_shift_t::one_half_cycle );}
  inline auto sample_shift() const { return control.rd<control_t::sample_shift_t>();}

  inline void dual_flash_mode(const control_t::dual_flash_mode_t::enum_t val) {  control.rmw( val );}
  inline void dual_flash_mode_enable() { control.rmw( control_t::dual_flash_mode_t::enable );}
  inline void dual_flash_mode_disable() { control.rmw( control_t::dual_flash_mode_t::disable );}
  inline auto dual_flash_mode() const { return control.rd<control_t::dual_flash_mode_t>();}

  inline void flash_memory_selection(const control_t::flash_memory_selection_t::enum_t val) {control.rmw( val );}
  inline void flash_memory_selection_chip_1() {control.rmw( control_t::flash_memory_selection_t::chip_1 );}
  inline void flash_memory_selection_chip_2() {control.rmw( control_t::flash_memory_selection_t::chip_2 );}
  inline auto flash_memory_selection() const {return control.rd<control_t::flash_memory_selection_t>();}

  inline void fifo_threshold_level(const uint8_t val) {control.rmw( (control_t::fifo_threshold_level_t::enum_t)val );}
  inline auto fifo_threshold_level() const {return (uint8_t) control.rd<control_t::fifo_threshold_level_t>();}

  inline void transfer_error_interrupt(const control_t::transfer_error_interrupt_t::enum_t val) {  control.rmw( val );}
  inline void transfer_error_interrupt_enable() { control.rmw( control_t::transfer_error_interrupt_t::enable );}
  inline void transfer_error_interrupt_disable() { control.rmw( control_t::transfer_error_interrupt_t::disable );}
  inline auto transfer_error_interrupt() const { return control.rd<control_t::transfer_error_interrupt_t>();}

  inline void transfer_complete_interrupt(const control_t::transfer_complete_interrupt_t::enum_t val) {  control.rmw( val );}
  inline void transfer_complete_interrupt_enable() { control.rmw( control_t::transfer_complete_interrupt_t::enable );}
  inline void transfer_complete_interrupt_disable() { control.rmw( control_t::transfer_complete_interrupt_t::disable );}
  inline auto transfer_complete_interrupt() const { return control.rd<control_t::transfer_complete_interrupt_t>();}

  inline void fifo_threshold_interrupt(const control_t::fifo_threshold_interrupt_t::enum_t val) {  control.rmw( val );}
  inline void fifo_threshold_interrupt_enable() { control.rmw( control_t::fifo_threshold_interrupt_t::enable );}
  inline void fifo_threshold_interrupt_disable() { control.rmw( control_t::fifo_threshold_interrupt_t::disable );}
  inline auto fifo_threshold_interrupt() const { return control.rd<control_t::fifo_threshold_interrupt_t>();}

  inline void status_match_interrupt(const control_t::status_match_interrupt_t::enum_t val) {  control.rmw( val );}
  inline void status_match_interrupt_enable() { control.rmw( control_t::status_match_interrupt_t::enable );}
  inline void status_match_interrupt_disable() { control.rmw( control_t::status_match_interrupt_t::disable );}
  inline auto status_match_interrupt() const { return control.rd<control_t::status_match_interrupt_t>();}

  inline void timeout_interrupt(const control_t::timeout_interrupt_t::enum_t val) {  control.rmw( val );}
  inline void timeout_interrupt_enable() { control.rmw( control_t::timeout_interrupt_t::enable );}
  inline void timeout_interrupt_disable() { control.rmw( control_t::timeout_interrupt_t::disable );}
  inline auto timeout_interrupt() const { return control.rd<control_t::timeout_interrupt_t>();}

  inline void automatic_poll_mode_stop(const control_t::automatic_poll_mode_stop_t::enum_t val) {  control.rmw( val );}
  inline void automatic_poll_mode_stop_enable() { control.rmw( control_t::automatic_poll_mode_stop_t::enable );}
  inline void automatic_poll_mode_stop_disable() { control.rmw( control_t::automatic_poll_mode_stop_t::disable );}
  inline auto automatic_poll_mode_stop() const { return control.rd<control_t::automatic_poll_mode_stop_t>();}

  inline void polling_match_mode(const control_t::polling_match_mode_t::enum_t val) {  control.rmw( val );}
  inline void polling_match_mode_enable() { control.rmw( control_t::polling_match_mode_t::enable );}
  inline void polling_match_mode_disable() { control.rmw( control_t::polling_match_mode_t::disable );}
  inline auto polling_match_mode() const { return control.rd<control_t::polling_match_mode_t>();}

  inline void prescaler (const uint8_t val) {  control.rmw( (control_t::prescaler_t::enum_t)val );}
  inline auto prescaler() const { return (uint8_t)control.rd<control_t::prescaler_t>();}


  struct config_t : public read_write_32_t
  {
    struct clock_mode_t            { enum enum_t { offset=0, mask=1, mode_0=0 , mode_3 }; } ;
    struct chip_select_high_time_t { enum enum_t { offset=8, mask=0b111, least_1_cycles=0, least_2_cycles, least_3_cycles, least_4_cycles, least_5_cycles, least_6_cycles, least_7_cycles, least_8_cycles  }; } ;
    struct flash_memory_size_t     { enum enum_t { offset=16, mask=0b11111 }; } ;
  } ;

  inline void clock_mode(const config_t::clock_mode_t::enum_t val) {  config.rmw( val );}
  inline void clock_mode_0() { config.rmw( config_t::clock_mode_t::mode_0 );}
  inline void clock_mode_3() { config.rmw( config_t::clock_mode_t::mode_3 );}
  inline auto clock_mode() const { return config.rd<config_t::clock_mode_t>();}

  inline void chip_select_high_time(const config_t::clock_mode_t::enum_t val) {  config.rmw( val );}
  inline void chip_select_high_time_least_1_cycles() { config.rmw( config_t::chip_select_high_time_t::least_1_cycles );}
  inline void chip_select_high_time_least_2_cycles() { config.rmw( config_t::chip_select_high_time_t::least_2_cycles );}
  inline void chip_select_high_time_least_3_cycles() { config.rmw( config_t::chip_select_high_time_t::least_3_cycles );}
  inline void chip_select_high_time_least_4_cycles() { config.rmw( config_t::chip_select_high_time_t::least_4_cycles );}
  inline void chip_select_high_time_least_5_cycles() { config.rmw( config_t::chip_select_high_time_t::least_5_cycles );}
  inline void chip_select_high_time_least_6_cycles() { config.rmw( config_t::chip_select_high_time_t::least_6_cycles );}
  inline void chip_select_high_time_least_7_cycles() { config.rmw( config_t::chip_select_high_time_t::least_7_cycles );}
  inline void chip_select_high_time_least_8_cycles() { config.rmw( config_t::chip_select_high_time_t::least_8_cycles );}
  inline auto chip_select_high_time() const { return config.rd<config_t::clock_mode_t>();}

  inline void flash_memory_size(const uint8_t val) {  config.rmw( (config_t::flash_memory_size_t::enum_t)val );}
  inline auto flash_memory_size() const { return (uint8_t)config.rd<config_t::flash_memory_size_t>();}

  struct status_t : public read_write_32_t
  {
    struct transfer_error_flag_t    { enum enum_t { offset=0, mask=1, not_occured=0, occured }; } ;
    struct transfer_complete_flag_t { enum enum_t { offset=1, mask=1, not_occured=0, occured }; } ;
    struct fifo_threshold_flag_t    { enum enum_t { offset=2, mask=1, not_occured=0, occured }; } ;
    struct status_match_flag_t      { enum enum_t { offset=3, mask=1, not_occured=0, occured }; } ;
    struct timeout_flag_t           { enum enum_t { offset=4, mask=1, not_occured=0, occured }; } ;
    struct busy_t                   { enum enum_t { offset=5, mask=1, idle=0, communication_or_fifo_not_empty }; } ;
    struct fifo_level_t             { enum enum_t { offset=8, mask=0b111111 }; } ;
  } ;

  inline auto transfer_error_flag()    const { return status.rd<status_t::transfer_error_flag_t>();}
  inline auto transfer_complete_flag() const { return status.rd<status_t::transfer_complete_flag_t>();}
  inline auto fifo_threshold_flag()    const { return status.rd<status_t::fifo_threshold_flag_t>();}
  inline auto status_match_flag()      const { return status.rd<status_t::status_match_flag_t>();}
  inline auto timeout_flag()           const { return status.rd<status_t::timeout_flag_t>();}
  inline auto busy()                   const { return status.rd<status_t::busy_t>();}
  inline auto fifo_level()             const { return status.rd<status_t::fifo_level_t>();}

  struct flag_clear_t : public read_write_32_t
  {
    struct transfer_error_flag_clear_t    { enum enum_t { offset=0, mask=1, no_effect=0, perform }; } ;
    struct transfer_complete_flag_clear_t { enum enum_t { offset=1, mask=1, no_effect=0, perform }; } ;
    struct status_match_flag_clear_t      { enum enum_t { offset=3, mask=1, no_effect=0, perform }; } ;
    struct timeout_flag_clear_t           { enum enum_t { offset=4, mask=1, no_effect=0, perform }; } ;
  } ;

  inline void transfer_error_flag_clear()    { flag_clear.rmw( flag_clear_t::transfer_error_flag_clear_t::perform );}
  inline void transfer_complete_flag_clear() { flag_clear.rmw( flag_clear_t::transfer_complete_flag_clear_t::perform );}
  inline void status_match_flag_clear()      { flag_clear.rmw( flag_clear_t::status_match_flag_clear_t::perform );}
  inline void timeout_flag_clear()           { flag_clear.rmw( flag_clear_t::timeout_flag_clear_t::perform );}

  struct data_length_t : public read_write_32_t
  {
  } ;

  inline void data_size(const uint32_t val) {  data_length.write(val-1 );}
  inline void data_size_undefined(const uint32_t val) {  data_length.write(0xffffffff);}
  inline auto data_size() const { return data_length.read() + 1 ;}

  struct communication_config_t : public read_write_32_t
  {
    struct instruction_t          { enum enum_t { offset=0,  mask=0xff }; } ;
    struct instruction_mode_t     { enum enum_t { offset=8,  mask=0b11, no=0, single_line, two_line, four_line }; } ;
    struct address_mode_t         { enum enum_t { offset=10, mask=0b11, no=0, single_line, two_line, four_line }; } ;
    struct address_size_t         { enum enum_t { offset=12, mask=0b11, size_8_bit=0, size_16_bit, size_24_bit, size_32_bit }; } ;
    struct alternate_bytes_mode_t { enum enum_t { offset=14, mask=0b11, no=0, single_line, two_line, four_line }; } ;
    struct alternate_bytes_size_t { enum enum_t { offset=16, mask=0b11, size_8_bit=0, size_16_bit, size_24_bit, size_32_bit }; } ;
    struct number_dummy_cycles_t  { enum enum_t { offset=18, mask=0b11111 }; } ;
    struct data_mode_t            { enum enum_t { offset=24, mask=0b11, no=0, single_line, two_line, four_line }; } ;
    struct functional_mode_t      { enum enum_t { offset=26, mask=0b11, indirect_write=0, indirect_read, automatic_polling, memory_mapped }; } ;
    struct send_instruction_mode_t{ enum enum_t { offset=28, mask=1, every_transaction=0, first_command }; } ;
    struct ddr_hold_t             { enum enum_t { offset=30, mask=1, analog_delay=0, cycle_1div4 }; } ;
    struct ddr_t                  { enum enum_t { offset=31, mask=1, disable=0, enable }; } ;
  } ;

  inline void instruction(const uint8_t val) {  communication_config.rmw( (communication_config_t::instruction_t::enum_t)val );}
  inline auto instruction() const { return (uint8_t)communication_config.rd<communication_config_t::instruction_t>();}

  inline void instruction_mode(const communication_config_t::instruction_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void instruction_mode_no() { communication_config.rmw( communication_config_t::instruction_mode_t::no );}
  inline void instruction_mode_single_line() { communication_config.rmw( communication_config_t::instruction_mode_t::single_line );}
  inline void instruction_mode_two_line() { communication_config.rmw( communication_config_t::instruction_mode_t::two_line );}
  inline void instruction_mode_four_line() { communication_config.rmw( communication_config_t::instruction_mode_t::four_line );}
  inline auto instruction_mode() const { return communication_config.rd<communication_config_t::instruction_mode_t>();}

  inline void address_mode(const communication_config_t::address_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void address_mode_no() { communication_config.rmw( communication_config_t::address_mode_t::no );}
  inline void address_mode_single_line() { communication_config.rmw( communication_config_t::address_mode_t::single_line );}
  inline void address_mode_two_line() { communication_config.rmw( communication_config_t::address_mode_t::two_line );}
  inline void address_mode_four_line() { communication_config.rmw( communication_config_t::address_mode_t::four_line );}
  inline auto address_mode() const { return communication_config.rd<communication_config_t::address_mode_t>();}

  inline void address_size(const communication_config_t::address_size_t::enum_t val) {  communication_config.rmw( val );}
  inline void address_size_8_bit() { communication_config.rmw( communication_config_t::address_size_t::size_8_bit );}
  inline void address_size_16_bit(){ communication_config.rmw( communication_config_t::address_size_t::size_16_bit );}
  inline void address_size_24_bit(){ communication_config.rmw( communication_config_t::address_size_t::size_24_bit );}
  inline void address_size_32_bit(){ communication_config.rmw( communication_config_t::address_size_t::size_32_bit );}
  inline auto address_size() const { return communication_config.rd<communication_config_t::address_size_t>();}

  inline void alternate_bytes_mode(const communication_config_t::alternate_bytes_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void alternate_bytes_mode_no() { communication_config.rmw( communication_config_t::alternate_bytes_mode_t::no );}
  inline void alternate_bytes_mode_single_line() { communication_config.rmw( communication_config_t::alternate_bytes_mode_t::single_line );}
  inline void alternate_bytes_mode_two_line() { communication_config.rmw( communication_config_t::alternate_bytes_mode_t::two_line );}
  inline void alternate_bytes_mode_four_line() { communication_config.rmw( communication_config_t::alternate_bytes_mode_t::four_line );}
  inline auto alternate_bytes_mode() const { return communication_config.rd<communication_config_t::alternate_bytes_mode_t>();}

  inline void alternate_bytes_size(const communication_config_t::alternate_bytes_size_t::enum_t val) {  communication_config.rmw( val );}
  inline void alternate_bytes_size_8_bit() { communication_config.rmw( communication_config_t::alternate_bytes_size_t::size_8_bit );}
  inline void alternate_bytes_size_16_bit(){ communication_config.rmw( communication_config_t::alternate_bytes_size_t::size_16_bit );}
  inline void alternate_bytes_size_24_bit(){ communication_config.rmw( communication_config_t::alternate_bytes_size_t::size_24_bit );}
  inline void alternate_bytes_size_32_bit(){ communication_config.rmw( communication_config_t::alternate_bytes_size_t::size_32_bit );}
  inline auto alternate_bytes_size() const { return communication_config.rd<communication_config_t::alternate_bytes_size_t>();}

  inline void number_dummy_cycles(const uint8_t val) {  communication_config.rmw( (communication_config_t::number_dummy_cycles_t::enum_t)val );}
  inline auto number_dummy_cycles() const { return (uint8_t) communication_config.rd<communication_config_t::number_dummy_cycles_t>();}

  inline void data_mode(const communication_config_t::data_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void data_mode_no() { communication_config.rmw( communication_config_t::data_mode_t::no );}
  inline void data_mode_single_line() { communication_config.rmw( communication_config_t::data_mode_t::single_line );}
  inline void data_mode_two_line() { communication_config.rmw( communication_config_t::data_mode_t::two_line );}
  inline void data_mode_four_line() { communication_config.rmw( communication_config_t::data_mode_t::four_line );}
  inline auto data_mode() const { return communication_config.rd<communication_config_t::data_mode_t>();}

  inline void functional_mode(const communication_config_t::functional_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void functional_mode_indirect_write() { communication_config.rmw( communication_config_t::functional_mode_t::indirect_write );}
  inline void functional_mode_indirect_read() { communication_config.rmw( communication_config_t::functional_mode_t::indirect_read );}
  inline void functional_mode_automatic_polling() { communication_config.rmw( communication_config_t::functional_mode_t::automatic_polling );}
  inline void functional_mode_memory_mapped() { communication_config.rmw( communication_config_t::functional_mode_t::memory_mapped );}
  inline auto functional_mode() const { return communication_config.rd<communication_config_t::functional_mode_t>();}

  inline void send_instruction_mode(const communication_config_t::send_instruction_mode_t::enum_t val) {  communication_config.rmw( val );}
  inline void send_instruction_mode_every_transaction() { communication_config.rmw( communication_config_t::send_instruction_mode_t::every_transaction );}
  inline void send_instruction_mode_first_command() { communication_config.rmw( communication_config_t::send_instruction_mode_t::first_command );}
  inline auto send_instruction_mode() const { return communication_config.rd<communication_config_t::send_instruction_mode_t>();}

  inline void ddr_hold(const communication_config_t::ddr_hold_t::enum_t val) {  communication_config.rmw( val );}
  inline void ddr_hold_analog_delay() { communication_config.rmw( communication_config_t::ddr_hold_t::analog_delay );}
  inline void ddr_hold_cycle_1div4() { communication_config.rmw( communication_config_t::ddr_hold_t::cycle_1div4 );}
  inline auto ddr_hold() const { return communication_config.rd<communication_config_t::ddr_hold_t>();}

  inline void ddr(const communication_config_t::ddr_t::enum_t val) {  communication_config.rmw( val );}
  inline void ddr_disable() { communication_config.rmw( communication_config_t::ddr_t::disable );}
  inline void ddr_enable() { communication_config.rmw( communication_config_t::ddr_t::enable );}
  inline auto ddr() const { return communication_config.rd<communication_config_t::ddr_t>();}


  control_t         control;                   // CR;       /*!< QUADSPI Control register,                           Address offset: 0x00 */
  config_t          config;                    // DCR;      /*!< QUADSPI Device Configuration register,              Address offset: 0x04 */
  status_t          status;                    // SR;       /*!< QUADSPI Status register,                            Address offset: 0x08 */
  flag_clear_t      flag_clear;                // FCR;      /*!< QUADSPI Flag Clear register,                        Address offset: 0x0C */
  data_length_t     data_length;               // DLR;      /*!< QUADSPI Data Length register,                       Address offset: 0x10 */
  communication_config_t communication_config; // CCR;      /*!< QUADSPI Communication Configuration register,       Address offset: 0x14 */
  volatile uint32_t address;                   // AR;       /*!< QUADSPI Address register,                           Address offset: 0x18 */
  volatile uint32_t alternate_bytes;           // ABR;      /*!< QUADSPI Alternate Bytes register,                   Address offset: 0x1C */
#if 0
  union {
	       struct
	         {
	    	   volatile uint8_t data_b0 ;
	    	   volatile uint8_t data_b1 ;
	    	   volatile uint8_t data_b2 ;
	    	   volatile uint8_t data_b3 ;
	         } ;
	       struct
	         {
	    	   volatile uint16_t data_hw0 ;
	    	   volatile uint16_t data_hw1 ;
	         } ;

           volatile uint32_t data;                      // DR;       /*!< QUADSPI Data register,                              Address offset: 0x20 */
        } ;
#endif

  union {
  volatile uint8_t  byte ;
  volatile uint32_t word;                      // DR;       /*!< QUADSPI Data register,                              Address offset: 0x20 */
        } data ;

  volatile uint32_t polling_status_mask;       // PSMKR;    /*!< QUADSPI Polling Status Mask register,               Address offset: 0x24 */
  volatile uint32_t polling_status_match;      // PSMAR;    /*!< QUADSPI Polling Status Match register,              Address offset: 0x28 */
  volatile uint32_t polling_interval;          // PIR;      /*!< QUADSPI Polling Interval register,                  Address offset: 0x2C */
  uint16_t : 16 ;
  volatile uint32_t low_power_timeout;         // LPTR;     /*!< QUADSPI Low Power Timeout register,                 Address offset: 0x30 */
  uint16_t : 16 ;

  inline void clock_enable() {  rcc.qspi_enable() ; }
  inline void clock_disable(){  rcc.qspi_disable() ; }
  inline void reset()        {  rcc.qspi_reset() ; }


  inline void flash_memory_size_bytes(const uint64_t val) { flash_memory_size(__builtin_ffs(val) - 2); }
  inline auto flash_memory_size_bytes() const { return (uint64_t) (1 << (flash_memory_size()+1));}


  inline void wait_not_busy() const{ while ( busy() == status_t::busy_t::communication_or_fifo_not_empty ) {} }



} ;



static qspi_t& qspi  = *((qspi_t*) qspi_addr);

}

using namespace stm32 ;

#endif /* __QSPI++_H__ */
