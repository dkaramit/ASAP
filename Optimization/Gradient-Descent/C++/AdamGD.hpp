#ifndef Adam_GD_class
#define Adam_GD_class

/*
Adam Gradient Descent (i.e. no adaptation of the learning rate).
AdamGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

#include"GD.hpp"

#define Adam_GD_Template template<class LD, class Func>
#define Adam_GD_Namespace AdamGD<LD,Func>

Adam_GD_Template
class AdamGD{
    public:
    Func target;
    LD beta_m,beta_v,gamma,epsilon,alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x, mE, vE;

    unsigned int dim;
    std::vector<LD> grad;
    LD beta_m_ac,beta_v_ac;


    AdamGD(Func target, std::vector<LD> x0, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    AdamGD(){};

    AdamGD& operator=(const AdamGD& strategy){
        this->target=strategy.target;
        this->beta_m=strategy.beta_m;
        this->beta_v=strategy.beta_v;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;
        this->x=strategy.x;
        
        this->dim=strategy.dim;
        this->grad=strategy.grad;
        this->beta_m_ac=strategy.beta_m_ac;
        this->beta_v_ac=strategy.beta_v_ac;
        this->steps=strategy.steps;

        this->mE=strategy.mE;
        this->vE=strategy.vE;

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
Adam_GD_Template
Adam_GD_Namespace::AdamGD(Func target, std::vector<LD> x0, LD beta_m, LD beta_v, LD epsilon, LD alpha){
    this->target=target;
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;
    this->x=x0;
    
    this->dim=(this->x).size();
    this->grad.resize(this->dim);
    this->steps.push_back(x0);

    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;


    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
    }

}

// The update function
Adam_GD_Template
LD Adam_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dx=0,_check=0,_x2=0;

    this->target.Grad(this->x,this->grad);
    
    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*this->grad[i];
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*this->grad[i]*this->grad[i];

        dx=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac) ) + this->epsilon);
        dx*=this->mE[i]/(1-this->beta_m_ac);

        this->x[i]=this->x[i] - dx;


        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(x);

    return _check;
}



#endif