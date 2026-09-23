#include "adc.h"
#include "pll.h"
#include "lpc21xx.h"

static unsigned int* Adc0_Vals = (unsigned int*)0xE0034010 ;

//-----------------------------------------------------------
void set_adc0( char channals , unsigned int sample_freq  )
{
   unsigned int adcr = channals ;  // установка каналов преобразования
   adcr |= ( get_pcclk() / sample_freq - 1) << ADCR_CLKDIV_BIT ;
   adcr |= ADCR_PDN   ;
   adcr |= ADCR_BURST ;
   ADCR = adcr ;
}
//-----------------------------------------------------------
void start_adc()
{
  //
}
//-----------------------------------------------------------
void stop_adc()
{
  //
}
//-----------------------------------------------------------
unsigned int get_adc0_val(unsigned int channal)
{
  return (Adc0_Vals[channal] >> ADDR_VddA_BIT) & 0x3FF ;
}
//-----------------------------------------------------------