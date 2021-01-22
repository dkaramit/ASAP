#set PATH variable to working directory

# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

 

Path=$(PWD)
CC=g++

Base = $(wildcard ./GD_base/*)
Vanilla_GD = $(wildcard ./VanillaGD/*)

FLG=  -std=c++17  -I "$(Path)/GD_base" -I "$(Path)/VanillaGD"  -lm   -DLONG=$(LONG)  -O3




all: VanillaGD_example.run

VanillaGD_example.run: makefile TargetFunc.hpp GD_base $(Base) VanillaGD $(Vanilla_GD)  VanillaGD_example.cpp 
	$(CC) -o "$(Path)/VanillaGD_example.run" "$(Path)/VanillaGD_example.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/GD.run" ] && rm "$(Path)/GD.run" || true
	 