#include <stdio.h>
#include "resid-visualizer.h"


ReSIDVisualizer::ReSIDVisualizer(ReSID *r, ReSIDPbData *d)
{
    R = r; 
    D = d;

    printf("[RSVIZ] ReSID visualizer initialized\n"); 
}

ReSIDVisualizer::~ReSIDVisualizer()
{
}

void ReSIDVisualizer::visualize()
{

    printf("[MAIN ] frame: %lu, buffers played: %lu, underruns: %lu\n",
        D->stat_framectr, 
        D->stat_cnt,
        D->stat_buf_underruns
        );
        // 1 WF, PW
    printf("[MAIN ] osc1-3 wf/pw: %02x/%02x%02x|%02x/%02x%02x|%02x/%02x%02x\n", 
        R->shadow_regs[0x00],        // WF 1
        R->shadow_regs[0x03] & 0x0f, // PW 1 HI (4bit)
        R->shadow_regs[0x02] ,       // PW 1 LO (8bit)

        // 2 WF, PW
        R->shadow_regs[0x04],        // WF 2
        R->shadow_regs[0x0A] & 0x0f, // PW 1 HI (4bit)
        R->shadow_regs[0x09] ,       // PW 1 LO (8bit)

        // 3 WF, PW
        R->shadow_regs[0x12],        // WF 3
        R->shadow_regs[0x11] & 0x0f, // PW 1 HI (4bit)
        R->shadow_regs[0x10]         // PW 1 LO (8bit)
        );
    printf("\x1b[2A");
    fflush(stdout);
}

