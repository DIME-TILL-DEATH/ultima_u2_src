/*
 * sdio++.h
 *
 *  Created on: 7ибля 2018 г.
 *      Author: klen
 */

#ifndef __SDIO++_H__
#define __SDIO++_H__

#include "types++.h"


namespace stm32f4
{

struct sdio_t
{
  struct power_control_t : public read_write_32_t
    {
       struct power_t   { enum enum_t { offset=0, mask=0b11, off=0 , on=3 }; } ;
    } ;

  inline void power(const power_control_t::power_t::enum_t val) {  power_control.rmw( val );}
  inline void power_off() { power_control.rmw( power_control_t::power_t::off );}
  inline void power_on()  { power_control.rmw( power_control_t::power_t::on );}
  inline auto power() const { return power_control.rd<power_control_t::power_t>();}

  struct clock_control_t : public read_write_32_t
    {
       struct clk_divider_t          { enum enum_t { offset=0, mask=0xff,  }; } ;
       struct clk_t                  { enum enum_t { offset=8, mask=1, disable=0, enable }; } ;
       struct power_saving_t         { enum enum_t { offset=9, mask=1, disable=0, enable }; } ;
       struct clock_divider_bypass_t { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
       struct bus_wide_t             { enum enum_t { offset=11, mask=0b11, wide1=0, wide4, wide8 }; } ;
       struct ck_polarity_t          { enum enum_t { offset=13, mask=1, rising=0, falling }; } ;
       struct flow_control_t         { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
    };

  inline void clk_divider(const uint8_t val) {  clock_control.rmw( (clock_control_t::clk_divider_t::enum_t)val );}
  inline auto clk_divider() const { return (uint8_t)clock_control.rd<clock_control_t::clk_divider_t>();}

  inline void clk(const clock_control_t::clk_t::enum_t val) {  clock_control.rmw( val );}
  inline void clk_disable() { clock_control.rmw( clock_control_t::clk_t::disable );}
  inline void clk_enable()  { clock_control.rmw( clock_control_t::clk_t::enable );}
  inline auto clk() const { return clock_control.rd<clock_control_t::clk_t>();}

  inline void power_saving(const clock_control_t::power_saving_t::enum_t val) {  clock_control.rmw( val );}
  inline void power_saving_disable() { clock_control.rmw( clock_control_t::power_saving_t::disable );}
  inline void power_saving_enable()  { clock_control.rmw( clock_control_t::power_saving_t::enable );}
  inline auto power_saving() const { return clock_control.rd<clock_control_t::power_saving_t>();}

  inline void clock_divider_bypass(const clock_control_t::clock_divider_bypass_t::enum_t val) {  clock_control.rmw( val );}
  inline void clock_divider_bypass_disable() { clock_control.rmw( clock_control_t::clock_divider_bypass_t::disable );}
  inline void clock_divider_bypass_enable()  { clock_control.rmw( clock_control_t::clock_divider_bypass_t::enable );}
  inline auto clock_divider_bypass() const { return clock_control.rd<clock_control_t::clock_divider_bypass_t>();}

  inline void bus_wide(const clock_control_t::bus_wide_t::enum_t val) {  clock_control.rmw( val );}
  inline void bus_wide1() { clock_control.rmw( clock_control_t::bus_wide_t::wide1 );}
  inline void bus_wide4() { clock_control.rmw( clock_control_t::bus_wide_t::wide4 );}
  inline void bus_wide8() { clock_control.rmw( clock_control_t::bus_wide_t::wide8 );}
  inline auto bus_wide() const { return clock_control.rd<clock_control_t::bus_wide_t>();}

  inline void ck_polarity(const clock_control_t::ck_polarity_t::enum_t val) {  clock_control.rmw( val );}
  inline void ck_polarity_rising() { clock_control.rmw( clock_control_t::ck_polarity_t::rising );}
  inline void ck_polarity_falling() { clock_control.rmw( clock_control_t::ck_polarity_t::falling );}
  inline auto ck_polarity() const { return clock_control.rd<clock_control_t::ck_polarity_t>();}

  inline void flow_control(const clock_control_t::flow_control_t::enum_t val) {  clock_control.rmw( val );}
  inline void flow_control_disable() { clock_control.rmw( clock_control_t::flow_control_t::disable );}
  inline void flow_control_enable() { clock_control.rmw( clock_control_t::flow_control_t::enable );}
  inline auto flow_control() const { return clock_control.rd<clock_control_t::flow_control_t>();}

  struct command_t : public read_write_32_t
     {
        struct command_index_t            { enum enum_t { offset=0, mask=0b111111,   }; } ;
        struct wait_for_response_t        { enum enum_t { offset=6, mask=0b11, short_disable=0, short_enable, long_disable, long_enable  }; } ;
        struct cpsm_waits_for_interrupt_t { enum enum_t { offset=8, mask=1, disable=0, enable }; } ;
        struct cpsm_waits_for_ends_of_data_transfer_t { enum enum_t { offset=9, mask=1, disable=0, enable }; } ;
        struct cpsm_t                     { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct io_suspend_command_t       { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct command_completion_t       { enum enum_t { offset=12, mask=1, disable=0, enable }; } ;
        struct ceata_interrupt_t          { enum enum_t { offset=13, mask=1, enable=0, disable }; } ;
        struct ceata_command_t            { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
     };

  inline void command_index(const uint8_t val) {  command.rmw( (command_t::command_index_t::enum_t)val );}
  inline auto command_index() const { return (uint8_t)command.rd<command_t::command_index_t>();}

  inline void wait_for_response(const command_t::wait_for_response_t::enum_t val) {  command.rmw( val );}
  inline void wait_for_response_short_disable() { command.rmw( command_t::wait_for_response_t::short_disable );}
  inline void wait_for_response_short_enable() { command.rmw( command_t::wait_for_response_t::short_enable );}
  inline void wait_for_response_long_disable() { command.rmw( command_t::wait_for_response_t::long_disable );}
  inline void wait_for_response_long_enable() { command.rmw( command_t::wait_for_response_t::long_enable );}
  inline auto wait_for_response() const { return command.rd<command_t::wait_for_response_t>();}

  inline void cpsm_waits_for_interrupt(const command_t::cpsm_waits_for_interrupt_t::enum_t val) {  command.rmw( val );}
  inline void cpsm_waits_for_interrupt_disable() { command.rmw( command_t::cpsm_waits_for_interrupt_t::disable );}
  inline void cpsm_waits_for_interrupt_enable() { command.rmw( command_t::cpsm_waits_for_interrupt_t::enable );}
  inline auto cpsm_waits_for_interrupt() const { return command.rd<command_t::cpsm_waits_for_interrupt_t>();}

  inline void cpsm_waits_for_ends_of_data_transfer(const command_t::cpsm_waits_for_ends_of_data_transfer_t::enum_t val) {  command.rmw( val );}
  inline void cpsm_waits_for_ends_of_data_transfer_disable() { command.rmw( command_t::cpsm_waits_for_ends_of_data_transfer_t::disable );}
  inline void cpsm_waits_for_ends_of_data_transfer_enable() { command.rmw( command_t::cpsm_waits_for_ends_of_data_transfer_t::enable );}
  inline auto cpsm_waits_for_ends_of_data_transfer() const { return command.rd<command_t::cpsm_waits_for_ends_of_data_transfer_t>();}

  inline void cpsm(const command_t::cpsm_t::enum_t val) {  command.rmw( val );}
  inline void cpsm_disable() { command.rmw( command_t::cpsm_t::disable );}
  inline void cpsm_enable() { command.rmw( command_t::cpsm_t::enable );}
  inline auto cpsm() const { return command.rd<command_t::cpsm_t>();}

  inline void io_suspend_command(const command_t::io_suspend_command_t::enum_t val) {  command.rmw( val );}
  inline void io_suspend_command_disable() { command.rmw( command_t::io_suspend_command_t::disable );}
  inline void io_suspend_command_enable() { command.rmw( command_t::io_suspend_command_t::enable );}
  inline auto io_suspend_command() const { return command.rd<command_t::io_suspend_command_t>();}

  inline void command_completion(const command_t::command_completion_t::enum_t val) {  command.rmw( val );}
  inline void command_completion_disable() { command.rmw( command_t::command_completion_t::disable );}
  inline void command_completion_enable() { command.rmw( command_t::command_completion_t::enable );}
  inline auto command_completion() const { return command.rd<command_t::command_completion_t>();}

  inline void ceata_interrupt(const command_t::ceata_interrupt_t::enum_t val) {  command.rmw( val );}
  inline void ceata_interrupt_disable() { command.rmw( command_t::ceata_interrupt_t::disable );}
  inline void ceata_interrupt_enable() { command.rmw( command_t::ceata_interrupt_t::enable );}
  inline auto ceata_interrupt() const { return command.rd<command_t::ceata_interrupt_t>();}

  inline void ceata_command(const command_t::ceata_command_t::enum_t val) {  command.rmw( val );}
  inline void ceata_command_disable() { command.rmw( command_t::ceata_command_t::disable );}
  inline void ceata_command_enable() { command.rmw( command_t::ceata_command_t::enable );}
  inline auto ceata_command() const { return command.rd<command_t::ceata_command_t>();}

  struct data_control_t : public read_write_32_t
     {
        struct transfer_t        { enum enum_t { offset=0, mask=1, disable=0, enable  }; } ;
        struct direction_t       { enum enum_t { offset=1, mask=1, controller_to_card=0, card_to_controller  }; } ;
        struct transfer_mode_t   { enum enum_t { offset=2, mask=1, block=0, stream_or_multibyte }; } ;
        struct dma_t             { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct block_size_t      { enum enum_t { offset=4, mask=0xf, bytes1=0, bytes2,   bytes4,    bytes8,    bytes16,   bytes32,   bytes64,   bytes128,
                                                                     bytes256, bytes512, bytes1024, bytes2048, bytes4096, bytes8192, bytes16384 }; } ;
        struct read_wait_start_t { enum enum_t { offset=8, mask=1, disable=0, enable  }; } ;
        struct read_wait_stop_t  { enum enum_t { offset=9, mask=1, disable=0, enable  }; } ;
        struct read_wait_mode_t  { enum enum_t { offset=10, mask=1, d2=0, ck  }; } ;
        struct dpsm_sdio_operation_t  { enum enum_t { offset=11, mask=1, disable=0, enable  }; } ;
     };

  inline void transfer(const data_control_t::transfer_t::enum_t val) {  data_control.rmw( val );}
  inline void transfer_disable() { data_control.rmw( data_control_t::transfer_t::disable );}
  inline void transfer_enable() { data_control.rmw( data_control_t::transfer_t::enable );}
  inline auto transfer() const { return data_control.rd<data_control_t::transfer_t>();}

  inline void direction(const data_control_t::direction_t::enum_t val) {  data_control.rmw( val );}
  inline void direction_controller_to_card() { data_control.rmw( data_control_t::direction_t::controller_to_card );}
  inline void direction_card_to_controller() { data_control.rmw( data_control_t::direction_t::card_to_controller );}
  inline auto direction() const { return data_control.rd<data_control_t::direction_t>();}

  inline void transfer_mode(const data_control_t::transfer_mode_t::enum_t val) {  data_control.rmw( val );}
  inline void transfer_mode_block() { data_control.rmw( data_control_t::transfer_mode_t::block );}
  inline void transfer_mode_stream_or_multibyte() { data_control.rmw( data_control_t::transfer_mode_t::stream_or_multibyte );}
  inline auto transfer_mode() const { return data_control.rd<data_control_t::transfer_mode_t>();}

  inline void dma(const data_control_t::dma_t::enum_t val) {  data_control.rmw( val );}
  inline void dma_disable() { data_control.rmw( data_control_t::dma_t::disable );}
  inline void dma_enable() { data_control.rmw( data_control_t::dma_t::enable );}
  inline auto dma() const { return data_control.rd<data_control_t::dma_t>();}

  inline void block_size(const data_control_t::block_size_t::enum_t val) {  data_control.rmw( val );}
  inline void block_size_bytes1() { data_control.rmw( data_control_t::block_size_t::bytes1 );}
  inline void block_size_bytes2() { data_control.rmw( data_control_t::block_size_t::bytes2 );}
  inline void block_size_bytes4() { data_control.rmw( data_control_t::block_size_t::bytes4 );}
  inline void block_size_bytes8() { data_control.rmw( data_control_t::block_size_t::bytes8 );}
  inline void block_size_bytes16() { data_control.rmw( data_control_t::block_size_t::bytes16 );}
  inline void block_size_bytes32() { data_control.rmw( data_control_t::block_size_t::bytes32 );}
  inline void block_size_bytes64() { data_control.rmw( data_control_t::block_size_t::bytes64 );}
  inline void block_size_bytes128() { data_control.rmw( data_control_t::block_size_t::bytes128 );}
  inline void block_size_bytes256() { data_control.rmw( data_control_t::block_size_t::bytes256 );}
  inline void block_size_bytes512() { data_control.rmw( data_control_t::block_size_t::bytes512 );}
  inline void block_size_bytes1024() { data_control.rmw( data_control_t::block_size_t::bytes1024 );}
  inline void block_size_bytes2048() { data_control.rmw( data_control_t::block_size_t::bytes2048 );}
  inline void block_size_bytes4096() { data_control.rmw( data_control_t::block_size_t::bytes4096 );}
  inline void block_size_bytes8192() { data_control.rmw( data_control_t::block_size_t::bytes8192 );}
  inline void block_size_bytes16384() { data_control.rmw( data_control_t::block_size_t::bytes16384 );}
  inline auto block_size() const { return data_control.rd<data_control_t::block_size_t>();}

  inline void read_wait_start(const data_control_t::read_wait_start_t::enum_t val) {  data_control.rmw( val );}
  inline void read_wait_start_disable() { data_control.rmw( data_control_t::read_wait_start_t::disable );}
  inline void read_wait_start_enable() { data_control.rmw( data_control_t::read_wait_start_t::enable );}
  inline auto read_wait_start() const { return data_control.rd<data_control_t::read_wait_start_t>();}

  inline void read_wait_stop(const data_control_t::read_wait_stop_t::enum_t val) {  data_control.rmw( val );}
  inline void read_wait_stop_disable() { data_control.rmw( data_control_t::read_wait_stop_t::disable );}
  inline void read_wait_stop_enable() { data_control.rmw( data_control_t::read_wait_stop_t::enable );}
  inline auto read_wait_stop() const { return data_control.rd<data_control_t::read_wait_stop_t>();}

  inline void read_wait_mode(const data_control_t::read_wait_mode_t::enum_t val) {  data_control.rmw( val );}
  inline void read_wait_mode_d2() { data_control.rmw( data_control_t::read_wait_mode_t::d2 );}
  inline void read_wait_mode_ck() { data_control.rmw( data_control_t::read_wait_mode_t::ck );}
  inline auto read_wait_mode() const { return data_control.rd<data_control_t::read_wait_mode_t>();}

  inline void dpsm_sdio_operation(const data_control_t::dpsm_sdio_operation_t::enum_t val) {  data_control.rmw( val );}
  inline void dpsm_sdio_operation_disable() { data_control.rmw( data_control_t::dpsm_sdio_operation_t::disable );}
  inline void dpsm_sdio_operation_enable() { data_control.rmw( data_control_t::dpsm_sdio_operation_t::enable );}
  inline auto dpsm_sdio_operation() const { return data_control.rd<data_control_t::dpsm_sdio_operation_t>();}

  struct  status_t : public read_write_32_t
     {
        struct command_response_crc_failed_t  { enum enum_t { offset=0,  mask=1, not_occured=0, occured  }; } ;
        struct data_block_crc_failed_t        { enum enum_t { offset=1,  mask=1, not_occured=0, occured  }; } ;
        struct command_response_timeout_t     { enum enum_t { offset=2,  mask=1, not_occured=0, occured  }; } ;
        struct data_timeout_t                 { enum enum_t { offset=3,  mask=1, not_occured=0, occured  }; } ;
        struct tx_fifo_underrun_error_t       { enum enum_t { offset=4,  mask=1, not_occured=0, occured  }; } ;
        struct rx_fifo_overrun_error_t        { enum enum_t { offset=5,  mask=1, not_occured=0, occured  }; } ;
        struct command_response_received_t    { enum enum_t { offset=6,  mask=1, not_occured=0, occured  }; } ;
        struct command_sent_t                 { enum enum_t { offset=7,  mask=1, not_occured=0, occured  }; } ;
        struct data_end_t                     { enum enum_t { offset=8,  mask=1, not_occured=0, occured  }; } ;
        struct start_bit_not_detected_t       { enum enum_t { offset=9,  mask=1, not_occured=0, occured  }; } ;
        struct data_block_end_t               { enum enum_t { offset=10, mask=1, not_occured=0, occured  }; } ;
        struct command_xfer_in_pogress_t      { enum enum_t { offset=11, mask=1, not_occured=0, occured  }; } ;
        struct data_tx_in_progress_t          { enum enum_t { offset=12, mask=1, not_occured=0, occured  }; } ;
        struct data_rx_in_progress_t          { enum enum_t { offset=13, mask=1, not_occured=0, occured  }; } ;
        struct tx_fifo_half_empty_t           { enum enum_t { offset=14, mask=1, not_occured=0, occured  }; } ;
        struct rx_fifo_half_full_t            { enum enum_t { offset=15, mask=1, not_occured=0, occured  }; } ;
        struct tx_fifo_full_t                 { enum enum_t { offset=16, mask=1, not_occured=0, occured  }; } ;
        struct rx_fifo_full_t                 { enum enum_t { offset=17, mask=1, not_occured=0, occured  }; } ;
        struct tx_fifo_empty_t                { enum enum_t { offset=18, mask=1, not_occured=0, occured  }; } ;
        struct rx_fifo_empty_t                { enum enum_t { offset=19, mask=1, not_occured=0, occured  }; } ;
        struct data_available_in_tx_fifo_t    { enum enum_t { offset=20, mask=1, not_occured=0, occured  }; } ;
        struct data_available_in_rx_fifo_t    { enum enum_t { offset=21, mask=1, not_occured=0, occured  }; } ;
        struct sd_io_received_t               { enum enum_t { offset=22, mask=1, not_occured=0, occured  }; } ;
        struct ce_ata_end_t                   { enum enum_t { offset=23, mask=1, not_occured=0, occured  }; } ;
     };

  inline auto command_response_crc_failed() const { return status.rd<status_t::command_response_crc_failed_t>();}
  inline auto data_block_crc_failed() const       { return status.rd<status_t::data_block_crc_failed_t>();}
  inline auto command_response_timeout() const    { return status.rd<status_t::command_response_timeout_t>();}
  inline auto data_timeout() const                { return status.rd<status_t::data_timeout_t>();}
  inline auto tx_fifo_underrun_error() const      { return status.rd<status_t::tx_fifo_underrun_error_t>();}
  inline auto rx_fifo_overrun_error() const       { return status.rd<status_t::rx_fifo_overrun_error_t>();}
  inline auto command_response_received() const   { return status.rd<status_t::command_response_received_t>();}
  inline auto command_sent() const                { return status.rd<status_t::command_sent_t>();}
  inline auto data_end() const                    { return status.rd<status_t::data_end_t>();}
  inline auto start_bit_not_detected() const      { return status.rd<status_t::start_bit_not_detected_t>();}
  inline auto data_block_end() const              { return status.rd<status_t::data_block_end_t>();}
  inline auto command_xfer_in_pogress() const     { return status.rd<status_t::command_xfer_in_pogress_t>();}
  inline auto data_tx_in_progress() const         { return status.rd<status_t::data_tx_in_progress_t>();}
  inline auto data_rx_in_progress() const         { return status.rd<status_t::data_rx_in_progress_t>();}
  inline auto tx_fifo_half_empty() const          { return status.rd<status_t::tx_fifo_half_empty_t>();}
  inline auto rx_fifo_half_full() const           { return status.rd<status_t::rx_fifo_half_full_t>();}
  inline auto tx_fifo_full() const                { return status.rd<status_t::tx_fifo_full_t>();}
  inline auto rx_fifo_full() const                { return status.rd<status_t::rx_fifo_full_t>();}
  inline auto tx_fifo_empty() const               { return status.rd<status_t::tx_fifo_empty_t>();}
  inline auto rx_fifo_empty() const               { return status.rd<status_t::rx_fifo_empty_t>();}
  inline auto data_available_in_tx_fifo() const   { return status.rd<status_t::data_available_in_tx_fifo_t>();}
  inline auto data_available_in_rx_fifo() const   { return status.rd<status_t::data_available_in_rx_fifo_t>();}
  inline auto sd_io_received() const              { return status.rd<status_t::sd_io_received_t>();}
  inline auto ce_ata_end() const                  { return status.rd<status_t::ce_ata_end_t>();}

  struct  interrupt_clear_t : public read_write_32_t
     {
       struct command_response_crc_failed_clear_t  { enum enum_t { offset=0,  mask=1, clear=1  }; } ;
       struct data_block_crc_failed_clear_t        { enum enum_t { offset=1,  mask=1, clear=1  }; } ;
       struct command_response_timeout_clear_t     { enum enum_t { offset=2,  mask=1, clear=1  }; } ;
       struct data_timeout_clear_t                 { enum enum_t { offset=3,  mask=1, clear=1  }; } ;
       struct tx_fifo_underrun_error_clear_t       { enum enum_t { offset=4,  mask=1, clear=1  }; } ;
       struct rx_fifo_overrun_error_clear_t        { enum enum_t { offset=5,  mask=1, clear=1  }; } ;
       struct command_response_received_clear_t    { enum enum_t { offset=6,  mask=1, clear=1  }; } ;
       struct command_sent_clear_t                 { enum enum_t { offset=7,  mask=1, clear=1  }; } ;
       struct data_end_clear_t                     { enum enum_t { offset=8,  mask=1, clear=1  }; } ;
       struct start_bit_not_detected_clear_t       { enum enum_t { offset=9,  mask=1, clear=1  }; } ;
       struct data_block_end_clear_t               { enum enum_t { offset=10, mask=1, clear=1  }; } ;

       struct sd_io_received_clear_t               { enum enum_t { offset=22, mask=1, clear=1  }; } ;
       struct ce_ata_end_clear_t                   { enum enum_t { offset=23, mask=1, clear=1  }; } ;
     };

  inline void command_response_crc_failed_clear()  { interrupt_clear.wr(interrupt_clear_t::command_response_crc_failed_clear_t::clear);}
  inline void data_block_crc_failed_clear()        { interrupt_clear.wr(interrupt_clear_t::data_block_crc_failed_clear_t::clear);}
  inline void command_response_timeout_clear()     { interrupt_clear.wr(interrupt_clear_t::command_response_timeout_clear_t::clear);}
  inline void data_timeout_clear()                 { interrupt_clear.wr(interrupt_clear_t::data_timeout_clear_t::clear);}
  inline void tx_fifo_underrun_error_clear()       { interrupt_clear.wr(interrupt_clear_t::tx_fifo_underrun_error_clear_t::clear);}
  inline void rx_fifo_overrun_error_clear()        { interrupt_clear.wr(interrupt_clear_t::rx_fifo_overrun_error_clear_t::clear);}
  inline void command_response_received_clear()    { interrupt_clear.wr(interrupt_clear_t::command_response_received_clear_t::clear);}
  inline void command_sent_clear()                 { interrupt_clear.wr(interrupt_clear_t::command_sent_clear_t::clear);}
  inline void data_end_clear()                     { interrupt_clear.wr(interrupt_clear_t::data_end_clear_t::clear);}
  inline void start_bit_not_detected_clear()       { interrupt_clear.wr(interrupt_clear_t::start_bit_not_detected_clear_t::clear);}
  inline void data_block_end_clear()               { interrupt_clear.wr(interrupt_clear_t::data_block_end_clear_t::clear);}

  inline void sd_io_received_clear()               { interrupt_clear.wr(interrupt_clear_t::sd_io_received_clear_t::clear);}
  inline void ce_ata_end_clear()                   { interrupt_clear.wr(interrupt_clear_t::ce_ata_end_clear_t::clear);}

  inline void static_flags_clear()                 {
                                                     interrupt_clear.write_or(
                                                	                         interrupt_clear_t::command_response_crc_failed_clear_t::clear,
									         interrupt_clear_t::data_block_crc_failed_clear_t::clear,
									         interrupt_clear_t::command_response_timeout_clear_t::clear,
									         interrupt_clear_t::data_timeout_clear_t::clear,
									         interrupt_clear_t::tx_fifo_underrun_error_clear_t::clear,
									         interrupt_clear_t::rx_fifo_overrun_error_clear_t::clear,
									         interrupt_clear_t::command_response_received_clear_t::clear,
									         interrupt_clear_t::command_sent_clear_t::clear,
									         interrupt_clear_t::data_end_clear_t::clear,
									         interrupt_clear_t::start_bit_not_detected_clear_t::clear,
									         interrupt_clear_t::data_block_end_clear_t::clear
									         /*interrupt_clear_t::sd_io_received_clear_t::clear,
									         interrupt_clear_t::ce_ata_end_clear_t::clear*/
                                                                               );
                                                   }

  struct  mask_t : public read_write_32_t
     {
       struct command_response_crc_failed_interrupt_t  { enum enum_t { offset=0,  mask=1, disable=0, enable  }; } ;
       struct data_block_crc_failed_interrupt_t        { enum enum_t { offset=1,  mask=1, disable=0, enable  }; } ;
       struct command_response_timeout_interrupt_t     { enum enum_t { offset=2,  mask=1, disable=0, enable  }; } ;
       struct data_timeout_interrupt_t                 { enum enum_t { offset=3,  mask=1, disable=0, enable  }; } ;
       struct tx_fifo_underrun_error_interrupt_t       { enum enum_t { offset=4,  mask=1, disable=0, enable  }; } ;
       struct rx_fifo_overrun_error_interrupt_t        { enum enum_t { offset=5,  mask=1, disable=0, enable  }; } ;
       struct command_response_received_interrupt_t    { enum enum_t { offset=6,  mask=1, disable=0, enable  }; } ;
       struct command_sent_interrupt_t                 { enum enum_t { offset=7,  mask=1, disable=0, enable  }; } ;
       struct data_end_interrupt_t                     { enum enum_t { offset=8,  mask=1, disable=0, enable  }; } ;
       struct start_bit_not_detected_interrupt_t       { enum enum_t { offset=9,  mask=1, disable=0, enable  }; } ;
       struct data_block_end_interrupt_t               { enum enum_t { offset=10, mask=1, disable=0, enable  }; } ;
       struct command_xfer_in_pogress_interrupt_t      { enum enum_t { offset=11, mask=1, disable=0, enable  }; } ;
       struct data_tx_in_progress_interrupt_t          { enum enum_t { offset=12, mask=1, disable=0, enable  }; } ;
       struct data_rx_in_progress_interrupt_t          { enum enum_t { offset=13, mask=1, disable=0, enable  }; } ;
       struct tx_fifo_half_empty_interrupt_t           { enum enum_t { offset=14, mask=1, disable=0, enable  }; } ;
       struct rx_fifo_half_full_interrupt_t            { enum enum_t { offset=15, mask=1, disable=0, enable  }; } ;
       struct tx_fifo_full_interrupt_t                 { enum enum_t { offset=16, mask=1, disable=0, enable  }; } ;
       struct rx_fifo_full_interrupt_t                 { enum enum_t { offset=17, mask=1, disable=0, enable  }; } ;
       struct tx_fifo_empty_interrupt_t                { enum enum_t { offset=18, mask=1, disable=0, enable  }; } ;
       struct rx_fifo_empty_interrupt_t                { enum enum_t { offset=19, mask=1, disable=0, enable  }; } ;
       struct data_available_in_tx_fifo_interrupt_t    { enum enum_t { offset=20, mask=1, disable=0, enable  }; } ;
       struct data_available_in_rx_fifo_interrupt_t    { enum enum_t { offset=21, mask=1, disable=0, enable  }; } ;
       struct sd_io_received_interrupt_t               { enum enum_t { offset=22, mask=1, disable=0, enable  }; } ;
       struct ce_ata_end_interrupt_t                   { enum enum_t { offset=23, mask=1, disable=0, enable  }; } ;
    };

  inline void command_response_crc_failed_interrupt(const mask_t::command_response_crc_failed_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void command_response_crc_failed_interrupt_disable() { mask.rmw( mask_t::command_response_crc_failed_interrupt_t::disable );}
  inline void command_response_crc_failed_interrupt_enable() { mask.rmw( mask_t::command_response_crc_failed_interrupt_t::enable );}
  inline auto command_response_crc_failed_interrupt() const { return mask.rd<mask_t::command_response_crc_failed_interrupt_t>();}

  inline void data_block_crc_failed_interrupt(const mask_t::data_block_crc_failed_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_block_crc_failed_interrupt_disable() { mask.rmw( mask_t::data_block_crc_failed_interrupt_t::disable );}
  inline void data_block_crc_failed_interrupt_enable() { mask.rmw( mask_t::data_block_crc_failed_interrupt_t::enable );}
  inline auto data_block_crc_failed_interrupt() const { return mask.rd<mask_t::data_block_crc_failed_interrupt_t>();}

  inline void command_response_timeout_interrupt(const mask_t::command_response_timeout_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void command_response_timeout_interrupt_disable() { mask.rmw( mask_t::command_response_timeout_interrupt_t::disable );}
  inline void command_response_timeout_interrupt_enable() { mask.rmw( mask_t::command_response_timeout_interrupt_t::enable );}
  inline auto command_response_timeout_interrupt() const { return mask.rd<mask_t::command_response_timeout_interrupt_t>();}

  inline void data_timeout_interrupt(const mask_t::data_timeout_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_timeout_interrupt_disable() { mask.rmw( mask_t::data_timeout_interrupt_t::disable );}
  inline void data_timeout_interrupt_enable() { mask.rmw( mask_t::data_timeout_interrupt_t::enable );}
  inline auto data_timeout_interrupt() const { return mask.rd<mask_t::data_timeout_interrupt_t>();}

  inline void tx_fifo_underrun_error_interrupt(const mask_t::tx_fifo_underrun_error_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void tx_fifo_underrun_error_interrupt_disable() { mask.rmw( mask_t::tx_fifo_underrun_error_interrupt_t::disable );}
  inline void tx_fifo_underrun_error_interrupt_enable() { mask.rmw( mask_t::tx_fifo_underrun_error_interrupt_t::enable );}
  inline auto tx_fifo_underrun_error_interrupt() const { return mask.rd<mask_t::tx_fifo_underrun_error_interrupt_t>();}

  inline void rx_fifo_overrun_error_interrupt(const mask_t::rx_fifo_overrun_error_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void rx_fifo_overrun_error_interrupt_disable() { mask.rmw( mask_t::rx_fifo_overrun_error_interrupt_t::disable );}
  inline void rx_fifo_overrun_error_interrupt_enable() { mask.rmw( mask_t::rx_fifo_overrun_error_interrupt_t::enable );}
  inline auto rx_fifo_overrun_error_interrupt() const { return mask.rd<mask_t::rx_fifo_overrun_error_interrupt_t>();}

  inline void command_response_received_interrupt(const mask_t::command_response_received_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void command_response_received_interrupt_disable() { mask.rmw( mask_t::command_response_received_interrupt_t::disable );}
  inline void command_response_received_interrupt_enable() { mask.rmw( mask_t::command_response_received_interrupt_t::enable );}
  inline auto command_response_received_interrupt() const { return mask.rd<mask_t::command_response_received_interrupt_t>();}

  inline void command_sent_interrupt(const mask_t::command_sent_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void command_sent_interrupt_disable() { mask.rmw( mask_t::command_sent_interrupt_t::disable );}
  inline void command_sent_interrupt_enable() { mask.rmw( mask_t::command_sent_interrupt_t::enable );}
  inline auto command_sent_interrupt() const { return mask.rd<mask_t::command_sent_interrupt_t>();}

  inline void data_end_interrupt(const mask_t::data_end_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_end_interrupt_disable() { mask.rmw( mask_t::data_end_interrupt_t::disable );}
  inline void data_end_interrupt_enable() { mask.rmw( mask_t::data_end_interrupt_t::enable );}
  inline auto data_end_interrupt() const { return mask.rd<mask_t::data_end_interrupt_t>();}

  inline void start_bit_not_detected_interrupt(const mask_t::start_bit_not_detected_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void start_bit_not_detected_interrupt_disable() { mask.rmw( mask_t::start_bit_not_detected_interrupt_t::disable );}
  inline void start_bit_not_detected_interrupt_enable() { mask.rmw( mask_t::start_bit_not_detected_interrupt_t::enable );}
  inline auto start_bit_not_detected_interrupt() const { return mask.rd<mask_t::start_bit_not_detected_interrupt_t>();}

  inline void data_block_end_interrupt(const mask_t::data_block_end_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_block_end_interrupt_disable() { mask.rmw( mask_t::data_block_end_interrupt_t::disable );}
  inline void data_block_end_interrupt_enable() { mask.rmw( mask_t::data_block_end_interrupt_t::enable );}
  inline auto data_block_end_interrupt() const { return mask.rd<mask_t::data_block_end_interrupt_t>();}

  inline void command_xfer_in_pogress_interrupt(const mask_t::command_xfer_in_pogress_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void command_xfer_in_pogress_interrupt_disable() { mask.rmw( mask_t::command_xfer_in_pogress_interrupt_t::disable );}
  inline void command_xfer_in_pogress_interrupt_enable() { mask.rmw( mask_t::command_xfer_in_pogress_interrupt_t::enable );}
  inline auto command_xfer_in_pogress_interrupt() const { return mask.rd<mask_t::command_xfer_in_pogress_interrupt_t>();}

  inline void data_tx_in_progress_interrupt(const mask_t::data_tx_in_progress_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_tx_in_progress_interrupt_disable() { mask.rmw( mask_t::data_tx_in_progress_interrupt_t::disable );}
  inline void data_tx_in_progress_interrupt_enable() { mask.rmw( mask_t::data_tx_in_progress_interrupt_t::enable );}
  inline auto data_tx_in_progress_interrupt() const { return mask.rd<mask_t::data_tx_in_progress_interrupt_t>();}

  inline void data_rx_in_progress_interrupt(const mask_t::data_rx_in_progress_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_rx_in_progress_interrupt_disable() { mask.rmw( mask_t::data_rx_in_progress_interrupt_t::disable );}
  inline void data_rx_in_progress_interrupt_enable() { mask.rmw( mask_t::data_rx_in_progress_interrupt_t::enable );}
  inline auto data_rx_in_progress_interrupt() const { return mask.rd<mask_t::data_rx_in_progress_interrupt_t>();}

  inline void tx_fifo_half_empty_interrupt(const mask_t::tx_fifo_half_empty_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void tx_fifo_half_empty_interrupt_disable() { mask.rmw( mask_t::tx_fifo_half_empty_interrupt_t::disable );}
  inline void tx_fifo_half_empty_interrupt_enable() { mask.rmw( mask_t::tx_fifo_half_empty_interrupt_t::enable );}
  inline auto tx_fifo_half_empty_interrupt() const { return mask.rd<mask_t::tx_fifo_half_empty_interrupt_t>();}

  inline void rx_fifo_full_empty_interrupt(const mask_t::rx_fifo_half_full_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void rx_fifo_full_empty_interrupt_disable() { mask.rmw( mask_t::rx_fifo_half_full_interrupt_t::disable );}
  inline void rx_fifo_full_empty_interrupt_enable() { mask.rmw( mask_t::rx_fifo_half_full_interrupt_t::enable );}
  inline auto rx_fifo_full_empty_interrupt() const { return mask.rd<mask_t::rx_fifo_half_full_interrupt_t>();}

  inline void tx_fifo_full_interrupt(const mask_t::tx_fifo_full_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void tx_fifo_full_interrupt_disable() { mask.rmw( mask_t::tx_fifo_full_interrupt_t::disable );}
  inline void tx_fifo_full_interrupt_enable() { mask.rmw( mask_t::tx_fifo_full_interrupt_t::enable );}
  inline auto tx_fifo_full_interrupt() const { return mask.rd<mask_t::tx_fifo_full_interrupt_t>();}

  inline void rx_fifo_full_interrupt(const mask_t::rx_fifo_full_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void rx_fifo_full_interrupt_disable() { mask.rmw( mask_t::rx_fifo_full_interrupt_t::disable );}
  inline void rx_fifo_full_interrupt_enable() { mask.rmw( mask_t::rx_fifo_full_interrupt_t::enable );}
  inline auto rx_fifo_full_interrupt() const { return mask.rd<mask_t::rx_fifo_full_interrupt_t>();}

  inline void tx_fifo_empty_interrupt(const mask_t::tx_fifo_empty_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void tx_fifo_empty_interrupt_disable() { mask.rmw( mask_t::tx_fifo_empty_interrupt_t::disable );}
  inline void tx_fifo_empty_interrupt_enable() { mask.rmw( mask_t::tx_fifo_empty_interrupt_t::enable );}
  inline auto tx_fifo_empty_interrupt() const { return mask.rd<mask_t::tx_fifo_empty_interrupt_t>();}

  inline void rx_fifo_empty_interrupt(const mask_t::rx_fifo_empty_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void rx_fifo_empty_interrupt_disable() { mask.rmw( mask_t::rx_fifo_empty_interrupt_t::disable );}
  inline void rx_fifo_empty_interrupt_enable() { mask.rmw( mask_t::rx_fifo_empty_interrupt_t::enable );}
  inline auto rx_fifo_empty_interrupt() const { return mask.rd<mask_t::rx_fifo_empty_interrupt_t>();}

  inline void data_available_in_tx_fifo_interrupt(const mask_t::data_available_in_tx_fifo_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_available_in_tx_fifo_interrupt_disable() { mask.rmw( mask_t::data_available_in_tx_fifo_interrupt_t::disable );}
  inline void data_available_in_tx_fifo_interrupt_enable() { mask.rmw( mask_t::data_available_in_tx_fifo_interrupt_t::enable );}
  inline auto data_available_in_tx_fifo_interrupt() const { return mask.rd<mask_t::data_available_in_tx_fifo_interrupt_t>();}

  inline void data_available_in_rx_fifo_interrupt(const mask_t::data_available_in_rx_fifo_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void data_available_in_rx_fifo_interrupt_disable() { mask.rmw( mask_t::data_available_in_rx_fifo_interrupt_t::disable );}
  inline void data_available_in_rx_fifo_interrupt_enable() { mask.rmw( mask_t::data_available_in_rx_fifo_interrupt_t::enable );}
  inline auto data_available_in_rx_fifo_interrupt() const { return mask.rd<mask_t::data_available_in_rx_fifo_interrupt_t>();}

  inline void sd_io_received_interrupt(const mask_t::sd_io_received_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void sd_io_received_interrupt_disable() { mask.rmw( mask_t::sd_io_received_interrupt_t::disable );}
  inline void sd_io_received_interrupt_enable() { mask.rmw( mask_t::sd_io_received_interrupt_t::enable );}
  inline auto sd_io_received_interrupt() const { return mask.rd<mask_t::sd_io_received_interrupt_t>();}

  inline void ce_ata_end_interrupt(const mask_t::ce_ata_end_interrupt_t::enum_t val) {  mask.rmw( val );}
  inline void ce_ata_end_interrupt_disable() { mask.rmw( mask_t::ce_ata_end_interrupt_t::disable );}
  inline void ce_ata_end_interrupt_enable() { mask.rmw( mask_t::ce_ata_end_interrupt_t::enable );}
  inline auto ce_ata_end_interrupt() const { return mask.rd<mask_t::ce_ata_end_interrupt_t>();}


  power_control_t   power_control;    //POWER;          /*!< SDIO power control register,    Address offset: 0x00 */
  clock_control_t   clock_control;    //CLKCR;          /*!< SDI clock control register,     Address offset: 0x04 */
  volatile uint32_t argument ;        //ARG;            /*!< SDIO argument register,         Address offset: 0x08 */
  command_t         command;          //CMD;            /*!< SDIO command register,          Address offset: 0x0C */
  volatile uint32_t command_response; //RESPCMD;        /*!< SDIO command response register, Address offset: 0x10 */
  volatile uint32_t response_1;       //RESP1;          /*!< SDIO response 1 register,       Address offset: 0x14 */
  volatile uint32_t response_2;       //RESP2;          /*!< SDIO response 2 register,       Address offset: 0x18 */
  volatile uint32_t response_3;       //RESP3;          /*!< SDIO response 3 register,       Address offset: 0x1C */
  volatile uint32_t response_4;       //RESP4;          /*!< SDIO response 4 register,       Address offset: 0x20 */
  volatile uint32_t data_timer;       //DTIMER;         /*!< SDIO data timer register,       Address offset: 0x24 */
  volatile uint32_t data_length;      //DLEN;           /*!< SDIO data length register,      Address offset: 0x28 */
  data_control_t    data_control;     //DCTRL;          /*!< SDIO data control register,     Address offset: 0x2C */
  volatile uint32_t data_counter;     //DCOUNT;         /*!< SDIO data counter register,     Address offset: 0x30 */
  status_t          status;           //STA;            /*!< SDIO status register,           Address offset: 0x34 */
  interrupt_clear_t interrupt_clear;  //ICR;            /*!< SDIO interrupt clear register,  Address offset: 0x38 */
  mask_t            mask;             //MASK;           /*!< SDIO mask register,             Address offset: 0x3C */
  uint32_t          reserved0[2];                       /*!< Reserved, 0x40-0x44                                  */
  volatile uint32_t fifo_counter;     //FIFOCNT;        /*!< SDIO FIFO counter register,     Address offset: 0x48 */
  uint32_t          reserved1[13];                      /*!< Reserved, 0x4C-0x7C                                  */
  volatile uint32_t fifo;             //FIFO;           /*!< SDIO data FIFO register,        Address offset: 0x80 */



  struct cmd_t
  {     command_t::command_index_t::enum_t index;
    	command_t::wait_for_response_t::enum_t response;
  	command_t::cpsm_waits_for_interrupt_t::enum_t waits_for_interrupt;
  	command_t::cpsm_waits_for_ends_of_data_transfer_t::enum_t wait_for_ends;
  	command_t::cpsm_t::enum_t cpsm;
  } ;

  inline void send_command(const cmd_t& cmd, const uint32_t arg)
     {
        argument = arg;
        command.modify( cmd.index, cmd.response , cmd.waits_for_interrupt, cmd.wait_for_ends,  cmd.cpsm ) ;
     }

  struct data_t
     {
  	uint32_t period;
  	uint32_t length;
  	data_control_t::transfer_t::enum_t transfer;
  	data_control_t::direction_t::enum_t direction;
  	data_control_t::transfer_mode_t::enum_t transfer_mode;
  	data_control_t::block_size_t::enum_t block_size;

     } ;

  inline void setup_data(const data_t& data)
     {
        data_timer = data.period;
        data_length = data.length;
        data_control.modify( data.transfer, data.direction, data.transfer_mode, data.block_size );
     }

  inline void clock_enable()
     {
        rcc.sdio_enable();
     }

  inline void clock_disable()
     {
        rcc.sdio_disable();
     }

  inline void reset()
     {
        rcc.sdio_reset();
     };

} ;

static sdio_t& sdio = *((sdio_t*) sdio_addr);

}

using namespace stm32f4 ;

#endif /* __SDIO++_H__ */
