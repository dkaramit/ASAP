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

int main(){
    func f(1);
    targetFunc<LD,func> target(f,1e-5);


    AdamGD<LD,targetFunc<LD,func>> GD(target,{-.5,.2},0.9,0.999,1e-8,1e-2);

    //run it 
    GD.run(1e-6,1e-6,100,50000);
    
    // print all the steps
    #if 0 
    for(auto step:GD.steps){
        for(auto x:step){cout<<x<<"\t";}
        cout<<endl;
    }
    cout<<"======================================================\n";
    #endif

    cout<<"N0 steps: "<<GD.steps.size()<<"\n";
    cout<<"minimum at x0=("<<GD.x[0]<<","<<GD.x[1]<<")"<<"\t";
    cout<<"with f(x0)="<<f(GD.x);
    cout<<endl;

    return 0;
}