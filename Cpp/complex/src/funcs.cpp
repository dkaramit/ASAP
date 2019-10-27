#include "../include/complex-headers.h"


/*=============== Member functions===================================*/
double  complex::Re() const {return this->re;}  ;
double  complex::Im() const {return this->im;} ;
//int  complex::Re() const {return this->re;}  ;
//int  complex::Im() const {return this->im;} ;

void complex::SetRe(double Re){this->re=Re;};
void complex::SetIm(double Im){this->im=Im;};

void complex::SetRe(int Re){this->re=Re;};
void complex::SetIm(int Im){this->im=Im;};

void complex::SetRe_Im(double Re,double Im){this->re=Re;this->im=Im;};
void complex::SetRe_Im(double Re,int Im){this->re=Re;this->im=Im;};
void complex::SetRe_Im(int Re,double Im){this->re=Re;this->im=Im;};
void complex::SetRe_Im(int Re,int Im){this->re=Re;this->im=Im;};
/*============End member functions===================================*/
