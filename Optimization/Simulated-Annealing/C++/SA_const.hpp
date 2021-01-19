# ifndef SA_const
#define SA_const
#include"SA.hpp"

SA_Template
SA_Namespace::SimulatedAnnealing(Func func, std::vector<std::array<LD,2>> region,
    std::vector<LD> x0 ,  LD T0, LD k, int IterationT, LD MinT, std::vector<LD> sigma, 
    LD tol, int Nstar, LD p0, int N0, LD k0 ){

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

    this->region=region;
    this->x=x0;
    this->_x=x0;
    this->xnew=x0;
    this->xmin=x0;
    this->sigma=sigma;

    this->dim=x0.size();

    this->T0=T0;
    this->E=func(x0);
    this->Enew=this->E;
    this->Emin=this->E;
    this->AccProb=0.;

    std::random_device RndDiv;
    this->RndE.seed( RndDiv() );




};


SA_Template
SA_Namespace::~SimulatedAnnealing(){};





#endif