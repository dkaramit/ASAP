# ifndef SA_const
#define SA_const
#include"SA.hpp"

SA_Template
SA_Namespace::SimulatedAnnealing(Func func, std::vector<std::array<LD,2>> region,
    std::vector<LD> x0 , LD T0, std::vector<LD> sigma){

    this->func = func;
    this->T=T0 ;


     


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