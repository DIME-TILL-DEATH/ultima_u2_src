#ifndef __STM32F7xx_HAL_PCD_EX_H
#define __STM32F7xx_HAL_PCD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_def.h"
   

typedef enum  
{
  PCD_LPM_L0_ACTIVE = 0x00U, /* on */
  PCD_LPM_L1_ACTIVE = 0x01U, /* LPM L1 sleep */
}pcd_lpm_msg_t;

typedef enum  
{
  PCD_BCD_ERROR                     = 0xFF, 
  PCD_BCD_CONTACT_DETECTION         = 0xFE,
  PCD_BCD_STD_DOWNSTREAM_PORT       = 0xFD,
  PCD_BCD_CHARGING_DOWNSTREAM_PORT  = 0xFC,
  PCD_BCD_DEDICATED_CHARGING_PORT   = 0xFB,
  PCD_BCD_DISCOVERY_COMPLETED       = 0x00,
  
}pcd_bcd_msg_t;


status_t HAL_PCDEx_SetTxFiFo(pcd_t *hpcd, uint8_t fifo, uint16_t size);
status_t HAL_PCDEx_SetRxFiFo(pcd_t *hpcd, uint16_t size);
status_t HAL_PCDEx_ActivateLPM(pcd_t *hpcd);
status_t HAL_PCDEx_DeActivateLPM(pcd_t *hpcd);
status_t HAL_PCDEx_ActivateBCD(pcd_t *hpcd);
status_t HAL_PCDEx_DeActivateBCD(pcd_t *hpcd);
void HAL_PCDEx_BCD_VBUSDetect(pcd_t *hpcd);
void HAL_PCDEx_LPM_Callback(pcd_t *hpcd, pcd_lpm_msg_t msg);
void HAL_PCDEx_BCD_Callback(pcd_t *hpcd, pcd_bcd_msg_t msg);


#ifdef __cplusplus
}
#endif


#endif /* __STM32F7xx_HAL_PCD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
