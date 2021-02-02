#ifndef FFANN_params
#define FFANN_params
#include"FFANN.hpp"





FFANN_Template
void FFANN_Namespace::update_weight(un_int l, un_int j, un_int i, LD value){
    weights[l][j][i]=value;
}


FFANN_Template
void FFANN_Namespace::update_bias(un_int l, un_int j, LD value){
    //remember that biases[l][j] corresponds to b^{(l+1)}_{j}
    biases[l][j]=value;
}



FFANN_Template
LD FFANN_Namespace::get_weight(un_int l, un_int j, un_int i){
    return weights[l][j][i];
}


FFANN_Template
LD FFANN_Namespace::get_bias(un_int l, un_int j){
    //remember that biases[l][j] corresponds to b^{(l+1)}_{j}
    return biases[l][j];
}


FFANN_Template
void FFANN_Namespace::init_weights(LD min_value,LD max_value){
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    RndE.seed(RndE () );
    LD value;

    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            for(un_int i=0; i<this->nodes[l]; ++i){
            value=UnDist( RndE )*(max_value - min_value) + min_value;
            update_weight(l,j,i,value);
            }
        }
    }
}

FFANN_Template
void FFANN_Namespace::init_biases(LD min_value,LD max_value){
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    RndE.seed(RndE () );
    LD value;

    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            value=UnDist( RndE )*(max_value - min_value) + min_value;
            update_bias(l,j,value);
        }
    }
}

FFANN_Template
void FFANN_Namespace::fill_weights_with(LD value){

    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            for(un_int i=0; i<this->nodes[l]; ++i){
                update_weight(l,j,i,value);
            }
        }
    }
}


FFANN_Template
void FFANN_Namespace::fill_biases_with(LD value){

    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            update_bias(l,j,value);
        }
    }
}

#endif