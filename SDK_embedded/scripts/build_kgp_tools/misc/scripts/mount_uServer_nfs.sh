#! /bin/sh

sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/lib                             /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/lib 2>&1
                                                                                             
sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/opt                             /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/opt 2>&1

sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/usr/include                     /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/include 2>&1
sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/usr/lib                         /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/lib 2>&1

sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/usr/arm-linux-gnueabihf/include /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/armv7l-kgp-linux-gnueabihf/include 2>&1
sudo mount -t nfs -O uid=1000,iocharset=utf-8 192.168.35.10:/usr/arm-linux-gnueabihf/lib     /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/armv7l-kgp-linux-gnueabihf/lib 2>&1
