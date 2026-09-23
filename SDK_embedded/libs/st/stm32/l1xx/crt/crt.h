#ifndef __CRT_H__
#define __CRT_H__

#ifdef  __cplusplus
 extern "C" {
#endif

typedef void( *IrqHandlerFunc )( void );

typedef enum
{
		vtStackEnd=0,            /* The initial stack pointer*/
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
		vtTAMPER_STAMP_IRQHandler,
		vtRTC_WKUP_IRQHandler,
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
		vtADC1_IRQHandler,
		vtUSB_HP_IRQHandler,
		vtUSB_LP_IRQHandler,
		vtDAC_IRQHandler,
		vtCOMP_IRQHandler,
		vtEXTI9_5_IRQHandler,
		vtLCD_IRQHandler,
		vtTIM9_IRQHandler,
		vtTIM10_IRQHandler,
		vtTIM11_IRQHandler,
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
		vtRTC_Alarm_IRQHandler,
		vtUSB_FS_WKUP_IRQHandler,
		vtTIM6_IRQHandler,
	#if defined STM32L1XX_MD
		vtTIM7_IRQHandler,
	#elif defined STM32L1XX_MDP
		vtTIM7_IRQHandler,
		vtTIM5_IRQHandler,
		vtSPI3_IRQHandler,
		vtDMA2_Channel1_IRQHandler,
		vtDMA2_Channel2_IRQHandler,
		vtDMA2_Channel3_IRQHandler,
		vtDMA2_Channel4_IRQHandler,
		vtDMA2_Channel5_IRQHandler,
		vtAES_IRQHandler,
		vtCOMP_ACQ_IRQHandler,
	#elif defined STM32L1XX_HD
		vtTIM7_IRQHandler,
		vtSDIO_IRQHandler,
		vtTIM5_IRQHandler,
		vtSPI3_IRQHandler,
		vtUART4_IRQHandler,
		vtUART5_IRQHandler,
		vtDMA2_Channel1_IRQHandler,
		vtDMA2_Channel2_IRQHandler,
		vtDMA2_Channel3_IRQHandler,
		vtDMA2_Channel4_IRQHandler,
		vtDMA2_Channel5_IRQHandler,
		vtAES_IRQHandler,
		vtCOMP_ACQ_IRQHandler,
	#endif

	vtVecCount
} VectorType ;

#include <stdint.h>
#include "system_stm32l1xx.h" // defines of SystemInit

#include "crt_common.h"


#ifdef  __cplusplus
 }
#endif

#endif /*__CRT_H__*/
