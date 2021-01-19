#include<iostream>

#include"GD.hpp"
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

    targetFunc<LD,func> target(f);

    /*The targetFunc class works!*/
    // targetFunc<LD,func> T1=target;
    // targetFunc<LD,func> T2;
    // T2=target;
    // cout<<target(vector<LD>{1,2})<<endl;
    // cout<<T1(vector<LD>{1,2})<<endl;
    // cout<<T2(vector<LD>{1,2})<<endl;


    GradientDescent<LD,targetFunc<LD,func>> GD(target,vector<LD>{-2,1},1e-1,1e-8,10);

    /*the different functions work!*/
    // cout<<GD.target(vector<LD>{1,2})<<endl;
    // vector<LD>Grad;
    // Grad=target.Grad(vector<LD>{1,33});
    // for(LD gi:Grad){
    //     cout<<gi<<endl;
    // }

    // run and print the result
    GD.run();
    for(LD x:GD.x1){
        cout<<x<<endl;
    }

    // this is the path
    for(auto p:GD.points){
        cout<<p[0]<<" "<<p[1]<<endl;
    }



    return 0;
}