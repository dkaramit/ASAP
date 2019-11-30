#ifndef Ros_constructor
#define Ros_constructor
#include "Ros_class.hpp"



//The constructor. Remember that N has default value
template<class diffeq, int N_eqs, class RK_method, class jacobian>
Ros<diffeq, N_eqs , RK_method, jacobian>:: Ros(diffeq dydt, double (&init_cond)[N_eqs] , 
        double initial_step_size, double minimum_step_size, double maximum_step_size,int maximum_No_steps, 
        double absolute_tolerance,double relative_tolerance,double beta,double fac_max){
        // Initialize inputs
        this->dydt=dydt;
        this->Jac=jacobian(dydt);

        this->h0=initial_step_size;
        this->hmin=minimum_step_size;
        this->hmax=maximum_step_size;
        this->max_N=maximum_No_steps;
        this->abs_tol=absolute_tolerance;
        this->rel_tol=relative_tolerance;
        this->beta=beta;
        this->fac_max=fac_max;

        // ---------------------------------------------------------------------------------- //
        // later, I'll make steps and solution std::vector
        this->steps = new double[this->max_N];//make a list in which you'll put the steps 
        this->err = new double[this->max_N];//make a list in which you'll put the errors 

        //define solution[N_eqs][No_steps]
        this->solution = new double*[N_eqs];
        for(int i = 0; i < N_eqs ;++i) {
                this->solution[i] = new double[ this->max_N ];
                this->solution[i][0]=init_cond[i];//put the initial condition
            } 
        // ---------------------------------------------------------------------------------- //
        
        // define k[N_eqs][method.s]
        this->k=new double*[N_eqs];
        for(int i = 0; i < N_eqs ;++i) {
                this->k[i] = new double[ this->method.s];
                } 
        
        //temporary arrays for the ak, gk, Jk, bk, bstark
        this->ak=new double[N_eqs];
        this->gk=new double[N_eqs];
        this->Jk=new double[N_eqs];
        this->bk=new double[N_eqs];
        this->bstark=new double[N_eqs];
        this->ynext=new double[N_eqs];
        this->ynext_star=new double[N_eqs];


        // calculate sums over gamma for all stages 
        this->sum_gamma=new double[this->method.s];
        for(int stage = 0; stage < this->method.s; stage++){this->sum_gamma[stage]=0;
          for(int j =0 ; j<(this->method.s)-1; j++ ) {  this->sum_gamma[stage]+=this->method.g[stage][j]; }
          }



        //temporary arrays for the deltas
        this->abs_delta=new double[N_eqs];
        

        //initialize tn, current_step, and End
        this->tn=0;
        this->current_step=0;
        
        };

//The destructor
template<class diffeq, int N_eqs, class RK_method, class jacobian>
Ros<diffeq, N_eqs, RK_method, jacobian>::~Ros(){
        std::cout << "I'm done" << std::endl;
        delete[] this->steps;
        delete[] this->solution;
        delete[] this->k;
        delete[] this->ak;
        delete[] this->gk;
        delete[] this->Jk;
        delete[] this->bk;
        delete[] this->bstark;
        delete[] this->ynext_star;
        delete[] this->ynext;
    };



#endif