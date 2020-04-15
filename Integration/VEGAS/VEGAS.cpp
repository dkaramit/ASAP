#include<iostream>
#include"VEGAS.hpp"
// 

#define Dim 6
#define Nbins 50
#define PointsPerBin 100000

#define LD double


// define the type of function to be used in VEGAS template
typedef void (*Func) (LD x[Dim], LD *retrn );

// Define a function
void f( LD x[Dim], LD *retrn ) {
    (*retrn)=1  ;

    for( int i=0; i<Dim ; ++i  ) {  (*retrn)*=x[i] ; }
    

}

void G(LD x[1], LD r[1]){

    r[0]=sin(x[0])*sin(x[0]);
}


#define for_all for( int i=0; i<Dim ; ++i  ) for( int j=0; j<Nbins ; ++j  )
#define for_dim for( int i=0; i<Dim ; ++i  ) 
#define for_bin for( int j=0; j<Nbins ; ++j  )

int main(){
    VEGAS<LD,Func,Dim,Nbins> Integral(f, PointsPerBin, 10);
    // Integral.PrintGrid();
    // Integral.PrintGrid(0);
    // Integral.PrintGrid(1);
    // std::cout<<Integral.Random(1e-8,2e-4)<<std::endl;
    // std::cout<<Integral.RandomBin(0)<<std::endl;
    // Integral.IntegrateDim( 0,0 );
    
    

    // -- Example of both Integrate1D 
    #if 1
    LD point[Dim];
    for_dim point[i]=i+1; 
    int dim=1, bin=3;

    point[dim]=0;//this is updated in Integrate1D
    
    std::cout<<"integral in ("<<Integral.Grid[dim][bin]<< ", "<<Integral.Grid[dim][bin+1]<<" ): for dimension "<<dim<<std::endl;
    std::cout<<Integral.Integrate1D(dim,bin,point)<<std::endl;// \int_{0}^{bin} dx f( point )
    std::cout<<"integral in (0,1) for dimension "<<dim<<" :"<<std::endl;
    std::cout<<Integral.Integrate1D(dim,point)<<std::endl;// \int_{0}^{1} dx f( point )
    // 
    
    // point[dim]=1;
    // std::cout<<Integral.IntegrateDim(dim, point[dim] )<<std::endl;// \int_{0}^{1} dx f( point )
    #endif


    








    return 0;
}