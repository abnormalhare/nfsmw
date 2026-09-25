#include "Speed/Indep/Libs/snd/9/source/library/cmn/sndcmn.h"
#include "snd/sndo.h"

int SNDPROFILE_outputlatency() {
    if (!sndgs.installed) {
        return 0;
    } else {
        return SNDPLATFORM_outputlatency();
    }
}
