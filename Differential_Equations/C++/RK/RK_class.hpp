#ifndef RK_class
#define RK_class

//This is a general implementation of explicit RK solver of
// a system of differential equations in the interval [0,1].


template<class diffeq, int number_of_eqs, class RK_method> //Note that you can use template to pass the method
class RK
{
    /*
    This is a class that defines an explicit Runge-Kutta solver for system of differential equations.
    The idea is to have a simple code that one can expand and experiment with.
    On how to use it, read the comments within the .hpp files, and the RK.cpp.

    On how the RK solver works, have a look at the jupyter notebook in the python directory. 
    */
private://There is no reason to make things private (if you break it it's not my fault)... 
    
public:
    int No_steps, current_step;
    bool End;
    double step_size,tn;
    diffeq dydt;
    double* steps;

    double** solution;

    RK_method method;

   
    //these are here to hold the k's, sum_i b_i*k_i and sum_j a_{ij}*k_j 
    double** k;
    double* ak;
    double* bk;

    double yn[number_of_eqs];//this is here to hold the current steps
    double fyn[number_of_eqs];//this is here to get dydt in each step
    
    RK(diffeq dydt , double  (&init)[number_of_eqs]  , int N=10000);
    ~RK();

    /*-------------------it would be nice to have a way to define these sums more generaly-----------------*/
    void sum_bk();// calculate sum_i b_i*k_i and passit to this->bk 

    void sum_ak(int stage); // calculate sum_j a_{ij}*k_j and passit to this->ak
    
    void next_step();
    void solve();


};



#endif