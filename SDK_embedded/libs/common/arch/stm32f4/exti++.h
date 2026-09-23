/*
 * syscfg++.h
 *
 *  Created on: 21 янв. 2018 г.
 *      Author: klen
 */

#ifndef __EXTI++_H__
#define __EXTI++_H__

#include "types++.h"

namespace stm32f4
{

struct exti_t
{
  struct interrupt_mask_t : public read_write_32_t
	{
	    struct pin0_t  { enum enum_t{ offset=0, mask=1, masked=0, unmasked };};
	    struct pin1_t  { enum enum_t{ offset=1, mask=1, masked=0, unmasked };};
	    struct pin2_t  { enum enum_t{ offset=2, mask=1, masked=0, unmasked };};
	    struct pin3_t  { enum enum_t{ offset=3, mask=1, masked=0, unmasked };};
	    struct pin4_t  { enum enum_t{ offset=4, mask=1, masked=0, unmasked };};
	    struct pin5_t  { enum enum_t{ offset=5, mask=1, masked=0, unmasked };};
	    struct pin6_t  { enum enum_t{ offset=6, mask=1, masked=0, unmasked };};
	    struct pin7_t  { enum enum_t{ offset=7, mask=1, masked=0, unmasked };};
	    struct pin8_t  { enum enum_t{ offset=8, mask=1, masked=0, unmasked };};
	    struct pin9_t  { enum enum_t{ offset=9, mask=1, masked=0, unmasked };};
	    struct pin10_t { enum enum_t{ offset=10,mask=1, masked=0, unmasked };};
	    struct pin11_t { enum enum_t{ offset=11,mask=1, masked=0, unmasked };};
	    struct pin12_t { enum enum_t{ offset=12,mask=1, masked=0, unmasked };};
	    struct pin13_t { enum enum_t{ offset=13,mask=1, masked=0, unmasked };};
	    struct pin14_t { enum enum_t{ offset=14,mask=1, masked=0, unmasked };};
	    struct pin15_t { enum enum_t{ offset=15,mask=1, masked=0, unmasked };};
	    struct pvd_t         { enum enum_t{ offset=16,mask=1, masked=0, unmasked };};
	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, masked=0, unmasked };};
	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, masked=0, unmasked };};
	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, masked=0, unmasked };};
	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, masked=0, unmasked };};
	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, masked=0, unmasked };};
	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, masked=0, unmasked };};
	};


  inline  void pin_interrupt(const interrupt_mask_t::pin0_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin0_interrupt(const interrupt_mask_t::pin0_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin0_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin0_t::masked) ;}
  inline  void pin0_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin0_t::unmasked) ;}
  inline  auto pin0_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin0_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin1_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin1_interrupt(const interrupt_mask_t::pin1_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin1_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin1_t::masked) ;}
  inline  void pin1_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin1_t::unmasked) ;}
  inline  auto pin1_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin1_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin2_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin2_interrupt(const interrupt_mask_t::pin2_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin2_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin2_t::masked) ;}
  inline  void pin2_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin2_t::unmasked) ;}
  inline  auto pin2_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin2_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin3_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin3_interrupt(const interrupt_mask_t::pin3_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin3_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin3_t::masked) ;}
  inline  void pin3_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin3_t::unmasked) ;}
  inline  auto pin3_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin3_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin4_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin4_interrupt(const interrupt_mask_t::pin4_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin4_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin4_t::masked) ;}
  inline  void pin4_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin4_t::unmasked) ;}
  inline  auto pin4_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin4_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin5_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin5_interrupt(const interrupt_mask_t::pin5_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin5_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin5_t::masked) ;}
  inline  void pin5_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin5_t::unmasked) ;}
  inline  auto pin5_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin5_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin6_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin6_interrupt(const interrupt_mask_t::pin6_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin6_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin6_t::masked) ;}
  inline  void pin6_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin6_t::unmasked) ;}
  inline  auto pin6_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin6_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin7_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin7_interrupt(const interrupt_mask_t::pin7_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin7_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin7_t::masked) ;}
  inline  void pin7_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin7_t::unmasked) ;}
  inline  auto pin7_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin7_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin8_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin8_interrupt(const interrupt_mask_t::pin8_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin8_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin8_t::masked) ;}
  inline  void pin8_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin8_t::unmasked) ;}
  inline  auto pin8_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin8_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin9_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin9_interrupt(const interrupt_mask_t::pin9_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin9_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin9_t::masked) ;}
  inline  void pin9_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin9_t::unmasked) ;}
  inline  auto pin9_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin9_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin10_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin10_interrupt(const interrupt_mask_t::pin10_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin10_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin10_t::masked) ;}
  inline  void pin10_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin10_t::unmasked) ;}
  inline  auto pin10_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin10_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin11_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin11_interrupt(const interrupt_mask_t::pin11_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin11_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin11_t::masked) ;}
  inline  void pin11_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin11_t::unmasked) ;}
  inline  auto pin11_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin11_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin12_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin12_interrupt(const interrupt_mask_t::pin12_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin12_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin12_t::masked) ;}
  inline  void pin12_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin12_t::unmasked) ;}
  inline  auto pin12_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin12_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin13_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin13_interrupt(const interrupt_mask_t::pin13_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin13_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin13_t::masked) ;}
  inline  void pin13_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin13_t::unmasked) ;}
  inline  auto pin13_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin13_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin14_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin14_interrupt(const interrupt_mask_t::pin14_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin14_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin14_t::masked) ;}
  inline  void pin14_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin14_t::unmasked) ;}
  inline  auto pin14_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin14_t>();}

  inline  void pin_interrupt(const interrupt_mask_t::pin15_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin15_interrupt(const interrupt_mask_t::pin15_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pin15_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pin15_t::masked) ;}
  inline  void pin15_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pin15_t::unmasked) ;}
  inline  auto pin15_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pin15_t>();}

  inline  void pvd_interrupt(const interrupt_mask_t::pvd_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void pvd_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::pvd_t::masked) ;}
  inline  void pvd_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::pvd_t::unmasked) ;}
  inline  auto pvd_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::pvd_t>();}

  inline  void rtc_alarm_interrupt(const interrupt_mask_t::rtc_alarm_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void rtc_alarm_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_alarm_t::masked) ;}
  inline  void rtc_alarm_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_alarm_t::unmasked) ;}
  inline  auto rtc_alarm_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::rtc_alarm_t>();}

  inline  void usb_otg_fs_wakeup_interrupt(const interrupt_mask_t::usb_otg_fs_wakeup_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void usb_otg_fs_wakeup_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::usb_otg_fs_wakeup_t::masked) ;}
  inline  void usb_otg_fs_wakeup_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::usb_otg_fs_wakeup_t::unmasked) ;}
  inline  auto usb_otg_fs_wakeup_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::usb_otg_fs_wakeup_t>();}

  inline  void ethernet_wakeup_interrupt(const interrupt_mask_t::ethernet_wakeup_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void ethernet_wakeup_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::ethernet_wakeup_t::masked) ;}
  inline  void ethernet_wakeup_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::ethernet_wakeup_t::unmasked) ;}
  inline  auto ethernet_wakeup_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::ethernet_wakeup_t>();}

  inline  void usb_otg_hs_wakeup_interrupt(const interrupt_mask_t::usb_otg_hs_wakeup_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void usb_otg_hs_wakeup_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::usb_otg_hs_wakeup_t::masked) ;}
  inline  void usb_otg_hs_wakeup_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::usb_otg_hs_wakeup_t::unmasked) ;}
  inline  auto usb_otg_hs_wakeup_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::usb_otg_hs_wakeup_t>();}

  inline  void rtc_tamper_time_stamp_interrupt(const interrupt_mask_t::rtc_tamper_time_stamp_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void rtc_tamper_time_stamp_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_tamper_time_stamp_t::masked) ;}
  inline  void rtc_tamper_time_stamp_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_tamper_time_stamp_t::unmasked) ;}
  inline  auto rtc_tamper_time_stamp_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::rtc_tamper_time_stamp_t>();}

  inline  void rtc_wakeup_interrupt(const interrupt_mask_t::rtc_wakeup_t::enum_t val){  interrupt_mask.rmw(val) ;}
  inline  void rtc_wakeup_interrupt_masked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_wakeup_t::masked) ;}
  inline  void rtc_wakeup_interrupt_unmasked() {  interrupt_mask.rmw( interrupt_mask_t::rtc_wakeup_t::unmasked) ;}
  inline  auto rtc_wakeup_interrupt()const {  return interrupt_mask.rd<interrupt_mask_t::rtc_wakeup_t>();}

  struct event_mask_t : public read_write_32_t
	{
	    struct pin0_t  { enum enum_t{ offset=0, mask=1, masked=0, unmasked };};
	    struct pin1_t  { enum enum_t{ offset=1, mask=1, masked=0, unmasked };};
	    struct pin2_t  { enum enum_t{ offset=2, mask=1, masked=0, unmasked };};
	    struct pin3_t  { enum enum_t{ offset=3, mask=1, masked=0, unmasked };};
	    struct pin4_t  { enum enum_t{ offset=4, mask=1, masked=0, unmasked };};
	    struct pin5_t  { enum enum_t{ offset=5, mask=1, masked=0, unmasked };};
	    struct pin6_t  { enum enum_t{ offset=6, mask=1, masked=0, unmasked };};
	    struct pin7_t  { enum enum_t{ offset=7, mask=1, masked=0, unmasked };};
	    struct pin8_t  { enum enum_t{ offset=8, mask=1, masked=0, unmasked };};
	    struct pin9_t  { enum enum_t{ offset=9, mask=1, masked=0, unmasked };};
	    struct pin10_t { enum enum_t{ offset=10,mask=1, masked=0, unmasked };};
	    struct pin11_t { enum enum_t{ offset=11,mask=1, masked=0, unmasked };};
	    struct pin12_t { enum enum_t{ offset=12,mask=1, masked=0, unmasked };};
	    struct pin13_t { enum enum_t{ offset=13,mask=1, masked=0, unmasked };};
	    struct pin14_t { enum enum_t{ offset=14,mask=1, masked=0, unmasked };};
	    struct pin15_t { enum enum_t{ offset=15,mask=1, masked=0, unmasked };};
	    struct pvd_t         { enum enum_t{ offset=16,mask=1, masked=0, unmasked };};
	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, masked=0, unmasked };};
	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, masked=0, unmasked };};
	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, masked=0, unmasked };};
	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, masked=0, unmasked };};
	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, masked=0, unmasked };};
	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, masked=0, unmasked };};
	};

  inline  void pin0_event(const event_mask_t::pin0_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin0_event_masked() {  event_mask.rmw( event_mask_t::pin0_t::masked) ;}
  inline  void pin0_event_unmasked() {  event_mask.rmw( event_mask_t::pin0_t::unmasked) ;}
  inline  auto pin0_event()const {  return event_mask.rd<event_mask_t::pin0_t>();}

  inline  void pin1_event(const event_mask_t::pin1_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin1_event_masked() {  event_mask.rmw( event_mask_t::pin1_t::masked) ;}
  inline  void pin1_event_unmasked() {  event_mask.rmw( event_mask_t::pin1_t::unmasked) ;}
  inline  auto pin1_event()const {  return event_mask.rd<event_mask_t::pin1_t>();}

  inline  void pin2_event(const event_mask_t::pin2_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin2_event_masked() {  event_mask.rmw( event_mask_t::pin2_t::masked) ;}
  inline  void pin2_event_unmasked() {  event_mask.rmw( event_mask_t::pin2_t::unmasked) ;}
  inline  auto pin2_event()const {  return event_mask.rd<event_mask_t::pin2_t>();}

  inline  void pin3_event(const event_mask_t::pin3_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin3_event_masked() {  event_mask.rmw( event_mask_t::pin3_t::masked) ;}
  inline  void pin3_event_unmasked() {  event_mask.rmw( event_mask_t::pin3_t::unmasked) ;}
  inline  auto pin3_event()const {  return event_mask.rd<event_mask_t::pin3_t>();}

  inline  void pin4_event(const event_mask_t::pin4_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin4_event_masked() {  event_mask.rmw( event_mask_t::pin4_t::masked) ;}
  inline  void pin4_event_unmasked() {  event_mask.rmw( event_mask_t::pin4_t::unmasked) ;}
  inline  auto pin4_event()const {  return event_mask.rd<event_mask_t::pin4_t>();}

  inline  void pin5_event(const event_mask_t::pin5_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin5_event_masked() {  event_mask.rmw( event_mask_t::pin5_t::masked) ;}
  inline  void pin5_event_unmasked() {  event_mask.rmw( event_mask_t::pin5_t::unmasked) ;}
  inline  auto pin5_event()const {  return event_mask.rd<event_mask_t::pin5_t>();}

  inline  void pin6_event(const event_mask_t::pin6_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin6_event_masked() {  event_mask.rmw( event_mask_t::pin6_t::masked) ;}
  inline  void pin6_event_unmasked() {  event_mask.rmw( event_mask_t::pin6_t::unmasked) ;}
  inline  auto pin6_event()const {  return event_mask.rd<event_mask_t::pin6_t>();}

  inline  void pin7_event(const event_mask_t::pin7_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin7_event_masked() {  event_mask.rmw( event_mask_t::pin7_t::masked) ;}
  inline  void pin7_event_unmasked() {  event_mask.rmw( event_mask_t::pin7_t::unmasked) ;}
  inline  auto pin7_event()const {  return event_mask.rd<event_mask_t::pin7_t>();}

  inline  void pin8_event(const event_mask_t::pin8_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin8_event_masked() {  event_mask.rmw( event_mask_t::pin8_t::masked) ;}
  inline  void pin8_event_unmasked() {  event_mask.rmw( event_mask_t::pin8_t::unmasked) ;}
  inline  auto pin8_event()const {  return event_mask.rd<event_mask_t::pin8_t>();}

  inline  void pin9_event(const event_mask_t::pin9_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin9_event_masked() {  event_mask.rmw( event_mask_t::pin9_t::masked) ;}
  inline  void pin9_event_unmasked() {  event_mask.rmw( event_mask_t::pin9_t::unmasked) ;}
  inline  auto pin9_event()const {  return event_mask.rd<event_mask_t::pin9_t>();}

  inline  void pin10_event(const event_mask_t::pin10_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin10_event_masked() {  event_mask.rmw( event_mask_t::pin10_t::masked) ;}
  inline  void pin10_event_unmasked() {  event_mask.rmw( event_mask_t::pin10_t::unmasked) ;}
  inline  auto pin10_event()const {  return event_mask.rd<event_mask_t::pin10_t>();}

  inline  void pin11_event(const event_mask_t::pin11_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin11_event_masked() {  event_mask.rmw( event_mask_t::pin11_t::masked) ;}
  inline  void pin11_event_unmasked() {  event_mask.rmw( event_mask_t::pin11_t::unmasked) ;}
  inline  auto pin11_event()const {  return event_mask.rd<event_mask_t::pin11_t>();}

  inline  void pin12_event(const event_mask_t::pin12_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin12_event_masked() {  event_mask.rmw( event_mask_t::pin12_t::masked) ;}
  inline  void pin12_event_unmasked() {  event_mask.rmw( event_mask_t::pin12_t::unmasked) ;}
  inline  auto pin12_event()const {  return event_mask.rd<event_mask_t::pin12_t>();}

  inline  void pin13_event(const event_mask_t::pin13_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin13_event_masked() {  event_mask.rmw( event_mask_t::pin13_t::masked) ;}
  inline  void pin13_event_unmasked() {  event_mask.rmw( event_mask_t::pin13_t::unmasked) ;}
  inline  auto pin13_event()const {  return event_mask.rd<event_mask_t::pin13_t>();}

  inline  void pin14_event(const event_mask_t::pin14_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin14_event_masked() {  event_mask.rmw( event_mask_t::pin14_t::masked) ;}
  inline  void pin14_event_unmasked() {  event_mask.rmw( event_mask_t::pin14_t::unmasked) ;}
  inline  auto pin14_event()const {  return event_mask.rd<event_mask_t::pin14_t>();}

  inline  void pin15_event(const event_mask_t::pin15_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pin15_event_masked() {  event_mask.rmw( event_mask_t::pin15_t::masked) ;}
  inline  void pin15_event_unmasked() {  event_mask.rmw( event_mask_t::pin15_t::unmasked) ;}
  inline  auto pin15_event()const {  return event_mask.rd<event_mask_t::pin15_t>();}

  inline  void pvd_event(const event_mask_t::pvd_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void pvd_event_masked() {  event_mask.rmw( event_mask_t::pvd_t::masked) ;}
  inline  void pvd_event_unmasked() {  event_mask.rmw( event_mask_t::pvd_t::unmasked) ;}
  inline  auto pvd_event()const {  return event_mask.rd<event_mask_t::pvd_t>();}

  inline  void rtc_alarm_event(const event_mask_t::rtc_alarm_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void rtc_alarm_event_masked() {  event_mask.rmw( event_mask_t::rtc_alarm_t::masked) ;}
  inline  void rtc_alarm_event_unmasked() {  event_mask.rmw( event_mask_t::rtc_alarm_t::unmasked) ;}
  inline  auto rtc_alarm_event()const {  return event_mask.rd<event_mask_t::rtc_alarm_t>();}

  inline  void usb_otg_fs_wakeup_event(const event_mask_t::usb_otg_fs_wakeup_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void usb_otg_fs_wakeup_event_masked() {  event_mask.rmw( event_mask_t::usb_otg_fs_wakeup_t::masked) ;}
  inline  void usb_otg_fs_wakeup_event_unmasked() {  event_mask.rmw( event_mask_t::usb_otg_fs_wakeup_t::unmasked) ;}
  inline  auto usb_otg_fs_wakeup_event()const {  return event_mask.rd<event_mask_t::usb_otg_fs_wakeup_t>();}

  inline  void ethernet_wakeup_event(const event_mask_t::ethernet_wakeup_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void ethernet_wakeup_event_masked() {  event_mask.rmw( event_mask_t::ethernet_wakeup_t::masked) ;}
  inline  void ethernet_wakeup_event_unmasked() {  event_mask.rmw( event_mask_t::ethernet_wakeup_t::unmasked) ;}
  inline  auto ethernet_wakeup_event()const {  return event_mask.rd<event_mask_t::ethernet_wakeup_t>();}

  inline  void usb_otg_hs_wakeup_event(const event_mask_t::usb_otg_hs_wakeup_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void usb_otg_hs_wakeup_event_masked() {  event_mask.rmw( event_mask_t::usb_otg_hs_wakeup_t::masked) ;}
  inline  void usb_otg_hs_wakeup_event_unmasked() {  event_mask.rmw( event_mask_t::usb_otg_hs_wakeup_t::unmasked) ;}
  inline  auto usb_otg_hs_wakeup_event()const {  return event_mask.rd<event_mask_t::usb_otg_hs_wakeup_t>();}

  inline  void rtc_tamper_time_stamp_event(const event_mask_t::rtc_tamper_time_stamp_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void rtc_tamper_time_stamp_event_masked() {  event_mask.rmw( event_mask_t::rtc_tamper_time_stamp_t::masked) ;}
  inline  void rtc_tamper_time_stamp_event_unmasked() {  event_mask.rmw( event_mask_t::rtc_tamper_time_stamp_t::unmasked) ;}
  inline  auto rtc_tamper_time_stamp_event()const {  return event_mask.rd<event_mask_t::rtc_tamper_time_stamp_t>();}

  inline  void rtc_wakeup_event(const event_mask_t::rtc_wakeup_t::enum_t val){  event_mask.rmw(val) ;}
  inline  void rtc_wakeup_event_masked() {  event_mask.rmw( event_mask_t::rtc_wakeup_t::masked) ;}
  inline  void rtc_wakeup_event_unmasked() {  event_mask.rmw( event_mask_t::rtc_wakeup_t::unmasked) ;}
  inline  auto rtc_wakeup_event()const {  return event_mask.rd<event_mask_t::rtc_wakeup_t>();}

  struct rising_trigger_selection_t : public read_write_32_t
  	{
  	    struct pin0_t  { enum enum_t{ offset=0, mask=1, disable=0, enable };};
  	    struct pin1_t  { enum enum_t{ offset=1, mask=1, disable=0, enable };};
  	    struct pin2_t  { enum enum_t{ offset=2, mask=1, disable=0, enable };};
  	    struct pin3_t  { enum enum_t{ offset=3, mask=1, disable=0, enable };};
  	    struct pin4_t  { enum enum_t{ offset=4, mask=1, disable=0, enable };};
  	    struct pin5_t  { enum enum_t{ offset=5, mask=1, disable=0, enable };};
  	    struct pin6_t  { enum enum_t{ offset=6, mask=1, disable=0, enable };};
  	    struct pin7_t  { enum enum_t{ offset=7, mask=1, disable=0, enable };};
  	    struct pin8_t  { enum enum_t{ offset=8, mask=1, disable=0, enable };};
  	    struct pin9_t  { enum enum_t{ offset=9, mask=1, disable=0, enable };};
  	    struct pin10_t { enum enum_t{ offset=10,mask=1, disable=0, enable };};
  	    struct pin11_t { enum enum_t{ offset=11,mask=1, disable=0, enable };};
  	    struct pin12_t { enum enum_t{ offset=12,mask=1, disable=0, enable };};
  	    struct pin13_t { enum enum_t{ offset=13,mask=1, disable=0, enable };};
  	    struct pin14_t { enum enum_t{ offset=14,mask=1, disable=0, enable };};
  	    struct pin15_t { enum enum_t{ offset=15,mask=1, disable=0, enable };};
  	    struct pvd_t         { enum enum_t{ offset=16,mask=1, disable=0, enable };};
  	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, disable=0, enable };};
  	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, disable=0, enable };};
  	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, disable=0, enable };};
  	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, disable=0, enable };};
  	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, disable=0, enable };};
  	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, disable=0, enable };};
  	};

    inline  void rising_trigger(const rising_trigger_selection_t::pin0_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin0_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin0_t::disable) ;}
    inline  void pin0_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin0_t::enable) ;}
    inline  auto pin0_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin0_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin1_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin1_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin1_t::disable) ;}
    inline  void pin1_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin1_t::enable) ;}
    inline  auto pin1_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin1_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin2_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin2_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin2_t::disable) ;}
    inline  void pin2_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin2_t::enable) ;}
    inline  auto pin2_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin2_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin3_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin3_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin3_t::disable) ;}
    inline  void pin3_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin3_t::enable) ;}
    inline  auto pin3_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin3_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin4_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin4_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin4_t::disable) ;}
    inline  void pin4_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin4_t::enable) ;}
    inline  auto pin4_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin4_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin5_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin5_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin5_t::disable) ;}
    inline  void pin5_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin5_t::enable) ;}
    inline  auto pin5_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin5_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin6_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin6_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin6_t::disable) ;}
    inline  void pin6_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin6_t::enable) ;}
    inline  auto pin6_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin6_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin7_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin7_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin7_t::disable) ;}
    inline  void pin7_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin7_t::enable) ;}
    inline  auto pin7_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin7_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin8_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin8_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin8_t::disable) ;}
    inline  void pin8_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin8_t::enable) ;}
    inline  auto pin8_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin8_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin9_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin9_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin9_t::disable) ;}
    inline  void pin9_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin9_t::enable) ;}
    inline  auto pin9_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin9_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin10_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin10_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin10_t::disable) ;}
    inline  void pin10_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin10_t::enable) ;}
    inline  auto pin10_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin10_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin11_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin11_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin11_t::disable) ;}
    inline  void pin11_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin11_t::enable) ;}
    inline  auto pin11_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin11_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin12_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin12_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin12_t::disable) ;}
    inline  void pin12_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin12_t::enable) ;}
    inline  auto pin12_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin12_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin13_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin13_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin13_t::disable) ;}
    inline  void pin13_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin13_t::enable) ;}
    inline  auto pin13_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin13_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin14_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin14_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin14_t::disable) ;}
    inline  void pin14_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin14_t::enable) ;}
    inline  auto pin14_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin14_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pin15_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pin15_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin15_t::disable) ;}
    inline  void pin15_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pin15_t::enable) ;}
    inline  auto pin15_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin15_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::pvd_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void pvd_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pvd_t::disable) ;}
    inline  void pvd_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::pvd_t::enable) ;}
    inline  auto pvd_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pvd_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::rtc_alarm_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void rtc_alarm_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_alarm_t::disable) ;}
    inline  void rtc_alarm_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_alarm_t::enable) ;}
    inline  auto rtc_alarm_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::rtc_alarm_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::usb_otg_fs_wakeup_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void usb_otg_fs_wakeup_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::usb_otg_fs_wakeup_t::disable) ;}
    inline  void usb_otg_fs_wakeup_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::usb_otg_fs_wakeup_t::enable) ;}
    inline  auto usb_otg_fs_wakeup_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::usb_otg_fs_wakeup_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::ethernet_wakeup_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void ethernet_wakeup_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::ethernet_wakeup_t::disable) ;}
    inline  void ethernet_wakeup_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::ethernet_wakeup_t::enable) ;}
    inline  auto ethernet_wakeup_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::ethernet_wakeup_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::usb_otg_hs_wakeup_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void usb_otg_hs_wakeup_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::usb_otg_hs_wakeup_t::disable) ;}
    inline  void usb_otg_hs_wakeup_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::usb_otg_hs_wakeup_t::enable) ;}
    inline  auto usb_otg_hs_wakeup_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::usb_otg_hs_wakeup_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::rtc_tamper_time_stamp_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void rtc_tamper_time_stamp_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_tamper_time_stamp_t::disable) ;}
    inline  void rtc_tamper_time_stamp_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_tamper_time_stamp_t::enable) ;}
    inline  auto rtc_tamper_time_stamp_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::rtc_tamper_time_stamp_t>();}

    inline  void rising_trigger(const rising_trigger_selection_t::rtc_wakeup_t::enum_t val){  rising_trigger_selection.rmw(val) ;}
    inline  void rtc_wakeup_rising_trigger_disable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_wakeup_t::disable) ;}
    inline  void rtc_wakeup_rising_trigger_enable() {  rising_trigger_selection.rmw( rising_trigger_selection_t::rtc_wakeup_t::enable) ;}
    inline  auto rtc_wakeup_rising_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::rtc_wakeup_t>();}

    struct falling_trigger_selection_t : public read_write_32_t
      	{
      	    struct pin0_t  { enum enum_t{ offset=0, mask=1, disable=0, enable };};
      	    struct pin1_t  { enum enum_t{ offset=1, mask=1, disable=0, enable };};
      	    struct pin2_t  { enum enum_t{ offset=2, mask=1, disable=0, enable };};
      	    struct pin3_t  { enum enum_t{ offset=3, mask=1, disable=0, enable };};
      	    struct pin4_t  { enum enum_t{ offset=4, mask=1, disable=0, enable };};
      	    struct pin5_t  { enum enum_t{ offset=5, mask=1, disable=0, enable };};
      	    struct pin6_t  { enum enum_t{ offset=6, mask=1, disable=0, enable };};
      	    struct pin7_t  { enum enum_t{ offset=7, mask=1, disable=0, enable };};
      	    struct pin8_t  { enum enum_t{ offset=8, mask=1, disable=0, enable };};
      	    struct pin9_t  { enum enum_t{ offset=9, mask=1, disable=0, enable };};
      	    struct pin10_t { enum enum_t{ offset=10,mask=1, disable=0, enable };};
      	    struct pin11_t { enum enum_t{ offset=11,mask=1, disable=0, enable };};
      	    struct pin12_t { enum enum_t{ offset=12,mask=1, disable=0, enable };};
      	    struct pin13_t { enum enum_t{ offset=13,mask=1, disable=0, enable };};
      	    struct pin14_t { enum enum_t{ offset=14,mask=1, disable=0, enable };};
      	    struct pin15_t { enum enum_t{ offset=15,mask=1, disable=0, enable };};
      	    struct pvd_t         { enum enum_t{ offset=16,mask=1, disable=0, enable };};
      	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, disable=0, enable };};
      	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, disable=0, enable };};
      	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, disable=0, enable };};
      	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, disable=0, enable };};
      	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, disable=0, enable };};
      	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, disable=0, enable };};
      	};

        inline  void falling_trigger(const falling_trigger_selection_t::pin0_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin0_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin0_t::disable) ;}
        inline  void pin0_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin0_t::enable) ;}
        inline  auto pin0_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin0_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin1_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin1_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin1_t::disable) ;}
        inline  void pin1_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin1_t::enable) ;}
        inline  auto pin1_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin1_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin2_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin2_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin2_t::disable) ;}
        inline  void pin2_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin2_t::enable) ;}
        inline  auto pin2_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin2_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin3_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin3_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin3_t::disable) ;}
        inline  void pin3_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin3_t::enable) ;}
        inline  auto pin3_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin3_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin4_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin4_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin4_t::disable) ;}
        inline  void pin4_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin4_t::enable) ;}
        inline  auto pin4_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin4_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin5_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin5_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin5_t::disable) ;}
        inline  void pin5_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin5_t::enable) ;}
        inline  auto pin5_falling_trigger()const {  return rising_trigger_selection.rd<rising_trigger_selection_t::pin5_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin6_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin6_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin6_t::disable) ;}
        inline  void pin6_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin6_t::enable) ;}
        inline  auto pin6_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin6_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin7_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin7_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin7_t::disable) ;}
        inline  void pin7_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin7_t::enable) ;}
        inline  auto pin7_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin7_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin8_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin8_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin8_t::disable) ;}
        inline  void pin8_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin8_t::enable) ;}
        inline  auto pin8_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin8_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin9_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin9_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin9_t::disable) ;}
        inline  void pin9_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin9_t::enable) ;}
        inline  auto pin9_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin9_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin10_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin10_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin10_t::disable) ;}
        inline  void pin10_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin10_t::enable) ;}
        inline  auto pin10_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin10_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin11_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin11_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin11_t::disable) ;}
        inline  void pin11_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin11_t::enable) ;}
        inline  auto pin11_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin11_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin12_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin12_t::disable) ;}
        inline  void pin12_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin12_t::enable) ;}
        inline  auto pin12_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin12_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin13_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin13_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin13_t::disable) ;}
        inline  void pin13_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin13_t::enable) ;}
        inline  auto pin13_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin13_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin14_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin14_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin14_t::disable) ;}
        inline  void pin14_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin14_t::enable) ;}
        inline  auto pin14_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin14_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pin15_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pin15_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin15_t::disable) ;}
        inline  void pin15_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pin15_t::enable) ;}
        inline  auto pin15_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pin15_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::pvd_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void pvd_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pvd_t::disable) ;}
        inline  void pvd_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::pvd_t::enable) ;}
        inline  auto pvd_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::pvd_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::rtc_alarm_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void rtc_alarm_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_alarm_t::disable) ;}
        inline  void rtc_alarm_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_alarm_t::enable) ;}
        inline  auto rtc_alarm_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::rtc_alarm_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::usb_otg_fs_wakeup_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void usb_otg_fs_wakeup_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::usb_otg_fs_wakeup_t::disable) ;}
        inline  void usb_otg_fs_wakeup_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::usb_otg_fs_wakeup_t::enable) ;}
        inline  auto usb_otg_fs_wakeup_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::usb_otg_fs_wakeup_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::ethernet_wakeup_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void ethernet_wakeup_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::ethernet_wakeup_t::disable) ;}
        inline  void ethernet_wakeup_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::ethernet_wakeup_t::enable) ;}
        inline  auto ethernet_wakeup_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::ethernet_wakeup_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::usb_otg_hs_wakeup_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void usb_otg_hs_wakeup_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::usb_otg_hs_wakeup_t::disable) ;}
        inline  void usb_otg_hs_wakeup_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::usb_otg_hs_wakeup_t::enable) ;}
        inline  auto usb_otg_hs_wakeup_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::usb_otg_hs_wakeup_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::rtc_tamper_time_stamp_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void rtc_tamper_time_stamp_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_tamper_time_stamp_t::disable) ;}
        inline  void rtc_tamper_time_stamp_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_tamper_time_stamp_t::enable) ;}
        inline  auto rtc_tamper_time_stamp_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::rtc_tamper_time_stamp_t>();}

        inline  void falling_trigger(const falling_trigger_selection_t::rtc_wakeup_t::enum_t val){  falling_trigger_selection.rmw(val) ;}
        inline  void rtc_wakeup_falling_trigger_disable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_wakeup_t::disable) ;}
        inline  void rtc_wakeup_falling_trigger_enable() {  falling_trigger_selection.rmw( falling_trigger_selection_t::rtc_wakeup_t::enable) ;}
        inline  auto rtc_wakeup_falling_trigger()const {  return falling_trigger_selection.rd<falling_trigger_selection_t::rtc_wakeup_t>();}

        struct software_interrupt_event_t : public read_write_32_t
          	{
          	    struct pin0_t  { enum enum_t{ offset=0, mask=1, perform=1 };};
          	    struct pin1_t  { enum enum_t{ offset=1, mask=1, perform=1 };};
          	    struct pin2_t  { enum enum_t{ offset=2, mask=1, perform=1 };};
          	    struct pin3_t  { enum enum_t{ offset=3, mask=1, perform=1 };};
          	    struct pin4_t  { enum enum_t{ offset=4, mask=1, perform=1 };};
          	    struct pin5_t  { enum enum_t{ offset=5, mask=1, perform=1 };};
          	    struct pin6_t  { enum enum_t{ offset=6, mask=1, perform=1 };};
          	    struct pin7_t  { enum enum_t{ offset=7, mask=1, perform=1 };};
          	    struct pin8_t  { enum enum_t{ offset=8, mask=1, perform=1 };};
          	    struct pin9_t  { enum enum_t{ offset=9, mask=1, perform=1 };};
          	    struct pin10_t { enum enum_t{ offset=10,mask=1, perform=1 };};
          	    struct pin11_t { enum enum_t{ offset=11,mask=1, perform=1 };};
          	    struct pin12_t { enum enum_t{ offset=12,mask=1, perform=1 };};
          	    struct pin13_t { enum enum_t{ offset=13,mask=1, perform=1 };};
          	    struct pin14_t { enum enum_t{ offset=14,mask=1, perform=1 };};
          	    struct pin15_t { enum enum_t{ offset=15,mask=1, perform=1 };};
          	    struct pvd_t         { enum enum_t{ offset=16,mask=1, perform=1 };};
          	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, perform=1 };};
          	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, perform=1 };};
          	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, perform=1 };};
          	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, perform=1 };};
          	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, perform=1 };};
          	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, perform=1 };};
          	};

            inline  void pin0_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin0_t::perform) ;}
            inline  void pin1_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin1_t::perform) ;}
            inline  void pin2_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin2_t::perform) ;}
            inline  void pin3_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin3_t::perform) ;}
            inline  void pin4_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin4_t::perform) ;}
            inline  void pin5_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin5_t::perform) ;}
            inline  void pin6_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin6_t::perform) ;}
            inline  void pin7_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin7_t::perform) ;}
            inline  void pin8_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin8_t::perform) ;}
            inline  void pin9_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::pin9_t::perform) ;}
            inline  void pin10_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin10_t::perform) ;}
            inline  void pin11_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin11_t::perform) ;}
            inline  void pin12_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin12_t::perform) ;}
            inline  void pin13_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin13_t::perform) ;}
            inline  void pin14_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin14_t::perform) ;}
            inline  void pin15_software_interrupt_event_generate(){ software_interrupt_event.rmw(software_interrupt_event_t::pin15_t::perform) ;}
            inline  void pvd_software_interrupt_event_generate()              {  software_interrupt_event.rmw(software_interrupt_event_t::pvd_t::perform) ;}
            inline  void rtc_alarm_software_interrupt_event_generate()        {  software_interrupt_event.rmw(software_interrupt_event_t::rtc_alarm_t::perform) ;}
            inline  void usb_otg_fs_wakeup_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::usb_otg_fs_wakeup_t::perform) ;}
            inline  void ethernet_wakeup_software_interrupt_event_generate()  {  software_interrupt_event.rmw(software_interrupt_event_t::ethernet_wakeup_t::perform) ;}
            inline  void usb_otg_hs_wakeup_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::usb_otg_hs_wakeup_t::perform) ;}
            inline  void rtc_tamper_time_stamp_software_interrupt_event_generate(){  software_interrupt_event.rmw(software_interrupt_event_t::rtc_tamper_time_stamp_t::perform) ;}
            inline  void rtc_wakeup_software_interrupt_event_generate()       {  software_interrupt_event.rmw(software_interrupt_event_t::rtc_wakeup_t::perform) ;}

            struct pending_t : public read_write_32_t
              	{
              	    struct pin0_t  { enum enum_t{ offset=0, mask=1, not_occured=0, occured=1 };};
              	    struct pin1_t  { enum enum_t{ offset=1, mask=1, not_occured=0, occured=1 };};
              	    struct pin2_t  { enum enum_t{ offset=2, mask=1, not_occured=0, occured=1 };};
              	    struct pin3_t  { enum enum_t{ offset=3, mask=1, not_occured=0, occured=1 };};
              	    struct pin4_t  { enum enum_t{ offset=4, mask=1, not_occured=0, occured=1 };};
              	    struct pin5_t  { enum enum_t{ offset=5, mask=1, not_occured=0, occured=1 };};
              	    struct pin6_t  { enum enum_t{ offset=6, mask=1, not_occured=0, occured=1 };};
              	    struct pin7_t  { enum enum_t{ offset=7, mask=1, not_occured=0, occured=1 };};
              	    struct pin8_t  { enum enum_t{ offset=8, mask=1, not_occured=0, occured=1 };};
              	    struct pin9_t  { enum enum_t{ offset=9, mask=1, not_occured=0, occured=1 };};
              	    struct pin10_t { enum enum_t{ offset=10,mask=1, not_occured=0, occured=1 };};
              	    struct pin11_t { enum enum_t{ offset=11,mask=1, not_occured=0, occured=1 };};
              	    struct pin12_t { enum enum_t{ offset=12,mask=1, not_occured=0, occured=1 };};
              	    struct pin13_t { enum enum_t{ offset=13,mask=1, not_occured=0, occured=1 };};
              	    struct pin14_t { enum enum_t{ offset=14,mask=1, not_occured=0, occured=1 };};
              	    struct pin15_t { enum enum_t{ offset=15,mask=1, not_occured=0, occured=1 };};
              	    struct pvd_t         { enum enum_t{ offset=16,mask=1, not_occured=0, occured=1 };};
              	    struct rtc_alarm_t   { enum enum_t{ offset=17,mask=1, not_occured=0, occured=1 };};
              	    struct usb_otg_fs_wakeup_t     { enum enum_t{ offset=18,mask=1, not_occured=0, occured=1 };};
              	    struct ethernet_wakeup_t       { enum enum_t{ offset=19,mask=1, not_occured=0, occured=1 };};
              	    struct usb_otg_hs_wakeup_t     { enum enum_t{ offset=20,mask=1, not_occured=0, occured=1 };};
              	    struct rtc_tamper_time_stamp_t { enum enum_t{ offset=21,mask=1, not_occured=0, occured=1 };};
              	    struct rtc_wakeup_t            { enum enum_t{ offset=22,mask=1, not_occured=0, occured=1 };};
              	};

                inline  auto pin0_pending()const {  return pending.rd<pending_t::pin0_t>();}
                inline  void pin0_pending_clear(){  pending.rmw(pending_t::pin0_t::occured) ;}

                inline  auto pin1_pending()const {  return pending.rd<pending_t::pin1_t>();}
                inline  void pin1_pending_clear(){  pending.rmw(pending_t::pin1_t::occured) ;}

                inline  auto pin2_pending()const {  return pending.rd<pending_t::pin2_t>();}
                inline  void pin2_pending_clear(){  pending.rmw(pending_t::pin2_t::occured) ;}

                inline  auto pin3_pending()const {  return pending.rd<pending_t::pin3_t>();}
                inline  void pin3_pending_clear(){  pending.rmw(pending_t::pin3_t::occured) ;}

                inline  auto pin4_pending()const {  return pending.rd<pending_t::pin4_t>();}
                inline  void pin4_pending_clear(){  pending.rmw(pending_t::pin4_t::occured) ;}

                inline  auto pin5_pending()const {  return pending.rd<pending_t::pin5_t>();}
                inline  void pin5_pending_clear(){  pending.rmw(pending_t::pin5_t::occured) ;}

                inline  auto pin6_pending()const {  return pending.rd<pending_t::pin6_t>();}
                inline  void pin6_pending_clear(){  pending.rmw(pending_t::pin6_t::occured) ;}

                inline  auto pin7_pending()const {  return pending.rd<pending_t::pin7_t>();}
                inline  void pin7_pending_clear(){  pending.rmw(pending_t::pin7_t::occured) ;}

                inline  auto pin8_pending()const {  return pending.rd<pending_t::pin8_t>();}
                inline  void pin8_pending_clear(){  pending.rmw(pending_t::pin8_t::occured) ;}

                inline  auto pin9_pending()const {  return pending.rd<pending_t::pin9_t>();}
                inline  void pin9_pending_clear(){  pending.rmw(pending_t::pin9_t::occured) ;}

                inline  auto pin10_pending()const {  return pending.rd<pending_t::pin10_t>();}
                inline  void pin10_pending_clear(){  pending.rmw(pending_t::pin10_t::occured) ;}

                inline  auto pin11_pending()const {  return pending.rd<pending_t::pin11_t>();}
                inline  void pin11_pending_clear(){  pending.rmw(pending_t::pin11_t::occured) ;}

                inline  auto pin12_pending()const {  return pending.rd<pending_t::pin12_t>();}
                inline  void pin12_pending_clear(){  pending.rmw(pending_t::pin12_t::occured) ;}

                inline  auto pin13_pending()const {  return pending.rd<pending_t::pin13_t>();}
                inline  void pin13_pending_clear(){  pending.rmw(pending_t::pin13_t::occured) ;}

                inline  auto pin14_pending()const {  return pending.rd<pending_t::pin14_t>();}
                inline  void pin14_pending_clear(){  pending.rmw(pending_t::pin14_t::occured) ;}

                inline  auto pin15_pending()const {  return pending.rd<pending_t::pin15_t>();}
                inline  void pin15_pending_clear(){  pending.rmw(pending_t::pin15_t::occured) ;}

                inline  auto pvd_pending()const {  return pending.rd<pending_t::pvd_t>();}
                inline  void pvd_pending_clear()              {  pending.rmw(pending_t::pvd_t::occured) ;}

                inline  auto rtc_alarm_pending()const {  return pending.rd<pending_t::rtc_alarm_t>();}
                inline  void rtc_alarm_pending_clear()        {  pending.rmw(pending_t::rtc_alarm_t::occured) ;}

                inline  auto usb_otg_fs_wakeup_pending()const {  return pending.rd<pending_t::usb_otg_fs_wakeup_t>();}
                inline  void usb_otg_fs_wakeup_pending_clear(){  pending.rmw(pending_t::usb_otg_fs_wakeup_t::occured) ;}

                inline  auto ethernet_wakeup_pending()const {  return pending.rd<pending_t::ethernet_wakeup_t>();}
                inline  void ethernet_wakeup_pending_clear()  {  pending.rmw(pending_t::ethernet_wakeup_t::occured) ;}

                inline  auto usb_otg_hs_wakeup_pending()const {  return pending.rd<pending_t::usb_otg_hs_wakeup_t>();}
                inline  void usb_otg_hs_wakeup_pending_clear(){  pending.rmw(pending_t::usb_otg_hs_wakeup_t::occured) ;}

                inline  auto rtc_tamper_time_stamp_pending()const {  return pending.rd<pending_t::rtc_tamper_time_stamp_t>();}
                inline  void rtc_tamper_time_stamp_pending_clear(){  pending.rmw(pending_t::rtc_tamper_time_stamp_t::occured) ;}

                inline  auto rtc_wakeup_pending()const {  return pending.rd<pending_t::rtc_wakeup_t>();}
                inline  void rtc_wakeup_pending_clear()       {  pending.rmw(pending_t::rtc_wakeup_t::occured) ;}


  interrupt_mask_t            interrupt_mask;            // IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
  event_mask_t                event_mask;                // EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
  rising_trigger_selection_t  rising_trigger_selection;  // RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
  falling_trigger_selection_t falling_trigger_selection; // FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
  software_interrupt_event_t  software_interrupt_event;  // SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
  pending_t                   pending;                   // PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */

};

static exti_t& exti = *((exti_t *) exti_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __EXTI++_H__ */
