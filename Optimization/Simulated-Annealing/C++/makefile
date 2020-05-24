#set PATH variable to working directory


# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

 

Path=$(PWD)
CC=g++
FLG=  -std=c++17  -I "$(Path)" -lm   -DLONG=$(LONG)  -O3


all: SA.run

SA.run: makefile SA_class.hpp  SA_const.hpp  SA_neighbour.hpp SA_temp.hpp SA_run.hpp SA.hpp  SA.cpp
	$(CC) -o "$(Path)/SA.run" "$(Path)/SA.cpp" $(FLG) 


clean:
	@[ -f "$(Path)/SA.run" ] && rm "$(Path)/SA.run" || true
	 