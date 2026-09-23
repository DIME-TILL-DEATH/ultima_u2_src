#! /bin/sh

mkdir -p tmp 2>&1
cd tmp 2>&1
. ../params.sh
. $SRC_PREFIX/build_kgp_tools/common/opt.sh
cd ../ ; rm -fr tmp  2>&1

if [ ${HOST} = "x86_64-kgp-linux-gnu" ] ; 
then
  DISTR_DIR=/opt/$TARGET
else
  DISTR_DIR=./$TARGET
fi

if [ -f $DISTR_DIR ] ;
then 
  echo "no files for arch!!!" 2>&1
  exit  2>&1
fi

if [ -e ./copy_libs.sh ] ;
then
	. ./copy_libs.sh $DISTR_DIR 2>&1
fi

PKG_NAME=${TARGET}_@_${HOST}_$(date +%Y%m%d)_$BUILD_NAME.7z

if [ -e $PKG_NAME ] ;
then
	echo "archive files already exists!!!" 2>&1
else
	7z a $PKG_NAME $DISTR_DIR/* 2>&1
fi

wput -v $PKG_NAME ftp://klen_s:nheitkb64@klen.org:21/Files/DevTools/$HOST/

echo www.klen.org/Files/DevTools/$HOST/$PKG_NAME

