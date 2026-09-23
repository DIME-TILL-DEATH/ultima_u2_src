#ifndef __STM32F7xx_HAL_PCD_H
#define __STM32F7xx_HAL_PCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbotg.h"

typedef enum 
{
  HAL_PCD_STATE_RESET   = 0x00U,
  HAL_PCD_STATE_READY   = 0x01U,
  HAL_PCD_STATE_ERROR   = 0x02U,
  HAL_PCD_STATE_BUSY    = 0x03U,
  HAL_PCD_STATE_TIMEOUT = 0x04U
} pcd_state_t;

/* Device LPM suspend state */
typedef enum  
{
  LPM_L0 = 0x00U, /* on */
  LPM_L1 = 0x01U, /* LPM L1 sleep */
  LPM_L2 = 0x02U, /* suspend */
  LPM_L3 = 0x03U, /* off */
}pcd_lpm_state_t;


typedef enum { irq, pool } handler_mode_t;

typedef struct
{
  usb_otg_global_t      *Instance;   /*!< Register base address              */
  usb_otg_config_t       Init;       /*!< PCD required parameters            */
  usb_otg_ep_t           IN_ep[16];  /*!< IN endpoint parameters             */
  usb_otg_ep_t           OUT_ep[16]; /*!< OUT endpoint parameters            */
  HAL_LockTypeDef         Lock;       /*!< PCD peripheral status              */
  volatile pcd_state_t    State;      /*!< PCD communication state            */
  uint32_t                Setup[12];  /*!< Setup packet buffer                */
  pcd_lpm_state_t         LPM_State;    /*!< LPM State                          */
  uint32_t                BESL;
  uint32_t                lpm_active;   /*!< Enable or disable the Link Power Management .                                  
                                        This parameter can be set to ENABLE or DISABLE */
  
  uint32_t battery_charging_active;     /*!< Enable or disable Battery charging.                                  
                                        This parameter can be set to ENABLE or DISABLE                      */
  void                    *pData;       /*!< Pointer to upper stack Handler */
  handler_mode_t          handler_mode ;
} pcd_t;

/**
  * @}
  */
    

#include "stm32f7xx_hal_pcd_ex.h"


#define PCD_SPEED_HIGH               0U
#define PCD_SPEED_HIGH_IN_FULL       1U
#define PCD_SPEED_FULL               2U

#define PCD_PHY_ULPI                 1U
#define PCD_PHY_EMBEDDED             2U
#define PCD_PHY_UTMI                 3U

#ifndef USBD_HS_TRDT_VALUE
 #define USBD_HS_TRDT_VALUE           9U
#endif /* USBD_HS_TRDT_VALUE */
#ifndef USBD_FS_TRDT_VALUE
 #define USBD_FS_TRDT_VALUE           5U
#endif /* USBD_HS_TRDT_VALUE */


#define __HAL_PCD_ENABLE(__HANDLE__)                   USB_EnableGlobalInt ((__HANDLE__)->Instance)
#define __HAL_PCD_DISABLE(__HANDLE__)                  USB_DisableGlobalInt ((__HANDLE__)->Instance)
   
#define __HAL_PCD_GET_FLAG(__HANDLE__, __INTERRUPT__)      ((USB_ReadInterrupts((__HANDLE__)->Instance) & (__INTERRUPT__)) == (__INTERRUPT__))
#define __HAL_PCD_CLEAR_FLAG(__HANDLE__, __INTERRUPT__)    (((__HANDLE__)->Instance->GINTSTS) = (__INTERRUPT__))
#define __HAL_PCD_IS_INVALID_INTERRUPT(__HANDLE__)         (USB_ReadInterrupts((__HANDLE__)->Instance) == 0)


#define __HAL_PCD_UNGATE_PHYCLOCK(__HANDLE__)             *(__IO uint32_t *)((uint32_t)((__HANDLE__)->Instance) + USB_OTG_PCGCCTL_BASE) &= \
                                                       ~(USB_OTG_PCGCCTL_STOPCLK)

#define __HAL_PCD_GATE_PHYCLOCK(__HANDLE__)               *(__IO uint32_t *)((uint32_t)((__HANDLE__)->Instance) + USB_OTG_PCGCCTL_BASE) |= USB_OTG_PCGCCTL_STOPCLK
                                                      
#define __HAL_PCD_IS_PHY_SUSPENDED(__HANDLE__)            ((*(__IO uint32_t *)((uint32_t)((__HANDLE__)->Instance) + USB_OTG_PCGCCTL_BASE))&0x10)
                                                         
#define USB_OTG_FS_WAKEUP_EXTI_RISING_EDGE                ((uint32_t)0x08U) 
#define USB_OTG_FS_WAKEUP_EXTI_FALLING_EDGE               ((uint32_t)0x0CU) 
#define USB_OTG_FS_WAKEUP_EXTI_RISING_FALLING_EDGE        ((uint32_t)0x10U) 

#define USB_OTG_HS_WAKEUP_EXTI_RISING_EDGE                ((uint32_t)0x08U) 
#define USB_OTG_HS_WAKEUP_EXTI_FALLING_EDGE               ((uint32_t)0x0CU) 
#define USB_OTG_HS_WAKEUP_EXTI_RISING_FALLING_EDGE        ((uint32_t)0x10U) 

#define USB_OTG_HS_WAKEUP_EXTI_LINE                       ((uint32_t)0x00100000U)  /*!< External interrupt line 20 Connected to the USB HS EXTI Line */
#define USB_OTG_FS_WAKEUP_EXTI_LINE                       ((uint32_t)0x00040000U)  /*!< External interrupt line 18 Connected to the USB FS EXTI Line */

#define __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_IT()    EXTI->IMR |= (USB_OTG_HS_WAKEUP_EXTI_LINE)
#define __HAL_USB_OTG_HS_WAKEUP_EXTI_DISABLE_IT()   EXTI->IMR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE)
#define __HAL_USB_OTG_HS_WAKEUP_EXTI_GET_FLAG()     EXTI->PR & (USB_OTG_HS_WAKEUP_EXTI_LINE)
#define __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG()   EXTI->PR = (USB_OTG_HS_WAKEUP_EXTI_LINE)

#define __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_EDGE() EXTI->FTSR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE);\
                                                          EXTI->RTSR |= USB_OTG_HS_WAKEUP_EXTI_LINE
                                                      
#define __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_FALLING_EDGE()  EXTI->FTSR |= (USB_OTG_HS_WAKEUP_EXTI_LINE);\
                                                            EXTI->RTSR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE)

#define __HAL_USB_OTG_HS_WAKEUP_EXTI_ENABLE_RISING_FALLING_EDGE()   EXTI->RTSR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE);\
                                                                    EXTI->FTSR &= ~(USB_OTG_HS_WAKEUP_EXTI_LINE;)\
                                                                    EXTI->RTSR |= USB_OTG_HS_WAKEUP_EXTI_LINE;\
                                                                    EXTI->FTSR |= USB_OTG_HS_WAKEUP_EXTI_LINE

#define __HAL_USB_OTG_HS_WAKEUP_EXTI_GENERATE_SWIT()   (EXTI->SWIER |= USB_OTG_FS_WAKEUP_EXTI_LINE) 
                                                                                                                    
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_IT()    EXTI->IMR |= USB_OTG_FS_WAKEUP_EXTI_LINE
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_DISABLE_IT()   EXTI->IMR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE)
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_GET_FLAG()     EXTI->PR & (USB_OTG_FS_WAKEUP_EXTI_LINE)
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG()   EXTI->PR = USB_OTG_FS_WAKEUP_EXTI_LINE

#define __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_EDGE() EXTI->FTSR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE);\
                                                          EXTI->RTSR |= USB_OTG_FS_WAKEUP_EXTI_LINE

                                                      
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_FALLING_EDGE()  EXTI->FTSR |= (USB_OTG_FS_WAKEUP_EXTI_LINE);\
                                                            EXTI->RTSR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE)

#define __HAL_USB_OTG_FS_WAKEUP_EXTI_ENABLE_RISING_FALLING_EDGE()  EXTI->RTSR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE);\
                                                                   EXTI->FTSR &= ~(USB_OTG_FS_WAKEUP_EXTI_LINE);\
                                                                   EXTI->RTSR |= USB_OTG_FS_WAKEUP_EXTI_LINE;\
                                                                   EXTI->FTSR |= USB_OTG_FS_WAKEUP_EXTI_LINE 
                                                         
#define __HAL_USB_OTG_FS_WAKEUP_EXTI_GENERATE_SWIT()  (EXTI->SWIER |= USB_OTG_FS_WAKEUP_EXTI_LINE)                                                     

status_t HAL_PCD_Init(pcd_t *hpcd);
status_t HAL_PCD_DeInit (pcd_t *hpcd);


status_t HAL_PCD_Start(pcd_t *hpcd);
status_t HAL_PCD_Stop(pcd_t *hpcd);
void pcd_handler(pcd_t *hpcd);

void HAL_PCD_DataOutStageCallback(pcd_t *hpcd, uint8_t epnum);
void HAL_PCD_DataInStageCallback(pcd_t *hpcd, uint8_t epnum);
void HAL_PCD_SetupStageCallback(pcd_t *hpcd);
void HAL_PCD_SOFCallback(pcd_t *hpcd);
void HAL_PCD_ResetCallback(pcd_t *hpcd);
void HAL_PCD_SuspendCallback(pcd_t *hpcd);
void HAL_PCD_ResumeCallback(pcd_t *hpcd);
void HAL_PCD_ISOOUTIncompleteCallback(pcd_t *hpcd, uint8_t epnum);
void HAL_PCD_ISOINIncompleteCallback(pcd_t *hpcd, uint8_t epnum);
void HAL_PCD_ConnectCallback(pcd_t *hpcd);
void HAL_PCD_DisconnectCallback(pcd_t *hpcd);

status_t HAL_PCD_DevConnect(pcd_t *hpcd);
status_t HAL_PCD_DevDisconnect(pcd_t *hpcd);
status_t HAL_PCD_SetAddress(pcd_t *hpcd, uint8_t address);
status_t HAL_PCD_EP_Open(pcd_t *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
status_t HAL_PCD_EP_Close(pcd_t *hpcd, uint8_t ep_addr);
status_t HAL_PCD_EP_Receive(pcd_t *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
status_t HAL_PCD_EP_Transmit(pcd_t *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
uint16_t HAL_PCD_EP_GetRxCount(pcd_t *hpcd, uint8_t ep_addr);
status_t HAL_PCD_EP_SetStall(pcd_t *hpcd, uint8_t ep_addr);
status_t HAL_PCD_EP_ClrStall(pcd_t *hpcd, uint8_t ep_addr);
status_t HAL_PCD_EP_Flush(pcd_t *hpcd, uint8_t ep_addr);
status_t HAL_PCD_ActivateRemoteWakeup(pcd_t *hpcd);
status_t HAL_PCD_DeActivateRemoteWakeup(pcd_t *hpcd);

pcd_state_t HAL_PCD_GetState(pcd_t *hpcd);

#define IS_PCD_ALL_INSTANCE(INSTANCE) (((INSTANCE) == USB_OTG_FS) || \
                                       ((INSTANCE) == USB_OTG_HS))


#ifdef __cplusplus
}
#endif


#endif /* __STM32F7xx_HAL_PCD_H */

