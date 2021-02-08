#ifndef FFANN_SGD
#define FFANN_SGD
#include<random>

#include"FFANN.hpp"

template<class LD, class Func,  unsigned int total_layers>
template<class Strategy>
void FFANN_Namespace::SGD(Strategy *strategy, 
                        const std::vector<std::vector<LD>> *data_in, const std::vector<std::vector<LD>> *data_out, 
                        LD abs_tol, LD rel_tol, un_int step_break, un_int max_step) {
   /*
   You have to pass the data (data_in are the inputs and data_out their corresponding outputs), and define the loss (and its derivative).

    strategy: the strategy that will be used to update the parameters

    data_in,data_out: the inputs and the corresponding outputs to be used for training

    abs_tol,rel_tol: determine the scale of a parameter 
    (e.g. the scale of w^{(l)}_{ji} is scale=abs_tol+rel_tol*self.weights[l][j][i])

    step_break:if the average scale (over the dimension of the output signal) is smaller than the gradient
    for step_break number of steps, the SGD exits the loop.

    max_step: SGD exits after max_step steps regardless of convergence. 
   */
   
    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; 
    std::uniform_int_distribution<unsigned int> UnInt;
    un_int data_size=data_in->size();
    UnInt=std::uniform_int_distribution<unsigned int>{0,data_size -1};

    un_int _s=0;
    un_int count_steps=1;
    LD _check=0;

    un_int index;
    std::vector<LD> x,t;
    while(count_steps<=max_step){
        //get a random data point
        index=UnInt(RndE); 
        x=data_in->operator[](index);
        t=data_out->operator[](index);

        // run feedForward and backProp to calculate signals and Deltas 
        inputSignal(x);
        feedForward();
        backPropagation();
        
        //strategy should have an update member. During this, w's and b's are updated.
        //it can return sumething that becomes less than one, when the gradient becomes
        //small enough (we can change it later, to make the convergence conditions more 
        //involved). 
        //It also should have access to "self" because it will need to know the 
        //structure of the network, the loss, and take their derivatives.
        _check=strategy->update(t, abs_tol, rel_tol);

        if(_check<1){_s+=1;}
        else{_s=0;}
        
        if(_s>step_break){break;}


        ++count_steps;
    }


}

#endif