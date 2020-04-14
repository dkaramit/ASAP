#ifndef VEGAS_Rand
#define VEGAS_Rand
#include"VEGAS.hpp"


//This defines a function that retunrs random numbers in the range [min,max].
// You can define your own here! 


VEGAS_Template
LD VEGAS_Namespace::Random(LD min, LD max){
    RndE.seed(RndDiv () );
    return (UnDist( RndE )*(max - min) + min ) ;
}

VEGAS_Template  
void VEGAS_Namespace::RandomGrid(int dim){
       last_dim=dim; //used in auxiliary function. 

       
        for (int bin=0 ; bin< Nbins  ; ++bin)
        {
            for(int Rpoint =0; Rpoint < PointsPerBin  ; ++Rpoint){
                this->RandPoints[bin][Rpoint]=  Random( Grid[dim][bin] , Grid[dim][bin+1]  );
            }
        }
    

}



#endif