#include "uart.h"
#include "pll.h"

// константы для доступа к VIC. 
#define UART0_VIC_CHANNEL		( ( unsigned int ) 0x0006 )
#define UART0_VIC_CHANNEL_BIT	        ( ( unsigned int ) 0x0040 )
#define UART0_VIC_ENABLE		( ( unsigned int ) 0x0020 )
#define CLEAR_VIC_INTERRUPT		( ( unsigned int ) 0x0000 )

//-----------------------------------------------
/*
static void uart0_isr(void) __attribute__((interrupt("IRQ"))) ;
static void uart0_isr(void)
{
  // Чтение IIR для сброса прерывания и анализа источныка прерывания
  unsigned int Tmp = U0IIR ;
  char data ;
  // Обработка
  switch ((Tmp >> 1) & 0x7)
    {
      case 1:
        // THRE interrupt
        break;
      case 2:
        data = U0RBR ;
        break;
      case 3:
        // RLS interrupt 
        break;
      case 6:
        // CTI interrupt 
        break;
   }
 
  // сброс прерывания в VIC контроллере
 VICVectAddr = 0 ;
}
*/
//-----------------------------------------------
void init_uart0(unsigned int baud)
{
  /* настройка скорости передачи UART */
  unsigned int divisor = get_pcclk() / (16 * baud);
  
  U0LCR = 0x83 ; /* 8 bit, 1 stop bit, no parity, enable DLAB */
  U0DLL = divisor & 0xFF ;
  U0DLM = (divisor >> 8) & 0xFF ;
  U0LCR &= ~0x80 ; /* Disable DLAB */
  PINSEL0 |= 0x05 ;
  U0FCR = 7 ;
  // разрешение прерываний модулем UART
  // U0IER = 1 ;


  
  /* установка VIC для прерываний UART. */
  
  //VICIntEnable |= UART0_VIC_CHANNEL_BIT;
 
  // назначаем самый медленный слот
  
  //VICVectAddr15 = ( unsigned int ) uart0_isr;
  //VICVectCntl15 = UART0_VIC_CHANNEL | UART0_VIC_ENABLE;
}
//---------------------------------------------------------------------------------
// прием пакета данных через UART0

void read_uart0(char* buf , unsigned size )
{
  for (unsigned int c = 0 ; c < size ; c++)
    {
      while( !(U0LSR & U0LSR_RDR_MASK )) ;
      *buf = U0RBR ;
      buf++ ;
    } 
}
//----------------------------------------------------------------------------------
// передача пакета данных через UART0
void write_uart0(char* buf , unsigned size )
{
  for (unsigned int c = 0 ; c < size ; c++)
      {
        while( !(U0LSR & U0LSR_THRE_MASK )) ;
        U0THR = *buf ;
        buf++ ;
      } 
}
//----------------------------------------------------------------------------------
