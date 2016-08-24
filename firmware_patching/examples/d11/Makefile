#/**************************************************************************
#*                                                                         *
#*          ###########   ###########   ##########    ##########           *
#*         ############  ############  ############  ############          *
#*         ##            ##            ##   ##   ##  ##        ##          *
#*         ##            ##            ##   ##   ##  ##        ##          *
#*         ###########   ####  ######  ##   ##   ##  ##    ######          *
#*          ###########  ####  #       ##   ##   ##  ##    #    #          *
#*                   ##  ##    ######  ##   ##   ##  ##    #    #          *
#*                   ##  ##    #       ##   ##   ##  ##    #    #          *
#*         ############  ##### ######  ##   ##   ##  ##### ######          *
#*         ###########    ###########  ##   ##   ##   ##########           *
#*                                                                         *
#*            S E C U R E   M O B I L E   N E T W O R K I N G              *
#*                                                                         *
#* Warning:                                                                *
#*                                                                         *
#* Our software may damage your hardware and may void your hardware’s      *
#* warranty! You use our tools at your own risk and responsibility!        *
#*                                                                         *
#* License:                                                                *
#* Copyright (c) 2015 NexMon Team                                          *
#*                                                                         *
#* Permission is hereby granted, free of charge, to any person obtaining   *
#* a copy of this software and associated documentation files (the         *
#* "Software"), to deal in the Software without restriction, including     *
#* without limitation the rights to use, copy, modify, merge, publish,     *
#* distribute copies of the Software, and to permit persons to whom the    *
#* Software is furnished to do so, subject to the following conditions:    *
#*                                                                         *
#* The above copyright notice and this permission notice shall be included *
#* in all copies or substantial portions of the Software.                  *
#*                                                                         *
#* Any use of the Software which results in an academic publication or     *
#* other publication which includes a bibliography must include a citation *
#* to the author's publication "M. Schulz, D. Wegemer and M. Hollick.      *
#* NexMon: A Cookbook for Firmware Modifications on Smartphones to Enable  *
#* Monitor Mode.".                                                         *
#*                                                                         *
#* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS *
#* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF              *
#* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  *
#* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY    *
#* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,    *
#* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE       *
#* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                  *
#*                                                                         *
#**************************************************************************/

BCMDHDFWPATH=../../../bootimg_src/firmware/brcmfmac43430-sdio.orig.bin
B43PREP=../../../buildtools/b43/debug/ucode_write_byte.pl
B43DASM=../../../buildtools/b43/disassembler/b43-dasm
B43ASM=../../../buildtools/b43/assembler/b43-asm

ucode.bin: $(BCMDHDFWPATH) Makefile
	dd if=$< of=ucode_raw.bin bs=1 skip=321984 count=45731
	$(B43PREP) ucode_raw.bin $@

ucode.asm: ucode.bin
	$(B43DASM) $< $@ --arch 15 --format raw-le32

# raw ucode in original byte format
ucode-patched_raw.bin: ucode.asm
	PATH=../../../buildtools/b43/assembler:$(PATH) $(B43ASM) $< ucode-patched.bin --format raw-le32
	$(B43PREP) -r ucode-patched.bin $@

# generate a patched ARM firmware file for linux
brcmfmac43430-sdio_mod.bin: ucode-patched_raw.bin
	cp ../../../bootimg_src/firmware/brcmfmac43430-sdio.orig.bin $@
	dd if=$< of=$@ obs=1 seek=321984 conv=notrunc

clean:
	rm -f ucode.bin ucode_raw.bin ucode-patched.bin ucode-patched_raw.bin ucode.asm brcmfmac43430-sdio_mod.bin
