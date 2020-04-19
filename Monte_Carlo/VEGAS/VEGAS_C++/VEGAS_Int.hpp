#ifndef VEGAS_Int
#define VEGAS_Int
#include"VEGAS.hpp"


VEGAS_Template
LD VEGAS_Namespace::Integrate(LD *IntMean, LD *IntSigma   ){


    for (int n_adapt=0 ; n_adapt<NAdapts; ++n_adapt){UpdateBins();}

    return  IntegrateBatch(IntMean, IntSigma); 



}

#endif