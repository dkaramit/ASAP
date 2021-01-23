#ifndef GD_base
#define GD_base

#include"GD.hpp"

/*
The base class for Gradient Descent.
Basically it only holds the  member function (run) that runs the
loop of updates (update), which should be defined in a derived class. 
*/

#include <vector>
#include <cmath>


#define GD_Template template<class LD>
#define GD_Namespace GradientDescent<LD>


GD_Template
class GradientDescent{
    public:
    
    // constructor and destructor (they will be overwritten by the derived class)
    GradientDescent(){};
    ~GradientDescent(){};

    // virtual update (it will be overwritten by the derived class)
    // update should return a number that when it is smaller than 1
    // the main loop stops.
    // This number can depend on two abs_tol and rel_tol
    virtual LD update(LD abs_tol, LD rel_tol);//this will be overwritten by the derived classes
    
    // function that runs the main loop.
    // abs_tol, rel_tol, , step_break: stop when _check<1 for step_break succesive steps
    // max_step: maximum number of steps
    void run(LD abs_tol=1e-5, LD rel_tol=1e-3, unsigned int step_break=100, unsigned int max_step=5000);
};


GD_Template
void GD_Namespace::run(LD abs_tol, LD rel_tol, unsigned int step_break, unsigned int max_step){
    
    unsigned int _s=0;
    unsigned int count_steps=1;
    
    LD _check;

    while(count_steps<=max_step){
        _check=this->update(abs_tol,rel_tol);

        count_steps++;

        if(_check<1){_s++;}
        else{_s=0;}
        if(_s>step_break){break;}

    }
}




#endif