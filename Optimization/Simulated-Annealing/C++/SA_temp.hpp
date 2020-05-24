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
void SA_Namespace::runT(){
    AccProb=0;
    for(int itT=0 ; itT<IterationT ; ++itT){
        PickNeighbour();
        Enew=func(xnew);

        // Update the point so far if Enew<Emin
        if(Enew<Emin){ 
            Emin=Enew ; 
            for(int d = 0 ; d<dim ; ++d){
                xmin[d]=xnew[d]; 
            }

        }

        if (Enew<E or BoltzmannP() > Random() ){
            AccProb++;
            E=Enew;
            for(int d = 0 ; d<dim ; ++d){
                x[d]=xnew[d]; 
            }
        }

    }
    
    AccProb=AccProb/((LD)IterationT);

}


// Find an initial temperature with high acceptance probability
SA_Template
void SA_Namespace::InitT(){
    int IterT0=0;
    while (IterT0<N0){
        runT(); 
        
        if (AccProb>p0){IterT0+=1;}        
        if (AccProb<p0 and IterT0>0){IterT0=0;}
        
        T*=k0;
        }
}


#endif