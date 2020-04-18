#include<iostream>
#include"VEGAS.hpp"
// 

#define NDim 6
#define NBin 10

#define _NPoints 500

#define _NBatches 100
#define LD  long double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[NDim], LD *retrn );

// Define a function
void f( LD x[NDim], LD *retrn ) {
    (*retrn)=1  ;

    for( int i=0; i<NDim ; ++i  ) {  (*retrn)*=200*exp(- pow(x[i] - 0.9,2)*20. ); }
    

}



#define for_all for( int i=0; i<NDim ; ++i  ) for( int j=0; j<NBin ; ++j  )
#define for_dim for( int i=0; i<NDim ; ++i  ) 
#define for_bin for( int j=0; j<NBin ; ++j  )

int main(){
    VEGAS<LD,Func,NDim,NBin> Integral(f,_NPoints,_NBatches ,2,.8);
    
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

    for (int i=0 ; i<20; ++i){Integral.UpdateBins();}   
    LD res,sigma,R;
    R=Integral.IntegrateBatch( &res,&sigma );
    std::cout<<  res <<" +/- "<<  sigma/res*100 <<"%" <<"  "<< R<<std::endl;




    return 0 ;
}



