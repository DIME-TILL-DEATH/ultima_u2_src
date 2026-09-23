#! /bin/sh

TARGET=armv7l-kgp-linux-gnueabihf
. ../host_params.sh

PLATFORM_GCC_CXXFLAGS_ARG="-fno-exceptions -fno-rtti"

PLATFORM_CONFIG_ARGS="--with-cpu=cortex-a9 --with-fpu=vfpv3-d16 --with-float=hard --with-mode=thumb --disable-werror --disable-mulilib --enable-interwork --disable-shared --enable-threads=posix --disable-libssp --disable-libmudflap --disable-libgomp --disable-sjlj-exceptions --disable-__cxa_atexit"

#multilib control 
#PLATFORM_CONFIG_ARGS="$PLATFORM_CONFIG_ARGS --with-multilib-list=thumb/thumb2"


FLAGS="-pipe -g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"




#add LTO options
if [ $HOST != x86_64-kgp-mingw32 ]
then
   if [ $HOST != i686-kgp-mingw32 ]
   then
	echo "Using build option with LTO optimisation"
	FLAGS="$FLAGS -flto=8 -ffat-lto-objects"
   fi
fi

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
