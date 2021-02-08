#include<iostream>
#include<vector>
#include<array>
#include <iomanip>
#include <string>
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
LD sigmoidActivationDerivative(LD x){return std::exp(-x)*std::pow(sigmoidActivation(x),2.);};


LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}


int main(){
    //some activation functions
    activationType<LD,Func> lin(linearActivation,linearActivationDerivative);
    activationType<LD,Func> sig(sigmoidActivation,sigmoidActivationDerivative);



    const unsigned int  total_layers=3;

    // array of activation functins in each layer
    array<activationType<LD,Func>, total_layers-1> activations{sig,lin};
    // this is how the network is constructed
    array<unsigned int, total_layers> nodes{2,2,1};
    FFANN<LD, Func, total_layers> brain(nodes,activations);
    brain.init_biases(-1,1);
    brain.init_weights(-1,1);

    loss<LD, FFANN<LD, Func, total_layers>> Q(Q_i,dQds_i,&brain);
    Vanilla_SGD<FFANN<LD, Func, total_layers>, loss<LD, FFANN<LD, Func, total_layers>>, LD  > 
    strategy(&brain,&Q,1e-1); 

    vector<vector<LD>> data_in{{1,1},{0,0},{1,0},{0,1}};
    vector<vector<LD>> data_out{{0},{0},{1},{1}};

    brain.SGD(&strategy,&data_in,&data_out,1e-3,1e-3,150,15000);





    /*print the results*/
    vector<LD> signal,target;
    LD meanQ=0;
    LD maxQ=0;

    for(unsigned int i=0; i<data_in.size(); ++i){
        cout<<"data point: (";
        
        for(unsigned int j=0; j<data_in[i].size(); ++j){
            cout<<data_in[i][j];

            if(j<data_in[i].size()-1){cout<<",";}

        }
        cout<<")\n";

        signal=brain(data_in[i]);
        
        cout<<"FFANN gives: (";
        for(unsigned int j=0; j<signal.size(); ++j){
            cout<< signal[j];
            if(j<signal.size()-1){cout<<",";}
        }
        cout<<")\t";
        
        target=data_out[i];
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

    meanQ=meanQ/((LD) data_out.size());
    cout<<"max loss: "<<maxQ<<endl;
    cout<<"mean loss: "<<meanQ<<endl;

    return 0;
}