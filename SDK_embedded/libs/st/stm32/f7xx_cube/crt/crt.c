#include "crt.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

//------------------------------------------------------------------------------------
void __attribute__((weak)) ResetHandler(void);

void __attribute__((weak)) NMIException(void);
#pragma weak NMIException = DefaultExceptionHandler

void __attribute__((weak)) HardFaultException(void);

void __attribute__((weak)) MemManageException(void);
#pragma weak MemManageException = DefaultExceptionHandler

void __attribute__((weak)) BusFaultException(void);
#pragma weak BusFaultException = DefaultExceptionHandler

void __attribute__((weak)) UsageFaultException(void);
#pragma weak UsageFaultException = DefaultExceptionHandler

#if defined __USE_FREERTOS__
	void vPortSVCHandler(void);
#else
	void __attribute__((weak)) SVCHandler(void);
	#pragma weak SVCHandler = DefaultExceptionHandler

#endif
void __attribute__((weak)) DebugMonitor(void);
#pragma weak DebugMonitor = DefaultExceptionHandler

#if defined __USE_FREERTOS__
	void xPortPendSVHandler(void);
	void xPortSysTickHandler(void);
#else
	void __attribute__((weak)) PendSVC(void);
	#pragma weak PendSVC = DefaultExceptionHandler
	void __attribute__((weak)) SysTickHandler(void);
	#pragma weak SysTickHandler = DefaultExceptionHandler
#endif

	void __attribute__((weak)) WWDG_IRQHandler(void);
	#pragma weak WWDG_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) PVD_IRQHandler(void);
	#pragma weak PVD_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TAMP_STAMP_IRQHandler(void);
	#pragma weak TAMPER_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) RTC_WKUP_IRQHandler(void);
	#pragma weak RTC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) FLASH_IRQHandler(void);
	#pragma weak FLASH_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) RCC_IRQHandler(void);
	#pragma weak RCC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI0_IRQHandler(void);
	#pragma weak EXTI0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI1_IRQHandler(void);
	#pragma weak EXTI1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI2_IRQHandler(void);
	#pragma weak EXTI2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI3_IRQHandler(void);
	#pragma weak EXTI3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI4_IRQHandler(void);
	#pragma weak EXTI4_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream0_IRQHandler(void);
	#pragma weak DMA1_Stream0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream1_IRQHandler(void);
	#pragma weak DMA1_Stream1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream2_IRQHandler(void);
	#pragma weak DMA1_Stream2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream3_IRQHandler(void);
	#pragma weak DMA1_Stream3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream4_IRQHandler(void);
	#pragma weak DMA1_Stream4_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream5_IRQHandler(void);
	#pragma weak DMA1_Stream5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream6_IRQHandler(void);
	#pragma weak DMA1_Stream6_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) ADC_IRQHandler(void);
	#pragma weak ADC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN1_TX_IRQHandler(void);
	#pragma weak CAN1_TX_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN1_RX0_IRQHandler(void);
	#pragma weak CAN1_RX0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN1_RX1_IRQHandler(void);
	#pragma weak CAN1_RX1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN1_SCE_IRQHandler(void);
	#pragma weak CAN1_SCE_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI9_5_IRQHandler(void);
	#pragma weak EXTI9_5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_BRK_TIM9_IRQHandler(void);
	#pragma weak TIM1_BRK_TIM9_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_UP_TIM10_IRQHandler(void);
	#pragma weak TIM1_UP_TIM10_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_TRG_COM_TIM11_IRQHandler(void);
	#pragma weak TIM1_TRG_COM_TIM11_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_CC_IRQHandler(void);
	#pragma weak TIM1_CC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM2_IRQHandler(void);
	#pragma weak TIM2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM3_IRQHandler(void);
	#pragma weak TIM3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM4_IRQHandler(void);
	#pragma weak TIM4_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C1_EV_IRQHandler(void);
	#pragma weak I2C1_EV_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C1_ER_IRQHandler(void);
	#pragma weak I2C1_ER_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C2_EV_IRQHandler(void);
	#pragma weak I2C2_EV_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C2_ER_IRQHandler(void);
	#pragma weak I2C2_ER_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI1_IRQHandler(void);
	#pragma weak SPI1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI2_IRQHandler(void);
	#pragma weak SPI2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) USART1_IRQHandler(void);
	#pragma weak USART1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) USART2_IRQHandler(void);
	#pragma weak USART2_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) USART3_IRQHandler(void);
	#pragma weak USART3_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) EXTI15_10_IRQHandler(void);
	#pragma weak EXTI15_10_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) RTC_Alarm_IRQHandler(void);
	#pragma weak RTC_Alarm_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_FS_WKUP_IRQHandler(void);
	#pragma weak OTG_FS_WKUP_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) TIM8_BRK_TIM12_IRQHandler(void);
	#pragma weak TIM8_BRK_TIM12_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM8_UP_TIM13_IRQHandler(void);
	#pragma weak TIM8_UP_TIM13_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM8_TRG_COM_TIM14_IRQHandler(void);
	#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM8_CC_IRQHandler(void);
	#pragma weak TIM8_CC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA1_Stream7_IRQHandler(void);
	#pragma weak DMA1_Stream7_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) FMC_IRQHandler(void);
	#pragma weak FMC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SDMMC1_IRQHandler(void);
	#pragma weak SDMMC1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM5_IRQHandler(void);
	#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI3_IRQHandler(void);
	#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) UART4_IRQHandler(void);
	#pragma weak UART4_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) UART5_IRQHandler(void);
	#pragma weak UART5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM6_DAC_IRQHandler(void);
	#pragma weak TIM6_DAC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM7_IRQHandler(void);
	#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream0_IRQHandler(void);
	#pragma weak DMA2_Stream0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream1_IRQHandler(void);
	#pragma weak DMA2_Stream1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream2_IRQHandler(void);
	#pragma weak DMA2_Stream2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream3_IRQHandler(void);
	#pragma weak DMA2_Stream3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream4_IRQHandler(void);
	#pragma weak DMA2_Stream4_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) ETH_IRQHandler(void);
	#pragma weak ETH_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) ETH_WKUP_IRQHandler(void);
	#pragma weak ETH_WKUP_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN2_TX_IRQHandler(void);
	#pragma weak CAN2_TX_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN2_RX0_IRQHandler(void);
	#pragma weak CAN2_RX0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN2_RX1_IRQHandler(void);
	#pragma weak CAN2_RX1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN2_SCE_IRQHandler(void);
	#pragma weak CAN2_SCE_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_FS_IRQHandler(void);
	#pragma weak OTG_FS_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream5_IRQHandler(void);
	#pragma weak DMA2_Stream5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream6_IRQHandler(void);
	#pragma weak DMA2_Stream6_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA2_Stream7_IRQHandler(void);
	#pragma weak DMA2_Stream7_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) USART6_IRQHandler(void);
	#pragma weak USART6_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C3_EV_IRQHandler(void);
	#pragma weak I2C3_EV_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C3_ER_IRQHandler(void);
	#pragma weak I2C3_ER_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_HS_EP1_OUT_IRQHandler(void);
	#pragma weak OTG_HS_EP1_OUT_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_HS_EP1_IN_IRQHandler(void);
	#pragma weak OTG_HS_EP1_IN_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_HS_WKUP_IRQHandler(void);
	#pragma weak OTG_HS_WKUP_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) OTG_HS_IRQHandler(void);
	#pragma weak OTG_HS_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DCMI_IRQHandler(void);
	#pragma weak DCMI_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CRYP_IRQHandler(void);
	#pragma weak CRYP_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) RNG_IRQHandler(void);
	#pragma weak RNG_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) FPU_IRQHandler(void);
	#pragma weak FPU_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) UART7_IRQHandler(void);
	#pragma weak UART7_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) UART8_IRQHandler(void);
        #pragma weak UART8_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) SPI4_IRQHandler(void);
        #pragma weak SPI4_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) SPI5_IRQHandler(void);
        #pragma weak SPI5_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) SPI6_IRQHandler(void);
        #pragma weak SPI6_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) SAI1_IRQHandler(void);
        #pragma weak SAI1_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) LTDC_IRQHandler(void);
        #pragma weak LTDC_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) LTDC_ER_IRQHandler(void);
        #pragma weak LTDC_ER_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) DMA2D_IRQHandler(void);
        #pragma weak DMA2D_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) SAI2_IRQHandler(void);
        #pragma weak SAI2_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) QUADSPI_IRQHandler(void);
        #pragma weak QUADSPI_IRQHandler = DefaultExceptionHandler

        void __attribute__((weak)) LPTIM1_IRQHandler(void);
        #pragma weak LPTIM1_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) CEC_IRQHandler(void);
        #pragma weak CEC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C4_EV_IRQHandler(void);
        #pragma weak I2C4_EV_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C4_ER_IRQHandler(void);
        #pragma weak I2C4_ER_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPDIF_RX_IRQHandler(void);
        #pragma weak SPDIF_RX_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DFSDM1_FLT0_IRQHandler(void);
        #pragma weak DFSDM1_FLT0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DFSDM1_FLT1_IRQHandler(void);
        #pragma weak DFSDM1_FLT1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DFSDM1_FLT2_IRQHandler(void);
        #pragma weak DFSDM1_FLT2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DFSDM1_FLT3_IRQHandler(void);
        #pragma weak DFSDM1_FLT3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SDMMC2_IRQHandler(void);
        #pragma weak SDMMC2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN3_TX_IRQHandler(void);
        #pragma weak CAN3_TX_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN3_RX0_IRQHandler(void);
        #pragma weak CAN3_RX0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN3_RX1_IRQHandler(void);
        #pragma weak CAN3_RX1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) CAN3_SCE_IRQHandler(void);
        #pragma weak CAN3_SCE_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) JPEG_IRQHandler(void);
        #pragma weak JPEG_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) MDIOS_IRQHandler(void);
        #pragma weak MDIOS_IRQHandler = DefaultExceptionHandler


#ifdef __cplusplus
 }
#endif


/* init value for the stack pointer. defined in linker script */
extern uint32_t __stack_end__;

__attribute__ (( section(".flash_vec_table")))
IrqHandlerFunc vec_table[] =
{
  (IrqHandlerFunc)&__stack_end__,            /* The initial stack pointer*/
  ResetHandler,             /* The reset handler*/
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  0,
  0,
  0,
  0,            /* Reserved */
#if defined __USE_FREERTOS__
  vPortSVCHandler,
#else
  SVCHandler,
#endif
  DebugMonitor,
  0,                      /* Reserved */
#if defined __USE_FREERTOS__
  xPortPendSVHandler,
  xPortSysTickHandler,
#else
  PendSVC,
  SysTickHandler,
#endif
  /* External Interrupts */
  WWDG_IRQHandler,                   /* Window WatchDog              */
  PVD_IRQHandler,                    /* PVD through EXTI Line detection */
  TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
  RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */
  FLASH_IRQHandler,                  /* FLASH                        */
  RCC_IRQHandler,                    /* RCC                          */
  EXTI0_IRQHandler,                  /* EXTI Line0                   */
  EXTI1_IRQHandler,                  /* EXTI Line1                   */
  EXTI2_IRQHandler,                  /* EXTI Line2                   */
  EXTI3_IRQHandler,                  /* EXTI Line3                   */
  EXTI4_IRQHandler,                  /* EXTI Line4                   */
  DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */
  DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */
  DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */
  DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */
  DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */
  DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */
  DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */
  ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */
  CAN1_TX_IRQHandler,                /* CAN1 TX                      */
  CAN1_RX0_IRQHandler,               /* CAN1 RX0                     */
  CAN1_RX1_IRQHandler,               /* CAN1 RX1                     */
  CAN1_SCE_IRQHandler,               /* CAN1 SCE                     */
  EXTI9_5_IRQHandler,                /* External Line[9:5]s          */
  TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9          */
  TIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10        */
  TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
  TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
  TIM2_IRQHandler,                   /* TIM2                         */
  TIM3_IRQHandler,                   /* TIM3                         */
  TIM4_IRQHandler,                   /* TIM4                         */
  I2C1_EV_IRQHandler,                /* I2C1 Event                   */
  I2C1_ER_IRQHandler,                /* I2C1 Error                   */
  I2C2_EV_IRQHandler,                /* I2C2 Event                   */
  I2C2_ER_IRQHandler,                /* I2C2 Error                   */
  SPI1_IRQHandler,                   /* SPI1                         */
  SPI2_IRQHandler,                   /* SPI2                         */
  USART1_IRQHandler,                 /* USART1                       */
  USART2_IRQHandler,                 /* USART2                       */
  USART3_IRQHandler,                 /* USART3                       */
  EXTI15_10_IRQHandler,              /* External Line[15:10]s        */
  RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */
  OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line */
  TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
  TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
  TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
  TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
  DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
  FMC_IRQHandler,                    /* FMC                          */
  SDMMC1_IRQHandler,                 /* SDMMC1                       */
  TIM5_IRQHandler,                   /* TIM5                         */
  SPI3_IRQHandler,                   /* SPI3                         */
  UART4_IRQHandler,                  /* UART4                        */
  UART5_IRQHandler,                  /* UART5                        */
  TIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
  TIM7_IRQHandler,                   /* TIM7                         */
  DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
  DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */
  DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */
  DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */
  DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */
  ETH_IRQHandler,                    /* Ethernet                     */
  ETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */
  CAN2_TX_IRQHandler,                /* CAN2 TX                      */
  CAN2_RX0_IRQHandler,               /* CAN2 RX0                     */
  CAN2_RX1_IRQHandler,               /* CAN2 RX1                     */
  CAN2_SCE_IRQHandler,               /* CAN2 SCE                     */
  OTG_FS_IRQHandler,                 /* USB OTG FS                   */
  DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */
  DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */
  DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */
  USART6_IRQHandler,                 /* USART6                       */
  I2C3_EV_IRQHandler,                /* I2C3 event                   */
  I2C3_ER_IRQHandler,                /* I2C3 error                   */
  OTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */
  OTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */
  OTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */
  OTG_HS_IRQHandler,                 /* USB OTG HS                   */
  DCMI_IRQHandler,                   /* DCMI                         */
  0,                                 /* Reserved                     */
  RNG_IRQHandler,                    /* RNG                          */
  FPU_IRQHandler,                    /* FPU                          */
  UART7_IRQHandler,                  /* UART7                        */
  UART8_IRQHandler,                  /* UART8                        */
  SPI4_IRQHandler,                   /* SPI4                         */
  SPI5_IRQHandler,                   /* SPI5                         */
  SPI6_IRQHandler,                   /* SPI6                         */
  SAI1_IRQHandler,                   /* SAI1                         */
  LTDC_IRQHandler,                   /* LTDC                         */
  LTDC_ER_IRQHandler,                /* LTDC error                   */
  DMA2D_IRQHandler,                  /* DMA2D                        */
  SAI2_IRQHandler,                   /* SAI2                         */
  QUADSPI_IRQHandler,                /* QUADSPI                      */
  LPTIM1_IRQHandler,                 /* LPTIM1                       */
  CEC_IRQHandler,                    /* HDMI_CEC                     */
  I2C4_EV_IRQHandler,                /* I2C4 Event                   */
  I2C4_ER_IRQHandler,                /* I2C4 Error                   */
  SPDIF_RX_IRQHandler,               /* SPDIF_RX                     */
  0,                                 /* Reserved                     */
  DFSDM1_FLT0_IRQHandler,            /* DFSDM1 Filter 0 global Interrupt */
  DFSDM1_FLT1_IRQHandler,            /* DFSDM1 Filter 1 global Interrupt */
  DFSDM1_FLT2_IRQHandler,            /* DFSDM1 Filter 2 global Interrupt */
  DFSDM1_FLT3_IRQHandler,            /* DFSDM1 Filter 3 global Interrupt */
  SDMMC2_IRQHandler,                 /* SDMMC2                       */
  CAN3_TX_IRQHandler,                /* CAN3 TX                      */
  CAN3_RX0_IRQHandler,               /* CAN3 RX0                     */
  CAN3_RX1_IRQHandler,               /* CAN3 RX1                     */
  CAN3_SCE_IRQHandler,               /* CAN3 SCE                     */
  JPEG_IRQHandler,                   /* JPEG                         */
  MDIOS_IRQHandler,                  /* MDIOS                        */

};


#include "crt_common.c"






