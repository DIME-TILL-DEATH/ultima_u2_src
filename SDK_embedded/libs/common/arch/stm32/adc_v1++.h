/*
 * adc_v1++.h
 *
 *  Created on: 23 матра 2018 г.
 *      Author: klen
 */

#ifndef __ADC_V1++_H__
#define __ADC_V1++_H__


namespace stm32
{

struct adc_t
 {

   adc_converter_t converter_1 ; // 0x000
   const uint32_t reserve0[44] ;
   adc_converter_t converter_2 ; // 0x100
   const uint32_t reserve1[44] ;
   adc_converter_t converter_3 ; // 0x200
   const uint32_t reserve2[44] ;

   struct status_t : public read_32_t
    {
       struct converter_1_analog_watchdog_flag_t               { enum enum_t { offset=0, mask=1, no_occured=0, occured   }; } ;
       struct converter_1_regular_channel_end_of_conversion_t  { enum enum_t { offset=1, mask=1, no_occured=0, occured   }; } ;
       struct converter_1_injected_channel_end_of_conversion_t { enum enum_t { offset=2, mask=1, no_occured=0, occured   }; } ;
       struct converter_1_injected_channel_start_flag_t        { enum enum_t { offset=3, mask=1, no_occured=0, occured   }; } ;
       struct converter_1_regular_channel_start_flag_t         { enum enum_t { offset=4, mask=1, no_occured=0, occured   }; } ;
       struct converter_1_overrun_t                            { enum enum_t { offset=5, mask=1, no_occured=0, occured   }; } ;

       struct converter_2_analog_watchdog_flag_t               { enum enum_t { offset=8, mask=1, no_occured=0, occured   }; } ;
       struct converter_2_regular_channel_end_of_conversion_t  { enum enum_t { offset=9, mask=1, no_occured=0, occured   }; } ;
       struct converter_2_injected_channel_end_of_conversion_t { enum enum_t { offset=10,mask=1, no_occured=0, occured   }; } ;
       struct converter_2_injected_channel_start_flag_t        { enum enum_t { offset=11,mask=1, no_occured=0, occured   }; } ;
       struct converter_2_regular_channel_start_flag_t         { enum enum_t { offset=12,mask=1, no_occured=0, occured   }; } ;
       struct converter_2_overrun_t                            { enum enum_t { offset=13,mask=1, no_occured=0, occured   }; } ;

       struct converter_3_analog_watchdog_flag_t               { enum enum_t { offset=8, mask=1, no_occured=0, occured   }; } ;
       struct converter_3_regular_channel_end_of_conversion_t  { enum enum_t { offset=9, mask=1, no_occured=0, occured   }; } ;
       struct converter_3_injected_channel_end_of_conversion_t { enum enum_t { offset=10,mask=1, no_occured=0, occured   }; } ;
       struct converter_3_injected_channel_start_flag_t        { enum enum_t { offset=11,mask=1, no_occured=0, occured   }; } ;
       struct converter_3_regular_channel_start_flag_t         { enum enum_t { offset=12,mask=1, no_occured=0, occured   }; } ;
       struct converter_3_overrun_t                            { enum enum_t { offset=13,mask=1, no_occured=0, occured   }; } ;
    };

   inline auto converter_1_analog_watchdog_flag() const        { return status.rd<status_t::converter_1_analog_watchdog_flag_t>();}
   inline auto converter_1_regular_channel_eoc() const         { return status.rd<status_t::converter_1_regular_channel_end_of_conversion_t>();}
   inline auto converter_1_injected_channel_eoc() const        { return status.rd<status_t::converter_1_injected_channel_end_of_conversion_t>();}
   inline auto converter_1_injected_channel_start_flag() const { return status.rd<status_t::converter_1_injected_channel_start_flag_t>();}
   inline auto converter_1_regular_channel_start_flag() const  { return status.rd<status_t::converter_1_regular_channel_start_flag_t>();}
   inline auto converter_1_overrun() const                     { return status.rd<status_t::converter_1_overrun_t>();}

   inline auto converter_2_analog_watchdog_flag() const        { return status.rd<status_t::converter_2_analog_watchdog_flag_t>();}
   inline auto converter_2_regular_channel_eoc() const         { return status.rd<status_t::converter_2_regular_channel_end_of_conversion_t>();}
   inline auto converter_2_injected_channel_eoc() const        { return status.rd<status_t::converter_2_injected_channel_end_of_conversion_t>();}
   inline auto converter_2_injected_channel_start_flag() const { return status.rd<status_t::converter_2_injected_channel_start_flag_t>();}
   inline auto converter_2_regular_channel_start_flag() const  { return status.rd<status_t::converter_2_regular_channel_start_flag_t>();}
   inline auto converter_2_overrun() const                     { return status.rd<status_t::converter_2_overrun_t>();}

   inline auto converter_3_analog_watchdog_flag() const        { return status.rd<status_t::converter_3_analog_watchdog_flag_t>();}
   inline auto converter_3_regular_channel_eoc() const         { return status.rd<status_t::converter_3_regular_channel_end_of_conversion_t>();}
   inline auto converter_3_injected_channel_eoc() const        { return status.rd<status_t::converter_3_injected_channel_end_of_conversion_t>();}
   inline auto converter_3_injected_channel_start_flag() const { return status.rd<status_t::converter_3_injected_channel_start_flag_t>();}
   inline auto converter_3_regular_channel_start_flag() const  { return status.rd<status_t::converter_3_regular_channel_start_flag_t>();}
   inline auto converter_3_overrun() const                     { return status.rd<status_t::converter_3_overrun_t>();}

   struct control_t : public read_write_32_t
    {
       struct multi_mode_t       { enum enum_t { offset=0,mask=0b11111,
                                                 /** All ADCs independent */
                                                 independed=0,

						  /** Dual modes (ADC1 + ADC2) */
                                                 /** Dual modes (ADC1 + ADC2) Combined regular simultaneous + injected simultaneous mode. */
                                                 dual_regular_simul_and_injected_simul,
                                                 /** Dual modes (ADC1 + ADC2) Combined regular simultaneous + alternate trigger mode. */
						  dual_regular_simul_and_alt_trig,
                                                 /** Dual modes (ADC1 + ADC2) Injected simultaneous mode only. */
						  dual_injected_simul=5,
                                                 /** Dual modes (ADC1 + ADC2) Regular simultaneous mode only. */
						  dual_regular_simul,
                                                 /** Dual modes (ADC1 + ADC2) Interleaved mode only. */
						  dual_interleaved,
                                                 /** Dual modes (ADC1 + ADC2) Alternate trigger mode only. */
                                                 dual_alt_trig=9,

						  /** Triple modes (ADC1 + ADC2 + ADC3) */
                                                 /** Triple modes (ADC1 + ADC2 + ADC3) Combined regular simultaneous + injected simultaneous mode. */
                                                 triple_regular_simul_and_injected_simul=17,
						  /** Triple modes (ADC1 + ADC2 + ADC3) Combined regular simultaneous + alternate trigger mode. */
						  triple_regular_simul_and_alt_trig=18,
                                                 /** Triple modes (ADC1 + ADC2 + ADC3) Injected simultaneous mode only. */
						  triple_injected_simul=21,
                                                 /** Triple modes (ADC1 + ADC2 + ADC3) Regular simultaneous mode only. */
						  triple_regular_simul,
                                                 /** Triple modes (ADC1 + ADC2 + ADC3) Interleaved mode only. */
						  triple_interleaved,
                                                 /** Triple modes (ADC1 + ADC2 + ADC3) Alternate trigger mode only. */
						  triple_alt_trig=25,
                                 };};
       struct delay_between_2_sampling_phases_t { enum enum_t { offset=8, mask=0b1111, }; } ;
       struct dma_disable_selection_t { enum enum_t { offset=13,mask=1, disable=0, enable  }; } ;
       struct dma_mode_t  { enum enum_t { offset=14,mask=0b11, disable=0, mode_1, mode_2, mode_3  }; } ;
       struct prescaler_t { enum enum_t { offset=16,mask=0b11, div_2=0, div_4, div_6, div_8  }; } ;
       struct vbat_t { enum enum_t { offset=22,mask=1, disable=0, enable }; } ;
       struct temp_and_vref_t { enum enum_t { offset=23,mask=1, disable=0, enable }; } ;
    };


   inline  void multi_mode( const control_t::multi_mode_t::enum_t val){  control.rmw(val) ;}
   inline  void multi_mode_independed() {  control.rmw( control_t::multi_mode_t::independed) ;}
   inline  void multi_mode_dual_regular_simul_and_injected_simul() {  control.rmw( control_t::multi_mode_t::dual_regular_simul_and_injected_simul) ;}
   inline  void multi_mode_dual_regular_simul_and_alt_trig() {  control.rmw( control_t::multi_mode_t::dual_regular_simul_and_alt_trig) ;}
   inline  void multi_mode_dual_injected_simul() {  control.rmw( control_t::multi_mode_t::dual_injected_simul) ;}
   inline  void multi_mode_dual_regular_simul() {  control.rmw( control_t::multi_mode_t::dual_regular_simul) ;}
   inline  void multi_mode_dual_interleaved() {  control.rmw( control_t::multi_mode_t::dual_interleaved) ;}
   inline  void multi_mode_dual_alt_trig() {  control.rmw( control_t::multi_mode_t::dual_alt_trig) ;}
   inline  void multi_mode_triple_regular_simul_and_injected_simul() {  control.rmw( control_t::multi_mode_t::triple_regular_simul_and_injected_simul) ;}
   inline  void multi_mode_triple_regular_simul_and_alt_trig() {  control.rmw( control_t::multi_mode_t::triple_regular_simul_and_alt_trig) ;}
   inline  void multi_mode_triple_injected_simul() {  control.rmw( control_t::multi_mode_t::triple_injected_simul) ;}
   inline  void multi_mode_triple_regular_simul() {  control.rmw( control_t::multi_mode_t::triple_regular_simul) ;}
   inline  void multi_mode_triple_interleaved() {  control.rmw( control_t::multi_mode_t::triple_interleaved) ;}
   inline  void multi_mode_triple_alt_trig() {  control.rmw( control_t::multi_mode_t::triple_alt_trig) ;}
   inline  auto multi_mode_() const {  return control.rd<control_t::multi_mode_t> ();}

   inline  void delay_between_2_sampling_phases( const uint8_t val){  control.rmw( (control_t::delay_between_2_sampling_phases_t::enum_t)(val - 5)) ;}
   inline  auto delay_between_2_sampling_phases() const {  return (uint8_t)control.rd<control_t::delay_between_2_sampling_phases_t> () + 5 ;}

   inline  void dma_disable_selection( const control_t::dma_disable_selection_t::enum_t val){  control.rmw(val) ;}
   inline  void dma_disable_selection_disable() {  control.rmw( control_t::dma_disable_selection_t::disable) ;}
   inline  void dma_disable_selection_enable() {  control.rmw( control_t::dma_disable_selection_t::enable) ;}
   inline  auto dma_disable_selection() const {  return control.rd<control_t::dma_disable_selection_t> ();}

   inline  void dma_mode( const control_t::dma_mode_t::enum_t val){  control.rmw(val) ;}
   inline  void dma_mode_disable() {  control.rmw( control_t::dma_mode_t::disable) ;}
   inline  void dma_mode_mode_1() {  control.rmw( control_t::dma_mode_t::mode_1) ;}
   inline  void dma_mode_mode_2() {  control.rmw( control_t::dma_mode_t::mode_2) ;}
   inline  void dma_mode_mode_3() {  control.rmw( control_t::dma_mode_t::mode_3) ;}
   inline  auto dma_mode() const {  return control.rd<control_t::dma_mode_t> ();}

   inline  void prescaler( const control_t::prescaler_t::enum_t val){  control.rmw(val) ;}
   inline  void prescaler_div_2() {  control.rmw( control_t::prescaler_t::div_2) ;}
   inline  void prescaler_div_4() {  control.rmw( control_t::prescaler_t::div_4) ;}
   inline  void prescaler_div_6() {  control.rmw( control_t::prescaler_t::div_6) ;}
   inline  void prescaler_div_8() {  control.rmw( control_t::prescaler_t::div_8) ;}
   inline  auto prescaler() const {  return control.rd<control_t::prescaler_t> ();}

   inline  void vbat( const control_t::vbat_t::enum_t val){  control.rmw(val) ;}
   inline  void vbat_disable() {  control.rmw( control_t::vbat_t::disable) ;}
   inline  void vbat_enable() {  control.rmw( control_t::vbat_t::enable) ;}
   inline  auto vbat() const {  return control.rd<control_t::vbat_t> ();}

   inline  void temp_and_vref( const control_t::temp_and_vref_t::enum_t val){  control.rmw(val) ;}
   inline  void temp_and_vref_disable() {  control.rmw( control_t::temp_and_vref_t::disable) ;}
   inline  void temp_and_vref_enable() {  control.rmw( control_t::temp_and_vref_t::enable) ;}
   inline  auto temp_and_vref() const {  return control.rd<control_t::temp_and_vref_t> ();}

   const status_t          status;          //CSR;    /*!< ADC Common status register,                  Address offset: ADC1 base address + 0x300 */
   control_t               control;         //CCR;    /*!< ADC common control register,                 Address offset: ADC1 base address + 0x304 */
   const volatile uint16_t regular_data_2 ; //CDR;    /*!< ADC common regular data register for dual
   const volatile uint16_t regular_data_1 ; //             AND triple modes,                            Address offset: ADC1 base address + 0x308 */

   inline void reset() {  rcc.adc_reset() ; }

 };

}

using namespace stm32;

#endif /* __ADC_V1++_H__ */
