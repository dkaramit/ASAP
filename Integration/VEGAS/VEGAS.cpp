#include<iostream>
#include"VEGAS.hpp"
// 

#define Dim 2
#define Nbins 100000

#define LD double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[Dim], LD retrn[Dim]);

// Define a function
void f( LD x[Dim], LD retrn[Dim] ) {

    for( int i=0; i<Dim ; ++i  ){

        retrn[i]=x[i]*2;
    }


}


#define for_all for( int i=0; i<Dim ; ++i  ) for( int j=0; j<Nbins ; ++j  )

int main(){
    VEGAS<LD,Func,Dim,Nbins> Integral(10);
    Integral.PrintGrid();
    // Integral.PrintGrid(0);
    // Integral.PrintGrid(1);



    return 0;
}