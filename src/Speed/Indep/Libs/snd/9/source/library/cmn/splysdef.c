#include "snd/sndo.h"

int SNDplaysetdef(SNDPLAYOPTS *pspo) {
    pspo->keynum = 60;

    pspo->pitchmult = 0x1000;
    pspo->timemult = 0x1000;
    pspo->tempomult = 0x1000;
    pspo->lowpasscutoff = -1;
    pspo->highpasscutoff = 0;
    pspo->velocity = 0x7F;
    pspo->vol = 0x7F;
    pspo->drylevel = 0x7F;
    pspo->bend = 0x40;
    pspo->fxlevel0 = 0;
    pspo->azimuth = 0;
    pspo->elevation = 0;

    return 0;
}
