LIBNAME = libdisplay

include $(SRC_DIR)/rules.mk

CXXFLAGS += -I./ \
	-I$(SRC_DIR)/include \
	-I$(SRC_DIR)/application \
	-I$(KLIBC_SRC_DIR) \
	-I$(DEVICES_SRC_DIR) \
	-I$(FREERTOS_KERNEL_SRC_DIR)/include \
    -I$(FREERTOS_PORTABLE_SRC_DIR) \
    $(APP_DEFS) \
	$(HARDWARE_DEFS) \
	$(FREERTOS_DEFS)
