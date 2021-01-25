#ifndef Vanilla_GD_class
#define Vanilla_GD_class

/*
Vanilla Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>


#define Vanilla_GD_Template template<class LD, class Func>
#define Vanilla_GD_Namespace VanillaGD<LD,Func>

Vanilla_GD_Template
class VanillaGD{
    public:
    //function to be minimized
    Func target;
    // the learning rate
    LD alpha;

    // the current position
    std::vector<LD> x;

    // a vector that holds the steps the algorithm takes
    std::vector<std::vector<LD>> steps;
    
    // the dimension of x
    unsigned int dim;

    // a vector that holds the gradient (same dim as x)
    std::vector<LD> grad;

    // constructor (a=1e-1 is the default value, but probably not that good in general)
    VanillaGD(Func target, std::vector<LD> x0, LD alpha=1e-1);
    // just an "empty" constructor
    VanillaGD(){};

    // Overload  operator= to make sure that it is copied correctly
    VanillaGD& operator=(const VanillaGD& strategy){
        this->target=strategy.target;
        this->alpha=strategy.alpha;
        
        this->x=strategy.x;
        this->dim=strategy.dim;
        this->grad=strategy.grad;
        
        this->steps=strategy.steps;
        
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
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(Func target, std::vector<LD> x0, LD alpha){
    this->target=target;
    this->alpha=alpha;

    this->x=x0;
    this->dim=(this->x).size();
    this->grad.resize(this->dim);
    
    this->steps.push_back(x0);
}

// The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0;
    // calculate the gradient at current position
    this->target.Grad(this->x,this->grad);
    
    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update the position
        this->x[i] = this->x[i] - (this->alpha)*this->grad[i] ; 
        
        // grad^2/(abs_tol + x * rel_tol)^2 for this direction
        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    
    //put the new x in steps 
    this->steps.push_back(x);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}



#endif