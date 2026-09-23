#! /bin/sh

# !!! В ОБЫЧНОМ СЛУЧАЕ НЕ ЗАПУСКАЕТСЯ ПРЯМО !!!
# используется скриптом distr.sh 

#используется при крос компиляции arm-kgp-eabi/(win32*win64)
#скрипт читает имя таргета и инсталирует либы в папку сборки архива

# заходим во временнуб директория для чтения params.sh и host_params.sh
mkdir ./tmp 2>&1
cd    ./tmp 2>&1

TMP_DIR=`pwd`

. ../params.sh

echo "copy host/target libs.." 2>&1 

cp /opt/$HOST/bin/libusb-1.0.dll $DEST/bin 2>&1

rm -fr $DEST/arm-kgp-eabi/sys-include 2>&1

#закодим в директории сборки либ и инсталируем их
# newlib
cd /opt/home/$TARGET/newlib 2>&1
make install prefix=$DEST 2>&1

# возвращаемся и удаляем временную папку
cd $TMP_DIR/.. 2>&1
rm -fr ./tmp 2>&1
