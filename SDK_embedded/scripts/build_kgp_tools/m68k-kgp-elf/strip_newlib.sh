#! /bin/sh

mkdir -p tmp 2>&1
cd tmp 2>&1
. ../params.sh
. $SRC_PREFIX/build_scripts/common/opt.sh
cd ../ ; rm -fr tmp  2>&1


#чистка библиотек
#фильтр файлов libc libg
LIB_DIR=$DEST/$TARGET/lib


REMOBJS_FILTER='printf|scanf|impure|malloc|free|putc|puts|getc|putw|getc|gets|getw|impure|fflush|fclose|syscalls|readr|lseakr|isattyr|findfp|closer|writer|strerror|refill|openr|makebuf|fstatr|freopen|fseek|ferror|feof|ftell|fopen|errno|fread|fwrite|fgetc|fputs|fputc|fgets|fprintf|fscanf|fungetc|rget|tmpfile|tmpnam|fdopen|signal|stdio|unlink|seek|tell|setvbuf|strtod|time|rand|srand|clearerr|_lseek_r|_isatty_r|_write_r'



TARGET=thumb/cortex-m4f
LIBG=$LIB_DIR/$TARGET/libg.a
LIBC=$LIB_DIR/$TARGET/libc.a
rm $LIBC
arm-kgp-eabi-ar d $LIBG `arm-kgp-eabi-ar t $LIBG | grep -E $REMOBJS_FILTER` 2>&1
cp  $LIBG $LIBC

TARGET=thumb/cortex-m3
LIBG=$LIB_DIR/$TARGET/libg.a
LIBC=$LIB_DIR/$TARGET/libc.a
rm $LIBC
arm-kgp-eabi-ar d $LIBG `arm-kgp-eabi-ar t $LIBG | grep -E $REMOBJS_FILTER` 2>&1
cp  $LIBG $LIBC

TARGET=thumb/thumb2
LIBG=$LIB_DIR/$TARGET/libg.a
LIBC=$LIB_DIR/$TARGET/libc.a
rm $LIBC
arm-kgp-eabi-ar d $LIBG `arm-kgp-eabi-ar t $LIBG | grep -E $REMOBJS_FILTER` 2>&1
cp  $LIBG $LIBC

TARGET=thumb
LIBG=$LIB_DIR/$TARGET/libg.a
LIBC=$LIB_DIR/$TARGET/libc.a
rm $LIBC
arm-kgp-eabi-ar d $LIBG `arm-kgp-eabi-ar t $LIBG | grep -E $REMOBJS_FILTER` 2>&1
cp  $LIBG $LIBC

TARGET=.
LIBG=$LIB_DIR/$TARGET/libg.a
LIBC=$LIB_DIR/$TARGET/libc.a
rm $LIBC
arm-kgp-eabi-ar d $LIBG `arm-kgp-eabi-ar t $LIBG | grep -E $REMOBJS_FILTER` 2>&1
cp  $LIBG $LIBC







