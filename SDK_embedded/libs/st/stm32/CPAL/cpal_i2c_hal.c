#if defined __STM32F1XX__
	#include "cpal_i2c_hal_stm32f10x"
#elif defined __STM32F2XX__
	#include "cpal_i2c_hal_stm32f2xx"
#elif defined __STM32F4XX__
	#include "cpal_i2c_hal_stm32f4xx"
#elif defined  __STM32L1XX__
	#include "cpal_i2c_hal_stm32l1xx"
#endif
