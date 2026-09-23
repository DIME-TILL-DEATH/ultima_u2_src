static const char *const multilib_raw[] = {
// cortex-r4
"thumb/cortex-r4 !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os !Ofast !flto;",
"thumb/cortex-r4.lto !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os !Ofast flto;",
"thumb/cortex-r4.O2 !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 O2 !Os !Ofast !flto;",
"thumb/cortex-r4.O2.lto !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 O2 !Os !Ofast flto;",
"thumb/cortex-r4.Os !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 Os !Ofast !flto;",
"thumb/cortex-r4.Os.lto !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 Os !Ofast flto;",
"thumb/cortex-r4.Ofast !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os Ofast !flto;",
"thumb/cortex-r4.Ofast.lto !marm mthumb march=armv7-r !mfloat-abi=hard !mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os Ofast flto;",

"thumb/cortex-r4.fpu !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os !Ofast !flto",
"thumb/cortex-r4.fpu.lto !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os !Ofast flto;",
"thumb/cortex-r4.fpu.O2 !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 O2 !Os !Ofast !flto",
"thumb/cortex-r4.fpu.O2.lto !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 O2 !Os !Ofast flto;",
"thumb/cortex-r4.fpu.Os !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 Os !Ofast !flto;",
"thumb/cortex-r4.fpu.Os.lto !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 Os !Ofast flto;",
"thumb/cortex-r4.fpu.Ofast !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os Ofast !flto;",
"thumb/cortex-r4.fpu.Ofast.lto !marm mthumb march=armv7-r mfloat-abi=hard mfpu=vfpv3-d16 mcpu=cortex-r4 !mcpu=cortex-r5 !mcpu=cortex-r7 !mcpu=cortex-r8 !O2 !Os Ofast flto;",
/*
// cortex-r5


// cortex-r7


// cortex-r8

*/
NULL
};

static const char *const multilib_reuse_raw[] = {
NULL
};

static const char *const multilib_matches_raw[] = {

"marm marm;",
"mthumb mthumb;",

"mfloat-abi=hard mfloat-abi=hard;",

"mfpu=vfpv3-d16 mfpu=vfpv3-d16;",

"march=armv7-r march=armv7-r;",
 
"mcpu=cortex-r4 mcpu=cortex-r4;",
"mcpu=cortex-r5 mcpu=cortex-r5;",
"mcpu=cortex-r7 mcpu=cortex-r7;",      
"mcpu=cortex-r8 mcpu=cortex-r8;",    

"O2 O2;",
"Os Os;",
"Ofast Ofast;",

"flto flto;",

NULL
};

static const char *multilib_extra = "";

static const char *const multilib_exclusions_raw[] = {
NULL
};

static const char *multilib_options = "marm/mthumb \
                                       march=armv7-r \
                                       mfpu=vfpv3-d16 \
                                       mfloat-abi=hard \
                                       mcpu=cortex-r4/mcu=cortex-r5/mcpu=cortex-r7/mcpu=cortex-r8 \
                                       flto \
                                       O2/Os/Ofast";
