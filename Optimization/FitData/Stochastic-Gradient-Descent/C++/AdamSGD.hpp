#ifndef Adam_SGD_class
#define Adam_SGD_class
#include"StochasticGradientDescent.hpp"

/*
Adam Stochastic Gradient Descent
*/

#include<vector>
#include<cmath>

#define Adam_SGD_Template template<class LD, class lossFunc>
#define Adam_SGD_Namespace AdamSGD<LD,lossFunc>

Adam_SGD_Template
class AdamSGD: public StochasticGradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;

    // vecors for the decaying averages of m and v
    std::vector<LD> mE, vE;

    // variables that accumulate beta_{m,v}^iteration
    LD beta_m_ac,beta_v_ac;
    
    AdamSGD()=default;
    // constructor with default values of the parameters    
    AdamSGD(lossFunc *Q, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Adam_SGD_Template
Adam_SGD_Namespace::AdamSGD(lossFunc *Q, LD beta_m, LD beta_v, LD epsilon, LD alpha):StochasticGradientDescent<LD,lossFunc>(Q){
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
Adam_SGD_Template
LD Adam_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    LD dw=0,_check=0,_w2=0;
    this->Q->randomPoint();

    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the gradient at current value of w and at the index^th data point 
        this->Q->grad(i);

        // calculate the decaying averages
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*this->Q->dQdw;
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*this->Q->dQdw*this->Q->dQdw;

        // update w
        dw=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac) ) + this->epsilon);
        dw*=this->mE[i]/(1-this->beta_m_ac);
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