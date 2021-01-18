#ifndef FFANN_update
#define FFANN_update

#include"FFANN.hpp"

FFANN_Template
void FFANN_Namespace::update_weight(int l, int j, int i, LD value){
    this->weights[l][j][i]=value;
}

FFANN_Template
void FFANN_Namespace::update_bias(int l, int j, LD value){
    this->biases[l][j]=value;
}




#endif