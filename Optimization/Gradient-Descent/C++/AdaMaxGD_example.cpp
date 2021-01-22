#include<iostream>

#include"GD.hpp"

#include"AdaMaxGD.hpp"

#include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;




using func= LD(*)(vector<LD> x);

LD f(vector<LD> x){return 1-std::exp(-(x[0]*x[0]+x[1]*x[1]));}



int main(){

    targetFunc<LD,func> target(f,1e-5);


    AdaMaxGD<LD,targetFunc<LD,func>> GD(target,{-.5,.2},0.9,0.999,1e-8,1e-2);



    GD.run(1e-6,1e-6,100,50000);

    for(auto step:GD.steps){
        for(auto x:step){cout<<x<<"\t";}
        cout<<endl;
    }

    cout<<"======================================================\n";
    vector<LD> g;
    target.Grad(GD.x,g);
    cout<<GD.steps.size()<<"\t"<<target(GD.x);
    cout<<"\t"<<GD.x[0]<<"\t"<<GD.x[1];
    cout<<"\t"<<g[0]<<"\t"<<g[1];
    cout<<endl;


    return 0;
}