#SRCS=$(wildcard *.c) ucode_compressed.c
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
Q=@

NEXMON_CHIP=CHIP_VER_BCM43438
NEXMON_FW_VERSION=FW_VER_7_45_41_26_r640327

CC=../../buildtools/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-

ORIG_FW=../../bootimg_src/firmware/brcmfmac43430-sdio.orig.bin

#all: bcmdhd/bcmdhd.ko fw_bcmdhd.bin fw_bcmdhd.complete.elf
all: brcmfmac/brcmfmac.ko brcmfmac43430-sdio.bin

#include ucode_compression_code.mk

brcmfmac/brcmfmac.ko: check-nexmon-setup-env
	make -C ../../kernel/ M=$$PWD/brcmfmac -j2

%.o: %.c ../include/*.h
	$(CC)gcc \
		-fplugin=../../buildtools/gcc-nexmon-plugin/nexmon.so \
		-fplugin-arg-nexmon-fwfile=brcmfmac43430-sdio.bin \
		-fplugin-arg-nexmon-ramstart=0x0 \
		-fplugin-arg-nexmon-objfile=$@ \
		-fplugin-arg-nexmon-ldfile=$(basename $@).generated.ld \
		-fplugin-arg-nexmon-makefile=$(basename $@).generated.mk \
		-fplugin-arg-nexmon-chipver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_CHIP) | $(CC)gcc -E -x c - | tail -n 1` \
		-fplugin-arg-nexmon-fwver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_FW_VERSION) | $(CC)gcc -E -x c - | tail -n 1` \
		-DNEXMON_CHIP=$(NEXMON_CHIP) \
		-DNEXMON_FW_VERSION=$(NEXMON_FW_VERSION) \
		-Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mthumb -march=armv7-r -ffunction-sections -fdata-sections -I../include -c $< -o $@

%.out: %.c ../include/*.h
	$(CC)gcc \
		-fplugin=../../buildtools/gcc-nexmon-plugin/nexmon.so \
		-fplugin-arg-nexmon-ramstart=0x0 \
		-fplugin-arg-nexmon-objfile=$@ \
		-fplugin-arg-nexmon-ldfile=$(basename $@).generated.ld \
		-fplugin-arg-nexmon-makefile=$(basename $@).generated.mk \
		-fplugin-arg-nexmon-chipver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_CHIP) | $(CC)gcc -E -x c - | tail -n 1` \
		-fplugin-arg-nexmon-fwver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_FW_VERSION) | $(CC)gcc -E -x c - | tail -n 1` \
		-DNEXMON_CHIP=$(NEXMON_CHIP) \
		-DNEXMON_FW_VERSION=$(NEXMON_FW_VERSION) \
		-E -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mthumb -march=armv7-r -ffunction-sections -fdata-sections -I../include -c $< -o $@

wrapper.o: ../include/wrapper.c
	make -C ../wrapper \
		NEXMON_CHIP=$(NEXMON_CHIP) \
		NEXMON_FW_VERSION=$(NEXMON_FW_VERSION) \
		WRAPPER_LD_FILE=$(NEXMON_FIRMWARE_PATCHING)/monitor_mode/$(basename $@).generated.ld \
		WRAPPER_OBJ_FILE=$(NEXMON_FIRMWARE_PATCHING)/monitor_mode/$@

patch.elf: patch.ld patch.o wrapper.o $(OBJS)
	$(CC)ld -T $< -o $@ --gc-sections --print-gc-sections -M

brcmfmac43430-sdio.bin: patch.elf $(ORIG_FW)
	cp $(ORIG_FW) $@
	$(CC)objcopy -O binary -j .text.patch $< section.generated.bin && dd if=section.generated.bin of=$@ bs=1 conv=notrunc seek=$$((0x12110))
	make -f patch.generated.mk Q=$(Q)
	make -f flashpatch.generated.mk Q=$(Q)

#fw_bcmdhd.complete.bin : fw_bcmdhd.bin ../../bootimg_src/firmware/rom.bin
#	dd if=../../bootimg_src/firmware/rom.bin of=$@ bs=1
#	dd if=fw_bcmdhd.bin of=$@ bs=1 seek=1572864

#fw_bcmdhd.complete.elf : fw_bcmdhd.complete.bin
#	$(CC)objcopy -O elf32-littlearm -Barm -I binary $< $@
#	$(CC)objcopy --set-section-flags .data=code $@

check-nexmon-setup-env:
ifndef NEXMON_SETUP_ENV
	$(error run 'source setup_env.sh' first)
endif

#install-firmware: fw_bcmdhd.bin
#	adb shell 'su -c "mount -o rw,remount /system"' && \
#	adb push $< /sdcard/ && \
#	adb shell 'su -c "cp /sdcard/fw_bcmdhd.bin /vendor/firmware/fw_bcmdhd.bin"'
#	adb shell 'su -c "ifconfig wlan0 down"'

clean-firmware: FORCE
#	rm -f fw_bcmdhd.bin fw_bcmdhd.complete.bin fw_bcmdhd.complete.elf *.o patch.elf ucode_compressed.c ucode_compressed.bin *.generated.* wrapper.ld
	rm -f brcmfmac43430-sdio.bin *.o ucode_compressed.c ucode_compressed.bin *.generated.* wrapper.ld

clean: clean-firmware
#	make -C ../../kernel/ M=$$PWD/bcmdhd clean

FORCE:
