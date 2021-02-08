#set PATH variable to working directory


# LONG=  #leave empty to use doubles
LONG=long #set to long , in order to use long doubles

 Headers=$(wildcard ./*.hpp)


Path=$(PWD)
CC=g++
FLG=  -std=c++17  -I "$(Path)" -lm   -DLONG=$(LONG)  -O3


all: FFANN.run FFANN_train.run

FFANN.run: makefile $(Headers) FFANN.cpp
	$(CC) -o "$(Path)/FFANN.run" "$(Path)/FFANN.cpp" $(FLG) -Wall

FFANN_train.run: makefile $(Headers) FFANN_train.cpp
	$(CC) -o "$(Path)/FFANN_train.run" "$(Path)/FFANN_train.cpp" $(FLG) -Wall


clean:
	@[ -f "$(Path)/FFANN.run" ] && rm "$(Path)/FFANN.run" || true
	@[ -f "$(Path)/FFANN_train.run" ] && rm "$(Path)/FFANN_train.run" || true
	 