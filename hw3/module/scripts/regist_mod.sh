#!/usr/bin/env bash
echo "7 6 1 7" > /proc/sys/kernel/printk
insmod module.ko
mknod /dev/stopwatch c 242 0
lsmod