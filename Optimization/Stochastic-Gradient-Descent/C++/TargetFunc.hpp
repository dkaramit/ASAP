#ifndef target_func
#define target_func


#include <cmath>
#include <vector>


// Generic target function implementation

template<class LD, class TFunc>
class targetFunc{
    public:
    TFunc f;
    std::vector<LD> w;
    std::vector<LD> *Z;
    unsigned int dim;

    targetFunc(){};
    targetFunc(TFunc func,const std::vector<LD> &w0){
        this->f=func;
        this->w=w0;
        this->dim=w0.size();
    }

    // I want to pass the entire model, and allow the optimization algorithms to 
    // change it. So I'll need to pass its reference 
    // (e.g. in lossFunc I have TFunc * as the target)
    targetFunc* operator=(targetFunc *tf){
        this->f=tf->f;
        this->w=tf->w;
        this->dim=tf->dim;
        return this;
    }

    void operator()(const std::vector<LD> &x, std::vector<LD> &y)
    {this->f(x,this->w,y);}
};

template<class LD, class QFunc, class TFunc>
class lossFunc{
    public:
    QFunc Q;
    TFunc *target;
    LD h;


    lossFunc(){};
    lossFunc(const QFunc &Q, TFunc *target, LD h=1e-8){
        this->target=target; //make it explicit 
        this->Q=Q;
        this->h=h;
    }
  
    
    LD operator()(const std::vector<LD> &x, const std::vector<LD> &y)
    {return    this->Q(*(this->target), x, y);}


    void Grad(const std::vector<LD> &x, const std::vector<LD> &y, std::vector<LD> &grad){
        // grad must have the same size as target->w
        //grad.reserve(target->w.size());// you can use this to ensure it, but it is probably slower
        
        for(unsigned int dim=0; dim<target->dim; dim++){
            target->w[dim]+=this->h;
            grad[dim]=this->operator()(x,y)/(2*this->h) ;
            
            target->w[dim]+=-2*this->h;
            grad[dim]+=-this->operator()(x,y)/(2*this->h) ;
            
            target->w[dim]+=-this->h;//return w to its initial value
        }
    };
};





#endif