/*
 * armv6_m++.h
 *
 *  Created on: 2 дек. 2018 г.
 *      Author: klen
 */

#ifndef __ARMV6_M++_H__
#define __ARMV6_M++_H__

#include "types++.h"

namespace armv6_m
{
__inline_static__ void     nop()  { asm volatile ("nop" ::: "memory"); }
  #define                  nop_rep(val) asm volatile (".rep " #val "\n nop\n .endr\n" ::: "memory")

__inline_static__ void     nop_loop(){ while (1) nop();}
__inline_static__ void     nop_while(const uint32_t n) {volatile uint32_t t = n; while (t--) nop(); }

__inline_static__ void     svc (const uint8_t val) { asm volatile ("svc %[immediate]"::[immediate] "I" (val));}
__inline_static__ void     dsb() { asm volatile ("dsb 0xf":::"memory"); }
__inline_static__ void     isb() { asm volatile ("isb 0xf":::"memory"); }
__inline_static__ void     dmb() { asm volatile ("dmb 0xf":::"memory"); }
__inline_static__ void     enable_irq() { asm volatile ("cpsie i" ::: "memory"); }
__inline_static__ void     disable_irq() { asm volatile ("cpsid i" ::: "memory");}
__inline_static__ uint32_t control() { uint32_t res; asm volatile ("mrs %0, control" : "=r" (res) );  return(res); }
__inline_static__ void     control(uint32_t control){ asm volatile ("msr control, %0" :: "r" (control) : "memory"); }
__inline_static__ uint32_t ipsr(){ uint32_t res; asm volatile ("mrs %0, ipsr" : "=r" (res) ); return(res); }
__inline_static__ uint32_t apsr(){ uint32_t res; asm volatile ("mrs %0, apsr" : "=r" (res) ); return(res);}
__inline_static__ uint32_t xpsr(){ uint32_t res; asm volatile ("mrs %0, xpsr" : "=r" (res) ); return(res);}
__inline_static__ uint32_t psp(){ uint32_t res; asm volatile ("mrs %0, psp\n"  : "=r" (res) ); return(res); }
__inline_static__ void     psp(uint32_t top_of_proc_stack){ asm volatile ("msr psp, %0\n" : : "r" (top_of_proc_stack) : "sp");}
__inline_static__ uint32_t msp(){ uint32_t res; asm volatile ("mrs %0, msp\n" : "=r" (res) ); return(res);}
__inline_static__ void     msp(uint32_t top_of_main_stack){ asm volatile ("msr msp, %0\n" : : "r" (top_of_main_stack) : "sp");}
__inline_static__ uint32_t primask(){ uint32_t res; asm volatile ("mrs %0, primask" : "=r" (res) );  return(res);}
__inline_static__ void     primask(uint32_t val) { asm volatile ("msr primask, %0" : : "r" (val) : "memory");}
__inline_static__ void     enable_fault_irq(){ asm volatile ("cpsie f" : : : "memory");}
__inline_static__ void     disable_fault_irq(){asm volatile ("cpsid f" : : : "memory");}
__inline_static__ uint32_t basepri(){ uint32_t res; asm volatile ("mrs %0, basepri" : "=r" (res) );  return(res);}
__inline_static__ void     basepri(uint32_t val){ asm volatile ("msr basepri, %0" : : "r" (val) : "memory");}
__inline_static__ void     basepri_max(uint32_t val){ asm volatile ("msr basepri_max, %0" : : "r" (val) : "memory");}
__inline_static__ uint32_t faultmask() { uint32_t res; asm volatile ("mrs %0, faultmask" : "=r" (res) ); return(res);}
__inline_static__ void     faultmask(uint32_t fault_mask){asm volatile ("msr faultmask, %0" : : "r" (fault_mask) : "memory");}
__inline_static__ void     wfi(){ asm volatile ("wfi"); }
__inline_static__ void     wfe(){ asm volatile ("wfe"); }
__inline_static__ void     sev(){ asm volatile ("sev"); }
__inline_static__ uint32_t rev(uint32_t val) { return __builtin_bswap32(val);} ;
__inline_static__ uint32_t rev16(uint32_t val){ uint32_t res; asm volatile ("rev16 %0, %1" : "=r" (res) : "r" (val) ); return(res);}
__inline_static__ int32_t  revsh(int32_t val){ return (short)__builtin_bswap16(val);} ;
__inline_static__ uint32_t ror(uint32_t val, uint32_t shift){ return (val >> shift) | (val << (32U - shift));}
__inline_static__ int32_t  clrsb(uint32_t val) { return __builtin_clrsb(val);} ;
__inline_static__ void     bkpt(uint8_t val=0){ asm volatile ("bkpt %0" :: "i" (val) ); }


//-------------------------------------------------------------------------
void __attribute__((weak,used))  hard_fault_exception_handler_c(uint32_t* hardfault_args)
{
	volatile uint32_t stacked_r0 =  hardfault_args[0];
	volatile uint32_t stacked_r1 =  hardfault_args[1];
	volatile uint32_t stacked_r2 =  hardfault_args[2];
	volatile uint32_t stacked_r3 =  hardfault_args[3];
	volatile uint32_t stacked_r12 = hardfault_args[4];
	volatile uint32_t stacked_lr =  hardfault_args[5];
	volatile uint32_t stacked_pc =  hardfault_args[6];
	volatile uint32_t stacked_psr = hardfault_args[7];

	volatile uint8_t trigger = 1 ;

	while (trigger)
  		{
			nop();
  		}

       // under debugger: return to situation context
       asm volatile (    "mov r0,  %[reg_r0]   \n"
  	                 "mov r1,  %[reg_r1]   \n"
  	                 "mov r2,  %[reg_r2]   \n"
  	                 "mov r3,  %[reg_r3]   \n"
  	                 "mov r12, %[reg_r12]  \n"
  	                 "mov lr,  %[reg_lr]   \n"
  	                 "mov pc,  %[reg_pc]   \n"
  	                 :
  	                 : [reg_r0] "r"(stacked_r0),
			   [reg_r1] "r"(stacked_r1),
			   [reg_r2] "r"(stacked_r2),
			   [reg_r3] "r"(stacked_r3),
			   [reg_r12]"r"(stacked_r12),
			   [reg_lr] "r"(stacked_lr),
			   [reg_pc] "r"(stacked_pc)
  	                 :
		   );

	(void) stacked_r0 ;
	(void) stacked_r1 ;
	(void) stacked_r2 ;
	(void) stacked_r3 ;
	(void) stacked_r12 ;
	(void) stacked_lr ;
	(void) stacked_pc ;
	(void) stacked_psr ;
}

//-------------------------------------------------------------------------
__attribute__((weak)) void hard_fault_exception_irq_handler()
{
  // read PSP and save return adress from stack sutable for M0/M0+ core
__asm volatile
      (
	  ".syntax unified                    \n"
          "      movs r0, #4                  \n"
	  "      mov  r1, lr                  \n"
	  "      tst  r1, r0                  \n"
          "      beq  _msp_select             \n"
	  "      mrs   r0, psp                \n"
	  "      b     _call_handler          \n"
	  " _msp_select:                      \n"
	  "      mrs   r0, msp                \n"
          " _call_handler:                    \n"
	  "      mov r2, %[hfh_addr]          \n"
          "      bx r2                        \n"
	  ".syntax divided                    \n"
	  : : [hfh_addr] "r" (hard_fault_exception_handler_c) :
      );
} ;

} // namespace armv6_m

using namespace armv6_m ;

#endif /* __ARMV6_M++_H__ */
