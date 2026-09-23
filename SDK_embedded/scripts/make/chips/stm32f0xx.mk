# дкодирование размера FLASH RAN CCM_RAM

#----- f0 famaly ---------
#STM32F030_set := $(call set_create, STM32F030F4 STM32F030K6 STM32F030C6 STM32F030C8 STM32F030CC STM32F030R8 STM32F030RC )
#STM32F070_set := $(call set_create, STM32F070F6 STM32F070C6 STM32F070CB STM32F070RB )

#CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F030_set)),STM32F030,not_stm32_target)
#ifeq (not_stm32_target,$(CHIP_TARGET))
#	CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F070_set)),STM32F070,not_stm32_target)
#	ifeq (not_stm32_target,$(CHIP_TARGET))
#	   $(error undefined F0 series chip: $(CHIP_TARGET))
#	endif
#endif

#030
#STM32F030_MEMSIZE_16K_set   := $(call set_create,F4 )
#STM32F030_MEMSIZE_32K_set   := $(call set_create,K6 C6 )
#STM32F030_MEMSIZE_64K_set   := $(call set_create,C8 R8 )
#STM32F030_MEMSIZE_256K_set  := $(call set_create,CC RC )

#070
#STM32F070_MEMSIZE_16K_set   := $(call set_create,F4 )
#STM32F070_MEMSIZE_32K_set   := $(call set_create,K6 C6 )


#$(error $(call substr,$(CHIP),10,11))

#ifeq ($(STM32_CHIP_SERIS_CODE),030)
#	ifeq      ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_16K_set)),$(true))
#		RAM_SIZE=96K
#	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_32K_set)),$(true))
#		RAM_SIZE=64K
#	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_64K_set)),$(true))
#		RAM_SIZE=48K
#	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_256K_set)),$(true))
#		RAM_SIZE=20K
#	endif
#else ifeq ($(STM32_CHIP_SERIS_CODE),020)	
    # dummy section for next purpose
#endif

#CHIP_TARGET=STM32F030T8
#RAM_SIZE=4K

CHIP_TARGET=STM32F051K8
RAM_SIZE=8K

	EEPROM_FLASH_SECTOR_A_OFFSET=0x1000
	EEPROM_FLASH_SECTOR_A_SIZE=0x1000
    EEPROM_FLASH_SECTOR_B_OFFSET=0x2000
	EEPROM_FLASH_SECTOR_B_SIZE=0x1000

CPU=CORTEX_M0
# -DSTM32F0 for libopencm3 sensivety code. TODO: get from lobopencm3 scripts
EXT_CHIP_FAMILY_DEF=-DARM_MATH_CM0 -DSTM32F0
CHIP_FAMILY=STM32F0XX
