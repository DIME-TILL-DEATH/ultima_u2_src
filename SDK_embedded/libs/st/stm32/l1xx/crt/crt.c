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

void __attribute__((weak)) ADC1_IRQHandler(void);
#pragma weak DC1_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_HP_IRQHandler(void);
#pragma weak USB_HP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) USB_LP_IRQHandler(void);
#pragma weak USB_LP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) DAC_IRQHandler(void);
#pragma weak DAC_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) COMP_IRQHandler(void);
#pragma weak COMP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) EXTI9_5_IRQHandler(void);
#pragma weak EXTI9_5_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) LCD_IRQHandler(void);
#pragma weak LCD_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM9_IRQHandler(void);
#pragma weak TIM9_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM10_IRQHandler(void);
#pragma weak TIM10_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM11_IRQHandler(void);
#pragma weak TIM11_IRQHandler = DefaultExceptionHandler

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

void __attribute__((weak)) USB_FS_WKUP_IRQHandler(void);
#pragma weak USB_FS_WKUP_IRQHandler = DefaultExceptionHandler

void __attribute__((weak)) TIM6_IRQHandler(void);
#pragma weak TIM6_IRQHandler = DefaultExceptionHandler

#if defined STM32L1XX_MD
	void __attribute__((weak)) TIM7_IRQHandler(void);
	#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

#elif defined STM32L1XX_MDP
	void __attribute__((weak)) TIM7_IRQHandler(void);
	#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM5_IRQHandler(void);
	#pragma weak TIM5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI3_IRQHandler(void);
	#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

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

	void __attribute__((weak)) AES_IRQHandler(void);
	#pragma weak AES_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) COMP_ACQ_IRQHandler(void);
	#pragma weak COMP_ACQ_IRQHandler = DefaultExceptionHandler

#elif defined STM32L1XX_HD
	void __attribute__((weak)) TIM7_IRQHandler(void);
	#pragma weak TIM7_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SDIO_IRQHandler(void);
	#pragma weak  = DefaultExceptionHandler

	void __attribute__((weak)) TIM5_IRQHandler(void);
	#pragma weak SDIO_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI3_IRQHandler(void);
	#pragma weak SPI3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) UART4_IRQHandler(void);
	#pragma weak  = DefaultExceptionHandler

	void __attribute__((weak)) UART5_IRQHandler(void);
	#pragma weak UART4_IRQHandler = DefaultExceptionHandler

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

	void __attribute__((weak)) AES_IRQHandler(void);
	#pragma weak AES_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) COMP_ACQ_IRQHandler(void);
	#pragma weak COMP_ACQ_IRQHandler = DefaultExceptionHandler

#endif


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
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_IRQHandler,
  DMA1_Channel3_IRQHandler,
  DMA1_Channel4_IRQHandler,
  DMA1_Channel5_IRQHandler,
  DMA1_Channel6_IRQHandler,
  DMA1_Channel7_IRQHandler,
  ADC1_IRQHandler,
  USB_HP_IRQHandler,
  USB_LP_IRQHandler,
  DAC_IRQHandler,
  COMP_IRQHandler,
  EXTI9_5_IRQHandler,
  LCD_IRQHandler,
  TIM9_IRQHandler,
  TIM10_IRQHandler,
  TIM11_IRQHandler,
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
  RTC_Alarm_IRQHandler,
  USB_FS_WKUP_IRQHandler,
  TIM6_IRQHandler,
#if defined STM32L1XX_MD
  TIM7_IRQHandler,
#elif defined STM32L1XX_MDP
  TIM7_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_IRQHandler,
  DMA2_Channel5_IRQHandler,
  AES_IRQHandler,
  COMP_ACQ_IRQHandler,
#elif defined STM32L1XX_HD
  TIM7_IRQHandler,
  SDIO_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_IRQHandler,
  DMA2_Channel5_IRQHandler,
  AES_IRQHandler,
  COMP_ACQ_IRQHandler
#endif
};


#include "crt_common.c"






