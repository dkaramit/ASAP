#ifndef VEGAS_const
#define VEGAS_const
#include"VEGAS.hpp"


VEGAS_Template
VEGAS_Namespace::VEGAS(int max_iterations){
    // points per bin
    this->max_iterations=max_iterations;

    // initialize the Grid. Each entry is the point where the Bin starts.
    // For example Grid[1][3] is the point where the 4th bin of 2nd dimension begins.
    // That is  for dimension Dim the ith bin is the interval [Grid[Dim-1][i-1] , Grid[Dim-1][i]]
    for( int dim=0 ; dim<Dim ; ++dim ){
        
        Grid[dim][0]=0;
        for( int bin=1 ; bin<Nbins+1 ; ++bin ){
            Grid[dim][bin]= Grid[dim][bin-1] + (LD)1/(Nbins);
        }

    }
}




#endif