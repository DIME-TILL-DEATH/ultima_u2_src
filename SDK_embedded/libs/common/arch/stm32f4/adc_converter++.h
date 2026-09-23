/*
 * adc_converter++.h
 *
 *  Created on: 12 января 2019 г.
 *      Author: klen
 */

#ifndef __ADC_CONVERTER++_H__
#define __ADC_CONVERTER++_H__

namespace stm32f4
{

struct adc_converter_t : public stm32::adc_converter_v1_t
{

  struct control_2_t : public read_write_32_t
  {
    struct external_event_select_for_injected_group_t
                                     { enum enum_t { offset=16, mask=0b1111,
                                                     tim1_cc4=0,
						     tim1_trgo,
						     tim2_cc1,
						     tim2_trgo,
						     tim3_cc2,
						     tim3_cc4,
						     tim4_cc1,
						     tim4_cc2,
                                                     tim4_cc3,
						     tim4_trgo,
						     tim5_cc4,
						     tim5_trgo,
						     tim8_cc2,
						     tim8_cc3,
						     tim8_cc4,
						     exti_line15 }; } ;

    struct external_event_select_for_regular_group_t
                                     { enum enum_t { offset=24, mask=0b1111,
                                                     tim1_cc1=0,
						     tim1_cc2,
						     tim1_cc3,
						     tim2_cc2,
						     tim2_cc3,
						     tim2_cc4,
						     tim2_rtgo,
						     tim3_cc1,
                                                     tim3_trgo,
						     tim4_cc4,
						     tim5_cc1,
						     tim5_cc2,
						     tim5_cc3,
						     tim8_cc1,
						     tim8_trgo,
						     exti_line11 }; } ;
  } ;

  inline  void external_event_select_for_injected_group( const control_2_t::external_event_select_for_injected_group_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_event_select_for_injected_group_tim1_cc4()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim1_cc4) ;}
  inline  void external_event_select_for_injected_group_tim1_trgo() {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim1_trgo) ;}
  inline  void external_event_select_for_injected_group_tim2_cc1()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim2_cc1) ;}
  inline  void external_event_select_for_injected_group_tim2_trgo() {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim2_trgo) ;}
  inline  void external_event_select_for_injected_group_tim3_cc2()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim3_cc2) ;}
  inline  void external_event_select_for_injected_group_tim3_cc4()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim3_cc4) ;}
  inline  void external_event_select_for_injected_group_tim4_cc1()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim4_cc1) ;}
  inline  void external_event_select_for_injected_group_tim4_cc2()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim4_cc2) ;}
  inline  void external_event_select_for_injected_group_tim4_cc3()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim4_cc3) ;}
  inline  void external_event_select_for_injected_group_tim4_trgo() {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim4_trgo) ;}
  inline  void external_event_select_for_injected_group_tim5_cc4()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim5_cc4) ;}
  inline  void external_event_select_for_injected_group_tim5_trgo() {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim5_trgo) ;}
  inline  void external_event_select_for_injected_group_tim8_cc2()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_cc2) ;}
  inline  void external_event_select_for_injected_group_tim8_cc3()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_cc3) ;}
  inline  void external_event_select_for_injected_group_tim8_cc4()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_cc4) ;}
  inline  void external_event_select_for_injected_group_exti_line15()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::exti_line15) ;}
  inline  auto external_event_select_for_injected_group() const {  return control_2.rd<control_2_t::external_event_select_for_injected_group_t> ();}

  inline  void external_event_select_for_regular_group( const control_2_t::external_event_select_for_regular_group_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_event_select_for_regular_group_tim1_cc1() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_cc1) ;}
  inline  void external_event_select_for_regular_group_tim1_cc2() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_cc2) ;}
  inline  void external_event_select_for_regular_group_tim1_cc3() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_cc3) ;}
  inline  void external_event_select_for_regular_group_tim2_cc2() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_cc2) ;}
  inline  void external_event_select_for_regular_group_tim2_cc3() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_cc3) ;}
  inline  void external_event_select_for_regular_group_tim2_cc4() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_cc4) ;}
  inline  void external_event_select_for_regular_group_tim2_rtgo(){  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_rtgo) ;}
  inline  void external_event_select_for_regular_group_tim3_cc1() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim3_cc1) ;}
  inline  void external_event_select_for_regular_group_tim3_trgo(){  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim3_trgo) ;}
  inline  void external_event_select_for_regular_group_tim4_cc4() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim4_cc4) ;}
  inline  void external_event_select_for_regular_group_tim5_cc1() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim5_cc1) ;}
  inline  void external_event_select_for_regular_group_tim5_cc2() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim5_cc2) ;}
  inline  void external_event_select_for_regular_group_tim5_cc3() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim5_cc3) ;}
  inline  void external_event_select_for_regular_group_tim8_cc1() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim8_cc1) ;}
  inline  void external_event_select_for_regular_group_tim8_trgo() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim8_trgo) ;}
  inline  void external_event_select_for_regular_group_exti_line11() {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::exti_line11) ;}
  inline  auto external_event_select_for_regular_group() const {  return control_2.rd<control_2_t::external_event_select_for_regular_group_t> ();}
} ;

}

using namespace stm32f4 ;

#endif /* ___ADC_CONVERTER++_H__ */
