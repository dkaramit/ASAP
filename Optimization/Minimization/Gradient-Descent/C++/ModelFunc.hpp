#ifndef model_func
#define model_func


#include <cmath>
#include <vector>


// Generic model and loss function implementation. I choose to pass "this" because it gives 
// mode freedom on how the functions can be defined


template<class LD>
class modelFunc{
    using MFunc= void (*)(modelFunc<LD> *);
    using MDer= void (*)(unsigned int,  modelFunc<LD> *);
    
    //the function
    MFunc f;
    // the derivative of wrt w_i
    MDer dfdw_i;
    
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

    modelFunc(){};
    modelFunc(const MFunc func, const MDer dfdw_i, const std::vector<unsigned int> &dimensions, const std::vector<LD> &w0){
        this->f=func;
        this->dfdw_i=dfdw_i;
        this->w=w0;
        this->dim=w0.size();
        this->dimensions=dimensions;

        this->signal.reserve(dimensions[1]);
        this->dsdw.reserve(dimensions[1]);
        this->input.reserve(dimensions[0]);
    }

    void setInput(std::vector<LD> &x){ 
        for (unsigned int i = 0; i < dimensions[0]; i++)
        {
            input[i]=x[i];
        }
        
    }

    void operator()(){ f(this); }

    void derivative_w(unsigned int i){
        dfdw_i(i,this);
    }
};

template<class LD, class MFunc>
class lossFunc{
    using QFunc= LD (*)(modelFunc<LD> *, unsigned int, LD );
    public:
    QFunc Q_i, dQds_i;
    MFunc *model;

    unsigned int N;
    
    LD dQdw; 

    lossFunc(){};
    lossFunc(const QFunc &Q_i, const QFunc &dQds_i, MFunc *model){
        this->Q_i=Q_i;
        this->dQds_i=dQds_i;
        this->model=model; 
        this->N=this->model->dimensions[1];
    }
  
    LD operator()(std::vector<LD> &target){
        LD sum_Q=0;
        
        for(unsigned int r=0; r<N; ++r){
            sum_Q+=Q_i(model, r,target[r]); 
        }
        sum_Q=sum_Q/((LD) N);

        return sum_Q;
    }


    void grad(unsigned int i, std::vector<LD> &target){
        /*calculates the derivatives wrt w_i*/
        LD tmp_dQds;
        model->derivative_w(i);
        dQdw=0;

        for(unsigned int r=0; r<N; ++r){
            tmp_dQds=dQds_i(model, r,target[r])/((LD)N);
            dQdw += tmp_dQds*model->dsdw[r];
        }

    }
};





#endif