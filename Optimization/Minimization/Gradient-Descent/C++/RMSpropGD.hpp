#ifndef RMSprop_GD_class
#define RMSprop_GD_class
#include"GradientDescent.hpp"

/*
RMSprop Gradient Descent
*/

#include<vector>
#include<cmath>

#define RMSprop_GD_Template template<class LD, class Function>
#define RMSprop_GD_Namespace RMSpropGD<LD,Function>

RMSprop_GD_Template
class RMSpropGD:public GradientDescent<LD,Function>{
    public:
    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // vector for the decaying average of the gradient
    std::vector<LD> gE;

    RMSpropGD()=default;
    // constructor with default values of the parameters    
    RMSpropGD(Function *function, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
RMSprop_GD_Template
RMSprop_GD_Namespace::RMSpropGD(Function *function, LD gamma, LD epsilon, LD alpha):GradientDescent<LD, Function>(function){
    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
    }
}



// // The update function
RMSprop_GD_Template
LD RMSprop_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD dx=0,_check=0,_x2=0;

    this->function->derivative(this->function->x);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate decaying average of the gradient
        gE[i]=gamma*gE[i] + (1-gamma)*this->function->grad[i]*this->function->grad[i];
        
        // update w
        dx=std::sqrt( 1/(gE[i]+epsilon)  )*this->function->grad[i]*alpha;
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