#ifndef VEGAS_UpBin
#define VEGAS_UpBin
#include"VEGAS.hpp"


VEGAS_Template
void VEGAS_Namespace::UpdateBins(){
    LD AbsInt = PartialIntegrals();
    LD dx0,dxi;
    LD binsizes[NBin];

    for(int dim = 0 ; dim < NDim ; ++dim)
        {
            // this is one way to find the  new delta x_0
            // delta x'_0 = delta x_0/(m_0+1)*\sum_{i=0}^{NBin}( delta x_i/(m_i+1) )^{-1}.
            // At the same time save the binsizes in order to update Grid directly
            dx0=0;
            for( int bin = 0 ; bin < NBin ; ++bin)
            {

                binsizes[bin]=Grid[dim][bin+1]-Grid[dim][bin];

                weights[dim][bin]=1+K_const * pow(weights[dim][bin]/AbsInt * log( weights[dim][bin]/AbsInt+1 ),alpha  );
                
                dx0+=weights[dim][0]/binsizes[0]*(binsizes[bin]/weights[dim][bin]);
            }
            dx0=1/dx0;

            dxi=0;
            Grid[dim][0]=0; // this is true by default. But put it to be sure...
            for( int bin = 0 ; bin < NBin ; ++bin)
            {
                Grid[dim][bin+1]=Grid[dim][bin]+ dx0*binsizes[bin]/weights[dim][bin]*weights[dim][0]/binsizes[0];
            }


        
        }


}



#endif