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



int main(){
    //some activation functions
    activationType<LD> lin(linearActivation,linearActivationDerivative);
    activationType<LD> sig(sigmoidActivation,sigmoidActivationDerivative);

    // array of activation functins in each layer
    vector<activationType<LD>> activations{lin,lin,lin};


    // this is how the network is constructed
    vector<unsigned int> nodes{2,3,4,2};
    FFANN<LD> brain(nodes,activations);
    

    brain.fill_biases_with(1);
    brain.fill_weights_with(0.2);
    brain.update_weight(0,0,0,-2);
    brain.update_weight(2,1,0,5);
    brain.update_bias(0,0,-1);
    brain.update_bias(1,1,3);

    std::string S;

    vector<LD> inputSignal{0.1,-2};
    brain.inputSignal(inputSignal);

    S="--weights, biases, and signals--";
    cout<<setfill('=')<<setw(S.length()+25)<<S<<setfill('=')<<setw(25)<<""<<endl<<endl;
    brain(inputSignal);
    brain.printWeights();
    brain.printBiases();
    brain.printSignals();

    S="--derivatives using feedForwardDerivatives--";
    cout<<setfill('=')<<setw(S.length()+25)<<S<<setfill('=')<<setw(25)<<""<<endl<<endl;
    brain.feedForwardDerivatives();
    brain.printDerivatives();
    brain.printTotalDerivatives();
    
    S="--derivatives using backProp--";
    cout<<setfill('=')<<setw(S.length()+25)<<S<<setfill('=')<<setw(25)<<""<<endl<<endl;
    brain.feedForward();
    brain.backPropagation();
    brain.printDelta();
    brain.printDerivatives_w();
    brain.printDerivatives_b();
    
    S="--numerical derivatives--";
    cout<<setfill('=')<<setw(S.length()+25)<<S<<setfill('=')<<setw(25)<<""<<endl<<endl;
    brain.evaluate(inputSignal);
    brain.totalNumericalDerivative();
    brain.printNumericalDerivatives();
    brain.printNumericalDerivatives_w();
    brain.printNumericalDerivatives_b();



    /*==========================---initialize and fill---==========================*/
    // brain.init_biases(-1,1);
    // brain.init_weights(-1,1);
    // brain.fill_biases_with(-55);
    // brain.fill_weights_with(666);
    /*==========================---update and get---==========================*/
    // brain.update_weight(0,0,1,5);
    // brain.update_weight(1,1,1,5);
    // cout<<brain.get_weight(0,0,1)<<endl;
    // cout<<brain.get_weight(1,1,1)<<endl;
    // brain.update_bias(1,1,-5);//remember that biases[l][j] correspond to b^{(l+1)}_{j}
    // cout<<brain.get_bias(1,1)<<endl;
    /*==========================---print---==========================*/
    
    return 0;
}