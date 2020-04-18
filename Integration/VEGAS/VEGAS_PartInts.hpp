#ifndef VEGAS_PartInts
#define VEGAS_PartInts
#include"VEGAS.hpp"


// Calculate the  partial integrals as well as NPoints*\int_{0}^1 dx |f|.
// The actual wheights are calculated in CalcWeights-Check.hpp, but here we just 
// do this so that this will be calced for UpdateBins(), regulate pass the partial integrals
// as m->m+1 , m-> (K* m log( m ))^alpha.

VEGAS_Template
LD VEGAS_Namespace::PartialIntegrals( ){
    LD FuncPoint, point[NDim];
    int bins[NDim];
    LD inv_dist;
    LD AbsInt=0;

    // you can reset the weights at the end of UpdateBins(), so you don't need to reset them here.
    // memset(weights , 0 ,sizeof  weights);// They say is the fastest way to set an array to 0;

    // you get NPoints number of points
    for(int np=0 ; np <AdaptPoints ;++np){
        
        // The contribution of each point is |f(x)|/p(x), and 1/p(x)=Nbins*binsize (you extract this information when you get the point). 
        inv_dist=1;
        
        // fill a point[NDims]. Get a random bin from each dimention. Here is where you can get 1/p(x).
        // Also in order to get the weight from this, you need to know in what bin is every point[dim].
        for(int dim = 0 ; dim < NDim ; ++dim){
            bins[dim]=RandomBin();

            point[dim] = Random( Grid[dim][bins[dim]] , Grid[dim][bins[dim]+1] ); 
            inv_dist*=NBin*(Grid[dim][bins[dim]+1] - Grid[dim][bins[dim]]);
        }
        Integrand( point , &FuncPoint );
        AbsInt +=  fabs(FuncPoint) * inv_dist;
        
        // This is the partial integral ( in the bin of dim, and [0,1] for all other dims). 
        // In each bin of each dim you just sum the contribution |f|/p.
        // You don't double-count anything because the dimensions are independent.
        for(int dim = 0 ; dim < NDim ; ++dim)
        {
            weights[dim][bins[dim]]+=fabs(FuncPoint) * inv_dist;
        }
    }
    return AbsInt;
}   





#endif