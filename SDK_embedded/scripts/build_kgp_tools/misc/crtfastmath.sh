#! /bin/sh

dest=$1


if [ -z $dir ]
then
   dest=crtfastmath
fi

touch tmp.c

mkdir /tmp/$dest
mkdir /tmp/$dest/arm-kgp-eabi
mkdir /tmp/$dest/arm-kgp-eabi/lib

arm-kgp-eabi-gcc tmp.c -c -o /tmp/$dest/arm-kgp-eabi/lib/crtfastmath.o

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb
arm-kgp-eabi-gcc -c tmp.c -mthumb -o /tmp/$dest/arm-kgp-eabi/lib/thumb/crtfastmath.o

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m0
arm-kgp-eabi-gcc -mthumb -mcpu=cortex-m0 -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m0/crtfastmath.o -c tmp.c

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m0plus
arm-kgp-eabi-gcc -mthumb -mcpu=cortex-m0plus -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m0plus/crtfastmath.o -c tmp.c

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m1
arm-kgp-eabi-gcc -mthumb -mcpu=cortex-m1 -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m1/crtfastmath.o -c tmp.c

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m1.small-multiply
arm-kgp-eabi-gcc -mthumb -mcpu=cortex-m1.small-multiply -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m1.small-multiply/crtfastmath.o -c tmp.c

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m3
arm-kgp-eabi-gcc -mthumb -mcpu=cortex-m3 -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m3/crtfastmath.o -c tmp.c

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m4sf
arm-kgp-eabi-gcc tmp.c -c -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m4sf/crtfastmath.o

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m7sf
arm-kgp-eabi-gcc tmp.c -c -mthumb -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m7sf/crtfastmath.o

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m7df
arm-kgp-eabi-gcc tmp.c -c -mthumb -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -o /tmp/$dest/arm-kgp-eabi/lib/thumb/cortex-m7df/crtfastmath.o

mkdir /tmp/$dest/arm-kgp-eabi/lib/thumb/thumb2
arm-kgp-eabi-gcc tmp.c -c -mthumb -march=armv7 -o /tmp/$dest/arm-kgp-eabi/lib/thumb/thumb2/crtfastmath.o

rm tmp.c
