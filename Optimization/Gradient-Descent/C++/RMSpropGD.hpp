#ifndef RMSprop_GD_class
#define RMSprop_GD_class

/*
RMSprop Gradient Descent
*/

#include<vector>
#include<cmath>

#define RMSprop_GD_Template template<class LD, class Func>
#define RMSprop_GD_Namespace RMSpropGD<LD,Func>

RMSprop_GD_Template
class RMSpropGD{
    public:
    // function to be minimized
    Func target;
    // the parameters of the algorithm
    LD gamma,epsilon,alpha;

    // position vector
    std::vector<LD> x;

    // vector that holds the positions
    std::vector<std::vector<LD>> steps;
    
    // dimension of x 
    unsigned int dim;

    // vector that holds the gradient
    std::vector<LD> grad;

    // vector that will be used to hold the decaying averages (gE[i] corresponds to the direction of x[i])   
    std::vector<LD> gE;

    // constractor (with some default values)
    RMSpropGD(Func target, std::vector<LD> x0, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);
    RMSpropGD(){};

    // overloading of operator= to make sure everything is copied correctly 
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
    // calculate the gradient at the current position
    this->target.Grad(this->x,this->grad);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // caclulate the decaying average of the gradient
        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*this->grad[i]*this->grad[i];
        
        // update the position
        dx=std::sqrt( 1/(this->gE[i]+this->epsilon)  )*this->grad[i]*this->alpha;
        this->x[i]=this->x[i] - dx;

        // grad^2/(abs_tol + x * rel_tol)^2 for this direction
        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(this->grad[i]/_x2)*(this->grad[i]/_x2);
    }
    // append the new posiotion in steps 
    this->steps.push_back(x);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}



#endif