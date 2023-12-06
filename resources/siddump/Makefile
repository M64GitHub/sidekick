CC=gcc
CXX=g++
CFLAGS+=-O3 -Wall
CXXFLAGS=$(CFLAGS)

siddump.exe: siddump.o cpu.o
	gcc -o $@ $^ -lm
#	strip $@

clean: 
	$(RM) *.o *.exe

.phony: clean


