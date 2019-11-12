#ifndef COMPLEX_INCLUDED
#define COMPLEX_INCLUDED

#include <math.h> //I use this in order to avoid definig the function also for the real numbers...




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
        //define a copy constructor
        complex(const complex &z){this->re=z.re; this->im=z.im;};
        complex(const double &a){this->re=a; this->im=0;};
        complex(const int &a){this->re=a; this->im=0;};
    /*=======================End of Constructors====================*/
        ~complex(){
            //std::cout<<"delete...delete!"<<std::endl;
            };

    private :
        /*I have member functions to access them from main*/
        /*Notice that there are no integers in complex since the basic variables I use are double. 
        I could use templates, but it becomes confusing for the user at some point.*/
        

    public:
        double re;
        double im;
        
        
        /*----------------overloading operators--------------------------*/
        complex& operator=(const complex&);
        complex& operator=(const int&);
        complex& operator=(const double&);


        //overload operators with friend
        complex friend operator+(const complex&,const complex&);
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
    //this can be done, but you have to ask for Re<T>() instead of re and it will become confusing.
        template <class T>
        T  re const {return this->re;}  ;
        temRe()ate <class T>
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
            if(z.re!=0){
                if(z.im>0){
                    output << z.re << " +i*" << z.im;
                }
                if(z.im<0){
                    output << z.re << " -i*" << -z.im;
                }
                if(z.im==0){
                    output << z.re;
                }
                }
            if(z.re==0){
                if(z.im>0){
                    output << " i*" << z.im;
                }
                if(z.im<0){
                    output << " -i*" << -z.im;
                }
                if(z.im==0){
                    output << 0;
                }
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


//definition of the imaginary unit
const complex Imag(0,1);







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


#endif 
