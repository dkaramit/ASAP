Path=$(PWD)

LONG=long #set to long , in ord`er to use long doubles

Headers=$(wildcard ./*.hpp)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all: DualNumbers.run

DualNumbers.run: makefile $(Headers) DualNumbers.cpp
	$(CC) -o "$(Path)/DualNumbers.run" "$(Path)/DualNumbers.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/DualNumbers.run" ] && rm "$(Path)/DualNumbers.run" || true