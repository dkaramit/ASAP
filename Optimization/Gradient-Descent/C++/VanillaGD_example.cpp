#include<iostream>

#include"GD_base/GD.hpp"

#include"VanillaGD/VanillaGD.hpp"

#include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;




using func= LD(*)(vector<LD> x);

LD f(vector<LD> x){return x[0]*x[0]+x[1]*x[1];}



int main(){

    targetFunc<LD,func> target(f,1e-5);


    VanillaGD<LD,targetFunc<LD,func>> GD(target, {-2,5}, 1e-3);



    GD.run(1e-5,1e-8,50,5000);

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