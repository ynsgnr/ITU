#!/bin/bash
make
mkdir /lib/modules/$(uname -r)/kernel/drivers/messagebox
cp -r * /lib/modules/$(uname -r)/kernel/drivers/messagebox
depmod -a /lib/modules/$(uname -r)/kernel/drivers/messagebox
modprobe -r messagebox
modprobe messagebox
chown root:chat -R /dev/messagebox
chmod -R g+rwx /dev/messagebox
