#ifndef Vanilla_SGD_class
#define Vanilla_SGD_class

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>
#include<random>

#define Vanilla_SGD_Template template<class LD, class lossFunc>
#define Vanilla_SGD_Namespace VanillaSGD<LD,lossFunc>

Vanilla_SGD_Template
class VanillaSGD{
    using vec2=std::vector<std::vector<LD>>;

    public:
    // the loss function
    lossFunc *Q;
    // pointer to vectors of input and output data
    vec2 *input_data;
    vec2 *output_data;

    // the learning rate
    LD alpha;

    // the dimension of the w parameters (same as grad obviously)
    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    vec2 steps;
    
    // size of input_data and output_data (should be constant, as they are assumed to be inputs)
    unsigned int data_size;

    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;
    
    // constructor (with default alpha)
    VanillaSGD(lossFunc *Q, vec2 *input_data, vec2 *output_data, LD alpha=1e-3);
    VanillaSGD(){};

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_SGD_Template
Vanilla_SGD_Namespace::VanillaSGD(lossFunc *Q, vec2 *input_data, vec2 *output_data, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;
    this->alpha=alpha;

    this->dim=Q->model->dim;

    this->steps.push_back(Q->model->w);

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
}



// // The update function
Vanilla_SGD_Template
LD Vanilla_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD _check=0,_w2=0,dw=0;
    // choose index of random data point
    unsigned int index=this->UnInt(this->RndE);
    std::vector<LD> t=output_data->operator[](index);

    // calculate the signal at current value of w and at the data point 
    Q->model->setInput(input_data->operator[](index));
    Q->model->operator()();

    
    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the gradient at current value of w and at the index^th data point 
        Q->grad(i,t);
        // update w (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        dw=(alpha)*Q->dQdw;
        Q->model->w[i] = Q->model->w[i] - dw ; 

        // grad^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + Q->model->w[i] * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);
    }
    // append new w to steps
    steps.push_back(Q->model->w);

    // calculate _check
    _check=std::sqrt(1/((LD) dim) *_check);
    return _check;
}

















#endif