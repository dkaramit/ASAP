#ifndef RMSprop_GD_class
#define RMSprop_GD_class

/*
RMSprop Gradient Descent
*/

#include<vector>
#include<cmath>

#define RMSprop_GD_Template template<class LD, class Function>
#define RMSprop_GD_Namespace RMSpropGD<LD,Function>

RMSprop_GD_Template
class RMSpropGD{
    public:
    // the function to be minimized (instance of class that is derived from Function)
    Function *function;
    LD f_min;

    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    std::vector<std::vector<LD>> steps;
    

    // we will use this to hold the mean gradient over all data-points
    std::vector<LD> grad;

    // vector for the decaying average of the gradient
    std::vector<LD> gE;

    RMSpropGD()=default;
    // constructor with default values of the parameters    
    RMSpropGD(Function *function, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
RMSprop_GD_Template
RMSprop_GD_Namespace::RMSpropGD(Function *function, LD gamma, LD epsilon, LD alpha){
    this->function=function;
    this->f_min=function->operator()(function->x);
    this->dim=function->dim;

    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;

    steps.push_back(this->function->x);

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
    }


}



// // The update function
RMSprop_GD_Template
LD RMSprop_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD dx=0,_check=0,_x2=0;

    function->derivative(function->x);

    for(unsigned int i=0 ; i<dim; ++i ){
        // calculate decaying average of the gradient
        gE[i]=gamma*gE[i] + (1-gamma)*function->grad[i]*function->grad[i];
        
        // update w
        dx=std::sqrt( 1/(gE[i]+epsilon)  )*function->grad[i]*alpha;
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