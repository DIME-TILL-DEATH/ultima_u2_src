#ifndef __LTC2654_H__
#define __LTC2654_H__

#include "stdint.h"
#include "sdk.h"

class ltc2654_t
{
public:

  enum command_t
  {
   c_write = 0,
   c_update,
   c_write_all_update,
   c_write_update,
   c_power_down,
   c_power_down_chip,
   c_select_internal_ref,
   c_select_external_ref,
   c_no_operation = 15
  } ;

  enum address_t
  {
    a_dac_a=0,
    a_dac_b,
    a_dac_c,
    a_dac_d,
    a_dac_all = 15
  }  ;

  typedef void (*io_init_t)();
  typedef void (*io_write_t)(const command_t cmd, const address_t addr, const uint16_t val);
  typedef void (*io_clear_t)();

  typedef struct
  {
    io_init_t  init;
    io_write_t write;
    io_clear_t clear;
    float      k[4] ;  // code = Vout * k  [ 1/V ]
  } io_t ;


  ltc2654_t(const io_t& io ): io(io)
     {
       io.init();
       //io.write (const command_t cmd, const address_t addr, const uint16_t val);
     }
   ~ltc2654_t()
     {

     }

   inline void clear()
     {
       io.clear();
     }

   inline void val( const address_t addr,  const uint16_t val , bool update = false )
     {
       if (addr == a_dac_all)
	    {
	      vals[a_dac_a] = vals[a_dac_b] = vals[a_dac_c] = vals[a_dac_d] = val;
	      io.write( update ? c_write_update : c_write, addr, val);
	    }
       else
	    {
	      vals[addr] = val ;
	      io.write( update ? c_write_update : c_write, addr, vals[addr]);
	    }
     }

   inline uint16_t val( const address_t addr)
     {
        return vals[addr];
     }

   inline void  voltage(const address_t addr, float u)
     {
        // перевод U -> val
        val( addr,  voltage2val(addr , u)) ;
     }

   inline float voltage( const address_t addr)
     {
        return val2voltage (addr , vals[addr]);
     }

   inline void update( const address_t addr = a_dac_all  )
     {

     }


protected:

   inline uint16_t voltage2val (const address_t addr, const float voltage)
     {
       if ( addr > a_dac_d) __throw_invalid_argument("voltage2val:: invalid addr") ;
       return  voltage * io.k[addr] ;
     }

   inline float val2voltage (const address_t addr, const uint16_t val)
     {
       if ( addr > a_dac_d) __throw_invalid_argument("val2voltage:: invalid addr") ;
       return  val / io.k[addr];
     }

private:

   const io_t& io ;
   uint16_t vals[4] ;  // code value lodaed to dac register
} ;

#endif __LTC2654_H__




//
/*  example for implement io and create a object

file:  dac8551.c
#include "dac8551.h"

void dac_a_io_init ()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    // init CS pins
    DACS_SPI_GPIO_CLOCK_ENABLE();
    GPIO_InitStruct.Pin = DACS_SPI_CS_A_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(DACS_SPI_PORT, &GPIO_InitStruct);

    // init SPI MOSI and CSK pins
    GPIO_InitStruct.Pin = DACS_SPI_MOSI_PIN|DACS_SPI_CLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(DACS_SPI_PORT, &GPIO_InitStruct);

    // init SPI
    DACS_SPI_CLK_ENABLE();
    SPI_HandleTypeDef hspi ;
    hspi.Instance = DACS_SPI;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLED;
    hspi.Init.CRCPolynomial     = 7;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    HAL_SPI_Init(&hspi);

    __HAL_SPI_ENABLE(&hspi);
}

void dac_b_io_init ()
{
      GPIO_InitTypeDef GPIO_InitStruct;
      // init CS pins
      DACS_SPI_GPIO_CLOCK_ENABLE();
      GPIO_InitStruct.Pin = DACS_SPI_CS_B_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
      HAL_GPIO_Init(DACS_SPI_PORT, &GPIO_InitStruct);
}

static void dac_spi_send (const dac8551_t::command_t& cmd )
{
    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    DACS_SPI->DR = cmd.mode ;
    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    while ( !((DACS_SPI->SR) & SPI_FLAG_RXNE));
    while ( ((DACS_SPI->SR) & SPI_FLAG_BSY));


    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    DACS_SPI->DR = cmd.hb ;
    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    while ( !((DACS_SPI->SR) & SPI_FLAG_RXNE));
    while ( ((DACS_SPI->SR) & SPI_FLAG_BSY));

    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    DACS_SPI->DR = cmd.lb ;
    while ( !((DACS_SPI->SR) & SPI_FLAG_TXE));
    while ( !((DACS_SPI->SR) & SPI_FLAG_RXNE));
    while ( ((DACS_SPI->SR) & SPI_FLAG_BSY));
}


void dac_a_spi_write (const dac8551_t::command_t& cmd)
{
    DACS_SPI_PORT->BSRR = DACS_SPI_CS_A_PIN << 16 ;
    dac_spi_send ( cmd ) ;
    DACS_SPI_PORT->BSRR = DACS_SPI_CS_A_PIN  ;
}

void dac_b_spi_write (const dac8551_t::command_t& cmd)
{
   DACS_SPI_PORT->BSRR = DACS_SPI_CS_B_PIN << 16 ;
   dac_spi_send ( cmd ) ;
   DACS_SPI_PORT->BSRR = DACS_SPI_CS_B_PIN  ;
}

// define a params
const float dac8551_ref = 4.096 ;
const float dac8551_k   = 1.0 ;

// define a io struct
const dac8551_t::io_t dac8551_a_io =
    {
	  .init  = dac_a_io_init,
	  .write = dac_a_spi_write ,
    };

const dac8551_t::io_t dac8551_b_io =
    {
	  .init  = dac_b_io_init,
	  .write = dac_b_spi_write ,
    };

// create object
dac8551_t  dac8551_a(dac8551_k, dac8551_ref , dac8551_a_io );
dac8551_t  dac8551_b(dac8551_k, dac8551_ref , dac8551_b_io );

 */
