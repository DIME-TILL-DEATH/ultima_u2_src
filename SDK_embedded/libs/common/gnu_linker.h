#ifndef __GNU_LINKER_H__
#define __GNU_LINKER_H__

#include "stddef.h"
#include "stdint.h"

// support SDK by GNU linker
// strong relative on SDK_embedded/scripts/ld/ld_*.m4

#ifdef __cplusplus
	extern "C" {
#endif

// flash area defines
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_stack_end() { extern uint32_t __stack_end__ ; return &__stack_end__ ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_flash_start() { extern uint8_t __flash_start__ ; return &__flash_start__ ; }
inline void*  gnu_linker_flash_end()   { extern uint8_t __flash_end__ ;   return &__flash_end__ ;   }
inline size_t gnu_linker_flash_size() { return (uint8_t*)gnu_linker_flash_end() - (uint8_t*)gnu_linker_flash_start() ; }
//--------------------------------------------------------------------------------------
inline void*  gnu_linker_image_start() { extern uint8_t __image_start__ ; return &__image_start__ ; }
inline void*  gnu_linker_image_end()   { extern uint8_t __image_end__ ; return &__image_end__ ; }
inline size_t gnu_linker_image_size() { return (uint8_t*)gnu_linker_image_end() - (uint8_t*)gnu_linker_image_start() ; }
//--------------------------------------------------------------------------------------
inline void*  gnu_linker_vec_start()   { extern uint8_t __vec_start__ ;  return &__vec_start__ ; }
inline void*  gnu_linker_vec_end()     { extern uint8_t __vec_end__ ;  return &__vec_end__ ; }
inline size_t gnu_linker_vec_size()   { return (uint8_t*)gnu_linker_vec_end() - (uint8_t*)gnu_linker_vec_start() ; }
//--------------------------------------------------------------------------------------
inline void*  gnu_linker_eeprom_sector_a_start() { extern uint8_t __eeprom_sector_a_start__ ; return &__eeprom_sector_a_start__ ; }
inline void*  gnu_linker_eeprom_sector_a_end()   { extern uint8_t __eeprom_sector_a_end__ ; return &__eeprom_sector_a_end__ ; }
inline size_t gnu_linker_eeprom_sector_a_size() { return (uint8_t*)gnu_linker_eeprom_sector_a_end() - (uint8_t*)gnu_linker_eeprom_sector_a_start() ; }

inline void*  gnu_linker_eeprom_sector_b_start() { extern uint8_t __eeprom_sector_b_start__ ; return &__eeprom_sector_b_start__ ; }
inline void*  gnu_linker_eeprom_sector_b_end()   { extern uint8_t __eeprom_sector_b_end__ ; return &__eeprom_sector_b_end__ ; }
inline size_t gnu_linker_eeprom_sector_b_size() { return (uint8_t*)gnu_linker_eeprom_sector_b_end() - (uint8_t*)gnu_linker_eeprom_sector_b_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_code_start() {  extern uint8_t __code_start__ ;  return &__code_start__ ; }
inline void*  gnu_linker_code_end()   {  extern uint8_t __code_end__ ;  return &__code_end__ ; }
inline size_t gnu_linker_code_size() {  return (uint8_t*)gnu_linker_code_end() - (uint8_t*)gnu_linker_code_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_preinit_array_start() { extern void (*__preinit_array_start__ []) (void) ;   return __preinit_array_start__ ; }
inline void*  gnu_linker_preinit_array_end()   { extern void (*__preinit_array_end__ []) (void) ;   return __preinit_array_end__ ; }
inline size_t gnu_linker_preinit_array_size() { return (uint8_t*)gnu_linker_preinit_array_end() - (uint8_t*)gnu_linker_preinit_array_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_init_array_start() { extern void (*__init_array_start__ []) (void) ; return __init_array_start__ ; }
inline void*  gnu_linker_init_array_end()   { extern void (*__init_array_end__ []) (void) ; return __init_array_end__ ; }
inline size_t gnu_linker_init_array_size() { return (uint8_t*)gnu_linker_init_array_end() - (uint8_t*)gnu_linker_init_array_start() ;}
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_fini_array_start() { extern void (*__fini_array_start__ []) (void) ;  return __fini_array_start__ ; }
inline void*  gnu_linker_fini_array_end()   { extern void (*__fini_array_end__ []) (void) ;  return __fini_array_end__ ; }
inline size_t gnu_linker_fini_array_size() { return (uint8_t*)gnu_linker_fini_array_end()  - (uint8_t*)gnu_linker_fini_array_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_privileged_functions_start() { extern uint8_t __privileged_functions_start__ ; return &__privileged_functions_start__ ; }
inline void*  gnu_linker_privileged_functions_end() { extern uint8_t __privileged_functions_end__ ; return &__privileged_functions_end__ ; }
inline size_t gnu_linker_privileged_functions_size(){  return (uint8_t*)gnu_linker_privileged_functions_end() - (uint8_t*)gnu_linker_privileged_functions_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_text_start() { extern uint8_t __text_start__ ; return &__text_start__ ; }
inline void*  gnu_linker_text_end()   { extern uint8_t __text_end__ ; return &__text_end__ ; }
inline size_t gnu_linker_text_size() { return (uint8_t*)gnu_linker_text_end() - (uint8_t*)gnu_linker_text_start() ; }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_rodata_start() { extern uint8_t __rodata_start__ ; return &__rodata_start__ ; }
inline void*  gnu_linker_rodata_end()   { extern uint8_t __rodata_end__ ; return &__rodata_end__ ; }
inline size_t gnu_linker_rodata_size() { return (uint8_t*)gnu_linker_rodata_end() - (uint8_t*)gnu_linker_rodata_start(); }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_const_data_start() { extern uint8_t __const_data_start__ ; return &__const_data_start__ ; }
inline void*  gnu_linker_const_data_end()   { extern uint8_t __const_data_end__ ; return &__const_data_end__ ; }
inline size_t gnu_linker_const_data_size() { return (uint8_t*)gnu_linker_const_data_end() - (uint8_t*)gnu_linker_const_data_start(); }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_ccm_data_load_start() { extern uint8_t __ccm_data_load_start__ ; return &__ccm_data_load_start__ ; }
inline void*  gnu_linker_ccm_data_load_end()   { extern uint8_t __ccm_data_load_end__ ; return &__ccm_data_load_end__ ; }
inline size_t gnu_linker_ccm_data_load_size() { return (uint8_t*)gnu_linker_ccm_data_load_end() - (uint8_t*)gnu_linker_ccm_data_load_start(); }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_itcm_data_load_start() { extern uint8_t __itcm_data_load_start__ ; return &__itcm_data_load_start__ ; }
inline void*  gnu_linker_itcm_data_load_end()   { extern uint8_t __itcm_data_load_end__ ; return &__itcm_data_load_end__ ; }
inline size_t gnu_linker_itcm_data_load_size() { return (uint8_t*)gnu_linker_itcm_data_load_end() - (uint8_t*)gnu_linker_itcm_data_load_start(); }
//---------------------------------------------------------------------------------------
inline void*  gnu_linker_dtcm_data_load_start() { extern uint8_t __dtcm_data_load_start__ ; return &__dtcm_data_load_start__ ; }
inline void*  gnu_linker_dtcm_data_load_end()   { extern uint8_t __dtcm_data_load_end__ ; return &__dtcm_data_load_end__ ; }
inline size_t gnu_linker_dtcm_data_load_size() { return (uint8_t*)gnu_linker_dtcm_data_load_end() - (uint8_t*)gnu_linker_dtcm_data_load_start(); }
//--------------------------------------------------------------------------------------
inline void*  gnu_linker_data_load_start() { extern uint8_t __data_load_start__ ; return &__data_load_start__ ; }
inline void*  gnu_linker_data_load_end()   { extern uint8_t __data_load_end__ ; return &__data_load_end__ ; }
inline size_t gnu_linker_data_load_size() { return (uint8_t*)gnu_linker_data_load_end() - (uint8_t*)gnu_linker_data_load_start(); }

#ifdef __EXT_MEM_BANK2__
inline void*  gnu_linker_ext_mem_bank2_data_load_start() { extern uint8_t __ext_mem_bank2_data_load_start__ ; return &__ext_mem_bank2_data_load_start__ ; }
inline void*  gnu_linker_ext_mem_bank2_data_load_end()   { extern uint8_t __ext_mem_bank2_data_load_end__ ; return &__ext_mem_bank2_data_load_end__ ; }
inline size_t gnu_linker_ext_mem_bank2_data_load_size() { return (uint8_t*)gnu_linker_ext_mem_bank2_data_load_end() - (uint8_t*)gnu_linker_ext_mem_bank2_data_load_start(); }
#endif

// ram area defines
//------------------------------------------------------------------------
inline void*  gnu_linker_sram_start() {   extern uint8_t __sram_start__ ;   return &__sram_start__ ; }
inline void*  gnu_linker_sram_end()   {   extern uint8_t __sram_end__ ;     return &__sram_end__ ;  }
inline size_t gnu_linker_sram_size() {   return (uint8_t*)gnu_linker_sram_end() - (uint8_t*)gnu_linker_sram_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_ccm_start() {   extern uint8_t __ccm_start__ ;   return &__ccm_start__ ; }
inline void*  gnu_linker_ccm_end()   {   extern uint8_t __ccm_end__ ;     return &__ccm_end__ ;  }
inline size_t gnu_linker_ccm_size() {   return (uint8_t*)gnu_linker_ccm_end() - (uint8_t*)gnu_linker_ccm_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_itcm_start() {   extern uint8_t __itcm_start__ ;   return &__itcm_start__ ; }
inline void*  gnu_linker_itcm_end()   {   extern uint8_t __itcm_end__ ;     return &__itcm_end__ ;  }
inline size_t gnu_linker_itcm_size() {   return (uint8_t*)gnu_linker_itcm_end() - (uint8_t*)gnu_linker_itcm_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_dtcm_start() {   extern uint8_t __dtcm_start__ ;   return &__dtcm_start__ ; }
inline void*  gnu_linker_dtcm_end()   {   extern uint8_t __dtcm_end__ ;     return &__dtcm_end__ ;  }
inline size_t gnu_linker_dtcm_size() {   return (uint8_t*)gnu_linker_dtcm_end() - (uint8_t*)gnu_linker_dtcm_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_ccm_data_start() {   extern uint8_t __ccm_data_start__ ;   return &__ccm_data_start__ ; }
inline void*  gnu_linker_ccm_data_end()   {   extern uint8_t __ccm_data_end__ ;     return &__ccm_data_end__ ;  }
inline size_t gnu_linker_ccm_data_size() {   return (uint8_t*)gnu_linker_ccm_data_end() - (uint8_t*)gnu_linker_ccm_data_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_ccm_bss_start() {   extern uint8_t __ccm_bss_start__ ;   return &__ccm_bss_start__ ; }
inline void*  gnu_linker_ccm_bss_end()   {   extern uint8_t __ccm_bss_end__ ;     return &__ccm_bss_end__ ;  }
inline size_t gnu_linker_ccm_bss_size() {   return (uint8_t*)gnu_linker_ccm_bss_end() - (uint8_t*)gnu_linker_ccm_bss_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_itcm_data_start() {   extern uint8_t __itcm_data_start__ ;   return &__itcm_data_start__ ; }
inline void*  gnu_linker_itcm_data_end()   {   extern uint8_t __itcm_data_end__ ;     return &__itcm_data_end__ ;  }
inline size_t gnu_linker_itcm_data_size() {   return (uint8_t*)gnu_linker_itcm_data_end() - (uint8_t*)gnu_linker_itcm_data_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_itcm_bss_start() {   extern uint8_t __itcm_bss_start__ ;   return &__itcm_bss_start__ ; }
inline void*  gnu_linker_itcm_bss_end()   {   extern uint8_t __itcm_bss_end__ ;     return &__itcm_bss_end__ ;  }
inline size_t gnu_linker_itcm_bss_size() {   return (uint8_t*)gnu_linker_itcm_bss_end() - (uint8_t*)gnu_linker_itcm_bss_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_dtcm_data_start() {   extern uint8_t __dtcm_data_start__ ;   return &__dtcm_data_start__ ; }
inline void*  gnu_linker_dtcm_data_end()   {   extern uint8_t __dtcm_data_end__ ;     return &__dtcm_data_end__ ;  }
inline size_t gnu_linker_dtcm_data_size() {   return (uint8_t*)gnu_linker_dtcm_data_end() - (uint8_t*)gnu_linker_dtcm_data_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_dtcm_bss_start() {   extern uint8_t __dtcm_bss_start__ ;   return &__dtcm_bss_start__ ; }
inline void*  gnu_linker_dtcm_bss_end()   {   extern uint8_t __dtcm_bss_end__ ;     return &__dtcm_bss_end__ ;  }
inline size_t gnu_linker_dtcm_bss_size() {   return (uint8_t*)gnu_linker_dtcm_bss_end() - (uint8_t*)gnu_linker_dtcm_bss_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_data_start() {   extern uint8_t __data_start__ ;   return &__data_start__ ; }
inline void*  gnu_linker_data_end()   {   extern uint8_t __data_end__ ;     return &__data_end__ ;  }
inline size_t gnu_linker_data_size() {   return (uint8_t*)gnu_linker_data_end() - (uint8_t*)gnu_linker_data_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_bss_start() {   extern uint8_t __bss_start__ ;   return &__bss_start__ ; }
inline void*  gnu_linker_bss_end()   {   extern uint8_t __bss_end__ ;     return &__bss_end__ ;  }
inline size_t gnu_linker_bss_size() {   return (uint8_t*)gnu_linker_bss_end() - (uint8_t*)gnu_linker_bss_start(); }




#ifdef __EXT_MEM_BANK2__
//------------------------------------------------------------------------
inline void*  gnu_linker_ext_mem_bank2_data_start() {   extern uint8_t __ext_mem_bank2_data_start__ ;   return &__ext_mem_bank2_data_start__ ; }
inline void*  gnu_linker_ext_mem_bank2_data_end()   {   extern uint8_t __ext_mem_bank2_data_end__ ;     return &__ext_mem_bank2_data_end__ ;  }
inline size_t gnu_linker_ext_mem_bank2_data_size() {   return (uint8_t*)gnu_linker_ext_mem_bank2_data_end() - (uint8_t*)gnu_linker_ext_mem_bank2_data_start(); }
//------------------------------------------------------------------------
inline void*  gnu_linker_ext_mem_bank2_bss_start() {   extern uint8_t __ext_mem_bank2_bss_start__ ;   return &__ext_mem_bank2_bss_start__ ; }
inline void*  gnu_linker_ext_mem_bank2_bss_end()   {   extern uint8_t __ext_mem_bank2_bss_end__ ;     return &__ext_mem_bank2_bss_end__ ;  }
inline size_t gnu_linker_ext_mem_bank2_bss_size() {   return (uint8_t*)gnu_linker_ext_mem_bank2_bss_end() - (uint8_t*)gnu_linker_ext_mem_bank2_bss_start(); }
#endif

//------------------------------------------------------------------------
inline size_t  gnu_linker_build_date() {   extern uint8_t __firmware_build_date__ ;   return (size_t)&__firmware_build_date__ ; }
inline size_t  gnu_linker_build_time() {   extern uint8_t __firmware_build_time__ ;   return (size_t)&__firmware_build_time__ ;  }

#ifdef __cplusplus
	}
#endif

#endif /*__GNU_LINKER_H__*/
