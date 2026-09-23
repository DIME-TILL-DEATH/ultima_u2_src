/*
 * otgfs++.h
 *
 *  Created on: 30 янв. 2017 г.
 *      Author: klen
 */

#ifndef __OTGFS++_H__
#define __OTGFS++_H__

#include "types++.h"

namespace stm32f4
{

struct otgfs_device_t
{
  struct control_status_t : public read_write_32_t
  {
  } ;

  struct interrupt_t : public read_write_32_t
  {
  } ;

  struct ahb_configuration_t : public read_write_32_t
  {
  } ;

  struct usb_configuration_t : public read_write_32_t
  {
  } ;

  struct reset_t : public read_write_32_t
  {
  } ;

  struct core_interrupt_t : public read_write_32_t
  {
  } ;

  struct interrupt_mask_t : public read_write_32_t
  {
  } ;

  struct receive_status_debug_read_t : public read_write_32_t
  {
  } ;

  struct status_read_and_pop_t : public read_write_32_t
  {
  } ;

  struct endpoint_0_transmit_fifo_size_t : public read_write_32_t
  {
  } ;

  struct general_core_configuration_t : public read_write_32_t
  {
  } ;

  struct in_endpoint_transmit_fifo_size_t : public read_write_32_t
  {
  } ;

  //------------------


  struct configuration_t : public read_write_32_t
  {
  } ;

  struct control_t : public read_write_32_t
  {
  } ;

  struct status_t : public read_write_32_t
  {
  } ;

  struct in_endpoint_common_interrupt_mask_t : public read_write_32_t
  {
  } ;

  struct out_endpoint_common_interrupt_mask_t : public read_write_32_t
  {
  } ;

  struct all_endpoints_interrupt_t : public read_write_32_t
  {
  } ;

  struct all_endpoints_interrupt_mask_t : public read_write_32_t
  {

  } ;

  control_status_t                control_status ;
  interrupt_t                     interrupt ;
  ahb_configuration_t             ahb_configuration ;
  usb_configuration_t             usb_configuration ;
  reset_t                         reset ;
  core_interrupt_t                core_interrupt ;
  interrupt_mask_t                interrupt_mask ;
  receive_status_debug_read_t     receive_status_debug_read;
  status_read_and_pop_t           status_read_and_pop;
  uint16_t : 16 ;
  volatile uint16_t               receive_fifo_size;
  endpoint_0_transmit_fifo_size_t endpoint_0_transmit_fifo_size ;
  uint32_t : 32 ;
  general_core_configuration_t    general_core_configuration ;
  volatile uint32_t               core_id_register ;
  in_endpoint_transmit_fifo_size_t device_in_endpoint_transmit_fifo_1_size ;
  in_endpoint_transmit_fifo_size_t device_in_endpoint_transmit_fifo_2_size ;
  in_endpoint_transmit_fifo_size_t device_in_endpoint_transmit_fifo_3_size ;

  uint32_t reserve[455];

  configuration_t configuration ;
  control_t control ;
  status_t status ;
  in_endpoint_common_interrupt_mask_t in_endpoint_common_interrupt_mask ;
  out_endpoint_common_interrupt_mask_t out_endpoint_common_interrupt_mask ;
  all_endpoints_interrupt_t all_endpoints_interrupt ;
  uint16_t : 16 ;
  volatile uint16_t           device_vbus_discharge_time ;
  uint16_t : 16 ;
  volatile uint16_t           device_vbus_pulsing_time ;

  inline void clock_enable() {  rcc.otgfs_enable() ; }
  inline void clock_disable(){  rcc.otgfs_disable(); }
  inline void clock_reset()  {  rcc.otgfs_reset() ; }

} ;

}

using namespace stm32f4 ;

#endif /* __OTGFS++_H__ */
