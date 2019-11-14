#ifndef RK_funcs
#define RK_funcs
#include "RK_class.hpp"



//The constructor. Remember that N has default value
template<class diffeq, class Array, class RK_method>
RK<diffeq, Array, RK_method>:: RK(diffeq & dydt, Array  & init_cond , int N){
        this->step_size= 1./(N-1.);

        this->dydt=dydt;
        this->No_steps=N;
        this->number_of_eqs= this->dydt.n;

        this->steps = new double[this->No_steps];//make a list in which you'll put the steps 

        //define solution[number_of_eqs][No_steps]
        this->solution = new double*[this->number_of_eqs];
        for(int i = 0; i < this->number_of_eqs ;++i) {
                this->solution[i] = new double[ this->No_steps];
                this->solution[i][0]=init_cond[i];//put the initial condition
            } 
        
        
        this->k=new double*[this->number_of_eqs];
        for(int i = 0; i < this->number_of_eqs ;++i) {
                this->k[i] = new double[ this->method.s];
                } 
        
        this->ak=new double[this->number_of_eqs];
        this->bk=new double[this->number_of_eqs];

        //initialize tn, current_step, and End

        this->tn=0;
        this->current_step=0;
        this->End=false;
        };

//The destructor
template<class diffeq, class Array, class RK_method>
RK<diffeq, Array, RK_method>::~RK(){
        // std::cout << "I'm done" << std::endl;
        delete[] this->steps;
        delete[] this->solution;
        delete[] this->k;
        delete[] this->ak;
        delete[] this->bk;
    };

/*-----------------------Begin: sum_ak---------------------------------*/
template<class diffeq, class Array, class RK_method>
void RK<diffeq, Array, RK_method>::sum_ak(int stage){
    // this function stores sum_{j}^{stage-1}a_{stage,j}\vec{k}_j*h in ak, so we first need to make all elements zero, and then take the sum for each component
    // for (int eq = 0; eq <this->number_of_eqs ; eq++){this->ak[eq]=0.;  }//again redundant but it is more clear this way
    for (int eq = 0; eq <this->number_of_eqs ; eq++){
        this->ak[eq]=0.;  //you cloud initialize it here for example.
        for (int j = 0; j < stage; j++){ this->ak[eq]=this->ak[eq]+(this->method).a[stage][j]*this->k[eq][j]*this->step_size;  }
    }
}
/*-----------------------End: sum_ak---------------------------------*/

/*-----------------------Begin: sum_bk---------------------------------*/
template<class diffeq, class Array, class RK_method>
void RK<diffeq, Array, RK_method>::sum_bk(){
    // this function stores sum_{i}^{s}b_{i}\vec{k}_i*h in bk, so we first need to make all elements zero, and then take the sum for each component
    // for (int eq = 0; eq <this->number_of_eqs ; eq++){this->bk[eq]=0.;  }//again redundant but it is more clear this way
    for (int eq = 0; eq <this->number_of_eqs ; eq++){
        this->bk[eq]=0.;  //you cloud initialize it here for example.
        for (int i = 0; i < (this->method).s; i++){ this->bk[eq]=this->bk[eq]+(this->method).b[i]*this->k[eq][i]*this->step_size;  }
    }

}
/*-----------------------End: sum_bk---------------------------------*/



/*---------------------------------------------------Begin: Get next step-------------------------------------------------------------------------------*/
template<class diffeq, class Array, class RK_method>
void RK<diffeq, Array, RK_method>::next_step(){
        if (this->current_step>= this->No_steps -1 )
        {
            this->End=true;
        } else{
            (this->current_step)++;//increase current_step
            // std::cout<<this->current_step*this->step_size<<std::endl;
 
            // calculate \vec{k}_1:
            // first calculate current value \vec{y} and fill yn
            for (int eq = 0; eq < this->number_of_eqs ; eq++){this->yn[eq]=this->solution[eq][this->current_step-1];}
            // then calculate f(n_n,t_n)
            this->dydt(this->fyn, this-> yn,this->tn );
            // with these we can calculate and fill \vec{k}_1
            for( int eq = 0; eq < this->number_of_eqs; eq++ ){ this->k[eq][0]=this->fyn[eq];  }


            // claculate the rest of \vec{k}_i
            for (int stage = 0; stage < (this->method).s; stage++){
                // first we need the sum_{j}^{stage-1}a_{stage,j}\vec{k}_j *h
                this->sum_ak(stage);
                // then we need \vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j} (so fill yn with this)
                for (int eq = 0; eq < this->number_of_eqs ; eq++){this->yn[eq]=this->solution[eq][this->current_step-1]+ak[eq];}
                // then calculate f(\vec{y}+sum_{j}^{stage-1}a_{stage,j}\vec{j}, tn + c[stage]*h )
                this->dydt(this->fyn, this-> yn,(this->tn)+(this->step_size)*(this->method).c[stage] );
                // now we can fill \vec{k}[stage]
                for( int eq = 0; eq < this->number_of_eqs; eq++ ){ this->k[eq][stage]=this->fyn[eq]; }
            }

            // now we can calulate \vec{y}_{n+1}
            // for this we need sum_{i}^{s}b_{i}\vec{k}_i *h. That is, call sum_bk
            this->sum_bk();
            // having bk, we naow have \vec{y}_{n+1}. 
            for (int eq = 0; eq < this->number_of_eqs; eq++){   
                this->solution[eq][this->current_step] =  this->solution[eq][this->current_step-1] + bk[eq];      
            }

            this->tn=this->current_step*this->step_size;
            this->steps[this->current_step]=this->tn;

        }
        

    }
/*---------------------------------------------------End: Get next step-------------------------------------------------------------------------------*/



/*---------------------------------------------------Begin: solve-------------------------------------------------------------------------------*/

template<class diffeq, class Array, class RK_method>
void RK<diffeq, Array, RK_method>::solve(){

        while (not this->End)
        {

            this->next_step();
        }

    } 
/*---------------------------------------------------End: solve-------------------------------------------------------------------------------*/




#endif