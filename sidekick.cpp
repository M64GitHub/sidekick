#include <stdio.h>
#include "sdl-audio.h"
#include "resid.h"
#include "resid-dmpplayer.h"
//#include "ln2.h"
#include "cybernoidII.h"

SDL_AudioDeviceID   SDL_Audio_DevID;
SDL_AudioSpec       SDL_Audio_Spec;

ReSIDPbData         D;
ReSID               R;

ReSIDDmpPlayer      DP(&R, &D);

void init()
{
    sdl_audio_init(&SDL_Audio_DevID, &SDL_Audio_Spec, &D);
}

int main(int argc, char **argv)
{
    SDL_Event event;
    printf("[MAIN ] sidekick!\n");
    init();

    // -- load sid dmp
    DP.setDmp(Cybernoid_II_dmp, Cybernoid_II_dmp_len);
    
    // -- play sid dmp
    DP.play();

    int i = 0;
    while(!DP.update()) {
        SDL_Delay(1); // time to do stuff

        // -- do visual stuff
        if(!(i++%40)) {
            printf("\r[MAIN ] frame: %lu, buffers played: %lu, underruns: %lu, osc1-3 wf/pw: %02x/%02x%02x|%02x/%02x%02x|%02x/%02x%02x", 
                D.stat_framectr, 
                D.stat_cnt,
                D.stat_buf_underruns,
                // 1 WF, PW
                R.shadow_regs[0x00],        // WF 1
                R.shadow_regs[0x03] & 0x0f, // PW 1 HI (4bit)
                R.shadow_regs[0x02] ,       // PW 1 LO (8bit)

                // 2 WF, PW
                R.shadow_regs[0x04],        // WF 2
                R.shadow_regs[0x0A] & 0x0f, // PW 1 HI (4bit)
                R.shadow_regs[0x09] ,       // PW 1 LO (8bit)

                // 3 WF, PW
                R.shadow_regs[0x12],        // WF 3
                R.shadow_regs[0x11] & 0x0f, // PW 1 HI (4bit)
                R.shadow_regs[0x10]         // PW 1 LO (8bit)
                );
            fflush(stdout);
        }

        // -- ctrl-c handler
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                printf("\n[MAIN ] ctrl-c hit, exitting ...\n");
                exit(1);
            break;
            default:
            break;
            }
        } 
    }
    
    // --

    printf("\n[MAIN ] sidekick end.\n");
    return 0;
}
