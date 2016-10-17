#pragma once

#include "../include/types.h"

struct tsf {
	unsigned int tsf_l;
	unsigned int tsf_h;
} __attribute__((packed));

struct ieee80211_radiotap_header {
	uint8 it_version;
	uint8 it_pad;
	uint16 it_len;
	uint32 it_present;
	struct tsf tsf;
	char flags;
	char PAD1;
	unsigned short chan_freq;
	unsigned short chan_flags;
	char dbm_antsignal;
	char PAD2;
//	unsigned short vht_known;
//	unsigned char vht_flags;
//	unsigned char vht_bandwidth;
//	unsigned char vht_mcs_nss[4];
//	unsigned char vht_coding;
//	unsigned char vht_group_id;
//	unsigned short vht_partial_aid;
	unsigned char vendor_oui[3];
	unsigned char vendor_sub_namespace;
	unsigned short vendor_skip_length;
} __attribute__((packed));

/**
 * struct ieee80211_radiotap_iterator - tracks walk thru present radiotap args
 * @rtheader: pointer to the radiotap header we are walking through
 * @max_length: length of radiotap header in cpu byte ordering
 * @this_arg_index: IEEE80211_RADIOTAP_... index of current arg
 * @this_arg: pointer to current radiotap arg
 * @arg_index: internal next argument index
 * @arg: internal next argument pointer
 * @next_bitmap: internal pointer to next present u32
 * @bitmap_shifter: internal shifter for curr u32 bitmap, b0 set == arg present
 */

struct ieee80211_radiotap_iterator {
    struct ieee80211_radiotap_header *rtheader;
    int max_length;
    int this_arg_index;
    uint8 *this_arg;

    int arg_index;
    uint8 *arg;
    uint32 *next_bitmap;
    uint32 bitmap_shifter;
};

extern int ieee80211_radiotap_iterator_init(struct ieee80211_radiotap_iterator *iterator, struct ieee80211_radiotap_header *radiotap_header, int max_length);
extern int ieee80211_radiotap_iterator_next(struct ieee80211_radiotap_iterator *iterator);
