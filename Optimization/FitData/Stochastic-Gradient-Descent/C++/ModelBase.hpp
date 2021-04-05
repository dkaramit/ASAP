#ifndef model_func
#define model_func


#include <cmath>
#include <random>
#include <vector>


// Generic model and loss function implementation. I choose to pass "this" because it gives 
// mode freedom on how the functions can be defined


template<class LD>
class modelBase{
    public:
    //vecotr of the free parameters of the model
    std::vector<LD> w;
    // size of w 
    unsigned int dim;
    //vector that holds the input and output dimensions
    std::vector<unsigned int> dimensions;
    
    //store the output signal here
    std::vector<LD> signal;
    //store the derivatives of the output signals over w_i here
    std::vector<LD> dsdw;
    // store the input so that you don't have to pass it evey time you call the model and its derivative
    std::vector<LD> input;

    modelBase()=default;
    modelBase(const std::vector<unsigned int> &dimensions, const std::vector<LD> &w0){
        this->w=w0;
        this->dim=w0.size();
        this->dimensions=dimensions;

        this->signal.resize(dimensions[1]);
        this->dsdw.resize(dimensions[1]);
        this->input.resize(dimensions[0]);
    }

    void setInput(std::vector<LD> &x){ 
        for (unsigned int i = 0; i < dimensions[0]; i++){input[i]=x[i];}
        
    }

    virtual void operator()(){}
    virtual void derivative_w(unsigned int i){}
};




template<class LD, class MFunc>
class lossFunc{
    using QFunc= LD (*)(LD, LD);
    using vec2=std::vector<std::vector<LD>>;
    public:
    QFunc Q_i, dQds_i;
    MFunc *model;

    // pointer to vectors of input and output data
    vec2 *input_data;
    vec2 *output_data;

    // size of input_data and output_data (should be constant, as they are assumed to be inputs)
    unsigned int data_size, dim;

    unsigned int N;
    
    LD dQdw; 
    std::vector<LD> t;
    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;

    lossFunc()=default;
    lossFunc(vec2 *input_data, vec2 *output_data, const QFunc &Q_i, const QFunc &dQds_i, MFunc *model){

        this->Q_i=Q_i;
        this->dQds_i=dQds_i;
        this->model=model; 
        this->N=this->model->dimensions[1];

        this->input_data=input_data;
        this->output_data=output_data;
        this->dim=model->dim;

        this->data_size=input_data->size();

        (this->t).resize(this->N);

        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
    }
  
    LD operator()(std::vector<LD> &target){
        LD sum_Q=0;
        
        for(unsigned int r=0; r<N; ++r){
            sum_Q+=Q_i(model->signal[r],target[r]); 
        }
        sum_Q=sum_Q/((LD) N);

        return sum_Q;
    }

    void randomPoint(){
        unsigned int index=this->UnInt(this->RndE);
        t=output_data->operator[](index);
        // calculate the signal at current value of w and at the data point 
        model->setInput(input_data->operator[](index));
        model->operator()();
    }

    void grad(unsigned int i){
        /*calculates the derivatives wrt w_i*/
        LD tmp_dQds;
        model->derivative_w(i);
        dQdw=0;

        for(unsigned int r=0; r<N; ++r){
            tmp_dQds=dQds_i(model->signal[r],t[r])/((LD)N);
            dQdw += tmp_dQds*model->dsdw[r];
        }

    }
};




#endif