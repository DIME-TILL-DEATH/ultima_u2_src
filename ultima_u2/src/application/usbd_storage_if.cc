
#include "appdefs.h"

#include "usbd_storage_if.h"
#include "qspi_flash.h"


#define STORAGE_LUN_COUNT                    1
#define STORAGE_SST26                        0

const uint8_t  STORAGE_Inquirydata_FS[] = {/* 36 */

  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,
  0x00,
  'A', 'M', 'T', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'S', 'S', 'T', '2', '6', ' ', ' ', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
};

extern usbd_t hUsbDeviceFS;

typedef storage_4k_sector_t<
                             sqi,
                             QSPI_CHIP,
                             QSPI_PRESCALER
                           > storage_t ;

static storage_t storage ;

int8_t storage_init (uint8_t lun)
{
  storage.initialize();
  return USBD_OK;
}


int8_t storage_capacity (uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  *block_num  = storage.sector_count ;
  *block_size = storage.sector_size ;
  return USBD_OK;
}

int8_t  storage_ready (uint8_t lun)
{
  if ( !storage.status() )
      	 return USBD_BUSY ;
  return USBD_OK;
}

int8_t  storage_write_protected (uint8_t lun)
{
  return 0 ;
}


int8_t storage_read (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  storage.read ( buf, blk_addr, blk_len);
  return USBD_OK;
}

int8_t storage_write (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  storage.write ( buf, blk_addr, blk_len);
  return USBD_OK;
}

int8_t storage_lun_count (void)
{
  return (STORAGE_LUN_COUNT - 1);
}

usbd_msc_io_t usbd_msc_io =
{
  storage_init,
  storage_capacity,
  storage_ready,
  storage_write_protected,
  storage_read,
  storage_write,
  storage_lun_count,
  (int8_t *)STORAGE_Inquirydata_FS,
};
