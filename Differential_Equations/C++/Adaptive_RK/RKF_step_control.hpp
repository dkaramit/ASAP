#ifndef RKF_step_control
#define RKF_step_control
#include "RKF_class.hpp"


/*----------------------------------------------define a Print to have easy acces to some info--------------------------------------------*/
static int x=0;
#define Print(m1,m2,m3,m4,m5) std::cout<<"   "<<m1<<"   "<<m2<<"   "<<m3<<"   "<<m4<<"   "<<m5<<std::endl; std::cin.get()
/*----------------------------------------------------------------------------------------------------------------------------------------*/

#define max(a,b)  (a <= b) ? b : a
#define min(a,b)  (a >= b) ? b : a


/*-----------------------Begin: step_control---------------------------------*/
template<class diffeq, int N_eqs, class RKF_method>
void RKF<diffeq, N_eqs, RKF_method>::step_control(){
    
    //calculate the absolute value of delta
    
    #if 1

    double Delta=0.;
    double _sc;
    double fac;
    
    for (int eq = 0; eq < N_eqs; eq++){
        _sc=max(fabs( ynext[eq] ), fabs( ynext_star[eq] ));
        _sc=abs_tol+rel_tol*_sc;
        Delta+= pow((abs_delta[eq]/_sc),2.);
        
    ;}
    Delta=pow(1./N_eqs*Delta,0.5);


    // Print(Delta,_sc, ' ',' ',' ');
    if(Delta<1) { h_stop=true ; err[current_step]=Delta; }
    //step size cotrol from "Solving Ordinary Differential Equations I"
    fac=min(pow( 1/Delta , 1./(method.p+1) ) , fac_max );
    
    h0= beta*h0*fac ;

    if (h0>hmax ){ h0=hmax;  }
    if (h0<hmin ){ h0=hmin;  }
        // Print(h0,Delta,tn);

    if (tn+h0>1. ){ h0=1-tn;  }
        // Print(h0,Delta,tn);
    
    #else
    h_stop=true;
    if (tn+h0>1. ){ h0=1-tn;  }
    #endif
    
    

}
/*-----------------------End: step_control---------------------------------*/


#endif