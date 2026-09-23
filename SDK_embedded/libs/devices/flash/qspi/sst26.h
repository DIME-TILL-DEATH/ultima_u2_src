/*
 * sst26.h
 *
 *  Created on: Feb 14, 2019
 *      Author: klen
 */

#ifndef __SST26_H__
#define __SST26_H__

#include "arch.h" // for qspi_t

namespace sst26
{

  enum serial_interface_t { spi=1, sqi=3 };

template <const serial_interface_t serial_interface, const qspi_t::control_t::flash_memory_selection_t::enum_t chip, const uint8_t prescaler>
class sst26_t
{
  private:
   static constexpr uint8_t sst26vf016=0x41; /* 16 M-bit */
   static constexpr uint8_t sst26vf032=0x42; /* 32 M-bit */
   static constexpr uint8_t sst26vf064=0x43; /* 64 M-bit */

   enum command_t
     {
 	  // configuration
 	  cmd_nop = 0 ,
 	  cmd_reset_enable           = 0x66,
 	  cmd_reset_memory           = 0x99,
 	  cmd_enable_quad_io         = 0x38,
 	  cmd_reset_quad_io          = 0xff,
 	  cmd_read_status            = 0x05,
 	  cmd_write_status           = 0x01,
 	  cmd_read_config            = 0x35,
 	  // read
 	  cmd_read_memory            = 0x03,
 	  cmd_read_memory_high_speed = 0x0b,
 	  cmd_quad_output_read       = 0x6b,
 	  cmd_quad_io_read           = 0xeb,
 	  cmd_quad_dual_output_read  = 0x3b,
 	  cmd_quad_dual_io_read      = 0xbb,
 	  cmd_set_burst_length       = 0xc0,
 	  cmd_read_burst_with_wrap   = 0xec,

 	  // write
 	  cmd_write_enable           = 0x06,
 	  cmd_write_disable          = 0x04,
 	  cmd_erase_4k_memry_array   = 0x20,
 	  cmd_erase_64k_32k_8k_memry_array = 0xd8,
 	  cmd_erase_full_array       = 0xc7,
 	  cmd_page_programm          = 0x02,
 	  cmd_sqi_quad_page_program  = 0x32,
 	  cmd_suspends_program_erase = 0xb0,
 	  cmd_resumes_program_erase  = 0x30,

 	  // identification
 	  cmd_id_read                = 0x9f,
 	  cmd_sqi_id_read            = 0xaf,
 	  cmd_serial_flash_discoverable_parameters = 0x5a,


 	  // protection
 	  cmd_read_block_protection_register = 0x72,
 	  cmd_write_block_protection_register = 0x42,
 	  cmd_lock_down_block_brotection_register = 0x8d,
 	  cmd_non_volatile_write_lock_down_register = 0xe8,
 	  cmd_global_block_protection_unlock = 0x98,
 	  cmd_read_security_id = 0x88,
 	  cmd_program_user_security_id_area = 0xa5,
 	  cmd_lockout_security_id_programming = 0x85,

           //power
 	  cmd_deep_power_down = 0xb9,
 	  cmd_relese_deep_power_down_read_id = 0xab,
     } ;

   struct dev_id_t
    {
      uint8_t manufacturer ;
      uint8_t type ;
      uint8_t id ;
      uint8_t : 8 ;

      inline dev_id_t& operator = (const uint32_t val)
	  {
	     *((uint32_t*)this) = val ;
	     return *this ;
	  }
   } ;

   union status_t
    {
      uint8_t val ;
      struct
        {
          uint8_t busy : 1 ;
          uint8_t wel  : 1 ;
          uint8_t wse  : 1 ;
          uint8_t wsp  : 1 ;
          uint8_t wpld : 1 ;
          uint8_t sec  : 1 ;
          uint8_t      : 1 ;
          uint8_t busy2: 1 ;
       } ;
    } ;

   union configuration_t
    {
       uint8_t val ;
       struct
         {
           uint8_t      : 1 ;
           uint8_t ioc  : 1 ;
           uint8_t      : 1 ;
           uint8_t bpnv : 1 ;
           uint8_t      : 1 ;
           uint8_t      : 1 ;
           uint8_t      : 1 ;
           uint8_t wpen : 1 ;
         } ;
    } ;

  public:

   inline void init( size_t& sector_count )
    {
      gpio_t::pin_configure(QSPI_CS);
      gpio_t::pin_configure(QSPI_CLK);
      gpio_t::pin_configure(QSPI_IO0);
      gpio_t::pin_configure(QSPI_IO1);
      gpio_t::pin_configure(QSPI_IO2_WP);
      gpio_t::pin_configure(QSPI_IO3_HOLD);

      qspi.clock_enable();
      qspi.wait_not_busy();
      qspi.prescaler(prescaler);
      qspi.flash_memory_selection( chip );
      qspi.clock_mode_3();
      qspi.address_size_24_bit();
      qspi.state_enable();


      reset_quad_io();
      spi_reset_quad_io();

      spi_reset_enable();
      spi_reset_memory();
      spi_write_enable();
      spi_global_block_protection_unlock ();
      spi_write_disable();

      dev_id_t dev_id ;
      spi_read_id ( dev_id ) ;
      switch( dev_id.id )
	{
	  case sst26vf016:
	     qspi.flash_memory_size_bytes(2*1024*1024);
	     sector_count = 2*1024*1024 / 4096 ;
	     break ;
	  case sst26vf032:
	     qspi.flash_memory_size_bytes(4*1024*1024);
	     sector_count = 4*1024*1024 / 4096 ;
	     break ;
	  case sst26vf064:
	     qspi.flash_memory_size_bytes(8*1024*1024);
	     sector_count = 8*1024*1024 / 4096 ;
	     break ;
	  default:
	     std::__throw_invalid_argument("unknown chip id or device failure");
        }



      if (serial_interface==sqi)
           spi_enable_quad_io();


    }





  template < command_t cmd >
  inline void spi_command ()
    {
	  qspi.data_size(0);
	  qspi.communication_config.modify(
			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
			qspi_t::communication_config_t::address_mode_t::no,
			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
			qspi_t::communication_config_t::data_mode_t::no,
			qspi_t::communication_config_t::functional_mode_t::indirect_write,
			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
			qspi_t::communication_config_t::ddr_t::disable
                                     );
    }



  inline void spi_wait_for_busy_write_operation ()
    {
	  while ( spi_read_status().busy ) {} ;
    }

  inline void spi_reset_enable()
    {
	  spi_command <cmd_reset_enable>() ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }
  inline void spi_reset_memory()
    {
	  spi_command<cmd_reset_memory> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_enable_quad_io()
    {
	  spi_command<cmd_enable_quad_io> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_reset_quad_io()
    {
	  spi_command<cmd_reset_quad_io> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }


  inline void spi_read_config ( configuration_t& configuration )
    {
	  spi_command_read<cmd_read_config, 1 >();
  	  configuration.val = qspi.data ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline status_t spi_read_status ()
    {
	  spi_command_read<cmd_read_status, 1 >();
	  status_t status ;
	  status.val = *((volatile uint8_t*)&qspi.data) ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
	  return status ;
    }

  inline void spi_read_id ( dev_id_t& dev_id )
    {
	  spi_command_read<cmd_id_read, 3 >();
          dev_id = qspi.data.word ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_read_memory_high_speed ( const uint32_t address, const size_t size , void* dest )
    {
	  spi_command_address_read<cmd_read_memory_high_speed>(address, size, 8);
          for ( size_t i = 0 ; i < size ; i++ )
            {
    	       //((uint8_t*)dest)[i] = *((volatile uint8_t*)&qspi.data) ;
              ((uint8_t*)dest)[i] = qspi.data.byte ;
            }
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_read_memory_high_speed_word ( const uint32_t address, const size_t size , void* dest )
    {
          spi_command_address_read<cmd_read_memory_high_speed>(address, size, 8);
          for ( size_t i = 0 ; i < size / 4 ; i++ )
            {
    	       ((uint32_t*)dest)[i] = qspi.data.word ;
            }
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_write_enable()
    {
	  spi_command<cmd_write_enable> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_write_disable()
    {
	  spi_command<cmd_write_disable> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void spi_page_programm ( const uint32_t address, const size_t size , const void* src )
    {
       spi_write_enable();
       spi_command_address_write<cmd_page_programm>(address, size);
       for ( size_t i = 0 ; i < size ; i++ )
         {
    	   //*((volatile uint8_t*)&qspi.data)  =  ((uint8_t*)src)[i] ;
	   qspi.data.byte  =  ((uint8_t*)src)[i] ;
         }
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       spi_wait_for_busy_write_operation();
    }

  inline void spi_page_programm_word ( const uint32_t address, const size_t size , const void* src )
    {
       spi_write_enable();
       spi_command_address_write<cmd_page_programm>(address, size);
       for ( size_t i = 0 ; i < size/4 ; i++ )
         {
    	   qspi.data.word  =  ((uint32_t*)src)[i] ;
         }
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       spi_wait_for_busy_write_operation();
    }


  inline void spi_erase_4k_memry_array ( const uint32_t address )
    {
       spi_write_enable();
       spi_command_address<cmd_erase_4k_memry_array>(address);
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       spi_wait_for_busy_write_operation();
    }

  inline void spi_erase ()
    {
       spi_write_enable();
       spi_command<cmd_erase_full_array>();
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       spi_wait_for_busy_write_operation();
    }

  inline void spi_global_block_protection_unlock ()
    {
       spi_command<cmd_global_block_protection_unlock> () ;
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
    }
/*
  //  SQI ----------------
  inline void sqi_wait_for_busy_write_operation ()
    {
	  while ( sqi_read_status().busy ) {} ;
    }

  inline void sqi_write_enable()
    {
	  sqi_command<cmd_write_enable> () ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline status_t sqi_read_status ()
    {
	  sqi_command_read<cmd_read_status, 1 , 2>();
	  status_t status ;
	  status.val = *((volatile uint8_t*)&qspi.data) ;
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
	  return status ;
    }

  inline void sqi_reset_quad_io()
    {
        sqi_command<cmd_reset_quad_io> () ;
	qspi.wait_not_busy();
	qspi.transfer_complete_flag_clear();
    }

  inline void sqi_read_memory_high_speed_word ( const uint32_t address, const size_t size , void* dest )
    {
          sqi_command_address_read<cmd_read_memory_high_speed>(address, size, 6);
          for ( size_t i = 0 ; i < size / 4 ; i++ )
            {
    	       ((uint32_t*)dest)[i] = qspi.data ;
            }
	  qspi.wait_not_busy();
	  qspi.transfer_complete_flag_clear();
    }

  inline void sqi_erase_4k_memry_array ( const uint32_t address )
    {
       sqi_write_enable();
       sqi_command_address<cmd_erase_4k_memry_array>(address);
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       sqi_wait_for_busy_write_operation();
    }

  inline void sqi_page_programm_word ( const uint32_t address, const size_t size , const void* src )
    {
       sqi_write_enable();
       sqi_command_address_write<cmd_page_programm>(address, size);
       for ( size_t i = 0 ; i < size/4 ; i++ )
         {
    	   qspi.data  =  ((uint32_t*)src)[i] ;
         }
       qspi.wait_not_busy();
       qspi.transfer_complete_flag_clear();
       sqi_wait_for_busy_write_operation();
    }
*/

  //  common ----------------
    inline void wait_for_busy_write_operation ()
      {
  	  while ( read_status().busy ) {} ;
      }

    inline void write_enable()
      {
  	  command<cmd_write_enable> () ;
  	  qspi.wait_not_busy();
  	  qspi.transfer_complete_flag_clear();
      }

    inline status_t read_status ()
      {
  	  command_read<cmd_read_status, 1 , serial_interface==spi ? 0:2 >();
  	  status_t status ;
  	  status.val = *((volatile uint8_t*)&qspi.data) ;
  	  qspi.wait_not_busy();
  	  qspi.transfer_complete_flag_clear();
  	  return status ;
      }

    inline void reset_quad_io()
      {
        command<cmd_reset_quad_io> () ;
  	qspi.wait_not_busy();
  	qspi.transfer_complete_flag_clear();
      }

    inline void read_memory_high_speed ( const uint32_t address, const size_t size , void* dest )
      {
         command_address_read<cmd_read_memory_high_speed>(address, size, serial_interface==spi ? 8:6);
         for ( size_t i = 0 ; i < size ; i++ )
              {
      	       ((uint32_t*)dest)[i] = qspi.data.byte ;
              }
  	  qspi.wait_not_busy();
  	  qspi.transfer_complete_flag_clear();
      }

    inline void read_memory_high_speed_word ( const uint32_t address, const size_t size , void* dest )
      {
         command_address_read<cmd_read_memory_high_speed>(address, size, serial_interface==spi ? 8:6);
         for ( size_t i = 0 ; i < size / 4 ; i++ )
              {
      	       ((uint32_t*)dest)[i] = qspi.data.word ;
              }
  	  qspi.wait_not_busy();
  	  qspi.transfer_complete_flag_clear();
      }

    inline void erase_4k_memry_array ( const uint32_t address )
      {
         write_enable();
         command_address<cmd_erase_4k_memry_array>(address);
         qspi.wait_not_busy();
         qspi.transfer_complete_flag_clear();
         wait_for_busy_write_operation();
      }

    inline void erase_full_array ()
      {
         write_enable();
         command<cmd_erase_full_array>();
         qspi.wait_not_busy();
         qspi.transfer_complete_flag_clear();
         wait_for_busy_write_operation();
      }

    inline void page_programm ( const uint32_t address, const size_t size , const void* src )
      {
         write_enable();
         command_address_write<cmd_page_programm>(address, size);
         for ( size_t i = 0 ; i < size ; i++ )
           {
      	   qspi.data.byte  =  ((uint32_t*)src)[i] ;
           }
         qspi.wait_not_busy();
         qspi.transfer_complete_flag_clear();
         wait_for_busy_write_operation();
      }

    inline void page_programm_word ( const uint32_t address, const size_t size , const void* src )
      {
         write_enable();
         command_address_write<cmd_page_programm>(address, size);
         for ( size_t i = 0 ; i < size/4 ; i++ )
           {
      	   qspi.data.word  =  ((uint32_t*)src)[i] ;
           }
         qspi.wait_not_busy();
         qspi.transfer_complete_flag_clear();
         wait_for_busy_write_operation();
      }

  protected:

    // spi template api
    template < const command_t cmd , const size_t size>
    inline void spi_command_read ()
      {
  	  qspi.data_size(size);
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
  			qspi_t::communication_config_t::address_mode_t::no,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::single_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_read,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
      }

    template < const command_t cmd , const size_t size>
    inline void spi_command_write ()
      {
  	  qspi.data_size(size);
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
  			qspi_t::communication_config_t::address_mode_t::no,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::single_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
      }

    template < const command_t cmd>
    inline void spi_command_address (const uint32_t address)
      {
  	  qspi.data_size(0);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
  			qspi_t::communication_config_t::address_mode_t::single_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::no,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }

    template < const command_t cmd>
    inline void spi_command_address_read (const uint32_t address, const uint32_t size, const uint32_t number_dummy_cycles = 0 )
      {
  	  qspi.data_size(size);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
  			qspi_t::communication_config_t::address_mode_t::single_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
  			qspi_t::communication_config_t::data_mode_t::single_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_read,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }

    template < const command_t cmd>
    inline void spi_command_address_write (const uint32_t address, const uint32_t size)
      {
  	  qspi.data_size(size);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::single_line,
  			qspi_t::communication_config_t::address_mode_t::single_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::single_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }

    // sqi template api
    /*
    template < command_t cmd >
    inline void sqi_command ()
      {
  	  qspi.data_size(0);
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::four_line,
  			qspi_t::communication_config_t::address_mode_t::no,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::no,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
      }

    template < const command_t cmd , const size_t size, const uint32_t number_dummy_cycles = 0>
    inline void sqi_command_read ()
      {
  	  qspi.data_size(size);
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::four_line,
  			qspi_t::communication_config_t::address_mode_t::no,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
  			qspi_t::communication_config_t::data_mode_t::four_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_read,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
      }

    template < const command_t cmd>
    inline void sqi_command_address (const uint32_t address)
      {
  	  qspi.data_size(0);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::four_line,
  			qspi_t::communication_config_t::address_mode_t::four_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
  			qspi_t::communication_config_t::data_mode_t::no,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }

    template < const command_t cmd>
    inline void sqi_command_address_read (const uint32_t address, const uint32_t size, const uint32_t number_dummy_cycles = 0 )
      {
  	  qspi.data_size(size);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::four_line,
  			qspi_t::communication_config_t::address_mode_t::four_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
  			qspi_t::communication_config_t::data_mode_t::four_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_read,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }

    template < const command_t cmd>
    inline void sqi_command_address_write (const uint32_t address, const uint32_t size, const uint32_t number_dummy_cycles = 0)
      {
  	  qspi.data_size(size);
  	  qspi.alternate_bytes = 0 ;
  	  qspi.communication_config.modify(
  			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
  			qspi_t::communication_config_t::instruction_mode_t::enum_t::four_line,
  			qspi_t::communication_config_t::address_mode_t::four_line,
  			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
  			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
  			qspi_t::communication_config_t::data_mode_t::four_line,
  			qspi_t::communication_config_t::functional_mode_t::indirect_write,
  			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
  			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
  			qspi_t::communication_config_t::ddr_t::disable
                                       );
  	  qspi.address = address ;
      }
      */

    // common template api
    template < command_t cmd >
      inline void command ()
        {
    	  qspi.data_size(0);
    	  qspi.communication_config.modify(
    			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
    			(qspi_t::communication_config_t::instruction_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::address_mode_t::no,
    			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
    			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
    			qspi_t::communication_config_t::data_mode_t::no,
    			qspi_t::communication_config_t::functional_mode_t::indirect_write,
    			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
    			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
    			qspi_t::communication_config_t::ddr_t::disable
                                         );
        }

      template < const command_t cmd , const size_t size, const uint32_t number_dummy_cycles = 0>
      inline void command_read ()
        {
    	  qspi.data_size(size);
    	  qspi.communication_config.modify(
    			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
    			(qspi_t::communication_config_t::instruction_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::address_mode_t::no,
    			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
    			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
    			qspi_t::communication_config_t::data_mode_t::four_line,
    			qspi_t::communication_config_t::functional_mode_t::indirect_read,
    			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
    			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
    			qspi_t::communication_config_t::ddr_t::disable
                                         );
        }

      template < const command_t cmd>
      inline void command_address (const uint32_t address)
        {
    	  qspi.data_size(0);
    	  qspi.alternate_bytes = 0 ;
    	  qspi.communication_config.modify(
    			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
    			(qspi_t::communication_config_t::instruction_mode_t::enum_t)serial_interface,
    			(qspi_t::communication_config_t::address_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
    			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)0,
    			qspi_t::communication_config_t::data_mode_t::no,
    			qspi_t::communication_config_t::functional_mode_t::indirect_write,
    			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
    			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
    			qspi_t::communication_config_t::ddr_t::disable
                                         );
    	  qspi.address = address ;
        }

      template < const command_t cmd>
      inline void command_address_read (const uint32_t address, const uint32_t size, const uint32_t number_dummy_cycles = 0 )
        {
    	  qspi.data_size(size);
    	  qspi.alternate_bytes = 0 ;
    	  qspi.communication_config.modify(
    			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
    			(qspi_t::communication_config_t::instruction_mode_t::enum_t)serial_interface,
    			(qspi_t::communication_config_t::address_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
    			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
    			(qspi_t::communication_config_t::data_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::functional_mode_t::indirect_read,
    			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
    			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
    			qspi_t::communication_config_t::ddr_t::disable
                                         );
    	  qspi.address = address ;
        }

      template < const command_t cmd>
      inline void command_address_write (const uint32_t address, const uint32_t size, const uint32_t number_dummy_cycles = 0)
        {
    	  qspi.data_size(size);
    	  qspi.alternate_bytes = 0 ;
    	  qspi.communication_config.modify(
    			(qspi_t::communication_config_t::instruction_t::enum_t)cmd,
    			(qspi_t::communication_config_t::instruction_mode_t::enum_t)serial_interface,
    			(qspi_t::communication_config_t::address_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::alternate_bytes_mode_t::no,
    			(qspi_t::communication_config_t::number_dummy_cycles_t::enum_t)number_dummy_cycles,
    			(qspi_t::communication_config_t::data_mode_t::enum_t)serial_interface,
    			qspi_t::communication_config_t::functional_mode_t::indirect_write,
    			qspi_t::communication_config_t::send_instruction_mode_t::every_transaction,
    			qspi_t::communication_config_t::ddr_hold_t::analog_delay,
    			qspi_t::communication_config_t::ddr_t::disable
                                         );
    	  qspi.address = address ;
        }
} ;

}

using namespace sst26 ;

#endif /* __SST26_H__ */





#if 0
#include "appdefs.h"

#include "flash/qspi/sst26.h"


template <const qspi_t::control_t::flash_memory_selection_t::enum_t chip, const uint8_t prescaler>
class storage_4k_sector_t : protected sst26_t<chip,prescaler>
{
   typedef sst26_t<chip,prescaler> intf ;

   public:
	  inline storage_4k_sector_t() {}
	  inline ~storage_4k_sector_t() {}
	  static constexpr uint32_t sector_size = 4096 ;
	  static constexpr uint32_t page_size = 256 ;
	  static constexpr uint32_t page_per_sector = sector_size / page_size ;

	  inline uint8_t status()
	  	{
	  		  return 0 ;
	  	}


	  inline uint32_t initilize()
	    {
	          intf::init();
		  return true ;
	    }

	  inline uint32_t read(uint8_t* buff, const uint32_t sector, const uint32_t count)
	    {
	         intf::read_memory_high_speed_word ( sector * sector_size , count  * sector_size, buff ) ;
                 return 0 ;
	    }

	  inline uint32_t write(const uint8_t* src, const uint32_t sector, const uint32_t count)
	    {
	        uint8_t*  buff = (uint8_t*)src ;
		uint32_t address = sector * sector_size ;
                for ( uint32_t sector_index = 0 ; sector_index < count ; sector_index++ )
                   {
        	     // очистка сектора 4k
                     intf::erase_4k_memry_array ( address ) ;
        	     for ( uint32_t i = 0 ;  i < page_per_sector ; i ++ )
        	       {
        		  intf::page_programm_word ( address + i*page_size , 256 , buff + i*page_size ) ;
        	       }

        	     buff += sector_size ;
        	     address += sector_size ;
                    }
                 return 0 ;
	    }

	  inline uint32_t erase(const uint32_t sector, const uint32_t count)
	    {
	         uint32_t address = sector * sector_size ;
	         for ( uint32_t sector_index = 0 ; sector_index < count ; sector_index++ )
	           {
	             // очистка сектора 4k
	             intf::erase_4k_memry_array ( address ) ;
	             address += sector_size ;
	           }
	         return 0;
	    }

	  inline uint32_t erase()
	    {
                intf::erase() ;
                return 0;
	    }

	  inline uint32_t ioctl ( const uint8_t cmd, void* buff )
	    {
		  return 0 ;
	    }

	  inline uint32_t fattime ()
	    {
		  return 0 ;
	    }

} ;


storage_4k_sector_t<
                     qspi_t::control_t::flash_memory_selection_t::enum_t::chip_1,
                     8
                   > storage_4k_sector ;

uint32_t out_buff[4*1024] ;
uint32_t  in_buff[4*1024] ;


void storage_test()
{
	for ( uint32_t i = 0 ; i < 4*1024 ; i++ )
		{ out_buff[i] = 3*i ; }

	storage_4k_sector.initilize() ;

	//storage_4k_sector.erase();

	storage_4k_sector.write( (uint8_t*)out_buff, 0, 4 );
	nop_rep(10);
	storage_4k_sector.read ( (uint8_t*)in_buff, 0, 4 );

}


#endif
