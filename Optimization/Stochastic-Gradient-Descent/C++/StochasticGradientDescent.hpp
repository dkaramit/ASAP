#ifndef SGD_base
#define SGD_base

/*
The base class for Stochastic Gradient Descent.
Basically it only holds the  member function (run) that runs the
loop of updates (update), which should be defined in a derived class. 
*/

#include <vector>
#include <cmath>


#define SGD_Template template<class LD,class Strategy>
#define SGD_Namespace StochasticGradientDescent<LD, Strategy>


SGD_Template
class StochasticGradientDescent{
    public:
    Strategy *strategy;

    StochasticGradientDescent(Strategy *strategy){
        this->strategy=strategy;
    };
    ~StochasticGradientDescent(){};

    
    // function that runs the main loop.
    // abs_tol, rel_tol, , step_break: stop when _check<1 for step_break succesive steps
    // max_step: maximum number of steps
    void run(LD abs_tol=1e-5, LD rel_tol=1e-3, unsigned int step_break=100, unsigned int max_step=5000);
};


SGD_Template
void SGD_Namespace::run(LD abs_tol, LD rel_tol, unsigned int step_break, unsigned int max_step){
    
    unsigned int _s=0;
    unsigned int count_steps=1;
    
    LD _check;

    while(count_steps<=max_step){
        // update should return a number that when it is smaller than 1
        // the loop stops.
        // This number can depend on two abs_tol and rel_tol
        _check=this->strategy->update(abs_tol,rel_tol);

        count_steps++;

        if(_check<1){_s++;}
        else{_s=0;}
        if(_s>step_break){break;}

    }
}


#endif