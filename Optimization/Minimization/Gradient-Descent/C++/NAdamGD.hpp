#ifndef NAdam_GD_class
#define NAdam_GD_class

/*
NAdam Gradient Descent
*/

#include<vector>
#include<cmath>

#define NAdam_GD_Template template<class LD, class Function>
#define NAdam_GD_Namespace NAdamGD<LD,Function>

NAdam_GD_Template
class NAdamGD{
    public:
    // the function to be minimized (instance of class that is derived from Function)
    Function *function;
    LD f_min;

    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;

    // the dimension of the x  
    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    std::vector<std::vector<LD>> steps;

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
NAdam_GD_Namespace::NAdamGD(Function *function, LD beta_m, LD beta_v, LD epsilon, LD alpha){
    this->function=function;
    this->f_min=function->operator()(function->x);
    this->dim=function->dim;

    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    steps.push_back(this->function->x);

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

    function->derivative(function->x);
    
    // accumulate the decay rates, in order to correct the averages 
    beta_m_ac*=beta_m_ac;
    beta_v_ac*=beta_v_ac;

    for(unsigned int i=0 ; i<dim; ++i ){

        // calculate decaying averages of the gradient and dx
        mE[i]=beta_m*mE[i] + (1-beta_m)*function->grad[i]; 
        vE[i]=beta_v*vE[i] + (1-beta_v)*function->grad[i]*function->grad[i];

        // update w
        dx=alpha/(std::sqrt(vE[i]/(1-beta_v_ac)) + epsilon);
        dx*=(beta_m*mE[i] + (1-beta_m)*function->grad[i])/(1-beta_m_ac);
        function->x[i]=function->x[i] - dx;
        
        // grad^2/(abs_tol + dx * rel_tol)^2 for this direction
        _x2=abs_tol + function->x[i] * rel_tol;
        _check+=(dx/_x2)*(dx/_x2);
    }
    // append new x to steps
    steps.push_back(function->x);

    // calculate _check
    _check=std::sqrt(1/((LD) dim) *_check);

    LD tmp_min=function->operator()(function->x);
    if(tmp_min<f_min){
        function->minimum=function->x;
        f_min=tmp_min;
    }

    return _check;
}
















#endif