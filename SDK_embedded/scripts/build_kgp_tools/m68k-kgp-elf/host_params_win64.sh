#! /bin/sh

DEST=`pwd`/../$TARGET
HOST=x86_64-kgp-mingw32
PLATFORM="$HOST"
SRC_PREFIX=../../../..

#---DFU-UTIL option---
DFU_UTIL_CUSTOM_CONFIG_OPT="PKG_CONFIG_PATH=/opt/x86_64-kgp-mingw32/x86_64-kgp-mingw32/lib/pkgconfig"
DFU_UTIL_CUSTOM_LIBS="-lusb-1.0"
DFU_UTIL_CUSTOM_INCDIR="-I/opt/x86_64-kgp-mingw32/x86_64-kgp-mingw32/include/libusb-1.0"

