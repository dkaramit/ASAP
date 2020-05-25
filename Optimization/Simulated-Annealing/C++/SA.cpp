#include<iostream>

#include"SA.hpp"


#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;



#define dim 10
typedef LD (*func)(LD x[dim]) ;


LD f(LD x[dim]){
    LD r=0;
    // for(int d ; d<dim ; ++d){ r+=pow(x[d],2);}
    for(int d ; d<dim-1 ; ++d){ r+=  pow(1-x[d],2) +500*pow(x[d+1]-x[d]*x[d],2) ;}

    return r  ;
}

 
int main(){
    LD region[dim][2];
    LD sigma[dim];
    
    LD x0[dim];
    for(int d ; d<dim ; ++d) { 
        x0[d]=0.2; sigma[d]=1e-3; 
        region[d][0]=-20;
        region[d][1]=20;
    }

    LD T0=f(x0)*10+1, k=1-5e-3, MinT=0.,  tol=1e-3 , p0=0.8 ,k0=1.1;
    int IterationT=250, Nstar=150, N0=50;

    SimulatedAnnealing<LD,func,dim> SA(f,region,x0,T0,k,IterationT,MinT,sigma,tol,Nstar,p0,N0,k0);

    // first run
    SA.run(false,false );
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 
    for(int d ; d<dim ; ++d){ cout<<SA.x[d]<<endl;}

    // restart with smaller sigma 
    for(int d ; d<dim ; ++d) { SA.sigma[d]=1e-6;}
    SA.run(false,true );
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 
    for(int d ; d<dim ; ++d){ cout<<SA.x[d]<<endl;}

    return 0;
}