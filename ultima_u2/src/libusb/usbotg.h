
#ifndef __USBOTG_H__
#define __USBOTG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal_def.h"


typedef enum 
{
   USB_OTG_DEVICE_MODE  = 0U,
   USB_OTG_HOST_MODE    = 1U,
   USB_OTG_DRD_MODE     = 2U
   
}usb_otg_mode_t;

/** 
  * @brief  URB States definition  
  */ 
typedef enum {
  URB_IDLE = 0U,
  URB_DONE,
  URB_NOTREADY,
  URB_NYET,
  URB_ERROR,
  URB_STALL
    
}usb_otg_urb_state_t;


typedef enum {
  HC_IDLE = 0U,
  HC_XFRC,
  HC_HALTED,
  HC_NAK,
  HC_NYET,
  HC_STALL,
  HC_XACTERR,  
  HC_BBLERR,   
  HC_DATATGLERR
    
}usb_otg_hc_state_t;

/** 
  * @brief  PCD Initialization Structure definition  
  */
typedef struct
{
  uint32_t dev_endpoints;        /*!< Device Endpoints number.
                                      This parameter depends on the used USB core.   
                                      This parameter must be a number between Min_Data = 1 and Max_Data = 15 */    
  
  uint32_t Host_channels;        /*!< Host Channels number.
                                      This parameter Depends on the used USB core.   
                                      This parameter must be a number between Min_Data = 1 and Max_Data = 15 */       

  uint32_t speed;                /*!< USB Core speed.
                                      This parameter can be any value of @ref USB_Core_Speed_                */        
                               
  uint32_t dma_enable;           /*!< Enable or disable of the USB embedded DMA.                             */            

  uint32_t ep0_mps;              /*!< Set the Endpoint 0 Max Packet size. 
                                      This parameter can be any value of @ref USB_EP0_MPS_                   */              
                       
  uint32_t phy_itface;           /*!< Select the used PHY interface.
                                      This parameter can be any value of @ref USB_Core_PHY_                  */ 
                                
  uint32_t Sof_enable;           /*!< Enable or disable the output of the SOF signal.                        */     
                               
  uint32_t low_power_enable;     /*!< Enable or disable the low power mode.                                  */
  
  uint32_t lpm_enable;           /*!< Enable or disable Link Power Management.                               */
  
  uint32_t battery_charging_enable; /*!< Enable or disable Battery charging.                                 */   
  
  uint32_t vbus_sensing_enable;  /*!< Enable or disable the VBUS Sensing feature.                            */ 

  uint32_t use_dedicated_ep1;    /*!< Enable or disable the use of the dedicated EP1 interrupt.              */      
  
  uint32_t use_external_vbus;    /*!< Enable or disable the use of the external VBUS.                        */   
  
}usb_otg_config_t;

typedef struct
{
  uint8_t   num;            /*!< Endpoint number
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15    */ 
                                
  uint8_t   is_in;          /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */ 
  
  uint8_t   is_stall;       /*!< Endpoint stall condition
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */ 
  
  uint8_t   type;           /*!< Endpoint type
                                 This parameter can be any value of @ref USB_EP_Type_                     */ 
                                
  uint8_t   data_pid_start; /*!< Initial data PID
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */
                                
  uint8_t   even_odd_frame; /*!< IFrame parity
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 1    */
                                
  uint16_t  tx_fifo_num;    /*!< Transmission FIFO number
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 15   */
                                
  uint32_t  maxpacket;      /*!< Endpoint Max packet size
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 64KB */

  uint8_t   *xfer_buff;     /*!< Pointer to transfer buffer                                               */
                                
  uint32_t  dma_addr;       /*!< 32 bits aligned transfer buffer address                                  */
  
  uint32_t  xfer_len;       /*!< Current transfer length                                                  */
  
  uint32_t  xfer_count;     /*!< Partial transfer length in case of multi packet transfer                 */

}usb_otg_ep_t;

typedef struct
{
  uint8_t   dev_addr ;     /*!< USB device address.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 255    */ 

  uint8_t   ch_num;        /*!< Host channel number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */ 
                                
  uint8_t   ep_num;        /*!< Endpoint number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */ 
                                
  uint8_t   ep_is_in;      /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */ 
                                
  uint8_t   speed;         /*!< USB Host speed.
                                This parameter can be any value of @ref USB_Core_Speed_                    */
                                
  uint8_t   do_ping;       /*!< Enable or disable the use of the PING protocol for HS mode.                */
  
  uint8_t   process_ping;  /*!< Execute the PING protocol for HS mode.                                     */

  uint8_t   ep_type;       /*!< Endpoint Type.
                                This parameter can be any value of @ref USB_EP_Type_                       */
                                
  uint16_t  max_packet;    /*!< Endpoint Max packet size.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 64KB   */
                                
  uint8_t   data_pid;      /*!< Initial data PID.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
                                
  uint8_t   *xfer_buff;    /*!< Pointer to transfer buffer.                                                */
  
  uint32_t  xfer_len;      /*!< Current transfer length.                                                   */
  
  uint32_t  xfer_count;    /*!< Partial transfer length in case of multi packet transfer.                  */
  
  uint8_t   toggle_in;     /*!< IN transfer current toggle flag.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
                                
  uint8_t   toggle_out;    /*!< OUT transfer current toggle flag
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  
  uint32_t  dma_addr;      /*!< 32 bits aligned transfer buffer address.                                   */
  
  uint32_t  ErrCnt;        /*!< Host channel error count.*/
  
  usb_otg_urb_state_t  urb_state;  /*!< URB state.
                                           This parameter can be any value of @ref USB_OTG_URBStateTypeDef */ 
  
  usb_otg_hc_state_t   state;     /*!< Host Channel state.
                                           This parameter can be any value of @ref USB_OTG_HCStateTypeDef  */ 
                                             
} usb_otg_hc_t ;
  

#define USB_OTG_MODE_DEVICE                    0U
#define USB_OTG_MODE_HOST                      1U
#define USB_OTG_MODE_DRD                       2U

#define USB_OTG_SPEED_HIGH                     0U
#define USB_OTG_SPEED_HIGH_IN_FULL             1U
#define USB_OTG_SPEED_LOW                      2U  
#define USB_OTG_SPEED_FULL                     3U
  
#define USB_OTG_ULPI_PHY                       1U
#define USB_OTG_EMBEDDED_PHY                   2U
#define USB_OTG_HS_EMBEDDED_PHY                3U

#if !defined  (USB_HS_PHYC_TUNE_VALUE) 
  #define USB_HS_PHYC_TUNE_VALUE    0x00000F13U /*!< Value of USB HS PHY Tune */
#endif /* USB_HS_PHYC_TUNE_VALUE */


#define USB_OTG_HS_MAX_PACKET_SIZE           512U
#define USB_OTG_FS_MAX_PACKET_SIZE           64U
#define USB_OTG_MAX_EP0_SIZE                 64U

#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     (0 << 1)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     (1 << 1)
#define DSTS_ENUMSPD_LS_PHY_6MHZ               (2 << 1)
#define DSTS_ENUMSPD_FS_PHY_48MHZ              (3 << 1)

#define DCFG_FRAME_INTERVAL_80                 0U
#define DCFG_FRAME_INTERVAL_85                 1U
#define DCFG_FRAME_INTERVAL_90                 2U
#define DCFG_FRAME_INTERVAL_95                 3U

#define DEP0CTL_MPS_64                         0U
#define DEP0CTL_MPS_32                         1U
#define DEP0CTL_MPS_16                         2U
#define DEP0CTL_MPS_8                          3U

#define EP_SPEED_LOW                           0U
#define EP_SPEED_FULL                          1U
#define EP_SPEED_HIGH                          2U

#define EP_TYPE_CTRL                           0U
#define EP_TYPE_ISOC                           1U
#define EP_TYPE_BULK                           2U
#define EP_TYPE_INTR                           3U
#define EP_TYPE_MSK                            3U

#define STS_GOUT_NAK                           1U
#define STS_DATA_UPDT                          2U
#define STS_XFER_COMP                          3U
#define STS_SETUP_COMP                         4U
#define STS_SETUP_UPDT                         6U

#define HCFG_30_60_MHZ                         0U
#define HCFG_48_MHZ                            1U
#define HCFG_6_MHZ                             2U

#define HPRT0_PRTSPD_HIGH_SPEED                0U
#define HPRT0_PRTSPD_FULL_SPEED                1U
#define HPRT0_PRTSPD_LOW_SPEED                 2U

   
#define HCCHAR_CTRL                            0U
#define HCCHAR_ISOC                            1U
#define HCCHAR_BULK                            2U
#define HCCHAR_INTR                            3U
       
#define HC_PID_DATA0                           0U
#define HC_PID_DATA2                           1U
#define HC_PID_DATA1                           2U
#define HC_PID_SETUP                           3U

#define GRXSTS_PKTSTS_IN                       2U
#define GRXSTS_PKTSTS_IN_XFER_COMP             3U
#define GRXSTS_PKTSTS_DATA_TOGGLE_ERR          5U
#define GRXSTS_PKTSTS_CH_HALTED                7U
    
#define USBx_PCGCCTL    *(__IO uint32_t *)((uint32_t)USBx + USB_OTG_PCGCCTL_BASE)
#define USBx_HPRT0      *(__IO uint32_t *)((uint32_t)USBx + USB_OTG_HOST_PORT_BASE)

#define USBx_DEVICE     ((USB_OTG_DeviceTypeDef *)((uint32_t )USBx + USB_OTG_DEVICE_BASE)) 
#define USBx_INEP(i)    ((USB_OTG_INEndpointTypeDef *)((uint32_t)USBx + USB_OTG_IN_ENDPOINT_BASE + (i)*USB_OTG_EP_REG_SIZE))        
#define USBx_OUTEP(i)   ((USB_OTG_OUTEndpointTypeDef *)((uint32_t)USBx + USB_OTG_OUT_ENDPOINT_BASE + (i)*USB_OTG_EP_REG_SIZE))        
#define USBx_DFIFO(i)   *(__IO uint32_t *)((uint32_t)USBx + USB_OTG_FIFO_BASE + (i) * USB_OTG_FIFO_SIZE)

#define USBx_HOST       ((USB_OTG_HostTypeDef *)((uint32_t )USBx + USB_OTG_HOST_BASE))  
#define USBx_HC(i)      ((USB_OTG_HostChannelTypeDef *)((uint32_t)USBx + USB_OTG_HOST_CHANNEL_BASE + (i)*USB_OTG_HOST_CHANNEL_SIZE))
#define USBPHYC         ((USBPHYC_GlobalTypeDef *)((uint32_t )USB_PHY_HS_CONTROLLER_BASE))    
    
    
/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
#define USB_MASK_INTERRUPT(__INSTANCE__, __INTERRUPT__)     ((__INSTANCE__)->GINTMSK &= ~(__INTERRUPT__))
#define USB_UNMASK_INTERRUPT(__INSTANCE__, __INTERRUPT__)   ((__INSTANCE__)->GINTMSK |= (__INTERRUPT__))
    
#define CLEAR_IN_EP_INTR(__EPNUM__, __INTERRUPT__)          (USBx_INEP(__EPNUM__)->DIEPINT = (__INTERRUPT__))
#define CLEAR_OUT_EP_INTR(__EPNUM__, __INTERRUPT__)         (USBx_OUTEP(__EPNUM__)->DOEPINT = (__INTERRUPT__))  

/* Exported functions --------------------------------------------------------*/
status_t USB_CoreInit(usb_otg_global_t *USBx, usb_otg_config_t Init);
status_t USB_DevInit(usb_otg_global_t *USBx, usb_otg_config_t Init);
status_t USB_EnableGlobalInt(usb_otg_global_t *USBx);
status_t USB_DisableGlobalInt(usb_otg_global_t *USBx);
status_t USB_SetCurrentMode(usb_otg_global_t *USBx , usb_otg_mode_t mode);
status_t USB_SetDevSpeed(usb_otg_global_t *USBx , uint8_t speed);
status_t USB_FlushRxFifo (usb_otg_global_t *USBx);
status_t USB_FlushTxFifo (usb_otg_global_t *USBx, uint32_t num );
status_t USB_ActivateEndpoint(usb_otg_global_t *USBx, usb_otg_ep_t *ep);
status_t USB_DeactivateEndpoint(usb_otg_global_t *USBx, usb_otg_ep_t *ep);
status_t USB_ActivateDedicatedEndpoint(usb_otg_global_t *USBx, usb_otg_ep_t *ep);
status_t USB_DeactivateDedicatedEndpoint(usb_otg_global_t *USBx, usb_otg_ep_t *ep);
status_t USB_EPStartXfer(usb_otg_global_t *USBx , usb_otg_ep_t *ep, uint8_t dma);
status_t USB_EP0StartXfer(usb_otg_global_t *USBx , usb_otg_ep_t *ep, uint8_t dma);
status_t USB_WritePacket(usb_otg_global_t *USBx, uint8_t *src, uint8_t ch_ep_num, uint16_t len, uint8_t dma);
void *            USB_ReadPacket(usb_otg_global_t *USBx, uint8_t *dest, uint16_t len);
status_t USB_EPSetStall(usb_otg_global_t *USBx , usb_otg_ep_t *ep);
status_t USB_EPClearStall(usb_otg_global_t *USBx , usb_otg_ep_t *ep);
status_t USB_SetDevAddress (usb_otg_global_t *USBx, uint8_t address);
status_t USB_DevConnect (usb_otg_global_t *USBx);
status_t USB_DevDisconnect (usb_otg_global_t *USBx);
status_t USB_StopDevice(usb_otg_global_t *USBx);
status_t USB_ActivateSetup (usb_otg_global_t *USBx);
status_t USB_EP0_OutStart(usb_otg_global_t *USBx, uint8_t dma, uint8_t *psetup);
uint8_t           USB_GetDevSpeed(usb_otg_global_t *USBx);
uint32_t          USB_GetMode(usb_otg_global_t *USBx);
uint32_t          USB_ReadInterrupts (usb_otg_global_t *USBx);
uint32_t          USB_ReadDevAllOutEpInterrupt (usb_otg_global_t *USBx);
uint32_t          USB_ReadDevOutEPInterrupt (usb_otg_global_t *USBx , uint8_t epnum);
uint32_t          USB_ReadDevAllInEpInterrupt (usb_otg_global_t *USBx);
uint32_t          USB_ReadDevInEPInterrupt (usb_otg_global_t *USBx , uint8_t epnum);
void              USB_ClearInterrupts (usb_otg_global_t *USBx, uint32_t interrupt);

status_t USB_HostInit (usb_otg_global_t *USBx, usb_otg_config_t cfg);
status_t USB_InitFSLSPClkSel(usb_otg_global_t *USBx , uint8_t freq);
status_t USB_ResetPort(usb_otg_global_t *USBx);
status_t USB_DriveVbus (usb_otg_global_t *USBx, uint8_t state);
uint32_t          USB_GetHostSpeed (usb_otg_global_t *USBx);
uint32_t          USB_GetCurrentFrame (usb_otg_global_t *USBx);
status_t USB_HC_Init(usb_otg_global_t *USBx,
                                  uint8_t ch_num,
                                  uint8_t epnum,
                                  uint8_t dev_address,
                                  uint8_t speed,
                                  uint8_t ep_type,
                                  uint16_t mps);
status_t USB_HC_StartXfer(usb_otg_global_t *USBx, usb_otg_hc_t *hc, uint8_t dma);
uint32_t          USB_HC_ReadInterrupt (usb_otg_global_t *USBx);
status_t USB_HC_Halt(usb_otg_global_t *USBx , uint8_t hc_num);
status_t USB_DoPing(usb_otg_global_t *USBx , uint8_t ch_num);
status_t USB_StopHost(usb_otg_global_t *USBx);

  
#ifdef __cplusplus
}
#endif


#endif /* __USBOTG_H__ */

