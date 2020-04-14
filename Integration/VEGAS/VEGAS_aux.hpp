#ifndef VEGAS_aux
#define VEGAS_aux
#include"VEGAS.hpp"



// Define functions that help with getting some feedback for the Grid
VEGAS_Template
void VEGAS_Namespace::PrintGrid(){
    for( int dim=0 ; dim<Dim ; ++dim ){
        for( int bin=0 ; bin<Nbins ; ++bin ){
            std::cout<<this->Grid[dim][bin]<<" ";
        }
        std::cout<<"\n";
    }

}

VEGAS_Template
void VEGAS_Namespace::PrintGrid(int dim){
    for( int bin=0 ; bin<Nbins ; ++bin ){
        std::cout<<this->Grid[dim][bin]<<" ";
    }
    std::cout<<"\n";

}



#endif