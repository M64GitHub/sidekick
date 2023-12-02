#include <stdio.h>
#include "sdl-audio.h"
#include "resid.h"
#include "resid-dmpplayer.h"
#include "resid-visualizer.h"

//#include "ln2.h"
#include "cybernoidII.h"

SDL_AudioDeviceID   SDL_Audio_DevID;
SDL_AudioSpec       SDL_Audio_Spec;

ReSIDPbData         D;
ReSID               R;

ReSIDDmpPlayer      DP(&R, &D);
ReSIDVisualizer     RV(&R, &D);

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
            RV.visualize();
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

    printf("\n[MAIN ] sidekick end.\n");
    return 0;
}
