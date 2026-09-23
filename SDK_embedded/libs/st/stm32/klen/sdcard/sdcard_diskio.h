#ifndef __SDCARD_DISKIO_H__
#define __SDCARD_DISKIO_H__

#ifdef __cplusplus
	extern "C" {
#endif


#include <stdint.h>

/*
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void);
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize);
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize);
*/

//-------------------------------------------------------------------

DSTATUS sdcard_disk_initialize ();
DSTATUS sdcard_disk_status ();
DRESULT sdcard_disk_read (uint8_t lun, BYTE* buffer , DWORD sector_number, uint16_t sector_count);
DRESULT sdcard_disk_write (uint8_t lun, const BYTE* buffer, DWORD sector_number, uint16_t sector_count );
DRESULT sdcard_disk_ioctl (uint8_t lun, BYTE command , void* params);

#ifdef __cplusplus
	}
#endif

#endif  /*__SDCARD_DISKIO_H__*/
