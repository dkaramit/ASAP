#ifndef FFANN_RMSprop_SGD
#define FFANN_RMSprop_SGD
#include<cmath>



template<class FFANN, class loss, class LD>
class RMSprop_SGD{
    using un_int= unsigned int;
    private:
    FFANN *model;
    loss *Q;    
    LD gamma,epsilon,alpha;
    un_int N,layers;

    std::vector<std::vector<std::vector<LD>>> meanWeights;
    std::vector<std::vector<LD>> meanBiases;



    public:

    RMSprop_SGD(FFANN *brain, loss *Q, LD gamma=0.99, LD epsilon=1e-6, LD alpha=1e-2){
        this->model=brain;
        this->Q=Q;
        this->gamma=gamma;
        this->epsilon=epsilon;
        this->alpha=alpha;

        this->layers=this->model->total_layers;
        this->N=this->model->nodes[this->layers-1];


        this->meanWeights.reserve(this->layers-1);
        this->meanBiases.reserve(this->layers-1);
        for(un_int l=0; l<this->layers-1; ++l){
            this->meanWeights[l].reserve(model->nodes[l+1]);
            this->meanBiases[l].reserve(model->nodes[l+1]);
            for(un_int j=0; j<this->model->nodes[l+1]; ++j){
                this->meanWeights[l][j].reserve(model->nodes[l]);
                this->meanBiases[l].push_back(0);
                for(un_int i=0; i<this->model->nodes[l]; ++i){
                    this->meanWeights[l][j].push_back(0);
                }
            }
        }
    }   


    LD update(std::vector<LD> target, LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;
        LD dw=0;

        for(un_int l=0; l<layers-1; ++l){
            for(un_int j=0; j< model->nodes[l+1] ; ++j){
                for(un_int i=0; i< model->nodes[l] ; ++i){
                    Q->grad(l,j,i,model->signals[layers-1],target);
                    meanWeights[l][j][i]=gamma*meanWeights[l][j][i] + (1-gamma)*(Q->dQdw)*(Q->dQdw);
                    dw=alpha/std::sqrt( (meanWeights[l][j][i]+epsilon)  )*Q->dQdw;

                    model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + model->get_weight(l,j,i) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                meanBiases[l][j]=gamma*meanBiases[l][j] + (1-gamma)*(Q->dQdb)*(Q->dQdb);
                dw=alpha/std::sqrt( (meanBiases[l][j]+epsilon)  )*Q->dQdb;

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