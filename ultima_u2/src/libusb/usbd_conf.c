#include "stm32f7xx.h"

#include "usbd_def.h"
#include "usbd_core.h"



void HAL_PCD_SetupStageCallback(pcd_t *hpcd)
{
  usbd_ll_setup_stage((usbd_t*)hpcd->pData, (uint8_t *)hpcd->Setup);
}

void HAL_PCD_DataOutStageCallback(pcd_t *hpcd, uint8_t epnum)
{
  usbd_ll_data_out_stage((usbd_t*)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

void HAL_PCD_DataInStageCallback(pcd_t *hpcd, uint8_t epnum)
{
  usbd_ll_data_in_stage((usbd_t*)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

void HAL_PCD_SOFCallback(pcd_t *hpcd)
{
  usbd_ll_sof((usbd_t*)hpcd->pData);
}

void HAL_PCD_ResetCallback(pcd_t *hpcd)
{ 
  USBD_SpeedTypeDef speed = USBD_SPEED_FULL;

  /*Set USB Current Speed*/
  switch (hpcd->Init.speed)
  {
  case PCD_SPEED_HIGH:
    speed = USBD_SPEED_HIGH;
    break;
  case PCD_SPEED_FULL:
    speed = USBD_SPEED_FULL;    
    break;
	
  default:
    speed = USBD_SPEED_FULL;    
    break;    
  }
  usbd_ll_set_speed((usbd_t*)hpcd->pData, speed);
  
  /*Reset Device*/
  usbd_ll_reset((usbd_t*)hpcd->pData);
}

void HAL_PCD_SuspendCallback(pcd_t *hpcd)
{  
   /* Inform USB library that core enters in suspend Mode */
  usbd_ll_suspend((usbd_t*)hpcd->pData);
  __HAL_PCD_GATE_PHYCLOCK(hpcd);
  /*Enter in STOP mode */
  /* USER CODE BEGIN 2 */
  if (hpcd->Init.low_power_enable)
  {
    port_set_sleep_deep();
  }
  /* USER CODE END 2 */
}

void HAL_PCD_ResumeCallback(pcd_t *hpcd)
{
  usbd_ll_resume((usbd_t*)hpcd->pData);

}

void HAL_PCD_ISOOUTIncompleteCallback(pcd_t *hpcd, uint8_t epnum)
{
  usbd_ll_iso_out_incomplete((usbd_t*)hpcd->pData, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(pcd_t *hpcd, uint8_t epnum)
{
  usbd_ll_iso_in_incomplete((usbd_t*)hpcd->pData, epnum);
}

void HAL_PCD_ConnectCallback(pcd_t *hpcd)
{
  usbd_ll_dev_connected((usbd_t*)hpcd->pData);
}

void HAL_PCD_DisconnectCallback(pcd_t *hpcd)
{
  usbd_ll_dev_disconnected((usbd_t*)hpcd->pData);
}

/*******************************************************************************
                       LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/

uint32_t usbd_ll_get_rx_data_size  (usbd_t *pdev, uint8_t  ep_addr)
{
  return HAL_PCD_EP_GetRxCount((pcd_t*) pdev->pData, ep_addr);
}

usbd_status_t  usbd_ll_init (pcd_t* pcd, usbd_t *pdev)
{ 
  /* Init USB_IP */
  if (pdev->id == full_speed) {
  /* Link The driver to the stack */	
  


      pcd->pData = pdev;
  pdev->pData = pcd;

 pcd->Instance = USB_OTG_FS;
 pcd->Init.dev_endpoints = 6;
 pcd->Init.speed = PCD_SPEED_FULL;
 pcd->Init.dma_enable = DISABLE;
 pcd->Init.ep0_mps = DEP0CTL_MPS_64;
 pcd->Init.phy_itface = PCD_PHY_EMBEDDED;
 pcd->Init.Sof_enable = DISABLE;
 pcd->Init.low_power_enable = DISABLE;
 pcd->Init.lpm_enable = DISABLE;
 pcd->Init.vbus_sensing_enable = ENABLE;
 pcd->Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(pcd) != HAL_OK)
  {
    port_error();
  }

  HAL_PCDEx_SetRxFiFo(pcd, 0x80);
  HAL_PCDEx_SetTxFiFo(pcd, 0, 0x40);
  HAL_PCDEx_SetTxFiFo(pcd, 1, 0x80);
  }
  return USBD_OK;
}

usbd_status_t  usbd_ll_deinit (usbd_t *pdev)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
 
  hal_status = HAL_PCD_DeInit(pdev->pData);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status; 
}

usbd_status_t  usbd_ll_start(usbd_t *pdev)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
 
  hal_status = HAL_PCD_Start(pdev->pData);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;  
}

usbd_status_t  usbd_ll_stop (usbd_t *pdev)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
 
  hal_status = HAL_PCD_Stop(pdev->pData);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status; 
}

usbd_status_t  usbd_ll_open_ep  (usbd_t *pdev,
                                      uint8_t  ep_addr,                                      
                                      uint8_t  ep_type,
                                      uint16_t ep_mps)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;

  hal_status = HAL_PCD_EP_Open(pdev->pData, 
                               ep_addr, 
                               ep_mps, 
                               ep_type);
  
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status; 
}

usbd_status_t  usbd_ll_close_ep (usbd_t *pdev, uint8_t ep_addr)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
  
  hal_status = HAL_PCD_EP_Close(pdev->pData, ep_addr);
      
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;  
}

usbd_status_t  usbd_ll_flush_ep (usbd_t *pdev, uint8_t ep_addr)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
  
  hal_status = HAL_PCD_EP_Flush(pdev->pData, ep_addr);
      
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;  
}

usbd_status_t  usbd_ll_stall_ep (usbd_t *pdev, uint8_t ep_addr)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
  
  hal_status = HAL_PCD_EP_SetStall(pdev->pData, ep_addr);
      
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;  
}

usbd_status_t  usbd_ll_clear_stall_ep (usbd_t *pdev, uint8_t ep_addr)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
  
  hal_status = HAL_PCD_EP_ClrStall(pdev->pData, ep_addr);  
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status; 
}

uint8_t usbd_ll_is_stall_ep (usbd_t *pdev, uint8_t ep_addr)
{
  pcd_t *hpcd = (pcd_t*) pdev->pData;
  
  if((ep_addr & 0x80) == 0x80)
  {
    return hpcd->IN_ep[ep_addr & 0x7F].is_stall; 
  }
  else
  {
    return hpcd->OUT_ep[ep_addr & 0x7F].is_stall; 
  }
}

usbd_status_t  usbd_ll_set_usb_address (usbd_t *pdev, uint8_t dev_addr)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;
  
  hal_status = HAL_PCD_SetAddress(pdev->pData, dev_addr);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;  
}

usbd_status_t  usbd_ll_transmit (usbd_t *pdev,
                                      uint8_t  ep_addr,                                      
                                      uint8_t  *pbuf,
                                      uint16_t  size)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;

  hal_status = HAL_PCD_EP_Transmit(pdev->pData, ep_addr, pbuf, size);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status;    
}

usbd_status_t  usbd_ll_prepare_receive(usbd_t *pdev,
                                           uint8_t  ep_addr,                                      
                                           uint8_t  *pbuf,
                                           uint16_t  size)
{
  status_t hal_status = HAL_OK;
  usbd_status_t usb_status = USBD_OK;

  hal_status = HAL_PCD_EP_Receive(pdev->pData, ep_addr, pbuf, size);
     
  switch (hal_status) {
    case HAL_OK :
      usb_status = USBD_OK;
    break;
    case HAL_ERROR :
      usb_status = USBD_FAIL;
    break;
    case HAL_BUSY :
      usb_status = USBD_BUSY;
    break;
    case HAL_TIMEOUT :
      usb_status = USBD_FAIL;
    break;
    default :
      usb_status = USBD_FAIL;
    break;
  }
  return usb_status; 
}


#if (USBD_LPM_ENABLED == 1)

void HAL_PCDEx_LPM_Callback(pcd_t *hpcd, pcd_lpm_msg_t msg)
{
  switch ( msg)
  {
  case PCD_LPM_L0_ACTIVE:
    if (hpcd->Init.low_power_enable)
    {
	port_system_init();
        port_reset_sleep_deep();
    }
    __HAL_PCD_UNGATE_PHYCLOCK(hpcd);
    usbd_ll_resume(hpcd->pData);
    break;
    
  case PCD_LPM_L1_ACTIVE:
    __HAL_PCD_GATE_PHYCLOCK(hpcd);
    usbd_ll_suspend(hpcd->pData);
    
    /*Enter in STOP mode */
    if (hpcd->Init.low_power_enable)
    {   
      port_set_sleep_deep();
    }     
    break;   
  }
}
#endif



#if defined (USB_OTG_GCCFG_BCDEN)

void HAL_PCDEx_BCD_Callback(pcd_t *hpcd, pcd_bcd_msg_t msg)
{
}

#endif
