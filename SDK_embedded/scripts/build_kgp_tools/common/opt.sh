#! /bin/sh

BUILD_NAME="CICHORIUM"

CFLAGS_COMMON_OPT="-pipe -g0 -Ofast -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite"
 #-flto=8 -ffat-lto-objects
BU_COMMON_CONFIG_ARGS="--disable-nls \
                       --enable-multilib \
                       --disable-werror \
                       --enable-lto \
                       --enable-plugins \
                       --enable-static  \
                       --disable-shared  \
                       --with-libexpat-prefix=/opt/$HOST \
                       --enable-gold" #-- no compiling GOLD with gcc7 
#                       --with-python=python" 

GCC_COMMON_CONFIG_ARGS="--disable-nls \
			--enable-gold \
			--disable-bootstrap \
			--enable-lto \
			--disable-libstdcxx-debug \
			--disable-libstdcxx-pch 
			--enable-nls \
			--enable-plugins \
			--disable-shared \
			--with-demangler-in-ld \
			--enable-static \
			--enable-symvers \
			--enable-visibility \
			--enable-libdecbumber \
			--enable-libquadmath \
			--enable-decimal-float=yes \
			--enable-version-specific-runtime-libs"
