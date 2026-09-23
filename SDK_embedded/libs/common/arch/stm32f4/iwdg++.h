/*
 * iwdg++.h
 *
 *  Created on: 22 авг. 2017 г.
 *      Author: klen
 */

#ifndef __IWDG++_H__
#define __IWDG++_H__

#include "types++.h"

namespace stm32f4
{

struct iwdg_t
{
  struct key_t : public read_write_32_t
  {
  };

  inline  void reset() { key.write(0xaaaa); }
  inline  void unlock(){ key.write(0x5555); }
  inline  void start() { key.write(0xcccc); }

  struct prescaler_t : public read_write_32_t
  {
    struct divider_t  { enum enum_t { offset=0,  mask=0b111, div_4=0 , div_8, div_16, div_32, div_64, div_128, div_256 } ; } ;
  };

  inline  void divider( const prescaler_t::divider_t::enum_t val){  prescaler.rmw(val) ;}
  inline  void divider_4()  {  prescaler.rmw( prescaler_t::divider_t::div_4)  ;}
  inline  void divider_8()  {  prescaler.rmw( prescaler_t::divider_t::div_8)  ;}
  inline  void divider_16() {  prescaler.rmw( prescaler_t::divider_t::div_16) ;}
  inline  void divider_32() {  prescaler.rmw( prescaler_t::divider_t::div_32) ;}
  inline  void divider_64() {  prescaler.rmw( prescaler_t::divider_t::div_64) ;}
  inline  void divider_128(){  prescaler.rmw( prescaler_t::divider_t::div_128);}
  inline  void divider_256(){  prescaler.rmw( prescaler_t::divider_t::div_256);}
  inline  auto divider() const {  return prescaler.rd<prescaler_t::divider_t> ();}


  struct status_t : public read_write_32_t
  {
    struct prescaler_value_update_t       { enum enum_t { offset=0,  mask=1, no_set=0, set=1 } ; } ;
    struct counter_reload_value_update_t  { enum enum_t { offset=1,  mask=1, no_set=0, set=1 } ; } ;
  };

  inline auto prescaler_value_update() const {  return status.rd<status_t::prescaler_value_update_t> ();}
  inline auto prescaler_value_update_wait() const {  while ( status.rd<status_t::prescaler_value_update_t>() == status_t::prescaler_value_update_t::set) {} }

  inline auto counter_reload_value_update() const {  return status.rd<status_t::counter_reload_value_update_t> ();}
  inline auto counter_reload_value_update_wait() const {  while ( status.rd<status_t::counter_reload_value_update_t>() == status_t::counter_reload_value_update_t::set) {} }



  key_t key ; // KR;   /*!< IWDG Key register,       Address offset: 0x00 */
  prescaler_t prescaler; // PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
  volatile uint32_t reload;  // IWDG Reload register,    Address offset: 0x08 */
  status_t status;   // IWDG Status register,    Address offset: 0x0C */

  inline void period_ms(const uint32_t val)
  {
	uint32_t count, prescale, reload ;
	prescaler_t::divider_t::enum_t div;

	count = (val << 5);    // Set the count to represent ticks of the 32kHz LSI clock
	prescale = (count >> 12); // Strip off the first 12 bits to get the prescale value required



	if (prescale > 256)      { div = prescaler_t::divider_t::div_256; reload = 0xffe; }
	else if (prescale > 128) { div = prescaler_t::divider_t::div_256; reload = (count >> 8);}
	else if (prescale > 64)  { div = prescaler_t::divider_t::div_128; reload = (count >> 7);}
	else if (prescale > 32)  { div = prescaler_t::divider_t::div_64;  reload = (count >> 6);}
	else if (prescale > 16)  { div = prescaler_t::divider_t::div_32;  reload = (count >> 5);}
	else if (prescale > 8)   { div = prescaler_t::divider_t::div_16;  reload = (count >> 4);}
	else if (prescale > 4)   { div = prescaler_t::divider_t::div_8;   reload = (count >> 3);}
	else {div = prescaler_t::divider_t::div_4;   reload = (count >> 2);	}

	/* Avoid the undefined situation of a zero count */
	if (count == 0) {
		count = 1;
	}

	prescaler_value_update_wait();
	unlock();
	divider(div);
	counter_reload_value_update_wait();
	this->reload=reload ;
  }
} ;

static iwdg_t& idwg = *((iwdg_t*) iwdg_addr);

}

using namespace stm32f4 ;

#endif /* __IWDG++_H__ */
