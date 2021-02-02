#ifndef FFANN_derivatives
#define FFANN_derivatives
#include"FFANN.hpp"

FFANN_Template
void FFANN_Namespace::feedForwardDerivatives(){
    /*
    Calculate the output and the "local" derivatives of the network
    This feed forward function also fills the self.totalDerivatives,
    with self.totalDerivatives[-1] being the derivatives of the output 
    nodes with respect to the input nodes
    */
    for(un_int l=1; l<total_layers; ++l){
        for(un_int j=0; j<nodes[l]; ++j){
            calcSignal(l,j);
        }
        mulM(l);
    }
}

FFANN_Template
void FFANN_Namespace::mulM(un_int l){
    /*
    Matrix multiplication to be used when calculating the derivatives.
    It is intended to be used the feedForwardDerivatives() call.
    totalDerivatives is

    totalDerivatives[0][j][i] = \dfrac{\partial s^{1}_{j}}{\partial s^{(0)}_{i}} 
    totalDerivatives[1][j][i] = \dfrac{\partial s^{2}_{j}}{\partial s^{(0)}_{i}} 
    .
    .
    .
    totalDerivatives[l][j][i] = \dfrac{\partial s^{l+1}_{j}}{\partial s^{(0)}_{i}} 

    using our convention, this is
    
    l=0:
    totalDerivatives[0][j][i] = derivatives[0][j][k]
    
    and
    l>0:
    totalDerivatives[l][j][i] = derivatives[l][j][k] * totalDerivatives[l-1][j][k] 
    */

        
    if(l==1){ 
        for(un_int j=0; j<nodes[1]; ++j){
            for(un_int i=0; i<nodes[0]; ++i){
                totalDerivatives[0][j][i]=derivatives[0][j][i];
            }
        }
    }
    else{
        for(un_int j=0; j<nodes[l]; ++j){
            for(un_int i=0; i<nodes[0]; ++i){
                totalDerivatives[l-1][j][i]=0;
                for(un_int k=0; k< nodes[l-1]; ++k){
                    totalDerivatives[l-1][j][i]+=derivatives[l-1][j][k]*totalDerivatives[l-2][k][i];
                }
            }

        }
    }


}


#endif