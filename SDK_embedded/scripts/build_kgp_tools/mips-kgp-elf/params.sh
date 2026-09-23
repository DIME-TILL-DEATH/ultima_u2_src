#! /bin/sh

TARGET=mips-kgp-elf
. ../host_params.sh

BU_CONFIG_OPT="--disable-sim"

PLATFORM_GCC_CXXFLAGS_ARG="-fno-exceptions -fno-rtti"
NEWLIB_ARG="--with-newlib --with-headers=../../src/newlib/newlib/libc/include"

PLATFORM_CONFIG_ARGS="--enable-mulilib --enable-interwork --disable-shared --disable-threads --with-float=soft --disable-libssp --disable-libmudflap --disable-libgomp --disable-sjlj-exceptions --disable-__cxa_atexit --enable-fixed-point --enable-decimal-float=yes --enable-libquadmath"


NEWLIB_DEFS="-DPREFER_SIZE_OVER_SPEED  -DSMALL_MEMORY"

FLAGS="-pipe -g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"

#add LTO options
FLAGS="$FLAGS -flto=8 -ffat-lto-objects"

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
