#include "../include/complex-headers.h"


/*===================Operator overloading============================*/

/*==================addition=========================================*/
complex operator+(const complex& z1, const complex& z2)
{
    complex w;
    w.SetRe(z1.Re()+z2.Re());
    w.SetIm(z1.Im()+z2.Im());
    return w;
}

complex operator+(const double& a, const complex& z)
{
    complex w;
    w.SetRe(a+z.Re());
    w.SetIm(z.Im());
    return w;
}

complex operator+(const int& a, const complex& z)
{
    complex w;
    w.SetRe(a+z.Re());
    w.SetIm(z.Im());
    return w;
}

complex operator+(const complex& z, const double& a)
{
    complex w;
    w.SetRe(a+z.Re());
    w.SetIm(z.Im());
    return w;
}

complex operator+(const complex& z, const int& a)
{
    complex w;
    w.SetRe(a+z.Re());
    w.SetIm(z.Im());
    return w;
}

/*==================substraction=========================================*/
complex operator-(const complex& z1, const complex& z2)
{
    complex w;
    w.SetRe(z1.Re()-z2.Re());
    w.SetIm(z1.Im()-z2.Im());
    return w;
}

complex operator-(const double& a, const complex& z)
{
    complex w;
    w.SetRe(a-z.Re());
    w.SetIm(-z.Im());
    return w;
}

complex operator-(const int& a, const complex& z)
{
complex w;
    w.SetRe(a-z.Re());
    w.SetIm(-z.Im());
    return w;
}

complex operator-(const complex& z, const double& a)
{
    complex w;
    w.SetRe(z.Re()-a);
    w.SetIm(z.Im());
    return w;
}

complex operator-(const complex& z, const int& a)
{
    complex w;
    w.SetRe(z.Re()-a);
    w.SetIm(z.Im());
    return w;
}

complex operator-(const complex& z)
{
    complex w;
    w.SetRe(-z.Re());
    w.SetIm(-z.Im());
    return w;
}

/*==============multiplication===========================*/

complex operator*(const complex& z1, const complex& z2)
{
    complex w;
    w.SetRe(z1.Re()*z2.Re() -z1.Im()*z2.Im()) ;
    w.SetIm(z1.re*z2.Im()+z1.Im()*z2.Re());
    return w;
}

complex operator*(const double& a, const complex& z)
{
    complex w;
    w.SetRe(a*z.Re());
    w.SetIm(a*z.Im());
    return w;
}

complex operator*(const int& a, const complex& z)
{
    complex w;
    w.SetRe(a*z.Re());
    w.SetIm(a*z.Im());
    return w;
}

complex operator*(const complex& z, const double& a)
{
    complex w;
    w.SetRe(a*z.Re());
    w.SetIm(a*z.Im());
    return w;
}

complex operator*(const complex& z, const int& a)
{
    complex w;
    w.SetRe(a*z.Re());
    w.SetIm(a*z.Im());
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
    w.SetRe(a/(pow(cabs(z),2))*conjugate(z).Re());
    w.SetIm(a/(pow(cabs(z),2))*conjugate(z).Im());
    return w;
}

complex operator/(const int& a, const complex& z)
{
    complex w;
    w.SetRe(a/(pow(cabs(z),2.))*conjugate(z).Re());
    w.SetIm(a/(pow(cabs(z),2.))*conjugate(z).Im());
    return w;
}

complex operator/(const complex& z, const double& a)
{
    complex w;
    w.SetRe(z.Re()/a);
    w.SetIm(z.Im()/a);
    return w;
}

complex operator/(const complex& z, const int& a)
{
    complex w;
    w.SetRe(z.Re()/(double)a);
    w.SetIm(z.Im()/(double)a);
    return w;
}

/*============End of operator overloading=========================*/
