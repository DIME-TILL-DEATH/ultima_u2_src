#! /bin/sh

CFLAGS="$CFLAGS_COMMON_OPT $OPT"

# дистр по уморчанию
if [ -z $BU_SRC_DISTR  ]
     then 
     BU_SRC_DISTR=bu-gdb
fi

# warning --with-sysroot=/opt/$TARGET небыло в arm-kgp-eabi

if [ -z $TARGET  ]
     then 
     SYS_ROOT=/
     else
     SYS_ROOT=/opt/$TARGET
fi


$SRC_PREFIX/src/$BU_SRC_DISTR/configure \
	--with-sysroot=$SYS_ROOT \
	--prefix=$DEST \
	--target=$TARGET  \
	--build=$HOST \
	$BU_COMMON_CONFIG_ARGS \
	CFLAGS="$CFLAGS" \
	--with-pkgversion="Klen's GNU package (KGP) for $TARGET platform. << $BUILD_NAME >>"  \
	$BU_CONFIG_OPT \
	-v  2>&1

if [ "$HOST"=="x86_64-kgp-mingw32" ]
	then
	mkdir -p binutils 2>&1
	ln -sf /opt/x86_64-kgp-mingw32/bin/x86_64-kgp-mingw32-windres binutils/windres
fi

nice -n 19 make $MAKE_ARG -j12 2>&1

make install 2>&1






 
