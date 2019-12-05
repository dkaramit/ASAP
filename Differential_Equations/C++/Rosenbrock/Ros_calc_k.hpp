#ifndef Ros_calc_k
#define Ros_calc_k
#include "Ros_class.hpp"
#include "Jacobian/Jacobian.hpp"
#include "LU/LU.hpp"



/*-----------------------Begin: calc_Jk---------------------------------*/
template<class diffeq, int  N_eqs, class RK_method, class jacobian>
void Ros<diffeq,  N_eqs, RK_method, jacobian>::calc_Jk(){
    /*
    Calculate product of matrix with vector. 
    We use it to get J*gk.
    */

    for(int i=0; i<N_eqs ; i++){
        Jk[i]=0;
        for(int j=0; j<N_eqs ; j++){ Jk[i]+=J[i][j]*gk[j]; }
    }
    

    
          
}
/*-----------------------End: calc_Jk---------------------------------*/

/*-----------------------Begin: calc_k---------------------------------*/
template<class diffeq, int  N_eqs, class RK_method, class jacobian>
void Ros<diffeq,  N_eqs, RK_method, jacobian>::calc_k(){
    // initialize the lhs coefficient to unity
    for(int i=0; i<N_eqs ; i++){ for(int j=0; j<N_eqs ; j++){  if(i==j){ _coeff[i][j]=1; }else{_coeff[i][j]=0;}  }}

    // Find the LUP decomposition of   (I-\gamma*h*J)     
    for(int i=0; i<N_eqs ; i++){yn[i]=solution[i][current_step-1]; }
    Jac(J,dfdt,yn,tn);

    for(int i=0; i<N_eqs ; i++){
        for(int j=0; j<N_eqs ; j++){
            _coeff[i][j]+=-h0*method.gamma*J[i][j];
         }
     }

    LUP<N_eqs>(_coeff,L,U,P);
    
    // solve for the k for the first stage
    // dydt(fyn,yn,tn);
    // for(int eq=0; eq<N_eqs ; eq++){ rhs[eq] = fyn[eq]*h0 + (method.gamma)*(h0*h0)*dfdt[eq] ; }
    // Solve_LU<N_eqs>(L,U,P,rhs, lu_sol);
    // for(int eq=0; eq<N_eqs ; eq++){ k[eq][0] = lu_sol[eq] ; }

    // calculate k for the other stages
    for(int stage = 0; stage < method.s; stage++){
        sum_ak(stage);
        sum_gk(stage);
        
        // setup the argument for dydt (it is evaluated at y_n+\sum a*k )
        for(int eq=0; eq<N_eqs ; eq++){yn[eq]=solution[eq][current_step-1] +ak[eq]  ; }
        /*--- Get the rhs terms ---*/
        // first term
        dydt(rhs1, yn  , tn+method.c[stage]*h0 );
        // second term
        for(int eq=0; eq<N_eqs ; eq++) { rhs2[eq] =  (h0*h0)*(method.gamma+sum_gamma[stage])*dfdt[eq]   ;  }
        // third term
        calc_Jk();
        // then the rhs becomes
        for(int eq=0; eq<N_eqs ; eq++) { rhs[eq]= rhs1[eq]*h0 + rhs2[eq] + Jk[eq]*h0  ;  }
        /*------------------------*/

        Solve_LU<N_eqs>(L,U,P,rhs, lu_sol);
        for( int eq = 0; eq < N_eqs; eq++ ){ k[eq][stage]=lu_sol[eq]; }
    }







    
          
}
/*-----------------------End: calc_k---------------------------------*/
#endif