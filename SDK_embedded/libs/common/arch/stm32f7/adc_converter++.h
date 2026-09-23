/*
 * adc_converter++.h
 *
 *  Created on: 12 января 2019 г.
 *      Author: klen
 */

#ifndef __ADC_CONVERTER++_H__
#define __ADC_CONVERTER++_H__

namespace stm32f7
{

struct adc_converter_t : public stm32::adc_converter_v1_t
{

  struct control_2_t : public read_write_32_t
  {
    struct external_event_select_for_injected_group_t
                                     { enum enum_t { offset=16, mask=0b1111,
                                                     tim1_trgo=0,
						     tim1_ch4,
						     tim2_trgo,
						     tim2_ch1,
						     tim3_ch4,
						     tim4_trgo,
						     tim8_ch4=7,
						     tim1_trgo_2,
						     tim8_trgo,
						     tim8_trgo_2,
				                     tim3_ch3,
						     tim5_trgo,
						     tim3_ch1,
						     tim6_trgo,
						      }; } ;

    struct external_event_select_for_regular_group_t
                                     { enum enum_t { offset=24, mask=0b1111,
                                                     tim1_ch1=0,
						     tim1_ch2,
						     tim1_ch3,
						     tim2_ch2,
						     tim5_trgo,
						     tim4_ch4,
						     tim3_ch4,
						     tim8_trgo,
                                                     tim8_trgo_2,
						     tim1_trgo,
						     tim1_rtgo_2,
						     tim2_trgo,
						     tim4_trgo,
						     tim6_trgo,
						     exti_line11=15 }; } ;
  } ;


  inline  void external_event_select_for_injected_group( const control_2_t::external_event_select_for_injected_group_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_event_select_for_injected_group_tim1_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim1_trgo) ;}
  inline  void external_event_select_for_injected_group_tim1_ch4()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim1_ch4) ;}
  inline  void external_event_select_for_injected_group_tim2_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim2_trgo) ;}
  inline  void external_event_select_for_injected_group_tim2_ch1()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim2_ch1) ;}
  inline  void external_event_select_for_injected_group_tim3_ch4()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim3_ch4) ;}
  inline  void external_event_select_for_injected_group_tim4_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim4_trgo) ;}
  inline  void external_event_select_for_injected_group_tim8_ch4()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_ch4) ;}
  inline  void external_event_select_for_injected_group_tim1_trgo_2(){  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim1_trgo_2) ;}
  inline  void external_event_select_for_injected_group_tim8_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_trgo) ;}
  inline  void external_event_select_for_injected_group_tim8_trgo_2(){  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim8_trgo_2) ;}
  inline  void external_event_select_for_injected_group_tim3_ch3()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim3_ch3) ;}
  inline  void external_event_select_for_injected_group_tim5_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim5_trgo) ;}
  inline  void external_event_select_for_injected_group_tim3_ch1()   {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim3_ch1) ;}
  inline  void external_event_select_for_injected_group_tim6_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_injected_group_t::tim6_trgo) ;}
  inline  auto external_event_select_for_injected_group() const {  return control_2.rd<control_2_t::external_event_select_for_injected_group_t> ();}

  inline  void external_event_select_for_regular_group( const control_2_t::external_event_select_for_regular_group_t::enum_t val){  control_2.rmw(val) ;}
  inline  void external_event_select_for_regular_group_tim1_ch1()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_ch1) ;}
  inline  void external_event_select_for_regular_group_tim1_ch2()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_ch2) ;}
  inline  void external_event_select_for_regular_group_tim1_ch3()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_ch3) ;}
  inline  void external_event_select_for_regular_group_tim2_ch2()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_ch2) ;}
  inline  void external_event_select_for_regular_group_tim5_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim5_trgo) ;}
  inline  void external_event_select_for_regular_group_tim4_ch4()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim4_ch4) ;}
  inline  void external_event_select_for_regular_group_tim3_ch4()   {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim3_ch4) ;}
  inline  void external_event_select_for_regular_group_tim8_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim8_trgo) ;}
  inline  void external_event_select_for_regular_group_tim8_trgo_2(){  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim8_trgo_2) ;}
  inline  void external_event_select_for_regular_group_tim1_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_trgo) ;}
  inline  void external_event_select_for_regular_group_tim1_rtgo_2(){  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim1_rtgo_2) ;}
  inline  void external_event_select_for_regular_group_tim2_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim2_trgo) ;}
  inline  void external_event_select_for_regular_group_tim4_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim4_trgo) ;}
  inline  void external_event_select_for_regular_group_tim6_trgo()  {  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::tim6_trgo) ;}
  inline  void external_event_select_for_regular_group_exti_line11(){  control_2.rmw( control_2_t::external_event_select_for_regular_group_t::exti_line11) ;}
  inline  auto external_event_select_for_regular_group() const {  return control_2.rd<control_2_t::external_event_select_for_regular_group_t> ();}

} ;

}

using namespace stm32f7 ;

#endif /* ___ADC_CONVERTER++_H__ */
