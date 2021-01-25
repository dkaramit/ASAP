#ifndef RMSprop_SGD_class
#define RMSprop_SGD_class

/*
RMSprop Stochastic Gradient Descent
*/

#include<vector>
#include<cmath>
#include<random>

#define RMSprop_SGD_Template template<class LD, class lossFunc>
#define RMSprop_SGD_Namespace RMSpropSGD<LD,lossFunc>

RMSprop_SGD_Template
class RMSpropSGD{
    using vec2=std::vector<std::vector<LD>>;

    public:
    // the loss function
    lossFunc Q;
    // pointer to vectors of input and output data
    vec2 *input_data;
    vec2 *output_data;

    // parameters of the algorithm
    LD gamma,epsilon,alpha;

    // the gradiend over the parameters of the model (the should be a pointer Q.target)
    std::vector<LD> grad;
    // the dimension of the w parameters (same as grad obviously)
    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    vec2 steps;
    
    // size of input_data and output_data (should be constant, as they are assumed to be inputs)
    unsigned int data_size;

    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;    

    // vector for the decaying average of the gradient
    std::vector<LD> gE;

    // constructor with default values of the parameters    
    RMSpropSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);
    RMSpropSGD(){};

    // overloading of operator= just to make sure that we can copy it correctly
    RMSpropSGD& operator=(const RMSpropSGD& strategy){
        this->Q=strategy.Q;
        this->input_data=strategy.input_data;
        this->output_data=strategy.output_data;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;

        this->dim=strategy.Q.target->dim;
        this->grad.resize(this->dim);

        this->steps=strategy.steps;

        this->data_size=input_data->size();
        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

        this->gE=strategy.gE;

        return *this;    
    };

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
RMSprop_SGD_Template
RMSprop_SGD_Namespace::RMSpropSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD gamma, LD epsilon, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;
    this->gamma=gamma;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->dim=Q.target->dim;
    this->grad.resize(this->dim);

    this->steps.push_back(Q.target->w);

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
    }
}



// // The update function
RMSprop_SGD_Template
LD RMSprop_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD dw=0,_check=0,_w2=0;

    // choose index of random data point
    unsigned int index=this->UnInt(this->RndE);
    // calculate the gradient at current value of w and at the index^th data point 
    this->Q.Grad(this->input_data->operator[](index),
                this->output_data->operator[](index),
                this->grad);


    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate decaying average of the gradient
        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*this->grad[i]*this->grad[i];
        
        // update w
        dw=std::sqrt( 1/(this->gE[i]+this->epsilon)  )*this->grad[i]*this->alpha;
        Q.target->w[i]=Q.target->w[i] - dw;

        // grad^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + Q.target->w[i] * rel_tol;
        _check+=(this->grad[i]/_w2)*(this->grad[i]/_w2);
    }
    // append new w to steps
    this->steps.push_back(Q.target->w);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif