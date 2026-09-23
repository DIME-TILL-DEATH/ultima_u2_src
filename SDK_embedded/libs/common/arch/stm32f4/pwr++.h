/*
 * rcc++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __PWR++_H__
#define __PWR++_H__

#include "types++.h"


namespace stm32f4
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
       struct power_voltage_level_selection_t  { enum enum_t { offset=5, mask=0b111, threshold_2v=0, threshold_2_1v, threshold_2_3v, threshold_2_5v, threshold_2_6v, threshold_2_7v, threshold_2_8v, threshold_2_9v  } ; } ;
       struct backup_domain_write_protection_t { enum enum_t { offset=8, mask=1, disable=0, enable } ; } ;
       struct flash_power_down_in_stop_mode_t  { enum enum_t { offset=9, mask=1, disable=0, enable } ; } ;
       struct regulator_voltage_scaling_output_selection_t  { enum enum_t { offset=14,mask=1, mode_2=0, mode_1  } ; } ;
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
    inline void power_voltage_level_selection_threshold_2v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2v); }
    inline void power_voltage_level_selection_threshold_2_1v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_1v); }
    inline void power_voltage_level_selection_threshold_2_3v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_3v); }
    inline void power_voltage_level_selection_threshold_2_5v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_5v); }
    inline void power_voltage_level_selection_threshold_2_6v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_6v); }
    inline void power_voltage_level_selection_threshold_2_7v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_7v); }
    inline void power_voltage_level_selection_threshold_2_8v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_8v); }
    inline void power_voltage_level_selection_threshold_2_9v()  { control.rmw(control_t::power_voltage_level_selection_t::threshold_2_9v); }
    inline auto power_voltage_level_selection() const {  return control.rd<control_t::power_voltage_level_selection_t> ();}

    inline void backup_domain_write_protection(const control_t::backup_domain_write_protection_t::enum_t val) { control.rmw(val);}
    inline void backup_domain_write_protection_disable()  { control.rmw(control_t::backup_domain_write_protection_t::disable); }
    inline void backup_domain_write_protection_enable()   { control.rmw(control_t::backup_domain_write_protection_t::enable); }
    inline auto backup_domain_write_protection() const {  return control.rd<control_t::backup_domain_write_protection_t> ();}

    inline void flash_power_down_in_stop_mode(const control_t::flash_power_down_in_stop_mode_t::enum_t val) { control.rmw(val);}
    inline void flash_power_down_in_stop_mode_disable()  { control.rmw(control_t::flash_power_down_in_stop_mode_t::disable); }
    inline void flash_power_down_in_stop_mode_enable()   { control.rmw(control_t::flash_power_down_in_stop_mode_t::enable); }
    inline auto flash_power_down_in_stop_mode() const {  return control.rd<control_t::flash_power_down_in_stop_mode_t> ();}

    inline void regulator_voltage_scaling_output_selection(const control_t::regulator_voltage_scaling_output_selection_t::enum_t val) { control.rmw(val);}
    inline void regulator_voltage_scaling_output_selection_mode_1()  { control.rmw(control_t::regulator_voltage_scaling_output_selection_t::mode_1); }
    inline void regulator_voltage_scaling_output_selection_mode_2()   { control.rmw(control_t::regulator_voltage_scaling_output_selection_t::mode_2); }
    inline auto regulator_voltage_scaling_output_selection() const {  return control.rd<control_t::regulator_voltage_scaling_output_selection_t> ();}

    struct control_and_status_t : public read_write_32_t
      {
       struct wakeup_flag_t                    { enum enum_t { offset=0, mask=1, not_occurred=0, occurred  } ; } ;
       struct standby_flag_t                   { enum enum_t { offset=1, mask=1, not_occurred=0, occurred  } ; } ;
       struct power_voltage_detector_output_t  { enum enum_t { offset=2, mask=1, higher=0, lower } ; } ;
       struct backup_regulator_ready_t         { enum enum_t { offset=3, mask=1, not_ready=0, ready } ; } ;
       struct wkup_pin_t                       { enum enum_t { offset=8, mask=1, disable=0, enable } ; } ;
       struct backup_regulator_t               { enum enum_t { offset=9, mask=1, disable=0, enable } ; } ;
       struct regulator_voltage_scaling_output_selection_ready_t  { enum enum_t { offset=14,mask=1, not_ready=0, ready  } ; } ;
      };

    inline auto wakeup_flag() const {  return control_and_status.rd<control_and_status_t::wakeup_flag_t> ();}

    inline auto standby_flag() const {  return control_and_status.rd<control_and_status_t::standby_flag_t> ();}

    inline auto power_voltage_detector_output() const {  return control_and_status.rd<control_and_status_t::power_voltage_detector_output_t> ();}

    inline auto backup_regulator_ready() const {  return control_and_status.rd<control_and_status_t::backup_regulator_ready_t> ();}

    inline void wkup_pin(const control_and_status_t::wkup_pin_t::enum_t val) { control_and_status.rmw(val);}
    inline void wkup_pin_disable()  { control_and_status.rmw(control_and_status_t::wkup_pin_t::disable); }
    inline void wkup_pin_enable()   { control_and_status.rmw(control_and_status_t::wkup_pin_t::enable); }
    inline auto wkup_pin() const {  return control_and_status.rd<control_and_status_t::wkup_pin_t> ();}

    inline void backup_regulator(const control_and_status_t::backup_regulator_t::enum_t val) { control_and_status.rmw(val);}
    inline void backup_regulator_disable()  { control_and_status.rmw(control_and_status_t::backup_regulator_t::disable); }
    inline void backup_regulator_enable()   { control_and_status.rmw(control_and_status_t::backup_regulator_t::enable); }
    inline auto backup_regulator() const {  return control_and_status.rd<control_and_status_t::backup_regulator_t> ();}

    inline auto regulator_voltage_scaling_output_selection_ready() const {  return control_and_status.rd<control_and_status_t::regulator_voltage_scaling_output_selection_ready_t> ();}

    control_t            control            ;  //  CR;   /*!< PWR power control register,        Address offset: 0x00 */
    control_and_status_t control_and_status ;  //  CSR;  /*!< PWR power control/status register, Address offset: 0x04 */

    inline void clock_enable()  { rcc.pwr_enable(); }
    inline void clock_disable() { rcc.pwr_disable(); }
    inline void reset()         { rcc.pwr_reset(); }

  } ;

static pwr_t& pwr   = *((pwr_t*) pwr_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __PWR++_H__ */
