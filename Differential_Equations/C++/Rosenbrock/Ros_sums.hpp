#ifndef Ros_sums
#define Ros_sums
#include "Ros_class.hpp"

/*-----------------------Begin: sum_ak---------------------------------*/
template<class diffeq, int N_eqs, class RK_method, class jacobian>
void Ros<diffeq,  N_eqs, RK_method, jacobian>::sum_ak(int stage){
    // this function stores sum_{j}^{stage-1}a_{stage,j}\vec{k}_j in ak, so we first need to make all elements zero, and then take the sum for each component
    for (int eq = 0; eq <N_eqs ; eq++){
        ak[eq]=0.; 
        for (int j = 0; j < stage; j++){ ak[eq]+=method.a[stage][j]*k[eq][j];  }
    }
    
}
/*-----------------------End: sum_ak---------------------------------*/


/*-----------------------Begin: sum_gk---------------------------------*/
template<class diffeq, int N_eqs, class RK_method, class jacobian>
void Ros<diffeq,  N_eqs, RK_method, jacobian>::sum_gk(int stage){
    // this function stores sum_{j}^{stage-1}g_{stage,j}\vec{k}_j in ak, so we first need to make all elements zero, and then take the sum for each component
    for (int eq = 0; eq <N_eqs ; eq++){
        gk[eq]=0.;  
        for (int j = 0; j < stage; j++){ gk[eq]+=method.g[stage][j]*k[eq][j];  }
    }
    
}
/*-----------------------End: sum_ak---------------------------------*/

/*-----------------------Begin: sum_bk---------------------------------*/
template<class diffeq, int  N_eqs, class RK_method, class jacobian>
void Ros<diffeq,  N_eqs, RK_method, jacobian>::sum_bk(){
    // this function stores sum_{i}^{s}b_{i}\vec{k}_i*h in bk and sum_{i}^{s}b_{i}^{\star}\vec{k}_i*h in bstark  
    for (int eq = 0; eq <N_eqs ; eq++){
        bk[eq]=0.;
        bstark[eq]=0.; 
        
        for (int i = 0; i < (method).s; i++){ 
            bk[eq]+=(method).b[i]*k[eq][i];  
            bstark[eq]+=(method).bstar[i]*k[eq][i];  
            }
        // std::cout<<bk[eq]<<"   "<<bstark[eq]<<"   "<< h0<<"\n";std::cin.get();
    }

}
/*-----------------------End: sum_bk---------------------------------*/




#endif