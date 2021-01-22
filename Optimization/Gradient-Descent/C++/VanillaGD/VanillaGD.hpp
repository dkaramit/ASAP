#ifndef Vanilla_GD_class
#define Vanilla_GD_class

/*
Vanilla Gradient Descent (i.e. no adaptation of the learning rate).
VanillaGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

#include"../GD_base/GD.hpp"

#define Vanilla_GD_Template template<class LD, class Func>
#define Vanilla_GD_Namespace VanillaGD<LD,Func>

Vanilla_GD_Template
class VanillaGD: public GD_Namespace{
    public:
    Func target;
    LD alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x;

    unsigned int dim;


    VanillaGD(Func target, std::vector<LD> x0, LD alpha=1e-1);
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(Func target, std::vector<LD> x0, LD alpha){
    this->target=target;
    this->alpha=alpha;
    this->x=x0;
    this->dim=(this->x).size();
    this->steps.push_back(x0);
}

// The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){
    LD _check=0,_x2=0;
    std::vector<LD> grad; 

    this->target.Grad(this->x,grad);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->x[i] = this->x[i] - (this->alpha)*grad[i] ; 

        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(grad[i]/_x2)*(grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check)*this->alpha;
    
    this->steps.push_back(x);

    // _check<1 means that we have converged
    return _check;
}



#endif