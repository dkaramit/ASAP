#ifndef Vanilla_SGD_class
#define Vanilla_SGD_class

/*
Vanilla Stochastic Gradient Descent (i.e. no adaptation of the learning rate).
VanillaSGD is a class rderived from GradientDescent
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
    lossFunc Q;
    vec2 *input_data;
    vec2 *output_data;
    LD alpha;


    vec2 steps;
    unsigned int dim;
    
    std::vector<LD> grad;
    
    unsigned int data_size;
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;
    
    
    VanillaSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD alpha=1e-3);

    VanillaSGD(){};
    VanillaSGD& operator=(const VanillaSGD& van){
        this->Q=van.Q;
        this->input_data=van.input_data;
        this->output_data=van.output_data;
        this->alpha=van.alpha;


        this->data_size=input_data->size();
        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
;

        this->steps=van.steps;
        this->dim=van.Q.target->dim;
        this->grad.resize(this->dim);

        return *this;    
    };

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);

};



// Constructor
Vanilla_SGD_Template
Vanilla_SGD_Namespace::VanillaSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;
    this->alpha=alpha;

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

    this->dim=Q.target->dim;
    this->grad.resize(this->dim);
    this->steps.push_back(Q.target->w);
}



// // The update function
Vanilla_SGD_Template
LD Vanilla_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    LD _check=0,_w2=0;
    unsigned int index=this->UnInt(this->RndE);
    this->Q.Grad(this->input_data->operator[](index),
                this->output_data->operator[](index),
                this->grad);
    
    for(unsigned int i=0 ; i<this->dim; ++i ){
        Q.target->w[i] = Q.target->w[i] - (this->alpha)*this->grad[i] ; 

        _w2=abs_tol + Q.target->w[i] * rel_tol;
        _check+=(this->grad[i]/_w2)*(this->grad[i]/_w2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(Q.target->w);

    return _check;
}

















#endif