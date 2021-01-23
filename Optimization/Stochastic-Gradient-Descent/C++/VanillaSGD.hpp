#ifndef Vanilla_SGD_class
#define Vanilla_SGD_class

/*
Vanilla Gradient Descent (i.e. no adaptation of the learning rate).
VanillaSGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

// #include"GD.hpp"

#define Vanilla_SGD_Template template<class LD, class Func>
#define Vanilla_SGD_Namespace VanillaSGD<LD,Func>

Vanilla_SGD_Template
class VanillaSGD{
    public:
    Func target;
    LD alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x;

    unsigned int dim;
    std::vector<LD> grad;


    VanillaSGD(Func target, std::vector<LD> x0, LD alpha=1e-1);
    VanillaSGD(){};

    VanillaSGD& operator=(const VanillaSGD& van){
        this->target=van.target;
        this->alpha=van.alpha;
        this->x=van.x;
        
        this->dim=van.dim;
        this->grad=van.grad;
        this->steps=van.steps;
        return *this;    
    };
    
    // the update function called from GradientDescent.update.
    // update should return a number that when it is smaller than 1
    // the main loop stops.
    // Here I choose this number to be:
    //  sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_SGD_Template
Vanilla_SGD_Namespace::VanillaSGD(Func target, std::vector<LD> x0, LD alpha){
    this->target=target;
    this->alpha=alpha;
    this->x=x0;
    
    this->dim=(this->x).size();
    this->grad.resize(this->dim);
    this->steps.push_back(x0);
}

// The update function
Vanilla_SGD_Template
LD Vanilla_SGD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0;
    this->target.Grad(this->x,this->grad);
    
    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->x[i] = this->x[i] - (this->alpha)*this->grad[i] ; 

        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(x);

    return _check;
}



#endif