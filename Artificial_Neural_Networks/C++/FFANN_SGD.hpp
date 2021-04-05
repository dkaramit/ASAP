#ifndef FFANN_SGD
#define FFANN_SGD

#define SGD_Template template<class LD,class lossFunc>
#define SGD_Namespace StochasticGradientDescent<LD, lossFunc>


SGD_Template
class StochasticGradientDescent{
    public:
    // the loss function
    lossFunc *Q;

    ~StochasticGradientDescent()=default;
    StochasticGradientDescent(lossFunc *Q){this->Q=Q;};

    virtual LD update(LD abs_tol, LD rel_tol){return 0;}

    // function that runs the main loop.
    // abs_tol, rel_tol, , step_break: stop when _check<1 for step_break succesive steps
    // max_step: maximum number of steps
    unsigned int run(LD abs_tol=1e-5, LD rel_tol=1e-3, unsigned int step_break=100, unsigned int max_step=5000);
};


SGD_Template
unsigned int SGD_Namespace::run(LD abs_tol, LD rel_tol, unsigned int step_break, unsigned int max_step){
  
    unsigned int _s=0;
    unsigned int count_steps=1;
    LD _check=0;

    while(count_steps<=max_step){
        //strategy should have an update member. During this, w's and b's are updated.
        //it can return sumething that becomes less than one, when the gradient becomes
        //small enough (we can change it later, to make the convergence conditions more 
        //involved). 
        //It also should have access to "self" because it will need to know the 
        //structure of the network, the loss, and take their derivatives.
        _check=update(abs_tol, rel_tol);
        if(_check<1){_s+=1;}
        else{_s=0;}
        
        if(_s>step_break){break;}


        ++count_steps;
    }

    return count_steps;
}

#endif