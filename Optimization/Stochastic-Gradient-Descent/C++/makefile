Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

ExamplesDir=$(wildcard Examples/*)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all: test.run

test.run: makefile TargetFunc.hpp SGD.hpp test.cpp
	$(CC) -o "$(Path)/test.run" "$(Path)/test.cpp" $(FLG) -Wall


# all:VanillaSGD_example.run 

VanillaSGD_example.run: makefile TargetFunc.hpp SGD.hpp VanillaSGD.hpp  SGD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/VanillaSGD_example.run" "$(Path)/Examples/VanillaSGD_example.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/VanillaSGD_example.run" ] && rm "$(Path)/VanillaSGD_example.run" || true
	 