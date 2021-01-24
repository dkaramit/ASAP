#include<iostream>
#include<vector>
#include<random>

#include"SGD.hpp"
#include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;




using TFunc= void (*)(const vector<LD> &x, const vector<LD> &w, vector<LD> &y);

void testF(const vector<LD> &x, const vector<LD> &w, vector<LD> &y){
    y[0]=w[0]*x[0]+w[1];
    y[1]=w[0]+w[1]*x[1];
}

using QFunc= LD (*)(targetFunc<LD,TFunc> f, const vector<LD> &x, const vector<LD> &y);
LD MSE(targetFunc<LD,TFunc> f, const vector<LD> &x, const vector<LD> &y){
    vector<LD> fx=y;
    f(x,fx);

    LD sum=0;
    for(unsigned int  i=0; i<y.size(); ++i){
        sum+=(fx[i]-y[i])*(fx[i]-y[i]);
    }
    sum=sum/((LD) fx.size());

    return sum;    
}

using vec2=vector<vector<LD>>;



int main(){


    std::vector<LD> w={5,-1};
    vec2 X,Y;
    
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_real_distribution<LD> UnDist{-1,2};
    LD x=0;
    for(int i=0;i<500;++i){
        x=UnDist(RndE);
        X.push_back({x});
        Y.push_back({5*x+1});
    }
    
    targetFunc<LD,TFunc> target(testF,w);
    lossFunc<LD,QFunc, targetFunc<LD,TFunc>> loss(MSE,&target);
    VanillaSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> vSGD(loss,X,Y,1e-2);


    StochasticGradientDescent<LD,VanillaSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>>> 
    SGD(vSGD);
    
    SGD.run(1e-8, 1e-5, 250, 5000);
    
    cout<<target.w[0]<<"\t"<<target.w[1]<<endl;



    return 0;
}