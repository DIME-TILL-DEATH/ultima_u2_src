/*
 * dma++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __DMA_F4_F7++_H__
#define __DMA_F4_F7++_H__


#include "types++.h"

namespace stm32
{

  struct dma_t
  {
    struct low_interrupt_status_t : public read_write_32_t
    {
      struct stream0_fifo_error_interrupt_t         { enum enum_t  { offset=0, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream0_direct_mode_error_interrupt_t  { enum enum_t  { offset=2, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream0_transfer_error_interrupt_t     { enum enum_t  { offset=3, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream0_half_transfer_interrupt_t      { enum enum_t  { offset=4, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream0_transfer_complete_interrupt_t  { enum enum_t  { offset=5, mask=1, no_occurred=0 , occurred} ; } ;

      struct stream1_fifo_error_interrupt_t         { enum enum_t  { offset=6, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream1_direct_mode_error_interrupt_t  { enum enum_t  { offset=8, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream1_transfer_error_interrupt_t     { enum enum_t  { offset=9, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream1_half_transfer_interrupt_t      { enum enum_t  { offset=10, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream1_transfer_complete_interrupt_t  { enum enum_t  { offset=11, mask=1,no_occurred=0 , occurred} ; } ;

      struct stream2_fifo_error_interrupt_t         { enum enum_t  { offset=16, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream2_direct_mode_error_interrupt_t  { enum enum_t  { offset=18, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream2_transfer_error_interrupt_t     { enum enum_t  { offset=19, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream2_half_transfer_interrupt_t      { enum enum_t  { offset=20, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream2_transfer_complete_interrupt_t  { enum enum_t  { offset=21, mask=1,no_occurred=0 , occurred} ; } ;

      struct stream3_fifo_error_interrupt_t         { enum enum_t  { offset=22, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream3_direct_mode_error_interrupt_t  { enum enum_t  { offset=24, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream3_transfer_error_interrupt_t     { enum enum_t  { offset=25, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream3_half_transfer_interrupt_t      { enum enum_t  { offset=26, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream3_transfer_complete_interrupt_t  { enum enum_t  { offset=27, mask=1,no_occurred=0 , occurred} ; } ;
    } ;

    inline auto stream0_fifo_error_interrupt_flag       () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream0_fifo_error_interrupt_t> ();}
    inline auto stream0_direct_mode_error_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream0_direct_mode_error_interrupt_t> ();}
    inline auto stream0_transfer_error_interrupt_flag   () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream0_transfer_error_interrupt_t> ();}
    inline auto stream0_half_transfer_interrupt_flag    () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream0_half_transfer_interrupt_t> ();}
    inline auto stream0_transfer_complete_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream0_transfer_complete_interrupt_t> ();}

    inline auto stream1_fifo_error_interrupt_flag       () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream1_fifo_error_interrupt_t> ();}
    inline auto stream1_direct_mode_error_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream1_direct_mode_error_interrupt_t> ();}
    inline auto stream1_transfer_error_interrupt_flag   () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream1_transfer_error_interrupt_t> ();}
    inline auto stream1_half_transfer_interrupt_flag    () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream1_half_transfer_interrupt_t> ();}
    inline auto stream1_transfer_complete_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream1_transfer_complete_interrupt_t> ();}

    inline auto stream2_fifo_error_interrupt_flag       () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream2_fifo_error_interrupt_t> ();}
    inline auto stream2_direct_mode_error_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream2_direct_mode_error_interrupt_t> ();}
    inline auto stream2_transfer_error_interrupt_flag   () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream2_transfer_error_interrupt_t> ();}
    inline auto stream2_half_transfer_interrupt_flag    () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream2_half_transfer_interrupt_t> ();}
    inline auto stream2_transfer_complete_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream2_transfer_complete_interrupt_t> ();}

    inline auto stream3_fifo_error_interrupt_flag       () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream3_fifo_error_interrupt_t> ();}
    inline auto stream3_direct_mode_error_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream3_direct_mode_error_interrupt_t> ();}
    inline auto stream3_transfer_error_interrupt_flag   () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream3_transfer_error_interrupt_t> ();}
    inline auto stream3_half_transfer_interrupt_flag    () const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream3_half_transfer_interrupt_t> ();}
    inline auto stream3_transfer_complete_interrupt_flag() const  {   return low_interrupt_status.rd<low_interrupt_status_t::stream3_transfer_complete_interrupt_t> ();}

    struct high_interrupt_status_t : public read_write_32_t
    {
      struct stream4_fifo_error_interrupt_t         { enum enum_t  { offset=0, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream4_direct_mode_error_interrupt_t  { enum enum_t  { offset=2, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream4_transfer_error_interrupt_t     { enum enum_t  { offset=3, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream4_half_transfer_interrupt_t      { enum enum_t  { offset=4, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream4_transfer_complete_interrupt_t  { enum enum_t  { offset=5, mask=1, no_occurred=0 , occurred} ; } ;

      struct stream5_fifo_error_interrupt_t         { enum enum_t  { offset=6, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream5_direct_mode_error_interrupt_t  { enum enum_t  { offset=8, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream5_transfer_error_interrupt_t     { enum enum_t  { offset=9, mask=1, no_occurred=0 , occurred} ; } ;
      struct stream5_half_transfer_interrupt_t      { enum enum_t  { offset=10, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream5_transfer_complete_interrupt_t  { enum enum_t  { offset=11, mask=1,no_occurred=0 , occurred} ; } ;

      struct stream6_fifo_error_interrupt_t         { enum enum_t  { offset=16, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream6_direct_mode_error_interrupt_t  { enum enum_t  { offset=18, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream6_transfer_error_interrupt_t     { enum enum_t  { offset=19, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream6_half_transfer_interrupt_t      { enum enum_t  { offset=20, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream6_transfer_complete_interrupt_t  { enum enum_t  { offset=21, mask=1,no_occurred=0 , occurred} ; } ;

      struct stream7_fifo_error_interrupt_t         { enum enum_t  { offset=22, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream7_direct_mode_error_interrupt_t  { enum enum_t  { offset=24, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream7_transfer_error_interrupt_t     { enum enum_t  { offset=25, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream7_half_transfer_interrupt_t      { enum enum_t  { offset=26, mask=1,no_occurred=0 , occurred} ; } ;
      struct stream7_transfer_complete_interrupt_t  { enum enum_t  { offset=27, mask=1,no_occurred=0 , occurred} ; } ;
    } ;

    inline auto stream4_fifo_error_interrupt_flag       () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream4_fifo_error_interrupt_t> ();}
    inline auto stream4_direct_mode_error_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream4_direct_mode_error_interrupt_t> ();}
    inline auto stream4_transfer_error_interrupt_flag   () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream4_transfer_error_interrupt_t> ();}
    inline auto stream4_half_transfer_interrupt_flag    () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream4_half_transfer_interrupt_t> ();}
    inline auto stream4_transfer_complete_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream4_transfer_complete_interrupt_t> ();}

    inline auto stream5_fifo_error_interrupt_flag       () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream5_fifo_error_interrupt_t> ();}
    inline auto stream5_direct_mode_error_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream5_direct_mode_error_interrupt_t> ();}
    inline auto stream5_transfer_error_interrupt_flag   () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream5_transfer_error_interrupt_t> ();}
    inline auto stream5_half_transfer_interrupt_flag    () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream5_half_transfer_interrupt_t> ();}
    inline auto stream5_transfer_complete_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream5_transfer_complete_interrupt_t> ();}

    inline auto stream6_fifo_error_interrupt_flag       () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream6_fifo_error_interrupt_t> ();}
    inline auto stream6_direct_mode_error_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream6_direct_mode_error_interrupt_t> ();}
    inline auto stream6_transfer_error_interrupt_flag   () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream6_transfer_error_interrupt_t> ();}
    inline auto stream6_half_transfer_interrupt_flag    () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream6_half_transfer_interrupt_t> ();}
    inline auto stream6_transfer_complete_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream6_transfer_complete_interrupt_t> ();}

    inline auto stream7_fifo_error_interrupt_flag       () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream7_fifo_error_interrupt_t> ();}
    inline auto stream7_direct_mode_error_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream7_direct_mode_error_interrupt_t> ();}
    inline auto stream7_transfer_error_interrupt_flag   () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream7_transfer_error_interrupt_t> ();}
    inline auto stream7_half_transfer_interrupt_flag    () const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream7_half_transfer_interrupt_t> ();}
    inline auto stream7_transfer_complete_interrupt_flag() const  {   return high_interrupt_status.rd<high_interrupt_status_t::stream7_transfer_complete_interrupt_t> ();}






    struct low_interrupt_clear_t : public read_write_32_t
    {
      struct stream0_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=0, mask=1, clear=1} ; } ;
      struct stream0_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=2, mask=1, clear=1} ; } ;
      struct stream0_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=3, mask=1, clear=1} ; } ;
      struct stream0_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=4, mask=1, clear=1} ; } ;
      struct stream0_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=5, mask=1, clear=1} ; } ;

      struct stream1_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=6, mask=1, clear=1} ; } ;
      struct stream1_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=8, mask=1, clear=1} ; } ;
      struct stream1_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=9, mask=1, clear=1} ; } ;
      struct stream1_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=10,mask=1, clear=1} ; } ;
      struct stream1_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=11,mask=1, clear=1} ; } ;

      struct stream2_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=16,mask=1, clear=1} ; } ;
      struct stream2_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=18,mask=1, clear=1} ; } ;
      struct stream2_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=19,mask=1, clear=1} ; } ;
      struct stream2_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=20,mask=1, clear=1} ; } ;
      struct stream2_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=21,mask=1, clear=1} ; } ;

      struct stream3_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=22,mask=1, clear=1} ; } ;
      struct stream3_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=24,mask=1, clear=1} ; } ;
      struct stream3_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=25,mask=1, clear=1} ; } ;
      struct stream3_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=26,mask=1, clear=1} ; } ;
      struct stream3_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=27,mask=1, clear=1} ; } ;
    } ;

    inline void stream0_fifo_error_interrupt_clear       () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream0_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream0_direct_mode_error_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream0_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream0_transfer_error_interrupt_clear   () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream0_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream0_half_transfer_interrupt_clear    () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream0_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream0_transfer_complete_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream0_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream1_fifo_error_interrupt_clear       () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream1_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream1_direct_mode_error_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream1_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream1_transfer_error_interrupt_clear   () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream1_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream1_half_transfer_interrupt_clear    () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream1_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream1_transfer_complete_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream1_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream2_fifo_error_interrupt_clear       () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream2_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream2_direct_mode_error_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream2_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream2_transfer_error_interrupt_clear   () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream2_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream2_half_transfer_interrupt_clear    () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream2_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream2_transfer_complete_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream2_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream3_fifo_error_interrupt_clear       () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream3_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream3_direct_mode_error_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream3_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream3_transfer_error_interrupt_clear   () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream3_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream3_half_transfer_interrupt_clear    () {  low_interrupt_clear.wr(low_interrupt_clear_t::stream3_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream3_transfer_complete_interrupt_clear() {  low_interrupt_clear.wr(low_interrupt_clear_t::stream3_transfer_complete_interrupt_flag_clear_t::clear) ;}

    struct high_interrupt_clear_t : public read_write_32_t
    {
      struct stream4_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=0, mask=1, clear=1} ; } ;
      struct stream4_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=2, mask=1, clear=1} ; } ;
      struct stream4_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=3, mask=1, clear=1} ; } ;
      struct stream4_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=4, mask=1, clear=1} ; } ;
      struct stream4_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=5, mask=1, clear=1} ; } ;

      struct stream5_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=6, mask=1, clear=1} ; } ;
      struct stream5_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=8, mask=1, clear=1} ; } ;
      struct stream5_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=9, mask=1, clear=1} ; } ;
      struct stream5_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=10,mask=1, clear=1} ; } ;
      struct stream5_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=11,mask=1, clear=1} ; } ;

      struct stream6_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=16,mask=1, clear=1} ; } ;
      struct stream6_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=18,mask=1, clear=1} ; } ;
      struct stream6_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=19,mask=1, clear=1} ; } ;
      struct stream6_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=20,mask=1, clear=1} ; } ;
      struct stream6_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=21,mask=1, clear=1} ; } ;

      struct stream7_fifo_error_interrupt_flag_clear_t         { enum enum_t  { offset=22,mask=1, clear=1} ; } ;
      struct stream7_direct_mode_error_interrupt_flag_clear_t  { enum enum_t  { offset=24,mask=1, clear=1} ; } ;
      struct stream7_transfer_error_interrupt_flag_clear_t     { enum enum_t  { offset=25,mask=1, clear=1} ; } ;
      struct stream7_half_transfer_interrupt_flag_clear_t      { enum enum_t  { offset=26,mask=1, clear=1} ; } ;
      struct stream7_transfer_complete_interrupt_flag_clear_t  { enum enum_t  { offset=27,mask=1, clear=1} ; } ;
    } ;

    inline void stream4_fifo_error_interrupt_clear       () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream4_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream4_direct_mode_error_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream4_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream4_transfer_error_interrupt_clear   () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream4_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream4_half_transfer_interrupt_clear    () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream4_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream4_transfer_complete_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream4_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream5_fifo_error_interrupt_clear       () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream5_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream5_direct_mode_error_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream5_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream5_transfer_error_interrupt_clear   () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream5_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream5_half_transfer_interrupt_clear    () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream5_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream5_transfer_complete_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream5_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream6_fifo_error_interrupt_clear       () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream6_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream6_direct_mode_error_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream6_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream6_transfer_error_interrupt_clear   () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream6_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream6_half_transfer_interrupt_clear    () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream6_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream6_transfer_complete_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream6_transfer_complete_interrupt_flag_clear_t::clear) ;}

    inline void stream7_fifo_error_interrupt_clear       () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream7_fifo_error_interrupt_flag_clear_t::clear);}
    inline void stream7_direct_mode_error_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream7_direct_mode_error_interrupt_flag_clear_t::clear) ;}
    inline void stream7_transfer_error_interrupt_clear   () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream7_transfer_error_interrupt_flag_clear_t::clear) ;}
    inline void stream7_half_transfer_interrupt_clear    () {  high_interrupt_clear.wr(high_interrupt_clear_t::stream7_half_transfer_interrupt_flag_clear_t::clear) ;}
    inline void stream7_transfer_complete_interrupt_clear() {  high_interrupt_clear.wr(high_interrupt_clear_t::stream7_transfer_complete_interrupt_flag_clear_t::clear) ;}



    low_interrupt_status_t  low_interrupt_status ; // LISR;   /*!< DMA low interrupt status register,      Address offset: 0x00 */
    high_interrupt_status_t high_interrupt_status; // HISR;   /*!< DMA high interrupt status register,     Address offset: 0x04 */
    low_interrupt_clear_t   low_interrupt_clear  ; // LIFCR;  /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
    high_interrupt_clear_t  high_interrupt_clear ; // HIFCR;  /*!< DMA high interrupt flag clear register, Address offset: 0x0C */

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case dma1_addr : rcc.dma1_enable(); break ;
               case dma2_addr : rcc.dma2_enable(); break ;
               default: { std::__throw_invalid_argument("invalid DMA object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case dma1_addr : rcc.dma1_disable(); break ;
               case dma2_addr : rcc.dma2_disable(); break ;
               default: {  std::__throw_invalid_argument("invalid DMA object") ; }
            }
       }
    inline void reset()
       {
          switch((uint32_t)this)
            {
               case dma1_addr : rcc.dma1_reset(); break ;
               case dma2_addr : rcc.dma2_reset(); break ;
               default: {  std::__throw_invalid_argument("invalid DMA object") ; }
            }
       };

  } ;

  struct dma1_t : public dma_t
  {
    inline void clock_enable() { rcc.dma1_enable() ; }
    inline void clock_disable() { rcc.dma1_disable() ; }
    inline void reset() { rcc.dma1_reset() ; }
  } ;

  struct dma2_t : public dma_t
  {
    inline void clock_enable() { rcc.dma2_enable() ; }
    inline void clock_disable() { rcc.dma2_disable() ; }
    inline void reset() { rcc.dma2_reset() ; }
  } ;

  static dma1_t& dma1 =   *((dma1_t*) dma1_addr);
  static dma2_t& dma2 =   *((dma2_t*) dma2_addr);

}

using namespace stm32 ;

#endif /* __DMA_F4_F7++_H__ */
