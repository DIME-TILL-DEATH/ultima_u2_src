#! /bin/sh

#DEST=`pwd`/../"$TARGET"_$(date +%Y%m%d)_$BUILD_NAME
DEST=`pwd`/../"$TARGET"

HOST=x86_64-kgp-mingw32
PLATFORM="Win x86_64"
SRC_PREFIX=../../../..

FLAGS="-g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"

