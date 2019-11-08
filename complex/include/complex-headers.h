#ifndef COMPLEX_HEADERS_H_INCLUDED
#define COMPLEX_HEADERS_H_INCLUDED
#include <iostream>
#include <math.h>

class complex
{
    /*constructor-destructor*/
public:

//    complex(double , double );
//    complex(double , int );
//    complex(int , double );
//    complex(int , int );
/*=========================Constructors=======================*/
    complex(){};
    complex(double a, double b){this->re=a; this->im=b;};
    complex(int a, double b){this->re=a; this->im=b;};
    complex(double a, int b){this->re=a; this->im=b;};
    complex(int a, int b){this->re=a; this->im=b;};
/*=======================End of Constructors====================*/
    ~complex(){};

private :
    /*I have member functions to access them from main*/
    /*Notice that there are no integers in complex since the basic variables I use are double. I could use templates, but it becomes confusing for the user at some point.*/
    double re;
    double im;

/*----------------overloading operators--------------------------*/
public:
    complex friend operator+(const complex&, const complex&);
    complex friend operator+(const double&, const complex&);
    complex friend operator+(const int&, const complex&);
    complex friend operator+(const complex&,const int&);

    complex friend operator-(const complex&, const complex&);
    complex friend operator-(const double&, const complex&);
    complex friend operator-(const int&, const complex&);
    complex friend operator-(const complex&,const int&);

    complex friend operator-(const complex&);

    complex friend operator*(const complex&, const complex&);
    complex friend operator*(const double&, const complex&);
    complex friend operator*(const int&, const complex&);
    complex friend operator*(const complex&,const double&);
    complex friend operator*(const complex&,const int&);

    complex friend operator/(const complex&, const complex&);
    complex friend operator/(const double&, const complex&);
    complex friend operator/(const int&, const complex&);
    complex friend operator/(const complex&,const double&);
    complex friend operator/(const complex&,const int&);
    /*-----------------------------------------------------*/


/*--------------member functions-----------------------------------------------------*/
/*Re and Im return only double. So everything that uses them uses double numbers.*/

/*
 //this can be done, but you have to ask for Re<T>() instead of Re() and it will become confusing.
    template <class T>
    T  Re() const {return this->re;}  ;
    template <class T>
    T  Im() const {return this->im;} ;
*/
    double  Re() const;
    double  Im() const;
//    int  Re() const; //this cannot be overloaded, since we don't know what it will return;
//    int  Im() const; //this cannot be overloaded, since we don't know what it will return;

    void SetRe(double);
    void SetIm(double);
    void SetRe(int);
    void SetIm(int);

    void SetRe_Im(double ,double );
    void SetRe_Im(double ,int );
    void SetRe_Im(int ,double );
    void SetRe_Im(int ,int );
/*---------------------------------------------------------------------------*/






/*---------------------------cin and cout--------------------------------------*/
   friend std::ostream &operator<<( std::ostream &output,const complex &z )
      {
        if(z.Im()>0){
            output << z.Re() << " +i " << z.Im();
        }
        if(z.Im()<0){
            output << z.Re() << " -i " << -z.Im();
        }
        if(z.Im()==0){
            output << z.Re();
        }
        return output;
      }

      friend std::istream &operator>>( std::istream  &input,  complex &z )
      {
         double temp;
         std::cout<<"real part: ";
         input >> temp; z.SetRe(temp);
         std::cout<<"imaginary part: ";
         input >> temp ; z.SetIm(temp);

         return input;

       }
};

/*--------------------------------------------------------------------------*/







/*new functions*/
complex  conjugate(const complex&);


/*overloading functions*/
double  arg(const complex&);
complex  log(const complex&);
complex  tan(const complex&);

complex  exp(const complex&);
complex  pow(const double&, const complex&);
complex  pow(const complex&, const complex&);
complex  pow(const complex&, const double&);


complex  cos(const complex&);
complex  sin(const complex&);
double  cabs(const complex&);




#endif // HEADERS_H_INCLUDED
