#ifndef __HMC832_H__
#define __HMC832_H__

#include "appdefs.h"

class hmc832_t
{
  public:

 /* class command_t
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
*/
  enum reg_addr_t:uint16_t
      { id=0,
        read_address_rst_strobe=0,
	rst=1,
	ref_div=2,
	freq_int=3,
	freq_frac=4,
	vco_spi=5,
	delta_sigma_config=6,
	lock_detect=7,
	analog_enable=8,
	charge_pump=9,
	autocalibration=0xa,
	phase_detector=0xb,
	exact_freq=0xc,
	spi_rdiv=0xf,
	vco_tune=0x10,
	sar=0x11,
	gpo2=0x12,
	builtin_selftest=0x13,

	vco_tuning=0,
	vco_enable=1,
	vco_output_divider=2,
	vco_config=3,
	vco_cal_bias=4,
	vco_cf_cal=5,
	vco_msb_cal= 6,
	vco_output_power=7,
      } ;

  typedef void (*io_init_t)();
  typedef uint16_t (*io_transaction_t)(uint16_t command);

  struct io_t
     {
        io_init_t  init;
        io_transaction_t transaction;
     }  ;


  hmc832_t(const io_t& io): io(io)
     {
     }

   ~hmc832_t()
     {
     }

   uint16_t inline freq()
     {
        command_t cmd(angle_raw) ;
        data_t data = io.transaction(cmd.val());;
        return data.val ;
     }

   uint16_t inline power()
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


protected:

private:
   const io_t& io ;
} ;

#endif __HMC832_H__



/*

#include "pos_hall.h"
#include "sensors/synthesizer/hmc832.h"

void synthesizer_io_init()
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
uint16_t synthesizer_read(uint16_t command)
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

uint16_t synthesizer_write(uint16_t command)
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
const hmc832_t::io_t hmc832_io =
    {
	  .init  = synthesizer_io_init,
	  .read = synthesizer_read ,
	  .write = synthesizer_write ,
    };


// create object
hmc832_t  synthesizer(hmc832_io);

*/



