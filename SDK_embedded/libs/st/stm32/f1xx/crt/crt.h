#ifndef __CRT_H__
#define __CRT_H__

#ifdef  __cplusplus
 extern "C" {
#endif

typedef void( *IrqHandlerFunc )( void );

typedef enum
{
		vtThreadMode=0,         /* Thread CPU mode, and the initial stack pointer offset in vec table*/
		vtResetHandler,             /* The reset handler*/
		vtNMIException,
		vtHardFaultException,
		vtMemManageException,
		vtBusFaultException,
		vtUsageFaultException,
		vtReserved0, vtReserved2, vtReserved3, vtReserved4,            /* Reserved */
	#if defined __USE_FREERTOS__
		vtvPortSVCHandler,
	#else
		vtSVCHandler,
	#endif
		vtDebugMonitor,
		vtReserved5,                      /* Reserved */
	#if defined __USE_FREERTOS__
		vtxPortPendSVHandler,
		vtxPortSysTickHandler,
	#else
		vtPendSVC,
		vtSysTickHandler,
	#endif
		vtWWDG_IRQHandler,
		vtPVD_IRQHandler,
		vtTAMPER_IRQHandler,
		vtRTC_IRQHandler,
		vtFLASH_IRQHandler,
		vtRCC_IRQHandler,
		vtEXTI0_IRQHandler,
		vtEXTI1_IRQHandler,
		vtEXTI2_IRQHandler,
		vtEXTI3_IRQHandler,
		vtEXTI4_IRQHandler,
		vtDMA1_Channel1_IRQHandler,
		vtDMA1_Channel2_IRQHandler,
		vtDMA1_Channel3_IRQHandler,
		vtDMA1_Channel4_IRQHandler,
		vtDMA1_Channel5_IRQHandler,
		vtDMA1_Channel6_IRQHandler,
		vtDMA1_Channel7_IRQHandler,
	#ifdef STM32F10X_MD
		vtADC1_2_IRQHandler,
		vtUSB_HP_CAN1_TX_IRQHandler,
		vtUSB_LP_CAN1_RX0_IRQHandler,
		vtCAN_RX1_IRQHandler,
		vtCAN_SCE_IRQHandler,
		vtEXTI9_5_IRQHandler,
		vtTIM1_BRK_IRQHandler,
		vtTIM1_UP_IRQHandler,
		vtTIM1_TRG_COM_IRQHandler,
		vtTIM1_CC_IRQHandler,
		vtTIM2_IRQHandler,
		vtTIM3_IRQHandler,
		vtTIM4_IRQHandler,
		vtI2C1_EV_IRQHandler,
		vtI2C1_ER_IRQHandler,
		vtI2C2_EV_IRQHandler,
		vtI2C2_ER_IRQHandler,
		vtSPI1_IRQHandler,
		vtSPI2_IRQHandler,
		vtUSART1_IRQHandler,
		vtUSART2_IRQHandler,
		vtUSART3_IRQHandler,
		vtEXTI15_10_IRQHandler,
		vtRTCAlarm_IRQHandler,
		vtUSBWakeUp_IRQHandler,
		vtTIM8_BRK_IRQHandler,
		vtTIM8_UP_IRQHandler,
		vtTIM8_TRG_COM_IRQHandler,
		vtTIM8_CC_IRQHandler,
		vtADC3_IRQHandler,
		vtFSMC_IRQHandler,
		vtSDIO_IRQHandler,
		vtTIM5_IRQHandler,
		vtSPI3_IRQHandler,
		vtUART4_IRQHandler,
		vtUART5_IRQHandler,
		vtTIM6_IRQHandler,
		vtTIM7_IRQHandler,
		vtDMA2_Channel1_IRQHandler,
		vtDMA2_Channel2_IRQHandler,
		vtDMA2_Channel3_IRQHandler,
		vtDMA2_Channel4_5_IRQHandler,
	#elif defined STM32F10X_HD
		vtADC1_2_IRQHandler,     /*!< ADC1 and ADC2 global Interrupt                       */
		vtUSB_HP_CAN1_TX_IRQHandler,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
		vtUSB_LP_CAN1_RX0_IRQHandler,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
		vtCAN1_RX1_IRQHandler,     /*!< CAN1 RX1 Interrupt                                   */
		vtCAN1_SCE_IRQHandler,     /*!< CAN1 SCE Interrupt                                   */
		vtEXTI9_5_IRQHandler,     /*!< External Line[9:5] Interrupts                        */
		vtTIM1_BRK_IRQHandler,     /*!< TIM1 Break Interrupt                                 */
		vtTIM1_UP_IRQHandler,     /*!< TIM1 Update Interrupt                                */
		vtTIM1_TRG_COM_IRQHandler,     /*!< TIM1 Trigger and Commutation Interrupt               */
		vtTIM1_CC_IRQHandler,     /*!< TIM1 Capture Compare Interrupt                       */
		vtTIM2_IRQHandler,     /*!< TIM2 global Interrupt                                */
		vtTIM3_IRQHandler,     /*!< TIM3 global Interrupt                                */
		vtTIM4_IRQHandler,     /*!< TIM4 global Interrupt                                */
		vtI2C1_EV_IRQHandler,     /*!< I2C1 Event Interrupt                                 */
		vtI2C1_ER_IRQHandler,     /*!< I2C1 Error Interrupt                                 */
		vtI2C2_EV_IRQHandler,     /*!< I2C2 Event Interrupt                                 */
		vtI2C2_ER_IRQHandler,     /*!< I2C2 Error Interrupt                                 */
		vtSPI1_IRQHandler,     /*!< SPI1 global Interrupt                                */
		vtSPI2_IRQHandler,     /*!< SPI2 global Interrupt                                */
		vtUSART1_IRQHandler,     /*!< USART1 global Interrupt                              */
		vtUSART2_IRQHandler,     /*!< USART2 global Interrupt                              */
		vtUSART3_IRQHandler,     /*!< USART3 global Interrupt                              */
		vtEXTI15_10_IRQHandler,     /*!< External Line[15:10] Interrupts                      */
		vtRTCAlarm_IRQHandler,     /*!< RTC Alarm through EXTI Line Interrupt                */
		vtUSBWakeUp_IRQHandler,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
		vtTIM8_BRK_IRQHandler,     /*!< TIM8 Break Interrupt                                 */
		vtTIM8_UP_IRQHandler,     /*!< TIM8 Update Interrupt                                */
		vtTIM8_TRG_COM_IRQHandler,     /*!< TIM8 Trigger and Commutation Interrupt               */
		vtTIM8_CC_IRQHandler,     /*!< TIM8 Capture Compare Interrupt                       */
		vtADC3_IRQHandler,     /*!< ADC3 global Interrupt                                */
		vtFSMC_IRQHandler,     /*!< FSMC global Interrupt                                */
		vtSDIO_IRQHandler,     /*!< SDIO global Interrupt                                */
		vtTIM5_IRQHandler,     /*!< TIM5 global Interrupt                                */
		vtSPI3_IRQHandler,     /*!< SPI3 global Interrupt                                */
		vtUART4_IRQHandler,     /*!< UART4 global Interrupt                               */
		vtUART5_IRQHandler,     /*!< UART5 global Interrupt                               */
		vtTIM6_IRQHandler,     /*!< TIM6 global Interrupt                                */
		vtTIM7_IRQHandler,     /*!< TIM7 global Interrupt                                */
		vtDMA2_Channel1_IRQHandler,     /*!< DMA2 Channel 1 global Interrupt                      */
		vtDMA2_Channel2_IRQHandler,     /*!< DMA2 Channel 2 global Interrupt                      */
		vtDMA2_Channel3_IRQHandler,     /*!< DMA2 Channel 3 global Interrupt                      */
		vtDMA2_Channel4_5_IRQHandler,      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
	#elif defined STM32F10X_CL
		vtADC1_2_IRQHandler,     /*!< ADC1 and ADC2 global Interrupt                       */
		vtCAN1_TX_IRQHandler,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
		vtCAN1_RX0_IRQHandler,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
		vtCAN1_RX1_IRQHandler,     /*!< CAN1 RX1 Interrupt                                   */
		vtCAN1_SCE_IRQHandler,     /*!< CAN1 SCE Interrupt                                   */
		vtEXTI9_5_IRQHandler,     /*!< External Line[9:5] Interrupts                        */
		vtTIM1_BRK_IRQHandler,     /*!< TIM1 Break Interrupt                                 */
		vtTIM1_UP_IRQHandler,     /*!< TIM1 Update Interrupt                                */
		vtTIM1_TRG_COM_IRQHandler,     /*!< TIM1 Trigger and Commutation Interrupt               */
		vtTIM1_CC_IRQHandler,     /*!< TIM1 Capture Compare Interrupt                       */
		vtTIM2_IRQHandler,     /*!< TIM2 global Interrupt                                */
		vtTIM3_IRQHandler,     /*!< TIM3 global Interrupt                                */
		vtTIM4_IRQHandler,     /*!< TIM4 global Interrupt                                */
		vtI2C1_EV_IRQHandler,     /*!< I2C1 Event Interrupt                                 */
		vtI2C1_ER_IRQHandler,    /*!< I2C1 Error Interrupt                                 */
		vtI2C2_EV_IRQHandler,     /*!< I2C2 Event Interrupt                                 */
		vtI2C2_ER_IRQHandler,     /*!< I2C2 Error Interrupt                                 */
		vtSPI1_IRQHandler,   /*!< SPI1 global Interrupt                                */
		vtSPI2_IRQHandler,    /*!< SPI2 global Interrupt                                */
		vtUSART1_IRQHandler,     /*!< USART1 global Interrupt                              */
		vtUSART2_IRQHandler,   /*!< USART2 global Interrupt                              */
		vtUSART3_IRQHandler,     /*!< USART3 global Interrupt                              */
		vtEXTI15_10_IRQHandler,     /*!< External Line[15:10] Interrupts                      */
		vtRTCAlarm_IRQHandler,    /*!< RTC Alarm through EXTI Line Interrupt                */
		vtOTG_FS_WKUP_IRQHandler,     /*!< USB OTG FS WakeUp from suspend through EXTI Line Interrupt */
		vtReserved6,
		vtReserved7,
		vtReserved8,
		vtReserved9,
		vtReserved10,
		vtReserved11,
		vtReserved12,
		vtTIM5_IRQHandler,     /*!< TIM5 global Interrupt                                */
		vtSPI3_IRQHandler,     /*!< SPI3 global Interrupt                                */
		vtUART4_IRQHandler,     /*!< UART4 global Interrupt                               */
		vtUART5_IRQHandler,     /*!< UART5 global Interrupt                               */
		vtTIM6_IRQHandler,   /*!< TIM6 global Interrupt                                */
		vtTIM7_IRQHandler,     /*!< TIM7 global Interrupt                                */
		vtDMA2_Channel1_IRQHandler,     /*!< DMA2 Channel 1 global Interrupt                      */
		vtDMA2_Channel2_IRQHandler,     /*!< DMA2 Channel 2 global Interrupt                      */
		vtDMA2_Channel3_IRQHandler,     /*!< DMA2 Channel 3 global Interrupt                      */
		vtDMA2_Channel4_IRQHandler,     /*!< DMA2 Channel 4 global Interrupt                      */
		vtDMA2_Channel5_IRQHandler,     /*!< DMA2 Channel 5 global Interrupt                      */
		vtETH_IRQHandler,     /*!< Ethernet global Interrupt                            */
		vtETH_WKUP_IRQHandler,     /*!< Ethernet Wakeup through EXTI line Interrupt          */
		vtCAN2_TX_IRQHandler,     /*!< CAN2 TX Interrupt                                    */
		vtCAN2_RX0_IRQHandler,     /*!< CAN2 RX0 Interrupt                                   */
		vtCAN2_RX1_IRQHandler,     /*!< CAN2 RX1 Interrupt                                   */
		vtCAN2_SCE_IRQHandler,     /*!< CAN2 SCE Interrupt                                   */
		vtOTG_FS_IRQHandler,
	#endif
		vtVecCount
} VectorType ;

#include <stdint.h>
#include "system_stm32f10x.h" // defines of SystemInit

#include "crt_common.h"


#ifdef  __cplusplus
 }
#endif

#endif /*__CRT_H__*/
