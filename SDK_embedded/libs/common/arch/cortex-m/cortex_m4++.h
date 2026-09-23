#ifndef __CORTEX_M4++_H__
#define __CORTEX_M4++_H__

#include "armv7e_m++.h"

namespace cortex_m4
{

// Application Program Status Register (APSR).
union apsr_t
  {
    struct
    {
      uint32_t  :16;                        /*!< bit:  0..15  Reserved */
      uint32_t ge:4;                        /*!< bit: 16..19  Greater than or Equal flags */
      uint32_t   :7;                        /*!< bit: 20..26  Reserved */
      uint32_t q :1;                        /*!< bit:     27  Saturation condition flag */
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
  //http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0552a/Babefdjc.html
  enum exception_num_t: int32_t
     {
        thread                  = 0,//-16,
        reset                   = 1,//-15,
        non_maskable_int        = 2,//-14,    /*!< 2 Non Maskable Interrupt                                          */
	hard_fault              = 3,//-13,    /*!< 3 Hard_Fault Interrupt                                            */
	memory_management       = 4,//-12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
	bus_fault               = 5,//-11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
	usage_fault             = 6,//-10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
	sv_call                 = 11,//-5,    /*!< 11 Cortex-M4 SV Call Interrupt                                    */
	debug_monitor           = 12,//-4,    /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
	pend_sv                 = 14,//-2,    /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
	sys_tick                = 15,//-1,    /*!< 15 Cortex-M4 System Tick Interrupt                                */
     } ;

   struct
    {
      uint32_t isr:9;               /*!< bit:  0.. 8  Exception number */
      uint32_t    :23;              /*!< bit:  9..31  Reserved */
    }  ;    /*!< Structure used for bit  access */
    uint32_t word;                  /*!< Type      used for word access */
} ;

// Execution Program Status register (EPSR).
union epsr_t
  {
    struct
    {
      uint32_t        :9 ; // 0...9
      uint32_t it_icil:6 ; // 10..15
      uint32_t        :8 ; // 16..23
      uint32_t       t:1 ; // 24
      uint32_t it_icih:2 ; // 25..26
      uint32_t        :6 ; // 27..31
    } ;           /*!< Structure used for bit  access */
    uint32_t word;                         /*!< Type      used for word access */
}  ;

// Union type to access the Special-Purpose Program Status Registers (xPSR).
union xpsr_t
{
  struct
  {
    uint32_t     isr:9;               /*!< bit:  0.. 8  Exception number */
    uint32_t        :7;               /*!< bit:  9..15  Reserved */
    uint32_t     ge :4;               /*!< bit: 16..19  Greater than or Equal flags */
    uint32_t        :4;               /*!< bit: 20..23  Reserved */
    uint32_t     t  :1;               /*!< bit:     24  Thumb bit        (read 0) */
    uint32_t it_icil:2;               /*!< bit: 25..26  saved IT state   (read 0) */
    uint32_t     q  :1;               /*!< bit:     27  Saturation condition flag */
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
    uint32_t fpca :1;              /*!< bit:      2  FP extension active flag */
    uint32_t      :29;             /*!< bit:  3..31  Reserved */
  } ;                              /*!< Structure used for bit  access */
  uint32_t word;                   /*!< Type      used for word access */
} ;


// Structure type to access the System Control and ID Register not in the SCB.
struct scnscb_t
{
  struct interrupt_controller_type_t : public read_write_32_t
     {
       struct lines_number_t                     { enum enum_t { offset=0,  mask=0xf} ; } ;
     };
  inline uint8_t interrupt_controller_lines_number() { return interrupt_controller_type.rd<interrupt_controller_type_t::lines_number_t> (); }

  struct auxiliary_control_t : public read_write_32_t
  {
     struct disables_interuption_of_multicycle_instruction_t                { enum enum_t { offset=0,  mask=0b1, disable=0, enable=1} ; } ;
     struct disables_write_buffer_use_during_default_memory_map_accesses_t  { enum enum_t { offset=1,  mask=0b1, disable=0, enable=1} ; } ;
     struct disables_folding_of_it_instructions_t                           { enum enum_t { offset=2,  mask=0b1, disable=0, enable=1} ; } ;
     struct disables_automatic_update_control_fpca_t                        { enum enum_t { offset=8,  mask=0b1, disable=0, enable=1} ; } ;
     struct disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t
                                                                            { enum enum_t { offset=9,  mask=0b1, disable=0, enable=1} ; } ;
  } ;

  inline  void disables_interuption_of_multicycle_instruction(const auxiliary_control_t::disables_interuption_of_multicycle_instruction_t::enum_t val){  auxiliary_control.rmw(val) ;}
  inline  void disables_interuption_of_multicycle_instruction_enable()  {  auxiliary_control.rmw( auxiliary_control_t::disables_interuption_of_multicycle_instruction_t::enable) ;}
  inline  void disables_interuption_of_multicycle_instruction_disable() {  auxiliary_control.rmw( auxiliary_control_t::disables_interuption_of_multicycle_instruction_t::disable) ;}
  inline  auto disables_interuption_of_multicycle_instruction() const {  return auxiliary_control.rd<auxiliary_control_t::disables_interuption_of_multicycle_instruction_t> ();}

  inline  void disables_write_buffer_use_during_default_memory_map_accesses(const auxiliary_control_t::disables_write_buffer_use_during_default_memory_map_accesses_t::enum_t val){  auxiliary_control.rmw(val) ;}
  inline  void disables_write_buffer_use_during_default_memory_map_accesses_enable()   {  auxiliary_control.rmw( auxiliary_control_t::disables_write_buffer_use_during_default_memory_map_accesses_t::enable) ;}
  inline  void disables_write_buffer_use_during_default_memory_map_accesses_disable() {  auxiliary_control.rmw( auxiliary_control_t::disables_write_buffer_use_during_default_memory_map_accesses_t::disable) ;}
  inline  auto disables_write_buffer_use_during_default_memory_map_accesses()const {  return auxiliary_control.rd<auxiliary_control_t::disables_write_buffer_use_during_default_memory_map_accesses_t> ();}

  inline  void disables_folding_of_it_instructions(const auxiliary_control_t::disables_folding_of_it_instructions_t::enum_t val){  auxiliary_control.rmw(val) ;}
  inline  void disables_folding_of_it_instructions_enable()   {  auxiliary_control.rmw( auxiliary_control_t::disables_folding_of_it_instructions_t::enable) ;}
  inline  void disables_folding_of_it_instructions_disable() {  auxiliary_control.rmw( auxiliary_control_t::disables_folding_of_it_instructions_t::disable) ;}
  inline  auto disables_folding_of_it_instructions()const {  return auxiliary_control.rd<auxiliary_control_t::disables_folding_of_it_instructions_t> ();}

  inline  void disables_automatic_update_control_fpca(const auxiliary_control_t::disables_automatic_update_control_fpca_t::enum_t val){  auxiliary_control.rmw(val) ;}
  inline  void disables_automatic_update_control_fpca_enable()   {  auxiliary_control.rmw( auxiliary_control_t::disables_automatic_update_control_fpca_t::enable) ;}
  inline  void disables_automatic_update_control_fpca_disable() {  auxiliary_control.rmw( auxiliary_control_t::disables_automatic_update_control_fpca_t::disable) ;}
  inline  auto disables_automatic_update_control_fpca()const {  return auxiliary_control.rd<auxiliary_control_t::disables_automatic_update_control_fpca_t> ();}

  inline  void disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions(const auxiliary_control_t::disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t::enum_t val){  auxiliary_control.rmw(val) ;}
  inline  void disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_enable()   {  auxiliary_control.rmw( auxiliary_control_t::disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t::enable) ;}
  inline  void disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_disable() {  auxiliary_control.rmw( auxiliary_control_t::disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t::disable) ;}
  inline  auto disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t()const {  return auxiliary_control.rd<auxiliary_control_t::disables_floating_point_instructions_completing_out_of_order_with_respect_to_integer_instructions_t> ();}


  uint32_t reserved ;
  const interrupt_controller_type_t  interrupt_controller_type ;
  auxiliary_control_t                auxiliary_control ;

} ;


// Structure type to access the Nested Vectored Interrupt Controller (NVIC).
struct core_nvic_t
{
  struct software_trigger_t : public read_write_32_t
     {
       struct interupt_id_t                     { enum enum_t { offset=0,  mask=0xff} ; } ;
     };

  inline void set_software_trigger( const uint8_t val){  software_trigger.rmw((software_trigger_t::interupt_id_t::enum_t)val) ;}

  inline void disable()
     { NRO
       clear_enable_vec[0] = clear_enable_vec[1] = clear_enable_vec[2] = clear_enable_vec[3] =
       clear_enable_vec[4] = clear_enable_vec[5] = clear_enable_vec[6] = clear_enable_vec[7] = 0xffffffff ;
     }
  inline void pending_clear()
     { NRO
       clear_pending_vec[0] = clear_pending_vec[1] = clear_pending_vec[2] = clear_pending_vec[3] =
       clear_pending_vec[4] = clear_pending_vec[5] = clear_pending_vec[6] = clear_pending_vec[7] =0xffffffff;
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

  volatile uint32_t set_enable_vec [8U];              /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
  uint32_t reserved0[24U];
  volatile uint32_t clear_enable_vec[8U];             /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
  uint32_t reserved1[24U];
  volatile uint32_t set_pending_vec[8U];              /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
  uint32_t reserved2[24U];
  volatile uint32_t clear_pending_vec[8U];            /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
  uint32_t reserved3[24U];
  volatile uint32_t active_vec[8U];                   /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
  uint32_t reserved4[56U];
  volatile uint8_t  priority_vec[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  uint32_t reserved5[644U];
  software_trigger_t software_trigger;            /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  ;


    #define MAKE_NVIC_IRQ_ITEM(periferial) \
    inline void periferial##_enable() {NRO set_enable_vec[(int16_t)irq_num_t::periferial/32] = 1 << ((int16_t)irq_num_t::periferial%32); } \
    inline void periferial##_disable(){NRO clear_enable_vec[(int16_t)irq_num_t::periferial/32] = 1<<((int16_t)irq_num_t::periferial%32); } \
    inline auto periferial() const {NRO return (state_t::enum_t)(set_enable_vec[(int16_t)irq_num_t::periferial/32] & 1<<((int16_t)irq_num_t::periferial%32)); } \
    inline void periferial##_pending_set() {NRO set_pending_vec[(int16_t)irq_num_t::periferial/32] = 1 << ((int16_t)irq_num_t::periferial%32); } \
    inline void periferial##_pending_clear() {NRO clear_pending_vec[(int16_t)irq_num_t::periferial/32] = 1<<((int16_t)irq_num_t::periferial%32); } \
    inline auto periferial##_pending() const {NRO return (pending_t::enum_t)(set_pending_vec[(int16_t)irq_num_t::periferial/32] & 1<<((int16_t)irq_num_t::periferial%32)); } \
    inline auto periferial##_active() const {NRO return (active_t::enum_t)(active_vec[(int16_t)irq_num_t::periferial/32] & 1<<((int16_t)irq_num_t::periferial%32)); } \
    inline void periferial##_priority(const uint8_t priority ) { NRO priority_vec[(int16_t)irq_num_t::periferial] = priority ; } \
    inline uint8_t periferial##_priority() const { NRO return priority_vec[(int16_t)irq_num_t::periferial] ; } \
    inline void periferial##_set_software_trigger() { core_nvic_t::set_software_trigger( (uint8_t)irq_num_t::periferial) ; }


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

  inline uint32_t config( const bool int_request, const bool state, const uint32_t reload, const uint32_t current = 0 )
     {
        if ( reload & ~0xffffff ) // ошибочное значение аргумента
           return -1 ;

        this->reload=reload ;
        this->current = current ;

        clock_source_processor_clk();
        int_request ? tick_int_request_enable() : tick_int_request_disable();
        state ? enable() : disable() ;

        return 0 ;
     }
} ;

struct scb_t
{
  struct cpuid_base_t : public read_write_32_t
  {
     struct revision_t  { enum enum_t { offset=0,  mask=0b1111 } ; } ;
     struct part_no_t   { enum enum_t { offset=4,  mask=0b111111111111 } ; } ;
     struct constant_t  { enum enum_t { offset=16, mask=0b1111 } ; } ;
     struct variant_t   { enum enum_t { offset=20, mask=0b1111 } ; } ;
     struct implementer_t { enum enum_t { offset=24, mask=0b11111111 } ; } ;
  };

  inline uint8_t    revision() const {return cpuid_base.rd<cpuid_base_t::revision_t> ();}
  inline uint16_t    part_no() const {return cpuid_base.rd<cpuid_base_t::part_no_t> ();}
  inline uint8_t    constant() const {return cpuid_base.rd<cpuid_base_t::constant_t> ();}
  inline uint8_t     variant() const {return cpuid_base.rd<cpuid_base_t::variant_t> ();}
  inline uint8_t implementer() const {return cpuid_base.rd<cpuid_base_t::implementer_t> ();}

  struct interrupt_control_and_state_t : public read_write_32_t
  {
    struct active_vector_t          { enum enum_t { offset=0,  mask=0x1ff } ; } ;
    struct return_to_base_level_t   { enum enum_t { offset=11, mask=0b1, preempted_active_exceptions_to_execute=0, no_active_exceptions=1 } ; } ;
    struct pending_vector_t         { enum enum_t { offset=12, mask=0x1ff } ; } ;
    struct isr_pending_t            { enum enum_t { offset=22, mask=0b1,  not_pending=0,  pending } ; } ;
    struct debug_t                  { enum enum_t { offset=23, mask=0b1, normal=0, under_debugging } ; } ;
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
  inline  auto debug()const {  return interrupt_control_and_state.rd<interrupt_control_and_state_t::debug_t> ();}

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
  inline void vector_table_offset( const uint32_t val ) { vector_table_offset_reg.write(val & 0x3ffffe00); }
  inline auto vector_table_offset() const { return vector_table_offset_reg.read(); }

  struct application_interrupt_and_reset_control_t : public read_write_32_t
  {
    struct vect_reset_t          { enum enum_t { offset=0,  mask=0b1 } ; } ;
    struct vect_clear_active_t   { enum enum_t { offset=1,  mask=0b1 } ; } ;
    struct system_reset_request_t{ enum enum_t { offset=2,  mask=0b1, no_action=0, request  } ; } ;
    struct priority_group_t      { enum enum_t { offset=8,  mask=0b111, priority_group_16=0, priority_group_8=0b100, priority_group_4=0b101, priority_group_2=0b110, priority_group_none=0b111 } ; } ;
    struct endianess_t           { enum enum_t { offset=15, mask=0b1, little=0 , big} ; } ;
    struct vector_key_t          { enum enum_t { offset=16, mask=0xffff, read_key=0xfa05 , write_key=0x5fa} ; } ;
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

  inline  void priority_group( const application_interrupt_and_reset_control_t::priority_group_t::enum_t val){  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key , val) ;}
  inline  void priority_group_16(){  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key, application_interrupt_and_reset_control_t::priority_group_t::priority_group_16) ;}
  inline  void priority_group_8() {  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key, application_interrupt_and_reset_control_t::priority_group_t::priority_group_8) ;}
  inline  void priority_group_4() {  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key, application_interrupt_and_reset_control_t::priority_group_t::priority_group_4) ;}
  inline  void priority_group_2() {  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key, application_interrupt_and_reset_control_t::priority_group_t::priority_group_2) ;}
  inline  void priority_group_none() {  application_interrupt_and_reset_control.modify( application_interrupt_and_reset_control_t::vector_key_t::write_key ,application_interrupt_and_reset_control_t::priority_group_t::priority_group_none) ;}
  inline  auto priority_group()const {  return application_interrupt_and_reset_control.rd<application_interrupt_and_reset_control_t::priority_group_t> ();}

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
    struct enters_thread_mode_t  { enum enum_t { offset=0,  mask=0b1, only_when_no_exception=0, any_level } ;} ;
    struct unprivileged_stir_access_t  { enum enum_t { offset=1,  mask=0b1, disable=0, enable } ;} ;
    struct unaligned_access_trap_t { enum enum_t { offset=3,  mask=0b1, disable=0, enable } ;} ;
    struct div_zero_trap_t { enum enum_t { offset=4,  mask=0b1, disable=0, enable } ;} ;
    struct handlers_priority_on_data_bus_faults_t { enum enum_t { offset=8,  mask=0b1, normal=0, ignore } ;} ;
    struct stack_alignment_on_exception_entry_t { enum enum_t { offset=9,  mask=0b1, aligned_4_byte=0, aligned_8_byte} ;} ;
  } ;

  inline  void enters_thread_mode(const configuration_control_t::enters_thread_mode_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void enters_thread_mode_only_when_no_exception() {  configuration_control.rmw( configuration_control_t::enters_thread_mode_t::only_when_no_exception) ;}
  inline  void enters_thread_mode_any_level() {  configuration_control.rmw( configuration_control_t::enters_thread_mode_t::any_level) ;}
  inline  auto enters_thread_mode()const {  return configuration_control.rd<configuration_control_t::enters_thread_mode_t>();}

  inline  void unprivileged_stir_access(const configuration_control_t::unprivileged_stir_access_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void unprivileged_stir_access_disable() {  configuration_control.rmw( configuration_control_t::unprivileged_stir_access_t::disable) ;}
  inline  void unprivileged_stir_access_enable() {  configuration_control.rmw( configuration_control_t::unprivileged_stir_access_t::enable) ;}
  inline  auto unprivileged_stir_access()const {  return configuration_control.rd<configuration_control_t::unprivileged_stir_access_t>();}

  inline  void unaligned_access_trap(const configuration_control_t::unaligned_access_trap_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void unaligned_access_trap_disable() {  configuration_control.rmw( configuration_control_t::unaligned_access_trap_t::disable) ;}
  inline  void unaligned_access_trap_enable() {  configuration_control.rmw( configuration_control_t::unaligned_access_trap_t::enable) ;}
  inline  auto unaligned_access_trap()const {  return configuration_control.rd<configuration_control_t::unaligned_access_trap_t>();}

  inline  void div_zero_trap(const configuration_control_t::div_zero_trap_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void div_zero_trap_disable() {  configuration_control.rmw( configuration_control_t::div_zero_trap_t::disable) ;}
  inline  void div_zero_trap_enable() {  configuration_control.rmw( configuration_control_t::div_zero_trap_t::enable) ;}
  inline  auto div_zero_trap()const {  return configuration_control.rd<configuration_control_t::div_zero_trap_t>();}

  inline  void handlers_priority_on_data_bus_faults(const configuration_control_t::handlers_priority_on_data_bus_faults_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void handlers_priority_on_data_bus_faults_normal() {  configuration_control.rmw( configuration_control_t::handlers_priority_on_data_bus_faults_t::normal) ;}
  inline  void handlers_priority_on_data_bus_faults_ignore() {  configuration_control.rmw( configuration_control_t::handlers_priority_on_data_bus_faults_t::ignore) ;}
  inline  auto handlers_priority_on_data_bus_faults()const {  return configuration_control.rd<configuration_control_t::handlers_priority_on_data_bus_faults_t>();}

  inline  void stack_alignment_on_exception_entry(const configuration_control_t::stack_alignment_on_exception_entry_t::enum_t val){  configuration_control.rmw(val) ;}
  inline  void stack_alignment_on_exception_entry_4_byte() {  configuration_control.rmw( configuration_control_t::stack_alignment_on_exception_entry_t::aligned_4_byte) ;}
  inline  void stack_alignment_on_exception_entry_8_byte() {  configuration_control.rmw( configuration_control_t::stack_alignment_on_exception_entry_t::aligned_8_byte) ;}
  inline  auto stack_alignment_on_exception_entry()const {  return configuration_control.rd<configuration_control_t::stack_alignment_on_exception_entry_t>();}

  // struct system_handler_priority_t : public read_write_32_t
  // эта структура реализована как  uint8_t system_handler_priority[12U];
  inline  void memory_management_fault_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::memory_management-4] = val; }
  inline  auto memory_management_fault_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::memory_management-4]; }

  inline  void bus_fault_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::bus_fault-4] = val; }
  inline  auto bus_fault_handler_priority()const {  return system_handler_priority[ipsr_t::exception_num_t::bus_fault-4]; }

  inline  void usage_fault_handler_priority(const uint8_t val){system_handler_priority[ipsr_t::exception_num_t::usage_fault-4] = val; }
  inline  auto usage_fault_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::usage_fault-4]; }

  inline  void svc_call_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::sv_call-4] = val; }
  inline  auto svc_call_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::sv_call-4]; }

  inline  void pend_sv_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::pend_sv-4] = val; }
  inline  auto pend_sv_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::pend_sv-4]; }

  inline  void systick_handler_priority(const uint8_t val){ system_handler_priority[ipsr_t::exception_num_t::sys_tick-4] = val; }
  inline  auto systick_handler_priority()const { return system_handler_priority[ipsr_t::exception_num_t::sys_tick-4]; }

  struct system_handler_control_and_state_t : public read_write_32_t
  {
    struct memory_management_fault_active_t { enum enum_t { offset=0,  mask=0b1, reset=0, set } ;} ;
    struct bus_fault_active_t { enum enum_t { offset=1,  mask=0b1, reset=0, set } ;} ;
    struct usage_fault_active_t { enum enum_t { offset=3,  mask=0b1, reset=0, set } ;} ;
    struct svc_call_active_t { enum enum_t { offset=7,  mask=0b1, reset=0, set } ;} ;
    struct debug_monitor_active_t { enum enum_t { offset=8,  mask=0b1, reset=0, set } ;} ;
    struct pend_sv_active_t { enum enum_t { offset=10,  mask=0b1, reset=0, set } ;} ;
    struct systick_active_t { enum enum_t { offset=11,  mask=0b1, reset=0, set } ;} ;

    struct usage_fault_pending_t { enum enum_t { offset=12,  mask=0b1, reset=0, set } ;} ;
    struct memory_management_fault_pending_t { enum enum_t { offset=13,  mask=0b1, reset=0, set } ;} ;
    struct bus_fault_pending_t { enum enum_t { offset=14,  mask=0b1, reset=0, set } ;} ;
    struct svc_call_pending_t { enum enum_t { offset=15,  mask=0b1, reset=0, set } ;} ;

    struct memory_management_fault_t { enum enum_t { offset=16,  mask=0b1, disable=0, enable } ;} ;
    struct bus_fault_t { enum enum_t { offset=17,  mask=0b1, disable=0, enable } ;} ;
    struct usage_fault_t { enum enum_t { offset=18,  mask=0b1, disable=0, enable } ;} ;
  }  ;

  inline  void memory_management_fault_active(const system_handler_control_and_state_t::memory_management_fault_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void memory_management_fault_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_active_t::reset) ;}
  inline  void memory_management_fault_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_active_t::set) ;}
  inline  auto memory_management_fault_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::memory_management_fault_active_t>();}

  inline  void bus_fault_active_active(const system_handler_control_and_state_t::bus_fault_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void bus_fault_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_active_t::reset) ;}
  inline  void bus_fault_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_active_t::set) ;}
  inline  auto bus_fault_active_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::bus_fault_active_t>();}

  inline  void usage_fault_active(const system_handler_control_and_state_t::usage_fault_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void usage_fault_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_active_t::reset) ;}
  inline  void usage_fault_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_active_t::set) ;}
  inline  auto usage_fault_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::usage_fault_active_t>();}

  inline  void svc_call_active(const system_handler_control_and_state_t::svc_call_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void svc_call_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::svc_call_active_t::reset) ;}
  inline  void svc_call_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::svc_call_active_t::set) ;}
  inline  auto svc_call_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::svc_call_active_t>();}

  inline  void debug_monitor_active(const system_handler_control_and_state_t::debug_monitor_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void debug_monitor_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::debug_monitor_active_t::reset) ;}
  inline  void debug_monitor_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::debug_monitor_active_t::set) ;}
  inline  auto debug_monitor_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::debug_monitor_active_t>();}

  inline  void pend_sv_active(const system_handler_control_and_state_t::pend_sv_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void pend_sv_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::pend_sv_active_t::reset) ;}
  inline  void pend_sv_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::pend_sv_active_t::set) ;}
  inline  auto pend_sv_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::pend_sv_active_t>();}

  inline  void systick_active(const system_handler_control_and_state_t::systick_active_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void systick_active_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::systick_active_t::reset) ;}
  inline  void systick_active_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::systick_active_t::set) ;}
  inline  auto systick_active()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::systick_active_t>();}

  inline  void usage_fault_pending(const system_handler_control_and_state_t::usage_fault_pending_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void usage_fault_pending_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_pending_t::reset) ;}
  inline  void usage_fault_pending_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_pending_t::set) ;}
  inline  auto usage_fault_pending()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::usage_fault_pending_t>();}

  inline  void memory_management_fault_pending(const system_handler_control_and_state_t::memory_management_fault_pending_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void memory_management_fault_pending_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_pending_t::reset) ;}
  inline  void memory_management_fault_pending_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_pending_t::set) ;}
  inline  auto memory_management_fault_pending()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::memory_management_fault_pending_t>();}

  inline  void bus_fault_pending(const system_handler_control_and_state_t::bus_fault_pending_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void bus_fault_pending_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_pending_t::reset) ;}
  inline  void bus_fault_pending_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_pending_t::set) ;}
  inline  auto bus_fault_pending()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::bus_fault_pending_t>();}

  inline  void svc_call_pending(const system_handler_control_and_state_t::svc_call_pending_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void svc_call_pending_reset() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::svc_call_pending_t::reset) ;}
  inline  void svc_call_pending_set() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::svc_call_pending_t::set) ;}
  inline  auto svc_call_pending()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::svc_call_pending_t>();}

  inline  void memory_management_fault(const system_handler_control_and_state_t::memory_management_fault_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void memory_management_fault_enable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_t::enable) ;}
  inline  void memory_management_fault_disable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::memory_management_fault_t::disable) ;}
  inline  auto memory_management_fault()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::memory_management_fault_t>();}

  inline  void bus_fault(const system_handler_control_and_state_t::bus_fault_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void bus_fault_enable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_t::enable) ;}
  inline  void bus_fault_disable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::bus_fault_t::disable) ;}
  inline  auto bus_fault()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::bus_fault_t>();}

  inline  void usage_fault(const system_handler_control_and_state_t::usage_fault_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void usage_fault_enable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_t::enable) ;}
  inline  void usage_fault_disable() {  system_handler_control_and_state.rmw( system_handler_control_and_state_t::usage_fault_t::disable) ;}
  inline  auto usage_fault()const {  return system_handler_control_and_state.rd<system_handler_control_and_state_t::usage_fault_t>();}

  struct configurable_fault_status_t : public read_write_32_t
  {
    struct instruction_access_violation_t { enum enum_t { offset=0,  mask=0b1, reset=0, set } ;} ;
    struct data_access_violation_t { enum enum_t { offset=1,  mask=0b1, reset=0, set } ;} ;
    struct memory_manager_fault_on_unstacking_t { enum enum_t { offset=3,  mask=0b1, reset=0, set } ;} ;
    struct memory_manager_fault_on_stacking_exception_entry_t { enum enum_t { offset=4,  mask=0b1, reset=0, set } ;} ;
    struct memory_manager_fault_on_fp_lazy_state_preservation_t { enum enum_t { offset=5,  mask=0b1, reset=0, set } ;} ;
    struct memory_manager_fault_address_register_t { enum enum_t { offset=7,  mask=0b1, reset=0, set } ;} ;

    struct instruction_bus_error_t { enum enum_t { offset=8,  mask=0b1, reset=0, set } ;} ;
    struct precise_data_bus_error_t { enum enum_t { offset=9,  mask=0b1, reset=0, set } ;} ;
    struct imprecise_data_bus_error_t { enum enum_t { offset=10,  mask=0b1, reset=0, set } ;} ;

    struct bus_fault_on_unstacking_from_exception_t { enum enum_t { offset=11,  mask=0b1, reset=0, set } ;} ;
    struct bus_fault_on_stacking_to_exception_t { enum enum_t { offset=12,  mask=0b1, reset=0, set } ;} ;
    struct bus_fault_on_fp_lazy_state_preservation_t { enum enum_t { offset=13,  mask=0b1, reset=0, set } ;} ;
    struct bus_fault_address_register_t { enum enum_t { offset=15,  mask=0b1, no_valid=0, valid_fault_address } ;} ;

    struct undefined_instruction_usage_fault_t { enum enum_t { offset=16,  mask=0b1, reset=0, set } ;};
    struct invalid_state_usage_fault_t { enum enum_t { offset=17,  mask=0b1, reset=0, set } ;};
    struct invalid_pc_load_usage_fault_t { enum enum_t { offset=18,  mask=0b1, reset=0, set } ;};
    struct no_coprocessor_usage_fault_t { enum enum_t { offset=19,  mask=0b1, reset=0, set } ;};

    struct unaligned_access_usage_fault_t { enum enum_t { offset=24,  mask=0b1, reset=0, set } ;};
    struct divide_by_zero_usage_fault_t  { enum enum_t { offset=25,  mask=0b1, reset=0, set } ;};
  } ;

  inline  void instruction_access_violation_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::instruction_access_violation_t::set) ;}
  inline  auto instruction_access_violation()const {  return configurable_fault_status.rd<configurable_fault_status_t::instruction_access_violation_t>();}

  inline  void data_access_violation_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::data_access_violation_t::set) ;}
  inline  auto data_access_violation()const {  return configurable_fault_status.rd<configurable_fault_status_t::data_access_violation_t>();}

  inline  void memory_manager_fault_on_unstacking_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::memory_manager_fault_on_unstacking_t::set) ;}
  inline  auto memory_manager_fault_on_unstacking()const {  return configurable_fault_status.rd<configurable_fault_status_t::memory_manager_fault_on_unstacking_t>();}

  inline  void memory_manager_fault_on_stacking_exception_entry_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::memory_manager_fault_on_stacking_exception_entry_t::set) ;}
  inline  auto memory_manager_fault_on_stacking_exception_entry()const {  return configurable_fault_status.rd<configurable_fault_status_t::memory_manager_fault_on_stacking_exception_entry_t>();}

  inline  void memory_manager_fault_on_fp_lazy_state_preservation_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::memory_manager_fault_on_fp_lazy_state_preservation_t::set) ;}
  inline  auto memory_manager_fault_on_fp_lazy_state_preservation()const {  return configurable_fault_status.rd<configurable_fault_status_t::memory_manager_fault_on_fp_lazy_state_preservation_t>();}

  inline  void memory_manager_fault_address_register_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::memory_manager_fault_address_register_t::set) ;}
  inline  auto memory_manager_fault_address_register()const {  return configurable_fault_status.rd<configurable_fault_status_t::memory_manager_fault_address_register_t>();}

  inline  void instruction_bus_error_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::instruction_bus_error_t::set) ;}
  inline  auto instruction_bus_error()const {  return configurable_fault_status.rd<configurable_fault_status_t::instruction_bus_error_t>();}

  inline  void precise_data_bus_error_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::precise_data_bus_error_t::set) ;}
  inline  auto precise_data_bus_error()const {  return configurable_fault_status.rd<configurable_fault_status_t::precise_data_bus_error_t>();}

  inline  void imprecise_data_bus_error_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::imprecise_data_bus_error_t::set) ;}
  inline  auto imprecise_data_bus_error()const {  return configurable_fault_status.rd<configurable_fault_status_t::imprecise_data_bus_error_t>();}

  inline  void bus_fault_on_unstacking_from_exception_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::bus_fault_on_unstacking_from_exception_t::set) ;}
  inline  auto bus_fault_on_unstacking_from_exception()const {  return configurable_fault_status.rd<configurable_fault_status_t::bus_fault_on_unstacking_from_exception_t>();}

  inline  void bus_fault_on_stacking_to_exception_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::bus_fault_on_stacking_to_exception_t::set) ;}
  inline  auto bus_fault_on_stacking_to_exception()const {  return configurable_fault_status.rd<configurable_fault_status_t::bus_fault_on_stacking_to_exception_t>();}

  inline  void bus_fault_on_fp_lazy_state_preservation_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::bus_fault_on_fp_lazy_state_preservation_t::set) ;}
  inline  auto bus_fault_on_fp_lazy_state_preservation()const {  return configurable_fault_status.rd<configurable_fault_status_t::bus_fault_on_fp_lazy_state_preservation_t>();}

  inline  void bus_fault_address_register_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::bus_fault_address_register_t::valid_fault_address) ;}
  inline  auto bus_fault_address_register()const {  return configurable_fault_status.rd<configurable_fault_status_t::bus_fault_address_register_t>();}

  inline  void undefined_instruction_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::undefined_instruction_usage_fault_t::set) ;}
  inline  auto undefined_instruction_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::undefined_instruction_usage_fault_t>();}

  inline  void invalid_state_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::invalid_state_usage_fault_t::set) ;}
  inline  auto invalid_state_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::invalid_state_usage_fault_t>();}

  inline  void invalid_pc_load_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::invalid_pc_load_usage_fault_t::set) ;}
  inline  auto invalid_pc_load_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::invalid_pc_load_usage_fault_t>();}

  inline  void no_coprocessor_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::no_coprocessor_usage_fault_t::set) ;}
  inline  auto no_coprocessor_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::no_coprocessor_usage_fault_t>();}

  inline  void unaligned_access_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::unaligned_access_usage_fault_t::set) ;}
  inline  auto unaligned_access_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::unaligned_access_usage_fault_t>();}

  inline  void divide_by_zero_usage_fault_clear() {  configurable_fault_status.rmw( configurable_fault_status_t::divide_by_zero_usage_fault_t::set) ;}
  inline  auto divide_by_zero_usage_fault()const {  return configurable_fault_status.rd<configurable_fault_status_t::divide_by_zero_usage_fault_t>();}

  struct hard_fault_status_t : public read_write_32_t
  {
    struct vector_table_hard_fault_t { enum enum_t { offset=1,  mask=0b1, reset=0, set } ;};
    struct forced_hard_fault_t { enum enum_t { offset=30,  mask=0b1, reset=0, set } ;};
    struct debug_evnt_t { enum enum_t { offset=31,  mask=0b1, reset=0, set } ;};
  } ;

  inline  void vector_table_hard_fault_clear() {  hard_fault_status.rmw( hard_fault_status_t::vector_table_hard_fault_t::set) ;}
  inline  auto vector_table_hard_fault()const {  return hard_fault_status.rd<hard_fault_status_t::vector_table_hard_fault_t>();}

  inline  void forced_hard_fault_clear() {  hard_fault_status.rmw( hard_fault_status_t::forced_hard_fault_t::set) ;}
  inline  auto forced_hard_fault()const {  return hard_fault_status.rd<hard_fault_status_t::forced_hard_fault_t>();}


  struct debug_fault_status_t : public read_write_32_t
  {
    //TODO заменить на битовое поле
  } ;

  struct memmanage_fault_address_t : public read_write_32_t
  {
    // 32-bit value address register
  } ;

  struct bus_fault_address_t : public read_write_32_t
  {
    // 32-bit value address register
  } ;

  struct auxiliary_fault_status_t : public read_write_32_t
  {
    //TODO заменить на битовое пполе
  } ;

  struct processor_feature_1_t : public read_write_32_t
  {
     //TODO заменить на битовое пполе
  } ;

  struct processor_feature_2_t : public read_write_32_t
  {
     //TODO заменить на битовое пполе
  } ;

  struct  debug_feature_t : public read_write_32_t
  {
    //TODO заменить на битовое пполе
  } ;

  struct   auxiliary_feature_t : public read_write_32_t
  {
    //TODO заменить на битовое пполе
  } ;

  struct   memory_model_feature_t : public read_write_32_t
  {
    //TODO заменить на битовое пполе
  } ;

  struct   instruction_set_attributes_t : public read_write_32_t
  {
    //TODO заменить на битовое пполе
  } ;

  struct   coprocessor_access_control_t : public read_write_32_t
  {
    //  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0646b/BABDBFBJ.html
    struct access_cp10_t { enum enum_t { offset=20,  mask=0b11, denied=0, privileged, full=0b11 } ;};
    struct access_cp11_t { enum enum_t { offset=22,  mask=0b11, denied=0, privileged, full=0b11 } ;};
  }  ;

  inline  void coprocessor_10_access(const coprocessor_access_control_t::access_cp10_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void coprocessor_10_access_deniede() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp10_t::denied) ;}
  inline  void coprocessor_10_access_privileged() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp10_t::privileged) ;}
  inline  void coprocessor_10_access_full() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp10_t::full) ;}
  inline  auto coprocessor_10_access()const {  return coprocessor_access_control.rd<coprocessor_access_control_t::access_cp10_t>();}

  inline  void coprocessor_11_access(const coprocessor_access_control_t::access_cp11_t::enum_t val){  system_handler_control_and_state.rmw(val) ;}
  inline  void coprocessor_11_access_deniede() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp11_t::denied) ;}
  inline  void coprocessor_11_access_privileged() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp11_t::privileged) ;}
  inline  void coprocessor_11_access_full() {  coprocessor_access_control.rmw( coprocessor_access_control_t::access_cp11_t::full) ;}
  inline  auto coprocessor_11_access()const {  return coprocessor_access_control.rd<coprocessor_access_control_t::access_cp11_t>();}

  cpuid_base_t                              cpuid_base ;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  interrupt_control_and_state_t             interrupt_control_and_state ;  /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  vector_table_offset_t                     vector_table_offset_reg;          /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  application_interrupt_and_reset_control_t application_interrupt_and_reset_control ;            /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  system_control_t                          system_control;                /*!< Offset: 0x010 (R/W)  System Control Register */
  configuration_control_t                   configuration_control ;        /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  uint8_t                                   system_handler_priority[12U];  /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  system_handler_control_and_state_t        system_handler_control_and_state ;      /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  configurable_fault_status_t               configurable_fault_status;/*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  hard_fault_status_t                       hard_fault_status ;            /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  debug_fault_status_t                      debug_fault_status;            /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  memmanage_fault_address_t                 memmanage_fault_address ;      /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  bus_fault_address_t                       bus_fault_address;             /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  auxiliary_fault_status_t                  auxiliary_fault_status;        /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  processor_feature_1_t                     processor_feature_1_t;         /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  processor_feature_2_t                     processor_feature_2_t;
  debug_feature_t                           debug_feature;                 /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  auxiliary_feature_t                       auxiliary_feature;             /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  memory_model_feature_t                    memory_model_feature_t[4U];             /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  instruction_set_attributes_t              instruction_set_attributes[5U]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32_t reserved0[5U];
  coprocessor_access_control_t              coprocessor_access_control;    /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} ;

struct itm_t
{
  struct   trace_state_t : public read_write_32_t
  {
    enum enum_t { mask=1, disable=0, enable } ;
  };

  inline  void stimulus_port(const uint8_t port, trace_state_t::enum_t val){  trace_state.rmw( val, port) ;}
  inline  void stimulus_port_enable(const uint8_t port) { trace_state.rmw( trace_state_t::enable, port) ; }
  inline  void stimulus_port_disable(const uint8_t port) { trace_state.rmw( trace_state_t::disable, port) ;}
  inline  auto stimulus_port(const uint8_t port)const {  return trace_state.rd<trace_state_t>(port);}

  struct   trace_privileg_t : public read_write_32_t
  {
    struct mask_enable_tracing_ports_7_0_t   { enum enum_t { offset=0, mask=1, reset=0, set } ;};
    struct mask_enable_tracing_ports_15_8_t  { enum enum_t { offset=1, mask=1, reset=0, set } ;};
    struct mask_enable_tracing_ports_23_16_t { enum enum_t { offset=2, mask=1, reset=0, set } ;};
    struct mask_enable_tracing_ports_31_24_t { enum enum_t { offset=3, mask=1, reset=0, set } ;};
  };

  inline  void mask_enable_tracing_ports_7_0(trace_privileg_t::mask_enable_tracing_ports_7_0_t::enum_t val){  trace_privileg.rmw( val) ;}
  inline  void mask_enable_tracing_ports_7_0_reset() { trace_privileg.rmw( trace_privileg_t::mask_enable_tracing_ports_7_0_t::reset) ; }
  inline  void mask_enable_tracing_ports_7_0_set() { trace_privileg.rmw(trace_privileg_t:: mask_enable_tracing_ports_7_0_t::set) ;}
  inline  auto mask_enable_tracing_ports_7_0()const {  return trace_privileg.rd<trace_privileg_t::mask_enable_tracing_ports_7_0_t>();}

  inline  void mask_enable_tracing_ports_15_8(trace_privileg_t::mask_enable_tracing_ports_15_8_t::enum_t val){  trace_privileg.rmw( val) ;}
  inline  void mask_enable_tracing_ports_15_8_reset() { trace_privileg.rmw( trace_privileg_t::mask_enable_tracing_ports_15_8_t::reset) ; }
  inline  void mask_enable_tracing_ports_15_8_set() { trace_privileg.rmw(trace_privileg_t:: mask_enable_tracing_ports_15_8_t::set) ;}
  inline  auto mask_enable_tracing_ports_15_8()const {  return trace_privileg.rd<trace_privileg_t::mask_enable_tracing_ports_15_8_t>();}

  inline  void mask_enable_tracing_ports_23_16(trace_privileg_t::mask_enable_tracing_ports_23_16_t::enum_t val){  trace_privileg.rmw( val) ;}
  inline  void mask_enable_tracing_ports_23_16_reset() { trace_privileg.rmw( trace_privileg_t::mask_enable_tracing_ports_23_16_t::reset) ; }
  inline  void mask_enable_tracing_ports_23_16_set() { trace_privileg.rmw(trace_privileg_t:: mask_enable_tracing_ports_23_16_t::set) ;}
  inline  auto mask_enable_tracing_ports_23_16()const {  return trace_privileg.rd<trace_privileg_t::mask_enable_tracing_ports_23_16_t>();}

  inline  void mask_enable_tracing_ports_31_24(trace_privileg_t::mask_enable_tracing_ports_31_24_t::enum_t val){  trace_privileg.rmw( val) ;}
  inline  void mask_enable_tracing_ports_31_24_reset() { trace_privileg.rmw( trace_privileg_t::mask_enable_tracing_ports_31_24_t::reset) ; }
  inline  void mask_enable_tracing_ports_31_24_set() { trace_privileg.rmw(trace_privileg_t:: mask_enable_tracing_ports_31_24_t::set) ;}
  inline  auto mask_enable_tracing_ports_31_24()const {  return trace_privileg.rd<trace_privileg_t::mask_enable_tracing_ports_31_24_t>();}

  struct   trace_control_t : public read_write_32_t
  {
    struct state_t                    { enum enum_t { offset=0, mask=1, disable=0, enable } ;};
    struct timestamp_t                { enum enum_t { offset=1, mask=1, disable=0, enable } ;};
    struct synchronization_triggers_t { enum enum_t { offset=2, mask=1, disable=0, enable } ;};
    struct dwt_stimulus_t             { enum enum_t { offset=3, mask=1, disable=0, enable } ;};
    struct swv_behavior_t             { enum enum_t { offset=4, mask=1, disable=0, enable } ;};
    struct timestamp_prescaler_t      { enum enum_t { offset=8, mask=0b11 } ;};
    struct atb_id_t                   { enum enum_t { offset=16, mask=0b1111111 } ;};
    struct busy_t                     { enum enum_t { offset=23, mask=1, no_busy=0, busy } ;};
  };

  inline  void state(trace_control_t::state_t::enum_t val){  trace_control.rmw( val) ;}
  inline  void state_enable() { trace_control.rmw( trace_control_t::state_t::disable) ; }
  inline  void state_disable() { trace_control.rmw(trace_control_t:: state_t::enable) ;}
  inline  auto state()const {  return trace_control.rd<trace_control_t::state_t>();}

  inline  void timestamp(trace_control_t::timestamp_t::enum_t val){  trace_control.rmw( val) ;}
  inline  void timestamp_enable() { trace_control.rmw( trace_control_t::timestamp_t::disable) ; }
  inline  void timestamp_disable() { trace_control.rmw(trace_control_t:: timestamp_t::enable) ;}
  inline  auto timestamp()const {  return trace_control.rd<trace_control_t::timestamp_t>();}

  inline  void synchronization_triggers(trace_control_t::synchronization_triggers_t::enum_t val){  trace_control.rmw( val) ;}
  inline  void synchronization_triggers_enable() { trace_control.rmw( trace_control_t::synchronization_triggers_t::disable) ; }
  inline  void synchronization_triggers_disable() { trace_control.rmw(trace_control_t::synchronization_triggers_t::enable) ;}
  inline  auto synchronization_triggers()const {  return trace_control.rd<trace_control_t::synchronization_triggers_t>();}

  inline  void dwt_stimulus(trace_control_t::dwt_stimulus_t::enum_t val){  trace_control.rmw( val) ;}
  inline  void dwt_stimulus_enable() { trace_control.rmw( trace_control_t::dwt_stimulus_t::disable) ; }
  inline  void dwt_stimulus_disable() { trace_control.rmw(trace_control_t::dwt_stimulus_t::enable) ;}
  inline  auto dwt_stimulus()const {  return trace_control.rd<trace_control_t::dwt_stimulus_t>();}

  inline  void swv_behavior(trace_control_t::swv_behavior_t::enum_t val){  trace_control.rmw( val) ;}
  inline  void swv_behavior_enable() { trace_control.rmw( trace_control_t::swv_behavior_t::disable) ; }
  inline  void swv_behavior_disable() { trace_control.rmw(trace_control_t::swv_behavior_t::enable) ;}
  inline  auto swv_behavior()const {  return trace_control.rd<trace_control_t::swv_behavior_t>();}

  inline  void timestamp_prescaler( uint8_t val){  trace_control.rmw( (trace_control_t::timestamp_prescaler_t::enum_t)val) ;}
  inline  auto timestamp_prescaler()const {  return (uint8_t)trace_control.rd<trace_control_t::timestamp_prescaler_t>();}

  inline  void atb_id( uint8_t val){  trace_control.rmw( (trace_control_t::atb_id_t::enum_t)val) ;}
  inline  auto atb_id()const {  return (uint8_t)trace_control.rd<trace_control_t::atb_id_t>();}

  inline  auto busy()const {  return trace_control.rd<trace_control_t::busy_t>();}
  inline  auto busy_wait()const { while ( busy() == trace_control_t::busy_t::busy) {} }

  struct integration_write_t : public read_write_32_t
  {
  };

  struct integration_read_t : public read_write_32_t
  {
  };

  struct integration_mode_control_t : public read_write_32_t
  {
  };

  struct lock_access_t : public read_write_32_t
  {
  };

  inline void unlock() { lock_access.write(0xC5ACCE55) ; }

  struct lock_status_t : public read_write_32_t
  {
  };


    union
    {
      volatile  uint8_t    byte;                    /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 8-bit */
      volatile  uint16_t   halfword;                /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 16-bit */
      volatile  uint32_t   word;                    /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 32-bit */
    } volatile  port [32];                                   /*!< Offset: 0x000 ( /W)  ITM Stimulus Port Registers */

    uint32_t reserved0 [864];
    trace_state_t trace_state;                      // TER;                    /*!< Offset: 0xE00 (R/W)  ITM Trace Enable Register */
    uint32_t reserved1[15U];
    trace_privileg_t trace_privileg;                // TPR;                    /*!< Offset: 0xE40 (R/W)  ITM Trace Privilege Register */
    uint32_t reserved2[15U];
    trace_control_t trace_control;                  // TCR;                    /*!< Offset: 0xE80 (R/W)  ITM Trace Control Register */
    uint32_t reserved3[29U];
    integration_write_t integration_write;          // IWR;                    /*!< Offset: 0xEF8 ( /W)  ITM Integration Write Register */
    integration_read_t integration_read;            // IRR;                    /*!< Offset: 0xEFC (R/ )  ITM Integration Read Register */
    integration_mode_control_t integration_mode_control; // IMCR;                   /*!< Offset: 0xF00 (R/W)  ITM Integration Mode Control Register */
    uint32_t reserved4[43U];
    lock_access_t lock_access;                      // LAR;                    /*!< Offset: 0xFB0 ( /W)  ITM Lock Access Register */
    lock_status_t lock_status;                      // LSR;                    /*!< Offset: 0xFB4 (R/ )  ITM Lock Status Register */
    uint32_t reserved5[6U];
    volatile uint32_t pid4;                         /*!< Offset: 0xFD0 (R/ )  ITM Peripheral Identification Register #4 */
    volatile uint32_t pid5;                         /*!< Offset: 0xFD4 (R/ )  ITM Peripheral Identification Register #5 */
    volatile uint32_t pid6;                         /*!< Offset: 0xFD8 (R/ )  ITM Peripheral Identification Register #6 */
    volatile uint32_t pid7;                         /*!< Offset: 0xFDC (R/ )  ITM Peripheral Identification Register #7 */
    volatile uint32_t pid0;                         /*!< Offset: 0xFE0 (R/ )  ITM Peripheral Identification Register #0 */
    volatile uint32_t pid1;                         /*!< Offset: 0xFE4 (R/ )  ITM Peripheral Identification Register #1 */
    volatile uint32_t pid2;                         /*!< Offset: 0xFE8 (R/ )  ITM Peripheral Identification Register #2 */
    volatile uint32_t pid3;                         /*!< Offset: 0xFEC (R/ )  ITM Peripheral Identification Register #3 */
    volatile uint32_t cid0;                         /*!< Offset: 0xFF0 (R/ )  ITM Component  Identification Register #0 */
    volatile uint32_t cid1;                         /*!< Offset: 0xFF4 (R/ )  ITM Component  Identification Register #1 */
    volatile uint32_t cid2;                         /*!< Offset: 0xFF8 (R/ )  ITM Component  Identification Register #2 */
    volatile uint32_t cid3;                         /*!< Offset: 0xFFC (R/ )  ITM Component  Identification Register #3 */

    inline void wait_for_available(const uint8_t port) const { while ( this->port[port].word == 0 ) { NRO } }
    inline void swo_enable(const uint8_t port)
      {
          unlock();
          trace_control.modify( itm_t::trace_control_t::swv_behavior_t::enable, (itm_t::trace_control_t::atb_id_t::enum_t)0x7f,
      			      itm_t::trace_control_t::synchronization_triggers_t::enable, itm_t::trace_control_t:: state_t::enable );
          trace_privileg.modify( itm_t::trace_privileg_t::mask_enable_tracing_ports_7_0_t::set,
      			       itm_t::trace_privileg_t::mask_enable_tracing_ports_15_8_t::set,
      			       itm_t::trace_privileg_t::mask_enable_tracing_ports_23_16_t::set,
      			       itm_t::trace_privileg_t::mask_enable_tracing_ports_31_24_t::set
                                    );

          stimulus_port_enable(port);
      }

    inline int send (const uint8_t port, const int c)
      {
         wait_for_available(port);
         this->port[port].byte = c ;
         return c ;
      }

    inline void send (const uint8_t port, const char* str)
      {
         while ( __builtin_expect ( *str != 0 , 1))
          {
             send(port,*str++);
          }
      }

} ;

struct dwt_t
{

  struct control_t : public read_write_32_t
    {
       struct cyc_counter_t              { enum enum_t { offset=0,  mask=1, disable=0 , enable } ; } ;
       struct post_counter_preset_t      { enum enum_t { offset=1,  mask=0b1111 } ; } ;
       struct post_counter_t             { enum enum_t { offset=5,  mask=0b1111 } ; } ;
       struct cyc_cnt_tap_t              { enum enum_t { offset=9,  mask=1, bit6=0 , bit10 } ; } ;
       struct sync_tap_t                 { enum enum_t { offset=10, mask=0b11, disable=0 , bit24, bit26, bit28 } ; } ;
       struct pc_sampler_t               { enum enum_t { offset=12, mask=1, disable=0 , enable } ; } ;
       struct exception_trace_t          { enum enum_t { offset=16, mask=1, disable=0 , enable } ; } ;
       struct cpi_counter_t              { enum enum_t { offset=17, mask=1, disable=0 , enable } ; } ;
       struct exception_overhead_event_t { enum enum_t { offset=18, mask=1, disable=0 , enable } ; } ;
       struct sleep_count_event_t        { enum enum_t { offset=19, mask=1, disable=0 , enable } ; } ;
       struct lsu_count_event_t          { enum enum_t { offset=20, mask=1, disable=0 , enable } ; } ;
       struct folded_instruction_count_event_t          { enum enum_t { offset=21, mask=1, disable=0 , enable } ; } ;
       struct cyc_event_t          { enum enum_t { offset=22, mask=1, disable=0 , enable } ; } ;
       struct no_fold_lsu_sleep_exc_counter_t          { enum enum_t { offset=24, mask=1, disable=0 , enable } ; } ;
       struct no_cyc_t       { enum enum_t { offset=25, mask=1, disable=0 , enable } ; } ;
       struct no_ext_trigger_t       { enum enum_t { offset=26, mask=1, disable=0 , enable } ; } ;
       struct no_sampling_and_exception_tracing_t       { enum enum_t { offset=27, mask=1, disable=0 , enable } ; } ;
       struct number_of_comparators_t       { enum enum_t { offset=28, mask=0b1111 } ; } ;
    };


    inline  void cyc_counter_state(const control_t::cyc_counter_t::enum_t val){  control.rmw(val) ;}
    inline  void cyc_counter_enable()   {  control.rmw(control_t::cyc_counter_t::enable) ;}
    inline  void cyc_counter_disable() {  control.rmw(control_t::cyc_counter_t::disable) ;}
    inline  auto cyc_counter_state()const {  return control.rd<control_t::cyc_counter_t>();}

    struct cyc_counter_t : public read_write_32_t
        {
        };

    struct cpi_counter_t : public read_write_32_t
        {
        };


    control_t          control ;     // CTRL;         /*!< Offset: 0x000 (R/W)  Control Register */
    volatile uint32_t  cyc_counter ; // CYCCNT;       /*!< Offset: 0x004 (R/W)  Cycle Count Register */
    volatile uint32_t  cpi_counter;  //CPICNT;        /*!< Offset: 0x008 (R/W)  CPI Count Register */

// TODO
/*
    //-----------------------------------------------------------------------------------
    // warning: not usable for mesure OS sync call as Delay,DelayUntil,etc... becouse
    // this calls set a scheduller to idle state, what deactivate a OS sync calls
    inline void __attribute__((always_inline))  rt_counter_start(size_t& counter)
    {
    	extern size_t rt_self_delay;
    	TScheduler::EnterCritical();
    	counter = rt_counter_cnt() + rt_self_delay ;
    }
    //-----------------------------------------------------------------------------------
    inline void __attribute__((always_inline))  rt_counter_start_woc(size_t& counter)
    {
    	extern size_t rt_self_delay;
    	counter = rt_counter_cnt() + rt_self_delay ;
    }
    //-----------------------------------------------------------------------------------
    // warning: not usable for mesure OS sync call as Delay,DelayUntil,etc... becouse
    // this calls set a scheduller to iddle state, what deactivate a OS sync calls
    inline size_t __attribute__((always_inline))  rt_counter_stop(size_t counter)
    {
        size_t tmp = rt_counter_cnt() - counter ;
        TScheduler::ExitCritical();
        return tmp ;
    }
    //-----------------------------------------------------------------------------------
    inline size_t __attribute__((always_inline))  rt_counter_stop_woc(size_t counter)
    {
      return rt_counter_cnt() - counter ;
    }
    //-----------------------------------------------------------------------------------
    inline float __attribute__((always_inline))  rt_counter_stop_us_woc(size_t counter)
    {
      extern float  rt_clock_period_uS ;
      return rt_counter_stop_woc(counter) * rt_clock_period_uS ;
    }
    //-----------------------------------------------------------------------------------
    // warning: not usable for mesure OS sync call as Delay,DelayUntil,etc... becouse
    // this calls set a scheduller to iddle state, what deactivate a OS sync calls
    inline float __attribute__((always_inline))  rt_counter_stop_us(size_t counter)
    {
      float tmp = rt_counter_stop_us_woc(counter);
      TScheduler::ExitCritical();
      return tmp ;
    }
    //-----------------------------------------------------------------------------------
    inline float __attribute__((always_inline))  rt_counter_us(size_t counter)
    {
      extern float  rt_clock_period_uS ;
      return counter * rt_clock_period_uS ;
    }
    //-----------------------------------------------------------------------------------
    inline void __attribute__((always_inline))  rt_counter_calibrate()
    {
      extern size_t rt_self_delay;
      size_t tmp ;
      rt_counter_start(tmp);
      rt_self_delay = rt_counter_stop(tmp); ;
    }*/
#if 0

  EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __IM  uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
  MASK0;                  /*!< Offset: 0x024 (R/W)  Mask Register 0 */
  FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
        uint32_t RESERVED0[1U];
  COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
  MASK1;                  /*!< Offset: 0x034 (R/W)  Mask Register 1 */
  FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
        uint32_t RESERVED1[1U];
  COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
  MASK2;                  /*!< Offset: 0x044 (R/W)  Mask Register 2 */
  FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
        uint32_t RESERVED2[1U];
  COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
  MASK3;                  /*!< Offset: 0x054 (R/W)  Mask Register 3 */
  FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
#endif



}  ;

struct tpi_t
{
  struct supported_parallel_port_size_t : public read_write_32_t
  {
    // TODO
  } ;

  struct curent_parallel_port_size_t : public read_write_32_t
  {
    // TODO
  } ;

  struct asynchronous_clock_prescaler_t : public read_write_32_t
  {
    // TODO
  } ;

  struct selected_pin_protocol_t : public read_write_32_t
  {
    // TODO
  } ;

  struct formatter_flush_status_t : public read_write_32_t
  {
    // TODO
  } ;

  struct formatter_flush_control_t : public read_write_32_t
  {
    // TODO
  } ;

  struct formatter_synchronization_counter_t : public read_write_32_t
  {
    // TODO
  } ;

  struct trigger_t : public read_write_32_t
  {
    // TODO
  } ;

  supported_parallel_port_size_t supported_parallel_port_size; // SSPSR;                  /*!< Offset: 0x000 (R/ )  Supported Parallel Port Size Register */
  curent_parallel_port_size_t    curent_parallel_port_size;    // CSPSR;                  /*!< Offset: 0x004 (R/W)  Current Parallel Port Size Register */
  uint32_t reserved0[2U];
  asynchronous_clock_prescaler_t asynchronous_clock_prescaler; // ACPR;                   /*!< Offset: 0x010 (R/W)  Asynchronous Clock Prescaler Register */
  uint32_t reserved1[55U];
  selected_pin_protocol_t         selected_pin_protocol;       // SPPR;                   /*!< Offset: 0x0F0 (R/W)  Selected Pin Protocol Register */
  uint32_t reserved2[131U];
  formatter_flush_status_t       formatter_flush_status;       // FFSR;                   /*!< Offset: 0x300 (R/ )  Formatter and Flush Status Register */
  formatter_flush_control_t      formatter_flush_control;      // FFCR;                   /*!< Offset: 0x304 (R/W)  Formatter and Flush Control Register */
  formatter_synchronization_counter_t formatter_synchronization_counter; // FSCR;         /*!< Offset: 0x308 (R/ )  Formatter Synchronization Counter Register */
  uint32_t reserved3[759U];
  trigger_t                      trigger;                      // TRIGGER;                /*!< Offset: 0xEE8 (R/ )  TRIGGER */

  #if 0 //TODO
  __IM  uint32_t FIFO0;                  /*!< Offset: 0xEEC (R/ )  Integration ETM Data */
  __IM  uint32_t ITATBCTR2;              /*!< Offset: 0xEF0 (R/ )  ITATBCTR2 */
        uint32_t RESERVED4[1U];
  __IM  uint32_t ITATBCTR0;              /*!< Offset: 0xEF8 (R/ )  ITATBCTR0 */
  __IM  uint32_t FIFO1;                  /*!< Offset: 0xEFC (R/ )  Integration ITM Data */
  __IOM uint32_t ITCTRL;                 /*!< Offset: 0xF00 (R/W)  Integration Mode Control */
        uint32_t RESERVED5[39U];
  __IOM uint32_t CLAIMSET;               /*!< Offset: 0xFA0 (R/W)  Claim tag set */
  __IOM uint32_t CLAIMCLR;               /*!< Offset: 0xFA4 (R/W)  Claim tag clear */
        uint32_t RESERVED7[8U];
  __IM  uint32_t DEVID;                  /*!< Offset: 0xFC8 (R/ )  TPIU_DEVID */
  __IM  uint32_t DEVTYPE;                /*!< Offset: 0xFCC (R/ )  TPIU_DEVTYPE */
  #endif
}  ;


  /**
    \brief  Structure type to access the Core Debug Register (CoreDebug).
   */
struct core_debug_t
{
  struct halting_control_and_status_t : public read_write_32_t
  {
    // TODO
  } ;

  struct core_register_selector_t : public read_write_32_t
  {
    // TODO
  } ;

  struct core_register_data_t : public read_write_32_t
  {
    // TODO
  } ;

  struct exception_and_monitor_control_t : public read_write_32_t
  {
    struct reset_vector_catch_t     { enum enum_t { offset=0,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_memmanage_exception_t     { enum enum_t { offset=4,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_usage_fault_access_coprocessor_t { enum enum_t { offset=5,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_usage_fault_checking_error_t { enum enum_t { offset=6,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_usage_fault_state_information_error_t { enum enum_t { offset=7,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_bus_fault_exception_t { enum enum_t { offset=8,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_exception_entry_return_t { enum enum_t { offset=9,  mask=1, disable=0 , enable } ; } ;
    struct halting_trap_on_hard_fault_exception_t { enum enum_t { offset=10,  mask=1, disable=0 , enable } ; } ;
    struct monitor_exception_t { enum enum_t { offset=16,  mask=1, disable=0 , enable } ; } ;
    struct monitor_exception_pending_t { enum enum_t { offset=17,  mask=1, clear=0 , set } ; } ;
    struct monitor_step_t { enum enum_t { offset=18,  mask=1, no_action=0 , step } ; } ;
    struct semaphore_t { enum enum_t { offset=19,  mask=1 } ; } ;
    struct debug_and_trace_t { enum enum_t { offset=24,  mask=1, disable=0, enable } ; } ;
  } ;

  inline  void debug_and_trace(const exception_and_monitor_control_t::debug_and_trace_t::enum_t val){  exception_and_monitor_control.rmw(val) ;}
  inline  void debug_and_trace_disable() {  exception_and_monitor_control.rmw( exception_and_monitor_control_t::debug_and_trace_t::disable) ;}
  inline  void debug_and_trace_enable() {  exception_and_monitor_control.rmw( exception_and_monitor_control_t::debug_and_trace_t::enable) ;}
  inline  auto debug_and_trace()const {  return exception_and_monitor_control.rd<exception_and_monitor_control_t::debug_and_trace_t>();}


  halting_control_and_status_t    debug_halting_control_and_status          ; // DHCSR;  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  core_register_selector_t        core_register_selector                    ; // DCRSR;  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  core_register_data_t            core_register_data                        ; // DCRDR;  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  exception_and_monitor_control_t exception_and_monitor_control ; // DEMCR;  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */

} ;

struct mpu_t
{
  // TODO
  /**
    \brief  Structure type to access the Memory Protection Unit (MPU).
   */
#if 0
  __IM  uint32_t TYPE;                   /*!< Offset: 0x000 (R/ )  MPU Type Register */
  __IOM uint32_t CTRL;                   /*!< Offset: 0x004 (R/W)  MPU Control Register */
  __IOM uint32_t RNR;                    /*!< Offset: 0x008 (R/W)  MPU Region RNRber Register */
  __IOM uint32_t RBAR;                   /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register */
  __IOM uint32_t RASR;                   /*!< Offset: 0x010 (R/W)  MPU Region Attribute and Size Register */
  __IOM uint32_t RBAR_A1;                /*!< Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register */
  __IOM uint32_t RASR_A1;                /*!< Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
  __IOM uint32_t RBAR_A2;                /*!< Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register */
  __IOM uint32_t RASR_A2;                /*!< Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
  __IOM uint32_t RBAR_A3;                /*!< Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register */
  __IOM uint32_t RASR_A3;                /*!< Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
#endif
}  ;

struct fpu_t
{
  // TODO
  // http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0646b/Bhccjgga.html

  uint32_t reserved0[1U];
  uint32_t _floating_point_context_control ;          //FPCCR;                  /*!< Offset: 0x004 (R/W)  Floating-Point Context Control Register */
  uint32_t _floating_point_context_address_register ; //FPCAR;                  /*!< Offset: 0x008 (R/W)  Floating-Point Context Address Register */
  uint32_t _floating_point_default_status_control ;   //FPDSCR;                 /*!< Offset: 0x00C (R/W)  Floating-Point Default Status Control Register */
  const uint32_t _media_and_fp_feature0;              // MVFR0;                 /*!< Offset: 0x010 (R/ )  Media and FP Feature Register 0 */
  const uint32_t _media_and_fp_feature1;              // MVFR1;                 /*!< Offset: 0x014 (R/ )  Media and FP Feature Register 1 */
}  ;

/* Memory mapping of Cortex-M4 Hardware */


/* Memory mapping of Cortex-M4 Hardware */
static const uint32_t scs_addr =           0xE000E000UL;                            /*!< System Control Space Base Address */
static const uint32_t itm_addr =           0xE0000000UL;                            /*!< ITM Base Address */
static const uint32_t dwt_addr =           0xE0001000UL;                            /*!< DWT Base Address */
static const uint32_t tpi_addr =           0xE0040000UL;                            /*!< TPI Base Address */
static const uint32_t core_debug_addr =    0xE000EDF0UL;                            /*!< Core Debug Base Address */
static const uint32_t sys_tick_addr =      scs_addr +  0x0010UL;                    /*!< SysTick Base Address */
static const uint32_t nvic_addr =          scs_addr +  0x0100UL;                    /*!< NVIC Base Address */
static const uint32_t scb_addr =           scs_addr +  0x0D00UL;                    /*!< System Control Block Base Address */
static const uint32_t mpu_addr =           scs_addr +  0x0D90UL;                    /*!< Memory Protection Unit */
static const uint32_t fpu_addr =           scs_addr +  0x0F30UL;                    /*!< Floating Point Unit */

static const uint32_t  nvic_prio_bits  =  4 ;

static scnscb_t&     scnscb    = *((scnscb_t*) scs_addr);
static scb_t&        scb       = *((scb_t*) scb_addr);
static sys_tick_t&   sys_tick  = *((sys_tick_t*) sys_tick_addr);
// ---- !!!  static nvic_t&       nvic      = *((nvic_t*) nvic_addr); // переехало на уровнь выше(stm32) для биндинга в stm32f4::nvic_t
static itm_t&        itm       = *((itm_t*) itm_addr);
static dwt_t&        dwt       = *((dwt_t*) dwt_addr);
static tpi_t&        tpi       = *((tpi_t*) tpi_addr);
static core_debug_t& core_debug= *((core_debug_t*) core_debug_addr);
static mpu_t&        mpu       = *((mpu_t*) mpu_addr);
static fpu_t&        fpu       = *((fpu_t*) fpu_addr);

}

using namespace cortex_m4 ;

#include "cortex_m++.h"

#endif // __CORTEX_M4++_H__



