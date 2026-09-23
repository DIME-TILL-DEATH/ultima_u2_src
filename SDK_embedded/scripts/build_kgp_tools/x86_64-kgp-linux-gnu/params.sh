#! /bin/sh

TARGET=x86_64-kgp-linux-gnu
HOST=$TARGET
DEST=/opt/$TARGET

PLATFORM="Linux x86_64"
SRC_PREFIX=../..

PLATFORM_CONFIG_ARGS="--disable-libsanitizer --disable-libssp --disable-libmpx --disable-multilib --enable-libquadmath --disable-decimal-float --disable-fixed-point --with-pic"

FLAGS="-g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite -fPIC"

CFLAGS="$FLAGS"

CXXFLAGS="$FLAGS"

CFLAGS_FOR_TARGET="$FLAGS"

CXXFLAGS_FOR_TARGET="$FLAGS"
