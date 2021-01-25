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
    lossFunc Q;
    vec2 *input_data;
    vec2 *output_data;
    LD gamma,epsilon,alpha;

    vec2 steps;
    std::vector<LD> gE;
    unsigned int dim;
    
    std::vector<LD> grad;
    

    unsigned int data_size;
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;
    
    
    RMSpropSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD gamma=0.95, LD epsilon=1e-6, LD alpha=1e-2);

    RMSpropSGD(){};
    RMSpropSGD& operator=(const RMSpropSGD& strategy){
        this->Q=strategy.Q;
        this->input_data=strategy.input_data;
        this->output_data=strategy.output_data;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;


        this->data_size=input_data->size();
        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
;

        this->steps=strategy.steps;
        this->dim=strategy.Q.target->dim;
        this->grad.resize(this->dim);

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

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

    this->dim=Q.target->dim;
    this->grad.resize(this->dim);
    this->steps.push_back(Q.target->w);

    for(unsigned int i=0; i<this->dim; ++i){
        this->gE.push_back(0);
    }

}



// // The update function
RMSprop_SGD_Template
LD RMSprop_SGD_Namespace::update(LD abs_tol, LD rel_tol){
    LD dw=0,_check=0,_w2=0;

    unsigned int index=this->UnInt(this->RndE);
    this->Q.Grad(this->input_data->operator[](index),
                this->output_data->operator[](index),
                this->grad);


    for(unsigned int i=0 ; i<this->dim; ++i ){

        this->gE[i]=this->gamma*this->gE[i] + (1-this->gamma)*this->grad[i]*this->grad[i];
        dw=std::sqrt( 1/(this->gE[i]+this->epsilon)  )*this->grad[i]*this->alpha;
        Q.target->w[i]=Q.target->w[i] - dw;
        

        _w2=abs_tol + Q.target->w[i] * rel_tol;
        _check+=(this->grad[i]/_w2)*(this->grad[i]/_w2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(Q.target->w);

    return _check;
}

















#endif