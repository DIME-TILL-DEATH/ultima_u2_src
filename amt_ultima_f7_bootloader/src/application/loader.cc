#include "appdefs.h"
#include "crc32.h"
#include "loader.h"
#include "display.h"
#include "aes.h"
#include "msc.h"

loader_task_t* loader_task ;


//-------------------------------------------
static void reset_perepherial()
{
	  // сброс использованной переферии
	  qspi.clock_enable();
	  qspi.reset();
}


static void jump_to_application( const uint32_t* vectors )
{
  reset_perepherial();

  scheduler_t::suspend_all();
  scheduler_t::enter_critical();

  sys_tick.tick_int_request_disable();
  sys_tick.disable();
  sys_tick.clock_source_external_clk();
  sys_tick.reload=0x0 ;
  sys_tick.current = 0 ;

  scb.sys_tick_exception_pending_clear();

  control(0);
  primask(0);
  basepri(0);

  asm volatile
  (
     "dsb                     \n"
     "msr msp, %[msp_init_val]\n" // store App stack init value to MSP
     :
     : [msp_init_val] "r" (vectors[0])
  );

  typedef void( *handler )( void );
  ((handler)vectors[1])();
}

void loader_task_t::check_read_protect()
{
  if ( flash.read_protect() == flash_t::option_control_t::read_protect_t::level_0 )
     if ( ! flash.programm_read_protect( flash_t::option_control_t::read_protect_t::level_1 ) )
         __throw_internal_error("flash set read protect failed",0);
}


void loader_task_t::firmware_update()
{
    UINT br ;
    size_t fw_size = f_size(&fw);
    size_t image_size = fw_size - sizeof(firmware_header_t) ;

    uint8_t in[16] ;
    uint8_t wout[16] ;
    uint8_t iv [16] ;

    uint8_t curr_msg_pos_col = 0 ;

    display_task->string( curr_msg_pos_col, 0, " check firmware");
    delay(20);

    firmware_header_t firmware_header ;
    // read header data
    f_read(&fw, &firmware_header, sizeof(firmware_header_t), &br) ;

    if ( firmware_header.header_data.size != image_size )
      {
        // файл не является прошивкой
    	f_close(&fw) ;
        f_unlink(fw_name) ;
    	return ;
      }

    size_t image_offset = f_tell(&fw) ;
    uint_least32_t crc ;
    crc32_init( &crc) ;
    memcpy ( iv , SD_MULTIPLAYER_AES128_CRYPT_IV, 16)  ;
    for (uint32_t ch = 0 ; ch < image_size / 16 ; ch++  )
       {
          f_read(&fw ,in ,16, &br) ;
          AES128_CBC_decrypt_buffer(wout, in, 16 , (const uint8_t*)SD_MULTIPLAYER_AES128_CRYPT_KEY , iv);
          memcpy (iv , in , 16 ) ;
          for (size_t wb = 0 ; wb < 16 ; wb++)
             {
               crc32_update( &crc, wout[wb]) ;
             }
          display_task->progress( ch*16 / (fw_size/16) );
        }
    crc = crc32_result(&crc) ;

    if ( (firmware_header.header_data.crc == crc) && (firmware_header.header_data.magic == FW_HEADER_DATA_MAGIC) )
      {
	    display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");
        delay(20);

        // стирание сектора по адресу заголовка 0x08040000 (сектор #5 256k )
        display_task->string( curr_msg_pos_col++, 0, "Erase FW header sector");
        delay(20);
        if (!flash.sector_erase( header_flash_sector ))
           {
        	  display_task->string( curr_msg_pos_col++, 0, "flash sector erase failed");
        	__throw_internal_error("flash sector erase failed",0);
           }
        display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");

        // вычисление числа стираймых секторов для приложения с адреса 0x08080000 (сектор #6 256k )
        size_t cse = image_size / (256*1024) + 1 ;
        display_task->string( curr_msg_pos_col++, 0, "Erase FW app sector");
        delay(20);
        for ( size_t sector = 0 ; sector < cse ;  sector++ )
                   {
          	         if (!flash.sector_erase( app_flash_sector + sector ))
          	            {
          	        	   display_task->string( curr_msg_pos_col++ , 0, "flash sector erase failed");
          	               __throw_internal_error("flash sector erase failed",0);
          	            }
          	         display_task->progress(sector);
          	       }
        display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");
        delay(20);


        // write header
        display_task->string( curr_msg_pos_col++ , 0 , " Write header");
        delay(20);
        if ( !flash.program_x8(header, &firmware_header, sizeof(firmware_header_t)))
           {
        	  display_task->string( curr_msg_pos_col++ , 0, "flash header write failed");
              __throw_internal_error("flash header write failed",0);
           }
        display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");
        delay(20);



        // write firmware
        display_task->string( curr_msg_pos_col++ , 0 , " Write app");
        delay(20);
        f_lseek (&fw, image_offset);
        memcpy ( iv , SD_MULTIPLAYER_AES128_CRYPT_IV, 16)  ;
        size_t wrp = app ;
        for (uint32_t ch = 0 ; ch < image_size / 16 ; ch++  )
            {
        	      f_read(&fw, in, 16, &br) ;
        	      AES128_CBC_decrypt_buffer(wout, in, 16 , (const uint8_t*)SD_MULTIPLAYER_AES128_CRYPT_KEY , iv);
        	      memcpy (iv , in , 16 ) ;

        	      if ( !flash.program_x8(wrp, wout, 16))
        	         {
        	    	    display_task->string( curr_msg_pos_col++ , 0, "flash app stream write failed");
        	    	    __throw_internal_error("flash app stream write failed",0);
        	         }
        	      wrp+=16 ;
        	      display_task->progress(ch * 16 / ( fw_size / 16) );
            }

        display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");
        delay(20);

        display_task->string( curr_msg_pos_col++, 0, "remove firmware file");
        delay(20);
        f_close(&fw) ;
        f_unlink(fw_name) ;
        display_task->string( curr_msg_pos_col, ok_msg_pos_row, "ok");
        delay(20);

        jump_to_application((uint32_t*)app);
      }

}


void loader_task_t::recovery()
{
   f_mount(0, "", 0) ;

   reset_perepherial();

   usb_task = new usb_task_t("MSC" , 20*configMINIMAL_STACK_SIZE, 0) ;

   display_task->clear();
   display_task->string(5 , 30, "recovery mode") ;

   // удаление loader_task
   remove();
 }


void loader_task_t::check_app()
{
  // проверка заголовка и контрольной суммы приложения
  firmware_header_t& firmware_header = *(firmware_header_t*)header ;

  if ( firmware_header.header_data.size + 0x40000 > devsign.flash_size*1024 )
	  return ;

  uint_least32_t crc ;
  crc32_init( &crc) ;
  for ( size_t i = 0 ; i < firmware_header.header_data.size ; i++ )
         crc32_update( &crc, ((uint8_t*)app)[i] ) ;

  crc = crc32_result(&crc) ;

  if ((firmware_header.header_data.crc == crc) && (firmware_header.header_data.magic == FW_HEADER_DATA_MAGIC))
	  jump_to_application((uint32_t*)app);
  else
  {

  }
}

void loader_task_t::check_fs()
{

	   if ((fres = f_mount(&fs, "", 1)) != FR_OK) /* Create FAT volume on the logical drive 0 */
		  {
			  uint8_t* buf ;
			  if ( !(buf = new uint8_t[FF_MAX_SS]))          // Working buffer for f_fdisk function.
			  {
				  display_task->string(0 , 0, "buffer allocated fail") ;
				  std::__throw_memmgr_error("buffer allocated fail");
			  }

			  if ((fres = f_mkfs("", FM_ANY, 0, buf, FF_MAX_SS)) != FR_OK)
			  {
				  display_task->string(0 , 0, "f_mkfs fail") ;
				  display_task->string(4 , 0, f_err2str(fres)) ;
				  std::__throw_memmgr_error("f_mkfs fail");
			  }

			  delete buf ;

			  if ((fres = f_setlabel("AMT")) != FR_OK)
			  {
				  display_task->string(0 , 0, "f_setlabel fail") ;
				  display_task->string(0 , 0, f_err2str(fres)) ;
				  std::__throw_memmgr_error("f_setlabel fail") ;
			  }

			  if ((fres = f_mount(&fs, "", 1)) != FR_OK) /* Create FAT volume on the logical drive 0 */
			  {
				  display_task->string(0 , 0, "f_mkfs fail after f_mkfs") ;
				  display_task->string(0 , 4, f_err2str(fres)) ;
				  std::__throw_memmgr_error("f_mount fail after f_mkfs");
			  }
		  }
}

void loader_task_t::check_firmware()
{
   fres = f_open( &fw , fw_name , FA_READ);
   if (( fres == FR_OK))
	   // обновление образа приложения
	   firmware_update() ;
}

void loader_task_t::code()
{
	// Read-out protection. Disabled for debug
//   check_read_protect();

   // проверка наличия файловой системы и ее востановление если необходимо
   check_fs();

   gpio_t::pin_config_t enc = ENCODER_BUTTON ;
   gpio_t::pin_configure(enc);

   delay(1000); // задержка секунда

   if ( enc.port.pin(enc.pin) == gpio_t::input_t::set)
   {
      // проверка наличия в корне fatfs файла firmware и обновление при наличии
      check_firmware();

      // проверка образа приложения и его старт
      check_app();
   }

   recovery() ;
}
