#ifndef AdaMax_GD_class
#define AdaMax_GD_class
#include"GradientDescent.hpp"

/*
AdaMax Gradient Descent
*/

#include<vector>
#include<cmath>

#define AdaMax_GD_Template template<class LD, class lossFunc>
#define AdaMax_GD_Namespace AdaMaxGD<LD,lossFunc>

AdaMax_GD_Template
class AdaMaxGD: public GradientDescent<LD,lossFunc>{
    public:
    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;
    
    // vector for the decaying averages of m
    std::vector<LD> mE;
    // vector for v_max (see update for its definition)
    std::vector<LD> v_max;

    // variables that accumulate beta_{m}^iteration
    LD beta_m_ac;

    AdaMaxGD()=default;
    // constructor with default values of the parameters    
    AdaMaxGD(lossFunc *Q, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
AdaMax_GD_Template
AdaMax_GD_Namespace::AdaMaxGD(lossFunc *Q, LD beta_m, LD beta_v, LD epsilon, LD alpha):GradientDescent<LD,lossFunc>(Q){
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->beta_m_ac=beta_m;

    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->v_max.push_back(0);
    }
}

// // The update function
AdaMax_GD_Template
LD AdaMax_GD_Namespace::update(LD abs_tol, LD rel_tol){
    LD _check=0,_w2=0,dw=0;
    
    this->Q->averageGrad();

    // accumulate the decay rates, in order to correct the averages 
    beta_m_ac*=beta_m_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){

        // caclulate the decaying average of the gradient and v_max
        mE[i]=beta_m*mE[i] + (1-beta_m)*this->Q->grad[i]; 
        v_max[i]=(std::abs(this->Q->grad[i]) > beta_v*v_max[i]) ? std::abs(this->Q->grad[i]) : beta_v*v_max[i]; 

        // update w
        dw=alpha/(v_max[i] + epsilon)  *mE[i]/(1-beta_m_ac);
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