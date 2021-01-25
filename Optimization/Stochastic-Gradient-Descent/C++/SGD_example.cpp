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

// this is the model. It is defined as a function of x that depends on various parameters w.
void testF(const vector<LD> &x, const vector<LD> &w, vector<LD> &y){
    y[0]=w[0]*x[0]+w[1];
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




targetFunc<LD,TFunc> target(testF,{0,-2});
lossFunc<LD,QFunc, targetFunc<LD,TFunc>> loss(MSE,&target);
vec2 X,Y;

// #define Vanilla
// #define RMSprop
// #define AdaDelta
// #define Adam
// #define AdaMax
#define NAdam

#ifdef Vanilla
using strategy=VanillaSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,1e-2}
#endif

#ifdef RMSprop
using strategy=RMSpropSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,1-1e-2,1e-5,1e-2}
#endif

#ifdef AdaDelta
using strategy=AdaDeltaSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,1-1e-2,1e-5,1}
#endif

#ifdef Adam
using strategy=AdamSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

#ifdef AdaMax
using strategy=AdaMaxSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

#ifdef NAdam
using strategy=NAdamSGD<LD,lossFunc<LD,QFunc, targetFunc<LD,TFunc>>> ;
#define params {loss,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

#if 1
int main(){
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_real_distribution<LD> UnDist{-1,1};
    
    LD x=0;

    for(int i=0;i<5000;++i){
        x=UnDist(RndE);
        X.push_back({x});
        Y.push_back({2*x+3});
    }
    
    StochasticGradientDescent<LD,strategy> SGD( strategy(params) );
    SGD.run(1e-5, 1e-5, 250, 5000);


    // print the results
    cout<<"w=(";
    for(unsigned int i=0 ; i<target.w.size() ; ++i){
        cout<<target.w[i];
        if(i!=target.w.size()-1){cout<<", ";}
        else{cout<<")\n";}
    }

    
    LD Qmean=0;
    for(unsigned int i=0 ; i<X.size() ; ++i){
        Qmean+=loss(X[i],Y[i]);
    }
    Qmean=Qmean/X.size();
    
    cout<<"No steps: "<<SGD.strategy.steps.size()<<"\t";
    cout<<"mean error, Q= "<<Qmean<<endl;

    
    return 0;
}

#endif