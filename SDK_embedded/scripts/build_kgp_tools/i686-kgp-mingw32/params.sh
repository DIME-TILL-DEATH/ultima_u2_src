#! /bin/sh

TARGET=i686-kgp-mingw32
. ../host_params.sh

PLATFORM="Win x86_32"
PLATFORM_CONFIG_ARGS="--enable-threads=win32 --disable-libstdcxx-threads --disable-libssp --disable-fixed-point"
FLAGS="-g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"
