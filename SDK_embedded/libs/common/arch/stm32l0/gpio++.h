/*
 * gpio++.h
 *
 *  Created on: 16 дке. 2018 г.
 *      Author: klen
 */

#ifndef __GPIO++_H__
#define __GPIO++_H__

#include "gpio_v2++.h"


namespace stm32l0
{
  inline bool clock_state()
   {
      switch((uint32_t)this)
        {
           case gpioa_addr : return rcc.gpioa_state();
           case gpiob_addr : return rcc.gpiob_state();
           case gpioc_addr : return rcc.gpioc_state();
           case gpiod_addr : return rcc.gpiod_state();
           case gpioe_addr : return rcc.gpioe_state();
           case gpioh_addr : return rcc.gpioh_state();
           default: { std::__throw_invalid_argument("invalid GPIO object") ; }
        }
   }

  struct gpio_t : public stm32::gpio_v2_t
  {
    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case gpioa_addr : rcc.gpioa_enable(); break ;
               case gpiob_addr : rcc.gpiob_enable(); break ;
               case gpioc_addr : rcc.gpioc_enable(); break ;
               case gpiod_addr : rcc.gpiod_enable(); break ;
               case gpioe_addr : rcc.gpioe_enable(); break ;
               case gpioh_addr : rcc.gpioh_enable(); break ;
               default: { std::__throw_invalid_argument("invalid GPIO object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case gpioa_addr : rcc.gpioa_disable(); break ;
               case gpiob_addr : rcc.gpiob_disable(); break ;
               case gpioc_addr : rcc.gpioc_disable(); break ;
               case gpiod_addr : rcc.gpiod_disable(); break ;
               case gpioe_addr : rcc.gpioe_disable(); break ;
               case gpioh_addr : rcc.gpioh_disable(); break ;
               default: {  std::__throw_invalid_argument("invalid GPIO object") ; }
            }
       }

    inline void reset()
      {
          switch((uint32_t)this)
            {
               case gpioa_addr : rcc.gpioa_reset(); break ;
               case gpiob_addr : rcc.gpiob_reset(); break ;
               case gpioc_addr : rcc.gpioc_reset(); break ;
               case gpiod_addr : rcc.gpiod_reset(); break ;
               case gpioe_addr : rcc.gpioe_reset(); break ;
               case gpioh_addr : rcc.gpioh_reset(); break ;
               default: {  std::__throw_invalid_argument("invalid GPIO object") ; }
            }
      };

    struct pin_config_t
      {
        gpio_t& port;
        const mode_t::enum_t mode;
        const output_type_t::enum_t output_type;
        const output_speed_t::enum_t output_speed ;
        const pull_t::enum_t pull ;
        const af_t::enum_t afio ;
        const pin_index_t pin;
        const bit_t bit;
        const output_t::enum_t state ;
      }  ;

    static inline void pin_configure(const pin_config_t& val, bool clock_enable=true)
      {
  	  if (clock_enable)
  	    val.port.clock_enable();
  	  val.port.pin(val.pin, val.mode );
  	  val.port.pin(val.pin, val.output_type);
  	  val.port.pin(val.pin, val.output_speed );
  	  val.port.pin(val.pin, val.pull );
  	  val.port.pin(val.pin, val.afio);
  	  val.port.pin(val.pin, val.state );
      }

    static inline void pin_default_state(const pin_config_t& val)
      {
  	  val.port.pin(val.pin, mode_t::enum_t::input );
  	  val.port.pin(val.pin, output_type_t::pull_push);
  	  val.port.pin(val.pin, output_speed_t::low );
  	  val.port.pin(val.pin, pull_t::no );
  	  val.port.pin(val.pin, af_t::af0);
  	  val.port.pin(val.pin, output_t::enum_t::reset );
      }

    static inline void pin_set  (const pin_config_t& val) { val.port.pin(val.pin, output_t::enum_t::set ); }
    static inline void pin_reset(const pin_config_t& val) { val.port.pin(val.pin, output_t::enum_t::reset ); }

};


struct gpioa_t : public gpio_t
{
        using gpio_t::pin ;
        template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
        template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }


        struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, uart2_rx=0, lptim1_in1, tim2_ch1, usart2_cts=4, tim2_etr, lpuart1_rx, comp1_out} ; } ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, evemt_out=0, lptim1_in2, tim2_ch2, i2c1_smba, usart2_rts_de, tim21_etr, lpuart1_tx} ; } ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, tim21_ch1=0, tim2_ch3=2, usart2_tx=4, lpuatr1_tx=6, comp2_out} ; } ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ; } ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ; } ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ; } ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ; } ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ; } ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ; } ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ; } ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ; } ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ; } ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ; } ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ; } ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ; } ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ; } ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline void pin0_af_uart2_rx()  { af.rmw( af_t::pin0_t::enum_t::uart2_rx ); }
        inline void pin0_af_lptim1_in1(){ af.rmw( af_t::pin0_t::enum_t::lptim1_in1 ); }
        inline void pin0_af_tim2_ch1()  { af.rmw( af_t::pin0_t::enum_t::tim2_ch1 ); }
        inline void pin0_af_usart2_cts(){ af.rmw( af_t::pin0_t::enum_t::usart2_cts ); }
        inline void pin0_af_tim2_etr()  { af.rmw( af_t::pin0_t::enum_t::tim2_etr ); }
        inline void pin0_af_lpuart1_rx(){ af.rmw( af_t::pin0_t::enum_t::lpuart1_rx ); }
        inline void pin0_af_comp1_out() { af.rmw( af_t::pin0_t::enum_t::comp1_out ); }
        inline auto pin0_af()  const  { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin1_af()  const  { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin2_af()  const  { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin3_af()  const  { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin4_af()  const  { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin5_af()  const  { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin6_af_af()  const  { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin7_af() const   { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin8_af()  const  { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin9_af()  const  { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin10_af() const   { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin11_af()  const  { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin12_af()  const  { return af.rd<af_t::pin12_t>() ; }


        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin13_af()  const  { return af.rd<af_t::pin13_t>() ; }


        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin14_af()  const  { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin15_af()  const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() const {  rcc.gpioa_enable() ; }
        inline void clock_disable() const  {  rcc.gpioa_disable() ; }
        inline void reset() const {  rcc.gpioa_reset() ; }

} ;


struct gpiob_t : public gpio_t
{
        using gpio_t::pin ;
        template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
        template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

        struct af_t
           {
             struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, } ;} ;
             struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, } ;} ;
             struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, } ;} ;
             struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ;} ;
             struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ;} ;
             struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ;} ;
             struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ;} ;
             struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ;} ;
             struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ;} ;
             struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ;} ;
             struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ;} ;
             struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ;} ;
             struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ;} ;
             struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ;} ;
             struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ;} ;
             struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ;} ;
           };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin2()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin3()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin13_af() const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin14_af() const  { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin15_af() const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiob_enable() ; }
        inline void clock_disable() {  rcc.gpiob_disable() ; }
        inline void reset() {  rcc.gpiob_reset() ; }
} ;


struct gpioc_t : public gpio_t
{
         using gpio_t::pin ;
         template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
         template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

         struct af_t
            {
              struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, } ;} ;
              struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, } ;} ;
              struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, } ;} ;
              struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ;} ;
              struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ;} ;
              struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ;} ;
              struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ;} ;
              struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ;} ;
              struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ;} ;
              struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ;} ;
              struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ;} ;
              struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ;} ;
              struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ;} ;
              struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ;} ;
              struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ;} ;
              struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ;} ;
            };

         inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

         inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

         inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin2()const { return af.rd<af_t::pin2_t>() ; }

         inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin3()const { return af.rd<af_t::pin3_t>() ; }

         inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

         inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

         inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

         inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

         inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

         inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

         inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

         inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

         inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

         inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin13_af() const { return af.rd<af_t::pin13_t>() ; }

         inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin14_af() const  { return af.rd<af_t::pin14_t>() ; }

         inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
         inline auto pin15_af() const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpioc_enable() ; }
        inline void clock_disable() {  rcc.gpioc_disable() ; }
        inline void reset() {  rcc.gpioc_reset() ; }
};


struct gpiod_t : public gpio_t
{
          using gpio_t::pin ;
          template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
          template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

          struct af_t
             {
               struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, } ;} ;
               struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, } ;} ;
               struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, } ;} ;
               struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ;} ;
               struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ;} ;
               struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ;} ;
               struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ;} ;
               struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ;} ;
               struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ;} ;
               struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ;} ;
               struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ;} ;
               struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ;} ;
               struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ;} ;
               struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ;} ;
               struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ;} ;
               struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ;} ;
             };

          inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

          inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

          inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin2()const { return af.rd<af_t::pin2_t>() ; }

          inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin3()const { return af.rd<af_t::pin3_t>() ; }

          inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

          inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

          inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

          inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

          inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

          inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

          inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

          inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

          inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

          inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin13_af() const { return af.rd<af_t::pin13_t>() ; }

          inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin14_af() const  { return af.rd<af_t::pin14_t>() ; }

          inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
          inline auto pin15_af() const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable() {  rcc.gpiod_enable() ; }
        inline void clock_disable() {  rcc.gpiod_disable() ; }
        inline void reset() {  rcc.gpiod_reset() ; }
} ;

struct gpioe_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
          {
            struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, } ;} ;
            struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, } ;} ;
            struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, } ;} ;
            struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ;} ;
            struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ;} ;
            struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ;} ;
            struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ;} ;
            struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ;} ;
            struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ;} ;
            struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ;} ;
            struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ;} ;
            struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ;} ;
            struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ;} ;
            struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ;} ;
            struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ;} ;
            struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ;} ;
          };

       inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

       inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

       inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin2()const { return af.rd<af_t::pin2_t>() ; }

       inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin3()const { return af.rd<af_t::pin3_t>() ; }

       inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

       inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

       inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

       inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

       inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

       inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

       inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

       inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

       inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

       inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin13_af() const { return af.rd<af_t::pin13_t>() ; }

       inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin14_af() const  { return af.rd<af_t::pin14_t>() ; }

       inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
       inline auto pin15_af() const  { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpioe_enable() ; }
        inline void clock_disable() {  rcc.gpioe_disable() ; }
        inline void clock_reset()   {  rcc.gpioe_reset() ; }
};

struct gpioh_t : public gpio_t
{

       using gpio_t::pin ;
       template<typename U, typename... Args> inline void pin(const U arg, const Args... args) { pin(arg); pin(args...); }
       template<typename U>                   inline void pin(const U arg)                     { pin(arg) ; }

       struct af_t
          {
            struct pin0_t  { enum enum_t:uint64_t { offset=0,  mask=0b1111, } ;} ;
            struct pin1_t  { enum enum_t:uint64_t { offset=4,  mask=0b1111, } ;} ;
            struct pin2_t  { enum enum_t:uint64_t { offset=8,  mask=0b1111, } ;} ;
            struct pin3_t  { enum enum_t:uint64_t { offset=12, mask=0b1111, } ;} ;
            struct pin4_t  { enum enum_t:uint64_t { offset=16, mask=0b1111, } ;} ;
            struct pin5_t  { enum enum_t:uint64_t { offset=20, mask=0b1111, } ;} ;
            struct pin6_t  { enum enum_t:uint64_t { offset=24, mask=0b1111, } ;} ;
            struct pin7_t  { enum enum_t:uint64_t { offset=28, mask=0b1111, } ;} ;
            struct pin8_t  { enum enum_t:uint64_t { offset=32, mask=0b1111, } ;} ;
            struct pin9_t  { enum enum_t:uint64_t { offset=36, mask=0b1111, } ;} ;
            struct pin10_t { enum enum_t:uint64_t { offset=40, mask=0b1111, } ;} ;
            struct pin11_t { enum enum_t:uint64_t { offset=44, mask=0b1111, } ;} ;
            struct pin12_t { enum enum_t:uint64_t { offset=48, mask=0b1111, } ;} ;
            struct pin13_t { enum enum_t:uint64_t { offset=52, mask=0b1111, } ;} ;
            struct pin14_t { enum enum_t:uint64_t { offset=56, mask=0b1111, } ;} ;
            struct pin15_t { enum enum_t:uint64_t { offset=60, mask=0b1111, } ;} ;
          };

        inline void pin(const af_t::pin0_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin0_af()const { return af.rd<af_t::pin0_t>() ; }

        inline void pin(const af_t::pin1_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin1_af()const { return af.rd<af_t::pin1_t>() ; }

        inline void pin(const af_t::pin2_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin2_af()const { return af.rd<af_t::pin2_t>() ; }

        inline void pin(const af_t::pin3_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin3_af()const { return af.rd<af_t::pin3_t>() ; }

        inline void pin(const af_t::pin4_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin4_af()const { return af.rd<af_t::pin4_t>() ; }

        inline void pin(const af_t::pin5_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin5_af()const { return af.rd<af_t::pin5_t>() ; }

        inline void pin(const af_t::pin6_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin6_af()const { return af.rd<af_t::pin6_t>() ; }

        inline void pin(const af_t::pin7_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin7_af()const { return af.rd<af_t::pin7_t>() ; }

        inline void pin(const af_t::pin8_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin8_af()const { return af.rd<af_t::pin8_t>() ; }

        inline void pin(const af_t::pin9_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin9_af()const { return af.rd<af_t::pin9_t>() ; }

        inline void pin(const af_t::pin10_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin10_af()const { return af.rd<af_t::pin10_t>() ; }

        inline void pin(const af_t::pin11_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin11_af()const { return af.rd<af_t::pin11_t>() ; }

        inline void pin(const af_t::pin12_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin12_af()const { return af.rd<af_t::pin12_t>() ; }

        inline void pin(const af_t::pin13_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin13_af()const { return af.rd<af_t::pin13_t>() ; }

        inline void pin(const af_t::pin14_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin14_af()const { return af.rd<af_t::pin14_t>() ; }

        inline void pin(const af_t::pin15_t::enum_t val) { af.rmw( val ) ; }
        inline auto pin15_af()const { return af.rd<af_t::pin15_t>() ; }

        inline void clock_enable()  {  rcc.gpioh_enable() ; }
        inline void clock_disable() {  rcc.gpioh_disable() ; }
        inline void clock_reset()   {  rcc.gpioh_reset() ; }
} ;

static gpioa_t& gpioa = *((gpioa_t*) gpioa_addr);
static gpiob_t& gpiob = *((gpiob_t*) gpiob_addr);
static gpioc_t& gpioc = *((gpioc_t*) gpioc_addr);
static gpiod_t& gpiod = *((gpiod_t*) gpiod_addr);
static gpioe_t& gpioe = *((gpioe_t*) gpioe_addr);
static gpioh_t& gpioh = *((gpioh_t*) gpioh_addr);


}

using namespace stm32l0 ;

#endif /* __GPIO++_H__ */
