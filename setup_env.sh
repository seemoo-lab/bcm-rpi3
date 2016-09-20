#!/bin/bash
OLD_PWD=$(pwd)
cd $(dirname ${BASH_SOURCE[0]})

if [ -d "$(pwd)/buildtools" ] && [ -d "$(pwd)/firmware_patching" ]; then
 export CC=$(pwd)/buildtools/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
 export CROSS_COMPILE=$(pwd)/buildtools/arm-eabi-4.7/bin/arm-eabi-

 export ARCH=arm
 export KERNEL=kernel7

 export NEXMON_FIRMWARE_PATCHING=$(pwd)/firmware_patching
 export NEXMON_ROOT=$(pwd)

 export NEXMON_SETUP_ENV=1
else
 echo "One or more required folders are missing!"
fi

cd "$OLD_PWD"
