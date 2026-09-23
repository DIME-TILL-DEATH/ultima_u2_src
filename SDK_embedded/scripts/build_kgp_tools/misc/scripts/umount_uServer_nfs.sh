#! /bin/sh

sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/lib 2>&1
sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/opt 2>&1

sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/include 2>&1
sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/lib 2>&1

sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/armv7l-kgp-linux-gnueabihf/include 2>&1
sudo umount /opt/armv7l-kgp-linux-gnueabihf/nfs_shared/usr/armv7l-kgp-linux-gnueabihf/lib 2>&1
