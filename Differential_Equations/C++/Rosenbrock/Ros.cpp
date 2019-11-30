// This is how you run RK. 
#include<iostream>
#include<fstream>
#include<cmath>
#include"Ros.hpp"
#include "Jacobian/Jacobian.hpp"//this is treated as user input, since one may have an analytic form.


class ROS3w{
    public:
        const int s=3;
        const int p=2;
        double c[3]={0,2/3.,4/3.};
        double b[3]={0.25,0.25,0.5 };
        double bstar[3]={ 0.746704703274 , 0.1144064078371 , 0.1388888888888 };
        double gamma=0.4358665215084;
        
        double a[3][3] , g[3][3];

        ~ROS3w(){};
        ROS3w(){
            
            for (int i = 0; i < s; i++){ for (int j = 0; j < s; j++){a[i][j]=0; g[i][j]=0; } }
            
            a[1][0]=2/3.;
            a[2][0]=2/3.;
            a[2][1]=2/3.;
            
            g[1][0]=0.3635068368900;
            g[2][0]=-0.8996866791992;
            g[2][1]=-0.1537997822626;
        };
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

#define initial_step_size 1e-4 
#define minimum_step_size 1e-7
#define maximum_step_size 1e-2
#define maximum_No_steps 1000000
#define absolute_tolerance 1e-7
#define relative_tolerance 1e-7
#define beta 0.85
#define fac_max 3



int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=5;
    y0[1]=10;
    y0[2]=0;
    Jacobian<diffeq,n_eqs> jac(sys);

    // this is not looing good.. Just pass the number of equations as argument to get rid of Array and Matrix...
    Ros<diffeq,n_eqs, ROS3w,Jacobian<diffeq,n_eqs> > System(sys,y0, 
     initial_step_size,  minimum_step_size,  maximum_step_size, maximum_No_steps, 
     absolute_tolerance, relative_tolerance, beta, fac_max);
    // System.next_step();
    System.solve();
    // 
    

    #if 0
    for (int i = 0; i < System.max_N; i++)
    {
       System.next_step();

       std::cout<<System.tn<<"\n";

       if(System.tn==1){break;} 
    }
    #endif

    
    #if 0
    for (int i = 0; i < System.current_step; i++)
    {

        std::cout<<i<<"  "<<System.steps[i]<<"\t\t\t\t";
        for(int eq =0; eq<n_eqs; eq++){ std::cout<< System.solution[eq][i]<< "\t\t\t"; }
        std::cout<<"\n";
        
        if(System.steps[i]==1){break;}
    }
    #endif


    std::ofstream f1,f2,f3,t,err;
    f1.open ("./0-test/y1.dat");
    f2.open ("./0-test/y2.dat");
    f3.open ("./0-test/y3.dat");
    t.open ("./0-test/t.dat");
    err.open ("./0-test/err.dat");
    

   
    for (int i = 0; i < System.current_step; i++)
    {
        f1 << System.solution[0][i] ;
        f1 << "\n";
        f2 << System.solution[1][i] ;
        f2 << "\n";
        f3 << System.solution[2][i] ;
        f3 << "\n";
        t << System.steps[i] ;
        t << "\n";
        err << System.err[i] ;
        err << "\n";
        
        // std::cout<<System.steps[i]<<"\t"<< System.solution[0][i] << "\t"<< System.solution[1][i] << "\t"<< System.solution[2][i] <<"\n";
        if(System.steps[i]==1){break;}
    }

    f1.close();
    f2.close();
    f3.close();
    t.close();

    // std::cout<<System.current_step<<std::endl;

    return 0;
 }