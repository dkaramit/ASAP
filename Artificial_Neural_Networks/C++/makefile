#set PATH variable to working directory


# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

 

Path=$(PWD)
CC=g++
FLG=  -std=c++17  -I "$(Path)" -lm   -DLONG=$(LONG)  -O3


all: FFANN.run

FFANN.run: makefile FFANN.hpp FFANN_class.hpp FFANN_const.hpp FFANN_init.hpp\
FFANN_ff.hpp FFANN_update.hpp FFANN_rw.hpp FFANN_aux.hpp FFANN.cpp
	$(CC) -o "$(Path)/FFANN.run" "$(Path)/FFANN.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/FFANN.run" ] && rm "$(Path)/FFANN.run" || true
	 