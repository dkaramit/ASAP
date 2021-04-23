#ifndef Duals_funcs
#define Duals_funcs

#include"DualNumbers_class.hpp"
#include<vector>
#include<cmath>

namespace dual{
    template<class LD>
    constexpr const LD Log10E=std::log10(std::exp(1));//define log10(e) which is useful for log10 definition
    
    template<class LD>
    DualNumbers<LD> sin(const DualNumbers<LD> &x){
        DualNumbers<LD>  result(std::sin(x.getValue()),  x.getVarN());
        LD _cos_=std::cos(x.getValue());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i,_cos_*x.getGrad(i));}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> cos(const DualNumbers<LD> &x){
        DualNumbers<LD>  result(std::cos(x.getValue()),  x.getVarN());
        LD _sin_=std::sin(x.getValue());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i,-_sin_*x.getGrad(i));}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> exp(const DualNumbers<LD> &x){
        DualNumbers<LD>  result(std::exp(x.getValue()),  x.getVarN());
        LD _exp_=std::exp(x.getValue());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i,_exp_*x.getGrad(i));}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> log(const DualNumbers<LD> &x){
        DualNumbers<LD>  result(std::log(x.getValue()),  x.getVarN());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i,1/x.getValue()*x.getGrad(i));}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> log10(const DualNumbers<LD> &x){
        return   Log10E<LD>*log(x);
    }

    template<class LD>
    DualNumbers<LD> sqrt(const DualNumbers<LD> &x){
        LD _sqrt_=std::sqrt(x.getValue());
        DualNumbers<LD>  result(_sqrt_,  x.getVarN());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i,0.5/_sqrt_*x.getGrad(i));}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> tan(const DualNumbers<LD> &x){
        LD _tan_=std::tan(x.getValue());
        DualNumbers<LD>  result(_tan_,  x.getVarN());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i, x.getGrad(i)*(1+_tan_*_tan_) );}
        return   result;
    }

    template<class LD>
    DualNumbers<LD> tanh(const DualNumbers<LD> &x){
        LD _tanh_=std::tanh(x.getValue());
        DualNumbers<LD>  result(_tanh_,  x.getVarN());

        for(unsigned int i=0; i<x.getVarN(); ++i){result.setGrad(i, x.getGrad(i)*(1-_tanh_*_tanh_) );}
        return   result;
    }

    /*pow is a bit different*/
    template<class LD>
    DualNumbers<LD> pow(const DualNumbers<LD> &x, const DualNumbers<LD> &y){
        LD _pow_=std::pow(x.getValue(),y.getValue());

        DualNumbers<LD>  result(_pow_,  x.getVarN());
        for(unsigned int i=0; i<x.getVarN(); ++i){
            result.setGrad(i,_pow_*(y.getValue()/x.getValue() * x.getGrad(i) + std::log(x.getValue()) *y.getGrad(i))  );
        }

        return   result;
    }

    template <class D,class T, 
            std::enable_if_t<std::is_arithmetic<T>::value, bool> = true> 
    D pow(const D &x, const T &y){
        D Y(y,x.getVarN());
        return   pow(x,Y);
    }

    template <class D, class T, 
            std::enable_if_t<std::is_arithmetic<T>::value, bool> = true> 
    D pow(const T &y, const D &x){
        D Y(y,x.getVarN());
        return   pow(Y,x);
    }
}

#endif