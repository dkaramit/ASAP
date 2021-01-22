#ifndef AdaDelta_GD_class
#define AdaDelta_GD_class

/*
AdaDelta Gradient Descent (i.e. no adaptation of the learning rate).
AdaDeltaGD is a class rderived from GradientDescent
*/

#include<vector>
#include<cmath>

#include"GD.hpp"

#define AdaDelta_GD_Template template<class LD, class Func>
#define AdaDelta_GD_Namespace AdaDeltaGD<LD,Func>

AdaDelta_GD_Template
class AdaDeltaGD: public GD_Namespace{
    public:
    Func target;
    LD gamma,epsilon,alpha;

    std::vector<std::vector<LD>> steps;
    std::vector<LD> x,gE, dxE, dx;

    unsigned int dim;


    AdaDeltaGD(Func target, std::vector<LD> x0, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1);

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
    this->steps.push_back(x0);

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
        this->dxE.push_back(0);
        this->dx.push_back(0);
    }

}






// The update function
AdaDelta_GD_Template
LD AdaDelta_GD_Namespace::update(LD abs_tol, LD rel_tol){

    LD _check=0,_x2=0;
    std::vector<LD> grad; 

    this->target.Grad(this->x,grad);

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*grad[i]*grad[i];
        this->dx[i]=std::sqrt( (this->dxE[i]+this->epsilon)/(this->gE[i]+this->epsilon)  )*grad[i]*this->alpha;
        this->dxE[i]=this->gamma*this->dxE[i] + (1-this->gamma)*this->dx[i]*this->dx[i];
        this->x[i]=this->x[i] - this->dx[i];


        _x2=abs_tol + this->x[i] * rel_tol;
        _check+=(grad[i]/_x2)*(grad[i]/_x2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(x);

    return _check;
}



#endif