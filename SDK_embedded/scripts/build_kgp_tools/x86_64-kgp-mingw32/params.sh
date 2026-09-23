#! /bin/sh

TARGET=x86_64-kgp-mingw32
. ../host_params.sh


PLATFORM="Win x86_64"
PLATFORM_CONFIG_ARGS="--enable-threads=win32 --disable-libstdcxx-threads --without-python"
FLAGS="-g0 -Os -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"
