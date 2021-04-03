Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

Headers=$(wildcard ./*.hpp)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all: simple_SGD.run

simple_SGD.run: makefile $(Headers) simple_SGD.cpp
	$(CC) -o "$(Path)/simple_SGD.run" "$(Path)/simple_SGD.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/simple_SGD.run" ] && rm "$(Path)/simple_SGD.run" || true