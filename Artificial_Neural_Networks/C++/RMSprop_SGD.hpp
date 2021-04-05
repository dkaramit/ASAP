#ifndef FFANN_RMSprop_SGD
#define FFANN_RMSprop_SGD
#include<cmath>
#include"FFANN_SGD.hpp"

template<class LD, class lossFunc>
class RMSprop_SGD:public StochasticGradientDescent<LD,lossFunc>{
    public:
    LD gamma,epsilon,alpha;
    
    std::vector<std::vector<std::vector<LD>>> meanWeights;
    std::vector<std::vector<LD>> meanBiases;


    RMSprop_SGD()=default;
    RMSprop_SGD(lossFunc *Q, LD gamma=0.99, LD epsilon=1e-6, LD alpha=1e-2):StochasticGradientDescent<LD,lossFunc>(Q){
        this->alpha=alpha;
        this->gamma=gamma;
        this->epsilon=epsilon;
        this->alpha=alpha;

        this->meanWeights.resize(this->Q->layers-1);
        this->meanBiases.resize(this->Q->layers-1);
        for(unsigned int l=0; l<this->Q->layers-1; ++l){
            this->meanWeights[l].resize(this->Q->model->nodes[l+1]);
            this->meanBiases[l].resize(this->Q->model->nodes[l+1]);
            for(unsigned int j=0; j<this->Q->model->nodes[l+1]; ++j){
                this->meanWeights[l][j].resize(this->Q->model->nodes[l]);
                this->meanBiases[l][j]=0;
                for(unsigned int i=0; i<this->Q->model->nodes[l]; ++i){
                    this->meanWeights[l][j][l]=0;
                }
            }
        }
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
                    meanWeights[l][j][i]=gamma*meanWeights[l][j][i] + (1-gamma)*(this->Q->dQdw)*(this->Q->dQdw);
                    dw=alpha/std::sqrt( (meanWeights[l][j][i]+epsilon)  )*this->Q->dQdw;

                    this->Q->model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + std::abs(this->Q->model->get_weight(l,j,i)) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                meanBiases[l][j]=gamma*meanBiases[l][j] + (1-gamma)*(this->Q->dQdb)*(this->Q->dQdb);
                dw=alpha/std::sqrt( (meanBiases[l][j]+epsilon)  )*this->Q->dQdb;

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