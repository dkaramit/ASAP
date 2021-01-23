#ifndef RMSprop_GD_class
#define RMSprop_GD_class

/*
RMSprop Gradient Descent (i.e. no adaptation of the learning rate).
RMSpropGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

#define RMSprop_GD_Template template<class LD, class Func>
#define RMSprop_GD_Namespace RMSpropGD<LD,Func>

RMSprop_GD_Template
class RMSpropGD{
    public:
    Func target;
    LD gamma,epsilon,alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x,gE;

    unsigned int dim;
    std::vector<LD> grad;


    RMSpropGD(Func target, std::vector<LD> x0, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);
    RMSpropGD(){};

    RMSpropGD& operator=(const RMSpropGD& strategy){
        this->target=strategy.target;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;
        this->x=strategy.x;
        
        this->dim=strategy.dim;
        this->grad=strategy.grad;
        this->steps=strategy.steps;

        this->gE=strategy.gE;

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
RMSprop_GD_Template
RMSprop_GD_Namespace::RMSpropGD(Func target, std::vector<LD> x0, LD gamma, LD epsilon, LD alpha){
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
    }

}

// The update function
RMSprop_GD_Template
LD RMSprop_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dx=0,_check=0,_x2=0;
    this->target.Grad(this->x,this->grad);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*this->grad[i]*this->grad[i];
        dx=std::sqrt( 1/(this->gE[i]+this->epsilon)  )*this->grad[i]*this->alpha;
        this->x[i]=this->x[i] - dx;


        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(x);

    return _check;
}



#endif