#ifndef FFANN_AdaDelta_SGD
#define FFANN_AdaDelta_SGD
#include<cmath>
#include"FFANN_SGD.hpp"



template<class LD, class lossFunc>
class AdaDelta_SGD:public StochasticGradientDescent<LD,lossFunc>{
    public:
    LD gamma,epsilon,alpha;
    std::vector<std::vector<std::vector<LD>>> mean_dw,mean_dQdw;
    std::vector<std::vector<LD>> mean_db,mean_dQdb;

    AdaDelta_SGD(lossFunc *Q, LD gamma=0.995, LD epsilon=1e-5, LD alpha=1):StochasticGradientDescent<LD,lossFunc>(Q){
        this->gamma=gamma;
        this->epsilon=epsilon;
        this->alpha=alpha;


        this->mean_dw.resize(this->Q->layers-1);
        this->mean_dQdw.resize(this->Q->layers-1);
        this->mean_db.resize(this->Q->layers-1);
        this->mean_dQdb.resize(this->Q->layers-1);

        for(unsigned int l=0; l<this->Q->layers-1; ++l){
            this->mean_dw[l].resize(this->Q->model->nodes[l+1]);
            this->mean_dQdw[l].resize(this->Q->model->nodes[l+1]);
            this->mean_db[l].resize(this->Q->model->nodes[l+1]);
            this->mean_dQdb[l].resize(this->Q->model->nodes[l+1]);
            for(unsigned int j=0; j<this->Q->model->nodes[l+1]; ++j){
                this->mean_dw[l][j].resize(this->Q->model->nodes[l]);
                this->mean_dQdw[l][j].resize(this->Q->model->nodes[l]);
                this->mean_db[l][j]=0;
                this->mean_dQdb[l][j]=0;
                for(unsigned int i=0; i<this->Q->model->nodes[l]; ++i){
                    this->mean_dw[l][j][i]=0;
                    this->mean_dQdw[l][j][i]=0;
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

                    mean_dQdw[l][j][i]=gamma*mean_dQdw[l][j][i] + (1-gamma)*(this->Q->dQdw)*(this->Q->dQdw);
                    dw=std::sqrt( (mean_dw[l][j][i]+epsilon)/(mean_dQdw[l][j][i]+epsilon))*(this->Q->dQdw)*alpha;
                    mean_dw[l][j][i]=gamma*mean_dw[l][j][i] + (1-gamma)*dw*dw;

                    this->Q->model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + std::abs(this->Q->model->get_weight(l,j,i)) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                mean_dQdb[l][j]=gamma*mean_dQdb[l][j] + (1-gamma)*(this->Q->dQdb)*(this->Q->dQdb);
                dw=std::sqrt( (mean_db[l][j]+epsilon)/(mean_dQdb[l][j]+epsilon))*(this->Q->dQdb)*alpha;
                mean_db[l][j]=gamma*mean_db[l][j] + (1-gamma)*dw*dw;

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