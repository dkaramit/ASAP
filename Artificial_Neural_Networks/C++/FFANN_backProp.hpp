#ifndef FFANN_backProp
#define FFANN_backProp
#include"FFANN.hpp"

FFANN_Template
void FFANN_Namespace::backPropagation(){
    /*
    Define Delta^{f}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{[N-(f+2)]}_{i}}.
    For f=0,1,2,...N-2 this is n^{(N-1)} \times n^{(N-(f+2))} matrix
    
    Notice that the Delta^{self.total_layers-2}_{ji} = \dfrac{\partial s^{[N-1)]}_{k}}{\partial s^{(0)}_{i}}
    */
    un_int N=total_layers;
    
    for(un_int j=0; j<nodes[N-1]; ++j){
        for(un_int i=0; i<nodes[N-2]; ++i){
            Delta[0][j][i]=derivatives[N-2][j][i];
        }
    }

    for(un_int f=1; f<N-1; ++f){
        for(un_int j=0; j<nodes[N-1]; ++j){
            for(un_int i=0; i<nodes[N-(f+2)]; ++i){
                Delta[f][j][i]=0;
                for(un_int k=0; k<nodes[N-(f+1)]; ++k){
                    Delta[f][j][i]+=Delta[f-1][j][k] * derivatives[N-(f+2)][k][i];
                }
            }
        }
    }     
}

FFANN_Template
void FFANN_Namespace::derivative_bw(un_int l,un_int j,un_int i){
    /*
    caclulate:
    
    \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l)}_{ji}} = \Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}s^{(l)}_{i}
    
    at the same time caclulate 
    
    \dfrac{\partial s^{(N-1)}_{r}}{\partial b^{(l+1)}_{j}} =\Delta^{ (N-(l+3)) }_{r j} \theta^{\prime\, (l+1)}_{j}
    
    and return the result for all r (r=# output nodes).
    */
    un_int N=total_layers;
    LD sum_ws=0;
    if(l==N-2){            
        for( un_int r=0; r<nodes[N-1];++r){
            if(j==r){
                sum_ws = 0;  
                for(un_int k=0; k<nodes[l]; ++k){sum_ws+=weights[l][j][k]*signals[l][k];}

                dsdb[r]=activations[l].derivative(sum_ws+biases[l][j]);
                dsdw[r]=dsdb[r]*signals[l][i];
            }
            else{
                dsdb[r]=0;
                dsdw[r]=0;
            }
        }
    }
    else{
        sum_ws = 0;  
        for(un_int k=0; k<nodes[l]; ++k){sum_ws+=weights[l][j][k]*signals[l][k];}
        for(un_int r=0; r<nodes[N-1]; ++r){
            dsdb[r]=Delta[N-(l+3)][r][j];
            dsdb[r]*=activations[l].derivative(sum_ws+biases[l][j]);
            dsdw[r]=dsdb[r]*signals[l][i];
        }
    }
}



#endif