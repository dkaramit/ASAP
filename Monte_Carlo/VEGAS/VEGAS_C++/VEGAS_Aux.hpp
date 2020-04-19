#ifndef VEGAS_aux
#define VEGAS_aux
#include"VEGAS.hpp"



// Define functions that help with getting some feedback for the Grid


VEGAS_Template
void VEGAS_Namespace::PrintGrid(){
    for( int dim=0 ; dim<NDim ; ++dim ){
        for( int bin=0 ; bin<NBin+1 ; ++bin ){
            std::cout<<this->Grid[dim][bin]<<" ";
        }
        std::cout<<"\n";
    }

}




VEGAS_Template
void VEGAS_Namespace::PrintGrid(int dim){
    for( int bin=0 ; bin<NBin+1 ; ++bin ){
        std::cout<<this->Grid[dim][bin]<<" ";
    }
    std::cout<<"\n";

}


VEGAS_Template
void VEGAS_Namespace::PrintWeights(){
        for(int dim = 0 ; dim < NDim ; ++dim)
            {
                for( int bin = 0 ; bin < NBin ; ++bin)
                {
                    std::cout<<weights[dim][bin]<<" ";
                }
            std::cout<<std::endl;
            }

}




#endif