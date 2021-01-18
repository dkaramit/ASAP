#ifndef FFANN_ff
#define FFANN_ff

#include"FFANN.hpp"

// set input signal
FFANN_Template
void FFANN_Namespace::input_signal(std::vector<LD> x){
    this->signals[0]=x;
}



// calculate the output of the jth node in the lth layer 
FFANN_Template
void FFANN_Namespace::calc_signal(int l, int j){
    if(l==0){return ;}


    //calculate the sum_i w^(l-1)_{ji}*x_{i}
    LD sum_wx = 0 ;
    for(unsigned int i=0; i<(this->signals[l-1]).size();i++){
        sum_wx+=this->weights[l-1][j][i] * this->signals[l-1][i];
    }

    // apply the correct function and biases by using l-1
    signals[l][j] =  this->activations[l-1]( sum_wx + this->biases[l-1][j] ); return;

}



FFANN_Template
void FFANN_Namespace::feed_forward(){


    for(int l=1; l<this->total_layers; l++){
        for(int j=0; j<this->nodes[l]; j++){
            this->calc_signal(l,j);
        }
    }

}
#endif