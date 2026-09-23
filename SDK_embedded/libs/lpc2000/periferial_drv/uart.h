#ifndef __UART_H__
#define __UART_H__

#include "lpc21xx.h"

void init_uart0(unsigned int baud) ;

void read_uart0(char* buf , unsigned int size ) ;
void write_uart0(char* buf , unsigned int size ) ;

inline int getchar_uart0() 
{
  while( !(U0LSR & U0LSR_RDR_MASK ) );
  return (int)U0RBR ;
}
inline void putchar_uart0(char c)
{
  while( !(U0LSR & U0LSR_THRE_MASK ) )
  U0THR = c ;   
}

#endif /*__UART_H__*/
