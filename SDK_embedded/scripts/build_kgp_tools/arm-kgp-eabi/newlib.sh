#! /bin/sh

CONFIG_ARG="
--disable-werror 
--enable-interwork 
--enable-multilib 
--enable-lite-exit 
--disable-newlib-supplied-syscalls 
--disable-newlib-atexit-alloc 
--enable-newlib-mb 
--disable-newlib-io-pos-args 
--disable-newlib-io-c99-formats 
--enable-newlib-multithread 
--enable-newlib-reent-small"


NANO_ARG="  --enable-newlib-nano-formatted-io 
            --enable-newlib-global-atexit 
            --disable-newlib-unbuf-stream-opt 
            --enable-newlib-reent-small 
	    --disable-newlib-fvwrite-in-streamio 
	    --disable-newlib-fseek-optimization 
	    --disable-newlib-wide-orient 
	    --enable-newlib-nano-malloc 
	    --disable-newlib-unbuf-stream-opt 
            --enable-target-optspace"

#if [ "$1" = nano  ]
     #then 
     #	echo use newlib-nano-2 sources  2>&1
     #	NEWLIB_SRC_DIR=newlib-nano-2
     #else
     #	if [ -z $1 ]
     #        then
     #           echo use native newlib sources  2>&1
     #	        NEWLIB_SRC_DIR=newlib
     #        else
     #           echo use "$1" newlib sources  2>&1
     #	        NEWLIB_SRC_DIR="$1"
     #   fi
#then
        #$CONFIG_ARG = "$COMMON_ARG $NANO_CONFIG_ARG"
        #$FLAGS = "$FLAGS -Os --disable-unroll-loop"
#fi

NEWLIB_SRC_DIR=newlib

AR_FOR_TARGET="arm-kgp-eabi-gcc-ar" NM_FOR_TARGET="arm-kgp-eabi-gcc-nm" RANLIB_FOR_TARGET="arm-kgp-eabi-gcc-ranlib" $SRC_PREFIX/src/$NEWLIB_SRC_DIR/configure --prefix=$DEST --target=$TARGET $CONFIG_ARG CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET  $NEWLIB_DEFS" CFLAGS="$CFLAGS_FOR_TARGET  $NEWLIB_DEFS" CCASFLAGS="$CFLAGS_FOR_TARGET  $NEWLIB_DEFS" -v 

nice -n 20 make -j12 2>&1

make install 2>&1


