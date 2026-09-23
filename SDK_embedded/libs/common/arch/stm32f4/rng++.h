/*
 * rng++.h
 *
 *  Created on: 30 янв. 2017 г.
 *      Author: klen
 */

#ifndef __RNG++_H__
#define __RNG++_H__

#include "types++.h"

namespace stm32f4
{

struct rng_t
{
  struct control_t : public read_write_32_t
  {
    struct state_t              { enum enum_t { offset=2, mask=1, disable=0 , enable }; } ;
    struct interrupt_state_t    { enum enum_t { offset=3, mask=1, disable=0 , enable }; } ;
  } ;

  inline void state(const control_t::state_t::enum_t val) {  control.rmw( val );}
  inline void state_enable() { control.rmw( control_t::state_t::enable );}
  inline void state_disable() { control.rmw( control_t::state_t::disable );}
  inline auto state() const { return control.rd<control_t::state_t>();}

  inline void interrupt(const control_t::interrupt_state_t::enum_t val) {control.rmw( val );}
  inline void interrupt_enable() {control.rmw( control_t::interrupt_state_t::enable );}
  inline void interrupt_disable() {control.rmw( control_t::interrupt_state_t::disable );}
  inline auto interrupt() const {return control.rd<control_t::interrupt_state_t>();}

  struct status_t : public read_write_32_t
  {
    struct ready_t                 { enum enum_t {offset=0,mask=1, no_ready=0, ready};} ;
    struct clock_error_t           { enum enum_t {offset=1,mask=1, no=0, yes};} ;
    struct seed_error_t            { enum enum_t {offset=2,mask=1, no=0, yes};} ;
    struct clock_error_interrupt_t { enum enum_t {offset=5,mask=1, no_occured=0, occured};};
    struct seed_error_interrupt_t  { enum enum_t {offset=6,mask=1, no_occured=0, occured};};
  } ;

  inline auto ready() const { return status.rd<status_t::ready_t>(); }
  inline void wait_ready() const { while (ready() == status_t::ready_t::no_ready) {} ;}

  inline auto clock_error() const { return status.rd<status_t::clock_error_t>(); }
  inline auto seed_error() const { return status.rd<status_t::seed_error_t>(); }

  inline auto clock_error_interrupt()  const{ return status.rd<status_t::clock_error_interrupt_t>(); }
  inline void clock_error_interrupt_clear() { status.rmw(status_t::clock_error_interrupt_t::no_occured); }

  inline auto seed_error_interrupt() const {return status.rd<status_t::seed_error_interrupt_t>();}
  inline void seed_error_interrupt_clear() { status.rmw(status_t::seed_error_interrupt_t::no_occured);}

  control_t  control ; // CR;  /*!< RNG control register, Address offset: 0x00 */
  status_t   status ;  // SR;  /*!< RNG status register,  Address offset: 0x04 */
  const uint32_t data ; // DR;  /*!< RNG data register,    Address offset: 0x08 */

  inline void clock_enable() {  rcc.rng_enable() ; }
  inline void clock_disable(){  rcc.rng_disable(); }
  inline void reset()        {  rcc.rng_reset() ; }

  inline uint32_t read() const { wait_ready(); return data ;}
  inline float    readf()const { return ((float)read()) / ((float)0xffffffff); }
  inline double   readd()const { return ((double)read()) / ((double)0xffffffffffffffff); }

} ;

static rng_t& rng   = *((rng_t*) rng_addr);

}

using namespace stm32f4 ;

#endif /* __RNG++_H__ */
