#include "gpio.h"
#include "lpc21xx.h"

#define SCS (*(volatile unsigned *)0xE01FC1A0)
#define SCS_OFFSET 0x1A0
#define SCS_GPIO0M_MASK 0x1
#define SCS_GPIO0M 0x1
#define SCS_GPIO0M_BIT 0

void set_gpio0_mode( enum TGPIOMode gpio_mode )
{
  gpio_mode ? ( SCS |= 0x1 ) : ( SCS &= 0x2 ) ;
}

void set_gpio1_mode( enum TGPIOMode gpio_mode)
{
  gpio_mode ? ( SCS |= 0x2 ) : ( SCS &= 0x1 ) ;
}
  
enum TGPIOMode get_gpio0_mode()
{
  return SCS & 0x1 ;  
}
enum TGPIOMode get_gpio1_mode()
{
  return SCS >> 1 ;     
}


void set_io_port0_fast()
{ 
   SCS |= 0x1 ;
}
void set_io_port0_norm()
{ 
   SCS &= 0x2 ;
}

unsigned char get_io_port0_mode()
{ 
  return SCS & 0x1 ;
}

void set_io_port1_fast()
{ 
   SCS |= 0x2 ;
}
void set_io_port1_norm()
{ 
   SCS &= 0x1 ;
}

unsigned char get_io_port1_mode()
{ 
  return (SCS & 0x2) >> 1 ;
}
