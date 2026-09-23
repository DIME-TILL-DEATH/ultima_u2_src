#! /bin/sh

#используется при крос компиляции mingw32/64
#скрипт читает имя таргета и инсталирует либы в папку сборки архива 

# заходим во временнуб директория для чтения params.sh и host_params.sh
mkdir ./tmp 2>&1
cd    ./tmp 2>&1

TMP_DIR=`pwd`

. ../params.sh

#закодим в директории сборки либ и инсталируем их
# gmp
cd /opt/home/$TARGET/gmp 2>&1
make -j12 install prefix=$DEST 2>&1
# mpfr
cd /opt/home/$TARGET/mpfr 2>&1
make -j12 install prefix=$DEST 2>&1
# mpc
cd /opt/home/$TARGET/mpc 2>&1
make -j12 install prefix=$DEST 2>&1
# isl
cd /opt/home/$TARGET/cloog 2>&1
make -j12 install prefix=$DEST 2>&1
# libusbx
cd /opt/home/$TARGET/libusb 2>&1
make -j12 install prefix=$DEST 2>&1
# expat
cd -j12 /opt/home/$TARGET/expat 2>&1
make install prefix=$DEST 2>&1
# mingw-w64
cd /opt/home/$TARGET/mingw_w64 2>&1
make -j12 install prefix=$DEST 2>&1

# возвращаемся и удаляем временную папку
cd $TMP_DIR/.. 2>&1
rm -fr ./tmp 2>&1
