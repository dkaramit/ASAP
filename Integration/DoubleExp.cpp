#include <iostream>
#include <vector>
#include "DoubleExp.hpp"





#define starting_exponent 5
#define maximum_exponent 12
#define relative_tolerance 1e-8
#define absolute_tolerance 1e-8
#define precision 8

#define LD long double

typedef LD (*func)(LD);

LD f(LD x){return 1/(sqrt(1+x) +sqrt(1-x) +2  );}

int main(){

    DoubleExp<func,double> DE( f,starting_exponent, maximum_exponent,
    relative_tolerance,absolute_tolerance, precision  );
    
    DE.integrate();

    std::cout<<"result: "<<DE.result<<" error: "<< DE.error <<std::endl;


    return 0;
}