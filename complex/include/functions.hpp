#ifndef COMPLEX_FUNC_INCLUDED
#define COMPLEX_FUNC_INCLUDED

#include "complex_headers.hpp"


/*================= new functions====================================*/
complex conjugate(const complex& z)
{

    return z.re-Imag* z.im;
}
/*================= End new functions====================================*/


/*====================function overloading======================*/
complex log(const  complex& z)
{    
    return log(cabs(z)) +Imag*arg(z)  ;
}

complex exp(const  complex& z)
{
    return exp(z.re)*cos(z.im) + Imag*exp(z.re)*sin(z.im);
}

complex cos(const complex& z)
{

    return (exp(Imag*z)+exp(-Imag*z))/2;
}

complex sin(const complex& z)
{

    return (exp(Imag*z)-exp(-Imag*z))/(2*Imag);;
}

complex tan( const complex& z)
{
    return sin(z)/cos(z);
}

double arg(const complex& z){
        return atan2(z.im,z.re);
}

complex pow(const complex& z1,const  complex& z2)
{
    return exp(z2*log(z1));
}

complex pow(const double& a,const  complex& z)
{
    return exp(z*log(a));
}

complex pow(const complex& z, const double& a)
{
    complex w;
    w=exp(a*Imag*arg(z));

    return pow(cabs(z),a)*w.re +Imag*(pow(cabs(z),a)*w.im);
}

double cabs(const complex& z)
{
    return sqrt(z.im*z.im + z.re*z.re);
}/*============ End function overloading==================*/




#endif