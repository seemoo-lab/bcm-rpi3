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
 * This file contains function prototypes for functions that already exist *
 * in the original firmware of the BCM4339 Wifi chip. With this file, we   *
 * intend to build wrapper functions that can be called directly from C    *
 * after including this header file and linking against the resulting      *
 * object file ../wrapper/wrapper.o. The latter is generated using the     *
 * Makefile ../wrapper/Makefile. Besides the object file, it also creates  *
 * the linker file ../wrapper/wrapper.ld which is based on this header     *
 * file. To make this work, the function prototypes have to be written as  *
 * one line per prototype. Each prototype has to start with the word       *
 * "extern" and end with a comment containing the functions location in    *
 * memory as a hex number. Before the address, there has to be a space.    *
 **************************************************************************/

#ifndef WRAPPER_H
#define WRAPPER_H
#include "../include/structs.h"

extern void *dma_rx(void *di); // 0x4E44
extern void dma_rxfill(void *di); // 0x5070
extern signed int dngl_sendpkt(void *sdio, void *frame, int chan); // 0x3520
extern int memcpy(void *dst, void *src, int len); // 0x2360
extern void *memset(void *dst, int value, int len); // 0x803B14
extern int osl_pktfree(void *a1, void *a2, int a3); // 0x62A0
extern void *pkt_buf_get_skb(void *osh, unsigned int len); // 0x625C
extern int printf(const char *format, ...); // 0x803B60
extern int wf_chspec_malformed(unsigned short chanpsec); // 0x80506C
extern void wl_monitor(void *a1, void *sts, void *p); // 0x819510
extern void *wlc_bsscfg_find_by_wlcif(void *wlc, int wlcif); // 0x1CF3E
extern int wlc_sendctl(void *wlc, sk_buff *p, int *qi, void *scb, unsigned int fifo, unsigned int rate_override, char enq_only); // 0x82DDC4
extern int wlc_recvdata(void *wlc, void *osh, void *rxh, void *p); // 0x1210C
extern void *wlc_bmac_mctrl(void *wlc_hw, int mask_1, int val); // 0x8457F4
extern void wlc_bmac_read_tsf(void *wlc_hw, unsigned int *tsf_l_ptr, unsigned int *tsf_h_ptr); // 0x1BEAC
extern int wlc_iovar_op(void *wlc, char *varname, void *params, int p_len, void *arg, int len, char set, void *wlcif); // 0x82ABEC
extern int wlc_phy_channel2freq(unsigned int channel); // 0x23278
extern void *wlc_recv(void *wlc, void *p); // 0x12A0C
extern void *wlc_ucode_download(void *wlc_hw); // 0x44EC0
extern int wlc_valid_chanspec(void *wlc_cm, unsigned short chanspec, int dualband); // 0x84EEA0
extern int wlc_valid_chanspec_plus4(void *wlc_cm, unsigned short chanspec, int dualband); // 0x84EEA4
extern int wlc_valid_chanspec_dualband(void *wlc_cm, unsigned short chanspec); // 0x84FF24
extern int sub_413E0(int a1); // 0x413E0
extern int sub_80EACC(int a1); // 0x80EACC

#endif /*WRAPPER_H*/
