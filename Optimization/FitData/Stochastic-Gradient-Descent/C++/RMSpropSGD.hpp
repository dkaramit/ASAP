#ifndef RMSprop_SGD_class
#define RMSprop_SGD_class
#include"StochasticGradientDescent.hpp"

/*
RMSprop Stochastic Gradient Descent
*/

#include<vector>
#include<cmath>

#define RMSprop_SGD_Template template<class LD, class lossFunc>
#define RMSprop_SGD_Namespace RMSpropSGD<LD,lossFunc>

RMSprop_SGD_Template
class RMSpropSGD: public StochasticGradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // vector for the decaying average of the gradient
    std::vector<LD> gE;

    RMSpropSGD()=default;
    // constructor with default values of the parameters    
    RMSpropSGD(lossFunc *Q, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
RMSprop_SGD_Template
RMSprop_SGD_Namespace::RMSpropSGD(lossFunc *Q, LD gamma, LD epsilon, LD alpha):StochasticGradientDescent<LD,lossFunc>(Q){
    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
    }
}



// // The update function
RMSprop_SGD_Template
LD RMSprop_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD dw=0,_check=0,_w2=0;
    this->Q->randomPoint();


    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the gradient at current value of w and at the index^th data point 
        this->Q->grad(i);

        // calculate decaying average of the gradient
        gE[i]=gamma*gE[i] + (1-gamma)*this->Q->dQdw*this->Q->dQdw;
        
        // update w
        dw=std::sqrt( 1/(gE[i]+epsilon)  )*this->Q->dQdw*alpha;
        this->Q->model->w[i]=this->Q->model->w[i] - dw;

        // dw^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + std::abs(this->Q->model->w[i]) * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);
    }
    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif