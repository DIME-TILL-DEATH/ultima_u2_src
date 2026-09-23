#! /bin/sh

. ./params.sh

DEST=/opt/home/$TARGET
SRC=/opt/$TARGET
#RUNTIME_LIB_SRC=/opt/x86_64-kgp-linux-gnu/lib

#SHARED_LIB_LIST='libcloog.so.0 libppl_c.so.4 libppl.so.9 libpwl.so.5 libgmpxx.so.4 libstdc++.so.6 libmpc.so.2 libmpfr.so.4 libgmp.so.10 libgcc_s.so.1 libquadmath.so.0 libgfortran.so.3  libexpat.so.1'

cd $DEST 2>&1
rm -fr ./$TARGET
cp -fr /opt/$TARGET ./

#cd $RUNTIME_LIB_SRC 2>&1
#cp $SHARED_LIB_LIST $DEST/$TARGET/lib64/ 2>&1

cd $DEST 2>&1

ARCH_NAME=$TARGET-linux-x86_64-$(date +%Y%m%d)-$BUILD_NAME.7z

7z a $ARCH_NAME ./$TARGET 2>&1
#tar cf - ./$TARGET  | xz -lz9evv > $ARCH_NAME.tar.xz 2>&1 

wput -v $ARCH_NAME ftp://klen_s:nheitkb64@klen.org:21/Files/DevTools/linux-x86_64/

echo www.klen.org/Files/DevTools/linux-x86_64/$ARCH_NAME

#rm -fr ./$TARGET

