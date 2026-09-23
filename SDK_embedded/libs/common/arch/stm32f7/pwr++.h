/*
 * rcc++.h
 *
 *  Created on: 30 окт. 2017 г.
 *      Author: klen
 */

#ifndef __PWR++_H__
#define __PWR++_H__

#include "types++.h"


namespace stm32f7
{

struct pwr_t
{
  struct power_control_1_t : public read_write_32_t
	{
	  	struct low_power_deepsleep_t { enum enum_t{ offset=0, mask=1, main_voltage_regulator=0 , lp_voltage_regulator };};
	  	struct power_down_deepsleep_t { enum enum_t{ offset=1, mask=1, enter_stop_mode=0 , enter_standby_mode };};
	  	struct clear_standby_flag_t { enum enum_t{ offset=3, mask=1, no_effect=0 , clear };};
	  	struct power_voltage_detector_t { enum enum_t{ offset=4, mask=1, disable=0 , enable };};
	  	struct power_voltage_detector_level_t { enum enum_t{ offset=5, mask=0b111, v20=0 , v21, v23, v25, v26, v27, v28, v29 };};
	  	struct backup_domain_access_t { enum enum_t{ offset=8, mask=1, disable=0 , enable };};
	  	struct flash_in_stop_mode_t  { enum enum_t{ offset=9, mask=1, normal=0 , power_down };};
	  	struct low_power_regulator_in_deepsleep_mode_t  { enum enum_t{ offset=10, mask=1, stop=0 , under_drive };};
	  	struct main_regulator_in_deepsleep_mode_t  { enum enum_t{ offset=11, mask=1, stop=0 , under_drive };};
	  	struct adcdc1_t  { enum enum_t{ offset=13, mask=1, disable=0 , enable };};
	  	struct regulator_voltage_scale_t  { enum enum_t{ offset=14, mask=0b11, scale3=1, scale2, scale1, };};
	  	struct over_drive_t  { enum enum_t{ offset=16, mask=1, disable=0 , enable };};
	  	struct over_drive_switching_t  { enum enum_t{ offset=17, mask=1, disable=0 , enable };};
	  	struct under_drive_in_stop_mode_t  { enum enum_t{ offset=18, mask=0b11, disable=0 , enable=0b11 };};
	};

  inline  void low_power_deepsleep(const power_control_1_t::low_power_deepsleep_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void low_power_deepsleep_main_voltage_regulator() {  power_control_1.rmw( power_control_1_t::low_power_deepsleep_t::main_voltage_regulator) ;}
  inline  void low_power_deepsleep_lp_voltage_regulator() {  power_control_1.rmw( power_control_1_t::low_power_deepsleep_t::lp_voltage_regulator) ;}
  inline  auto low_power_deepsleep()const {  return power_control_1.rd<power_control_1_t::low_power_deepsleep_t>();}

  inline  void power_down_deepsleep(const power_control_1_t::power_down_deepsleep_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void power_down_deepsleep_enter_stop_mode() {  power_control_1.rmw( power_control_1_t::power_down_deepsleep_t::enter_stop_mode) ;}
  inline  void power_down_deepsleep_enter_standby_mode() {  power_control_1.rmw( power_control_1_t::power_down_deepsleep_t::enter_standby_mode) ;}
  inline  auto power_down_deepsleep()const {  return power_control_1.rd<power_control_1_t::power_down_deepsleep_t>();}

  inline  void clear_standby_flag() {  power_control_1.rmw( power_control_1_t::clear_standby_flag_t::clear) ;}

  inline  void power_voltage_detector(const power_control_1_t::power_voltage_detector_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void power_voltage_detector_disable() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_t::disable) ;}
  inline  void power_voltage_detector_enable() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_t::enable) ;}
  inline  auto power_voltage_detector()const {  return power_control_1.rd<power_control_1_t::power_voltage_detector_t>();}

  inline  void power_voltage_detector_level(const power_control_1_t::power_voltage_detector_level_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void power_voltage_detector_level_2v0() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v20) ;}
  inline  void power_voltage_detector_level_2v1() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v21) ;}
  inline  void power_voltage_detector_level_2v3() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v23) ;}
  inline  void power_voltage_detector_level_2v5() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v25) ;}
  inline  void power_voltage_detector_level_2v6() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v26) ;}
  inline  void power_voltage_detector_level_2v7() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v27) ;}
  inline  void power_voltage_detector_level_2v8() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v28) ;}
  inline  void power_voltage_detector_level_2v9() {  power_control_1.rmw( power_control_1_t::power_voltage_detector_level_t::v29) ;}
  inline  auto power_voltage_detector_level()const {  return power_control_1.rd<power_control_1_t::power_voltage_detector_level_t>();}

  inline  void backup_domain_access(const power_control_1_t::backup_domain_access_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void backup_domain_access_disable() {  power_control_1.rmw( power_control_1_t::backup_domain_access_t::disable) ;}
  inline  void backup_domain_access_enable() {  power_control_1.rmw( power_control_1_t::backup_domain_access_t::enable) ;}
  inline  auto backup_domain_access()const {  return power_control_1.rd<power_control_1_t::backup_domain_access_t>();}

  inline  void flash_in_stop_mode(const power_control_1_t::flash_in_stop_mode_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void flash_in_stop_mode_normal() {  power_control_1.rmw( power_control_1_t::flash_in_stop_mode_t::normal) ;}
  inline  void flash_in_stop_mode_power_down() {  power_control_1.rmw( power_control_1_t::flash_in_stop_mode_t::power_down) ;}
  inline  auto flash_in_stop_mode()const {  return power_control_1.rd<power_control_1_t::flash_in_stop_mode_t>();}

  inline  void low_power_regulator_in_deepsleep_mode(const power_control_1_t::low_power_regulator_in_deepsleep_mode_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void low_power_regulator_in_deepsleep_mode_stop() {  power_control_1.rmw( power_control_1_t::low_power_regulator_in_deepsleep_mode_t::stop) ;}
  inline  void low_power_regulator_in_deepsleep_mode_under_drive() {  power_control_1.rmw( power_control_1_t::low_power_regulator_in_deepsleep_mode_t::under_drive) ;}
  inline  auto low_power_regulator_in_deepsleep_mode()const {  return power_control_1.rd<power_control_1_t::low_power_regulator_in_deepsleep_mode_t>();}

  inline  void main_regulator_in_deepsleep_mode(const power_control_1_t::main_regulator_in_deepsleep_mode_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void main_regulator_in_deepsleep_mode_stop() {  power_control_1.rmw( power_control_1_t::main_regulator_in_deepsleep_mode_t::stop) ;}
  inline  void main_regulator_in_deepsleep_mode_under_drive() {  power_control_1.rmw( power_control_1_t::main_regulator_in_deepsleep_mode_t::under_drive) ;}
  inline  auto main_regulator_in_deepsleep_mode()const {  return power_control_1.rd<power_control_1_t::main_regulator_in_deepsleep_mode_t>();}

  inline  void adcdc1(const power_control_1_t::adcdc1_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void adcdc1_enable() {  power_control_1.rmw( power_control_1_t::adcdc1_t::disable) ;}
  inline  void adcdc1_disable() {  power_control_1.rmw( power_control_1_t::adcdc1_t::enable) ;}
  inline  auto adcdc1()const {  return power_control_1.rd<power_control_1_t::adcdc1_t>();}

  inline  void regulator_voltage_scale(const power_control_1_t::regulator_voltage_scale_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void regulator_voltage_scale1() {  power_control_1.rmw( power_control_1_t::regulator_voltage_scale_t::scale1) ;}
  inline  void regulator_voltage_scale2() {  power_control_1.rmw( power_control_1_t::regulator_voltage_scale_t::scale2) ;}
  inline  void regulator_voltage_scale3() {  power_control_1.rmw( power_control_1_t::regulator_voltage_scale_t::scale3) ;}
  inline  auto regulator_voltage_scale()const {  return power_control_1.rd<power_control_1_t::regulator_voltage_scale_t>();}

  inline  void over_drive(const power_control_1_t::over_drive_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void over_drive_disable() {  power_control_1.rmw( power_control_1_t::over_drive_t::disable) ;}
  inline  void over_drive_enable() {  power_control_1.rmw( power_control_1_t::over_drive_t::enable) ;}
  inline  auto over_drive()const {  return power_control_1.rd<power_control_1_t::over_drive_t>();}

  inline  void over_drive_switching(const power_control_1_t::over_drive_switching_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void over_drive_switching_disable() {  power_control_1.rmw( power_control_1_t::over_drive_switching_t::disable) ;}
  inline  void over_drive_switching_enable() {  power_control_1.rmw( power_control_1_t::over_drive_switching_t::enable) ;}
  inline  auto over_drive_switching()const {  return power_control_1.rd<power_control_1_t::over_drive_switching_t>();}

  inline  void under_drive_in_stop_mode(const power_control_1_t::under_drive_in_stop_mode_t::enum_t val){  power_control_1.rmw(val) ;}
  inline  void under_drive_in_stop_mode_disable() {  power_control_1.rmw( power_control_1_t::under_drive_in_stop_mode_t::disable) ;}
  inline  void under_drive_in_stop_mode_enable() {  power_control_1.rmw( power_control_1_t::under_drive_in_stop_mode_t::enable) ;}
  inline  auto under_drive_in_stop_mode()const {  return power_control_1.rd<power_control_1_t::under_drive_in_stop_mode_t>();}

  struct power_control_status_1_t : public read_write_32_t
	{
	  struct wakeup_internal_flag_t   { enum enum_t{ offset=0, mask=1, no_occurred=0 , occurred };};
	  struct standby_flag_t           { enum enum_t{ offset=1, mask=1, no_occurred=0 , occurred };};
	  struct pvd_output_flag_t        { enum enum_t{ offset=2, mask=1, vdd_higher_pvd_threshold=0 , vdd_lower_pvd_threshold };};
	  struct backup_regulator_flag_t  { enum enum_t{ offset=3, mask=1, not_ready=0 , ready };};
	  struct backup_regulator_t       { enum enum_t{ offset=9, mask=1, disable=0 , enable };};
	  struct regulator_voltage_scale_output_selection_ready_t { enum enum_t{ offset=14, mask=1, not_ready=0 , ready }; };
	  struct over_drive_mode_ready_t  { enum enum_t{ offset=16, mask=1, not_ready=0 , ready }; };
	  struct over_drive_mode_switching_active_t   { enum enum_t{ offset=17, mask=1, not_active=0 , active }; };
	  struct over_drive_flag_t        { enum enum_t{ offset=17, mask=1, disabled=0 , activated_in_stop_mode }; };
	};

  inline  auto wakeup_internal_flag() const {  return power_control_status_1.rd<power_control_status_1_t::wakeup_internal_flag_t>();}
  inline  auto standby_flag() const {  return power_control_status_1.rd<power_control_status_1_t::standby_flag_t>();}
  inline  auto pvd_output_flag() const {  return power_control_status_1.rd<power_control_status_1_t::pvd_output_flag_t>();}
  inline  auto backup_regulator_flag() const {  return power_control_status_1.rd<power_control_status_1_t::backup_regulator_flag_t>();}

  inline  void backup_regulator(const power_control_status_1_t::backup_regulator_t::enum_t val){  power_control_status_1.rmw(val) ;}
  inline  void backup_regulator_disable() {  power_control_status_1.rmw( power_control_status_1_t::backup_regulator_t::disable) ;}
  inline  void backup_regulator_enable() {  power_control_status_1.rmw( power_control_status_1_t::backup_regulator_t::enable) ;}
  inline  auto backup_regulator()const {  return power_control_status_1.rd<power_control_status_1_t::backup_regulator_t>();}

  inline  auto regulator_voltage_scale_output_selection_ready() const {  return power_control_status_1.rd<power_control_status_1_t::regulator_voltage_scale_output_selection_ready_t>();}
  inline  void wait_regulator_voltage_scale_output_selection_ready() const {  while(regulator_voltage_scale_output_selection_ready()==power_control_status_1_t::regulator_voltage_scale_output_selection_ready_t::not_ready) {} ; }

  inline  auto over_drive_mode_ready() const {  return power_control_status_1.rd<power_control_status_1_t::over_drive_mode_ready_t>();}
  inline  void wait_over_drive_mode_ready() const { while( over_drive_mode_ready() == power_control_status_1_t::over_drive_mode_ready_t::not_ready ) {} ; }

  inline  auto over_drive_mode_switching_active() const {  return power_control_status_1.rd<power_control_status_1_t::over_drive_mode_switching_active_t>();}
  inline  void wait_over_drive_mode_switching_active() const { while( over_drive_mode_switching_active() == power_control_status_1_t::over_drive_mode_switching_active_t::not_active ) {} ; }

  inline  auto over_drive_flag() const {  return power_control_status_1.rd<power_control_status_1_t::over_drive_flag_t>();}
  inline  void over_drive_flag_clear() {  power_control_status_1.rmw( power_control_status_1_t::over_drive_flag_t::activated_in_stop_mode) ;}

  struct power_control_2_t : public read_write_32_t
	{
	  struct pa0_pin_wakeup_clear_t   { enum enum_t{ offset=0, mask=1, no_effect=0 , clear };};
	  struct pa2_pin_wakeup_clear_t   { enum enum_t{ offset=1, mask=1, no_effect=0 , clear };};
	  struct pc1_pin_wakeup_clear_t   { enum enum_t{ offset=2, mask=1, no_effect=0 , clear };};
	  struct pc13_pin_wakeup_clear_t  { enum enum_t{ offset=3, mask=1, no_effect=0 , clear };};
	  struct pi8_pin_wakeup_clear_t   { enum enum_t{ offset=4, mask=1, no_effect=0 , clear };};
	  struct pi11_pin_wakeup_clear_t  { enum enum_t{ offset=5, mask=1, no_effect=0 , clear };};

	  struct pa0_pin_wakeup_polarity_t   { enum enum_t{ offset=8, mask=1, rising_edge=0 , falling_edge };};
	  struct pa2_pin_wakeup_polarity_t   { enum enum_t{ offset=9, mask=1, rising_edge=0 , falling_edge };};
	  struct pc1_pin_wakeup_polarity_t   { enum enum_t{ offset=10, mask=1, rising_edge=0 , falling_edge };};
	  struct pc13_pin_wakeup_polarity_t  { enum enum_t{ offset=11, mask=1, rising_edge=0 , falling_edge };};
	  struct pi8_pin_wakeup_polarity_t   { enum enum_t{ offset=12, mask=1, rising_edge=0 , falling_edge };};
	  struct pi11_pin_wakeup_polarity_t  { enum enum_t{ offset=13, mask=1, rising_edge=0 , falling_edge };};
	};


  inline  void pa0_pin_wakeup_clear() {  power_control_2.rmw( power_control_2_t::pa0_pin_wakeup_clear_t::clear) ;}
  inline  void pa2_pin_wakeup_clear() {  power_control_2.rmw( power_control_2_t::pa2_pin_wakeup_clear_t::clear) ;}
  inline  void pc1_pin_wakeup_clear() {  power_control_2.rmw( power_control_2_t::pc1_pin_wakeup_clear_t::clear) ;}
  inline  void pc13_pin_wakeup_clear(){  power_control_2.rmw( power_control_2_t::pc13_pin_wakeup_clear_t::clear) ;}
  inline  void pi8_pin_wakeup_clear() {  power_control_2.rmw( power_control_2_t::pi8_pin_wakeup_clear_t::clear) ;}
  inline  void pi11_pin_wakeup_clear(){  power_control_2.rmw( power_control_2_t::pi11_pin_wakeup_clear_t::clear) ;}

  inline  void pa0_pin_wakeup_polarity(const power_control_2_t::pa0_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pa0_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pa0_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pa0_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pa0_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pa0_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pa0_pin_wakeup_polarity_t>();}

  inline  void pa2_pin_wakeup_polarity(const power_control_2_t::pa2_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pa2_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pa2_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pa2_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pa2_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pa2_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pa2_pin_wakeup_polarity_t>();}

  inline  void pc1_pin_wakeup_polarity(const power_control_2_t::pc1_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pc1_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pc1_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pc1_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pc1_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pc1_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pc1_pin_wakeup_polarity_t>();}

  inline  void pc13_pin_wakeup_polarity(const power_control_2_t::pc13_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pc13_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pc13_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pc13_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pc13_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pc13_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pc13_pin_wakeup_polarity_t>();}

  inline  void pi8_pin_wakeup_polarity(const power_control_2_t::pi8_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pi8_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pi8_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pi8_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pi8_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pi8_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pi8_pin_wakeup_polarity_t>();}

  inline  void pi11_pin_wakeup_polarity(const power_control_2_t::pi11_pin_wakeup_polarity_t::enum_t val){  power_control_2.rmw(val) ;}
  inline  void pi11_pin_wakeup_polarity_rising_edge() {  power_control_2.rmw( power_control_2_t::pi11_pin_wakeup_polarity_t::rising_edge) ;}
  inline  void pi11_pin_wakeup_polarity_falling_edge() {  power_control_2.rmw( power_control_2_t::pi11_pin_wakeup_polarity_t::falling_edge) ;}
  inline  auto pi11_pin_wakeup_polarity()const {  return power_control_2.rd<power_control_2_t::pi11_pin_wakeup_polarity_t>();}

  struct power_control_status_2_t : public read_write_32_t
	{
	  struct pa0_pin_wakeup_event_t   { enum enum_t{ offset=0, mask=1, no_occurred=0 , occurred };};
	  struct pa2_pin_wakeup_event_t   { enum enum_t{ offset=1, mask=1, no_occurred=0 , occurred };};
	  struct pc1_pin_wakeup_event_t   { enum enum_t{ offset=2, mask=1, no_occurred=0 , occurred };};
	  struct pc13_pin_wakeup_event_t  { enum enum_t{ offset=3, mask=1, no_occurred=0 , occurred };};
	  struct pi8_pin_wakeup_event_t   { enum enum_t{ offset=4, mask=1, no_occurred=0 , occurred };};
	  struct pi11_pin_wakeup_event_t  { enum enum_t{ offset=5, mask=1, no_occurred=0 , occurred };};

	  struct pa0_pin_wakeup_t   { enum enum_t{ offset=8, mask=1, disable=0 , enable };};
	  struct pa2_pin_wakeup_t   { enum enum_t{ offset=9, mask=1, disable=0 , enable };};
	  struct pc1_pin_wakeup_t   { enum enum_t{ offset=10, mask=1, disable=0 , enable };};
	  struct pc13_pin_wakeup_t  { enum enum_t{ offset=11, mask=1, disable=0 , enable };};
	  struct pi8_pin_wakeup_t   { enum enum_t{ offset=12, mask=1, disable=0 , enable };};
	  struct pi11_pin_wakeup_t  { enum enum_t{ offset=13, mask=1, disable=0 , enable };};
	};

  inline  auto pa0_pin_wakeup_event()   const {  return power_control_status_2.rd<power_control_status_2_t::pa0_pin_wakeup_event_t>();}
  inline  auto pa2_pin_wakeup_event()   const {  return power_control_status_2.rd<power_control_status_2_t::pa2_pin_wakeup_event_t>();}
  inline  auto pc1_pin_wakeup_event_t() const {  return power_control_status_2.rd<power_control_status_2_t::pc1_pin_wakeup_event_t>();}
  inline  auto pc13_pin_wakeup_event_t()const {  return power_control_status_2.rd<power_control_status_2_t::pc13_pin_wakeup_event_t>();}
  inline  auto pi8_pin_wakeup_event_t() const {  return power_control_status_2.rd<power_control_status_2_t::pi8_pin_wakeup_event_t>();}
  inline  auto pi11_pin_wakeup_event_t()const {  return power_control_status_2.rd<power_control_status_2_t::pi11_pin_wakeup_event_t>();}

  inline  void pa0_pin_wakeup(const power_control_status_2_t::pa0_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pa0_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pa0_pin_wakeup_t::disable) ;}
  inline  void pa0_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pa0_pin_wakeup_t::enable) ;}
  inline  auto pa0_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pa0_pin_wakeup_t>();}

  inline  void pa2_pin_wakeup(const power_control_status_2_t::pa2_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pa2_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pa2_pin_wakeup_t::disable) ;}
  inline  void pa2_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pa2_pin_wakeup_t::enable) ;}
  inline  auto pa2_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pa2_pin_wakeup_t>();}

  inline  void pc1_pin_wakeup(const power_control_status_2_t::pc1_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pc1_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pc1_pin_wakeup_t::disable) ;}
  inline  void pc1_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pc1_pin_wakeup_t::enable) ;}
  inline  auto pc1_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pc1_pin_wakeup_t>();}

  inline  void pc13_pin_wakeup(const power_control_status_2_t::pc13_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pc13_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pc13_pin_wakeup_t::disable) ;}
  inline  void pc13_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pc13_pin_wakeup_t::enable) ;}
  inline  auto pc13_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pc13_pin_wakeup_t>();}

  inline  void pi8_pin_wakeup(const power_control_status_2_t::pi8_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pi8_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pi8_pin_wakeup_t::disable) ;}
  inline  void pi8_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pi8_pin_wakeup_t::enable) ;}
  inline  auto pi8_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pi8_pin_wakeup_t>();}

  inline  void pi11_pin_wakeup(const power_control_status_2_t::pi11_pin_wakeup_t::enum_t val){  power_control_status_2.rmw(val) ;}
  inline  void pi11_pin_wakeup_disable() {  power_control_status_2.rmw( power_control_status_2_t::pi11_pin_wakeup_t::disable) ;}
  inline  void pi11_pin_wakeup_enable() {  power_control_status_2.rmw( power_control_status_2_t::pi11_pin_wakeup_t::enable) ;}
  inline  auto pi11_pin_wakeup()const {  return power_control_status_2.rd<power_control_status_2_t::pi11_pin_wakeup_t>();}

  power_control_1_t        power_control_1 ;       // CR1;   /*!< PWR power control register 1,        Address offset: 0x00 */
  power_control_status_1_t power_control_status_1; // CSR1;  /*!< PWR power control/status register 2, Address offset: 0x04 */
  power_control_2_t        power_control_2 ;       // CR2;   /*!< PWR power control register 2,        Address offset: 0x08 */
  power_control_status_2_t power_control_status_2; // CSR2;  /*!< PWR power control/status register 2, Address offset: 0x0C */
};

static pwr_t& pwr   = *((pwr_t*) pwr_addr);

}  // stm32f7

using namespace stm32f7 ;

#endif /* __PWR++_H__ */
