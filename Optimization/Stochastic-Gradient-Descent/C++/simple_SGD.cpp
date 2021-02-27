#include<iostream>
#include<vector>
#include<random>

#include"SGD.hpp"
#include"ModelFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;


// the loss function for one dimension. The class lossFunc averages over all dimensions.
LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

// the derivative of the loss function for one dimension.
LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}


// basically macros for the model function and its derivative 
using MFunc= void (*)(vector<LD> *x, vector<LD> *w, vector<LD> *output);
using MDer= void (*)(unsigned int i, std::vector<LD> *x, std::vector<LD> *w, std::vector<LD> *dsdw);


// the model
void f(vector<LD> *x, vector<LD> *w, vector<LD> *signal){
    (*signal)[0]=(*x)[0]*(*w)[0]+ (*w)[1];
}

// the model's derivative. Clearly there should be better ways to define the derivative
void dfdw_i(unsigned int i, vector<LD> *x, vector<LD> *w, vector<LD> *dsdw){
    if(i==0){ (*dsdw)[0]=(*x)[0];}
    if(i==1){ (*dsdw)[0]=1;}

}

// setup the model
modelFunc<LD> model(f,dfdw_i,vector<unsigned int>{1,1},vector<LD>{1,1});
// this is the loss function
lossFunc<LD,modelFunc<LD>> Q(Q_i,dQds_i,&model);


// #define Vanilla
// #define RMSprop
// #define AdaDelta
// #define Adam
// #define AdaMax
#define NAdam

// we\ll need these vectors to pass the data
using vec2=vector<vector<LD>>;
vec2 X,Y;


#ifdef Vanilla
using strategy=VanillaSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,1e-2}
#endif


#ifdef RMSprop
using strategy=RMSpropSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,1-1e-2,1e-5,1e-2}
#endif

#ifdef AdaDelta
using strategy=AdaDeltaSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,1-1e-2,1e-5,1}
#endif

#ifdef Adam
using strategy=AdamSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

#ifdef AdaMax
using strategy=AdaMaxSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

#ifdef NAdam
using strategy=NAdamSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,&X,&Y,0.9,0.999,1e-8,1e-2}
#endif

int main(){
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_real_distribution<LD> UnDist{-1,1};   
    LD x=0;
    for(int i=0;i<50;++i){
        x=UnDist(RndE);
        X.push_back({x});
        Y.push_back({2*x+3});
    }


    strategy  Strategy(params);
    StochasticGradientDescent<LD, strategy> SGD( &Strategy );
    SGD.run(1e-5, 1e-5, 250, 50000);

    // print the results
    cout<<"w=(";
    for(unsigned int i=0 ; i<model.w.size() ; ++i){
        cout<<model.w[i];
        if(i!=model.w.size()-1){cout<<", ";}
        else{cout<<")\n";}
    }

    
    LD Qmean=0;
    for(unsigned int i=0 ; i<X.size() ; ++i){
        model(&X[i]);
        Qmean+=Q(model.signal,Y[i]);
    }
    Qmean=Qmean/X.size();
    
    cout<<"No steps: "<<Strategy.steps.size()<<"\t";
    cout<<"mean error, Q= "<<Qmean<<endl;
    
    return 0;
}