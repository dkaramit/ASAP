#ifndef FFANN_call
#define FFANN_call
#include"FFANN.hpp"


FFANN_Template
void FFANN_Namespace::evaluate(const std::vector<LD> &x){
    /*
    Calculate the output with self.signals[0]=x (without the derivatives).
    The outputs of all nodes are stored in self.signals
    */
    LD sum_ws;

    inputSignal(x);
    
    for(un_int l=1; l<total_layers;++l){
        for(un_int j=0; j<nodes[l];++j){
            sum_ws=0.;
            for(un_int i=0;i<nodes[l-1];++i){sum_ws+=weights[l-1][j][i] * signals[l-1][i];}
            signals[l][j] = activations[l-1](sum_ws+biases[l-1][j]);
        }
    }
}



FFANN_Template
void FFANN_Namespace::inputSignal(const std::vector<LD> &x){
    /*Read the input (x) and store it in this->signals[0]*/
    signals[0]=x;
}


FFANN_Template
void FFANN_Namespace::calcSignal(un_int l, un_int j){
    /*
    Calculate the output of the j node of layer l and 
    the (local) derivatives of s^{l}_{j} with respect s^{l-1}_{i} (far all i).
    we use:
    
    derivatives[0][j][i]= \dfrac{\partial s^{1}_{j}}{\partial s^{(0)}_{i}} 
    derivatives[1][j][i]= \dfrac{\partial s^{2}_{j}}{\partial s^{(1)}_{i}} 

    derivatives[l][j][i]= \dfrac{\partial s^{l+1}_{j}}{\partial s^{(l)}_{i}} 
    

    Note the convention:
    1. \theta^{(l)} =  activations[l-1]
    2. b^{(l)} = biases[l-1]

    It is intended to be used after the l-1 signals have been calulated
    within the feedForward() call.

    Note that this function is meaningless for l=0, since signals[0] is input
    */

    // Notice again that self.biases[l-1][j] correspond to the bias of node j and layer l.
    LD sum_ws=0.;
    for(un_int i=0;i<nodes[l-1];++i){sum_ws+=weights[l-1][j][i] * signals[l-1][i];}
    
    LD arg=sum_ws+biases[l-1][j];
    
    signals[l][j] = activations[l-1](arg);

    // fill also the derivatives (does the same thing as self.derivative for all i in self.nodes[l-1])
    for(un_int i=0;i<nodes[l-1];++i){
        derivatives[l-1][j][i]= activations[l-1].derivative(arg) * weights[l-1][j][i];
    } 

}


FFANN_Template
void FFANN_Namespace::feedForward(){
    /*
    Calculate only the output of the network and the local derivatives
    */

    // start from l=1, since l=0 is the input.
    for(un_int l=1; l<total_layers;++l){
        for(un_int j=0; j<nodes[l];++j){
            calcSignal(l,j);
        }
    }
}

FFANN_Template
std::vector<LD> FFANN_Namespace::operator()(const std::vector<LD> &x){
    /*
    Calculates the output and the derivatives of the network with self.signals[0]=x
    */
    
    std::vector<LD> output;
    inputSignal(x);
    feedForward();
    output=signals[total_layers-1];

    return output;
}





#endif