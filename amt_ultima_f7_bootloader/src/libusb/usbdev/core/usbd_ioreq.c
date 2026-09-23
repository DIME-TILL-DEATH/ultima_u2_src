#include "usbd_ioreq.h"

usbd_status_t  usbd_ctl_send_data (usbd_t  *pdev,
                               uint8_t *pbuf,
                               uint16_t len)
{
  /* Set EP0 State */
  pdev->ep0_state          = USBD_EP0_DATA_IN;                                      
  pdev->ep_in[0].total_length = len;
  pdev->ep_in[0].rem_length   = len;
 /* Start the transfer */
  usbd_ll_transmit (pdev, 0x00, pbuf, len);
  
  return USBD_OK;
}

usbd_status_t  usbd_ctl_continue_send_data (usbd_t  *pdev,
                                       uint8_t *pbuf,
                                       uint16_t len)
{
 /* Start the next transfer */
  usbd_ll_transmit (pdev, 0x00, pbuf, len);
  
  return USBD_OK;
}

usbd_status_t  usbd_ctl_prepare_rx (usbd_t  *pdev,
                                  uint8_t *pbuf,                                  
                                  uint16_t len)
{
  /* Set EP0 State */
  pdev->ep0_state = USBD_EP0_DATA_OUT; 
  pdev->ep_out[0].total_length = len;
  pdev->ep_out[0].rem_length   = len;
  /* Start the transfer */
  usbd_ll_prepare_receive (pdev,
                          0,
                          pbuf,
                         len);
  
  return USBD_OK;
}

usbd_status_t  usbd_ctl_continue_rx (usbd_t  *pdev,
                                          uint8_t *pbuf,                                          
                                          uint16_t len)
{

  usbd_ll_prepare_receive (pdev,
                          0,                     
                          pbuf,                         
                          len);
  return USBD_OK;
}

usbd_status_t  usbd_ctl_send_status (usbd_t  *pdev)
{

  /* Set EP0 State */
  pdev->ep0_state = USBD_EP0_STATUS_IN;
  
 /* Start the transfer */
  usbd_ll_transmit (pdev, 0x00, NULL, 0);
  
  return USBD_OK;
}

usbd_status_t  usbd_ctl_receive_status (usbd_t  *pdev)
{
  /* Set EP0 State */
  pdev->ep0_state = USBD_EP0_STATUS_OUT; 
  
 /* Start the transfer */  
  usbd_ll_prepare_receive ( pdev,
                    0,
                    NULL,
                    0);  

  return USBD_OK;
}

uint16_t  usbd_get_rx_count (usbd_t  *pdev , uint8_t ep_addr)
{
  return usbd_ll_get_rx_data_size(pdev, ep_addr);
}

