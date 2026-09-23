#! /bin/sh

CONFIG_ARG='--enable-interwork 
            --enable-multilib  
            --disable-newlib-atexit-alloc 
            --enable-newlib-multithread  
            --disable-newlib-supplied-syscalls 
            --enable-newlib-mb 
            --disable-werror 
            --disable-newlib-io-pos-args 
            --disable-newlib-io-c99-formats  
            --enable-target-optspace'



#--enable-newlib-reent-small

if [ "$1" = nano  ]
     then 
     	echo use newlib-nano-2 sources  2>&1
	NEWLIB_SRC_DIR=newlib-nano-2
     else
     	if [ -z $1 ]
             then
                echo use native newlib sources  2>&1
	        NEWLIB_SRC_DIR=newlib
             else
                echo use "$1" newlib sources  2>&1
	        NEWLIB_SRC_DIR="$1"
        fi
fi

$SRC_PREFIX/src/$NEWLIB_SRC_DIR/configure --prefix=$DEST --target=$TARGET $CONFIG_ARG CFLAGS="$FLAGS  $NEWLIB_DEFS" -v 

nice -9 make -j12 2>&1

make install 2>&1


