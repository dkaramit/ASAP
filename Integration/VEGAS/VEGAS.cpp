#include<iostream>
#include"VEGAS.hpp"
// 

#define NDim 5
#define NBin 12
#define _NPoints 1000

#define LD  long double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[NDim], LD *retrn );

// Define a function
void f( LD x[NDim], LD *retrn ) {
    (*retrn)=1  ;

    for( int i=0; i<NDim ; ++i  ) {  (*retrn)*=-exp(- pow(x[i] - 0.9,2)*50. ); }
    

}



#define for_all for( int i=0; i<NDim ; ++i  ) for( int j=0; j<NBin ; ++j  )
#define for_dim for( int i=0; i<NDim ; ++i  ) 
#define for_bin for( int j=0; j<NBin ; ++j  )

int main(){
    VEGAS<LD,Func,NDim,NBin> Integral(f,_NPoints,150,0.1);
    // Integral.PrintGrid(0);
    // Integral.PrintGrid(1);
    // std::cout<<Integral.Random(1e-8,2e-4)<<std::endl;
    // std::cout<<Integral.RandomBin(0)<<std::endl;
    // std::cout<<Integral.IntegrateTot()<<std::endl;
    // Integral.CalculateWeights();
    // Integral.PartialIntegrals();
    // Integral.CheckWeights();
    // Integral.PrintWeights();

    std::cout<<"============================================"<<std::endl;
    Integral.PrintGrid();
    std::cout<<Integral.IntegrateTot()<<std::endl;

    for (int i=0 ; i<50; ++i){Integral.UpdateBins();}   
    std::cout<<Integral.IntegrateTot()<<std::endl;
    std::cout<<"============================================"<<std::endl;
    Integral.PrintGrid();






}