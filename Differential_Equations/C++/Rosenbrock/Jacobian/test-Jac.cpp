#include<iostream>
#include"Jacobian.hpp"

// #define _class //run it with class with overloaded operator()
#define _function //run it with function pointer




// this is how the diffeq should look like
#define n_eqs 2 //number of equations
typedef double Array[n_eqs];//define an array type of length n_eqs
//-------------------------------------------------------------------------//



#ifdef _function
typedef void (*diffeq)(Array &lhs, Array &y  , double t); // define function pointer
void sys(Array &lhs, Array &y  , double t)
{

    lhs[0]=y[1]*y[0]*t;
    lhs[1]=y[0]*y[1]+t;

}
#endif


#ifdef _class
class Cdiffeq{
    public:
    Cdiffeq(){};
    ~Cdiffeq(){};
    void operator()(Array &lhs, Array &y  , double t)
    {
        lhs[0]=y[1]*y[0]*t;
        lhs[1]=y[0]*y[1]+t;
    }


};
#endif


using std::cout;
using std::endl;


int main(){
    #ifdef _class
        Cdiffeq dydt;
        Jacobian<Cdiffeq,n_eqs> jac(dydt);
    #endif

    #ifdef _function
        Jacobian<diffeq,n_eqs> jac(sys);
    #endif

    Array dfdt;
    // Matrix J={{0,0},{0,0}};
    double J[n_eqs][n_eqs];

    Array y={1,4.2};
    double t=0.3;

    jac(J,dfdt,y,t);

    cout<<"dfdt=[";
    for(int i=0; i<n_eqs ; i++){  cout<<dfdt[i]; if(i!=n_eqs-1){cout<<",";}   }
    cout<<"]"<<endl;


    cout<<"J=["<<endl;
    
    for (int i = 0; i < n_eqs; i++){
         cout<<"[";
        for (int j = 0; j < n_eqs; j++) {cout<<J[i][j]; if(j!=n_eqs-1){cout<<",";} }
          cout<<"]";if(i!=n_eqs-1){cout<<",";}cout<<endl;
        
        
    }  
    cout<<"]"<<endl;
    





    return 0;
}