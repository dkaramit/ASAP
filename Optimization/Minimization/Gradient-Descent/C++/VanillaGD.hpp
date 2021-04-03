#ifndef Vanilla_GD_class
#define Vanilla_GD_class

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>

#define Vanilla_GD_Template template<class LD, class Function>
#define Vanilla_GD_Namespace VanillaGD<LD,Function>

Vanilla_GD_Template
class VanillaGD{
    public:
    // the function to be minimized (instance of class that is derived from Function)
    Function *function;
    LD f_min;

    // the learning rate
    LD alpha;

    // the dimension of the x  
    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    std::vector<std::vector<LD>> steps;
    

    VanillaGD()=default;
    // constructor (with default alpha)
    VanillaGD(Function *function, LD alpha=1e-3);

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(Function *function, LD alpha){
    this->function=function;
    this->f_min=function->operator()(function->x);
    this->dim=function->dim;

    this->alpha=alpha;

    steps.push_back(this->function->x);
}



// // The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD _check=0,_x2=0,dx=0;

    function->derivative(function->x);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update x (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        dx=(alpha)*function->grad[i];
        function->x[i] = function->x[i] - dx ; 

        // function->grad^2/(abs_tol + dx * rel_tol)^2 for this direction
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