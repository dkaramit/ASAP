#ifndef target_func
#define target_func


#include <cmath>
#include <vector>


// Generic target function implementation

template<class LD>
class targetFunc{
    /*
    This is how the function should look like.
    The key point is to have way to update the parameters w.
    */
   using Func=std::vector<LD>& (*)(std::vector<LD>& ) 
    public:
    Func f;
    std::vector<LD> w0;
    unsigned int dim;

    targetFunc(Func func, std::vector<LD> w0){
        this->f=func;
        this->w0=w0;
        this->dim=w0.size();
    }

    std::vector<LD>& operator()(std::vector<LD> &x){ return this->f(x);}
};

template<class LD, class Func>
class lossFunc{
    public:
    
};





#endif