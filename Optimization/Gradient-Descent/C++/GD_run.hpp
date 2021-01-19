#ifndef GD_run
#define GD_run

#include "GD.hpp"



GD_Template
void GD_Namespace::update(){
    this->grad=this->target.Grad(this->x0);
    this->x1 = this->x0;
    for(unsigned int dim=0; dim<this->x0.size();dim++){
        this->x1[dim]-=this->alpha*grad[dim];
    }

}


GD_Template
void GD_Namespace::run(){
    int _s=0;
    LD _check=0.;
    while(true){
        this->update();
        
        this->points.push_back(this->x1);


        _check=0.;
        for(LD _:this->grad){_check+=_*_;}
        _check=std::sqrt(_check);


        if(_check<this->tol/this->alpha){_s+=1;}
        else{_s=0;}

        if (_s>this->step_break){break;}

        this->x0=this->x1;
    }


}

#endif