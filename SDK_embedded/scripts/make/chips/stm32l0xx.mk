# дкодирование размера FLASH RAM CCM_RAM

#----- l011xx famaly ---------
STM32L011x3_set := $(call set_create,STM32L011D3 STM32L011F3 STM32L011E3 STM32L011G3 STM32L011K3)
STM32L011x4_set := $(call set_create,STM32L011D4 STM32L011F4 STM32L011E4 STM32L011G4 STM32L011K4)


test_in_set=$(if $(call set_is_member,$(call substr,$(1),1,11),$(2)),yes,no)

ifeq (yes,$(call test_in_set,$(CHIP),$(STM32L011x3_set)))
   CHIP_TARGET:=STM32F011x3
   RAM_SIZE=2K
else ifeq (yes,$(call test_in_set,$(CHIP),$(STM32L011x4_set)))
   CHIP_TARGET:=STM32F011x4
   RAM_SIZE=2K
else   
   $(error $(CHIP) has no CHIP_TARGET, see scripts/make/chips/stm32f7xx.mk file)
endif



#----- f4xx famaly ---------
#ifeq ($(CHIP),STM32F767ZIT6)
#	RAM_SIZE=512K
#	CCM_RAM_SIZE=0K
#else ifeq ($(CHIP),STM32F767II)

#endif

CPU=CORTEX_M0PLUS

EXT_CHIP_FAMILY_DEF=-DARM_MATH_CM0PLUS -D__FPU_PRESENT=0 -DSTM32L0
CHIP_FAMILY=STM32L0XX

