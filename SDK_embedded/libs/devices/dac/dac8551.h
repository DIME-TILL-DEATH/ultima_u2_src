#ifndef __DAC8551_H__
#define __DAC8551_H__

#include "appdefs.h"

class dac8551_t
{
public:

  typedef enum
  {
   dmNormal = 0,
   dmOutput_1k = 1,
   dmOutput_2k = 2,
   dmHighZ = 3
  }mode_t ;

  typedef struct
  {
    uint8_t  mode ;
    union
    {
       uint16_t val  ;
       struct
       {
	 uint8_t lb ;
	 uint8_t hb ;
       };
    };
  } __PACKED__ command_t ;

  typedef void (*io_init_t)();
  typedef void (*io_write_t)(const command_t& cmd);


  typedef struct
  {
    io_init_t  init;
    io_write_t write;
  } io_t ;


   dac8551_t(const float& k,  const float& ref , const io_t& io ): k(k), ref(ref), io(io)
     {
       m = dmNormal ;
       io.init();
       command_t cmd ;
       cmd.mode = m ;
       cmd.val  = 0 ;
       io.write (cmd);
     }
   inline float ref_voltage() { return ref ; }
   ~dac8551_t()
     {

     }

   void mode(mode_t mode)
     {
       m = mode ;
       command_t cmd ;
       cmd.mode = m ;
       cmd.val  = 0 ;
       io.write(cmd);
     }
   mode_t inline  mode() { return m; } ;

   inline uint16_t val () { return v; }
   inline void val(uint16_t v)
   {
     this->v = v ;
     m = dmNormal ;
     command_t cmd ;
     cmd.mode = m ;
     cmd.val  = this->v ;
     io.write(cmd);
   }

   inline float voltage() { return  ref*((1.0f+k)*v/65536.0f - k) ; }
   inline void  voltage(float val)
     {
       v = (val / ref + k )*65536.0f/(1.0f+k) ;
       m = dmNormal ;
       command_t cmd ;
       cmd.mode = m ;
       cmd.val  = v ;
       io.write(cmd);
     }


protected:
private:

   const io_t& io ;
   const float& k   ;  // k=R2/R1 in OUT OPA circut. see detait in www.ti.com/lit/ds/symlink/dac8551.pdf, BIPOLAR OPERATION USING THE DAC8551, page 19
   const float& ref ;
   mode_t m ;
   uint16_t v ;  // code value lodaed to dac register
} ;

#endif __DAC8551_H__




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
