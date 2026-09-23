#ifndef __ARCH_H__
#define __ARCH_H__

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "stm32++.h"

//----------------------------------------------
// general macro defines -----------------------
#include "sdkdefs.h"


// suppor memory bit banding
#if defined (__CORTEX_M3__) || ( __CORTEX_M4F__ )
   #define  CCMDATARAM_ADDR_2_BB_ADDR(REG,BIT)  (uint32_t*)(CCMDATARAM_BB_BASE + ((  (uint32_t)&(REG) - CCMDATARAM_BASE) * 32) + (BIT * 4))
   #define  SRAM_ADDR_2_BB_ADDR(REG,BIT)        (uint32_t*)(SRAM_BB_BASE +       ((  (uint32_t)&(REG) - SRAM_BASE)       * 32) + (BIT * 4))
   #define  SRAM1_ADDR_2_BB_ADDR(REG,BIT)       (uint32_t*)(SRAM1_BB_BASE +      ((  (uint32_t)&(REG) - SRAM1_BASE)      * 32) + (BIT * 4))
   #define  SRAM2_ADDR_2_BB_ADDR(REG,BIT)       (uint32_t*)(SRAM2_BB_BASE +      ((  (uint32_t)&(REG) - SRAM2_BASE)      * 32) + (BIT * 4))
   #define  SRAM3_ADDR_2_BB_ADDR(REG,BIT)       (uint32_t*)(SRAM3_BB_BASE +      ((  (uint32_t)&(REG) - SRAM3_BASE)      * 32) + (BIT * 4))
   #define  PERIPH_ADDR_2_BB_ADDR(REG,BIT)      (uint32_t*)(PERIPH_BB_BASE +     ((  (uint32_t)&(REG) - PERIPH_BASE)     * 32) + (BIT * 4))
   #define  BKPSRAM_ADDR_2_BB_ADDR(REG,BIT)     (uint32_t*)(BKPSRAM_BB_BASE +    ((  (uint32_t)&(REG) - BKPSRAM_BASE)    * 32) + (BIT * 4))
#endif


#endif /*__ARCH_H__*/
