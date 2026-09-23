/*
 * rcc++.h
 *
 *  Created on: 8 дек. 2018 г.
 *      Author: klen
 */

#ifndef __PWR++_H__
#define __PWR++_H__

#include "types++.h"


namespace stm32l0
{

struct pwr_t
  {
    // RM0090 DocID018909 Rev 13 141/1748

    struct control_t : public read_write_32_t
      {
       struct low_power_deepsleep_t            { enum enum_t { offset=0, mask=1, disable=0, enable} ; } ;
       struct power_down_deepsleep_t           { enum enum_t { offset=1, mask=1, stop_mode=0, standby_mode  } ; } ;
       struct clear_wakeup_flag_t              { enum enum_t { offset=2, mask=1, clear=1  } ; } ;
       struct clear_standby_flag_t             { enum enum_t { offset=3, mask=1, clear=1  } ; } ;
       struct power_voltage_detector_t         { enum enum_t { offset=4, mask=1, disable=0, enable } ; } ;
       struct power_voltage_level_selection_t  { enum enum_t { offset=5, mask=0b111, threshold_1_9v=0, threshold_2_1v, threshold_2_3v, threshold_2_5v, threshold_2_7v, threshold_2_9v, threshold_3_1v, external_input_analog  } ; } ;
       struct backup_domain_write_protection_t { enum enum_t { offset=8, mask=1, disable=0, enable } ; } ;
       struct vref_internal_in_low_power_t     { enum enum_t { offset=9, mask=1, enable=0, disable } ; } ;
       struct fast_wakeup_t                    { enum enum_t { offset=10,mask=1, disable=0, enable } ; } ;
       struct regulator_voltage_scaling_t      { enum enum_t { offset=11,mask=0b11, range_1=1, range_2, range_3  } ; } ;
       struct deepsleep_nvm_kept_off_t         { enum enum_t { offset=13,mask=1, disable=0, enable  } ; } ;
       struct low_power_run_mode_t             { enum enum_t { offset=14,mask=1, voltage_regulator_main=0, voltage_regulator_low_power  } ; } ;
       struct low_power_deep_sleep_mode_t      { enum enum_t { offset=16,mask=1, voltage_regulator_main=0, voltage_regulator_low_power  } ; } ;
      };

    inline void low_power_deepsleep(const control_t::low_power_deepsleep_t::enum_t val) { control.rmw(val);}
    inline void low_power_deepsleep_disable()  { control.rmw(control_t::low_power_deepsleep_t::disable); }
    inline void low_power_deepsleep_enable()   { control.rmw(control_t::low_power_deepsleep_t::enable); }
    inline auto low_power_deepsleep() const {  return control.rd<control_t::low_power_deepsleep_t> ();}

    inline void power_down_deepsleep(const control_t::power_down_deepsleep_t::enum_t val) { control.rmw(val);}
    inline void power_down_deepsleep_stop_mode()      { control.rmw(control_t::power_down_deepsleep_t::stop_mode); }
    inline void power_down_deepsleep_standby_mode()   { control.rmw(control_t::power_down_deepsleep_t::standby_mode); }
    inline auto power_down_deepsleep() const {  return control.rd<control_t::power_down_deepsleep_t> ();}

    inline void wakeup_flag_clear() { control.rmw(control_t::clear_wakeup_flag_t::clear); }

    inline void standby_flag_clear() { control.rmw(control_t::clear_standby_flag_t::clear); }

    inline void power_voltage_detector(const control_t::power_voltage_detector_t::enum_t val) { control.rmw(val);}
    inline void power_voltage_detector_disable()  { control.rmw(control_t::power_voltage_detector_t::disable); }
    inline void power_voltage_detector_enable()   { control.rmw(control_t::power_voltage_detector_t::enable); }
    inline auto power_voltage_detector() const {  return control.rd<control_t::power_voltage_detector_t> ();}

    inline void power_voltage_level_selection(const control_t::power_voltage_level_selection_t::enum_t val) { control.rmw(val);}
    inline void power_voltage_level_selection_threshold_1_9v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_1_9v); }
    inline void power_voltage_level_selection_threshold_2_1v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_1v); }
    inline void power_voltage_level_selection_threshold_2_3v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_3v); }
    inline void power_voltage_level_selection_threshold_2_5v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_5v); }
    inline void power_voltage_level_selection_threshold_2_7v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_7v); }
    inline void power_voltage_level_selection_threshold_2_9v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_9v); }
    inline void power_voltage_level_selection_threshold_3_1v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_3_1v); }
    inline void power_voltage_level_selection_threshold_external_input_analog()  { control.rmw(control_t::power_voltage_level_selection_t::external_input_analog); }
    inline auto power_voltage_level_selection() const {  return control.rd<control_t::power_voltage_level_selection_t> ();}

    inline void backup_domain_write_protection(const control_t::backup_domain_write_protection_t::enum_t val) { control.rmw(val);}
    inline void backup_domain_write_protection_disable()  { control.rmw(control_t::backup_domain_write_protection_t::disable); }
    inline void backup_domain_write_protection_enable()   { control.rmw(control_t::backup_domain_write_protection_t::enable); }
    inline auto backup_domain_write_protection() const {  return control.rd<control_t::backup_domain_write_protection_t> ();}

    inline void vref_internal_in_low_power(const control_t::vref_internal_in_low_power_t::enum_t val) { control.rmw(val);}
    inline void vref_internal_in_low_power_disable()  { control.rmw(control_t::vref_internal_in_low_power_t::disable); }
    inline void vref_internal_in_low_power_enable()   { control.rmw(control_t::vref_internal_in_low_power_t::enable); }
    inline auto vref_internal_in_low_power() const {  return control.rd<control_t::vref_internal_in_low_power_t> ();}

    inline void fast_wakeup(const control_t::fast_wakeup_t::enum_t val) { control.rmw(val);}
    inline void fast_wakeup_disable()  { control.rmw(control_t::fast_wakeup_t::disable); }
    inline void fast_wakeup_enable()   { control.rmw(control_t::fast_wakeup_t::enable); }
    inline auto fast_wakeup() const {  return control.rd<control_t::fast_wakeup_t> ();}


    inline void regulator_voltage_scaling(const control_t::regulator_voltage_scaling_t::enum_t val) { control.rmw(val);}
    inline void regulator_voltage_scaling_range_1() { control.rmw(control_t::regulator_voltage_scaling_t::range_1); }
    inline void regulator_voltage_scaling_range_2() { control.rmw(control_t::regulator_voltage_scaling_t::range_2); }
    inline void regulator_voltage_scaling_range_3() { control.rmw(control_t::regulator_voltage_scaling_t::range_3); }
    inline auto regulator_voltage_scaling() const {  return control.rd<control_t::regulator_voltage_scaling_t> ();}

    inline void deepsleep_nvm_kept_off(const control_t::deepsleep_nvm_kept_off_t::enum_t val) { control.rmw(val);}
    inline void deepsleep_nvm_kept_off_disable()  { control.rmw(control_t::deepsleep_nvm_kept_off_t::disable); }
    inline void deepsleep_nvm_kept_off_enable()   { control.rmw(control_t::deepsleep_nvm_kept_off_t::enable); }
    inline auto deepsleep_nvm_kept_off() const {  return control.rd<control_t::deepsleep_nvm_kept_off_t> ();}

    inline void low_power_run_mode(const control_t::low_power_run_mode_t::enum_t val) { control.rmw(val);}
    inline void low_power_run_mode_voltage_regulator_main()  { control.rmw(control_t::low_power_run_mode_t::voltage_regulator_main); }
    inline void low_power_run_mode_voltage_regulator_low_power()   { control.rmw(control_t::low_power_run_mode_t::voltage_regulator_low_power); }
    inline auto low_power_run_mode() const {  return control.rd<control_t::low_power_run_mode_t> ();}

    inline void low_power_deep_sleep_mode(const control_t::low_power_deep_sleep_mode_t::enum_t val) { control.rmw(val);}
    inline void low_power_deep_sleep_mode_voltage_regulator_main()  { control.rmw(control_t::low_power_deep_sleep_mode_t::voltage_regulator_main); }
    inline void low_power_deep_sleep_mode_voltage_regulator_low_power()   { control.rmw(control_t::low_power_deep_sleep_mode_t::voltage_regulator_low_power); }
    inline auto low_power_deep_sleep_mode() const {  return control.rd<control_t::low_power_deep_sleep_mode_t> ();}

    struct control_and_status_t : public read_write_32_t
      {
       struct wakeup_flag_t                    { enum enum_t { offset=0, mask=1, not_occurred=0, occurred  } ; } ;
       struct standby_flag_t                   { enum enum_t { offset=1, mask=1, not_occurred=0, occurred  } ; } ;
       struct power_voltage_detector_output_t  { enum enum_t { offset=2, mask=1, higher=0, lower } ; } ;
       struct vrefint_ready_t                  { enum enum_t { offset=3, mask=1, not_ready=0, ready } ; } ;
       struct voltage_scaling_select_ready_t   { enum enum_t { offset=4, mask=1, ready=0, not_ready } ; } ;
       struct regulator_low_power_flag_t       { enum enum_t { offset=5, mask=1, not_occurred=0, occurred } ; } ;

       struct wkup_pin_1_t                       { enum enum_t { offset=8, mask=1, disable=0, enable } ; } ;
       struct wkup_pin_2_t                       { enum enum_t { offset=9, mask=1, disable=0, enable } ; } ;
       struct wkup_pin_3_t                       { enum enum_t { offset=10, mask=1, disable=0, enable } ; } ;
      };

    inline auto wakeup_flag() const {  return control_and_status.rd<control_and_status_t::wakeup_flag_t> ();}

    inline auto standby_flag() const {  return control_and_status.rd<control_and_status_t::standby_flag_t> ();}

    inline auto power_voltage_detector_output() const {  return control_and_status.rd<control_and_status_t::power_voltage_detector_output_t> ();}

    inline auto vrefint_ready() const {  return control_and_status.rd<control_and_status_t::vrefint_ready_t> ();}
    inline auto vrefint_ready_wait() const {  while(vrefint_ready() == control_and_status_t::vrefint_ready_t::not_ready  ) {} }

    inline auto voltage_scaling_select_ready() const {  return control_and_status.rd<control_and_status_t::voltage_scaling_select_ready_t> ();}
    inline auto voltage_scaling_select_ready_wait() const {  while(voltage_scaling_select_ready() == control_and_status_t::voltage_scaling_select_ready_t::not_ready  ) {} }

    inline auto regulator_low_power_flag() const {  return control_and_status.rd<control_and_status_t::regulator_low_power_flag_t> ();}

    inline void wkup_pin_1(const control_and_status_t::wkup_pin_1_t::enum_t val) { control_and_status.rmw(val);}
    inline void wkup_pin_1_disable()  { control_and_status.rmw(control_and_status_t::wkup_pin_1_t::disable); }
    inline void wkup_pin_1_enable()   { control_and_status.rmw(control_and_status_t::wkup_pin_1_t::enable); }
    inline auto wkup_pin_1() const {  return control_and_status.rd<control_and_status_t::wkup_pin_1_t> ();}

    inline void wkup_pin_2(const control_and_status_t::wkup_pin_2_t::enum_t val) { control_and_status.rmw(val);}
    inline void wkup_pin_2_disable()  { control_and_status.rmw(control_and_status_t::wkup_pin_2_t::disable); }
    inline void wkup_pin_2_enable()   { control_and_status.rmw(control_and_status_t::wkup_pin_2_t::enable); }
    inline auto wkup_pin_2() const {  return control_and_status.rd<control_and_status_t::wkup_pin_2_t> ();}

    inline void wkup_pin_3(const control_and_status_t::wkup_pin_3_t::enum_t val) { control_and_status.rmw(val);}
    inline void wkup_pin_3_disable()  { control_and_status.rmw(control_and_status_t::wkup_pin_3_t::disable); }
    inline void wkup_pin_3_enable()   { control_and_status.rmw(control_and_status_t::wkup_pin_3_t::enable); }
    inline auto wkup_pin_3() const {  return control_and_status.rd<control_and_status_t::wkup_pin_3_t> ();}


    control_t            control            ;  //  CR;   /*!< PWR power control register,        Address offset: 0x00 */
    control_and_status_t control_and_status ;  //  CSR;  /*!< PWR power control/status register, Address offset: 0x04 */

    inline void clock_enable()  { rcc.pwr_enable(); }
    inline void clock_disable() { rcc.pwr_disable(); }
    inline void reset()         { rcc.pwr_reset(); }

  } ;

static pwr_t& pwr   = *((pwr_t*) pwr_addr);

}  // stm32l0

using namespace stm32l0 ;

#endif /* __PWR++_H__ */
