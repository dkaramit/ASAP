// This is how you run RK. 
#include<iostream>
#include<fstream>
#include<cmath>
#include"RK.hpp"



//You need to define a method. When I package everything, I'll include a few methods, but the idea is for the user to define their own.
//define the method (Ther is waste of memory here, but it is convinient to do it this way)
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
#define n_eqs 3 //number of equations
typedef double Array[n_eqs];//define an array type of length n_eqs
typedef void (*diffeq)(Array &lhs, Array &y  , double t );
//-------------------------------------------------------------------------//

void sys( Array &lhs, Array &y  , double t )
        {
            //lhs is an array that gets the return value (the left hand side of the equation)
            //y is an array with values of y
            //t is the value of the variable t
            
            lhs[0]=-20*y[0]*pow(t,3.);
            lhs[1]=5*y[0]*pow(t,2)+2*(-pow( y[1],2  )+pow( y[2],2 ) )*t;
            lhs[2]=15*y[0]*pow(t,2)+2*(pow( y[1],2  )-pow( y[2],2 ) )*t;

        };




int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=5;
    y0[1]=10;
    y0[2]=0;
    diffeq dydt=sys;

    //dydt(lhs,y0,5.2);
    //std::cout << lhs[1] << std::endl;
    //definition with N
    int N=5000;
    RK<diffeq,n_eqs,RK4> System(sys,y0,N);
    System.solve();

    std::ofstream f1,f2,f3,t;
    f1.open ("./test/y1.dat");
    f2.open ("./test/y2.dat");
    f3.open ("./test/y3.dat");
    t.open ("./test/t.dat");
   
    for (int i = 0; i < N; i++)
    {
        f1 << System.solution[0][i] ;
        f1 << "\n";
        f2 << System.solution[1][i] ;
        f2 << "\n";
        f3 << System.solution[2][i] ;
        f3 << "\n";
        t << System.steps[i] ;
        t << "\n";
        // std::cout<<System.steps[i]<<"\t"<< System.solution[0][i] << "\t"<< System.solution[1][i] << "\t"<< System.solution[2][i] <<"\n";
    }

    f1.close();
    f2.close();
    f3.close();
    t.close();


    return 0;
 }