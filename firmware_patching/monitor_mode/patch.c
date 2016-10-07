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
//#include "../include/helper.h"
#include "ieee80211_radiotap.h"
#include "radiotap.h"
#include "d11.h"
#include "brcm.h"

struct brcmf_proto_bcdc_header {
	unsigned char flags;
	unsigned char priority;
	unsigned char flags2;
	unsigned char data_offset;
};

struct bdc_radiotap_header {
    struct brcmf_proto_bcdc_header bdc;
    struct ieee80211_radiotap_header radiotap;
} __attribute__((packed));

void *
skb_push(sk_buff *p, unsigned int len) {
    p->data -= len;
    p->len += len;

    return p->data;
}

void *
skb_pull(sk_buff *p, unsigned int len) {
    p->data += len;
    p->len -= len;

    return p->data;
}

void
conf_fpb(void)
{
    //REMAP REG CONFIG
    *((uint32_t *) 0xE0002004) = 0xa0;
    //REMAP COMP[0], bit[0] is 1 to enable
    *((uint32_t *) 0xE0002008) = (0x81F620 | 0x1);
    //ENABLE CONTROL
    *((uint32_t *) 0xE0002000) |=  0x3;
    printf("FPB config finished!\n");
}

__attribute__((naked)) void
wlc_ucode_download_hook(void)
{
    asm(
        "push {r0-r3,lr}\n"             // Push the registers that could be modified by a call to a C function
        "bl conf_fpb\n"             // Call a C function
        "pop {r0-r3,lr}\n"              // Pop the registers that were saved before
        "b wlc_ucode_download\n"        // Call the hooked function
        );
}

__attribute__((naked)) void
fpb_remap_dest(void)
{
    asm(
        "bl wl_monitor_hook\n"
       );
}

void
wl_monitor_hook(struct wl_info *wl, struct wl_rxsts *sts, struct sk_buff *p) {
    struct sk_buff *p_new = pkt_buf_get_skb(OSL_INFO_ADDR, p->len + sizeof(struct bdc_radiotap_header));
    struct bdc_radiotap_header *frame = (struct bdc_radiotap_header *) p_new->data;

    struct tsf tsf;
	wlc_bmac_read_tsf(wl->wlc_hw, &tsf.tsf_l, &tsf.tsf_h);

	memset(p_new->data, 0, sizeof(struct bdc_radiotap_header));

    frame->bdc.flags = 0x20;
    frame->bdc.priority = 0;
    frame->bdc.flags2 = 0;
    frame->bdc.data_offset = 0;

    frame->radiotap.it_version = 0;
    frame->radiotap.it_pad = 0;
    frame->radiotap.it_len = sizeof(struct ieee80211_radiotap_header);
    frame->radiotap.it_present = 
          (1<<IEEE80211_RADIOTAP_TSFT) 
        | (1<<IEEE80211_RADIOTAP_FLAGS)
        | (1<<IEEE80211_RADIOTAP_CHANNEL)
        | (1<<IEEE80211_RADIOTAP_DBM_ANTSIGNAL);
    frame->radiotap.tsf.tsf_l = tsf.tsf_l;
    frame->radiotap.tsf.tsf_h = tsf.tsf_h;
    frame->radiotap.flags = IEEE80211_RADIOTAP_F_FCS;
    frame->radiotap.chan_freq = wlc_phy_channel2freq(CHSPEC_CHANNEL(sts->chanspec));
    frame->radiotap.chan_flags = 0;
    frame->radiotap.dbm_antsignal = sts->rssi;
	
	memcpy(p_new->data + sizeof(struct bdc_radiotap_header), p->data + 6, p->len - 6);

	p_new->len -= 6;
	dngl_sendpkt(SDIO_INFO_ADDR, p_new, 2);
}

int
inject_frame(sk_buff *p) {
    int rtap_len = 0;
    int data_rate = 0;

    //needed for sending:
    struct wlc_info *wlc = WLC_INFO_ADDR;
    void *bsscfg = 0;

    //Radiotap parsing:
    //struct ieee80211_radiotap_iterator iterator;
    //struct ieee80211_radiotap_header *rtap_header;
    //TODO

    // remove bdc header
    skb_pull(p, 4);

    rtap_len = *((char *)(p->data + 2));
    //parse radiotap header
    //TODO

    //remove radiotap header
    skb_pull(p, rtap_len);

    bsscfg = wlc_bsscfg_find_by_wlcif(wlc, 0);

    //TODO last parameter is the rate, currently fix on 1MBit
    int ret2 = wlc_sendctl(wlc, p, *(int **)((*((int *)(bsscfg + 0xC))) + 0xC), wlc->band->hwrs_scb, 1, data_rate, 0);
    printf("wlc_sendctl() ret: %d\n", ret2);

    return 0;
}

int
handle_sdio_xmit_request_hook(void *sdio_hw, struct sk_buff *p) {
    printf("sdio xmit req hook!\n");
    return inject_frame(p);
}


int
wlc_recvdata_hook(void *wlc, void *osh, void *rxh, void *p) {
    return osl_pktfree(osh, p, 0);
}
