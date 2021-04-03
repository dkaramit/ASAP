Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

Headers=$(wildcard ./*.hpp)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all: simple_GD.run

simple_GD.run: makefile $(Headers) simple_GD.cpp
	$(CC) -o "$(Path)/simple_GD.run" "$(Path)/simple_GD.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/simple_GD.run" ] && rm "$(Path)/simple_GD.run" || true