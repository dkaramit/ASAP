#ifndef target_func
#define target_func


#include <cmath>
#include <vector>


// Generic target function implementation
// Here the function is assumed to get vector<LD> and return LD
// So, we can be another class with an overloaded operator() or
// using Func = LD (*)(const std::vector<LD>&); //recommended
// using Func = LD (*)(std::vector<LD>);


template<class LD, class Func>
class targetFunc{
    public:
    Func  target;
    LD h;

    
    targetFunc(){};
    ~targetFunc(){};
    
    targetFunc(Func  target, LD h=1e-8){
        // target: the target function
        // h: stepsize for the derivative 
        this->target=target;
        this->h=h;
        };

    targetFunc(const targetFunc  &target_obj, LD h=1e-8){  
        this->target=target_obj.target;
        this->h=h;
        };
    

    LD operator()(const std::vector<LD> &x){ return this->target(x);}
    
    void Grad(const std::vector<LD> &x, std::vector<LD> &grad){
        // grad must have at least the same size x 
        //grad.reserve(x.size());// you can use this to ensure it, but it is probably slower

        std::vector<LD> xp=x; //I will use xp as the x \pm h needed
        
        for(unsigned int dim=0; dim<x.size(); dim++){
            xp[dim]+=this->h;
            grad[dim]=this->target(xp)/(2*this->h) ;
            
            xp[dim]+=-2*this->h;
            grad[dim]+=-this->target(xp)/(2*this->h) ;
        }
    };
};



#endif