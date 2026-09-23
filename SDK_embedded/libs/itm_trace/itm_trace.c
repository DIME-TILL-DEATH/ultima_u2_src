#include "itm_trace.h"
#include "stdint.h"

#define ITM_PORT *(volatile unsigned *)0xE0000000

/*********************************************************************
*
*       _Delay
*/
static void _Delay(int NumLoops) {
  volatile int i;

  for (i = 0; i < NumLoops; i++);
}

unsigned long GetCpuClock(void);

void itm_trace_init(uint32_t boud)
{
  uint32_t SWOPrescaler;

   *((volatile unsigned *)0xE000EDFC) = 0x01000000;   // "Debug Exception and Monitor Control Register (DEMCR)"
   *((volatile unsigned *)0xE0042004) = 0x00000027;
   *((volatile unsigned *)0xE00400F0) = 0x00000002;   // "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO)
  SWOPrescaler = (GetCpuClock() / boud) - 1;  // SWOSpeed in Hz
   *((volatile unsigned *)0xE0040010) = SWOPrescaler; // "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output
   *((volatile unsigned *)0xE0000FB0) = 0xC5ACCE55;   // ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC
   *((volatile unsigned *)0xE0000E80) = 0x0001000D;   // ITM Trace Control Register
   *((volatile unsigned *)0xE0000E40) = 0x0000000F;   // ITM Trace Privilege Register
   *((volatile unsigned *)0xE0000E00) = 0x00000001;   // ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port.
   *((volatile unsigned *)0xE0001000) = 0x400003FE;   // DWT_CTRL
   *((volatile unsigned *)0xE0040304) = 0x00000100;   // Formatter and Flush Control Register
/*
  i = 0;
  while (1) {
    _Delay(100);
    while (ITM_PORT == 0);       // Wait while Fifo full
    ITM_PORT = i;                // Output counter
    i++;
  }*/
}

void itm_trace_putc(int c)
{
  while (ITM_PORT == 0);
  ITM_PORT = c;
}
