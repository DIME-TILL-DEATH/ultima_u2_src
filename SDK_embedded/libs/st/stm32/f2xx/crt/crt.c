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

void __attribute__((weak)) TAMPER_IRQHandler(void);
#pragma weak TAMPER_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) RTC_IRQHandler(void);
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

void __attribute__((weak)) ADC_IRQHandler(void);     /*!< ADC1 ADC2 and ADC3 global Interrupt                       */
#pragma weak ADC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_TX_IRQHandler(void);     /*!< USB Device High Priority or CAN1 TX Interrupts       */
#pragma weak CAN1_TX_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_RX0_IRQHandler(void);     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
#pragma weak CAN1_RX0_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_RX1_IRQHandler(void);     /*!< CAN1 RX1 Interrupt                                   */
#pragma weak CAN1_RX1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_SCE_IRQHandler(void);     /*!< CAN1 SCE Interrupt                                   */
#pragma weak CAN1_SCE_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) EXTI9_5_IRQHandler(void);    /*!< External Line[9:5] Interrupts                        */
#pragma weak EXTI9_5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_BRK_TIM9_IRQHandler(void);     /*!< TIM1 Break and TIM9                                  */
#pragma weak TIM1_BRK_TIM9_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_UP_TIM10_IRQHandler(void);     /* TIM1 Update and TIM10        */
#pragma weak TIM1_UP_TIM10_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_TRG_COM_TIM11_IRQHandler(void);     /* TIM1 Trigger and Commutation and TIM11 */
#pragma weak TIM1_TRG_COM_TIM11_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_CC_IRQHandler(void);     /*!< TIM1 Capture Compare Interrupt                       */
#pragma weak TIM1_CC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM2_IRQHandler(void);     /*!< TIM2 global Interrupt                                */
#pragma weak TIM2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM3_IRQHandler(void);     /*!< TIM3 global Interrupt                                */
#pragma weak TIM3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM4_IRQHandler(void);     /*!< TIM4 global Interrupt                                */
#pragma weak TIM4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C1_EV_IRQHandler(void);    /*!< I2C1 Event Interrupt                                 */
#pragma weak I2C1_EV_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C1_ER_IRQHandler(void);    /*!< I2C1 Error Interrupt                                 */
#pragma weak I2C1_ER_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C2_EV_IRQHandler(void);     /*!< I2C2 Event Interrupt                                 */
#pragma weak I2C2_EV_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C2_ER_IRQHandler(void);     /*!< I2C2 Error Interrupt                                 */
#pragma weak I2C2_ER_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI1_IRQHandler(void);   /*!< SPI1 global Interrupt                                */
#pragma weak SPI1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI2_IRQHandler(void);    /*!< SPI2 global Interrupt                                */
#pragma weak SPI2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USART1_IRQHandler(void);     /*!< USART1 global Interrupt                              */
#pragma weak USART1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USART2_IRQHandler(void);   /*!< USART2 global Interrupt                              */
#pragma weak USART2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USART3_IRQHandler(void);     /*!< USART3 global Interrupt                              */
#pragma weak USART3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) EXTI15_10_IRQHandler(void);     /*!< External Line[15:10] Interrupts                      */
#pragma weak EXTI15_10_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) RTCAlarm_IRQHandler(void);    /*!< RTC Alarm through EXTI Line Interrupt                */
#pragma weak RTCAlarm_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_FS_WKUP_IRQHandler(void);     /*!< USB OTG FS WakeUp from suspend through EXTI Line Interrupt */
#pragma weak OTG_FS_WKUP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_BRK_TIM12_IRQHandler(void);         /* TIM8 Break and TIM12         */
#pragma weak TIM8_BRK_TIM12_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_UP_TIM13_IRQHandler(void);          /* TIM8 Update and TIM13        */
#pragma weak TIM8_UP_TIM13_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_TRG_COM_TIM14_IRQHandler(void);     /* TIM8 Trigger and Commutation and TIM14 */
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_CC_IRQHandler(void);                /* TIM8 Capture Compare         */
#pragma weak TIM8_CC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Stream7_IRQHandler(void);           /* DMA1 Stream7                 */
#pragma weak DMA1_Stream7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) FSMC_IRQHandler(void);                   /* FSMC                         */
#pragma weak FSMC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SDIO_IRQHandler(void);                   /* SDIO                         */
#pragma weak SDIO_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM5_IRQHandler(void);     /*!< TIM5 global Interrupt                                */
#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI3_IRQHandler(void);     /*!< SPI3 global Interrupt                                */
#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART4_IRQHandler(void);     /*!< UART4 global Interrupt                               */
#pragma weak UART4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART5_IRQHandler(void);     /*!< UART5 global Interrupt                               */
#pragma weak UART5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) IM6_DAC_IRQHandler(void);               /* TIM6 and DAC1&2 underrun errors */
#pragma weak IM6_DAC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM7_IRQHandler(void);     /*!< TIM7 global Interrupt                                */
#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream0_IRQHandler(void);           /* DMA2 Stream 0                */
#pragma weak DMA2_Stream0_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream1_IRQHandler(void);     /*!< DMA2 Channel 1 global Interrupt                      */
#pragma weak DMA2_Stream1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream2_IRQHandler(void);     /*!< DMA2 Channel 2 global Interrupt                      */
#pragma weak DMA2_Stream2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream3_IRQHandler(void);     /*!< DMA2 Channel 3 global Interrupt                      */
#pragma weak DMA2_Stream3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream4_IRQHandler(void);     /*!< DMA2 Channel 4 global Interrupt                      */
#pragma weak DMA2_Stream4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) ETH_IRQHandler(void);     /*!< Ethernet global Interrupt                            */
#pragma weak ETH_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) ETH_WKUP_IRQHandler(void);     /*!< Ethernet Wakeup through EXTI line Interrupt          */
#pragma weak ETH_WKUP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN2_TX_IRQHandler(void);     /*!< CAN2 TX Interrupt                                    */
#pragma weak CAN2_TX_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN2_RX0_IRQHandler(void);     /*!< CAN2 RX0 Interrupt                                   */
#pragma weak CAN2_RX0_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN2_RX1_IRQHandler(void);     /*!< CAN2 RX1 Interrupt                                   */
#pragma weak CAN2_RX1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN2_SCE_IRQHandler(void);     /*!< CAN2 SCE Interrupt                                   */
#pragma weak CAN2_SCE_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_FS_IRQHandler(void);
#pragma weak OTG_FS_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream5_IRQHandler(void);           /* DMA2 Stream 5                */
#pragma weak DMA2_Stream5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream6_IRQHandler(void);           /* DMA2 Stream 6                */
#pragma weak DMA2_Stream6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Stream7_IRQHandler(void);           /* DMA2 Stream 7                */
#pragma weak DMA2_Stream7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USART6_IRQHandler(void);                 /* USART6                       */
#pragma weak USART6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C3_EV_IRQHandler(void);                /* I2C3 event                   */
#pragma weak I2C3_EV_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) I2C3_ER_IRQHandler(void);               /* I2C3 error                   */
#pragma weak I2C3_ER_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_HS_EP1_OUT_IRQHandler(void);         /* USB OTG HS End Point 1 Out   */
#pragma weak  OTG_HS_EP1_OUT_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_HS_EP1_IN_IRQHandler(void);          /* USB OTG HS End Point 1 In    */
#pragma weak OTG_HS_EP1_IN_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_HS_WKUP_IRQHandler(void);            /* USB OTG HS Wakeup through EXTI */
#pragma weak OTG_HS_WKUP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_HS_IRQHandler(void);                 /* USB OTG HS                   */
#pragma weak OTG_HS_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DCMI_IRQHandler(void);                   /* DCMI                         */
#pragma weak DCMI_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CRYP_IRQHandler(void);                   /* CRYP crypto                  */
#pragma weak CRYP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) HASH_RNG_IRQHandler(void);               /* Hash and Rng                 */
#pragma weak HASH_RNG_IRQHandler = DefaultExceptionHandler

#ifdef __cplusplus
 }
#endif


/* init value for the stack pointer. defined in linker script */
extern unsigned long _stack_end_;

__attribute__ (( section(".flash_vec_table")))
IrqHandlerFunc flash_vec_table[] =
{
  (IrqHandlerFunc)&_stack_end_,            /* The initial stack pointer*/
  ResetHandler,             /* The reset handler*/
  NMIException,
  HardFaultException,
  MemManageException,
  BusFaultException,
  UsageFaultException,
  0, 0, 0, 0,            /* Reserved */
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
  WWDG_IRQHandler,
  PVD_IRQHandler,
  TAMPER_IRQHandler,
  RTC_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMA1_Stream0_IRQHandler,
  DMA1_Stream1_IRQHandler,
  DMA1_Stream2_IRQHandler,
  DMA1_Stream3_IRQHandler,
  DMA1_Stream4_IRQHandler,
  DMA1_Stream5_IRQHandler,
  DMA1_Stream6_IRQHandler,
  ADC_IRQHandler,     /*!< ADC1 ADC2 and ADC3 global Interrupt                       */
  CAN1_TX_IRQHandler,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  CAN1_RX0_IRQHandler,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQHandler,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQHandler,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQHandler,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_TIM9_IRQHandler,     /*!< TIM1 Break and TIM9                                  */
  TIM1_UP_TIM10_IRQHandler,     /* TIM1 Update and TIM10        */
  TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
  TIM1_CC_IRQHandler,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQHandler,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQHandler,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQHandler,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQHandler,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQHandler,    /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQHandler,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQHandler,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQHandler,   /*!< SPI1 global Interrupt                                */
  SPI2_IRQHandler,    /*!< SPI2 global Interrupt                                */
  USART1_IRQHandler,     /*!< USART1 global Interrupt                              */
  USART2_IRQHandler,   /*!< USART2 global Interrupt                              */
  USART3_IRQHandler,     /*!< USART3 global Interrupt                              */
  EXTI15_10_IRQHandler,     /*!< External Line[15:10] Interrupts                      */
  RTCAlarm_IRQHandler,    /*!< RTC Alarm through EXTI Line Interrupt                */
  OTG_FS_WKUP_IRQHandler,     /*!< USB OTG FS WakeUp from suspend through EXTI Line Interrupt */
  TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */
  TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */
  TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
  TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */
  DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */
  FSMC_IRQHandler,                   /* FSMC                         */
  SDIO_IRQHandler,                   /* SDIO                         */
  TIM5_IRQHandler,     /*!< TIM5 global Interrupt                                */
  SPI3_IRQHandler,     /*!< SPI3 global Interrupt                                */
  UART4_IRQHandler,     /*!< UART4 global Interrupt                               */
  UART5_IRQHandler,     /*!< UART5 global Interrupt                               */
  IM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */
  TIM7_IRQHandler,     /*!< TIM7 global Interrupt                                */
  DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */
  DMA2_Stream1_IRQHandler,     /*!< DMA2 Channel 1 global Interrupt                      */
  DMA2_Stream2_IRQHandler,     /*!< DMA2 Channel 2 global Interrupt                      */
  DMA2_Stream3_IRQHandler,     /*!< DMA2 Channel 3 global Interrupt                      */
  DMA2_Stream4_IRQHandler,     /*!< DMA2 Channel 4 global Interrupt                      */
  ETH_IRQHandler,     /*!< Ethernet global Interrupt                            */
  ETH_WKUP_IRQHandler,     /*!< Ethernet Wakeup through EXTI line Interrupt          */
  CAN2_TX_IRQHandler,     /*!< CAN2 TX Interrupt                                    */
  CAN2_RX0_IRQHandler,     /*!< CAN2 RX0 Interrupt                                   */
  CAN2_RX1_IRQHandler,     /*!< CAN2 RX1 Interrupt                                   */
  CAN2_SCE_IRQHandler,     /*!< CAN2 SCE Interrupt                                   */
  OTG_FS_IRQHandler,
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
  CRYP_IRQHandler,                   /* CRYP crypto                  */
  HASH_RNG_IRQHandler               /* Hash and Rng                 */
};


#include "crt_common.c"






