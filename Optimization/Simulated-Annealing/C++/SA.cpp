#include<iostream>

#include"SA.hpp"


#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;



#define dim 2
typedef LD (*func)(LD x[dim]) ;


LD f(LD x[dim]){
    LD r=0;
    // for(int d ; d<dim ; ++d){ r+=pow(x[d],2);}
    r=pow(3-x[0],2) +300*pow(x[1]-x[0]*x[0],2);
    return r  ;
}

 
int main(){
    LD region[dim][2];
    LD sigma[dim];
    
    LD x0[dim];
    for(int d ; d<dim ; ++d) { 
        x0[d]=0.2; sigma[d]=1e0; 
        region[d][0]=-10;
        region[d][1]=10;
    }

    LD T0=f(x0)*10+1, k=1-5e-3, MinT=0.,  tol=1e-3 , p0=0.8 ,k0=1.1;
    int IterationT=150, Nstar=150, N0=50;

    SimulatedAnnealing<LD,func,dim> SA(f,region,x0,T0,k,IterationT,MinT,sigma,tol,Nstar,p0,N0,k0);

    // first run
    SA.run(false,false );
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 
    for(int d ; d<dim ; ++d){ cout<<SA.x[d]<<endl;}

    // restart with smaller sigma 
    for(int d ; d<dim ; ++d) { SA.sigma[d]=1e-3;}
    SA.run(false,true );
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 
    for(int d ; d<dim ; ++d){ cout<<SA.x[d]<<endl;}

    return 0;
}