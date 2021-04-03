#ifndef Func_HEAD
#define Func_HEAD


#include <cmath>
#include <vector>
// Base class for the function to be minimized
// You should define a class that inherits from this, so that you can define operator()
// and overload the derivative.
template<class LD>
class Function{
    
    public:
    //vector of the free parameters of the model
    std::vector<LD> x;
    //this is to hold the absolute minimum in case GD escapes it
    std::vector<LD> minimum;
    // size of x 
    unsigned int dim;
    
    // this will be used to hold the gradients
    std::vector<LD> grad;

    Function()=default;
    Function(const std::vector<LD> &x0){
        // x0: initial x
        this->x=x0;
        this->minimum=x0;
        this->dim=x0.size();
        this->grad.reserve(this->dim);
    }

    virtual LD operator()(std::vector<LD> &x){return 0;}

    virtual void derivative(std::vector<LD> &x, LD h=1e-5){
        std::vector<LD> _x=x;
        LD heff;
        LD f0,f1;
        for(unsigned int i=0; i<dim; ++i){
            heff=std::abs(_x[i])*h+h;
            _x[i]-=heff;
            f0=this->operator()(_x);
            _x[i]+=2*heff;
            f1=this->operator()(_x);

            _x[i]-=heff;
            grad[i]=(f1-f0)/(2*heff);
        }
    }
};

#endif