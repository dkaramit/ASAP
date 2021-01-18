#ifndef FFANN_aux
#define FFANN_aux

#include "FFANN.hpp"

FFANN_Template
void FFANN_Namespace::print_weights(){

    for(unsigned int  l=0; l<this->weights.size(); l++){
        std::cout<<"l="<<l<<":"<<std::endl;  
        for(unsigned int  j=0; j<this->weights[l].size();j++){
            for(unsigned int  i=0; i<this->weights[l][j].size();i++){
                std::cout<< this->weights[l][j][i]<<"\t";
            }
            std::cout<<std::endl;
        } 
            std::cout<<"=================="<<std::endl;
    }
}




FFANN_Template
void FFANN_Namespace::print_biases(){

    for(unsigned int  l=0; l<this->biases.size(); l++){
        std::cout<<"l="<<l+1<<":"<<std::endl;  
        for(unsigned int  j=0; j<this->biases[l].size();j++){
            std::cout<<this->biases[l][j]<<"\t";
        } 
            std::cout<<std::endl<<"=================="<<std::endl;
    }
}





FFANN_Template
void FFANN_Namespace::print_signals(){
    for(unsigned int  l=0; l<this->signals.size(); l++){
        std::cout<<"l="<<l<<":"<<std::endl;  
        for(unsigned int  j=0; j<this->signals[l].size();j++){
            std::cout<<this->signals[l][j]<<"\t";
        } 
            std::cout<<std::endl<<"=================="<<std::endl;
    }

}
#endif