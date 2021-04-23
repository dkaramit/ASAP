#ifndef Duals_con
#define Duals_con

#include"DualNumbers_class.hpp"


Dual_template
Dual_namespace::DualNumbers(LD value, unInt varN){
    this->value=value;
    this->varN=varN;

    (this->grad).resize(varN);
}




Dual_template
Dual_namespace::DualNumbers(LD value, vecGrad grad){
    this->value=value;
    this->varN=grad.size();

    (this->grad).resize(varN);
    for(unInt i=0; i<this->varN; ++i){
        this->grad[i]=grad[i];
    }
}

Dual_template
Dual_namespace::DualNumbers(const DualNumbers<LD> &D){
    this->value=D.value;
    this->varN=D.grad.size();

    (this->grad).resize(this->varN);
    for(unInt i=0; i<this->varN; ++i){
        this->grad[i]=D.grad[i];
    }
}


#endif