# дкодирование размера FLASH RAN CCM_RAM

#----- f4xx famaly ---------
STM32F405xx_set := $(call set_create,STM32F405RG STM32F405VG STM32F405ZG)
STM32F415xx_set := $(call set_create,STM32F415RG STM32F415VG STM32F415ZG)
STM32F407xx_set := $(call set_create,STM32F407VG STM32F407VE STM32F407ZG STM32F407ZE STM32F407IG STM32F407IE)
STM32F417xx_set := $(call set_create,STM32F417VG STM32F417VE STM32F417ZG STM32F417ZE STM32F417IG STM32F417IE)
STM32F427xx_set := $(call set_create,STM32F427VG STM32F427VI STM32F427ZG STM32F427ZI STM32F427IG STM32F427II)
STM32F437xx_set := $(call set_create,STM32F437VG STM32F437VI STM32F437ZG STM32F437ZI STM32F437IG STM32F437II)
STM32F429xx_set := $(call set_create,STM32F429VG STM32F429VI STM32F429ZG STM32F429ZI STM32F429BG STM32F429BI STM32F429NG STM32F439NI STM32F429IG STM32F429II)
STM32F439xx_set := $(call set_create,STM32F439VG STM32F439VI STM32F439ZG STM32F439ZI STM32F439BG STM32F439BI STM32F439NG STM32F439NI STM32F439IG STM32F439II)
STM32F401xC_set := $(call set_create,STM32F401CB STM32F401CC STM32F401RB STM32F401RC STM32F401VB STM32F401VC)
STM32F401xE_set := $(call set_create,STM32F401CD STM32F401RD STM32F401VD STM32F401CE STM32F401RE STM32F401VE)
STM32F411xE_set := $(call set_create,STM32F411CD STM32F411RD STM32F411VD STM32F411CE STM32F411RE STM32F411VE)


CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F405xx_set)),STM32F405xx,not_stm32_target)
ifeq (not_stm32_target,$(CHIP_TARGET))
	CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F415xx_set)),STM32F415xx,not_stm32_target)
	ifeq (not_stm32_target,$(CHIP_TARGET))
		CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F407xx_set)),STM32F407xx,not_stm32_target)
		ifeq (not_stm32_target,$(CHIP_TARGET))
			CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F417xx_set)),STM32F417xx,not_stm32_target)
			ifeq (not_stm32_target,$(CHIP_TARGET))
				CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F427xx_set)),STM32F427xx,not_stm32_target)
				ifeq (not_stm32_target,$(CHIP_TARGET))
					CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F437xx_set)),STM32F437xx,not_stm32_target)
					ifeq (not_stm32_target,$(CHIP_TARGET))
						CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F429xx_set)),STM32F429xx,not_stm32_target)
						ifeq (not_stm32_target,$(CHIP_TARGET))
							CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F439xx_set)),STM32F439xx,not_stm32_target)
							ifeq (not_stm32_target,$(CHIP_TARGET))
								CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F401xC_set)),STM32F401xC,not_stm32_target)
								ifeq (not_stm32_target,$(CHIP_TARGET))
									CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F401xE_set)),STM32F401xE,not_stm32_target)
									ifeq (not_stm32_target,$(CHIP_TARGET))
										CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F411xE_set)),STM32F411xE,not_stm32_target)
										ifeq (not_stm32_target,$(CHIP_TARGET))
											$(error ---QQQQQQ $(CHIP_TARGET))
										endif
									endif
								endif
							endif
						endif
					endif
				endif
			endif
		endif
	endif
endif

#446
#all chips has 128K RAM

#427/429/437/439
#all chips has 256K RAM

#411
#all chips has 128K RAM

#405/407/415/417
#all chips has 192K RAM

#401
STM32F401_MEMSIZE_96K_set := $(call set_create,CD CE RD RE VD VE)
STM32F401_MEMSIZE_64K_set := $(call set_create,CB CC RB RC VB VC)

ifeq ($(STM32_CHIP_SERIS_CODE),446)
	SRAM_SIZE=128K
else ifneq (,$(call findstring,$(STM32_CHIP_SERIS_CODE),427 429 437 439))
	SRAM_SIZE=192K
	CCM_SRAM_SIZE=64K
	
	EEPROM_FLASH_SECTOR_A_OFFSET=0x4000
	EEPROM_FLASH_SECTOR_A_SIZE=0x4000
    EEPROM_FLASH_SECTOR_B_OFFSET=0x8000
	EEPROM_FLASH_SECTOR_B_SIZE=0x4000
	
else ifneq (,$(call findstring,$(STM32_CHIP_SERIS_CODE),411))
	SRAM_SIZE=128K
else ifneq (,$(call findstring,$(STM32_CHIP_SERIS_CODE),405 407 415 417))
	SRAM_SIZE=128K
	CCM_SRAM_SIZE=64K
	
	EEPROM_FLASH_SECTOR_A_OFFSET=0x4000
	EEPROM_FLASH_SECTOR_A_SIZE=0x4000
    EEPROM_FLASH_SECTOR_B_OFFSET=0x8000
	EEPROM_FLASH_SECTOR_B_SIZE=0x4000
	
else ifneq (,$(call findstring,$(STM32_CHIP_SERIS_CODE),401))
	ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F401_MEMSIZE_96K_set)),$(true))
		SRAM_SIZE=96K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F401_MEMSIZE_64K_set)),$(true))
		SRAM_SIZE=64K
	endif
endif

#проверка условий по RCC
ifeq ($(OSC_STATE),RCC_HSE_BYPASS)
   ifeq ($(OSC_TYPE),RCC_OSCILLATORTYPE_HSI)
      $(error KGP BUILD SYSTEM ERROR: Platform $(PLATFORM) with stm32f4xx chip has not config HSI and LSI with state RCC_HSE_BYPASS , fix platform info to /scripts/make/platform.mk (( see stm32f4xx_hal_rcc.h)))
   endif
   ifeq ($(OSC_TYPE),RCC_OSCILLATORTYPE_LSI)
      $(error KGP BUILD SYSTEM ERROR: Platform $(PLATFORM) with stm32f4xx chip has not config HSI and LSI with state RCC_HSE_BYPASS , fix platform info to /scripts/make/platform.mk (( see stm32f4xx_hal_rcc.h)))	
   endif
endif

CPU=CORTEX_M4F
# -DSTM32F4 for libopencm3 sensivety code. TODO: get from lobopencm3 scripts
EXT_CHIP_FAMILY_DEF=-DARM_MATH_CM4 -D__FPU_USED=1 -D__FPU_PRESENT=1 -DSTM32F4
CHIP_FAMILY=STM32F4XX
