/*
 * can++.h
 *
 *  Created on: 07 сен. 2017 г.
 *      Author: klen
 */

#ifndef __CAN++_H__
#define __CAN++_H__

#include "types++.h"

// TODO доделать до конца

namespace stm32f4
{

struct can_t
  {

  struct tx_mailbox_t
    {
      volatile uint32_t identifier;  /*!< CAN TX mailbox identifier register */
      volatile uint32_t data_length_control_and_time_stamp; /*!< CAN mailbox data length control and time stamp register */
      volatile uint32_t data_low; /*!< CAN mailbox data low register */
      volatile uint32_t data_high; /*!< CAN mailbox data high register */
    };

  struct fifo_mailbox_t
    {
      volatile uint32_t identifier;  /*!< CAN receive FIFO mailbox identifier register */
      volatile uint32_t data_length_control_and_time_stamp; /*!< CAN receive FIFO mailbox data length control and time stamp register */
      volatile uint32_t data_low; /*!< CAN receive FIFO mailbox data low register */
      volatile uint32_t data_high; /*!< CAN receive FIFO mailbox data high register */
    } ;

  struct filter_t
    {
      volatile uint32_t bank_register1; /*!< CAN Filter bank register 1 */
      volatile uint32_t bank_register2; /*!< CAN Filter bank register 2 */
    } ;

  struct master_control_t : public read_write_32_t
  {
    struct initialization_request_t            { enum enum_t { offset=0,  mask=1, reset=0 ,  set } ; } ;
    struct sleep_mode_request_t                { enum enum_t { offset=1,  mask=1, reset=0 ,  set } ; } ;
    struct tarnsmit_fifo_priority_t            { enum enum_t { offset=2,  mask=1, by_id_message=0 ,  by_request_order } ; } ;
    struct receive_fifo_locked_mode_t          { enum enum_t { offset=3,  mask=1, not_locked=0 ,  locked_against_overrun } ; } ;
    struct no_automatic_retransmission_t       { enum enum_t { offset=4,  mask=1, disable=0 ,  enable } ; } ;
    struct automatic_wakeup_mode_t             { enum enum_t { offset=5,  mask=1, left_on_software=0 ,  left_automatically_by_hardware } ; } ;
    struct automatic_bus_off_management_t      { enum enum_t { offset=6,  mask=1, left_on_software=0 ,  left_automatically_by_hardware } ; } ;
    struct time_triggered_communication_mode_t { enum enum_t { offset=7,  mask=1, disable=0 ,  enable } ; } ;
    struct software_master_reset_t             { enum enum_t { offset=15, mask=1, unactive=0, activated,  } ; } ;
    struct debug_freeze_t                      { enum enum_t { offset=16, mask=1, disable=0 ,  enable } ; } ;
  } ;

    inline  void initialization_request( const master_control_t::initialization_request_t::enum_t val){  master_control.rmw(val) ;}
    inline  void initialization_request_set()   {  master_control.rmw( master_control_t::initialization_request_t::set) ;}
    inline  void initialization_request_reset() {  master_control.rmw( master_control_t::initialization_request_t::reset) ;}
    inline  auto initialization_request() const {  return master_control.rd<master_control_t::initialization_request_t> ();}

    inline  void sleep_mode_request( const master_control_t::sleep_mode_request_t::enum_t val){  master_control.rmw(val) ;}
    inline  void sleep_mode_request_set()   {  master_control.rmw( master_control_t::sleep_mode_request_t::set) ;}
    inline  void sleep_mode_request_reset()   {  master_control.rmw( master_control_t::sleep_mode_request_t::reset) ;}
    inline  auto sleep_mode_request() const {  return master_control.rd<master_control_t::sleep_mode_request_t> ();}

    inline  void tarnsmit_fifo_priority( const master_control_t::tarnsmit_fifo_priority_t::enum_t val){  master_control.rmw(val) ;}
    inline  void tarnsmit_fifo_priority_by_id_message()   {  master_control.rmw( master_control_t::tarnsmit_fifo_priority_t::by_id_message) ;}
    inline  void tarnsmit_fifo_priority_by_request_order(){  master_control.rmw( master_control_t::tarnsmit_fifo_priority_t::by_request_order) ;}
    inline  auto tarnsmit_fifo_priority() const {  return master_control.rd<master_control_t::tarnsmit_fifo_priority_t> ();}

    inline  void receive_fifo_locked_mode( const master_control_t::receive_fifo_locked_mode_t::enum_t val){  master_control.rmw(val) ;}
    inline  void receive_fifo_locked_mode_not_locked()   {  master_control.rmw( master_control_t::receive_fifo_locked_mode_t::not_locked) ;}
    inline  void receive_fifo_locked_mode_locked_against_overrun(){  master_control.rmw( master_control_t::receive_fifo_locked_mode_t::locked_against_overrun) ;}
    inline  auto receive_fifo_locked_mode() const {  return master_control.rd<master_control_t::receive_fifo_locked_mode_t> ();}


    inline  void no_automatic_retransmission( const master_control_t::no_automatic_retransmission_t::enum_t val){  master_control.rmw(val) ;}
    inline  void no_automatic_retransmission_enable() {  master_control.rmw( master_control_t::no_automatic_retransmission_t::enable) ;}
    inline  void no_automatic_retransmission_disable(){  master_control.rmw( master_control_t::no_automatic_retransmission_t::disable) ;}
    inline  auto no_automatic_retransmission() const {  return master_control.rd<master_control_t::no_automatic_retransmission_t>();}

    inline  void automatic_wakeup_mode( const master_control_t::automatic_wakeup_mode_t::enum_t val){  master_control.rmw(val) ;}
    inline  void automatic_wakeup_mode_left_on_software() {  master_control.rmw( master_control_t::automatic_wakeup_mode_t::left_on_software) ;}
    inline  void automatic_wakeup_mode_left_automatically_by_hardware(){  master_control.rmw( master_control_t::automatic_wakeup_mode_t::left_automatically_by_hardware) ;}
    inline  auto automatic_wakeup_mode() const {  return master_control.rd<master_control_t::automatic_wakeup_mode_t> ();}

    inline  void automatic_bus_off_management( const master_control_t::automatic_bus_off_management_t::enum_t val){  master_control.rmw(val) ;}
    inline  void automatic_bus_off_management_left_on_software() {  master_control.rmw( master_control_t::automatic_bus_off_management_t::left_on_software) ;}
    inline  void automatic_bus_off_management_left_automatically_by_hardware(){  master_control.rmw( master_control_t::automatic_bus_off_management_t::left_automatically_by_hardware) ;}
    inline  auto automatic_bus_off_management() const {  return master_control.rd<master_control_t::automatic_bus_off_management_t> ();}

    inline  void time_triggered_communication_mode( const master_control_t::time_triggered_communication_mode_t::enum_t val){  master_control.rmw(val) ;}
    inline  void time_triggered_communication_mode_enable() {  master_control.rmw( master_control_t::time_triggered_communication_mode_t::enable) ;}
    inline  void time_triggered_communication_mode_disable(){  master_control.rmw( master_control_t::time_triggered_communication_mode_t::disable) ;}
    inline  auto time_triggered_communication_mode() const {  return master_control.rd<master_control_t::time_triggered_communication_mode_t> ();}

    inline  void software_master_reset_activate() {  master_control.rmw( master_control_t::software_master_reset_t::activated) ;}
    inline  auto software_master_reset() const {  return master_control.rd<master_control_t::software_master_reset_t> ();}

    inline  void debug_freeze( const master_control_t::debug_freeze_t::enum_t val){  master_control.rmw(val) ;}
    inline  void debug_freeze_enable() {  master_control.rmw( master_control_t::debug_freeze_t::enable) ;}
    inline  void debug_freeze_disable(){  master_control.rmw( master_control_t::debug_freeze_t::disable) ;}
    inline  auto debug_freeze() const {  return master_control.rd<master_control_t::debug_freeze_t> ();}

#if 0

  __reg_rw_def__ ( master_status_t )
 {
   __inline__ bit_state_t initialization_acknowledge() const {NRO RD(_initialization_acknowledge);}

   __inline__ bit_state_t sleep_acknowledge() const {NRO RD(_sleep_acknowledge);}

   __inline__ bit_state_t error_interrupt() const {NRO RD(_error_interrupt);}
   __inline__ void error_interrupt_clear() {NRO RMW(_error_interrupt,bs_high);}

   __inline__ bit_state_t wakeup_interrupt() const {NRO RD(_wakeup_interrupt);}
   __inline__ void wakeup_interrupt_clear() {NRO RMW(_wakeup_interrupt,bs_high);}

   __inline__ bit_state_t sleep_acknowledge_interrupt() const {NRO RD(_sleep_acknowledge_interrupt);}
   __inline__ void sleep_acknowledge_interrupt_clear() {NRO RMW(_sleep_acknowledge_interrupt,bs_high);}

   __inline__ bit_state_t transmit_mode() const {NRO RD(_transmit_mode);}

   __inline__ bit_state_t receive_mode() const {NRO RD(_receive_mode);}

   __inline__ bit_state_t last_sample_point() const {NRO RD(_last_sample_point);}

   __inline__ bit_state_t rx_signal() const {NRO RD(_rx_signal);}


   volatile bit_state_t _initialization_acknowledge : 1 ; //0
   volatile bit_state_t _sleep_acknowledge : 1 ; //1
   volatile bit_state_t _error_interrupt      : 1 ; //2
   volatile bit_state_t _wakeup_interrupt     : 1 ; //3
   volatile bit_state_t _sleep_acknowledge_interrupt  : 1 ; //4
   uint32_t  : 3 ; // // 5..7
   volatile bit_state_t _transmit_mode   : 1 ; //8
   volatile bit_state_t _receive_mode    : 1 ; //9
   volatile bit_state_t _last_sample_point : 1 ; //10
   volatile bit_state_t _rx_signal       : 1 ; //11
   uint32_t  : 20 ; // 12..31
 } __reg_attr__ ;

 __reg_rw_def__ ( transmit_status_t )
 {

   __inline__ bit_state_t request_completed_mailbox0() const {NRO RD(_request_completed_mailbox0);}
   __inline__ void request_completed_mailbox0_clear() {NRO RMW(_request_completed_mailbox0,bs_high);}

   __inline__ bit_state_t transmission_ok_of_mailbox0() const {NRO RD(_transmission_ok_of_mailbox0);}
   __inline__ void transmission_ok_of_mailbox0_clear() {NRO RMW(_transmission_ok_of_mailbox0,bs_high);}

   __inline__ bit_state_t arbitration_lost_for_mailbox0() const {NRO RD(_arbitration_lost_for_mailbox0);}
   __inline__ void arbitration_lost_for_mailbox0_clear() {NRO RMW(_arbitration_lost_for_mailbox0,bs_high);}

   __inline__ bit_state_t transmission_error_of_mailbox0() const {NRO RD(_transmission_error_of_mailbox0);}
   __inline__ void transmission_error_of_mailbox0_clear() {NRO RMW(_transmission_error_of_mailbox0,bs_high);}

   __inline__ perform_activated_t abort_request_for_mailbox0() const {NRO RD(_abort_request_for_mailbox0);}
   __inline__ void abort_request_for_mailbox0_perform()  {NRO RMW(_abort_request_for_mailbox0,pa_activated);}


   __inline__ bit_state_t request_completed_mailbox1() const {NRO RD(_request_completed_mailbox1);}
   __inline__ void request_completed_mailbox1_clear() {NRO RMW(_request_completed_mailbox1,bs_high);}

   __inline__ bit_state_t transmission_ok_of_mailbox1() const {NRO RD(_transmission_ok_of_mailbox1);}
   __inline__ void transmission_ok_of_mailbox1_clear() {NRO RMW(_transmission_ok_of_mailbox1,bs_high);}

   __inline__ bit_state_t arbitration_lost_for_mailbox1() const {NRO RD(_arbitration_lost_for_mailbox1);}
   __inline__ void arbitration_lost_for_mailbox1_clear() {NRO RMW(_arbitration_lost_for_mailbox1,bs_high);}

   __inline__ bit_state_t transmission_error_of_mailbox1() const {NRO RD(_transmission_error_of_mailbox1);}
   __inline__ void transmission_error_of_mailbox1_clear() {NRO RMW(_transmission_error_of_mailbox1,bs_high);}

   __inline__ perform_activated_t abort_request_for_mailbox1() const {NRO RD(_abort_request_for_mailbox1);}
   __inline__ void abort_request_for_mailbox1_perform()  {NRO RMW(_abort_request_for_mailbox1,pa_activated);}



  __inline__ bit_state_t request_completed_mailbox2() const {NRO RD(_request_completed_mailbox2);}
  __inline__ void request_completed_mailbox2_clear() {NRO RMW(_request_completed_mailbox2,bs_high);}

  __inline__ bit_state_t transmission_ok_of_mailbox2() const {NRO RD(_transmission_ok_of_mailbox2);}
  __inline__ void transmission_ok_of_mailbox2_clear() {NRO RMW(_transmission_ok_of_mailbox2,bs_high);}

  __inline__ bit_state_t arbitration_lost_for_mailbox2() const {NRO RD(_arbitration_lost_for_mailbox2);}
  __inline__ void arbitration_lost_for_mailbox2_clear() {NRO RMW(_arbitration_lost_for_mailbox2,bs_high);}

  __inline__ bit_state_t transmission_error_of_mailbox2() const {NRO RD(_transmission_error_of_mailbox2);}
  __inline__ void transmission_error_of_mailbox2_clear() {NRO RMW(_transmission_error_of_mailbox2,bs_high);}

  __inline__ perform_activated_t abort_request_for_mailbox2() const {NRO RD(_abort_request_for_mailbox2);}
  __inline__ void abort_request_for_mailbox2_perform()  {NRO RMW(_abort_request_for_mailbox2,pa_activated);}

  __inline__ uint8_t mailbox_code() const {NRO RD(_mailbox_code);}

  __inline__ bit_state_t transmit_mailbox_0_empty() const {NRO RD(_transmit_mailbox_0_empty);}

  __inline__ bit_state_t transmit_mailbox_1_empty() const {NRO RD(_transmit_mailbox_1_empty);}

  __inline__ bit_state_t transmit_mailbox_2_empty() const {NRO RD(_transmit_mailbox_2_empty);}

  __inline__ bit_state_t lowest_priority_flag_for_mailbox0() const {NRO RD(_lowest_priority_flag_for_mailbox0);}

  __inline__ bit_state_t lowest_priority_flag_for_mailbox1() const {NRO RD(_lowest_priority_flag_for_mailbox1);}

  __inline__ bit_state_t lowest_priority_flag_for_mailbox2() const {NRO RD(_lowest_priority_flag_for_mailbox2);}


  volatile bit_state_t _request_completed_mailbox0    : 1 ; //0
  volatile bit_state_t _transmission_ok_of_mailbox0   : 1 ; //1
  volatile bit_state_t _arbitration_lost_for_mailbox0 : 1 ; //2
  volatile bit_state_t _transmission_error_of_mailbox0: 1 ; //3
  uint32_t  : 3 ; // 4..6
  volatile perform_activated_t _abort_request_for_mailbox0    : 1 ; //7
  volatile bit_state_t _request_completed_mailbox1    : 1 ; //8
  volatile bit_state_t _transmission_ok_of_mailbox1   : 1 ; //9
  volatile bit_state_t _arbitration_lost_for_mailbox1 : 1 ; //10
  volatile bit_state_t _transmission_error_of_mailbox1: 1 ; //11
  uint32_t  : 3 ; // 12..14
  volatile perform_activated_t _abort_request_for_mailbox1    : 1 ; //15
  volatile bit_state_t _request_completed_mailbox2    : 1 ; //16
  volatile bit_state_t _transmission_ok_of_mailbox2   : 1 ; //17
  volatile bit_state_t _arbitration_lost_for_mailbox2 : 1 ; //18
  volatile bit_state_t _transmission_error_of_mailbox2: 1 ; //19
  uint32_t  : 3 ; // 20..22
  volatile perform_activated_t _abort_request_for_mailbox2    : 1 ; //23
  volatile uint32_t    _mailbox_code                  : 2 ; //24..25
  volatile bit_state_t _transmit_mailbox_0_empty      : 1 ; //26
  volatile bit_state_t _transmit_mailbox_1_empty      : 1 ; //27
  volatile bit_state_t _transmit_mailbox_2_empty      : 1 ; //28
  volatile bit_state_t _lowest_priority_flag_for_mailbox0 : 1 ; //29
  volatile bit_state_t _lowest_priority_flag_for_mailbox1 : 1 ; //30
  volatile bit_state_t _lowest_priority_flag_for_mailbox2 : 1 ; //31

 } __reg_attr__ ;

 __reg_rw_def__ ( receive_fifo_t )
 {
   __inline__ uint8_t messages_pending() const {NRO RD(_messages_pending);}

   __inline__ bit_state_t full() const {NRO RD(_full);}
   __inline__ void full_clear() {NRO RMW(_full,bs_high);}

   __inline__ bit_state_t overrun() const {NRO RD(_overrun);}
   __inline__ void overrun_clear() {NRO RMW(_overrun,bs_high);}

   __inline__ void release() {NRO RMW(_release,rlb_release);}

   volatile uint32_t  _messages_pending    : 2 ; //0..1
   uint32_t : 1 ; // 2
   volatile bit_state_t  _full    : 1 ; //3
   volatile bit_state_t  _overrun : 1 ; //4
   volatile release_bit_t  _release : 1 ; //5
   uint32_t : 26 ; // 6..31

 } __reg_attr__ ;

 __reg_rw_def__ ( interrupt_t )
 {

   __inline__ void transmit_mailbox_empty(const state_enable_t val) {NRO RMW(_transmit_mailbox_empty,val) ; }
   __inline__ state_enable_t transmit_mailbox_empty() const         {NRO RD (_transmit_mailbox_empty) ; }
   __inline__ void transmit_mailbox_empty_enable()                  {NRO RMW(_transmit_mailbox_empty,se_enable) ; }
   __inline__ void transmit_mailbox_empty_disable()                 {NRO RMW(_transmit_mailbox_empty,se_disable); }

   __inline__ void fifo_0_message_pending(const state_enable_t val) {NRO RMW(_fifo_0_message_pending,val) ; }
   __inline__ state_enable_t fifo_0_message_pending() const         {NRO RD (_fifo_0_message_pending) ; }
   __inline__ void fifo_0_message_pending_enable()                  {NRO RMW(_fifo_0_message_pending,se_enable) ; }
   __inline__ void fifo_0_message_pending_disable()                 {NRO RMW(_fifo_0_message_pending,se_disable); }

   __inline__ void fifo_0_full(const state_enable_t val) {NRO RMW(_fifo_0_full,val) ; }
   __inline__ state_enable_t fifo_0_full() const         {NRO RD (_fifo_0_full) ; }
   __inline__ void fifo_0_full_enable()                  {NRO RMW(_fifo_0_full,se_enable) ; }
   __inline__ void fifo_0_full_disable()                 {NRO RMW(_fifo_0_full,se_disable); }

   __inline__ void fifo_0_overrun(const state_enable_t val) {NRO RMW(_fifo_0_overrun,val) ; }
   __inline__ state_enable_t fifo_0_overrun() const         {NRO RD (_fifo_0_overrun) ; }
   __inline__ void fifo_0_overrun_enable()                  {NRO RMW(_fifo_0_overrun,se_enable) ; }
   __inline__ void fifo_0_overrun_disable()                 {NRO RMW(_fifo_0_overrun,se_disable); }

   __inline__ void fifo_1_message_pending(const state_enable_t val) {NRO RMW(_fifo_1_message_pending,val) ; }
   __inline__ state_enable_t fifo_1_message_pending() const         {NRO RD (_fifo_1_message_pending) ; }
   __inline__ void fifo_1_message_pending_enable()                  {NRO RMW(_fifo_1_message_pending,se_enable) ; }
   __inline__ void fifo_1_message_pending_disable()                 {NRO RMW(_fifo_1_message_pending,se_disable); }

   __inline__ void fifo_1_full(const state_enable_t val) {NRO RMW(_fifo_1_full,val) ; }
   __inline__ state_enable_t fifo_1_full() const         {NRO RD (_fifo_1_full) ; }
   __inline__ void fifo_1_full_enable()                  {NRO RMW(_fifo_1_full,se_enable) ; }
   __inline__ void fifo_1_full_disable()                 {NRO RMW(_fifo_1_full,se_disable); }

   __inline__ void fifo_1_overrun(const state_enable_t val) {NRO RMW(_fifo_1_overrun,val) ; }
   __inline__ state_enable_t fifo_1_overrun() const         {NRO RD (_fifo_1_overrun) ; }
   __inline__ void fifo_1_overrun_enable()                  {NRO RMW(_fifo_1_overrun,se_enable) ; }
   __inline__ void fifo_1_overrun_disable()                 {NRO RMW(_fifo_1_overrun,se_disable); }

   __inline__ void error_warning(const state_enable_t val) {NRO RMW(_error_warning,val) ; }
   __inline__ state_enable_t error_warning() const         {NRO RD (_error_warning) ; }
   __inline__ void error_warning_enable()                  {NRO RMW(_error_warning,se_enable) ; }
   __inline__ void error_warning_disable()                 {NRO RMW(_error_warning,se_disable); }

   __inline__ void error_passive(const state_enable_t val) {NRO RMW(_error_passive,val) ; }
   __inline__ state_enable_t error_passive() const         {NRO RD (_error_passive) ; }
   __inline__ void error_passive_enable()                  {NRO RMW(_error_passive,se_enable) ; }
   __inline__ void error_passive_disable()                 {NRO RMW(_error_passive,se_disable); }

   __inline__ void bus_off(const state_enable_t val) {NRO RMW(_bus_off,val) ; }
   __inline__ state_enable_t bus_off() const         {NRO RD (_bus_off) ; }
   __inline__ void bus_off_enable()                  {NRO RMW(_bus_off,se_enable) ; }
   __inline__ void bus_off_disable()                 {NRO RMW(_bus_off,se_disable); }

   __inline__ void last_error_code(const state_enable_t val) {NRO RMW(_last_error_code,val) ; }
   __inline__ state_enable_t last_error_code() const         {NRO RD (_last_error_code) ; }
   __inline__ void last_error_code_enable()                  {NRO RMW(_last_error_code,se_enable) ; }
   __inline__ void last_error_code_disable()                 {NRO RMW(_last_error_code,se_disable); }

   __inline__ void error(const state_enable_t val) {NRO RMW(_error,val) ; }
   __inline__ state_enable_t error() const         {NRO RD (_error) ; }
   __inline__ void error_enable()                  {NRO RMW(_error,se_enable) ; }
   __inline__ void error_disable()                 {NRO RMW(_error,se_disable); }

   __inline__ void wakeup(const state_enable_t val) {NRO RMW(_wakeup,val) ; }
   __inline__ state_enable_t wakeup() const         {NRO RD (_wakeup) ; }
   __inline__ void wakeup_enable()                  {NRO RMW(_wakeup,se_enable) ; }
   __inline__ void wakeup_disable()                 {NRO RMW(_wakeup,se_disable); }

   __inline__ void sleep(const state_enable_t val) {NRO RMW(_sleep,val) ; }
   __inline__ state_enable_t sleep() const         {NRO RD (_sleep) ; }
   __inline__ void sleep_enable()                  {NRO RMW(_sleep,se_enable); }
   __inline__ void sleep_disable()                 {NRO RMW(_sleep,se_disable); }


   volatile state_enable_t _transmit_mailbox_empty  : 1 ; //0
   volatile state_enable_t _fifo_0_message_pending  : 1 ; //1
   volatile state_enable_t _fifo_0_full             : 1 ; //2
   volatile state_enable_t _fifo_0_overrun          : 1 ; //3
   volatile state_enable_t _fifo_1_message_pending  : 1 ; //4
   volatile state_enable_t _fifo_1_full             : 1 ; //5
   volatile state_enable_t _fifo_1_overrun          : 1 ; //6
   uint32_t : 1 ; // 7
   volatile state_enable_t _error_warning           : 1 ; //8
   volatile state_enable_t _error_passive           : 1 ; //9
   volatile state_enable_t _bus_off                 : 1 ; //10
   volatile state_enable_t _last_error_code         : 1 ; //11
   uint32_t : 3 ; // 12..14
   volatile state_enable_t _error                   : 1 ; //15
   volatile state_enable_t _wakeup                  : 1 ; //16
   volatile state_enable_t _sleep                   : 1 ; //17
   uint32_t : 14 ; // 18..31
 } __reg_attr__ ;
#endif

  master_control_t  master_control ; //  MCR;                 /*!< CAN master control register,         Address offset: 0x00          */
//  master_status_t   master_status ; //  MSR;                 /*!< CAN master status register,          Address offset: 0x04          */
//  transmit_status_t transmit_status ; // TSR;                 /*!< CAN transmit status register,        Address offset: 0x08          */
//  receive_fifo_t    receive_fifo_0 ; // RF0R;                /*!< CAN receive FIFO 0 register,         Address offset: 0x0C          */
//  receive_fifo_t    receive_fifo_1 ; // RF1R;                /*!< CAN receive FIFO 1 register,         Address offset: 0x10          */
//  interrupt_t interrupt ;// IER;                 /*!< CAN interrupt enable register,       Address offset: 0x14          */
#if 0
  __IO uint32_t              ESR;                 /*!< CAN error status register,           Address offset: 0x18          */
    __IO uint32_t              BTR;                 /*!< CAN bit timing register,             Address offset: 0x1C          */
    uint32_t                   RESERVED0[88];       /*!< Reserved, 0x020 - 0x17F                                            */
    tx_mailbox_t      sTxMailBox[3];       /*!< CAN Tx MailBox,                      Address offset: 0x180 - 0x1AC */
    fifo_mailbox_t    sFIFOMailBox[2];     /*!< CAN FIFO MailBox,                    Address offset: 0x1B0 - 0x1CC */
    uint32_t                   RESERVED1[12];       /*!< Reserved, 0x1D0 - 0x1FF                                            */
    __IO uint32_t              FMR;                 /*!< CAN filter master register,          Address offset: 0x200         */
    __IO uint32_t              FM1R;                /*!< CAN filter mode register,            Address offset: 0x204         */
    uint32_t                   RESERVED2;           /*!< Reserved, 0x208                                                    */
    __IO uint32_t              FS1R;                /*!< CAN filter scale register,           Address offset: 0x20C         */
    uint32_t                   RESERVED3;           /*!< Reserved, 0x210                                                    */
    __IO uint32_t              FFA1R;               /*!< CAN filter FIFO assignment register, Address offset: 0x214         */
    uint32_t                   RESERVED4;           /*!< Reserved, 0x218                                                    */
    __IO uint32_t              FA1R;                /*!< CAN filter activation register,      Address offset: 0x21C         */
    uint32_t                   RESERVED5[8];        /*!< Reserved, 0x220-0x23F                                              */
    filter_t sFilterRegister[28]; /*!< CAN Filter Register,                 Address offset: 0x240-0x31C   */
#endif

    inline void clock_enable()
       {
          switch((uint32_t)this)
            {
               case can1_addr : rcc.can1_enable(); break ;
               case can2_addr : rcc.can2_enable(); break ;
               default: { std::__throw_invalid_argument("invalid CAN object") ; }
            }
       }

    inline void clock_disable()
       {
          switch((uint32_t)this)
            {
               case can1_addr : rcc.can1_disable(); break ;
               case can2_addr : rcc.can2_disable(); break ;
               default: {  std::__throw_invalid_argument("invalid CAN object") ; }
            }
       }
    inline void reset()
       {
          switch((uint32_t)this)
            {
               case can1_addr : rcc.can1_reset(); break ;
               case can2_addr : rcc.can2_reset(); break ;
               default: {  std::__throw_invalid_argument("invalid CAN object") ; }
            }
       };
  } ;

  struct can1_t : public can_t
    {
      inline void clock_enable() {  rcc.can1_enable() ; }
      inline void clock_disable() {  rcc.can1_disable() ; }
      inline void clock_reset() {  rcc.can1_reset() ; }
    };

  struct can2_t : public can_t
    {
      inline void clock_enable() {  rcc.can2_enable() ; }
      inline void clock_disable() {  rcc.can2_disable() ; }
      inline void clock_reset() {  rcc.can2_reset() ; }
    };

  static can1_t& can1 = *((can1_t*) can1_addr);
  static can2_t& can2 = *((can2_t*) can2_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __CAN++_H__ */
