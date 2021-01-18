#ifndef FFANN_const
#define FFANN_const

#include "FFANN.hpp"


FFANN_Template
FFANN_Namespace::FFANN(int inputs, int outputs, std::vector<int> hidden_nodes, std::vector<Func> activations){

    this->inputs = inputs; 
    this->outputs = outputs; 
    this->hidden_nodes = hidden_nodes;
    this->activations=activations;

    // number of hidden layers and number of total layers 
    this->hidden_layers=(this->hidden_nodes).size();
    this->total_layers=2+this->hidden_layers;

    // initialize the nodes vector
    this->nodes.push_back(inputs);
    for(int _:hidden_nodes){nodes.push_back(_);}
    this->nodes.push_back(outputs);

    // initialize the signals to 0
    for(int l=0; l<this->total_layers; l++ ){    
        {
            std::vector<LD> tmpV;
            for(int j=0; j<this->nodes[l]; j++ ){ tmpV.push_back(0); }
            this->signals.push_back(tmpV);
        }
    }
    
    }





FFANN_Template
FFANN_Namespace::~FFANN(){}

#endif