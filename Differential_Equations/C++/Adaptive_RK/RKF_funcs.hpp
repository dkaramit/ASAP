#ifndef RKF_funcs
#define RKF_funcs
#include "RKF_class.hpp"



//The constructor. Remember that N has default value
template<class diffeq, class Array, class RKF_method>
RKF<diffeq, Array, RKF_method>:: RKF(diffeq& dydt, Array& init_cond , 
        double initial_step_size, double minimum_step_size, double maximum_step_size,int maximum_No_steps, 
        double relative_tolerance, double absolute_tolerance,double beta,double _TINY){
        // Initialize inputs
        this->dydt=dydt;
        this->N_eqs= this->dydt.n;
        this->h0=initial_step_size;
        this->hmin=minimum_step_size;
        this->hmax=maximum_step_size;
        this->max_N=maximum_No_steps;
        this->rel_eps=relative_tolerance;
        this->abs_eps=absolute_tolerance;
        this->beta=beta;
        this->_TINY=_TINY;

        // ---------------------------------------------------------------------------------- //
        // later, I'll make steps and solution std::vector
        this->steps = new double[this->max_N];//make a list in which you'll put the steps 

        //define solution[N_eqs][No_steps]
        this->solution = new double*[this->N_eqs];
        for(int i = 0; i < this->N_eqs ;++i) {
                this->solution[i] = new double[ this->max_N ];
                this->solution[i][0]=init_cond[i];//put the initial condition
            } 
        // ---------------------------------------------------------------------------------- //
        
        // define k[N_eqs][method.s]
        this->k=new double*[this->N_eqs];
        for(int i = 0; i < this->N_eqs ;++i) {
                this->k[i] = new double[ this->method.s];
                } 
        
        //temporary arrays for the sums ak, bk, bstark
        this->ak=new double[this->N_eqs];
        this->bk=new double[this->N_eqs];
        this->bstark=new double[this->N_eqs];

        //temporary arrays for the deltas
        this->abs_delta=new double[this->N_eqs];
        this->rel_delta=new double[this->N_eqs];
        

        //initialize tn, current_step, and End
        this->tn=0;
        this->current_step=0;
        };

//The destructor
template<class diffeq, class Array, class RKF_method>
RKF<diffeq, Array, RKF_method>::~RKF(){
        std::cout << "I'm done" << std::endl;
        delete[] this->steps;
        delete[] this->solution;
        delete[] this->k;
        delete[] this->ak;
        delete[] this->bk;
        delete[] this->bstark;
    };

/*-----------------------Begin: sum_ak---------------------------------*/
template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::sum_ak(int stage){
    // this function stores sum_{j}^{stage-1}a_{stage,j}\vec{k}_j*h in ak, so we first need to make all elements zero, and then take the sum for each component
    // for (int eq = 0; eq <this->N_eqs ; eq++){this->ak[eq]=0.;  }//again redundant but it is more clear this way
    for (int eq = 0; eq <this->N_eqs ; eq++){
        this->ak[eq]=0.;  //you cloud initialize it here for example.
        for (int j = 0; j < stage; j++){ this->ak[eq]=this->ak[eq]+(this->method).a[stage][j]*this->k[eq][j]*this->h0;  }
    }
}
/*-----------------------End: sum_ak---------------------------------*/

/*-----------------------Begin: sum_bk---------------------------------*/
template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::sum_bk(){
    // this function stores sum_{i}^{s}b_{i}\vec{k}_i*h in bk and sum_{i}^{s}b_{i}^{\star}\vec{k}_i*h in bstark  
    for (int eq = 0; eq <this->N_eqs ; eq++){
        this->bk[eq]=0.;
        this->bstark[eq]=0.; 
        
        for (int i = 0; i < (this->method).s; i++){ 
            this->bk[eq]=this->bk[eq]+(this->method).b[i]*this->k[eq][i]*this->h0;  
            this->bstark[eq]=this->bstark[eq]+(this->method).bstar[i]*this->k[eq][i]*this->h0;  
            }
    }

}
/*-----------------------End: sum_bk---------------------------------*/

/*-----------------------Begin: calc_k---------------------------------*/
template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::calc_k(){
            // calculate \vec{k}_1:
            // first calculate current value \vec{y} and fill yn
            for (int eq = 0; eq < this->N_eqs ; eq++){this->yn[eq]=this->solution[eq][this->current_step-1];}
            // then calculate f(n_n,t_n)
            this->dydt(this->fyn, this-> yn,this->tn );
            // with these we can calculate and fill \vec{k}_1
            for( int eq = 0; eq < this->N_eqs; eq++ ){ this->k[eq][0]=this->fyn[eq];  }


            // claculate the rest of \vec{k}_i
            for (int stage = 0; stage < (this->method).s; stage++){
                // first we need the sum_{j}^{stage-1}a_{stage,j}\vec{k}_j *h
                this->sum_ak(stage);
                // then we need \vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j} (so fill yn with this)
                for (int eq = 0; eq < this->N_eqs ; eq++){this->yn[eq]=this->solution[eq][this->current_step-1]+ak[eq];}
                // then calculate f(\vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j}, tn + c[stage]*h )
                this->dydt(this->fyn, this-> yn,(this->tn)+(this->h0)*(this->method).c[stage] );
                // now we can fill \vec{k}[stage]
                for( int eq = 0; eq < this->N_eqs; eq++ ){ this->k[eq][stage]=this->fyn[eq]; }
            }
}
/*-----------------------End: calc_k---------------------------------*/

/*----------------------------------------------define a Print to have easy acces to some info--------------------------------------------*/
static int x=0;
#define Print(m1,m2,m3,m4) std::cout<<x++<<"   "<<m1<<"   "<<m2<<"   "<<m3<<"   "<<m4<<std::endl; std::cin.get()
/*----------------------------------------------------------------------------------------------------------------------------------------*/



/*-----------------------Begin: step_control---------------------------------*/
template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::step_control(){
    
    h_stop=true;

}
/*-----------------------End: step_control---------------------------------*/

/*---------------------------------------------------Begin: Get next step-------------------------------------------------------------------------------*/
template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::next_step(){
        //set h_stop=false, to start looking for stepsize
        this->h_stop=false;
        //increase current_step
        (this->current_step)++;
        

        //calculate ynext and ynext_star until h_stop=true 
        while (not this->h_stop)
        {
            // calculate \vec{k}:
            this->calc_k();
        
            // now we can calulate \vec{y}_{n+1}
            // for this we need sum_{i}^{s}b_{i}\vec{k}_i *h. That is, call sum_bk
            this->sum_bk();
            // having bk, we now have \vec{y}_{n+1} \vec{y}^{\star}_{n+1}. 
            for (int eq = 0; eq < this->N_eqs; eq++)
            {   
                this->ynext[eq] =  this->yn[eq] + bk[eq];
                this->ynext_star[eq] =  this->yn[eq] + bstark[eq];       
            
                // calculate the erros

                this->abs_delta[eq]=(this->ynext[eq])-(this->ynext_star[eq]);
                                    
                if( fabs(this->ynext[eq]) > this->_TINY )
                {
                    this->rel_delta[eq]=this->abs_delta[eq]/this->ynext[eq];
                } else{
                    this->rel_delta[eq]=this->abs_delta[eq];
                }

                // call step_control to see if the error is acceptable
                this->step_control();
                
            }

        }
            
        for (int eq = 0; eq < this->N_eqs; eq++)
        {
            this->yn[eq]=this->ynext[eq];
            this->solution[eq][this->current_step]=this->ynext[eq];

        }
    
        this->tn= this->tn + this->h0;
        
        
        this->steps[this->current_step] = this->tn;

        // std::cout<<this->current_step<<std::endl;
}
/*---------------------------------------------------End: Get next step-------------------------------------------------------------------------------*/



/*---------------------------------------------------Begin: solve-------------------------------------------------------------------------------*/

template<class diffeq, class Array, class RKF_method>
void RKF<diffeq, Array, RKF_method>::solve(){

        while (true )
        {
            // std::cout<< current_step <<"  "<< tn <<"\n";

            if( this->tn>=1.  or this->current_step == this->max_N  ) {break ;}
            this->next_step();

            
        }

    } 
/*---------------------------------------------------End: solve-------------------------------------------------------------------------------*/




#endif