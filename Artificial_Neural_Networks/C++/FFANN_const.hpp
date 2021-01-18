#ifndef FFANN_const
#define FFANN_const

#include "FFANN.hpp"


FFANN_Template
FFANN_Namespace::FFANN(int inputs, int outputs, std::vector<int> hidden_nodes, 
                Func hidden_activation, Func output_activation){

    this->inputs = inputs; 
    this->outputs = outputs; 
    this->hidden_nodes = hidden_nodes;
    this->hidden_activation=hidden_activation;
    this->output_activation=output_activation;


    // number of hidden layers and number of total layers 
    this->hidden_layers=(this->hidden_nodes).size();
    this->total_layers=2+this->hidden_layers;

    // initialize the nodes vector
    this->nodes.push_back(inputs);
    for(int _:hidden_nodes){nodes.push_back(_);}
    this->nodes.push_back(outputs);




    // self.signals=[ [0 for j in range(self.nodes[l])]  for l in range(self.total_layers)]
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