# LONG= #leave empty to use doubles
LONG=long #set to long , in order to use long doubles



Path=$(PWD)
CC=g++

FLG=  -std=c++17  -I "$(Path)" -lm  -DLONG=$(LONG)  -O3 #-Wall


all:  test.run


test.run: *.hpp test-LU.cpp makefile
	$(CC) -o "$(Path)/test.run" "$(Path)/test-LU.cpp" $(FLG) 


clean:
	@[ -f "$(Path)/test.run" ] && rm "$(Path)/test.run" || true
	