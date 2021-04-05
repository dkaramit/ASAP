#ifndef RMSprop_GD_class
#define RMSprop_GD_class
#include"GradientDescent.hpp"

/*
RMSprop Gradient Descent
*/

#include<vector>
#include<cmath>

#define RMSprop_GD_Template template<class LD, class lossFunc>
#define RMSprop_GD_Namespace RMSpropGD<LD,lossFunc>

RMSprop_GD_Template
class RMSpropGD: public GradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // vector for the decaying average of the gradient
    std::vector<LD> gE;

    RMSpropGD()=default;
    // constructor with default values of the parameters    
    RMSpropGD(lossFunc *Q, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
RMSprop_GD_Template
RMSprop_GD_Namespace::RMSpropGD(lossFunc *Q, LD gamma, LD epsilon, LD alpha):GradientDescent<LD,lossFunc>(Q){
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
    
    LD dw=0,_check=0,_w2=0;

    this->Q->averageGrad();

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate decaying average of the gradient
        gE[i]=gamma*gE[i] + (1-gamma)*this->Q->grad[i]*this->Q->grad[i];
        
        // update w
        dw=std::sqrt( 1/(gE[i]+epsilon)  )*this->Q->grad[i]*alpha;
        this->Q->model->w[i]=this->Q->model->w[i] - dw;

        // dw^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + std::abs(this->Q->model->w[i]) * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);

        this->Q->grad[i]=0;
    }
    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif