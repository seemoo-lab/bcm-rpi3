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

#include <firmware_version.h>
#include <bcm43438.h>
#include <wrapper.h>	// wrapper definitions for functions that already exist in the firmware
#include <structs.h>	// structures that are used by the code in the firmware
#include <patcher.h>
//#include <helper.h>
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

inline uint16_t
get_unaligned_le16(uint8 *p) {
    return p[0] | p[1] << 8;
}

inline uint32_t
get_unaligned_le32(uint8 *p) {
    return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

/* see: https://github.com/spotify/linux/blob/master/net/wireless/radiotap.c */

/**
 * ieee80211_radiotap_iterator_init - radiotap parser iterator initialization
 * @iterator: radiotap_iterator to initialize
 * @radiotap_header: radiotap header to parse
 * @max_length: total length we can parse into (eg, whole packet length)
 *
 * Returns: 0 or a negative error code if there is a problem.
 *
 * This function initializes an opaque iterator struct which can then
 * be passed to ieee80211_radiotap_iterator_next() to visit every radiotap
 * argument which is present in the header.  It knows about extended
 * present headers and handles them.
 *
 * How to use:
 * call __ieee80211_radiotap_iterator_init() to init a semi-opaque iterator
 * struct ieee80211_radiotap_iterator (no need to init the struct beforehand)
 * checking for a good 0 return code.  Then loop calling
 * __ieee80211_radiotap_iterator_next()... it returns either 0,
 * -ENOENT if there are no more args to parse, or -1 if there is a problem.
 * The iterator's @this_arg member points to the start of the argument
 * associated with the current argument index that is present, which can be
 * found in the iterator's @this_arg_index member.  This arg index corresponds
 * to the IEEE80211_RADIOTAP_... defines.
 *
 * Radiotap header length:
 * You can find the CPU-endian total radiotap header length in
 * iterator->max_length after executing ieee80211_radiotap_iterator_init()
 * successfully.
 *
 * Alignment Gotcha:
 * You must take care when dereferencing iterator.this_arg
 * for multibyte types... the pointer is not aligned.  Use
 * get_unaligned((type *)iterator.this_arg) to dereference
 * iterator.this_arg for type "type" safely on all arches.
 *
 * Example code:
 * See Documentation/networking/radiotap-headers.txt
 */

int ieee80211_radiotap_iterator_init(
    struct ieee80211_radiotap_iterator *iterator,
    struct ieee80211_radiotap_header *radiotap_header,
    int max_length)
{
    /* Linux only supports version 0 radiotap format */
    if (radiotap_header->it_version)
        return -1;

    /* sanity check for allowed length and radiotap length field */
    if (max_length < get_unaligned_le16((uint8 *) &radiotap_header->it_len))
        return -1;

    iterator->rtheader = radiotap_header;
    iterator->max_length = get_unaligned_le16((uint8 *) &radiotap_header->it_len);
    iterator->arg_index = 0;
    iterator->bitmap_shifter = get_unaligned_le32((uint8 *) &radiotap_header->it_present);
    //The original radiotap header (without sub-header) consists of 8 byte
    iterator->arg = (uint8 *)radiotap_header + sizeof(uint8) * 8;
    iterator->this_arg = 0;

    /* find payload start allowing for extended bitmap(s) */

    if (iterator->bitmap_shifter & (1<<IEEE80211_RADIOTAP_EXT)) {
        while (get_unaligned_le32(iterator->arg) & (1<<IEEE80211_RADIOTAP_EXT)) {
            iterator->arg += sizeof(uint32);

            /*
             * check for insanity where the present bitmaps
             * keep claiming to extend up to or even beyond the
             * stated radiotap header length
             */

            if (((unsigned long)iterator->arg - (unsigned long)iterator->rtheader) > iterator->max_length)
                return -1;
        }

        iterator->arg += sizeof(uint32);

        /*
         * no need to check again for blowing past stated radiotap
         * header length, because ieee80211_radiotap_iterator_next
         * checks it before it is dereferenced
         */
    }

    /* we are all initialized happily */

    return 0;
}

/* see: https://github.com/spotify/linux/blob/master/net/wireless/radiotap.c */

/**
 * ieee80211_radiotap_iterator_next - return next radiotap parser iterator arg
 * @iterator: radiotap_iterator to move to next arg (if any)
 *
 * Returns: 0 if there is an argument to handle,
 * -ENOENT if there are no more args or -1
 * if there is something else wrong.
 *
 * This function provides the next radiotap arg index (IEEE80211_RADIOTAP_*)
 * in @this_arg_index and sets @this_arg to point to the
 * payload for the field.  It takes care of alignment handling and extended
 * present fields.  @this_arg can be changed by the caller (eg,
 * incremented to move inside a compound argument like
 * IEEE80211_RADIOTAP_CHANNEL).  The args pointed to are in
 * little-endian format whatever the endianess of your CPU.
 *
 * Alignment Gotcha:
 * You must take care when dereferencing iterator.this_arg
 * for multibyte types... the pointer is not aligned.  Use
 * get_unaligned((type *)iterator.this_arg) to dereference
 * iterator.this_arg for type "type" safely on all arches.
 */

int ieee80211_radiotap_iterator_next(
    struct ieee80211_radiotap_iterator *iterator)
{

    /*
     * small length lookup table for all radiotap types we heard of
     * starting from b0 in the bitmap, so we can walk the payload
     * area of the radiotap header
     *
     * There is a requirement to pad args, so that args
     * of a given length must begin at a boundary of that length
     * -- but note that compound args are allowed (eg, 2 x u16
     * for IEEE80211_RADIOTAP_CHANNEL) so total arg length is not
     * a reliable indicator of alignment requirement.
     *
     * upper nybble: content alignment for arg
     * lower nybble: content length for arg
     */

    uint8 rt_sizes[] = {
        [IEEE80211_RADIOTAP_TSFT] = 0x88,
        [IEEE80211_RADIOTAP_FLAGS] = 0x11,
        [IEEE80211_RADIOTAP_RATE] = 0x11,
        [IEEE80211_RADIOTAP_CHANNEL] = 0x24,
        [IEEE80211_RADIOTAP_FHSS] = 0x22,
        [IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = 0x11,
        [IEEE80211_RADIOTAP_DBM_ANTNOISE] = 0x11,
        [IEEE80211_RADIOTAP_LOCK_QUALITY] = 0x22,
        [IEEE80211_RADIOTAP_TX_ATTENUATION] = 0x22,
        [IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = 0x22,
        [IEEE80211_RADIOTAP_DBM_TX_POWER] = 0x11,
        [IEEE80211_RADIOTAP_ANTENNA] = 0x11,
        [IEEE80211_RADIOTAP_DB_ANTSIGNAL] = 0x11,
        [IEEE80211_RADIOTAP_DB_ANTNOISE] = 0x11,
        [IEEE80211_RADIOTAP_RX_FLAGS] = 0x22,
        [IEEE80211_RADIOTAP_TX_FLAGS] = 0x22,
        [IEEE80211_RADIOTAP_RTS_RETRIES] = 0x11,
        [IEEE80211_RADIOTAP_DATA_RETRIES] = 0x11,
        /*
         * add more here as they are defined in
         * include/net/ieee80211_radiotap.h
         */
    };

    /*
     * for every radiotap entry we can at
     * least skip (by knowing the length)...
     */

    while (iterator->arg_index < sizeof(rt_sizes)) {
        int hit = 0;
        int pad;

        if (!(iterator->bitmap_shifter & 1))
            goto next_entry; /* arg not present */

        /*
         * arg is present, account for alignment padding
         *  8-bit args can be at any alignment
         * 16-bit args must start on 16-bit boundary
         * 32-bit args must start on 32-bit boundary
         * 64-bit args must start on 64-bit boundary
         *
         * note that total arg size can differ from alignment of
         * elements inside arg, so we use upper nybble of length
         * table to base alignment on
         *
         * also note: these alignments are ** relative to the
         * start of the radiotap header **.  There is no guarantee
         * that the radiotap header itself is aligned on any
         * kind of boundary.
         *
         * the above is why get_unaligned() is used to dereference
         * multibyte elements from the radiotap area
         */

        pad = (((unsigned long)iterator->arg) -
            ((unsigned long)iterator->rtheader)) &
            ((rt_sizes[iterator->arg_index] >> 4) - 1);

        if (pad)
            iterator->arg +=
                (rt_sizes[iterator->arg_index] >> 4) - pad;

        /*
         * this is what we will return to user, but we need to
         * move on first so next call has something fresh to test
         */
        iterator->this_arg_index = iterator->arg_index;
        iterator->this_arg = iterator->arg;
        hit = 1;

        /* internally move on the size of this arg */
        iterator->arg += rt_sizes[iterator->arg_index] & 0x0f;

        /*
         * check for insanity where we are given a bitmap that
         * claims to have more arg content than the length of the
         * radiotap section.  We will normally end up equalling this
         * max_length on the last arg, never exceeding it.
         */
        if (((unsigned long)iterator->arg - (unsigned long)iterator->rtheader) > iterator->max_length)
            return -1;

    next_entry:
        iterator->arg_index++;
        if ((iterator->arg_index & 31) == 0) {
            /* completed current u32 bitmap */
            if (iterator->bitmap_shifter & 1) {
                /* b31 was set, there is more */
                /* move to next u32 bitmap */
                iterator->bitmap_shifter =
                    get_unaligned_le32((uint8 *) iterator->next_bitmap);
                iterator->next_bitmap++;
            } else
                /* no more bitmaps: end */
                iterator->arg_index = sizeof(rt_sizes);
        } else /* just try the next bit */
            iterator->bitmap_shifter >>= 1;

        /* if we found a valid arg earlier, return it now */
        if (hit)
            return 0;
    }

    /* we don't know how to handle any more args, we're done */
    return -2;
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

    //needed for sending:
    struct wlc_info *wlc = WLC_INFO_ADDR;
    int short_preamble = 0;
    struct wlc_txh_info txh = {0};
    int data_rate = 0;
    //Radiotap parsing:
    struct ieee80211_radiotap_iterator iterator;
    struct ieee80211_radiotap_header *rtap_header;

    //parse radiotap header
    rtap_len = *((char *)(p->data + 2));

    rtap_header = (struct ieee80211_radiotap_header *) p->data;

    int ret = ieee80211_radiotap_iterator_init(&iterator, rtap_header, rtap_len);

    while(!ret) {
        ret = ieee80211_radiotap_iterator_next(&iterator);
        if(ret) {
            continue;
        }
        switch(iterator.this_arg_index) {
            case IEEE80211_RADIOTAP_RATE:
                data_rate = (*iterator.this_arg);
                break;
            case IEEE80211_RADIOTAP_CHANNEL:
                //printf("Channel (freq): %d\n", iterator.this_arg[0] | (iterator.this_arg[1] << 8) );
                break;
            default:
                //printf("default: %d\n", iterator.this_arg_index);
                break;
        }
    }
    
    //remove radiotap header
    skb_pull(p, rtap_len);

    //inject frame without using the queue
    if(wlc->band->hwrs_scb) {
        wlc_d11hdrs(wlc, p, wlc->band->hwrs_scb, short_preamble, 0, 1, 1, 0, 0, data_rate);
        
        p->scb = wlc->band->hwrs_scb;

        wlc_get_txh_info(wlc, p, &txh);

        wlc_txfifo(wlc, 1, p, &txh, 1, 1);
    } else {
        printf("no scb found, discarding packet!\n");
        osl_pktfree(wlc->osh, p, 0);
    }

    return 0;
}

int
wlc_sdio_hook(int a1, int a2, struct sk_buff *p)
{
    inject_frame(p);
    return 0;
}

int
wlc_recvdata_hook(void *wlc, void *osh, void *rxh, void *p) {
    return osl_pktfree(osh, p, 0);
}

__attribute__((at(0x1210C, "", CHIP_VER_BCM43438, FW_VER_ALL)))
BPatch(wlc_recvdata_hook, wlc_recvdata_hook);

__attribute__((at(0x7EF8, "", CHIP_VER_BCM43438, FW_VER_ALL)))
BPatch(wlc_sdio_hook, wlc_sdio_hook);
