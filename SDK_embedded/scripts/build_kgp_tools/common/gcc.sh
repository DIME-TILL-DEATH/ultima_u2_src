#! /bin/sh

if [ -z $LANGUGES  ]
     then 
          LANGUGES="c,c++,lto"
#,fortran
fi
#
# дистр по уморчанию если не указан в скриптах
if [ -z $GCC_SRC_DISTR  ]
     then 
     GCC_SRC_DISTR=gcc
fi

# дистр если указан в параметре командной строки
if [ -n "$1" ]
     then
	GCC_SRC_DISTR="$1"
     	echo use GCC sources $GCC_SRC_DISTR 2>&1
fi

CFLAGS_ARG=$CFLAGS_FOR_TARGET
FCFLAGS_ARG=$FLAGS
CXXFLAGS_ARG="$CXXFLAGS_FOR_TARGET $PLATFORM_GCC_CXXFLAGS_ARG" 
HOST_LIBGCC2_CFLAGS_ARG="$CFLAGS_ARG $PLATFORM_GCC_CXXFLAGS_ARG"
HOST_LIBS_ARG="-static-libstdc++ -lstdc++"

#if [ -z $TARGET  ]
#     then 
#     SYS_ROOT=/
#     else
#     SYS_ROOT=/opt/$TARGET
#fi

$SRC_PREFIX/src/$GCC_SRC_DISTR/configure \
	--with-pic \
	--prefix=$DEST \
	--target=$TARGET \
	--build=$HOST 	\
	--enable-languages=$LANGUGES \
	$GCC_COMMON_CONFIG_ARGS \
	$PLATFORM_CONFIG_ARGS \
	$NEWLIB_ARG \
	--enable-symvers \
	--enable-visibility \
	--with-pkgversion="Klen's GNU package (KGP) for $PLATFORM platform. << $BUILD_NAME >>" \
	-v \
        --enable-nls \
        --enable-plugins --with-plugin-ld=$DEST/bin/$TARGET-ld.bfd
	CFLAGS_FOR_BOOT="$CFLAGS_FOR_BOOT_ARG" \
	CFLAGS_FOR_TARGET="$CFLAGS_ARG" \
	CFLAGS="$CFLAGS_ARG" \
	CXXFLAGS="$CFLAGS_ARG" \
	CXXFLAGS_FOR_TARGET="$CXXFLAGS_ARG" \
	FCFLAGS="$FCFLAGS_ARG" \
	HOST_LIBGCC2_CFLAGS="$HOST_LIBGCC2_CFLAGS_ARG" \
	HOST_LIBS="$HOST_LIBS_ARG" \
        

CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS"   HOST_LIBGCC2_CFLAGS="$HOST_LIBGCC2_CFLAGS_ARG"  LIBGCC2_DEBUG_CFLAGS="$LIBGCC2_DEBUG_CFLAGS" nice -n 19 make -j12 2>&1

make install 2>&1

