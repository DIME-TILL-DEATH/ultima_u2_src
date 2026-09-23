# дкодирование размера FLASH RAN CCM_RAM

#----- f1xx famaly ---------
STM32F100xB_set := $(call set_create,STM32F100C4 STM32F100R4 STM32F100C6 STM32F100R6 STM32F100C8 STM32F100R8 STM32F100V8 STM32F100CB STM32F100RB STM32F100VB)
STM32F100xE_set := $(call set_create,STM32F100RC STM32F100VC STM32F100ZC STM32F100RD STM32F100VD STM32F100ZD STM32F100RE STM32F100VE STM32F100ZE)
STM32F101x6_set := $(call set_create,STM32F101C4 STM32F101R4 STM32F101T4 STM32F101C6 STM32F101R6 STM32F101T6)
STM32F101xB_set := $(call set_create,STM32F101C8 STM32F101R8 STM32F101T8 STM32F101V8 STM32F101CB STM32F101RB STM32F101TB STM32F101VB)
STM32F101xE_set := $(call set_create,STM32F101RC STM32F101VC STM32F101ZC STM32F101RD STM32F101VD STM32F101ZD STM32F101RE STM32F101VE STM32F101ZE)
STM32F101xG_set := $(call set_create,STM32F101RF STM32F101VF STM32F101ZF STM32F101RG STM32F101VG STM32F101ZG)
STM32F102x6_set := $(call set_create,STM32F102C4 STM32F102R4 STM32F102C6 STM32F102R6)
STM32F102xB_set := $(call set_create,STM32F102C8 STM32F102R8 STM32F102CB STM32F102RB)
STM32F103x6_set := $(call set_create,STM32F103C4 STM32F103R4 STM32F103T4 STM32F103C6 STM32F103R6 STM32F103T6)
STM32F103xB_set := $(call set_create,STM32F103C8 STM32F103R8 STM32F103T8 STM32F103V8 STM32F103CB STM32F103RB STM32F103TB STM32F103VB)
STM32F103xE_set := $(call set_create,STM32F103RC STM32F103VC STM32F103ZC STM32F103RD STM32F103VD STM32F103ZD STM32F103RE STM32F103VE STM32F103ZE)
STM32F103xG_set := $(call set_create,STM32F103RF STM32F103VF STM32F103ZF STM32F103RG STM32F103VG STM32F103ZG)
STM32F105xC_set := $(call set_create,STM32F105R8 STM32F105V8 STM32F105RB STM32F105VB STM32F105RC STM32F105VC)
STM32F107xC_set := $(call set_create,STM32F107RB STM32F107VB STM32F107RC STM32F107VC)

CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F100xB_set)),STM32F100xB,not_stm32_target)
ifeq (not_stm32_target,$(CHIP_TARGET))
	CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F100xE_set)),STM32F100xE,not_stm32_target)
	ifeq (not_stm32_target,$(CHIP_TARGET))
		CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F101x6_set)),STM32F101x6,not_stm32_target)
		ifeq (not_stm32_target,$(CHIP_TARGET))
			CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F101xB_set)),STM32F101xB,not_stm32_target)
			ifeq (not_stm32_target,$(CHIP_TARGET))
				CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F101xE_set)),STM32F101xE,not_stm32_target)
				ifeq (not_stm32_target,$(CHIP_TARGET))
					CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F101xG_set)),STM32F101xG,not_stm32_target)
					ifeq (not_stm32_target,$(CHIP_TARGET))
						CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F102x6_set)),STM32F102x6,not_stm32_target)
						ifeq (not_stm32_target,$(CHIP_TARGET))
							CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F102xB_set)),STM32F102xB,not_stm32_target)
							ifeq (not_stm32_target,$(CHIP_TARGET))
								CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F103x6_set)),STM32F103x6,not_stm32_target)
								ifeq (not_stm32_target,$(CHIP_TARGET))
									CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F103xB_set)),STM32F103xB,not_stm32_target)
									ifeq (not_stm32_target,$(CHIP_TARGET))
										CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F103xE_set)),STM32F103xE,not_stm32_target)
										ifeq (not_stm32_target,$(CHIP_TARGET))
											CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F103xG_set)),STM32F103xG,not_stm32_target)
											ifeq (not_stm32_target,$(CHIP_TARGET))
												CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F105xC_set)),STM32F105xC,not_stm32_target)
												ifeq (not_stm32_target,$(CHIP_TARGET))
													CHIP_TARGET:=$(if $(call set_is_member, $(call substr,$(CHIP),1,11) ,$(STM32F107xC_set)),STM32F107xC,not_stm32_target)
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
	endif
endif

#105/107
# all chips has a 64K RAM

# 103
STM32F103_MEMSIZE_96K_set  := $(call set_create,RF RG VF VG ZF ZG )
STM32F103_MEMSIZE_64K_set  := $(call set_create,RD RE VD VE ZD ZE)
STM32F103_MEMSIZE_48K_set  := $(call set_create,RC VC ZC)
STM32F103_MEMSIZE_20K_set  := $(call set_create,C8 CB R8 RB T8 TB V8 VB)
STM32F103_MEMSIZE_10K_set  := $(call set_create,C6 R6 T6)
STM32F103_MEMSIZE_6K_set   := $(call set_create,C4 R4 T4)

#102
STM32F102_MEMSIZE_16K_set  := $(call set_create,CB RB)
STM32F102_MEMSIZE_10K_set  := $(call set_create,C8 R8)
STM32F102_MEMSIZE_6K_set   := $(call set_create,C6 R6)
STM32F102_MEMSIZE_4K_set   := $(call set_create,C4 R4)

#101
STM32F101_MEMSIZE_80K_set  := $(call set_create,RF RG VF FG ZF ZG)
STM32F101_MEMSIZE_48K_set  := $(call set_create,RD RE VD VE ZD ZE)
STM32F101_MEMSIZE_32K_set  := $(call set_create,RC VC ZC)
STM32F101_MEMSIZE_16K_set  := $(call set_create,CB RB TB VB)
STM32F101_MEMSIZE_10K_set  := $(call set_create,C8 R8 T8 V8)
STM32F101_MEMSIZE_6K_set   := $(call set_create,C6 R6 T6)
STM32F101_MEMSIZE_4K_set   := $(call set_create,R4 T4)

#100
STM32F100_MEMSIZE_32K_set  := $(call set_create,RD RE VD VE ZD ZE)
STM32F100_MEMSIZE_24K_set  := $(call set_create,RC VC ZC)
STM32F100_MEMSIZE_8K_set   := $(call set_create,C8 CB R8 RB V8 VB)
STM32F100_MEMSIZE_4K_set   := $(call set_create,C4 C6 R4 R6)

#$(error $(call substr,$(CHIP),10,11))

ifeq ($(STM32_CHIP_SERIS_CODE),107)
	RAM_SIZE=64K
else ifeq ($(STM32_CHIP_SERIS_CODE),105)
	RAM_SIZE=64K
else ifeq ($(STM32_CHIP_SERIS_CODE),103)
	ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_96K_set)),$(true))
		RAM_SIZE=96K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_64K_set)),$(true))
		RAM_SIZE=64K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_48K_set)),$(true))
		RAM_SIZE=48K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_20K_set)),$(true))
		RAM_SIZE=20K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_10K_set)),$(true))
		RAM_SIZE=10K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F103_MEMSIZE_6K_set)),$(true))
		RAM_SIZE=6K
	endif
else ifeq ($(STM32_CHIP_SERIS_CODE),102)
	ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F102_MEMSIZE_16K_set)),$(true))
		RAM_SIZE=16K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F102_MEMSIZE_10K_set)),$(true))
		RAM_SIZE=10K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F102_MEMSIZE_6K_set)),$(true))
		RAM_SIZE=6K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F102_MEMSIZE_4K_set)),$(true))
		RAM_SIZE=4K
	endif
else ifeq ($(STM32_CHIP_SERIS_CODE),101)	
	ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_80K_set)),$(true))
		RAM_SIZE=80K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_48K_set)),$(true))
		RAM_SIZE=48K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_32K_set)),$(true))
		RAM_SIZE=32K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_16K_set)),$(true))
		RAM_SIZE=16K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_10K_set)),$(true))
		RAM_SIZE=10K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_6K_set)),$(true))
		RAM_SIZE=6K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F101_MEMSIZE_4K_set)),$(true))
		RAM_SIZE=4K
	endif
else ifeq ($(STM32_CHIP_SERIS_CODE),100)	
	ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F100_MEMSIZE_32K_set)),$(true))
		RAM_SIZE=32K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F100_MEMSIZE_24K_set)),$(true))
		RAM_SIZE=24K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F100_MEMSIZE_8K_set)),$(true))
		RAM_SIZE=8K
	else ifeq ($(call set_is_member, $(call substr,$(CHIP),10,11) ,$(STM32F100_MEMSIZE_4K_set)),$(true))
		RAM_SIZE=4K
	endif
endif

CPU=CORTEX_M3
# -DSTM32F1 for libopencm3 sensivety code. TODO: get from lobopencm3 scripts
EXT_CHIP_FAMILY_DEF=-DARM_MATH_CM3 -DSTM32F1
CHIP_FAMILY=STM32F1XX
