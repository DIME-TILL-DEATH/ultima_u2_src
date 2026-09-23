/*
 * fs_browser.h
 *
 *  Created on: 9 мар. 2019 г.
 *      Author: klen
 */

#ifndef __FS_BROWSER_H__
#define __FS_BROWSER_H__

#include "sdk.h"
#include "ff.h"
#include <vector>

class fs_browser_task_t : public task_t
{
   public:

	  struct browser_t
	  {
	    size_t curr_dir_child_index  ;  // порядковый номер объекта текущей директории в списке объектов родительской директори
	    size_t object_index ;  // порядковый номер объекта файла в списке текущей директории

	    DIR dir;
	    FILINFO fno;
	    char buf[FF_MAX_LFN+4] ;
	    emb_string tmp ;
	    emb_string play_list_folder ;

	  } ;

	  enum action_param_t { ap_1_wav, ap_2_wav } ;
	  enum notify_t { qn_next=0, qn_prev,qn_action } ;
      struct query_notify_t
      {
	    notify_t notify : 8 ;
	    union
	    {
	      struct
	      {
	       action_param_t action_param : 16 ;
	       uint32_t play_index : 8 ;
	       uint32_t play_next : 8 ;
	      } __attribute__((packed));
	     }__attribute__((packed));
       } __attribute__((packed));


    inline void next_notify()
        {
          query_notify_t qn = { .notify=qn_next };
          notify_for(qn) ;
        }
    inline void prev_notify()
        {
          query_notify_t qn = { .notify=qn_prev };
          notify_for(qn) ;
        }
    inline void action_notify()
        {
          query_notify_t qn ;
          qn.notify=qn_action;
          qn.action_param = ap_1_wav;
          qn.play_index = 0 ;
          qn.play_next = 0 ;
          notify_for(qn) ;
        }
    inline void curr_path(emb_string& dst)
       {
          f_getcwd( browser.buf , FF_MAX_LFN);
          dst = emb_string(browser.buf);
       }
    inline uint8_t status_path(void)
       {
    	  return (browser.fno.fattrib & AM_DIR);
       }
    inline void erase_cur_preset(char* path_source , char* data, const char* init, const char* name0, const char* name1)
    	{
    		FILINFO fno;
    		fres = f_findfirst(&dir, &fno, path_source, "*.wav");
    		if( fres == FR_OK && fno.fname[0] )
    		{
    			str = (char*)path_source;
        		str.append("/");
        		str.append(fno.fname);
        		f_unlink(str.c_str());
    		}
			str = (char*)path_source;
    		str.append("/");
    		str.append("preset_cab.ult");
    		for(uint8_t j = 0 ; j < 15 ; j++)
    		{
    			data[j] = name0[j];
    			data[j + 15] = name1[j];
    		}
    		for(uint8_t j = 0 ; j < (256 - 30) ; j++) data[j + 30] = init[j];
    		write(str.c_str(), 0 , 256 , (char*)data);
    	}
    inline void write_impulse(char* path_source,char* path_dest,uint8_t* buf,uint8_t fl)
       {
    	  FILINFO fno;
    	  FILINFO fno1;
    	  size_t bytes_readed;
    	  size_t bytes_write;
    	  FSIZE_t file_size;
    	  if(!fl)
    	  {
    		  fres = f_findfirst(&dir, &fno, path_source, "*.wav");
    		  if ( fres == FR_OK && fno.fname[0] )
    		  {
        		  str = (char*)path_source;
        		  str.append("/");
        		  str.append(fno.fname);
        		  fres = f_open(&file0,str.c_str(),FA_READ);
        		  file_size = f_size(&file0);
        		  fres = f_read(&file0,buf,file_size,&bytes_readed);
        		  f_close(&file0);
            	  fres = f_findfirst(&dir, &fno1, path_dest, "*.wav");
            	  if ( fres == FR_OK && fno1.fname[0] )
            	  {
            		  str1 = (char*)path_dest;
            		  str1.append("/");
            		  str1.append(fno1.fname);
            		  f_unlink(str1.c_str());
            	  }
        		  str = (char*)path_dest;
        		  str.append("/");
        		  str.append(fno.fname);
        		  fres = f_open(&file0,str.c_str(),FA_CREATE_ALWAYS | FA_WRITE);
            	  f_write(&file0,buf,bytes_readed,&bytes_write);
            	  f_close(&file0);
    		  }
    	  }
    	  else {
        	  fres = f_findfirst(&dir, &fno1, path_dest, "*.wav");
        	  if ( fres == FR_OK && fno1.fname[0] )
        	  {
        		  str1 = (char*)path_dest;
        		  str1.append("/");
        		  str1.append(fno1.fname);
        		  f_unlink(str1.c_str());
        	  }
        	  str = (char*)browser.buf;
        	  str.append("/");
        	  str.append(browser.fno.fname);
    		  fres = f_open(&file0,str.c_str(),FA_READ);
        	  file_size = f_size(&file0);
        	  fres = f_read(&file0,buf,file_size,&bytes_readed);
        	  f_close(&file0);
        	  str = (char*)path_dest;
        	  str.append("/");
        	  str.append(browser.fno.fname);
        	  fres = f_open(&file0,str.c_str(),FA_CREATE_ALWAYS | FA_WRITE);
        	  f_write(&file0,buf,bytes_readed,&bytes_write);
        	  f_close(&file0);
    	  }
       }

      inline fs_browser_task_t (const char* name , const int stack_size , const int priority, bool suspend) : task_t(name , stack_size , priority , suspend) {} ;
      inline virtual ~fs_browser_task_t() {} ;

      void start();
      void stop();

      size_t read( const char* path, const size_t offset, const size_t size ,  void* buf) ;
      size_t write( const char* path, const size_t offset, const size_t size , const void* buf);

      // провека на наличие wave файла и
      size_t wave_find(char* path);
      size_t check_wave(char* path0) ;
      void truncate_wave(const char* path, const size_t offset , const size_t len, char* buf);

      void check_preset( const size_t preset_count, char* data, const char* init, const char* name0, const char* name1);

      //-------------------------------------------------------------------
      void action(action_param_t val , uint8_t play_index , uint8_t play_next);
      void curr();
      void next();
      void prev();

      void enter_dir( const char* name, const char* high_level_node, bool begin );
     //------------------------------------------------------------------------
      inline void notify_for(const query_notify_t& val)
        {
    	  if ( cpu_exception_num())
     	   {
     	       // send comand from ISR
     	       BaseType_t xHigherPriorityTaskWoken ;
              notify_from_isr( *((uint32_t*)&val), eSetValueWithOverwrite,&xHigherPriorityTaskWoken);
               portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
     	   }
          else
     	   {
     	   // thread mode
              notify(*((uint32_t*)&val), eSetValueWithOverwrite);
     	   }

        }

      inline void browser_name(emb_string& dst)
         {
           dst = browser.fno.fname ;
         }

   protected:
      void code() ;
      void fscheck();

   private:
      FATFS fs ;
      FRESULT fres ;

      FIL file0 ;
      FIL file1 ;
      DIR dir ;

      emb_string str;
      emb_string str1 ;


      browser_t browser ;
      FRESULT  fr         ; // результат файловой операции


};

extern fs_browser_task_t* fs_browser_task ;

#endif /* __FS_BROWSER_H__ */
