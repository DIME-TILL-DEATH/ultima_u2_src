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
		vtReserved0,
		vtReserved1,
		vtReserved2,
		vtReserved3,            /* Reserved */
	#if defined __USE_FREERTOS__
		vtvPortSVCHandler,
	#else
		vtSVCHandler,
	#endif
		vtDebugMonitor,
		vtReserved4,                      /* Reserved */
	#if defined __USE_FREERTOS__
		vtxPortPendSVHandler,
		vtxPortSysTickHandler,
	#else
		vtPendSVC,
		vtSysTickHandler,
	#endif
		  /* External Interrupts */
		vtWWDG_IRQHandler,                   /* Window WatchDog              */
		vtPVD_IRQHandler,                    /* PVD through EXTI Line detection */
		vtTAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
		vtRTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */
		vtFLASH_IRQHandler,                  /* FLASH                        */
		vtRCC_IRQHandler,                    /* RCC                          */
		vtEXTI0_IRQHandler,                  /* EXTI Line0                   */
		vtEXTI1_IRQHandler,                  /* EXTI Line1                   */
		vtEXTI2_IRQHandler,                  /* EXTI Line2                   */
		vtEXTI3_IRQHandler,                  /* EXTI Line3                   */
		vtEXTI4_IRQHandler,                  /* EXTI Line4                   */
		vtDMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */
		vtDMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */
		vtDMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */
		vtDMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */
		vtDMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */
		vtDMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */
		vtDMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */
		vtADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */
		vtCAN1_TX_IRQHandler,                /* CAN1 TX                      */
		vtCAN1_RX0_IRQHandler,               /* CAN1 RX0                     */
		vtCAN1_RX1_IRQHandler,               /* CAN1 RX1                     */
		vtCAN1_SCE_IRQHandler,               /* CAN1 SCE                     */
		vtEXTI9_5_IRQHandler,                /* External Line[9:5]s          */
		vtTIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9          */
		vtTIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10        */
		vtTIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
		vtTIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
		vtTIM2_IRQHandler,                   /* TIM2                         */
		vtTIM3_IRQHandler,                   /* TIM3                         */
		vtTIM4_IRQHandler,                   /* TIM4                         */
		vtI2C1_EV_IRQHandler,                /* I2C1 Event                   */
		vtI2C1_ER_IRQHandler,                /* I2C1 Error                   */
		vtI2C2_EV_IRQHandler,                /* I2C2 Event                   */
		vtI2C2_ER_IRQHandler,                /* I2C2 Error                   */
		vtSPI1_IRQHandler,                   /* SPI1                         */
		vtSPI2_IRQHandler,                   /* SPI2                         */
		vtUSART1_IRQHandler,                 /* USART1                       */
		vtUSART2_IRQHandler,                 /* USART2                       */
		vtUSART3_IRQHandler,                 /* USART3                       */
		vtEXTI15_10_IRQHandler,              /* External Line[15:10]s        */
		vtRTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */
		vtOTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line */
		vtTIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
		vtTIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
		vtTIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
		vtTIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
		vtDMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
		vtFMC_IRQHandler,                    /* FMC                          */
		vtSDMMC1_IRQHandler,                 /* SDMMC1                       */
		vtTIM5_IRQHandler,                   /* TIM5                         */
		vtSPI3_IRQHandler,                   /* SPI3                         */
		vtUART4_IRQHandler,                  /* UART4                        */
		vtUART5_IRQHandler,                  /* UART5                        */
		vtTIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
		vtTIM7_IRQHandler,                   /* TIM7                         */
		vtDMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
		vtDMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */
		vtDMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */
		vtDMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */
		vtDMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */
		vtETH_IRQHandler,                    /* Ethernet                     */
		vtETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */
		vtCAN2_TX_IRQHandler,                /* CAN2 TX                      */
		vtCAN2_RX0_IRQHandler,               /* CAN2 RX0                     */
		vtCAN2_RX1_IRQHandler,               /* CAN2 RX1                     */
		vtCAN2_SCE_IRQHandler,               /* CAN2 SCE                     */
		vtOTG_FS_IRQHandler,                 /* USB OTG FS                   */
		vtDMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */
		vtDMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */
		vtDMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */
		vtUSART6_IRQHandler,                 /* USART6                       */
		vtI2C3_EV_IRQHandler,                /* I2C3 event                   */
		vtI2C3_ER_IRQHandler,                /* I2C3 error                   */
		vtOTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */
		vtOTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */
		vtOTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */
		vtOTG_HS_IRQHandler,                 /* USB OTG HS                   */
		vtDCMI_IRQHandler,                   /* DCMI                         */
		vtReserved5,                                 /* Reserved                     */
		vtRNG_IRQHandler,                    /* RNG                          */
		vtFPU_IRQHandler,                    /* FPU                          */
		vtUART7_IRQHandler,                  /* UART7                        */
		vtUART8_IRQHandler,                  /* UART8                        */
		vtSPI4_IRQHandler,                   /* SPI4                         */
		vtSPI5_IRQHandler,                   /* SPI5                         */
		vtSPI6_IRQHandler,                   /* SPI6                         */
		vtSAI1_IRQHandler,                   /* SAI1                         */
		vtLTDC_IRQHandler,                   /* LTDC                         */
		vtLTDC_ER_IRQHandler,                /* LTDC error                   */
		vtDMA2D_IRQHandler,                  /* DMA2D                        */
		vtSAI2_IRQHandler,                   /* SAI2                         */
		vtQUADSPI_IRQHandler,                /* QUADSPI                      */
		vtLPTIM1_IRQHandler,                 /* LPTIM1                       */
		vtCEC_IRQHandler,                    /* HDMI_CEC                     */
		vtI2C4_EV_IRQHandler,                /* I2C4 Event                   */
		vtI2C4_ER_IRQHandler,                /* I2C4 Error                   */
		vtSPDIF_RX_IRQHandler,               /* SPDIF_RX                     */
		vtReserved6,                                 /* Reserved                     */
		vtDFSDM1_FLT0_IRQHandler,            /* DFSDM1 Filter 0 global Interrupt */
		vtDFSDM1_FLT1_IRQHandler,            /* DFSDM1 Filter 1 global Interrupt */
		vtDFSDM1_FLT2_IRQHandler,            /* DFSDM1 Filter 2 global Interrupt */
		vtDFSDM1_FLT3_IRQHandler,            /* DFSDM1 Filter 3 global Interrupt */
		vtSDMMC2_IRQHandler,                 /* SDMMC2                       */
		vtCAN3_TX_IRQHandler,                /* CAN3 TX                      */
		vtCAN3_RX0_IRQHandler,               /* CAN3 RX0                     */
		vtCAN3_RX1_IRQHandler,               /* CAN3 RX1                     */
		vtCAN3_SCE_IRQHandler,               /* CAN3 SCE                     */
		vtJPEG_IRQHandler,                   /* JPEG                         */
		vtMDIOS_IRQHandler,                  /* MDIOS                        */


		vtVecCount
} VectorType ;

#include <stdint.h>
#include "system_stm32f7xx.h" // defines of SystemInit

#include "crt_common.h"


#ifdef  __cplusplus
 }
#endif

#endif /*__CRT_H__*/
