#include<iostream>

#include<vector>
#include<array>

#include"SA.hpp"


#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;
using std::array;



#define dim 6
typedef LD (*func)(vector<LD> x) ;


LD f(vector<LD> x){
    LD r=0;
    // for(int d = 0 ; d<dim ; ++d){ r+=pow(x[d],2);}
    for(int d = 0 ; d < dim-1 ; ++d){ r+=  pow(1-x[d],2) +500*pow(x[d+1]-x[d]*x[d],2) ;}

    return r  ;
}

 
int main(){
    vector< array<LD,2> > region;
    vector<LD> x0;
    vector<LD>sigma;


    for(int d = 0 ; d<dim ; ++d) { 
        x0.push_back(0.2); sigma.push_back(1e-3); 
        region.push_back(array<LD,2>{-20,20});
    }

    LD T0=f(x0)*10+1, k=1-5e-3, MinT=0.,  tol=1e-3 , p0=0.8 ,k0=1.1;
    int IterationT=250, Nstar=150, N0=50;

    SimulatedAnnealing<LD,func> SA(f,region,x0,T0,k,IterationT,MinT,sigma,tol,Nstar,p0,N0,k0);

    // first run
    SA.run(false,false );
    for(auto _:SA.x){ cout<<_<<endl;}
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 

    // restart with smaller sigma 
    for(int d = 0 ; d<dim ; ++d) { SA.sigma[d]=1e-6;}
    SA.run(false,true );
    for(auto _:SA.x){ cout<<_<<endl;}
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 


    return 0;
}