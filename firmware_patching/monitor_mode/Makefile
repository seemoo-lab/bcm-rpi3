CC=../../buildtools/arm-eabi-4.7/bin/arm-eabi-
FUNCTIONS = wlc_recvdata_hook wl_monitor_hook fpb_remap_dest wlc_ucode_download_hook
FUNCTIONS_BIN = $(FUNCTIONS:=.bin)

all: brcmfmac/brcmfmac.ko brcmfmac43430-sdio.bin

brcmfmac/brcmfmac.ko: check-nexmon-setup-env
	make -C ../../kernel/ bcm2709_defconfig
	make -C ../../kernel/
	make -C ../../kernel/ M=$$PWD/brcmfmac -j2

brcmfmac43430-sdio.bin: patcher.py patch.elf text.bin $(FUNCTIONS_BIN)
	./patcher.py

patch.o: patch.c ../include/*.h
	$(CC)gcc -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mthumb -march=armv7-m -ffunction-sections -fdata-sections -c $< -o $@

../wrapper/wrapper.o: ../include/wrapper.h
	make -C ../wrapper

patch.elf: patch.ld patch.o ../wrapper/wrapper.o
	$(CC)ld -T $< -o $@ --gc-sections --print-gc-sections -M
#	$(CC)ld -N -T $< -o $@ --gc-sections --print-gc-sections -M

$(FUNCTIONS_BIN): patch.elf
	$(CC)objcopy -O binary -j .text.$(basename $@) $< $@

text.bin: patch.elf
	$(CC)objcopy -O binary -j .text $< $@

#fw_bcmdhd.complete.bin : brcmfmac43430-sdio.bin ../../bootimg_src/firmware/rom.bin
#	dd if=../../bootimg_src/firmware/rom.bin of=$@ bs=1
#	dd if=brcmfmac43430-sdio.bin of=$@ bs=1 seek=1572864

#fw_bcmdhd.complete.elf : fw_bcmdhd.complete.bin
#	$(CC)objcopy -O elf32-littlearm -Barm -I binary $< $@
#	$(CC)objcopy --set-section-flags .data=code $@

check-nexmon-setup-env:
ifndef NEXMON_SETUP_ENV
	$(error run 'source setup_env.sh' first)
endif

clean:
	rm -f brcmfmac43430-sdio.bin fw_bcmdhd.complete.bin patch.o patch.elf text.bin $(FUNCTIONS_BIN)
	make -C ../../kernel/ M=$$PWD/brcmfmac clean

FORCE:
