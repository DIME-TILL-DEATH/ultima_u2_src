/*
 * storage_qspi.cc
 *
 *  Created on: Feb 3, 2019
 *      Author: klen
 */


#include "appdefs.h"

#include "flash/qspi/sst26.h"
#include "ff.h"
#include "diskio.h"

template <const serial_interface_t serial_interface, const qspi_t::control_t::flash_memory_selection_t::enum_t chip, const uint8_t prescaler>
class storage_4k_sector_t : protected sst26_t<serial_interface,chip,prescaler>
{
   typedef sst26_t<serial_interface,chip,prescaler> intf ;



   public:

      DSTATUS stat = STA_NOINIT ;


	  inline storage_4k_sector_t() {}
	  inline ~storage_4k_sector_t() {}
	  static constexpr uint32_t sector_size = 4096 ;
	  static constexpr uint32_t page_size = 256 ;
	  static constexpr uint32_t page_per_sector = sector_size / page_size ;

	  size_t sector_count ;

	  inline DSTATUS status()
	     {
	         return stat ;
	     }

	  inline DSTATUS initialize()
	     {
	         if ( stat & STA_NOINIT )
	           {
	             intf::init( sector_count );
	             stat &= ~STA_NOINIT ;
	           }
		 return stat ;
	     }

	  inline DRESULT read(uint8_t* buff, const uint32_t sector, const uint32_t count)
	    {
	         intf::read_memory_high_speed_word ( sector * sector_size , count  * sector_size, buff ) ;
                 return RES_OK ;
	    }

	  inline DRESULT write(const uint8_t* src, const uint32_t sector, const uint32_t count)
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
                 return RES_OK ;
	    }

	  inline DRESULT ioctl ( const uint8_t cmd, void* buff )
	    {
		return RES_OK ;
	    }

	  inline DWORD fattime ()
	    {
		return RES_OK ;
	    }

/*
	  inline DRESULT erase(const uint32_t sector, const uint32_t count = 1)
	    {
	         uint32_t address = sector * sector_size ;
	         for ( uint32_t sector_index = 0 ; sector_index < count ; sector_index++ )
	           {
	             // очистка сектора 4k
	             intf::erase_4k_memry_array ( address ) ;
	             address += sector_size ;
	           }
	        return RES_OK;
	    }

	  inline void erase()
	    {
                intf::erase() ;
	    }
*/
};

typedef storage_4k_sector_t< sqi,
                             QSPI_CHIP,
                             QSPI_PRESCALER
                           > storage_t ;

static storage_t storage ;


//------- обертки -------------------------------------


DSTATUS storage_get_status()
{
  return storage.status() ;
}
DSTATUS storage_initialize()
{
  return storage.initialize() ;
}

DSTATUS storage_deinitialize()
{
  return STA_NOINIT ;
}

DRESULT storage_read(uint8_t *buf, const uint32_t block_index, const uint32_t block_count )
{
  return storage.read(buf,block_index,block_count);
}
DRESULT storage_write(const uint8_t *buf, const uint32_t block_index, const uint32_t block_count)
{
  return storage.write(buf,block_index,block_count);
}
DRESULT storage_ioctl(const uint8_t command , void* params)
{
  switch ( command )
  {
    case GET_SECTOR_COUNT:
      *((uint32_t*)params) = storage.sector_count ;
      break ;
    case GET_SECTOR_SIZE:
      *((uint32_t*)params) = storage.sector_size ;
      break ;
    case GET_BLOCK_SIZE:
      *((uint32_t*)params) = 1 ;
      break ;
    case CTRL_SYNC:
      break ;
    default:
    	*((unsigned int*)params) = 0 ;
      return RES_PARERR ;
  }
  return RES_OK ;
}


//-----------------------------------------------------
#if 0
PARTITION VolToPart[] = {
       {0, 1},    /* "0:" ==> Physical drive 0, 1st partition */
       {0, 2},    /* "1:" ==> Physical drive 0, 2nd partition */
       //{1, 0}     /* "2:" ==> Physical drive 1, auto detection */
   };
#endif

extern "C"  DSTATUS storage_init(BYTE drv , storage_fn_t* storage_fn)
{
  if ( storage.stat == STA_NOINIT )
  {
	storage_fn->storage_initialize   = storage_initialize ;
    storage_fn->storage_deinitialize = storage_deinitialize ;
    storage_fn->storage_get_status   = storage_get_status ;
    storage_fn->storage_read         = storage_read;
    storage_fn->storage_write        = storage_write;
    storage_fn->storage_ioctl        = storage_ioctl;

    storage_initialize();
  }

  return storage.stat ;

}
#if 0
char ts[1024] ;
DWORD fre_sect, tot_sect;
float free_Mb, tot_Mb ;
void storage_mount()
{
    FATFS fs;           /* Filesystem object */
    FIL fil;            /* File object */
    FRESULT res;        /* API result code */
    UINT bw;            /* Bytes written */
    BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
    DWORD fre_clust, fre_sect, tot_sect;

#if 0
  DWORD plist[] = {50, 50, 0, 0};  /* Divide drive into two partitions */
  nop_rep(10);
  if ( (res = f_fdisk(0, plist, work)) != FR_OK)                    /* Divide physical drive 0 */
    {
      std::__throw_runtime_error(f_err2str(f_result));
    }
  nop_rep(10);

#endif

  //storage_initialize();
  //storage.read ( (uint8_t*)in_buff, 0, 4 );

  //storage.erase();

  nop_rep(10);
/*
  if ( (res = f_mkfs("", FM_FAT, 0, work, sizeof(work))) != FR_OK)
    {
      std::__throw_runtime_error(f_err2str(res));
    }
  nop_rep(10);
*/

  if ((res = f_mount(&fs, "", 0)) != FR_OK) /* Create FAT volume on the logical drive 0 */
    {
      std::__throw_runtime_error(f_err2str(res));
    }
  nop_rep(10);

  FATFS* pfs = &fs ;
  if ((res = f_getfree("0:", &fre_clust, &pfs)) != FR_OK)  std::__throw_runtime_error(f_err2str(res));

  tot_sect = (fs.n_fatent - 2) * fs.csize;
  fre_sect = fre_clust * fs.csize;

  tot_Mb = tot_sect * storage.sector_size / (1024.0f*1024.0f) ;
  free_Mb = fre_sect * storage.sector_size / (1024.0f*1024.0f) ;


  /* Create a file as new */

  if ((res = f_open(&fil, "a.txt", FA_READ/*FA_CREATE_NEW | FA_WRITE*/)) != FR_OK)
     {
       std::__throw_runtime_error(f_err2str(res));
     }

      /* Write a message */
//      f_write(&fil, "Hello, World!\r\n", 15, &bw);
   //   if (bw != 15) ...

  if ((res = f_read(&fil, ts , 15, &bw)) != FR_OK)
     {
       std::__throw_runtime_error(f_err2str(res));
     }

      /* Close the file */
      f_close(&fil);

  f_mount(0, "", 0);
}
#endif


//#if FF_USE_LFN == 3	/* Dynamic memory allocation */
//   extern "C" void* ff_memalloc (UINT msize){ return malloc(msize); }
//   extern "C" void  ff_memfree (void* mblock){	free(mblock);}
//#endif

#if FF_FS_REENTRANT
   extern "C" int  ff_cre_syncobj (BYTE vol,FF_SYNC_t* sobj) { *sobj = xSemaphoreCreateMutex(); return (int)(*sobj != NULL); }
   extern "C" int  ff_del_syncobj (FF_SYNC_t sobj)           { vSemaphoreDelete(sobj);  return 1; }
   extern "C" int  ff_req_grant   (FF_SYNC_t sobj)           { return (int)(xSemaphoreTake(sobj, FF_FS_TIMEOUT) == pdTRUE);}
   extern "C" void ff_rel_grant (FF_SYNC_t sobj)             { xSemaphoreGive(sobj);}
#endif

