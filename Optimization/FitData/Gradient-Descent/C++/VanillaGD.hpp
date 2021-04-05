#ifndef Vanilla_GD_class
#define Vanilla_GD_class
#include"GradientDescent.hpp"

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>

#define Vanilla_GD_Template template<class LD, class lossFunc>
#define Vanilla_GD_Namespace VanillaGD<LD,lossFunc>

Vanilla_GD_Template
class VanillaGD: public GradientDescent<LD,lossFunc>{
    public:
    // the learning rate
    LD alpha;
    
    VanillaGD()=default;
    // constructor (with default alpha)
    VanillaGD(lossFunc *Q, LD alpha=1e-3);

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(lossFunc *Q, LD alpha):GradientDescent<LD,lossFunc>(Q){
    this->alpha=alpha;
}



// // The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){
    LD _check=0,_w2=0,dw=0;
    this->Q->averageGrad();
    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update w (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        dw=(alpha)*this->Q->grad[i];
        this->Q->model->w[i] = this->Q->model->w[i] - dw ; 

        // dw^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + std::abs(this->Q->model->w[i]) * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);
        // reset grad to 0
        this->Q->grad[i]=0;
    }

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif