#ifndef FFANN_Vanilla_SGD
#define FFANN_Vanilla_SGD
#include<cmath>



template<class FFANN, class loss, class LD>
class Vanilla_SGD{
    private:
    FFANN *model;
    loss *Q;    
    LD alpha;
    unsigned int N,layers;

    public:

    Vanilla_SGD(FFANN *brain, loss *Q, LD alpha=1e-3){
        this->model=brain;
        this->Q=Q;
        this->alpha=alpha;
        
        this->layers=this->model->total_layers;
        this->N=this->model->nodes[this->layers-1];
    }   


    LD update(std::vector<LD> target, LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;
        LD dw=0;

        for(unsigned int l=0; l<layers-1; ++l){
            for(unsigned int j=0; j< model->nodes[l+1] ; ++j){
                for(unsigned int i=0; i< model->nodes[l] ; ++i){
                    Q->grad(l,j,i,model->signals[layers-1],target);
                    dw=alpha*(Q->dQdw);
                    model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + model->get_weight(l,j,i) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                dw=alpha*(Q->dQdb);
                model->addToBias(l,j,  -dw);
                _w2=abs_tol + model->get_bias(l,j) * rel_tol;
                _check+=(dw/_w2)*(dw/_w2);
            }
        }

        _check=std::sqrt(1./((LD) N) *_check);

        return _check;
    }


};

#endif