#ifndef FFANN_N_derivatives
#define FFANN_N_derivatives
#include"FFANN.hpp"

FFANN_Template
void FFANN_Namespace::numericalDerivative(un_int input_node, LD h){
    /*
    Numerical derivatives with respect to "input_node". Stores the result in 
    
    numericalDerivatives[j][input_node] for all j=0,1,...total_layers-1.

    It is still better to just run *this(), because *this() calculates everything (marginally) faster.  
    */
    
    LD h1=h+std::abs(signals[0][input_node])*h;
    for(un_int r=0; r<nodes[0]; ++r){_signals[0][r]=signals[0][r];}
    
    
    signals[0][input_node]+=h1;
    _signals[0][input_node]-=h1;
    
    LD sum_ws1,sum_ws0;
    for(un_int l=1; l<total_layers-1; ++l){
        for(un_int j=0; j<nodes[l]; ++j){
            sum_ws1=0;
            sum_ws0=0;
            for(un_int i=0; i<nodes[l-1]; ++i){
                sum_ws1 += weights[l-1][j][i] * signals[l-1][i];
                sum_ws0 += weights[l-1][j][i] * _signals[l-1][i];
            }
            signals[l][j]  =  activations[l-1]( sum_ws1 + biases[l-1][j]  );
            _signals[l][j] =  activations[l-1]( sum_ws0 + biases[l-1][j]  );
        }
    }
    
    // run the last layer outside the loop becasuse the last j-loop gives us the derivatives!
    LD f0,f1;

    un_int l=total_layers-1;
    for(un_int j=0; j<nodes[l]; ++j){
        sum_ws1=0;
        sum_ws0=0;
        for(un_int i=0; i<nodes[l-1]; ++i){
            sum_ws1 += weights[l-1][j][i] * signals[l-1][i] ;
            sum_ws0 += weights[l-1][j][i] * _signals[l-1][i];
        }

        f1 =  activations[l-1]( sum_ws1 + biases[l-1][j]  );
        f0 =  activations[l-1]( sum_ws0 + biases[l-1][j]  );
        numericalDerivatives[j][input_node]=(f1-f0)/(2*h1);
    }
    
    signals[0][input_node]-=h1;
    signals[0][input_node]-=signals[0][input_node];

}


FFANN_Template
void FFANN_Namespace::totalNumericalDerivative(LD h){
    /*
    Run numericalDerivative for all input nodes. 
    The result is stored in numericalDerivatives
    */
    std::vector<std::vector<LD>> tmp;
    tmp.resize(total_layers);
    for(un_int l=0; l<total_layers; ++l){
        tmp[l].reserve(nodes[l]-1);
        for(un_int j=0; j<nodes[l]; ++j){
            tmp[l].push_back(signals[l][j]);
            _signals[l][j]=signals[l][j];
        }
    }

    for(un_int r=0; r<nodes[0]; ++r){
        numericalDerivative(r);
    }

    for(un_int l=0; l<total_layers; ++l){
        for(un_int j=0; j<nodes[l]; ++j){
            signals[l][j]=tmp[l][j];
            _signals[l][j]=signals[l][j];
        }
    }

}







FFANN_Template
void FFANN_Namespace::numericalDerivative_bw(un_int l,un_int j,un_int i,LD h){
    /*
    numerical derivative

    \dfrac{\partial s^{(N-1)}_{r}}{\partial w^{(l)}_{ji}} and 
    \dfrac{\partial s^{(N-1)}_{r}}{\partial b^{(l+1)}_{j}} 

    (for all r=0,1,...nodes[total_layers-1])

    using the formula: 

    \dfrac{\partial s^{(N-1)}_{r}}{\partial s^{(l+1)}_{j}} \theta^{\prime\, (l+1)}_{j}s^{(l)}_{i}

    Notice that we need to update only the signals at layers greater that l+2!
    */

    un_int N=total_layers;
    LD sum_ws=0;
    if(l==N-2){            
        for(un_int r=0; r<nodes[N-1]; ++r){
            if(j==r){
                sum_ws=0; 
                for(un_int k=0; k<nodes[l]; ++k){sum_ws+=weights[l][j][k]*signals[l][k];}
                numerical_dsdb[r]=activations[l].derivative(sum_ws+biases[l][j]);
                numerical_dsdw[r]=activations[l].derivative(sum_ws+biases[l][j])*signals[l][i];
            }
            else{
                numerical_dsdb[r]=0;
                numerical_dsdw[r]=0;
            }
        }
    }

    LD h1=h+std::abs(signals[l+1][j])*h;

    // only the l+1 layers are relevant here
    std::vector<std::vector<LD>> tmp;
    tmp.resize(total_layers);
    for(un_int _l=l+1; _l<total_layers; ++_l){
        tmp[_l].reserve(nodes[_l]-1);
        for(un_int _j=0; _j<nodes[_l]; ++_j){
            tmp[_l].push_back(signals[_l][_j]);
            _signals[_l][_j]=signals[_l][_j];
        }
    }

    sum_ws=0;
    for(un_int k=0; k<nodes[l]; ++k){sum_ws+=weights[l][j][k] * signals[l][k];}
    
    LD factor_w=activations[l].derivative(sum_ws +biases[l][j])*signals[l][i];
    LD factor_b=activations[l].derivative(sum_ws +biases[l][j]);

    signals[l+1][j]=signals[l+1][j]+h1;
    _signals[l+1][j]=_signals[l+1][j]-h1;
    
    LD sum_ws0=0;
    LD sum_ws1=0;
    
    for(un_int l1=l+2; l1<N; ++l1){
        for(un_int j1=0; j1<nodes[l1]; ++j1){
            sum_ws1=0;
            sum_ws0=0;
            for(un_int i1=0; i1<nodes[l1-1]; ++i1){
                sum_ws1 += weights[l1-1][j1][i1] * signals[l1-1][i1];
                sum_ws0 += weights[l1-1][j1][i1] * _signals[l1-1][i1];
            }
            signals[l1][j1]  =  activations[l1-1]( sum_ws1 + biases[l1-1][j1]  );
            _signals[l1][j1] =  activations[l1-1]( sum_ws0 + biases[l1-1][j1]  );
        }
    }

    std::vector<LD> f1=signals[N-1];
    std::vector<LD> f0=_signals[N-1];
    

    for(un_int r=0; r<nodes[N-1]; ++r){
        numerical_dsdw[r]=(f1[r]-f0[r])/(2.*h1 )*factor_w;
        numerical_dsdb[r]=(f1[r]-f0[r])/(2.*h1 )*factor_b;
    }


    // after everything, restore the signals (only everything after l+1 is changed, but deepcopy should be faster in general)
    for(un_int _l=l+1; _l<total_layers; ++_l){
        for(un_int _j=0; _j<nodes[_l]; ++_j){
            signals[_l][_j]=tmp[_l][_j];
            _signals[_l][_j]=signals[_l][_j];
        }
    }
}
#endif