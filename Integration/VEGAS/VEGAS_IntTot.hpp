#ifndef VEGAS_IntTot
#define VEGAS_IntTot
#include"VEGAS.hpp"


// I take the total integral as follows.
// First, I don't want to go into every bin to take the same amount of points for every bin.
//  So I just take NPoints and each point just contributes f(x)/p(x). To take
// NPoints quickly, I run a loop and I just choose a random bin for each dim.
// Here, 1/p(x) is calculated at the same time you find the point, sine it is just 
// (number of bins)*(binsize of the selected bin).

VEGAS_Template
LD VEGAS_Namespace::IntegrateTot( ){
    LD FuncPoint, point[NDim];
    int bin;
    LD inv_dist;
    LD IntTot=0;
    for(int np=0 ; np <NPoints ;++np){
        inv_dist=1;
        
        for(int dim = 0 ; dim < NDim ; ++dim){
            bin=RandomBin();
            point[dim] = Random( Grid[dim][bin] , Grid[dim][bin+1] ); 
            inv_dist*=NBin*(Grid[dim][bin+1] - Grid[dim][bin]);
        }
        Integrand( point , &FuncPoint );
        IntTot +=  FuncPoint * inv_dist;
    }

    return IntTot/NPoints;
}

#endif