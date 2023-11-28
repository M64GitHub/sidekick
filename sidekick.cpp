#include <stdio.h>
#include "sdl-audio.h"
#include "resid.h"
#include "resid-dmpplayer.h"
#include "ln2.h"

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
    printf("[MAIN ] sidekick!\n");
    init();

    // -- load sid dmp
    DP.setDmp(Last_Ninja2_dmp, Last_Ninja2_dmp_len);
    
    // -- play sid dmp
    DP.play();

    while(!DP.update()) {
        SDL_Delay(10); // time to do stuff
        D.buf_lock = 0;
    } 
    
    // --

    printf("\n[MAIN ] sidekick end.\n");
    return 0;
}
