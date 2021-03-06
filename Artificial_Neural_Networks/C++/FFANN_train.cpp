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


LD linearActivation(LD x){return x;}
LD linearActivationDerivative(LD x){return 1;}
LD sigmoidActivation(LD x){return 1/(1+std::exp(-x));}
LD sigmoidActivationDerivative(LD x){return std::exp(-x)*std::pow(sigmoidActivation(x),2.);};



// the loss function for one dimension. The class lossFunc averages over all dimensions.
LD Q_i(FFANN<LD> *model, unsigned int i, LD target){
    return (model->signals[model->total_layers-1][i]-target)*(model->signals[model->total_layers-1][i]-target);
}

// the derivative of the loss function for one dimension.
LD dQds_i(FFANN<LD> *model, unsigned int i, LD target){
    return 2*(model->signals[model->total_layers-1][i]-target);
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


    // array of activation functins in each layer
    vector<activationType<LD>> activations{sig,lin};
    // this is how the network is constructed
    vector<unsigned int> nodes{2,2,1};
    FFANN<LD> brain(nodes,activations);
    brain.init_biases(-1,1);
    brain.init_weights(-1,1);


    loss<LD> Q(Q_i,dQds_i,&brain);


    #ifdef vanilla
    Vanilla_SGD<FFANN<LD>, loss<LD>, LD  >
    strategy(&brain,&Q,1e-2); 
    #endif
     
    #ifdef rms_prop
    RMSprop_SGD<FFANN<LD>, loss<LD>, LD  > 
    strategy(&brain,&Q,0.999,1e-4,1e-2); 
    #endif

    #ifdef ada_delta
    AdaDelta_SGD<FFANN<LD>, loss<LD>, LD  > 
    strategy(&brain,&Q,0.999,1e-4,1); 
    #endif

    #ifdef adam
    Adam_SGD<FFANN<LD>, loss<LD>, LD  > 
    strategy(&brain,&Q,0.9,0.999,1e-8,1e-2); 
    #endif

    #ifdef adaMax
    AdaMax_SGD<FFANN<LD>, loss<LD>, LD  > 
    strategy(&brain,&Q,0.9,0.999,1e-8,1e-2); 
    #endif

    #ifdef nadam
    NAdam_SGD<FFANN<LD>, loss<LD>, LD  > 
    strategy(&brain,&Q,0.9,0.999,1e-8,1e-2); 
    #endif

    vector<vector<LD>> data_in{{1,1},{0,0},{1,0},{0,1}};
    vector<vector<LD>> data_out{{0},{0},{1},{1}};

    cout<<brain.SGD(&strategy,&data_in,&data_out,1e-5,1e-5,150,1000000)<<endl;





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