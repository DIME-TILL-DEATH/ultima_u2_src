#ifndef __USBD_MSC_H
#define __USBD_MSC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_msc_bot.h"
#include  "usbd_msc_scsi.h"
#include  "usbd_ioreq.h"

#define MSC_MAX_FS_PACKET            0x40
#define MSC_MAX_HS_PACKET            0x200

#define BOT_GET_MAX_LUN              0xFE
#define BOT_RESET                    0xFF
#define USB_MSC_CONFIG_DESC_SIZ      32
 

#define MSC_EPIN_ADDR                0x81 
#define MSC_EPOUT_ADDR               0x01 

typedef struct
{
  int8_t (* init) (uint8_t lun);
  int8_t (* capacity) (uint8_t lun, uint32_t *block_num, uint16_t *block_size);
  int8_t (* ready) (uint8_t lun);
  int8_t (* write_protected) (uint8_t lun);
  int8_t (* read) (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
  int8_t (* lun_count)(void);
  int8_t *inquiry;
  
} usbd_msc_io_t ;


typedef struct
{
  uint32_t            max_lun;
  uint32_t            interface;
  uint8_t             bot_state;
  uint8_t             bot_status;
  uint16_t            bot_data_length;
  uint8_t             bot_data[MSC_MEDIA_PACKET];
  usbd_msc_bot_cbw_t  cbw;
  usbd_msc_bot_csw_t  csw;
  
  usbd_scsi_sense_t   scsi_sense [SENSE_LIST_DEEPTH];
  uint8_t             scsi_sense_head;
  uint8_t             scsi_sense_tail;
  
  uint16_t            scsi_blk_size;
  uint32_t            scsi_blk_nbr;
  
  uint32_t            scsi_blk_addr;
  uint32_t            scsi_blk_len;
}
usbd_msc_bot_t;

/* Structure for MSC process */
extern usbd_class_t  msc_usbd_class;
#define USBD_MSC_CLASS    &USBD_MSC

uint8_t  usbd_msc_register_storage  (usbd_t   *pdev,
				     usbd_msc_io_t *fops);


#ifdef __cplusplus
}
#endif

#endif  /* __USBD_MSC_H */

