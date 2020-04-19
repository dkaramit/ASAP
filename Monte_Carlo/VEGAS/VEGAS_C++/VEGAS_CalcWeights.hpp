#ifndef VEGAS_CalcWeights
#define VEGAS_CalcWeights
#include"VEGAS.hpp"
// this only helps to check and make sure that the weights are ok. In the Correct CalcWeights, I 
// regulate them with the dumping factor, so the check will fail.



// Calsulate the weights. Basically, you calculate int_{0}^{1} |f|, and as you sample you can also 
// get the partial integrals (since you know in which bin is each point). 
VEGAS_Template
LD VEGAS_Namespace::CalculateWeights( ){
    LD FuncPoint, point[NDim];
    int bins[NDim];
    LD inv_dist;
    LD AbsInt=0;

    memset(weights , 0 ,sizeof  weights);// They say is the fastest way to set an array to 0;

    // you get NPoints number of points
    for(int np=0 ; np <NPoints ;++np){
        
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
            weights[dim][bins[dim]]+=fabs(FuncPoint) * inv_dist ;
        }
    }
    // Since you have the partial integrals, the weight is this over the total integral of |f|.
    // You can check and see that the sum over the bits of each dim is 1.
    for(int dim = 0 ; dim < NDim ; ++dim)
        {
            for( int bin = 0 ; bin < NBin ; ++bin)
            {
                weights[dim][bin]=weights[dim][bin]/AbsInt;
            }
        }
    
    // return the integral of |f| over [0,1] in case you are curious. 
    return AbsInt/NPoints;
}


VEGAS_Template
void VEGAS_Namespace::CheckWeights(){
    LD tmp;

        for(int dim = 0 ; dim < NDim ; ++dim)
            {
                tmp=0;
                for( int bin = 0 ; bin < NBin ; ++bin)
                {
                    tmp+=weights[dim][bin];
                }
            std::cout<<tmp<<std::endl;
            }

}



#endif