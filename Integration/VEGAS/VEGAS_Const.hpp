#ifndef VEGAS_const
#define VEGAS_const
#include"VEGAS.hpp"


VEGAS_Template
VEGAS_Namespace::VEGAS(Func function, int NPoints, int K_const, LD alpha){
    this->Integrand=function;
    this->NPoints=NPoints;
    this->K_const=K_const;
    this->alpha=alpha;




    std::uniform_int_distribution<> _UnInt(0, NBin-1);
    this-> UnInt =_UnInt;

    // initialize the Grid. Each entry is the point where the Bin starts.
    // For example Grid[1][3] is the point where the 4th bin of 2nd dimension begins.
    // That is  for dimension NDim the ith bin is the interval [Grid[NDim-1][i-1] , Grid[NDim-1][i]]
    for( int dim=0 ; dim<NDim ; ++dim )
    {
        Grid[dim][0]=0;
        for( int bin=1 ; bin<NBin+1 ; ++bin ){
            Grid[dim][bin]= Grid[dim][bin-1] + (LD)1/(NBin);
        }
    }
}




#endif