#ifndef GD_const
#define GD_const

#include "GD.hpp"

GD_Template
GD_Namespace::GradientDescent(Func target, std::vector<LD> x0, LD alpha, LD tol, LD step_break){

    this->target = target; 
    
    this->alpha=alpha;
    this->tol=tol;
    this->step_break=step_break;

    
    // initialize x0,x1
    for(LD _:x0){
        this->x0.push_back(_);
        this->x1.push_back(_);
    }


}



#endif