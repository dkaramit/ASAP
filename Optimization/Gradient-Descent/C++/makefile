Path=$(PWD)

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

ExamplesDir=$(wildcard Examples/*)

CC=g++
STD=-std=c++17
OPT=-O3



FLG=  $(STD)  -I "$(Path)"  -lm   $(OPT) -DLONG=$(LONG) 

all:VanillaGD_example.run AdaDeltaGD_example.run RMSpropGD_example.run\
	AdamGD_example.run AdaMaxGD_example.run NAdamGD_example.run

VanillaGD_example.run: makefile TargetFunc.hpp GD.hpp VanillaGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/VanillaGD_example.run" "$(Path)/Examples/VanillaGD_example.cpp" $(FLG) -Wall

AdaDeltaGD_example.run: makefile TargetFunc.hpp GD.hpp AdaDeltaGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/AdaDeltaGD_example.run" "$(Path)/Examples/AdaDeltaGD_example.cpp" $(FLG) -Wall

RMSpropGD_example.run: makefile TargetFunc.hpp GD.hpp RMSpropGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/RMSpropGD_example.run" "$(Path)/Examples/RMSpropGD_example.cpp" $(FLG) -Wall

AdamGD_example.run: makefile TargetFunc.hpp GD.hpp AdamGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/AdamGD_example.run" "$(Path)/Examples/AdamGD_example.cpp" $(FLG) -Wall

AdaMaxGD_example.run: makefile TargetFunc.hpp GD.hpp AdaMaxGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/AdaMaxGD_example.run" "$(Path)/Examples/AdaMaxGD_example.cpp" $(FLG) -Wall

NAdamGD_example.run: makefile TargetFunc.hpp GD.hpp NAdamGD.hpp  GD.hpp Examples $(ExamplesDir) 
	$(CC) -o "$(Path)/NAdamGD_example.run" "$(Path)/Examples/NAdamGD_example.cpp" $(FLG) -Wall

clean:
	@[ -f "$(Path)/VanillaGD_example.run" ] && rm "$(Path)/VanillaGD_example.run" || true
	@[ -f "$(Path)/AdaDeltaGD_example.run" ] && rm "$(Path)/AdaDeltaGD_example.run" || true
	@[ -f "$(Path)/RMSpropGD_example.run" ] && rm "$(Path)/RMSpropGD_example.run" || true
	@[ -f "$(Path)/AdamGD_example.run" ] && rm "$(Path)/AdamGD_example.run" || true
	@[ -f "$(Path)/AdaMaxGD_example.run" ] && rm "$(Path)/AdaMaxGD_example.run" || true
	@[ -f "$(Path)/NAdamGD_example.run" ] && rm "$(Path)/NAdamGD_example.run" || true
	 