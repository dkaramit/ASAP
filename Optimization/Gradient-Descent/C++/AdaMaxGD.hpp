#ifndef AdaMax_GD_class
#define AdaMax_GD_class

/*
AdaMax Gradient Descent
*/

#include<vector>
#include<cmath>

#define AdaMax_GD_Template template<class LD, class Func>
#define AdaMax_GD_Namespace AdaMaxGD<LD,Func>

AdaMax_GD_Template
class AdaMaxGD{
    public:
    // function to be minimized
    Func target;
    // parameters of the algorithm
    LD beta_m,beta_v,gamma,epsilon,alpha;
    
    // position vector 
    std::vector<LD> x;
    // dimension of position vector
    unsigned int dim;

    // vector that will be used to hold the gradient at each step 
    std::vector<LD> grad;

    // vector that holds the steps the algorithm takes
    std::vector<std::vector<LD>> steps;

    // vector for the decaying averge
    std::vector<LD> mE;
    // vecor for the maximum v (see the update function for its definition)
    std::vector<LD> v_max;

    // parameter for the accumulation of beta_m^iteration
    LD beta_m_ac;

    // constructor with some default values
    AdaMaxGD(Func target, std::vector<LD> x0, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    AdaMaxGD(){};

    // overloading of operator= so that everything is copied correctly 
    AdaMaxGD& operator=(const AdaMaxGD& strategy){
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
        this->v_max=strategy.v_max;

        this->beta_m_ac=strategy.beta_m_ac;
        
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
AdaMax_GD_Template
AdaMax_GD_Namespace::AdaMaxGD(Func target, std::vector<LD> x0, LD beta_m, LD beta_v, LD epsilon, LD alpha){
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
        this->v_max.push_back(0);
    }

    this->beta_m_ac=beta_m;
}

// The update function
AdaMax_GD_Template
LD AdaMax_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dx=0,_check=0,_x2=0;

    // calculate gradient at current position
    this->target.Grad(this->x,this->grad);
    
    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the decaying average of m
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*this->grad[i]; 
        // determine v_max
        this->v_max[i]=(std::abs(this->grad[i]) > this->beta_v*this->v_max[i]) ? std::abs(this->grad[i]) : this->beta_v*this->v_max[i]; 
        
        // update position        
        dx=this->alpha/(this->v_max[i] + this->epsilon)  *this->mE[i]/(1-this->beta_m_ac);
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