#ifndef NAdam_GD_class
#define NAdam_GD_class
#include"GradientDescent.hpp"

/*
NAdam Gradient Descent
*/

#include<vector>
#include<cmath>

#define NAdam_GD_Template template<class LD, class Function>
#define NAdam_GD_Namespace NAdamGD<LD,Function>

NAdam_GD_Template
class NAdamGD: public GradientDescent<LD,Function>{
    public:
    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;

    // vecors for the decaying averages of m and v
    std::vector<LD> mE, vE;

    // variables that accumulate beta_{m,v}^iteration
    LD beta_m_ac,beta_v_ac;
    
    NAdamGD()=default;
    // constructor with default values of the parameters    
    NAdamGD(Function *function,LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
NAdam_GD_Template
NAdam_GD_Namespace::NAdamGD(Function *function, LD beta_m, LD beta_v, LD epsilon, LD alpha):GradientDescent<LD, Function>(function){
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;


    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;

    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
    }
}



// // The update function
NAdam_GD_Template
LD NAdam_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0,dx=0;

    this->function->derivative(this->function->x);
    
    // accumulate the decay rates, in order to correct the averages 
    beta_m_ac*=beta_m_ac;
    beta_v_ac*=beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){

        // calculate decaying averages of the gradient and dx
        mE[i]=beta_m*mE[i] + (1-beta_m)*this->function->grad[i]; 
        vE[i]=beta_v*vE[i] + (1-beta_v)*this->function->grad[i]*this->function->grad[i];

        // update w
        dx=alpha/(std::sqrt(vE[i]/(1-beta_v_ac)) + epsilon);
        dx*=(beta_m*mE[i] + (1-beta_m)*this->function->grad[i])/(1-beta_m_ac);
        this->function->x[i]=this->function->x[i] - dx;
        
        // dx^2/(abs_tol + x * rel_tol)^2 for this direction
        _x2=abs_tol + std::abs(this->function->x[i]) * rel_tol;
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