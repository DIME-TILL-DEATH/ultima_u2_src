SDK_STM32_DIR=UNKNOWN_STM32_SDK_DIR

# выбор путей исходников стандартной библиотеки STM32
SDK_STM32_COMMON_DIR=$(SDK_DIR)/libs/common/arch/stm32
ifeq ($(CHIP_FAMILY),STM32L0XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32l0
else ifeq ($(CHIP_FAMILY),STM32L1XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32l1
else ifeq ($(CHIP_FAMILY),STM32F0XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f0
else ifeq ($(CHIP_FAMILY),STM32F1XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f1
else ifeq ($(CHIP_FAMILY),STM32F2XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f2
else ifeq ($(CHIP_FAMILY),STM32F3XX)
	SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f3	
else ifeq ($(CHIP_FAMILY),STM32F4XX)
    SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f4
else ifeq ($(CHIP_FAMILY),STM32F7XX)
    SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32f7
else ifeq ($(CHIP_FAMILY),STM32H7XX)
    SDK_STM32_DIR=$(SDK_DIR)/libs/common/arch/stm32h7
else
    $(error KGP BUILD SYSTEM ERROR: Family of chip $(CHIP) unknown, modify  /scripts/make/chips/stm32.mk for support this chip)	    
endif

LIBOPENCM3_SRC_DIR=$(SDK_DIR)/libs/st/stm32/libopencm3

# hardware depended library HAL
STM32_CRT2_SRC_DIR=$(SDK_DIR)/libs/st/stm32/crt2
STM32_USBD_CORE_SRC_DIR=$(SDK_STM32_DIR)/usb_device/core
STM32_USBD_CDC_SRC_DIR=$(SDK_STM32_DIR)/usb_device/class/cdc
STM32_USBD_CDC_INTERFACE_SRC_DIR=$(SDK_STM32_DIR)/usbd_cdc_interface
STM32_USBD_MSC_SRC_DIR=$(SDK_STM32_DIR)/usb_device/class/msc
STM32_USBD_MSC_INTERFACE_SRC_DIR=$(SDK_STM32_DIR)/usbd_msc_interface
STM32_ETH_DRV_SRC_DIR=$(SDK_STM32_DIR)/ETH_Driver
STM32_SD_HAL_SRC_DIR=$(SDK_STM32_DIR)/libsd_hal

# multihardware library
STM32_CPAL_SRC_DIR=$(SDK_STM32_DIR)/../CPAL
STM32_CMSIS_COMMON_SRC_DIR=$(SDK_STM32_DIR)/../CMSIS
STM32_CRT_COMMON_SRC_DIR=$(SDK_STM32_DIR)/../klen/crt




# выбор путей исходников FreeRTOS/ports/PLUS
FREERTOS_KERNEL_SRC_DIR=$(SDK_DIR)/libs/FreeRTOS/Source
FREERTOS_PLUS_TCP_SRC_DIR=$(SDK_DIR)/libs/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP
ifeq ($(CPU),CORTEX_M0)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM_CM0
else ifeq ($(CPU),CORTEX_M3)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM_CM3
else ifeq ($(CPU),CORTEX_M3_MPU)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM_CM3_MPU
else ifeq ($(CPU),CORTEX_M4F)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM_CM4F
else ifeq ($(CPU),CORTEX_M7)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM_CM7/r0p1
	FREERTOS_PLUS_TCP_POTRABLE_SRC_DIR=$(FREERTOS_PLUS_TCP_SRC_DIR)/portable/NetworkInterface/STM32F7xx
else ifeq ($(CPU),ARM7_LPC2000)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM7_LPC2000
else ifeq ($(CPU),ARM7_LPC2300)
	FREERTOS_PORTABLE_SRC_DIR=$(FREERTOS_KERNEL_SRC_DIR)/portable/GCC/ARM7_LPC23xx
endif



# platfor independed librares

KLEN_INLINED_SRC_DIR=$(SDK_STM32_DIR)/../klen/inlined
WRAPERS_SRC_DIR=$(SDK_DIR)/libs/wrapers
MMGR_SRC_DIR=$(SDK_DIR)/libs/mmgr
KLIBC_SRC_DIR=$(SDK_DIR)/libs/klibc
FATFS_SRC_DIR=$(SDK_DIR)/libs/fatfs/source
I2C_SRC_DIR=$(SDK_STM32_DIR)/../klen/i2c
I2C_GPIO_SRC_DIR=$(SDK_STM32_DIR)/../klen/i2c_gpio
TLSF_SRC_DIR=$(SDK_DIR)/libs/tlsf
READLINE_SRC_DIR=$(SDK_DIR)/libs/readline
LUA_SRC_DIR=$(SDK_DIR)/libs/lua/src
CELT_SRC_DIR=$(SDK_DIR)/libs/celt-0.11.1
VMATH_SRC_DIR=$(SDK_DIR)/libs/vmath
RTCOUNTER_SRC_DIR=$(SDK_DIR)/libs/rtcounter
CONSOLE_SRC_DIR=$(SDK_DIR)/libs/console
CONSOLE_HANDLERS_SRC_DIR=$(SDK_DIR)/libs/console_handlers
FILTER_SRC_DIR=$(SDK_DIR)/libs/filter
ITM_TRACE_SRC_DIR=$(SDK_DIR)/libs/itm_trace
SUNSET_SRC_DIR=$(SDK_DIR)/libs/sunset
TINY_AES128_SRC_DIR=$(SDK_DIR)/libs/tiny_aes128
HASH_SRC_DIR=$(SDK_DIR)/libs/hash
TRE_SRC_DIR=$(SDK_DIR)/libs/tre
DEVICES_SRC_DIR=$(SDK_DIR)/libs/devices
EMFAT_SRC_DIR=$(SDK_DIR)/libs/emfat
LED_SRC_DIR=$(SDK_DIR)/libs/led
FIXMATH_SRC_DIR=$(SDK_DIR)/libs/fixmath/src

