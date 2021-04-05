#ifndef FFANN_const
#define FFANN_const
#include"FFANN.hpp"



FFANN_Template
FFANN_Namespace::FFANN(nodeArray &nodes, actArray &activationFunctions){
    this->nodes=nodes;
    this->activations=activationFunctions;
    this->total_layers=nodes.size();
    // reserve space for signals (and _signals)
    this->signals.resize(this->total_layers);
    this->_signals.resize(this->total_layers);
    for(un_int l=0; l<this->total_layers;++l){
        this->signals[l].resize( this-> nodes[l] );
        this->_signals[l].resize( this-> nodes[l] );
        for(un_int j=0; j<this->nodes[l]; ++j){
            this->signals[l][j]=0;
            this->_signals[l][j]=0;
        }
    }
    // std::copy(this->signals.begin(), this->signals.end(),this->_signals.begin());
    
    // reserve space for weights, biases, and local derivatives
    this->weights.resize(this->total_layers-1);
    this->biases.resize(this->total_layers-1);
    this->derivatives.resize(this->total_layers-1);
    for(un_int l=0; l<this->total_layers-1; ++l){
        this->weights[l].resize(nodes[l+1]);
        this->derivatives[l].resize(nodes[l+1]);
        this->biases[l].resize(nodes[l+1]);
        for(un_int j=0; j<this->nodes[l+1]; ++j){
            this->weights[l][j].resize(nodes[l]);
            this->derivatives[l][j].resize(nodes[l]);
            this->biases[l][j]=0;
            for(un_int i=0; i<this->nodes[l]; ++i){
                this->weights[l][j][i]=0;
                this->derivatives[l][j][i]=0;
            }
        }
    }


    // reserve space for totalDerivatives
    this->totalDerivatives.resize(this->total_layers-1);
    for(un_int l=0; l<this->total_layers-1; ++l){
        this->totalDerivatives[l].resize(this->nodes[l+1]);
        for(un_int j=0; j<this->nodes[l+1]; ++j){
          this->totalDerivatives[l][j].resize(this->nodes[0]);
            for(un_int i=0; i<this->nodes[0]; ++i){
                this->totalDerivatives[l][j][i]=0;
            }
        }
    }

    // reserve space for Delta
    this->Delta.resize(this->total_layers-1);
    for(un_int f=0; f<this->total_layers-1; ++f){
        this->Delta[f].resize(nodes[this->total_layers-1]);
        for(un_int j=0; j<this->nodes[this->total_layers-1]; ++j){
            this->Delta[f][j].resize(nodes[this->total_layers-(f+2)]);
            for(un_int i=0; i<this->nodes[this->total_layers-(f+2)]; ++i){
                this->Delta[f][j][i]=0;
                
            }
        }
    }

    // set up and initialize numericalDerivatives, dsdw and dsdb
    this->dsdw.resize(this->nodes[this->total_layers-1]);
    this->dsdb.resize(this->nodes[this->total_layers-1]);
    this->numerical_dsdw.resize(this->nodes[this->total_layers-1]);
    this->numerical_dsdb.resize(this->nodes[this->total_layers-1]);
    this->numericalDerivatives.resize(this->nodes[this->total_layers-1]);
    for(un_int p=0; p<this->nodes[this->total_layers-1]; ++p){
        this->dsdw[p]=0;
        this->dsdb[p]=0;
        this->numerical_dsdw[p]=0;
        this->numerical_dsdb[p]=0;

        this->numericalDerivatives[p].resize(nodes[0]);
        for(un_int r=0; r<this->nodes[0]; ++r){
            this->numericalDerivatives[p][r]=0;
        }
    }

};


#endif