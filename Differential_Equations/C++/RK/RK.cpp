#include<iostream>
#include<cmath>
#include"RK.hpp"


//define the method
struct RK4{
    public:
        int s=4;
        double c[4]={0,0.5,0.5,1.};
        double b[4]={1/6.,1/3.,1/3.,1/6.};
        double a[4][4];

        RK4(){
            for (int i = 0; i <s ; i++) {for (int j = 0; j <s ; j++) {this->a[i][j]=0;}}
            this->a[1][0]=0.5;
            this->a[2][1]=0.5;
            this->a[3][2]=1.;
        };
        ~RK4(){};


};

// this is how the diffeq should look like
#define n_eqs 2 //number of equations
typedef double Array[n_eqs];//define an array type of length n_eqs
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
    RK<diffeq,Array,RK4> System(dydt,y0,N);
    

    return 0;
 }