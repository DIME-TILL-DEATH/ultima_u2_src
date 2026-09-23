/*
 * armv7e_m++.h
 *
 *  Created on: 6 авг. 2017 г.
 *      Author: klen
 */

#ifndef __ARMV7E_M++_H__
#define __ARMV7E_M++_H__

#include "types++.h"

namespace armv7e_m
{
__inline_static__ void     nop()  { asm volatile ("nop" ::: "memory"); }
  #define                  nop_rep(val) asm volatile (".rep " #val "\n nop\n .endr\n" ::: "memory")

__inline_static__ void     nop_loop(){ while (1) nop();}
__inline_static__ void     nop_while(const uint32_t n) {volatile uint32_t t = n; while (t--) nop(); }
__inline_static__ void     nop_wait(const volatile uint32_t n) { while (n) nop(); }

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
__inline_static__ uint32_t fpscr(){ NRO uint32_t res; asm volatile (""); asm volatile ("vmrs %0, fpscr" : "=r" (res) ); return(res); }
__inline_static__ void     fpscr(uint32_t val) { NRO asm volatile ("vmsr fpscr, %0" : : "r" (val) : "vfpcc"); }
__inline_static__ void     wfi(){ asm volatile ("wfi"); }
__inline_static__ void     wfe(){ asm volatile ("wfe"); }
__inline_static__ void     sev(){ asm volatile ("sev"); }
__inline_static__ uint32_t rev(uint32_t val) { return __builtin_bswap32(val);} ;
__inline_static__ uint32_t rev16(uint32_t val){ uint32_t res; asm volatile ("rev16 %0, %1" : "=r" (res) : "r" (val) ); return(res);}
__inline_static__ int32_t  revsh(int32_t val){ return (short)__builtin_bswap16(val);} ;
__inline_static__ uint32_t ror(uint32_t val, uint32_t shift){ return (val >> shift) | (val << (32U - shift));}
__inline_static__ uint32_t rbit(uint32_t val){ uint32_t res; asm volatile ("rbit %0, %1" : "=r" (res) : "r" (val) ); return(res);}
__inline_static__ uint32_t rrx(uint32_t val){ uint32_t res; asm volatile  ("rrx %0, %1" : "=r"(res) : "r"(val) ); return(res);}
__inline_static__ int32_t  clz(uint32_t val) { return __builtin_clz(val);} ;
__inline_static__ int32_t  ctz(uint32_t val) { return __builtin_ctz(val);} ;
__inline_static__ int32_t  clrsb(uint32_t val) { return __builtin_clrsb(val);} ;
__inline_static__ void     bkpt(uint8_t val=0){ asm volatile ("bkpt %0" :: "i" (val) ); }
__inline_static__ uint8_t  ldrexb(volatile uint8_t *addr){ uint32_t res; asm volatile ("ldrexb %0, %1" : "=r" (res) : "Q" (*addr) ); return ((uint8_t) res);}
__inline_static__ uint16_t ldrexh(volatile uint16_t *addr){uint32_t res; asm volatile ("ldrexh %0, %1" : "=r" (res) : "Q" (*addr) ); return ((uint16_t) res); }
__inline_static__ uint32_t ldrex(volatile uint32_t *addr){uint32_t res; asm volatile ("ldrex  %0, %1" : "=r" (res) : "Q" (*addr) ); return(res);}
__inline_static__ uint32_t strexb(uint8_t val, volatile uint8_t *addr){uint32_t res; asm volatile ("strexb %0, %2, %1" : "=&r" (res), "=Q" (*addr) : "r" ((uint32_t)val) ); return(res);}
__inline_static__ uint32_t strexh(uint16_t val, volatile uint16_t *addr){ uint32_t res; asm volatile ("strexh %0, %2, %1" : "=&r" (res), "=Q" (*addr) : "r" ((uint32_t)val) ); return(res);}
__inline_static__ uint32_t strex(uint32_t val, volatile uint32_t *addr){ uint32_t res; asm volatile ("strex %0, %2, %1" : "=&r" (res), "=Q" (*addr) : "r" (val) ); return(res);}
__inline_static__ void     clrex(void){asm volatile ("clrex" ::: "memory");}
__inline_static__ uint8_t  ldrbt(volatile uint8_t *addr){ uint32_t res; asm volatile ("ldrbt %0, %1" : "=r" (res) : "Q" (*addr) ); return ((uint8_t) res); }
__inline_static__ uint16_t ldrht(volatile uint16_t *addr){ uint32_t res; asm volatile ("ldrht %0, %1" : "=r" (res) : "Q" (*addr) );return ((uint16_t) res); }
__inline_static__ uint32_t ldrt(volatile uint32_t *addr){ uint32_t res; asm volatile ("ldrt %0, %1" : "=r" (res) : "Q" (*addr) ); return(res);}
__inline_static__ void     strbt(uint8_t val, volatile uint8_t *addr){ asm volatile ("strbt %1, %0" : "=Q" (*addr) : "r" ((uint32_t)val) );}
__inline_static__ void     strht(uint16_t val, volatile uint16_t *addr){asm volatile ("strht %1, %0" : "=Q" (*addr) : "r" ((uint32_t)val) );}
__inline_static__ void     strt(uint32_t val, volatile uint32_t *addr){ asm volatile ("strt %1, %0" : "=Q" (*addr) : "r" (val) );}
__inline_static__ int32_t  ssat(const int32_t val, const uint8_t sbit){ uint32_t res ; asm ("ssat %0, %1, %2" : "=r" (res) :  "I" (sbit), "r" (val) ); return res; }
__inline_static__ uint32_t usat(const uint32_t val, const uint8_t sbit){uint32_t res; asm ("usat %0, %1, %2" : "=r" (res) :  "I" (sbit), "r" (val) ); return res;}

// обертки арифметических инструкций uint32 -> uint64
//u64=u32xu32
__inline_static__ uint64_t umull (const uint32_t op1, const uint32_t op2){union llreg_u {uint32_t w32[2];uint64_t w64;} llr; asm volatile ("umull %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
//s64=s32*s32
__inline_static__  int64_t smull (const  int32_t op1, const  int32_t op2){union llreg   { int32_t w32[2]; int64_t w64;} llr; asm volatile ("smull %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
//u64=u32xu32+u64
__inline_static__ uint64_t umlal (const uint32_t op1, const uint32_t op2, const uint64_t acc){union llreg_u {uint32_t w32[2];uint64_t w64;} llr; llr.w64 = acc; asm volatile ("umlal %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
//s64=s32xs32+s64
__inline_static__  int64_t smlal (const  int32_t op1, const  int32_t op2, const  int64_t acc){union llreg   { int32_t w32[2]; int64_t w64;} llr; llr.w64 = acc; asm volatile ("smlal %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}

// обертки SIMD инструкций

__inline_static__ uint32_t sadd8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("sadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qadd8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shadd8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uadd8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqadd8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhadd8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhadd8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t ssub8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("ssub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qsub8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qsub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shsub8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shsub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t usub8 (const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("usub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqsub8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqsub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhsub8(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhsub8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t sadd16(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("sadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qadd16(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shadd16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uadd16(const  uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqadd16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhadd16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhadd16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t ssub16 (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("ssub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qsub16 (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qsub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shsub16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shsub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t usub16 (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("usub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqsub16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqsub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhsub16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhsub16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t sasx   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("sasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qasx   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shasx  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) );return(res);}
__inline_static__ uint32_t uasx   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqasx  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhasx  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhasx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t ssax   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("ssax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t qsax   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("qsax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t shsax  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("shsax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) );return(res);}
__inline_static__ uint32_t usax   (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("usax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uqsax  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uqsax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t uhsax  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uhsax %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t usad8  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("usad8 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t usada8 (const uint32_t op1, const uint32_t op2, uint32_t op3){uint32_t res; asm volatile ("usada8 %0, %1, %2, %3" : "=r" (res) : "r" (op1), "r" (op2), "r" (op3) );  return(res);}
__inline_static__ int32_t  ssat16 (const  int32_t op1, const uint8_t sbit) {int32_t res; asm volatile ("ssat16 %0, %1, %2" : "=r" (res) :  "I" (sbit), "r" (op1) ); return res; }
__inline_static__ uint32_t usat16 (const uint32_t op1, const uint8_t sbit){uint32_t res; asm volatile ("usat16 %0, %1, %2" : "=r" (res) :  "I" (sbit), "r" (op1) ); return res; }
__inline_static__ uint32_t uxtb16 (const uint32_t op1){ uint32_t res; asm volatile ("uxtb16 %0, %1" : "=r" (res) : "r" (op1)); return(res);}
__inline_static__ uint32_t uxtab16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("uxtab16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t sxtb16 (const uint32_t op1){uint32_t res; asm volatile ("sxtb16 %0, %1" : "=r" (res) : "r" (op1)); return(res);}
__inline_static__ uint32_t sxtab16(const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("sxtab16 %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t smuad  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("smuad %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) );return(res);}
__inline_static__ uint32_t smuadx (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("smuadx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t smlad  (const uint32_t op1, const uint32_t op2, const uint32_t op3){uint32_t res; asm volatile ("smlad %0, %1, %2, %3" : "=r" (res) : "r" (op1), "r" (op2), "r" (op3) );  return(res);}
__inline_static__ uint32_t smladx (const uint32_t op1, const uint32_t op2, const uint32_t op3){ uint32_t res; asm volatile ("smladx %0, %1, %2, %3" : "=r" (res) : "r" (op1), "r" (op2), "r" (op3) ); return(res);}
__inline_static__ uint64_t smlald (const uint32_t op1, const uint32_t op2, const uint64_t acc){ union llreg_u{ uint32_t w32[2]; uint64_t w64; } llr; llr.w64 = acc; asm volatile ("smlald %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
__inline_static__ uint64_t smlaldx(const uint32_t op1, const uint32_t op2, const uint64_t acc){ union llreg_u{ uint32_t w32[2]; uint64_t w64; } llr; llr.w64 = acc; asm volatile ("smlaldx %0, %1, %2, %3": "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
__inline_static__ uint32_t smusd  (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("smusd %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t smusdx (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("smusdx %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t smlsd  (const uint32_t op1, const uint32_t op2, const uint32_t op3){ uint32_t res; asm volatile ("smlsd %0, %1, %2, %3" : "=r" (res) : "r" (op1), "r" (op2), "r" (op3) );return(res);}
__inline_static__ uint32_t smlsdx (const uint32_t op1, const uint32_t op2, const uint32_t op3){ uint32_t res; asm volatile ("smlsdx %0, %1, %2, %3" : "=r" (res) : "r" (op1), "r" (op2), "r" (op3) );  return(res);}
__inline_static__ uint64_t smlsld (const uint32_t op1, const uint32_t op2, const uint64_t acc){union llreg_u{ uint32_t w32[2]; uint64_t w64; } llr; llr.w64 = acc; asm volatile ("smlsld %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
__inline_static__ uint64_t smlsldx(const uint32_t op1, const uint32_t op2, const uint64_t acc){ union llreg_u{ uint32_t w32[2]; uint64_t w64;} llr;llr.w64 = acc; asm volatile ("smlsldx %0, %1, %2, %3" : "=r" (llr.w32[0]), "=r" (llr.w32[1]): "r" (op1), "r" (op2) , "0" (llr.w32[0]), "1" (llr.w32[1]) ); return(llr.w64);}
__inline_static__ uint32_t sel    (const uint32_t op1, const uint32_t op2){uint32_t res; asm volatile ("sel %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ int32_t  qadd   (const  int32_t op1, const int32_t op2){int32_t res; asm volatile ("qadd %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ int32_t  qsub   (const  int32_t op1, const int32_t op2){ int32_t res; asm volatile ("qsub %0, %1, %2" : "=r" (res) : "r" (op1), "r" (op2) ); return(res);}
__inline_static__ uint32_t smmla  (const  int32_t op1, const int32_t op2, const int32_t op3){int32_t res; asm volatile ("smmla %0, %1, %2, %3" : "=r" (res): "r"  (op1), "r" (op2), "r" (op3) ); return(res);}
__inline_static__ uint32_t pkhbt  (const uint32_t op1, const uint32_t op2, const uint8_t shift){ uint32_t res ; asm volatile("pkhbt %0, %1, %2, lsl %3" : "=r" (res) :  "r" (op1), "r" (op2), "I" (shift)  ); return res; }
__inline_static__ uint32_t pkhtb  (const uint32_t op1, const uint32_t op2, const uint8_t shift){ uint32_t res ; if (shift == 0) asm volatile ("pkhtb %0, %1, %2" : "=r" (res) :  "r" (op1), "r" (op2)  ); else asm ("pkhtb %0, %1, %2, asr %3" : "=r" (res) :  "r" (op1), "r" (op2), "I" (shift)  ); return  res; }

// FPU instructions

#if __ARM_FP & 0x2 /* half precision FPU */

  #define __ARM_FP_HALF_PRECISION__

  // VCVT{y}{cond}.F<32|64>.F16 <Sd|Dd>, Sm
  // VCVT{y}{cond}.F16.F<32|64> Sd, <Sm|Dm>
  // компилятор атоматически использует данные инструкции совместно с типом __fp16 при подаче опции -mfp16-format=ieee/arm

#endif

#if __ARM_FP & 0x4 /* single precision FPU */

  #define __ARM_FP_SINGLE__
  __inline_static__ float    vsqrtf  (const float val) { float res   ; asm volatile ("vsqrt.f32 %[dst], %[src]  \r\n" : [dst]"=w"(res) : [src]"w"(val) ); return (res) ;}
  __inline_static__ float    vabsf   (const float val) { float res   ; asm volatile ("vabs.f32  %[dst], %[src]  \r\n" : [dst]"=w"(res) : [src]"w"(val) ); return (res) ;}

#endif

#if __ARM_FP & 0x8 /* double precision FPU */

  #define __ARM_FP_DOUBLE__
  __inline_static__ double   vsqrt  (const double val) { double res ; asm volatile ("vsqrt.f64 %P[dst], %P[src]\r\n" : [dst]"=w"(res) : [src]"w"(val) ); return (res) ;}
  __inline_static__ double   vabs   (const double val) { double res ; asm volatile ("vabs.f64  %P[dst], %P[src]\r\n" : [dst]"=w"(res) : [src]"w"(val) ); return (res) ;}

#endif

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

  	(void)trigger ;

         // under debugger: return to situation context
         asm volatile (  "ldr r0,  %[reg_r0]   \n"
    	                 "ldr r1,  %[reg_r1]   \n"
    	                 "ldr r2,  %[reg_r2]   \n"
    	                 "ldr r3,  %[reg_r3]   \n"
    	                 "ldr r12, %[reg_r12]  \n"
    	                 "ldr lr,  %[reg_lr]   \n"
    	                 "ldr pc,  %[reg_pc]   \n"
    	                 :
    	                 : [reg_r0] "m"(stacked_r0),
  			   [reg_r1] "m"(stacked_r1),
  			   [reg_r2] "m"(stacked_r2),
  			   [reg_r3] "m"(stacked_r3),
  			   [reg_r12]"m"(stacked_r12),
  			   [reg_lr] "m"(stacked_lr),
  			   [reg_pc] "m"(stacked_pc)
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
  // read PSP and save return adress from stack sutable for M3/M4/M7 core
  __asm volatile
        (
  	  ".syntax unified           \n"
          "      tst  lr, #4         \n"
          "      ite  eq             \n"
  	  "      mrseq   r0, msp     \n"
          "      mrsne   r0, psp     \n"
          "      bx %[hfh_addr]      \n"
  	  ".syntax divided           \n"
  	  : : [hfh_addr] "r" (hard_fault_exception_handler_c) :
        );

} ;

} // namespace armv7e_m

using namespace armv7e_m ;

#endif /* __ARMV7E_M++_H__ */
