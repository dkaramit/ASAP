Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

Headers=$(wildcard ./*.hpp)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all:SGD_example.run 


SGD_example.run: makefile $(Headers) SGD_example.cpp
	$(CC) -o "$(Path)/SGD_example.run" "$(Path)/SGD_example.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/SGD_example.run" ] && rm "$(Path)/SGD_example.run" || true