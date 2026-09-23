/*
 * dac++.h
 *
 *  Created on: 09.09.2017
 *      Author: klen
 */

#ifndef __DAC++_H__
#define __DAC++_H__

#include "types++.h"

namespace stm32
{

struct dac_t
 {
  struct control_t : public read_write_32_t
  {
    struct channel_1_state_t                     { enum enum_t { offset=0,  mask=1, disable=0 , enable } ; } ;
    struct channel_1_output_buff_t               { enum enum_t { offset=1,  mask=1, enable=0 , disable } ; } ;
    struct channel_1_trigger_t                   { enum enum_t { offset=2,  mask=1, disable=0 , enable } ; } ;
    struct channel_1_trigger_select_t            { enum enum_t { offset=3,  mask=0b111, tim6=0 , tim8, tim7, tim5, tim2, tim4, ext_line_9, software } ; } ;
    struct channel_1_wave_t                      { enum enum_t { offset=6,  mask=0b11, disable=0, noise, triangle } ; } ;
    struct channel_1_mask_amplitude_selector_t   { enum enum_t { offset=8,  mask=0b1111, mamp1=0, mamp3, mamp7, mamp15, mamp31, mamp63, mamp127, mamp255, mamp511, mamp1023, mamp2047, mamp4095 } ; } ;
    struct channel_1_dma_t                       { enum enum_t { offset=12, mask=1, disable=0 , enable } ; } ;
    struct channel_1_dma_underrun_interrupt_t    { enum enum_t { offset=13, mask=1, disable=0 , enable } ; } ;

    struct channel_2_state_t                     { enum enum_t { offset=16,  mask=1, disable=0 , enable } ; } ;
    struct channel_2_output_buff_t               { enum enum_t { offset=17,  mask=1, enable=0 , disable } ; } ;
    struct channel_2_trigger_t                   { enum enum_t { offset=18,  mask=1, disable=0 , enable } ; } ;
    struct channel_2_trigger_select_t            { enum enum_t { offset=19,  mask=0b111, tim6=0 , tim8, tim7, tim5, tim2, tim4, ext_line_9, software } ; } ;
    struct channel_2_wave_t                      { enum enum_t { offset=22,  mask=0b11, disable=0, noise, triangle } ; } ;
    struct channel_2_mask_amplitude_selector_t   { enum enum_t { offset=24,  mask=0b1111, mamp1=0, mamp3, mamp7, mamp15, mamp31, mamp63, mamp127, mamp255, mamp511, mamp1023, mamp2047, mamp4095 } ; } ;
    struct channel_2_dma_t                       { enum enum_t { offset=28, mask=1, disable=0 , enable } ; } ;
    struct channel_2_dma_underrun_interrupt_t    { enum enum_t { offset=29, mask=1, disable=0 , enable } ; } ;
  } ;

    inline  void channel_1_state( const control_t::channel_1_state_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_enable()   {  control.rmw( control_t::channel_1_state_t::enable) ;}
    inline  void channel_1_disable() {  control.rmw( control_t::channel_1_state_t::disable) ;}
    inline  auto channel_1_state() const {  return control.rd<control_t::channel_1_state_t> ();}

    inline  void channel_1_output_buff( const control_t::channel_1_output_buff_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_output_buff_enable()   {  control.rmw( control_t::channel_1_output_buff_t::enable) ;}
    inline  void channel_1_output_buff_disable() {  control.rmw( control_t::channel_1_output_buff_t::disable) ;}
    inline  auto channel_1_output_buff() const {  return control.rd<control_t::channel_1_output_buff_t> ();}

    inline  void channel_1_trigger( const control_t::channel_1_trigger_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_trigger_enable()   {  control.rmw( control_t::channel_1_trigger_t::enable) ;}
    inline  void channel_1_trigger_disable() {  control.rmw( control_t::channel_1_trigger_t::disable) ;}
    inline  auto channel_1_trigger() const {  return control.rd<control_t::channel_1_trigger_t> ();}

    inline  void channel_1_trigger_select( const control_t::channel_1_trigger_select_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_trigger_select_tim6() {  control.rmw( control_t::channel_1_trigger_select_t::tim6) ;}
    inline  void channel_1_trigger_select_tim8() {  control.rmw( control_t::channel_1_trigger_select_t::tim8) ;}
    inline  void channel_1_trigger_select_tim7() {  control.rmw( control_t::channel_1_trigger_select_t::tim7) ;}
    inline  void channel_1_trigger_select_tim5() {  control.rmw( control_t::channel_1_trigger_select_t::tim5) ;}
    inline  void channel_1_trigger_select_tim2() {  control.rmw( control_t::channel_1_trigger_select_t::tim2) ;}
    inline  void channel_1_trigger_select_tim4() {  control.rmw( control_t::channel_1_trigger_select_t::tim4) ;}
    inline  void channel_1_trigger_select_ext_line_9() {  control.rmw( control_t::channel_1_trigger_select_t::ext_line_9) ;}
    inline  void channel_1_trigger_select_software() {  control.rmw( control_t::channel_1_trigger_select_t::software) ;}
    inline  auto channel_1_trigger_select() const {  return control.rd<control_t::channel_1_trigger_select_t> ();}

    inline  void channel_1_wave( const control_t::channel_1_wave_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_wave_disable()   {  control.rmw( control_t::channel_1_wave_t::disable) ;}
    inline  void channel_1_wave_noise()   {  control.rmw( control_t::channel_1_wave_t::noise) ;}
    inline  void channel_1_wave_triangele() {  control.rmw( control_t::channel_1_wave_t::triangle) ;}
    inline  auto channel_1_wave() const {  return control.rd<control_t::channel_1_wave_t> ();}

    inline  void channel_1_mask_amplitude_selector( const control_t::channel_1_mask_amplitude_selector_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_mask_amplitude_selector_mamp1()   {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp1) ;}
    inline  void channel_1_mask_amplitude_selector_mamp3()   {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp3) ;}
    inline  void channel_1_mask_amplitude_selector_mamp7()   {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp7) ;}
    inline  void channel_1_mask_amplitude_selector_mamp15()  {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp15) ;}
    inline  void channel_1_mask_amplitude_selector_mamp31()  {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp31) ;}
    inline  void channel_1_mask_amplitude_selector_mamp63()  {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp63) ;}
    inline  void channel_1_mask_amplitude_selector_mamp127() {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp127) ;}
    inline  void channel_1_mask_amplitude_selector_mamp255() {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp255) ;}
    inline  void channel_1_mask_amplitude_selector_mamp511() {  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp511) ;}
    inline  void channel_1_mask_amplitude_selector_mamp1023(){  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp1023) ;}
    inline  void channel_1_mask_amplitude_selector_mamp2047(){  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp2047) ;}
    inline  void channel_1_mask_amplitude_selector_mamp4095(){  control.rmw( control_t::channel_1_mask_amplitude_selector_t::mamp4095) ;}
    inline  auto channel_1_mask_amplitude_selector() const {  return control.rd<control_t::channel_1_mask_amplitude_selector_t> ();}

    inline  void channel_1_dma( const control_t::channel_1_dma_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_dma_enable()   {  control.rmw( control_t::channel_1_dma_t::enable) ;}
    inline  void channel_1_dma_disable() {  control.rmw( control_t::channel_1_dma_t::disable) ;}
    inline  auto channel_1_dma() const {  return control.rd<control_t::channel_1_dma_t> ();}

    inline  void channel_1_dma_underrun_interrupt( const control_t::channel_1_dma_underrun_interrupt_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_1_dma_underrun_interrupt_enable()   {  control.rmw( control_t::channel_1_dma_underrun_interrupt_t::enable) ;}
    inline  void channel_1_dma_underrun_interrupt_disable() {  control.rmw( control_t::channel_1_dma_underrun_interrupt_t::disable) ;}
    inline  auto channel_1_dma_underrun_interrupt() const {  return control.rd<control_t::channel_1_dma_underrun_interrupt_t> ();}


    inline  void channel_2_state( const control_t::channel_2_state_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_enable()   {  control.rmw( control_t::channel_2_state_t::enable) ;}
    inline  void channel_2_disable() {  control.rmw( control_t::channel_2_state_t::disable) ;}
    inline  auto channel_2_state() const {  return control.rd<control_t::channel_2_state_t> ();}

    inline  void channel_2_output_buff( const control_t::channel_2_output_buff_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_output_buff_enable()   {  control.rmw( control_t::channel_2_output_buff_t::enable) ;}
    inline  void channel_2_output_buff_disable() {  control.rmw( control_t::channel_2_output_buff_t::disable) ;}
    inline  auto channel_2_output_buff() const {  return control.rd<control_t::channel_2_output_buff_t> ();}

    inline  void channel_2_trigger( const control_t::channel_2_trigger_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_trigger_enable()   {  control.rmw( control_t::channel_2_trigger_t::enable) ;}
    inline  void channel_2_trigger_disable() {  control.rmw( control_t::channel_2_trigger_t::disable) ;}
    inline  auto channel_2_trigger() const {  return control.rd<control_t::channel_2_trigger_t> ();}

    inline  void channel_2_trigger_select( const control_t::channel_2_trigger_select_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_trigger_select_tim6() {  control.rmw( control_t::channel_2_trigger_select_t::tim6) ;}
    inline  void channel_2_trigger_select_tim8() {  control.rmw( control_t::channel_2_trigger_select_t::tim8) ;}
    inline  void channel_2_trigger_select_tim7() {  control.rmw( control_t::channel_2_trigger_select_t::tim7) ;}
    inline  void channel_2_trigger_select_tim5() {  control.rmw( control_t::channel_2_trigger_select_t::tim5) ;}
    inline  void channel_2_trigger_select_tim2() {  control.rmw( control_t::channel_2_trigger_select_t::tim2) ;}
    inline  void channel_2_trigger_select_tim4() {  control.rmw( control_t::channel_2_trigger_select_t::tim4) ;}
    inline  void channel_2_trigger_select_ext_line_9() {  control.rmw( control_t::channel_2_trigger_select_t::ext_line_9) ;}
    inline  void channel_2_trigger_select_software() {  control.rmw( control_t::channel_2_trigger_select_t::software) ;}
    inline  auto channel_2_trigger_select() const {  return control.rd<control_t::channel_2_trigger_select_t> ();}

    inline  void channel_2_wave( const control_t::channel_2_wave_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_wave_disable()   {  control.rmw( control_t::channel_2_wave_t::disable) ;}
    inline  void channel_2_wave_noise()   {  control.rmw( control_t::channel_2_wave_t::noise) ;}
    inline  void channel_2_wave_triangele() {  control.rmw( control_t::channel_2_wave_t::triangle) ;}
    inline  auto channel_2_wave() const {  return control.rd<control_t::channel_2_wave_t> ();}

    inline  void channel_2_mask_amplitude_selector( const control_t::channel_2_mask_amplitude_selector_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_mask_amplitude_selector_mamp1()   {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp1) ;}
    inline  void channel_2_mask_amplitude_selector_mamp3()   {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp3) ;}
    inline  void channel_2_mask_amplitude_selector_mamp7()   {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp7) ;}
    inline  void channel_2_mask_amplitude_selector_mamp15()  {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp15) ;}
    inline  void channel_2_mask_amplitude_selector_mamp31()  {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp31) ;}
    inline  void channel_2_mask_amplitude_selector_mamp63()  {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp63) ;}
    inline  void channel_2_mask_amplitude_selector_mamp127() {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp127) ;}
    inline  void channel_2_mask_amplitude_selector_mamp255() {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp255) ;}
    inline  void channel_2_mask_amplitude_selector_mamp511() {  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp511) ;}
    inline  void channel_2_mask_amplitude_selector_mamp1023(){  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp1023) ;}
    inline  void channel_2_mask_amplitude_selector_mamp2047(){  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp2047) ;}
    inline  void channel_2_mask_amplitude_selector_mamp4095(){  control.rmw( control_t::channel_2_mask_amplitude_selector_t::mamp4095) ;}
    inline  auto channel_2_mask_amplitude_selector() const {  return control.rd<control_t::channel_2_mask_amplitude_selector_t> ();}

    inline  void channel_2_dma( const control_t::channel_2_dma_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_dma_enable()   {  control.rmw( control_t::channel_2_dma_t::enable) ;}
    inline  void channel_2_dma_disable() {  control.rmw( control_t::channel_2_dma_t::disable) ;}
    inline  auto channel_2_dma() const {  return control.rd<control_t::channel_2_dma_t> ();}

    inline  void channel_2_dma_underrun_interrupt( const control_t::channel_2_dma_underrun_interrupt_t::enum_t val){  control.rmw(val) ;}
    inline  void channel_2_dma_underrun_interrupt_enable()   {  control.rmw( control_t::channel_2_dma_underrun_interrupt_t::enable) ;}
    inline  void channel_2_dma_underrun_interrupt_disable() {  control.rmw( control_t::channel_2_dma_underrun_interrupt_t::disable) ;}
    inline  auto channel_2_dma_underrun_interrupt() const {  return control.rd<control_t::channel_2_dma_underrun_interrupt_t> ();}

    struct software_trigger_t : public read_write_32_t
    {
      struct channel_1_software_trigger_t { enum enum_t { offset=0, mask=1 } ; } ;
      struct channel_2_software_trigger_t { enum enum_t { offset=1, mask=1 } ; } ;
    } ;

    inline  void  channel_1_software_trigger(){ software_trigger.rmw( software_trigger_t::channel_1_software_trigger_t::mask); }
    inline  void  channel_2_software_trigger(){ software_trigger.rmw( software_trigger_t::channel_2_software_trigger_t::mask); }


    struct status_t : public read_write_32_t
    {
      struct channel_1_dma_underrun_t  { enum enum_t { offset=0,  mask=13, no_occured=0 ,  occured } ; } ;
      struct channel_2_dma_underrun_t  { enum enum_t { offset=0,  mask=29, no_occured=0 ,  occured } ; } ;
    } ;

    inline  auto channel_1_dma_underrun() const {  return status.rd<status_t::channel_1_dma_underrun_t> ();}
    inline  auto channel_2_dma_underrun() const {  return status.rd<status_t::channel_2_dma_underrun_t> ();}


    control_t   control ; // CR;       /*!< DAC control register,                                    Address offset: 0x00 */
    software_trigger_t software_trigger; //_IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
    volatile uint32_t channel_1_12bit_right_aligned;//DHR12R1;  /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
    volatile uint32_t channel_1_12bit_left_aligned;//DHR12L1;  /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
    volatile uint32_t channel_1_8bit_right_aligned;//DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
    volatile uint32_t channel_2_12bit_right_aligned;//DHR12R2;  /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
    volatile uint32_t channel_2_12bit_left_aligned;//DHR12L2;  /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
    volatile uint32_t channel_2_8bit_right_aligned;//DHR8R2;   /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
    volatile uint32_t dual_12bit_right_aligned; //DHR12RD;  /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
    volatile uint32_t dual_12bit_left_aligned; //DHR12LD;  /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
    volatile uint32_t dual_8bit_right_aligned; //DHR8RD;   /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
    volatile const uint32_t channel_1_output; //     /*!< DAC channel1 data output register,                       Address offset: 0x2C */
    volatile const uint32_t channel_2_output; //     /*!< DAC channel2 data output register,                       Address offset: 0x30 */
    status_t status; // SR;       /*!< DAC status register,                                     Address offset: 0x34 */

    inline void clock_enable() {  rcc.dac_enable() ; }
    inline void clock_disable(){  rcc.dac_disable(); }
    inline void reset()  {  rcc.dac_reset() ; }

  } ;

static dac_t& dac   = *((dac_t*) dac_addr);

}  // stm32

using namespace stm32 ;

#endif /* __DAC++_H__ */
