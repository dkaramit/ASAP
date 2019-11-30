#ifndef RKF_calc_k
#define RKF_calc_k
#include "RKF_class.hpp"

/*-----------------------Begin: calc_k---------------------------------*/
template<class diffeq, int N_eqs, class RKF_method>
void RKF<diffeq, N_eqs, RKF_method>::calc_k(){
            // You can first calculate the first stage and then the rest of them, since the first one does not need ak. 

            // Or for the shake of simplicity, calculae all of them in one loop (shouldn't be slower since the sum_ak for stage=0 should'n realy do anything).
            // claculate the \vec{k}_i
            for (int stage = 0; stage < method.s; stage++){
                
                // first we need the sum_{j}^{stage-1}a_{stage,j}\vec{k}_j *h
                sum_ak(stage);

                // then we need \vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j} (so fill yn with this)
                for (int eq = 0; eq < N_eqs ; eq++){yn[eq]=solution[eq][current_step-1]+ak[eq];}
                
                // then calculate f(\vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j}, tn + c[stage]*h )
                dydt(fyn,  yn,tn+h0*(method.c)[stage] );
                
                // now we can fill \vec{k}[stage]
                for( int eq = 0; eq < N_eqs; eq++ ){ k[eq][stage]=fyn[eq]; }
            }
}
/*-----------------------End: calc_k---------------------------------*/
#endif