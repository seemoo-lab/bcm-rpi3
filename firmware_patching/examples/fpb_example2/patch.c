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

#include "../../include/bcm43438.h"
#include "../../include/wrapper.h"	// wrapper definitions for functions that already exist in the firmware
#include "../../include/structs.h"	// structures that are used by the code in the firmware

void
conf_fpb(void)
{
    //REMAP REG CONFIG
    *((uint32_t *) 0xE0002004) = 0xa0;
    //REMAP COMP[0], bit[0] is 1 to enable
    *((uint32_t *) 0xE0002008) = (0x84EEA0| 0x1);
    //ENABLE CONTROL
    *((uint32_t *) 0xE0002000) |=  0x3;
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
 * Hooks a function which is called after the wlc_ucode_download() function. 
 * The BL to this function gets overwritten by a flash patch
 */
__attribute__((naked)) int
wlc_valid_chanspec_orig(void *wlc_cm, unsigned short chanspec, int dualband)
{
	asm(
        "push {r3-r9,lr}\n"
		"b wlc_valid_chanspec_plus4\n"		// Call the hooked function
		);
}

int
wlc_valid_chanspec_hook_in_c(void *wlc_cm, unsigned short chanspec, int dualband, int lr)
{
    printf("HOOK!\n");
    return wlc_valid_chanspec_orig(wlc_cm, chanspec, dualband);
    /*
    int ret = wlc_valid_chanspec_orig(wlc_cm, chanspec, dualband);
    if ((chanspec == 0x100e) && dualband == 1) {
        ret = 1;
    }

    return ret;
    */
}

__attribute__((naked)) void
fpb_remap_dest(void)
{
	asm(
       "b wlc_valid_chanspec_hook_in_c\n"
       );
}

int
wlc_bmac_recv_hook(struct wlc_hw_info *wlc_hw, unsigned int fifo, int bound, int *processed_frame_cnt) {
    return 0;
}

void
dummy_0F0(void) {
    ;
}
