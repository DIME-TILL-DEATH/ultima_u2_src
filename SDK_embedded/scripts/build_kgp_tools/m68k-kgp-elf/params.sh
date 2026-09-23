#! /bin/sh

TARGET=m68k-kgp-elf
. ../host_params.sh

PLATFORM_GCC_CXXFLAGS_ARG="-fno-exceptions -fno-rtti"
NEWLIB_ARG="--with-newlib --with-headers=../../src/newlib/newlib/libc/include"

PLATFORM_CONFIG_ARGS="--enable-mulilib --disable-shared --disable-threads --disable-libssp --disable-libmudflap --disable-libdecbumber --disable-libquadmath --disable-decimal-float --disable-fixed-point --disable-libgomp --disable-sjlj-exceptions --disable-__cxa_atexit"

NEWLIB_DEFS="-DPREFER_SIZE_OVER_SPEED  -DSMALL_MEMORY"

FLAGS="-pipe -g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite -flto=8 -ffat-lto-objects"

#FLAGS="-flto=8 -ffat-lto-objects"

#if [ -f ../opt.sh ] ; 
#then
#  echo "Using build option from opt.sh "
#  . ../opt.sh
#fi

#for strip.sh & distr.sh
#if [ -f ./opt.sh ] ; 
#then
#  echo "Using build option from opt.sh "
#  . ./opt.sh
#fi
