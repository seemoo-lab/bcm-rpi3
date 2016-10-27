#!/bin/bash
OLD_PWD=$(pwd)
ARCH=`uname -m`
cd $(dirname ${BASH_SOURCE[0]})

if [ -d "$(pwd)/buildtools" ] && [ -d "$(pwd)/firmware_patching" ] && [ $ARCH != "armv7l" ]; then
 # Compiler for the NexMon firmware
 export CC=$(pwd)/buildtools/gcc-arm-none-eabi-5_4-2016q2_x86/bin/arm-none-eabi-
 # Compiler for the RPI3 kernel
 export CROSS_COMPILE=$(pwd)/buildtools/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-

 export ARCH=arm
 export KERNEL=kernel7

 export NEXMON_FIRMWARE_PATCHING=$(pwd)/firmware_patching
 export NEXMON_ROOT=$(pwd)
 export NEXMON_SETUP_ENV=1
else if [ $ARCH != "armv7l" ]; then
 echo "One or more required folders are missing!"
fi
fi

if [ $ARCH == "armv7l" ]; then
 echo "Raspberry Pi detected, disabling cross-compilation."
 export CC=$(pwd)/buildtools/gcc-arm-none-eabi-5_4-2016q2_arm/bin/arm-none-eabi-
 export NEXMON_FIRMWARE_PATCHING=$(pwd)/firmware_patching
 export NEXMON_SETUP_ENV=1
 export NEXMON_ROOT=$(pwd)
fi

cd "$OLD_PWD"
