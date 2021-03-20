#ifndef Adam_SGD_class
#define Adam_SGD_class

/*
Adam Stochastic Gradient Descent
*/

#include<vector>
#include<cmath>
#include<random>

#define Adam_SGD_Template template<class LD, class lossFunc>
#define Adam_SGD_Namespace AdamSGD<LD,lossFunc>

Adam_SGD_Template
class AdamSGD{
    using vec2=std::vector<std::vector<LD>>;

    public:
    // the loss function
    lossFunc *Q;
    // pointer to vectors of input and output data
    vec2 *input_data;
    vec2 *output_data;

    // parameters of the algorithm
    LD beta_m,beta_v,epsilon,alpha;

    // the dimension of the w parameters (same as grad obviously)
    unsigned int dim;
    
    // a vector that holds the w as the algorith runs
    vec2 steps;
    
    // size of input_data and output_data (should be constant, as they are assumed to be inputs)
    unsigned int data_size;

    
    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;

    // vecors for the decaying averages of m and v
    std::vector<LD> mE, vE;

    // variables that accumulate beta_{m,v}^iteration
    LD beta_m_ac,beta_v_ac;
    

    
    // constructor with default values of the parameters    
    AdamSGD(lossFunc *Q, vec2 *input_data, vec2 *output_data,LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    AdamSGD(){};


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);
};



// Constructor
Adam_SGD_Template
Adam_SGD_Namespace::AdamSGD(lossFunc *Q, vec2 *input_data, vec2 *output_data, LD beta_m, LD beta_v, LD epsilon, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;

    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->dim=Q->model->dim;

    this->steps.push_back(Q->model->w);

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

    this->beta_m_ac=beta_m;
    this->beta_v_ac=beta_v;

    for(unsigned int i=0; i<this->dim; ++i){
        this->mE.push_back(0);
        this->vE.push_back(0);
    }
}



// // The update function
Adam_SGD_Template
LD Adam_SGD_Namespace::update(LD abs_tol, LD rel_tol){

    LD dw=0,_check=0,_w2=0;

    // choose index of random data point
    unsigned int index=this->UnInt(this->RndE);
    std::vector<LD> t=output_data->operator[](index);

    // calculate the signal at current value of w and at the data point 
    Q->model->setInput(input_data->operator[](index));
    Q->model->operator()();


    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        // calculate the gradient at current value of w and at the index^th data point 
        Q->grad(i,t);

        // calculate the decaying averages
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*Q->dQdw;
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*Q->dQdw*Q->dQdw;

        // update w
        dw=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac) ) + this->epsilon);
        dw*=this->mE[i]/(1-this->beta_m_ac);
        Q->model->w[i]=Q->model->w[i] - dw;
        
        // grad^2/(abs_tol + w * rel_tol)^2 for this direction
        _w2=abs_tol + Q->model->w[i] * rel_tol;
        _check+=(dw/_w2)*(dw/_w2);
    }
    // append new w to steps
    this->steps.push_back(Q->model->w);

    // calculate _check
    _check=std::sqrt(1/((LD) this->dim) *_check);
    return _check;
}

















#endif