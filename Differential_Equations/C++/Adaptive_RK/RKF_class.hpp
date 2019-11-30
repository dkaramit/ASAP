#ifndef RKF_class
#define RKF_class

//This is a general implementation of explicit embedded RK solver of
// a system of differential equations in the interval [0,1].


template<class diffeq, int N_eqs, class RK_method> //Note that you can use template to pass the method
class RKF
{
    /*      */
private://There is no reason to make things private (if you break it it's not my fault)... 
    
public:
    //Inputs. The initial condition is given as a Array (the type is users choice as long as it can be called with [])
    diffeq dydt;
    RK_method method;
    double h0, hmin, hmax, abs_tol, rel_tol, beta, fac_max;
    int max_N;
    
    //things that we'll need
    int current_step;
    bool h_stop;//h_stop becomes true when suitable stepsize is found.    
    double tn;
    double *steps, *err;
    double** solution;


   
    //these are here to hold the k's, sum_i b_i*k_i, sum_i b_i^{\star}*k_i, and sum_j a_{ij}*k_j 
    double **k;
    double *ak, *bk,*bstark;
    double *abs_delta;

    double *ynext;//this is here to hold the prediction
    double *ynext_star;//this is here to hold the second prediction

    double yn[N_eqs];//thi i here to hold accepted ynext (redundant, I'll remove it later)
    double fyn[N_eqs];//this is here to get dydt in each step
    
    RKF(diffeq  dydt, double (&init_cond)[N_eqs], 
        double initial_step_size=1e-5, double minimum_step_size=1e-11, double maximum_step_size=1e-3,int maximum_No_steps=1000000, 
        double absolute_tolerance=1e-15,double relative_tolerance=1e-15,double beta=0.85,double fac_max=3);
    
    ~RKF();

    /*-------------------it would be nice to have a way to define these sums more generaly-----------------*/
    void next_step();

    void calc_k();

    void sum_ak(int stage); // calculate sum_j a_{ij}*k_j and passit to this->ak
    void sum_bk();// calculate sum_i b_i*k_i and passit to this->bk 
    void sum_bstark();// calculate sum_i b^{\star}_i*k_i and passit to this->bk
    

    
    void step_control();//adjust stepsize until error is acceptable
    void solve();


};



#endif