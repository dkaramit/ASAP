// This is how you run RK. 
#include<iostream>
#include<fstream>
#include<cmath>
#include"RKF.hpp"



//---this is fake RK method. I use it to see if the program runs
struct RKfake{
    public:
        int s=4;
        int p=4;
        double c[4]={0,0.5,0.5,1.};
        double b[4]={1/6.,1/3.,1/3.,1/6.};
        double bstar[4]={1/6.+0.01,1/3.-0.01,1/3.-0.01,1/6.+0.01};
        double a[4][4];

        RKfake(){
            for (int i = 0; i <s ; i++) {for (int j = 0; j <s ; j++) {this->a[i][j]=0;}}
            this->a[1][0]=0.5;
            this->a[2][1]=0.5;
            this->a[3][2]=1.;
        };
        ~RKfake(){};


};

// this is how the diffeq should look like
#define n_eqs 3 //number of equations
typedef double Array[n_eqs];//define an array type of length n_eqs
//-------------------------------------------------------------------------//



class diffeq{
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
            
            lhs[0]=-20*y[0]*pow(t,3.);
            lhs[1]=5*y[0]*pow(t,2)+2*(-pow( y[1],2  )+pow( y[2],2 ) )*t;
            lhs[2]=15*y[0]*pow(t,2)+2*(pow( y[1],2  )-pow( y[2],2 ) )*t;

        }


};



int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=5;
    y0[1]=10;
    y0[2]=0;
    diffeq dydt;


    RKF<diffeq,Array,RKfake> System(dydt,y0);
    //System.max_N=10000;
    System.solve();

    #if 0
    for (int i = 0; i < System.max_N; i++)
    {
        std::cout<<System.steps[i]<<"\t"<< System.solution[0][i] << "\t"<< System.solution[1][i] << "\t"<< System.solution[2][i] <<"\n";
        if(System.steps[i]==1){break;}
    }
    #endif

    return 0;
 }