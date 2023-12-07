#include <stdio.h>
#include "sdl-audio.h"
#include "resid.h"
#include "resid-dmpplayer.h"
#include "resid-visualizer.h"
#include "sidekick-gfx.h"

// #include "music-turrican.h"
#include "music-cybernoidII.h"

SDL_AudioDeviceID   SDL_Audio_DevID;
SDL_AudioSpec       SDL_Audio_Spec;

ReSID               R;
ReSIDPbData         D;

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
    // DP.setDmp(Cybernoid_II_dmp, Cybernoid_II_dmp_len);
    // DP.setDmp(m64dmp, m64dmp_len);
    DP.setDmp(Cybernoid_II_dmp, Cybernoid_II_dmp_len);
   
    // print logo
    printf("%s", sidekick_unicode);
    printf("\x1b[2A");       // 2 lines up
    printf("\x1b[?25l");     // cursor off
    printf("\x1b[38;5;60m"); // color
    printf(
        "                                            "
        "                                   ");
    printf("2023, M64\n");
    printf("\x1b[0m");
    
    // -- play sid dmp
    DP.play();

    int i = 0;
    while(!DP.update()) {
        SDL_Delay(5); // time to do stuff

        // -- do visual stuff
        if(!(i++%4)) {
            RV.visualize();
        } 
        
        // -- ctrl-c handler
        if(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                printf("\n[MAIN ] ctrl-c hit, exitting ...\n");
                printf("\x1b[?25h");
                printf("\x1b[0m");
                exit(1);
            break;
            default:
            break;
            }
        }
    }

    printf("\x1b[?25h");  // cursor on
    printf("\x1b[0m");    // reset all attributes (cursor color)

    printf("\n[MAIN ] sidekick end.\n");
    return 0;
}
