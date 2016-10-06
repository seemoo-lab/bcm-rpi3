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
 * About this file:                                                        *
 * TODO                                                                    *
 **************************************************************************/

#ifndef WRAPPER_C
#define WRAPPER_C

#include <firmware_version.h>
#include <structs.h>

#ifndef WRAPPER_H
    // if this file is not included in the wrapper.h file, create dummy functions
    #define VOID_DUMMY { ; }
    #define RETURN_DUMMY { ; return 0; }

    #define AT(CHIPVER, FWVER, ADDR) __attribute__((at(ADDR, "dummy", CHIPVER, FWVER)))
#else
    // if this file is included in the wrapper.h file, create prototypes
    #define VOID_DUMMY ;
    #define RETURN_DUMMY ;
    #define AT(CHIPVER, FWVER, ADDR)
#endif

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x4E44)
void *
dma_rx(void *di)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x5070)
void
dma_rxfill(void *di)
VOID_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x3520)
signed int
dngl_sendpkt(void *sdio, void *frame, int chan)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x4264)
void *
handle_sdio_xmit_request(void *sdio_hw, void *p)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x2360)
int
memcpy(void *dst, void *src, int len)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x803B14)
void *
memset(void *dst, int value, int len)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x62A0)
int
osl_pktfree(void *a1, void *a2, int a3)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x625C)
void *
pkt_buf_get_skb(void *osh, unsigned int len)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x803B60)
int
printf(const char *format, ...)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x80506C)
int
wf_chspec_malformed(unsigned short chanpsec)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x819510)
void
wl_monitor(void *a1, void *sts, void *p)
VOID_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x1210C)
int
wlc_recvdata(void *wlc, void *osh, void *rxh, void *p)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x8457F4)
void *
wlc_bmac_mctrl(void *wlc_hw, int mask_1, int val)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x1BEAC)
void
wlc_bmac_read_tsf(void *wlc_hw, unsigned int *tsf_l_ptr, unsigned int *tsf_h_ptr)
VOID_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x1CF3E)
void *
wlc_bsscfg_find_by_wlcif(void *wlc, int wlcif)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x86AC74)
void *
wlc_scb_set_bsscfg(void *scb, void *bsscfg)
RETURN_DUMMY

//AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x82DDC4)
AT(CHIP_VER_BCM43438, FW_VER_ALL, 0xdc84)
int
wlc_sendctl(void *wlc, void *p, void *qi, void *scb, unsigned int fifo, unsigned int rate_override, char enq_only)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x82ABEC)
int
wlc_iovar_op(void *wlc, char *varname, void *params, int p_len, void *arg, int len, char set, void *wlcif)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x23278)
int
wlc_phy_channel2freq(unsigned int channel)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x12A0C)
void *
wlc_recv(void *wlc, void *p)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x301F8)
void *
wlc_scb_lookup(void *wlc, void *bsscfg, char *ea, int bandunit)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x44EC0)
void *
wlc_ucode_download(void *wlc_hw)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x84EEA0)
int
wlc_valid_chanspec(void *wlc_cm, unsigned short chanspec, int dualband)
RETURN_DUMMY

AT(CHIP_VER_BCM43438, FW_VER_ALL, 0x84FF24)
int
wlc_valid_chanspec_dualband(void *wlc_cm, unsigned short chanspec)
RETURN_DUMMY

#undef VOID_DUMMY
#undef RETURN_DUMMY
#undef AT

#endif /*WRAPPER_C*/
