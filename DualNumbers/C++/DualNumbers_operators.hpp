#ifndef Duals_op
#define Duals_op

#include"DualNumbers_class.hpp"

/*--------------------overload operators that do not make sense to be defined inside the class-------------------------------*/

// add other types with dual number
template<class LD>
DualNumbers<LD> operator+(const int &y, const DualNumbers<LD> &x){
    return  x+y;
}

template<class LD>
DualNumbers<LD> operator+(const double &y, const DualNumbers<LD> &x){
    return  x+y;
}

template<class LD>
DualNumbers<LD> operator+(const long double &y, const DualNumbers<LD> &x){
    return  x+y;
}

// subtract other types from dual number
template<class LD>
DualNumbers<LD> operator-(const int &y, const DualNumbers<LD> &x){
    return  y+(-x);
}

template<class LD>
DualNumbers<LD> operator-(const double &y, const DualNumbers<LD> &x){
    return  y+(-x);
}

template<class LD>
DualNumbers<LD> operator-(const long double &y, const DualNumbers<LD> &x){
    return  y+(-x);
}

// multiply other types with dual number
template<class LD>
DualNumbers<LD> operator*(const int &y, const DualNumbers<LD> &x){
    return  x*y;
}

template<class LD>
DualNumbers<LD> operator*(const double &y, const DualNumbers<LD> &x){
    return  x*y;
}

template<class LD>
DualNumbers<LD> operator*(const long double &y, const DualNumbers<LD> &x){
    return  x*y;
}







#endif