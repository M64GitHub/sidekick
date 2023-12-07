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
    // -- tests


    // -- Visualize oscillators
    printf("\x1b[38;5;60m"); // color
    printf("  |OSC| WV/CTL | PULSEWIDTH             |\n");
    for(int i=0; i<3; i++) {
        visualizeOsc(i + 1);
    }

    // -- MAIN Volume
    printf("\x1b[38;5;60m"); // color
    printf("  Main Volume: %f\n", 0.0);

    printf("  Frame: %lu, Buffers Played: %lu, Underruns: %lu\n",
        D->stat_framectr, 
        D->stat_cnt,
        D->stat_buf_underruns
        );

    printf("\x1b[6A"); // go 6 lines up
    fflush(stdout);
}

// nr: 1...3
// returns: # of lines printed
int ReSIDVisualizer::visualizeOsc(int nr) 
{
    int  i;
    char bar16[17];
    bar16[16] = 0;

    int osc_base = (nr-1) * 7;
    printf("\x1b[38;5;%dm", nr - 1 + 97); 
    // -- OSC CTRL bits, WF, PW
    printf("  | %d |", nr);
    if(R->shadow_regs[osc_base + 0x04] & 8) printf("T"); else printf(" ");
    if(R->shadow_regs[osc_base + 0x04] & 4) printf("R"); else printf(" ");
    if(R->shadow_regs[osc_base + 0x04] & 2) printf("S"); else printf(" ");
    if(R->shadow_regs[osc_base + 0x04] & 1) printf("G"); else printf(" ");
    printf(" %02x | %02x%02x ",
        R->shadow_regs[osc_base + 0x04],        // WF 1
        R->shadow_regs[osc_base + 0x03] & 0x0f, // PW 1 HI (4bit)
        R->shadow_regs[osc_base + 0x02]         // PW 1 LO (8bit)
        );

    // PW h-bar
    for(i=0;i<0x10;i++) {
        if( i < (R->shadow_regs[osc_base + 0x03] & 0x0f) ) bar16[i] = '*'; 
        else bar16[i] = ' ';
    }
    printf("%s", bar16);

    // PW v-bar (8 steps)
    int v_val = (R->shadow_regs[osc_base + 0x03] & 0x0f) >> 1;
    // U+2581 + v_val
    printf("%c%c%c |", 0xe2, 0x96, 0x81 + v_val);

    printf("\n");
    return 1;
}

