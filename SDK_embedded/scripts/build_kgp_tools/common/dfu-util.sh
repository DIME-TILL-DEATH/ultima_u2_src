#! /bin/bash

#BUILD_STRING="$KGP_STRING $TARGET/$HOST $BUILD_NAME $(date +%Y%m%d)"
BUILD_STRING="$BUILD_NAME"

CFLAGS_ARG="-g0 -Os -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite -DBUILD_STRING=\"\\\"$BUILD_STRING\"\\\""
$SRC_PREFIX/src/dfu-util/configure --prefix=$DEST --host=$HOST $CONFIG_OPT $DFU_UTIL_CUSTOM_CONFIG_OPT  LIBS="$DFU_UTIL_CUSTOM_LIBS"  CFLAGS="$CFLAGS_ARG $DFU_UTIL_CUSTOM_INCDIR" -v 

nice -n 19 make $MAKE_PARAMS -j12 V=1 2>&1

make install 2>&1
