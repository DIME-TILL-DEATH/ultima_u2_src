#! /bin/sh

TARGET=arm-kgp-eabi
. ../host_params.sh

PLATFORM_GCC_CXXFLAGS_ARG=""
NEWLIB_ARG="--with-newlib --with-headers=../../src/newlib/newlib/libc/include"

#multilib control
PLATFORM_MULTILIB="--with-multilib-list=rmprofile"

PLATFORM_CONFIG_ARGS="--enable-multilib $PLATFORM_MULTILIB --enable-interwork --disable-shared --disable-threads --disable-libssp --disable-libmudflap --disable-libgomp --disable-sjlj-exceptions --disable-__cxa_atexit --disable-io --without-io --enable-fixed-point"
#--disable-libbacktrace 
 

NEWLIB_DEFS="-DPREFER_SIZE_OVER_SPEED  -DSMALL_MEMORY"

CFLAGS_FOR_TARGET="-pipe -Ofast -fomit-frame-pointer -ffunction-sections -fdata-sections -fgraphite -funroll-loops"


LIBGCC2_DEBUG_CFLAGS="$CFLAGS_FOR_TARGET"
 
CXXFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables"

#add LTO options
if [ $HOST != x86_64-kgp-mingw32 ]
then
   if [ $HOST != i686-kgp-mingw32 ]
   then
	echo "Using build option for host with LTO optimisation"

	CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -flto"
#-ffat-lto-objects
        CXXFLAGS_FOR_TARGET="$CXXFLAGS_FOR_TARGET -flto"
#-ffat-lto-objects

        echo "$CXXFLAGS_FOR_TARGET"
   else
        echo "Using build option for host without LTO optimisation"   
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
