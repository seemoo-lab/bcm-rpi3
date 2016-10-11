#!/bin/bash
OLD_PWD=$(pwd)
cd $(dirname ${BASH_SOURCE[0]})

if [ -d "$(pwd)/buildtools" ] && [ -d "$(pwd)/firmware_patching" ]; then
 # Compiler for the NexMon firmware
 export CC=$(pwd)/buildtools/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-
 # Compiler for the RPI3 kernel
 export CROSS_COMPILE=$(pwd)/buildtools/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-

 export ARCH=arm
 export KERNEL=kernel7

 export NEXMON_FIRMWARE_PATCHING=$(pwd)/firmware_patching
 export NEXMON_ROOT=$(pwd)

 export NEXMON_SETUP_ENV=1
else
 echo "One or more required folders are missing!"
fi

cd "$OLD_PWD"
