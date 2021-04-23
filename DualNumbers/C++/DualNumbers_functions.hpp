#ifndef Duals_funcs
#define Duals_funcs

#include"DualNumbers_class.hpp"
#include<vector>
#include<cmath>


template<class LD>
DualNumbers<LD> std::sin(DualNumbers<LD> x){
    std::vector<LD> grad;
    LD _cos_=std::cos(x.getValue());
    for(unsigned int i=0; i<x.getVarN(); ++i){grad.push_back(_cos_*x.getGrad(i));}
    return  DualNumbers<LD>(std::sin(x.getValue()),grad) ;
}
template<class LD>
DualNumbers<LD> std::cos(DualNumbers<LD> x){
    std::vector<LD> grad;
    LD _sin_=std::sin(x.getValue());
    for(unsigned int i=0; i<x.getVarN(); ++i){grad.push_back(-_sin_*x.getGrad(i));}
    return  DualNumbers<LD>(std::cos(x.getValue()),grad) ;
}




#endif