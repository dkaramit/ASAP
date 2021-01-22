#ifndef SA_run
#define SA_run
#include"SA.hpp"



SA_Template
void SA_Namespace::run(bool CList, LD tol, LD MinT, LD Nstar, int IterationT,
                        int N0, int k0, LD p0){

    //if you put N0=0, this->run will first run initT  otherwise set T=T0.
    // Note: N0!=0 if you run this function after another run, T0 will be the 
    // output of the first time InitT ran (otherwise it will be just T0 you put in the constructor).
    if (N0==0){T=T0;}
    else{InitT(IterationT, N0, k0, p0);T0=T;}
    
            

    int IterConv=0;

    while (T>MinT and Nstar>IterConv){
        runT(IterationT);
        
        if (AccProb<tol){IterConv++;}
        if (AccProb>tol and IterConv>0){IterConv=0;}
        
        if (CList){
            ListProb.push_back(AccProb);
            ListE.push_back(E);
            ListEmin.push_back(Emin);
        }        
        
        nextT();

    }


    E=Emin;
    for(unsigned int d = 0 ; d<dim ; ++d){
                x[d]=xmin[d]; 
            }
}


#endif