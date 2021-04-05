#ifndef FFANN_Vanilla_SGD
#define FFANN_Vanilla_SGD
#include<cmath>
#include"FFANN_SGD.hpp"



template<class LD, class lossFunc>
class Vanilla_SGD:public StochasticGradientDescent<LD,lossFunc>{
    public:
    LD alpha;

    Vanilla_SGD()=default;
    Vanilla_SGD(lossFunc *Q, LD alpha=1e-3):StochasticGradientDescent<LD,lossFunc>(Q){
        this->alpha=alpha;
    }   


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;
        LD dw=0;
        this->Q->randomDataPoint();    

        for(unsigned int l=0; l<this->Q->layers-1; ++l){
            for(unsigned int j=0; j< this->Q->model->nodes[l+1] ; ++j){
                for(unsigned int i=0; i< this->Q->model->nodes[l] ; ++i){
                    this->Q->grad(l,j,i);
                    dw=alpha*(this->Q->dQdw);
                    this->Q->model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + std::abs(this->Q->model->get_weight(l,j,i)) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                dw=alpha*(this->Q->dQdb);
                this->Q->model->addToBias(l,j,  -dw);
                _w2=abs_tol + std::abs(this->Q->model->get_bias(l,j)) * rel_tol;
                _check+=(dw/_w2)*(dw/_w2);
            }
        }

        _check=std::sqrt(1./((LD) this->Q->N) *_check);

        return _check;
    }


};

#endif