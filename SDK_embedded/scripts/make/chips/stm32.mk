#таблица соответствия микросхемы 
# !!!!!!! нада сделать!!!!!


#       TYPE_CODE (F)
#           | 
#           | |SERIS_CODE
#           | |
#           | | |PINCOUNT_CODE
#           ||-|| |CASE_CODE:  
#      STM32F405RET6-TEMP_RANGE_CODE
#      |---| |   |
#        |   |   |SIZE_CODE
#  ST_CODE (STM32)
#            |
#            | FAMILY_CODE
#
#
#
#
#

STM32_CHIP_ST_CODE:=$(call substr,$(CHIP),1,5)
STM32_CHIP_TYPE_CODE:=$(call substr,$(CHIP),6,6)

STM32_CHIP_FAMILY_CODE:=$(call substr,$(CHIP),7,7)
STM32_CHIP_SERIS_CODE:=$(call substr,$(CHIP),7,9)
STM32_CHIP_PINCOUNT_CODE:=$(call substr,$(CHIP),10,10)
STM32_FLASH_SIZE_CODE:=$(call substr,$(CHIP),11,11)
STM32_CHIP_CASE_CODE:=$(call substr,$(CHIP),12,12)
STM32_CHIP_TEMP_RANGE_CODE:=$(call substr,$(CHIP),13,13)

#общие для stm32 параметры скрипта линкера
FLASH_ORIGIN=0x08000000

# вычисление размера FLASH
ifeq (I,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=2048K
	#2097152 bytes
else ifeq (G,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=1024K
	#1048576
else ifeq (F,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=768K
	#786432
else ifeq (E,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=512K
	#524288
else ifeq (D,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=384K
	#393216
else ifeq (C,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=256K
	#262144
else ifeq (B,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=128K
	#131072
else ifeq (8,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=64K
	#65536
else ifeq (6,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=32K
	#32768
else ifeq (4,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=16K
	#16384
else ifeq (3,$(STM32_FLASH_SIZE_CODE))
	FLASH_SIZE=8K
	#8192	
else
    $(error KGP BUILD SYSTEM ERROR: Chip $(CHIP) unknown chip FLASH size, modify  /scripts/make/chips/stm32.mk for support this chip)	
endif

# вычисление типа корпуса
ifeq (K,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=QFM32
else ifeq (T,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=QFN36
else ifeq (H,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=QFN40
else ifeq (C,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=LQFP/QFN48
else ifeq (R,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=LQFP/BGA/CSP64
else ifeq (O,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=CSP90
else ifeq (V,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=LQFP/BGA100
else ifeq (Q,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=BGA132
else ifeq (Z,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=LQFP144
else ifeq (I,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=LQFP/UFBGA176
else ifeq (A,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=UFBGA169
else ifeq (F,$(STM32_CHIP_CASE_CODE))
	CHIP_CASE=TSSOP20_UFQFPN20
endif

# вычисление температурного диапазона
ifeq (6,$(STM32_CHIP_TEMP_RANGE_CODE))
	CHIP_TEMP_RANGE=-40..085
else ifeq (7,$(STM32_CHIP_CASE_CODE))
    CHIP_TEMP_RANGE=-40..105
endif

#параметры скрипта линкера по микросхеме
ifeq ($(STM32_CHIP_TYPE_CODE),F)
   ifeq ($(STM32_CHIP_FAMILY_CODE),7)
	   include $(SDK_DIR)/scripts/make/chips/stm32f7xx.mk
	   ITCM_SRAM_ORIGIN=0x00000000
	   ITCM_SRAM_SIZE=16K
   else ifeq ($(STM32_CHIP_FAMILY_CODE),4)
	   include $(SDK_DIR)/scripts/make/chips/stm32f4xx.mk
	   CCM_SRAM_ORIGIN=0x10000000
       SRAM_ORIGIN=0x20000000
   else ifeq ($(STM32_CHIP_FAMILY_CODE),3)
	   include $(SDK_DIR)/scripts/make/chips/stm32f3xx.mk
       SRAM_ORIGIN=0x20000000
   else ifeq ($(STM32_CHIP_FAMILY_CODE),2)
	   include $(SDK_DIR)/scripts/make/chips/stm32f2xx.mk
       SRAM_ORIGIN=0x20000000
   else ifeq ($(STM32_CHIP_FAMILY_CODE),1)
	   include $(SDK_DIR)/scripts/make/chips/stm32f1xx.mk
       SRAM_ORIGIN=0x20000000
   else ifeq ($(STM32_CHIP_FAMILY_CODE),0)
	   include $(SDK_DIR)/scripts/make/chips/stm32f0xx.mk
       SRAM_ORIGIN=0x20000000
   else
	$(error KGP BUILD SYSTEM ERROR: Chip $(CHIP) unknown family, add chip info to /scripts/make/chips/stm32.mk)
   endif
else  ifeq ($(STM32_CHIP_TYPE_CODE),L)
  ifeq ($(STM32_CHIP_FAMILY_CODE),0)
	   include $(SDK_DIR)/scripts/make/chips/stm32l0xx.mk
       SRAM_ORIGIN=0x20000000
  else
	$(error KGP BUILD SYSTEM ERROR: Chip $(CHIP) unknown family, add chip info to /scripts/make/chips/stm32.mk)
  endif
else  ifeq ($(STM32_CHIP_TYPE_CODE),H)
  ifeq ($(STM32_CHIP_FAMILY_CODE),7)
	   include $(SDK_DIR)/scripts/make/chips/stm32h7xx.mk
  else
	$(error KGP BUILD SYSTEM ERROR: Chip $(CHIP) unknown family, add chip info to /scripts/make/chips/stm32.mk)
  endif  
else
  $(error KGP BUILD SYSTEM ERROR: Chip $(CHIP) unknown type, add chip info to /scripts/make/chips/stm32.mk)
endif




DFU_USB_VIDPID=0483:df11



