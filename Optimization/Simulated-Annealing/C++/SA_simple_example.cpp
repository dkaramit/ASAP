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



typedef LD (*func)(vector<LD> x) ;


LD f(vector<LD> x){

    return x[0]*x[0]+x[1]*x[1] ;
}

 
int main(){
    vector< array<LD,2> > region{{-1,1},{-1,1}};
    vector<LD> x0{1,1};
    vector<LD>sigma{1e-2,1e-2};


    LD T0=std::abs(f(x0)*10+1), k=1-1e-3, MinT=0.,  tol=1e-5 , p0=0.8 ,k0=1.1;
    int IterationT=50, Nstar=150, N0=100;

    SimulatedAnnealing<LD,func> SA(f,region,x0,T0,k,IterationT,MinT,sigma,tol,Nstar,p0,N0,k0);


    SA.run(false,false);
    for(auto _:SA.x){ cout<<_<<endl;}
    cout<<SA.T<<"  "<<SA.AccProb<<"  "<<"  "<<SA.E <<endl; 


    return 0;
}