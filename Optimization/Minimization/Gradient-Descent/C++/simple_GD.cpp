#include<iostream>
#include<vector>
#include<random>

#include"GD.hpp"
#include"Function.hpp"



using std::cout;
using std::endl;


template<class LD>
class func: public Function<LD>{
    public:

    func(){}
    func(const std::vector<LD> &x0):Function<LD>(x0){}

    LD operator()(std::vector<LD> &x){
        // return std::log(1+ std::pow((x[0]-2),2) + std::pow((x[1]-3*x[0]*x[0]),2));
        return std::pow((x[0]-2),2)+std::pow((x[1]-1),2);
    }
};



#ifndef LONG
    #define LONG long
#endif

#define LD LONG double


std::vector<LD> x0={0,0};
func<LD> f(x0); 



// #define Vanilla
// #define RMSprop
// #define AdaDelta
// #define Adam
// #define AdaMax
#define NAdam




#ifdef Vanilla
using strategy=VanillaGD<LD, func<LD>> ;
#define params {&f,1e-2}
#endif


#ifdef RMSprop
using strategy=RMSpropGD<LD, func<LD>> ;
#define params {&f,1-1e-2,1e-5,1e-2}
#endif

#ifdef AdaDelta
using strategy=AdaDeltaGD<LD, func<LD>> ;
#define params {&f,1-1e-2,1e-5,1}
#endif

#ifdef Adam
using strategy=AdamGD<LD, func<LD>> ;
#define params {&f,0.9,0.999,1e-8,1e-2}
#endif

#ifdef AdaMax
using strategy=AdaMaxGD<LD, func<LD>> ;
#define params {&f,0.9,0.999,1e-8,1e-2}
#endif

#ifdef NAdam
using strategy=NAdamGD<LD, func<LD>> ;
#define params {&f,0.9,0.999,1e-8,1e-2}
#endif

int main(){

    strategy  GD(params);
    GD.run(1e-4, 1e-3, 5000, 15000);




    for(unsigned int s=0; s<GD.steps.size(); ++s){
        cout<<f(GD.steps[s])<<" ";
        for(unsigned int i=0; i<f.dim; ++i){
            cout<<GD.steps[s][i];
            if(i==f.dim-1){cout<<endl;}
            else{cout<<" ";}
        }
    }


    cout<<f(f.x)<<" ";    
    for(unsigned int i=0; i<f.dim; ++i){
        cout<<f.x[i];
        if(i==f.dim-1){cout<<endl;}
        else{cout<<" ";}
    }


    cout<<f(f.minimum)<<" ";    
    for(unsigned int i=0; i<f.dim; ++i){
        cout<<f.minimum[i];
        if(i==f.dim-1){cout<<endl;}
        else{cout<<" ";}
    }

    return 0;
}