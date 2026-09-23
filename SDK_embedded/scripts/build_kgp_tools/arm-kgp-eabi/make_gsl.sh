#! /bin/sh

# M4_Ofast
cd gsl_float 2>&1
pwd 2>&1

make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fp -mfloat-abi=hard -mcpu=cortex-m4 -mtune=cortex-m4 -mfpu=fpv4-sp-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions" LTCFLAGS="-mthumb -march=armv7e-m+fp -mfloat-abi=hard -mcpu=cortex-m4 -mtune=cortex-m4 -mfpu=fpv4-sp-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions" 2>&1
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m4.hard_float.Ofast 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m4.hard_float.Ofast 2>&1

exit 1

# M4_Os
make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fp -mfloat-abi=hard -mcpu=cortex-m4 -mtune=cortex-m4 -mfpu=fpv4-sp-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite" LTCFLAGS="-mthumb -march=armv7e-m+fp -mfloat-abi=hard -mcpu=cortex-m4 -mtune=cortex-m4 -mfpu=fpv4-sp-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite" 2>&1
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m4.hard_float.Os 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m4.hard_float.Os 2>&1

# M7_sp_Ofast
make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-sp-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions" LTCFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-sp-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions" 2>&1
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.sp.Ofast 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.sp.Ofast 2>&1

# M7_sp_Os
make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-sp-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite" LTCFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-sp-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite" 2>&1
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.sp.Os 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.sp.Os 2>&1

make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions" LTCFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-d16 -pipe -g0 -Ofast -flto=8 -ffunction-sections -fdata-sections -fgraphite -funroll-loops -finline-functions"
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.dp.Ofast 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.dp.Ofast 2>&1

make clean 2>&1
make -j12 CFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite" LTCFLAGS="-mthumb -march=armv7e-m+fpv5 -mfloat-abi=hard -mcpu=cortex-m7 -mtune=cortex-m7 -mfpu=fpv5-d16 -pipe -g0 -Os -flto=8 -ffunction-sections -fdata-sections -fgraphite"
cp .libs/libfgsl.a            /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.dp.Os 2>&1
cp cblas/.libs/libfgslcblas.a /opt/arm-kgp-eabi/arm-kgp-eabi/lib/thumb/cortex-m7.hard_float.dp.Os 2>&1
