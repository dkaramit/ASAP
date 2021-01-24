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
    unsigned int dim;

    targetFunc(){};
    targetFunc(TFunc func, std::vector<LD> w0){
        this->f=func;
        this->w=w0;
        this->dim=w0.size();
    }

    targetFunc& operator=(const targetFunc& tf){
        this->f=tf.f;
        this->w=tf.w;
        this->dim=tf.dim;

        return *this;
    }

    void operator()(const std::vector<LD> &x, std::vector<LD> &y)
    {this->f(x,this->w,y);}
};

template<class LD, class QFunc, class TFunc>
class lossFunc{
    public:
    QFunc Q;
    TFunc target;
    LD h;

    lossFunc(const QFunc &Q,const TFunc &target, LD h=1e-8){
        this->target=target;
        this->Q=Q;
        this->h=h;
    }

    LD operator()(const std::vector<LD> &x, const std::vector<LD> &y)
    {return    this->Q(target, x, y);}


    void Grad(const std::vector<LD> &x, const std::vector<LD> &y, std::vector<LD> &grad){
        // grad must have at least the same size y 
        //grad.reserve(y.size());// you can use this to ensure it, but it is probably slower
        
        for(unsigned int dim=0; dim<target.dim; dim++){
            target.w[dim]+=this->h;
            grad[dim]=this->operator()(x,y)/(2*this->h) ;
            
            target.w[dim]+=-2*this->h;
            grad[dim]+=-this->operator()(x,y)/(2*this->h) ;
            
            target.w[dim]+=-this->h;//return w to its initial value
        }
    };
};





#endif