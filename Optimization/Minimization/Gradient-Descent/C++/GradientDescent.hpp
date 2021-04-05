#ifndef GD_Head
#define GD_Head

/*
Basically it only holds the  member function (run) that runs the
loop of updates (update), which should be defined in a derived class. 
*/

#include <vector>
#include <cmath>


#define GD_Template template<class LD,class Function>
#define GD_Namespace GradientDescent<LD, Function>


GD_Template
class GradientDescent{
    public:
    // the function to be minimized (instance of class that is derived from Function)
    Function *function;
    LD f_min;
    // the dimension of the x  
    unsigned int dim;    
    // a vector that holds the w as the algorith runs
    std::vector<std::vector<LD>> steps;


    ~GradientDescent()=default;
    GradientDescent(Function *function){
        this->function=function;
        this->f_min=function->operator()(function->x);
        this->dim=function->dim;
        steps.push_back(this->function->x);
    };

    virtual LD update(LD abs_tol, LD rel_tol){return 0;};
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
        // update should return a number that when it is smaller than 1
        // the loop stops.
        // This number can depend on two abs_tol and rel_tol
        _check=update(abs_tol,rel_tol);

        count_steps++;

        if(_check<1){_s++;}
        else{_s=0;}
        if(_s>step_break){break;}

    }
}


#endif