# -------------------------------------------------------------------------- #
#  sidekick - commandline sid sound effect player                  2023, M64 # 
#                                                  <m64.overdrive@gmail.com> #
# -------------------------------------------------------------------------- #

BINARY=sidekick
# CC=zig c++
# CXX=zig c++

CXX=g++

CFLAGS+=-O3 -Wall
CXXFLAGS+=$(CFLAGS)

$(BINARY): main.o sdl-audio.o \
	resid.o \
	resid-dmpplayer.o \
	resid-visualizer.o \
	resid/sid.o \
	resid/envelope.o \
	resid/extfilt.o \
	resid/filter.o \
	resid/pot.o \
	resid/voice.o \
	resid/wave.o \
	resid/wave6581_PST.o \
	resid/wave6581_PS_.o \
	resid/wave6581_P_T.o \
	resid/wave6581__ST.o \
	resid/wave8580_PST.o \
	resid/wave8580_PS_.o \
	resid/wave8580_P_T.o \
	resid/wave8580__ST.o

	$(CXX) -o $@ $^ -lm -lSDL2 

clean:
	$(RM) *.o resid/*.o $(BINARY)

.phony: clean

