#ifndef SA_run
#define SA_run
#include"SA.hpp"



SA_Template
void SA_Namespace::run(bool CList, bool restart){

    //if you don't restart, run initT otherwise set T=T0 (the output of the first initT). 
    if (restart){ T=T0;}
    else{InitT();T0=T;}
    
            

    int IterConv=0;

    while (T>MinT and Nstar>IterConv){
        runT();
        
        if (AccProb<tol){IterConv++;}
        if (AccProb>tol and IterConv>0){IterConv=0;}
        
        if (CList){
            ListProb.push_back(AccProb);
            ListE.push_back(E);
            ListEmin.push_back(Emin);

            // for(int d = 0 ; d<dim ; ++d){
            //    points[d].push_back(x[d]) ;
            // }
        }        
        
        nextT();

    }


    E=Emin;
    for(unsigned int d = 0 ; d<dim ; ++d){
                x[d]=xmin[d]; 
            }
}


#endif