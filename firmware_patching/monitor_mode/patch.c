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
//#include "../include/helper.h"	// useful helper functions

/*
signed int
dngl_sendpkt_hook(int sdio, int frame, int chan) {
    int *sdio_addr = (int *) 0xa0;
    *sdio_addr = (int) sdio;
    return dngl_sendpkt(sdio, frame, chan);
}
*/

int
wlc_bmac_recv_hook(struct wlc_hw_info *wlc_hw, unsigned int fifo, int bound, int *processed_frame_cnt) {
    struct wlc_pub *pub = wlc_hw->wlc->pub;
    sk_buff *p;
    sk_buff *head = 0;
    sk_buff *tail = 0;
    int n = 0;
    int mpc = 0;
    int bound_limit = bound ? pub->tunables->rxbnd : -1;

    while((p == dma_rx(wlc_hw->di[fifo]))) {
		wlc_bmac_mctrl(wlc_hw, 
            MCTL_PROMISC | 
            MCTL_KEEPBADFCS | 
            MCTL_KEEPCONTROL | 
            MCTL_BCNS_PROMISC, 
            MCTL_PROMISC | 
            //MCTL_KEEPBADFCS | 
            MCTL_KEEPCONTROL | 
            MCTL_BCNS_PROMISC);
        if(!tail) {
            head = tail = p;
        } else { 
            tail->prev = p;
            tail = p;
        }

        dma_rxfill(wlc_hw->di[fifo]);

        while((p = head)) {
            head = head->prev;
            p->prev = 0;

            dngl_sendpkt(SDIO_INFO_ADDR, p, 2);
        }

        wlc_iovar_op(wlc_hw->wlc, "mpc", 0, 0, &mpc, 4, 1, 0);

        if(++n >= bound_limit) {
            break;
        }
    }

    *processed_frame_cnt += n;

    return n >= bound_limit;
}
