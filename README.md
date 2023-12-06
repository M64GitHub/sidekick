# sidekick

cmdline sid sound effects player

## siddmp m64 edition

I have extended the original siddmp utility to output ".dmp" files and "_dmp.h"-files.  

The utility can be found under resources/siddmp and has its own Makefile. You
can use it to create the dmp-files to be played by sidekick.

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


