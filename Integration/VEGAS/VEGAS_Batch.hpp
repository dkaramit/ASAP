#ifndef VEGAS_IntBatch
#define VEGAS_IntBatch
#include"VEGAS.hpp"


// Integrate using batches. 
// I use the estimator provided by 
// G. PETER LEPAGE JOURNAL  OF COMPUTATIONAL A New Algorithm PHYSICS 27, 192-203 (1978)
// Seems to wotk fine!

VEGAS_Template
LD VEGAS_Namespace::IntegrateBatch(LD *IntMean, LD *IntSigma   ){
    
    LD SumI3Var=0; //To get Sum_b I^3/\sigma^2
    LD SumI2Var=0; //To get Sum_b I^2/\sigma^2

    LD SumInvVar= 0; // To get Sum_b 1/var_b 
    LD SumI1Var=0;  // To get Sum_b I_b/var_b

    LD res,var,chi2; //temporary variables to get the results from IntegrateTot
    for(int batch=0 ; batch<NBatches ; ++batch){
        IntegrateTot(&res,&var);
        
        SumI2Var+=res*res/var;
        
        SumI3Var+=res*res*res/var;
        
        SumInvVar+=1/var;
        
        SumI1Var+=res/var;

    }

    *IntMean=SumI3Var/SumI2Var;
    
    *IntSigma=*IntMean/sqrt( SumI2Var);

    chi2=SumI2Var+(*IntMean)*(*IntMean)*SumInvVar-2*SumI1Var*(*IntMean) ;

    return  chi2/(NBatches-1);
    



}


#endif