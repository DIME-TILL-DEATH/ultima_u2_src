/*
 * dma++.h
 *
 *  Created on: 14 сен. 2018 г.
 *      Author: klen
 */

#ifndef __DMA_STREAM++_H__
#define __DMA_STREAM++_H__

#include "types++.h"

#include "dma_stream_f4_f7++.h"

namespace stm32f4
{

struct dma1_stream0_t : public stm32::dma1_stream0_t
 {
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,
      spi3_rx=0,
      i2c1_rx,
      tim4_ch1,
      i2s3_ext_rx,
      uart5_rx,
      uatr8_tx,
      tim5_ch3_tim5_up,
    }  ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){ configuration.rmw( val) ; }
  inline void channel_spi3_rx()             { configuration.rmw( channel_t::spi3_rx) ; }
  inline void channel_i2c1_rx()             { configuration.rmw( channel_t::i2c1_rx) ; }
  inline void channel_tim4_ch1()            { configuration.rmw( channel_t::tim4_ch1) ; }
  inline void channel_i2s3_ext_rx()         { configuration.rmw( channel_t::i2s3_ext_rx) ; }
  inline void channel_uart5_rx()            { configuration.rmw( channel_t::uart5_rx) ; }
  inline void channel_uart8_tx()            { configuration.rmw( channel_t::uatr8_tx) ; }
  inline void channel_uart5_ch3_tim5_up()   { configuration.rmw( channel_t::tim5_ch3_tim5_up) ; }
  inline channel_t::enum_t channel()   const   {  return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream0_t& ref() { return *((stm32f4::dma1_stream0_t*) dma1_stream0_addr); };
} ;

struct dma1_stream1_t : public stm32::dma1_stream1_t
{
  struct channel_t { enum enum_t
   {
      offset=25, mask= 0b111,
      uart2_up_tim2_ch3=3,
      usart3_rx,
      uart7_tx,
      tim5_ch4_tim5_trig,
      tim6_up,
    }  ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val) ; }
  inline void channel_uart2_up_tim2_ch3()   {  configuration.rmw(channel_t::uart2_up_tim2_ch3) ; }
  inline void channel_usart3_rx()           {  configuration.rmw(channel_t::usart3_rx) ; }
  inline void channel_uart7_tx()            {  configuration.rmw(channel_t::uart7_tx) ; }
  inline void channel_tim5_ch4_tim5_trig()  {  configuration.rmw(channel_t::tim5_ch4_tim5_trig) ; }
  inline void channel_tim6_up()             {  configuration.rmw(channel_t::tim6_up) ; }
  inline auto channel()  const {  return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream1_t& ref() { return *((stm32f4::dma1_stream1_t*) dma1_stream1_addr); };
} ;


struct dma1_stream2_t : public stm32::dma1_stream2_t
{
    struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,
      spi3_rx=0,
      tim7_up,
      i2s3_ext_rx,
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
  inline void channel_i2s3_ext_rx()         {  configuration.rmw(channel_t::i2s3_ext_rx) ;}
  inline void channel_i2c3_rx()             {  configuration.rmw(channel_t::i2c3_rx) ;}
  inline void channel_uart4_rx()            {  configuration.rmw(channel_t::uart4_rx) ;}
  inline void channel_tim3_ch4_tim3_up()    {  configuration.rmw(channel_t::tim3_ch4_tim3_up) ;}
  inline void channel_tim5_ch1()            {  configuration.rmw(channel_t::tim5_ch1) ;}
  inline void channel_i2c2_rx()             {  configuration.rmw(channel_t::i2c2_rx) ;}
  inline auto channel() const  {  return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream2_t& ref() { return *((stm32f4::dma1_stream2_t*) dma1_stream2_addr); };

} ;

struct dma1_stream3_t : public stm32::dma1_stream3_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      spi2_rx,
      tim4_ch2=2,
      i2s2_ext_rx,
      usart3_tx,
      uart7_rx,
      tim5_ch4_tim5_trig,
      i2c2_rx,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val ); }
  inline void channel_spi2_rx()             {  configuration.rmw(channel_t::spi2_rx ) ;}
  inline void channel_tim4_ch2()            {  configuration.rmw(channel_t::tim4_ch2 ) ;}
  inline void channel_i2s2_ext_rx()         {  configuration.rmw(channel_t::i2s2_ext_rx ) ;}
  inline void channel_usart3_tx()           {  configuration.rmw(channel_t::usart3_tx ) ;}
  inline void channel_uart7_rx()            {  configuration.rmw(channel_t::uart7_rx) ;}
  inline void channel_tim5_ch4_tim5_trig()  {  configuration.rmw(channel_t::tim5_ch4_tim5_trig ) ;}
  inline void channel_i2c2_rx()             {  configuration.rmw(channel_t::i2c2_rx) ;}
  inline auto channel() const  {  return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream3_t& ref() { return *((stm32f4::dma1_stream3_t*) dma1_stream3_addr); };

} ;

struct dma1_stream4_t : public stm32::dma1_stream4_t
{
    struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      spi2_tx=0,
      tim7_up,
      i2s2_ext_tx,
      i2c3_tx,
      uart4_tx,
      tim3_ch1_tim3_trig,
      tim5_ch2,
      usart3_tx
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val );}
  inline void channel_spi2_tx()             {  configuration.rmw(channel_t::spi2_tx) ;}
  inline void channel_tim7_up()             {  configuration.rmw(channel_t::tim7_up);}
  inline void channel_i2s2_ext_tx()         {  configuration.rmw(channel_t::i2s2_ext_tx);}
  inline void channel_i2c3_tx()             {  configuration.rmw(channel_t::i2c3_tx );}
  inline void channel_uart4_tx()            {  configuration.rmw(channel_t::uart4_tx);}
  inline void channel_tim3_ch1_tim3_trig()  {  configuration.rmw(channel_t::tim3_ch1_tim3_trig );}
  inline void channel_tim5_ch2()            {  configuration.rmw(channel_t::tim5_ch2);}
  inline void channel_usart3_tx()           {  configuration.rmw(channel_t::usart3_tx);}
  inline auto channel() const  { return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream4_t& ref() { return *((stm32f4::dma1_stream4_t*) dma1_stream4_addr); };
} ;

struct dma1_stream5_t : public stm32::dma1_stream5_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      spi3_tx,
      i2c1_rx,
      i2s_ext_tx,
      tim2_ch1,
      usart2_rx,
      tim3_ch2,
      dac1=7,
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw( val );}
  inline void channel_spi3_tx()       {  configuration.rmw( channel_t::spi3_tx ) ;}
  inline void channel_i2c1_rx()       {  configuration.rmw( channel_t::i2c1_rx ) ;}
  inline void channel_i2c4_tx()       {  configuration.rmw( channel_t::i2s_ext_tx) ;}
  inline void channel_tim2_ch1()      {  configuration.rmw( channel_t::tim2_ch1 ) ;}
  inline void channel_usart2_rx()     {  configuration.rmw( channel_t::usart2_rx ) ;}
  inline void channel_tim3_ch2()      {  configuration.rmw( channel_t::tim3_ch2 ) ;}
  inline void channel_dac1()          {  configuration.rmw( channel_t::dac1) ;}
  inline auto channel() const {  return configuration.rd<channel_t> (); }

  inline static stm32f4::dma1_stream5_t& ref() { return *((stm32f4::dma1_stream5_t*) dma1_stream5_addr); };
} ;

struct dma1_stream6_t : public stm32::dma1_stream6_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      i2c1_tx=1,
      tim4_up,
      tim2_ch2_tim2_ch4,
      usart2_tx,
      uart8_rx,
      tim5_up,
      dac2,
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
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma1_stream6_t& ref() { return *((stm32f4::dma1_stream6_t*) dma1_stream6_addr); };
} ;

struct dma1_stream7_t : public stm32::dma1_stream7_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

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

  inline static stm32f4::dma1_stream7_t& ref() { return *((stm32f4::dma1_stream7_t*) dma1_stream7_addr); };
} ;

struct dma2_stream0_t : public stm32::dma2_stream0_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      adc1=0,
      adc3=2,
      spi1_rx,
      spi4_rx,
      tim1_trig=6
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_adc1()                {  configuration.rmw( channel_t::adc1) ;}
  inline void channel_adc3()                {  configuration.rmw( channel_t::adc3) ;}
  inline void channel_spi1_rx()             {  configuration.rmw( channel_t::spi1_rx) ;}
  inline void channel_spi4_rx()             {  configuration.rmw( channel_t::spi4_rx) ;}
  inline void channel_tim1_trig()           {  configuration.rmw( channel_t::tim1_trig) ;}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream0_t& ref() { return *((stm32f4::dma2_stream0_t*) dma2_stream0_addr); };
} ;

struct dma2_stream1_t : public stm32::dma2_stream1_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      sai1_a=0,
      dcmi,
      adc3,
      spi4_tx=4,
      usart6_rx,
      tim1_ch1,
      tim8_up,
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
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream1_t& ref() { return *((stm32f4::dma2_stream1_t*) dma2_stream1_addr); };

} ;

struct dma2_stream2_t : public stm32::dma2_stream2_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      tim8_ch1_tim8_ch2_tim8_ch3=0,
      adc2,
      spi1_rx=3,
      usart1_rx,
      usart6_rx,
      tim1_ch2,
      tim8_ch1
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val)      {  configuration.rmw(  val );}
  inline void channel_tim8_ch1_tim8_ch2_tim8_ch3(){  configuration.rmw( channel_t::tim8_ch1_tim8_ch2_tim8_ch3);}
  inline void channel_adc2()                      {  configuration.rmw( channel_t::adc2 );}
  inline void channel_spi1_rx()                   {  configuration.rmw( channel_t::spi1_rx);}
  inline void channel_usart1_rx()                 {  configuration.rmw( channel_t::usart1_rx);}
  inline void channel_usart6_rx()                 {  configuration.rmw( channel_t::usart6_rx);}
  inline void channel_tim1_ch2()                  {  configuration.rmw( channel_t::tim1_ch2);}
  inline void channel_tim8_ch1()                  {  configuration.rmw( channel_t::tim8_ch1);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream2_t& ref() { return *((stm32f4::dma2_stream2_t*) dma2_stream2_addr); };

} ;

struct dma2_stream3_t : public stm32::dma2_stream3_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      sai_a=0,
      adc2,
      spi5_rx,
      spi1_tx,
      sdio,
      spi4_rx,
      tim1_ch1,
      tim8_ch2
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(  val );}
  inline void channel_sai_a()               {  configuration.rmw( channel_t::sai_a);}
  inline void channel_adc2()                {  configuration.rmw( channel_t::adc2);}
  inline void channel_spi5_rx()             {  configuration.rmw( channel_t::spi5_rx);}
  inline void channel_spi1_tx()             {  configuration.rmw( channel_t::spi1_tx);}
  inline void channel_sdio()                {  configuration.rmw( channel_t::sdio);}
  inline void channel_spi4_rx()             {  configuration.rmw( channel_t::spi4_rx);}
  inline void channel_tim1_ch1()            {  configuration.rmw( channel_t::tim1_ch1);}
  inline void channel_tim8_ch2()            {  configuration.rmw( channel_t::tim8_ch2);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream3_t& ref() { return *((stm32f4::dma2_stream3_t*) dma2_stream3_addr); };

} ;

struct dma2_stream4_t : public stm32::dma2_stream4_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      adc1=0,
      sai1_b,
      spi5_tx,
      spi4_tx=5,
      tim1_ch4_tim1_trig_tim1_com,
      tim8_ch3
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val){  configuration.rmw(val);}
  inline void channel_adc1()                {  configuration.rmw( channel_t::adc1);}
  inline void channel_sai1_b()              {  configuration.rmw( channel_t::sai1_b);}
  inline void channel_spi5_tx()             {  configuration.rmw( channel_t::spi5_tx);}
  inline void channel_spi4_tx()             {  configuration.rmw( channel_t::spi4_tx);}
  inline void channel_tim1_ch4_tim1_trig_tim1_com(){  configuration.rmw( channel_t::tim1_ch4_tim1_trig_tim1_com);}
  inline void channel_tim8_ch3()            {  configuration.rmw( channel_t::tim8_ch3);}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream4_t& ref() { return *((stm32f4::dma2_stream4_t*) dma2_stream4_addr); };

} ;

struct dma2_stream5_t : public stm32::dma2_stream5_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      sai1_b=0,
      spi6_tx,
      crypt_out,
      spi1_tx,
      usart1_rx,
      tim1_up=6,
      spi5_rx,
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
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream5_t& ref() { return *((stm32f4::dma2_stream5_t*) dma2_stream5_addr); };

} ;

struct dma2_stream6_t : public stm32::dma2_stream6_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      tim1_ch1_tim1_ch2_tim1_ch3=0,
      spi6_rx,
      crypt_in,
      sdio=4,
      usart6_tx,
      tim1_ch3,
      spi5_tx
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val)      {  configuration.rmw(val);}
  inline void channel_tim1_ch1_tim1_ch2_tim1_ch3(){  configuration.rmw( channel_t::tim1_ch1_tim1_ch2_tim1_ch3);}
  inline void channel_spi6_rx()                   {  configuration.rmw( channel_t::spi6_rx);}
  inline void channel_crypt_in()                  {  configuration.rmw( channel_t::crypt_in);}
  inline void channel_sdio()                      {  configuration.rmw( channel_t::sdio );}
  inline void channel_usart6_tx()                 {  configuration.rmw( channel_t::usart6_tx);}
  inline void channel_tim1_ch3()                  {  configuration.rmw( channel_t::tim1_ch3 );}
  inline void channel_spi5_tx()                   {  configuration.rmw( channel_t::spi5_tx );}
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream6_t& ref() { return *((stm32f4::dma2_stream6_t*) dma2_stream6_addr); };

} ;

struct dma2_stream7_t : public stm32::dma2_stream7_t
{
  struct channel_t { enum enum_t
    {
      offset=25, mask= 0b111,

      dcmi=1,
      hash_in,
      usart1_tx=4,
      usart6_tx,
      tim8_ch4_tim8_trig_tim8_com=7
    } ; } ;

  inline void channel( const dma_stream_t::configuration_t::channel_t::enum_t val){ dma_stream_t::channel(val); }

  inline void channel( const channel_t::enum_t val)       {  configuration.rmw( val );}
  inline void channel_dcmi()                       {  configuration.rmw( channel_t::dcmi);}
  inline void channel_hash_in()                    {  configuration.rmw( channel_t::hash_in);}
  inline void channel_usart1_tx()                  {  configuration.rmw( channel_t::usart1_tx);}
  inline void channel_usart6_tx()                  {  configuration.rmw( channel_t::usart6_tx);}
  inline void channel_tim8_ch4_tim8_trig_tim8_com(){  configuration.rmw( channel_t::tim8_ch4_tim8_trig_tim8_com); }
  inline auto channel() const {  return configuration.rd<channel_t> ();}

  inline static stm32f4::dma2_stream7_t& ref() { return *((stm32f4::dma2_stream7_t*) dma2_stream7_addr); };
} ;

static dma1_stream0_t& dma1_stream0 = *((dma1_stream0_t*) dma1_stream0_addr);
static dma1_stream1_t& dma1_stream1 = *((dma1_stream1_t*) dma1_stream1_addr);
static dma1_stream2_t& dma1_stream2 = *((dma1_stream2_t*) dma1_stream2_addr);
static dma1_stream3_t& dma1_stream3 = *((dma1_stream3_t*) dma1_stream3_addr);
static dma1_stream4_t& dma1_stream4 = *((dma1_stream4_t*) dma1_stream4_addr);
static dma1_stream5_t& dma1_stream5 = *((dma1_stream5_t*) dma1_stream5_addr);
static dma1_stream6_t& dma1_stream6 = *((dma1_stream6_t*) dma1_stream6_addr);
static dma1_stream7_t& dma1_stream7 = *((dma1_stream7_t*) dma1_stream7_addr);

static dma2_stream0_t& dma2_stream0 = *((dma2_stream0_t*) dma2_stream0_addr);
static dma2_stream1_t& dma2_stream1 = *((dma2_stream1_t*) dma2_stream1_addr);
static dma2_stream2_t& dma2_stream2 = *((dma2_stream2_t*) dma2_stream2_addr);
static dma2_stream3_t& dma2_stream3 = *((dma2_stream3_t*) dma2_stream3_addr);
static dma2_stream4_t& dma2_stream4 = *((dma2_stream4_t*) dma2_stream4_addr);
static dma2_stream5_t& dma2_stream5 = *((dma2_stream5_t*) dma2_stream5_addr);
static dma2_stream6_t& dma2_stream6 = *((dma2_stream6_t*) dma2_stream6_addr);
static dma2_stream7_t& dma2_stream7 = *((dma2_stream7_t*) dma2_stream7_addr);

}

using namespace stm32f4 ;

#endif /* __DMA_STREAM++_H__ */
