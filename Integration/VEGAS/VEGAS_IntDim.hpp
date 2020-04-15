#ifndef VEGAS_BinInt
#define VEGAS_BinInt
#include"VEGAS.hpp"



VEGAS_Template
LD VEGAS_Namespace::IntegrateDim(int dim, LD x){
    LD IntD=1;
    // use RandomBin to get random number in all other dimentions in all of their bins.

    return IntD;

}





    
 
VEGAS_Template
LD VEGAS_Namespace::Integrate1D(int dim , int bin , LD point[Dim]  ){
    LD Func_point;
    LD range=Grid[dim][bin+1]-Grid[dim][bin];

    LD Int1D=0;

    for(int n_point=0 ; n_point < PointsPerBin ; ++n_point){
        point[dim]=Random(Grid[dim][bin] , Grid[dim][bin+1]);
        Integrand( point, &Func_point );
        // std::cout<<point[dim]<<"  "<<Func_point<<std::endl;
        Int1D+=Func_point;
    }

    return Int1D*range/PointsPerBin;
}    

// #define Alternative
#ifndef Alternative
VEGAS_Template
LD VEGAS_Namespace::Integrate1D(int dim , LD point[Dim]  ){
    LD Int1D=0;
    for (  int bin=0; bin <Nbins ; ++bin ){
        Int1D+=Integrate1D( dim , bin , point  );
    }

    return Int1D;
}    
#endif


// Alternative way to define Integrate1D( int dim , LD point) using RandomBin. Slower
#ifdef Alternative
VEGAS_Template
LD VEGAS_Namespace::Integrate1D(int dim , LD point[Dim]  ){
    LD Func_point;
    LD range;
    LD Int1D[Nbins];
    int n_points[Nbins];

    for(int bin=0 ; bin<Nbins ; ++bin ){Int1D[bin]=0; n_points[bin]=0;}

    
    int bin;
    for(int n_p=0 ; n_p < Nbins*PointsPerBin ; ++n_p){
        bin=RandomBin(dim);
        n_points[bin]++;

        range=Grid[dim][bin+1]-Grid[dim][bin];
        point[dim]=Random(Grid[dim][bin] , Grid[dim][bin+1]);

        Integrand( point, &Func_point );
        Int1D[bin]+=Func_point*range; 
    }
    LD Int1=0;
    for(int bin=0 ; bin<Nbins ; ++bin ){Int1+=Int1D[bin]/n_points[bin];  }

    return Int1;
}    

#endif
    

 



#endif