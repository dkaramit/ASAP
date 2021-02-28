#include<iostream>
#include<vector>
#include<array>
#include <iomanip>
#include <string>
#include <fstream>

#include"FFANN.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::vector;
using std::array;

LD linearActivation(LD x){return x;}
LD linearActivationDerivative(LD x){return 1;}

LD sigmoidActivation(LD x){return 1/(1+std::exp(-x));}
LD sigmoidActivationDerivative(LD x){return std::exp(-x)*std::pow(sigmoidActivation(x),2.);}

LD expActivation(LD x){return std::exp(x) ;}
LD expActivationDerivative(LD x){return std::exp(x) ;}

LD dexpActivation(LD x){return std::exp(x) + std::exp(-x);}
LD dexpActivationDerivative(LD x){return std::exp(x) - std::exp(-x) ;}

LD tanhActivation(LD x){return std::tanh(x) ;}
LD tanhActivationDerivative(LD x){return 1-std::tanh(x)*std::tanh(x);}

LD gaussActivation(LD x){return std::exp(-x*x) ;}
LD gaussActivationDerivative(LD x){return -2*x*std::exp(-x*x) ;}

LD softPlusActivation(LD x){return std::log(1 + std::exp(x));}
LD softPlusActivationDerivative(LD x){return  1/(1 + std::exp(-x));}



LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}

// #define vanilla
// #define rms_prop
// #define ada_delta
// #define adam
// #define adaMax
#define nadam

int main(){
    //some activation functions
    activationType<LD> lin(linearActivation,linearActivationDerivative);
    activationType<LD> sig(sigmoidActivation,sigmoidActivationDerivative);
    activationType<LD> exp(expActivation,expActivationDerivative);
    activationType<LD> dexp(dexpActivation,dexpActivationDerivative);
    activationType<LD> tanh(tanhActivation,tanhActivationDerivative);
    activationType<LD> gauss(gaussActivation,gaussActivationDerivative);
    activationType<LD> softPlus(softPlusActivation,softPlusActivationDerivative);

    /*simplest fit*/
    vector<activationType<LD>> activations{sig,dexp};
    vector<unsigned int> nodes{1,4,2};

    /*not so simple fit, but still works*/
    // vector<activationType<LD>> activations{gauss,gauss,softPlus};
    // vector<unsigned int> nodes{1,5,5,2};

    FFANN<LD> brain(nodes,activations);
    brain.init_biases(-1e-1,1e-1);
    brain.init_weights(-1e-1,1e-1);


    loss<LD, FFANN<LD>> Q(Q_i,dQds_i,&brain);
    #ifdef vanilla
    Vanilla_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  >
    strategy(&brain,&Q,1e-2); 
    #endif
     
    #ifdef rms_prop
    RMSprop_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  > 
    strategy(&brain,&Q,0.999,1e-4,1e-2); 
    #endif

    #ifdef ada_delta
    AdaDelta_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  > 
    strategy(&brain,&Q,0.9999,1e-5,1); 
    #endif

    #ifdef adam
    Adam_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  > 
    strategy(&brain,&Q,0.99,0.9999,1e-8,1e-2); 
    #endif

    #ifdef adaMax
    AdaMax_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  > 
    strategy(&brain,&Q,0.99,0.9999,1e-8,1e-2); 
    #endif

    #ifdef nadam
    NAdam_SGD<FFANN<LD>, loss<LD, FFANN<LD>>, LD  > 
    strategy(&brain,&Q,0.9,0.999,1e-8,1e-3); 
    #endif



    vector<vector<LD>> logT;
    vector<vector<LD>> rdofs;
    
    LD tmp1,tmp2;
    std::ifstream data_file("eos2020.dat");


    while (true){
        data_file>>tmp1;
        logT.push_back(vector<LD>{std::log10(tmp1)});
        
        data_file>>tmp1;
        data_file>>tmp2;
        rdofs.push_back(vector<LD>{tmp1,tmp2});

        if (data_file.eof()){
            break;
        }
    }
    
    cout<<brain.SGD(&strategy,&logT,&rdofs,1e-3,1e-3,2*logT.size(),5000000)<<endl;
    
    for(unsigned int i=0; i<logT.size(); ++i){
        cout<<logT[i][0]<<","<<rdofs[i][0]<<","<<rdofs[i][1]<<",";
        brain.inputSignal(logT[i]);
        brain.feedForward();
        cout<<brain.signals[brain.total_layers-1][0]<<","<<brain.signals[brain.total_layers-1][1];
        

        cout<<"\n";
    }
    

    //use this to easily stop when get the data in python
    cout<<"end"<<"\n";

    /*print the results*/
    vector<LD> signal,target;
    LD meanQ=0;
    LD maxQ=0;

    for(unsigned int i=0; i<logT.size(); ++i){
        cout<<"data point: (";
        
        for(unsigned int j=0; j<logT[i].size(); ++j){
            cout<<logT[i][j];

            if(j<logT[i].size()-1){cout<<",";}

        }
        cout<<")\n";

        signal=brain(logT[i]);
        
        cout<<"FFANN gives: (";
        for(unsigned int j=0; j<signal.size(); ++j){
            cout<< signal[j];
            if(j<signal.size()-1){cout<<",";}
        }
        cout<<")\t";
        
        target=rdofs[i];
        cout<<"The target is: (";
        for(unsigned int j=0; j<target.size(); ++j){
            cout<< target[j];
            if(j<target.size()-1){cout<<",";}
        }
        cout<<")\n";
        cout<<endl;

        meanQ+=Q(signal,target);
        if (Q(signal,target)>maxQ){maxQ=Q(signal,target);}

    }

    meanQ=meanQ/((LD) rdofs.size());
    cout<<"max loss: "<<maxQ<<endl;
    cout<<"mean loss: "<<meanQ<<endl;

    return 0;
}