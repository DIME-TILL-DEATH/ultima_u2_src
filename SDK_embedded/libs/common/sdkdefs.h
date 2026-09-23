#ifndef __SDKDEFS_H__
#define __SDKDEFS_H__

#define _BV(val) (1<<val)
#define __PACKED__  __attribute__ ((packed))
#define __ALIGN_4__ __attribute__ ((aligned(4)))
#define __ALIGN_8__ __attribute__ ((aligned(4)))

#define likely(x)	       __builtin_expect(!!(x), 1)
#define unlikely(x)	       __builtin_expect(!!(x), 0)
#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#if !defined NULL
        #define  NULL    (void*)0
#endif

#define __RAMFUNC__  __attribute__ ((section(".ramfunc"),noinline,long_call))
#define __CONST_DATA__ __attribute__ ((section(".const_data")))
#define __FUNC_USED__ __attribute__((used))

#define __CCM_BSS__ __attribute__ ((section(".ccm_bss")))
#define __CCM_DATA__ __attribute__ ((section(".ccm_data")))

#if defined (__EXT_MEM_BANK0__)
   #define   __EXT_MEM_BANK0_BSS__   __attribute__ ((section(".ext_mem_bank0_bss")))
   #define   __EXT_MEM_BANK0_DATA__  __attribute__ ((section(".ext_mem_bank0_data")))
#endif

#if defined (__EXT_MEM_BANK1__)
   #define   __EXT_MEM_BANK1_BSS__   __attribute__ ((section(".ext_mem_bank1_bss")))
   #define   __EXT_MEM_BANK1_DATA__  __attribute__ ((section(".ext_mem_bank1_data")))
#endif

#if defined (__EXT_MEM_BANK2__)
   #define   __EXT_MEM_BANK2_BSS__   __attribute__ ((section(".ext_mem_bank2_bss")))
   #define   __EXT_MEM_BANK2_DATA__  __attribute__ ((section(".ext_mem_bank2_data")))
#endif

#if defined (__EXT_MEM_BANK3__)
   #define   __EXT_MEM_BANK3_BSS__   __attribute__ ((section(".ext_mem_bank3_bss")))
   #define   __EXT_MEM_BANK3_DATA__  __attribute__ ((section(".ext_mem_bank3_data")))
#endif

#endif /*__SDKDEFS_H__*/
