include $(SRC_DIR)/rules.mk

LIB_FLAGS=	-I./ \
		    -I$(SRC_DIR)/include \
            -I$(STM32_CRT2_SRC_DIR)	\
        	-I$(KLIBC_SRC_DIR) \
        	-I$(TLSF_SRC_DIR) \
            -I$(FREERTOS_KERNEL_SRC_DIR)/include \
		    -I$(FREERTOS_PORTABLE_SRC_DIR) \
		    -I$(MMGR_SRC_DIR) \
            -I$(KLEN_INLINED_SRC_DIR) \
            -I$(HASH_SRC_DIR) \
            -I$(TINY_AES128_SRC_DIR) \
            -I$(FATFS_SRC_DIR) \
            -I$(TINY_AES128_SRC_DIR) \
            -I$(DEVICES_SRC_DIR) \
            -I$(SRC_DIR)/libstorage \
            -I$(SRC_DIR)/libdisplay \
            -I$(SRC_DIR)/libusb \
            -I$(SRC_DIR)/libusb/usbdev/core \
            -I$(SRC_DIR)/libusb/usbdev/class/msc \
			$(APP_DEFS) \
			$(HARDWARE_DEFS) \
			$(FREERTOS_DEFS) \
			$(MEM_POOLS_DEFS)

CXXFLAGS += $(LIB_FLAGS)
CFLAGS += $(LIB_FLAGS)

LIBS =

LD_EXT_FLAGS=


CUSTOM_RM_FILES=$(OUT_DIR)/image.*





