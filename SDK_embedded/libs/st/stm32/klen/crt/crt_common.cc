#include "arch.h"
#include "gnu_linker.h"





#include "arch/cortex-m/cm4_core++.h"
#include "arch/stm32f7/stm32++.h"




// this source is included to port version crt 
void ResetHandler(void)  __attribute__((/*naked*/,noreturn)) ; // comment naked attr for workaround compiler fault


// c++ error handler , that is invoked when a pure virtual function is called
void __attribute__((weak,noreturn))  __cxa_pure_virtual()
{
	while(1) {}
}

// c++ error handler , that is invoked when in function calls exceptions caused
void __attribute__((weak,noreturn,used))  abort()
{
	while(1) {}
}

//  normal main() return handler
void __attribute__((weak,noreturn)) __main_exit_handler(int retval)
{
  (void)  retval ;
  while(1) {}
}

// _init stub function
void __attribute__ ((weak)) _init(void)
{
}
// _fini stub function
void __attribute__ ((weak)) _fini(void)
{
}

void __attribute__((weak)) DefaultExceptionHandler(void)
{
  // use cortex_isr_num() for  unhandled interrupt number detect
  //volatile VectorType vt ;
  //vt = cortex_isr_num();
  while(1)
    {
      asm volatile  ("nop");
    }
  //(void)vt ;
}
//-------------------------------------------------------------------------
void __attribute__((weak)) assert_failed(uint8_t* file, uint32_t line)
{
  while(1)
    {
      asm volatile  ("nop");
    }
}
//-------------------------------------------------------------------------
void __attribute__((weak)) exit(uint32_t err)
{
  while(1)
    {
      asm volatile  ("nop");
    }
}
//-------------------------------------------------------------------------
void __attribute__((weak,used))  hard_fault_handler_c(uint32_t* hardfault_args)
{
	volatile uint32_t stacked_r0 =  hardfault_args[0];
	volatile uint32_t stacked_r1 =  hardfault_args[1];
	volatile uint32_t stacked_r2 =  hardfault_args[2];
	volatile uint32_t stacked_r3 =  hardfault_args[3];
	volatile uint32_t stacked_r12 = hardfault_args[4];
	volatile uint32_t stacked_lr =  hardfault_args[5];
	volatile uint32_t stacked_pc =  hardfault_args[6];
	volatile uint32_t stacked_psr = hardfault_args[7];

	register volatile uint8_t trigger = 1 ;

        #ifndef __CORTEX_M0__   // in M0 VTOR is not present
	   volatile uint32_t scb_vtor = SCB->VTOR ; // wiev vector location
	   (void)scb_vtor ;
        #endif

	while (trigger)
  		{
			asm volatile  ("nop");
  		}

	// under debugger: return to situation context
       asm volatile (    "mov r0,  %[reg_r0]   \n"
  	                 "mov r1,  %[reg_r1]   \n"
  	                 "mov r2,  %[reg_r2]   \n"
  	                 "mov r3,  %[reg_r3]   \n"
  	                 "mov r12, %[reg_r12]  \n"
  	                 "mov lr,  %[reg_lr]   \n"
  	                 "mov pc,  %[reg_pc]   \n"
  	                 :
  	                 : [reg_r0] "r"(stacked_r0),
			   [reg_r1] "r"(stacked_r1),
			   [reg_r2] "r"(stacked_r2),
			   [reg_r3] "r"(stacked_r3),
			   [reg_r12]"r"(stacked_r12),
			   [reg_lr] "r"(stacked_lr),
			   [reg_pc] "r"(stacked_pc)
  	                 :
		   );

	(void) stacked_r0 ;
	(void) stacked_r1 ;
	(void) stacked_r2 ;
	(void) stacked_r3 ;
	(void) stacked_r12 ;
	(void) stacked_lr ;
	(void) stacked_pc ;
	(void) stacked_psr ;
}

//-------------------------------------------------------------------------
void __attribute__((weak)) HardFaultException(void)
{
  // read PSP and save return adress from stack sutable for M0/M3/M4/M7 core

  __asm volatile
      (
	  ".syntax unified                    \n"
          "      movs r0, #4                  \n"
	  "      mov  r1, lr                  \n"
	  "      tst  r1, r0                  \n"
          "      beq  _msp_select             \n"
	  "      mrs   r0, psp                \n"
	  "      b     _call_handler          \n"
	  " _msp_select:                      \n"
	  "      mrs   r0, msp                \n"
          " _call_handler:                    \n"
          "      ldr r1,  [r0, #24]           \n"
	  "      mov r2, %[hfh_addr]          \n"
          "      bx r2                        \n"
	  ".syntax divided                    \n"
	  : : [hfh_addr] "r" (hard_fault_handler_c) :
      );
} ;
//-------------------------------------------------------------------------

#if defined __USE_RAM_VEC_TABLE__

#include "misc.h" // defines of NVIC_SetVectorTable

IrqHandlerFunc __attribute__ ((externally_visible,section(".ram_vec_table")))
ram_vec_table [ sizeof(flash_vec_table) / sizeof(IrqHandlerFunc)] ;

void vec_table_copy2ram(unsigned map_needed )
{
  // ����������� �������
  for (uint32_t vec_index = 0 ; vec_index <  sizeof(flash_vec_table) / sizeof(IrqHandlerFunc) ; vec_index++ )
      ram_vec_table[vec_index] = flash_vec_table[vec_index] ;

  if ( map_needed )
    vec_map2ram (0) ;
}
//---------------------------------------------------------------------
void vec_set (  VectorType vec_type  , void* handler )
{
  ram_vec_table[vec_type] =  (IrqHandlerFunc)handler ;
}

void vec_map2ram ( unsigned* vec_table )
{
  NVIC_SetVectorTable(NVIC_VectTab_RAM, (unsigned)(vec_table - SRAM_BASE) ) ;
}
//-------------------------------------------------------------------
inline void vec_map2flash ( unsigned* vec_table )
{
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, (unsigned)(vec_table - FLASH_BASE) ) ;
}
//-------------------------------------------------------------------

#endif //__USE_RAM_VEC_TABLE__
//---------------------------------------------------------------------
void crt_init()
{
   // fill  all internal memory for dummy pattern
   #ifndef FILL_RAM_PATTRERN
               #define FILL_RAM_PATTRERN 0x12345678
   #endif

   unsigned long* ram = gnu_linker_sram_start() ;
   unsigned long* ram_end  ;
   asm volatile ("mov %0 , sp \n" : "=r"(ram_end) : : );
   while( ram < ram_end )
          {
           *(ram++) = FILL_RAM_PATTRERN;
          }

  // init .ccm_data section
  unsigned long* data_load = gnu_linker_ccm_data_load_start() ;
  unsigned long* data = gnu_linker_ccm_data_start() ;
  unsigned long* data_end = gnu_linker_ccm_data_end();
  while( data < data_end )
            {
             *(data++) = *(data_load++);
            }


  // init .data section
  data_load = gnu_linker_data_load_start();
  data = gnu_linker_data_start();
  data_end = gnu_linker_data_end();
  while( data < data_end )
         {
          *(data++) = *(data_load++);
         }

  // init .ccm_bss section
  unsigned long* bss =gnu_linker_ccm_bss_start() ;
  unsigned long* bss_end = gnu_linker_ccm_bss_end() ;
  while(bss < bss_end )
   {
    *(bss++) = 0 ;
   }

  // init .bss section
  bss = gnu_linker_bss_start() ;
  bss_end = gnu_linker_bss_end() ;
  while(bss < bss_end )
   {
    *(bss++) = 0 ;
   }

#ifdef __EXT_MEM_BANK0__

  // init external memory bank0 interface and device, user defined code
  ext_mem_bank0_init();

  // init .data section on ext_mem_bank0
  extern unsigned long  __ext_mem_bank0_data_load_start__ ;
  extern unsigned long  __ext_mem_bank0_data_start__ ;
  extern unsigned long  __ext_mem_bank0_data_end__ ;
  unsigned long* ext_mem_bank0_data_load = &__ext_mem_bank0_data_load_start__ ;
  unsigned long* ext_mem_bank0_data = &__ext_mem_bank0_data_start__ ;
  unsigned long* ext_mem_bank0_data_end = &__ext_mem_bank0_data_end__ ;
  while( ext_mem_bank0_data < ext_mem_bank0_data_end )
    {
      *(ext_mem_bank0_data++) = *(ext_mem_bank0_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank0_bss_start__ ;
  extern unsigned long  __ext_mem_bank0_bss_end__   ;
  unsigned long* ext_mem_bank0_bss = &__ext_mem_bank0_bss_start__ ;
  unsigned long* ext_mem_bank0_bss_end = &__ext_mem_bank0_bss_end__ ;
  while(ext_mem_bank0_bss < ext_mem_bank0_bss_end )
    {
      *(ext_mem_bank0_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK1__

  // init external memory bank1 interface and device, user defined code
  ext_mem_bank1_init();

  // init .data section on ext_mem_bank1
  extern unsigned long  __ext_mem_bank1_data_load_start_ ;
  extern unsigned long  __ext_mem_bank1_data_start__ ;
  extern unsigned long  __ext_mem_bank1_data_end__ ;
  unsigned long* ext_mem_bank1_data_load = &__ext_mem_bank1_data_load_start__ ;
  unsigned long* ext_mem_bank1_data = &__ext_mem_bank1_data_start__ ;
  unsigned long* ext_mem_bank1_data_end = &__ext_mem_bank1_data_end__ ;
  while( ext_mem_bank1_data < ext_mem_bank1_data_end )
    {
      *(ext_mem_bank1_data++) = *(ext_mem_bank1_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank1_bss_start__ ;
  extern unsigned long  __ext_mem_bank1_bss_end__   ;
  unsigned long* ext_mem_bank1_bss = &__ext_mem_bank1_bss_start__ ;
  unsigned long* ext_mem_bank1_bss_end = &__ext_mem_bank1_bss_end__ ;
  while(ext_mem_bank1_bss < ext_mem_bank1_bss_end )
    {
      *(ext_mem_bank1_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK2__

  // init external memory bank2 interface and device, user defined code
  ext_mem_bank2_init();

  // init .data section on ext_mem_bank2
  extern unsigned long  __ext_mem_bank2_data_load_start__ ;
  extern unsigned long  __ext_mem_bank2_data_start__ ;
  extern unsigned long  __ext_mem_bank2_data_end__ ;
  unsigned long* ext_mem_bank2_data_load = &__ext_mem_bank2_data_load_start__ ;
  unsigned long* ext_mem_bank2_data = &__ext_mem_bank2_data_start__ ;
  unsigned long* ext_mem_bank2_data_end = &__ext_mem_bank2_data_end__ ;
  while( ext_mem_bank2_data < ext_mem_bank2_data_end )
    {
      *(ext_mem_bank2_data++) = *(ext_mem_bank2_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank2_bss_start__ ;
  extern unsigned long  __ext_mem_bank2_bss_end__   ;
  unsigned long* ext_mem_bank2_bss = &__ext_mem_bank2_bss_start__ ;
  unsigned long* ext_mem_bank2_bss_end = &__ext_mem_bank2_bss_end__ ;
  while(ext_mem_bank2_bss < ext_mem_bank2_bss_end )
    {
      *(ext_mem_bank2_bss++) = 0 ;
    }
#endif

#ifdef __EXT_MEM_BANK3__

  // init external memory bank3 interface and device, user defined code
  ext_mem_bank3_init();

  // init .data section on ext_mem_bank3
  extern unsigned long  __ext_mem_bank3_data_load_start__ ;
  extern unsigned long  __ext_mem_bank3_data_start__ ;
  extern unsigned long  __ext_mem_bank3_data_end__ ;
  unsigned long* ext_mem_bank3_data_load = &__ext_mem_bank3_data_load_start__ ;
  unsigned long* ext_mem_bank3_data = &__ext_mem_bank3_data_start__ ;
  unsigned long* ext_mem_bank3_data_end = &__ext_mem_bank3_data_end__ ;
  while( ext_mem_bank3_data < ext_mem_bank3_data_end )
    {
      *(ext_mem_bank3_data++) = *(ext_mem_bank3_data_load++);
    }

  // init .bss section
  extern unsigned long  __ext_mem_bank3_bss_start__ ;
  extern unsigned long  __ext_mem_bank3_bss_end__   ;
  unsigned long* ext_mem_bank3_bss = &__ext_mem_bank3_bss_start__ ;
  unsigned long* ext_mem_bank3_bss_end = &__ext_mem_bank3_bss_end__ ;
  while(ext_mem_bank3_bss < ext_mem_bank3_bss_end )
    {
      *(ext_mem_bank3_bss++) = 0 ;
    }
#endif

}
//---------------------------------------------------------------------
void ResetHandler(void)
{
        // reset PLLs, RCC , Vector Table Relocation in Internal FLASH, external RAM , other...
	//void SystemInit(void);
	//SystemInit();
        void system_init();
        system_init();




        //#ifndef VECT_TAB_ADDR
           scb.
        //#else
        //system_init( VECT_TAB_ADDR );





// TODO этот код есть в void SystemInit(void);  оставляю на всякий случай до следующего раза, нудно удалить
//        #if defined( __CORTEX_M4__) ||  defined( __CORTEX_M7__) // arch have FPU
//           #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
//	   // Enable access to Floating-Point coprocessor.
//	   SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
//           #endif
//        #endif

	// easy way (with not using SysTickTimer) without  HAL_Init()
	// configure flash prefetch, instruction cache, data cache
	// set interrupt group priority NVIC_PRIORITYGROUP_4
	// use systick as time base source and configure 1ms tick (default clock after Reset is HSI)
	// call HAL_MspInit() for owerwrite id above if needed
	// HAL_Init();
        // set system and buses clock (implement in cmsis::system_stm32f4xx_klen_utils.c)
	void KlenSystemClockConfig();
	KlenSystemClockConfig();

	// delay for GDB connect
	#ifndef DELAY_FOR_GDB
		#define DELAY_FOR_GDB 10000
	#endif

        #define  nop_rep(n)   asm volatile (".rep " #n "\n"\
                                            "   nop\n"\
			                    ".endr\n")
        #define  nop_while(n) {volatile uint32_t t = n; while (t--) nop_rep(1); }
	nop_while(DELAY_FOR_GDB);



	// fill memory and initialize .bss , .data  sections
	crt_init();

	// switch vec table to ram
	#if defined __USE_RAM_VEC_TABLE__
		vec_table_copy2ram( 1 ) ;
	#endif //RAM_VEC_TABLE

	// вызов конструкторов глобальных объектов
	// и функций с атрибутом constructor
	void __libc_init_array(void);
	__libc_init_array() ;

	// вызов основной функции
	int main (void) ;
	int retval = main();

	// вызов деструкторов  глобальных объектов
	// и функций с атрибутом destructor
	void __libc_fini_array(void);
	__libc_fini_array() ;

	// call exit function
	__main_exit_handler(retval);
}


