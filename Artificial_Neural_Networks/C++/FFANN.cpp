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
    array<activationType<LD,Func>, total_layers-1> activations{lin,lin,sig};

    // this is how the network is constructed
    FFANN<LD, Func, total_layers> brain(nodes,activations);


    cout<<activations[2](5)<<endl;
    cout<<brain.activations[2].derivative(5)<<endl;
    

    return 0;
}