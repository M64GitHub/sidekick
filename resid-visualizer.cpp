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
    int i;
    char bar16[17];
    bar16[16] = 0;

    printf("[RSVIZ] frame: %lu, buffers played: %lu, underruns: %lu\n",
        D->stat_framectr, 
        D->stat_cnt,
        D->stat_buf_underruns
        );

    // -- OSC 1 WF, PW
    printf("[RSVIZ] OSC 1 |WF ");
    // if(R->shadow_regs[0x04] & 1) printf("*"); else printf(" ");
    if(R->shadow_regs[0x04] & 8) printf("T"); else printf(" ");
    if(R->shadow_regs[0x04] & 4) printf("R"); else printf(" ");
    if(R->shadow_regs[0x04] & 2) printf("S"); else printf(" ");
    if(R->shadow_regs[0x04] & 1) printf("G"); else printf(" ");
    printf(" %02x|PW %02x%02x ",
        R->shadow_regs[0x04],        // WF 1
        R->shadow_regs[0x03] & 0x0f, // PW 1 HI (4bit)
        R->shadow_regs[0x02]         // PW 1 LO (8bit)
        );

    // PW h-bar
    for(i=0;i<0x10;i++) {
        if( i < (R->shadow_regs[0x03] & 0x0f) ) bar16[i] = '*'; 
        else bar16[i] = ' ';
    }
    printf("%s|\n", bar16);

    // -- OSC 2 WF, PW
    printf("[RSVIZ] OSC 2 |WF ");
    // if(R->shadow_regs[0x0B] & 1) printf("*"); else printf(" ");
    if(R->shadow_regs[0x0B] & 8) printf("T"); else printf(" ");
    if(R->shadow_regs[0x0B] & 4) printf("R"); else printf(" ");
    if(R->shadow_regs[0x0B] & 2) printf("S"); else printf(" ");
    if(R->shadow_regs[0x0B] & 1) printf("G"); else printf(" ");
    printf(" %02x|PW %02x%02x ",
        R->shadow_regs[0x0B],        // WF 2
        R->shadow_regs[0x0A] & 0x0f, // PW 2 HI (4bit)
        R->shadow_regs[0x09]         // PW 2 LO (8bit)
        );

    // PW h-bar
    for(i=0;i<0x10;i++) {
        if( i < (R->shadow_regs[0x0A] & 0x0f) ) bar16[i] = '*'; 
        else bar16[i] = ' ';
    }
    printf("%s|\n", bar16);

    // -- OSC 3 WF, PW
    printf("[RSVIZ] OSC 3 |WF ");
    // if(R->shadow_regs[0x12] & 1) printf("*"); else printf(" ");
    if(R->shadow_regs[0x12] & 8) printf("T"); else printf(" ");
    if(R->shadow_regs[0x12] & 4) printf("R"); else printf(" ");
    if(R->shadow_regs[0x12] & 2) printf("S"); else printf(" ");
    if(R->shadow_regs[0x12] & 1) printf("G"); else printf(" ");
    printf(" %02x|PW %02x%02x ",
        R->shadow_regs[0x12],        // WF 3
        R->shadow_regs[0x11] & 0x0f, // PW 3 HI (4bit)
        R->shadow_regs[0x10]         // PW 3 LO (8bit)
        );

    // PW h-bar
    for(i=0;i<0x10;i++) {
        if( i < (R->shadow_regs[0x11] & 0x0f) ) bar16[i] = '*'; 
        else bar16[i] = ' ';
    }
    printf("%s|\n", bar16);

    // -- MAIN Volume
    printf("[RSVIZ] Main Volume: %f\n", 0.0);


    printf("\x1b[5A");
    fflush(stdout);
}

