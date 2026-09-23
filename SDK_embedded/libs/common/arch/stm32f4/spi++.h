/*
 * spi++.h
 *
 *  Created on: 19 нбр. 2018 г.
 *      Author: klen
 */

#ifndef __SPI++_H__
#define __SPI++_H__

#include "types++.h"

namespace stm32f4
{

struct spi_t
{
  struct control_1_t : public read_write_32_t
  {
    struct clock_phase_t                  { enum enum_t { offset=0, mask=1, first_clock=0 , second_clock }; } ;
    struct clock_polarity_t               { enum enum_t { offset=1, mask=1, low=0, hight }; } ;
    struct mode_selection_t               { enum enum_t { offset=2, mask=1, slave=0, master }; } ;
    struct boud_rate_t                    { enum enum_t { offset=3, mask=0b111, fpclk_div_2=0, fpclk_div_4, fpclk_div_8, fpclk_div_16, fpclk_div_32, fpclk_div_64, fpclk_div_128, fpclk_div_256}; } ;
    struct state_t                        { enum enum_t { offset=6, mask=1, disable=0, enable }; } ;
    struct frame_first_t                  { enum enum_t { offset=7, mask=1, msb=0, lsb }; } ;
    struct internal_slave_t               { enum enum_t { offset=8, mask=1, deselect=0, select }; } ;
    struct software_slave_management_t    { enum enum_t { offset=9, mask=1, disable=0 , enable }; } ;
    struct receive_only_t                 { enum enum_t { offset=10, mask=1, disable=0 , enable }; } ;
    struct frame_size_t                   { enum enum_t { offset=11, mask=1, byte=0, word }; } ;
    struct crc_transfer_next_t            { enum enum_t { offset=12, mask=1, data_phase=0, next_transfer_is_crc }; } ;
    struct hardware_crc_calculation       { enum enum_t { offset=13, mask=1, disable=0, enable }; } ;
    struct output_in_bidirectional_mode_t { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
    struct bidirectional_data_mode_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;
  } ;

  inline void clock_phase(const control_1_t::clock_phase_t::enum_t val) {  control_1.rmw( val );}
  inline void clock_phase_first_clock() { control_1.rmw( control_1_t::clock_phase_t::first_clock );}
  inline void clock_phase_second_clock() { control_1.rmw( control_1_t::clock_phase_t::second_clock );}
  inline auto clock_phase() const { return control_1.rd<control_1_t::clock_phase_t>();}

  inline void clock_polarity(const control_1_t::clock_polarity_t::enum_t val) {  control_1.rmw( val );}
  inline void clock_polarity_low() { control_1.rmw( control_1_t::clock_polarity_t::low );}
  inline void clock_polarity_hight() { control_1.rmw( control_1_t::clock_polarity_t::hight );}
  inline auto clock_polarity() const { return control_1.rd<control_1_t::clock_polarity_t>();}

  inline void mode_selection(const control_1_t::mode_selection_t::enum_t val) {  control_1.rmw( val );}
  inline void mode_selection_slave() { control_1.rmw( control_1_t::mode_selection_t::slave );}
  inline void mode_selection_master() { control_1.rmw( control_1_t::mode_selection_t::master );}
  inline auto mode_selection()  const{ return control_1.rd<control_1_t::mode_selection_t>();}

  inline void boud_rate(const control_1_t::boud_rate_t::enum_t val) {  control_1.rmw( val );}
  inline void boud_rate_fpclk_div_2()   { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_2 );}
  inline void boud_rate_fpclk_div_4()   { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_4 );}
  inline void boud_rate_fpclk_div_8()   { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_8 );}
  inline void boud_rate_fpclk_div_16()  { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_16 );}
  inline void boud_rate_fpclk_div_32()  { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_32 );}
  inline void boud_rate_fpclk_div_64()  { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_64 );}
  inline void boud_rate_fpclk_div_128() { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_128 );}
  inline void boud_rate_fpclk_div_256() { control_1.rmw( control_1_t::boud_rate_t::fpclk_div_256 );}
  inline auto boud_rate() const { return control_1.rd<control_1_t::boud_rate_t>();}

  inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
  inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
  inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
  inline auto state() const { return control_1.rd<control_1_t::state_t>();}

  inline void frame_first(const control_1_t::frame_first_t::enum_t val) {  control_1.rmw( val );}
  inline void frame_first_msb() { control_1.rmw( control_1_t::frame_first_t::msb );}
  inline void frame_first_lsb() { control_1.rmw( control_1_t::frame_first_t::lsb );}
  inline auto frame_first() const { return control_1.rd<control_1_t::frame_first_t>();}

  inline void internal_slave(const control_1_t::internal_slave_t::enum_t val) {  control_1.rmw( val );}
  inline void internal_slave_deselect() { control_1.rmw( control_1_t::internal_slave_t::deselect );}
  inline void internal_slave_select() { control_1.rmw( control_1_t::internal_slave_t::select );}
  inline auto internal_slave() const { return control_1.rd<control_1_t::internal_slave_t>();}

  inline void software_slave_management_t(const control_1_t::software_slave_management_t::enum_t val) {  control_1.rmw( val );}
  inline void software_slave_management_disable(){ control_1.rmw( control_1_t::software_slave_management_t::disable );}
  inline void software_slave_management_enable() { control_1.rmw( control_1_t::software_slave_management_t::enable );}
  inline auto software_slave_management_t() const{ return control_1.rd<control_1_t::software_slave_management_t>();}

  inline void receive_only(const control_1_t::receive_only_t::enum_t val) {  control_1.rmw( val );}
  inline void receive_only_disable() { control_1.rmw( control_1_t::receive_only_t::disable );}
  inline void receive_only_enable() { control_1.rmw( control_1_t::receive_only_t::enable );}
  inline auto receive_only() const{ return control_1.rd<control_1_t::receive_only_t>();}


  inline void frame_size(const control_1_t::frame_size_t::enum_t val) {  control_1.rmw( val );}
  inline void frame_size_byte() { control_1.rmw( control_1_t::frame_size_t::byte );}
  inline void frame_size_word() { control_1.rmw( control_1_t::frame_size_t::word );}
  inline auto frame_size() const { return control_1.rd<control_1_t::frame_size_t>();}

  inline void crc_transfer_next(const control_1_t::crc_transfer_next_t::enum_t val) {  control_1.rmw( val );}
  inline void crc_transfer_next_data_phase() { control_1.rmw( control_1_t::crc_transfer_next_t::data_phase );}
  inline void crc_transfer_next_next_transfer_is_crc() { control_1.rmw( control_1_t::crc_transfer_next_t::next_transfer_is_crc );}
  inline auto crc_transfer_next() const { return control_1.rd<control_1_t::crc_transfer_next_t>();}

  inline void hardware_crc_calculation(const control_1_t::hardware_crc_calculation::enum_t val) {  control_1.rmw( val );}
  inline void hardware_crc_calculation_disable() { control_1.rmw( control_1_t::hardware_crc_calculation::disable );}
  inline void hardware_crc_calculation_enable() { control_1.rmw( control_1_t::hardware_crc_calculation::enable );}
  inline auto hardware_crc_calculation() const { return control_1.rd<control_1_t::hardware_crc_calculation>();}

  inline void output_in_bidirectional_mode(const control_1_t::output_in_bidirectional_mode_t::enum_t val) {  control_1.rmw( val );}
  inline void output_in_bidirectional_mode_disable() { control_1.rmw( control_1_t::output_in_bidirectional_mode_t::disable );}
  inline void output_in_bidirectional_mode_enable() { control_1.rmw( control_1_t::output_in_bidirectional_mode_t::enable );}
  inline auto output_in_bidirectional_mode() const { return control_1.rd<control_1_t::output_in_bidirectional_mode_t>();}

  inline void bidirectional_data_mode(const control_1_t::bidirectional_data_mode_t::enum_t val) {  control_1.rmw( val );}
  inline void bidirectional_data_mode_disable() { control_1.rmw( control_1_t::bidirectional_data_mode_t::disable );}
  inline void bidirectional_data_mode_enable() { control_1.rmw( control_1_t::bidirectional_data_mode_t::enable );}
  inline auto bidirectional_data_mode() const { return control_1.rd<control_1_t::bidirectional_data_mode_t>();}

  struct control_2_t : public read_write_32_t
  {
    struct rx_buff_dma_t                    { enum enum_t { offset=0, mask=1, disable=0 , enable }; } ;
    struct tx_buff_dma_t                    { enum enum_t { offset=1, mask=1, disable=0 , enable }; } ;
    struct ss_output_t                      { enum enum_t { offset=2, mask=1, disable=0 , enable }; } ;
    struct frame_format_t                   { enum enum_t { offset=4, mask=1, motorola=0 , texas_instruments }; } ;
    struct error_interupt_t                 { enum enum_t { offset=5, mask=1, disable=0 , enable }; } ;
    struct rx_buffer_not_empty_interrupt_t  { enum enum_t { offset=6, mask=1, disable=0 , enable }; } ;
    struct tx_buffer_empty_interrupt_t      { enum enum_t { offset=7, mask=1, disable=0 , enable }; } ;

  } ;

  inline void rx_buff_dma(const control_2_t::rx_buff_dma_t::enum_t val) {  control_2.rmw( val );}
  inline void rx_dma_buff_disable() { control_2.rmw( control_2_t::rx_buff_dma_t::disable );}
  inline void rx_dma_buff_enable()  { control_2.rmw( control_2_t::rx_buff_dma_t::enable );}
  inline auto rx_buff_dma() const { return control_2.rd<control_2_t::rx_buff_dma_t>();}

  inline void tx_buff_dma(const control_2_t::tx_buff_dma_t::enum_t val) {  control_2.rmw( val );}
  inline void tx_buff_dma_disable() { control_2.rmw( control_2_t::tx_buff_dma_t::disable );}
  inline void tx_buff_dma_enable()  { control_2.rmw( control_2_t::tx_buff_dma_t::enable );}
  inline auto tx_buff_dma_dma() const { return control_2.rd<control_2_t::tx_buff_dma_t>();}

  inline void ss_output(const control_2_t::ss_output_t::enum_t val) {  control_2.rmw( val );}
  inline void ss_output_disable() { control_2.rmw( control_2_t::ss_output_t::disable );}
  inline void ss_output_enable()  { control_2.rmw( control_2_t::ss_output_t::enable );}
  inline auto ss_output() const { return control_2.rd<control_2_t::ss_output_t>();}

  inline void frame_format(const control_2_t::frame_format_t::enum_t val) {  control_2.rmw( val );}
  inline void frame_format_motorola() { control_2.rmw( control_2_t::frame_format_t::motorola );}
  inline void frame_format_texas_instruments()  { control_2.rmw( control_2_t::frame_format_t::texas_instruments );}
  inline auto frame_format() const { return control_2.rd<control_2_t::frame_format_t>();}

  inline void error_interupt(const control_2_t::error_interupt_t::enum_t val) {  control_2.rmw( val );}
  inline void error_interupt_disable() { control_2.rmw( control_2_t::error_interupt_t::disable );}
  inline void error_interupt_enable()  { control_2.rmw( control_2_t::error_interupt_t::enable );}
  inline auto error_interupt_t() const { return control_2.rd<control_2_t::error_interupt_t>();}

  inline void rx_buffer_not_empty_interrupt(const control_2_t::rx_buffer_not_empty_interrupt_t::enum_t val) {  control_2.rmw( val );}
  inline void rx_buffer_not_empty_interrupt_disable() { control_2.rmw( control_2_t::rx_buffer_not_empty_interrupt_t::disable );}
  inline void rx_buffer_not_empty_interrupt_enable()  { control_2.rmw( control_2_t::rx_buffer_not_empty_interrupt_t::enable );}
  inline auto rx_buffer_not_empty_interrupt_t() const { return control_2.rd<control_2_t::rx_buffer_not_empty_interrupt_t>();}

  inline void tx_buffer_empty_interrupt(const control_2_t::tx_buffer_empty_interrupt_t::enum_t val) {  control_2.rmw( val );}
  inline void tx_buffer_empty_interrupt_disable() { control_2.rmw( control_2_t::tx_buffer_empty_interrupt_t::disable );}
  inline void tx_buffer_empty_interrupt_enable()  { control_2.rmw( control_2_t::tx_buffer_empty_interrupt_t::enable );}
  inline auto tx_buffer_empty_interrupt_t() const { return control_2.rd<control_2_t::tx_buffer_empty_interrupt_t>();}

  struct status_t : public read_write_32_t
  {
    struct rx_buff_t            { enum enum_t { offset=0, mask=1, empty=0 , not_empty }; } ;
    struct tx_buff_t            { enum enum_t { offset=1, mask=1, not_empty=0,  empty }; } ;
    struct channel_side_t       { enum enum_t { offset=2, mask=1, left=0,  right }; } ;
    struct underrun_t           { enum enum_t { offset=3, mask=1, no_occurred=0,  occurred }; } ;
    struct crc_error_t          { enum enum_t { offset=4, mask=1, match=0,  no_match }; } ;
    struct mode_fault_t         { enum enum_t { offset=5, mask=1, no_occurred=0,  occurred }; } ;
    struct overrun_t            { enum enum_t { offset=6, mask=1, no_occurred=0,  occurred }; } ;
    struct busy_t               { enum enum_t { offset=7, mask=1, idle=0, communication_or_tx_buffer_not_empty }; } ;
    struct frame_format_error_t { enum enum_t { offset=8, mask=1, no_occurred=0,  occurred }; } ;
  } ;

  inline auto rx_buff() const { return status.rd<status_t::rx_buff_t>();}
  inline auto tx_buff() const { return status.rd<status_t::tx_buff_t>();}
  inline auto channel_side() const { return status.rd<status_t::channel_side_t>();}
  inline auto underrun() const { return status.rd<status_t::underrun_t>();}

  inline auto crc_error() const { return status.rd<status_t::crc_error_t>();}
  inline void crc_error_clear() { status.rmw( status_t::crc_error_t::match );}
  
  inline auto  mode_fault() const { return status.rd<status_t::mode_fault_t>();}
  inline auto  overrun() const { return status.rd<status_t::overrun_t>();}
  inline auto  busy() const { return status.rd<status_t::busy_t>();}
  inline auto  frame_format_error() const { return status.rd<status_t::frame_format_error_t>();}

  control_1_t  control_1 ; //CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  control_2_t  control_2 ; //CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  status_t     status    ; //SR;         /*!< SPI status register,                                Address offset: 0x08 */
  union
  {
    struct
      {
         volatile uint8_t byte_data      ;
         const uint8_t : 8 ;
      } ;
    volatile uint16_t half_data      ; //DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  };
  const    uint16_t : 16 ;
  volatile uint16_t crc_polynomial ; //CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
  const    uint16_t : 16 ;  
  volatile uint16_t rx_crc ; //RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
  const    uint16_t : 16 ;  
  volatile uint16_t tx_crc ; //TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
  const    uint16_t : 16 ;

  // middle-level API


  inline void clock_enable()
     {
        switch((uint32_t)this)
          {
             case spi1_addr : rcc.spi1_enable(); break ;
             case spi2_addr : rcc.spi2_enable(); break ;
             case spi3_addr : rcc.spi3_enable(); break ;
             default: { std::__throw_invalid_argument("invalid SPI object") ; }
          }
     }

  inline void clock_disable()
     {
        switch((uint32_t)this)
          {
             case spi1_addr : rcc.spi1_disable(); break ;
             case spi2_addr : rcc.spi2_disable(); break ;
             case spi3_addr : rcc.spi3_disable(); break ;
             default: {  std::__throw_invalid_argument("invalid SPI object") ; }
          }
     }
  inline void reset()
     {
        switch((uint32_t)this)
          {
             case spi1_addr : rcc.spi1_reset(); break ;
             case spi2_addr : rcc.spi2_reset(); break ;
             case spi3_addr : rcc.spi3_reset(); break ;
             default: {  std::__throw_invalid_argument("invalid SPI object") ; }
          }
     };


  inline void wait_tx_empty() const{ while ( tx_buff() == status_t::tx_buff_t::not_empty ) {} }
  inline void wait_rx_not_empty() const{ while ( rx_buff() == status_t::rx_buff_t::empty ) {} }
  inline void wait_not_busy() const{ while ( busy() == status_t::busy_t::communication_or_tx_buffer_not_empty ) {} }

} ;


struct i2s_t
{
  struct config_t : public read_write_32_t
  {
    struct channel_length_t   { enum enum_t { offset=0, mask=1, word=0, double_word }; } ;
    struct data_length_t      { enum enum_t { offset=1, mask=0b11, two_bytes=0, three_bytes, four_bytes }; } ;
    struct i2s_clock_polarity_t   { enum enum_t { offset=3, mask=1, low=0, high }; } ;
    struct standard_t         { enum enum_t { offset=4, mask=0b11, philips=0, left_justified, right_justified, pcm }; } ;
    struct pcm_frame_synchronization_t   { enum enum_t { offset=7, mask=1, short_frane=0, long_frame }; } ;
    struct congiguration_mode_t { enum enum_t { offset=8, mask=0b11, slave_transmit=0, slave_receive, master_transmit, master_receive }; } ;
    struct i2s_state_t          { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
    struct mode_t               { enum enum_t { offset=11, mask=1, spi=0, i2s }; } ;
  };

  inline void channel_length(const config_t::channel_length_t::enum_t val) {  config.rmw( val );}
  inline void channel_length_word() { config.rmw( config_t::channel_length_t::word );}
  inline void channel_length_double_word() { config.rmw( config_t::channel_length_t::double_word );}
  inline auto channel_length() const { return config.rd<config_t::channel_length_t>();}

  inline void data_length(const config_t::data_length_t::enum_t val) {  config.rmw( val );}
  inline void data_length_two_bytes() { config.rmw( config_t::data_length_t::two_bytes );}
  inline void data_length_three_bytes() { config.rmw( config_t::data_length_t::three_bytes );}
  inline void data_length_four_bytes() { config.rmw( config_t::data_length_t::four_bytes );}
  inline auto data_length() const { return config.rd<config_t::data_length_t>();}

  inline void i2s_clock_polarity(const config_t::i2s_clock_polarity_t::enum_t val) {  config.rmw( val );}
  inline void i2s_clock_polarity_low() { config.rmw( config_t::i2s_clock_polarity_t::low );}
  inline void i2s_clock_polarity_high() { config.rmw( config_t::i2s_clock_polarity_t::high );}
  inline auto i2s_clock_polarity() const { return config.rd<config_t::i2s_clock_polarity_t>();}

  inline void standard(const config_t::standard_t::enum_t val) {  config.rmw( val );}
  inline void standard_philips() { config.rmw( config_t::standard_t::philips );}
  inline void standard_left_justified() { config.rmw( config_t::standard_t::left_justified );}
  inline void standard_right_justified() { config.rmw( config_t::standard_t::right_justified );}
  inline void standard_pcm() { config.rmw( config_t::standard_t::pcm );}
  inline auto standard() const { return config.rd<config_t::standard_t>();}

  inline void pcm_frame_synchronization(const config_t::pcm_frame_synchronization_t::enum_t val) {  config.rmw( val );}
  inline void pcm_frame_synchronization_short() { config.rmw( config_t::pcm_frame_synchronization_t::short_frane );}
  inline void pcm_frame_synchronization_long() { config.rmw( config_t::pcm_frame_synchronization_t::long_frame );}
  inline auto pcm_frame_synchronization() const { return config.rd<config_t::pcm_frame_synchronization_t>();}

  inline void congiguration_mode(const config_t::congiguration_mode_t::enum_t val) {  config.rmw( val );}
  inline void congiguration_mode_slave_transmit() { config.rmw( config_t::congiguration_mode_t::slave_transmit );}
  inline void congiguration_mode_slave_receive() { config.rmw( config_t::congiguration_mode_t::slave_receive );}
  inline void congiguration_mode_master_transmit() { config.rmw( config_t::congiguration_mode_t::master_transmit );}
  inline void congiguration_mode_master_receive() { config.rmw( config_t::congiguration_mode_t::master_receive );}
  inline auto congiguration_mode() const { return config.rd<config_t::congiguration_mode_t>();}

  inline void i2s_state(const config_t::i2s_state_t::enum_t val) {  config.rmw( val );}
  inline void i2s_enable() { config.rmw( config_t::i2s_state_t::enable );}
  inline void i2s_disable() { config.rmw( config_t::i2s_state_t::disable );}
  inline auto i2s_state() const { return config.rd<config_t::i2s_state_t>();}

  inline void mode(const config_t::mode_t::enum_t val) {  config.rmw( val );}
  inline void mode_spi() { config.rmw( config_t::mode_t::spi );}
  inline void mode_i2s() { config.rmw( config_t::mode_t::i2s );}
  inline auto mode() const { return config.rd<config_t::mode_t>();}


  struct prescaler_t : public read_write_32_t
  {
    struct linear_prescaler_t    { enum enum_t { offset=0, mask=0xff }; } ;
    struct odd_t          { enum enum_t { offset=8, mask=1, mul_2=0, mul_2_plus_1 }; } ;
    struct master_clock_output_t { enum enum_t { offset=9, mask=1, disable=0, enable }; } ;
  };

  inline void linear_prescaler(const uint8_t val) {  prescaler.rmw( (prescaler_t::linear_prescaler_t::enum_t)val );}
  inline auto linear_prescaler() const { return (uint8_t)prescaler.rd<prescaler_t::linear_prescaler_t>();}

  inline void odd(const prescaler_t::odd_t::enum_t val) {  prescaler.rmw( val );}
  inline void odd_mul_2() { prescaler.rmw( prescaler_t::odd_t::mul_2 );}
  inline void odd_mul_2_plus_1() { prescaler.rmw( prescaler_t::odd_t::mul_2_plus_1 );}
  inline auto odd() const { return prescaler.rd<prescaler_t::odd_t>();}

  inline void master_clock_output(const prescaler_t::master_clock_output_t::enum_t val) {  prescaler.rmw( val );}
  inline void master_clock_output_disable() { prescaler.rmw( prescaler_t::master_clock_output_t::disable );}
  inline void master_clock_output_enable() { prescaler.rmw( prescaler_t::master_clock_output_t::enable );}
  inline auto master_clock_output() const { return prescaler.rd<prescaler_t::master_clock_output_t>();}

  config_t       config ; //I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  prescaler_t    prescaler ; //I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */

  inline void clock_enable()
     {
        switch((uint32_t)this)
          {
             case spi1_addr : rcc.spi1_enable(); break ;
             case spi2_addr : rcc.spi2_enable(); break ;
             case spi3_addr : rcc.spi3_enable(); break ;
             default: { std::__throw_invalid_argument("invalid SPI object") ; }
          }
     }

  inline void clock_disable()
     {
        switch((uint32_t)this)
          {
            case spi1_addr : rcc.spi1_disable(); break ;
            case spi2_addr : rcc.spi2_disable(); break ;
            case spi3_addr : rcc.spi3_disable(); break ;
            default: { std::__throw_invalid_argument("invalid SPI object") ; }
          }
     }

  inline void reset()
    {
        switch((uint32_t)this)
          {
             case spi1_addr : rcc.spi1_reset(); break ;
             case spi2_addr : rcc.spi2_reset(); break ;
             case spi3_addr : rcc.spi3_reset(); break ;
             default: {  std::__throw_invalid_argument("invalid SPI object") ; }
          }
    };

};



struct spi1_t : public spi_t
  {
    inline void clock_enable() {  rcc.spi1_enable() ; }
    inline void clock_disable() {  rcc.spi1_disable() ; }
    inline void reset() {  rcc.spi1_reset() ; }
    inline static spi1_t& ref() { return *((spi1_t *) spi1_addr) ; }
  };

struct spi2_t : public spi_t
  {
    inline void clock_enable() {  rcc.spi2_enable() ; }
    inline void clock_disable(){  rcc.spi2_disable(); }
    inline void reset()  {  rcc.spi2_reset() ; }
    inline static spi2_t& ref() { return *((spi2_t *) spi2_addr) ; }
  };

struct spi3_t : public spi_t
  {
    inline void clock_enable() {  rcc.spi3_enable() ; }
    inline void clock_disable(){  rcc.spi3_disable(); }
    inline void reset()  {  rcc.spi3_reset() ; }
    inline static spi3_t& ref() { return *((spi3_t *) spi3_addr) ; }
  };


static spi1_t& spi1 = *((spi1_t *) spi1_addr);
static spi2_t& spi2 = *((spi2_t *) spi2_addr);
static spi3_t& spi3 = *((spi3_t *) spi3_addr);

struct i2s1_t : public spi1_t, public i2s_t
  {
    inline static i2s1_t& ref() { return *((i2s1_t *) spi1_addr) ; }
  };

struct i2s2_t : public spi2_t, public i2s_t
  {
    inline static i2s2_t& ref() { return *((i2s2_t *) spi2_addr) ; }
  };

struct i2s3_t : public spi3_t, public i2s_t
  {
    inline static i2s3_t& ref() { return *((i2s3_t *) spi3_addr) ; }
  };

static i2s1_t& i2s1 = *((i2s1_t *) spi1_addr);
static i2s2_t& i2s2 = *((i2s2_t *) spi2_addr);
static i2s3_t& i2s3 = *((i2s3_t *) spi3_addr);

};

using namespace stm32f4 ;

#endif /* __SPI++_H__ */
