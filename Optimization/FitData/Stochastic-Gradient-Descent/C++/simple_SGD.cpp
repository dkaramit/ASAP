#include<iostream>
#include<vector>
#include<random>

#include"SGD.hpp"
#include"ModelBase.hpp"

using std::cout;
using std::endl;
using std::vector;

template<class LD>
class modelFunc: public modelBase<LD>{
    public:
    modelFunc()=default;
    modelFunc(const std::vector<unsigned int> &dimensions, const std::vector<LD> &w0):modelBase<LD>(dimensions,w0){};
    
    void operator()(){this->signal[0]=this->input[0]* this->w[0]+ this->w[1];}
    void derivative_w(unsigned int i){
        if(i==0){ this->dsdw[0]=this->input[0];}
        if(i==1){ this->dsdw[0]=1;}
    }
};



#ifndef LONG
#define LONG long
#endif

#define LD LONG double

// the loss function for one dimension. The class lossFunc averages over all dimensions.
LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

// the derivative of the loss function for one dimension.
LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}


// #define Vanilla
// #define RMSprop
// #define AdaDelta
// #define Adam
// #define AdaMax
#define NAdam



#ifdef Vanilla
using strategy=VanillaSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q, 1e-2}
#endif


#ifdef RMSprop
using strategy=RMSpropSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q, 1-1e-2,1e-5,1e-2}
#endif

#ifdef AdaDelta
using strategy=AdaDeltaSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,1-1e-2,1e-5,1}
#endif

#ifdef Adam
using strategy=AdamSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,0.9,0.999,1e-8,1e-2}
#endif

#ifdef AdaMax
using strategy=AdaMaxSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,0.9,0.999,1e-8,1e-2}
#endif

#ifdef NAdam
using strategy=NAdamSGD<LD, lossFunc<LD,modelFunc<LD>>> ;
#define params {&Q,0.9,0.999,1e-8,1e-2}
#endif

int main(){
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_real_distribution<LD> UnDist{-1,1};   
    // we\ll need these vectors to pass the data
    using vec2=vector<vector<LD>>;
    vec2 X,Y;
    LD x=0;
    for(int i=0;i<100;++i){
        x=UnDist(RndE);
        X.push_back({x});
        Y.push_back({2*x+3});
    }

    // setup the model
    modelFunc<LD> model(vector<unsigned int>{1,1},vector<LD>{1,1});
    // this is the loss function
    lossFunc<LD,modelFunc<LD>> Q(&X,&Y,Q_i,dQds_i,&model);

    strategy  SGD(params);


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
        model.setInput(X[i]);
        model();
        Qmean+=Q(Y[i]);
    }
    Qmean=Qmean/X.size();
    
    cout<<"No steps: "<<SGD.steps.size()<<"\t";
    cout<<"mean error, Q= "<<Qmean<<endl;
    
    
    return 0;
}