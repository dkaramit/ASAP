#ifndef AdaMax_GD_class
#define AdaMax_GD_class
#include"GradientDescent.hpp"

/*
AdaMax Gradient Descent
*/

#include<vector>
#include<cmath>

#define AdaMax_GD_Template template<class LD, class Function>
#define AdaMax_GD_Namespace AdaMaxGD<LD,Function>

AdaMax_GD_Template
class AdaMaxGD: public GradientDescent<LD,Function>{
    public:
    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;
    
    // vector for the decaying averages of m
    std::vector<LD> mE;
    // vector for v_max (see update for its definition)
    std::vector<LD> v_max;

    // variables that accumulate beta_{m}^iteration
    LD beta_m_ac;

    // constructor with default values of the parameters    
    AdaMaxGD(Function *function,LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    AdaMaxGD(){};


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
AdaMax_GD_Template
AdaMax_GD_Namespace::AdaMaxGD(Function *function, LD beta_m, LD beta_v, LD epsilon, LD alpha):GradientDescent<LD, Function>(function){
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->beta_m_ac=beta_m;

    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->v_max.push_back(0);
    }
}



// // The update function
AdaMax_GD_Template
LD AdaMax_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0,dx=0;

    this->function->derivative(this->function->x);

    // accumulate the decay rates, in order to correct the averages 
    beta_m_ac*=beta_m_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){

        // caclulate the decaying average of the gradient and v_max
        mE[i]=beta_m*mE[i] + (1-beta_m)*this->function->grad[i]; 
        v_max[i]=(std::abs(this->function->grad[i]) > beta_v*v_max[i]) ? std::abs(this->function->grad[i]) : beta_v*v_max[i]; 

        // update w
        dx=alpha/(v_max[i] + epsilon)  *mE[i]/(1-beta_m_ac);
        this->function->x[i]=this->function->x[i] - dx;
        

        // grad^2/(abs_tol + dx * rel_tol)^2 for this direction
        _x2=abs_tol + this->function->x[i] * rel_tol;
        _check+=(dx/_x2)*(dx/_x2);
    }
    // append new x to steps
    this->steps.push_back(this->function->x);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);

    LD tmp_min=this->function->operator()(this->function->x);
    if(tmp_min<this->f_min){
        this->function->minimum=this->function->x;
        this->f_min=tmp_min;
    }

    return _check;
}
















#endif