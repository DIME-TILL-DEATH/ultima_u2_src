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
		vtReserved4,
		vtReserved5,
		vtReserved6,
		vtReserved7,
		vtReserved8,
		vtReserved9,
		vtReserved10,            /* Reserved */
	#if defined __USE_FREERTOS__
		vtvPortSVCHandler,
	#else
		vtSVCHandler,
	#endif
		vtReserved12,
		vtReserved13,                      /* Reserved */
	#if defined __USE_FREERTOS__
		vtxPortPendSVHandler,
		vtxPortSysTickHandler,
	#else
		vtPendSVC,
		vtSysTickHandler,
	#endif
		vtWWDG_IRQHandler,
		vtReserved17,
		vtRTC_IRQHandler,
		vtFLASH_IRQHandler,
		vtRCC_IRQHandler,
		vtEXTI0_1_IRQHandler,
		vtEXTI2_3_IRQHandler,
		vtEXTI4_15_IRQHandler,
		vtReserved24,
		vtDMA_Channal0_IRQHandler,
		vtDMA_Channal2_3_IRQHandler,
		vtDMA_Channal4_5_IRQHandler,
		vtADC_IRQHandler,
		vtTIM1_BRK_UP_TRG_COM_IRQHandler,
		vtTIM1_CC_IRQHandler,
		vtReserved31,
		vtTIM3_IRQHandler,
		vtTIM6_IRQHandler,
		vtReserved34,
		vtTIM14_IRQHandler,
		vtTIM15_IRQHandler,
		vtTIM16_IRQHandler,
		vtTIM17_IRQHandler,
		vtI2C1_IRQHandler,
		vtI2C2_IRQHandler,
		vtSPI1_IRQHandler,
		vtSPI2_IRQHandler,
		vtUSART1_IRQHandler,
		vtUSART2_IRQHandler,
		vtUSART3_4_5_6_IRQHandler,
		vtReserved47,
		vtUSB_IRQHandler,

		vtVecCount
} VectorType ;

#include <stdint.h>
#include "system_stm32f0xx.h" // defines of SystemInit

#include "crt_common.h"


#ifdef  __cplusplus
 }
#endif

#endif /*__CRT_H__*/
