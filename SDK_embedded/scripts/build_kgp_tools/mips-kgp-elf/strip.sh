#! /bin/sh

mkdir -p tmp 2>&1
cd tmp 2>&1
. ../params.sh
. $SRC_PREFIX/build_scripts/common/opt.sh
cd ../ ; rm -fr tmp  2>&1

if [ -z $HOST ] ; 
then
  HOST=linux64
  DISTR_DIR=/opt/$TARGET
else
  DISTR_DIR=./$TARGET
fi

if [ -f ./$TARGET ] ; 
then
  echo "no files for strip!!!" 2>&1
  exit  2>&1
fi

$HOST-strip ./$TARGET/bin/* 2>&1
$HOST-strip ./$TARGET/$TARGET/bin/* 2>&1
$HOST-strip ./$TARGET/libexec/gcc/$TARGET/*/* 2>&1






