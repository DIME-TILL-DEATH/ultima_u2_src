/*
 * sai++.h
 *
 *  Created on: 12 янв. 2018 г.
 *      Author: klen
 */

#ifndef __SAI++_H__
#define __SAI++_H__

#include "types++.h"

namespace stm32f7
{

struct sai_block_t
{
  struct configuration_1_t : public read_write_32_t
  {
    struct mode_t { enum enum_t { offset=0, mask=0b11, master_tx=0, master_rx, slave_tx, slave_rx }; } ;
    struct protocol_t { enum enum_t { offset=2, mask=0b11, free=0 , spdif, ac97 }; } ;
    struct data_size_t { enum enum_t { offset=5, mask=0b111, bits8=2, bits10, bits16, bits20, bits24, bits32  }; } ;
    struct least_significant_bit_first_t { enum enum_t { offset=8, mask=1, msb=0 , lsb }; } ;
    struct clock_strobing_edge_t { enum enum_t { offset=9, mask=1, rise=0 , fall }; } ;
    struct synchronization_t { enum enum_t { offset=10, mask=0b11, async=0 , internal_audio, external_sai }; } ;
    struct fone_t { enum enum_t { offset=12, mask=1, stereo=0 , mono }; } ;
    struct output_drive_t { enum enum_t { offset=13, mask=1, when_sai_enable=0 , immediately }; } ;
    struct state_t { enum enum_t { offset=16, mask=1, disable=0 , enable }; } ;
    struct dma_t { enum enum_t { offset=17, mask=1, disable=0 , enable }; } ;
    struct master_clock_divider_state_t { enum enum_t { offset=19, mask=1, enable=0 , disable }; } ;
    struct master_clock_divider_t { enum enum_t { offset=20, mask=0b1111, div1=0, div2, div4, div6, div8, div10, div12, div14, div16, div18, div20, div22, div24, div26, div28, div30  }; } ;

  } ;

  inline void mode(const configuration_1_t::mode_t::enum_t val) {  configuration_1.rmw( val );}
  inline void mode_master_tx() { configuration_1.rmw( configuration_1_t::mode_t::master_tx );}
  inline void mode_master_rx() { configuration_1.rmw( configuration_1_t::mode_t::master_rx );}
  inline void mode_slave_tx() { configuration_1.rmw( configuration_1_t::mode_t::slave_tx );}
  inline void mode_slave_rx() { configuration_1.rmw( configuration_1_t::mode_t::slave_rx );}
  inline auto mode() const { return configuration_1.rd<configuration_1_t::mode_t>();}

  inline void protocol(const configuration_1_t::protocol_t::enum_t val) {  configuration_1.rmw( val );}
  inline void protocol_free() { configuration_1.rmw( configuration_1_t::protocol_t::free );}
  inline void protocol_spdif() { configuration_1.rmw( configuration_1_t::protocol_t::spdif );}
  inline void protocol_ac97() { configuration_1.rmw( configuration_1_t::protocol_t::ac97 );}
  inline auto protocol() const { return configuration_1.rd<configuration_1_t::protocol_t>();}

  inline void data_size(const configuration_1_t::data_size_t::enum_t val) {  configuration_1.rmw( val );}
  inline void data_size_bits8() { configuration_1.rmw( configuration_1_t::data_size_t::bits8 );}
  inline void data_size_bits10() { configuration_1.rmw( configuration_1_t::data_size_t::bits10 );}
  inline void data_size_bits16() { configuration_1.rmw( configuration_1_t::data_size_t::bits16 );}
  inline void data_size_bits20() { configuration_1.rmw( configuration_1_t::data_size_t::bits20 );}
  inline void data_size_bits24() { configuration_1.rmw( configuration_1_t::data_size_t::bits24 );}
  inline void data_size_bits32() { configuration_1.rmw( configuration_1_t::data_size_t::bits32 );}
  inline auto data_size() const { return configuration_1.rd<configuration_1_t::data_size_t>();}

  inline void least_significant_bit_first(const configuration_1_t::least_significant_bit_first_t::enum_t val) {  configuration_1.rmw( val );}
  inline void least_significant_bit_first_msb() { configuration_1.rmw( configuration_1_t::least_significant_bit_first_t::msb );}
  inline void least_significant_bit_first_lsb() { configuration_1.rmw( configuration_1_t::least_significant_bit_first_t::lsb );}
  inline auto least_significant_bit_first() const { return configuration_1.rd<configuration_1_t::least_significant_bit_first_t>();}

  inline void clock_strobing_edge(const configuration_1_t::clock_strobing_edge_t::enum_t val) {  configuration_1.rmw( val );}
  inline void clock_strobing_edge_rise() { configuration_1.rmw( configuration_1_t::clock_strobing_edge_t::rise );}
  inline void clock_strobing_edge_fall() { configuration_1.rmw( configuration_1_t::clock_strobing_edge_t::fall );}
  inline auto clock_strobing_edge() const { return configuration_1.rd<configuration_1_t::clock_strobing_edge_t>();}

  inline void synchronization(const configuration_1_t::synchronization_t::enum_t val) {  configuration_1.rmw( val );}
  inline void synchronization_async() { configuration_1.rmw( configuration_1_t::synchronization_t::async );}
  inline void synchronization_internal_audio() { configuration_1.rmw( configuration_1_t::synchronization_t::internal_audio );}
  inline void synchronization_external_sai() { configuration_1.rmw( configuration_1_t::synchronization_t::external_sai );}
  inline auto synchronization() const { return configuration_1.rd<configuration_1_t::synchronization_t>();}

  inline void fone(const configuration_1_t::fone_t::enum_t val) {  configuration_1.rmw( val );}
  inline void fone_stereo() { configuration_1.rmw( configuration_1_t::fone_t::stereo );}
  inline void fone_mono()   { configuration_1.rmw( configuration_1_t::fone_t::mono );}
  inline auto fone() const  { return configuration_1.rd<configuration_1_t::fone_t>();}

  inline void output_drive(const configuration_1_t::output_drive_t::enum_t val) {  configuration_1.rmw( val );}
  inline void output_drive_when_sai_enable() { configuration_1.rmw( configuration_1_t::output_drive_t::when_sai_enable );}
  inline void output_drive_immediately()   { configuration_1.rmw( configuration_1_t::output_drive_t::immediately );}
  inline auto output_drive() const  { return configuration_1.rd<configuration_1_t::output_drive_t>();}

  inline void state(const configuration_1_t::state_t::enum_t val) {  configuration_1.rmw( val );}
  inline void state_disable() { configuration_1.rmw( configuration_1_t::state_t::disable );}
  inline void state_enable()   { configuration_1.rmw( configuration_1_t::state_t::enable );}
  inline auto state() const  { return configuration_1.rd<configuration_1_t::state_t>();}

  inline void dma(const configuration_1_t::dma_t::enum_t val) {  configuration_1.rmw( val );}
  inline void dma_disable() { configuration_1.rmw( configuration_1_t::dma_t::disable );}
  inline void dma_enable()   { configuration_1.rmw( configuration_1_t::dma_t::enable );}
  inline auto dma() const  { return configuration_1.rd<configuration_1_t::dma_t>();}

  inline void master_clock_divider_state(const configuration_1_t::master_clock_divider_state_t::enum_t val) {  configuration_1.rmw( val );}
  inline void master_clock_divider_state_disable() { configuration_1.rmw( configuration_1_t::master_clock_divider_state_t::disable );}
  inline void master_clock_divider_state_enable()   { configuration_1.rmw( configuration_1_t::master_clock_divider_state_t::enable );}
  inline auto master_clock_divider_state() const  { return configuration_1.rd<configuration_1_t::master_clock_divider_state_t>();}

  inline void master_clock_divider(const configuration_1_t::master_clock_divider_t::enum_t val) {  configuration_1.rmw( val );}
  inline void master_clock_divider_div1()  { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div1 );}
  inline void master_clock_divider_div2()  { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div2 );}
  inline void master_clock_divider_div4()  { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div4 );}
  inline void master_clock_divider_div6()  { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div6 );}
  inline void master_clock_divider_div8()  { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div8 );}
  inline void master_clock_divider_div10() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div10 );}
  inline void master_clock_divider_div12() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div12 );}
  inline void master_clock_divider_div14() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div14 );}
  inline void master_clock_divider_div16() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div16 );}
  inline void master_clock_divider_div18() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div18 );}
  inline void master_clock_divider_div20() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div20 );}
  inline void master_clock_divider_div22() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div22 );}
  inline void master_clock_divider_div24() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div24 );}
  inline void master_clock_divider_div26() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div26 );}
  inline void master_clock_divider_div28() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div28 );}
  inline void master_clock_divider_div30() { configuration_1.rmw( configuration_1_t::master_clock_divider_t::div30 );}
  inline auto master_clock_divider() const  { return configuration_1.rd<configuration_1_t::master_clock_divider_t>();}


  struct configuration_2_t : public read_write_32_t
  {
    struct fifo_threshold_t { enum enum_t { offset=0, mask=0b111, threshold_1div4=0, threshold_1div2, threshold_3div4, threshold_full }; } ;
    struct fifo_flush_t { enum enum_t { offset=3, mask=0b1, perform=1 }; } ;
    struct tristate_management_t { enum enum_t { offset=4, mask=0b1, force_zero=0, hi_z }; } ;
    struct mute_t { enum enum_t { offset=5, mask=0b1, disable=0, enable }; } ;
    struct mute_val_t { enum enum_t { offset=6, mask=0b1, zero=0, last }; } ;
    struct mute_counter_t { enum enum_t { offset=7, mask=0b111111 }; } ;
    struct compliment_bit_t { enum enum_t { offset=13, mask=0b1, to_1s=0, to_2s }; } ;
    struct companding_mode_t { enum enum_t { offset=14, mask=0b11, no=0, mu_law=2, a_lav }; } ;
  } ;

  inline void fifo_threshold(const configuration_2_t::fifo_threshold_t::enum_t val) {  configuration_2.rmw( val );}
  inline void fifo_threshold_1div4() { configuration_2.rmw( configuration_2_t::fifo_threshold_t::threshold_1div4 );}
  inline void fifo_threshold_1div2() { configuration_2.rmw( configuration_2_t::fifo_threshold_t::threshold_1div2 );}
  inline void fifo_threshold_3div4() { configuration_2.rmw( configuration_2_t::fifo_threshold_t::threshold_3div4 );}
  inline void fifo_threshold_full() { configuration_2.rmw( configuration_2_t::fifo_threshold_t::threshold_full );}
  inline auto fifo_threshold() const  { return configuration_2.rd<configuration_2_t::fifo_threshold_t>();}

  inline void fifo_flush() { configuration_2.rmw( configuration_2_t::fifo_flush_t::perform ); }

  inline void tristate_management(const configuration_2_t::tristate_management_t::enum_t val) {  configuration_2.rmw( val );}
  inline void tristate_management_force_zero() { configuration_2.rmw( configuration_2_t::tristate_management_t::force_zero );}
  inline void tristate_management_hi_z() { configuration_2.rmw( configuration_2_t::tristate_management_t::hi_z );}
  inline auto tristate_management() const  { return configuration_2.rd<configuration_2_t::tristate_management_t>();}

  inline void mute(const configuration_2_t::mute_t::enum_t val) {  configuration_2.rmw( val );}
  inline void mute_disable() { configuration_2.rmw( configuration_2_t::mute_t::disable );}
  inline void mute_enable() { configuration_2.rmw( configuration_2_t::mute_t::enable );}
  inline auto mute() const  { return configuration_2.rd<configuration_2_t::mute_t>();}

  inline void mute_val(const configuration_2_t::mute_val_t::enum_t val) {  configuration_2.rmw( val );}
  inline void mute_val_zero() { configuration_2.rmw( configuration_2_t::mute_val_t::zero );}
  inline void mute_val_last() { configuration_2.rmw( configuration_2_t::mute_val_t::last );}
  inline auto mute_val() const  { return configuration_2.rd<configuration_2_t::mute_val_t>();}

  inline  void mute_counter(const uint8_t val){  configuration_2.rmw( (configuration_2_t::mute_counter_t::enum_t)val) ;}
  inline  auto mute_counter() const {  return (uint8_t) configuration_2.rd<configuration_2_t::mute_counter_t> ();}

  inline void compliment_bit(const configuration_2_t::compliment_bit_t::enum_t val) {  configuration_2.rmw( val );}
  inline void compliment_bit_to_1s() { configuration_2.rmw( configuration_2_t::compliment_bit_t::to_1s );}
  inline void compliment_bit_to_2s() { configuration_2.rmw( configuration_2_t::compliment_bit_t::to_2s );}
  inline auto compliment_bit() const  { return configuration_2.rd<configuration_2_t::compliment_bit_t>();}

  inline void companding_mode(const configuration_2_t::companding_mode_t::enum_t val) {  configuration_2.rmw( val );}
  inline void companding_mode_no() { configuration_2.rmw( configuration_2_t::companding_mode_t::no );}
  inline void companding_mode_mu_law() { configuration_2.rmw( configuration_2_t::companding_mode_t::mu_law );}
  inline void companding_mode_a_lav() { configuration_2.rmw( configuration_2_t::companding_mode_t::a_lav );}
  inline auto companding_mode() const  { return configuration_2.rd<configuration_2_t::companding_mode_t>();}

  struct frame_configuration_t : public read_write_32_t
  {
    struct length_t { enum enum_t { offset=0, mask=0xff }; } ;
    struct synchronization_active_level_length_t { enum enum_t { offset=8, mask=0b111111,  }; } ;
    struct synchronization_definition_t { enum enum_t { offset=16, mask=0b1, start=0, start_channel_side_id }; } ;
    struct synchronization_polarity_t { enum enum_t { offset=17, mask=0b1, low=0, high }; } ;
    struct synchronization_offset_t { enum enum_t { offset=18, mask=0b1, first_bit=0, before_first_bit }; } ;
  } ;

  inline void length(const uint8_t val) {  frame_configuration.rmw( (frame_configuration_t::length_t::enum_t )val );}
  inline auto length() const  { return (uint8_t)frame_configuration.rd<frame_configuration_t::length_t>();}

  inline void synchronization_active_level_length( const uint8_t val) {  frame_configuration.rmw( (frame_configuration_t::synchronization_active_level_length_t::enum_t)val );}
  inline auto synchronization_active_level_length() const  { return (uint8_t)frame_configuration.rd<frame_configuration_t::synchronization_active_level_length_t>();}

  inline void synchronization_definition(const frame_configuration_t::synchronization_definition_t::enum_t val) {  frame_configuration.rmw( val );}
  inline void synchronization_definition_start() { frame_configuration.rmw( frame_configuration_t::synchronization_definition_t::start );}
  inline void synchronization_definition_start_channel_side_id() { frame_configuration.rmw( frame_configuration_t::synchronization_definition_t::start_channel_side_id );}
  inline auto synchronization_definition() const  { return frame_configuration.rd<frame_configuration_t::synchronization_definition_t>();}

  inline void synchronization_polarity(const frame_configuration_t::synchronization_polarity_t::enum_t val) {  frame_configuration.rmw( val );}
  inline void synchronization_polarity_low() { frame_configuration.rmw( frame_configuration_t::synchronization_polarity_t::low );}
  inline void synchronization_polarity_high() { frame_configuration.rmw( frame_configuration_t::synchronization_polarity_t::high );}
  inline auto synchronization_polarity() const  { return frame_configuration.rd<frame_configuration_t::synchronization_polarity_t>();}

  inline void synchronization_offset(const frame_configuration_t::synchronization_offset_t::enum_t val) {  frame_configuration.rmw( val );}
  inline void synchronization_offset_first_bit() { frame_configuration.rmw( frame_configuration_t::synchronization_offset_t::first_bit );}
  inline void synchronization_offset_before_first_bit() { frame_configuration.rmw( frame_configuration_t::synchronization_offset_t::before_first_bit );}
  inline auto synchronization_offset() const  { return frame_configuration.rd<frame_configuration_t::synchronization_offset_t>();}

  struct slots_t : public read_write_32_t
  {
    struct first_bit_offset_t { enum enum_t { offset=0, mask=0b11111 }; } ;
    struct size_t { enum enum_t { offset=6, mask=0b11, data_size=0, bits16, bits32 }; } ;
    struct number_t  { enum enum_t { offset=8, mask=0b1111 }; };
    struct slot_0_t  { enum enum_t { offset=16, mask=1, disable=0, enable }; };
    struct slot_1_t  { enum enum_t { offset=17, mask=1, disable=0, enable }; };
    struct slot_2_t  { enum enum_t { offset=18, mask=1, disable=0, enable }; };
    struct slot_3_t  { enum enum_t { offset=19, mask=1, disable=0, enable }; };
    struct slot_4_t  { enum enum_t { offset=20, mask=1, disable=0, enable }; };
    struct slot_5_t  { enum enum_t { offset=21, mask=1, disable=0, enable }; };
    struct slot_6_t  { enum enum_t { offset=22, mask=1, disable=0, enable }; };
    struct slot_7_t  { enum enum_t { offset=23, mask=1, disable=0, enable }; };
    struct slot_8_t  { enum enum_t { offset=24, mask=1, disable=0, enable }; };
    struct slot_9_t  { enum enum_t { offset=25, mask=1, disable=0, enable }; };
    struct slot_10_t { enum enum_t { offset=26, mask=1, disable=0, enable }; };
    struct slot_11_t { enum enum_t { offset=27, mask=1, disable=0, enable }; };
    struct slot_12_t { enum enum_t { offset=28, mask=1, disable=0, enable }; };
    struct slot_13_t { enum enum_t { offset=29, mask=1, disable=0, enable }; };
    struct slot_14_t { enum enum_t { offset=30, mask=1, disable=0, enable }; };
    struct slot_15_t { enum enum_t { offset=31, mask=1, disable=0, enable }; };
  } ;

  inline void first_bit_offset(const uint8_t val) {  slots.rmw( (slots_t::first_bit_offset_t::enum_t )val );}
  inline auto first_bit_offset() const  { return (uint8_t)slots.rd<slots_t::first_bit_offset_t>();}

  inline void size(const slots_t::size_t::enum_t val) {  slots.rmw( val );}
  inline void size_data_size() { slots.rmw( slots_t::size_t::data_size );}
  inline void size_bits16() { slots.rmw( slots_t::size_t::bits16 );}
  inline void size_bits32() { slots.rmw( slots_t::size_t::bits32 );}
  inline auto size() const  { return slots.rd<slots_t::size_t>();}

  inline void number(const uint8_t val) {  slots.rmw( (slots_t::number_t::enum_t )val );}
  inline auto number() const  { return (uint8_t)slots.rd<slots_t::number_t>();}

  inline void slot_0(const slots_t::slot_0_t::enum_t val) {  slots.rmw( val );}
  inline void slot_0_disable() { slots.rmw( slots_t::slot_0_t::disable );}
  inline void slot_0_enable() { slots.rmw( slots_t::slot_0_t::enable );}
  inline auto slot_0() const  { return slots.rd<slots_t::slot_0_t>();}

  inline void slot_1(const slots_t::slot_1_t::enum_t val) {  slots.rmw( val );}
  inline void slot_1_disable() { slots.rmw( slots_t::slot_1_t::disable );}
  inline void slot_1_enable() { slots.rmw( slots_t::slot_1_t::enable );}
  inline auto slot_1() const  { return slots.rd<slots_t::slot_1_t>();}

  inline void slot_2(const slots_t::slot_2_t::enum_t val) {  slots.rmw( val );}
  inline void slot_2_disable() { slots.rmw( slots_t::slot_2_t::disable );}
  inline void slot_2_enable() { slots.rmw( slots_t::slot_2_t::enable );}
  inline auto slot_2() const  { return slots.rd<slots_t::slot_2_t>();}

  inline void slot_3(const slots_t::slot_3_t::enum_t val) {  slots.rmw( val );}
  inline void slot_3_disable() { slots.rmw( slots_t::slot_3_t::disable );}
  inline void slot_3_enable() { slots.rmw( slots_t::slot_3_t::enable );}
  inline auto slot_3() const  { return slots.rd<slots_t::slot_3_t>();}

  inline void slot_4(const slots_t::slot_4_t::enum_t val) {  slots.rmw( val );}
  inline void slot_4_disable() { slots.rmw( slots_t::slot_4_t::disable );}
  inline void slot_4_enable() { slots.rmw( slots_t::slot_4_t::enable );}
  inline auto slot_4() const  { return slots.rd<slots_t::slot_4_t>();}

  inline void slot_5(const slots_t::slot_5_t::enum_t val) {  slots.rmw( val );}
  inline void slot_5_disable() { slots.rmw( slots_t::slot_5_t::disable );}
  inline void slot_5_enable() { slots.rmw( slots_t::slot_5_t::enable );}
  inline auto slot_5() const  { return slots.rd<slots_t::slot_5_t>();}

  inline void slot_6(const slots_t::slot_6_t::enum_t val) {  slots.rmw( val );}
  inline void slot_6_disable() { slots.rmw( slots_t::slot_6_t::disable );}
  inline void slot_6_enable() { slots.rmw( slots_t::slot_6_t::enable );}
  inline auto slot_6() const  { return slots.rd<slots_t::slot_6_t>();}

  inline void slot_7(const slots_t::slot_7_t::enum_t val) {  slots.rmw( val );}
  inline void slot_7_disable() { slots.rmw( slots_t::slot_7_t::disable );}
  inline void slot_7_enable() { slots.rmw( slots_t::slot_7_t::enable );}
  inline auto slot_7() const  { return slots.rd<slots_t::slot_7_t>();}

  inline void slot_8(const slots_t::slot_8_t::enum_t val) {  slots.rmw( val );}
  inline void slot_8_disable() { slots.rmw( slots_t::slot_8_t::disable );}
  inline void slot_8_enable() { slots.rmw( slots_t::slot_8_t::enable );}
  inline auto slot_8() const  { return slots.rd<slots_t::slot_8_t>();}

  inline void slot_9(const slots_t::slot_9_t::enum_t val) {  slots.rmw( val );}
  inline void slot_9_disable() { slots.rmw( slots_t::slot_9_t::disable );}
  inline void slot_9_enable() { slots.rmw( slots_t::slot_9_t::enable );}
  inline auto slot_9() const  { return slots.rd<slots_t::slot_9_t>();}

  inline void slot_10(const slots_t::slot_10_t::enum_t val) {  slots.rmw( val );}
  inline void slot_10_disable() { slots.rmw( slots_t::slot_10_t::disable );}
  inline void slot_10_enable() { slots.rmw( slots_t::slot_10_t::enable );}
  inline auto slot_10() const  { return slots.rd<slots_t::slot_10_t>();}

  inline void slot_11(const slots_t::slot_11_t::enum_t val) {  slots.rmw( val );}
  inline void slot_11_disable() { slots.rmw( slots_t::slot_11_t::disable );}
  inline void slot_11_enable() { slots.rmw( slots_t::slot_11_t::enable );}
  inline auto slot_11() const  { return slots.rd<slots_t::slot_11_t>();}

  inline void slot_12(const slots_t::slot_12_t::enum_t val) {  slots.rmw( val );}
  inline void slot_12_disable() { slots.rmw( slots_t::slot_12_t::disable );}
  inline void slot_12_enable() { slots.rmw( slots_t::slot_12_t::enable );}
  inline auto slot_12() const  { return slots.rd<slots_t::slot_12_t>();}

  inline void slot_13(const slots_t::slot_13_t::enum_t val) {  slots.rmw( val );}
  inline void slot_13_disable() { slots.rmw( slots_t::slot_13_t::disable );}
  inline void slot_13_enable() { slots.rmw( slots_t::slot_13_t::enable );}
  inline auto slot_13() const  { return slots.rd<slots_t::slot_13_t>();}

  inline void slot_14(const slots_t::slot_14_t::enum_t val) {  slots.rmw( val );}
  inline void slot_14_disable() { slots.rmw( slots_t::slot_14_t::disable );}
  inline void slot_14_enable() { slots.rmw( slots_t::slot_14_t::enable );}
  inline auto slot_14() const  { return slots.rd<slots_t::slot_14_t>();}

  inline void slot_15(const slots_t::slot_15_t::enum_t val) {  slots.rmw( val );}
  inline void slot_15_disable() { slots.rmw( slots_t::slot_15_t::disable );}
  inline void slot_15_enable() { slots.rmw( slots_t::slot_15_t::enable );}
  inline auto slot_15() const  { return slots.rd<slots_t::slot_15_t>();}

  struct interrupt_t : public read_write_32_t
  {
    struct overrun_underrun_t { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
    struct mute_detection_t   { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
    struct wrong_clock_configuration_t  { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
    struct fifo_request_t  { enum enum_t { offset=3, mask=1, disable=0, enable}; } ;
    struct codec_not_ready_t  { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
    struct anticipated_frame_synchronization_detection_t  { enum enum_t { offset=5, mask=1, disable=0, enable}; } ;
    struct late_frame_synchronization_detection  { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
  };

  inline void interrupt_overrun_underrun(const interrupt_t::overrun_underrun_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_overrun_underrun_disable() { interrupt.rmw( interrupt_t::overrun_underrun_t::disable );}
  inline void interrupt_overrun_underrun_enable() { interrupt.rmw( interrupt_t::overrun_underrun_t::enable );}
  inline auto interrupt_overrun_underrun() const  { return interrupt.rd<interrupt_t::overrun_underrun_t>();}

  inline void interrupt_mute_detection(const interrupt_t::mute_detection_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_mute_detection_disable() { interrupt.rmw( interrupt_t::mute_detection_t::disable );}
  inline void interrupt_mute_detection_enable() { interrupt.rmw( interrupt_t::mute_detection_t::enable );}
  inline auto interrupt_mute_detection() const  { return interrupt.rd<interrupt_t::mute_detection_t>();}

  inline void interrupt_wrong_clock_configuration(const interrupt_t::wrong_clock_configuration_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_wrong_clock_configuration_disable() { interrupt.rmw( interrupt_t::wrong_clock_configuration_t::disable );}
  inline void interrupt_wrong_clock_configuration_enable() { interrupt.rmw( interrupt_t::wrong_clock_configuration_t::enable );}
  inline auto interrupt_wrong_clock_configuration() const  { return interrupt.rd<interrupt_t::wrong_clock_configuration_t>();}

  inline void interrupt_fifo_request(const interrupt_t::fifo_request_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_fifo_request_disable() { interrupt.rmw( interrupt_t::fifo_request_t::disable );}
  inline void interrupt_fifo_request_enable() { interrupt.rmw( interrupt_t::fifo_request_t::enable );}
  inline auto interrupt_fifo_request() const  { return interrupt.rd<interrupt_t::fifo_request_t>();}

  inline void interrupt_codec_not_ready(const interrupt_t::codec_not_ready_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_codec_not_ready_disable() { interrupt.rmw( interrupt_t::codec_not_ready_t::disable );}
  inline void interrupt_codec_not_ready_enable() { interrupt.rmw( interrupt_t::codec_not_ready_t::enable );}
  inline auto interrupt_codec_not_ready() const  { return interrupt.rd<interrupt_t::codec_not_ready_t>();}

  inline void interrupt_anticipated_frame_synchronization_detection(const interrupt_t::anticipated_frame_synchronization_detection_t::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_anticipated_frame_synchronization_detection_disable() { interrupt.rmw( interrupt_t::anticipated_frame_synchronization_detection_t::disable );}
  inline void interrupt_anticipated_frame_synchronization_detection_enable() { interrupt.rmw( interrupt_t::anticipated_frame_synchronization_detection_t::enable );}
  inline auto interrupt_anticipated_frame_synchronization_detection() const  { return interrupt.rd<interrupt_t::anticipated_frame_synchronization_detection_t>();}

  inline void interrupt_late_frame_synchronization_detection(const interrupt_t::late_frame_synchronization_detection::enum_t val) {  interrupt.rmw( val );}
  inline void interrupt_late_frame_synchronization_detection_disable() { interrupt.rmw( interrupt_t::late_frame_synchronization_detection::disable );}
  inline void interrupt_late_frame_synchronization_detection_enable() { interrupt.rmw( interrupt_t::late_frame_synchronization_detection::enable );}
  inline auto interrupt_late_frame_synchronization_detection() const  { return interrupt.rd<interrupt_t::late_frame_synchronization_detection>();}

  struct status_t : public read_write_32_t
  {
    struct overrun_underrun_t { enum enum_t { offset=0, mask=1, not_occured=0, occured}; } ;
    struct mute_detection_t   { enum enum_t { offset=1, mask=1, not_occured=0, occured}; } ;
    struct wrong_clock_configuration_t  { enum enum_t { offset=2, mask=1, not_occured=0, occured}; } ;
    struct fifo_request_t  { enum enum_t { offset=3, mask=1, not_occured=0, occured}; } ;
    struct codec_not_ready_t  { enum enum_t { offset=4, mask=1, not_occured=0, occured}; } ;
    struct anticipated_frame_synchronization_detection_t  { enum enum_t { offset=5, mask=1, not_occured=0, occured}; } ;
    struct late_frame_synchronization_detection_t  { enum enum_t { offset=6, mask=1, not_occured=0, occured}; } ;
    struct fifo_level_threshold_t  { enum enum_t { offset=16, mask=0b111 }; } ;
  };

  inline auto overrun_underrun() const  { return status.rd<status_t::overrun_underrun_t>();}
  inline auto mute_detection() const  { return status.rd<status_t::mute_detection_t>();}
  inline auto wrong_clock_configuration() const  { return status.rd<status_t::wrong_clock_configuration_t>();}
  inline auto fifo_request() const  { return status.rd<status_t::fifo_request_t>();}
  inline auto codec_not_ready() const  { return status.rd<status_t::codec_not_ready_t>();}
  inline auto anticipated_frame_synchronization_detection() const  { return status.rd<status_t::anticipated_frame_synchronization_detection_t>();}
  inline auto late_frame_synchronization_detection() const  { return status.rd<status_t::late_frame_synchronization_detection_t>();}
  inline auto fifo_level_threshold() const  { return status.rd<status_t::fifo_level_threshold_t>();}


  struct clear_t : public read_write_32_t
  {
	struct overrun_underrun_clear_t { enum enum_t { offset=0, mask=1, no_affect=0, clear}; } ;
	struct mute_detection_clear_t   { enum enum_t { offset=1, mask=1, no_affect=0, clear}; } ;
	struct wrong_clock_configuration_clear_t  { enum enum_t { offset=2, mask=1, no_affect=0, clear}; } ;
	struct codec_not_ready_clear_t  { enum enum_t { offset=4, mask=1, no_affect=0, clear}; } ;
	struct anticipated_frame_synchronization_detection_clear_t  { enum enum_t { offset=5, mask=1, no_affect=0, clear}; } ;
	struct late_frame_synchronization_detection_clear_t  { enum enum_t { offset=6, mask=1, no_affect=0, clear}; } ;
  };

  inline void overrun_underrun_clear() { clear.rmw( clear_t::overrun_underrun_clear_t::clear );}
  inline void mute_detection_clear() { clear.rmw( clear_t::mute_detection_clear_t::clear );}
  inline void wrong_clock_configuration_clear() { clear.rmw( clear_t::wrong_clock_configuration_clear_t::clear );}
  inline void codec_not_ready_clear() { clear.rmw( clear_t::codec_not_ready_clear_t::clear );}
  inline void anticipated_frame_synchronization_detection_clear() { clear.rmw( clear_t::anticipated_frame_synchronization_detection_clear_t::clear );}
  inline void late_frame_synchronization_detection_clear() { clear.rmw( clear_t::late_frame_synchronization_detection_clear_t::clear );}

  configuration_1_t  configuration_1 ; /*!< SAI block x configuration register 1,     Address offset: 0x04 */
  configuration_2_t  configuration_2 ; /*!< SAI block x configuration register 2,     Address offset: 0x08 */
  frame_configuration_t frame_configuration; /*!< SAI block x frame configuration register, Address offset: 0x0C */
  slots_t            slots;            /*!< SAI block x slot register,                Address offset: 0x10 */
  interrupt_t        interrupt;        /*!< SAI block x interrupt mask register,      Address offset: 0x14 */
  status_t           status;           /*!< SAI block x status register,              Address offset: 0x18 */
  clear_t            clear;            /*!< SAI block x clear flag register,          Address offset: 0x1C */
  volatile uint32_t  data;             /*!< SAI block x data register,                Address offset: 0x20 */
} ;


struct sai_t
{
  struct global_configuration_t : public read_write_32_t
  {
    struct synchronization_inputs_t { enum enum_t { offset=0, mask=0b11, sai1=0 , sai2 }; } ;
    struct synchronization_outputs_t{ enum enum_t { offset=4, mask=0b11, no=0 , block_a, block_b, disable }; } ;
  } ;

  inline void synchronization_inputs(const global_configuration_t::synchronization_inputs_t::enum_t val) {  global_configuration.rmw( val );}
  inline void synchronization_inputs_sai1() { global_configuration.rmw( global_configuration_t::synchronization_inputs_t::sai1 );}
  inline void synchronization_inputs_sai2() { global_configuration.rmw( global_configuration_t::synchronization_inputs_t::sai2 );}
  inline auto synchronization_inputs() const { return global_configuration.rd<global_configuration_t::synchronization_inputs_t>();}

  inline void synchronization_outputs(const global_configuration_t::synchronization_outputs_t::enum_t val) {  global_configuration.rmw( val );}
  inline void synchronization_outputs_block_a() { global_configuration.rmw( global_configuration_t::synchronization_outputs_t::block_a );}
  inline void synchronization_outputs_block_b() { global_configuration.rmw( global_configuration_t::synchronization_outputs_t::block_b );}
  inline auto synchronization_outputs() const { return global_configuration.rd<global_configuration_t::synchronization_outputs_t>();}

  global_configuration_t  global_configuration ; /*!< SAI global configuration register,        Address offset: 0x00 */

  sai_block_t block_a ;
  sai_block_t block_b ;

} ;

struct sai1_t : public sai_t
{
  inline void clock_enable() { rcc.sai1_enable() ; }
  inline void clock_disable() { rcc.sai1_disable() ; }
  inline void reset() { rcc.sai1_reset() ; }
} ;

struct sai2_t : public sai_t
{
  inline void clock_enable() { rcc.sai2_enable() ; }
  inline void clock_disable() { rcc.sai2_disable() ; }
  inline void reset() { rcc.sai2_reset() ; }
} ;

static sai1_t& sai1 = *((sai1_t*) sai1_addr);
static sai2_t& sai2 = *((sai2_t*) sai2_addr);

}

using namespace stm32f7 ;

#endif /* __SAI++_H__ */
