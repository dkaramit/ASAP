// This is how you run Euler. You need to include the <array> because 
// it is a very nice way to declare and pass lists in functions.

#include <iostream>
#include <fstream>
#include"Euler.hpp"


// this is how the diffeq should look like
#define n_eqs 2 //number of equations



//-------------------------------typedef------------------------------------//
//To define the various Arrays you may need, you can use    std::array as:

// #define use_std_array  //uncomment to use std::array
#ifdef use_std_array
#include <array>
typedef std::array<double, n_eqs> Array; //define an array type of length n_eqs
#endif


#ifndef use_std_array
//or define it like this:
typedef double Array[n_eqs];//define an array type of length n_eqs
#endif
//-------------------------------------------------------------------------//



 class diffeq
{
    public:
        int n;//number of equations
        diffeq(){
            this->n=n_eqs;
        };
        ~diffeq(){};
        
        
        //Overloading the braket operator.
        void operator()( Array &lhs, Array &y  , double t )
        {
            //lhs is an array that gets the return value (the left hand side of the equation)
            //y is an array with values of y
            //t is the value of the variable t
            
            lhs[0]=(-y[0]*y[0]+y[1]*y[1])*2*pow(t,0.1);
            lhs[1]=(y[0]*y[0]-y[1]*y[1])*2*pow(t,0.1);

        }


};



int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=1.2;
    y0[1]=0.6;
    diffeq dydt;

    //dydt(lhs,y0,5.2);
    //std::cout << lhs[1] << std::endl;
    int N=10000;
    Euler<diffeq,Array> System(dydt,y0,N);
    System.solve();

    std::ofstream f1,f2,t;
    f1.open ("data/y1.dat");
    f2.open ("data/y2.dat");
    t.open ("data/t.dat");
   
    for (int i = 0; i < N; i++)
    {
        f1 << System.solution[0][i] ;
        f1 << "\n";
        f2 << System.solution[1][i] ;
        f2 << "\n";
        t << System.steps[i] ;
        t << "\n";
        std::cout<<System.steps[i]<<"\t"<< System.solution[0][i] << "\t"<< System.solution[1][i] <<"\n";
         
            }
    

    return 0;
 }