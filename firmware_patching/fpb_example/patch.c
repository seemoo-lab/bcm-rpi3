/***************************************************************************
 *                                                                         *
 *          ###########   ###########   ##########    ##########           *
 *         ############  ############  ############  ############          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ###########   ####  ######  ##   ##   ##  ##    ######          *
 *          ###########  ####  #       ##   ##   ##  ##    #    #          *
 *                   ##  ##    ######  ##   ##   ##  ##    #    #          *
 *                   ##  ##    #       ##   ##   ##  ##    #    #          *
 *         ############  ##### ######  ##   ##   ##  ##### ######          *
 *         ###########    ###########  ##   ##   ##   ##########           *
 *                                                                         *
 *            S E C U R E   M O B I L E   N E T W O R K I N G              *
 *                                                                         *
 * Warning:                                                                *
 *                                                                         *
 * Our software may damage your hardware and may void your hardware’s      *
 * warranty! You use our tools at your own risk and responsibility!        *
 *                                                                         *
 * License:                                                                *
 * Copyright (c) 2015 NexMon Team                                          *
 *                                                                         *
 * Permission is hereby granted, free of charge, to any person obtaining   *
 * a copy of this software and associated documentation files (the         *
 * "Software"), to deal in the Software without restriction, including     *
 * without limitation the rights to use, copy, modify, merge, publish,     *
 * distribute copies of the Software, and to permit persons to whom the    *
 * Software is furnished to do so, subject to the following conditions:    *
 *                                                                         *
 * The above copyright notice and this permission notice shall be included *
 * in all copies or substantial portions of the Software.                  *
 *                                                                         *
 * Any use of the Software which results in an academic publication or     *
 * other publication which includes a bibliography must include a citation *
 * to the author's publication "M. Schulz, D. Wegemer and M. Hollick.      *
 * NexMon: A Cookbook for Firmware Modifications on Smartphones to Enable  *
 * Monitor Mode.".                                                         *
 *                                                                         *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF              *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY    *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,    *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE       *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                  *
 *                                                                         *
 **************************************************************************/

#include "../include/bcm43438.h"
#include "../include/wrapper.h"	// wrapper definitions for functions that already exist in the firmware
#include "../include/structs.h"	// structures that are used by the code in the firmware

uint32_t little_endian_16_bit(uint32_t val)
{
        return ((val & 0xFFFF0000) >> 16) | ((val & 0x0000FFFF) << 16);
}

void
conf_fpb(void)
{
    //ENABLE CONTROL
    *((uint32_t *) 0xE0002000) |=  0x3;
    //REMAP REG CONFIG
    *((uint32_t *) 0xE0002004) = 0x20007000;
    //REMAP COMP[0], bit[0] is 1 to enable
    *((uint32_t *) 0xE0002008) = (0x4E9A0 | 0x1);
    //NEW INSTRUCTION in REMAP TABLE
    *((uint32_t *) 0x20007000) = little_endian_16_bit(0xF7B2F836);
    //F7B2F836 b2f736f8
	printf("FPB config finished!\n");
}

/**
 *	hook to call function for FPB configuration
 */
__attribute__((naked)) void
wlc_ucode_download_hook(void)
{
	asm(
		"push {r0-r3,lr}\n"				// Push the registers that could be modified by a call to a C function
		"bl conf_fpb\n"				// Call a C function
		"pop {r0-r3,lr}\n"				// Pop the registers that were saved before
		"b wlc_ucode_download\n"		// Call the hooked function
		);
}

/*
 * print something to show that the flash patch works
 */
void
hello_fpb(void)
{
	printf("called via FPB!\n");
}

/*
 * Hooks a function which is called after the wlc_ucode_download() function. 
 * The BL to this function gets overwritten by a flash patch
 */
__attribute__((naked)) void
sub_413E0_hook(void)
{
	asm(
		"push {r0-r3,lr}\n"				// Push the registers that could be modified by a call to a C function
		"bl hello_fpb\n"				// Call a C function
		"pop {r0-r3,lr}\n"				// Pop the registers that were saved before
		"b sub_413E0\n"		// Call the hooked function
		);
}

void
dummy_0F0(void) {
    ;
}
