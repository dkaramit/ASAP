#ifndef FFANN_init
#define FFANN_init

#include"FFANN.hpp"


FFANN_Template
void FFANN_Namespace::init_params(LD min, LD max){
    // initialize the biases and weights with random numbers in [min,max]

    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    RndE.seed(RndE () );
    
    for(int l=0; l<this->hidden_layers+1; l++ ){    
        {
            std::vector<LD> tmpV;
            for(int j=0; j<this->nodes[l+1]; j++ ){ tmpV.push_back(UnDist( RndE )*(max - min) + min); }
            this->biases.push_back(tmpV);
        }
    }


    for(int l=0; l<this->hidden_layers+1; l++ ){    
        {
            std::vector<std::vector<LD>> tmpV2;
            for(int j=0; j<this->nodes[l+1]; j++ ){ 
                {
                    std::vector<LD> tmpV; 
                    for(int i=0; i<this->nodes[l]; i++ ){tmpV.push_back(UnDist( RndE )*(max-min)+min);}
                    tmpV2.push_back(tmpV);
                }
            }
            this->weights.push_back(tmpV2);
        }
    }
}




#endif