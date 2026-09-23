#include "diskio.h"
#include "sdio_sd.h"

//---------------------------------------------------------
DSTATUS sdcard_disk_initialize ()
{
            SD_LowLevel_DetectInit();
            if ( SD_LowLevel_Detect() == SD_NOT_PRESENT )
              {
                 //rmsg( "sd card not present\n") ;
                 while(1);
              }

            //rmsg( "SD card in socket\n") ;
            SD_LowLevel_SocketPowerInit();
            SD_LowLevel_SocketPower(1);
            //rmsg( "SD power is on\n") ;


            while(SD_Init() != SD_OK)
              {
                 SD_DeInit();
              }


            SD_Error Status = SD_OK;//SD_Init();
            //rmsg( "SD_Init: %s\n" , SD_Error2Msg(Status)) ;

            if ( Status != SD_OK )
                  while(1);


  return 0 /*STA_NOINIT	STA_NODISK	 STA_PROTECT*/	;
}
//---------------------------------------------------------
DSTATUS sdcard_disk_status ()
{
	return 0 /*STA_NOINIT	STA_NODISK	 STA_PROTECT*/	;
}
//---------------------------------------------------------
DRESULT sdcard_disk_read (uint8_t lun,BYTE* buffer , DWORD sector_number, uint16_t sector_count)
{
	SD_Error Status = SD_ReadMultiBlocks( buffer , sector_number , 0, sector_count) ;
    Status = SD_WaitReadOperation();
    (void)Status ;
    while(SD_GetStatus() != SD_TRANSFER_OK);
	return RES_OK ;
}
//---------------------------------------------------------
DRESULT sdcard_disk_write (uint8_t lun,const BYTE* buffer, DWORD sector_number, uint16_t sector_count )
{
	SD_Error Status = SD_WriteMultiBlocks( buffer , sector_number , 0, sector_count) ;
    Status = SD_WaitWriteOperation();
    (void)Status ;
    while(SD_GetStatus() != SD_TRANSFER_OK);
	return RES_OK ;
}
//---------------------------------------------------------
DRESULT sdcard_disk_ioctl (uint8_t lun,BYTE command , void* params)
{
	switch (command)
	{
		case CTRL_SYNC:
			return RES_OK ;
			break ;
		case GET_SECTOR_SIZE:
			*((unsigned int*)params) = 0 ;
			return RES_PARERR ;
			break ;
		case GET_SECTOR_COUNT:
			*((DWORD*)params) =  10000 ;
			break ;
		case GET_BLOCK_SIZE:
			*((DWORD*)params) =  1 ;
			break ;
		case CTRL_ERASE_SECTOR:
			return RES_ERROR ;
		default :
			return RES_PARERR ;
	}
	return RES_OK ;
}
//---------------------------------------------------------
