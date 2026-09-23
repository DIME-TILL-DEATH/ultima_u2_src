#include "usbd_msc_bot.h"
#include "usbd_msc_scsi.h"
#include "usbd_msc.h"
#include "usbd_msc_data.h"

void scsi_sense_code(usbd_t  *pdev, uint8_t lun, uint8_t sKey, uint8_t ASC)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;

  hmsc->scsi_sense[hmsc->scsi_sense_tail].Skey  = sKey;
  hmsc->scsi_sense[hmsc->scsi_sense_tail].w.ASC = ASC << 8;
  hmsc->scsi_sense_tail++;
  if (hmsc->scsi_sense_tail == SENSE_LIST_DEEPTH)
  {
    hmsc->scsi_sense_tail = 0;
  }
}

static int8_t scsi_test_unit_ready(usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
    
  /* case 9 : Hi > D0 */
  if (hmsc->cbw.dDataLength != 0)
  {
    scsi_sense_code(pdev,
                   hmsc->cbw.bLUN, 
                   ILLEGAL_REQUEST, 
                   INVALID_CDB);
    return -1;
  }  
  
  if(((usbd_msc_io_t *)pdev->pUserData)->ready(lun) !=0 )
  {
    scsi_sense_code(pdev,
                   lun,
                   NOT_READY, 
                   MEDIUM_NOT_PRESENT);
    
    hmsc->bot_state = USBD_BOT_NO_DATA;
    return -1;
  } 
  hmsc->bot_data_length = 0;
  return 0;
}

static int8_t  scsi_inquiry(usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  uint8_t* pPage;
  uint16_t len;
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  
  if (params[1] & 0x01)/*Evpd is set*/
  {
    pPage = (uint8_t *)MSC_Page00_Inquiry_Data;
    len = LENGTH_INQUIRY_PAGE00;
  }
  else
  {
    
    pPage = (uint8_t *)&((usbd_msc_io_t *)pdev->pUserData)->inquiry[lun * STANDARD_INQUIRY_DATA_LEN];
    len = pPage[4] + 5;
    
    if (params[4] <= len)
    {
      len = params[4];
    }
  }
  hmsc->bot_data_length = len;
  
  while (len) 
  {
    len--;
    hmsc->bot_data[len] = pPage[len];
  }
  return 0;
}

static int8_t scsi_read_capacity_10(usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  
  if(((usbd_msc_io_t *)pdev->pUserData)->capacity(lun, &hmsc->scsi_blk_nbr, &hmsc->scsi_blk_size) != 0)
  {
    scsi_sense_code(pdev,
                   lun,
                   NOT_READY, 
                   MEDIUM_NOT_PRESENT);
    return -1;
  } 
  else
  {
    
    hmsc->bot_data[0] = (uint8_t)((hmsc->scsi_blk_nbr - 1) >> 24);
    hmsc->bot_data[1] = (uint8_t)((hmsc->scsi_blk_nbr - 1) >> 16);
    hmsc->bot_data[2] = (uint8_t)((hmsc->scsi_blk_nbr - 1) >>  8);
    hmsc->bot_data[3] = (uint8_t)(hmsc->scsi_blk_nbr - 1);
    
    hmsc->bot_data[4] = (uint8_t)(hmsc->scsi_blk_size >>  24);
    hmsc->bot_data[5] = (uint8_t)(hmsc->scsi_blk_size >>  16);
    hmsc->bot_data[6] = (uint8_t)(hmsc->scsi_blk_size >>  8);
    hmsc->bot_data[7] = (uint8_t)(hmsc->scsi_blk_size);
    
    hmsc->bot_data_length = 8;
    return 0;
  }
}

static int8_t scsi_read_format_capacity(usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  
  uint16_t blk_size;
  uint32_t blk_nbr;
  uint16_t i;
  
  for(i=0 ; i < 12 ; i++) 
  {
    hmsc->bot_data[i] = 0;
  }
  
  if(((usbd_msc_io_t *)pdev->pUserData)->capacity(lun, &blk_nbr, &blk_size) != 0)
  {
    scsi_sense_code(pdev,
                   lun,
                   NOT_READY, 
                   MEDIUM_NOT_PRESENT);
    return -1;
  } 
  else
  {
    hmsc->bot_data[3] = 0x08;
    hmsc->bot_data[4] = (uint8_t)((blk_nbr - 1) >> 24);
    hmsc->bot_data[5] = (uint8_t)((blk_nbr - 1) >> 16);
    hmsc->bot_data[6] = (uint8_t)((blk_nbr - 1) >>  8);
    hmsc->bot_data[7] = (uint8_t)(blk_nbr - 1);
    
    hmsc->bot_data[8] = 0x02;
    hmsc->bot_data[9] = (uint8_t)(blk_size >>  16);
    hmsc->bot_data[10] = (uint8_t)(blk_size >>  8);
    hmsc->bot_data[11] = (uint8_t)(blk_size);
    
    hmsc->bot_data_length = 12;
    return 0;
  }
}

static int8_t scsi_mode_sense_6 (usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  uint16_t len = 8 ;
  hmsc->bot_data_length = len;
  
  while (len) 
  {
    len--;
    hmsc->bot_data[len] = MSC_Mode_Sense6_data[len];
  }
  return 0;
}

static int8_t scsi_mode_sense_10 (usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  uint16_t len = 8;
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  
  hmsc->bot_data_length = len;

  while (len) 
  {
    len--;
    hmsc->bot_data[len] = MSC_Mode_Sense10_data[len];
  }
  return 0;
}

static int8_t scsi_request_sense (usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  uint8_t i;
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  
  for(i=0 ; i < REQUEST_SENSE_DATA_LEN ; i++) 
  {
    hmsc->bot_data[i] = 0;
  }
  
  hmsc->bot_data[0]	= 0x70;		
  hmsc->bot_data[7]	= REQUEST_SENSE_DATA_LEN - 6;	
  
  if((hmsc->scsi_sense_head != hmsc->scsi_sense_tail)) {
    
    hmsc->bot_data[2]     = hmsc->scsi_sense[hmsc->scsi_sense_head].Skey;		
    hmsc->bot_data[12]    = hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASCQ;	
    hmsc->bot_data[13]    = hmsc->scsi_sense[hmsc->scsi_sense_head].w.b.ASC;	
    hmsc->scsi_sense_head++;
    
    if (hmsc->scsi_sense_head == SENSE_LIST_DEEPTH)
    {
      hmsc->scsi_sense_head = 0;
    }
  }
  hmsc->bot_data_length = REQUEST_SENSE_DATA_LEN;  
  
  if (params[4] <= REQUEST_SENSE_DATA_LEN)
  {
    hmsc->bot_data_length = params[4];
  }
  return 0;
}



static int8_t scsi_start_stop_unit(usbd_t  *pdev, uint8_t lun, uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;
  hmsc->bot_data_length = 0;
  return 0;
}

static int8_t scsi_process_read (usbd_t  *pdev, uint8_t lun)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*)pdev->pClassData;
  uint32_t len;

  len = MIN(hmsc->scsi_blk_len , MSC_MEDIA_PACKET);

  if( ((usbd_msc_io_t *)pdev->pUserData)->read(lun ,
                              hmsc->bot_data,
                              hmsc->scsi_blk_addr / hmsc->scsi_blk_size,
                              len / hmsc->scsi_blk_size) < 0)
  {

    scsi_sense_code(pdev,
                   lun,
                   HARDWARE_ERROR,
                   UNRECOVERED_READ_ERROR);
    return -1;
  }


  usbd_ll_transmit (pdev,
             MSC_EPIN_ADDR,
             hmsc->bot_data,
             len);


  hmsc->scsi_blk_addr   += len;
  hmsc->scsi_blk_len    -= len;

  /* case 6 : Hi = Di */
  hmsc->csw.dDataResidue -= len;

  if (hmsc->scsi_blk_len == 0)
  {
    hmsc->bot_state = USBD_BOT_LAST_DATA_IN;
  }
  return 0;
}

static int8_t scsi_check_address_range (usbd_t  *pdev, uint8_t lun , uint32_t blk_offset , uint16_t blk_nbr)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;

  if ((blk_offset + blk_nbr) > hmsc->scsi_blk_nbr )
  {
    scsi_sense_code(pdev,
                   lun,
                   ILLEGAL_REQUEST,
                   ADDRESS_OUT_OF_RANGE);
    return -1;
  }
  return 0;
}

static int8_t scsi_read_10(usbd_t  *pdev, uint8_t lun , uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;
  
  if(hmsc->bot_state == USBD_BOT_IDLE)  /* Idle */
  {
    
    /* case 10 : Ho <> Di */
    
    if ((hmsc->cbw.bmFlags & 0x80) != 0x80)
    {
      scsi_sense_code(pdev,
                     hmsc->cbw.bLUN, 
                     ILLEGAL_REQUEST, 
                     INVALID_CDB);
      return -1;
    }    
    
    if(((usbd_msc_io_t *)pdev->pUserData)->ready(lun) !=0 )
    {
      scsi_sense_code(pdev,
                     lun,
                     NOT_READY, 
                     MEDIUM_NOT_PRESENT);
      return -1;
    } 
    
    hmsc->scsi_blk_addr = (params[2] << 24) | \
      (params[3] << 16) | \
        (params[4] <<  8) | \
          params[5];
    
    hmsc->scsi_blk_len =  (params[7] <<  8) | \
      params[8];  
    
    
    
    if( scsi_check_address_range(pdev, lun, hmsc->scsi_blk_addr, hmsc->scsi_blk_len) < 0)
    {
      return -1; /* error */
    }
    
    hmsc->bot_state = USBD_BOT_DATA_IN;
    hmsc->scsi_blk_addr *= hmsc->scsi_blk_size;
    hmsc->scsi_blk_len  *= hmsc->scsi_blk_size;
    
    /* cases 4,5 : Hi <> Dn */
    if (hmsc->cbw.dDataLength != hmsc->scsi_blk_len)
    {
      scsi_sense_code(pdev,
                     hmsc->cbw.bLUN, 
                     ILLEGAL_REQUEST, 
                     INVALID_CDB);
      return -1;
    }
  }
  hmsc->bot_data_length = MSC_MEDIA_PACKET;  
  
  return scsi_process_read(pdev, lun);
}

static int8_t scsi_process_write (usbd_t  *pdev, uint8_t lun)
{
  uint32_t len;
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;

  len = MIN(hmsc->scsi_blk_len , MSC_MEDIA_PACKET);

  if(((usbd_msc_io_t *)pdev->pUserData)->write(lun ,
                              hmsc->bot_data,
                              hmsc->scsi_blk_addr / hmsc->scsi_blk_size,
                              len / hmsc->scsi_blk_size) < 0)
  {
    scsi_sense_code(pdev,
                   lun,
                   HARDWARE_ERROR,
                   WRITE_FAULT);
    return -1;
  }


  hmsc->scsi_blk_addr  += len;
  hmsc->scsi_blk_len   -= len;

  /* case 12 : Ho = Do */
  hmsc->csw.dDataResidue -= len;

  if (hmsc->scsi_blk_len == 0)
  {
    MSC_BOT_SendCSW (pdev, USBD_CSW_CMD_PASSED);
  }
  else
  {
    /* Prepare EP to Receive next packet */
    usbd_ll_prepare_receive (pdev,
                            MSC_EPOUT_ADDR,
                            hmsc->bot_data,
                            MIN (hmsc->scsi_blk_len, MSC_MEDIA_PACKET));
  }

  return 0;
}


static int8_t scsi_write_10 (usbd_t  *pdev, uint8_t lun , uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;
  
  if (hmsc->bot_state == USBD_BOT_IDLE) /* Idle */
  {
    
    /* case 8 : Hi <> Do */
    
    if ((hmsc->cbw.bmFlags & 0x80) == 0x80)
    {
      scsi_sense_code(pdev,
                     hmsc->cbw.bLUN, 
                     ILLEGAL_REQUEST, 
                     INVALID_CDB);
      return -1;
    }
    
    /* Check whether Media is ready */
    if(((usbd_msc_io_t *)pdev->pUserData)->ready(lun) !=0 )
    {
      scsi_sense_code(pdev,
                     lun,
                     NOT_READY, 
                     MEDIUM_NOT_PRESENT);
      return -1;
    } 
    
    /* Check If media is write-protected */
    if(((usbd_msc_io_t *)pdev->pUserData)->write_protected(lun) !=0 )
    {
      scsi_sense_code(pdev,
                     lun,
                     NOT_READY, 
                     WRITE_PROTECTED);
      return -1;
    } 
    
    
    hmsc->scsi_blk_addr = (params[2] << 24) | \
      (params[3] << 16) | \
        (params[4] <<  8) | \
          params[5];
    hmsc->scsi_blk_len = (params[7] <<  8) | \
      params[8];  
    
    /* check if LBA address is in the right range */
    if(scsi_check_address_range(pdev,
                              lun,
                              hmsc->scsi_blk_addr,
                              hmsc->scsi_blk_len) < 0)
    {
      return -1; /* error */      
    }
    
    hmsc->scsi_blk_addr *= hmsc->scsi_blk_size;
    hmsc->scsi_blk_len  *= hmsc->scsi_blk_size;
    
    /* cases 3,11,13 : Hn,Ho <> D0 */
    if (hmsc->cbw.dDataLength != hmsc->scsi_blk_len)
    {
      scsi_sense_code(pdev,
                     hmsc->cbw.bLUN, 
                     ILLEGAL_REQUEST, 
                     INVALID_CDB);
      return -1;
    }
    
    /* Prepare EP to receive first data packet */
    hmsc->bot_state = USBD_BOT_DATA_OUT;  
    usbd_ll_prepare_receive (pdev,
                      MSC_EPOUT_ADDR,
                      hmsc->bot_data, 
                      MIN (hmsc->scsi_blk_len, MSC_MEDIA_PACKET));  
  }
  else /* Write Process ongoing */
  {
    return scsi_process_write(pdev, lun);
  }
  return 0;
}

static int8_t scsi_verify_10(usbd_t  *pdev, uint8_t lun , uint8_t *params)
{
  usbd_msc_bot_t  *hmsc = (usbd_msc_bot_t*) pdev->pClassData;

  if ((params[1]& 0x02) == 0x02)
  {
    scsi_sense_code (pdev,
                    lun,
                    ILLEGAL_REQUEST,
                    INVALID_FIELED_IN_COMMAND);
    return -1; /* Error, Verify Mode Not supported*/
  }

  if(scsi_check_address_range(pdev,
                            lun,
                            hmsc->scsi_blk_addr,
                            hmsc->scsi_blk_len) < 0)
  {
    return -1; /* error */
  }
  hmsc->bot_data_length = 0;
  return 0;
}


int8_t scsi_process_cmd(usbd_t  *pdev,
                           uint8_t lun,
                           uint8_t *params)
{

  switch (params[0])
  {
  case SCSI_TEST_UNIT_READY:
    return scsi_test_unit_ready(pdev, lun, params);

  case SCSI_REQUEST_SENSE:
    return scsi_request_sense (pdev, lun, params);
  case SCSI_INQUIRY:
    return scsi_inquiry(pdev, lun, params);

  case SCSI_START_STOP_UNIT:
    return scsi_start_stop_unit(pdev, lun, params);

  case SCSI_ALLOW_MEDIUM_REMOVAL:
    return scsi_start_stop_unit(pdev, lun, params);

  case SCSI_MODE_SENSE6:
    return scsi_mode_sense_6 (pdev, lun, params);

  case SCSI_MODE_SENSE10:
    return scsi_mode_sense_10 (pdev, lun, params);

  case SCSI_READ_FORMAT_CAPACITIES:
    return scsi_read_format_capacity(pdev, lun, params);

  case SCSI_READ_CAPACITY10:
    return scsi_read_capacity_10(pdev, lun, params);

  case SCSI_READ10:
    return scsi_read_10(pdev, lun, params);

  case SCSI_WRITE10:
    return scsi_write_10(pdev, lun, params);

  case SCSI_VERIFY10:
    return scsi_verify_10(pdev, lun, params);

  default:
    scsi_sense_code(pdev,
                   lun,
                   ILLEGAL_REQUEST,
                   INVALID_CDB);
    return -1;
  }
}


