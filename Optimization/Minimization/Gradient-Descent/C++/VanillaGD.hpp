#ifndef Vanilla_GD_class
#define Vanilla_GD_class

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate)
*/

#include<vector>
#include<cmath>

#define Vanilla_GD_Template template<class LD, class lossFunc>
#define Vanilla_GD_Namespace VanillaGD<LD,lossFunc>

Vanilla_GD_Template
class VanillaGD{
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
    // we will use this to hold the mean gradient over all data-points
    std::vector<LD> grad;

    // constructor (with default alpha)
    VanillaGD(lossFunc *Q, vec2 *input_data, vec2 *output_data, LD alpha=1e-3);
    VanillaGD(){};

  
    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Vanilla_GD_Template
Vanilla_GD_Namespace::VanillaGD(lossFunc *Q, vec2 *input_data, vec2 *output_data, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;
    this->alpha=alpha;

    this->dim=Q->model->dim;

    this->steps.push_back(Q->model->w);

    this->data_size=input_data->size();

    (this->grad).reserve(this->data_size);
    for (unsigned int i = 0; i < this->data_size; i++){
        (this->grad).push_back(0);
    }
    
}



// // The update function
Vanilla_GD_Template
LD Vanilla_GD_Namespace::update(LD abs_tol, LD rel_tol){
    
    LD _check=0,_w2=0,dw=0;

    // average grad over all data
    for (unsigned int index=0; index<data_size; ++index){
        std::vector<LD> t=output_data->operator[](index);

        // calculate the signal at current value of w and at the data point 
        Q->model->setInput(input_data->operator[](index));
        Q->model->operator()();
        for(unsigned int i=0 ; i<this->dim; ++i ){
            Q->grad(i,t);
            grad[i]+=(Q->dQdw)/data_size;
        }
    }
    
    for(unsigned int i=0 ; i<this->dim; ++i ){
        // update w (remember that model is a pointer to the model, so as update runs, the model is 
        // updated)
        dw=(alpha)*grad[i];
        Q->model->w[i] = Q->model->w[i] - dw ; 

        // grad^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + Q->model->w[i] * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);

        // reset grad to 0
        grad[i]=0;
    }
    // append new w to steps
    steps.push_back(Q->model->w);

    // calculate _check
    _check=std::sqrt(1/((LD) dim) *_check);
    return _check;
}

















#endif