#ifndef AdaDelta_GD_class
#define AdaDelta_GD_class

/*
AdaDelta Gradient Descent
*/

#include<vector>
#include<cmath>

#define AdaDelta_GD_Template template<class LD, class Func>
#define AdaDelta_GD_Namespace AdaDeltaGD<LD,Func>

AdaDelta_GD_Template
class AdaDeltaGD{
    public:
    // function to be minimized
    Func target;
    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // position vector
    std::vector<LD> x;
    // dimension of x 
    unsigned int dim;

    // vector that holds the gradient at the current position
    std::vector<LD> grad;
    
    // vector that holds the positions the algorithm takes
    std::vector<std::vector<LD>> steps;
    
    // decaying averages of gradient and steps
    std::vector<LD> gE,dxE;
    

    // constructor with default variables
    AdaDeltaGD(Func target, std::vector<LD> x0, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1);
    AdaDeltaGD(){};

    // overloading of operator= to make sure all attributes are copied correctly
    AdaDeltaGD& operator=(const AdaDeltaGD& strategy){
        this->target=strategy.target;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;
        this->x=strategy.x;
        
        this->dim=strategy.dim;
        
        this->grad=strategy.grad;

        this->steps=strategy.steps;

        this->gE=strategy.gE;
        this->dxE=strategy.dxE;

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
AdaDelta_GD_Template
AdaDelta_GD_Namespace::AdaDeltaGD(Func target, std::vector<LD> x0, LD gamma, LD epsilon, LD alpha){
    this->target=target;
    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;
    this->x=x0;
    
    this->dim=(this->x).size();

    this->grad.resize(this->dim);
    
    this->steps.push_back(x0);

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
        this->dxE.push_back(0);
    }

}

// The update function
AdaDelta_GD_Template
LD AdaDelta_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dx=0,_check=0,_x2=0;
    // calculate the gradient at the current position
    this->target.Grad(this->x,this->grad);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the decaying average of the gradient
        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*this->grad[i]*this->grad[i];
        
        // update the position
        dx=std::sqrt( (this->dxE[i]+this->epsilon)/(this->gE[i]+this->epsilon)  )*this->grad[i]*this->alpha;
        this->x[i]=this->x[i] - dx;
        
        //calculate the decaying average of dx (in the i direction)
        this->dxE[i]=this->gamma*this->dxE[i] + (1-this->gamma)*dx*dx;

        // grad^2/(abs_tol + x * rel_tol)^2 for this direction
        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    // append new position to steps
    this->steps.push_back(x);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}



#endif