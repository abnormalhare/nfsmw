#include "Speed/Indep/Libs/snd/9/source/library/cmn/sndcmn.h"
unsigned int SNDIrandseed[6];

unsigned int SNDIrandseedorig[6] = {
    0xF22D0E56, 0x883126E9, 0xC624DD2F, 0x0702C49C, 0x9E353F7D, 0x6fDF3B64,
};

void SNDI_randomseed(unsigned int seed) {
    int i;

    for (i = 0; i < 6; i++) {
        SNDIrandseed[i] = SNDIrandseedorig[i] + seed;
    }
}

unsigned int iSNDrandom() {
    unsigned int ax = SNDIrandseed[5] + SNDIrandseed[4];
    unsigned int c = 0;

    if (ax < SNDIrandseed[5] || ax < SNDIrandseed[4]) {
        c = 1;
    }
    SNDIrandseed[4] = ax;

    ax = ax + SNDIrandseed[3] + c;
    c = (unsigned int)(ax < SNDIrandseed[3]);
    SNDIrandseed[3] = ax;

    ax = ax + SNDIrandseed[2] + c;
    c = (unsigned int)(ax < SNDIrandseed[2]);
    SNDIrandseed[2] = ax;

    ax = ax + SNDIrandseed[1] + c;
    c = (unsigned int)(ax < SNDIrandseed[1]);
    SNDIrandseed[1] = ax;

    ax = ax + SNDIrandseed[0] + c;
    SNDIrandseed[0] = ax;

    if (++SNDIrandseed[5] != 0) {
        return SNDIrandseed[0];
    }
    if (++SNDIrandseed[4] != 0) {
        return SNDIrandseed[0];
    }
    if (++SNDIrandseed[3] != 0) {
        return SNDIrandseed[0];
    }
    if (++SNDIrandseed[2] != 0) {
        return SNDIrandseed[0];
    }
    if (++SNDIrandseed[1] == 0) {
        // might be a fakematch...
        SNDIrandseed[0]++;
        ax++;
    }

    return ax;
}
