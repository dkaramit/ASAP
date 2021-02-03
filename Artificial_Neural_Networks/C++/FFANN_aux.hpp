#ifndef FFANN_aux
#define FFANN_aux
#include"FFANN.hpp"


FFANN_Template
void FFANN_Namespace::printSignals(){
    std::cout<<"s^{(l)}_{j}"<<std::endl;

    for(un_int l=0; l<total_layers; ++l){
        std::cout<<"l= "<<l<<"\t size:"<<nodes[l]<<std::endl;
        for(un_int j=0; j<nodes[l]; ++j){
            std::cout<<signals[l][j]<<"\t";
        }
        std::cout<<std::endl;
    }

}

FFANN_Template
void FFANN_Namespace::printWeights(){
    std::cout<<"w^{(l)}_{ji}"<<std::endl;
    for(un_int l=0; l<total_layers-1; ++l){
        std::cout<<"l= "<<l<<"\t size:"<<nodes[l+1]<<"x"<<nodes[l]<<std::endl;
        for(un_int j=0; j<nodes[l+1]; ++j){
            for(un_int i=0; i<nodes[l]; ++i){
                std::cout<<weights[l][j][i]<<"\t";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}


FFANN_Template
void FFANN_Namespace::printBiases(){
    std::cout<<"b^{(l)}_{j}"<<std::endl;
    for(un_int l=0; l<total_layers-1; ++l){
        std::cout<<"l= "<<l+1<<"\t size:"<<nodes[l+1]<<std::endl;
        for(un_int j=0; j<nodes[l+1]; ++j){
            std::cout<<biases[l][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}





FFANN_Template
void FFANN_Namespace::printDerivatives(){
    std::cout<<"\\dfrac{\\partial s^{l+1}_{j}}{\\partial s^{(l)}_{i}}"<<std::endl;

    for(un_int l=0; l<total_layers-1; ++l){
        std::cout<<"l= "<<l<<"\t size:"<<nodes[l+1]<<"x"<<nodes[l]<<std::endl;
        for(un_int j=0; j<nodes[l+1]; ++j){
            for(un_int i=0; i<nodes[l]; ++i){
                std::cout<<derivatives[l][j][i]<<"\t";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}



FFANN_Template
void FFANN_Namespace::printTotalDerivatives(){
    std::cout<<"\\dfrac{\\partial s^{l+1}_{j}}{\\partial s^{(0)}_{i}}"<<std::endl;
    
    for(un_int l=0; l<total_layers-1; ++l){
        std::cout<<"l= "<<l<<"\t size:"<<nodes[l+1]<<"x"<<nodes[0]<<std::endl;
        for(un_int j=0; j<nodes[l+1]; ++j){
            for(un_int i=0; i<nodes[0]; ++i){
                std::cout<<totalDerivatives[l][j][i]<<"\t";
            }
        std::cout<<std::endl;
        }
    std::cout<<std::endl;
    }

}



FFANN_Template
void FFANN_Namespace::printDelta(){
    std::cout<<"\\dfrac{\\partial s^{[N-1)]}_{k}}{\\partial s^{[N-(f+2)]}_{i}}"<<std::endl;
    
    for(un_int f=0; f<total_layers-1; ++f){
        std::cout<<"f= "<<f<<"\t size:"<<nodes[total_layers-1]<<"x"<<nodes[total_layers-(f+2)]<<std::endl;
        for(un_int j=0; j<nodes[total_layers-1]; ++j){
            for(un_int i=0; i<nodes[total_layers-(f+2)]; ++i){
                std::cout<<Delta[f][j][i]<<"\t";
            }
        std::cout<<std::endl;
        }
    std::cout<<std::endl;
    }

}


FFANN_Template
void FFANN_Namespace::printNumericalDerivatives(){
    std::cout<<"\\dfrac{\\partial s^{(N-1)}_{p}}{\\partial s^{(0)}_{r}}"<<std::endl;
    std::cout<<"size:"<<nodes[total_layers-1]<<"x"<<nodes[0]<<std::endl;
    for(un_int p=0; p<this->nodes[total_layers-1]; ++p){
        for(un_int r=0; r<nodes[0]; ++r){
        std::cout<< numericalDerivatives[p][r] <<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

}

FFANN_Template
void FFANN_Namespace::printDerivatives_w(){
    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<nodes[l+1]; ++j){
            for(un_int i=0; i<nodes[l]; ++i){
                derivative_bw(l,j,i);
                std::cout<<"\\dfrac{ds_j}{w^("<<l<<")_"<<j<<i<<"}= (";
                for(un_int r=0; r<nodes[total_layers-1]; ++r){
                    std::cout<<dsdw[r];
                    if(r==nodes[total_layers-1]-1){std::cout<<")";} 
                    else{std::cout<<",";} 
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}

FFANN_Template
void FFANN_Namespace::printDerivatives_b(){
    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<nodes[l+1]; ++j){
            derivative_bw(l,j,0);
            std::cout<<"\\dfrac{ds_j}{b^("<<l+1<<")_"<<j<<"}= (";
            for(un_int r=0; r<nodes[total_layers-1]; ++r){
                std::cout<<dsdb[r];
                if(r==nodes[total_layers-1]-1){std::cout<<")";} 
                else{std::cout<<",";} 
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}



FFANN_Template
void FFANN_Namespace::printNumericalDerivatives_w(){
    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<nodes[l+1]; ++j){
            for(un_int i=0; i<nodes[l]; ++i){
                numericalDerivative_bw(l,j,i);
                std::cout<<"\\dfrac{ds_j}{w^("<<l<<")_"<<j<<i<<"}= (";
                for(un_int r=0; r<nodes[total_layers-1]; ++r){
                    std::cout<<numerical_dsdw[r];
                    if(r==nodes[total_layers-1]-1){std::cout<<")";} 
                    else{std::cout<<",";} 
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}

FFANN_Template
void FFANN_Namespace::printNumericalDerivatives_b(){
    for(un_int l=0; l<total_layers-1; ++l){
        for(un_int j=0; j<nodes[l+1]; ++j){
            numericalDerivative_bw(l,j,0);
            std::cout<<"\\dfrac{ds_j}{b^("<<l+1<<")_"<<j<<"}= (";
            for(un_int r=0; r<nodes[total_layers-1]; ++r){
                std::cout<<numerical_dsdb[r];
                if(r==nodes[total_layers-1]-1){std::cout<<")";} 
                else{std::cout<<",";} 
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}

#endif