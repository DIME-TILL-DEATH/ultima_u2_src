#include "usbd_ctlreq.h"
#include "usbd_ioreq.h"

static void usbd_get_descriptor(usbd_t *pdev ,
                               USBD_SetupReqTypedef *req);

static void usbd_set_address(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req);

static void usbd_set_config(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req);

static void usbd_get_config(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req);

static void usbd_get_status(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req);

static void usbd_set_feature(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req);

static void usbd_clear_feature(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req);

static uint8_t usbd_get_len(uint8_t *buf);

/**
  * @}
  */ 


/** @defgroup USBD_REQ_Private_Functions
  * @{
  */ 


/**
* @brief  USBD_StdDevReq
*         Handle standard usb device requests
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
usbd_status_t  usbd_std_dev_req (usbd_t *pdev , USBD_SetupReqTypedef  *req)
{
  usbd_status_t ret = USBD_OK;
  
  switch (req->bRequest) 
  {
  case USB_REQ_GET_DESCRIPTOR: 
    
    usbd_get_descriptor (pdev, req) ;
    break;
    
  case USB_REQ_SET_ADDRESS:                      
    usbd_set_address(pdev, req);
    break;
    
  case USB_REQ_SET_CONFIGURATION:                    
    usbd_set_config (pdev , req);
    break;
    
  case USB_REQ_GET_CONFIGURATION:                 
    usbd_get_config (pdev , req);
    break;
    
  case USB_REQ_GET_STATUS:                                  
    usbd_get_status (pdev , req);
    break;
    
    
  case USB_REQ_SET_FEATURE:   
    usbd_set_feature (pdev , req);
    break;
    
  case USB_REQ_CLEAR_FEATURE:                                   
    usbd_ctl_error (pdev , req);
    break;
    
  default:  
    usbd_ctl_error(pdev , req);
    break;
  }
  
  return ret;
}

/**
* @brief  USBD_StdItfReq
*         Handle standard usb interface requests
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
usbd_status_t  usbd_std_itf_req (usbd_t *pdev , USBD_SetupReqTypedef  *req)
{
  usbd_status_t ret = USBD_OK;
  
  switch (pdev->dev_state) 
  {
  case USBD_STATE_CONFIGURED:
    
    if (LOBYTE(req->wIndex) <= USBD_MAX_NUM_INTERFACES) 
    {
      pdev->pClass->Setup (pdev, req); 
      
      if((req->wLength == 0)&& (ret == USBD_OK))
      {
         usbd_ctl_send_status(pdev);
      }
    } 
    else 
    {                                               
	usbd_ctl_error(pdev , req);
    }
    break;
    
  default:
    usbd_ctl_error(pdev , req);
    break;
  }
  return USBD_OK;
}

/**
* @brief  USBD_StdEPReq
*         Handle standard usb endpoint requests
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
usbd_status_t  usbd_std_ep_req (usbd_t *pdev , USBD_SetupReqTypedef  *req)
{
  
  uint8_t   ep_addr;
  usbd_status_t ret = USBD_OK;
  USBD_EndpointTypeDef   *pep;
  ep_addr  = LOBYTE(req->wIndex);   
  
  /* Check if it is a class request */
  if ((req->bmRequest & 0x60) == 0x20)
  {
    pdev->pClass->Setup (pdev, req);
    
    return USBD_OK;
  }
  
  switch (req->bRequest) 
  {
    
  case USB_REQ_SET_FEATURE :
    
    switch (pdev->dev_state) 
    {
    case USBD_STATE_ADDRESSED:          
      if ((ep_addr != 0x00) && (ep_addr != 0x80)) 
      {
        usbd_ll_stall_ep(pdev , ep_addr);
      }
      break;	
      
    case USBD_STATE_CONFIGURED:   
      if (req->wValue == USB_FEATURE_EP_HALT)
      {
        if ((ep_addr != 0x00) && (ep_addr != 0x80)) 
        { 
          usbd_ll_stall_ep(pdev , ep_addr);
          
        }
      }
      pdev->pClass->Setup (pdev, req);   
      usbd_ctl_send_status(pdev);
      
      break;
      
    default:                         
      usbd_ctl_error(pdev , req);
      break;    
    }
    break;
    
  case USB_REQ_CLEAR_FEATURE :
    
    switch (pdev->dev_state) 
    {
    case USBD_STATE_ADDRESSED:          
      if ((ep_addr != 0x00) && (ep_addr != 0x80)) 
      {
        usbd_ll_stall_ep(pdev , ep_addr);
      }
      break;	
      
    case USBD_STATE_CONFIGURED:   
      if (req->wValue == USB_FEATURE_EP_HALT)
      {
        if ((ep_addr & 0x7F) != 0x00) 
        {        
          usbd_ll_clear_stall_ep(pdev , ep_addr);
          pdev->pClass->Setup (pdev, req);
        }
        usbd_ctl_send_status(pdev);
      }
      break;
      
    default:                         
      usbd_ctl_error(pdev , req);
      break;    
    }
    break;
    
  case USB_REQ_GET_STATUS:                  
    switch (pdev->dev_state) 
    {
    case USBD_STATE_ADDRESSED:          
      if ((ep_addr & 0x7F) != 0x00) 
      {
        usbd_ll_stall_ep(pdev , ep_addr);
      }
      break;	
      
    case USBD_STATE_CONFIGURED:
      pep = ((ep_addr & 0x80) == 0x80) ? &pdev->ep_in[ep_addr & 0x7F]:\
                                         &pdev->ep_out[ep_addr & 0x7F];
      if(usbd_ll_is_stall_ep(pdev, ep_addr))
      {
        pep->status = 0x0001;     
      }
      else
      {
        pep->status = 0x0000;  
      }
      
      usbd_ctl_send_data (pdev,
                        (uint8_t *)&pep->status,
                        2);
      break;
      
    default:                         
      usbd_ctl_error(pdev , req);
      break;
    }
    break;
    
  default:
    break;
  }
  return ret;
}
/**
* @brief  USBD_GetDescriptor
*         Handle Get Descriptor requests
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_get_descriptor(usbd_t *pdev ,
                               USBD_SetupReqTypedef *req)
{
  uint16_t len;
  uint8_t *pbuf;
  
    
  switch (req->wValue >> 8)
  { 
#if (USBD_LPM_ENABLED == 1)
  case USB_DESC_TYPE_BOS:
    pbuf = pdev->pDesc->GetBOSDescriptor(pdev->dev_speed, &len);
    break;
#endif    
  case USB_DESC_TYPE_DEVICE:
    pbuf = pdev->pDesc->GetDeviceDescriptor(pdev->dev_speed, &len);
    break;
    
  case USB_DESC_TYPE_CONFIGURATION:     
    if(pdev->dev_speed == USBD_SPEED_HIGH )   
    {
      pbuf   = (uint8_t *)pdev->pClass->GetHSConfigDescriptor(&len);
      pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
    }
    else
    {
      pbuf   = (uint8_t *)pdev->pClass->GetFSConfigDescriptor(&len);
      pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
    }
    break;
    
  case USB_DESC_TYPE_STRING:
    switch ((uint8_t)(req->wValue))
    {
    case USBD_IDX_LANGID_STR:
     pbuf = pdev->pDesc->GetLangIDStrDescriptor(pdev->dev_speed, &len);        
      break;
      
    case USBD_IDX_MFC_STR:
      pbuf = pdev->pDesc->GetManufacturerStrDescriptor(pdev->dev_speed, &len);
      break;
      
    case USBD_IDX_PRODUCT_STR:
      pbuf = pdev->pDesc->GetProductStrDescriptor(pdev->dev_speed, &len);
      break;
      
    case USBD_IDX_SERIAL_STR:
      pbuf = pdev->pDesc->GetSerialStrDescriptor(pdev->dev_speed, &len);
      break;
      
    case USBD_IDX_CONFIG_STR:
      pbuf = pdev->pDesc->GetConfigurationStrDescriptor(pdev->dev_speed, &len);
      break;
      
    case USBD_IDX_INTERFACE_STR:
      pbuf = pdev->pDesc->GetInterfaceStrDescriptor(pdev->dev_speed, &len);
      break;
      
    default:
#if (USBD_SUPPORT_USER_STRING == 1)
      pbuf = pdev->pClass->GetUsrStrDescriptor(pdev, (req->wValue) , &len);
      break;
#else      
      usbd_ctl_error(pdev , req);
      return;
#endif   
    }
    break;
  case USB_DESC_TYPE_DEVICE_QUALIFIER:                   

    if(pdev->dev_speed == USBD_SPEED_HIGH  )   
    {
      pbuf   = (uint8_t *)pdev->pClass->GetDeviceQualifierDescriptor(&len);
      break;
    }
    else
    {
      usbd_ctl_error(pdev , req);
      return;
    } 

  case USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION:
    if(pdev->dev_speed == USBD_SPEED_HIGH  )   
    {
      pbuf   = (uint8_t *)pdev->pClass->GetOtherSpeedConfigDescriptor(&len);
      pbuf[1] = USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION;
      break; 
    }
    else
    {
      usbd_ctl_error(pdev , req);
      return;
    }

  default: 
    usbd_ctl_error(pdev , req);
    return;
  }
  
  if((len != 0)&& (req->wLength != 0))
  {
    
    len = MIN(len , req->wLength);
    
    usbd_ctl_send_data (pdev,
                      pbuf,
                      len);
  }
  
}

/**
* @brief  USBD_SetAddress
*         Set device address
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_set_address(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req)
{
  uint8_t  dev_addr; 
  
  if ((req->wIndex == 0) && (req->wLength == 0)) 
  {
    dev_addr = (uint8_t)(req->wValue) & 0x7F;     
    
    if (pdev->dev_state == USBD_STATE_CONFIGURED) 
    {
	usbd_ctl_error(pdev , req);
    } 
    else 
    {
      pdev->dev_address = dev_addr;
      usbd_ll_set_usb_address(pdev, dev_addr);
      usbd_ctl_send_status(pdev);
      
      if (dev_addr != 0) 
      {
        pdev->dev_state  = USBD_STATE_ADDRESSED;
      } 
      else 
      {
        pdev->dev_state  = USBD_STATE_DEFAULT; 
      }
    }
  } 
  else 
  {
      usbd_ctl_error(pdev , req);
  } 
}

/**
* @brief  USBD_SetConfig
*         Handle Set device configuration request
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_set_config(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req)
{
  
  static uint8_t  cfgidx;
  
  cfgidx = (uint8_t)(req->wValue);                 
  
  if (cfgidx > USBD_MAX_NUM_CONFIGURATION ) 
  {            
      usbd_ctl_error(pdev , req);
  } 
  else 
  {
    switch (pdev->dev_state) 
    {
    case USBD_STATE_ADDRESSED:
      if (cfgidx) 
      {                                			   							   							   				
        pdev->dev_config = cfgidx;
        pdev->dev_state = USBD_STATE_CONFIGURED;
        if(usbd_set_class_config(pdev , cfgidx) == USBD_FAIL)
        {
          usbd_ctl_error(pdev , req);
          return;
        }
        usbd_ctl_send_status(pdev);
      }
      else 
      {
         usbd_ctl_send_status(pdev);
      }
      break;
      
    case USBD_STATE_CONFIGURED:
      if (cfgidx == 0) 
      {                           
        pdev->dev_state = USBD_STATE_ADDRESSED;
        pdev->dev_config = cfgidx;          
        usbd_clear_class_config(pdev , cfgidx);
        usbd_ctl_send_status(pdev);
        
      } 
      else  if (cfgidx != pdev->dev_config) 
      {
        /* Clear old configuration */
        usbd_clear_class_config(pdev , pdev->dev_config);
        
        /* set new configuration */
        pdev->dev_config = cfgidx;
        if(usbd_set_class_config(pdev , cfgidx) == USBD_FAIL)
        {
          usbd_ctl_error(pdev , req);
          return;
        }
        usbd_ctl_send_status(pdev);
      }
      else
      {
        usbd_ctl_send_status(pdev);
      }
      break;
      
    default:					
      usbd_ctl_error(pdev , req);
      break;
    }
  }
}

/**
* @brief  USBD_GetConfig
*         Handle Get device configuration request
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_get_config(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req)
{

  if (req->wLength != 1) 
  {                   
      usbd_ctl_error(pdev , req);
  }
  else 
  {
    switch (pdev->dev_state )  
    {
    case USBD_STATE_ADDRESSED:                     
      pdev->dev_default_config = 0;
      usbd_ctl_send_data (pdev,
                        (uint8_t *)&pdev->dev_default_config,
                        1);
      break;
      
    case USBD_STATE_CONFIGURED:   
      
      usbd_ctl_send_data (pdev,
                        (uint8_t *)&pdev->dev_config,
                        1);
      break;
      
    default:
      usbd_ctl_error(pdev , req);
      break;
    }
  }
}

/**
* @brief  USBD_GetStatus
*         Handle Get Status request
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_get_status(usbd_t *pdev ,
                           USBD_SetupReqTypedef *req)
{
  
    
  switch (pdev->dev_state) 
  {
  case USBD_STATE_ADDRESSED:
  case USBD_STATE_CONFIGURED:
    
#if ( USBD_SELF_POWERED == 1)
    pdev->dev_config_status = USB_CONFIG_SELF_POWERED;                                  
#else
    pdev->dev_config_status = 0;                                   
#endif
                      
    if (pdev->dev_remote_wakeup) 
    {
       pdev->dev_config_status |= USB_CONFIG_REMOTE_WAKEUP;                                
    }
    
    usbd_ctl_send_data (pdev,
                      (uint8_t *)& pdev->dev_config_status,
                      2);
    break;
    
  default :
    usbd_ctl_error(pdev , req);
    break;
  }
}


/**
* @brief  USBD_SetFeature
*         Handle Set device feature request
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_set_feature(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req)
{

  if (req->wValue == USB_FEATURE_REMOTE_WAKEUP)
  {
    pdev->dev_remote_wakeup = 1;  
    pdev->pClass->Setup (pdev, req);   
    usbd_ctl_send_status(pdev);
  }

}


/**
* @brief  USBD_ClrFeature
*         Handle clear device feature request
* @param  pdev: device instance
* @param  req: usb request
* @retval status
*/
static void usbd_clear_feature(usbd_t *pdev ,
                            USBD_SetupReqTypedef *req)
{
  switch (pdev->dev_state)
  {
  case USBD_STATE_ADDRESSED:
  case USBD_STATE_CONFIGURED:
    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP) 
    {
      pdev->dev_remote_wakeup = 0; 
      pdev->pClass->Setup (pdev, req);   
      usbd_ctl_send_status(pdev);
    }
    break;
    
  default :
    usbd_ctl_error(pdev , req);
    break;
  }
}

/**
* @brief  USBD_ParseSetupRequest 
*         Copy buffer into setup structure
* @param  pdev: device instance
* @param  req: usb request
* @retval None
*/

void usbd_parse_setup_request(USBD_SetupReqTypedef *req, uint8_t *pdata)
{
  req->bmRequest     = *(uint8_t *)  (pdata);
  req->bRequest      = *(uint8_t *)  (pdata +  1);
  req->wValue        = SWAPBYTE      (pdata +  2);
  req->wIndex        = SWAPBYTE      (pdata +  4);
  req->wLength       = SWAPBYTE      (pdata +  6);

}

/**
* @brief  USBD_CtlError 
*         Handle USB low level Error
* @param  pdev: device instance
* @param  req: usb request
* @retval None
*/

void usbd_ctl_error( usbd_t *pdev ,
                            USBD_SetupReqTypedef *req)
{
  usbd_ll_stall_ep(pdev , 0x80);
  usbd_ll_stall_ep(pdev , 0);
}


/**
  * @brief  USBD_GetString
  *         Convert Ascii string into unicode one
  * @param  desc : descriptor buffer
  * @param  unicode : Formatted string buffer (unicode)
  * @param  len : descriptor length
  * @retval None
  */
void usbd_get_string(uint8_t *desc, uint8_t *unicode, uint16_t *len)
{
  uint8_t idx = 0;
  
  if (desc != NULL) 
  {
    *len =  usbd_get_len(desc) * 2 + 2;
    unicode[idx++] = *len;
    unicode[idx++] =  USB_DESC_TYPE_STRING;
    
    while (*desc != '\0') 
    {
      unicode[idx++] = *desc++;
      unicode[idx++] =  0x00;
    }
  } 
}

/**
  * @brief  USBD_GetLen
  *         return the string length
   * @param  buf : pointer to the ascii string buffer
  * @retval string length
  */
static uint8_t usbd_get_len(uint8_t *buf)
{
    uint8_t  len = 0;

    while (*buf != '\0') 
    {
        len++;
        buf++;
    }

    return len;
}

