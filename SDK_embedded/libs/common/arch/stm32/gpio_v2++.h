/*
 * gpio++.h
 *
 *  Created on: 30 янв. 2017 г.
 *      Author: klen
 */

#ifndef __GPIO_V2++_H__
#define __GPIO_V2++_H__

#include "types++.h"

// TODO  подумать об необходимости протяжки всех функций с аргументом  enum bit_t как в pin( const bit_t bit )



namespace stm32
{

struct gpio_v2_t
{
  enum pin_index_t { i0=0,     i1,       i2,       i3,       i4,       i5,       i6,       i7,       i8,       i9,       i10,        i11,        i12,        i13,        i14,        i15 } ;
  enum bit_t       { b0=1<<i0, b1=1<<i1, b2=1<<i2, b3=1<<i3, b4=1<<i4, b5=1<<i5, b6=1<<i6, b7=1<<i7, b8=1<<i8, b9=1<<i9, b10=1<<i10, b11=1<<i11, b12=1<<i12, b13=1<<i13, b14=1<<i14, b15=1<<i15 } ;

  struct mode_t : public read_write_32_t
     {
       enum enum_t { mask=0b11, input=0, output, alternate_function, analog, } ;
       struct pin0_t { enum enum_t { offset=0,  mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin1_t { enum enum_t { offset=2,  mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin2_t { enum enum_t { offset=4,  mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin3_t { enum enum_t { offset=6,  mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin4_t { enum enum_t { offset=8,  mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin5_t { enum enum_t { offset=10, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin6_t { enum enum_t { offset=12, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin7_t { enum enum_t { offset=14, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin8_t { enum enum_t { offset=16, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin9_t { enum enum_t { offset=18, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin10_t{ enum enum_t { offset=20, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin11_t{ enum enum_t { offset=22, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin12_t{ enum enum_t { offset=24, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin13_t{ enum enum_t { offset=26, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin14_t{ enum enum_t { offset=28, mask=0b11, input=0, output, alternate_function, analog} ; } ;
       struct pin15_t{ enum enum_t { offset=30, mask=0b11, input=0, output, alternate_function, analog} ; } ;

     };

  inline void pin( const pin_index_t index, const typename mode_t::enum_t val ) { mode.rmw( val, 2 * index ); }
  inline void pin_mode_input( const pin_index_t index )              { pin( index, mode_t::input ); }
  inline void pin_mode_output( const pin_index_t index )             { pin( index, mode_t::output ); }
  inline void pin_mode_alternate_function( const pin_index_t index ) { pin( index, mode_t::alternate_function ); }
  inline void pin_mode_analog( const pin_index_t index )             { pin( index, mode_t::analog ); }
  inline auto pin_mode( const pin_index_t index) const { return mode.rd<mode_t>( 2 * index); }

  inline void pin(const typename mode_t::pin0_t::enum_t val) { mode.rmw(val);}
  inline void pin0_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin0_t::enum_t)val);}
  inline void pin0_mode_input()  { mode.rmw(mode_t::pin0_t::input); }
  inline void pin0_mode_output() { mode.rmw(mode_t::pin0_t::output); }
  inline void pin0_mode_alternate_function() { mode.rmw(mode_t::pin0_t::alternate_function); }
  inline void pin0_mode_analog() { mode.rmw(mode_t::pin0_t::analog); }
  inline auto pin0_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin0_t> ();}

  inline void pin(const typename mode_t::pin1_t::enum_t val) { mode.rmw(val);}
  inline void pin1_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin1_t::enum_t)val);}
  inline void pin1_mode_input()  { mode.rmw(mode_t::pin1_t::input); }
  inline void pin1_mode_output() { mode.rmw(mode_t::pin1_t::output); }
  inline void pin1_mode_alternate_function() { mode.rmw(mode_t::pin1_t::alternate_function); }
  inline void pin1_mode_analog() { mode.rmw(mode_t::pin1_t::analog); }
  inline auto pin1_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin1_t> ();}

  inline void pin(const typename mode_t::pin2_t::enum_t val) { mode.rmw(val);}
  inline void pin2_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin2_t::enum_t)val);}
  inline void pin2_mode_input()  { mode.rmw(mode_t::pin2_t::input); }
  inline void pin2_mode_output() { mode.rmw(mode_t::pin2_t::output); }
  inline void pin2_mode_alternate_function() { mode.rmw(mode_t::pin2_t::alternate_function); }
  inline void pin2_mode_analog() { mode.rmw(mode_t::pin2_t::analog); }
  inline auto pin2_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin2_t> ();}

  inline void pin(const typename mode_t::pin3_t::enum_t val) { mode.rmw(val);}
  inline void pin3_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin3_t::enum_t)val);}
  inline void pin3_mode_input()  { mode.rmw(mode_t::pin3_t::input); }
  inline void pin3_mode_output() { mode.rmw(mode_t::pin3_t::output); }
  inline void pin3_mode_alternate_function() { mode.rmw(mode_t::pin3_t::alternate_function); }
  inline void pin3_mode_analog() { mode.rmw(mode_t::pin3_t::analog); }
  inline auto pin3_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin3_t> ();}

  inline void pin(const typename mode_t::pin4_t::enum_t val) { mode.rmw(val);}
  inline void pin4_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin4_t::enum_t)val);}
  inline void pin4_mode_input()  { mode.rmw(mode_t::pin4_t::input); }
  inline void pin4_mode_output() { mode.rmw(mode_t::pin4_t::output); }
  inline void pin4_mode_alternate_function() { mode.rmw(mode_t::pin4_t::alternate_function); }
  inline void pin4_mode_analog() { mode.rmw(mode_t::pin4_t::analog); }
  inline auto pin4_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin4_t> ();}

  inline void pin(const typename mode_t::pin5_t::enum_t val) { mode.rmw(val);}
  inline void pin5_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin5_t::enum_t)val);}
  inline void pin5_mode_input()  { mode.rmw(mode_t::pin5_t::input); }
  inline void pin5_mode_output() { mode.rmw(mode_t::pin5_t::output); }
  inline void pin5_mode_alternate_function() { mode.rmw(mode_t::pin5_t::alternate_function); }
  inline void pin5_mode_analog() { mode.rmw(mode_t::pin5_t::analog); }
  inline auto pin5_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin5_t> ();}

  inline void pin(const typename mode_t::pin6_t::enum_t val) { mode.rmw(val);}
  inline void pin6_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin6_t::enum_t)val);}
  inline void pin6_mode_input()  { mode.rmw(mode_t::pin6_t::input); }
  inline void pin6_mode_output() { mode.rmw(mode_t::pin6_t::output); }
  inline void pin6_mode_alternate_function() { mode.rmw(mode_t::pin6_t::alternate_function); }
  inline void pin6_mode_analog() { mode.rmw(mode_t::pin6_t::analog); }
  inline auto pin6_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin6_t> ();}

  inline void pin(const typename mode_t::pin7_t::enum_t val) { mode.rmw(val);}
  inline void pin7_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin7_t::enum_t)val);}
  inline void pin7_mode_input()  { mode.rmw(mode_t::pin7_t::input); }
  inline void pin7_mode_output() { mode.rmw(mode_t::pin7_t::output); }
  inline void pin7_mode_alternate_function() { mode.rmw(mode_t::pin7_t::alternate_function); }
  inline void pin7_mode_analog() { mode.rmw(mode_t::pin7_t::analog); }
  inline auto pin7_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin7_t> ();}

  inline void pin(const typename mode_t::pin8_t::enum_t val) { mode.rmw(val);}
  inline void pin8_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin8_t::enum_t)val);}
  inline void pin8_mode_input()  { mode.rmw(mode_t::pin8_t::input); }
  inline void pin8_mode_output() { mode.rmw(mode_t::pin8_t::output); }
  inline void pin8_mode_alternate_function() { mode.rmw(mode_t::pin8_t::alternate_function); }
  inline void pin8_mode_analog() { mode.rmw(mode_t::pin8_t::analog); }
  inline auto pin8_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin8_t> ();}

  inline void pin(const typename mode_t::pin9_t::enum_t val) { mode.rmw(val);}
  inline void pin9_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin9_t::enum_t)val);}
  inline void pin9_mode_input()  { mode.rmw(mode_t::pin9_t::input); }
  inline void pin9_mode_output() { mode.rmw(mode_t::pin9_t::output); }
  inline void pin9_mode_alternate_function() { mode.rmw(mode_t::pin9_t::alternate_function); }
  inline void pin9_mode_analog() { mode.rmw(mode_t::pin9_t::analog); }
  inline auto pin9_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin9_t> ();}

  inline void pin(const typename mode_t::pin10_t::enum_t val) { mode.rmw(val);}
  inline void pin10_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin10_t::enum_t)val);}
  inline void pin10_mode_input()  { mode.rmw(mode_t::pin10_t::input); }
  inline void pin10_mode_output() { mode.rmw(mode_t::pin10_t::output); }
  inline void pin10_mode_alternate_function() { mode.rmw(mode_t::pin10_t::alternate_function); }
  inline void pin10_mode_analog() { mode.rmw(mode_t::pin10_t::analog); }
  inline auto pin10_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin10_t> ();}

  inline void pin(const typename mode_t::pin11_t::enum_t val) { mode.rmw(val);}
  inline void pin11_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin11_t::enum_t)val);}
  inline void pin11_mode_input()  { mode.rmw(mode_t::pin11_t::input); }
  inline void pin11_mode_output() { mode.rmw(mode_t::pin11_t::output); }
  inline void pin11_mode_alternate_function() { mode.rmw(mode_t::pin11_t::alternate_function); }
  inline void pin11_mode_analog() { mode.rmw(mode_t::pin11_t::analog); }
  inline auto pin11_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin11_t> ();}

  inline void pin(const typename mode_t::pin12_t::enum_t val) { mode.rmw(val);}
  inline void pin12_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin12_t::enum_t)val);}
  inline void pin12_mode_input()  { mode.rmw(mode_t::pin12_t::input); }
  inline void pin12_mode_output() { mode.rmw(mode_t::pin12_t::output); }
  inline void pin12_mode_alternate_function() { mode.rmw(mode_t::pin12_t::alternate_function); }
  inline void pin12_mode_analog() { mode.rmw(mode_t::pin12_t::analog); }
  inline auto pin12_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin12_t> ();}

  inline void pin(const typename mode_t::pin13_t::enum_t val) { mode.rmw(val);}
  inline void pin13_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin13_t::enum_t)val);}
  inline void pin13_mode_input()  { mode.rmw(mode_t::pin13_t::input); }
  inline void pin13_mode_output() { mode.rmw(mode_t::pin13_t::output); }
  inline void pin13_mode_alternate_function() { mode.rmw(mode_t::pin13_t::alternate_function); }
  inline void pin13_mode_analog() { mode.rmw(mode_t::pin13_t::analog); }
  inline auto pin13_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin13_t> ();}

  inline void pin(const typename mode_t::pin14_t::enum_t val) { mode.rmw(val);}
  inline void pin14_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin14_t::enum_t)val);}
  inline void pin14_mode_input()  { mode.rmw(mode_t::pin14_t::input); }
  inline void pin14_mode_output() { mode.rmw(mode_t::pin14_t::output); }
  inline void pin14_mode_alternate_function() { mode.rmw(mode_t::pin14_t::alternate_function); }
  inline void pin14_mode_analog() { mode.rmw(mode_t::pin14_t::analog); }
  inline auto pin14_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin14_t> ();}

  inline void pin(const typename mode_t::pin15_t::enum_t val) { mode.rmw(val);}
  inline void pin15_mode(const typename mode_t::enum_t val) { mode.rmw((mode_t::pin15_t::enum_t)val);}
  inline void pin15_mode_input()  { mode.rmw(mode_t::pin15_t::input); }
  inline void pin15_mode_output() { mode.rmw(mode_t::pin15_t::output); }
  inline void pin15_mode_alternate_function() { mode.rmw(mode_t::pin15_t::alternate_function); }
  inline void pin15_mode_analog() { mode.rmw(mode_t::pin15_t::analog); }
  inline auto pin15_mode() const {  return (mode_t::enum_t)mode.rd<mode_t::pin15_t> ();}

  struct output_type_t : public read_write_32_t
     {
       enum enum_t { mask=0b1, pull_push=0, open_drain,  } ;
       struct pin0_t { enum enum_t { offset=0,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin1_t { enum enum_t { offset=1,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin2_t { enum enum_t { offset=2,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin3_t { enum enum_t { offset=3,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin4_t { enum enum_t { offset=4,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin5_t { enum enum_t { offset=5,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin6_t { enum enum_t { offset=6,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin7_t { enum enum_t { offset=7,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin8_t { enum enum_t { offset=8,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin9_t { enum enum_t { offset=9,  mask=1, pull_push=0, open_drain} ; } ;
       struct pin10_t{ enum enum_t { offset=10, mask=1, pull_push=0, open_drain} ; } ;
       struct pin11_t{ enum enum_t { offset=11, mask=1, pull_push=0, open_drain} ; } ;
       struct pin12_t{ enum enum_t { offset=12, mask=1, pull_push=0, open_drain} ; } ;
       struct pin13_t{ enum enum_t { offset=13, mask=1, pull_push=0, open_drain} ; } ;
       struct pin14_t{ enum enum_t { offset=14, mask=1, pull_push=0, open_drain} ; } ;
       struct pin15_t{ enum enum_t { offset=15, mask=1, pull_push=0, open_drain} ; } ;
     };

  inline void pin( const pin_index_t index, const output_type_t::enum_t val ) { output_type.rmw( val, index ); }
  inline void pin_output_type_pull_push ( const pin_index_t index ) { pin( index, output_type_t::pull_push ); }
  inline void pin_output_type_open_drain( const pin_index_t index ) { pin( index, output_type_t::open_drain); }
  inline auto pin_output_type( const pin_index_t index) const { return output_type.rd<output_type_t>( index); }

  inline void pin(output_type_t::pin0_t::enum_t val) { output_type.rmw(val);}
  inline void pin0_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin0_t::enum_t)val);}
  inline void pin0_output_type_pull_push()  { output_type.rmw(output_type_t::pin0_t::pull_push); }
  inline void pin0_output_type_open_drain() { output_type.rmw(output_type_t::pin0_t::open_drain); }
  inline auto pin0_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin0_t> ();}

  inline void pin(output_type_t::pin1_t::enum_t val) { output_type.rmw(val);}
  inline void pin1_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin1_t::enum_t)val);}
  inline void pin1_output_type_pull_push()  { output_type.rmw(output_type_t::pin1_t::pull_push); }
  inline void pin1_output_type_open_drain() { output_type.rmw(output_type_t::pin1_t::open_drain); }
  inline auto pin1_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin1_t> ();}

  inline void pin(output_type_t::pin2_t::enum_t val) { output_type.rmw(val);}
  inline void pin2_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin2_t::enum_t)val);}
  inline void pin2_output_type_pull_push()  { output_type.rmw(output_type_t::pin2_t::pull_push); }
  inline void pin2_output_type_open_drain() { output_type.rmw(output_type_t::pin2_t::open_drain); }
  inline auto pin2_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin2_t> ();}

  inline void pin(output_type_t::pin3_t::enum_t val) { output_type.rmw(val);}
  inline void pin3_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin3_t::enum_t)val);}
  inline void pin3_output_type_pull_push()  { output_type.rmw(output_type_t::pin3_t::pull_push); }
  inline void pin3_output_type_open_drain() { output_type.rmw(output_type_t::pin3_t::open_drain); }
  inline auto pin3_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin3_t> ();}

  inline void pin(output_type_t::pin4_t::enum_t val) { output_type.rmw(val);}
  inline void pin4_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin4_t::enum_t)val);}
  inline void pin4_output_type_pull_push()  { output_type.rmw(output_type_t::pin4_t::pull_push); }
  inline void pin4_output_type_open_drain() { output_type.rmw(output_type_t::pin4_t::open_drain); }
  inline auto pin4_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin4_t> ();}

  inline void pin(output_type_t::pin5_t::enum_t val) { output_type.rmw(val);}
  inline void pin5_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin5_t::enum_t)val);}
  inline void pin5_output_type_pull_push()  { output_type.rmw(output_type_t::pin5_t::pull_push); }
  inline void pin5_output_type_open_drain() { output_type.rmw(output_type_t::pin5_t::open_drain); }
  inline auto pin5_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin5_t> ();}

  inline void pin(output_type_t::pin6_t::enum_t val) { output_type.rmw(val);}
  inline void pin6_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin6_t::enum_t)val);}
  inline void pin6_output_type_pull_push()  { output_type.rmw(output_type_t::pin6_t::pull_push); }
  inline void pin6_output_type_open_drain() { output_type.rmw(output_type_t::pin6_t::open_drain); }
  inline auto pin6_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin6_t> ();}

  inline void pin(output_type_t::pin7_t::enum_t val) { output_type.rmw(val);}
  inline void pin7_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin7_t::enum_t)val);}
  inline void pin7_output_type_pull_push()  { output_type.rmw(output_type_t::pin7_t::pull_push); }
  inline void pin7_output_type_open_drain() { output_type.rmw(output_type_t::pin7_t::open_drain); }
  inline auto pin7_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin7_t> ();}

  inline void pin(output_type_t::pin8_t::enum_t val) { output_type.rmw(val);}
  inline void pin8_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin8_t::enum_t)val);}
  inline void pin8_output_type_pull_push()  { output_type.rmw(output_type_t::pin8_t::pull_push); }
  inline void pin8_output_type_open_drain() { output_type.rmw(output_type_t::pin8_t::open_drain); }
  inline auto pin8_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin8_t> ();}

  inline void pin(output_type_t::pin9_t::enum_t val) { output_type.rmw(val);}
  inline void pin9_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin9_t::enum_t)val);}
  inline void pin9_output_type_pull_push()  { output_type.rmw(output_type_t::pin9_t::pull_push); }
  inline void pin9_output_type_open_drain() { output_type.rmw(output_type_t::pin9_t::open_drain); }
  inline auto pin9_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin9_t> ();}

  inline void pin(output_type_t::pin10_t::enum_t val) { output_type.rmw(val);}
  inline void pin10_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin10_t::enum_t)val);}
  inline void pin10_output_type_pull_push()  { output_type.rmw(output_type_t::pin10_t::pull_push); }
  inline void pin10_output_type_open_drain() { output_type.rmw(output_type_t::pin10_t::open_drain); }
  inline auto pin10_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin10_t> ();}

  inline void pin(output_type_t::pin11_t::enum_t val) { output_type.rmw(val);}
  inline void pin11_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin11_t::enum_t)val);}
  inline void pin11_output_type_pull_push()  { output_type.rmw(output_type_t::pin11_t::pull_push); }
  inline void pin11_output_type_open_drain() { output_type.rmw(output_type_t::pin11_t::open_drain); }
  inline auto pin11_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin11_t> ();}

  inline void pin(output_type_t::pin12_t::enum_t val) { output_type.rmw(val);}
  inline void pin12_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin12_t::enum_t)val);}
  inline void pin12_output_type_pull_push()  { output_type.rmw(output_type_t::pin12_t::pull_push); }
  inline void pin12_output_type_open_drain() { output_type.rmw(output_type_t::pin12_t::open_drain); }
  inline auto pin12_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin12_t> ();}

  inline void pin(output_type_t::pin13_t::enum_t val) { output_type.rmw(val);}
  inline void pin13_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin13_t::enum_t)val);}
  inline void pin13_output_type_pull_push()  { output_type.rmw(output_type_t::pin13_t::pull_push); }
  inline void pin13_output_type_open_drain() { output_type.rmw(output_type_t::pin13_t::open_drain); }
  inline auto pin13_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin13_t> ();}

  inline void pin(output_type_t::pin14_t::enum_t val) { output_type.rmw(val);}
  inline void pin14_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin14_t::enum_t)val);}
  inline void pin14_output_type_pull_push()  { output_type.rmw(output_type_t::pin14_t::pull_push); }
  inline void pin14_output_type_open_drain() { output_type.rmw(output_type_t::pin14_t::open_drain); }
  inline auto pin14_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin14_t> ();}

  inline void pin(output_type_t::pin15_t::enum_t val) { output_type.rmw(val);}
  inline void pin15_output_type(const output_type_t::enum_t val) { output_type.rmw((output_type_t::pin15_t::enum_t)val);}
  inline void pin15_output_type_pull_push()  { output_type.rmw(output_type_t::pin15_t::pull_push); }
  inline void pin15_output_type_open_drain() { output_type.rmw(output_type_t::pin15_t::open_drain); }
  inline auto pin15_output_type() const {  return (output_type_t::enum_t)output_type.rd<output_type_t::pin15_t> ();}

  struct output_speed_t : public read_write_32_t
       {
         enum enum_t { mask=0b11, low=0, medium, high, very_high } ;
         struct pin0_t { enum enum_t { offset=0,  mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin1_t { enum enum_t { offset=2,  mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin2_t { enum enum_t { offset=4,  mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin3_t { enum enum_t { offset=6,  mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin4_t { enum enum_t { offset=8,  mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin5_t { enum enum_t { offset=10, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin6_t { enum enum_t { offset=12, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin7_t { enum enum_t { offset=14, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin8_t { enum enum_t { offset=16, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin9_t { enum enum_t { offset=18, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin10_t{ enum enum_t { offset=20, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin11_t{ enum enum_t { offset=22, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin12_t{ enum enum_t { offset=24, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin13_t{ enum enum_t { offset=26, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin14_t{ enum enum_t { offset=28, mask=0b11, low=0, medium, high, very_high} ; } ;
         struct pin15_t{ enum enum_t { offset=30, mask=0b11, low=0, medium, high, very_high} ; } ;
       };

    inline void pin( const pin_index_t index, const output_speed_t::enum_t val ) { output_speed.rmw( val, 2*index ); }
    inline void pin_output_speed_low( const pin_index_t index )       { pin( index, output_speed_t::low ); }
    inline void pin_output_speed_medium( const pin_index_t index )    { pin( index, output_speed_t::medium); }
    inline void pin_output_speed_high( const pin_index_t index )      { pin( index, output_speed_t::high ); }
    inline void pin_output_speed_very_high( const pin_index_t index ) { pin( index, output_speed_t::very_high); }
    inline auto pin_output_speed( const pin_index_t index) const { return output_speed.rd<output_speed_t>( 2*index); }

    inline void pin(const output_speed_t::pin0_t::enum_t val) { output_speed.rmw(val);}
    inline void pin0_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin0_t::enum_t)val);}
    inline void pin0_output_speed_low()  { output_speed.rmw(output_speed_t::pin0_t::low); }
    inline void pin0_output_speed_medium() { output_speed.rmw(output_speed_t::pin0_t::medium); }
    inline void pin0_output_speed_high()  { output_speed.rmw(output_speed_t::pin0_t::high); }
    inline void pin0_output_speed_very_high() { output_speed.rmw(output_speed_t::pin0_t::very_high); }
    inline auto pin0_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin0_t> ();}

    inline void pin(const output_speed_t::pin1_t::enum_t val) { output_speed.rmw(val);}
    inline void pin1_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin1_t::enum_t)val);}
    inline void pin1_output_speed_low()  { output_speed.rmw(output_speed_t::pin1_t::low); }
    inline void pin1_output_speed_medium() { output_speed.rmw(output_speed_t::pin1_t::medium); }
    inline void pin1_output_speed_high()  { output_speed.rmw(output_speed_t::pin1_t::high); }
    inline void pin1_output_speed_very_high() { output_speed.rmw(output_speed_t::pin1_t::very_high); }
    inline auto pin1_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin1_t> ();}

    inline void pin(const output_speed_t::pin2_t::enum_t val) { output_speed.rmw(val);}
    inline void pin2_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin2_t::enum_t)val);}
    inline void pin2_output_speed_low()  { output_speed.rmw(output_speed_t::pin2_t::low); }
    inline void pin2_output_speed_medium() { output_speed.rmw(output_speed_t::pin2_t::medium); }
    inline void pin2_output_speed_high()  { output_speed.rmw(output_speed_t::pin2_t::high); }
    inline void pin2_output_speed_very_high() { output_speed.rmw(output_speed_t::pin2_t::very_high); }
    inline auto pin2_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin2_t> ();}

    inline void pin(const output_speed_t::pin3_t::enum_t val) { output_speed.rmw(val);}
    inline void pin3_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin3_t::enum_t)val);}
    inline void pin3_output_speed_low()  { output_speed.rmw(output_speed_t::pin3_t::low); }
    inline void pin3_output_speed_medium() { output_speed.rmw(output_speed_t::pin3_t::medium); }
    inline void pin3_output_speed_high()  { output_speed.rmw(output_speed_t::pin3_t::high); }
    inline void pin3_output_speed_very_high() { output_speed.rmw(output_speed_t::pin3_t::very_high); }
    inline auto pin3_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin3_t> ();}

    inline void pin(const output_speed_t::pin4_t::enum_t val) { output_speed.rmw(val);}
    inline void pin4_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin4_t::enum_t)val);}
    inline void pin4_output_speed_low()  { output_speed.rmw(output_speed_t::pin4_t::low); }
    inline void pin4_output_speed_medium() { output_speed.rmw(output_speed_t::pin4_t::medium); }
    inline void pin4_output_speed_high()  { output_speed.rmw(output_speed_t::pin4_t::high); }
    inline void pin4_output_speed_very_high() { output_speed.rmw(output_speed_t::pin4_t::very_high); }
    inline auto pin4_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin4_t> ();}

    inline void pin(const output_speed_t::pin5_t::enum_t val) { output_speed.rmw(val);}
    inline void pin5_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin5_t::enum_t)val);}
    inline void pin5_output_speed_low()  { output_speed.rmw(output_speed_t::pin5_t::low); }
    inline void pin5_output_speed_medium() { output_speed.rmw(output_speed_t::pin5_t::medium); }
    inline void pin5_output_speed_high()  { output_speed.rmw(output_speed_t::pin5_t::high); }
    inline void pin5_output_speed_very_high() { output_speed.rmw(output_speed_t::pin5_t::very_high); }
    inline auto pin5_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin5_t> ();}

    inline void pin(const output_speed_t::pin6_t::enum_t val) { output_speed.rmw(val);}
    inline void pin6_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin6_t::enum_t)val);}
    inline void pin6_output_speed_low()  { output_speed.rmw(output_speed_t::pin6_t::low); }
    inline void pin6_output_speed_medium() { output_speed.rmw(output_speed_t::pin6_t::medium); }
    inline void pin6_output_speed_high()  { output_speed.rmw(output_speed_t::pin6_t::high); }
    inline void pin6_output_speed_very_high() { output_speed.rmw(output_speed_t::pin6_t::very_high); }
    inline auto pin6_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin6_t> ();}

    inline void pin(const output_speed_t::pin7_t::enum_t val) { output_speed.rmw(val);}
    inline void pin7_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin7_t::enum_t)val);}
    inline void pin7_output_speed_low()  { output_speed.rmw(output_speed_t::pin7_t::low); }
    inline void pin7_output_speed_medium() { output_speed.rmw(output_speed_t::pin7_t::medium); }
    inline void pin7_output_speed_high()  { output_speed.rmw(output_speed_t::pin7_t::high); }
    inline void pin7_output_speed_very_high() { output_speed.rmw(output_speed_t::pin7_t::very_high); }
    inline auto pin7_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin7_t> ();}

    inline void pin(const output_speed_t::pin8_t::enum_t val) { output_speed.rmw(val);}
    inline void pin8_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin8_t::enum_t)val);}
    inline void pin8_output_speed_low()  { output_speed.rmw(output_speed_t::pin8_t::low); }
    inline void pin8_output_speed_medium() { output_speed.rmw(output_speed_t::pin8_t::medium); }
    inline void pin8_output_speed_high()  { output_speed.rmw(output_speed_t::pin8_t::high); }
    inline void pin8_output_speed_very_high() { output_speed.rmw(output_speed_t::pin8_t::very_high); }
    inline auto pin8_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin8_t> ();}

    inline void pin(const output_speed_t::pin9_t::enum_t val) { output_speed.rmw(val);}
    inline void pin9_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin9_t::enum_t)val);}
    inline void pin9_output_speed_low()  { output_speed.rmw(output_speed_t::pin9_t::low); }
    inline void pin9_output_speed_medium() { output_speed.rmw(output_speed_t::pin9_t::medium); }
    inline void pin9_output_speed_high()  { output_speed.rmw(output_speed_t::pin9_t::high); }
    inline void pin9_output_speed_very_high() { output_speed.rmw(output_speed_t::pin9_t::very_high); }
    inline auto pin9_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin9_t> ();}

    inline void pin(const output_speed_t::pin10_t::enum_t val) { output_speed.rmw(val);}
    inline void pin10_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin10_t::enum_t)val);}
    inline void pin10_output_speed_low()  { output_speed.rmw(output_speed_t::pin10_t::low); }
    inline void pin10_output_speed_medium() { output_speed.rmw(output_speed_t::pin10_t::medium); }
    inline void pin10_output_speed_high()  { output_speed.rmw(output_speed_t::pin10_t::high); }
    inline void pin10_output_speed_very_high() { output_speed.rmw(output_speed_t::pin10_t::very_high); }
    inline auto pin10_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin10_t> ();}

    inline void pin(const output_speed_t::pin11_t::enum_t val) { output_speed.rmw(val);}
    inline void pin11_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin11_t::enum_t)val);}
    inline void pin11_output_speed_low()  { output_speed.rmw(output_speed_t::pin11_t::low); }
    inline void pin11_output_speed_medium() { output_speed.rmw(output_speed_t::pin11_t::medium); }
    inline void pin11_output_speed_high()  { output_speed.rmw(output_speed_t::pin11_t::high); }
    inline void pin11_output_speed_very_high() { output_speed.rmw(output_speed_t::pin11_t::very_high); }
    inline auto pin11_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin11_t> ();}

    inline void pin(const output_speed_t::pin12_t::enum_t val) { output_speed.rmw(val);}
    inline void pin12_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin12_t::enum_t)val);}
    inline void pin12_output_speed_low()  { output_speed.rmw(output_speed_t::pin12_t::low); }
    inline void pin12_output_speed_medium() { output_speed.rmw(output_speed_t::pin12_t::medium); }
    inline void pin12_output_speed_high()  { output_speed.rmw(output_speed_t::pin12_t::high); }
    inline void pin12_output_speed_very_high() { output_speed.rmw(output_speed_t::pin12_t::very_high); }
    inline auto pin12_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin12_t> ();}

    inline void pin(const output_speed_t::pin13_t::enum_t val) { output_speed.rmw(val);}
    inline void pin13_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin13_t::enum_t)val);}
    inline void pin13_output_speed_low()  { output_speed.rmw(output_speed_t::pin13_t::low); }
    inline void pin13_output_speed_medium() { output_speed.rmw(output_speed_t::pin13_t::medium); }
    inline void pin13_output_speed_high()  { output_speed.rmw(output_speed_t::pin13_t::high); }
    inline void pin13_output_speed_very_high() { output_speed.rmw(output_speed_t::pin13_t::very_high); }
    inline auto pin13_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin13_t> ();}

    inline void pin(const output_speed_t::pin14_t::enum_t val) { output_speed.rmw(val);}
    inline void pin14_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin14_t::enum_t)val);}
    inline void pin14_output_speed_low()  { output_speed.rmw(output_speed_t::pin14_t::low); }
    inline void pin14_output_speed_medium() { output_speed.rmw(output_speed_t::pin14_t::medium); }
    inline void pin14_output_speed_high()  { output_speed.rmw(output_speed_t::pin14_t::high); }
    inline void pin14_output_speed_very_high() { output_speed.rmw(output_speed_t::pin14_t::very_high); }
    inline auto pin14_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin14_t> ();}

    inline void pin(const output_speed_t::pin15_t::enum_t val) { output_speed.rmw(val);}
    inline void pin15_output_speed(const output_speed_t::enum_t val) { output_speed.rmw((output_speed_t::pin15_t::enum_t)val);}
    inline void pin15_output_speed_low()  { output_speed.rmw(output_speed_t::pin15_t::low); }
    inline void pin15_output_speed_medium() { output_speed.rmw(output_speed_t::pin15_t::medium); }
    inline void pin15_output_speed_high()  { output_speed.rmw(output_speed_t::pin15_t::high); }
    inline void pin15_output_speed_very_high() { output_speed.rmw(output_speed_t::pin15_t::very_high); }
    inline auto pin15_output_speed() const {  return (output_speed_t::enum_t)output_speed.rd<output_speed_t::pin15_t> ();}

    struct pull_t : public read_write_32_t
         {
           enum enum_t { mask=0b11, no=0, up, down } ;
           struct pin0_t { enum enum_t { offset=0,  mask=0b11, no=0, up, down} ; } ;
           struct pin1_t { enum enum_t { offset=2,  mask=0b11, no=0, up, down} ; } ;
           struct pin2_t { enum enum_t { offset=4,  mask=0b11, no=0, up, down} ; } ;
           struct pin3_t { enum enum_t { offset=6,  mask=0b11, no=0, up, down} ; } ;
           struct pin4_t { enum enum_t { offset=8,  mask=0b11, no=0, up, down} ; } ;
           struct pin5_t { enum enum_t { offset=10, mask=0b11, no=0, up, down} ; } ;
           struct pin6_t { enum enum_t { offset=12, mask=0b11, no=0, up, down} ; } ;
           struct pin7_t { enum enum_t { offset=14, mask=0b11, no=0, up, down} ; } ;
           struct pin8_t { enum enum_t { offset=16, mask=0b11, no=0, up, down} ; } ;
           struct pin9_t { enum enum_t { offset=18, mask=0b11, no=0, up, down} ; } ;
           struct pin10_t{ enum enum_t { offset=20, mask=0b11, no=0, up, down} ; } ;
           struct pin11_t{ enum enum_t { offset=22, mask=0b11, no=0, up, down} ; } ;
           struct pin12_t{ enum enum_t { offset=24, mask=0b11, no=0, up, down} ; } ;
           struct pin13_t{ enum enum_t { offset=26, mask=0b11, no=0, up, down} ; } ;
           struct pin14_t{ enum enum_t { offset=28, mask=0b11, no=0, up, down} ; } ;
           struct pin15_t{ enum enum_t { offset=30, mask=0b11, no=0, up, down} ; } ;
         };

      inline void pin( const pin_index_t index, const pull_t::enum_t val ) { pull.rmw( val, 2*index );  }
      inline void pin_pull_no( const pin_index_t index )    { pin( index, pull_t::no ); }
      inline void pin_pull_up( const pin_index_t index )    { pin( index, pull_t::up); }
      inline void pin_pull_down( const pin_index_t index )  { pin( index, pull_t::down ); }
      inline auto pin_pull( const pin_index_t index) const  { return pull.rd<pull_t>( 2*index); }

      inline void pin(const pull_t::pin0_t::enum_t val) { pull.rmw(val);}
      inline void pin0_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin0_t::enum_t)val);}
      inline void pin0_pull_no()   { pull.rmw(pull_t::pin0_t::no); }
      inline void pin0_pull_up()   { pull.rmw(pull_t::pin0_t::up); }
      inline void pin0_pull_down() { pull.rmw(pull_t::pin0_t::down); }
      inline auto pin0_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin0_t> ();}

      inline void pin(const pull_t::pin1_t::enum_t val) { pull.rmw(val);}
      inline void pin1_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin1_t::enum_t)val);}
      inline void pin1_pull_no()   { pull.rmw(pull_t::pin1_t::no); }
      inline void pin1_pull_up()   { pull.rmw(pull_t::pin1_t::up); }
      inline void pin1_pull_down() { pull.rmw(pull_t::pin1_t::down); }
      inline auto pin1_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin1_t> ();}

      inline void pin(const pull_t::pin2_t::enum_t val) { pull.rmw(val);}
      inline void pin2_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin2_t::enum_t)val);}
      inline void pin2_pull_no()   { pull.rmw(pull_t::pin2_t::no); }
      inline void pin2_pull_up()   { pull.rmw(pull_t::pin2_t::up); }
      inline void pin2_pull_down() { pull.rmw(pull_t::pin2_t::down); }
      inline auto pin2_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin2_t> ();}

      inline void pin(const pull_t::pin3_t::enum_t val) { pull.rmw(val);}
      inline void pin3_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin3_t::enum_t)val);}
      inline void pin3_pull_no()   { pull.rmw(pull_t::pin3_t::no); }
      inline void pin3_pull_up()   { pull.rmw(pull_t::pin3_t::up); }
      inline void pin3_pull_down() { pull.rmw(pull_t::pin3_t::down); }
      inline auto pin3_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin3_t> ();}

      inline void pin(const pull_t::pin4_t::enum_t val) { pull.rmw(val);}
      inline void pin4_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin4_t::enum_t)val);}
      inline void pin4_pull_no()   { pull.rmw(pull_t::pin4_t::no); }
      inline void pin4_pull_up()   { pull.rmw(pull_t::pin4_t::up); }
      inline void pin4_pull_down() { pull.rmw(pull_t::pin4_t::down); }
      inline auto pin4_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin4_t> ();}

      inline void pin(const pull_t::pin5_t::enum_t val) { pull.rmw(val);}
      inline void pin5_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin5_t::enum_t)val);}
      inline void pin5_pull_no()   { pull.rmw(pull_t::pin5_t::no); }
      inline void pin5_pull_up()   { pull.rmw(pull_t::pin5_t::up); }
      inline void pin5_pull_down() { pull.rmw(pull_t::pin5_t::down); }
      inline auto pin5_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin5_t> ();}

      inline void pin(const pull_t::pin6_t::enum_t val) { pull.rmw(val);}
      inline void pin6_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin6_t::enum_t)val);}
      inline void pin6_pull_no()   { pull.rmw(pull_t::pin6_t::no); }
      inline void pin6_pull_up()   { pull.rmw(pull_t::pin6_t::up); }
      inline void pin6_pull_down() { pull.rmw(pull_t::pin6_t::down); }
      inline auto pin6_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin6_t> ();}

      inline void pin(const pull_t::pin7_t::enum_t val) { pull.rmw(val);}
      inline void pin7_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin7_t::enum_t)val);}
      inline void pin7_pull_no()   { pull.rmw(pull_t::pin7_t::no); }
      inline void pin7_pull_up()   { pull.rmw(pull_t::pin7_t::up); }
      inline void pin7_pull_down() { pull.rmw(pull_t::pin7_t::down); }
      inline auto pin7_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin7_t> ();}

      inline void pin(const pull_t::pin8_t::enum_t val) { pull.rmw(val);}
      inline void pin8_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin8_t::enum_t)val);}
      inline void pin8_pull_no()   { pull.rmw(pull_t::pin8_t::no); }
      inline void pin8_pull_up()   { pull.rmw(pull_t::pin8_t::up); }
      inline void pin8_pull_down() { pull.rmw(pull_t::pin8_t::down); }
      inline auto pin8_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin8_t> ();}

      inline void pin(const pull_t::pin9_t::enum_t val) { pull.rmw(val);}
      inline void pin9_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin9_t::enum_t)val);}
      inline void pin9_pull_no()   { pull.rmw(pull_t::pin9_t::no); }
      inline void pin9_pull_up()   { pull.rmw(pull_t::pin9_t::up); }
      inline void pin9_pull_down() { pull.rmw(pull_t::pin9_t::down); }
      inline auto pin9_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin9_t> ();}

      inline void pin(const pull_t::pin10_t::enum_t val) { pull.rmw(val);}
      inline void pin10_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin10_t::enum_t)val);}
      inline void pin10_pull_no()   { pull.rmw(pull_t::pin10_t::no); }
      inline void pin10_pull_up()   { pull.rmw(pull_t::pin10_t::up); }
      inline void pin10_pull_down() { pull.rmw(pull_t::pin10_t::down); }
      inline auto pin10_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin10_t> ();}

      inline void pin(const pull_t::pin11_t::enum_t val) { pull.rmw(val);}
      inline void pin11_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin11_t::enum_t)val);}
      inline void pin11_pull_no()   { pull.rmw(pull_t::pin11_t::no); }
      inline void pin11_pull_up()   { pull.rmw(pull_t::pin11_t::up); }
      inline void pin11_pull_down() { pull.rmw(pull_t::pin11_t::down); }
      inline auto pin11_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin11_t> ();}

      inline void pin(const pull_t::pin12_t::enum_t val) { pull.rmw(val);}
      inline void pin12_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin12_t::enum_t)val);}
      inline void pin12_pull_no()   { pull.rmw(pull_t::pin12_t::no); }
      inline void pin12_pull_up()   { pull.rmw(pull_t::pin12_t::up); }
      inline void pin12_pull_down() { pull.rmw(pull_t::pin12_t::down); }
      inline auto pin12_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin12_t> ();}

      inline void pin(const pull_t::pin13_t::enum_t val) { pull.rmw(val);}
      inline void pin13_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin13_t::enum_t)val);}
      inline void pin13_pull_no()   { pull.rmw(pull_t::pin13_t::no); }
      inline void pin13_pull_up()   { pull.rmw(pull_t::pin13_t::up); }
      inline void pin13_pull_down() { pull.rmw(pull_t::pin13_t::down); }
      inline auto pin13_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin13_t> ();}

      inline void pin(const pull_t::pin14_t::enum_t val) { pull.rmw(val);}
      inline void pin14_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin14_t::enum_t)val);}
      inline void pin14_pull_no()   { pull.rmw(pull_t::pin14_t::no); }
      inline void pin14_pull_up()   { pull.rmw(pull_t::pin14_t::up); }
      inline void pin14_pull_down() { pull.rmw(pull_t::pin14_t::down); }
      inline auto pin14_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin14_t> ();}

      inline void pin(const pull_t::pin15_t::enum_t val) { pull.rmw(val);}
      inline void pin15_pull(const pull_t::enum_t val) { pull.rmw((pull_t::pin15_t::enum_t)val);}
      inline void pin15_pull_no()   { pull.rmw(pull_t::pin15_t::no); }
      inline void pin15_pull_up()   { pull.rmw(pull_t::pin15_t::up); }
      inline void pin15_pull_down() { pull.rmw(pull_t::pin15_t::down); }
      inline auto pin15_pull() const {  return (pull_t::enum_t)pull.rd<pull_t::pin15_t> ();}

      struct input_t : public read_write_32_t
         {
           enum enum_t { mask=1, reset=0, set=1,  } ;
         };

      inline auto pin( const pin_index_t index ) const { return (((read_write_32_t*)&input))->rd<input_t>(index);  }
      inline auto pin( const bit_t bit ) const { return (((read_write_32_t*)&input))->rd<input_t>(__builtin_ctz(bit));  }

      inline auto pin0() const {  return (((read_write_32_t*)&input))->rd<input_t>(i0);  }
      inline auto pin1() const {  return (((read_write_32_t*)&input))->rd<input_t>(i1);  }
      inline auto pin2() const {  return (((read_write_32_t*)&input))->rd<input_t>(i2);  }
      inline auto pin3() const {  return (((read_write_32_t*)&input))->rd<input_t>(i3);  }
      inline auto pin4() const {  return (((read_write_32_t*)&input))->rd<input_t>(i4);  }
      inline auto pin5() const {  return (((read_write_32_t*)&input))->rd<input_t>(i5);  }
      inline auto pin6() const {  return (((read_write_32_t*)&input))->rd<input_t>(i6);  }
      inline auto pin7() const {  return (((read_write_32_t*)&input))->rd<input_t>(i7);  }
      inline auto pin8() const {  return (((read_write_32_t*)&input))->rd<input_t>(i8);  }
      inline auto pin9() const {  return (((read_write_32_t*)&input))->rd<input_t>(i9);  }
      inline auto pin10()const {  return (((read_write_32_t*)&input))->rd<input_t>(i10); }
      inline auto pin11()const {  return (((read_write_32_t*)&input))->rd<input_t>(i11); }
      inline auto pin12()const {  return (((read_write_32_t*)&input))->rd<input_t>(i12); }
      inline auto pin13()const {  return (((read_write_32_t*)&input))->rd<input_t>(i13); }
      inline auto pin14()const {  return (((read_write_32_t*)&input))->rd<input_t>(i14); }
      inline auto pin15()const {  return (((read_write_32_t*)&input))->rd<input_t>(i15); }

      struct output_t : public read_write_32_t
         {
           enum enum_t { mask=1, reset=0, set=1  } ;
           struct pin0_t { enum enum_t { offset=0,  mask=0b11, reset=0, set=1} ; } ;
           struct pin1_t { enum enum_t { offset=2,  mask=0b11, reset=0, set=1} ; } ;
           struct pin2_t { enum enum_t { offset=4,  mask=0b11, reset=0, set=1} ; } ;
           struct pin3_t { enum enum_t { offset=6,  mask=0b11, reset=0, set=1} ; } ;
           struct pin4_t { enum enum_t { offset=8,  mask=0b11, reset=0, set=1} ; } ;
           struct pin5_t { enum enum_t { offset=10, mask=0b11, reset=0, set=1} ; } ;
           struct pin6_t { enum enum_t { offset=12, mask=0b11, reset=0, set=1} ; } ;
           struct pin7_t { enum enum_t { offset=14, mask=0b11, reset=0, set=1} ; } ;
           struct pin8_t { enum enum_t { offset=16, mask=0b11, reset=0, set=1} ; } ;
           struct pin9_t { enum enum_t { offset=18, mask=0b11, reset=0, set=1} ; } ;
           struct pin10_t{ enum enum_t { offset=20, mask=0b11, reset=0, set=1} ; } ;
           struct pin11_t{ enum enum_t { offset=22, mask=0b11, reset=0, set=1} ; } ;
           struct pin12_t{ enum enum_t { offset=24, mask=0b11, reset=0, set=1} ; } ;
           struct pin13_t{ enum enum_t { offset=26, mask=0b11, reset=0, set=1} ; } ;
           struct pin14_t{ enum enum_t { offset=28, mask=0b11, reset=0, set=1} ; } ;
           struct pin15_t{ enum enum_t { offset=30, mask=0b11, reset=0, set=1} ; } ;
         };

      inline void pin( const pin_index_t index, const output_t::enum_t val ) { (((read_write_32_t&)output)).rmw( val, index );  }
      inline void pin_output_reset( const pin_index_t index )  { pin( index, output_t::reset ); }
      inline void pin_output_set( const pin_index_t index )    { pin( index, output_t::set); }
      inline void pin_output_toggle(const pin_index_t index )  { (((read_write_32_t&)output)).write(output^(1<<index));  }
      inline auto pin_output( const pin_index_t index) const  { return (((read_write_32_t&)output)).rd<output_t>( index); }

      inline void pin(const output_t::pin0_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin0_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin0_t::reset);}
      inline void pin0_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin0_t::set); }
      inline void pin0_output_toggle() { (((read_write_32_t&)output)).write(output^b0); }
      inline auto pin0_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin0_t> ();}

      inline void pin(const output_t::pin1_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin1_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin1_t::reset);}
      inline void pin1_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin1_t::set); }
      inline void pin1_output_toggle() { (((read_write_32_t&)output)).write(output^b1); }
      inline auto pin1_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin1_t> ();}

      inline void pin(const output_t::pin2_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin2_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin2_t::reset);}
      inline void pin2_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin2_t::set); }
      inline void pin2_output_toggle() { (((read_write_32_t&)output)).write(output^b2); }
      inline auto pin2_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin2_t> ();}

      inline void pin(const output_t::pin3_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin3_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin3_t::reset);}
      inline void pin3_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin3_t::set); }
      inline void pin3_output_toggle() { (((read_write_32_t&)output)).write(output^b3); }
      inline auto pin3_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin3_t> ();}

      inline void pin(const output_t::pin4_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin4_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin4_t::reset);}
      inline void pin4_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin4_t::set); }
      inline void pin4_output_toggle() { (((read_write_32_t&)output)).write(output^b4); }
      inline auto pin4_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin4_t> ();}

      inline void pin(const output_t::pin5_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin5_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin5_t::reset);}
      inline void pin5_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin5_t::set); }
      inline void pin5_output_toggle() { (((read_write_32_t&)output)).write(output^b5); }
      inline auto pin5_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin5_t> ();}

      inline void pin(const output_t::pin6_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin6_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin6_t::reset);}
      inline void pin6_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin6_t::set); }
      inline void pin6_output_toggle() { (((read_write_32_t&)output)).write(output^b6); }
      inline auto pin6_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin6_t> ();}

      inline void pin(const output_t::pin7_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin7_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin7_t::reset);}
      inline void pin7_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin7_t::set); }
      inline void pin7_output_toggle() { (((read_write_32_t&)output)).write(output^b7); }
      inline auto pin7_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin7_t> ();}

      inline void pin(const output_t::pin8_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin8_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin8_t::reset);}
      inline void pin8_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin8_t::set); }
      inline void pin8_output_toggle() { (((read_write_32_t&)output)).write(output^b8); }
      inline auto pin8_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin8_t> ();}

      inline void pin(const output_t::pin9_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin9_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin9_t::reset);}
      inline void pin9_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin9_t::set); }
      inline void pin9_output_toggle() { (((read_write_32_t&)output)).write(output^b9); }
      inline auto pin9_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin9_t> ();}

      inline void pin(const output_t::pin10_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin10_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin10_t::reset);}
      inline void pin10_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin10_t::set); }
      inline void pin10_output_toggle() { (((read_write_32_t&)output)).write(output^b10); }
      inline auto pin10_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin10_t> ();}

      inline void pin(const output_t::pin11_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin11_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin11_t::reset);}
      inline void pin11_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin11_t::set); }
      inline void pin11_output_toggle() { (((read_write_32_t&)output)).write(output^b11); }
      inline auto pin11_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin11_t> ();}

      inline void pin(const output_t::pin12_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin12_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin12_t::reset);}
      inline void pin12_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin12_t::set); }
      inline void pin12_output_toggle() { (((read_write_32_t&)output)).write(output^b12); }
      inline auto pin12_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin12_t> ();}

      inline void pin(const output_t::pin13_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin13_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin13_t::reset);}
      inline void pin13_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin13_t::set); }
      inline void pin13_output_toggle() { (((read_write_32_t&)output)).write(output^b13); }
      inline auto pin13_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin13_t> ();}

      inline void pin(const output_t::pin14_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin14_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin14_t::reset);}
      inline void pin14_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin14_t::set); }
      inline void pin14_output_toggle() { (((read_write_32_t&)output)).write(output^b14); }
      inline auto pin14_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin14_t> ();}

      inline void pin(const output_t::pin15_t::enum_t val) { (((read_write_32_t&)output)).rmw(val);}
      inline void pin15_output_reset() { (((read_write_32_t&)output)).rmw(output_t::pin15_t::reset);}
      inline void pin15_output_set()   { (((read_write_32_t&)output)).rmw(output_t::pin15_t::set); }
      inline void pin15_output_toggle() { (((read_write_32_t&)output)).write(output^b15); }
      inline auto pin15_output() const {  return (output_t::enum_t)(((read_write_32_t&)output)).rd<output_t::pin15_t> ();}

      struct set_reset_t : public read_write_32_t
         {
           enum enum_t { reset=0, set=1} ;
           struct pin0_set_t { enum enum_t { offset=0,  mask=1, no_action=0, set=1} ; } ;
           struct pin1_set_t { enum enum_t { offset=1,  mask=1, no_action=0, set=1} ; } ;
           struct pin2_set_t { enum enum_t { offset=2,  mask=1, no_action=0, set=1} ; } ;
           struct pin3_set_t { enum enum_t { offset=3,  mask=1, no_action=0, set=1} ; } ;
           struct pin4_set_t { enum enum_t { offset=4,  mask=1, no_action=0, set=1} ; } ;
           struct pin5_set_t { enum enum_t { offset=5,  mask=1, no_action=0, set=1} ; } ;
           struct pin6_set_t { enum enum_t { offset=6,  mask=1, no_action=0, set=1} ; } ;
           struct pin7_set_t { enum enum_t { offset=7,  mask=1, no_action=0, set=1} ; } ;
           struct pin8_set_t { enum enum_t { offset=8,  mask=1, no_action=0, set=1} ; } ;
           struct pin9_set_t { enum enum_t { offset=9,  mask=1, no_action=0, set=1} ; } ;
           struct pin10_set_t{ enum enum_t { offset=10, mask=1, no_action=0, set=1} ; } ;
           struct pin11_set_t{ enum enum_t { offset=11, mask=1, no_action=0, set=1} ; } ;
           struct pin12_set_t{ enum enum_t { offset=12, mask=1, no_action=0, set=1} ; } ;
           struct pin13_set_t{ enum enum_t { offset=13, mask=1, no_action=0, set=1} ; } ;
           struct pin14_set_t{ enum enum_t { offset=14, mask=1, no_action=0, set=1} ; } ;
           struct pin15_set_t{ enum enum_t { offset=15, mask=1, no_action=0, set=1} ; } ;
           struct pin0_reset_t { enum enum_t { offset=0,mask=1, no_action=0, reset=1} ; } ;
           struct pin1_reset_t { enum enum_t { offset=1,mask=1, no_action=0, reset=1} ; } ;
           struct pin2_reset_t { enum enum_t { offset=2,mask=1, no_action=0, reset=1} ; } ;
           struct pin3_reset_t { enum enum_t { offset=3,mask=1, no_action=0, reset=1} ; } ;
           struct pin4_reset_t { enum enum_t { offset=4,mask=1, no_action=0, reset=1} ; } ;
           struct pin5_reset_t { enum enum_t { offset=5,mask=1, no_action=0, reset=1} ; } ;
           struct pin6_reset_t { enum enum_t { offset=6,mask=1, no_action=0, reset=1} ; } ;
           struct pin7_reset_t { enum enum_t { offset=7,mask=1, no_action=0, reset=1} ; } ;
           struct pin8_reset_t { enum enum_t { offset=8,mask=1, no_action=0, reset=1} ; } ;
           struct pin9_reset_t { enum enum_t { offset=9,mask=1, no_action=0, reset=1} ; } ;
           struct pin10_reset_t{ enum enum_t { offset=10,mask=1, no_action=0, reset=1} ; } ;
           struct pin11_reset_t{ enum enum_t { offset=11,mask=1, no_action=0, reset=1} ; } ;
           struct pin12_reset_t{ enum enum_t { offset=12,mask=1, no_action=0, reset=1} ; } ;
           struct pin13_reset_t{ enum enum_t { offset=13,mask=1, no_action=0, reset=1} ; } ;
           struct pin14_reset_t{ enum enum_t { offset=14,mask=1, no_action=0, reset=1} ; } ;
           struct pin15_reset_t{ enum enum_t { offset=15,mask=1, no_action=0, reset=1} ; } ;
         };

      inline void pin( const pin_index_t index, const set_reset_t::enum_t val )   { val ? set_reset.reg_low_value.write( 1 << index) : set_reset.reg_high_value.write( 1 << index) ; }
      inline void pin_set  ( const pin_index_t index ) { set_reset.reg_low_value.write( 1 << index); }
      inline void pin_reset( const pin_index_t index ) { set_reset.reg_high_value.write( 1 << index); }
      inline auto pin_get  ( const pin_index_t index ) { return (set_reset_t::enum_t) input & (1 << index); }

      inline void pin( const bit_t bit, const set_reset_t::enum_t val ) { val ? set_reset.reg_low_value.write(bit) : set_reset.reg_high_value.write(bit) ; }
      inline void pin_set  ( const bit_t bit ) { set_reset.reg_low_value.write( bit ); }
      inline void pin_reset( const bit_t bit ) { set_reset.reg_high_value.write( bit ); }
      inline auto pin_get  ( const bit_t bit ) { return (set_reset_t::enum_t) input & bit; }

      inline void pin0_set()   { set_reset.reg_low_value.write( 1 << 0 ); }
      inline void pin0_reset() { set_reset.reg_high_value.write( 1 << 0  );}

      inline void pin1_set()   { set_reset.reg_low_value.write( 1 << 1 ); }
      inline void pin1_reset() { set_reset.reg_high_value.write( 1 << 1  );}

      inline void pin2_set()   { set_reset.reg_low_value.write( 1 << 2 ); }
      inline void pin2_reset() { set_reset.reg_high_value.write( 1 << 2  );}

      inline void pin3_set()   { set_reset.reg_low_value.write( 1 << 3 ); }
      inline void pin3_reset() { set_reset.reg_high_value.write( 1 << 3  );}

      inline void pin4_set()   { set_reset.reg_low_value.write( 1 << 4 ); }
      inline void pin4_reset() { set_reset.reg_high_value.write( 1 << 4  );}

      inline void pin5_set()   { set_reset.reg_low_value.write( 1 << 5 ); }
      inline void pin5_reset() { set_reset.reg_high_value.write( 1 << 5  );}

      inline void pin6_set()   { set_reset.reg_low_value.write( 1 << 6 ); }
      inline void pin6_reset() { set_reset.reg_high_value.write( 1 << 6  );}

      inline void pin7_set()   { set_reset.reg_low_value.write( 1 << 7 ); }
      inline void pin7_reset() { set_reset.reg_high_value.write( 1 << 7  );}

      inline void pin8_set()   { set_reset.reg_low_value.write( 1 << 8 ); }
      inline void pin8_reset() { set_reset.reg_high_value.write( 1 << 8  );}

      inline void pin9_set()   { set_reset.reg_low_value.write( 1 << 9 ); }
      inline void pin9_reset() { set_reset.reg_high_value.write( 1 << 9  );}

      inline void pin10_set()   { set_reset.reg_low_value.write( 1 << 10 ); }
      inline void pin10_reset() { set_reset.reg_high_value.write( 1 << 10  );}

      inline void pin11_set()   { set_reset.reg_low_value.write( 1 << 11 ); }
      inline void pin11_reset() { set_reset.reg_high_value.write( 1 << 11  );}

      inline void pin12_set()   { set_reset.reg_low_value.write( 1 << 12 ); }
      inline void pin12_reset() { set_reset.reg_high_value.write( 1 << 12  );}

      inline void pin13_set()   { set_reset.reg_low_value.write( 1 << 13 ); }
      inline void pin13_reset() { set_reset.reg_high_value.write( 1 << 13  );}

      inline void pin14_set()   { set_reset.reg_low_value.write( 1 << 14 ); }
      inline void pin14_reset() { set_reset.reg_high_value.write( 1 << 14  );}

      inline void pin15_set()   { set_reset.reg_low_value.write( 1 << 15 ); }
      inline void pin15_reset() { set_reset.reg_high_value.write( 1 << 15  );}

      struct lock_t : public read_write_32_t
               {
                 struct key_t  { enum enum_t { off=0 , on, offset=16, mask=1,  } ; } ;
               };

      template<typename... Args> inline auto pins_lock(const Args... args)
          { NRO uint16_t tmp = 0 ;
            pins_lock( tmp , args...);
            lock.write( (tmp) | (lock_t::key_t::mask << lock_t::key_t::offset));
            lock.write(  tmp );
            lock.write( (tmp) | (lock_t::key_t::mask << lock_t::key_t::offset));
            lock.read();
 	   return lock.rd<lock_t::key_t>();
          }

      template<typename... Args> inline uint16_t pins_lock(uint16_t& tmp , const pin_index_t arg, const Args... args) { pins_lock( tmp, arg); pins_lock( tmp, args...); return tmp ; }
      inline uint16_t pins_lock(uint16_t& tmp, const pin_index_t arg) { tmp |= 1 << arg ; return tmp ; }
      inline uint16_t pins_lock(uint16_t& tmp) const { return tmp ; } // завершающая версия
      inline auto pins_lock() { return lock.rd<lock_t::key_t>(); }

      struct af_t : public read_write_64_t
      {
	enum enum_t : uint64_t { mask=0b1111, af0=0, af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12, af13, af14, af15 };
      };

      inline void pin(const pin_index_t index, const af_t::enum_t val) { af.rmw( val, index*4 ); }
      inline void pin_af0(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af1(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af2(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af3(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af4(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af5(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af6(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af7(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af8(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af9(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af10(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af11(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af12(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af13(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af14(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline void pin_af15(const pin_index_t index) { af.rmw( af_t::af0 , index*4 ); }
      inline auto pin_af(const pin_index_t index) const { return af.rd<af_t>( index*4 ); }


      mode_t          mode;    /*!< GPIO port mode register,               Address offset: 0x00      */
      output_type_t   output_type;   /*!< GPIO port output type register,        Address offset: 0x04      */
      output_speed_t  output_speed;  /*!< GPIO port output speed register,       Address offset: 0x08      */
      pull_t          pull;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
      const uint32_t  input;      /*!< GPIO port input data register,         Address offset: 0x10      */
      uint32_t        output;      /*!< GPIO port output data register,        Address offset: 0x14      */
      set_reset_t     set_reset;   /*!< GPIO port pin set/reset register,      Address offset: 0x18      */
      lock_t          lock;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
      af_t            af  ;     /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */

      // терминальный вызов шаблона с вариативным аргументом  void pin(const U arg, const Args... args)
      // размещаемым в gpioX_t
      inline void pin(){}

}  ;


}

using namespace stm32 ;

#endif /* __GPIO_V2++_H__ */
