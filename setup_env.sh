if [ -d "$(pwd)/buildtools" ]; then
export CC=$(pwd)/buildtools/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
export CROSS_COMPILE=$(pwd)/buildtools/arm-eabi-4.7/bin/arm-eabi-

export ARCH=arm
export KERNEL=kernel7

export NEXMON_FIRMWARE_PATCHING=$(pwd)/firmware_patching
export NEXMON_ROOT=$(pwd)

export NEXMON_SETUP_ENV=1

else 

echo "This script should be run at nexmon's root folder!"
fi

