#ifndef __AS5407_H__
#define __AS5407_H__

#include "appdefs.h"

class as5407_t
{
  public:

  class command_t
  {
    public:
     inline command_t(uint16_t address, bool read=true)
     {
       this->address = address ;
       this->read = read ;

       uint16_t tmp = *((uint16_t*)this);
       parity = 0 ;
       for ( uint8_t bit = 0 ; bit < 15 ; bit++ )
	 {
	   if ( tmp & 1) parity++ ;
	   tmp >>= 1 ;
	 }
     }

     uint16_t inline val() { return *((uint16_t*)this); }

    protected:
      inline command_t(){}
    private :
     uint16_t address : 14 ;
     uint16_t read    : 1  ;
     uint16_t parity  : 1  ;

  } ;


  struct data_t
  {

    data_t(const uint16_t val)  { *this = val; }

    inline data_t& operator = ( const uint16_t val) { *((uint16_t*)this) = val; return *this ; }

    bool inline verify ()
      {
         uint16_t tmp = *((uint16_t*)this);
         for ( uint8_t bit = 0 ; bit < 15 ; bit++ )
	    {
	      if ( tmp & 1) parity++ ;
	      tmp >>= 1 ;
	    }
         return parity ;
      }

     uint16_t val             : 14 ;
     uint16_t error           : 1  ;
     uint16_t parity          : 1  ;

  } ;

  enum reg_addr_t:uint16_t
      { nop=0,
        error=1,
	programming=3,
	diagnostic_and_agc=0x3ffc,
	magnitude=0x3ffd,
	angle_raw=0x3ffe,
	angle_with_comp=0x3fff,

	zero_pos_msb=0x16,
	zero_pos_lsb=0x17,

	setting1 = 0x18,
	setting2 = 0x19


      } ;

  union error_t
     {
       uint16_t val ;
       struct
        {
           uint16_t framing         : 1 ;
           uint16_t invalid_command : 1 ;
           uint16_t parity          : 1 ;
        };
     };

  union programming_t
     {
       uint16_t val ;
       struct
        {
           uint16_t programing_enable : 1 ;
           uint16_t : 1 ;
           uint16_t refresh           : 1 ;
           uint16_t start             : 1 ;
           uint16_t : 2 ;
           uint16_t verify            : 1 ;
        };
     };

  union diagnostic_t
     {
       uint16_t val ;
       struct
        {
           uint16_t automatic_gain_control : 8 ;
           uint16_t offset_compensation    : 1 ;
           uint16_t cordic_owerflow        : 1 ;
           uint16_t mgnetic_field_strength_too_low : 1 ;
           uint16_t mgnetic_field_strength_too_high: 1 ;
        };
     };


  typedef void (*io_init_t)();
  typedef uint16_t (*io_transaction_t)(uint16_t command);

  struct io_t
     {
        io_init_t  init;
        io_transaction_t transaction;
     }  ;


   as5407_t(const io_t& io): io(io)
     {
     }

   ~as5407_t()
     {
     }

   uint16_t inline angle()
     {
        command_t cmd(angle_raw) ;
        data_t data = io.transaction(cmd.val());;
        return data.val ;
     }

   uint16_t inline zero_pos()
     {
        uint16_t tmp ;

        command_t cmd1(zero_pos_msb) ;
        io.transaction(cmd1.val());
        command_t cmd2(zero_pos_lsb) ;
        tmp = io.transaction(cmd2.val()) << 6 ;
        command_t cmd3(nop) ;
        tmp |= ( io.transaction(cmd3.val()) & 0b111111) ;
        return tmp ;
     }


   float inline rad()
     {
        return 2 * pi * angle() / ((1 << 14) - 1 ) ;
     }

   float inline grad()
     {
        return 360 * angle() / ((1 << 14) - 1 ) ;
     }




protected:

private:
   static constexpr float pi = 3.14159265359 ;
   const io_t& io ;
} ;

#endif __AS5407_H__



/*

#include "pos_hall.h"
#include "sensors/position/as5407.h"

void pos_sensor_io_init()
{
  // инициализация SPI
  gpio_t::pin_configure(POS_SENSOR_CS);
  gpio_t::pin_configure(POS_SENSOR_SCK);
  gpio_t::pin_configure(POS_SENSOR_MISO);
  gpio_t::pin_configure(POS_SENSOR_MOSI);

  pos_sensor_spi.clock_enable();
  pos_sensor_spi.reset();
  pos_sensor_spi.ss_output_enable();

  pos_sensor_spi.master_selection_master();
  pos_sensor_spi.boud_rate_fpclk_div_32();
  pos_sensor_spi.clock_polarity_hight();
  pos_sensor_spi.clock_phase_second_clock();
  pos_sensor_spi.data_frame_format_word();
  pos_sensor_spi.data_format_msb();

  spi2.enable();
}
uint16_t pos_sensor_transaction(uint16_t command)
{
  uint16_t data ;

  POS_SENSOR_CS.port.pin_reset(POS_SENSOR_CS.bit ) ;

  pos_sensor_spi.write( command );
  pos_sensor_spi.wait_tx_empty();
  pos_sensor_spi.wait_rx_not_empty();
  data = pos_sensor_spi.read() ;
  pos_sensor_spi.wait_not_busy();

  POS_SENSOR_CS.port.pin_set(POS_SENSOR_CS.bit ) ;
  return data ;

}

// define a io struct
const as5407_t::io_t pos_sensor_io =
    {
	  .init  = pos_sensor_io_init,
	  .transaction = pos_sensor_transaction ,
    };


// create object
as5407_t  pos_sensor(pos_sensor_io);

*/







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
