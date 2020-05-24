# ifndef SA_const
#define SA_const
#include"SA.hpp"

SA_Template
SA_Namespace::SimulatedAnnealing(Func func, LD region[dim][2],
    LD x0[dim] ,  LD T0, LD k, int IterationT, LD MinT, LD sigma[dim], LD tol, int Nstar, LD p0, int N0, LD k0 ){

    this->func = func;
    this->T=T0 ;
    this->k=k ;
    this->MinT=MinT ;  
    this->tol=tol ; 
    this->p0=p0 ; 
    this->k0=k0;

    this->IterationT=IterationT;
    this->Nstar=Nstar;
    this->N0=N0;

    for(int d = 0 ; d<dim ; ++d){
        this->region[d][0]=region[d][0];
        this->region[d][1]=region[d][1];

        this->x[d]=x0[d];
        this->xnew[d]=x0[d];
        this->xmin[d]=x0[d];

        // sigma must be smaller (region[d][1]- region[d][0])*2, otherwise you get out of the boundary
        this->sigma[d]=sigma[d];
        // if ( this->sigma[d] > (region[d][1]- region[d][0])*2 ){
        //     this->sigma[d] =  (region[d][1]- region[d][0])*2;
        // }
    }

    this->T0=T0;
    this->E=func(x0);
    this->Enew=this->E;
    this->Emin=this->E;
    this->AccProb=0.;





};


SA_Template
SA_Namespace::~SimulatedAnnealing(){};





#endif