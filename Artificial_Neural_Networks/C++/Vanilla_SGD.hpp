#ifndef FFANN_Vanilla_SGD
#define FFANN_Vanilla_SGD
#include<cmath>



template<class FFANN, class loss, class LD>
class Vanilla_SGD{
    public:
    FFANN *model;
    loss *Q;    
    LD alpha;

    unsigned int N,layers;

    Vanilla_SGD(FFANN *brain, loss *Q, LD alpha=1e-3){
        this->model=brain;
        this->Q=Q;
        this->alpha=alpha;
        
        this->N=this->model->nodes[model->nodes.size()-1];
        this->layers=this->model->nodes.size();
    }   


    LD update(std::vector<LD> target, LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;

        std::vector<LD> signal=model->signals[layers-1];
        for(unsigned int l=0; l<layers; ++l){
            for(unsigned int j=0; j< model->nodes[l+1] ; ++j){
                for(unsigned int i=0; i< model->nodes[l] ; ++i){
                    Q->grad(l,j,i,signal,target);

                    model->addToWeight(l,j,i,  -alpha*(Q->dQdw));

                    _w2=abs_tol + model->get_weight(l,j,i) * rel_tol;
                    _check+=(Q->dQdw/_w2)*(Q->dQdw/_w2);

                }
                model->addToBias(l,j,  -alpha*(Q->dQdb));
                _w2=abs_tol + model->get_bias(l,j) * rel_tol;
                _check+=(Q->dQdb/_w2)*(Q->dQdb/_w2);
            }
        }

        _check=std::sqrt(1./((LD) N) *_check);

        return _check;
    }


};

#endif