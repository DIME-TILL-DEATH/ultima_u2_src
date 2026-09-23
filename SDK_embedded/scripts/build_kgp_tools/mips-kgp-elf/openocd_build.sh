#! /bin/sh

CUSTOM_CONFIG_OPT=
CUSTOM_LIBS="-L/usr/lib/x86_64-linux-gnu -lpthread -lrt"

. ../params.sh

if [ -f ../params_host.sh ] ; 
then 
  . ../params_host.sh
fi

. ../../build_scripts/arm-kgp-eabi/openocd.sh

