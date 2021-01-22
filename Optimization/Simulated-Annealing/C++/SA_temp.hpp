#ifndef SA_Temp
#define SA_Temp
#include"SA.hpp"

// Decrease the temperature
SA_Template
void SA_Namespace::nextT(){
    T*=k;
}

SA_Template
LD SA_Namespace:: BoltzmannP(){
    return exp(-(Enew-E)/T);
}

// Find next E for the current temperature
SA_Template
void SA_Namespace::runT(int IterationT){

    AccProb=0;
    for(int itT=0 ; itT<IterationT ; ++itT){
        PickNeighbour();
        Enew=func(xnew);

        // Update the point so far if Enew<Emin
        if(Enew<Emin){ 
            Emin=Enew ; 
            xmin=xnew;
        }

        if (Enew<E or BoltzmannP() > Random() ){
            AccProb++;
            E=Enew;
            x=xnew;
        }

    }
    
    AccProb=AccProb/((LD)IterationT);

}


// Find an initial temperature with high acceptance probability
SA_Template
void SA_Namespace::InitT(int IterationT, int N0, int k0, LD p0){
    int IterT0=0;
    while (IterT0<N0){
        runT(IterationT); 
        
        if (AccProb>p0){IterT0+=1;}        
        if (AccProb<p0 and IterT0>0){IterT0=0;}
        
        T*=k0;
        }
}


#endif