#ifndef GD_run
#define GD_run

#include "GD.hpp"




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