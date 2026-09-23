include $(SRC_DIR)/rules.mk

LIB_FLAGS=	-I./ \
			-I$(SRC_DIR)/include \
			-I$(STM32_CRT2_SRC_DIR)	\
        	-I$(KLIBC_SRC_DIR) \
        	-I$(MMGR_SRC_DIR) \
            -I$(FREERTOS_KERNEL_SRC_DIR)/include \
            -I$(FREERTOS_PORTABLE_SRC_DIR) \
            -I$(LED_SRC_DIR) \
            -I$(DEVICES_SRC_DIR) \
            -I$(FATFS_SRC_DIR) \
            -I$(SRC_DIR)/libdisplay \
            -I$(SRC_DIR)/libusb \
            -I$(SRC_DIR)/libusb/usbdev/core \
            -I$(SRC_DIR)/libusb/usbdev/class/msc \
            -I$(SRC_DIR)/libst_dsp \
			$(APP_DEFS) \
			$(HARDWARE_DEFS) \
			$(FREERTOS_DEFS)

CXXFLAGS += $(LIB_FLAGS)
CFLAGS += $(LIB_FLAGS)

LIBS =

CUSTOM_RM_FILES=$(OUT_DIR)/image.*






