#ifndef NAdam_GD_class
#define NAdam_GD_class

/*
NAdam Gradient Descent (i.e. no adaptation of the learning rate).
NAdamGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

#include"GD.hpp"

#define NAdam_GD_Template template<class LD, class Func>
#define NAdam_GD_Namespace NAdamGD<LD,Func>

NAdam_GD_Template
class NAdamGD{
    public:
    // function to be minimized
    Func target;
    // parameters of the algorithm
    LD beta_m,beta_v,gamma,epsilon,alpha;

    // vector of (current) position
    std::vector<LD> x;
    
    // dimension of x
    unsigned int dim;

    // vector that will be used to hold the gradient at every step (same dimension as x)
    std::vector<LD> grad;

    // vector of positions
    std::vector<std::vector<LD>> steps;

    // vectors that hold the decaying averages of m and v 
    std::vector<LD> mE, vE;

    // variables that accumulate beta_{m,v}^iteration 
    LD beta_m_ac,beta_v_ac;

    // costructor with default arguments
    NAdamGD(Func target, std::vector<LD> x0, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    NAdamGD(){};

    // overloading of operator= so that everything is copied correctly 
    NAdamGD& operator=(const NAdamGD& strategy){
        this->target=strategy.target;
        this->beta_m=strategy.beta_m;
        this->beta_v=strategy.beta_v;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;
        this->x=strategy.x;
        
        this->dim=strategy.dim;
        this->grad=strategy.grad;

        this->steps=strategy.steps;
        

        this->mE=strategy.mE;
        this->vE=strategy.vE;

        this->beta_m_ac=strategy.beta_m_ac;
        this->beta_v_ac=strategy.beta_v_ac;

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
NAdam_GD_Template
NAdam_GD_Namespace::NAdamGD(Func target, std::vector<LD> x0, LD beta_m, LD beta_v, LD epsilon, LD alpha){
    this->target=target;
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;
    this->x=x0;
    
    this->dim=(this->x).size();
    this->grad.resize(this->dim);

    this->steps.push_back(x0);


    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
    }

    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;

}

// The update function
NAdam_GD_Template
LD NAdam_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dx=0,_check=0,_x2=0;

    // calculate gradient at current position
    this->target.Grad(this->x,this->grad);
    
    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the decaying averages of m and v
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*this->grad[i]; 
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*this->grad[i]*this->grad[i];
        
        // update the position
        dx=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac)) + this->epsilon);
        dx*=(this->beta_m*this->mE[i] + (1-this->beta_m)*this->grad[i])/(1-this->beta_m_ac);
        this->x[i]=this->x[i] - dx;

        // grad^2/(abs_tol + x * rel_tol)^2 for this direction
        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    
    // append new position to steps
    this->steps.push_back(x);
    
    //calculate _check 
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}



#endif