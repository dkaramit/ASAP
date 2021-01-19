#set PATH variable to working directory


# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

 

Path=$(PWD)
CC=g++
FLG=  -std=c++17  -I "$(Path)" -lm   -DLONG=$(LONG)  -O3


all: GD.run

GD.run: makefile GD.hpp GD_class.hpp GD_const.hpp GD_run.hpp GD.cpp
	$(CC) -o "$(Path)/GD.run" "$(Path)/GD.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/GD.run" ] && rm "$(Path)/GD.run" || true
	 