#include<iostream>
#include"VEGAS.hpp"
// 

#define Dim 200
#define Nbins 10
#define PointsPerBin 10

#define LD double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[Dim], LD retrn[Dim]);

// Define a function
void f( LD x[Dim], LD retrn[Dim] ) {

    for( int i=0; i<Dim ; ++i  ){

        retrn[i]=1;
    }


}


#define for_all for( int i=0; i<Dim ; ++i  ) for( int j=0; j<Nbins ; ++j  )

int main(){
    VEGAS<LD,Func,Dim,Nbins,PointsPerBin> Integral(10);
    Integral.PrintGrid();
    // Integral.PrintGrid(0);
    // Integral.PrintGrid(1);
    // std::cout<<Integral.Random(1e-8,2e-4)<<std::endl;
    // Integral.RandomGrid(199);
    // Integral.PrintRandomGrid();
    // Integral.PrintMeans();



    
    return 0;
}