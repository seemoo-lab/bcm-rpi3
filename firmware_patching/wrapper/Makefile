CC=../../buildtools/gcc-arm-none-eabi-5_4-2016q2/bin/arm-none-eabi-

NEXMON_CHIP=CHIP_VER_BCM4339
NEXMON_FW_VERSION=FW_VER_6_37_32_RC23_34_40_r581243

WRAPPER_PRE_FILE=wrapper.generated.pre
WRAPPER_OBJ_FILE=$(NEXMON_FIRMWARE_PATCHING)/wrapper/wrapper.o

all: $(WRAPPER_OBJ_FILE)

$(WRAPPER_OBJ_FILE): ../include/wrapper.c
	$(CC)gcc \
		-fplugin=../../buildtools/gcc-nexmon-plugin/nexmon.so \
		-fplugin-arg-nexmon-fwfile=brcmfmac43430-sdio.bin \
		-fplugin-arg-nexmon-ramstart=0x0 \
		-fplugin-arg-nexmon-objfile=$(WRAPPER_OBJ_FILE) \
		-fplugin-arg-nexmon-prefile=$(WRAPPER_PRE_FILE) \
		-fplugin-arg-nexmon-chipver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_CHIP) | $(CC)gcc -E -x c - | tail -n 1` \
		-fplugin-arg-nexmon-fwver=`printf "#include \"../include/firmware_version.h\"\n%s\n" $(NEXMON_FW_VERSION) | $(CC)gcc -E -x c - | tail -n 1` \
		-DNEXMON_CHIP=$(NEXMON_CHIP) \
		-DNEXMON_FW_VERSION=$(NEXMON_FW_VERSION) \
		-Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mthumb -march=armv7-r -ffunction-sections -fdata-sections -I../include -c $< -o $@

clean: 
	rm -f wrapper.o wrapper.ld
