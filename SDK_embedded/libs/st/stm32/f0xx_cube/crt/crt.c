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

	void __attribute__((weak)) RTC_IRQHandler(void);
	#pragma weak RTC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) FLASH_IRQHandler(void);
	#pragma weak FLASH_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) RCC_IRQHandler(void);
	#pragma weak RCC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI0_1_IRQHandler(void);
	#pragma weak EXTI0_1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI2_3_IRQHandler(void);
	#pragma weak EXTI2_3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) EXTI4_15_IRQHandler(void);
	#pragma weak EXTI4_15_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) DMA_Channal0_IRQHandler(void);
	#pragma weak DMA_Channal0_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA_Channal2_3_IRQHandler(void);
	#pragma weak DMA_Channal2_3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) DMA_Channal4_5_IRQHandler(void);
	#pragma weak DMA_Channal4_5_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) ADC_IRQHandler(void);
	#pragma weak ADC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_BRK_UP_TRG_COM_IRQHandler(void);
	#pragma weak TIM1_BRK_UP_TRG_COM_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM1_CC_IRQHandler(void);
	#pragma weak TIM1_CC_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM3_IRQHandler(void);
	#pragma weak TIM3_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM6_IRQHandler(void);
	#pragma weak TIM6_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM14_IRQHandler(void);
	#pragma weak TIM14_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM15_IRQHandler(void);
	#pragma weak TIM15_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM16_IRQHandler(void);
	#pragma weak TIM16_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) TIM17_IRQHandler(void);
	#pragma weak TIM17_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) I2C1_IRQHandler(void);
	#pragma weak I2C1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) I2C2_IRQHandler(void);
	#pragma weak I2C2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI1_IRQHandler(void);
	#pragma weak SPI1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) SPI2_IRQHandler(void);
	#pragma weak SPI2_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) USART1_IRQHandler(void);
	#pragma weak USART1_IRQHandler = DefaultExceptionHandler

	void __attribute__((weak)) USART2_IRQHandler(void);
	#pragma weak USART2_IRQHandler = DefaultExceptionHandler


	void __attribute__((weak)) USART3_4_5_6_IRQHandler(void);
	#pragma weak USART3_4_5_6_IRQHandler = DefaultExceptionHandler


        void __attribute__((weak)) USB_IRQHandler(void);
        #pragma weak USB_IRQHandler = DefaultExceptionHandler


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
   0,
   0,
   0,
   0,
   0,
   0,
   0,            /* Reserved */
   #if defined __USE_FREERTOS__
      vPortSVCHandler,
   #else
      SVCHandler,
   #endif
   0,
   0,                      /* Reserved */
   #if defined __USE_FREERTOS__
      xPortPendSVHandler,
      xPortSysTickHandler,
   #else
      PendSVC,
      SysTickHandler,
   #endif
   WWDG_IRQHandler,
   0,
   RTC_IRQHandler,
   FLASH_IRQHandler,
   RCC_IRQHandler,
   EXTI0_1_IRQHandler,
   EXTI2_3_IRQHandler,
   EXTI4_15_IRQHandler,
   0,
   DMA_Channal0_IRQHandler,
   DMA_Channal2_3_IRQHandler,
   DMA_Channal4_5_IRQHandler,
   ADC_IRQHandler,
   TIM1_BRK_UP_TRG_COM_IRQHandler,
   TIM1_CC_IRQHandler,
   0,
   TIM3_IRQHandler,
   TIM6_IRQHandler,
   0,
   TIM14_IRQHandler,
   TIM15_IRQHandler,
   TIM16_IRQHandler,
   TIM17_IRQHandler,
   I2C1_IRQHandler,
   I2C2_IRQHandler,
   SPI1_IRQHandler,
   SPI2_IRQHandler,
   USART1_IRQHandler,
   USART2_IRQHandler,
   USART3_4_5_6_IRQHandler,
   0,
   USB_IRQHandler
};


#include "crt_common.c"






