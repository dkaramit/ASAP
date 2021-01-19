#ifndef target_func
#define target_func


#include <cmath>
#include <vector>


// Generic target function implementation

template<class LD, class Func>
class targetFunc{
    public:
    
    Func  target;
    LD h;

    
    targetFunc(){};
    ~targetFunc(){};
    
    targetFunc(Func  target, LD h=1e-8){
        this->target=target;
        this->h=h;
        };

    targetFunc(const targetFunc  &target_obj, LD h=1e-8){  
        this->target=target_obj.target;
        this->h=h;
        };
    

    LD operator()(std::vector<LD> x){ return this->target(x);}
    
    std::vector<LD> Grad(std::vector<LD> x){
        LD dfdx0,dfdx1;
        std::vector<LD> x0,x1,Grad;

        for(LD _:x){
            x0.push_back(_);
            x1.push_back(_);
        }
        
        for(unsigned int dim=0; dim<x.size(); dim++){
            x0[dim]=x[dim]-this->h;
            x1[dim]=x[dim]+this->h;
            
            dfdx0=this->target(x0) ;
            dfdx1=this->target(x1) ;

            x0[dim]=x[dim];
            x1[dim]=x[dim];
            
            Grad.push_back((dfdx1-dfdx0)/(2*this->h));
        }

        return Grad;




    };
};



#endif