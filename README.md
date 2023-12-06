# sidekick
![sidekick_400pct](https://github.com/M64GitHub/sidekick/assets/84202356/d9647fd1-f9c8-4a4e-bdc5-d9caebd62538)

Commandline SID sound Effects player  

`sidekick` is a command line SID utility for directly playing back SID sound effects or full tunes. It also can be used as a nifty modular SID debug or visualisation utility, and for cross platform audio development.  
 - Enhance your shell scripts with audio notification sounds like a SID kick-drum or a nice arpeggio
 - Have a possibility to test your various sound ideas immediately without a Commodore64
 - Listen to/test/modify SID-Wizard Instruments quickly, debug hardrestart issues, test sync modes, etc ...
 - Playback and inspect sid tunes, while having a visually rich and detailed information display
 - Playback full tunes in (non-blocking) backgrounding mode (unix fork) to use SID sounds in your programs
 - Cut out your favorite parts out of any SID music and play them in your own programs
   
 - Maintain your collection of sounds in (neo)vim compatible pure ascii files.
 - .wav output: render your ideas or parts of songs into high quality wave files for your DAW or hardware samplers

Sound effects shall be possible to be specified as text inputs and various file input formats.
It shall be possible to specify the SID register values directly as a string input, or use 
SID-Wizards instrument format and note input as text, or play back dumps of full songs

`sidekick` is fully written in C++, it is using the SDL audio layer for playback, and reSID for SID chip sound emulation.
It also follows a modular approach to easily build your own utilities based upon it, or extend it based on your needs.

## Development status
 - Playback (blocking) of SID dumps is working (need to use `&` in your scripts under linux)
 - Basic visualisation of SID chip debug information is working
 - A dump of cybernoid II music is builtin, until parameter handling is ready :) -> standalone test music player
   
![Selection_128](https://github.com/M64GitHub/sidekick/assets/84202356/8751997d-b15f-43f7-8174-ce53637576b4)
 
For testing purposes:

### siddmp m64 edition

I have extended the original siddmp utility to output binary ".dmp" files and ascii "_dmp.h"-files, 
and included it in this repository. This way you can use it to convert .sid files for testing sidekick.

The utility can be found under resources/siddmp and has its own Makefile. You
can use it to create the dmp-files to be played by sidekick, or for playback on microcontrollers, see the note below:

```
M64 edition                                                                2023

siddmp still writes its outpout to stdout, additionaly it creates:

<sidfile>.dmp - a binary sid dump of the first 25 bytes at $d400, each frame

<sidfile>.h   - an ascii readable C header file of the binary dmp ready to 
                include

These files can be used for playback on microcontrollers with or without 
SD-card usage (stream .dmp file or include .h file to play from memory),
or by any siddmp utility for further investigation.

Especially useful to debug hardrestart usage and instrument timings.
```

## Testing sidekick with your own music

 - Convert your sid file using this version of siddmp
 - copy/move the _dmp.h file into the source tree
 - in `main.cpp`: `#include` this header file
 - change the line `DP.setDmp(Cybernoid_II_dmp, Cybernoid_II_dmp_len);` to the contents of your include file
 - build using `make`
 - you have your own standalone executable music player!

2023, M64
