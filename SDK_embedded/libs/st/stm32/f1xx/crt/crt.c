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

void __attribute__((weak)) DMA1_Channel1_IRQHandler(void);
#pragma weak DMA1_Channel1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel2_IRQHandler(void);
#pragma weak DMA1_Channel2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel3_IRQHandler(void);
#pragma weak DMA1_Channel3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel4_IRQHandler(void);
#pragma weak DMA1_Channel4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel5_IRQHandler(void);
#pragma weak DMA1_Channel5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel6_IRQHandler(void);
#pragma weak DMA1_Channel6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA1_Channel7_IRQHandler(void);
#pragma weak DMA1_Channel7_IRQHandler = DefaultExceptionHandler

#ifdef STM32F10X_MD

void __attribute__((weak)) ADC1_2_IRQHandler(void);
#pragma weak ADC1_2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_HP_CAN1_TX_IRQHandler(void);
#pragma weak USB_HP_CAN1_TX_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_LP_CAN1_RX0_IRQHandler(void);
#pragma weak USB_LP_CAN1_RX0_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN_RX1_IRQHandler(void);
#pragma weak CAN_RX1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN_SCE_IRQHandler(void);
#pragma weak CAN_SCE_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) EXTI9_5_IRQHandler(void);
#pragma weak EXTI9_5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_BRK_IRQHandler(void);
#pragma weak TIM1_BRK_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_UP_IRQHandler(void);
#pragma weak TIM1_UP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_TRG_COM_IRQHandler(void);
#pragma weak TIM1_TRG_COM_IRQHandler = DefaultExceptionHandler

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

void __attribute__((weak)) RTCAlarm_IRQHandler(void);
#pragma weak RTCAlarm_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USBWakeUp_IRQHandler(void);
#pragma weak USBWakeUp_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_BRK_IRQHandler(void);
#pragma weak TIM8_BRK_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_UP_IRQHandler(void);
#pragma weak TIM8_UP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_TRG_COM_IRQHandler(void);
#pragma weak TIM8_TRG_COM_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_CC_IRQHandler(void);
#pragma weak TIM8_CC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) ADC3_IRQHandler(void);
#pragma weak ADC3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) FSMC_IRQHandler(void);
#pragma weak FSMC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SDIO_IRQHandler(void);
#pragma weak SDIO_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM5_IRQHandler(void);
#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI3_IRQHandler(void);
#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART4_IRQHandler(void);
#pragma weak UART4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART5_IRQHandler(void);
#pragma weak UART5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM6_IRQHandler(void);
#pragma weak TIM6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM7_IRQHandler(void);
#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel1_IRQHandler(void);
#pragma weak DMA2_Channel1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel2_IRQHandler(void);
#pragma weak DMA2_Channel2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel3_IRQHandler(void);
#pragma weak DMA2_Channel3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel4_5_IRQHandler(void);
#pragma weak DMA2_Channel4_5_IRQHandler = DefaultExceptionHandler

#elif defined STM32F10X_HD

void __attribute__((weak)) ADC1_2_IRQHandler(void);
#pragma weak ADC1_2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_HP_CAN1_TX_IRQHandler(void);
#pragma weak USB_HP_CAN1_TX_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_LP_CAN1_RX0_IRQHandler(void);
#pragma weak USB_LP_CAN1_RX0_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_RX1_IRQHandler(void);
#pragma weak CAN1_RX1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) CAN1_SCE_IRQHandler(void);
#pragma weak CAN1_SCE_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) EXTI9_5_IRQHandler(void);
#pragma weak EXTI9_5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_BRK_IRQHandler(void);
#pragma weak TIM1_BRK_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_UP_IRQHandler(void);
#pragma weak TIM1_UP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_TRG_COM_IRQHandler(void);
#pragma weak TIM1_TRG_COM_IRQHandler = DefaultExceptionHandler

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

void __attribute__((weak)) RTCAlarm_IRQHandler(void);
#pragma weak RTCAlarm_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USBWakeUp_IRQHandler(void);
#pragma weak USBWakeUp_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_BRK_IRQHandler(void);
#pragma weak TIM8_BRK_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_UP_IRQHandler(void);
#pragma weak TIM8_UP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_TRG_COM_IRQHandler(void);
#pragma weak TIM8_TRG_COM_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM8_CC_IRQHandler(void);
#pragma weak TIM8_CC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) ADC3_IRQHandler(void);
#pragma weak ADC3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) FSMC_IRQHandler(void);
#pragma weak FSMC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SDIO_IRQHandler(void);
#pragma weak SDIO_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM5_IRQHandler(void);
#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI3_IRQHandler(void);
#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART4_IRQHandler(void);
#pragma weak UART4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART5_IRQHandler(void);
#pragma weak UART5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM6_IRQHandler(void);
#pragma weak TIM6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM7_IRQHandler(void);
#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel1_IRQHandler(void);
#pragma weak DMA2_Channel1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel2_IRQHandler(void);
#pragma weak DMA2_Channel2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel3_IRQHandler(void);
#pragma weak DMA2_Channel3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel4_5_IRQHandler(void);
#pragma weak DMA2_Channel4_5_IRQHandler = DefaultExceptionHandler

#elif defined STM32F10X_CL

void __attribute__((weak)) ADC1_2_IRQHandler(void);
#pragma weak ADC1_2_IRQHandler = DefaultExceptionHandler

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

void __attribute__((weak)) TIM1_BRK_IRQHandler(void);
#pragma weak TIM1_BRK_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_UP_IRQHandler(void);
#pragma weak TIM1_UP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM1_TRG_COM_IRQHandler(void);
#pragma weak TIM1_TRG_COM_IRQHandler = DefaultExceptionHandler

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

void __attribute__((weak)) RTCAlarm_IRQHandler(void);
#pragma weak RTCAlarm_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) OTG_FS_WKUP_IRQHandler(void);
#pragma weak OTG_FS_WKUP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak))  TIM5_IRQHandler(void);
#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) SPI3_IRQHandler(void);
#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART4_IRQHandler(void);
#pragma weak UART4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) UART5_IRQHandler(void);
#pragma weak UART5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM6_IRQHandler(void);
#pragma weak TIM6_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM7_IRQHandler(void);
#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel1_IRQHandler(void);
#pragma weak DMA2_Channel1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel2_IRQHandler(void);
#pragma weak DMA2_Channel2_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel3_IRQHandler(void);
#pragma weak DMA2_Channel3_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel4_IRQHandler(void);
#pragma weak DMA2_Channel4_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DMA2_Channel5_IRQHandler(void);
#pragma weak DMA2_Channel5_IRQHandler = DefaultExceptionHandler

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

#endif

#ifdef __cplusplus
 }
#endif


 /* init value for the stack pointer. defined in linker script */
 extern uint8_t __stack_end__;

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
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_IRQHandler,
  DMA1_Channel3_IRQHandler,
  DMA1_Channel4_IRQHandler,
  DMA1_Channel5_IRQHandler,
  DMA1_Channel6_IRQHandler,
  DMA1_Channel7_IRQHandler,
#ifdef STM32F10X_MD
  ADC1_2_IRQHandler,
  USB_HP_CAN1_TX_IRQHandler,
  USB_LP_CAN1_RX0_IRQHandler,
  CAN_RX1_IRQHandler,
  CAN_SCE_IRQHandler,
  EXTI9_5_IRQHandler,
  TIM1_BRK_IRQHandler,
  TIM1_UP_IRQHandler,
  TIM1_TRG_COM_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTCAlarm_IRQHandler,
  USBWakeUp_IRQHandler,
  TIM8_BRK_IRQHandler,
  TIM8_UP_IRQHandler,
  TIM8_TRG_COM_IRQHandler,
  TIM8_CC_IRQHandler,
  ADC3_IRQHandler,
  FSMC_IRQHandler,
  SDIO_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  TIM6_IRQHandler,
  TIM7_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_5_IRQHandler,
#elif defined STM32F10X_HD
  ADC1_2_IRQHandler,     /*!< ADC1 and ADC2 global Interrupt                       */
  USB_HP_CAN1_TX_IRQHandler,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQHandler,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQHandler,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQHandler,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQHandler,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_IRQHandler,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQHandler,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQHandler,     /*!< TIM1 Trigger and Commutation Interrupt               */
  TIM1_CC_IRQHandler,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQHandler,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQHandler,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQHandler,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQHandler,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQHandler,     /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQHandler,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQHandler,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQHandler,     /*!< SPI1 global Interrupt                                */
  SPI2_IRQHandler,     /*!< SPI2 global Interrupt                                */
  USART1_IRQHandler,     /*!< USART1 global Interrupt                              */
  USART2_IRQHandler,     /*!< USART2 global Interrupt                              */
  USART3_IRQHandler,     /*!< USART3 global Interrupt                              */
  EXTI15_10_IRQHandler,     /*!< External Line[15:10] Interrupts                      */
  RTCAlarm_IRQHandler,     /*!< RTC Alarm through EXTI Line Interrupt                */
  USBWakeUp_IRQHandler,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
  TIM8_BRK_IRQHandler,     /*!< TIM8 Break Interrupt                                 */
  TIM8_UP_IRQHandler,     /*!< TIM8 Update Interrupt                                */
  TIM8_TRG_COM_IRQHandler,     /*!< TIM8 Trigger and Commutation Interrupt               */
  TIM8_CC_IRQHandler,     /*!< TIM8 Capture Compare Interrupt                       */
  ADC3_IRQHandler,     /*!< ADC3 global Interrupt                                */
  FSMC_IRQHandler,     /*!< FSMC global Interrupt                                */
  SDIO_IRQHandler,     /*!< SDIO global Interrupt                                */
  TIM5_IRQHandler,     /*!< TIM5 global Interrupt                                */
  SPI3_IRQHandler,     /*!< SPI3 global Interrupt                                */
  UART4_IRQHandler,     /*!< UART4 global Interrupt                               */
  UART5_IRQHandler,     /*!< UART5 global Interrupt                               */
  TIM6_IRQHandler,     /*!< TIM6 global Interrupt                                */
  TIM7_IRQHandler,     /*!< TIM7 global Interrupt                                */
  DMA2_Channel1_IRQHandler,     /*!< DMA2 Channel 1 global Interrupt                      */
  DMA2_Channel2_IRQHandler,     /*!< DMA2 Channel 2 global Interrupt                      */
  DMA2_Channel3_IRQHandler,     /*!< DMA2 Channel 3 global Interrupt                      */
  DMA2_Channel4_5_IRQHandler,      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
#elif defined STM32F10X_CL
  ADC1_2_IRQHandler,     /*!< ADC1 and ADC2 global Interrupt                       */
  CAN1_TX_IRQHandler,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  CAN1_RX0_IRQHandler,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQHandler,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQHandler,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQHandler,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_IRQHandler,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQHandler,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQHandler,     /*!< TIM1 Trigger and Commutation Interrupt               */
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  TIM5_IRQHandler,     /*!< TIM5 global Interrupt                                */
  SPI3_IRQHandler,     /*!< SPI3 global Interrupt                                */
  UART4_IRQHandler,     /*!< UART4 global Interrupt                               */
  UART5_IRQHandler,     /*!< UART5 global Interrupt                               */
  TIM6_IRQHandler,   /*!< TIM6 global Interrupt                                */
  TIM7_IRQHandler,     /*!< TIM7 global Interrupt                                */
  DMA2_Channel1_IRQHandler,     /*!< DMA2 Channel 1 global Interrupt                      */
  DMA2_Channel2_IRQHandler,     /*!< DMA2 Channel 2 global Interrupt                      */
  DMA2_Channel3_IRQHandler,     /*!< DMA2 Channel 3 global Interrupt                      */
  DMA2_Channel4_IRQHandler,     /*!< DMA2 Channel 4 global Interrupt                      */
  DMA2_Channel5_IRQHandler,     /*!< DMA2 Channel 5 global Interrupt                      */
  ETH_IRQHandler,     /*!< Ethernet global Interrupt                            */
  ETH_WKUP_IRQHandler,     /*!< Ethernet Wakeup through EXTI line Interrupt          */
  CAN2_TX_IRQHandler,     /*!< CAN2 TX Interrupt                                    */
  CAN2_RX0_IRQHandler,     /*!< CAN2 RX0 Interrupt                                   */
  CAN2_RX1_IRQHandler,     /*!< CAN2 RX1 Interrupt                                   */
  CAN2_SCE_IRQHandler,     /*!< CAN2 SCE Interrupt                                   */
  OTG_FS_IRQHandler,
#endif
};


#include "crt_common.c"






