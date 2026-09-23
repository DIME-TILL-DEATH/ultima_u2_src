
#include "usbd_core.h"

usbd_status_t usbd_init(pcd_t* pcd, usbd_t *pdev, usbd_descriptors_t *pdesc, uint8_t id)
{
  /* Check whether the USB Host handle is valid */
  if(pdev == NULL)
  {
    return USBD_FAIL; 
  }
  
  /* Unlink previous class*/
  if(pdev->pClass != NULL)
  {
    pdev->pClass = NULL;
  }
  
  /* Assign USBD Descriptors */
  if(pdesc != NULL)
  {
    pdev->pDesc = pdesc;
  }
  
  /* Set Device initial State */
  pdev->dev_state  = USBD_STATE_DEFAULT;
  pdev->id = id;
  /* Initialize low level driver */
  usbd_ll_init( pcd, pdev);
  
  return USBD_OK;
}


usbd_status_t usbd_deinit(usbd_t *pdev)
{
  /* Set Default State */
  pdev->dev_state  = USBD_STATE_DEFAULT;
  
  /* Free Class Resources */
  pdev->pClass->DeInit(pdev, pdev->dev_config);  
  
    /* Stop the low level driver  */
  usbd_ll_stop(pdev);
  
  /* Initialize low level driver */
  usbd_ll_deinit(pdev);
  
  return USBD_OK;
}



usbd_status_t  usbd_register_class(usbd_t *pdev, usbd_class_t *pclass)
{
  usbd_status_t   status = USBD_OK;
  if(pclass != 0)
  {
    /* link the class to the USB Device handle */
    pdev->pClass = pclass;
    status = USBD_OK;
  }
  else
  {
    status = USBD_FAIL; 
  }
  
  return status;
}


usbd_status_t  usbd_start  (usbd_t *pdev)
{
  
  /* Start the low level driver  */
  usbd_ll_start(pdev);
  
  return USBD_OK;  
}


usbd_status_t  usbd_stop   (usbd_t *pdev)
{
  /* Free Class Resources */
  pdev->pClass->DeInit(pdev, pdev->dev_config);  

  /* Stop the low level driver  */
  usbd_ll_stop(pdev);
  
  return USBD_OK;  
}


usbd_status_t  usbd_run_test_mode (usbd_t  *pdev)
{
  return USBD_OK;
}

usbd_status_t usbd_set_class_config(usbd_t  *pdev, uint8_t cfgidx)
{
  usbd_status_t   ret = USBD_FAIL;
  
  if(pdev->pClass != NULL)
  {
    /* Set configuration  and Start the Class*/
    if(pdev->pClass->Init(pdev, cfgidx) == 0)
    {
      ret = USBD_OK;
    }
  }
  return ret; 
}

usbd_status_t usbd_clear_class_config(usbd_t  *pdev, uint8_t cfgidx)
{
  /* Clear configuration  and De-initialize the Class process*/
  pdev->pClass->DeInit(pdev, cfgidx);  
  return USBD_OK;
}

usbd_status_t usbd_ll_setup_stage(usbd_t *pdev, uint8_t *psetup)
{

  usbd_parse_setup_request(&pdev->request, psetup);
  
  pdev->ep0_state = USBD_EP0_SETUP;
  pdev->ep0_data_len = pdev->request.wLength;
  
  switch (pdev->request.bmRequest & 0x1F) 
  {
  case USB_REQ_RECIPIENT_DEVICE:   
    usbd_std_dev_req (pdev, &pdev->request);
    break;
    
  case USB_REQ_RECIPIENT_INTERFACE:     
    usbd_std_itf_req(pdev, &pdev->request);
    break;
    
  case USB_REQ_RECIPIENT_ENDPOINT:        
    usbd_std_ep_req(pdev, &pdev->request);
    break;
    
  default:           
    usbd_ll_stall_ep(pdev , pdev->request.bmRequest & 0x80);
    break;
  }  
  return USBD_OK;  
}

usbd_status_t usbd_ll_data_out_stage(usbd_t *pdev , uint8_t epnum, uint8_t *pdata)
{
  USBD_EndpointTypeDef    *pep;
  
  if(epnum == 0) 
  {
    pep = &pdev->ep_out[0];
    
    if ( pdev->ep0_state == USBD_EP0_DATA_OUT)
    {
      if(pep->rem_length > pep->maxpacket)
      {
        pep->rem_length -=  pep->maxpacket;
       
        usbd_ctl_continue_rx (pdev,
                            pdata,
                            MIN(pep->rem_length ,pep->maxpacket));
      }
      else
      {
        if((pdev->pClass->EP0_RxReady != NULL)&&
           (pdev->dev_state == USBD_STATE_CONFIGURED))
        {
          pdev->pClass->EP0_RxReady(pdev); 
        }
        usbd_ctl_send_status(pdev);
      }
    }
  }
  else if((pdev->pClass->DataOut != NULL)&&
          (pdev->dev_state == USBD_STATE_CONFIGURED))
  {
    pdev->pClass->DataOut(pdev, epnum); 
  }  
  return USBD_OK;
}

usbd_status_t usbd_ll_data_in_stage(usbd_t *pdev ,uint8_t epnum, uint8_t *pdata)
{
  USBD_EndpointTypeDef    *pep;
    
  if(epnum == 0) 
  {
    pep = &pdev->ep_in[0];
    
    if ( pdev->ep0_state == USBD_EP0_DATA_IN)
    {
      if(pep->rem_length > pep->maxpacket)
      {
        pep->rem_length -=  pep->maxpacket;
        
        usbd_ctl_continue_send_data (pdev,
                                  pdata, 
                                  pep->rem_length);
        
        /* Prepare endpoint for premature end of transfer */
        usbd_ll_prepare_receive (pdev,
                                0,
                                NULL,
                                0);  
      }
      else
      { /* last packet is MPS multiple, so send ZLP packet */
        if((pep->total_length % pep->maxpacket == 0) &&
           (pep->total_length >= pep->maxpacket) &&
             (pep->total_length < pdev->ep0_data_len ))
        {
          
          usbd_ctl_continue_send_data(pdev , NULL, 0);
          pdev->ep0_data_len = 0;
          
        /* Prepare endpoint for premature end of transfer */
          usbd_ll_prepare_receive (pdev,
                                0,
                                NULL,
                                0);
        }
        else
        {
          if((pdev->pClass->EP0_TxSent != NULL)&&
             (pdev->dev_state == USBD_STATE_CONFIGURED))
          {
            pdev->pClass->EP0_TxSent(pdev); 
          }          
          usbd_ctl_receive_status(pdev);
        }
      }
    }
    if (pdev->dev_test_mode == 1)
    {
      usbd_run_test_mode(pdev);
      pdev->dev_test_mode = 0;
    }
  }
  else if((pdev->pClass->DataIn != NULL)&& 
          (pdev->dev_state == USBD_STATE_CONFIGURED))
  {
    pdev->pClass->DataIn(pdev, epnum); 
  }  
  return USBD_OK;
}

usbd_status_t usbd_ll_reset(usbd_t  *pdev)
{
  /* Open EP0 OUT */
  usbd_ll_open_ep(pdev,
              0x00,
              USBD_EP_TYPE_CTRL,
              USB_MAX_EP0_SIZE);
  
  pdev->ep_out[0].maxpacket = USB_MAX_EP0_SIZE;
  
  /* Open EP0 IN */
  usbd_ll_open_ep(pdev,
              0x80,
              USBD_EP_TYPE_CTRL,
              USB_MAX_EP0_SIZE);
  
  pdev->ep_in[0].maxpacket = USB_MAX_EP0_SIZE;
  /* Upon Reset call user call back */
  pdev->dev_state = USBD_STATE_DEFAULT;
  
  if (pdev->pClassData) 
    pdev->pClass->DeInit(pdev, pdev->dev_config);  
 
  
  return USBD_OK;
}

usbd_status_t usbd_ll_set_speed(usbd_t  *pdev, USBD_SpeedTypeDef speed)
{
  pdev->dev_speed = speed;
  return USBD_OK;
}

usbd_status_t usbd_ll_suspend(usbd_t  *pdev)
{
  pdev->dev_old_state =  pdev->dev_state;
  pdev->dev_state  = USBD_STATE_SUSPENDED;
  return USBD_OK;
}

usbd_status_t usbd_ll_resume(usbd_t  *pdev)
{
  pdev->dev_state = pdev->dev_old_state;  
  return USBD_OK;
}

usbd_status_t usbd_ll_sof(usbd_t  *pdev)
{
  if(pdev->dev_state == USBD_STATE_CONFIGURED)
  {
    if(pdev->pClass->SOF != NULL)
    {
      pdev->pClass->SOF(pdev);
    }
  }
  return USBD_OK;
}

usbd_status_t usbd_ll_iso_in_incomplete(usbd_t  *pdev, uint8_t epnum)
{
  return USBD_OK;
}

usbd_status_t usbd_ll_iso_out_incomplete(usbd_t  *pdev, uint8_t epnum)
{
  return USBD_OK;
}

usbd_status_t usbd_ll_dev_connected(usbd_t  *pdev)
{
  return USBD_OK;
}

usbd_status_t usbd_ll_dev_disconnected(usbd_t  *pdev)
{
  /* Free Class Resources */
  pdev->dev_state = USBD_STATE_DEFAULT;
  pdev->pClass->DeInit(pdev, pdev->dev_config);
  return USBD_OK;
}
