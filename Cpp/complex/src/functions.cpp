#include "../include/complex-headers.h"


/*================= new functions====================================*/
complex conjugate(const complex& z)
{
    complex zc;
    zc.SetRe(z.Re());
    zc.SetIm(-z.Im());
    return zc;
}
/*================= End new functions====================================*/


/*====================function overloading======================*/
complex log(const  complex& z)
{
    complex w;
    w.SetRe_Im(log(cabs(z)),arg(z)) ;
    return w;
}

complex exp(const  complex& z)
{
    complex w;
    w.SetRe_Im(exp(z.Re())*cos(z.Im()) , exp(z.Re())*sin(z.Im())) ;
    return w;
}

complex cos(const complex& z)
{
    complex w1,w2,w3;
    w2.SetIm(0);
    w2.SetRe(2);
    w3.SetRe(0);
    w3.SetIm(1);
    w1=(exp(w3*z)+exp(-w3*z))/w2;
    return w1;
}

complex sin(const complex& z)
{
    complex w1,w2,w3;
    w2.SetRe(0);
    w2.SetIm(2);
    w3.SetRe(0);
    w3.SetIm(1);
    w1=(exp(w3*z)-exp(-w3*z))/w2;
    return w1;
}

complex tan( const complex& z)
{
    complex w;
    w=sin(z)/cos(z);
    return w;
}

double arg(const complex& z)
{
        return atan2(z.Im(),z.Re());
}

complex pow(const complex& z1,const  complex& z2)
{
    complex w,w2,w3;
    w=exp(z2*log(z1));
    return w;
}

complex pow(const double& a,const  complex& z)
{
    complex w,w2,w3;
    w=exp(z*log(a));
    return w;
}

complex pow(const complex& z, const double& a)
{
    complex w,w2,w3;
    w3.SetRe(0);
    w3.SetIm(1);
    w2=exp(a*w3*arg(z));
    w.SetRe(pow(cabs(z),a)*w2.Re());
    w.SetIm(pow(cabs(z),a)*w2.Im());
    return w;
}

double cabs(const complex& z)
{
    return sqrt(z.Im()*z.Im() + z.Re()*z.Re());
}/*============ End function overloading==================*/
