/*
 * flash++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __FLASH++_H__
#define __FLASH++_H__

#include "types++.h"

namespace stm32f4
{

struct flash_t
  {
    // TODO
    // RM0090 DocID018909 Rev 13 97/1748

    struct access_control_t : public read_write_32_t
       {
         struct latency_t      { enum enum_t { offset=0, mask=0b111, zero_wait=0, wait_1, wait_2, wait_3, wait_4, wait_5, wait_6, wait_7 } ; } ;
         struct prefetch_t     { enum enum_t { offset=8, mask=1, disable=0,  enable } ; } ;
         struct icache_t       { enum enum_t { offset=9, mask=1, disable=0,  enable } ; } ;
         struct dcache_t       { enum enum_t { offset=10, mask=1, disable=0,  enable } ; } ;
         struct icache_reset_t { enum enum_t { offset=11, mask=1, no_reset=0,  reset } ; } ;
         struct dcache_reset_t { enum enum_t { offset=12, mask=1, no_reset=0,  reset } ; } ;
       };

    inline void latency(const access_control_t::latency_t::enum_t val) { access_control.rmw(val);}
    inline void latency_zero_wait()   { access_control.rmw(access_control_t::latency_t::zero_wait); }
    inline void latency_wait_1()   { access_control.rmw(access_control_t::latency_t::wait_1); }
    inline void latency_wait_2()   { access_control.rmw(access_control_t::latency_t::wait_2); }
    inline void latency_wait_3()   { access_control.rmw(access_control_t::latency_t::wait_3); }
    inline void latency_wait_4()   { access_control.rmw(access_control_t::latency_t::wait_4); }
    inline void latency_wait_5()   { access_control.rmw(access_control_t::latency_t::wait_5); }
    inline void latency_wait_6()   { access_control.rmw(access_control_t::latency_t::wait_6); }
    inline void latency_wait_7()   { access_control.rmw(access_control_t::latency_t::wait_7); }
    inline auto latency() const {  return access_control.rd<access_control_t::latency_t> ();}

    inline void prefetch(const access_control_t::prefetch_t::enum_t val) { access_control.rmw(val);}
    inline void prefetch_disable() { access_control.rmw(access_control_t::prefetch_t::disable); }
    inline void prefetch_enable()  { access_control.rmw(access_control_t::prefetch_t::enable); }
    inline auto prefetch() const {  return access_control.rd<access_control_t::prefetch_t> ();}

    inline void icache(const access_control_t::icache_t::enum_t val) { access_control.rmw(val);}
    inline void icache_disable() { access_control.rmw(access_control_t::icache_t::disable); }
    inline void icache_enable()  { access_control.rmw(access_control_t::icache_t::enable); }
    inline auto icache() const {  return access_control.rd<access_control_t::icache_t> ();}

    inline void dcache(const access_control_t::dcache_t::enum_t val) { access_control.rmw(val);}
    inline void dcache_disable() { access_control.rmw(access_control_t::dcache_t::disable); }
    inline void dcache_enable()  { access_control.rmw(access_control_t::dcache_t::enable); }
    inline auto dcache() const {  return access_control.rd<access_control_t::dcache_t> ();}

    inline void icache_reset_state(const access_control_t::icache_reset_t::enum_t val) { access_control.rmw(val);}
    inline void icache_reset_state_no_reset() { access_control.rmw(access_control_t::icache_reset_t::no_reset); }
    inline void icache_reset_state_reset()  { access_control.rmw(access_control_t::icache_reset_t::reset); }
    inline auto icache_reset_state() const {  return access_control.rd<access_control_t::icache_reset_t> ();}
    inline void icache_reset()  { icache_reset_state_reset() ; icache_reset_state_no_reset(); }

    inline void dcache_reset_state(const access_control_t::icache_reset_t::enum_t val) { access_control.rmw(val);}
    inline void dcache_reset_state_no_reset() { access_control.rmw(access_control_t::icache_reset_t::no_reset); }
    inline void dcache_reset_state_reset()  { access_control.rmw(access_control_t::icache_reset_t::reset); }
    inline auto dcache_reset_state() const {  return access_control.rd<access_control_t::icache_reset_t> ();}
    inline void dcache_reset()  { dcache_reset_state_reset() ; dcache_reset_state_no_reset(); }

    struct key_t : public read_write_32_t
    {
    } ;
    inline void unlock() { key.write(0x45670123) ; key.write(0xCDEF89AB) ; }

    struct option_key_t : public read_write_32_t
    {
    } ;
    inline void option_unlock() { option_key.write(0x08192A3B) ; option_key.write(0x4C5D6E7F) ; }

    struct status_t : public read_write_32_t
       {
         struct end_of_operation_t             { enum enum_t { offset=0,  mask=1, not_occured=0, occured } ; } ;
         struct operation_error_t              { enum enum_t { offset=1,  mask=1, not_occured=0, occured } ; } ;
         struct write_protection_error_t       { enum enum_t { offset=4,  mask=1, not_occured=0, occured } ; } ;
         struct programming_alligment_error_t  { enum enum_t { offset=5,  mask=1, not_occured=0, occured } ; } ;
         struct programming_parallelism_error_t{ enum enum_t { offset=6,  mask=1, not_occured=0, occured } ; } ;
         struct programming_sequence_error_t   { enum enum_t { offset=7,  mask=1, not_occured=0, occured } ; } ;
         struct busy_t                         { enum enum_t { offset=16, mask=1, no_busy=0, busy } ;} ;
       };

    inline auto end_of_operation() const {  return status.rd<status_t::end_of_operation_t> ();}
    inline void end_of_operation_clear() { status.rmw(status_t::end_of_operation_t::occured); }

    inline auto operation_error() const {  return status.rd<status_t::operation_error_t> ();}
    inline void operation_error_clear() { status.rmw(status_t::operation_error_t::occured); }

    inline auto write_protection_error() const {  return status.rd<status_t::write_protection_error_t> ();}
    inline void write_protection_error_clear() { status.rmw(status_t::write_protection_error_t::occured); }

    inline auto programming_alligment_error() const {  return status.rd<status_t::programming_alligment_error_t> ();}
    inline void programming_alligment_error_clear() { status.rmw(status_t::programming_alligment_error_t::occured); }

    inline auto programming_parallelism_error() const {  return status.rd<status_t::programming_parallelism_error_t> ();}
    inline void programming_parallelism_error_clear() { status.rmw(status_t::programming_parallelism_error_t::occured); }

    inline auto programming_sequence_error() const {  return status.rd<status_t::programming_sequence_error_t> ();}
    inline void programming_sequence_error_clear() { status.rmw(status_t::programming_sequence_error_t::occured); }

    inline auto busy() const {  return status.rd<status_t::busy_t> ();}
    inline void busy_wait() { while ( busy() == status_t::busy_t::busy) {} }


    struct control_t : public read_write_32_t
       {
         struct programming_t                { enum enum_t { offset=0,  mask=1, deactivated=0,activated=1 } ; } ;
         struct sector_erase_t               { enum enum_t { offset=1,  mask=1, deactivated=0,activated=1 } ; } ;
         struct mass_erase_t                 { enum enum_t { offset=2,  mask=1, deactivated=0,activated=1 } ; } ;
         struct sector_number_t              { enum enum_t { offset=3,  mask=0b1111 } ; } ;
         struct program_size_t               { enum enum_t { offset=8,  mask=0b11, x8=0 , x16, x32, x64} ; } ;
         struct start_t                      { enum enum_t { offset=16, mask=1, perform=1 } ; } ;
         struct end_of_operation_interrupt_t { enum enum_t { offset=24, mask=1, disable=0, enable } ; } ;
	 struct error_interrupt_t            { enum enum_t { offset=25, mask=1, disable=0, enable } ; } ;
	 struct lock_t                       { enum enum_t { offset=31, mask=1, active=1 } ; } ;
       };

    inline void programming_activated() { control.rmw(control_t::programming_t::activated);}
    inline void programming_deactivated() { control.rmw(control_t::programming_t::deactivated);}
    inline auto programming() const { return control.rd<control_t::programming_t>();  }

    inline void sector_erase_activated() { control.rmw(control_t::sector_erase_t::activated);}
    inline void sector_erase_deactivated() { control.rmw(control_t::sector_erase_t::deactivated);}
    inline auto sector_erase() const { return control.rd<control_t::sector_erase_t>();  }

    inline void mass_erase_activated() { control.rmw(control_t::mass_erase_t::activated);}
    inline void mass_erase_deactivated() { control.rmw(control_t::mass_erase_t::deactivated);}
    inline auto mass_erase() const { return control.rd<control_t::mass_erase_t>();  }

    inline void sector_number(const uint8_t val) { control.rmw((control_t::sector_number_t::enum_t) val);}
    inline auto sector_number() const { return (uint8_t)control.rd<control_t::sector_number_t>();  }

    inline void program_size( const control_t::program_size_t::enum_t val) { control.rmw(val);}
    inline void program_size_x8()  { control.rmw(control_t::program_size_t::x8);  }
    inline void program_size_x16() { control.rmw(control_t::program_size_t::x16);  }
    inline void program_size_x32() { control.rmw(control_t::program_size_t::x32);  }
    inline void program_size_x64() { control.rmw(control_t::program_size_t::x64);  }
    inline auto program_size() { return control.rd<control_t::program_size_t>();}

    inline void start() { control.rmw(control_t::start_t::perform);  }
    inline auto start_state() { return control.rd<control_t::start_t>();}

    inline void end_of_operation_interrupt( const control_t::end_of_operation_interrupt_t::enum_t val) { control.rmw(val);}
    inline void end_of_operation_interrupt_disable()  { control.rmw(control_t::end_of_operation_interrupt_t::disable);  }
    inline void end_of_operation_interrupt_enable() { control.rmw(control_t::end_of_operation_interrupt_t::enable);  }
    inline auto end_of_operation_interrupt() { return control.rd<control_t::end_of_operation_interrupt_t>();}

    inline void error_interrupt( const control_t::error_interrupt_t::enum_t val) { control.rmw(val);}
    inline void error_interrupt_disable()  { control.rmw(control_t::error_interrupt_t::disable);  }
    inline void error_interrupt_enable() { control.rmw(control_t::error_interrupt_t::enable);  }
    inline auto error_interrupt() { return control.rd<control_t::error_interrupt_t>();}

    inline void lock() { control.rmw(control_t::lock_t::active);  }
    inline auto lock_state() { return control.rd<control_t::lock_t>();}

    struct option_control_t : public read_write_32_t
      {
  	  struct option_lock_t { enum enum_t { offset=0, mask=1, activated=1 }; } ;
  	  struct option_start_t { enum enum_t { offset=1, mask=1, activated=1 }; } ;
  	  struct bor_reset_level_t { enum enum_t { offset=2, mask=0b11, vbor3=0, vbor2, vbor1, off }; } ;

  	  struct user_option_bytes_wdg_sw_t     { enum enum_t { offset=5, mask=1, reset=0, set=1 }; } ;
  	  struct user_option_bytes_nrst_stop_t  { enum enum_t { offset=6, mask=1, reset=0, set=1 }; } ;
  	  struct user_option_bytes_nrst_stdby_t { enum enum_t { offset=7, mask=1, reset=0, set=1 }; } ;

  	  struct read_protect_t { enum enum_t { offset=8, mask=0xff, level_0=0xaa, level_1=0xbb, level_2=0xcc }; } ;
  	  struct not_write_protect_t { enum enum_t { offset=16, mask=0xfff }; } ;
      } ;

    inline  void option_lock() {  option_control.rmw( option_control_t::option_lock_t::activated) ;}
    inline  void option_start() {  option_control.rmw( option_control_t::option_start_t::activated) ;}

    inline  void bor_reset_level(const option_control_t::bor_reset_level_t::enum_t val){  option_control.rmw(val) ;}
    inline  void bor_reset_level_vbor3(){  option_control.rmw( option_control_t::bor_reset_level_t::vbor3) ;}
    inline  void bor_reset_level_vbor2(){  option_control.rmw( option_control_t::bor_reset_level_t::vbor2) ;}
    inline  void bor_reset_level_vbor1(){  option_control.rmw( option_control_t::bor_reset_level_t::vbor1) ;}
    inline  void bor_reset_level_off(){  option_control.rmw( option_control_t::bor_reset_level_t::off) ;}
    inline  auto bor_reset_level()const {  return option_control.rd<option_control_t::bor_reset_level_t>();}

    inline  void user_option_bytes_wdg_sw(const option_control_t::user_option_bytes_wdg_sw_t::enum_t val){  option_control.rmw(val) ;}
    inline  void user_option_bytes_wdg_sw_reset(){  option_control.rmw( option_control_t::user_option_bytes_wdg_sw_t::reset) ;}
    inline  void user_option_bytes_wdg_sw_set()  {  option_control.rmw( option_control_t::user_option_bytes_wdg_sw_t::set) ;}
    inline  auto user_option_bytes_wdg_sw()const {  return option_control.rd<option_control_t::user_option_bytes_wdg_sw_t>();}

    inline  void user_option_bytes_nrst_stop(const option_control_t::user_option_bytes_nrst_stop_t::enum_t val){  option_control.rmw(val) ;}
    inline  void user_option_bytes_nrst_stop_reset(){  option_control.rmw( option_control_t::user_option_bytes_nrst_stop_t::reset) ;}
    inline  void user_option_bytes_nrst_stop_set()  {  option_control.rmw( option_control_t::user_option_bytes_nrst_stop_t::set) ;}
    inline  auto user_option_bytes_nrst_stop()const {  return option_control.rd<option_control_t::user_option_bytes_nrst_stop_t>();}

    inline  void user_option_bytes_nrst_stdby(const option_control_t::user_option_bytes_nrst_stdby_t::enum_t val){  option_control.rmw(val) ;}
    inline  void user_option_bytes_nrst_stdby_reset(){  option_control.rmw( option_control_t::user_option_bytes_nrst_stdby_t::reset) ;}
    inline  void user_option_bytes_nrst_stdby_set()  {  option_control.rmw( option_control_t::user_option_bytes_nrst_stdby_t::set) ;}
    inline  auto user_option_bytes_nrst_stdby()const {  return option_control.rd<option_control_t::user_option_bytes_nrst_stdby_t>();}

    inline  void read_protect(const option_control_t::read_protect_t::enum_t val){  option_control.rmw(val) ;}
    inline  void read_protect_level_0(){  option_control.rmw( option_control_t::read_protect_t::level_0) ;}
    inline  void read_protect_level_1(){  option_control.rmw( option_control_t::read_protect_t::level_1) ;}
    inline  void read_protect_level_2(){  option_control.rmw( option_control_t::read_protect_t::level_2) ;}
    inline  auto read_protect()const {  return option_control.rd<option_control_t::read_protect_t>();}

    inline  void not_write_protect(const option_control_t::read_protect_t::enum_t val){  option_control.rmw(val) ;}
    inline  auto not_write_protect()const {  return option_control.rd<option_control_t::read_protect_t>();}

    access_control_t    access_control;   // ACR;      /*!< FLASH access control register,   Address offset: 0x00 */
    key_t               key;              // KEYR;     /*!< FLASH key register,              Address offset: 0x04 */
    option_key_t        option_key;       // OPTKEYR;  /*!< FLASH option key register,       Address offset: 0x08 */
    status_t            status;           // SR;       /*!< FLASH status register,           Address offset: 0x0C */

    control_t           control;          // CR;       /*!< FLASH control register,          Address offset: 0x10 */
    option_control_t    option_control;   // OPTCR;    /*!< FLASH option control register ,  Address offset: 0x14 */


    inline bool mass_erase( const control_t::program_size_t::enum_t ps = control_t::program_size_t::x32)
     {
	busy_wait() ;
 	if (lock_state() != control_t::lock_t::active) return false ;
 	unlock();
	program_size(ps) ;
	mass_erase_activated() ;
      	start();
      	dsb();
	busy_wait() ;
	mass_erase_deactivated();
	lock();
	return true ;
      }

    inline bool sector_erase( const uint8_t sn , const control_t::program_size_t::enum_t ps = control_t::program_size_t::x32)
      {
   	busy_wait() ;
   	if (lock_state() != control_t::lock_t::active) return false ;
   	unlock();
	program_size(ps) ;
	sector_number(sn);
	sector_erase_activated();
	start();
	dsb();
	busy_wait() ;
	sector_erase_deactivated();
	lock();
	return true ;
      }

    inline bool program(const uint32_t address, const void* data, const uint32_t size, const control_t::program_size_t::enum_t ps = control_t::program_size_t::x32)
      {
    	busy_wait() ;
    	if (lock_state() != control_t::lock_t::active) return false ;
    	unlock();

    	program_size(ps);
        size_t wr = size / (1<<ps) ;

        programming_activated();

        switch ( ps )
        {
          case control_t::program_size_t::x8 :
              for (size_t i = 0; i < wr; i++)
                        { *(((volatile uint8_t*)address)+i) = *(((uint8_t*)data)+i); dsb();}
              break ;
          case control_t::program_size_t::x16 :
              for (size_t i = 0; i < wr; i++)
                        { *(((volatile uint16_t*)address)+i) = *(((uint16_t*)data)+i); dsb();}
              break ;
          case control_t::program_size_t::x32 :
              for (size_t i = 0; i < wr; i++)
                        { *(((volatile uint32_t*)address)+i) = *(((uint32_t*)data)+i); dsb();}
              break ;
          case control_t::program_size_t::x64 :
              for (size_t i = 0; i < wr; i++)
                        { *(((volatile uint64_t*)address)+i) = *(((uint64_t*)data)+i); dsb();}
              break ;
          default :
              programming_deactivated();
      	      lock();
              return false ;

        }

        busy_wait() ;
        programming_deactivated();
	lock();
      	return true ;
      }

    inline bool program_x8(const uint32_t address, const void* data, const uint32_t size)
      {
    	 busy_wait() ;
    	 if (lock_state() != control_t::lock_t::active) return false ;
    	 unlock();
         program_size(control_t::program_size_t::x8);
         programming_activated();
         size_t wr = size / (1<<control_t::program_size_t::x8) ;
         for (size_t i = 0; i < wr; i++)
                  { *(((volatile uint8_t*)address)+i) = *(((uint8_t*)data)+i); dsb(); }
         busy_wait() ;
      	 programming_deactivated();
      	 lock();
      	 return true ;
      }

    inline bool program_x16(const uint32_t address, const void* data, const uint32_t size)
      {
	 busy_wait() ;
	 if (lock_state() != control_t::lock_t::active) return false ;
	 unlock();
         program_size(control_t::program_size_t::x16);
         programming_activated();
         size_t wr = size / (1<<control_t::program_size_t::x16) ;
         for (size_t i = 0; i < wr; i++)
            { *(((volatile uint16_t*)address)+i) = *(((uint16_t*)data)+i); dsb(); }
         busy_wait() ;
	 programming_deactivated();
	 lock();
	 return true ;
      }

    inline bool program_x32(const uint32_t address, const void* data, const uint32_t size)
      {
    	 busy_wait() ;
    	 if (lock_state() != control_t::lock_t::active) return false ;
    	 unlock();
         program_size(control_t::program_size_t::x32);
         programming_activated();
         size_t wr = size / (1<<control_t::program_size_t::x32) ;
         for (size_t i = 0; i < wr; i++)
                  { *(((volatile uint32_t*)address)+i) = *(((uint32_t*)data)+i); dsb(); }
         busy_wait() ;
      	 programming_deactivated();
      	 lock();
      	 return true ;
      }

    inline bool program_x64(const uint32_t address, const void* data, const uint32_t size)
      {
 	 busy_wait() ;
 	 if (lock_state() != control_t::lock_t::active) return false ;
 	 unlock();
         program_size(control_t::program_size_t::x64);
         programming_activated();
         size_t wr = size / (1<<control_t::program_size_t::x64) ;
         for (size_t i = 0; i < wr; i++)
               { *(((volatile uint64_t*)address)+i) = *(((uint64_t*)data)+i); dsb(); }
         busy_wait() ;
   	 programming_deactivated();
   	 lock();
   	 return true ;
      }

    inline bool programm_read_protect( option_control_t::read_protect_t::enum_t level )
      {
         busy_wait() ;
         if (lock_state() != control_t::lock_t::active) return false ;
         option_unlock();
         read_protect(level) ;
         option_start();
         busy_wait() ;
         option_lock();
         return true ;
      }

  };

static flash_t& flash   = *((flash_t*) flash_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __FLASH++_H__ */
