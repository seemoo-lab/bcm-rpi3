#pragma once

#define WL_CHANSPEC_CHAN_MASK       0x00ff
#define CHSPEC_CHANNEL(chspec)  ((unsigned char)((chspec) & WL_CHANSPEC_CHAN_MASK))
