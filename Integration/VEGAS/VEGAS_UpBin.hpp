#ifndef VEGAS_UpBin
#define VEGAS_UpBin
#include"VEGAS.hpp"


VEGAS_Template
void VEGAS_Namespace::UpdateBins(){

    LD AbsInt = PartialIntegrals();
    
    LD dx0,dxi;
    LD binsizes[NBin];
    



    LD w0;//This is a temporary variable to keep weights[dim][0]. Do this in order to be able to reset
    // all weights at the end of each loop. 
    for(int dim = 0 ; dim < NDim ; ++dim)
        {
            // this is one way to find the  new delta x_0
            // delta x'_0 = delta x_0/(m_0+1)*\sum_{i=0}^{NBin}( delta x_i/(m_i+1) )^{-1}.
            // At the same time save the binsizes in order to update Grid directly
            dx0=0;
            

            // w0=1+constK*pow(weights[dim][0]/AbsInt,alpha);
            // this is weights[dim][0] (the regulated one) for bin=m of this dim.
            w0=1+ pow(1+weights[dim][0]/AbsInt * log(constK*weights[dim][0]/AbsInt + 1 ),alpha  );

            for( int bin = 0 ; bin < NBin ; ++bin)
            {

                binsizes[bin]=Grid[dim][bin+1]-Grid[dim][bin];
                // weights[dim][bin]=1+constK*pow(weights[dim][bin]/AbsInt,alpha);
                weights[dim][bin]=1+ pow(1+weights[dim][bin]/AbsInt * log(constK*weights[dim][bin]/AbsInt + 1 ),alpha  );
                
                dx0+=w0/binsizes[0]*(binsizes[bin]/weights[dim][bin]);
            }
            dx0=1/dx0;

            dxi=0;
            Grid[dim][0]=0; // this is true by default. But put it to be sure...
            for( int bin = 0 ; bin < NBin ; ++bin)
            {
                Grid[dim][bin+1]=Grid[dim][bin]+ dx0*binsizes[bin]/weights[dim][bin]*w0/binsizes[0];
                weights[dim][bin]=0; //You no longer need this weight. 
            }


        
        }


}



#endif