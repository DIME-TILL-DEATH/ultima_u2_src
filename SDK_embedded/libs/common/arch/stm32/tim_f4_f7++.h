/*
 * tim++.h
 *
 *  Created on: 26 сен 2018 г.
 *      Author: klen
 */

#ifndef __TIM_F4_F7++_H__
#define __TIM_F4_F7++_H__

#include "types++.h"

/*
   карта типов таймеров

   basic_tim_t
       |
       |---> tim6_t --> tim6
       |
       |---> tim7_t --> tim7
       |
       |---> gp1_tim_t [ + 1 CC chanal]
       |          |
       |          |---> tim10_t --> tim10
       |          |
       |          |---> tim11_t [ + TIM11_OR  ] ---> { tim11 }
       |          |
       |          |---> tim13_t --> tim13
       |          |
       |           ---> tim14_t --> tim14
       |
       |
       |---> gp2_tim_t [ + 2 CC chanals + master/slave ]
       |         |
       |         |---> [ ITR connection tim9 ] ---> tim9 ---> {tim9}
       |         |
       |          ---> [ ITR connection tim12 ] ---> tim12 ---> {tim12}
       |
       |
       |---> gp3_tim_t [ + 4 CC chanals + master/slave + Center-aligned mode ]
       |         |
       |         |---> tim3_t ---> {tim3}
       |         |
       |         |---> tim4_t ---> {tim4}
       |         |
       |          ---> gp4_tim_t [ + 32bit counters]
       |                   |
       |                   |
       |                   |---> tim2_t [ + TIM2_OR ]---> {tim2}
       |                   |
       |                   |
       |                    ---> tim5_t [ + TIM5_OR ]---> {tim5}
       |
       |
        ---> [ + advanced caps ] ---> adv_tim_t
                                         |
                                         |---> tim1_t ---> {tim8}
                                         |
                                          ---> tim8_t ---> {tim8}
 */

namespace stm32
{
  struct basic_tim_t // базовые таймеры. TIM6, TIM7
  {
    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_update_generation=0, overflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_update_generation );}
    inline void update_request_source_overflow() { control_1.rmw( control_1_t::update_request_source_t::overflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}


    struct control_2_t : public read_write_32_t
    {
      struct master_mode_selection_t { enum enum_t { offset=4, mask=0b111, reset=0, counter_enable, update }; } ;
    } ;

    inline void master_mode_selection(const control_2_t::master_mode_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void master_mode_selection_reset() { control_2.rmw( control_2_t::master_mode_selection_t::reset );}
    inline void master_mode_selection_counter_enable() { control_2.rmw( control_2_t::master_mode_selection_t::counter_enable );}
    inline void master_mode_selection_update() { control_2.rmw( control_2_t::master_mode_selection_t::update );}
    inline auto master_mode_selection() const { return control_2.rd<control_2_t::master_mode_selection_t>();}

    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t   { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct update_dma_request_t { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void update_dma_request(const dma_interrupt_t::update_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::enable );}
    inline void update_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::disable );}
    inline auto update_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::update_dma_request_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t  { enum enum_t { offset=0, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generation() { event_generation.rmw( event_generation_t::update_t::perform );}

    control_1_t     control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    control_2_t     control_2 ;          //CR2;  /*!< TIM control register 2,              Address offset: 0x04 */
    const uint32_t : 32;
    dma_interrupt_t dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t        status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t event_generation; //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    const    uint32_t : 32 ;
    const    uint32_t : 32 ;
    const    uint32_t : 32 ;

    volatile uint16_t counter ;
    const    uint16_t : 16 ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;

    volatile uint16_t auto_reload ;
    const    uint16_t : 16 ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim6_addr : rcc.tim6_enable(); break ;
               case tim7_addr : rcc.tim7_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim6_addr : rcc.tim6_disable(); break ;
               case tim7_addr : rcc.tim7_disable(); break ;
               default: {  std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim6_addr : rcc.tim6_reset(); break ;
               case tim7_addr : rcc.tim7_reset(); break ;
               default: {  std::__throw_invalid_argument("invalid TIM object") ; }
            }
       };
  } ;
  struct gp1_tim_t // таймеры общего применеия, типа 1, TIM10/TIM11  TIM13/TIM14 (один канал СС)
  {
    gp1_tim_t() {}

    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_update_generation=0, overflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct ti_clock_division_t     { enum enum_t { offset=8, mask=0b11, div1=0, div2, div4 }; } ;

    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_update_generation );}
    inline void update_request_source_overflow() { control_1.rmw( control_1_t::update_request_source_t::overflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}

    inline void ti_clock_division(const control_1_t::ti_clock_division_t::enum_t val) {  control_1.rmw( val );}
    inline void ti_clock_division_div1() { control_1.rmw( control_1_t::ti_clock_division_t::div1 );}
    inline void ti_clock_division_div2() { control_1.rmw( control_1_t::ti_clock_division_t::div2 );}
    inline void ti_clock_division_div4() { control_1.rmw( control_1_t::ti_clock_division_t::div4 );}
    inline auto ti_clock_division() const { return control_1.rd<control_1_t::ti_clock_division_t>();}

    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t            { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct cc1_interrupt_t { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void cc1_interrupt(const dma_interrupt_t::cc1_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::enable );}
    inline void cc1_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::disable );}
    inline auto cc1_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc1_interrupt_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
      struct cc1_interrupt_flag_t { enum enum_t { offset=1, mask=1, no_occured=0, occured}; } ;
      struct cc1_ovecapture_flag_t { enum enum_t { offset=9, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    inline void cc1_interrupt_flag_clear() { status.rmw( status_t::cc1_interrupt_flag_t::no_occured );}
    inline auto cc1_interrupt_flag() const { return status.rd<status_t::cc1_interrupt_flag_t>();}

    inline void cc1_ovecapture_flag_clear() { status.rmw( status_t::cc1_ovecapture_flag_t::no_occured );}
    inline auto cc1_ovecapture_flag() const { return status.rd<status_t::cc1_ovecapture_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t  { enum enum_t { offset=0, mask=1, perform=1}; } ;
      struct  cc1_t     { enum enum_t { offset=1, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generate() { event_generation.rmw( event_generation_t::update_t::perform );}
    inline void cc1_generate()          { event_generation.rmw( event_generation_t::cc1_t::perform );}

    struct cc_mode_t : public read_write_32_t
      {
        struct  cc1_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture}; } ;

        struct  oc1_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc1_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc1_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;

        struct  ic1_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic1_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc1_selection(const cc_mode_t::cc1_selection_t::enum_t val) {  cc_mode.rmw( val );}
    inline void cc1_selection_output_compare() { cc_mode.rmw( cc_mode_t::cc1_selection_t::output_compare );}
    inline void cc1_selection_inpit_capture() { cc_mode.rmw( cc_mode_t::cc1_selection_t::inpit_capture );}
    inline auto cc1_selection() const { return cc_mode.rd<cc_mode_t::cc1_selection_t>();}

    inline void oc1_fast(const cc_mode_t::oc1_fast_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_fast_disable() { cc_mode.rmw( cc_mode_t::oc1_fast_t::disable );}
    inline void oc1_fast_enable() { cc_mode.rmw( cc_mode_t::oc1_fast_t::enable );}
    inline auto oc1_fast() const { return cc_mode.rd<cc_mode_t::oc1_fast_t>();}

    inline void oc1_preload(const cc_mode_t::oc1_preload_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_preload_disable() { cc_mode.rmw( cc_mode_t::oc1_preload_t::disable );}
    inline void oc1_preload_enable() { cc_mode.rmw( cc_mode_t::oc1_preload_t::enable );}
    inline auto oc1_preload() const { return cc_mode.rd<cc_mode_t::oc1_preload_t>();}

    inline void oc1_mode(const cc_mode_t::oc1_mode_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_mode_frozen() { cc_mode.rmw( cc_mode_t::oc1_mode_t::frozen );}
    inline void oc1_mode_active() { cc_mode.rmw( cc_mode_t::oc1_mode_t::active );}
    inline void oc1_mode_inactive() { cc_mode.rmw( cc_mode_t::oc1_mode_t::inactive );}
    inline void oc1_mode_toggle() { cc_mode.rmw( cc_mode_t::oc1_mode_t::toggle );}
    inline void oc1_mode_force_inactive() { cc_mode.rmw( cc_mode_t::oc1_mode_t::force_inactive );}
    inline void oc1_mode_force_active() { cc_mode.rmw( cc_mode_t::oc1_mode_t::force_active );}
    inline void oc1_mode_pwm1() { cc_mode.rmw( cc_mode_t::oc1_mode_t::pwm1 );}
    inline void oc1_mode_pwm2() { cc_mode.rmw( cc_mode_t::oc1_mode_t::pwm2 );}
    inline auto oc1_mode() const { return cc_mode.rd<cc_mode_t::oc1_mode_t>();}

    inline void ic1_precscaler(const cc_mode_t::ic1_precscaler_t::enum_t val) {  cc_mode.rmw( val );}
    inline void ic1_precscaler_every_first()  { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_first );}
    inline void ic1_precscaler_every_second() { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_second );}
    inline void ic1_precscaler_every_thirh()  { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_thirh );}
    inline void ic1_precscaler_every_eighth() { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_eighth );}
    inline auto ic1_precscaler() const { return cc_mode.rd<cc_mode_t::ic1_precscaler_t>();}

    inline void ic1_filter(const cc_mode_t::ic1_filter::enum_t val) {  cc_mode.rmw( val );}
    inline void ic1_filter_disable()  { cc_mode.rmw( cc_mode_t::ic1_filter::disable );}
    inline void ic1_filter_fck_n2()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n2 );}
    inline void ic1_filter_fck_n4()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n4 );}
    inline void ic1_filter_fck_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n8 );}
    inline void ic1_filter_fdts2_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts2_n6 );}
    inline void ic1_filter_fdts2_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts2_n8 );}
    inline void ic1_filter_fdts4_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts4_n6 );}
    inline void ic1_filter_fdts4_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts4_n8 );}
    inline void ic1_filter_fdts8_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts8_n6 );}
    inline void ic1_filter_fdts8_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts8_n8 );}
    inline void ic1_filter_fdts16_n5()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n5 );}
    inline void ic1_filter_fdts16_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n6 );}
    inline void ic1_filter_fdts16_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n8 );}
    inline void ic1_filter_fdts32_n5()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n5 );}
    inline void ic1_filter_fdts32_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n6 );}
    inline void ic1_filter_fdts32_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n8 );}
    inline auto ic1_filter() const { return cc_mode.rd<cc_mode_t::ic1_filter>();}

    struct cc_enable_t : public read_write_32_t
      {
        struct  cc1_state_t   { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
        struct  cc1_config_t  { enum enum_t { offset=1, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                             } ;
      } ;

    inline void cc1_state(const cc_enable_t::cc1_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc1_disable() { cc_enable.rmw( cc_enable_t::cc1_state_t::disable );}
    inline void cc1_enable() { cc_enable.rmw( cc_enable_t::cc1_state_t::enable );}
    inline auto cc1_state() const { return cc_enable.rd<cc_enable_t::cc1_state_t>();}

    // как output compare
    inline void oc1_polarity(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1_polarity_high() { cc_enable.rmw( cc_enable_t::cc1_config_t::high );}
    inline void oc1_polarity_low() { cc_enable.rmw( cc_enable_t::cc1_config_t::low );}
    inline auto oc1_polarity_() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    // как input capture
    inline void ic1_config(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic1_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_rise );}
    inline void ic1_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc1_config_t::inverted_fall );}
    inline void ic1_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_both );}
    inline auto ic1_config() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    control_1_t               control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    const uint32_t : 32;
    const uint32_t : 32;
    dma_interrupt_t           dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t                  status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t        event_generation; //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    cc_mode_t    cc_mode ;
    const    uint32_t : 32 ;
    cc_enable_t  cc_enable ;

    volatile uint16_t counter ;
    const    uint16_t : 16 ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;

    volatile uint16_t auto_reload ;
    const    uint16_t : 16 ;

    const uint32_t : 32;

    volatile uint16_t capture_compare ;
    const    uint16_t : 16 ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim10_addr : rcc.tim10_enable(); break ;
               case tim11_addr : rcc.tim11_enable(); break ;
               case tim13_addr : rcc.tim13_enable(); break ;
               case tim14_addr : rcc.tim14_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim10_addr : rcc.tim10_disable(); break ;
               case tim11_addr : rcc.tim11_disable(); break ;
               case tim13_addr : rcc.tim13_disable(); break ;
               case tim14_addr : rcc.tim14_disable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim10_addr : rcc.tim10_reset(); break ;
               case tim11_addr : rcc.tim11_reset(); break ;
               case tim13_addr : rcc.tim13_reset(); break ;
               case tim14_addr : rcc.tim14_reset(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
  } ;
  struct gp2_tim_t // таймеры общего применеия, типа 2, TIM9  TIM12 (два канала СС) + Master/Slave
  {
    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_update_generation=0, overflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct ti_clock_division_t     { enum enum_t { offset=8, mask=0b11, div1=0, div2, div4 }; } ;

    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_update_generation );}
    inline void update_request_source_overflow() { control_1.rmw( control_1_t::update_request_source_t::overflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}

    inline void ti_clock_division(const control_1_t::ti_clock_division_t::enum_t val) {  control_1.rmw( val );}
    inline void ti_clock_division_div1() { control_1.rmw( control_1_t::ti_clock_division_t::div1 );}
    inline void ti_clock_division_div2() { control_1.rmw( control_1_t::ti_clock_division_t::div2 );}
    inline void ti_clock_division_div4() { control_1.rmw( control_1_t::ti_clock_division_t::div4 );}
    inline auto ti_clock_division() const { return control_1.rd<control_1_t::ti_clock_division_t>();}

    struct slave_mode_control_t : public read_write_32_t
    {
      struct slave_mode_t  { enum enum_t { offset=0, mask=0b111, disable=0, reset=0b100, gated, trigger, extrenal_clock }; } ;
      struct trigger_t  { enum enum_t { offset=4, mask=0b111, internal_trigger_0=0, internal_trigger_1, internal_trigger_2, internal_trigger_3, ti1_edge_detector, filtered_timer_input_1, filtered_timer_input_2}; } ;
      struct master_slave_mode_t  { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
    };

    inline void slave_mode(const slave_mode_control_t::slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::disable );}
    inline void slave_mode_reset() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::reset );}
    inline void slave_mode_gated() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::gated );}
    inline void slave_mode_trigger() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::trigger );}
    inline void slave_mode_extrenal_clock() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::extrenal_clock );}
    inline auto slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::slave_mode_t>();}

    inline void master_slave_mode(const slave_mode_control_t::master_slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void master_slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::disable );}
    inline void master_slave_mode_enable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::enable );}
    inline auto master_slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::master_slave_mode_t>();}



    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t  { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct cc1_interrupt_t     { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
      struct cc2_interrupt_t     { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
      struct trigger_interrupt_t { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void cc1_interrupt(const dma_interrupt_t::cc1_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::enable );}
    inline void cc1_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::disable );}
    inline auto cc1_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc1_interrupt_t>();}

    inline void cc2_interrupt(const dma_interrupt_t::cc2_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::enable );}
    inline void cc2_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::disable );}
    inline auto cc2_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc2_interrupt_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
      struct cc1_interrupt_flag_t { enum enum_t { offset=1, mask=1, no_occured=0, occured}; } ;
      struct cc2_interrupt_flag_t { enum enum_t { offset=2, mask=1, no_occured=0, occured}; } ;

      struct cc1_ovecapture_flag_t { enum enum_t { offset=9, mask=1, no_occured=0, occured}; } ;
      struct cc2_ovecapture_flag_t { enum enum_t { offset=10, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    inline void cc1_interrupt_flag_clear() { status.rmw( status_t::cc1_interrupt_flag_t::no_occured );}
    inline auto cc1_interrupt_flag() const { return status.rd<status_t::cc1_interrupt_flag_t>();}

    inline void cc2_interrupt_flag_clear() { status.rmw( status_t::cc2_interrupt_flag_t::no_occured );}
    inline auto cc2_interrupt_flag() const { return status.rd<status_t::cc2_interrupt_flag_t>();}

    inline void cc1_ovecapture_flag_clear() { status.rmw( status_t::cc1_ovecapture_flag_t::no_occured );}
    inline auto cc1_ovecapture_flag() const { return status.rd<status_t::cc1_ovecapture_flag_t>();}

    inline void cc2_ovecapture_flag_clear() { status.rmw( status_t::cc2_ovecapture_flag_t::no_occured );}
    inline auto cc2_ovecapture_flag() const { return status.rd<status_t::cc2_ovecapture_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t   { enum enum_t { offset=0, mask=1, perform=1}; } ;
      struct  cc1_t      { enum enum_t { offset=1, mask=1, perform=1}; } ;
      struct  cc2_t      { enum enum_t { offset=2, mask=1, perform=1}; } ;
      struct  trigger_t  { enum enum_t { offset=6, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generate() { event_generation.rmw( event_generation_t::update_t::perform );}
    inline void cc1_generate()          { event_generation.rmw( event_generation_t::cc1_t::perform );}
    inline void cc2_generate()          { event_generation.rmw( event_generation_t::cc2_t::perform );}
    inline void trigger_generate()          { event_generation.rmw( event_generation_t::trigger_t::perform );}

    struct cc_mode_t : public read_write_32_t
      {
        struct  cc1_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_1, inpit_capture_internal_trigger_2, inpit_capture_trc}; } ;

        struct  oc1_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc1_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc1_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;

        struct  ic1_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic1_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc2_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_2, inpit_capture_internal_trigger_1, inpit_capture_trc}; } ;

        struct  oc2_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc2_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc2_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;

        struct  ic2_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic2_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;


      } ;

    inline void cc1_selection(const cc_mode_t::cc1_selection_t::enum_t val) {  cc_mode.rmw( val );}
    inline void cc1_selection_output_compare() { cc_mode.rmw( cc_mode_t::cc1_selection_t::output_compare );}
    inline void cc1_selection_inpit_capture_internal_trigger_1() { cc_mode.rmw( cc_mode_t::cc1_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc1_selection_inpit_capture_internal_trigger_2() { cc_mode.rmw( cc_mode_t::cc1_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc1_selection_inpit_capture_trc() { cc_mode.rmw( cc_mode_t::cc1_selection_t::inpit_capture_trc );}
    inline auto cc1_selection() const { return cc_mode.rd<cc_mode_t::cc1_selection_t>();}

    inline void oc1_fast(const cc_mode_t::oc1_fast_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_fast_disable() { cc_mode.rmw( cc_mode_t::oc1_fast_t::disable );}
    inline void oc1_fast_enable() { cc_mode.rmw( cc_mode_t::oc1_fast_t::enable );}
    inline auto oc1_fast() const { return cc_mode.rd<cc_mode_t::oc1_fast_t>();}

    inline void oc1_preload(const cc_mode_t::oc1_preload_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_preload_disable() { cc_mode.rmw( cc_mode_t::oc1_preload_t::disable );}
    inline void oc1_preload_enable() { cc_mode.rmw( cc_mode_t::oc1_preload_t::enable );}
    inline auto oc1_preload() const { return cc_mode.rd<cc_mode_t::oc1_preload_t>();}

    inline void oc1_mode(const cc_mode_t::oc1_mode_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc1_mode_frozen() { cc_mode.rmw( cc_mode_t::oc1_mode_t::frozen );}
    inline void oc1_mode_active() { cc_mode.rmw( cc_mode_t::oc1_mode_t::active );}
    inline void oc1_mode_inactive() { cc_mode.rmw( cc_mode_t::oc1_mode_t::inactive );}
    inline void oc1_mode_toggle() { cc_mode.rmw( cc_mode_t::oc1_mode_t::toggle );}
    inline void oc1_mode_force_inactive() { cc_mode.rmw( cc_mode_t::oc1_mode_t::force_inactive );}
    inline void oc1_mode_force_active() { cc_mode.rmw( cc_mode_t::oc1_mode_t::force_active );}
    inline void oc1_mode_pwm1() { cc_mode.rmw( cc_mode_t::oc1_mode_t::pwm1 );}
    inline void oc1_mode_pwm2() { cc_mode.rmw( cc_mode_t::oc1_mode_t::pwm2 );}
    inline auto oc1_mode() const { return cc_mode.rd<cc_mode_t::oc1_mode_t>();}

    inline void ic1_precscaler(const cc_mode_t::ic1_precscaler_t::enum_t val) {  cc_mode.rmw( val );}
    inline void ic1_precscaler_every_first()  { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_first );}
    inline void ic1_precscaler_every_second() { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_second );}
    inline void ic1_precscaler_every_thirh()  { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_thirh );}
    inline void ic1_precscaler_every_eighth() { cc_mode.rmw( cc_mode_t::ic1_precscaler_t::every_eighth );}
    inline auto ic1_precscaler() const { return cc_mode.rd<cc_mode_t::ic1_precscaler_t>();}

    inline void ic1_filter(const cc_mode_t::ic1_filter::enum_t val) {  cc_mode.rmw( val );}
    inline void ic1_filter_disable()  { cc_mode.rmw( cc_mode_t::ic1_filter::disable );}
    inline void ic1_filter_fck_n2()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n2 );}
    inline void ic1_filter_fck_n4()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n4 );}
    inline void ic1_filter_fck_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fck_n8 );}
    inline void ic1_filter_fdts2_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts2_n6 );}
    inline void ic1_filter_fdts2_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts2_n8 );}
    inline void ic1_filter_fdts4_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts4_n6 );}
    inline void ic1_filter_fdts4_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts4_n8 );}
    inline void ic1_filter_fdts8_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts8_n6 );}
    inline void ic1_filter_fdts8_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts8_n8 );}
    inline void ic1_filter_fdts16_n5()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n5 );}
    inline void ic1_filter_fdts16_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n6 );}
    inline void ic1_filter_fdts16_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts16_n8 );}
    inline void ic1_filter_fdts32_n5()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n5 );}
    inline void ic1_filter_fdts32_n6()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n6 );}
    inline void ic1_filter_fdts32_n8()  { cc_mode.rmw( cc_mode_t::ic1_filter::fdts32_n8 );}
    inline auto ic1_filter() const { return cc_mode.rd<cc_mode_t::ic1_filter>();}


    inline void cc2_selection(const cc_mode_t::cc2_selection_t::enum_t val) {  cc_mode.rmw( val );}
    inline void cc2_selection_output_compare() { cc_mode.rmw( cc_mode_t::cc2_selection_t::output_compare );}
    inline void cc2_selection_inpit_capture_internal_trigger_1() { cc_mode.rmw( cc_mode_t::cc2_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc2_selection_inpit_capture_internal_trigger_2() { cc_mode.rmw( cc_mode_t::cc2_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc2_selection_inpit_capture_trc() { cc_mode.rmw( cc_mode_t::cc2_selection_t::inpit_capture_trc );}
    inline auto cc2_selection() const { return cc_mode.rd<cc_mode_t::cc2_selection_t>();}

    inline void oc2_fast(const cc_mode_t::oc2_fast_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc2_fast_disable() { cc_mode.rmw( cc_mode_t::oc2_fast_t::disable );}
    inline void oc2_fast_enable() { cc_mode.rmw( cc_mode_t::oc2_fast_t::enable );}
    inline auto oc2_fast() const { return cc_mode.rd<cc_mode_t::oc2_fast_t>();}

    inline void oc2_preload(const cc_mode_t::oc2_preload_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc2_preload_disable() { cc_mode.rmw( cc_mode_t::oc2_preload_t::disable );}
    inline void oc2_preload_enable() { cc_mode.rmw( cc_mode_t::oc2_preload_t::enable );}
    inline auto oc2_preload() const { return cc_mode.rd<cc_mode_t::oc2_preload_t>();}

    inline void oc2_mode(const cc_mode_t::oc2_mode_t::enum_t val) {  cc_mode.rmw( val );}
    inline void oc2_mode_frozen() { cc_mode.rmw( cc_mode_t::oc2_mode_t::frozen );}
    inline void oc2_mode_active() { cc_mode.rmw( cc_mode_t::oc2_mode_t::active );}
    inline void oc2_mode_inactive() { cc_mode.rmw( cc_mode_t::oc2_mode_t::inactive );}
    inline void oc2_mode_toggle() { cc_mode.rmw( cc_mode_t::oc2_mode_t::toggle );}
    inline void oc2_mode_force_inactive() { cc_mode.rmw( cc_mode_t::oc2_mode_t::force_inactive );}
    inline void oc2_mode_force_active() { cc_mode.rmw( cc_mode_t::oc2_mode_t::force_active );}
    inline void oc2_mode_pwm1() { cc_mode.rmw( cc_mode_t::oc2_mode_t::pwm1 );}
    inline void oc2_mode_pwm2() { cc_mode.rmw( cc_mode_t::oc2_mode_t::pwm2 );}
    inline auto oc2_mode() const { return cc_mode.rd<cc_mode_t::oc2_mode_t>();}

    inline void ic2_precscaler(const cc_mode_t::ic2_precscaler_t::enum_t val) {  cc_mode.rmw( val );}
    inline void ic2_precscaler_every_first()  { cc_mode.rmw( cc_mode_t::ic2_precscaler_t::every_first );}
    inline void ic2_precscaler_every_second() { cc_mode.rmw( cc_mode_t::ic2_precscaler_t::every_second );}
    inline void ic2_precscaler_every_thirh()  { cc_mode.rmw( cc_mode_t::ic2_precscaler_t::every_thirh );}
    inline void ic2_precscaler_every_eighth() { cc_mode.rmw( cc_mode_t::ic2_precscaler_t::every_eighth );}
    inline auto ic2_precscaler() const { return cc_mode.rd<cc_mode_t::ic2_precscaler_t>();}

    inline void ic2_filter(const cc_mode_t::ic2_filter::enum_t val) {  cc_mode.rmw( val );}
    inline void ic2_filter_disable()  { cc_mode.rmw( cc_mode_t::ic2_filter::disable );}
    inline void ic2_filter_fck_n2()  { cc_mode.rmw( cc_mode_t::ic2_filter::fck_n2 );}
    inline void ic2_filter_fck_n4()  { cc_mode.rmw( cc_mode_t::ic2_filter::fck_n4 );}
    inline void ic2_filter_fck_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fck_n8 );}
    inline void ic2_filter_fdts2_n6()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts2_n6 );}
    inline void ic2_filter_fdts2_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts2_n8 );}
    inline void ic2_filter_fdts4_n6()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts4_n6 );}
    inline void ic2_filter_fdts4_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts4_n8 );}
    inline void ic2_filter_fdts8_n6()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts8_n6 );}
    inline void ic2_filter_fdts8_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts8_n8 );}
    inline void ic2_filter_fdts16_n5()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts16_n5 );}
    inline void ic2_filter_fdts16_n6()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts16_n6 );}
    inline void ic2_filter_fdts16_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts16_n8 );}
    inline void ic2_filter_fdts32_n5()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts32_n5 );}
    inline void ic2_filter_fdts32_n6()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts32_n6 );}
    inline void ic2_filter_fdts32_n8()  { cc_mode.rmw( cc_mode_t::ic2_filter::fdts32_n8 );}
    inline auto ic2_filter() const { return cc_mode.rd<cc_mode_t::ic2_filter>();}



    struct cc_enable_t : public read_write_32_t
      {
        struct  cc1_state_t   { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
        struct  cc1_config_t  { enum enum_t { offset=1, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc2_state_t   { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
        struct  cc2_config_t  { enum enum_t { offset=5, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;
      } ;

    inline void cc1_state(const cc_enable_t::cc1_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc1_disable() { cc_enable.rmw( cc_enable_t::cc1_state_t::disable );}
    inline void cc1_enable() { cc_enable.rmw( cc_enable_t::cc1_state_t::enable );}
    inline auto cc1_state() const { return cc_enable.rd<cc_enable_t::cc1_state_t>();}

    // как output compare
    inline void oc1_polarity(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1_polarity_high() { cc_enable.rmw( cc_enable_t::cc1_config_t::high );}
    inline void oc1_polarity_low() { cc_enable.rmw( cc_enable_t::cc1_config_t::low );}
    inline auto oc1_polarity() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    // как input capture
    inline void ic1_config(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic1_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_rise );}
    inline void ic1_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc1_config_t::inverted_fall );}
    inline void ic1_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_both );}
    inline auto ic1_config() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    inline void cc2_state(const cc_enable_t::cc2_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc2_disable() { cc_enable.rmw( cc_enable_t::cc2_state_t::disable );}
    inline void cc2_enable() { cc_enable.rmw( cc_enable_t::cc2_state_t::enable );}
    inline auto cc2_state() const { return cc_enable.rd<cc_enable_t::cc2_state_t>();}

    // как output compare
    inline void oc2_polarity(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2_polarity_high() { cc_enable.rmw( cc_enable_t::cc2_config_t::high );}
    inline void oc2_polarity_low() { cc_enable.rmw( cc_enable_t::cc2_config_t::low );}
    inline auto oc2_polarity() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    // как input capture
    inline void ic2_config(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic2_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_rise );}
    inline void ic2_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc2_config_t::inverted_fall );}
    inline void ic2_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_both );}
    inline auto ic2_config() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    control_1_t               control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    const uint32_t : 32;
    slave_mode_control_t      slave_mode_control;  //SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    dma_interrupt_t           dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t                  status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t        event_generation; //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    cc_mode_t    cc_mode ;
    const    uint32_t : 32 ;
    cc_enable_t  cc_enable ;

    volatile uint16_t counter ;
    const    uint16_t : 16 ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;

    volatile uint16_t auto_reload ;
    const    uint16_t : 16 ;

    const uint32_t : 32;

    volatile uint16_t cc1 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc2 ;
    const    uint16_t : 16 ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim9_addr  : rcc.tim9_enable(); break ;
               case tim12_addr : rcc.tim12_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim9_addr  : rcc.tim9_disable(); break ;
               case tim12_addr : rcc.tim12_disable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim9_addr  : rcc.tim9_reset(); break ;
               case tim12_addr : rcc.tim12_reset(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
  } ;
  struct gp3_tim_t // таймеры общего применеия, типа 3, TIM3  TIM4 (четыре канала СС) + Master/Slave
  {
    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_update_generation=0, overflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct direction_t             { enum enum_t { offset=4, mask=1, up=0, down }; } ;
      struct aligned_t               { enum enum_t { offset=5, mask=0b11, edge=0, center_counting_down, center_counting_up, center_counting_up_down }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct ti_clock_division_t     { enum enum_t { offset=8, mask=0b11, div1=0, div2, div4 }; } ;
    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_update_generation );}
    inline void update_request_source_overflow() { control_1.rmw( control_1_t::update_request_source_t::overflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void direction(const control_1_t::direction_t::enum_t val) {  control_1.rmw( val );}
    inline void direction_up() { control_1.rmw( control_1_t::direction_t::up );}
    inline void direction_down() { control_1.rmw( control_1_t::direction_t::down );}
    inline auto direction() const { return control_1.rd<control_1_t::direction_t>();}

    inline void aligned(const control_1_t::aligned_t::enum_t val) {  control_1.rmw( val );}
    inline void aligned_edge() { control_1.rmw( control_1_t::aligned_t::edge );}
    inline void aligned_center_counting_up() { control_1.rmw( control_1_t::aligned_t::center_counting_up );}
    inline void aligned_center_counting_down() { control_1.rmw( control_1_t::aligned_t::center_counting_down );}
    inline void aligned_center_counting_up_down() { control_1.rmw( control_1_t::aligned_t::center_counting_up_down );}
    inline auto aligned() const { return control_1.rd<control_1_t::aligned_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}

    inline void ti_clock_division(const control_1_t::ti_clock_division_t::enum_t val) {  control_1.rmw( val );}
    inline void ti_clock_division_div1() { control_1.rmw( control_1_t::ti_clock_division_t::div1 );}
    inline void ti_clock_division_div2() { control_1.rmw( control_1_t::ti_clock_division_t::div2 );}
    inline void ti_clock_division_div4() { control_1.rmw( control_1_t::ti_clock_division_t::div4 );}
    inline auto ti_clock_division() const { return control_1.rd<control_1_t::ti_clock_division_t>();}

    struct control_2_t : public read_write_32_t
    {
      struct cc_dma_selection_t         { enum enum_t { offset=3, mask=1, cc_event=0, update_event }; } ;
      struct master_mode_selection_t    { enum enum_t { offset=4, mask=0b111, reset=0, enable, update, oc1_pulse, oc1_ref, oc2_ref, oc3_ref, oc4_ref}; } ;
      struct ti1_selection_t            { enum enum_t { offset=7, mask=1, chanel1_pin=0, chanel1_2_3_pin_xor }; } ;
    } ;

    inline void cc_dma_selection(const control_2_t::cc_dma_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void cc_dma_selection_cc_event()     { control_2.rmw( control_2_t::cc_dma_selection_t::cc_event );}
    inline void cc_dma_selection_update_event() { control_2.rmw( control_2_t::cc_dma_selection_t::update_event );}
    inline auto cc_dma_selection() const { return control_2.rd<control_2_t::cc_dma_selection_t>();}

    inline void master_mode_selection(const control_2_t::master_mode_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void master_mode_selection_reset() { control_2.rmw( control_2_t::master_mode_selection_t::reset );}
    inline void master_mode_selection_enable() { control_2.rmw( control_2_t::master_mode_selection_t::enable );}
    inline void master_mode_selection_update() { control_2.rmw( control_2_t::master_mode_selection_t::update );}
    inline void master_mode_selection_oc1_pulse() { control_2.rmw( control_2_t::master_mode_selection_t::oc1_pulse );}
    inline void master_mode_selection_oc1_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc1_ref );}
    inline void master_mode_selection_oc2_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc2_ref  );}
    inline void master_mode_selection_oc3_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc3_ref  );}
    inline void master_mode_selection_oc4_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc4_ref  );}
    inline auto master_mode_selection() const { return control_2.rd<control_2_t::master_mode_selection_t>();}

    inline void ti1_selection(const control_2_t::ti1_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void ti1_selection_chanel1_pin()     { control_2.rmw( control_2_t::ti1_selection_t::chanel1_pin );}
    inline void ti1_selection_chanel1_2_3_pin_xor() { control_2.rmw( control_2_t::ti1_selection_t::chanel1_2_3_pin_xor );}
    inline auto ti1_selection() const { return control_2.rd<control_2_t::ti1_selection_t>();}

    struct slave_mode_control_t : public read_write_32_t
    {
      struct slave_mode_t  { enum enum_t { offset=0, mask=0b111, disable=0, encoder_mode_1, encoder_mode_2, encoder_mode_3, reset, gated, trigger, extrenal_clock }; } ;
      struct trigger_t  { enum enum_t { offset=4, mask=0b111, internal_trigger_0=0, internal_trigger_1, internal_trigger_2, internal_trigger_3, ti1_edge_detector, filtered_timer_input_1, filtered_timer_input_2, external_trigger_input}; } ;
      struct master_slave_mode_t  { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct external_trigger_filter_t  { enum enum_t { offset=8, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_6, fdts2_8, fdts4_6, fdts4_8, fdts8_6, fdts8_8, fdts16_5, fdts16_6, fdts16_8, fdts32_5, fdts32_6, fdts32_8}; } ;
      struct external_trigger_prescaler_t  { enum enum_t { offset=12, mask=0b11, div1=0, div2, div4, div8 }; } ;
      struct external_clock_t { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
      struct external_trigger_polarity_t  { enum enum_t { offset=15, mask=1, rise_edge=0, fall_edge }; } ;


    };

    inline void slave_mode(const slave_mode_control_t::slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::disable );}
    inline void slave_mode_encoder_mode_1() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_1 );}
    inline void slave_mode_encoder_mode_2() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_2 );}
    inline void slave_mode_encoder_mode_3() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_3 );}
    inline void slave_mode_reset() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::reset );}
    inline void slave_mode_gated() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::gated );}
    inline void slave_mode_trigger() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::trigger );}
    inline void slave_mode_extrenal_clock() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::extrenal_clock );}
    inline auto slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::slave_mode_t>();}

    inline void trigger(const slave_mode_control_t::trigger_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void trigger_internal_trigger_0() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_0 );}
    inline void trigger_internal_trigger_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_1 );}
    inline void trigger_internal_trigger_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_2 );}
    inline void trigger_internal_trigger_3() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_3 );}
    inline void trigger_internal_ti1_edge_detector() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::ti1_edge_detector );}
    inline void trigger_internal_filtered_timer_input_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_1 );}
    inline void trigger_internal_filtered_timer_input_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_2 );}
    inline void trigger_internal_external_trigger_input() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::external_trigger_input );}
    inline auto trigger() const { return slave_mode_control.rd<slave_mode_control_t::trigger_t>();}

    inline void master_slave_mode(const slave_mode_control_t::master_slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void master_slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::disable );}
    inline void master_slave_mode_enable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::enable );}
    inline auto master_slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::master_slave_mode_t>();}

    inline void external_trigger_filter(const slave_mode_control_t::external_trigger_filter_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_filter_disable() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::disable );}
    inline void external_trigger_filter_fck_n2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n2 );}
    inline void external_trigger_filter_fck_n4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n4 );}
    inline void external_trigger_filter_fck_n8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n8 );}
    inline void external_trigger_filter_fdts2_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_6 );}
    inline void external_trigger_filter_fdts2_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_8 );}
    inline void external_trigger_filter_fdts4_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_6 );}
    inline void external_trigger_filter_fdts4_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_8 );}
    inline void external_trigger_filter_fdts8_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_6 );}
    inline void external_trigger_filter_fdts8_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_8 );}
    inline void external_trigger_filter_fdts16_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_5 );}
    inline void external_trigger_filter_fdts16_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_6 );}
    inline void external_trigger_filter_fdts16_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_8 );}
    inline void external_trigger_filter_fdts32_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_5 );}
    inline void external_trigger_filter_fdts32_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_6 );}
    inline void external_trigger_filter_fdts32_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_8 );}
    inline auto external_trigger_filter() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_filter_t>();}

    inline void external_trigger_prescaler(const slave_mode_control_t::external_trigger_prescaler_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_prescaler_div1() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div1 );}
    inline void external_trigger_prescaler_div2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div2 );}
    inline void external_trigger_prescaler_div4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div4 );}
    inline void external_trigger_prescaler_div8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div8 );}
    inline auto external_trigger_prescaler() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_prescaler_t>();}

    inline void external_clock(const slave_mode_control_t::external_clock_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_clock_disable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::disable );}
    inline void external_clock_enable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::enable );}
    inline auto external_clock() const { return slave_mode_control.rd<slave_mode_control_t::external_clock_t>();}


    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t    { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct cc1_interrupt_t       { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
      struct cc2_interrupt_t       { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
      struct cc3_interrupt_t       { enum enum_t { offset=3, mask=1, disable=0, enable}; } ;
      struct cc4_interrupt_t       { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
      struct trigger_interrupt_t   { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
      struct update_dma_request_t  { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
      struct cc1_dma_request_t     { enum enum_t { offset=9, mask=1, disable=0, enable}; } ;
      struct cc2_dma_request_t     { enum enum_t { offset=10, mask=1, disable=0, enable}; } ;
      struct cc3_dma_request_t     { enum enum_t { offset=11, mask=1, disable=0, enable}; } ;
      struct cc4_dma_request_t     { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
      struct trigger_dma_request_t { enum enum_t { offset=14, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void cc1_interrupt(const dma_interrupt_t::cc1_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::enable );}
    inline void cc1_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::disable );}
    inline auto cc1_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc1_interrupt_t>();}

    inline void cc2_interrupt(const dma_interrupt_t::cc2_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::enable );}
    inline void cc2_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::disable );}
    inline auto cc2_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc2_interrupt_t>();}

    inline void cc3_interrupt(const dma_interrupt_t::cc3_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::enable );}
    inline void cc3_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::disable );}
    inline auto cc3_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc3_interrupt_t>();}

    inline void cc4_interrupt(const dma_interrupt_t::cc4_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::enable );}
    inline void cc4_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::disable );}
    inline auto cc4_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc4_interrupt_t>();}

    inline void trigger_interrupt(const dma_interrupt_t::trigger_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::enable );}
    inline void trigger_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::disable );}
    inline auto trigger_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::trigger_interrupt_t>();}

    inline void update_dma_request(const dma_interrupt_t::update_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::enable );}
    inline void update_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::disable );}
    inline auto update_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::update_dma_request_t>();}

    inline void cc1_dma_request(const dma_interrupt_t::cc1_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::enable );}
    inline void cc1_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::disable );}
    inline auto cc1_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc1_dma_request_t>();}

    inline void cc2_dma_request(const dma_interrupt_t::cc2_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::enable );}
    inline void cc2_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::disable );}
    inline auto cc2_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc2_dma_request_t>();}

    inline void cc3_dma_request(const dma_interrupt_t::cc3_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::enable );}
    inline void cc3_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::disable );}
    inline auto cc3_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc3_dma_request_t>();}

    inline void cc4_dma_request(const dma_interrupt_t::cc4_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::enable );}
    inline void cc4_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::disable );}
    inline auto cc4_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc4_dma_request_t>();}

    inline void trigger_dma_request(const dma_interrupt_t::trigger_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::enable );}
    inline void trigger_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::disable );}
    inline auto trigger_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::trigger_interrupt_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
      struct cc1_interrupt_flag_t { enum enum_t { offset=1, mask=1, no_occured=0, occured}; } ;
      struct cc2_interrupt_flag_t { enum enum_t { offset=2, mask=1, no_occured=0, occured}; } ;
      struct cc3_interrupt_flag_t { enum enum_t { offset=3, mask=1, no_occured=0, occured}; } ;
      struct cc4_interrupt_flag_t { enum enum_t { offset=4, mask=1, no_occured=0, occured}; } ;
      struct trigger_interrupt_flag_t       { enum enum_t { offset=6, mask=1, no_occured=0, occured}; } ;

      struct cc1_ovecapture_flag_t { enum enum_t { offset=9, mask=1, no_occured=0, occured}; } ;
      struct cc2_ovecapture_flag_t { enum enum_t { offset=10, mask=1, no_occured=0, occured}; } ;
      struct cc3_ovecapture_flag_t { enum enum_t { offset=11, mask=1, no_occured=0, occured}; } ;
      struct cc4_ovecapture_flag_t { enum enum_t { offset=12, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    inline void cc1_interrupt_flag_clear() { status.rmw( status_t::cc1_interrupt_flag_t::no_occured );}
    inline auto cc1_interrupt_flag() const { return status.rd<status_t::cc1_interrupt_flag_t>();}

    inline void cc2_interrupt_flag_clear() { status.rmw( status_t::cc2_interrupt_flag_t::no_occured );}
    inline auto cc2_interrupt_flag() const { return status.rd<status_t::cc2_interrupt_flag_t>();}

    inline void cc3_interrupt_flag_clear() { status.rmw( status_t::cc3_interrupt_flag_t::no_occured );}
    inline auto cc3_interrupt_flag() const { return status.rd<status_t::cc3_interrupt_flag_t>();}

    inline void cc4_interrupt_flag_clear() { status.rmw( status_t::cc4_interrupt_flag_t::no_occured );}
    inline auto cc4_interrupt_flag() const { return status.rd<status_t::cc4_interrupt_flag_t>();}

    inline void trigger_interrupt_flag_clear() { status.rmw( status_t::trigger_interrupt_flag_t::no_occured );}
    inline auto trigger_interrupt_flag() const { return status.rd<status_t::trigger_interrupt_flag_t>();}

    inline void cc1_ovecapture_flag_clear() { status.rmw( status_t::cc1_ovecapture_flag_t::no_occured );}
    inline auto cc1_ovecapture_flag() const { return status.rd<status_t::cc1_ovecapture_flag_t>();}

    inline void cc2_ovecapture_flag_clear() { status.rmw( status_t::cc2_ovecapture_flag_t::no_occured );}
    inline auto cc2_ovecapture_flag() const { return status.rd<status_t::cc2_ovecapture_flag_t>();}

    inline void cc3_ovecapture_flag_clear() { status.rmw( status_t::cc3_ovecapture_flag_t::no_occured );}
    inline auto cc3_ovecapture_flag() const { return status.rd<status_t::cc3_ovecapture_flag_t>();}

    inline void cc4_ovecapture_flag_clear() { status.rmw( status_t::cc4_ovecapture_flag_t::no_occured );}
    inline auto cc4_ovecapture_flag() const { return status.rd<status_t::cc4_ovecapture_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t   { enum enum_t { offset=0, mask=1, perform=1}; } ;
      struct  cc1_t      { enum enum_t { offset=1, mask=1, perform=1}; } ;
      struct  cc2_t      { enum enum_t { offset=2, mask=1, perform=1}; } ;
      struct  cc3_t      { enum enum_t { offset=3, mask=1, perform=1}; } ;
      struct  cc4_t      { enum enum_t { offset=4, mask=1, perform=1}; } ;
      struct  trigger_t  { enum enum_t { offset=6, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generate() { event_generation.rmw( event_generation_t::update_t::perform );}
    inline void cc1_event_generate()    { event_generation.rmw( event_generation_t::cc1_t::perform );}
    inline void cc2_event_generate()    { event_generation.rmw( event_generation_t::cc2_t::perform );}
    inline void cc3_event_generate()    { event_generation.rmw( event_generation_t::cc3_t::perform );}
    inline void cc4_event_generate()    { event_generation.rmw( event_generation_t::cc4_t::perform );}
    inline void trigger_event_generate(){ event_generation.rmw( event_generation_t::trigger_t::perform );}

    struct cc_mode_1_t : public read_write_32_t
      {
        struct  cc1_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_1, inpit_capture_internal_trigger_2, inpit_capture_trc}; } ;

        struct  oc1_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc1_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc1_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc1_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic1_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic1_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc2_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_2, inpit_capture_internal_trigger_1, inpit_capture_trc}; } ;

        struct  oc2_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc2_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc2_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc2_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic2_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic2_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc1_selection(const cc_mode_1_t::cc1_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc1_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::output_compare );}
    inline void cc1_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc1_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc1_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_trc );}
    inline auto cc1_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc1_selection_t>();}

    inline void oc1_fast(const cc_mode_1_t::oc1_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::disable );}
    inline void oc1_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::enable );}
    inline auto oc1_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc1_fast_t>();}

    inline void oc1_preload(const cc_mode_1_t::oc1_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::disable );}
    inline void oc1_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::enable );}
    inline auto oc1_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc1_preload_t>();}

    inline void oc1_mode(const cc_mode_1_t::oc1_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::frozen );}
    inline void oc1_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::active );}
    inline void oc1_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::inactive );}
    inline void oc1_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::toggle );}
    inline void oc1_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_inactive );}
    inline void oc1_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_active );}
    inline void oc1_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm1 );}
    inline void oc1_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm2 );}
    inline auto oc1_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc1_mode_t>();}

    inline void oc1_clear(const cc_mode_1_t::oc1_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::disable );}
    inline void oc1_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::enable );}
    inline auto oc1_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc1_clear_t>();}

    inline void ic1_precscaler(const cc_mode_1_t::ic1_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_first );}
    inline void ic1_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_second );}
    inline void ic1_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_thirh );}
    inline void ic1_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_eighth );}
    inline auto ic1_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic1_precscaler_t>();}

    inline void ic1_filter(const cc_mode_1_t::ic1_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::disable );}
    inline void ic1_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n2 );}
    inline void ic1_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n4 );}
    inline void ic1_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n8 );}
    inline void ic1_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n6 );}
    inline void ic1_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n8 );}
    inline void ic1_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n6 );}
    inline void ic1_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n8 );}
    inline void ic1_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n6 );}
    inline void ic1_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n8 );}
    inline void ic1_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n5 );}
    inline void ic1_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n6 );}
    inline void ic1_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n8 );}
    inline void ic1_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n5 );}
    inline void ic1_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n6 );}
    inline void ic1_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n8 );}
    inline auto ic1_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic1_filter>();}


    inline void cc2_selection(const cc_mode_1_t::cc2_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc2_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::output_compare );}
    inline void cc2_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc2_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc2_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_trc );}
    inline auto cc2_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc2_selection_t>();}

    inline void oc2_fast(const cc_mode_1_t::oc2_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::disable );}
    inline void oc2_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::enable );}
    inline auto oc2_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc2_fast_t>();}

    inline void oc2_preload(const cc_mode_1_t::oc2_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::disable );}
    inline void oc2_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::enable );}
    inline auto oc2_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc2_preload_t>();}

    inline void oc2_mode(const cc_mode_1_t::oc2_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::frozen );}
    inline void oc2_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::active );}
    inline void oc2_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::inactive );}
    inline void oc2_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::toggle );}
    inline void oc2_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_inactive );}
    inline void oc2_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_active );}
    inline void oc2_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm1 );}
    inline void oc2_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm2 );}
    inline auto oc2_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc2_mode_t>();}

    inline void oc2_clear(const cc_mode_1_t::oc2_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::disable );}
    inline void oc2_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::enable );}
    inline auto oc2_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc2_clear_t>();}

    inline void ic2_precscaler(const cc_mode_1_t::ic2_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_first );}
    inline void ic2_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_second );}
    inline void ic2_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_thirh );}
    inline void ic2_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_eighth );}
    inline auto ic2_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic2_precscaler_t>();}

    inline void ic2_filter(const cc_mode_1_t::ic2_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::disable );}
    inline void ic2_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n2 );}
    inline void ic2_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n4 );}
    inline void ic2_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n8 );}
    inline void ic2_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n6 );}
    inline void ic2_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n8 );}
    inline void ic2_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n6 );}
    inline void ic2_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n8 );}
    inline void ic2_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n6 );}
    inline void ic2_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n8 );}
    inline void ic2_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n5 );}
    inline void ic2_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n6 );}
    inline void ic2_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n8 );}
    inline void ic2_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n5 );}
    inline void ic2_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n6 );}
    inline void ic2_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n8 );}
    inline auto ic2_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic2_filter>();}

    struct cc_mode_2_t : public read_write_32_t
      {
        struct  cc3_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_3, inpit_capture_internal_trigger_4, inpit_capture_trc}; } ;

        struct  oc3_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc3_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc3_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc3_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic3_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic3_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc4_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_4, inpit_capture_internal_trigger_3, inpit_capture_trc}; } ;

        struct  oc4_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc4_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc4_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc4_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic4_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic4_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc3_selection(const cc_mode_2_t::cc3_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc3_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::output_compare );}
    inline void cc3_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc3_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc3_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_trc );}
    inline auto cc3_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc3_selection_t>();}

    inline void oc3_fast(const cc_mode_2_t::oc3_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::disable );}
    inline void oc3_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::enable );}
    inline auto oc3_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc3_fast_t>();}

    inline void oc3_preload(const cc_mode_2_t::oc3_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::disable );}
    inline void oc3_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::enable );}
    inline auto oc3_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc3_preload_t>();}

    inline void oc3_mode(const cc_mode_2_t::oc3_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::frozen );}
    inline void oc3_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::active );}
    inline void oc3_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::inactive );}
    inline void oc3_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::toggle );}
    inline void oc3_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_inactive );}
    inline void oc3_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_active );}
    inline void oc3_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm1 );}
    inline void oc3_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm2 );}
    inline auto oc3_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc3_mode_t>();}

    inline void oc3_clear(const cc_mode_2_t::oc3_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::disable );}
    inline void oc3_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::enable );}
    inline auto oc3_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc3_clear_t>();}

    inline void ic3_precscaler(const cc_mode_2_t::ic3_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_first );}
    inline void ic3_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_second );}
    inline void ic3_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_thirh );}
    inline void ic3_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_eighth );}
    inline auto ic3_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic3_precscaler_t>();}

    inline void ic3_filter(const cc_mode_2_t::ic3_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::disable );}
    inline void ic3_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n2 );}
    inline void ic3_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n4 );}
    inline void ic3_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n8 );}
    inline void ic3_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n6 );}
    inline void ic3_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n8 );}
    inline void ic3_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n6 );}
    inline void ic3_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n8 );}
    inline void ic3_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n6 );}
    inline void ic3_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n8 );}
    inline void ic3_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n5 );}
    inline void ic3_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n6 );}
    inline void ic3_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n8 );}
    inline void ic3_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n5 );}
    inline void ic3_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n6 );}
    inline void ic3_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n8 );}
    inline auto ic3_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic3_filter>();}


    inline void cc4_selection(const cc_mode_2_t::cc4_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc4_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::output_compare );}
    inline void cc4_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc4_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc4_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_trc );}
    inline auto cc4_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc4_selection_t>();}

    inline void oc4_fast(const cc_mode_2_t::oc4_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::disable );}
    inline void oc4_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::enable );}
    inline auto oc4_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc4_fast_t>();}

    inline void oc4_preload(const cc_mode_2_t::oc4_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::disable );}
    inline void oc4_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::enable );}
    inline auto oc4_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc4_preload_t>();}

    inline void oc4_mode(const cc_mode_2_t::oc4_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::frozen );}
    inline void oc4_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::active );}
    inline void oc4_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::inactive );}
    inline void oc4_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::toggle );}
    inline void oc4_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_inactive );}
    inline void oc4_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_active );}
    inline void oc4_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm1 );}
    inline void oc4_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm2 );}
    inline auto oc4_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc4_mode_t>();}

    inline void oc4_clear(const cc_mode_2_t::oc4_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::disable );}
    inline void oc4_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::enable );}
    inline auto oc4_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc4_clear_t>();}

    inline void ic4_precscaler(const cc_mode_2_t::ic4_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_first );}
    inline void ic4_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_second );}
    inline void ic4_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_thirh );}
    inline void ic4_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_eighth );}
    inline auto ic4_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic4_precscaler_t>();}

    inline void ic4_filter(const cc_mode_2_t::ic4_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::disable );}
    inline void ic4_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n2 );}
    inline void ic4_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n4 );}
    inline void ic4_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n8 );}
    inline void ic4_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n6 );}
    inline void ic4_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n8 );}
    inline void ic4_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n6 );}
    inline void ic4_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n8 );}
    inline void ic4_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n6 );}
    inline void ic4_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n8 );}
    inline void ic4_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n5 );}
    inline void ic4_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n6 );}
    inline void ic4_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n8 );}
    inline void ic4_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n5 );}
    inline void ic4_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n6 );}
    inline void ic4_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n8 );}
    inline auto ic4_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic4_filter>();}

    struct cc_enable_t : public read_write_32_t
      {
        struct  cc1_state_t   { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
        struct  cc1_config_t  { enum enum_t { offset=1, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc2_state_t   { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
        struct  cc2_config_t  { enum enum_t { offset=5, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc3_state_t   { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
        struct  cc3_config_t  { enum enum_t { offset=9, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc4_state_t   { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
        struct  cc4_config_t  { enum enum_t { offset=13, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;
      } ;

    inline void cc1_state(const cc_enable_t::cc1_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc1_disable() { cc_enable.rmw( cc_enable_t::cc1_state_t::disable );}
    inline void cc1_enable() { cc_enable.rmw( cc_enable_t::cc1_state_t::enable );}
    inline auto cc1_state() const { return cc_enable.rd<cc_enable_t::cc1_state_t>();}

    // как output compare
    inline void oc1_polarity(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1_polarity_high() { cc_enable.rmw( cc_enable_t::cc1_config_t::high );}
    inline void oc1_polarity_low() { cc_enable.rmw( cc_enable_t::cc1_config_t::low );}
    inline auto oc1_polarity() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    // как input capture
    inline void ic1_config(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic1_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_rise );}
    inline void ic1_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc1_config_t::inverted_fall );}
    inline void ic1_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_both );}
    inline auto ic1_config() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    inline void cc2_state(const cc_enable_t::cc2_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc2_disable() { cc_enable.rmw( cc_enable_t::cc2_state_t::disable );}
    inline void cc2_enable() { cc_enable.rmw( cc_enable_t::cc2_state_t::enable );}
    inline auto cc2_state() const { return cc_enable.rd<cc_enable_t::cc2_state_t>();}

    // как output compare
    inline void oc2_polarity(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2_polarity_high() { cc_enable.rmw( cc_enable_t::cc2_config_t::high );}
    inline void oc2_polarity_low() { cc_enable.rmw( cc_enable_t::cc2_config_t::low );}
    inline auto oc2_polarity() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    // как input capture
    inline void ic2_config(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic2_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_rise );}
    inline void ic2_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc2_config_t::inverted_fall );}
    inline void ic2_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_both );}
    inline auto ic2_config() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    inline void cc3_state(const cc_enable_t::cc3_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc3_disable() { cc_enable.rmw( cc_enable_t::cc3_state_t::disable );}
    inline void cc3_enable() { cc_enable.rmw( cc_enable_t::cc3_state_t::enable );}
    inline auto cc3_state() const { return cc_enable.rd<cc_enable_t::cc3_state_t>();}

    // как output compare
    inline void oc3_polarity(const cc_enable_t::cc3_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc3_polarity_high() { cc_enable.rmw( cc_enable_t::cc3_config_t::high );}
    inline void oc3_polarity_low() { cc_enable.rmw( cc_enable_t::cc3_config_t::low );}
    inline auto oc3_polarity() const { return cc_enable.rd<cc_enable_t::cc3_config_t>();}

    // как input capture
    inline void ic3_config(const cc_enable_t::cc3_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic3_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc3_config_t::non_inverted_rise );}
    inline void ic3_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc3_config_t::inverted_fall );}
    inline void ic3_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc3_config_t::non_inverted_both );}
    inline auto ic3_config() const { return cc_enable.rd<cc_enable_t::cc3_config_t>();}

    inline void cc4_state(const cc_enable_t::cc4_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc4_disable() { cc_enable.rmw( cc_enable_t::cc4_state_t::disable );}
    inline void cc4_enable() { cc_enable.rmw( cc_enable_t::cc4_state_t::enable );}
    inline auto cc4_state() const { return cc_enable.rd<cc_enable_t::cc4_state_t>();}

    // как output compare
    inline void oc4_polarity(const cc_enable_t::cc4_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc4_polarity_high() { cc_enable.rmw( cc_enable_t::cc4_config_t::high );}
    inline void oc4_polarity_low() { cc_enable.rmw( cc_enable_t::cc4_config_t::low );}
    inline auto oc4_polarity() const { return cc_enable.rd<cc_enable_t::cc4_config_t>();}

    // как input capture
    inline void ic4_config(const cc_enable_t::cc4_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic4_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc4_config_t::non_inverted_rise );}
    inline void ic4_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc4_config_t::inverted_fall );}
    inline void ic4_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc4_config_t::non_inverted_both );}
    inline auto ic4_config() const { return cc_enable.rd<cc_enable_t::cc4_config_t>();}

    struct dma_control_t : public read_write_32_t
      {
        struct  dma_base_address_t   { enum enum_t { offset=0, mask=0b11111, control_1=0, control_2, slave_mode_control, dma_interrupt, status, event_generation,
  	                                                                   cc_mode_1, cc_mode_2, cc_enable, counter, prescaler,
  									   auto_reload, cc1=13, cc2, cc3, cc4,
  									   dma_control=17,  dma_address
                                     }; } ;
        struct  dma_burst_length_t   { enum enum_t { offset=8, mask=0b11111}; } ;
      } ;
    inline void dma_base_address(const dma_control_t::dma_base_address_t::enum_t val) {  dma_control.rmw( val );}
    inline void dma_base_address_control_1() { dma_control.rmw( dma_control_t::dma_base_address_t::control_1 );}
    inline void dma_base_address_control_2() { dma_control.rmw( dma_control_t::dma_base_address_t::control_2 );}
    inline void dma_base_address_slave_mode_control() { dma_control.rmw( dma_control_t::dma_base_address_t::slave_mode_control );}
    inline void dma_base_address_dma_interrupt() { dma_control.rmw( dma_control_t::dma_base_address_t::dma_interrupt );}
    inline void dma_base_address_status() { dma_control.rmw( dma_control_t::dma_base_address_t::status );}
    inline void dma_base_address_event_generation() { dma_control.rmw( dma_control_t::dma_base_address_t::event_generation );}
    inline void dma_base_address_cc_mode_1() { dma_control.rmw( dma_control_t::dma_base_address_t::cc_mode_1 );}
    inline void dma_base_address_cc_mode_2() { dma_control.rmw( dma_control_t::dma_base_address_t::cc_mode_2 );}
    inline void dma_base_address_cc_enable() { dma_control.rmw( dma_control_t::dma_base_address_t::cc_enable );}
    inline void dma_base_address_counter() { dma_control.rmw( dma_control_t::dma_base_address_t::counter );}
    inline void dma_base_address_prescaler() { dma_control.rmw( dma_control_t::dma_base_address_t::prescaler );}
    inline void dma_base_address_auto_reload() { dma_control.rmw( dma_control_t::dma_base_address_t::auto_reload );}
    inline void dma_base_address_cc1() { dma_control.rmw( dma_control_t::dma_base_address_t::cc1 );}
    inline void dma_base_address_cc2() { dma_control.rmw( dma_control_t::dma_base_address_t::cc2 );}
    inline void dma_base_address_cc3() { dma_control.rmw( dma_control_t::dma_base_address_t::cc3 );}
    inline void dma_base_address_cc4() { dma_control.rmw( dma_control_t::dma_base_address_t::cc4 );}
    inline void dma_base_address_dma_control() { dma_control.rmw( dma_control_t::dma_base_address_t::dma_control );}
    inline void dma_base_address_dma_address() { dma_control.rmw( dma_control_t::dma_base_address_t::dma_address );}
    inline auto dma_base_address() const { return dma_control.rd<dma_control_t::dma_base_address_t>();}


    inline void dma_burst_length( const uint8_t val) {  dma_control.rmw( (dma_control_t::dma_burst_length_t::enum_t)val );}
    inline auto dma_burst_length() const { return (uint8_t) dma_control.rd<dma_control_t::dma_burst_length_t>();}

    control_1_t               control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    control_2_t               control_2 ;          //CR2;  /*!< TIM control register 2,              Address offset: 0x04 */
    slave_mode_control_t      slave_mode_control;  //SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    dma_interrupt_t           dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t                  status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t        event_generation; //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    cc_mode_1_t  cc_mode_1 ;
    cc_mode_2_t  cc_mode_2 ;
    cc_enable_t  cc_enable ;

    volatile uint16_t counter ;
    const    uint16_t : 16 ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;

    volatile uint16_t auto_reload ;
    const    uint16_t : 16 ;



    const uint32_t : 32;

    volatile uint16_t cc1 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc2 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc3 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc4 ;
    const    uint16_t : 16 ;


    const uint32_t : 32;

    dma_control_t dma_control ;

    volatile uint16_t dma_address ;
    const    uint16_t : 16 ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim3_addr : rcc.tim3_enable(); break ;
               case tim4_addr : rcc.tim4_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim3_addr : rcc.tim3_disable(); break ;
               case tim4_addr : rcc.tim4_disable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim3_addr : rcc.tim3_reset(); break ;
               case tim4_addr : rcc.tim4_reset(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
  } ;
  struct gp4_tim_t // таймеры общего применеия, типа 4, TIM2  TIM5 (32 бит четыре канала СС) + Master/Slave
  {
    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_update_generation=0, overflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct direction_t             { enum enum_t { offset=4, mask=1, up=0, down }; } ;
      struct aligned_t               { enum enum_t { offset=5, mask=0b11, edge=0, center_counting_down, center_counting_up, center_counting_up_down }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct ti_clock_division_t     { enum enum_t { offset=8, mask=0b11, div1=0, div2, div4 }; } ;
    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_update_generation );}
    inline void update_request_source_overflow() { control_1.rmw( control_1_t::update_request_source_t::overflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void direction(const control_1_t::direction_t::enum_t val) {  control_1.rmw( val );}
    inline void direction_up() { control_1.rmw( control_1_t::direction_t::up );}
    inline void direction_down() { control_1.rmw( control_1_t::direction_t::down );}
    inline auto direction() const { return control_1.rd<control_1_t::direction_t>();}

    inline void aligned(const control_1_t::aligned_t::enum_t val) {  control_1.rmw( val );}
    inline void aligned_edge() { control_1.rmw( control_1_t::aligned_t::edge );}
    inline void aligned_center_counting_up() { control_1.rmw( control_1_t::aligned_t::center_counting_up );}
    inline void aligned_center_counting_down() { control_1.rmw( control_1_t::aligned_t::center_counting_down );}
    inline void aligned_center_counting_up_down() { control_1.rmw( control_1_t::aligned_t::center_counting_up_down );}
    inline auto aligned() const { return control_1.rd<control_1_t::aligned_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}

    inline void ti_clock_division(const control_1_t::ti_clock_division_t::enum_t val) {  control_1.rmw( val );}
    inline void ti_clock_division_div1() { control_1.rmw( control_1_t::ti_clock_division_t::div1 );}
    inline void ti_clock_division_div2() { control_1.rmw( control_1_t::ti_clock_division_t::div2 );}
    inline void ti_clock_division_div4() { control_1.rmw( control_1_t::ti_clock_division_t::div4 );}
    inline auto ti_clock_division() const { return control_1.rd<control_1_t::ti_clock_division_t>();}

    struct control_2_t : public read_write_32_t
    {
      struct cc_dma_selection_t         { enum enum_t { offset=3, mask=1, cc_event=0, update_event }; } ;
      struct master_mode_selection_t    { enum enum_t { offset=4, mask=0b111, reset=0, enable, update, oc1_pulse, oc1_ref, oc2_ref, oc3_ref, oc4_ref}; } ;
      struct ti1_selection_t            { enum enum_t { offset=7, mask=1, chanel1_pin=0, chanel1_2_3_pin_xor }; } ;
    } ;

    inline void cc_dma_selection(const control_2_t::cc_dma_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void cc_dma_selection_cc_event()     { control_2.rmw( control_2_t::cc_dma_selection_t::cc_event );}
    inline void cc_dma_selection_update_event() { control_2.rmw( control_2_t::cc_dma_selection_t::update_event );}
    inline auto cc_dma_selection() const { return control_2.rd<control_2_t::cc_dma_selection_t>();}

    inline void master_mode_selection(const control_2_t::master_mode_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void master_mode_selection_reset() { control_2.rmw( control_2_t::master_mode_selection_t::reset );}
    inline void master_mode_selection_enable() { control_2.rmw( control_2_t::master_mode_selection_t::enable );}
    inline void master_mode_selection_update() { control_2.rmw( control_2_t::master_mode_selection_t::update );}
    inline void master_mode_selection_oc1_pulse() { control_2.rmw( control_2_t::master_mode_selection_t::oc1_pulse );}
    inline void master_mode_selection_oc1_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc1_ref );}
    inline void master_mode_selection_oc2_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc2_ref  );}
    inline void master_mode_selection_oc3_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc3_ref  );}
    inline void master_mode_selection_oc4_ref() { control_2.rmw( control_2_t::master_mode_selection_t::oc4_ref  );}
    inline auto master_mode_selection() const { return control_2.rd<control_2_t::master_mode_selection_t>();}

    inline void ti1_selection(const control_2_t::ti1_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void ti1_selection_chanel1_pin()     { control_2.rmw( control_2_t::ti1_selection_t::chanel1_pin );}
    inline void ti1_selection_chanel1_2_3_pin_xor() { control_2.rmw( control_2_t::ti1_selection_t::chanel1_2_3_pin_xor );}
    inline auto ti1_selection() const { return control_2.rd<control_2_t::ti1_selection_t>();}

    struct slave_mode_control_t : public read_write_32_t
    {
      struct slave_mode_t  { enum enum_t { offset=0, mask=0b111, disable=0, encoder_mode_1, encoder_mode_2, encoder_mode_3, reset, gated, trigger, extrenal_clock }; } ;
      struct trigger_t  { enum enum_t { offset=4, mask=0b111, internal_trigger_0=0, internal_trigger_1, internal_trigger_2, internal_trigger_3, ti1_edge_detector, filtered_timer_input_1, filtered_timer_input_2, external_trigger_input}; } ;
      struct master_slave_mode_t  { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct external_trigger_filter_t  { enum enum_t { offset=8, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_6, fdts2_8, fdts4_6, fdts4_8, fdts8_6, fdts8_8, fdts16_5, fdts16_6, fdts16_8, fdts32_5, fdts32_6, fdts32_8}; } ;
      struct external_trigger_prescaler_t  { enum enum_t { offset=12, mask=0b11, div1=0, div2, div4, div8 }; } ;
      struct external_clock_t { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
      struct external_trigger_polarity_t  { enum enum_t { offset=15, mask=1, rise_edge=0, fall_edge }; } ;


    };

    inline void slave_mode(const slave_mode_control_t::slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::disable );}
    inline void slave_mode_encoder_mode_1() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_1 );}
    inline void slave_mode_encoder_mode_2() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_2 );}
    inline void slave_mode_encoder_mode_3() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_3 );}
    inline void slave_mode_reset() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::reset );}
    inline void slave_mode_gated() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::gated );}
    inline void slave_mode_trigger() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::trigger );}
    inline void slave_mode_extrenal_clock() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::extrenal_clock );}
    inline auto slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::slave_mode_t>();}

    inline void trigger(const slave_mode_control_t::trigger_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void trigger_internal_trigger_0() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_0 );}
    inline void trigger_internal_trigger_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_1 );}
    inline void trigger_internal_trigger_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_2 );}
    inline void trigger_internal_trigger_3() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_3 );}
    inline void trigger_internal_ti1_edge_detector() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::ti1_edge_detector );}
    inline void trigger_internal_filtered_timer_input_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_1 );}
    inline void trigger_internal_filtered_timer_input_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_2 );}
    inline void trigger_internal_external_trigger_input() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::external_trigger_input );}
    inline auto trigger() const { return slave_mode_control.rd<slave_mode_control_t::trigger_t>();}

    inline void master_slave_mode(const slave_mode_control_t::master_slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void master_slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::disable );}
    inline void master_slave_mode_enable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::enable );}
    inline auto master_slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::master_slave_mode_t>();}

    inline void external_trigger_filter(const slave_mode_control_t::external_trigger_filter_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_filter_disable() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::disable );}
    inline void external_trigger_filter_fck_n2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n2 );}
    inline void external_trigger_filter_fck_n4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n4 );}
    inline void external_trigger_filter_fck_n8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n8 );}
    inline void external_trigger_filter_fdts2_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_6 );}
    inline void external_trigger_filter_fdts2_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_8 );}
    inline void external_trigger_filter_fdts4_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_6 );}
    inline void external_trigger_filter_fdts4_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_8 );}
    inline void external_trigger_filter_fdts8_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_6 );}
    inline void external_trigger_filter_fdts8_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_8 );}
    inline void external_trigger_filter_fdts16_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_5 );}
    inline void external_trigger_filter_fdts16_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_6 );}
    inline void external_trigger_filter_fdts16_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_8 );}
    inline void external_trigger_filter_fdts32_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_5 );}
    inline void external_trigger_filter_fdts32_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_6 );}
    inline void external_trigger_filter_fdts32_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_8 );}
    inline auto external_trigger_filter() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_filter_t>();}

    inline void external_trigger_prescaler(const slave_mode_control_t::external_trigger_prescaler_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_prescaler_div1() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div1 );}
    inline void external_trigger_prescaler_div2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div2 );}
    inline void external_trigger_prescaler_div4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div4 );}
    inline void external_trigger_prescaler_div8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div8 );}
    inline auto external_trigger_prescaler() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_prescaler_t>();}

    inline void external_clock(const slave_mode_control_t::external_clock_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_clock_disable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::disable );}
    inline void external_clock_enable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::enable );}
    inline auto external_clock() const { return slave_mode_control.rd<slave_mode_control_t::external_clock_t>();}

    inline void external_trigger_polarity(const slave_mode_control_t::external_trigger_polarity_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_polarity_rise_edge() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_polarity_t::rise_edge );}
    inline void external_trigger_polarity_fall_edge() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_polarity_t::fall_edge );}
    inline auto external_trigger_polarity() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_polarity_t>();}


    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t    { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct cc1_interrupt_t       { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
      struct cc2_interrupt_t       { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
      struct cc3_interrupt_t       { enum enum_t { offset=3, mask=1, disable=0, enable}; } ;
      struct cc4_interrupt_t       { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
      struct trigger_interrupt_t   { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
      struct update_dma_request_t  { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
      struct cc1_dma_request_t     { enum enum_t { offset=9, mask=1, disable=0, enable}; } ;
      struct cc2_dma_request_t     { enum enum_t { offset=10, mask=1, disable=0, enable}; } ;
      struct cc3_dma_request_t     { enum enum_t { offset=11, mask=1, disable=0, enable}; } ;
      struct cc4_dma_request_t     { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
      struct trigger_dma_request_t { enum enum_t { offset=14, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void cc1_interrupt(const dma_interrupt_t::cc1_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::enable );}
    inline void cc1_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::disable );}
    inline auto cc1_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc1_interrupt_t>();}

    inline void cc2_interrupt(const dma_interrupt_t::cc2_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::enable );}
    inline void cc2_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::disable );}
    inline auto cc2_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc2_interrupt_t>();}

    inline void cc3_interrupt(const dma_interrupt_t::cc3_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::enable );}
    inline void cc3_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::disable );}
    inline auto cc3_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc3_interrupt_t>();}

    inline void cc4_interrupt(const dma_interrupt_t::cc4_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::enable );}
    inline void cc4_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::disable );}
    inline auto cc4_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc4_interrupt_t>();}

    inline void trigger_interrupt(const dma_interrupt_t::trigger_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::enable );}
    inline void trigger_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::disable );}
    inline auto trigger_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::trigger_interrupt_t>();}

    inline void update_dma_request(const dma_interrupt_t::update_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::enable );}
    inline void update_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::disable );}
    inline auto update_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::update_dma_request_t>();}

    inline void cc1_dma_request(const dma_interrupt_t::cc1_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::enable );}
    inline void cc1_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::disable );}
    inline auto cc1_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc1_dma_request_t>();}

    inline void cc2_dma_request(const dma_interrupt_t::cc2_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::enable );}
    inline void cc2_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::disable );}
    inline auto cc2_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc2_dma_request_t>();}

    inline void cc3_dma_request(const dma_interrupt_t::cc3_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::enable );}
    inline void cc3_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::disable );}
    inline auto cc3_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc3_dma_request_t>();}

    inline void cc4_dma_request(const dma_interrupt_t::cc4_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::enable );}
    inline void cc4_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::disable );}
    inline auto cc4_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc4_dma_request_t>();}

    inline void trigger_dma_request(const dma_interrupt_t::trigger_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::enable );}
    inline void trigger_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::disable );}
    inline auto trigger_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::trigger_dma_request_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
      struct cc1_interrupt_flag_t { enum enum_t { offset=1, mask=1, no_occured=0, occured}; } ;
      struct cc2_interrupt_flag_t { enum enum_t { offset=2, mask=1, no_occured=0, occured}; } ;
      struct cc3_interrupt_flag_t { enum enum_t { offset=3, mask=1, no_occured=0, occured}; } ;
      struct cc4_interrupt_flag_t { enum enum_t { offset=4, mask=1, no_occured=0, occured}; } ;
      struct trigger_interrupt_flag_t       { enum enum_t { offset=6, mask=1, no_occured=0, occured}; } ;

      struct cc1_ovecapture_flag_t { enum enum_t { offset=9, mask=1, no_occured=0, occured}; } ;
      struct cc2_ovecapture_flag_t { enum enum_t { offset=10, mask=1, no_occured=0, occured}; } ;
      struct cc3_ovecapture_flag_t { enum enum_t { offset=11, mask=1, no_occured=0, occured}; } ;
      struct cc4_ovecapture_flag_t { enum enum_t { offset=12, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    inline void cc1_interrupt_flag_clear() { status.rmw( status_t::cc1_interrupt_flag_t::no_occured );}
    inline auto cc1_interrupt_flag() const { return status.rd<status_t::cc1_interrupt_flag_t>();}

    inline void cc2_interrupt_flag_clear() { status.rmw( status_t::cc2_interrupt_flag_t::no_occured );}
    inline auto cc2_interrupt_flag() const { return status.rd<status_t::cc2_interrupt_flag_t>();}

    inline void cc3_interrupt_flag_clear() { status.rmw( status_t::cc3_interrupt_flag_t::no_occured );}
    inline auto cc3_interrupt_flag() const { return status.rd<status_t::cc3_interrupt_flag_t>();}

    inline void cc4_interrupt_flag_clear() { status.rmw( status_t::cc4_interrupt_flag_t::no_occured );}
    inline auto cc4_interrupt_flag() const { return status.rd<status_t::cc4_interrupt_flag_t>();}

    inline void trigger_interrupt_flag_clear() { status.rmw( status_t::trigger_interrupt_flag_t::no_occured );}
    inline auto trigger_interrupt_flag() const { return status.rd<status_t::trigger_interrupt_flag_t>();}

    inline void cc1_ovecapture_flag_clear() { status.rmw( status_t::cc1_ovecapture_flag_t::no_occured );}
    inline auto cc1_ovecapture_flag() const { return status.rd<status_t::cc1_ovecapture_flag_t>();}

    inline void cc2_ovecapture_flag_clear() { status.rmw( status_t::cc2_ovecapture_flag_t::no_occured );}
    inline auto cc2_ovecapture_flag() const { return status.rd<status_t::cc2_ovecapture_flag_t>();}

    inline void cc3_ovecapture_flag_clear() { status.rmw( status_t::cc3_ovecapture_flag_t::no_occured );}
    inline auto cc3_ovecapture_flag() const { return status.rd<status_t::cc3_ovecapture_flag_t>();}

    inline void cc4_ovecapture_flag_clear() { status.rmw( status_t::cc4_ovecapture_flag_t::no_occured );}
    inline auto cc4_ovecapture_flag() const { return status.rd<status_t::cc4_ovecapture_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t   { enum enum_t { offset=0, mask=1, perform=1}; } ;
      struct  cc1_t      { enum enum_t { offset=1, mask=1, perform=1}; } ;
      struct  cc2_t      { enum enum_t { offset=2, mask=1, perform=1}; } ;
      struct  cc3_t      { enum enum_t { offset=3, mask=1, perform=1}; } ;
      struct  cc4_t      { enum enum_t { offset=4, mask=1, perform=1}; } ;
      struct  trigger_t  { enum enum_t { offset=6, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generate() { event_generation.rmw( event_generation_t::update_t::perform );}
    inline void cc1_generate()          { event_generation.rmw( event_generation_t::cc1_t::perform );}
    inline void cc2_generate()          { event_generation.rmw( event_generation_t::cc2_t::perform );}
    inline void cc3_generate()          { event_generation.rmw( event_generation_t::cc3_t::perform );}
    inline void cc4_generate()          { event_generation.rmw( event_generation_t::cc4_t::perform );}
    inline void trigger_generate()          { event_generation.rmw( event_generation_t::trigger_t::perform );}

    struct cc_mode_1_t : public read_write_32_t
      {
        struct  cc1_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_1, inpit_capture_internal_trigger_2, inpit_capture_trc}; } ;

        struct  oc1_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc1_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc1_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc1_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic1_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic1_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc2_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_2, inpit_capture_internal_trigger_1, inpit_capture_trc}; } ;

        struct  oc2_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc2_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc2_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc2_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic2_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic2_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc1_selection(const cc_mode_1_t::cc1_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc1_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::output_compare );}
    inline void cc1_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc1_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc1_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_trc );}
    inline auto cc1_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc1_selection_t>();}

    inline void oc1_fast(const cc_mode_1_t::oc1_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::disable );}
    inline void oc1_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::enable );}
    inline auto oc1_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc1_fast_t>();}

    inline void oc1_preload(const cc_mode_1_t::oc1_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::disable );}
    inline void oc1_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::enable );}
    inline auto oc1_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc1_preload_t>();}

    inline void oc1_mode(const cc_mode_1_t::oc1_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::frozen );}
    inline void oc1_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::active );}
    inline void oc1_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::inactive );}
    inline void oc1_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::toggle );}
    inline void oc1_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_inactive );}
    inline void oc1_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_active );}
    inline void oc1_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm1 );}
    inline void oc1_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm2 );}
    inline auto oc1_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc1_mode_t>();}

    inline void oc1_clear(const cc_mode_1_t::oc1_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::disable );}
    inline void oc1_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::enable );}
    inline auto oc1_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc1_clear_t>();}

    inline void ic1_precscaler(const cc_mode_1_t::ic1_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_first );}
    inline void ic1_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_second );}
    inline void ic1_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_thirh );}
    inline void ic1_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_eighth );}
    inline auto ic1_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic1_precscaler_t>();}

    inline void ic1_filter(const cc_mode_1_t::ic1_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::disable );}
    inline void ic1_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n2 );}
    inline void ic1_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n4 );}
    inline void ic1_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n8 );}
    inline void ic1_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n6 );}
    inline void ic1_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n8 );}
    inline void ic1_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n6 );}
    inline void ic1_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n8 );}
    inline void ic1_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n6 );}
    inline void ic1_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n8 );}
    inline void ic1_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n5 );}
    inline void ic1_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n6 );}
    inline void ic1_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n8 );}
    inline void ic1_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n5 );}
    inline void ic1_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n6 );}
    inline void ic1_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n8 );}
    inline auto ic1_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic1_filter>();}


    inline void cc2_selection(const cc_mode_1_t::cc2_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc2_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::output_compare );}
    inline void cc2_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc2_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc2_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_trc );}
    inline auto cc2_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc2_selection_t>();}

    inline void oc2_fast(const cc_mode_1_t::oc2_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::disable );}
    inline void oc2_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::enable );}
    inline auto oc2_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc2_fast_t>();}

    inline void oc2_preload(const cc_mode_1_t::oc2_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::disable );}
    inline void oc2_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::enable );}
    inline auto oc2_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc2_preload_t>();}

    inline void oc2_mode(const cc_mode_1_t::oc2_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::frozen );}
    inline void oc2_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::active );}
    inline void oc2_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::inactive );}
    inline void oc2_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::toggle );}
    inline void oc2_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_inactive );}
    inline void oc2_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_active );}
    inline void oc2_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm1 );}
    inline void oc2_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm2 );}
    inline auto oc2_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc2_mode_t>();}

    inline void oc2_clear(const cc_mode_1_t::oc2_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::disable );}
    inline void oc2_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::enable );}
    inline auto oc2_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc2_clear_t>();}

    inline void ic2_precscaler(const cc_mode_1_t::ic2_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_first );}
    inline void ic2_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_second );}
    inline void ic2_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_thirh );}
    inline void ic2_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_eighth );}
    inline auto ic2_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic2_precscaler_t>();}

    inline void ic2_filter(const cc_mode_1_t::ic2_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::disable );}
    inline void ic2_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n2 );}
    inline void ic2_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n4 );}
    inline void ic2_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n8 );}
    inline void ic2_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n6 );}
    inline void ic2_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n8 );}
    inline void ic2_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n6 );}
    inline void ic2_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n8 );}
    inline void ic2_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n6 );}
    inline void ic2_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n8 );}
    inline void ic2_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n5 );}
    inline void ic2_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n6 );}
    inline void ic2_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n8 );}
    inline void ic2_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n5 );}
    inline void ic2_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n6 );}
    inline void ic2_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n8 );}
    inline auto ic2_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic2_filter>();}

    struct cc_mode_2_t : public read_write_32_t
      {
        struct  cc3_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_3, inpit_capture_internal_trigger_4, inpit_capture_trc}; } ;

        struct  oc3_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc3_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc3_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc3_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic3_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic3_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc4_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_4, inpit_capture_internal_trigger_3, inpit_capture_trc}; } ;

        struct  oc4_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc4_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc4_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc4_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic4_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic4_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc3_selection(const cc_mode_2_t::cc3_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc3_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::output_compare );}
    inline void cc3_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc3_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc3_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_trc );}
    inline auto cc3_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc3_selection_t>();}

    inline void oc3_fast(const cc_mode_2_t::oc3_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::disable );}
    inline void oc3_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::enable );}
    inline auto oc3_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc3_fast_t>();}

    inline void oc3_preload(const cc_mode_2_t::oc3_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::disable );}
    inline void oc3_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::enable );}
    inline auto oc3_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc3_preload_t>();}

    inline void oc3_mode(const cc_mode_2_t::oc3_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::frozen );}
    inline void oc3_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::active );}
    inline void oc3_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::inactive );}
    inline void oc3_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::toggle );}
    inline void oc3_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_inactive );}
    inline void oc3_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_active );}
    inline void oc3_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm1 );}
    inline void oc3_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm2 );}
    inline auto oc3_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc3_mode_t>();}

    inline void oc3_clear(const cc_mode_2_t::oc3_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::disable );}
    inline void oc3_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::enable );}
    inline auto oc3_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc3_clear_t>();}

    inline void ic3_precscaler(const cc_mode_2_t::ic3_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_first );}
    inline void ic3_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_second );}
    inline void ic3_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_thirh );}
    inline void ic3_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_eighth );}
    inline auto ic3_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic3_precscaler_t>();}

    inline void ic3_filter(const cc_mode_2_t::ic3_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::disable );}
    inline void ic3_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n2 );}
    inline void ic3_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n4 );}
    inline void ic3_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n8 );}
    inline void ic3_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n6 );}
    inline void ic3_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n8 );}
    inline void ic3_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n6 );}
    inline void ic3_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n8 );}
    inline void ic3_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n6 );}
    inline void ic3_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n8 );}
    inline void ic3_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n5 );}
    inline void ic3_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n6 );}
    inline void ic3_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n8 );}
    inline void ic3_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n5 );}
    inline void ic3_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n6 );}
    inline void ic3_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n8 );}
    inline auto ic3_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic3_filter>();}


    inline void cc4_selection(const cc_mode_2_t::cc4_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc4_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::output_compare );}
    inline void cc4_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc4_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc4_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_trc );}
    inline auto cc4_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc4_selection_t>();}

    inline void oc4_fast(const cc_mode_2_t::oc4_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::disable );}
    inline void oc4_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::enable );}
    inline auto oc4_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc4_fast_t>();}

    inline void oc4_preload(const cc_mode_2_t::oc4_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::disable );}
    inline void oc4_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::enable );}
    inline auto oc4_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc4_preload_t>();}

    inline void oc4_mode(const cc_mode_2_t::oc4_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::frozen );}
    inline void oc4_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::active );}
    inline void oc4_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::inactive );}
    inline void oc4_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::toggle );}
    inline void oc4_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_inactive );}
    inline void oc4_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_active );}
    inline void oc4_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm1 );}
    inline void oc4_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm2 );}
    inline auto oc4_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc4_mode_t>();}

    inline void oc4_clear(const cc_mode_2_t::oc4_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::disable );}
    inline void oc4_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::enable );}
    inline auto oc4_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc4_clear_t>();}

    inline void ic4_precscaler(const cc_mode_2_t::ic4_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_first );}
    inline void ic4_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_second );}
    inline void ic4_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_thirh );}
    inline void ic4_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_eighth );}
    inline auto ic4_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic4_precscaler_t>();}

    inline void ic4_filter(const cc_mode_2_t::ic4_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::disable );}
    inline void ic4_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n2 );}
    inline void ic4_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n4 );}
    inline void ic4_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n8 );}
    inline void ic4_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n6 );}
    inline void ic4_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n8 );}
    inline void ic4_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n6 );}
    inline void ic4_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n8 );}
    inline void ic4_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n6 );}
    inline void ic4_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n8 );}
    inline void ic4_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n5 );}
    inline void ic4_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n6 );}
    inline void ic4_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n8 );}
    inline void ic4_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n5 );}
    inline void ic4_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n6 );}
    inline void ic4_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n8 );}
    inline auto ic4_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic4_filter>();}

    struct cc_enable_t : public read_write_32_t
      {
        struct  cc1_state_t   { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
        struct  cc1_config_t  { enum enum_t { offset=1, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc2_state_t   { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
        struct  cc2_config_t  { enum enum_t { offset=5, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc3_state_t   { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
        struct  cc3_config_t  { enum enum_t { offset=9, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;

        struct  cc4_state_t   { enum enum_t { offset=13, mask=1, disable=0, enable}; } ;
        struct  cc4_config_t  { enum enum_t { offset=15, mask=0b111,
  	                      /*as output compare polarity*/ high=0b000, low=0b001,
                                /*as input capture */ non_inverted_rise=0b000 , inverted_fall=0b001, non_inverted_both=0b101  };
                              } ;
      } ;

    inline void cc1_state(const cc_enable_t::cc1_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc1_disable() { cc_enable.rmw( cc_enable_t::cc1_state_t::disable );}
    inline void cc1_enable() { cc_enable.rmw( cc_enable_t::cc1_state_t::enable );}
    inline auto cc1_state() const { return cc_enable.rd<cc_enable_t::cc1_state_t>();}

    // как output compare
    inline void oc1_polarity(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1_polarity_high() { cc_enable.rmw( cc_enable_t::cc1_config_t::high );}
    inline void oc1_polarity_low() { cc_enable.rmw( cc_enable_t::cc1_config_t::low );}
    inline auto oc1_polarity() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    // как input capture
    inline void ic1_config(const cc_enable_t::cc1_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic1_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_rise );}
    inline void ic1_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc1_config_t::inverted_fall );}
    inline void ic1_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc1_config_t::non_inverted_both );}
    inline auto ic1_config() const { return cc_enable.rd<cc_enable_t::cc1_config_t>();}

    inline void cc2_state(const cc_enable_t::cc2_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc2_disable() { cc_enable.rmw( cc_enable_t::cc2_state_t::disable );}
    inline void cc2_enable() { cc_enable.rmw( cc_enable_t::cc2_state_t::enable );}
    inline auto cc2_state() const { return cc_enable.rd<cc_enable_t::cc2_state_t>();}

    // как output compare
    inline void oc2_polarity(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2_polarity_high() { cc_enable.rmw( cc_enable_t::cc2_config_t::high );}
    inline void oc2_polarity_low() { cc_enable.rmw( cc_enable_t::cc2_config_t::low );}
    inline auto oc2_polarity() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    // как input capture
    inline void ic2_config(const cc_enable_t::cc2_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic2_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_rise );}
    inline void ic2_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc2_config_t::inverted_fall );}
    inline void ic2_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc2_config_t::non_inverted_both );}
    inline auto ic2_config() const { return cc_enable.rd<cc_enable_t::cc2_config_t>();}

    inline void cc3_state(const cc_enable_t::cc3_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc3_disable() { cc_enable.rmw( cc_enable_t::cc3_state_t::disable );}
    inline void cc3_enable() { cc_enable.rmw( cc_enable_t::cc3_state_t::enable );}
    inline auto cc3_state() const { return cc_enable.rd<cc_enable_t::cc3_state_t>();}

    // как output compare
    inline void oc3_polarity(const cc_enable_t::cc3_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc3_polarity_high() { cc_enable.rmw( cc_enable_t::cc3_config_t::high );}
    inline void oc3_polarity_low() { cc_enable.rmw( cc_enable_t::cc3_config_t::low );}
    inline auto oc3_polarity() const { return cc_enable.rd<cc_enable_t::cc3_config_t>();}

    // как input capture
    inline void ic3_config(const cc_enable_t::cc3_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic3_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc3_config_t::non_inverted_rise );}
    inline void ic3_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc3_config_t::inverted_fall );}
    inline void ic3_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc3_config_t::non_inverted_both );}
    inline auto ic3_config() const { return cc_enable.rd<cc_enable_t::cc3_config_t>();}

    inline void cc4_state(const cc_enable_t::cc4_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc4_disable() { cc_enable.rmw( cc_enable_t::cc4_state_t::disable );}
    inline void cc4_enable() { cc_enable.rmw( cc_enable_t::cc4_state_t::enable );}
    inline auto cc4_state() const { return cc_enable.rd<cc_enable_t::cc4_state_t>();}

    // как output compare
    inline void oc4_polarity(const cc_enable_t::cc4_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc4_polarity_high() { cc_enable.rmw( cc_enable_t::cc4_config_t::high );}
    inline void oc4_polarity_low() { cc_enable.rmw( cc_enable_t::cc4_config_t::low );}
    inline auto oc4_polarity() const { return cc_enable.rd<cc_enable_t::cc4_config_t>();}

    // как input capture
    inline void ic4_config(const cc_enable_t::cc4_config_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic4_config_non_inverted_rise() { cc_enable.rmw( cc_enable_t::cc4_config_t::non_inverted_rise );}
    inline void ic4_config_inverted_fall() { cc_enable.rmw( cc_enable_t::cc4_config_t::inverted_fall );}
    inline void ic4_config_non_inverted_both() { cc_enable.rmw( cc_enable_t::cc4_config_t::non_inverted_both );}
    inline auto ic4_config() const { return cc_enable.rd<cc_enable_t::cc4_config_t>();}

    struct dma_control_t : public read_write_32_t
      {
        struct  dma_base_address_t   { enum enum_t { offset=0, mask=0b11111, }; } ; // TODO сделать символьное смещение
        struct  dma_burst_length_t   { enum enum_t { offset=8, mask=0b11111}; } ;
      } ;

    control_1_t               control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    control_2_t               control_2 ;          //CR2;  /*!< TIM control register 2,              Address offset: 0x04 */
    slave_mode_control_t      slave_mode_control;  //SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
    dma_interrupt_t           dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t                  status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t        event_generation; //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    cc_mode_1_t  cc_mode_1 ;
    cc_mode_2_t  cc_mode_2 ;
    cc_enable_t  cc_enable ;

    volatile uint32_t counter ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;


    volatile uint32_t auto_reload ;

    const uint32_t : 32;

    volatile uint32_t cc1 ;
    volatile uint32_t cc2 ;
    volatile uint32_t cc3 ;
    volatile uint32_t cc4 ;

    const uint32_t : 32;

    dma_control_t dma_control ;

    volatile uint16_t dma_address ;
    const    uint16_t : 16 ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim2_addr : rcc.tim2_enable(); break ;
               case tim5_addr : rcc.tim5_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim2_addr : rcc.tim2_disable(); break ;
               case tim5_addr : rcc.tim5_disable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim2_addr : rcc.tim2_reset(); break ;
               case tim5_addr : rcc.tim5_reset(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
  } ;
  struct adv_tim_t // продвинутые таймеры TIM1 TIM8
  {
    adv_tim_t() {}
    struct control_1_t : public read_write_32_t
    {
      struct state_t                 { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct update_event_t          { enum enum_t { offset=1, mask=1, enable=0, disable }; } ;
      struct update_request_source_t { enum enum_t { offset=2, mask=1, overflow_underflow_update_generation=0, overflow_underflow }; } ;
      struct one_pulse_mode_t        { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
      struct direction_t             { enum enum_t { offset=4, mask=1, up=0, down }; } ;
      struct aligned_t               { enum enum_t { offset=5, mask=0b11, edge=0, center_counting_down, center_counting_up, center_counting_up_down }; } ;
      struct auto_reload_preload_t   { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct ti_clock_division_t     { enum enum_t { offset=8, mask=0b11, div1=0, div2, div4 }; } ;
    } ;

    inline void state(const control_1_t::state_t::enum_t val) {  control_1.rmw( val );}
    inline void enable() { control_1.rmw( control_1_t::state_t::enable );}
    inline void disable() { control_1.rmw( control_1_t::state_t::disable );}
    inline auto state() const { return control_1.rd<control_1_t::state_t>();}

    inline void update_event(const control_1_t::update_event_t::enum_t val) {  control_1.rmw( val );}
    inline void update_event_enable() { control_1.rmw( control_1_t::update_event_t::enable );}
    inline void update_event_disable() { control_1.rmw( control_1_t::update_event_t::disable );}
    inline auto update_event() const { return control_1.rd<control_1_t::update_event_t>();}

    inline void update_request_source(const control_1_t::update_request_source_t::enum_t val) {  control_1.rmw( val );}
    inline void update_request_source_overflow_underflow_update_generation() { control_1.rmw( control_1_t::update_request_source_t::overflow_underflow_update_generation );}
    inline void update_request_source_overflow_underflow() { control_1.rmw( control_1_t::update_request_source_t::overflow_underflow );}
    inline auto update_request_source() const { return control_1.rd<control_1_t::update_request_source_t>();}

    inline void one_pulse_mode(const control_1_t::one_pulse_mode_t::enum_t val) {  control_1.rmw( val );}
    inline void one_pulse_mode_enable() { control_1.rmw( control_1_t::one_pulse_mode_t::enable );}
    inline void one_pulse_mode_disable() { control_1.rmw( control_1_t::one_pulse_mode_t::disable );}
    inline auto one_pulse_mode() const { return control_1.rd<control_1_t::one_pulse_mode_t>();}

    inline void direction(const control_1_t::direction_t::enum_t val) {  control_1.rmw( val );}
    inline void direction_up() { control_1.rmw( control_1_t::direction_t::up );}
    inline void direction_down() { control_1.rmw( control_1_t::direction_t::down );}
    inline auto direction() const { return control_1.rd<control_1_t::direction_t>();}

    inline void aligned(const control_1_t::aligned_t::enum_t val) {  control_1.rmw( val );}
    inline void aligned_edge() { control_1.rmw( control_1_t::aligned_t::edge );}
    inline void aligned_center_counting_up() { control_1.rmw( control_1_t::aligned_t::center_counting_up );}
    inline void aligned_center_counting_down() { control_1.rmw( control_1_t::aligned_t::center_counting_down );}
    inline void aligned_center_counting_up_down() { control_1.rmw( control_1_t::aligned_t::center_counting_up_down );}
    inline auto aligned() const { return control_1.rd<control_1_t::aligned_t>();}

    inline void auto_reload_preload(const control_1_t::auto_reload_preload_t::enum_t val) {  control_1.rmw( val );}
    inline void auto_reload_preload_enable() { control_1.rmw( control_1_t::auto_reload_preload_t::enable );}
    inline void auto_reload_preload_disable() { control_1.rmw( control_1_t::auto_reload_preload_t::disable );}
    inline auto auto_reload_preload() const { return control_1.rd<control_1_t::auto_reload_preload_t>();}

    inline void ti_clock_division(const control_1_t::ti_clock_division_t::enum_t val) {  control_1.rmw( val );}
    inline void ti_clock_division_div1() { control_1.rmw( control_1_t::ti_clock_division_t::div1 );}
    inline void ti_clock_division_div2() { control_1.rmw( control_1_t::ti_clock_division_t::div2 );}
    inline void ti_clock_division_div4() { control_1.rmw( control_1_t::ti_clock_division_t::div4 );}
    inline auto ti_clock_division() const { return control_1.rd<control_1_t::ti_clock_division_t>();}

    struct control_2_t : public read_write_32_t
    {
      struct cc_preload_t               { enum enum_t { offset=0, mask=1, disable=0, enable }; } ;
      struct cc_control_update_t        { enum enum_t { offset=2, mask=1, commutation_generate=0, commutation_generate_trigger_input_rise }; } ;
      struct cc_dma_selection_t         { enum enum_t { offset=3, mask=1, cc_event=0, update_event }; } ;
      struct master_mode_selection_trgo_t    { enum enum_t { offset=4, mask=0b111, reset=0, enable, update, cc1if_pulse, oc1ref, oc2ref, oc3ref, oc4ref}; } ;
      struct ti1_selection_t            { enum enum_t { offset=7, mask=1, chanel1_pin=0, chanel1_2_3_pin_xor }; } ;
      struct oc1_output_idle_state_t    { enum enum_t { offset=8, mask=1, low=0, high }; } ;
      struct oc1n_output_idle_state_t   { enum enum_t { offset=9, mask=1, low=0, high }; } ;
      struct oc2_output_idle_state_t    { enum enum_t { offset=10,mask=1, low=0, high }; } ;
      struct oc2n_output_idle_state_t   { enum enum_t { offset=11,mask=1, low=0, high }; } ;
      struct oc3_output_idle_state_t    { enum enum_t { offset=12,mask=1, low=0, high }; } ;
      struct oc3n_output_idle_state_t   { enum enum_t { offset=13,mask=1, low=0, high }; } ;
      struct oc4_output_idle_state_t    { enum enum_t { offset=14,mask=1, low=0, high }; } ;
    } ;

    inline void cc_preload(const control_2_t::cc_preload_t::enum_t val) {  control_2.rmw( val );}
    inline void cc_preload_disable()     { control_2.rmw( control_2_t::cc_preload_t::disable );}
    inline void cc_preload_enable() { control_2.rmw( control_2_t::cc_preload_t::enable );}
    inline auto cc_preload() const { return control_2.rd<control_2_t::cc_preload_t>();}

    inline void cc_control_update(const control_2_t::cc_control_update_t::enum_t val) {  control_2.rmw( val );}
    inline void cc_control_update_commutation_generate()     { control_2.rmw( control_2_t::cc_control_update_t::commutation_generate );}
    inline void cc_control_update_commutation_generate_trigger_input_rise() { control_2.rmw( control_2_t::cc_control_update_t::commutation_generate_trigger_input_rise );}
    inline auto cc_control_update() const { return control_2.rd<control_2_t::cc_control_update_t>();}

    inline void cc_dma_selection(const control_2_t::cc_dma_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void cc_dma_selection_cc_event()     { control_2.rmw( control_2_t::cc_dma_selection_t::cc_event );}
    inline void cc_dma_selection_update_event() { control_2.rmw( control_2_t::cc_dma_selection_t::update_event );}
    inline auto cc_dma_selection() const { return control_2.rd<control_2_t::cc_dma_selection_t>();}

    inline void master_mode_selection_trgo(const control_2_t::master_mode_selection_trgo_t::enum_t val) {  control_2.rmw( val );}
    inline void master_mode_selection_trgo_reset() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::reset );}
    inline void master_mode_selection_trgo_enable() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::enable );}
    inline void master_mode_selection_trgo_update() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::update );}
    inline void master_mode_selection_trgo_cc1if_pulse() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::cc1if_pulse );}
    inline void master_mode_selection_trgo_oc1ref() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::oc1ref );}
    inline void master_mode_selection_trgo_oc2ref() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::oc2ref  );}
    inline void master_mode_selection_trgo_oc3ref() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::oc3ref  );}
    inline void master_mode_selection_trgo_oc4ref() { control_2.rmw( control_2_t::master_mode_selection_trgo_t::oc4ref  );}
    inline auto master_mode_selection_trgo() const { return control_2.rd<control_2_t::master_mode_selection_trgo_t>();}

    inline void ti1_selection(const control_2_t::ti1_selection_t::enum_t val) {  control_2.rmw( val );}
    inline void ti1_selection_chanel1_pin()     { control_2.rmw( control_2_t::ti1_selection_t::chanel1_pin );}
    inline void ti1_selection_chanel1_2_3_pin_xor() { control_2.rmw( control_2_t::ti1_selection_t::chanel1_2_3_pin_xor );}
    inline auto ti1_selection() const { return control_2.rd<control_2_t::ti1_selection_t>();}

    inline void oc1_output_idle_state(const control_2_t::oc1_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc1_output_idle_state_low()  { control_2.rmw( control_2_t::oc1_output_idle_state_t::low );}
    inline void oc1_output_idle_state_high() { control_2.rmw( control_2_t::oc1_output_idle_state_t::high );}
    inline auto oc1_output_idle_state() const { return control_2.rd<control_2_t::oc1_output_idle_state_t>();}

    inline void oc1n_output_idle_state(const control_2_t::oc1n_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc1n_output_idle_state_low()  { control_2.rmw( control_2_t::oc1n_output_idle_state_t::low );}
    inline void oc1n_output_idle_state_high() { control_2.rmw( control_2_t::oc1n_output_idle_state_t::high );}
    inline auto oc1n_output_idle_state() const { return control_2.rd<control_2_t::oc1n_output_idle_state_t>();}

    inline void oc2_output_idle_state(const control_2_t::oc2_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc2_output_idle_state_low()  { control_2.rmw( control_2_t::oc2_output_idle_state_t::low );}
    inline void oc2_output_idle_state_high() { control_2.rmw( control_2_t::oc2_output_idle_state_t::high );}
    inline auto oc2_output_idle_state() const { return control_2.rd<control_2_t::oc2_output_idle_state_t>();}

    inline void oc2n_output_idle_state(const control_2_t::oc2n_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc2n_output_idle_state_low()  { control_2.rmw( control_2_t::oc2n_output_idle_state_t::low );}
    inline void oc2n_output_idle_state_high() { control_2.rmw( control_2_t::oc2n_output_idle_state_t::high );}
    inline auto oc2n_output_idle_state() const { return control_2.rd<control_2_t::oc2n_output_idle_state_t>();}

    inline void oc3_output_idle_state(const control_2_t::oc3_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc3_output_idle_state_low()  { control_2.rmw( control_2_t::oc3_output_idle_state_t::low );}
    inline void oc3_output_idle_state_high() { control_2.rmw( control_2_t::oc3_output_idle_state_t::high );}
    inline auto oc3_output_idle_state() const { return control_2.rd<control_2_t::oc3_output_idle_state_t>();}

    inline void oc3n_output_idle_state(const control_2_t::oc3n_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc3n_output_idle_state_low()  { control_2.rmw( control_2_t::oc3n_output_idle_state_t::low );}
    inline void oc3n_output_idle_state_high() { control_2.rmw( control_2_t::oc3n_output_idle_state_t::high );}
    inline auto oc3n_output_idle_state() const { return control_2.rd<control_2_t::oc3n_output_idle_state_t>();}

    inline void oc4_output_idle_state(const control_2_t::oc4_output_idle_state_t::enum_t val) {  control_2.rmw( val );}
    inline void oc4_output_idle_state_low()  { control_2.rmw( control_2_t::oc4_output_idle_state_t::low );}
    inline void oc4_output_idle_state_high() { control_2.rmw( control_2_t::oc4_output_idle_state_t::high );}
    inline auto oc4_output_idle_state() const { return control_2.rd<control_2_t::oc4_output_idle_state_t>();}

    struct slave_mode_control_t : public read_write_32_t
    {
      struct slave_mode_t  { enum enum_t { offset=0, mask=0b111, disable=0, encoder_mode_1, encoder_mode_2, encoder_mode_3, reset, gated, trigger, extrenal_clock }; } ;
      struct trigger_t  { enum enum_t { offset=4, mask=0b111, internal_trigger_0=0, internal_trigger_1, internal_trigger_2, internal_trigger_3, ti1_edge_detector, filtered_timer_input_1, filtered_timer_input_2, external_trigger_input}; } ;
      struct master_slave_mode_t  { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;
      struct external_trigger_filter_t  { enum enum_t { offset=8, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_6, fdts2_8, fdts4_6, fdts4_8, fdts8_6, fdts8_8, fdts16_5, fdts16_6, fdts16_8, fdts32_5, fdts32_6, fdts32_8}; } ;
      struct external_trigger_prescaler_t  { enum enum_t { offset=12, mask=0b11, div1=0, div2, div4, div8 }; } ;
      struct external_clock_t { enum enum_t { offset=14, mask=1, disable=0, enable }; } ;
      struct external_trigger_polarity_t  { enum enum_t { offset=15, mask=1, rise_edge=0, fall_edge }; } ;


    };

    inline void slave_mode(const slave_mode_control_t::slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::disable );}
    inline void slave_mode_encoder_mode_1() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_1 );}
    inline void slave_mode_encoder_mode_2() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_2 );}
    inline void slave_mode_encoder_mode_3() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::encoder_mode_3 );}
    inline void slave_mode_reset() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::reset );}
    inline void slave_mode_gated() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::gated );}
    inline void slave_mode_trigger() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::trigger );}
    inline void slave_mode_extrenal_clock() { slave_mode_control.rmw( slave_mode_control_t::slave_mode_t::extrenal_clock );}
    inline auto slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::slave_mode_t>();}

    inline void trigger(const slave_mode_control_t::trigger_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void trigger_internal_trigger_0() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_0 );}
    inline void trigger_internal_trigger_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_1 );}
    inline void trigger_internal_trigger_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_2 );}
    inline void trigger_internal_trigger_3() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::internal_trigger_3 );}
    inline void trigger_internal_ti1_edge_detector() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::ti1_edge_detector );}
    inline void trigger_internal_filtered_timer_input_1() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_1 );}
    inline void trigger_internal_filtered_timer_input_2() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::filtered_timer_input_2 );}
    inline void trigger_internal_external_trigger_input() { slave_mode_control.rmw( slave_mode_control_t::trigger_t::external_trigger_input );}
    inline auto trigger() const { return slave_mode_control.rd<slave_mode_control_t::trigger_t>();}

    inline void master_slave_mode(const slave_mode_control_t::master_slave_mode_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void master_slave_mode_disable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::disable );}
    inline void master_slave_mode_enable() { slave_mode_control.rmw( slave_mode_control_t::master_slave_mode_t::enable );}
    inline auto master_slave_mode() const { return slave_mode_control.rd<slave_mode_control_t::master_slave_mode_t>();}

    inline void external_trigger_filter(const slave_mode_control_t::external_trigger_filter_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_filter_disable() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::disable );}
    inline void external_trigger_filter_fck_n2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n2 );}
    inline void external_trigger_filter_fck_n4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n4 );}
    inline void external_trigger_filter_fck_n8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fck_n8 );}
    inline void external_trigger_filter_fdts2_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_6 );}
    inline void external_trigger_filter_fdts2_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts2_8 );}
    inline void external_trigger_filter_fdts4_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_6 );}
    inline void external_trigger_filter_fdts4_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts4_8 );}
    inline void external_trigger_filter_fdts8_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_6 );}
    inline void external_trigger_filter_fdts8_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts8_8 );}
    inline void external_trigger_filter_fdts16_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_5 );}
    inline void external_trigger_filter_fdts16_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_6 );}
    inline void external_trigger_filter_fdts16_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts16_8 );}
    inline void external_trigger_filter_fdts32_5() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_5 );}
    inline void external_trigger_filter_fdts32_6() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_6 );}
    inline void external_trigger_filter_fdts32_8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_filter_t::fdts32_8 );}
    inline auto external_trigger_filter() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_filter_t>();}

    inline void external_trigger_prescaler(const slave_mode_control_t::external_trigger_prescaler_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_prescaler_div1() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div1 );}
    inline void external_trigger_prescaler_div2() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div2 );}
    inline void external_trigger_prescaler_div4() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div4 );}
    inline void external_trigger_prescaler_div8() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_prescaler_t::div8 );}
    inline auto external_trigger_prescaler() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_prescaler_t>();}

    inline void external_clock(const slave_mode_control_t::external_clock_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_clock_disable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::disable );}
    inline void external_clock_enable() { slave_mode_control.rmw( slave_mode_control_t::external_clock_t::enable );}
    inline auto external_clock() const { return slave_mode_control.rd<slave_mode_control_t::external_clock_t>();}

    inline void external_trigger_polarity(const slave_mode_control_t::external_trigger_polarity_t::enum_t val) {  slave_mode_control.rmw( val );}
    inline void external_trigger_polarity_rise_edge() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_polarity_t::rise_edge );}
    inline void external_trigger_polarity_fall_edge() { slave_mode_control.rmw( slave_mode_control_t::external_trigger_polarity_t::fall_edge );}
    inline auto external_trigger_polarity() const { return slave_mode_control.rd<slave_mode_control_t::external_trigger_polarity_t>();}


    struct dma_interrupt_t : public read_write_32_t
    {
      struct update_interrupt_t    { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
      struct cc1_interrupt_t       { enum enum_t { offset=1, mask=1, disable=0, enable}; } ;
      struct cc2_interrupt_t       { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
      struct cc3_interrupt_t       { enum enum_t { offset=3, mask=1, disable=0, enable}; } ;
      struct cc4_interrupt_t       { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
      struct com_interrupt_t       { enum enum_t { offset=5, mask=1, disable=0, enable}; } ;
      struct trigger_interrupt_t   { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
      struct break_interrupt_t     { enum enum_t { offset=7, mask=1, disable=0, enable}; } ;
      struct update_dma_request_t  { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
      struct cc1_dma_request_t     { enum enum_t { offset=9, mask=1, disable=0, enable}; } ;
      struct cc2_dma_request_t     { enum enum_t { offset=10, mask=1, disable=0, enable}; } ;
      struct cc3_dma_request_t     { enum enum_t { offset=11, mask=1, disable=0, enable}; } ;
      struct cc4_dma_request_t     { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
      struct com_dma_request_t     { enum enum_t { offset=13, mask=1, disable=0, enable}; } ;
      struct trigger_dma_request_t { enum enum_t { offset=14, mask=1, disable=0, enable}; } ;
    } ;

    inline void update_interrupt(const dma_interrupt_t::update_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::enable );}
    inline void update_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::update_interrupt_t::disable );}
    inline auto update_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::update_interrupt_t>();}

    inline void cc1_interrupt(const dma_interrupt_t::cc1_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::enable );}
    inline void cc1_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_interrupt_t::disable );}
    inline auto cc1_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc1_interrupt_t>();}

    inline void cc2_interrupt(const dma_interrupt_t::cc2_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::enable );}
    inline void cc2_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_interrupt_t::disable );}
    inline auto cc2_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc2_interrupt_t>();}

    inline void cc3_interrupt(const dma_interrupt_t::cc3_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::enable );}
    inline void cc3_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_interrupt_t::disable );}
    inline auto cc3_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc3_interrupt_t>();}

    inline void cc4_interrupt(const dma_interrupt_t::cc4_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::enable );}
    inline void cc4_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_interrupt_t::disable );}
    inline auto cc4_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::cc4_interrupt_t>();}

    inline void com_interrupt(const dma_interrupt_t::com_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void com_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::com_interrupt_t::enable );}
    inline void com_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::com_interrupt_t::disable );}
    inline auto com_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::com_interrupt_t>();}

    inline void trigger_interrupt(const dma_interrupt_t::trigger_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::enable );}
    inline void trigger_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_interrupt_t::disable );}
    inline auto trigger_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::trigger_interrupt_t>();}

    inline void break_interrupt(const dma_interrupt_t::break_interrupt_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void break_interrupt_enable() { dma_interrupt.rmw( dma_interrupt_t::break_interrupt_t::enable );}
    inline void break_interrupt_disable() { dma_interrupt.rmw( dma_interrupt_t::break_interrupt_t::disable );}
    inline auto break_interrupt() const { return dma_interrupt.rd<dma_interrupt_t::break_interrupt_t>();}

    inline void update_dma_request(const dma_interrupt_t::update_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void update_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::enable );}
    inline void update_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::update_dma_request_t::disable );}
    inline auto update_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::update_dma_request_t>();}

    inline void cc1_dma_request(const dma_interrupt_t::cc1_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc1_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::enable );}
    inline void cc1_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc1_dma_request_t::disable );}
    inline auto cc1_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc1_dma_request_t>();}

    inline void cc2_dma_request(const dma_interrupt_t::cc2_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc2_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::enable );}
    inline void cc2_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc2_dma_request_t::disable );}
    inline auto cc2_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc2_dma_request_t>();}

    inline void cc3_dma_request(const dma_interrupt_t::cc3_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc3_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::enable );}
    inline void cc3_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc3_dma_request_t::disable );}
    inline auto cc3_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc3_dma_request_t>();}

    inline void cc4_dma_request(const dma_interrupt_t::cc4_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void cc4_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::enable );}
    inline void cc4_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::cc4_dma_request_t::disable );}
    inline auto cc4_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::cc4_dma_request_t>();}

    inline void com_dma_request(const dma_interrupt_t::com_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void com_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::com_dma_request_t::enable );}
    inline void com_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::com_dma_request_t::disable );}
    inline auto com_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::com_dma_request_t>();}

    inline void trigger_dma_request(const dma_interrupt_t::trigger_dma_request_t::enum_t val) {  dma_interrupt.rmw( val );}
    inline void trigger_dma_request_enable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::enable );}
    inline void trigger_dma_request_disable() { dma_interrupt.rmw( dma_interrupt_t::trigger_dma_request_t::disable );}
    inline auto trigger_dma_request() const { return dma_interrupt.rd<dma_interrupt_t::trigger_dma_request_t>();}

    struct status_t : public read_write_32_t
    {
      struct update_interrupt_flag_t   { enum enum_t { offset=0, mask=1, no_occured=0, occured}; } ;
      struct cc1_interrupt_flag_t { enum enum_t { offset=1, mask=1, no_occured=0, occured}; } ;
      struct cc2_interrupt_flag_t { enum enum_t { offset=2, mask=1, no_occured=0, occured}; } ;
      struct cc3_interrupt_flag_t { enum enum_t { offset=3, mask=1, no_occured=0, occured}; } ;
      struct cc4_interrupt_flag_t { enum enum_t { offset=4, mask=1, no_occured=0, occured}; } ;
      struct com_interrupt_flag_t { enum enum_t { offset=5, mask=1, no_occured=0, occured}; } ;
      struct trigger_interrupt_flag_t       { enum enum_t { offset=6, mask=1, no_occured=0, occured}; } ;
      struct break_interrupt_flag_t { enum enum_t { offset=7, mask=1, no_occured=0, occured}; } ;

      struct cc1_ovecapture_flag_t { enum enum_t { offset=9, mask=1, no_occured=0, occured}; } ;
      struct cc2_ovecapture_flag_t { enum enum_t { offset=10, mask=1, no_occured=0, occured}; } ;
      struct cc3_ovecapture_flag_t { enum enum_t { offset=11, mask=1, no_occured=0, occured}; } ;
      struct cc4_ovecapture_flag_t { enum enum_t { offset=12, mask=1, no_occured=0, occured}; } ;
    } ;

    inline void update_interrupt_flag_clear() { status.rmw( status_t::update_interrupt_flag_t::no_occured );}
    inline auto update_interrupt_flag() const { return status.rd<status_t::update_interrupt_flag_t>();}

    inline void cc1_interrupt_flag_clear() { status.rmw( status_t::cc1_interrupt_flag_t::no_occured );}
    inline auto cc1_interrupt_flag() const { return status.rd<status_t::cc1_interrupt_flag_t>();}

    inline void cc2_interrupt_flag_clear() { status.rmw( status_t::cc2_interrupt_flag_t::no_occured );}
    inline auto cc2_interrupt_flag() const { return status.rd<status_t::cc2_interrupt_flag_t>();}

    inline void cc3_interrupt_flag_clear() { status.rmw( status_t::cc3_interrupt_flag_t::no_occured );}
    inline auto cc3_interrupt_flag() const { return status.rd<status_t::cc3_interrupt_flag_t>();}

    inline void cc4_interrupt_flag_clear() { status.rmw( status_t::cc4_interrupt_flag_t::no_occured );}
    inline auto cc4_interrupt_flag() const { return status.rd<status_t::cc4_interrupt_flag_t>();}

    inline void com_interrupt_flag_clear() { status.rmw( status_t::com_interrupt_flag_t::no_occured );}
    inline auto com_interrupt_flag() const { return status.rd<status_t::com_interrupt_flag_t>();}

    inline void trigger_interrupt_flag_clear() { status.rmw( status_t::trigger_interrupt_flag_t::no_occured );}
    inline auto trigger_interrupt_flag() const { return status.rd<status_t::trigger_interrupt_flag_t>();}

    inline void break_interrupt_flag_clear() { status.rmw( status_t::break_interrupt_flag_t::no_occured );}
    inline auto break_interrupt_flag() const { return status.rd<status_t::break_interrupt_flag_t>();}

    inline void cc1_ovecapture_flag_clear() { status.rmw( status_t::cc1_ovecapture_flag_t::no_occured );}
    inline auto cc1_ovecapture_flag() const { return status.rd<status_t::cc1_ovecapture_flag_t>();}

    inline void cc2_ovecapture_flag_clear() { status.rmw( status_t::cc2_ovecapture_flag_t::no_occured );}
    inline auto cc2_ovecapture_flag() const { return status.rd<status_t::cc2_ovecapture_flag_t>();}

    inline void cc3_ovecapture_flag_clear() { status.rmw( status_t::cc3_ovecapture_flag_t::no_occured );}
    inline auto cc3_ovecapture_flag() const { return status.rd<status_t::cc3_ovecapture_flag_t>();}

    inline void cc4_ovecapture_flag_clear() { status.rmw( status_t::cc4_ovecapture_flag_t::no_occured );}
    inline auto cc4_ovecapture_flag() const { return status.rd<status_t::cc4_ovecapture_flag_t>();}

    struct event_generation_t : public read_write_32_t
    {
      struct  update_t   { enum enum_t { offset=0, mask=1, perform=1}; } ;
      struct  cc1_t      { enum enum_t { offset=1, mask=1, perform=1}; } ;
      struct  cc2_t      { enum enum_t { offset=2, mask=1, perform=1}; } ;
      struct  cc3_t      { enum enum_t { offset=3, mask=1, perform=1}; } ;
      struct  cc4_t      { enum enum_t { offset=4, mask=1, perform=1}; } ;
      struct  com_t      { enum enum_t { offset=5, mask=1, perform=1}; } ;
      struct  trigger_t  { enum enum_t { offset=6, mask=1, perform=1}; } ;
      struct  break_t    { enum enum_t { offset=7, mask=1, perform=1}; } ;
    } ;

    inline void update_event_generate() { event_generation.rmw( event_generation_t::update_t::perform );}
    inline void cc1_generate()          { event_generation.rmw( event_generation_t::cc1_t::perform );}
    inline void cc2_generate()          { event_generation.rmw( event_generation_t::cc2_t::perform );}
    inline void cc3_generate()          { event_generation.rmw( event_generation_t::cc3_t::perform );}
    inline void cc4_generate()          { event_generation.rmw( event_generation_t::cc4_t::perform );}
    inline void com_generate()          { event_generation.rmw( event_generation_t::com_t::perform );}
    inline void trigger_generate()      { event_generation.rmw( event_generation_t::trigger_t::perform );}
    inline void break_generate()        { event_generation.rmw( event_generation_t::break_t::perform );}

    struct cc_mode_1_t : public read_write_32_t
      {
        struct  cc1_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_1, inpit_capture_internal_trigger_2, inpit_capture_trc}; } ;

        struct  oc1_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc1_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc1_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc1_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic1_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic1_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc2_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_2, inpit_capture_internal_trigger_1, inpit_capture_trc}; } ;

        struct  oc2_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc2_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc2_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc2_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic2_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic2_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc1_selection(const cc_mode_1_t::cc1_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc1_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::output_compare );}
    inline void cc1_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc1_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc1_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc1_selection_t::inpit_capture_trc );}
    inline auto cc1_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc1_selection_t>();}

    inline void oc1_fast(const cc_mode_1_t::oc1_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::disable );}
    inline void oc1_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_fast_t::enable );}
    inline auto oc1_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc1_fast_t>();}

    inline void oc1_preload(const cc_mode_1_t::oc1_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::disable );}
    inline void oc1_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_preload_t::enable );}
    inline auto oc1_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc1_preload_t>();}

    inline void oc1_mode(const cc_mode_1_t::oc1_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::frozen );}
    inline void oc1_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::active );}
    inline void oc1_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::inactive );}
    inline void oc1_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::toggle );}
    inline void oc1_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_inactive );}
    inline void oc1_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::force_active );}
    inline void oc1_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm1 );}
    inline void oc1_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc1_mode_t::pwm2 );}
    inline auto oc1_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc1_mode_t>();}

    inline void oc1_clear(const cc_mode_1_t::oc1_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc1_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::disable );}
    inline void oc1_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc1_clear_t::enable );}
    inline auto oc1_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc1_clear_t>();}

    inline void ic1_precscaler(const cc_mode_1_t::ic1_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_first );}
    inline void ic1_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_second );}
    inline void ic1_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_thirh );}
    inline void ic1_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic1_precscaler_t::every_eighth );}
    inline auto ic1_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic1_precscaler_t>();}

    inline void ic1_filter(const cc_mode_1_t::ic1_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic1_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::disable );}
    inline void ic1_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n2 );}
    inline void ic1_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n4 );}
    inline void ic1_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fck_n8 );}
    inline void ic1_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n6 );}
    inline void ic1_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts2_n8 );}
    inline void ic1_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n6 );}
    inline void ic1_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts4_n8 );}
    inline void ic1_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n6 );}
    inline void ic1_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts8_n8 );}
    inline void ic1_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n5 );}
    inline void ic1_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n6 );}
    inline void ic1_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts16_n8 );}
    inline void ic1_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n5 );}
    inline void ic1_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n6 );}
    inline void ic1_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic1_filter::fdts32_n8 );}
    inline auto ic1_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic1_filter>();}


    inline void cc2_selection(const cc_mode_1_t::cc2_selection_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void cc2_selection_output_compare() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::output_compare );}
    inline void cc2_selection_inpit_capture_internal_trigger_2() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_2 );}
    inline void cc2_selection_inpit_capture_internal_trigger_1() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_internal_trigger_1 );}
    inline void cc2_selection_inpit_capture_trc() { cc_mode_1.rmw( cc_mode_1_t::cc2_selection_t::inpit_capture_trc );}
    inline auto cc2_selection() const { return cc_mode_1.rd<cc_mode_1_t::cc2_selection_t>();}

    inline void oc2_fast(const cc_mode_1_t::oc2_fast_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_fast_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::disable );}
    inline void oc2_fast_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_fast_t::enable );}
    inline auto oc2_fast() const { return cc_mode_1.rd<cc_mode_1_t::oc2_fast_t>();}

    inline void oc2_preload(const cc_mode_1_t::oc2_preload_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_preload_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::disable );}
    inline void oc2_preload_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_preload_t::enable );}
    inline auto oc2_preload() const { return cc_mode_1.rd<cc_mode_1_t::oc2_preload_t>();}

    inline void oc2_mode(const cc_mode_1_t::oc2_mode_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_mode_frozen() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::frozen );}
    inline void oc2_mode_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::active );}
    inline void oc2_mode_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::inactive );}
    inline void oc2_mode_toggle() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::toggle );}
    inline void oc2_mode_force_inactive() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_inactive );}
    inline void oc2_mode_force_active() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::force_active );}
    inline void oc2_mode_pwm1() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm1 );}
    inline void oc2_mode_pwm2() { cc_mode_1.rmw( cc_mode_1_t::oc2_mode_t::pwm2 );}
    inline auto oc2_mode() const { return cc_mode_1.rd<cc_mode_1_t::oc2_mode_t>();}

    inline void oc2_clear(const cc_mode_1_t::oc2_clear_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void oc2_clear_disable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::disable );}
    inline void oc2_clear_enable() { cc_mode_1.rmw( cc_mode_1_t::oc2_clear_t::enable );}
    inline auto oc2_clear() const { return cc_mode_1.rd<cc_mode_1_t::oc2_clear_t>();}

    inline void ic2_precscaler(const cc_mode_1_t::ic2_precscaler_t::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_precscaler_every_first()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_first );}
    inline void ic2_precscaler_every_second() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_second );}
    inline void ic2_precscaler_every_thirh()  { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_thirh );}
    inline void ic2_precscaler_every_eighth() { cc_mode_1.rmw( cc_mode_1_t::ic2_precscaler_t::every_eighth );}
    inline auto ic2_precscaler() const { return cc_mode_1.rd<cc_mode_1_t::ic2_precscaler_t>();}

    inline void ic2_filter(const cc_mode_1_t::ic2_filter::enum_t val) {  cc_mode_1.rmw( val );}
    inline void ic2_filter_disable()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::disable );}
    inline void ic2_filter_fck_n2()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n2 );}
    inline void ic2_filter_fck_n4()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n4 );}
    inline void ic2_filter_fck_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fck_n8 );}
    inline void ic2_filter_fdts2_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n6 );}
    inline void ic2_filter_fdts2_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts2_n8 );}
    inline void ic2_filter_fdts4_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n6 );}
    inline void ic2_filter_fdts4_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts4_n8 );}
    inline void ic2_filter_fdts8_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n6 );}
    inline void ic2_filter_fdts8_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts8_n8 );}
    inline void ic2_filter_fdts16_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n5 );}
    inline void ic2_filter_fdts16_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n6 );}
    inline void ic2_filter_fdts16_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts16_n8 );}
    inline void ic2_filter_fdts32_n5()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n5 );}
    inline void ic2_filter_fdts32_n6()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n6 );}
    inline void ic2_filter_fdts32_n8()  { cc_mode_1.rmw( cc_mode_1_t::ic2_filter::fdts32_n8 );}
    inline auto ic2_filter() const { return cc_mode_1.rd<cc_mode_1_t::ic2_filter>();}

    struct cc_mode_2_t : public read_write_32_t
      {
        struct  cc3_selection_t  { enum enum_t { offset=0, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_3, inpit_capture_internal_trigger_4, inpit_capture_trc}; } ;

        struct  oc3_fast_t       { enum enum_t { offset=2, mask=1, disable=0, enable }; } ;
        struct  oc3_preload_t    { enum enum_t { offset=3, mask=1, disable=0, enable }; } ;
        struct  oc3_mode_t       { enum enum_t { offset=4, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc3_clear_t      { enum enum_t { offset=7, mask=1, disable=0, enable }; } ;

        struct  ic3_precscaler_t { enum enum_t { offset=2, mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic3_filter       { enum enum_t { offset=4, mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;

        struct  cc4_selection_t  { enum enum_t { offset=8, mask=0b11, output_compare=0 , inpit_capture_internal_trigger_4, inpit_capture_internal_trigger_3, inpit_capture_trc}; } ;

        struct  oc4_fast_t       { enum enum_t { offset=10, mask=1, disable=0, enable }; } ;
        struct  oc4_preload_t    { enum enum_t { offset=11, mask=1, disable=0, enable }; } ;
        struct  oc4_mode_t       { enum enum_t { offset=12, mask=0b111, frozen=0, active, inactive, toggle, force_inactive, force_active, pwm1, pwm2  }; } ;
        struct  oc4_clear_t      { enum enum_t { offset=15, mask=1, disable=0, enable }; } ;

        struct  ic4_precscaler_t { enum enum_t { offset=10,mask=0b11, every_first=0, every_second, every_thirh, every_eighth }; } ;
        struct  ic4_filter       { enum enum_t { offset=12,mask=0b1111, disable=0, fck_n2, fck_n4, fck_n8, fdts2_n6, fdts2_n8, fdts4_n6, fdts4_n8, fdts8_n6, fdts8_n8, fdts16_n5, fdts16_n6, fdts16_n8, fdts32_n5, fdts32_n6, fdts32_n8 }; } ;
      } ;

    inline void cc3_selection(const cc_mode_2_t::cc3_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc3_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::output_compare );}
    inline void cc3_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc3_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc3_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc3_selection_t::inpit_capture_trc );}
    inline auto cc3_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc3_selection_t>();}

    inline void oc3_fast(const cc_mode_2_t::oc3_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::disable );}
    inline void oc3_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_fast_t::enable );}
    inline auto oc3_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc3_fast_t>();}

    inline void oc3_preload(const cc_mode_2_t::oc3_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::disable );}
    inline void oc3_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_preload_t::enable );}
    inline auto oc3_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc3_preload_t>();}

    inline void oc3_mode(const cc_mode_2_t::oc3_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::frozen );}
    inline void oc3_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::active );}
    inline void oc3_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::inactive );}
    inline void oc3_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::toggle );}
    inline void oc3_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_inactive );}
    inline void oc3_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::force_active );}
    inline void oc3_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm1 );}
    inline void oc3_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc3_mode_t::pwm2 );}
    inline auto oc3_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc3_mode_t>();}

    inline void oc3_clear(const cc_mode_2_t::oc3_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc3_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::disable );}
    inline void oc3_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc3_clear_t::enable );}
    inline auto oc3_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc3_clear_t>();}

    inline void ic3_precscaler(const cc_mode_2_t::ic3_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_first );}
    inline void ic3_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_second );}
    inline void ic3_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_thirh );}
    inline void ic3_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic3_precscaler_t::every_eighth );}
    inline auto ic3_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic3_precscaler_t>();}

    inline void ic3_filter(const cc_mode_2_t::ic3_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic3_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::disable );}
    inline void ic3_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n2 );}
    inline void ic3_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n4 );}
    inline void ic3_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fck_n8 );}
    inline void ic3_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n6 );}
    inline void ic3_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts2_n8 );}
    inline void ic3_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n6 );}
    inline void ic3_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts4_n8 );}
    inline void ic3_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n6 );}
    inline void ic3_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts8_n8 );}
    inline void ic3_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n5 );}
    inline void ic3_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n6 );}
    inline void ic3_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts16_n8 );}
    inline void ic3_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n5 );}
    inline void ic3_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n6 );}
    inline void ic3_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic3_filter::fdts32_n8 );}
    inline auto ic3_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic3_filter>();}


    inline void cc4_selection(const cc_mode_2_t::cc4_selection_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void cc4_selection_output_compare() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::output_compare );}
    inline void cc4_selection_inpit_capture_internal_trigger_4() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_4 );}
    inline void cc4_selection_inpit_capture_internal_trigger_3() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_internal_trigger_3 );}
    inline void cc4_selection_inpit_capture_trc() { cc_mode_2.rmw( cc_mode_2_t::cc4_selection_t::inpit_capture_trc );}
    inline auto cc4_selection() const { return cc_mode_2.rd<cc_mode_2_t::cc4_selection_t>();}

    inline void oc4_fast(const cc_mode_2_t::oc4_fast_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_fast_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::disable );}
    inline void oc4_fast_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_fast_t::enable );}
    inline auto oc4_fast() const { return cc_mode_2.rd<cc_mode_2_t::oc4_fast_t>();}

    inline void oc4_preload(const cc_mode_2_t::oc4_preload_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_preload_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::disable );}
    inline void oc4_preload_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_preload_t::enable );}
    inline auto oc4_preload() const { return cc_mode_2.rd<cc_mode_2_t::oc4_preload_t>();}

    inline void oc4_mode(const cc_mode_2_t::oc4_mode_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_mode_frozen() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::frozen );}
    inline void oc4_mode_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::active );}
    inline void oc4_mode_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::inactive );}
    inline void oc4_mode_toggle() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::toggle );}
    inline void oc4_mode_force_inactive() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_inactive );}
    inline void oc4_mode_force_active() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::force_active );}
    inline void oc4_mode_pwm1() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm1 );}
    inline void oc4_mode_pwm2() { cc_mode_2.rmw( cc_mode_2_t::oc4_mode_t::pwm2 );}
    inline auto oc4_mode() const { return cc_mode_2.rd<cc_mode_2_t::oc4_mode_t>();}

    inline void oc4_clear(const cc_mode_2_t::oc4_clear_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void oc4_clear_disable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::disable );}
    inline void oc4_clear_enable() { cc_mode_2.rmw( cc_mode_2_t::oc4_clear_t::enable );}
    inline auto oc4_clear() const { return cc_mode_2.rd<cc_mode_2_t::oc4_clear_t>();}

    inline void ic4_precscaler(const cc_mode_2_t::ic4_precscaler_t::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_precscaler_every_first()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_first );}
    inline void ic4_precscaler_every_second() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_second );}
    inline void ic4_precscaler_every_thirh()  { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_thirh );}
    inline void ic4_precscaler_every_eighth() { cc_mode_2.rmw( cc_mode_2_t::ic4_precscaler_t::every_eighth );}
    inline auto ic4_precscaler() const { return cc_mode_2.rd<cc_mode_2_t::ic4_precscaler_t>();}

    inline void ic4_filter(const cc_mode_2_t::ic4_filter::enum_t val) {  cc_mode_2.rmw( val );}
    inline void ic4_filter_disable()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::disable );}
    inline void ic4_filter_fck_n2()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n2 );}
    inline void ic4_filter_fck_n4()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n4 );}
    inline void ic4_filter_fck_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fck_n8 );}
    inline void ic4_filter_fdts2_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n6 );}
    inline void ic4_filter_fdts2_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts2_n8 );}
    inline void ic4_filter_fdts4_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n6 );}
    inline void ic4_filter_fdts4_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts4_n8 );}
    inline void ic4_filter_fdts8_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n6 );}
    inline void ic4_filter_fdts8_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts8_n8 );}
    inline void ic4_filter_fdts16_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n5 );}
    inline void ic4_filter_fdts16_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n6 );}
    inline void ic4_filter_fdts16_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts16_n8 );}
    inline void ic4_filter_fdts32_n5()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n5 );}
    inline void ic4_filter_fdts32_n6()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n6 );}
    inline void ic4_filter_fdts32_n8()  { cc_mode_2.rmw( cc_mode_2_t::ic4_filter::fdts32_n8 );}
    inline auto ic4_filter() const { return cc_mode_2.rd<cc_mode_2_t::ic4_filter>();}

    struct cc_enable_t : public read_write_32_t
      {
        struct  cc1_state_t     { enum enum_t { offset=0, mask=1, disable=0, enable}; } ;
        struct  oc1_polarity_t  { enum enum_t { offset=1, mask=1, high=0, low}; } ;
        struct  oc1n_state_t    { enum enum_t { offset=2, mask=1, disable=0, enable}; } ;
        struct  oc1n_polarity_t { enum enum_t { offset=3, mask=1, high=0, low}; } ;
        struct  ic1_polarity_t  { enum enum_t { offset=1, mask=0b111, rise=0b000 , fall=0b001, both=0b101  };} ;

        struct  cc2_state_t     { enum enum_t { offset=4, mask=1, disable=0, enable}; } ;
        struct  oc2_polarity_t  { enum enum_t { offset=5, mask=1, high=0, low}; } ;
        struct  oc2n_state_t    { enum enum_t { offset=6, mask=1, disable=0, enable}; } ;
        struct  oc2n_polarity_t { enum enum_t { offset=7, mask=1, high=0, low}; } ;
        struct  ic2_polarity_t  { enum enum_t { offset=5, mask=0b111, rise=0b000 , fall=0b001, both=0b101  };} ;

        struct  cc3_state_t     { enum enum_t { offset=8, mask=1, disable=0, enable}; } ;
        struct  oc3_polarity_t  { enum enum_t { offset=9, mask=1, high=0, low}; } ;
        struct  oc3n_state_t    { enum enum_t { offset=10, mask=1, disable=0, enable}; } ;
        struct  oc3n_polarity_t { enum enum_t { offset=11, mask=1, high=0, low}; } ;
        struct  ic3_polarity_t  { enum enum_t { offset=9, mask=0b111, rise=0b000 , fall=0b001, both=0b101  };} ;

        struct  cc4_state_t     { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
        struct  oc4_polarity_t  { enum enum_t { offset=13, mask=1, high=0, low}; } ;
        struct  ic4_polarity_t  { enum enum_t { offset=13, mask=1, rise=0 , fall };} ;
      } ;

    inline void cc1_state(const cc_enable_t::cc1_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc1_disable() { cc_enable.rmw( cc_enable_t::cc1_state_t::disable );}
    inline void cc1_enable() { cc_enable.rmw( cc_enable_t::cc1_state_t::enable );}
    inline auto cc1_state() const { return cc_enable.rd<cc_enable_t::cc1_state_t>();}

    // как output compare
    inline void oc1_polarity(const cc_enable_t::oc1_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1_polarity_high() { cc_enable.rmw( cc_enable_t::oc1_polarity_t::high );}
    inline void oc1_polarity_low() { cc_enable.rmw( cc_enable_t::oc1_polarity_t::low );}
    inline auto oc1_polarity() const { return cc_enable.rd<cc_enable_t::oc1_polarity_t>();}

    inline void oc1n_state(const cc_enable_t::oc1n_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1n_disable() { cc_enable.rmw( cc_enable_t::oc1n_state_t::disable );}
    inline void oc1n_enable() { cc_enable.rmw( cc_enable_t::oc1n_state_t::enable );}
    inline auto oc1n_state() const { return cc_enable.rd<cc_enable_t::oc1n_state_t>();}

    inline void oc1n_polarity(const cc_enable_t::oc1n_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc1n_polarity_high() { cc_enable.rmw( cc_enable_t::oc1n_polarity_t::high );}
    inline void oc1n_polarity_low() { cc_enable.rmw( cc_enable_t::oc1n_polarity_t::low );}
    inline auto oc1n_polarity() const { return cc_enable.rd<cc_enable_t::oc1n_polarity_t>();}

    inline void ic1_polarity(const cc_enable_t::ic1_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic1_polarity_rise() { cc_enable.rmw( cc_enable_t::ic1_polarity_t::rise );}
    inline void ic1_polarity_fall() { cc_enable.rmw( cc_enable_t::ic1_polarity_t::fall);}
    inline void ic1_polarity_both() { cc_enable.rmw( cc_enable_t::ic1_polarity_t::both );}
    inline auto ic1_polarity() const { return cc_enable.rd<cc_enable_t::ic1_polarity_t>();}

    inline void cc2_state(const cc_enable_t::cc2_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc2_disable() { cc_enable.rmw( cc_enable_t::cc2_state_t::disable );}
    inline void cc2_enable() { cc_enable.rmw( cc_enable_t::cc2_state_t::enable );}
    inline auto cc2_state() const { return cc_enable.rd<cc_enable_t::cc2_state_t>();}

    // как output compare
    inline void oc2_polarity(const cc_enable_t::oc2_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2_polarity_high() { cc_enable.rmw( cc_enable_t::oc2_polarity_t::high );}
    inline void oc2_polarity_low() { cc_enable.rmw( cc_enable_t::oc2_polarity_t::low );}
    inline auto oc2_polarity() const { return cc_enable.rd<cc_enable_t::oc2_polarity_t>();}

    inline void oc2n_state(const cc_enable_t::oc2n_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2n_disable() { cc_enable.rmw( cc_enable_t::oc2n_state_t::disable );}
    inline void oc2n_enable() { cc_enable.rmw( cc_enable_t::oc2n_state_t::enable );}
    inline auto oc2n_state() const { return cc_enable.rd<cc_enable_t::oc2n_state_t>();}

    inline void oc2n_polarity(const cc_enable_t::oc2n_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc2n_polarity_high() { cc_enable.rmw( cc_enable_t::oc2n_polarity_t::high );}
    inline void oc2n_polarity_low() { cc_enable.rmw( cc_enable_t::oc2n_polarity_t::low );}
    inline auto oc2n_polarity() const { return cc_enable.rd<cc_enable_t::oc2n_polarity_t>();}

    inline void ic2_polarity(const cc_enable_t::ic2_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic2_polarity_rise() { cc_enable.rmw( cc_enable_t::ic2_polarity_t::rise );}
    inline void ic2_polarity_fall() { cc_enable.rmw( cc_enable_t::ic2_polarity_t::fall );}
    inline void ic2_polarity_both() { cc_enable.rmw( cc_enable_t::ic2_polarity_t::both );}
    inline auto ic2_polarity() const { return cc_enable.rd<cc_enable_t::ic2_polarity_t>();}



    inline void cc3_state(const cc_enable_t::cc3_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc3_disable() { cc_enable.rmw( cc_enable_t::cc3_state_t::disable );}
    inline void cc3_enable() { cc_enable.rmw( cc_enable_t::cc3_state_t::enable );}
    inline auto cc3_state() const { return cc_enable.rd<cc_enable_t::cc3_state_t>();}

    // как output compare
    inline void oc3_polarity(const cc_enable_t::oc3_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc3_polarity_high() { cc_enable.rmw( cc_enable_t::oc3_polarity_t::high );}
    inline void oc3_polarity_low() { cc_enable.rmw( cc_enable_t::oc3_polarity_t::low );}
    inline auto oc3_polarity() const { return cc_enable.rd<cc_enable_t::oc3_polarity_t>();}

    inline void oc3n_state(const cc_enable_t::oc3n_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc3n_disable() { cc_enable.rmw( cc_enable_t::oc3n_state_t::disable );}
    inline void oc3n_enable() { cc_enable.rmw( cc_enable_t::oc3n_state_t::enable );}
    inline auto oc3n_state() const { return cc_enable.rd<cc_enable_t::oc3n_state_t>();}

    inline void oc3n_polarity(const cc_enable_t::oc3n_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc3n_polarity_high() { cc_enable.rmw( cc_enable_t::oc3n_polarity_t::high );}
    inline void oc3n_polarity_low() { cc_enable.rmw( cc_enable_t::oc3n_polarity_t::low );}
    inline auto oc3n_polarity() const { return cc_enable.rd<cc_enable_t::oc3n_polarity_t>();}

    inline void ic3_polarity(const cc_enable_t::ic3_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic3_polarity_rise() { cc_enable.rmw( cc_enable_t::ic3_polarity_t::rise );}
    inline void ic3_polarity_fall() { cc_enable.rmw( cc_enable_t::ic3_polarity_t::fall );}
    inline void ic3_polarity_both() { cc_enable.rmw( cc_enable_t::ic3_polarity_t::both );}
    inline auto ic3_polarity() const { return cc_enable.rd<cc_enable_t::ic3_polarity_t>();}

    inline void cc4_state(const cc_enable_t::cc4_state_t::enum_t val) {  cc_enable.rmw( val );}
    inline void cc4_disable() { cc_enable.rmw( cc_enable_t::cc4_state_t::disable );}
    inline void cc4_enable() { cc_enable.rmw( cc_enable_t::cc4_state_t::enable );}
    inline auto cc4_state() const { return cc_enable.rd<cc_enable_t::cc4_state_t>();}

    inline void oc4_polarity(const cc_enable_t::oc4_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void oc4_polarity_high() { cc_enable.rmw( cc_enable_t::oc4_polarity_t::high );}
    inline void oc4_polarity_low() { cc_enable.rmw( cc_enable_t::oc4_polarity_t::low );}
    inline auto oc4_polarity() const { return cc_enable.rd<cc_enable_t::oc4_polarity_t>();}

    inline void ic4_polarity(const cc_enable_t::ic4_polarity_t::enum_t val) {  cc_enable.rmw( val );}
    inline void ic4_polarity_rise() { cc_enable.rmw( cc_enable_t::ic4_polarity_t::rise );}
    inline void ic4_polarity_fall() { cc_enable.rmw( cc_enable_t::ic4_polarity_t::fall );}
    inline auto ic4_polarity() const { return cc_enable.rd<cc_enable_t::ic4_polarity_t>();}

    struct repetition_counter_t : public read_write_32_t
      {
        struct  val_t   { enum enum_t { offset=0, mask=0xff}; } ;
      };

    inline void repetition(const uint8_t val) {  repetition_counter.rmw( (repetition_counter_t::val_t::enum_t)(val - 1) );}
    inline auto repetition() const { return (uint8_t) repetition_counter.rd<repetition_counter_t::val_t>() + 1;}

    struct break_dead_time_t : public read_write_32_t
      {
        struct  dead_time_generator_t   { enum enum_t { offset=0, mask=0xff}; } ;
        struct  lock_t                  { enum enum_t { offset=8, mask=0b11, off=0, level_1, level_2, level_3}; } ;
        struct  off_state_selection_idle_t  { enum enum_t { offset=10, mask=1, low=0, high}; } ;
        struct  off_state_selection_run_t   { enum enum_t { offset=11, mask=1, low=0, high}; } ;
        struct  break_input_t   { enum enum_t { offset=12, mask=1, disable=0, enable}; } ;
        struct  break_polarity_t   { enum enum_t { offset=13, mask=1, low=0, high}; } ;
        struct  automatic_output_t   { enum enum_t { offset=14, mask=1, disable=0, enable}; } ;
        struct  main_output_t   { enum enum_t { offset=15, mask=1, disable=0, enable}; } ;
      };

    inline void dead_time_generator(const uint8_t val) {  break_dead_time.rmw( (break_dead_time_t::dead_time_generator_t::enum_t)val );}
    inline auto dead_time_generator() const { return (uint8_t) break_dead_time.rd<break_dead_time_t::dead_time_generator_t>();}

    inline void lock(const break_dead_time_t::lock_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void lock_off()     { break_dead_time.rmw( break_dead_time_t::lock_t::off );}
    inline void lock_level_1() { break_dead_time.rmw( break_dead_time_t::lock_t::level_1 );}
    inline void lock_level_2() { break_dead_time.rmw( break_dead_time_t::lock_t::level_2 );}
    inline void lock_level_3() { break_dead_time.rmw( break_dead_time_t::lock_t::level_3 );}
    inline auto lock() const { return break_dead_time.rd<break_dead_time_t::lock_t>();}

    inline void off_state_selection_idle(const break_dead_time_t::off_state_selection_idle_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void off_state_selection_idle_low()     { break_dead_time.rmw( break_dead_time_t::off_state_selection_idle_t::low );}
    inline void off_state_selection_idle_high() { break_dead_time.rmw( break_dead_time_t::off_state_selection_idle_t::high );}
    inline auto off_state_selection_idle() const { return break_dead_time.rd<break_dead_time_t::off_state_selection_idle_t>();}

    inline void off_state_selection_run(const break_dead_time_t::off_state_selection_run_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void off_state_selection_run_low()     { break_dead_time.rmw( break_dead_time_t::off_state_selection_run_t::low );}
    inline void off_state_selection_run_high() { break_dead_time.rmw( break_dead_time_t::off_state_selection_run_t::high );}
    inline auto off_state_selection_run() const { return break_dead_time.rd<break_dead_time_t::off_state_selection_run_t>();}

    inline void break_input(const break_dead_time_t::break_input_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void break_input_disable() { break_dead_time.rmw( break_dead_time_t::break_input_t::disable );}
    inline void break_input_enable()  { break_dead_time.rmw( break_dead_time_t::break_input_t::enable );}
    inline auto break_input() const { return break_dead_time.rd<break_dead_time_t::break_input_t>();}

    inline void break_polarity(const break_dead_time_t::break_polarity_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void break_polarity_low() { break_dead_time.rmw( break_dead_time_t::break_polarity_t::low );}
    inline void break_polarity_high()  { break_dead_time.rmw( break_dead_time_t::break_polarity_t::high );}
    inline auto break_polarity() const { return break_dead_time.rd<break_dead_time_t::break_polarity_t>();}

    inline void automatic_output(const break_dead_time_t::automatic_output_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void automatic_output_disable() { break_dead_time.rmw( break_dead_time_t::automatic_output_t::disable );}
    inline void automatic_output_enable()  { break_dead_time.rmw( break_dead_time_t::automatic_output_t::enable );}
    inline auto automatic_output() const { return break_dead_time.rd<break_dead_time_t::automatic_output_t>();}

    inline void main_output(const break_dead_time_t::main_output_t::enum_t val) {  break_dead_time.rmw( val );}
    inline void main_output_disable() { break_dead_time.rmw( break_dead_time_t::main_output_t::disable );}
    inline void main_output_enable()  { break_dead_time.rmw( break_dead_time_t::main_output_t::enable );}
    inline auto main_output() const { return break_dead_time.rd<break_dead_time_t::main_output_t>();}

    struct dma_control_t : public read_write_32_t
      {
        struct  dma_base_address_t   { enum enum_t { offset=0, mask=0b11111, }; } ; // TODO сделать символьное смещение
        struct  dma_burst_length_t   { enum enum_t { offset=8, mask=0b11111}; } ;
      } ;



    control_1_t               control_1 ;          //CR1;  /*!< TIM control register 1,              Address offset: 0x00 */
    control_2_t               control_2 ;          //CR2;  /*!< TIM control register 2,              Address offset: 0x04 */
    slave_mode_control_t      slave_mode_control;  //SMCR; /*!< TIM slave mode control register,     Address offset: 0x08 */
    dma_interrupt_t           dma_interrupt;       //DIER; /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
    status_t                  status;              //SR;   /*!< TIM status register,                 Address offset: 0x10 */
    event_generation_t        event_generation;    //EGR;  /*!< TIM event generation register,       Address offset: 0x14 */
    cc_mode_1_t  cc_mode_1 ;
    cc_mode_2_t  cc_mode_2 ;
    cc_enable_t  cc_enable ;

    volatile uint16_t counter ;
    const    uint16_t : 16 ;

    volatile uint16_t prescaler ;
    const    uint16_t : 16 ;

    volatile uint16_t auto_reload ;
    const    uint16_t : 16 ;

    repetition_counter_t repetition_counter ;

    volatile uint16_t cc1 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc2 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc3 ;
    const    uint16_t : 16 ;

    volatile uint16_t cc4 ;
    const    uint16_t : 16 ;

    break_dead_time_t break_dead_time ;

    dma_control_t dma_control ;
    volatile uint32_t dma_address ;

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case tim1_addr : rcc.tim1_enable(); break ;
               case tim8_addr : rcc.tim8_enable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case tim1_addr : rcc.tim1_disable(); break ;
               case tim8_addr : rcc.tim8_disable(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }

    inline void reset()
       {
          switch((uint32_t)this)
            {
               case tim1_addr : rcc.tim1_reset(); break ;
               case tim8_addr : rcc.tim8_reset(); break ;
               default: { std::__throw_invalid_argument("invalid TIM object") ; }
            }
       }
  } ;
}

using namespace stm32 ;

#endif /* __TIM_F4_F7++_H__ */
