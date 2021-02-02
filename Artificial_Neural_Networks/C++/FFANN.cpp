#include<iostream>
#include<vector>
#include<array>

#include"FFANN.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;
using std::array;


using Func= LD(*)(LD);

LD linearActivation(LD x){return x;}
LD linearActivationDerivative(LD x){return 1;}
LD sigmoidActivation(LD x){return 1/(1+std::exp(-x));}
LD sigmoidActivationDerivative(LD x){return std::exp(-x)*std::pow(sigmoidActivation(x),2.);};


#define total_layers 4
int main(){
    //some activation functions
    activationType<LD,Func> lin(linearActivation,linearActivationDerivative);
    activationType<LD,Func> sig(sigmoidActivation,sigmoidActivationDerivative);

    // array of number of nodes in each layer
    array<unsigned int, total_layers> nodes{2,3,4,2};
    // array of activation functins in each layer
    array<activationType<LD,Func>, total_layers-1> activations{lin,lin,lin};

    // this is how the network is constructed
    FFANN<LD, Func, total_layers> brain(nodes,activations);
    brain.fill_biases_with(1);
    brain.fill_weights_with(0.2);
    brain.update_weight(0,0,0,-2);
    brain.update_weight(2,1,0,5);
    brain.update_bias(0,0,-1);
    brain.update_bias(1,1,3);



    brain.inputSignal(vector<LD>{0.1,-2});
    // brain.feedForward();

    // vector<LD> x=brain(vector<LD>{3,0});
    // for(auto X:x ){cout<<X<<endl;}

    // brain.evaluate(vector<LD>{0.1,-2});

    brain.feedForwardDerivatives();

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
    // brain.printSignals();
    // brain.printWeights();
    // brain.printBiases();
    // brain.printDerivatives();
    // brain.printTotalDerivatives();
    // brain.printDelta();
    // brain.printNumericalDerivatives();

    return 0;
}