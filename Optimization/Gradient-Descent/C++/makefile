#set PATH variable to working directory

LONG=  #leave empty to use doubles
# LONG=long #set to long , in order to use long doubles

 

Path=$(PWD)
CC=g++

FLG=  -std=c++17  -I "$(Path)"  -lm   -DLONG=$(LONG)  -O3

all: VanillaGD_example.run AdaDeltaGD_example.run RMSpropGD_example.run AdamGD_example.run AdaMaxGD_example.run NAdamGD_example.run

VanillaGD_example.run: makefile TargetFunc.hpp GD.hpp VanillaGD.hpp  VanillaGD_example.cpp 
	$(CC) -o "$(Path)/VanillaGD_example.run" "$(Path)/VanillaGD_example.cpp" $(FLG) -Wall

AdaDeltaGD_example.run: makefile TargetFunc.hpp GD.hpp AdaDeltaGD.hpp  AdaDeltaGD_example.cpp 
	$(CC) -o "$(Path)/AdaDeltaGD_example.run" "$(Path)/AdaDeltaGD_example.cpp" $(FLG) -Wall

RMSpropGD_example.run: makefile TargetFunc.hpp GD.hpp RMSpropGD.hpp  RMSpropGD_example.cpp 
	$(CC) -o "$(Path)/RMSpropGD_example.run" "$(Path)/RMSpropGD_example.cpp" $(FLG) -Wall

AdamGD_example.run: makefile TargetFunc.hpp GD.hpp AdamGD.hpp  AdamGD_example.cpp 
	$(CC) -o "$(Path)/AdamGD_example.run" "$(Path)/AdamGD_example.cpp" $(FLG) -Wall

AdaMaxGD_example.run: makefile TargetFunc.hpp GD.hpp AdaMaxGD.hpp  AdaMaxGD_example.cpp 
	$(CC) -o "$(Path)/AdaMaxGD_example.run" "$(Path)/AdaMaxGD_example.cpp" $(FLG) -Wall

NAdamGD_example.run: makefile TargetFunc.hpp GD.hpp NAdamGD.hpp  NAdamGD_example.cpp 
	$(CC) -o "$(Path)/NAdamGD_example.run" "$(Path)/NAdamGD_example.cpp" $(FLG) -Wall

clean:
	@[ -f "$(Path)/VanillaGD_example.run" ] && rm "$(Path)/VanillaGD_example.run" || true
	@[ -f "$(Path)/AdaDeltaGD_example.run" ] && rm "$(Path)/AdaDeltaGD_example.run" || true
	@[ -f "$(Path)/RMSpropGD_example.run" ] && rm "$(Path)/RMSpropGD_example.run" || true
	@[ -f "$(Path)/AdamGD_example.run" ] && rm "$(Path)/AdamGD_example.run" || true
	@[ -f "$(Path)/AdaMaxGD_example.run" ] && rm "$(Path)/AdaMaxGD_example.run" || true
	@[ -f "$(Path)/NAdamGD_example.run" ] && rm "$(Path)/NAdamGD_example.run" || true
	 