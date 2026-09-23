static const char *const multilib_raw[] = {
// cortex-m0

// cortex-m0plus

// cortex-m3
"thumb/cortex-m3 !marm mthumb !march=armv6s-m march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp mfloat-abi=soft !mfloat-abi=softfp !mfloat-abi=hard mcpu=cortex-m3 !mcpu=cortex-m4 !mcpu=cortex-m7 mtune=cortex-m3 !mtune=cortex-m4 !mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os !Ofast;",
"thumb/cortex-m3.Os !marm mthumb !march=armv6s-m march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp mfloat-abi=soft !mfloat-abi=softfp !mfloat-abi=hard mcpu=cortex-m3 !mcpu=cortex-m4 !mcpu=cortex-m7 mtune=cortex-m3 !mtune=cortex-m4 !mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 Os !Ofast;",
"thumb/cortex-m3.Ofast !marm mthumb !march=armv6s-m march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp mfloat-abi=soft !mfloat-abi=softfp !mfloat-abi=hard mcpu=cortex-m3 !mcpu=cortex-m4 !mcpu=cortex-m7 mtune=cortex-m3 !mtune=cortex-m4 !mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os Ofast;",

// cortex-m4
"thumb/cortex-m4.hard_float !marm mthumb !march=armv6s-m !march=armv7-m march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 mcpu=cortex-m4 !mcpu=cortex-m7 !mtune=cortex-m3 mtune=cortex-m4 !mtune=cortex-m7 mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os !Ofast;",
"thumb/cortex-m4.hard_float.Os !marm mthumb !march=armv6s-m !march=armv7-m march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 mcpu=cortex-m4 !mcpu=cortex-m7 !mtune=cortex-m3 mtune=cortex-m4 !mtune=cortex-m7 mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 Os !Ofast;",
"thumb/cortex-m4.hard_float.Ofast !marm mthumb !march=armv6s-m !march=armv7-m march=armv7e-m+fp !march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 mcpu=cortex-m4 !mcpu=cortex-m7 !mtune=cortex-m3 mtune=cortex-m4 !mtune=cortex-m7 mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os Ofast;",

// cortex-m7+vfpv5-sp-d16 автоматический ключ ликеру march=armv7e-m+fpv5
"thumb/cortex-m7.hard_float.sp !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os !Ofast;",
"thumb/cortex-m7.hard_float.sp.Os !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 Os !Ofast;",
"thumb/cortex-m7.hard_float.sp.Ofast !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp march=armv7e-m+fpv5 !march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 mfpu=fpv5-sp-d16 !mfpu=fpv5-d16 !Os Ofast;",

// cortex-m7+vfpv5-d16: автоматический ключ ликеру march=armv7e-m+fp.dp
"thumb/cortex-m7.hard_float.dp !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 mfpu=fpv5-d16 !Os !Ofast;",
"thumb/cortex-m7.hard_float.dp.Os !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 mfpu=fpv5-d16 Os !Ofast;",
"thumb/cortex-m7.hard_float.dp.Ofast !marm mthumb !march=armv6s-m !march=armv7-m !march=armv7e-m+fp !march=armv7e-m+fpv5 march=armv7e-m+fp.dp !mfloat-abi=soft !mfloat-abi=softfp mfloat-abi=hard !mcpu=cortex-m3 !mcpu=cortex-m4 mcpu=cortex-m7 !mtune=cortex-m3 !mtune=cortex-m4 mtune=cortex-m7 !mfpu=fpv4-sp-d16 !mfpu=fpv5-sp-d16 mfpu=fpv5-d16 !Os Ofast;",
NULL
};

static const char *const multilib_reuse_raw[] = {
NULL
};

static const char *const multilib_matches_raw[] = {

"marm marm;",
"mthumb mthumb;",

"march=armv6-m march=armv6s-m;",
"march=armv6s-m march=armv6s-m;",

"march=armv7-m march=armv7-m;",

"march=armv7e-m+fp march=armv7e-m+fp;",
"march=armv7e-m+fpv5 march=armv7e-m+fpv5;",
"march=armv7e-m+fp.dp march=armv7e-m+fp.dp;",

"mfloat-abi=soft mfloat-abi=soft;",
"mfloat-abi=softfp mfloat-abi=softfp;",
"mfloat-abi=hard mfloat-abi=hard;",

"mcpu=cortex-m3 mcpu=cortex-m3;",
"mcpu=cortex-m4 mcpu=cortex-m4;",
"mcpu=cortex-m7 mcpu=cortex-m7;",
"mtune=cortex-m3 mtune=cortex-m3;",
"mtune=cortex-m4 mtune=cortex-m4;",
"mtune=cortex-m7 mtune=cortex-m7;",

"mfpu=fpv4-sp-d16 mfpu=fpv4-sp-d16;",
"mfpu=fpv5-sp-d16 mfpu=fpv5-sp-d16;",
"mfpu=fpv5-d16 mfpu=fpv5-d16;",

"Os Os;",
"Ofast Ofast;",

NULL
};

static const char *multilib_extra = "";

static const char *const multilib_exclusions_raw[] = {
NULL
};

static const char *multilib_options = "marm/mthumb march=armv6s-m/march=armv7-m/march=armv7e-m+fp/march=armv7e-m+fpv5/march=armv7e-m+fp.dp mfloat-abi=soft/mfloat-abi=softfp/mfloat-abi=hard mcpu=cortex-m3/mcpu=cortex-m4/mcpu=cortex-m7 mtune=cortex-m3/mtune=cortex-m4/mtune=cortex-m7 mfpu=fpv4-sp-d16/mfpu=fpv5-sp-d16/mfpu=fpv5-d16 Os/Ofast";
