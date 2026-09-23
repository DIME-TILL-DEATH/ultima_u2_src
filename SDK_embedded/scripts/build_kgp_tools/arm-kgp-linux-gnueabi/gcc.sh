#! /bin/sh

if [ -z $LANGUGES  ]
     then 
     LANGUGES=c,c++,lto,fortran
fi

COMMON_CONFIG_ARGS="--with-ppl --with-cloog --disable-libstdcxx-debug --disable-libstdcxx-pch --enable-nls --enable-plugins --enable-libquadmath --enable-fixed-point --enable-lto --enable-gold"

PLATFORM_CONFIG_ARGS="--enable-mulilib --enable-interwork --disable-shared --enable-threads=posix --with-arch=armv7-a --with-tune=cortex-a9 --with-fpu=vfpv3-d16 --with-float=softfp --disable-sjlj-exceptions --with-demangler-in-ld --enable-static  --disable-shared"

LIBS_ARG="--with-headers=$DEST/$TARGET/include  --libdir=$DEST/$TARGET/lib"

FLAGS="-g0 -Os -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite -flto -fPIC"

#if [ -f ./custom_gcc_opt.sh ] ; 
#then 
#  . ./custom_gcc_opt.sh
#fi

CFLAGS_FOR_BOOT_ARG=$FLAGS
CFLAGS_ARG=$FLAGS
CXXFLAGS_ARG="$FLAGS -fno-exceptions"
HOST_LIBGCC2_CFLAGS_ARG='$FLAGS -fno-exceptions -fno-rtti'
FCFLAGS_ARG=$FLAGS

$SRC_PREFIX/src/gcc/configure --prefix=$DEST --target=$TARGET --host=$HOST --enable-languages=$LANGUGES $COMMON_CONFIG_ARGS $PLATFORM_CONFIG_ARGS $LIBS_ARG --enable-symvers --enable-visibility --with-pkgversion="Klen's GNU package (KGP) for ARMv7/elf platform" -v CFLAGS_FOR_BOOT="$CFLAGS_FOR_BOOT_ARG" CFLAGS="$CFLAGS_ARG" CXXFLAGS="$CXXFLAGS_ARG" HOST_LIBGCC2_CFLAGS="$HOST_LIBGCC2_CFLAGS_ARG" FCFLAGS="$FCFLAGS_ARG"

make $MAKE_ARGS -j12 2>&1

make install 2>&1

