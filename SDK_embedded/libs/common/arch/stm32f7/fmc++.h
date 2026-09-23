/*
 * rcc++.h
 *
 *  Created on: 30 окт. 2017 г.
 *      Author: klen
 */

#ifndef __FMC++_H__
#define __FMC++_H__

#include "types++.h"


namespace stm32f7
{

struct fmc_t
{
  enum chip_t{ chip1=0, chip2, chip3, chip4 };

  struct bank1_control_t : public read_write_32_t
	{

	   struct state_t                     { enum enum_t{ offset=0,  mask=1, disable=0, enable };};
	   struct multiplexing_t              { enum enum_t{ offset=1,  mask=1, disable=0, enable };};
	   struct memory_type_t               { enum enum_t{ offset=2,  mask=0b11, sram=0, psram_cram, nor_or_onenand };};
	   struct data_bus_width_t            { enum enum_t{ offset=4,  mask=0b11, bit8=0, bit16, bit32 };};
	   struct nor_flash_access_t          { enum enum_t{ offset=6,  mask=1, disable=0, enable };};
	   struct burst_t                     { enum enum_t{ offset=8,  mask=1, disable=0, enable };};
	   struct nwait_signal_polarity_t     { enum enum_t{ offset=9,  mask=1, low=0, high };};
	   struct wrapped_burst_mode_t        { enum enum_t{ offset=10, mask=1, disable=0, enable };};
	   struct nwait_timing_configuration_t{ enum enum_t{ offset=11, mask=1, active_one_data_cycle=0, active_during_wait_state };};
	   struct write_t                     { enum enum_t{ offset=12, mask=1, disable=0, enable };};
	   struct wait_t                      { enum enum_t{ offset=13, mask=1, disable=0, enable };};
	   struct extended_mode_t             { enum enum_t{ offset=14, mask=1, disable=0, enable };};
	   struct asynchronous_wait_t         { enum enum_t{ offset=15, mask=1, disable=0, enable };};
	   struct cram_page_size_t            { enum enum_t{ offset=16, mask=0b111, no_burst_split=0, bytes128, bytes256, bytes512, bytes1024 };};
	   struct write_burst_t               { enum enum_t{ offset=19, mask=1, disable=0, enable };};
	   struct continuous_clock_t          { enum enum_t{ offset=20, mask=1, disable=0, enable };};
	   struct write_fifo_t                { enum enum_t{ offset=20, mask=1, enable=0, disable };};
	};

  inline void bank1( const chip_t chip, const bank1_control_t::state_t::enum_t val){ bank1_control[chip].rmw(val); }
  inline void bank1_enable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::state_t::enable) ; }
  inline void bank1_disable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::state_t::disable) ; }
  inline auto bank1( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::state_t>() ; }

  inline void bank1_multiplexing( const chip_t chip, const bank1_control_t::multiplexing_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_multiplexing_enable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::multiplexing_t::enable) ; }
  inline void bank1_multiplexing_disable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::multiplexing_t::disable) ; }
  inline auto bank1_multiplexing( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::multiplexing_t>() ; }

  inline void bank1_memory_type( const chip_t chip, const bank1_control_t::memory_type_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_memory_type_sram( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::memory_type_t::sram) ; }
  inline void bank1_memory_type_psram_cram( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::memory_type_t::psram_cram) ; }
  inline void bank1_memory_type_nor_or_onenand( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::memory_type_t::nor_or_onenand) ; }
  inline auto bank1_memory_type( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::memory_type_t>() ; }

  inline void bank1_data_bus_width( const chip_t chip, const bank1_control_t::data_bus_width_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_data_bus_width_bit8( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::data_bus_width_t::bit8) ; }
  inline void bank1_data_bus_width_bit16( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::data_bus_width_t::bit16) ; }
  inline void bank1_data_bus_width_bit32( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::data_bus_width_t::bit32) ; }
  inline auto bank1_data_bus_width( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::data_bus_width_t>() ; }

  inline void bank1_nor_flash_access( const chip_t chip, const bank1_control_t::nor_flash_access_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_nor_flash_access_enable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::nor_flash_access_t::enable) ; }
  inline void bank1_nor_flash_access_disable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::nor_flash_access_t::disable) ; }
  inline auto bank1_nor_flash_access( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::nor_flash_access_t>() ; }

  inline void bank1_burst( const chip_t chip, const bank1_control_t::burst_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_burst_enable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::burst_t::enable) ; }
  inline void bank1_burst_disable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::burst_t::disable) ; }
  inline auto bank1_burst( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::burst_t>() ; }

  inline void bank1_nwait_signal_polarity( const chip_t chip, const bank1_control_t::nwait_signal_polarity_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_nwait_signal_polarity_high( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::nwait_signal_polarity_t::high) ; }
  inline void bank1_nwait_signal_polarity_low( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::nwait_signal_polarity_t::low) ; }
  inline auto bank1_nwait_signal_polarity( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::nwait_signal_polarity_t>() ; }

  inline void bank1_wrapped_burst_mode( const chip_t chip, const bank1_control_t::wrapped_burst_mode_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_wrapped_burst_mode_enable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::wrapped_burst_mode_t::enable) ; }
  inline void bank1_wrapped_burst_mode_disable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::wrapped_burst_mode_t::disable) ; }
  inline auto bank1_wrapped_burst_mode( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::wrapped_burst_mode_t>() ; }

  inline void bank1_nwait_timing_configuration( const chip_t chip, const bank1_control_t::nwait_timing_configuration_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_nwait_timing_configuration_active_one_data_cycle( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::nwait_timing_configuration_t::active_one_data_cycle) ; }
  inline void bank1_nwait_timing_configuration_active_during_wait_state( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::nwait_timing_configuration_t::active_during_wait_state) ; }
  inline auto bank1_nwait_timing_configuration( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::nwait_timing_configuration_t>() ; }

  inline void bank1_write( const chip_t chip, const bank1_control_t::write_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_write_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::write_t::disable) ; }
  inline void bank1_write_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::write_t::enable) ; }
  inline auto bank1_write( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::write_t>() ; }

  inline void bank1_wait( const chip_t chip, const bank1_control_t::wait_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_wait_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::wait_t::disable) ; }
  inline void bank1_wait_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::wait_t::enable) ; }
  inline auto bank1_wait( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::wait_t>() ; }

  inline void bank1_extended_mode( const chip_t chip, const bank1_control_t::extended_mode_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_extended_mode_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::extended_mode_t::disable) ; }
  inline void bank1_extended_mode_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::extended_mode_t::enable) ; }
  inline auto bank1_extended_mode( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::extended_mode_t>() ; }

  inline void bank1_asynchronous_wait( const chip_t chip, const bank1_control_t::asynchronous_wait_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_asynchronous_wait_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::asynchronous_wait_t::disable) ; }
  inline void bank1_asynchronous_wait_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::asynchronous_wait_t::enable) ; }
  inline auto bank1_asynchronous_wait( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::asynchronous_wait_t>() ; }

  inline void bank1_cram_page_size( const chip_t chip, const bank1_control_t::cram_page_size_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_cram_page_size_128bytes( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::cram_page_size_t::bytes128) ; }
  inline void bank1_cram_page_size_256bytes( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::cram_page_size_t::bytes256) ; }
  inline void bank1_cram_page_size_512bytes( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::cram_page_size_t::bytes512) ; }
  inline void bank1_cram_page_size_1024bytes( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::cram_page_size_t::bytes1024) ; }
  inline auto bank1_cram_page_siz( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::cram_page_size_t>() ; }

  inline void bank1_write_burst( const chip_t chip, const bank1_control_t::write_burst_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_write_burst_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::write_burst_t::disable) ; }
  inline void bank1_write_burst_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::write_burst_t::enable) ; }
  inline auto bank1_write_burst( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::write_burst_t>() ; }

  inline void bank1_continuous_clock( const chip_t chip, const bank1_control_t::continuous_clock_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_continuous_clock_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::continuous_clock_t::disable) ; }
  inline void bank1_continuous_clock_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::continuous_clock_t::enable) ; }
  inline auto bank1_continuous_clock( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::continuous_clock_t>() ; }

  inline void bank1_write_fifo( const chip_t chip, const bank1_control_t::write_fifo_t::enum_t val){ bank1_control[chip].rmw(val) ; }
  inline void bank1_write_fifo_disable( const chip_t chip){ bank1_control[chip].rmw(bank1_control_t::write_fifo_t::disable) ; }
  inline void bank1_write_fifo_enable( const chip_t chip) { bank1_control[chip].rmw(bank1_control_t::write_fifo_t::enable) ; }
  inline auto bank1_write_fifo( const chip_t chip) const { return bank1_control[chip].rd<bank1_control_t::write_fifo_t>() ; }

  struct bank1_timing_t : public read_write_32_t
	{
	  struct address_setup_phase_duration_t  { enum enum_t{ offset=0,  mask=0b1111 };};
	  struct address_hold_phase_duration_t   { enum enum_t{ offset=4,  mask=0b1111 };};
	  struct data_phase_duration_t           { enum enum_t{ offset=8,  mask=0xff   };};
	  struct bus_turnaround_phase_duration_t { enum enum_t{ offset=16, mask=0b1111 };};
	  struct clock_divide_ratio_t            { enum enum_t{ offset=20, mask=0b1111 };};
	  struct data_latency_ratio_t            { enum enum_t{ offset=24, mask=0b1111 };};
	  struct access_t                        { enum enum_t{ offset=28, mask=0b11, mode_a=0, mode_b, mode_c, mode_d };};
	};

  inline void bank1_address_setup_phase_duration( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::address_setup_phase_duration_t::enum_t)val) ; }
  inline auto bank1_address_setup_phase_duration( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::address_setup_phase_duration_t>() ; }

  inline void bank1_address_hold_phase_duration( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::address_hold_phase_duration_t::enum_t)val) ; }
  inline auto bank1_address_hold_phase_duration( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::address_hold_phase_duration_t>() ; }

  inline void bank1_data_phase_duration( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::data_phase_duration_t::enum_t)val) ; }
  inline auto bank1_data_phase_duration( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::data_phase_duration_t>() ; }

  inline void bank1_bus_turnaround_phase_duration( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::bus_turnaround_phase_duration_t::enum_t)val) ; }
  inline auto bank1_bus_turnaround_phase_duration( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::bus_turnaround_phase_duration_t>() ; }

  inline void bank1_clock_divide_ratio( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::clock_divide_ratio_t::enum_t)val) ; }
  inline auto bank1_clock_divide_ratio( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::clock_divide_ratio_t>() ; }

  inline void bank1_data_latency_ratio( const chip_t chip, const uint8_t val){ bank1_timing[chip].rmw((bank1_timing_t::data_latency_ratio_t::enum_t)val) ; }
  inline auto bank1_data_latency_ratio( const chip_t chip) const { return (uint8_t)bank1_timing[chip].rd<bank1_timing_t::data_latency_ratio_t>() ; }

  inline void bank1_bank1_access( const chip_t chip, const bank1_timing_t::access_t::enum_t val){ bank1_timing[chip].rmw(val) ; }
  inline void bank1_access_a( const chip_t chip){ bank1_timing[chip].rmw(bank1_timing_t::access_t::mode_a); }
  inline void bank1_access_b( const chip_t chip){ bank1_timing[chip].rmw(bank1_timing_t::access_t::mode_b); }
  inline void bank1_access_c( const chip_t chip){ bank1_timing[chip].rmw(bank1_timing_t::access_t::mode_c); }
  inline void bank1_access_d( const chip_t chip){ bank1_timing[chip].rmw(bank1_timing_t::access_t::mode_d); }
  inline auto bank1_access( const chip_t chip) const { return bank1_timing[chip].rd<bank1_timing_t::access_t>() ; }

  struct bank1_write_timing_t : public read_write_32_t
	{
	  struct address_setup_phase_duration_t     { enum enum_t{ offset=0,  mask=0b1111 };};
	  struct address_hold_phase_duration_t      { enum enum_t{ offset=4,  mask=0b1111 };};
	  struct data_phase_duration_t              { enum enum_t{ offset=8,  mask=0xff   };};
	  struct bus_turnaround_phase_duration_t    { enum enum_t{ offset=16, mask=0b1111 };};
	  struct access_t                           { enum enum_t{ offset=28, mask=0b11, mode_a=0, mode_b, mode_c, mode_d };};

	  inline static uint32_t map_addr(const chip_t val) { switch ( val ) { case 0 : return 0; case 1 : return 1; case 2: return 5; case 3: return 6; } return -1; };
	};

  inline void bank1_write_address_setup_phase_duration( const chip_t chip, const uint8_t val){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(( bank1_write_timing_t::address_setup_phase_duration_t::enum_t)val) ; }
  inline auto bank1_write_address_setup_phase_duration( const chip_t chip) const { return (uint8_t)bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rd<bank1_write_timing_t::address_setup_phase_duration_t>() ; }

  inline void bank1_write_address_hold_phase_duration( const chip_t chip, const uint8_t val){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(( bank1_write_timing_t::address_hold_phase_duration_t::enum_t)val) ; }
  inline auto bank1_write_address_hold_phase_duration( const chip_t chip) const { return (uint8_t)bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rd<bank1_write_timing_t::address_hold_phase_duration_t>() ; }

  inline void bank1_write_data_phase_duration( const chip_t chip, const uint8_t val){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(( bank1_write_timing_t::data_phase_duration_t::enum_t)val) ; }
  inline auto bank1_write_data_phase_duration( const chip_t chip) const { return (uint8_t)bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rd<bank1_write_timing_t::data_phase_duration_t>() ; }

  inline void bank1_write_bus_turnaround_phase_duration( const chip_t chip, const uint8_t val){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(( bank1_write_timing_t::bus_turnaround_phase_duration_t::enum_t)val) ; }
  inline auto bank1_write_bus_turnaround_phase_duration( const chip_t chip) const { return (uint8_t)bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rd<bank1_write_timing_t::bus_turnaround_phase_duration_t>() ; }

  inline void bank1_write_access( const chip_t chip, const bank1_write_timing_t::access_t::enum_t val){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(val) ; }
  inline void bank1_write_access_a( const chip_t chip){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(bank1_write_timing_t::access_t::mode_a); }
  inline void bank1_write_access_b( const chip_t chip){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(bank1_write_timing_t::access_t::mode_b); }
  inline void bank1_write_access_c( const chip_t chip){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(bank1_write_timing_t::access_t::mode_c); }
  inline void bank1_write_access_d( const chip_t chip){ bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rmw(bank1_write_timing_t::access_t::mode_d); }
  inline auto bank1_write_access( const chip_t chip) const { return bank1_write_timing[bank1_write_timing_t::map_addr(chip)].rd<bank1_write_timing_t::access_t>() ; }

  struct bank3_control_t : public read_write_32_t
	{
       // TODO
	};

  struct bank3_status_and_interrupt_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank3_common_memory_space_timing_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank3_attribute_memory_space_timing_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank3_ecc_result_t : public read_write_32_t
	{
	   // TODO
	};


  struct bank5_6_control_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank5_6_timing_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank5_6_common_mode_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank5_6_refresh_timer_t : public read_write_32_t
	{
	   // TODO
	};

  struct bank5_6_status_t : public read_write_32_t
	{
	   // TODO
	};

  bank1_control_t   bank1_control[4];  //!< NOR/PSRAM chip-select control register(BCR) and
  bank1_timing_t    bank1_timing[4] ; //   chip-select timing register(BTR), Address offset: 0x00-1C

  uint32_t reserve0[24] ;

  bank3_control_t  bank3_control; // PCR;       /*!< NAND Flash control register,                       Address offset: 0x80 */
  bank3_status_and_interrupt_t bank3_status_and_interrupt; //  SR;        /*!< NAND Flash FIFO status and interrupt register,     Address offset: 0x84 */
  bank3_common_memory_space_timing_t bank3_common_memory_space_timing; //  PMEM;      /*!< NAND Flash Common memory space timing register,    Address offset: 0x88 */
  bank3_attribute_memory_space_timing_t bank3_attribute_memory_space_timing; //  PATT;      /*!< NAND Flash Attribute memory space timing register, Address offset: 0x8C */
  uint32_t reserve1;  /*!< Reserved, 0x90                                                          */
  bank3_ecc_result_t bank3_ecc_result;//  ECCR;      /*!< NAND Flash ECC result registers,                   Address offset: 0x94 */

  uint32_t reserve2[27] ;

  bank1_write_timing_t     bank1_write_timing[7];  /*!< NOR/PSRAM write timing registers, Address offset: 0x104-0x11C */
  /*bank1_write_timing_t     bank1_write_timing;
  uint32_t reserve3[3] ;
  bank1_write_timing_t     bank1_write_timing;
  bank1_write_timing_t     bank1_write_timing;*/

  uint32_t reserve4[8] ;

  bank5_6_control_t bank5_6_control[2];//  SDCR[2];   /*!< SDRAM Control registers ,      Address offset: 0x140-0x144  */
  bank5_6_timing_t bank5_6_timing[2];//  SDTR[2];   /*!< SDRAM Timing registers ,       Address offset: 0x148-0x14C  */
  bank5_6_common_mode_t bank5_6_common_mode;//  SDCMR;     /*!< SDRAM Command Mode register,    Address offset: 0x150  */
  bank5_6_refresh_timer_t bank5_6_refresh_timer;//  SDRTR;     /*!< SDRAM Refresh Timer register,   Address offset: 0x154  */
  bank5_6_status_t bank5_6_status;//  SDSR;      /*!< SDRAM Status register,          Address offset: 0x158  */
};

static fmc_t& fmc   = *((fmc_t*) fmc_addr);

}  // stm32f7

using namespace stm32f7 ;

#endif /* __FMC++_H__ */
