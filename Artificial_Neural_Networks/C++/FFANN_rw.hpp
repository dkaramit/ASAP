#ifndef FFANN_rw
#define FFANN_rw

#include"FFANN.hpp"

// for l in range(self.layers+1):
//     for j in range(self.nodes[l+1]):
//         X.append(self.biases[l][j])
//         for i in range(self.nodes[l]):
//             X.append(self.weights[l][j][i])
// return X

FFANN_Template
void FFANN_Namespace::write_params(std::vector<LD> *X){

    for(int l=0; l< this->hidden_layers+1; l++){
       for(int j=0; j< this->nodes[l+1]; j++){
           X->push_back(this->biases[l][j]);
           for(int i=0; i< this->nodes[l]; i++){
               X->push_back(this->weights[l][j][i]);
           }

       }


    }
}

FFANN_Template
void FFANN_Namespace::read_params(std::vector<LD> *X){
    int _s=0;
    for(int l=0; l< this->hidden_layers+1; l++){
        for(int j=0; j< this->nodes[l+1]; j++){
            this->biases[l][j]=(*X)[_s];
            _s++;
            for(int i=0; i< this->nodes[l]; i++){
                this->weights[l][j][i]=(*X)[_s];
                _s++;
            }

       }


    }

}


#endif