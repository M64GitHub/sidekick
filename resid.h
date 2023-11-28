#ifndef SDL_RESID_H
#define SDL_RESID_H

#include "audio-config.h"
#include "resid/sid.h"

typedef struct S_ReSIDPbData {
    short buf[CFG_AUDIO_BUF_SIZE+1];
    char buf_consumed = 0;
    char buf_lock = 0;
    char play = 0;
    unsigned long stat_cnt = 0;
    unsigned long stat_bufwrites = 0;
    unsigned long stat_buf_underruns = 0;
    unsigned long stat_framectr = 0;
} ReSIDPbData;

class ReSID 
{
public:
    ReSID();
    ~ReSID();

    void writeRegs(unsigned char *regs, int len);

    // dumb audio rendering, not frame aware
    int clock(unsigned int cycles, short *buf, int buflen);

    // calculated CONSTANTS
    int SAMPLES_PER_FRAME;
    int CYCLES_PER_FRAME;
    double CYCLES_PER_SAMPLE;

private:
    void precalcConstants();

    SID sid;
    unsigned char old_regs[32];
};

#endif

