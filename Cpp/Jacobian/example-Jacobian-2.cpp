//Compile with:
// g++ example-Jacobian-2.cpp

#include <iostream>
#include <array>
//#include <boost/numeric/ublas/io.hpp>//Overloading of cout for matrix
#include "Jacobian.hpp"


#define Ns 3//Number of equations.
#define fori(i) for (int i = 0; i < Ns; ++i)//define a simple for loop like this

using namespace std;

typedef array<double, Ns> position;
typedef array<double, Ns> lhs;
typedef array<double, Ns> fs;


//This class defines the system of differential equations as an object.
//In order to use it as a function, we can overload the braket operator.
class Sys
{
    public:

        Sys()
        {
             // cout << "system start without a."<<"\n";
        }

        ~Sys()
        {
            // cout << "system finished" << "\n";
        }


        double a;
        Sys(double a_)
        {
            this->a=a_;
            // cout << "system start with a="<<a_ << "\n";
        }


        //Overloading the braket operator.
        void operator()( const position &x_ , lhs &dxdt_ , double t )
        {
            dxdt_[0]=this->a*sin(x_[0])+exp(x_[2])*t;
            dxdt_[1]=x_[0]*x_[1]*t;
            dxdt_[2]=x_[0]*x_[0]*x_[2]*t*t;

        }


};

//Call this to print the exact derivetives
void Exactdfdt(position &x, double t)
{
    fs Edfdt;
    Edfdt[0]=exp(x[2]);
    Edfdt[1]=x[0]*x[1];
    Edfdt[2]=2*x[0]*x[0]*x[2]*t;
    fori(i){cout <<"Edf"<<i<<"dt= " <<Edfdt[i] << "\n";}

}
//Call this to print the exact Jacobian
void ExactJac(position &x, double t,double a)
{
    Matrix EJ(Ns,Ns);
    EJ(0,0)=a*cos(x[0]);
    EJ(0,1)=0;
    EJ(0,2)=exp(x[2])*t;
    EJ(1,0)=x[1]*t;
    EJ(1,1)=x[0]*t;
    EJ(1,2)=0;
    EJ(2,0)=2*x[0]*x[2]*t*t;
    EJ(2,1)=0;
    EJ(2,2)=x[0]*x[0]*t*t;

    cout << "EJ=" ;
    fori(i){if(i!=0){cout << "  {";} if(i==0){cout <<"{";} fori(j) {  cout <<EJ(i,j); if(j<Ns-1){cout<<"\t";}  }cout << "}\n";}

}


int main()
{


    Sys eqs(2.);//define the system (with some vale for a)
    position x={3.,-0.2,0.1};//define a position (these will represent the initial conditions)

    lhs dxdt;//The array dxdt is used to comunicate with sys (they are passed by reference, and the are constantly being modified)

    double t=2.;

    //Example:
    //eqs(x,dxdt,t);
    //Calling sys like this, calculates dxdt[0] and dxdt[1] for x={3.,-0.2} and t as


    Jacobian<Sys> jac(eqs,1e-6,Ns);//declare the Jacobian (with h=10^-6 and dim=Ns)
    //jac.sys(x,dxdt,0.);//You can also call sys like this. It does the same thing as sys!

    Matrix J(Ns,Ns);
    fs dfdt;
    jac(x,J,t,dfdt);

    // I need to work on my formating (i.e. use printf)
    cout << "J=" ;
    fori(i){if(i!=0){cout << "  {";} if(i==0){cout <<"{";} fori(j) {  cout <<J(i,j); if(j<Ns-1){cout<<"\t";}  }cout << "}\n";  }
    //Check against the exact Jacobian
    ExactJac(x,t,eqs.a);




    cout << "\n";
    fori(i){cout <<"df"<<i<<"dt= " <<dfdt[i] << "\n";}
    //Check against the exact derivatives
    Exactdfdt(x,t);


    return 0;
}
