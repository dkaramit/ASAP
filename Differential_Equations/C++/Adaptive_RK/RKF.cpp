// This is how you run RK. 
#include<iostream>
#include<fstream>
#include<cmath>
#include"RKF.hpp"


class DormandPrince{
    public:
        int s=7;
        int p=4;
        double c[7]={0,1/5.,3/10.,4/5.,8/9.,1.,1.};
        double b[7]={5179/57600.,0,7571/16695.,393/640.,-92097/339200.,187/2100.,1/40.};
        double bstar[7]={ 35/384.,0.,500/1113.,125/192.,-2187/6784.,11/84.,0 };
        double a[7][7];

        ~DormandPrince(){};
        DormandPrince(){
            
            for (int i = 0; i < s; i++){ for (int j = 0; j < s; j++){a[i][j]=0;} }
            
            
            
            
            a[1][0]=1/5.;
            
            a[2][0]=3/40.;
            a[2][1]=9/40.;
            
            a[3][0]=44/45.;
            a[3][1]=-56/15.;
            a[3][2]=32/9.;
            
            a[4][0]=19372/6561.;
            a[4][1]=-25360/2187.;
            a[4][2]=64448/6561.;
            a[4][3]=-212/729. ;       
            

            a[5][0]=9017/3168.;
            a[5][1]=-355/33.;
            a[5][2]=46732/5247.;
            a[5][3]=49/176.;
            a[5][4]=-5103/18656.;
            
            
            a[6][0]=35/384.;
            a[6][1]=0;
            a[6][2]=500/1113.;
            a[6][3]=125/192.;
            a[6][4]=-2187/6784.;
            a[6][5]=11/84.;
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
#define minimum_step_size 1e-11 
#define maximum_step_size 1e-2
#define maximum_No_steps 1000000
#define absolute_tolerance 1e-15
#define relative_tolerance 1e-15
#define beta 0.85
#define fac_max 3

int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=5;
    y0[1]=10;
    y0[2]=0;
    diffeq dydt=sys;


    RKF<diffeq,n_eqs,DormandPrince> System(dydt,y0, 
     initial_step_size,  minimum_step_size,  maximum_step_size, maximum_No_steps, 
     absolute_tolerance, relative_tolerance, beta, fac_max);
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
    f1.open ("./test/y1.dat");
    f2.open ("./test/y2.dat");
    f3.open ("./test/y3.dat");
    t.open ("./test/t.dat");
    err.open ("./test/err.dat");
    

   
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