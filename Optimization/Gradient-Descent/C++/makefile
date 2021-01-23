Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

Headers=$(wildcard ./*.hpp)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all:GD_example.run 


GD_example.run: makefile $(Headers) GD_example.cpp
	$(CC) -o "$(Path)/GD_example.run" "$(Path)/GD_example.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/GD_example.run" ] && rm "$(Path)/GD_example.run" || true