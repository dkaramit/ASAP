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
    lossFunc Q;
    vec2 *input_data;
    vec2 *output_data;
    LD beta_m,beta_v,gamma,epsilon,alpha;

    vec2 steps;
    std::vector<LD> mE, vE;
    unsigned int dim;
    
    std::vector<LD> grad;
    LD beta_m_ac,beta_v_ac;
    

    unsigned int data_size;
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;
    
    
    AdamSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data,LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-6, LD alpha=1e-2);
    AdamSGD(){};

    AdamSGD& operator=(const AdamSGD& strategy){
        this->Q=strategy.Q;
        this->input_data=strategy.input_data;
        this->output_data=strategy.output_data;
        this->beta_m=strategy.beta_m;
        this->beta_v=strategy.beta_v;
        this->gamma=strategy.gamma;
        this->epsilon=strategy.epsilon;
        this->alpha=strategy.alpha;


        this->data_size=input_data->size();
        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
;

        this->steps=strategy.steps;
        this->dim=strategy.Q.target->dim;
        this->grad.resize(this->dim);

        this->mE=strategy.mE;
        this->vE=strategy.vE;

        this->beta_m_ac=strategy.beta_m_ac;
        this->beta_v_ac=strategy.beta_v_ac;
 

        return *this;    
    };

    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3);

};



// Constructor
Adam_SGD_Template
Adam_SGD_Namespace::AdamSGD(const lossFunc &Q, vec2 *input_data, vec2 *output_data, LD beta_m, LD beta_v, LD epsilon, LD alpha){
    this->Q=Q;
    this->input_data=input_data;
    this->output_data=output_data;
    this->beta_m=beta_m;
    this->beta_v=beta_v;
    this->epsilon=epsilon;
    this->alpha=alpha;

    this->data_size=input_data->size();
    this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};

    this->dim=Q.target->dim;
    this->grad.resize(this->dim);
    this->steps.push_back(Q.target->w);

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

    unsigned int index=this->UnInt(this->RndE);
    this->Q.Grad(this->input_data->operator[](index),
                this->output_data->operator[](index),
                this->grad);

    // accumulate the decay rates, in order to correct the averages 
    this->beta_m_ac*=this->beta_m_ac;
    this->beta_v_ac*=this->beta_v_ac;

    for(unsigned int i=0 ; i<this->dim; ++i ){
        this->mE[i]=this->beta_m*this->mE[i] + (1-this->beta_m)*this->grad[i];
        this->vE[i]=this->beta_v*this->vE[i] + (1-this->beta_v)*this->grad[i]*this->grad[i];

        dw=this->alpha/(std::sqrt(this->vE[i]/(1-this->beta_v_ac) ) + this->epsilon);
        dw*=this->mE[i]/(1-this->beta_m_ac);

        Q.target->w[i]=Q.target->w[i] - dw;
        

        _w2=abs_tol + Q.target->w[i] * rel_tol;
        _check+=(this->grad[i]/_w2)*(this->grad[i]/_w2);
    }
    _check=std::sqrt(1/((LD) this->dim) *_check);
    
    this->steps.push_back(Q.target->w);

    return _check;
}

















#endif