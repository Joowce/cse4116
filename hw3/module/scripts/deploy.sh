#!/usr/bin/env bash
target_dir=/data/local/tmp

adb push module.ko ${target_dir}
adb push scripts/regist_mod.sh ${target_dir}