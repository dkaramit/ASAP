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
class NAdamGD: public GD_Namespace{
    public:
    Func target;
    LD beta_m,beta_v,gamma,epsilon,alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x, mE, vE, dx;

    unsigned int dim;
    LD beta_m_ac,beta_v_ac;


    NAdamGD(Func target, std::vector<LD> x0, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);

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
    this->steps.push_back(x0);

    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;


    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
        this->dx.push_back(0);
    }

}






// The update function
NAdam_GD_Template
LD NAdam_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0;
    std::vector<LD> grad; 

    this->target.Grad(this->x,grad);
    
    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*grad[i]; 
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*grad[i]*grad[i];

        this->dx[i]=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac)) + this->epsilon);
        this->dx[i]*=(this->beta_m*this->mE[i] + (1-this->beta_m)*grad[i])/(1-this->beta_m_ac);

        this->x[i]=this->x[i] - this->dx[i];


        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(grad[i]/_x2)*(grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(x);

    return _check;
}



#endif