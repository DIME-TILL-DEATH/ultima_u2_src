/*
 * ethmac++.h
 *
 *  Created on: 11 окт. 2018 г.
 *      Author: klen
 */

#ifndef __ETHMAC_F4_F7++_H__
#define __ETHMAC_F4_F7++_H__


#include "types++.h"
#include "rcc++.h"

namespace stm32
{

  /* особый тип read_write_xx_t с реализацией обхода ошибок

  STM32F76xxx and STM32F77xxx device errata ES0334 Rev 5   22/28
  2.16.5 Successive write operations to the same register might not be fully taken into account
  */

  template<typename T, typename Y>
  struct read_write_eth_workarounds_t : public read_write_t<T,Y>
  {
    void inline write( void (*action)(uint32_t), const uint32_t action_val, const T val )
       { NRO
         *(((volatile T*)this))  = val;
         const T tmp = *(((volatile T*)this)) ;
         action (action_val) ;
         *(((volatile T*)this)) = tmp ;
       }

    template <typename U> void inline rmw( void (*action)(uint32_t), const uint32_t action_val, const U val)
       { NRO
         const T tmp = ((*(((volatile T*)this))) & (~(U::mask << U::offset ))) | ((val & U::mask) << U::offset) ;
         *((volatile T*)this) = tmp ;
         action (action_val) ;
         *((volatile T*)this) = tmp ;
       }

    template<typename... Args> inline T modify_action( void (*action)(uint32_t), const uint32_t action_val, const Args... args)
            { NRO T tmp = read_t<T,Y>::read() ; read_write_t<T,Y>::modify( tmp , args...);  write(action,action_val,tmp) ; return tmp ; }
  };

  typedef read_write_eth_workarounds_t<uint32_t,read_write_16_t> read_write_32_eth_workarounds_t ;
  typedef read_write_eth_workarounds_t<uint64_t,read_write_32_t> read_write_64_eth_workarounds_t ;


  struct eth_t
  {
    struct mac_t
    {
       struct config_t : public read_write_32_eth_workarounds_t
         {
           struct receiver_t                    { enum enum_t  { offset=2, mask=1, disable=0 , enable} ; } ;
           struct transmitter_t                 { enum enum_t  { offset=3, mask=1, disable=0 , enable} ; } ;
           struct deferral_check_t              { enum enum_t  { offset=4, mask=1, disable=0 , enable} ; } ;
           struct back_off_limit_t              { enum enum_t  { offset=5, mask=0b11, min_n_10=0 , min_n_8, min_n_4, min_n_1} ; } ;
           struct automatic_pad_crc_stripping_t { enum enum_t  { offset=7, mask=1, disable=0 , enable} ; } ;
           struct retry_t                       { enum enum_t  { offset=9, mask=1, enable=0 , disable} ; } ;
           struct ipv4_checksum_offload_t       { enum enum_t  { offset=10, mask=1, disable=0 , enable} ; } ;
           struct duplex_mode_t                 { enum enum_t  { offset=11, mask=1, disable=0 , enable} ; } ;
           struct loopback_mode_t               { enum enum_t  { offset=12, mask=1, disable=0 , enable} ; } ;
           struct receive_own_t                 { enum enum_t  { offset=13, mask=1, enable=0, disable} ; } ;
           struct speed_t                       { enum enum_t  { offset=14, mask=1, bps10M=0, bps100M} ; } ;
           struct carrier_sense_t               { enum enum_t  { offset=16, mask=1, enable=0, disable} ; } ;
           struct interfame_gap_t               { enum enum_t  { offset=17, mask=0b111, times_96bit=0, times_88bit, times_80bit, times_72bit,
	                                                               times_64bit, times_56bit, times_48bit, times_40bit} ; } ;
           struct jabber_t                      { enum enum_t  { offset=22, mask=1, enable=0, disable} ; } ;
           struct watchdog_t                    { enum enum_t  { offset=23, mask=1, enable=0, disable} ; } ;
           struct crc_stripping_type_frames_t   { enum enum_t  { offset=25, mask=1, disable=0, enable} ; } ;
         };

       inline  void receiver(const config_t::receiver_t::enum_t val){  config.rmw(nop_while, 100, val) ;}
       inline  void receiver_disable() {  config.rmw( nop_while, 100, config_t::receiver_t::disable) ;}
       inline  void receiver_enable() {  config.rmw( nop_while,100, config_t::receiver_t::enable) ;}
       inline  auto receiver()const {  return config.rd<config_t::receiver_t>();}

       inline  void transmitter(const config_t::transmitter_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void transmitter_disable() {  config.rmw( nop_while, 100, config_t::transmitter_t::disable) ;}
       inline  void transmitter_enable() {  config.rmw( nop_while, 100, config_t::transmitter_t::enable) ;}
       inline  auto transmitter()const {  return config.rd<config_t::transmitter_t>();}

       inline  void deferral_check(const config_t::deferral_check_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void deferral_check_disable() {  config.rmw( nop_while, 100, config_t::deferral_check_t::disable) ;}
       inline  void deferral_check_enable() {  config.rmw( nop_while, 100, config_t::deferral_check_t::enable) ;}
       inline  auto deferral_check()const {  return config.rd<config_t::deferral_check_t>();}

       inline  void back_off_limit(const config_t::back_off_limit_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void back_off_limit_min_n_10(){  config.rmw( nop_while, 100, config_t::back_off_limit_t::min_n_10) ;}
       inline  void back_off_limit_min_n_8() {  config.rmw( nop_while, 100, config_t::back_off_limit_t::min_n_8) ;}
       inline  void back_off_limit_min_n_4() {  config.rmw( nop_while, 100, config_t::back_off_limit_t::min_n_4) ;}
       inline  void back_off_limit_min_n_1() {  config.rmw( nop_while, 100, config_t::back_off_limit_t::min_n_1) ;}
       inline  auto back_off_limit() const {  return config.rd<config_t::back_off_limit_t>();}

       inline  void automatic_pad_crc_stripping(const config_t::automatic_pad_crc_stripping_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void automatic_pad_crc_stripping_disable() {  config.rmw( nop_while, 100, config_t::automatic_pad_crc_stripping_t::disable) ;}
       inline  void automatic_pad_crc_stripping_enable() {  config.rmw( nop_while, 100, config_t::automatic_pad_crc_stripping_t::enable) ;}
       inline  auto automatic_pad_crc_stripping()const {  return config.rd<config_t::automatic_pad_crc_stripping_t>();}

       inline  void retry(const config_t::retry_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void retry_disable() {  config.rmw( nop_while, 100, config_t::retry_t::disable) ;}
       inline  void retry_enable() {  config.rmw( nop_while, 100, config_t::retry_t::enable) ;}
       inline  auto retry()const {  return config.rd<config_t::retry_t>();}

       inline  void ipv4_checksum_offload(const config_t::ipv4_checksum_offload_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void ipv4_checksum_offload_disable() {  config.rmw( nop_while, 100, config_t::ipv4_checksum_offload_t::disable) ;}
       inline  void ipv4_checksum_offload_enable() {  config.rmw( nop_while, 100, config_t::ipv4_checksum_offload_t::enable) ;}
       inline  auto ipv4_checksum_offload()const {  return config.rd<config_t::ipv4_checksum_offload_t>();}

       inline  void duplex_mode(const config_t::duplex_mode_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void duplex_mode_disable() {  config.rmw( nop_while, 100, config_t::duplex_mode_t::disable) ;}
       inline  void duplex_mode_enable() {  config.rmw( nop_while, 100, config_t::duplex_mode_t::enable) ;}
       inline  auto duplex_mode()const {  return config.rd<config_t::duplex_mode_t>();}

       inline  void loopback_mode(const config_t::loopback_mode_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void loopback_mode_disable() {  config.rmw( nop_while, 100, config_t::loopback_mode_t::disable) ;}
       inline  void loopback_mode_enable() {  config.rmw( nop_while, 100, config_t::loopback_mode_t::enable) ;}
       inline  auto loopback_mode()const {  return config.rd<config_t::loopback_mode_t>();}

       inline  void receive_own(const config_t::receive_own_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void receive_own_disable() {  config.rmw( nop_while, 100, config_t::receive_own_t::disable) ;}
       inline  void receive_own_enable() {  config.rmw( nop_while, 100, config_t::receive_own_t::enable) ;}
       inline  auto receive_own()const {  return config.rd<config_t::receive_own_t>();}

       inline  void speed(const config_t::speed_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void speed_bps10M() {  config.rmw( nop_while, 100, config_t::speed_t::bps10M) ;}
       inline  void speed_bps100M(){  config.rmw( nop_while, 100, config_t::speed_t::bps100M) ;}
       inline  auto speed()const {  return config.rd<config_t::speed_t>();}

       inline  void carrier_sense(const config_t::carrier_sense_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void carrier_sense_disable() {  config.rmw( nop_while, 100, config_t::carrier_sense_t::disable) ;}
       inline  void carrier_sense_enable() {  config.rmw( nop_while, 100, config_t::carrier_sense_t::enable) ;}
       inline  auto carrier_sense()const {  return config.rd<config_t::carrier_sense_t>();}

       inline  void interfame_gap(const config_t::interfame_gap_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void interfame_gap_times_96bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_96bit) ;}
       inline  void interfame_gap_times_88bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_88bit) ;}
       inline  void interfame_gap_times_80bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_80bit) ;}
       inline  void interfame_gap_times_72bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_72bit) ;}
       inline  void interfame_gap_times_64bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_64bit) ;}
       inline  void interfame_gap_times_56bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_56bit) ;}
       inline  void interfame_gap_times_48bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_48bit) ;}
       inline  void interfame_gap_times_40bit() {  config.rmw( nop_while, 100, config_t::interfame_gap_t::times_40bit) ;}
       inline  auto interfame_gap()const {  return config.rd<config_t::interfame_gap_t>();}

       inline  void jabber(const config_t::jabber_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void jabber_disable() {  config.rmw( nop_while, 100, config_t::jabber_t::disable) ;}
       inline  void jabber_enable() {  config.rmw( nop_while, 100, config_t::jabber_t::enable) ;}
       inline  auto jabber()const {  return config.rd<config_t::jabber_t>();}

       inline  void watchdog(const config_t::watchdog_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void watchdog_disable() {  config.rmw( nop_while, 100, config_t::watchdog_t::disable) ;}
       inline  void watchdog_enable() {  config.rmw( nop_while, 100, config_t::watchdog_t::enable) ;}
       inline  auto watchdog()const {  return config.rd<config_t::watchdog_t>();}

       inline  void crc_stripping_type_frames(const config_t::crc_stripping_type_frames_t::enum_t val){  config.rmw(nop_while, 100,val) ;}
       inline  void crc_stripping_type_frames_disable() {  config.rmw( nop_while, 100, config_t::crc_stripping_type_frames_t::disable) ;}
       inline  void crc_stripping_type_frames_enable() {  config.rmw( nop_while, 100, config_t::crc_stripping_type_frames_t::enable) ;}
       inline  auto crc_stripping_type_frames()const {  return config.rd<config_t::crc_stripping_type_frames_t>();}

       struct frame_filter_t : public read_write_32_eth_workarounds_t
          {
	     struct promiscuous_mode_t                      { enum enum_t  { offset=0, mask=1, disable=0 , enable} ; } ;
	     struct hash_unicast_t                          { enum enum_t  { offset=1, mask=1, disable=0 , enable} ; } ;
	     struct hash_multicast_t                        { enum enum_t  { offset=2, mask=1, disable=0 , enable} ; } ;
	     struct destination_address_inverse_filtering_t { enum enum_t  { offset=3, mask=1, disable=0 , enable} ; } ;
	     struct pass_all_multicast_t                    { enum enum_t  { offset=4, mask=1, disable=0 , enable} ; } ;
	     struct droadcast_frames_t                      { enum enum_t  { offset=5, mask=1, enable=0 , disable} ; } ;
	     struct pass_control_frames_t                   { enum enum_t  { offset=6, mask=0b11, prevent_all=0, forwards_all_except_pause, forwards_all_even_fail_address_filter, forwards_address_filter} ; } ;
	     struct source_address_inverse_filtering_t      { enum enum_t  { offset=8, mask=1, disable=0 , enable} ; } ;
	     struct source_address_filter_t                 { enum enum_t  { offset=9, mask=1, disable=0 , enable} ; } ;
	     struct hash_perfect_filter_t                   { enum enum_t  { offset=10,mask=1, disable=0 , enable} ; } ;
	     struct receive_all_t                           { enum enum_t  { offset=31,mask=1, disable=0 , enable} ; } ;
          } ;

       inline  void promiscuous_mode(const frame_filter_t::promiscuous_mode_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void promiscuous_mode_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::promiscuous_mode_t::disable) ;}
       inline  void promiscuous_mode_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::promiscuous_mode_t::enable) ;}
       inline  auto promiscuous_mode()const {  return frame_filter.rd<frame_filter_t::promiscuous_mode_t>();}

       inline  void hash_unicast(const frame_filter_t::hash_unicast_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void hash_unicast_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_unicast_t::disable) ;}
       inline  void hash_unicast_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_unicast_t::enable) ;}
       inline  auto hash_unicast()const {  return frame_filter.rd<frame_filter_t::hash_unicast_t>();}

       inline  void hash_multicast(const frame_filter_t::hash_multicast_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void hash_multicast_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_multicast_t::disable) ;}
       inline  void hash_multicast_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_multicast_t::enable) ;}
       inline  auto hash_multicast()const {  return frame_filter.rd<frame_filter_t::hash_multicast_t>();}

       inline  void destination_address_inverse_filtering(const frame_filter_t::destination_address_inverse_filtering_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void destination_address_inverse_filtering_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::destination_address_inverse_filtering_t::disable) ;}
       inline  void destination_address_inverse_filtering_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::destination_address_inverse_filtering_t::enable) ;}
       inline  auto destination_address_inverse_filtering()const {  return frame_filter.rd<frame_filter_t::destination_address_inverse_filtering_t>();}

       inline  void pass_all_multicast(const frame_filter_t::pass_all_multicast_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void pass_all_multicast_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_all_multicast_t::disable) ;}
       inline  void pass_all_multicast_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_all_multicast_t::enable) ;}
       inline  auto pass_all_multicast()const {  return frame_filter.rd<frame_filter_t::pass_all_multicast_t>();}

       inline  void droadcast_frames(const frame_filter_t::droadcast_frames_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void droadcast_frames_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::droadcast_frames_t::disable) ;}
       inline  void droadcast_frames_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::droadcast_frames_t::enable) ;}
       inline  auto droadcast_frames()const {  return frame_filter.rd<frame_filter_t::droadcast_frames_t>();}

       inline  void pass_control_frames(const frame_filter_t::pass_control_frames_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void pass_control_frames_prevent_all() {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_control_frames_t::prevent_all) ;}
       inline  void pass_control_frames_forwards_all_except_pause() {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_control_frames_t::forwards_all_except_pause) ;}
       inline  void pass_control_frames_forwards_all_even_fail_address_filter() {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_control_frames_t::forwards_all_even_fail_address_filter) ;}
       inline  void pass_control_frames_forwards_address_filter() {  frame_filter.rmw( nop_while, 100, frame_filter_t::pass_control_frames_t::forwards_address_filter) ;}
       inline  auto pass_control_frames()const {  return frame_filter.rd<frame_filter_t::pass_control_frames_t>();}

       inline  void source_address_inverse_filtering(const frame_filter_t::source_address_inverse_filtering_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void source_address_inverse_filtering_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::source_address_inverse_filtering_t::disable) ;}
       inline  void source_address_inverse_filtering_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::source_address_inverse_filtering_t::enable) ;}
       inline  auto source_address_inverse_filtering()const {  return frame_filter.rd<frame_filter_t::source_address_inverse_filtering_t>();}

       inline  void source_address_filter(const frame_filter_t::source_address_filter_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void source_address_filter_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::source_address_filter_t::disable) ;}
       inline  void source_address_filter_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::source_address_filter_t::enable) ;}
       inline  auto source_address_filter()const {  return frame_filter.rd<frame_filter_t::source_address_filter_t>();}

       inline  void hash_perfect_filter(const frame_filter_t::hash_perfect_filter_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void hash_perfect_filter_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_perfect_filter_t::disable) ;}
       inline  void hash_perfect_filter_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::hash_perfect_filter_t::enable) ;}
       inline  auto hash_perfect_filter()const {  return frame_filter.rd<frame_filter_t::hash_perfect_filter_t>();}

       inline  void receive_all(const frame_filter_t::receive_all_t::enum_t val){  frame_filter.rmw(nop_while, 100,val) ;}
       inline  void receive_all_disable() {  frame_filter.rmw( nop_while, 100, frame_filter_t::receive_all_t::disable) ;}
       inline  void receive_all_enable()  {  frame_filter.rmw( nop_while, 100, frame_filter_t::receive_all_t::enable) ;}
       inline  auto receive_all()const {  return frame_filter.rd<frame_filter_t::receive_all_t>();}

       struct hash_table_t : public read_write_64_eth_workarounds_t
          {} ;

       inline  void hash(const uint64_t val){  hash_table.write( nop_while, 100, val ) ;}
       inline  auto hash() const { return hash_table.read();}

       struct mii_address_t : public read_write_32_t
          {
	     struct busy_t       { enum enum_t { offset=0, mask=1, no_operation=0, operation_ongoing }; } ;
	     struct operation_t  { enum enum_t { offset=1, mask=1, read=0, write }; } ;
	     struct clock_range_t{ enum enum_t { offset=2, mask=0b111, hclk_div42=0, hclk_div62, hclk_div16, hclk_div26, hclk_div102  }; } ;
	     struct register_t   { enum enum_t { offset=6, mask=0b11111 }; } ;
	     struct phy_t        { enum enum_t { offset=11,mask=0b11111 }; } ;
          } ;

       inline  auto mii_busy()const {  return mii_address.rd<mii_address_t::busy_t>();}
       inline  void mii_busy_set() { mii_address.rmw(mii_address_t::busy_t::operation_ongoing) ;}
       inline  void mii_busy_wait() const { while ( mii_busy()== mii_address_t::busy_t::operation_ongoing) {} }

       inline  void mii_operation(const mii_address_t::operation_t::enum_t val){  mii_address.rmw(val) ;}
       inline  void mii_operation_read() { mii_address.rmw(mii_address_t::operation_t::read) ;}
       inline  void mii_operation_write(){ mii_address.rmw(mii_address_t::operation_t::write) ;}
       inline  auto mii_operation() const { return mii_address.rd<mii_address_t::operation_t>();}

       inline  void mii_clock_range(const mii_address_t::clock_range_t::enum_t val){  mii_address.rmw(val) ;}
       inline  void mii_clock_range_hclk_div42(){ mii_address.rmw(mii_address_t::clock_range_t::hclk_div42) ;}
       inline  void mii_clock_range_hclk_div62(){ mii_address.rmw(mii_address_t::clock_range_t::hclk_div62) ;}
       inline  void mii_clock_range_hclk_div16(){ mii_address.rmw(mii_address_t::clock_range_t::hclk_div16) ;}
       inline  void mii_clock_range_hclk_div26(){ mii_address.rmw(mii_address_t::clock_range_t::hclk_div26) ;}
       inline  void mii_clock_range_hclk_div102(){ mii_address.rmw(mii_address_t::clock_range_t::hclk_div102) ;}
       inline  auto mii_clock_range() const { return mii_address.rd<mii_address_t::clock_range_t>();}

       inline  void mii_register(const uint8_t val){  mii_address.rmw( (mii_address_t::register_t::enum_t)val) ;}
       inline  auto mii_register() const { return (uint8_t)mii_address.rd<mii_address_t::register_t>();}

       inline  void mii_phy(const uint8_t val){  mii_address.rmw( (mii_address_t::phy_t::enum_t)val) ;}
       inline  auto mii_phy() const { return (uint8_t)mii_address.rd<mii_address_t::phy_t>();}


       struct flow_control_t : public read_write_32_eth_workarounds_t
          {
	     struct flow_control_busy_back_pressure_t         { enum enum_t  { offset=0, mask=1, disable=0 , enable} ; } ;
	     struct transmit_flow_control_t                   { enum enum_t  { offset=1, mask=1, disable=0 , enable} ; } ;
	     struct receive_flow_control_t                    { enum enum_t  { offset=2, mask=1, disable=0 , enable} ; } ;
	     struct unicast_pause_frame_detect_t              { enum enum_t  { offset=3, mask=1, disable=0 , enable} ; } ;
	     struct pause_low_threshold_t                     { enum enum_t  { offset=4, mask=0b11, minus_4_slot=0 , minus_28_slot, minus_114_slot, minus_256_slot} ; } ;
	     struct zero_quanta_pause_t                       { enum enum_t  { offset=7, mask=1, enable=0 , disable} ; } ;
	     struct pause_time_t                              { enum enum_t  { offset=16, mask=0xffff } ; } ;
          };

       inline  void flow_control_busy_back_pressure(const flow_control_t::flow_control_busy_back_pressure_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void flow_control_busy_back_pressure_disable() { flow_control.rmw( nop_while, 100, flow_control_t::flow_control_busy_back_pressure_t::disable) ;}
       inline  void flow_control_busy_back_pressure_enable() { flow_control.rmw( nop_while, 100, flow_control_t::flow_control_busy_back_pressure_t::enable) ;}
       inline  auto flow_control_busy_back_pressure() const { return flow_control.rd<flow_control_t::flow_control_busy_back_pressure_t>();}

       inline  void transmit_flow_control(const flow_control_t::transmit_flow_control_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void transmit_flow_control_disable() { flow_control.rmw( nop_while, 100, flow_control_t::transmit_flow_control_t::disable) ;}
       inline  void transmit_flow_control_enable() { flow_control.rmw( nop_while, 100, flow_control_t::transmit_flow_control_t::enable) ;}
       inline  auto transmit_flow_control() const { return flow_control.rd<flow_control_t::transmit_flow_control_t>();}

       inline  void receive_flow_control(const flow_control_t::receive_flow_control_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void receive_flow_control_disable() { flow_control.rmw( nop_while, 100, flow_control_t::receive_flow_control_t::disable) ;}
       inline  void receive_flow_control_enable() { flow_control.rmw( nop_while, 100, flow_control_t::receive_flow_control_t::enable) ;}
       inline  auto receive_flow_control() const { return flow_control.rd<flow_control_t::receive_flow_control_t>();}

       inline  void unicast_pause_frame_detect(const flow_control_t::unicast_pause_frame_detect_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void unicast_pause_frame_detect_disable() { flow_control.rmw( nop_while, 100, flow_control_t::unicast_pause_frame_detect_t::disable) ;}
       inline  void unicast_pause_frame_detect_enable() { flow_control.rmw( nop_while, 100, flow_control_t::unicast_pause_frame_detect_t::enable) ;}
       inline  auto unicast_pause_frame_detect() const { return flow_control.rd<flow_control_t::unicast_pause_frame_detect_t>();}

       inline  void pause_low_threshold(const flow_control_t::pause_low_threshold_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void pause_low_threshold_minus_4_slot() { flow_control.rmw( nop_while, 100, flow_control_t::pause_low_threshold_t::minus_4_slot) ;}
       inline  void pause_low_threshold_minus_28_slot() { flow_control.rmw( nop_while, 100, flow_control_t::pause_low_threshold_t::minus_28_slot) ;}
       inline  void pause_low_threshold_minus_114_slot() { flow_control.rmw( nop_while, 100, flow_control_t::pause_low_threshold_t::minus_114_slot) ;}
       inline  void pause_low_threshold_minus_256_slot() { flow_control.rmw( nop_while, 100, flow_control_t::pause_low_threshold_t::minus_256_slot) ;}
       inline  auto pause_low_threshold() const { return flow_control.rd<flow_control_t::pause_low_threshold_t>();}

       inline  void zero_quanta_pause(const flow_control_t::zero_quanta_pause_t::enum_t val){  flow_control.rmw(nop_while, 100,val) ;}
       inline  void zero_quanta_pause_disable() { flow_control.rmw( nop_while, 100, flow_control_t::zero_quanta_pause_t::disable) ;}
       inline  void zero_quanta_pause_enable() { flow_control.rmw( nop_while, 100, flow_control_t::zero_quanta_pause_t::enable) ;}
       inline  auto zero_quanta_pause() const { return flow_control.rd<flow_control_t::zero_quanta_pause_t>();}

       inline  void pause_time(const uint16_t val){  flow_control.rmw( nop_while, 100, (flow_control_t::pause_time_t::enum_t)val) ;}
       inline  auto pause_time() const { return (uint16_t)flow_control.rd<flow_control_t::pause_time_t>();}

       struct vlan_tag_t : public read_write_32_eth_workarounds_t
          {
	     struct identifier_t   { enum enum_t  { offset=0, mask=0xffff} ; } ;
	     struct comparison_t   { enum enum_t  { offset=16, mask=1, bit16=0, bit12} ; } ;
          } ;

       inline  void vlan_tag_comparison(const vlan_tag_t::comparison_t::enum_t val){  vlan_tag.rmw(nop_while, 100,val) ;}
       inline  void vlan_tag_comparison_bit16() {  vlan_tag.rmw( nop_while, 100, vlan_tag_t::comparison_t::bit16) ;}
       inline  void vlan_tag_comparison_bit12() {  vlan_tag.rmw( nop_while, 100, vlan_tag_t::comparison_t::bit12) ;}
       inline  auto vlan_tag_comparison()const {  return vlan_tag.rd<vlan_tag_t::comparison_t>();}

       inline  void vlan_tag_identifier(const uint16_t val){  vlan_tag.rmw(nop_while, 100,(vlan_tag_t::identifier_t::enum_t)val) ;}
       inline  auto vlan_tag_identifier()const {  return (uint16_t)vlan_tag.rd<vlan_tag_t::identifier_t>();}

       struct remote_wakeup_frame_filter_t : public read_write_32_t
          {} ;

       struct pmt_control_status_t : public read_write_32_t
          {} ;

       struct debug_t : public read_write_32_t
          {} ;

       struct interrupt_status_t : public read_write_32_t
          {} ;

       struct interrupt_mask_t : public read_write_32_t
          {} ;

       struct address_t : public read_write_64_t
          {} ;


       void inline address (const uint8_t index, const uint8_t* val)
         {
	   (&(address_0.reg_value))[index]  = 0x80000000ul |
   	                                                  ((uint32_t)val[5] << 8 ) |
   		                                           (uint32_t)val[4] |
   			                       ((uint64_t)((uint32_t)val[3] << 24) |
   			                                  ((uint32_t)val[2] << 16) |
   			                                  ((uint32_t)val[1] << 8 ) |
			                                             val[0])<< 32  ;
         }



       config_t                     config;         // *MACCR;
       frame_filter_t               frame_filter;   // *MACFFR;
       hash_table_t                 hash_table;     // *MACHTHR;
                                                    // *MACHTLR;
       mii_address_t                mii_address;    //  MACMIIAR;
       volatile uint16_t            mii_data ;      //  MACMIIDR;
       const    uint16_t : 16 ;
       flow_control_t               flow_control;   // *MACFCR;
       vlan_tag_t                   vlan_tag;       //  MACVLANTR;
       const uint32_t               reserved0[2];
       remote_wakeup_frame_filter_t remote_wakeup_frame_filter; //*MACRWUFFR;
       pmt_control_status_t         pmt_control_status;         // MACPMTCSR;
       const    uint32_t : 32 ;
       debug_t                      debug;
       interrupt_status_t           interrupt_status;// MACSR;
       interrupt_mask_t             interrupt_mask;  // MACIMR;
       address_t                    address_0;       //*MACA0HR;
                                                     //*MACA0LR;
       address_t                    address_1;       //*MACA1HR;
                                                     //*MACA1LR;
       address_t                    address_2;       //*MACA2HR;
                                                     //*MACA2LR;
       address_t                    address_3;       //*MACA3HR;
                                                     //*MACA3LR;
       const uint32_t               reserved1[40];





    };

    struct mmc_t
       {

          struct control_t : public read_write_32_t
             {} ;

          struct receive_interrupt_t : public read_write_32_t
             {} ;

          struct transmit_interrupt_t : public read_write_32_t
             {} ;

          struct receive_interrupt_mask_t : public read_write_32_t
             {} ;

          struct transmit_interrupt_mask_t : public read_write_32_t
             {} ;

          struct receive_interrupt_mask : public read_write_32_t
             {} ;

          struct transmit_interrupt_mask : public read_write_32_t
             {} ;

          struct transmitted_good_frames_after_single_collision_counter_t : public read_write_32_t
             {} ;

          struct transmitted_good_frames_after_more_collision_counter_t : public read_write_32_t
             {} ;

          struct transmitted_good_frames_counter_t : public read_write_32_t
             {} ;

          struct received_frames_with_crc_error_t : public read_write_32_t
             {} ;

          struct received_frames_with_alignment_error_counter_t : public read_write_32_t
             {} ;

          struct received_good_unicast_frames_counter_t : public read_write_32_t
             {} ;

          control_t                control;     // MMCCR;
          receive_interrupt_t      receive_interrupt; //MMCRIR;
          transmit_interrupt_t     transmit_interrupt;//MMCTIR;
          receive_interrupt_mask_t receive_interrupt_mask;// MMCRIMR;
          transmit_interrupt_mask_t transmit_interrupt_mask;// MMCTIMR;
          const uint32_t reserved0[14];
          transmitted_good_frames_after_single_collision_counter_t transmitted_good_frames_after_single_collision_counter_t;//MMCTGFSCCR;
          transmitted_good_frames_after_more_collision_counter_t   transmitted_good_frames_after_more_collision_counter;// MMCTGFMSCCR;
          const uint32_t reserved1[5];
          transmitted_good_frames_counter_t transmitted_good_frames_counter;//MMCTGFCR;
          const uint32_t reserved2[10];
          received_frames_with_crc_error_t received_frames_with_crc_error; //counterMMCRFCECR;
          received_frames_with_alignment_error_counter_t received_frames_with_alignment_error_counter;//MMCRFAECR;
          const uint32_t reserved3[10];
          received_good_unicast_frames_counter_t received_good_unicast_frames_counter;//MMCRGUFCR;
          const uint32_t reserved4[334];
       };

    struct ptp_t
       {
          struct time_stamp_control_t : public read_write_32_t
            {} ;
          struct time_stamp_status_t : public read_write_32_t
            {} ;
          struct pps_control_t : public read_write_32_t
            {} ;

          time_stamp_control_t time_stamp_control;//*PTPTSCR;
          volatile uint32_t subsecond_increment;//PTPSSIR;
          volatile uint64_t time_stamp;//PTPTSHR;
                                       //PTPTSLR;
          volatile uint64_t time_stamp_update;//PTPTSHUR;
          struct {                                    //PTPTSLUR;
                   volatile uint32_t time_stamp_addend;//PTPTSAR;
                   volatile uint64_t target_time;//PTPTTHR;
                                                 //PTPTTLR;
                 } __attribute__((packed)) ;
          const uint32_t : 32 ;

          time_stamp_status_t time_stamp_status;//PTPTSSR;
          pps_control_t pps_control; //PTPPPSCR
          const uint32_t reserved[563];
       }   ;

    struct dma_t
       {
          struct bus_mode_t : public read_write_32_eth_workarounds_t
             {
                struct software_reset_state_t         { enum enum_t  { offset=0, mask=1, no_action=0 , action} ; } ;
                struct arbitration_t                  { enum enum_t  { offset=1, mask=1, round_robin=0 , rx_priority} ; } ;
                struct descriptor_skip_length_t       { enum enum_t  { offset=2, mask=0b11111 } ; } ;
                struct enhanced_descriptor_format_t   { enum enum_t  { offset=7, mask=1, disable=0 , enable} ; } ;
                struct programmable_burst_length_t    { enum enum_t  { offset=8, mask=0b111111 } ; } ;
                struct rx_priority_ratio_t            { enum enum_t  { offset=14, mask=0b11, ratio_1_by_1=0, ratio_1_by_2, ratio_1_by_3, ratio_1_by_4 } ; } ;
                struct fixed_burst_t                  { enum enum_t  { offset=16, mask=1, disable=0 , enable} ; } ;
                struct rx_programmable_burst_length_t { enum enum_t  { offset=17, mask=0b111111 } ; } ;
                struct separete_programmable_burst_length_t { enum enum_t  { offset=23, mask=1, disable=0, enable } ; } ;
                struct programmable_burst_length_x4_t { enum enum_t  { offset=24, mask=1, disable=0, enable } ; } ;
                struct address_aligned_beats_t        { enum enum_t  { offset=25, mask=1, disable=0, enable } ; } ;
                struct mixed_burst_t                  { enum enum_t  { offset=26, mask=1, disable=0, enable } ; } ;

             } ;

          inline  void software_reset_state_reset() {  bus_mode.rmw( nop_while, 100, bus_mode_t::software_reset_state_t::action) ;}
          inline  auto software_reset_state()const {  return bus_mode.rd<bus_mode_t::software_reset_state_t>();}
          inline  void software_reset_state_wait() { while (software_reset_state() == bus_mode_t::software_reset_state_t::action) ; }

          inline  void arbitration(const bus_mode_t::arbitration_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void arbitration_round_robin() {  bus_mode.rmw( nop_while, 100, bus_mode_t::arbitration_t::round_robin) ;}
          inline  void arbitration_rx_priority() {  bus_mode.rmw( nop_while, 100, bus_mode_t::arbitration_t::rx_priority) ;}
          inline  auto arbitration()const {  return bus_mode.rd<bus_mode_t::arbitration_t>();}

          inline  void descriptor_skip_length(const uint8_t val){  bus_mode.rmw(nop_while, 100,(bus_mode_t::descriptor_skip_length_t::enum_t)val) ;}
          inline  auto descriptor_skip_length()const {  return (uint8_t)bus_mode.rd<bus_mode_t::descriptor_skip_length_t>();}

          inline  void enhanced_descriptor_format(const bus_mode_t::enhanced_descriptor_format_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void enhanced_descriptor_format_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::enhanced_descriptor_format_t::disable) ;}
          inline  void enhanced_descriptor_format_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::enhanced_descriptor_format_t::enable) ;}
          inline  auto enhanced_descriptor_format()const {  return bus_mode.rd<bus_mode_t::enhanced_descriptor_format_t>();}

          inline  void programmable_burst_length(const uint8_t val){  bus_mode.rmw(nop_while, 100,(bus_mode_t::programmable_burst_length_t::enum_t)val) ;}
          inline  auto programmable_burst_length()const {  return (uint8_t)bus_mode.rd<bus_mode_t::programmable_burst_length_t>();}

          inline  void rx_priority_ratio(const bus_mode_t::rx_priority_ratio_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void rx_priority_ratio_1_by_1() {  bus_mode.rmw( nop_while, 100, bus_mode_t::rx_priority_ratio_t::ratio_1_by_1) ;}
          inline  void rx_priority_ratio_2_by_1() {  bus_mode.rmw( nop_while, 100, bus_mode_t::rx_priority_ratio_t::ratio_1_by_2) ;}
          inline  void rx_priority_ratio_3_by_1() {  bus_mode.rmw( nop_while, 100, bus_mode_t::rx_priority_ratio_t::ratio_1_by_3) ;}
          inline  void rx_priority_ratio_4_by_1() {  bus_mode.rmw( nop_while, 100, bus_mode_t::rx_priority_ratio_t::ratio_1_by_4) ;}
          inline  auto rx_priority_ratio()const {  return bus_mode.rd<bus_mode_t::rx_priority_ratio_t>();}

          inline  void fixed_burst(const bus_mode_t::fixed_burst_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void fixed_burst_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::fixed_burst_t::disable) ;}
          inline  void fixed_burst_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::fixed_burst_t::enable) ;}
          inline  auto fixed_burst()const {  return bus_mode.rd<bus_mode_t::fixed_burst_t>();}

          inline  void rx_programmable_burst_length(const uint8_t val){  bus_mode.rmw(nop_while, 100,(bus_mode_t::rx_programmable_burst_length_t::enum_t)val) ;}
          inline  auto rx_programmable_burst_length()const {  return (uint8_t)bus_mode.rd<bus_mode_t::rx_programmable_burst_length_t>();}

          inline  void separete_programmable_burst_length(const bus_mode_t::separete_programmable_burst_length_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void separete_programmable_burst_length_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::separete_programmable_burst_length_t::disable) ;}
          inline  void separete_programmable_burst_length_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::separete_programmable_burst_length_t::enable) ;}
          inline  auto separete_programmable_burst_length()const {  return bus_mode.rd<bus_mode_t::separete_programmable_burst_length_t>();}

          inline  void programmable_burst_length_x4(const bus_mode_t::programmable_burst_length_x4_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void programmable_burst_length_x4_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::programmable_burst_length_x4_t::disable) ;}
          inline  void programmable_burst_length_x4_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::programmable_burst_length_x4_t::enable) ;}
          inline  auto programmable_burst_length_x4()const {  return bus_mode.rd<bus_mode_t::programmable_burst_length_x4_t>();}

          inline  void address_aligned_beats(const bus_mode_t::address_aligned_beats_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void address_aligned_beats_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::address_aligned_beats_t::disable) ;}
          inline  void address_aligned_beats_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::address_aligned_beats_t::enable) ;}
          inline  auto address_aligned_beats()const {  return bus_mode.rd<bus_mode_t::address_aligned_beats_t>();}

          inline  void mixed_burst(const bus_mode_t::mixed_burst_t::enum_t val){  bus_mode.rmw(nop_while, 100,val) ;}
          inline  void mixed_burst_disable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::mixed_burst_t::disable) ;}
          inline  void mixed_burst_enable() {  bus_mode.rmw( nop_while, 100, bus_mode_t::mixed_burst_t::enable) ;}
          inline  auto mixed_burst()const {  return bus_mode.rd<bus_mode_t::mixed_burst_t>();}

          struct status_t : public read_write_32_t
             {
                struct transmit_status_t                      { enum enum_t  { offset=0, mask=1, not_occured=0, occured} ; } ;
                struct transmit_process_stoped_status_t       { enum enum_t  { offset=1, mask=1, not_occured=0, occured} ; } ;
                struct transmit_buffer_unavailable_status_t   { enum enum_t  { offset=2, mask=1, not_occured=0, occured} ; } ;
                struct transmit_jabber_timeout_status_t       { enum enum_t  { offset=3, mask=1, not_occured=0, occured} ; } ;
                struct overflow_status_t                      { enum enum_t  { offset=4, mask=1, not_occured=0, occured} ; } ;
                struct underflow_status_t                     { enum enum_t  { offset=5, mask=1, not_occured=0, occured} ; } ;
                struct receive_status_t                       { enum enum_t  { offset=6, mask=1, not_occured=0, occured} ; } ;
                struct receive_buffer_unavailable_status_t    { enum enum_t  { offset=7, mask=1, not_occured=0, occured} ; } ;
                struct receive_process_stopped_status_t       { enum enum_t  { offset=8, mask=1, not_occured=0, occured} ; } ;
                struct receive_watchdog_timeout_status_t      { enum enum_t  { offset=9, mask=1, not_occured=0, occured} ; } ;
                struct early_transmit_status_t                { enum enum_t  { offset=10,mask=1, not_occured=0, occured} ; } ;
                struct fatal_bus_error_status_t               { enum enum_t  { offset=13,mask=1, not_occured=0, occured} ; } ;
                struct early_receive_status_t                 { enum enum_t  { offset=14,mask=1, not_occured=0, occured} ; } ;
                struct abnormal_summary_status_t              { enum enum_t  { offset=15,mask=1, not_occured=0, occured} ; } ;
                struct normal_status_summary_status_t         { enum enum_t  { offset=16,mask=1, not_occured=0 , occured} ; } ;
                struct receive_process_state_t                { enum enum_t  { offset=17,mask=0b111, stoped=0, fetching_desctiptor, waiting_for_receive=3, descriptor_unavailable, closing_descriptor, writing_data_to_host_memory=7  } ; } ;
                struct transmit_process_state_t               { enum enum_t  { offset=20,mask=0b111, stoped=0, fetching_desctiptor, waiting_for_status, reading_data_from_host_memory, descriprtor_unavalable_or_buffer_overflow=6, closing_descriptor } ; } ;
                struct transfer_error_status_t                { enum enum_t  { offset=23,mask=1, rxdma=0, txdma } ; } ;
                struct io_error_status_t                      { enum enum_t  { offset=24,mask=1, write=0, read } ; } ;
                struct access_error_status_t                  { enum enum_t  { offset=25,mask=1, data_buffer=0, descriptor } ; } ;
                struct mmc_status_t                           { enum enum_t  { offset=27,mask=1, not_occured=0, occured} ; } ;
                struct pmt_status_t                           { enum enum_t  { offset=28,mask=1, not_occured=0, occured} ; } ;
                struct time_stamp_trigger_status_t            { enum enum_t  { offset=29,mask=1, not_occured=0, occured} ; } ;
             } ;

          inline  void receive_buffer_unavailable_status_clear(){  status.rmw(status_t::receive_buffer_unavailable_status_t::occured) ;}
          inline  auto receive_buffer_unavailable_status()const {  return status.rd<status_t::receive_buffer_unavailable_status_t>();}


          struct operation_mode_t : public read_write_32_eth_workarounds_t
             {
                struct reception_t                      { enum enum_t  { offset=1, mask=1, disable=0 , enable} ; } ;
                struct operate_second_frame_t           { enum enum_t  { offset=2, mask=1, disable=0 , enable} ; } ;
                struct receive_threshold_control_t      { enum enum_t  { offset=3, mask=0b11, level64=0, level32, level96, level128} ; } ;
                struct forward_undersized_good_frames_t { enum enum_t  { offset=6, mask=1, disable=0 , enable} ; } ;
                struct forward_error_frames_t           { enum enum_t  { offset=7, mask=1, disable=0 , enable} ; } ;
                struct transmittion_t                   { enum enum_t  { offset=13, mask=1, disable=0 , enable} ; } ;
                struct transmit_threshold_control_t     { enum enum_t  { offset=14, mask=0b111, level64=0, level128, level192, level256, level40, level32, level24, level16} ; } ;
                struct flush_tx_fifo_t                  { enum enum_t  { offset=20, mask=1, no_action=0 , action} ; } ;
                struct transmit_store_forward_t         { enum enum_t  { offset=21, mask=1, disable=0 , enable} ; } ;
                struct flushing_received_frames_t       { enum enum_t  { offset=24, mask=1, enable=0 , disable} ; } ;
                struct receive_store_forward_t          { enum enum_t  { offset=25, mask=1, disable=0 , enable} ; } ;
                struct dropping_tcp_ip_checksum_error_frames_t { enum enum_t  { offset=26, mask=1, enable=0 , disable} ; } ;
             } ;

          inline  void reception(const operation_mode_t::reception_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void reception_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::reception_t::disable) ;}
          inline  void reception_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::reception_t::enable) ;}
          inline  auto reception()const {  return operation_mode.rd<operation_mode_t::reception_t>();}

          inline  void operate_second_frame(const operation_mode_t::operate_second_frame_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void operate_second_frame_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::operate_second_frame_t::disable) ;}
          inline  void operate_second_frame_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::operate_second_frame_t::enable) ;}
          inline  auto operate_second_frame()const {  return operation_mode.rd<operation_mode_t::operate_second_frame_t>();}

          inline  void receive_threshold_control(const operation_mode_t::receive_threshold_control_t::enum_t val){  operation_mode.rmw(nop_while, 100,val);}
          inline  void receive_threshold_control_level64() {  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_threshold_control_t::level64) ;}
          inline  void receive_threshold_control_level32() {  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_threshold_control_t::level32) ;}
          inline  void receive_threshold_control_level96() {  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_threshold_control_t::level96) ;}
          inline  void receive_threshold_control_level128(){  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_threshold_control_t::level128);}
          inline  auto receive_threshold_control()const {  return operation_mode.rd<operation_mode_t::receive_threshold_control_t>();}

          inline  void forward_undersized_good_frames(const operation_mode_t::forward_undersized_good_frames_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void forward_undersized_good_frames_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::forward_undersized_good_frames_t::disable) ;}
          inline  void forward_undersized_good_frames_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::forward_undersized_good_frames_t::enable) ;}
          inline  auto forward_undersized_good_frames()const {  return operation_mode.rd<operation_mode_t::forward_undersized_good_frames_t>();}

          inline  void forward_error_frames(const operation_mode_t::forward_error_frames_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void forward_error_frames_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::forward_error_frames_t::disable) ;}
          inline  void forward_error_frames_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::forward_error_frames_t::enable) ;}
          inline  auto forward_error_frames()const {  return operation_mode.rd<operation_mode_t::forward_error_frames_t>();}

          inline  void transmittion(const operation_mode_t::transmittion_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void transmittion_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmittion_t::disable) ;}
          inline  void transmittion_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmittion_t::enable) ;}
          inline  auto transmittion()const {  return operation_mode.rd<operation_mode_t::transmittion_t>();}

          inline  void transmit_threshold_control(const operation_mode_t::transmit_threshold_control_t::enum_t val){  operation_mode.rmw(nop_while, 100,val);}
          inline  void transmit_threshold_control_level64() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level64) ;}
          inline  void transmit_threshold_control_level128(){  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level128) ;}
          inline  void transmit_threshold_control_level192(){  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level192) ;}
          inline  void transmit_threshold_control_level256(){  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level256) ;}
          inline  void transmit_threshold_control_level40() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level40) ;}
          inline  void transmit_threshold_control_level32() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level32) ;}
          inline  void transmit_threshold_control_level24() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level24) ;}
          inline  void transmit_threshold_control_level16() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_threshold_control_t::level16) ;}
          inline  auto transmit_threshold_control()const {  return operation_mode.rd<operation_mode_t::transmit_threshold_control_t>();}

          inline  void flush_tx_fifo() {  operation_mode.rmw( nop_while, 100, operation_mode_t::flush_tx_fifo_t::action) ;}
          inline  auto flush_tx_fifo_state()const {  return operation_mode.rd<operation_mode_t::flush_tx_fifo_t>();}
          inline  void flush_tx_fifo_wait()  { while( flush_tx_fifo_state() == operation_mode_t::flush_tx_fifo_t::action ) ; }

          inline  void transmit_store_forward(const operation_mode_t::transmit_store_forward_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void transmit_store_forward_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_store_forward_t::disable) ;}
          inline  void transmit_store_forward_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::transmit_store_forward_t::enable) ;}
          inline  auto transmit_store_forward()const {  return operation_mode.rd<operation_mode_t::transmit_store_forward_t>();}

          inline  void flushing_received_frames(const operation_mode_t::flushing_received_frames_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void flushing_received_frames_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::flushing_received_frames_t::disable) ;}
          inline  void flushing_received_frames_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::flushing_received_frames_t::enable) ;}
          inline  auto flushing_received_frames()const {  return operation_mode.rd<operation_mode_t::flushing_received_frames_t>();}

          inline  void receive_store_forward(const operation_mode_t::receive_store_forward_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void receive_store_forward_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_store_forward_t::disable) ;}
          inline  void receive_store_forward_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::receive_store_forward_t::enable) ;}
          inline  auto receive_store_forward()const {  return operation_mode.rd<operation_mode_t::receive_store_forward_t>();}

          inline  void dropping_tcp_ip_checksum_error_frames(const operation_mode_t::dropping_tcp_ip_checksum_error_frames_t::enum_t val){  operation_mode.rmw(nop_while, 100,val) ;}
          inline  void dropping_tcp_ip_checksum_error_frames_disable() {  operation_mode.rmw( nop_while, 100, operation_mode_t::dropping_tcp_ip_checksum_error_frames_t::disable) ;}
          inline  void dropping_tcp_ip_checksum_error_frames_enable()  {  operation_mode.rmw( nop_while, 100, operation_mode_t::dropping_tcp_ip_checksum_error_frames_t::enable) ;}
          inline  auto dropping_tcp_ip_checksum_error_frames()const {  return operation_mode.rd<operation_mode_t::dropping_tcp_ip_checksum_error_frames_t>();}

          struct interrupt_t : public read_write_32_t
             {
               struct transmit_interrupt_t       { enum enum_t  { offset=0, mask=1, disable=0 , enable} ; } ;
               struct transmit_process_stoped_interrupt_t       { enum enum_t  { offset=1, mask=1, disable=0 , enable} ; } ;
               struct transmit_buffer_unavailable_interrupt_t   { enum enum_t  { offset=2, mask=1, disable=0 , enable} ; } ;
               struct transmit_jabber_timeout_interrupt_t       { enum enum_t  { offset=3, mask=1, disable=0 , enable} ; } ;
               struct overflow_interrupt_t                      { enum enum_t  { offset=4, mask=1, disable=0 , enable} ; } ;
               struct underflow_interrupt_t                     { enum enum_t  { offset=5, mask=1, disable=0 , enable} ; } ;
               struct receive_interrupt_t                       { enum enum_t  { offset=6, mask=1, disable=0 , enable} ; } ;
               struct receive_buffer_unavailable_interrupt_t    { enum enum_t  { offset=7, mask=1, disable=0 , enable} ; } ;
               struct receive_process_stopped_interrupt_t       { enum enum_t  { offset=8, mask=1, disable=0 , enable} ; } ;
               struct receive_watchdog_timeout_interrupt_t      { enum enum_t  { offset=9, mask=1, disable=0 , enable} ; } ;
               struct early_transmit_interrupt_t                { enum enum_t  { offset=10, mask=1, disable=0 , enable} ; } ;
               struct fatal_bus_error_interrupt_t               { enum enum_t  { offset=13, mask=1, disable=0 , enable} ; } ;
               struct early_receive_interrupt_t                 { enum enum_t  { offset=14, mask=1, disable=0 , enable} ; } ;
               struct abnormal_summary_interrupt_t              { enum enum_t  { offset=15, mask=1, disable=0 , enable} ; } ;
               struct normal_interrupt_summary_interrupt_t      { enum enum_t  { offset=16, mask=1, disable=0 , enable} ; } ;
               struct mmc_interrupt_t                           { enum enum_t  { offset=27, mask=1, disable=0 , enable} ; } ;
               struct pmt_interrupt_t                           { enum enum_t  { offset=28, mask=1, disable=0 , enable} ; } ;
               struct time_stamp_trigger_interrupt_t            { enum enum_t  { offset=29, mask=1, disable=0 , enable} ; } ;
             } ;

          inline  void transmit_interrupt(const interrupt_t::transmit_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void transmit_interrupt_disable() {  interrupt.rmw(interrupt_t::transmit_interrupt_t::disable) ;}
          inline  void transmit_interrupt_enable() {  interrupt.rmw( interrupt_t::transmit_interrupt_t::enable) ;}
          inline  auto transmit_interrupt()const {  return interrupt.rd<interrupt_t::transmit_interrupt_t>();}

          inline  void transmit_process_stoped_interrupt(const interrupt_t::transmit_process_stoped_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void transmit_process_stoped_interrupt_disable() {  interrupt.rmw(interrupt_t::transmit_process_stoped_interrupt_t::disable) ;}
          inline  void transmit_process_stoped_interrupt_enable() {  interrupt.rmw( interrupt_t::transmit_process_stoped_interrupt_t::enable) ;}
          inline  auto transmit_process_stoped_interrupt()const {  return interrupt.rd<interrupt_t::transmit_process_stoped_interrupt_t>();}

          inline  void transmit_buffer_unavailable_interrupt(const interrupt_t::transmit_buffer_unavailable_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void transmit_buffer_unavailable_interrupt_disable() {  interrupt.rmw(interrupt_t::transmit_buffer_unavailable_interrupt_t::disable) ;}
          inline  void transmit_buffer_unavailable_interrupt_enable() {  interrupt.rmw( interrupt_t::transmit_buffer_unavailable_interrupt_t::enable) ;}
          inline  auto transmit_buffer_unavailable_interrupt()const {  return interrupt.rd<interrupt_t::transmit_buffer_unavailable_interrupt_t>();}

          inline  void transmit_jabber_timeout_interrupt(const interrupt_t::transmit_jabber_timeout_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void transmit_jabber_timeout_interrupt_disable() {  interrupt.rmw(interrupt_t::transmit_jabber_timeout_interrupt_t::disable) ;}
          inline  void transmit_jabber_timeout_interrupt_enable() {  interrupt.rmw( interrupt_t::transmit_jabber_timeout_interrupt_t::enable) ;}
          inline  auto transmit_jabber_timeout_interrupt()const {  return interrupt.rd<interrupt_t::transmit_jabber_timeout_interrupt_t>();}

          inline  void overflow_interrupt(const interrupt_t::overflow_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void overflow_interrupt_disable() {  interrupt.rmw(interrupt_t::overflow_interrupt_t::disable) ;}
          inline  void overflow_interrupt_enable() {  interrupt.rmw( interrupt_t::overflow_interrupt_t::enable) ;}
          inline  auto overflow_interrupt()const {  return interrupt.rd<interrupt_t::overflow_interrupt_t>();}

          inline  void underflow_interrupt(const interrupt_t::underflow_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void underflow_interrupt_disable() {  interrupt.rmw(interrupt_t::underflow_interrupt_t::disable) ;}
          inline  void underflow_interrupt_enable() {  interrupt.rmw( interrupt_t::underflow_interrupt_t::enable) ;}
          inline  auto underflow_interrupt()const {  return interrupt.rd<interrupt_t::underflow_interrupt_t>();}

          inline  void receive_interrupt(const interrupt_t::receive_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void receive_interrupt_disable() {  interrupt.rmw(interrupt_t::receive_interrupt_t::disable) ;}
          inline  void receive_interrupt_enable() {  interrupt.rmw( interrupt_t::receive_interrupt_t::enable) ;}
          inline  auto receive_interrupt()const {  return interrupt.rd<interrupt_t::receive_interrupt_t>();}

          inline  void receive_buffer_unavailable_interrupt(const interrupt_t::receive_buffer_unavailable_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void receive_buffer_unavailable_interrupt_disable() {  interrupt.rmw(interrupt_t::receive_buffer_unavailable_interrupt_t::disable) ;}
          inline  void receive_buffer_unavailable_interrupt_enable() {  interrupt.rmw( interrupt_t::receive_buffer_unavailable_interrupt_t::enable) ;}
          inline  auto receive_buffer_unavailable_interrupt()const {  return interrupt.rd<interrupt_t::receive_buffer_unavailable_interrupt_t>();}

          inline  void receive_process_stopped_interrupt(const interrupt_t::receive_process_stopped_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void receive_process_stopped_interrupt_disable() {  interrupt.rmw(interrupt_t::receive_process_stopped_interrupt_t::disable) ;}
          inline  void receive_process_stopped_interrupt_enable() {  interrupt.rmw( interrupt_t::receive_process_stopped_interrupt_t::enable) ;}
          inline  auto receive_process_stopped_interrupt()const {  return interrupt.rd<interrupt_t::receive_process_stopped_interrupt_t>();}

          inline  void receive_watchdog_timeout_interrupt(const interrupt_t::receive_watchdog_timeout_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void receive_watchdog_timeout_interrupt_disable() {  interrupt.rmw(interrupt_t::receive_watchdog_timeout_interrupt_t::disable) ;}
          inline  void receive_watchdog_timeout_interrupt_enable() {  interrupt.rmw( interrupt_t::receive_watchdog_timeout_interrupt_t::enable) ;}
          inline  auto receive_watchdog_timeout_interrupt()const {  return interrupt.rd<interrupt_t::receive_watchdog_timeout_interrupt_t>();}

          inline  void early_transmit_interrupt(const interrupt_t::early_transmit_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void early_transmit_interrupt_disable() {  interrupt.rmw(interrupt_t::early_transmit_interrupt_t::disable) ;}
          inline  void early_transmit_interrupt_enable() {  interrupt.rmw( interrupt_t::early_transmit_interrupt_t::enable) ;}
          inline  auto early_transmit_interrupt()const {  return interrupt.rd<interrupt_t::early_transmit_interrupt_t>();}

          inline  void fatal_bus_error_interrupt(const interrupt_t::fatal_bus_error_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void fatal_bus_error_interrupt_disable() {  interrupt.rmw(interrupt_t::fatal_bus_error_interrupt_t::disable) ;}
          inline  void fatal_bus_error_interrupt_enable() {  interrupt.rmw( interrupt_t::fatal_bus_error_interrupt_t::enable) ;}
          inline  auto fatal_bus_error_interrupt()const {  return interrupt.rd<interrupt_t::fatal_bus_error_interrupt_t>();}

          inline  void early_receive_interrupt(const interrupt_t::early_receive_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void early_receive_interrupt_disable() {  interrupt.rmw(interrupt_t::early_receive_interrupt_t::disable) ;}
          inline  void early_receive_interrupt_enable() {  interrupt.rmw( interrupt_t::early_receive_interrupt_t::enable) ;}
          inline  auto early_receive_interrupt()const {  return interrupt.rd<interrupt_t::early_receive_interrupt_t>();}

          inline  void abnormal_summary_interrupt(const interrupt_t::abnormal_summary_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void abnormal_summary_interrupt_disable() {  interrupt.rmw(interrupt_t::abnormal_summary_interrupt_t::disable) ;}
          inline  void abnormal_summary_interrupt_enable() {  interrupt.rmw( interrupt_t::abnormal_summary_interrupt_t::enable) ;}
          inline  auto abnormal_summary_interrupt()const {  return interrupt.rd<interrupt_t::abnormal_summary_interrupt_t>();}

          inline  void normal_interrupt_summary_interrupt(const interrupt_t::normal_interrupt_summary_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void normal_interrupt_summary_interrupt_disable() {  interrupt.rmw(interrupt_t::normal_interrupt_summary_interrupt_t::disable) ;}
          inline  void normal_interrupt_summary_interrupt_enable() {  interrupt.rmw( interrupt_t::normal_interrupt_summary_interrupt_t::enable) ;}
          inline  auto normal_interrupt_summary_interrupt()const {  return interrupt.rd<interrupt_t::normal_interrupt_summary_interrupt_t>();}

          inline  void mmc_interrupt(const interrupt_t::mmc_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void mmc_interrupt_disable() {  interrupt.rmw(interrupt_t::mmc_interrupt_t::disable) ;}
          inline  void mmc_interrupt_enable() {  interrupt.rmw( interrupt_t::mmc_interrupt_t::enable) ;}
          inline  auto mmc_interrupt()const {  return interrupt.rd<interrupt_t::mmc_interrupt_t>();}

          inline  void pmt_interrupt(const interrupt_t::pmt_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void pmt_interrupt_disable() {  interrupt.rmw(interrupt_t::pmt_interrupt_t::disable) ;}
          inline  void pmt_interrupt_enable() {  interrupt.rmw( interrupt_t::pmt_interrupt_t::enable) ;}
          inline  auto pmt_interrupt()const {  return interrupt.rd<interrupt_t::pmt_interrupt_t>();}

          inline  void time_stamp_trigger_interrupt(const interrupt_t::time_stamp_trigger_interrupt_t::enum_t val){  interrupt.rmw(val) ;}
          inline  void time_stamp_trigger_interrupt_disable() {  interrupt.rmw(interrupt_t::time_stamp_trigger_interrupt_t::disable) ;}
          inline  void time_stamp_trigger_interrupt_enable() {  interrupt.rmw( interrupt_t::time_stamp_trigger_interrupt_t::enable) ;}
          inline  auto time_stamp_trigger_interrupt()const {  return interrupt.rd<interrupt_t::time_stamp_trigger_interrupt_t>();}



          struct missed_frame_buffer_overflow_t : public read_write_32_t
             {} ;
          struct receive_status_watchdog_timer_t : public read_write_32_t
             {} ;

          bus_mode_t bus_mode; //*DMABMR;
          volatile uint32_t  transmit_poll_demand;//DMATPDR;
          volatile uint32_t  receive_poll_demand;//DMARPDR;
          volatile uint32_t  receive_descriptor_list_address; //DMARDLAR;
          volatile uint32_t  transmit_descriptor_list_address; //DMATDLAR;
          status_t status; //DMASR;
          operation_mode_t operation_mode;//*DMAOMR;
          interrupt_t interrupt;//DMAIER;
          missed_frame_buffer_overflow_t missed_frame_buffer_overflow_counter_t; //DMAMFBOCR;
          receive_status_watchdog_timer_t receive_status_watchdog_timer; //DMARSWTR;
          const uint32_t reserved[8];
          volatile uint32_t current_host_transmit_descriptor; //DMACHTDR;
          volatile uint32_t current_host_receive_descriptor; //DMACHRDR;
          volatile uint32_t current_host_transmit_buffer_address; //DMACHTBAR;
          volatile uint32_t current_host_receive_buffer_address; //DMACHRBAR;
       };

    // note: * - регистры требующие "кривой" записи для обхода аппаратной ошибки

    mac_t mac ;
    mmc_t mmc ;
    ptp_t ptp ;
    dma_t dma ;

    inline void clock_enable()     { rcc.eth_enable(); }
    inline void clock_tx_enable()  { rcc.eth_tx_enable(); }
    inline void clock_rx_enable()  { rcc.eth_rx_enable(); }
    inline void clock_ptp_enable() { rcc.eth_ptp_enable();}

    inline void clock_disable()    { rcc.eth_disable(); }
    inline void clock_tx_disable() { rcc.eth_tx_disable(); }
    inline void clock_rx_disable() { rcc.eth_rx_disable(); }
    inline void clock_ptp_disable(){ rcc.eth_ptp_disable();}

    inline void reset()            { rcc.eth_reset();}

    void init_rmii()
    {
      /*
       RMII_REF_CLK ----------------------> PA1
       RMII_MDIO -------------------------> PA2
       RMII_MII_CRS_DV -------------------> PA7
       RMII_MII_TXD1 ---------------------> PB13
       RMII_MDC --------------------------> PC1
       RMII_MII_RXD0 ---------------------> PC4
       RMII_MII_RXD1 ---------------------> PC5
       RMII_MII_RXER ---------------------> PG2
       RMII_MII_TX_EN --------------------> PG11
       RMII_MII_TXD0 ---------------------> PG13
     */

       gpioa.clock_enable();
       gpioa.pin( gpio_t::mode_t::pin1_t::alternate_function,
    	      gpio_t::mode_t::pin2_t::alternate_function,
              gpio_t::mode_t::pin7_t::alternate_function,
    	      gpio_t::pull_t::pin1_t::no,
    	      gpio_t::pull_t::pin2_t::no,
    	      gpio_t::pull_t::pin7_t::no,
    	      gpio_t::output_speed_t::pin1_t::very_high,
    	      gpio_t::output_speed_t::pin2_t::very_high,
    	      gpio_t::output_speed_t::pin3_t::very_high,
    	      gpioa_t::af_t::pin1_t::eth_mii_rx_clk_eth_rmii_ref_clk,
    	      gpioa_t::af_t::pin2_t::eth_mdio,
    	      gpioa_t::af_t::pin7_t::eth_mii_rx_dv_eth_rmii_crs_dv
    	    ) ;

      gpiob.clock_enable();
      gpiob.pin( gpio_t::mode_t::pin13_t::alternate_function,
      	     gpio_t::pull_t::pin13_t::no,
      	     gpio_t::output_speed_t::pin13_t::very_high,
      	     gpiob_t::af_t::pin13_t::eth_mii_txd1_eth_rmii_txd1
      	    ) ;

      gpioc.clock_enable();
      gpioc.pin( gpio_t::mode_t::pin1_t::alternate_function,
    	     gpio_t::mode_t::pin4_t::alternate_function,
    	     gpio_t::mode_t::pin5_t::alternate_function,
                 gpio_t::pull_t::pin1_t::no,
                 gpio_t::pull_t::pin4_t::no,
                 gpio_t::pull_t::pin5_t::no,
                 gpio_t::output_speed_t::pin1_t::very_high,
                 gpio_t::output_speed_t::pin4_t::very_high,
                 gpio_t::output_speed_t::pin5_t::very_high,
                 gpioc_t::af_t::pin1_t::eth_mdc,
                 gpioc_t::af_t::pin4_t::eth_mii_rxd0_eth_rmii_rxd0,
                 gpioc_t::af_t::pin5_t::eth_mii_rxd1_eth_rmii_rxd1
               ) ;

      gpiog.clock_enable();
      gpiog.pin( gpio_t::mode_t::pin11_t::alternate_function,
     	         gpio_t::mode_t::pin13_t::alternate_function,
                 gpio_t::pull_t::pin11_t::no,
                 gpio_t::pull_t::pin13_t::no,
                 gpio_t::output_speed_t::pin11_t::very_high,
                 gpio_t::output_speed_t::pin13_t::very_high,
                 gpiog_t::af_t::pin11_t::eth_mii_tx_en_eth_rmii_tx_en,
                 gpiog_t::af_t::pin13_t::eth_mii_txd0_eth_rmii_txd0
     	   ) ;

      nvic.eth_enable();
      nvic.eth_priority(0x80) ;

      rcc.eth_enable();
      rcc.eth_rx_enable();
      rcc.eth_tx_enable();

      syscfg.clock_enable();
      syscfg.ethernet_phy_rmii();

    }

    inline void phy_read(const uint8_t phy, const uint8_t reg, uint32_t *val)
    {
       mac.mii_address.modify( (eth_t::mac_t::mii_address_t::phy_t::enum_t)phy,
    			       (eth_t::mac_t::mii_address_t::register_t::enum_t)reg,
    			        eth_t::mac_t::mii_address_t::operation_t::read,
    			        eth_t::mac_t::mii_address_t::busy_t::operation_ongoing
    	                      );
       mac.mii_busy_wait();
       *val = mac.mii_data;

    }

    inline void phy_write(const uint8_t phy, const uint8_t reg, uint32_t val)
    {
       mac.mii_data = val ;
       mac.mii_address.modify( (eth_t::mac_t::mii_address_t::phy_t::enum_t)phy,
                               (eth_t::mac_t::mii_address_t::register_t::enum_t)reg,
                                eth_t::mac_t::mii_address_t::operation_t::write,
                                eth_t::mac_t::mii_address_t::busy_t::operation_ongoing
                             );
       mac.mii_busy_wait();
    }


    struct init_t
      {
        bool             auto_negotiation;
        mac_t::config_t::speed_t::enum_t          speed;
        mac_t::config_t::ipv4_checksum_offload_t::enum_t    ipv4_checksum_offload;
        mac_t::config_t::duplex_mode_t::enum_t    duplex_mode;
        uint16_t             PhyAddress;
        uint32_t             MediaInterface    ;
     } ;



  } ;

  static eth_t& eth   = *((eth_t*) eth_addr);

}

using namespace stm32 ;

#endif /* __ETHMAC_F4_F7++_H__ */
