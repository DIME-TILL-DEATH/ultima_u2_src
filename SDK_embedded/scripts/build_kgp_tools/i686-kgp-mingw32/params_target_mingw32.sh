#! /bin/sh

DEST=`pwd`/../"$TARGET"
#_"$HOST"_$(date +%Y%m%d)_$BUILD_NAME

HOST=i686-kgp-mingw32
PLATFORM="Win x86_32"
SRC_PREFIX=../../../..

FLAGS="-g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"
