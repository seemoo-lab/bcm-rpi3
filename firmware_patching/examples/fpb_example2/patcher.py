#!/usr/bin/env python2

import os
import sys
import time
sys.path.append('../../../buildtools/binary_patcher')
sys.path.append('../../../buildtools/elffile')
import binary_patcher
from binary_patcher import *
import elffile

ef = elffile.open(name="patch.elf")

# This function gives us the address of a function in our patch.elf file It helps to identify where functions where automatically placed by the linker
def getSectionAddr(name):
    try:
        return next((header for header in ef.sectionHeaders if header.name == name), None).addr
    except:
        return 0

patch_firmware("../../../bootimg_src/firmware/brcmfmac43430-sdio.orig.bin", 
    "brcmfmac43430-sdio.bin", [
	# The text section is always required and contains code that is called by patches and hooks but not directly placed to predefined memory locations
	ExternalArmPatch(getSectionAddr(".text"), "text.bin"),

	ExternalArmPatch(getSectionAddr(".text.wlc_ucode_download_hook"), "wlc_ucode_download_hook.bin"),
        BLPatch(0x4E994, getSectionAddr(".text.wlc_ucode_download_hook") + 1),
        
        ExternalArmPatch(getSectionAddr(".text.wlc_bmac_recv_hook"), "wlc_bmac_recv_hook.bin"),
	#ExternalArmPatch(getSectionAddr(".text.sub_413E0_hook"), "sub_413E0_hook.bin"),

        ExternalArmPatch(getSectionAddr(".text.wlc_valid_chanspec_hook_in_c"), "wlc_valid_chanspec_hook_in_c.bin"),

	ExternalArmPatch(0xa0, "fpb_remap_dest.bin"),
        #BLPatch(0x4E9A0, getSectionAddr(".text.sub_413E0_hook")),

	# This line replaces the firmware version string that is printed to the console on startup to identify which firmware is loaded by the driver
	#StringPatch(0x4C55D, (os.getcwd().split('/')[-1] + " (" + time.strftime("%d.%m.%Y %H:%M:%S") + ")\n")[:52]), # 53 character string
	], 0x0)
