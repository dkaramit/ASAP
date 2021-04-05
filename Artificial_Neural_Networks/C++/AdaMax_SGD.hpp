#ifndef FFANN_AdaMax_SGD
#define FFANN_AdaMax_SGD
#include"FFANN_SGD.hpp"



template<class LD, class lossFunc>
class AdaMax_SGD:public StochasticGradientDescent<LD,lossFunc>{
    public:
    LD gamma,epsilon,alpha;

    LD beta_m, beta_v;
    LD beta_m_ac;

    std::vector<std::vector<std::vector<LD>>> mw,vw_max;
    std::vector<std::vector<LD>> mb,vb_max;

    AdaMax_SGD(lossFunc *Q, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-8, LD alpha=1e-2):StochasticGradientDescent<LD,lossFunc>(Q){
        this->beta_m=beta_m;
        this->beta_v=beta_v;
        this->epsilon=epsilon;
        this->alpha=alpha;
        
        this->beta_m_ac=beta_m;


        this->mw.resize(this->Q->layers-1);
        this->vw_max.resize(this->Q->layers-1);
        this->mb.resize(this->Q->layers-1);
        this->vb_max.resize(this->Q->layers-1);

        for(unsigned int  l=0; l<this->Q->layers-1; ++l){
            this->mw[l].resize(this->Q->model->nodes[l+1]);
            this->vw_max[l].resize(this->Q->model->nodes[l+1]);
            this->mb[l].resize(this->Q->model->nodes[l+1]);
            this->vb_max[l].resize(this->Q->model->nodes[l+1]);
            for(unsigned int  j=0; j<this->Q->model->nodes[l+1]; ++j){
                this->mw[l][j].resize(this->Q->model->nodes[l]);
                this->vw_max[l][j].resize(this->Q->model->nodes[l]);
                this->mb[l][j]=0;
                this->vb_max[l][j]=0;
                for(unsigned int  i=0; i<this->Q->model->nodes[l]; ++i){
                    this->mw[l][j][i]=0;
                    this->vw_max[l][j][i]=0;
                }
            }
        }
    }   


    LD update(LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;
        LD dw=0;
        this->Q->randomDataPoint();    

        beta_m_ac*=beta_m_ac;

        for(unsigned int  l=0; l<this->Q->layers-1; ++l){
            for(unsigned int  j=0; j< this->Q->model->nodes[l+1] ; ++j){
                for(unsigned int  i=0; i< this->Q->model->nodes[l] ; ++i){
                    this->Q->grad(l,j,i);

                    mw[l][j][i]=beta_m*mw[l][j][i] + (1-beta_m)*this->Q->dQdw;
                    
                    vw_max[l][j][i]=beta_v*vw_max[l][j][i];
                    if(vw_max[l][j][i]<std::abs(this->Q->dQdw)){
                        vw_max[l][j][i]=std::abs(this->Q->dQdw);
                    } 

                    dw=alpha/(vw_max[l][j][i] + epsilon)*mw[l][j][i]/(1-beta_m_ac);


                    this->Q->model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + std::abs(this->Q->model->get_weight(l,j,i)) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                mb[l][j]=beta_m*mb[l][j] + (1-beta_m)*this->Q->dQdb;
                
                vb_max[l][j]=beta_v*vb_max[l][j];
                if(vb_max[l][j]<std::abs(this->Q->dQdb)){
                    vb_max[l][j]=std::abs(this->Q->dQdb);
                } 

                    dw=alpha/(vb_max[l][j] + epsilon)*mb[l][j]/(1-beta_m_ac);


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