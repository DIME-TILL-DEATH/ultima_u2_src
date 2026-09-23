#! /bin/sh

DEST=/opt/$TARGET
HOST=x86_64-kgp-linux-gnu
PLATFORM="$HOST"
SRC_PREFIX=../..

#---DFU-UTIL option---
DFU_UTIL_CUSTOM_LIBS="-lrt -lusb-1.0 -ludev -lpthread"
DFU_UTIL_CUSTOM_INCDIR="-I/opt/x86_64-kgp-linux-gnu/include/libusb-1.0"

