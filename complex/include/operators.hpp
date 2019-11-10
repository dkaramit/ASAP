#ifndef COMPLEX_OP_INCLUDED
#define COMPLEX_OP_INCLUDED


#include "complex_headers.hpp"


/*===================Operator overloading============================*/
//equal
complex& complex::operator=(const complex& z){
    this->re=z.re;
    this->im=z.im;

    return *this;
}

complex& complex::operator=(const int& a){
    this->re=a;
    this->im=0;
   return *this;
}
complex& complex::operator=(const double& a){
    this->re=a;
    this->im=0;
   return *this;
}
/*==================addition=========================================*/
complex operator+(const complex& z1, const complex& z2)
{
    complex w(z1.re+z2.re,z1.im+z2.im);
    return w;
}

complex operator+(const double& a, const complex& z)
{
    complex w(a+z.re,z.im);

    return  w ;
}

complex operator+(const int& a, const complex& z)
{
    complex w(a+z.re,z.im);

    return w;
}

complex operator+(const complex& z, const double& a)
{
    complex w(a+z.re,z.im);
    return w;
}

complex operator+(const complex& z, const int& a)
{
    complex w(a+z.re,z.im);
    return w;
}

/*==================substraction=========================================*/
complex operator-(const complex& z1, const complex& z2)
{
    complex w(z1.re-z2.re,z1.im-z2.im);
    return w;
}

complex operator-(const double& a, const complex& z)
{
    complex w(a-z.re,-z.im);
    return w;
}

complex operator-(const int& a, const complex& z)
{
complex w(a-z.re,-z.im);
    return w;
}

complex operator-(const complex& z, const double& a)
{
    complex w(z.re-a,z.im);
    return w;
}

complex operator-(const complex& z, const int& a)
{
    complex w(z.re-a,z.im);
    return w;
}

complex operator-(const complex& z)
{
    complex w(-z.re,-z.im);
    return w;
}

/*==============multiplication===========================*/

complex operator*(const complex& z1, const complex& z2)
{
    complex w;
    w.re=(z1.re*z2.re -z1.im*z2.im) ;
    w.im=(z1.re*z2.im+z1.im*z2.re);
    return w;
}

complex operator*(const double& a, const complex& z)
{
    complex w;
    w.re=(a*z.re);
    w.im=(a*z.im);
    return w;
}

complex operator*(const int& a, const complex& z)
{
    complex w;
    w.re=(a*z.re);
    w.im=(a*z.im);
    return w;
}

complex operator*(const complex& z, const double& a)
{
    complex w;
    w.re=(a*z.re);
    w.im=(a*z.im);
    return w;
}

complex operator*(const complex& z, const int& a)
{
    complex w;
    w.re=(a*z.re);
    w.im=(a*z.im);
    return w;
}

/*==============division===========================*/

complex operator/(const complex& z1, const complex& z2)
{
    complex w;
    w=z1*conjugate(z2)/(pow(cabs(z2),2.));
    return w;
}

complex operator/(const double& a, const complex& z)
{
    complex w;
    w.re=(a/(pow(cabs(z),2))*conjugate(z).re);
    w.im=(a/(pow(cabs(z),2))*conjugate(z).im);
    return w;
}

complex operator/(const int& a, const complex& z)
{
    complex w;
    w.re=(a/(pow(cabs(z),2.))*conjugate(z).re);
    w.im=(a/(pow(cabs(z),2.))*conjugate(z).im);
    return w;
}

complex operator/(const complex& z, const double& a)
{
    complex w;
    w.re=(z.re/a);
    w.im=(z.im/a);
    return w;
}

complex operator/(const complex& z, const int& a)
{
    complex w;
    w.re=(z.re/(double)a);
    w.im=(z.im/(double)a);
    return w;
}


/*============End of operator overloading=========================*/
#endif