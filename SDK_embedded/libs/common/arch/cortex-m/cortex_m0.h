#ifndef __CORTEX_M0++_H__
#define __CORTEX_M0++_H__

#include "armv6_m++.h"

namespace cortex_m0
{

// Application Program Status Register (APSR).
union apsr_t
  {
    struct
    {
      uint32_t  :28;                        /*!< bit:  0..15  Reserved */
      uint32_t v :1;                        /*!< bit:     28  Overflow condition code flag */
      uint32_t c :1;                        /*!< bit:     29  Carry condition code flag */
      uint32_t z :1;                        /*!< bit:     30  Zero condition code flag */
      uint32_t n :1;                        /*!< bit:     31  Negative condition code flag */
    } ;           /*!< Structure used for bit  access */
    uint32_t word;                         /*!< Type      used for word access */
}  ;

// Union type to access the Interrupt Program Status Register (IPSR).
union ipsr_t
{
  //http://infocenter.arm.com/help/topic/com.arm.doc.dui0662b/DUI0662B_cortex_m0p_r0p1_dgug.pdf
  enum exception_num_t: int32_t
     {
        thread                  = 0,//-16,
        reset                   = 1,//-15,
        non_maskable_int        = 2,//-14,    /*!< 2  Non Maskable Interrupt                                          */
	hard_fault              = 3,//-13,    /*!< 3  Cortex-M0+ Hard Fault Interrupt                                             */
	sv_call                 = 11,//-5,    /*!< 11 Cortex-M0+ SV Call Interrupt                                   */
	pend_sv                 = 14,//-2,    /*!< 14 Cortex-M0+ Pend SV Interrupt                                   */
	sys_tick                = 15,//-1,    /*!< 15 Cortex-M0+ System Tick Interrupt
     } ;

   struct
    {
      uint32_t isr:6;               /*!< bit:  0.. 6  Exception number */
      uint32_t    :26;              /*!< bit:  7..31  Reserved */
    }  ;    /*!< Structure used for bit  access */
    uint32_t word;                  /*!< Type      used for word access */
} ;

// Execution Program Status register (EPSR).
union epsr_t
  {
    struct
    {
      uint32_t        :24 ;// 0..23
      uint32_t       t:1 ; // 24
      uint32_t        :7 ; // 25..31
    } ;           /*!< Structure used for bit  access */
    uint32_t word;                         /*!< Type      used for word access */
}  ;

// Union type to access the Special-Purpose Program Status Registers (xPSR).
union xpsr_t
{
  struct
  {
    uint32_t     isr:6;               /*!< bit:  0.. 5  Exception number */
    uint32_t        :18;              /*!< bit:  6..23  Reserved */
    uint32_t     t  :1;               /*!< bit:     24  Thumb bit        (read 0) */
    uint32_t        :3;               /*!< bit: 25..27  Reserved */
    uint32_t     v  :1;               /*!< bit:     28  Overflow condition code flag */
    uint32_t     c  :1;               /*!< bit:     29  Carry condition code flag */
    uint32_t     z  :1;               /*!< bit:     30  Zero condition code flag */
    uint32_t     n  :1;               /*!< bit:     31  Negative condition code flag */
  } __reg_attr__ ;    /*!< Structure used for bit  access */
  uint32_t word;                  /*!< Type      used for word access */
} ;


// Union type to access the Control Registers (CONTROL).
union control_t
{
  struct
  {
    uint32_t npriv:1;              /*!< bit:      0  Execution privilege in Thread mode */
    uint32_t spsel:1;              /*!< bit:      1  Stack to be used */
    uint32_t      :30;             /*!< bit:  2..31  Reserved */
  } ;                              /*!< Structure used for bit  access */
  uint32_t word;                   /*!< Type      used for word access */
} ;


// Structure type to access the System Control and ID Register not in the SCB.
struct scnscb_t
{
 // TODO
} ;


// Structure type to access the System Timer (SysTick).
struct sys_tick_t
{
  struct control_status_t : public read_write_32_t
     {
       struct state_t                     { enum enum_t { offset=0,  mask=1, disable=0 , enable } ; } ;
       struct tick_int_request_t          { enum enum_t { offset=1,  mask=1, disable=0 , enable } ; } ;
       struct clock_source_t              { enum enum_t { offset=2,  mask=1, external_clk=0 , processor_clk } ; } ;
       struct counting_flag_t             { enum enum_t { offset=16, mask=1, no_zero_counted=0 , zero_counted } ; } ;
     };

  inline  void state(const control_status_t::state_t::enum_t val){  control_status.rmw(val) ;}
  inline  void enable()   {  control_status.rmw( control_status_t::state_t::enable) ;}
  inline  void disable() {  control_status.rmw( control_status_t::state_t::disable) ;}
  inline  auto state()const {  return control_status.rd<control_status_t::state_t> ();}

  inline  void tick_int_request(const control_status_t::tick_int_request_t::enum_t val){  control_status.rmw(val) ;}
  inline  void tick_int_request_enable()   {  control_status.rmw( control_status_t::tick_int_request_t::enable) ;}
  inline  void tick_int_request_disable() {  control_status.rmw( control_status_t::tick_int_request_t::disable) ;}
  inline  auto tick_int_request()const {  return control_status.rd<control_status_t::tick_int_request_t> ();}

  inline  void clock_source(const control_status_t::clock_source_t::enum_t val){  control_status.rmw(val) ;}
  inline  void clock_source_external_clk() {  control_status.rmw( control_status_t::clock_source_t::external_clk) ;}
  inline  void clock_source_processor_clk() {  control_status.rmw( control_status_t::clock_source_t::processor_clk) ;}
  inline  auto clock_source()const {  return control_status.rd<control_status_t::clock_source_t> ();}

  inline  auto counting_flag()const {  return control_status.rd<control_status_t::counting_flag_t> ();}

  struct calibration_t : public read_write_32_t
     {
       struct reload_value_for_10ms_timing_t { enum enum_t { offset=0,  mask=0xffffff } ; } ;
       struct scew_t                         { enum enum_t { offset=30, mask=1, ms10_exact=0,  ms10_inexact_or_not_given } ; } ;
       struct ref_clock_t                    { enum enum_t { offset=2,  mask=1, provided=0 , no_provided } ; } ;
     };

  inline  uint32_t reload_value_for_10ms_timing()const {  return calibration.rd<calibration_t::reload_value_for_10ms_timing_t> ();}
  inline  calibration_t::scew_t::enum_t  scew()const {  return calibration.rd<calibration_t::scew_t> ();}
  inline  calibration_t::ref_clock_t::enum_t  ref_clock()const {  return calibration.rd<calibration_t::ref_clock_t> ();}

  control_status_t  control_status ;    // CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32_t reload;             // LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32_t current;            // VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  calibration_t     calibration;        // CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} ;

struct scb_t
{
  struct cpuid_base_t : public read_write_32_t
  {
     struct revision_t  { enum enum_t { offset=0,  mask=0b1111 } ; } ;
     struct part_no_t   { enum enum_t { offset=4,  mask=0b111111111111, cortex_m0plus=0xc60, } ; } ;
     struct architecture_t { enum enum_t { offset=16, mask=0b1111, armv6_m=0xc, } ; } ;
     struct variant_t   { enum enum_t { offset=20, mask=0b1111 } ; } ;
     struct implementer_t { enum enum_t { offset=24, mask=0b11111111 } ; } ;
  };

  inline uint8_t     revision() const {return cpuid_base.rd<cpuid_base_t::revision_t> ();}
  inline uint16_t     part_no() const {return cpuid_base.rd<cpuid_base_t::part_no_t> ();}
  inline uint8_t architecture() const {return cpuid_base.rd<cpuid_base_t::architecture_t> ();}
  inline uint8_t      variant() const {return cpuid_base.rd<cpuid_base_t::variant_t> ();}
  inline uint8_t  implementer() const {return cpuid_base.rd<cpuid_base_t::implementer_t> ();}

  struct interrupt_control_and_state_t : public read_write_32_t
  {
    struct active_vector_t          { enum enum_t { offset=0,  mask=0x1ff } ; } ;
    struct return_to_base_level_t   { enum enum_t { offset=11, mask=0b1, preempted_active_exceptions_to_execute=0, no_active_exceptions=1 } ; } ;
    struct pending_vector_t         { enum enum_t { offset=12, mask=0x1ff } ; } ;
    struct isr_pending_t            { enum enum_t { offset=22, mask=0b1,  not_pending=0,  pending } ; } ;
    struct sys_tick_exception_pending_clear_t { enum enum_t { offset=25, mask=0b1,  clear=1 } ; } ;
    struct sys_tick_exception_pending_set_t   { enum enum_t { offset=26, mask=0b1,  set_to_pending=1 } ; } ;
    struct sys_tick_exception_pending_read_t  { enum enum_t { offset=26, mask=0b1,  not_pending=0,  pending } ; } ;

    struct pend_sv_exception_pending_clear_t  { enum enum_t { offset=27, mask=0b1,  clear=1 } ; } ;
    struct pend_sv_exception_pending_set_t    { enum enum_t { offset=28, mask=0b1,  set_to_pending=1 } ; } ;
    struct pend_sv_exception_pending_read_t   { enum enum_t { offset=28, mask=0b1,  not_pending=0,  pending } ; } ;

    struct nmi_exception_pending_set_t   { enum enum_t { offset=31, mask=0b1,  set_to_pending=1 } ; } ;
    struct nmi_exception_pending_read_t  { enum enum_t { offset=31, mask=0b1,  not_pending=0,  pending } ; } ;

  }  ;

  inline  auto active_vector()const {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::active_vector_t> ();}
  inline  auto return_to_base_level()const {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::return_to_base_level_t> ();}
  inline  auto pending_vector()const {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::pending_vector_t> ();}
  inline  auto isr_pending()const {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::isr_pending_t> ();}

  inline void sys_tick_exception_pending_clear() { interrupt_control_and_state.rmw(interrupt_control_and_state_t::sys_tick_exception_pending_clear_t::clear) ;}
  inline void sys_tick_exception_pending_set()   { interrupt_control_and_state.rmw(interrupt_control_and_state_t::sys_tick_exception_pending_set_t::set_to_pending) ;}
  inline auto sys_tick_exception_pending()const  {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::sys_tick_exception_pending_read_t> ();}

  inline void pend_sv_exception_pending_clear() { interrupt_control_and_state.rmw(interrupt_control_and_state_t::sys_tick_exception_pending_clear_t::clear) ;}
  inline void pend_sv_exception_pending_set()   { interrupt_control_and_state.rmw(interrupt_control_and_state_t::pend_sv_exception_pending_set_t::set_to_pending) ;}
  inline auto pend_sv_exception_pending()const  {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::pend_sv_exception_pending_read_t> ();}

  inline void nmi_exception_pending_set()   { interrupt_control_and_state.rmw(interrupt_control_and_state_t::nmi_exception_pending_set_t::set_to_pending) ;}
  inline auto nmi_exception_pending()const  {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::nmi_exception_pending_read_t> ();}


  struct vector_table_offset_t : public read_write_32_t
  {
  } ;
  inline void vector_table_offset( const uint32_t val ) { vector_table_offset_reg.write(val & 0x3fffff80); }
  inline auto vector_table_offset() const { return vector_table_offset_reg.read(); }

  struct application_interrupt_and_reset_control_t : public read_write_32_t
  {
    struct vect_clear_active_t   { enum enum_t { offset=1,  mask=0b1 } ; } ;
    struct system_reset_request_t{ enum enum_t { offset=2,  mask=0b1, request=1  } ; } ;
    struct endianess_t           { enum enum_t { offset=15, mask=0b1, little=0 , big} ; } ;
    struct vector_key_t          { enum enum_t { offset=16, mask=0xffff, write_key=0x5fa} ; } ;
  };
  inline void system_reset()
     {
        dsb(); // завершение обращений к памяти
        application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key,
							application_interrupt_and_reset_control_t::system_reset_request_t::request
	                                              );
        dsb();      // завершение обращений к памяти
        nop_loop(); // ожидание сброса
     }

  struct system_control_t : public read_write_32_t
  {
    struct sleep_on_exit_t  { enum enum_t { offset=1,  mask=0b1, do_not_sleep=0, enter_sleep } ;} ;
    struct sleep_deep_t     { enum enum_t { offset=2,  mask=0b1, disable=0, enable } ;} ;
    struct send_event_on_pending_t { enum enum_t { offset=4,  mask=0b1, only_enabled=0, all } ;} ;
  } ;

  inline  void sleep_on_exit(const system_control_t::sleep_on_exit_t::enum_t val){  system_control.rmw(val) ;}
  inline  void sleep_on_exit_do_not_sleep() {  system_control.rmw( system_control_t::sleep_on_exit_t::do_not_sleep) ;}
  inline  void sleep_on_exit_enter_sleep() {  system_control.rmw( system_control_t::sleep_on_exit_t::enter_sleep) ;}
  inline  auto sleep_on_exit()const {  return system_control.rd<system_control_t::sleep_on_exit_t>();}

  inline  void sleep_deep(const system_control_t::sleep_deep_t::enum_t val){  system_control.rmw(val) ;}
  inline  void sleep_deep_enable() {  system_control.rmw( system_control_t::sleep_deep_t::enable) ;}
  inline  void sleep_deep_disable() {  system_control.rmw( system_control_t::sleep_deep_t::disable) ;}
  inline  auto sleep_deep()const {  return system_control.rd<system_control_t::sleep_deep_t>();}

  inline  void send_event_on_pending(const system_control_t::send_event_on_pending_t::enum_t val){  system_control.rmw(val) ;}
  inline  void send_event_on_pending_only_enabled() {  system_control.rmw( system_control_t::send_event_on_pending_t::only_enabled) ;}
  inline  void send_event_on_pending_all() {  system_control.rmw( system_control_t::send_event_on_pending_t::all) ;}
  inline  auto send_event_on_pending()const {  return system_control.rd<system_control_t::send_event_on_pending_t>();}


  struct configuration_control_t : public read_write_32_t
  {
    struct unaligned_access_trap_t { enum enum_t { offset=3,  mask=0b1, disable=0, enable } ;} ;
    struct stack_alignment_on_exception_entry_t { enum enum_t { offset=9,  mask=0b1, aligned_4_byte=0, aligned_8_byte} ;} ;
  } ;

  inline  auto unaligned_access_trap()const {  return configuration_control.rd<configuration_control_t::unaligned_access_trap_t>();}

  inline  auto stack_alignment_on_exception_entry()const {  return configuration_control.rd<configuration_control_t::stack_alignment_on_exception_entry_t>();}

  // struct system_handler_priority_t : public read_write_32_t
  // эта структура реализована как  uint8_t system_handler_priority[8U];
  inline  void svc_call_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::sv_call-8] = val; }
  inline  auto svc_call_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::sv_call-8]; }

  inline  void pend_sv_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::pend_sv-8] = val; }
  inline  auto pend_sv_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::pend_sv-8]; }

  inline  void systick_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::sys_tick-8] = val; }
  inline  auto systick_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::sys_tick-8]; }

  cpuid_base_t                              cpuid_base ;                            /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  interrupt_control_and_state_t             interrupt_control_and_state ;           /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  vector_table_offset_t                     vector_table_offset_reg;                /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  application_interrupt_and_reset_control_t application_interrupt_and_reset_control;/*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  system_control_t                          system_control;                         /*!< Offset: 0x010 (R/W)  System Control Register */
  configuration_control_t                   configuration_control ;                 /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  uint32_t : 32 ;
  uint8_t                                   system_handler_priority[8];             /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */

} ;

// Structure type to access the Nested Vectored Interrupt Controller (NVIC).
struct core_nvic_t
{
  inline void enable()
     { NRO
       set_enable_vec[0] = 0xffffffff ;
     }

  inline void disable()
     { NRO
       clear_enable_vec[0] = 0xffffffff ;
     }

  inline void pending_set()
     { NRO
       set_pending_vec[0] = 0xffffffff;
     }

  inline void pending_clear()
     { NRO
       clear_pending_vec[0] = 0xffffffff;
     }

  inline void priority_reset()
     { NRO
       for (uint32_t i = 0 ; i < sizeof(priority_vec) ; i++)
         priority_vec[i] = 0 ;
     }

  inline void reset()
     { NRO
       disable() ;
       pending_clear();
       priority_reset();
     }

  volatile uint32_t set_enable_vec [1];    /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
  uint32_t reserved0[31];
  volatile uint32_t clear_enable_vec[1];   /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
  uint32_t reserved1[31];
  volatile uint32_t set_pending_vec[1];    /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
  uint32_t reserved2[31];
  volatile uint32_t clear_pending_vec[1];  /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
  uint32_t reserved3[95];
  volatile uint8_t  priority_vec[32];       /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
}  ;


#define MAKE_NVIC_IRQ_ITEM(irq_num) \
inline void irq_num##_enable()          {NRO set_enable_vec[0]   = 1 << ((int16_t)irq_num_t::irq_num); } \
inline void irq_num##_disable()         {NRO clear_enable_vec[0] = 1 << ((int16_t)irq_num_t::irq_num); } \
inline auto irq_num##_state()     const {NRO return (state_t::enum_t)(set_enable_vec[0] & 1<<((int16_t)irq_num_t::irq_num)); } \
inline void irq_num##_pending_set()     {NRO set_pending_vec[0]  = 1 << ((int16_t)irq_num_t::irq_num); } \
inline void irq_num##_pending_clear()   {NRO clear_pending_vec[0]= 1 << ((int16_t)irq_num_t::irq_num); } \
inline auto irq_num##_pending()   const {NRO return (pending_t::enum_t)(set_pending_vec[0] & 1<<((int16_t)irq_num_t::irq_num)); } \
//inline void irq_num##_priority(const uint8_t priority ) { NRO (int16_t)irq_num_t::irq_num < 0 ? scb.system_handler_priority[ (int16_t)irq_num_t::irq_num - 8] = priority :   \
//                                                                          priority_vec[(int16_t)irq_num_t::irq_num]      = (uint8_t)priority ; } \
//inline uint8_t irq_num##_priority() const { NRO return (int16_t)irq_num_t::irq_num < 0 ? scb.system_handler_priority[ (int16_t)irq_num_t::irq_num - 8] : \
                                                                            priority_vec[(int16_t)irq_num_t::irq_num] ; }


/* Memory mapping of Cortex-M0 Hardware */
static const uint32_t scs_addr =           0xE000E000UL;                            /*!< System Control Space Base Address */
static const uint32_t sys_tick_addr =      scs_addr +  0x0010UL;                    /*!< SysTick Base Address */
static const uint32_t nvic_addr =          scs_addr +  0x0100UL;                    /*!< NVIC Base Address */
static const uint32_t scb_addr =           scs_addr +  0x0D00UL;                    /*!< System Control Block Base Address */

static const uint32_t  nvic_prio_bits  =  2 ;

static scnscb_t&     scnscb    = *((scnscb_t*) scs_addr);
static scb_t&        scb       = *((scb_t*) scb_addr);
static sys_tick_t&   sys_tick  = *((sys_tick_t*) sys_tick_addr);
// ---- !!!  static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало на уровнь выше(stm32) для биндинга в stm32f4::nvic_t


}

using namespace cortex_m0 ;

#include "cortex_m++.h"

#endif // __CORTEX_M0++_H__



