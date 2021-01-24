#ifndef GD_base
#define GD_base

#include"SGD.hpp"

/*
The base class for Stochastic Gradient Descent.
Basically it only holds the  member function (run) that runs the
loop of updates (update), which should be defined in a derived class. 
*/

#include <vector>
#include <cmath>


#define GD_Template template<class LD,class Strategy>
#define GD_Namespace StochasticGradientDescent<LD, Strategy>


GD_Template
class StochasticGradientDescent{
    public:
    Strategy strategy;
    // constructor and destructor (they will be overwritten by the derived class)
    StochasticGradientDescent(const Strategy &strategy){
        this->strategy=strategy;
    };
    ~StochasticGradientDescent(){};

    
    // function that runs the main loop.
    // abs_tol, rel_tol, , step_break: stop when _check<1 for step_break succesive steps
    // max_step: maximum number of steps
    void run(LD abs_tol=1e-5, LD rel_tol=1e-3, unsigned int step_break=100, unsigned int max_step=5000);
};




#endif