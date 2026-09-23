#! /bin/sh

mkdir -p tmp 2>&1
cd tmp 2>&1
. ../params.sh
. $SRC_PREFIX/build_kgp_tools/common/opt.sh
cd ../ ; 

"$HOST"-strip $DEST/bin/* 2>&1
"$HOST"-strip $DEST/$TARGET/bin/* 2>&1
"$HOST"-strip $DEST/libexec/gcc/*/*/* 2>&1

rm -fr tmp  2>&1



