#include <stdio.h>
#include "resid.h"

ReSID::ReSID()
{
    double d;

    // -- precalculate constants
    // SAMPLES_PER_FRAME
    //
    // 44.1 kHz =  22.676... us
    d = ((double)1000.0) / ((double) CFG_AUDIO_SAMPLING_RATE);
    // 50 Hz = 20ms. => 20000us / 22.676 us = 882.00144  
    d = ((double)20.0) / d;
    SAMPLES_PER_FRAME = (int) d;
    printf("[ReSID] samples per frame : %d (%f)\n", SAMPLES_PER_FRAME, d);
    
    // CYCLES_PER_FRAME
    //
    // 50 Hz = 20ms. 1 cycle = 1,015us => 20000 / 1.015
    d = ((double)20000) / ((double)1.015) + 0.5;
    CYCLES_PER_FRAME = (int) d;
    printf("[ReSID] cycles  per frame : %d (%f)\n", CYCLES_PER_FRAME, d - 0.5);

    // CYCLES_PER_SAMPLE
    //
    // 44.1 kHz =  22.676 us
    d = ((double)1000000.0) / ((double) CFG_AUDIO_SAMPLING_RATE);
    // 1 cycle = 1,015us => 22676 / 1.015
    d = d / ((double)1.015);
    CYCLES_PER_SAMPLE = d;
    printf("[ReSID] cycles  per sample: %f\n", CYCLES_PER_SAMPLE);

    for(int i=0; i<32; i++) { old_regs[i] = 0; }

    sid.set_sampling_parameters(985248, SAMPLE_RESAMPLE_INTERPOLATE, 44100);

    sid.set_chip_model(MOS6581);
    printf("[ReSID] ReSID chip model: MOS6581\n");

    printf("[ReSID] ReSID initialized\n");
}

ReSID::~ReSID()
{
}

void ReSID::writeRegs(unsigned char *regs, int len)
{
    // SID only has 24 writable registers, SIDDMP does 25
    if(len > 25) return;

    for(int i=0; i<len; i++) {
        if(regs[i] != old_regs[i]) {
            sid.write(i, regs[i]);
            old_regs[i] = regs[i];     
        }
    }
}

int ReSID::clock(unsigned int cycles, short *buf, int buflen)
{
    cycle_count delta_t = cycles;
    return sid.clock(delta_t, buf, buflen);
}
