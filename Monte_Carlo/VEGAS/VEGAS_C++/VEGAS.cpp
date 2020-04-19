#include<iostream>
#include"VEGAS.hpp"
// 

// Dimention of integral
#define NDim 2

// number of bins (the same in every dimention)
#define NBin 7

// number of points in each evaluation of the integral
#define NPoints 3000
// number of batches (each batch calculates the integral using NPoints number of poins).
#define NBatches 10


// Number of interations to use to refine the grid
#define NAdapts 25
// Number of points to use when refining the grid
#define AdaptPoints 500


// The constant that multiplies the regulated weights in the logarithm (you can take it to be ~1000).
// the function that regulates the weights is different that what peaple use.
//  K_const=0 implies no logarithmic term
#define constK 1000

// The damping exponent. This regulates how fast the grid adapts. It should be in [0.2,2],
// but I find that 0.5 usually works  given large enough NAdapts.
// Large alpha destibilizes the adaptation, and small aplha results to slow adaptation. 
#define alpha 0.5


#define LD  double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[NDim], LD *retrn );

// example function
// void f( LD x[NDim], LD *retrn ) {
//     (*retrn)=1  ;
//     for( int i=0; i<NDim ; ++i  ) {  (*retrn)*=200*exp(- pow(x[i] - 0.1,2)*20. ); }
// }

// see that it adapts correctly to dim=0, and leaves dim=1 mostly unaffected.
void f( LD x[NDim], LD *retrn ) {
    (*retrn)= 40000*exp( - pow(x[0]-0.5,2)*150.  )  ;

}


#define for_all for( int i=0; i<NDim ; ++i  ) for( int j=0; j<NBin ; ++j  )
#define for_dim for( int i=0; i<NDim ; ++i  ) 
#define for_bin for( int j=0; j<NBin ; ++j  )

int main(){
    VEGAS<LD,Func,NDim,NBin> Integral(f,NPoints,NBatches,NAdapts, AdaptPoints ,constK,alpha);
    
    // Integral.PrintGrid();
    // Integral.PrintGrid(1);
    
    
    // std::cout<<Integral.Random( Integral.Grid[0][0],Integral.Grid[0][1] )<<std::endl;
    // std::cout<<Integral.RandomBin(0)<<std::endl;
    
    // std::cout<<Integral.IntegrateTot()<<std::endl;
    
    
    // Integral.CalculateWeights();
    // Integral.CheckWeights();
    // Integral.PrintWeights();

    #if 0 // See how the weights are updated
    std::cout<<"============================================"<<std::endl;
    Integral.PrintGrid();

    for (int i=0 ; i<50; ++i){Integral.UpdateBins();}   
    

    std::cout<<"============================================"<<std::endl;
    Integral.PrintGrid();
    #endif



    #if 0 // Check the (relative) variance before and after adaptation

    LD res,var;
    Integral.IntegrateTot( &res,&var );
    std::cout<<  res <<" +/- "<<  sqrt(var)/res*100 <<"%" <<std::endl;

    for (int i=0 ; i<25; ++i){Integral.UpdateBins();}   
    // std::cout<<Integral.IntegrateTot()<<std::endl;

    Integral.IntegrateTot( &res,&var );
    std::cout<<  res <<" +/- "<<  sqrt(var)/res*100 <<"%" <<std::endl;
    

    #endif

    #if 0
    for (int i=0 ; i<20; ++i){Integral.UpdateBins();}   
    
    LD res,sigma,R;
    R=Integral.IntegrateBatch( &res,&sigma );
    std::cout<<  res <<" +/- "<<  sigma/res*100 <<"%" <<"  "<< R<<std::endl;
    #endif

    LD res,sigma,R;
    R=Integral.Integrate( &res,&sigma );

    std::cout<<"Result= "<<  res <<" +/- "<<  sigma/res*100 <<"%" <<", with R="<< R<<std::endl;

    Integral.PrintGrid();
    return 0 ;
}



