/*
 * dma++.h
 *
 *  Created on: 31 янв. 2017 г.
 *      Author: klen
 */

#ifndef __DMA_STREAM++_H__
#define __DMA_STREAM++_H__

#include "types++.h"

#include "dma_stream_f4_f7++.h"

namespace stm32f7
{

struct dma1_stream0_t : public stm32::dma1_stream0_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi3_rx=0,
      i2c1_rx,
      tim4_ch1,
      uart5_rx=4,
      uatr8_tx,
      tim5_ch3_tim5_up,
	  i2c3_tx=8
    }  ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){ configuration.rmw( val) ; }
  inline void channel_spi3_rx()             { configuration.rmw( channel_t::spi3_rx) ; }
  inline void channel_i2c1_rx()             { configuration.rmw( channel_t::i2c1_rx) ; }
  inline void channel_tim4_ch1()            { configuration.rmw( channel_t::tim4_ch1) ; }
  inline void channel_uart5_rx()            { configuration.rmw( channel_t::uart5_rx) ; }
  inline void channel_uart8_tx()            { configuration.rmw( channel_t::uatr8_tx) ; }
  inline void channel_uart5_ch3_tim5_up()   { configuration.rmw( channel_t::tim5_ch3_tim5_up) ; }
  inline void channel_i2c3_tx()             { configuration.rmw( channel_t::i2c3_tx) ; }
  inline auto channel() const {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream0_t& ref() { return *((stm32f7::dma1_stream0_t*) dma1_stream0_addr); };
} ;

struct dma1_stream1_t : public stm32::dma1_stream1_t
{
  struct channel_t { enum enum_t
   {
      offset=25, mask= 0b1111,
	  spdifrx_dt=0,
	  i2c3_rx,
      uart2_up_tim2_ch3=3,
      usart3_rx,
      uart7_tx,
      tim5_ch4_tim5_trig,
      tim6_up,
	  i2c4_rx,
	  spi2_rx
    }  ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val) ; }
  inline void channel_spdifrx_dt()          {  configuration.rmw(channel_t::spdifrx_dt) ; }
  inline void channel_i2c3_rx()             {  configuration.rmw(channel_t::i2c3_rx) ; }
  inline void channel_uart2_up_tim2_ch3()   {  configuration.rmw(channel_t::uart2_up_tim2_ch3) ; }
  inline void channel_usart3_rx()           {  configuration.rmw(channel_t::usart3_rx) ; }
  inline void channel_uart7_tx()            {  configuration.rmw(channel_t::uart7_tx) ; }
  inline void channel_tim5_ch4_tim5_trig()  {  configuration.rmw(channel_t::tim5_ch4_tim5_trig) ; }
  inline void channel_tim6_up()             {  configuration.rmw(channel_t::tim6_up) ; }
  inline void channel_i2c4_rx()             {  configuration.rmw(channel_t::i2c4_rx) ; }
  inline void channel_spi2_rx()             {  configuration.rmw(channel_t::spi2_rx) ; }
  inline auto channel()  const {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream1_t& ref() { return *((stm32f7::dma1_stream1_t*) dma1_stream1_addr); };
} ;


struct dma1_stream2_t : public stm32::dma1_stream2_t
{
    struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi3_rx=0,
      tim7_up,
	  i2c4_rx,
      i2c3_rx,
      uart4_rx,
      tim3_ch4_tim3_up,
      tim5_ch1,
      i2c2_rx,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val) ; }
  inline void channel_spi3_rx()             {  configuration.rmw(channel_t::spi3_rx) ;}
  inline void channel_tim7_up()             {  configuration.rmw(channel_t::tim7_up) ;}
  inline void channel_i2c4_rx()             {  configuration.rmw(channel_t::i2c4_rx) ;}
  inline void channel_i2c3_rx()             {  configuration.rmw(channel_t::i2c3_rx) ;}
  inline void channel_uart4_rx()            {  configuration.rmw(channel_t::uart4_rx) ;}
  inline void channel_tim3_ch4_tim3_up()    {  configuration.rmw(channel_t::tim3_ch4_tim3_up) ;}
  inline void channel_tim5_ch1()            {  configuration.rmw(channel_t::tim5_ch1) ;}
  inline void channel_i2c2_rx()             {  configuration.rmw(channel_t::i2c2_rx) ;}
  inline auto channel() const  {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream2_t& ref() { return *((stm32f7::dma1_stream2_t*) dma1_stream2_addr); };
} ;

struct dma1_stream3_t : public stm32::dma1_stream3_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi2_rx=0,
      tim4_ch2=2,
      usart3_tx=4,
      uart7_rx,
      tim5_ch4_tim5_trig,
      i2c2_rx,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val ); }
  inline void channel_spi2_rx()             {  configuration.rmw(channel_t::spi2_rx ) ;}
  inline void channel_tim4_ch2()            {  configuration.rmw(channel_t::tim4_ch2 ) ;}
  inline void channel_usart3_tx()           {  configuration.rmw(channel_t::usart3_tx ) ;}
  inline void channel_uart7_rx()            {  configuration.rmw(channel_t::uart7_rx) ;}
  inline void channel_tim5_ch4_tim5_trig()  {  configuration.rmw(channel_t::tim5_ch4_tim5_trig ) ;}
  inline void channel_i2c2_rx()             {  configuration.rmw(channel_t::i2c2_rx) ;}
  inline auto channel() const  {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream3_t& ref() { return *((stm32f7::dma1_stream3_t*) dma1_stream3_addr); };
} ;

struct dma1_stream4_t : public stm32::dma1_stream4_t
{
    struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi2_tx=0,
      tim7_up,
      i2c3_tx=3,
      uart4_tx,
      tim3_ch1_tim3_trig,
      tim5_ch2,
      usart3_tx,
	  i2c2_tx
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val );}
  inline void channel_spi2_tx()             {  configuration.rmw(channel_t::spi2_tx) ;}
  inline void channel_tim7_up()             {  configuration.rmw(channel_t::tim7_up);}
  inline void channel_i2c3_tx()             {  configuration.rmw(channel_t::i2c3_tx );}
  inline void channel_uart4_tx()            {  configuration.rmw(channel_t::uart4_tx);}
  inline void channel_tim3_ch1_tim3_trig()  {  configuration.rmw(channel_t::tim3_ch1_tim3_trig );}
  inline void channel_tim5_ch2()            {  configuration.rmw(channel_t::tim5_ch2);}
  inline void channel_usart3_tx()           {  configuration.rmw(channel_t::usart3_tx);}
  inline void channel_i2c2_tx()             {  configuration.rmw(channel_t::i2c2_tx);}
  inline auto channel() const  { return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream4_t& ref() { return *((stm32f7::dma1_stream4_t*) dma1_stream4_addr); };
} ;

struct dma1_stream5_t : public stm32::dma1_stream5_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi3_tx=0,
      i2c1_rx,
      i2c4_tx,
      tim2_ch1,
      usart2_rx,
      tim3_ch2,
	  dac1=7,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw( val );}
  inline void channel_spi3_tx()       {  configuration.rmw( channel_t::spi3_tx ) ;}
  inline void channel_i2c1_rx()       {  configuration.rmw( channel_t::i2c1_rx ) ;}
  inline void channel_i2c4_tx()       {  configuration.rmw( channel_t::i2c4_tx) ;}
  inline void channel_tim2_ch1()      {  configuration.rmw( channel_t::tim2_ch1 ) ;}
  inline void channel_usart2_rx()     {  configuration.rmw( channel_t::usart2_rx ) ;}
  inline void channel_tim3_ch2()      {  configuration.rmw( channel_t::tim3_ch2 ) ;}
  inline void channel_dac1()          {  configuration.rmw( channel_t::dac1) ;}
  inline auto channel() const {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream5_t& ref() { return *((stm32f7::dma1_stream5_t*) dma1_stream5_addr); };
} ;

struct dma1_stream6_t : public stm32::dma1_stream6_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
	  spdifrx_cs=0,
      i2c1_tx,
      tim4_up,
      tim2_ch2_tim2_ch4,
      usart2_tx,
      uart8_rx,
      tim5_up,
      dac2,
	  i2c4_tx,
	  spi2_tx
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw( val );}
  inline void channel_i2c1_tx()             {  configuration.rmw( channel_t::i2c1_tx ) ;}
  inline void channel_tim4_up()             {  configuration.rmw( channel_t::tim4_up) ;}
  inline void channel_tim2_ch2_tim2_ch4()   {  configuration.rmw( channel_t::tim2_ch2_tim2_ch4 ) ;}
  inline void channel_usart2_tx()           {  configuration.rmw( channel_t::usart2_tx ) ;}
  inline void channel_uart8_rx()            {  configuration.rmw( channel_t::uart8_rx ) ;}
  inline void channel_tim5_up()             {  configuration.rmw( channel_t::tim5_up) ;}
  inline void channel_dac2()                {  configuration.rmw( channel_t::dac2) ;}
  inline void channel_i2c4_tx()             {  configuration.rmw( channel_t::i2c4_tx) ;}
  inline void channel_spi2_tx()             {  configuration.rmw( channel_t::spi2_tx) ;}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma1_stream6_t& ref() { return *((stm32f7::dma1_stream6_t*) dma1_stream6_addr); };
} ;

struct dma1_stream7_t : public stm32::dma1_stream7_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      spi3_tx=0,
      i2c1_tx,
      tim4_ch3,
      tim2_up_tim2_ch4,
      uart5_tx,
      tim3_ch3,
      i2c2_tx=7,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_spi3_tx()             {  configuration.rmw( channel_t::spi3_tx) ;}
  inline void channel_i2c1_tx()             {  configuration.rmw( channel_t::i2c1_tx) ;}
  inline void channel_tim4_ch3()            {  configuration.rmw( channel_t::tim4_ch3) ;}
  inline void channel_tim2_up_tim2_ch4()    {  configuration.rmw( channel_t::tim2_up_tim2_ch4) ;}
  inline void channel_uart5_tx()            {  configuration.rmw( channel_t::uart5_tx) ;}
  inline void channel_tim3_ch3()            {  configuration.rmw( channel_t::tim3_ch3) ;}
  inline void channel_i2c2_tx()             {  configuration.rmw( channel_t::i2c2_tx) ;}
  inline auto channel() const {  return configuration.rd<channel_t> (); }

  inline static stm32f7::dma1_stream7_t& ref() { return *((stm32f7::dma1_stream7_t*) dma1_stream7_addr); };
} ;

struct dma2_stream0_t : public stm32::dma2_stream0_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      adc1=0,
      adc3=2,
      spi1_rx,
      spi4_rx,
      tim1_trig=6,
      dfsdm1_flt0,
      jpeg_in,
      sai1_b,
      sdmmc2
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_adc1()                { configuration.rmw( channel_t::adc1) ;}
  inline void channel_adc3()                { configuration.rmw( channel_t::adc3) ;}
  inline void channel_spi1_rx()             { configuration.rmw( channel_t::spi1_rx) ;}
  inline void channel_spi4_rx()             { configuration.rmw( channel_t::spi4_rx) ;}
  inline void channel_tim1_trig()           { configuration.rmw( channel_t::tim1_trig) ;}
  inline void channel_dfsdm1_flt0()         { configuration.rmw( channel_t::dfsdm1_flt0) ;}
  inline void channel_jpeg_in()             { configuration.rmw( channel_t::jpeg_in) ;}
  inline void channel_sai1_b()              { configuration.rmw( channel_t::sai1_b) ;}
  inline void channel_sdmmc2()              { configuration.rmw( channel_t::sdmmc2) ;}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream0_t& ref() { return *((stm32f7::dma2_stream0_t*) dma2_stream0_addr); };
} ;

struct dma2_stream1_t : public stm32::dma2_stream1_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,

      sai1_a=0,
      dcmi,
      adc3,
      spi4_tx=4,
      usart6_rx,
      tim1_ch1,
      tim8_up,
	  dfsdm1_flt1,
	  jpeg_out,
	  sai2_b
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val);}
  inline void channel_sai1_a()              {  configuration.rmw( channel_t::sai1_a) ;}
  inline void channel_dcmi()                {  configuration.rmw( channel_t::dcmi) ;}
  inline void channel_adc3()                {  configuration.rmw( channel_t::adc3) ;}
  inline void channel_spi4_tx()             {  configuration.rmw( channel_t::spi4_tx) ;}
  inline void channel_usart6_rx()           {  configuration.rmw( channel_t::usart6_rx) ;}
  inline void channel_tim1_ch1()            {  configuration.rmw( channel_t::tim1_ch1) ;}
  inline void channel_tim8_up()             {  configuration.rmw( channel_t::tim8_up);}
  inline void channel_dfsdm1_flt1()         {  configuration.rmw( channel_t::dfsdm1_flt1);}
  inline void channel_jpeg_out()            {  configuration.rmw( channel_t::jpeg_out);}
  inline void channel_sai2_b()              {  configuration.rmw( channel_t::sai2_b);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream1_t& ref() { return *((stm32f7::dma2_stream1_t*) dma2_stream1_addr); };
} ;

struct dma2_stream2_t : public stm32::dma2_stream2_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      tim8_ch1_tim8_ch2_tim8_ch3=0,
      adc2,
      spi1_rx=3,
      usart1_rx,
      usart6_rx,
      tim1_ch2,
      tim8_ch1,
	  dfsdm1_flt2,
	  spi4_tx,
	  sai2_a,
	  quadspi
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_tim8_ch1_tim8_ch2_tim8_ch3(){  configuration.rmw( channel_t::tim8_ch1_tim8_ch2_tim8_ch3);}
  inline void channel_adc2()                      {  configuration.rmw( channel_t::adc2 );}
  inline void channel_spi1_rx()                   {  configuration.rmw( channel_t::spi1_rx);}
  inline void channel_usart1_rx()                 {  configuration.rmw( channel_t::usart1_rx);}
  inline void channel_usart6_rx()                 {  configuration.rmw( channel_t::usart6_rx);}
  inline void channel_tim1_ch2()                  {  configuration.rmw( channel_t::tim1_ch2);}
  inline void channel_tim8_ch1()                  {  configuration.rmw( channel_t::tim8_ch1);}
  inline void channel_dfsdm1_flt2()               {  configuration.rmw( channel_t::dfsdm1_flt2);}
  inline void channel_spi4_tx()                   {  configuration.rmw( channel_t::spi4_tx);}
  inline void channel_sai2_a()                    {  configuration.rmw( channel_t::sai2_a);}
  inline void channel_quadspi()                   {  configuration.rmw( channel_t::quadspi);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream2_t& ref() { return *((stm32f7::dma2_stream2_t*) dma2_stream2_addr); };

} ;

struct dma2_stream3_t : public stm32::dma2_stream3_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      sai_a=0,
      adc2,
      spi5_rx,
      spi1_tx,
      sdmmc1,
      spi4_rx,
      tim1_ch1,
      tim8_ch2,
	  dfsdm1_flt3,
	  jpeg_in
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_sai_a()               {  configuration.rmw( channel_t::sai_a);}
  inline void channel_adc2()                {  configuration.rmw( channel_t::adc2);}
  inline void channel_spi5_rx()             {  configuration.rmw( channel_t::spi5_rx);}
  inline void channel_spi1_tx()             {  configuration.rmw( channel_t::spi1_tx);}
  inline void channel_sdmmc1()              {  configuration.rmw( channel_t::sdmmc1);}
  inline void channel_spi4_rx()             {  configuration.rmw( channel_t::spi4_rx);}
  inline void channel_tim1_ch1()            {  configuration.rmw( channel_t::tim1_ch1);}
  inline void channel_tim8_ch2()            {  configuration.rmw( channel_t::tim8_ch2);}
  inline void channel_dfsdm1_flt3()         {  configuration.rmw( channel_t::dfsdm1_flt3);}
  inline void channel_jpeg_in()             {  configuration.rmw( channel_t::jpeg_in);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream3_t& ref() { return *((stm32f7::dma2_stream3_t*) dma2_stream3_addr); };
} ;

struct dma2_stream4_t : public stm32::dma2_stream4_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      adc1=0,
      sai1_b,
      spi5_tx,
	  sai2_a,
      spi4_tx=5,
      tim1_ch4_tim1_trig_tim1_com,
      tim8_ch3,
	  dfsdm1_flt0,
	  jpeg_out
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val);}
  inline void channel_adc1()                {  configuration.rmw( channel_t::adc1);}
  inline void channel_sai1_b()              {  configuration.rmw( channel_t::sai1_b);}
  inline void channel_spi5_tx()             {  configuration.rmw( channel_t::spi5_tx);}
  inline void channel_sai2_a()              {  configuration.rmw( channel_t::sai2_a);}
  inline void channel_spi4_tx()             {  configuration.rmw( channel_t::spi4_tx);}
  inline void channel_tim1_ch4_tim1_trig_tim1_com(){  configuration.rmw( channel_t::tim1_ch4_tim1_trig_tim1_com);}
  inline void channel_tim8_ch3()            {  configuration.rmw( channel_t::tim8_ch3);}
  inline void channel_dfsdm1_flt0()         {  configuration.rmw( channel_t::dfsdm1_flt0);}
  inline void channel_jpeg_out()            {  configuration.rmw( channel_t::jpeg_out);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream4_t& ref() { return *((stm32f7::dma2_stream4_t*) dma2_stream4_addr); };
} ;

struct dma2_stream5_t : public stm32::dma2_stream5_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      sai1_b=0,
      spi6_tx,
      crypt_out,
      spi1_tx,
      usart1_rx,
      tim1_up=6,
      spi5_rx,
	  dfsdm1_flt1,
	  //spi5_rx, ?????  RM0410 DocID028270 Rev 2  246/1896
	  sdmmc2=11
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_sai1_b()              {  configuration.rmw( channel_t::sai1_b);}
  inline void channel_spi6_tx()             {  configuration.rmw( channel_t::spi6_tx);}
  inline void channel_crypt_out()           {  configuration.rmw( channel_t::crypt_out);}
  inline void channel_spi1_tx()             {  configuration.rmw( channel_t::spi1_tx);}
  inline void channel_usart1_rx()           {  configuration.rmw( channel_t::usart1_rx);}
  inline void channel_tim1_up()             {  configuration.rmw( channel_t::tim1_up);}
  inline void channel_spi5_rx()             {  configuration.rmw( channel_t::spi5_rx);}
  inline void channel_dfsdm1_flt1()         {  configuration.rmw( channel_t::dfsdm1_flt1);}
  inline void channel_sdmmc2()              {  configuration.rmw( channel_t::sdmmc2);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream5_t& ref() { return *((stm32f7::dma2_stream5_t*) dma2_stream5_addr); };
} ;

struct dma2_stream6_t : public stm32::dma2_stream6_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      tim1_ch1_tim1_ch2_tim1_ch3=0,
      spi6_rx,
      crypt_in,
	  sai2_b,
      sdmmc1,
      usart6_tx,
      tim1_ch3,
      spi5_tx,
	  dfsdm1_flt2,
	  sai1_a=10
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val);}
  inline void channel_tim1_ch1_tim1_ch2_tim1_ch3(){  configuration.rmw( channel_t::tim1_ch1_tim1_ch2_tim1_ch3);}
  inline void channel_spi6_rx()                   {  configuration.rmw( channel_t::spi6_rx);}
  inline void channel_crypt_in()                  {  configuration.rmw( channel_t::crypt_in);}
  inline void channel_sai2_b()                    {  configuration.rmw( channel_t::sai2_b);}
  inline void channel_sdmmc1()                    {  configuration.rmw( channel_t::sdmmc1 );}
  inline void channel_usart6_tx()                 {  configuration.rmw( channel_t::usart6_tx);}
  inline void channel_tim1_ch3()                  {  configuration.rmw( channel_t::tim1_ch3 );}
  inline void channel_spi5_tx()                   {  configuration.rmw( channel_t::spi5_tx );}
  inline void channel_dfsdm1_flt2()               {  configuration.rmw( channel_t::dfsdm1_flt2 );}
  inline void channel_sai1_a()                    {  configuration.rmw( channel_t::sai1_a );}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream6_t& ref() { return *((stm32f7::dma2_stream6_t*) dma2_stream6_addr); };
} ;

struct dma2_stream7_t : public stm32::dma2_stream7_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b1111,
      sai2_b=0,
      dcmi,
      hash_in,
	  quadspi,
      usart1_tx,
      usart6_tx,
      tim8_ch4_tim8_trig_tim8_com=7,
	  dfsdm1_flt3
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw( val );}
  inline void channel_dcmi()                       {  configuration.rmw( channel_t::dcmi);}
  inline void channel_hash_in()                    {  configuration.rmw( channel_t::hash_in);}
  inline void channel_usart1_tx()                  {  configuration.rmw( channel_t::usart1_tx);}
  inline void channel_usart6_tx()                  {  configuration.rmw( channel_t::usart6_tx);}
  inline void channel_tim8_ch4_tim8_trig_tim8_com(){  configuration.rmw( channel_t::tim8_ch4_tim8_trig_tim8_com); }
  inline void channel_tim8_dfsdm1_flt3()           {  configuration.rmw( channel_t::dfsdm1_flt3); }
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f7::dma2_stream7_t& ref() { return *((stm32f7::dma2_stream7_t*) dma2_stream7_addr); };
} ;


  static stm32f7::dma1_stream0_t& dma1_stream0 = *((stm32f7::dma1_stream0_t*) dma1_stream0_addr);
  static stm32f7::dma1_stream1_t& dma1_stream1 = *((stm32f7::dma1_stream1_t*) dma1_stream1_addr);
  static stm32f7::dma1_stream2_t& dma1_stream2 = *((stm32f7::dma1_stream2_t*) dma1_stream2_addr);
  static stm32f7::dma1_stream3_t& dma1_stream3 = *((stm32f7::dma1_stream3_t*) dma1_stream3_addr);
  static stm32f7::dma1_stream4_t& dma1_stream4 = *((stm32f7::dma1_stream4_t*) dma1_stream4_addr);
  static stm32f7::dma1_stream5_t& dma1_stream5 = *((stm32f7::dma1_stream5_t*) dma1_stream5_addr);
  static stm32f7::dma1_stream6_t& dma1_stream6 = *((stm32f7::dma1_stream6_t*) dma1_stream6_addr);
  static stm32f7::dma1_stream7_t& dma1_stream7 = *((stm32f7::dma1_stream7_t*) dma1_stream7_addr);

  static stm32f7::dma2_stream0_t& dma2_stream0 = *((stm32f7::dma2_stream0_t*) dma2_stream0_addr);
  static stm32f7::dma2_stream1_t& dma2_stream1 = *((stm32f7::dma2_stream1_t*) dma2_stream1_addr);
  static stm32f7::dma2_stream2_t& dma2_stream2 = *((stm32f7::dma2_stream2_t*) dma2_stream2_addr);
  static stm32f7::dma2_stream3_t& dma2_stream3 = *((stm32f7::dma2_stream3_t*) dma2_stream3_addr);
  static stm32f7::dma2_stream4_t& dma2_stream4 = *((stm32f7::dma2_stream4_t*) dma2_stream4_addr);
  static stm32f7::dma2_stream5_t& dma2_stream5 = *((stm32f7::dma2_stream5_t*) dma2_stream5_addr);
  static stm32f7::dma2_stream6_t& dma2_stream6 = *((stm32f7::dma2_stream6_t*) dma2_stream6_addr);
  static stm32f7::dma2_stream7_t& dma2_stream7 = *((stm32f7::dma2_stream7_t*) dma2_stream7_addr);

}

using namespace stm32f7 ;

#endif /* __DMA_STREAM++_H__ */
