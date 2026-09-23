#! /bin/sh


BU_COMMON_OPT='--enable-nls --enable-multilib --disable-werror --enable-lto --enable-plugins --enable-gold  --enable-static  --disable-shared'

CFLAGS='-g0 -Os -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite'

#if [ -f ./custom_bu_opt.sh ] ; 
#then 
#  . ./custom_bu_opt.sh
#fi

$SRC_PREFIX/src/bu-gdb/configure --prefix=$DEST --target=$TARGET  --host=$HOST $BU_COMMON_OPT CFLAGS="$CFLAGS" --with-pkgversion="Klen's GNU package (KGP) for ARMv7/elf platform" -v  2>&1


make $MAKE_ARG -j12 2>&1

make install 2>&1

