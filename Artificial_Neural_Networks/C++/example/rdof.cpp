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


using Func= LD(*)(LD);

LD linearActivation(LD x){return x;}
LD linearActivationDerivative(LD x){return 1;}
LD sigmoidActivation(LD x){return 1/(1+std::exp(-x));}
LD sigmoidActivationDerivative(LD x){return std::exp(-x)*std::pow(sigmoidActivation(x),2.);}
LD expActivation(LD x){return std::exp(x);}
LD expActivationDerivative(LD x){return std::exp(x);}



LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}

// #define vanilla
// #define rms_prop
// #define ada_delta
#define adam

int main(){
    //some activation functions
    activationType<LD,Func> lin(linearActivation,linearActivationDerivative);
    activationType<LD,Func> sig(sigmoidActivation,sigmoidActivationDerivative);
    activationType<LD,Func> exp(expActivation,expActivationDerivative);


    // array of activation functins in each layer
    vector<activationType<LD,Func>> activations{sig,lin};
    // this is how the network is constructed
    vector<unsigned int> nodes{1,6,2};
    FFANN<LD, Func> brain(nodes,activations);
    brain.init_biases(-1e-1,1e-1);
    brain.init_weights(-1e-1,1e-1);


    loss<LD, FFANN<LD, Func>> Q(Q_i,dQds_i,&brain);
    #ifdef vanilla
    Vanilla_SGD<FFANN<LD, Func>, loss<LD, FFANN<LD, Func>>, LD  >
    strategy(&brain,&Q,1e-2); 
    #endif
     
    #ifdef rms_prop
    RMSprop_SGD<FFANN<LD, Func>, loss<LD, FFANN<LD, Func>>, LD  > 
    strategy(&brain,&Q,0.999,1e-4,1e-2); 
    #endif

    #ifdef ada_delta
    AdaDelta_SGD<FFANN<LD, Func>, loss<LD, FFANN<LD, Func>>, LD  > 
    strategy(&brain,&Q,0.9999,1e-5,1); 
    #endif

    #ifdef adam
    Adam_SGD<FFANN<LD, Func>, loss<LD, FFANN<LD, Func>>, LD  > 
    strategy(&brain,&Q,0.9,0.999,1e-8,1e-2); 
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

    #if 0
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
    #endif

    return 0;
}