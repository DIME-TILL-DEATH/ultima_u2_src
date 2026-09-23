#include "stm32++.h"

// -------- интерфейс системных вызовов ------------------
 uint32_t __attribute__((noinline)) sys_call_1(uint32_t p1, uint32_t p2) { asm volatile ("svc #1") ; return p1; }
 uint32_t __attribute__((noinline)) sys_call_2(uint32_t p1, uint32_t p2) { asm volatile ("svc #2") ; return p1; }
 uint32_t __attribute__((noinline)) sys_call_3(uint32_t p1, uint32_t p2) { asm volatile ("svc #3") ; return p1; }
 uint32_t __attribute__((noinline)) sys_call_15(uint32_t p1, uint32_t p2) { asm volatile ("svc #15") ; return p1; }

// -------- обработчики системных вызовов -----------------

extern "C" __attribute__((used)) uint32_t __attribute__((noinline)) svc_1_handler(uint32_t* svc_args)
{
	return *svc_args = svc_args[0] * svc_args[1] ;
}

extern "C" __attribute__((used)) uint32_t __attribute__((noinline)) svc_2_handler(uint32_t* svc_args)
{
	return *svc_args *= 2;
}

extern "C" __attribute__((used)) uint32_t __attribute__((noinline)) svc_3_handler(uint32_t* svc_args)
{
	return *svc_args *= 3;
}
