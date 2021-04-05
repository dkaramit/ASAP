#ifndef AdaDelta_GD_class
#define AdaDelta_GD_class
#include"GradientDescent.hpp"

/*
AdaDelta Gradient Descent
*/

#include<vector>
#include<cmath>

#define AdaDelta_GD_Template template<class LD, class lossFunc>
#define AdaDelta_GD_Namespace AdaDeltaGD<LD,lossFunc>

AdaDelta_GD_Template
class AdaDeltaGD: public GradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // vectors for the decaying averages of the gradient and dw
    std::vector<LD> gE,dwE;
    
    AdaDeltaGD()=default;
    // constructor with default values of the parameters    
    AdaDeltaGD(lossFunc *Q, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1);

    

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// costuctor
AdaDelta_GD_Template
AdaDelta_GD_Namespace::AdaDeltaGD(lossFunc *Q, LD gamma, LD epsilon, LD alpha):GradientDescent<LD,lossFunc>(Q){
    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
        this->dwE.push_back(0);
    }
}



// // The update function
AdaDelta_GD_Template
LD AdaDelta_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD _check=0,_w2=0,dw=0;

    this->Q->averageGrad();

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate decaying average of the gradient
        gE[i]=gamma*gE[i] + (1-gamma)*this->Q->grad[i]*this->Q->grad[i];
        
        // update w
        dw=std::sqrt( (dwE[i]+epsilon)/(gE[i]+epsilon)  )*this->Q->grad[i]*alpha;
        this->Q->model->w[i]=this->Q->model->w[i] - dw;
        

        // calculate decaying average of the stepsize
        dwE[i]=gamma*dwE[i] + (1-gamma)*dw*dw;
        
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