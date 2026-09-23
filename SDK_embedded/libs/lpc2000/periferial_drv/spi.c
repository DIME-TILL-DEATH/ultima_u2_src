#include "spi.h"
#include "lpc2148.h"
//------------------------------------------------------------
static uint32_t spi_1_chip_select_pin  ;
static volatile uint32_t* spi_1_chip_select_fioclr_reg ;
static volatile uint32_t* spi_1_chip_select_fioset_reg ;
//------------------------------------------------------------
/*
void spi_isr(void) __attribute__((interrupt("IRQ"))) ;
void spi_isr(void)
{
   if ((S1SPSR & 0xF8) == 0x80)
  {
      *spi_msg++ = S1SPDR; // read byte from slave
      if (--spi_count > 0)
         S1SPDR = *spi_msg; // sent next byte
      else
    	  spi_state = SPI_OK; // transfer completed
   } 
   else // SPI error
   {
     *spi_msg = S1SPDR; // dummy read to clear flags
     spi_state = SPI_ERROR;
    }
  S1SPINT = 0x01; // reset interrupt flag
  VICVectAddr = 0; // reset VIC
}
*/
//------------------------------------------------------------
void spi_1_init(spi_1_cs_port port , uint32_t pin)
{
/*
	VICVectAddr1 = (uint32_t) spi_isr;
	VICVectCntl1 = 0x2A; // Channel0 on Source#10 ... enabled
	VICIntEnable |= 0x400; // 10th bit is the SPI
*/
	PCONP  |= (1<<PCONP_PCSPI1_BIT) ;
	// reset pin-functions
	PINSEL1 &= ~(
			(3UL << 2) | // SCK
			(3UL << 4) | // MISO
			(3UL << 6) | // MOSI
			(3UL << 8)); // SSEL

	// set pin-functions to SSP
	PINSEL1 |= (
			(2UL << 2) | // SCK
			(2UL << 4) | // MISO
			(2UL << 6)); // MOSI


#define SSPCR0_DSS      0
#define SSPCR0_CPOL     6
#define SSPCR0_CPHA     7
#define SSPCR0_SCR      8
#define SSPCR1_SSE      1
#define SSPSR_TNF       1
#define SSPSR_RNE       2
#define SSPSR_BSY       4
	// configure and enable as SPI-Master
	SSPCR0 = ((8-1) << SSPCR0_DSS ) | (0 << SSPCR0_CPOL) |
		 	 (0 << SSPCR0_CPHA ) | (0 << SSPCR0_SCR);
	SSPCR1 = (1 << SSPCR1_SSE);

	SSPCPSR = 24 ;

	/*
	SSPCCR1 = 32; // SCK = 1 MHz, counter > 8 and even
	SSPCR1 = SSPCR_MSTR ;  // CPHA=0, CPOL=0, master mode, MSB first,
			 //SSPCR_SPIE ; // interrupt disable
    */

	// установка вывода CS
	spi_1_chip_select_pin = pin ;
	if ( port == scspFIO0 )
	{
		FIO0DIR |= (1 << pin) ;
		spi_1_chip_select_fioclr_reg = &FIO0CLR ;
		spi_1_chip_select_fioset_reg = &FIO0SET ;
	}
	else
	{
		FIO1DIR |= (1 << pin) ;
		spi_1_chip_select_fioclr_reg = &FIO1CLR ;
		spi_1_chip_select_fioset_reg = &FIO1SET ;
	}

	spi_1_chip_enable();
	spi_1_chip_disable();
}
//------------------------------------------------------------
void spi_1_chip_enable()
{
    *spi_1_chip_select_fioclr_reg = (1<<spi_1_chip_select_pin) ;
}
//------------------------------------------------------------
void spi_1_chip_disable()
{
	*spi_1_chip_select_fioset_reg = (1<<spi_1_chip_select_pin) ;
}
//------------------------------------------------------------
uint8_t spi_1_write_byte( uint8_t byte_out )
{
	uint8_t byte_in;
	while( !( SSPSR & (1 << SSPSR_TNF)));
	SSPDR = byte_out;
	while( !( SSPSR & ( 1 << SSPSR_RNE)));
	byte_in = SSPDR;
	return byte_in;
}
//------------------------------------------------------------
void spi_1_read_block( uint8_t *buf, uint32_t size )
{
   while ( size-- )
   {
	   while( !( SSPSR & (1 << SSPSR_TNF)));
	   SSPDR = 0xff ;
	   while( !( SSPSR & ( 1 << SSPSR_RNE))) ;
	   *(buf++) = SSPDR ;
   }
}
//------------------------------------------------------------
void spi_1_write_block( uint8_t *buf, uint32_t size )
{
  uint8_t dummy ;
  while ( size-- )
   {
	   while( !( SSPSR & (1 << SSPSR_TNF)));
	   SSPDR = *(buf++) ;
	   while( !( SSPSR & ( 1 << SSPSR_RNE))) ;
	   dummy = SSPDR ;
   }
  (void)dummy ;
}
//------------------------------------------------------------
