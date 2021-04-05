#ifndef Vanilla_SGD_class
#define Vanilla_SGD_class
#include"StochasticGradientDescent.hpp"

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>

#define Vanilla_SGD_Template template<class LD, class lossFunc>
#define Vanilla_SGD_Namespace VanillaSGD<LD,lossFunc>

Vanilla_SGD_Template
class VanillaSGD: public StochasticGradientDescent<LD,lossFunc>{
    public:
    // the learning rate
    LD alpha;
    
    VanillaSGD()=default;
    // constructor (with default alpha)
    VanillaSGD(lossFunc *Q, LD alpha=1e-3);

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_SGD_Template
Vanilla_SGD_Namespace::VanillaSGD(lossFunc *Q, LD alpha):StochasticGradientDescent<LD,lossFunc>(Q){
    this->alpha=alpha;
}



// // The update function
Vanilla_SGD_Template
LD Vanilla_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    LD _check=0,_w2=0,dw=0;
    this->Q->randomPoint();

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update w (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        this->Q->grad(i);
        dw=(alpha)*this->Q->dQdw;
        this->Q->model->w[i] = this->Q->model->w[i] - dw ; 

        // dw^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + std::abs(this->Q->model->w[i]) * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);
    }

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif