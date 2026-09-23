#include "stm32f7xx_hal_conf.h" // file must be stored in application: PROJECT_DIR/src/include/stm32f4xx_hal_conf.h
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_pwr.h"
#include "stm32f7xx_hal_flash.h"

#define HSE_TIMEOUT_VALUE          ((uint32_t)100)
#define HSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define LSI_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define PLL_TIMEOUT_VALUE          ((uint32_t)100)  /* 100 ms */
#define CLOCKSWITCH_TIMEOUT_VALUE  ((uint32_t)5000) /* 5 s    */

typedef enum { cv168Mhz=0,
               cv192Mhz,
	       cv216Mhz,
	       cv240Mhz,
               #ifdef  PLL_N
                   cvUserPLL_N,
               #endif
               cvCount
             } clock_val_t ;

typedef struct
{
  uint32_t Q;   // USB OTG FS, SDIO and RNG clock divider =  PLL_VCO / Q, result must be 48MHz
  uint32_t N;   // Pll multipiller (freq of pll oscilator)  PLL_VCO = ( F_OSC / M) * N, where ( F_OSC / M) = 1MHz
  uint32_t FL ; // flash latency

} pll_config_t;

static const pll_config_t pll_configs[] =
    {
        { 7 ,    336   , FLASH_LATENCY_5  },
        { 8 ,    384   , FLASH_LATENCY_5  },
        { 9 ,    432   , FLASH_LATENCY_5  },
        { 10,    480   , FLASH_LATENCY_5  },
#ifdef  PLL_N
	{ PLL_Q, PLL_N , FLASH_LATENCY },
#endif
    };

#ifdef  PLL_N
    #if PLL_CONFIG>4
        #error "PLL_CONFIG more than 4 - is a cvUserPLL_N"
    #endif
#else
    #if PLL_CONFIG>3
        #error "PLL_CONFIG more than 3 - is a cv240Mhz"
    #endif
#endif

// интересные значения найденые на эмуляоре STM32CubeMX
// osc=8 MHz M=4 N=240 P=2 Q=10 ->  pll=480 usb=48MHz SYS=240 MHz
// osc=8 MHz M=4 N=264 P=2 Q=11 ->  pll=528 usb=48MHz SYS=264 MHz
// osc=8 MHz M=4 N=288 P=2 Q=12 ->  pll=576 usb=48MHz SYS=288 MHz не страртовал
// osc=8 MHz M=4 N=312 P=2 Q=13 ->  pll=624 usb=48MHz SYS=312 MHz не страртовал

/************************* PLL Parameters *************************************/


// PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
#ifndef PLL_M
  #define PLL_M      (unsigned int)F_OSC/( 1000000 )
#endif

#define PLL_N  pll_configs[PLL_CONFIG].N  /*336*/    /*384*/  /*432*/   /*480*/

// USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */
#define PLL_Q  pll_configs[PLL_CONFIG].Q  /*7*/      /*8*/   /*9*/    /*10*/

// SYSCLK = PLL_VCO / PLL_P
#define PLL_P  2

#define FLASH_LATENCY pll_configs[PLL_CONFIG].FL
//***********************************************************************************



/*
* @brief  System Clock Configuration
*         The system Clock is configured as follow :
*            System Clock source            = PLL (HSE)
*            SYSCLK(Hz)                     = 216000000
*            HCLK(Hz)                       = 216000000
*            AHB Prescaler                  = 1
*            APB1 Prescaler                 = 4
*            APB2 Prescaler                 = 2
*            HSE Frequency(Hz)              = 8000000
*            PLL_M                          = 8
*            PLL_N                          = 432
*            PLL_P                          = 2
*            PLL_Q                          = 9
*            PLL_R                          = 7
*            VDD(V)                         = 3.3
*            Main regulator output voltage  = Scale1 mode
*            Flash Latency(WS)              = 7
* @param  None
* @retval None
*/
void KlenSystemClockConfig(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1) {};
  }

  /* Activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    while(1) {};
  }


  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    while(1) {};
  }
}

