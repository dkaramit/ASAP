#ifndef NAdam_GD_class
#define NAdam_GD_class
#include"GradientDescent.hpp"

/*
NAdam Gradient Descent
*/

#include<vector>
#include<cmath>

#define NAdam_GD_Template template<class LD, class lossFunc>
#define NAdam_GD_Namespace NAdamGD<LD,lossFunc>

NAdam_GD_Template
class NAdamGD: public GradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;

    // vecors for the decaying averages of m and v
    std::vector<LD> mE, vE;

    // variables that accumulate beta_{m,v}^iteration
    LD beta_m_ac,beta_v_ac;
    
    NAdamGD()=default;
    // constructor with default values of the parameters    
    NAdamGD(lossFunc *Q,LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
NAdam_GD_Template
NAdam_GD_Namespace::NAdamGD(lossFunc *Q, LD beta_m, LD beta_v, LD epsilon, LD alpha):GradientDescent<LD,lossFunc>(Q){
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;

    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
    }
}



// // The update function
NAdam_GD_Template
LD NAdam_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_w2=0,dw=0;
    this->Q->averageGrad();

    // accumulate the decay rates, in order to correct the averages 
    beta_m_ac*=beta_m_ac;
    beta_v_ac*=beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){

        // calculate decaying averages of the gradient and dw
        mE[i]=beta_m*mE[i] + (1-beta_m)*this->Q->grad[i]; 
        vE[i]=beta_v*vE[i] + (1-beta_v)*this->Q->grad[i]*this->Q->grad[i];

        // update w
        dw=alpha/(std::sqrt(vE[i]/(1-beta_v_ac)) + epsilon);
        dw*=(beta_m*mE[i] + (1-beta_m)*this->Q->grad[i])/(1-beta_m_ac);
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