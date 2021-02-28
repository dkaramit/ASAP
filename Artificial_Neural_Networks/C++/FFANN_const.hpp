#ifndef FFANN_const
#define FFANN_const
#include"FFANN.hpp"



FFANN_Template
FFANN_Namespace::FFANN(nodeArray &nodes, actArray &activationFunctions){
    this->nodes=nodes;
    this->activations=activationFunctions;
    this->total_layers=nodes.size();

    // reserve space for signals (and _signals)
    this->signals.reserve(this->total_layers);
    this->_signals.reserve(this->total_layers);
    for(un_int l=0; l<this->total_layers;++l){
        this->signals[l].reserve( this-> nodes[l] );
        this->_signals[l].reserve( this-> nodes[l] );
        for(un_int j=0; j<this->nodes[l]; ++j){
            this->signals[l].push_back(0);
            this->_signals[l].push_back(0);
        }
    }
    // std::copy(this->signals.begin(), this->signals.end(),this->_signals.begin());
    
    // reserve space for weights, biases, and local derivatives
    this->weights.reserve(this->total_layers-1);
    this->biases.reserve(this->total_layers-1);
    this->derivatives.reserve(this->total_layers-1);
    for(un_int l=0; l<this->total_layers-1; ++l){
        this->weights[l].reserve(nodes[l+1]);
        this->derivatives[l].reserve(nodes[l+1]);
        this->biases[l].reserve(nodes[l+1]);
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            this->weights[l][j].reserve(nodes[l]);
            this->derivatives[l][j].reserve(nodes[l]);
            this->biases[l].push_back(0);
            for(un_int i=0; i<this->nodes[l]; ++i){
                this->weights[l][j].push_back(0);
                this->derivatives[l][j].push_back(0);
            }
        }
    }


    // reserve space for totalDerivatives
    this->totalDerivatives.reserve(this->total_layers-1);
    for(un_int l=0; l<this->total_layers-1; ++l){
        this->totalDerivatives[l].reserve(this->nodes[l+1]);
        for(un_int j=0; j<this->nodes[l+1]; ++j){
          this->totalDerivatives[l][j].reserve(this->nodes[0]);
            for(un_int i=0; i<this->nodes[0]; ++i){
                this->totalDerivatives[l][j].push_back(0);
            }
        }
    }

    // reserve space for Delta
    this->Delta.reserve(this->total_layers-1);
    for(un_int f=0; f<this->total_layers-1; ++f){
        this->Delta[f].reserve(nodes[this->total_layers-1]);
        for(un_int j=0; j<this->nodes[this->total_layers-1]; ++j){
            this->Delta[f][j].reserve(nodes[this->total_layers-(f+2)]);
            for(un_int i=0; i<this->nodes[this->total_layers-(f+2)]; ++i){
                this->Delta[f][j].push_back(0);
                
            }
        }
    }

    // set up and initialize numericalDerivatives, dsdw and dsdb
    this->dsdw.reserve(this->nodes[this->total_layers-1]);
    this->dsdb.reserve(this->nodes[this->total_layers-1]);
    this->numerical_dsdw.reserve(this->nodes[this->total_layers-1]);
    this->numerical_dsdb.reserve(this->nodes[this->total_layers-1]);
    this->numericalDerivatives.reserve(this->nodes[this->total_layers-1]);
    for(un_int p=0; p<this->nodes[this->total_layers-1]; ++p){
        this->dsdw.push_back(0);
        this->dsdb.push_back(0);
        this->numerical_dsdw.push_back(0);
        this->numerical_dsdb.push_back(0);

        this->numericalDerivatives[p].reserve(nodes[0]);
        for(un_int r=0; r<this->nodes[0]; ++r){
            this->numericalDerivatives[p].push_back(0);
        }
    }

};


FFANN_Template
FFANN_Namespace::FFANN(un_int inputNodes, un_int outputNodes, 
                    nodeArray  &hiddenNodes, actArray &activationFunctions){

    nodeArray _nodes;
    _nodes.reserve(2+hiddenNodes.size());

    _nodes.push_back(inputNodes);

    for(un_int j:hiddenNodes){
        _nodes.push_back(j);
    }
    _nodes.push_back(outputNodes);

    
    this->operator=(FFANN<LD>(_nodes, activationFunctions));
    this->printBiases();

}

#endif