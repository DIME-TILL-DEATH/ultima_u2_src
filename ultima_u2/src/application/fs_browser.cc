/*
 * fs_browser.cc
 *
 *  Created on: 9 мар. 2019 г.
 *      Author: klen
 */

#include "fs_browser.h"
#include "display.h"
#include "controls.h"
#include "gui.h"

fs_browser_task_t* fs_browser_task ;

void fs_browser_task_t::code()
{

  start();

  while (1)
  {

      // ожидания уведомления о запросе данных
      query_notify_t qn ;
      notify_wait( 0, 0 , (uint32_t*)&qn, portMAX_DELAY) ;

      switch( qn.notify )
      {
         case qn_prev :
                        prev();
            	        break ;
         case qn_next :
            	        next();
            	        break ;
         case qn_action :
            	        action( qn.action_param , qn.play_index , qn.play_next);
            	        break ;
         default: {}
      }


	  scheduler_t::yeld();
  }
}


void fs_browser_task_t::start()
{
   fscheck();
}

void fs_browser_task_t::stop()
{
   f_close(&file0);
   f_close(&file1);
   f_mount(0, "", 0);
}

void fs_browser_task_t::fscheck()
{
  emb_string temp;
  controls.usb_vbus_irq_disable();

  if ((fres = f_mount(&fs, "", 1)) != FR_OK) /* Create FAT volume on the logical drive 0 */
  {
	  uint8_t* buf ;
	  if ( !(buf = new uint8_t[FF_MAX_SS]))          // Working buffer for f_fdisk function.
	  {
		  display_task->line_12x13(0 , 4 , "buffer allocated fail", 0) ;
		  std::__throw_memmgr_error("buffer allocated fail");
	  }

	  if ((fres = f_mkfs("", FM_ANY, 0, buf, FF_MAX_SS)) != FR_OK)
	  {
		  display_task->line_12x13(0 , 4 , "f_mkfs fail", 0) ;
		  display_task->line_12x13(0 , 6 , f_err2str(fres), 0) ;
		  std::__throw_memmgr_error("buffer allocated fail");
	  }

	  delete buf ;

	  if ((fres = f_mount(&fs, "", 1)) != FR_OK) /* Create FAT volume on the logical drive 0 */
	  {
		  display_task->line_12x13(0 , 4 , "f_mkfs fail after f_mkfs", 0) ;
		  display_task->line_12x13(0 , 6 , f_err2str(fres), 0) ;
		  std::__throw_memmgr_error("f_mkfs fail after f_mkfs");
	  }
  }

  if ((fres = f_open(&file0, "/system.ult", FA_OPEN_ALWAYS)) != FR_OK)
  {
	  display_task->line_12x13(0 , 4 , "f_open fail", 0) ;
	  display_task->line_12x13(0 , 6 , f_err2str(fres), 0) ;
	  std::__throw_memmgr_error("f_open fail");
  }

  f_close(&file0);

  display_task->clear();
  for (size_t i = 1 ; i <= FS_PRESETS_COUNT ; i++)
  {
	  emb_printf::sprintf( str, "/%2", i );
	  emb_printf::sprintf( temp, "/%2/preset_cab.ult", i );

	  fres = f_opendir(&dir, str.c_str());
	  switch (fres)
	  {
	  	  case FR_OK :
	  		  f_open(&file0,temp.c_str(),FA_OPEN_ALWAYS);
	  		  f_close(&file0);
	  		  f_closedir(&dir);
	  		  break;
          case FR_NO_PATH :
        	  display_task->line_12x13(0 , 0 , "Create presets",0) ;
        	  if ( (fres = f_mkdir(str.c_str())) != FR_OK)
              {
        		  display_task->line_12x13(0 , 2 , "f_mkdir", 0) ;
        		  display_task->line_12x13(0 , 4 , str.c_str(), 0) ;
        		  display_task->line_12x13(0 , 6 , f_err2str(fres), 0) ;
        		  std::__throw_runtime_error(f_err2str(fres));
              }
        	  display_task->line_12x13(0 , 6 , str.c_str(),1) ;
        	  display_task->line_12x13(0 , 6 , str.c_str(),0) ;
	  		  f_open(&file0,temp.c_str(),FA_OPEN_ALWAYS);
	  		  f_close(&file0);
        	  break;
          default:
          {
              display_task->line_12x13(0 , 2 , "f_opendir", 0) ;
              display_task->line_12x13(0 , 4 , str.c_str(), 0) ;
              display_task->line_12x13(0 , 6 , f_err2str(fres), 0) ;
              std::__throw_runtime_error(f_err2str(fres));
          }
	  }

  }

  fres = f_opendir(&dir,"/Impulses");
  if(fres == FR_NO_PATH)f_mkdir("/Impulses");
  fres = f_opendir(&dir,"/Impulses");
  f_closedir(&dir);

  browser.play_list_folder = emb_string("/Impulses");
  enter_dir( "/Impulses" , "", true) ;

  gui_task->resume();
  controls.usb_vbus_irq_enable();
}


size_t fs_browser_task_t::read( const char* path, const size_t offset, const size_t size , void* buf)
{
  if ((fres = f_open(&file0, path, FA_READ)) != FR_OK)
  {
 	return 0 ;
  }
  size_t bytes_readed ;
  if ((fres = f_lseek(&file0, offset)) != FR_OK)
          {
           f_close(&file0);
            return 0 ;
          }

  if ((fres = f_read(&file0, buf, size, &bytes_readed)) != FR_OK)
        {
           f_close(&file0);
   	   return 0 ;
        }

  f_close(&file0);
  return bytes_readed;

}

size_t fs_browser_task_t::write( const char* path, const size_t offset, const size_t size , const void* buf)
{
  if ((fres = f_open(&file0, path, FA_OPEN_ALWAYS | FA_WRITE)) != FR_OK)
      {
 	return 0 ;
      }
  size_t bytes_write ;
  if ((fres = f_lseek(&file0, offset)) != FR_OK)
          {
           f_close(&file0);
            return 0 ;
          }

  if ((fres = f_write(&file0, buf, size, &bytes_write)) != FR_OK)
        {
           f_close(&file0);
   	   return 0 ;
        }

   f_close(&file0);
   return bytes_write ;
}

void fs_browser_task_t::truncate_wave(const char* path, const size_t offset, const size_t len, char* buf)
{
	size_t bytes_readed ;
	if ((fres = f_open(&file0, path, FA_READ | FA_WRITE)) != FR_OK)
	    {
	      return ;
	    }
	if ((fres = f_lseek(&file0,offset)) != FR_OK)
	    {
	      return ;
	    }
	if ((fres = f_read(&file0, buf, len, &bytes_readed)) != FR_OK)
	    {
	      return ;
	    }

	if(bytes_readed < len)
	    memset ( buf+ bytes_readed , 0,  len-bytes_readed) ;

	if ((fres = f_truncate(&file0)) != FR_OK)
	    {
	      return ;
	    }

	f_close(&file0);
}
size_t fs_browser_task_t::wave_find(char* path)
{
    FILINFO fno;    /* File information */
    fres = f_findfirst(&dir, &fno, path, "*.wav");  /* Start to search for photo files */
    size_t wave_count = 0 ;
    if ( fres == FR_OK && fno.fname[0] )wave_count +=1;
    return wave_count ;
}
size_t fs_browser_task_t::check_wave(char* path0)
{
      FILINFO fno;    /* File information */
      fres = f_findfirst(&dir, &fno, path0, "*.wav");  /* Start to search for photo files */
      size_t wave_count = 0 ;
      if ( fres == FR_OK && fno.fname[0] )
      {
    	  wave_count+=1 ;
    	  strncat( path0, "/" , 127);
    	  strncat( path0, fno.fname , 127);

    	  f_closedir(&dir);
      }

      return wave_count ;
}
void fs_browser_task_t::check_preset(const size_t preset_count, char* data, const char* init, const char* name0, const char* name1)
{
  emb_string path ;
  for(uint8_t i = 1 ; i <= preset_count ; i++)
    {
  	  emb_printf::sprintf( path, "/%2/preset_cab.ult", i );
  	  if(! read(path.c_str(), 0, 256 , (char*)data))
  	  {
  		  for(uint8_t j = 0 ; j < 15 ; j++)
  		  {
  			  data[j] = name0[j];
  			  data[j + 15] = name1[j];
  		  }

  		  for(uint8_t j = 0 ; j < (256 - 30) ; j++) data[j + 30] = init[j];

  		  fs_browser_task->write(path.c_str(), 0 , 256 , (char*)data);

  		  path.resize(2);

  		  display_task->line_12x13(0 , 6 , path.c_str() , 0) ;
  	  }
    }
}

void fs_browser_task_t::action( action_param_t val , uint8_t play_index , uint8_t play_next)
   {
         if ( browser.fno.fattrib & AM_DIR )
       	 {
       		 // entry to dir
       		  browser.tmp = emb_string(browser.fno.fname) ;
    		  if ( browser.tmp == ".." )
       		    {
       		       fr = f_getcwd( browser.buf , FF_MAX_LFN);
       		       browser.tmp = browser.buf ;
       		       size_t slash_pos = browser.tmp.find_last_of('/') ;
       		       browser.tmp = browser.tmp.substr( slash_pos + 1, browser.tmp.length());
       		    }
       		             // entry to dir
       		 enter_dir( (const char*)browser.fno.fname, browser.tmp.c_str(), false ) ;
       	 }
       	 else
       	 {

       	 }
}

void fs_browser_task_t::next()
        {
           DIR dir = browser.dir ;
           FILINFO fno = browser.fno ;
           if ( (fr = f_readdir(&browser.dir, &browser.fno)) == FR_OK )
             {
               if ( !browser.fno.fname[0] )
               {
                  browser.dir = dir ;
                  browser.fno = fno ;
               }
             }
          }

void fs_browser_task_t::prev()
        {

	       browser.tmp = browser.fno.fname ;
           size_t index = 0 ;
           // проход c вычисленем индекса текущего файла
           f_readdir(&browser.dir, NULL);

           while ((fr = f_readdir(&browser.dir, &browser.fno)) == FR_OK  && browser.fno.fname[0] )
           {
               index++ ;
               if ( browser.tmp == browser.fno.fname )
               {
                  index-- ;
                  if ( index )
                    {
                      // второй проход по индексу -1 с получением имени передидущего файла
                      f_readdir(&browser.dir, NULL);
                      for ( size_t i = 0 ; i < index; i++ )
                         f_readdir(&browser.dir, &browser.fno) ;
                    }
                   return ;
               }
           }
        }

void fs_browser_task_t::enter_dir( const char* name, const char* high_level_node, bool begin = false )
        {
       	 if ( !begin )
       	    if ((fr = f_closedir( &browser.dir ))!=FR_OK)
       	       {
        	         ////rmsg( ConsoleTask->ReadLine(),"error :%s\n" , f_err2str(fr));
            	         enter_dir("/" , "", true);
       	       }
       	 if ((fr = f_opendir ( &browser.dir, name ))!=FR_OK)
   	      {
             	  //rmsg( ConsoleTask->ReadLine(),"error :%s\ngo to IMPULSE" , f_err2str(fr));
             	  enter_dir("/", "", true);
             	  return ;
   	       }
       	 if ((fr = f_chdir( name ))!=FR_OK)
   	       {
           	  //rmsg( ConsoleTask->ReadLine(),"error :%s\n" , f_err2str(fr));
             	  enter_dir("/","", true);
             	  return ;
   	       }
       	fr =f_getcwd( browser.buf,FF_MAX_LFN);
         if ( name[0]=='.' && name[1]=='.' && name[2]==0 )
       	     {
       	       browser.tmp = high_level_node ;
       	       while(  ((fr = f_readdir ( &browser.dir, &browser.fno))==FR_OK) && (browser.tmp != browser.fno.fname) && (browser.fno.fname[0]) )
       	          {}
       	       if ( fr != FR_OK )
       	       {
       	         //rmsg( ConsoleTask->ReadLine(),"error :%s\n" , f_err2str(fr));
       	         enter_dir("/", "", true);
       	       }
       	     }
       	  else
       	    {
       	      if ((fr = f_readdir ( &browser.dir, &browser.fno))!=FR_OK)
       	        {
       	          //rmsg( ConsoleTask->ReadLine(),"error :%s\n" , f_err2str(fr));
       	          enter_dir("/", "", true);
       	        }
       	    }
        }
