#! /bin/sh

DISTR=openocd

CFLAGS_ARG="-g0 -Os -fomit-frame-pointer -funroll-loops -ffunction-sections -fdata-sections -fgraphite -flto=8"
#-flto=8 -static

CONFIG_OPT='--enable-nls --with-ftd2xx-lib=static --enable-ft2232_ftd2xx --enable-jlink --enable-rlink --enable-usb_blaster_ftd2xx --enable-amtjtagaccel --enable-zy1000-master --enable-ioutil --enable-ioutil --enable-stlink --enable-presto_ftd2xx --enable-usbprog --enable-vsllink --enable-ulink --enable-arm-jtag-ew --enable-buspirate --enable-remote-bitbang --disable-werror --enable-maintainer-mode --enable-doxygen-pdf'


$SRC_PREFIX/src/$DISTR/configure --prefix=$DEST --host=$HOST $CONFIG_OPT $CUSTOM_CONFIG_OPT LIBS="$CUSTOM_LIBS" CFLAGS="$CFLAGS_ARG" BUILD_EDITION_NAME="$BUILD_EDITION_NAME"

make CC=gcc $MAKE_PARAMS -j12 2>&1

make install 2>&1
