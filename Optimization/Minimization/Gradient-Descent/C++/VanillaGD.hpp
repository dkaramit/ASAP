#ifndef Vanilla_GD_class
#define Vanilla_GD_class
#include"GradientDescent.hpp"

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>

#define Vanilla_GD_Template template<class LD, class Function>
#define Vanilla_GD_Namespace VanillaGD<LD,Function>

Vanilla_GD_Template
class VanillaGD: public GradientDescent<LD,Function>{
    public:
    // the learning rate
    LD alpha;

    VanillaGD()=default;
    // constructor (with default alpha)
    VanillaGD(Function *function, LD alpha=1e-3);

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(Function *function, LD alpha):GradientDescent<LD, Function>(function){
    this->alpha=alpha;
}



// // The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD _check=0,_x2=0,dx=0;

    this->function->derivative(this->function->x);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update x (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        dx=(alpha)*this->function->grad[i];
        this->function->x[i] = this->function->x[i] - dx ; 

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