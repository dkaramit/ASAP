#include<iostream>
#include<vector>

#include"GD.hpp"
#include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;

// you can do this
// using func= LD(*)(const vector<LD> &x);
// LD f(const vector<LD> &x){return 1-std::exp(-(x[0]*x[0]+x[1]*x[1]));}

// The following, though, is much more powerful, as you can pass all kinds of extra parameters
class func{
    public:
    
    LD Z;
    func(){this->Z=0;};
    func(LD z){this->Z=z;};
    ~func(){};
    
    func& operator=(const func &f){this->Z=f.Z;  return *this;}

    LD operator()(const vector<LD> &x){return this->Z-std::exp(-(x[0]*x[0]+x[1]*x[1]));}
};

// global (for this example)
func f(1);
targetFunc<LD,func> target(f,1e-5);
vector<LD> x0={-.5,.2};


// uncomment the strategy you would like to see


// #define Vanilla //run vanilla GD
// #define AdaDelta //run AdaDelta GD
// #define RMSprop //run RMSprop GD
// #define Adam //run Adam GD
// #define AdaMax //run AdaMax GD
#define NAdam //run NAdam GD

#ifdef Vanilla
using strategy=VanillaGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 1e-2}
#endif

#ifdef AdaDelta
using strategy=AdaDeltaGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 1-1e-2, 1e-6, 1}
#endif

#ifdef RMSprop
using strategy=RMSpropGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 1-1e-3, 1e-5, 1e-2}
#endif

#ifdef Adam
using strategy=AdamGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 0.9, 0.999, 1e-8, 1e-2}
#endif

#ifdef AdaMax
using strategy=AdaMaxGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 0.9, 0.999, 1e-8, 1e-2}
#endif

#ifdef NAdam
using strategy=NAdamGD<LD,targetFunc<LD,func>>;
#define params {target, x0, 0.9, 0.999, 1e-8, 1e-2}
#endif

int main(){
   
    GradientDescent<LD,strategy> GD( strategy(params) );
    
    //run it 
    GD.run(1e-6,1e-6,100,50000);
    
    #if 0 
    // print all the steps
    for(auto step:GD.steps){
        for(auto x:step){cout<<x<<"\t";}
        cout<<endl;
    }
    cout<<"======================================================\n";
    #endif

    cout<<"N0 steps: "<<GD.strategy.steps.size()<<"\n";
    cout<<"minimum at x0=("<<GD.strategy.x[0]<<","<<GD.strategy.x[1]<<")"<<"\t";
    cout<<"with f(x0)="<<f(GD.strategy.x);
    cout<<endl;

    return 0;
}