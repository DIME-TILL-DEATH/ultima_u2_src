#include "stm32f7xx_hal_pcd.h"


/*
 ===============================================================================
                 ##### Extended features functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Update FIFO configuration

@endverbatim
  * @{
  */

/**
  * @brief  Set Tx FIFO
  * @param  hpcd: PCD handle
  * @param  fifo: The number of Tx fifo
  * @param  size: Fifo size
  * @retval HAL status
  */
status_t HAL_PCDEx_SetTxFiFo(pcd_t *hpcd, uint8_t fifo, uint16_t size)
{
  uint8_t i = 0;
  uint32_t Tx_Offset = 0;

  /*  TXn min size = 16 words. (n  : Transmit FIFO index)
      When a TxFIFO is not used, the Configuration should be as follows: 
          case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txm can use the space allocated for Txn.
         case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txn should be configured with the minimum space of 16 words
     The FIFO is used optimally when used TxFIFOs are allocated in the top 
         of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
     When DMA is used 3n * FIFO locations should be reserved for internal DMA registers */
  
  Tx_Offset = hpcd->Instance->GRXFSIZ;
  
  if(fifo == 0)
  {
    hpcd->Instance->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((uint32_t)size << 16) | Tx_Offset);
  }
  else
  {
    Tx_Offset += (hpcd->Instance->DIEPTXF0_HNPTXFSIZ) >> 16;
    for (i = 0; i < (fifo - 1); i++)
    {
      Tx_Offset += (hpcd->Instance->DIEPTXF[i] >> 16);
    }
    
    /* Multiply Tx_Size by 2 to get higher performance */
    hpcd->Instance->DIEPTXF[fifo - 1] = (uint32_t)(((uint32_t)size << 16) | Tx_Offset);
  }
  
  return HAL_OK;
}

/**
  * @brief  Set Rx FIFO
  * @param  hpcd: PCD handle
  * @param  size: Size of Rx fifo
  * @retval HAL status
  */
status_t HAL_PCDEx_SetRxFiFo(pcd_t *hpcd, uint16_t size)
{
  hpcd->Instance->GRXFSIZ = size;
  
  return HAL_OK;
}

/**
  * @brief  Activate LPM Feature
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
status_t HAL_PCDEx_ActivateLPM(pcd_t *hpcd)
{
  usb_otg_global_t *USBx = hpcd->Instance;
  
  hpcd->lpm_active = ENABLE;
  hpcd->LPM_State = LPM_L0;
  USBx->GINTMSK |= USB_OTG_GINTMSK_LPMINTM;
  USBx->GLPMCFG |= (USB_OTG_GLPMCFG_LPMEN | USB_OTG_GLPMCFG_LPMACK | USB_OTG_GLPMCFG_ENBESL);
  
  return HAL_OK;  
}

/**
  * @brief  DeActivate LPM feature.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
status_t HAL_PCDEx_DeActivateLPM(pcd_t *hpcd)
{
  usb_otg_global_t *USBx = hpcd->Instance;
  
  hpcd->lpm_active = DISABLE;
  USBx->GINTMSK &= ~USB_OTG_GINTMSK_LPMINTM;
  USBx->GLPMCFG &= ~(USB_OTG_GLPMCFG_LPMEN | USB_OTG_GLPMCFG_LPMACK | USB_OTG_GLPMCFG_ENBESL);
  
  return HAL_OK;  
}

#if defined (USB_OTG_GCCFG_BCDEN)
/**
  * @brief  Handle BatteryCharging Process.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
void HAL_PCDEx_BCD_VBUSDetect(pcd_t *hpcd)
{
  usb_otg_global_t *USBx = hpcd->Instance;
  uint32_t tickstart = HAL_GetTick();
  
  /* Start BCD When device is connected */
  if (USBx_DEVICE->DCTL & USB_OTG_DCTL_SDIS)
  { 
    /* Enable DCD : Data Contact Detect */
    USBx->GCCFG |= USB_OTG_GCCFG_DCDEN;
    
    /* Wait Detect flag or a timeout is happen*/
    while ((USBx->GCCFG & USB_OTG_GCCFG_DCDET) == 0)
    {
      /* Check for the Timeout */
      if((HAL_GetTick() - tickstart ) > 1000)
      {
        HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_ERROR);
        return;
      }
    }
    
    /* Right response got */
    HAL_Delay(100); 
    
    /* Check Detect flag*/
    if (USBx->GCCFG & USB_OTG_GCCFG_DCDET)
    {
      HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_CONTACT_DETECTION);
    }
    
    /*Primary detection: checks if connected to Standard Downstream Port  
    (without charging capability) */
    USBx->GCCFG &=~ USB_OTG_GCCFG_DCDEN;
    USBx->GCCFG |=  USB_OTG_GCCFG_PDEN;
    HAL_Delay(100); 
    
    if (!(USBx->GCCFG & USB_OTG_GCCFG_PDET))
    {
      /* Case of Standard Downstream Port */
      HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_STD_DOWNSTREAM_PORT);
    }
    else  
    {
      /* start secondary detection to check connection to Charging Downstream 
      Port or Dedicated Charging Port */
      USBx->GCCFG &=~ USB_OTG_GCCFG_PDEN;
      USBx->GCCFG |=  USB_OTG_GCCFG_SDEN;
      HAL_Delay(100); 
      
      if ((USBx->GCCFG) & USB_OTG_GCCFG_SDET)
      { 
        /* case Dedicated Charging Port  */
        HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_DEDICATED_CHARGING_PORT);
      }
      else
      {
        /* case Charging Downstream Port  */
        HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_CHARGING_DOWNSTREAM_PORT);
      }
    }
    /* Battery Charging capability discovery finished */
    HAL_PCDEx_BCD_Callback(hpcd, PCD_BCD_DISCOVERY_COMPLETED);
  }
}

/**
  * @brief  Activate BatteryCharging feature.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
status_t HAL_PCDEx_ActivateBCD(pcd_t *hpcd)
{
  usb_otg_global_t *USBx = hpcd->Instance;

  hpcd->battery_charging_active = ENABLE; 
  USBx->GCCFG |= (USB_OTG_GCCFG_BCDEN);
  
  return HAL_OK;  
}

/**
  * @brief  Deactivate BatteryCharging feature.
  * @param  hpcd: PCD handle
  * @retval HAL status
  */
status_t HAL_PCDEx_DeActivateBCD(pcd_t *hpcd)
{
  usb_otg_global_t *USBx = hpcd->Instance;
  hpcd->battery_charging_active = DISABLE; 
  USBx->GCCFG &= ~(USB_OTG_GCCFG_BCDEN);
  return HAL_OK;  
}



#endif /* USB_OTG_GCCFG_BCDEN */
