/*
 * dbgmcr++.h
 *
 *  Created on: 20 янв. 2018 г.
 *      Author: klen
 */

#ifndef __DBGMCU++_H__
#define __DBGMCU++_H__

#include "types++.h"

namespace stm32f7
{

struct dbgmcu_t //TODO
{
  struct idcode_t : public read_write_32_t
  {
    struct dev_t    { enum enum_t { offset=0,  mask=0xfff,
                                    stm32f74x_75x = 0x449,
                                    stm32f76x_77x = 0x451,
	                            stm32f72x_73x = 0x452,
	                           };
                     } ;

    struct rev_t   { enum enum_t { offset=16, mask=0xffff }; } ;

    struct rev_stm32f74x_75x_t   { enum enum_t { offset=16, mask=0xffff, rev_A=0x1000, rev_Z=0x1001, }; } ;
    struct rev_stm32f76x_77x_t   { enum enum_t { offset=16, mask=0xffff, rev_A=0x1000 }; } ;
    struct rev_stm32f73x_73x_t   { enum enum_t { offset=16, mask=0xffff, rev_A=0x1000 }; } ;
    // ..
    // TODO
  } ;

  inline auto dev() const { return idcode.rd<idcode_t::dev_t>();}
  inline auto rev() const { return idcode.rd<idcode_t::rev_t>();}

  struct configuration_t : public read_write_32_t
    {
      struct debug_sleep_mode_t     { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct debug_stop_mode_t      { enum enum_t { offset=1, mask=1, disable=0, enable }; } ;
      struct debug_standby_mode_t   { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
      struct trace_io_t             { enum enum_t { offset=5, mask=1, disable=0, enable }; } ;
      struct trace_mode_t           { enum enum_t { offset=6, mask=0b11, asynchronous=0, synchronous_data_size_1, synchronous_data_size_2, synchronous_data_size_4  }; } ;
    } ;

  inline void debug_sleep_mode(const configuration_t::debug_sleep_mode_t::enum_t val) {  configuration.rmw( val );}
  inline void debug_sleep_mode_enable() { configuration.rmw( configuration_t::debug_sleep_mode_t::enable );}
  inline void debug_sleep_mode_disable() { configuration.rmw( configuration_t::debug_sleep_mode_t::disable );}
  inline auto debug_sleep_mode() const { return configuration.rd<configuration_t::debug_sleep_mode_t>();}

  inline void debug_stop_mode(const configuration_t::debug_stop_mode_t::enum_t val) {  configuration.rmw( val );}
  inline void debug_stop_mode_enable() { configuration.rmw( configuration_t::debug_stop_mode_t::enable );}
  inline void debug_stop_mode_disable() { configuration.rmw( configuration_t::debug_stop_mode_t::disable );}
  inline auto debug_stop_mode_mode() const { return configuration.rd<configuration_t::debug_stop_mode_t>();}

  inline void debug_standby_mode(const configuration_t::debug_standby_mode_t::enum_t val) {  configuration.rmw( val );}
  inline void debug_standby_mode_enable() { configuration.rmw( configuration_t::debug_standby_mode_t::enable );}
  inline void debug_standby_mode_disable() { configuration.rmw( configuration_t::debug_standby_mode_t::disable );}
  inline auto debug_standby_mode() const { return configuration.rd<configuration_t::debug_standby_mode_t>();}

  inline void trace_io(const configuration_t::trace_io_t::enum_t val) {  configuration.rmw( val );}
  inline void trace_io_enable() { configuration.rmw( configuration_t::trace_io_t::enable );}
  inline void trace_io_disable() { configuration.rmw( configuration_t::trace_io_t::disable );}
  inline auto trace_io_mode() const { return configuration.rd<configuration_t::trace_io_t>();}

  inline void trace_mode(const configuration_t::trace_mode_t::enum_t val) {  configuration.rmw( val );}
  inline void trace_mode_asynchronous() { configuration.rmw( configuration_t::trace_mode_t::asynchronous );}
  inline void trace_mode_synchronous_data_size_1() { configuration.rmw( configuration_t::trace_mode_t::synchronous_data_size_1 );}
  inline void trace_mode_synchronous_data_size_2() { configuration.rmw( configuration_t::trace_mode_t::synchronous_data_size_2 );}
  inline void trace_mode_synchronous_data_size_4() { configuration.rmw( configuration_t::trace_mode_t::synchronous_data_size_4 );}
  inline auto trace_mode() const { return configuration.rd<configuration_t::trace_mode_t>();}

  struct apb1_freeze_t : public read_write_32_t
    {
      enum enum_t       {  mask=0b1, no_stop=0, stop } ;
      struct tim2_stop_t     { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct tim3_stop_t     { enum enum_t { offset=1, mask=1, disable=0, enable }; } ;
      struct tim4_stop_t     { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
      struct tim5_stop_t     { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct tim6_stop_t     { enum enum_t { offset=4, mask=1, disable=0, enable }; } ;
      struct tim7_stop_t     { enum enum_t { offset=5, mask=1, disable=0, enable }; } ;
      struct tim12_stop_t    { enum enum_t { offset=6, mask=1, disable=0, enable }; } ;
      struct tim13_stop_t    { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct tim14_stop_t    { enum enum_t { offset=8, mask=1, disable=0, enable }; } ;
      struct lptim1_stop_t   { enum enum_t { offset=9, mask=1, disable=0, enable }; } ;
      struct rtc_stop_t      { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
      struct wwdg_stop_t     { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
      struct iwdg_stop_t     { enum enum_t { offset=12, mask=1, disable=0, enable }; } ;
      struct can3_stop_t     { enum enum_t { offset=13, mask=1, disable=0, enable }; } ;
      struct i2c1_smbus_timeout_t { enum enum_t { offset=21, mask=1, disable=0, enable }; } ;
      struct i2c2_smbus_timeout_t { enum enum_t { offset=22, mask=1, disable=0, enable }; } ;
      struct i2c3_smbus_timeout_t { enum enum_t { offset=23, mask=1, disable=0, enable }; } ;
      struct i2c4_smbus_timeout_t { enum enum_t { offset=24, mask=1, disable=0, enable }; } ;
      struct can1_stop_t     { enum enum_t { offset=25, mask=1, disable=0, enable }; } ;
      struct can2_stop_t     { enum enum_t { offset=26, mask=1, disable=0, enable }; } ;

      enum peripheral_t { tim2=tim2_stop_t::offset,
                       tim3=tim3_stop_t::offset,
 			  tim4=tim4_stop_t::offset,
 			  tim5=tim5_stop_t::offset,
 			  tim6=tim6_stop_t::offset,
 			  tim7=tim7_stop_t::offset,
 			  tim12=tim12_stop_t::offset,
 			  tim13=tim13_stop_t::offset,
 			  tim14=tim14_stop_t::offset,
 			  lptim1=lptim1_stop_t::offset,
 			  rtc=rtc_stop_t::offset,
 			  wwdg=wwdg_stop_t::offset,
 			  iwdg=iwdg_stop_t::offset,
 			  can3=can3_stop_t::offset,
 			  i2c1=i2c1_smbus_timeout_t::offset,
 			  i2c2=i2c2_smbus_timeout_t::offset,
 			  i2c3=i2c3_smbus_timeout_t::offset,
 			  i2c4=i2c4_smbus_timeout_t::offset,
 			  can1=can1_stop_t::offset,
 			  can2=can2_stop_t::offset,
                     } ;
    } ;



  inline void tim2_stop(const apb1_freeze_t::tim2_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim2_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim2_stop_t::enable );}
  inline void tim2_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim2_stop_t::disable );}
  inline auto tim2_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim2_stop_t>();}

  inline void tim3_stop(const apb1_freeze_t::tim3_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim3_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim3_stop_t::enable );}
  inline void tim3_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim3_stop_t::disable );}
  inline auto tim3_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim3_stop_t>();}

  inline void tim4_stop(const apb1_freeze_t::tim4_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim4_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim4_stop_t::enable );}
  inline void tim4_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim4_stop_t::disable );}
  inline auto tim4_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim4_stop_t>();}

  inline void tim5_stop(const apb1_freeze_t::tim5_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim5_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim5_stop_t::enable );}
  inline void tim5_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim5_stop_t::disable );}
  inline auto tim5_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim5_stop_t>();}

  inline void tim6_stop(const apb1_freeze_t::tim6_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim6_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim6_stop_t::enable );}
  inline void tim6_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim6_stop_t::disable );}
  inline auto tim6_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim6_stop_t>();}

  inline void tim7_stop(const apb1_freeze_t::tim7_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim7_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim7_stop_t::enable );}
  inline void tim7_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim7_stop_t::disable );}
  inline auto tim7_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim7_stop_t>();}

  inline void tim12_stop(const apb1_freeze_t::tim12_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim12_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim12_stop_t::enable );}
  inline void tim12_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim12_stop_t::disable );}
  inline auto tim12_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim12_stop_t>();}

  inline void tim13_stop(const apb1_freeze_t::tim13_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim13_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim13_stop_t::enable );}
  inline void tim13_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim13_stop_t::disable );}
  inline auto tim13_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim13_stop_t>();}

  inline void tim14_stop(const apb1_freeze_t::tim14_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void tim14_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::tim14_stop_t::enable );}
  inline void tim14_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::tim14_stop_t::disable );}
  inline auto tim14_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim14_stop_t>();}

  inline void lptim1_stop(const apb1_freeze_t::lptim1_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void lptim1_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::lptim1_stop_t::enable );}
  inline void lptim1_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::lptim1_stop_t::disable );}
  inline auto lptim1_stop() const { return apb1_freeze.rd<apb1_freeze_t::lptim1_stop_t>();}

  inline void rtc_stop(const apb1_freeze_t::rtc_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void rtc_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::rtc_stop_t::enable );}
  inline void rtc_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::rtc_stop_t::disable );}
  inline auto rtc_stop() const { return apb1_freeze.rd<apb1_freeze_t::rtc_stop_t>();}

  inline void wwdg_stop(const apb1_freeze_t::wwdg_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void wwdg_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::wwdg_stop_t::enable );}
  inline void wwdg_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::wwdg_stop_t::disable );}
  inline auto wwdg_stop() const { return apb1_freeze.rd<apb1_freeze_t::wwdg_stop_t>();}

  inline void iwdg_stop(const apb1_freeze_t::iwdg_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void iwdg_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::iwdg_stop_t::enable );}
  inline void iwdg_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::iwdg_stop_t::disable );}
  inline auto iwdg_stop() const { return apb1_freeze.rd<apb1_freeze_t::iwdg_stop_t>();}

  inline void can3_stop(const apb1_freeze_t::can3_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void can3_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::can3_stop_t::enable );}
  inline void can3_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::can3_stop_t::disable );}
  inline auto can3_stop() const { return apb1_freeze.rd<apb1_freeze_t::can3_stop_t>();}

  inline void i2c1_smbus_timeout(const apb1_freeze_t::i2c1_smbus_timeout_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void i2c1_smbus_timeout_enable() { apb1_freeze.rmw( apb1_freeze_t::i2c1_smbus_timeout_t::enable );}
  inline void i2c1_smbus_timeout_disable() { apb1_freeze.rmw( apb1_freeze_t::i2c1_smbus_timeout_t::disable );}
  inline auto i2c1_smbus_timeout() const { return apb1_freeze.rd<apb1_freeze_t::i2c1_smbus_timeout_t>();}

  inline void i2c2_smbus_timeout(const apb1_freeze_t::i2c2_smbus_timeout_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void i2c2_smbus_timeout_enable() { apb1_freeze.rmw( apb1_freeze_t::i2c2_smbus_timeout_t::enable );}
  inline void i2c2_smbus_timeout_disable() { apb1_freeze.rmw( apb1_freeze_t::i2c2_smbus_timeout_t::disable );}
  inline auto i2c2_smbus_timeout() const { return apb1_freeze.rd<apb1_freeze_t::i2c2_smbus_timeout_t>();}

  inline void i2c3_smbus_timeout(const apb1_freeze_t::i2c3_smbus_timeout_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void i2c3_smbus_timeout_enable() { apb1_freeze.rmw( apb1_freeze_t::i2c3_smbus_timeout_t::enable );}
  inline void i2c3_smbus_timeout_disable() { apb1_freeze.rmw( apb1_freeze_t::i2c3_smbus_timeout_t::disable );}
  inline auto i2c3_smbus_timeout() const { return apb1_freeze.rd<apb1_freeze_t::i2c3_smbus_timeout_t>();}

  inline void can1_stop(const apb1_freeze_t::can1_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void can1_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::can1_stop_t::enable );}
  inline void can1_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::can1_stop_t::disable );}
  inline auto can1_stop() const { return apb1_freeze.rd<apb1_freeze_t::can1_stop_t>();}

  inline void can2_stop(const apb1_freeze_t::can2_stop_t::enum_t val) {  apb1_freeze.rmw( val );}
  inline void can2_stop_enable() { apb1_freeze.rmw( apb1_freeze_t::can2_stop_t::enable );}
  inline void can2_stop_disable() { apb1_freeze.rmw( apb1_freeze_t::can2_stop_t::disable );}
  inline auto can2_stop() const { return apb1_freeze.rd<apb1_freeze_t::tim14_stop_t>();}

  inline void state_stop(const apb1_freeze_t::peripheral_t val) { apb1_freeze.rmw( apb1_freeze_t::stop,  val ) ; }
  inline void state_no_stop(const apb1_freeze_t::peripheral_t val){ apb1_freeze.rmw( apb1_freeze_t::no_stop, val ) ; }


  struct apb2_freeze_t : public read_write_32_t
    {
      enum enum_t       {  mask=0b1, no_stop=0, stop } ;
      struct tim1_stop_t     { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct tim8_stop_t     { enum enum_t { offset=1, mask=1, disable=0, enable }; } ;
      struct tim9_stop_t     { enum enum_t { offset=16, mask=1, disable=0, enable }; } ;
      struct tim10_stop_t    { enum enum_t { offset=17, mask=1, disable=0, enable }; } ;
      struct tim11_stop_t    { enum enum_t { offset=18, mask=1, disable=0, enable }; } ;

      enum peripheral_t { tim1=tim1_stop_t::offset,
                          tim8=tim8_stop_t::offset,
    			  tim9=tim9_stop_t::offset,
    			  tim10=tim10_stop_t::offset,
    			  tim11=tim11_stop_t::offset,
                        } ;
    } ;

  inline void tim1_stop(const apb2_freeze_t::tim1_stop_t::enum_t val) {  apb2_freeze.rmw( val );}
  inline void tim1_stop_enable() { apb2_freeze.rmw( apb2_freeze_t::tim1_stop_t::enable );}
  inline void tim1_stop_disable() { apb2_freeze.rmw( apb2_freeze_t::tim1_stop_t::disable );}
  inline auto tim1_stop() const { return apb2_freeze.rd<apb2_freeze_t::tim1_stop_t>();}

  inline void tim8_stop(const apb2_freeze_t::tim8_stop_t::enum_t val) {  apb2_freeze.rmw( val );}
  inline void tim8_stop_enable() { apb2_freeze.rmw( apb2_freeze_t::tim8_stop_t::enable );}
  inline void tim8_stop_disable() { apb2_freeze.rmw( apb2_freeze_t::tim8_stop_t::disable );}
  inline auto tim8_stop() const { return apb2_freeze.rd<apb2_freeze_t::tim8_stop_t>();}

  inline void tim9_stop(const apb2_freeze_t::tim9_stop_t::enum_t val) {  apb2_freeze.rmw( val );}
  inline void tim9_stop_enable() { apb2_freeze.rmw( apb2_freeze_t::tim9_stop_t::enable );}
  inline void tim9_stop_disable() { apb2_freeze.rmw( apb2_freeze_t::tim9_stop_t::disable );}
  inline auto tim9_stop() const { return apb2_freeze.rd<apb2_freeze_t::tim9_stop_t>();}

  inline void tim10_stop(const apb2_freeze_t::tim10_stop_t::enum_t val) {  apb2_freeze.rmw( val );}
  inline void tim10_stop_enable() { apb2_freeze.rmw( apb2_freeze_t::tim10_stop_t::enable );}
  inline void tim10_stop_disable() { apb2_freeze.rmw( apb2_freeze_t::tim10_stop_t::disable );}
  inline auto tim10_stop() const { return apb2_freeze.rd<apb2_freeze_t::tim10_stop_t>();}

  inline void tim11_stop(const apb2_freeze_t::tim11_stop_t::enum_t val) {  apb2_freeze.rmw( val );}
  inline void tim11_stop_enable() { apb2_freeze.rmw( apb2_freeze_t::tim11_stop_t::enable );}
  inline void tim11_stop_disable() { apb2_freeze.rmw( apb2_freeze_t::tim11_stop_t::disable );}
  inline auto tim11_stop() const { return apb2_freeze.rd<apb2_freeze_t::tim11_stop_t>();}

  idcode_t        idcode ;       //IDCODE   /*!< MCU device ID code,               Address offset: 0x00 */
  configuration_t configuration; //CR;      /*!< Debug MCU configuration register, Address offset: 0x04 */
  apb1_freeze_t   apb1_freeze; //APB1FZ;  /*!< Debug MCU APB1 freeze register,   Address offset: 0x08 */
  apb2_freeze_t   apb2_freeze; //APB2FZ;  /*!< Debug MCU APB2 freeze register,   Address offset: 0x0C */

} ;

static dbgmcu_t& dbgmcu = *((dbgmcu_t*) dbgmcu_addr);

}

using namespace stm32f7 ;

#endif /* __DBGMCU++_H__ */
