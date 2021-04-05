#ifndef FFANN_Adam_SGD
#define FFANN_Adam_SGD
#include<cmath>
#include"FFANN_SGD.hpp"



template<class LD, class lossFunc>
class Adam_SGD:public StochasticGradientDescent<LD,lossFunc>{
    public:
    LD gamma,epsilon,alpha;

    LD beta_m, beta_v;
    LD beta_m_ac, beta_v_ac;

    std::vector<std::vector<std::vector<LD>>> mw,vw;
    std::vector<std::vector<LD>> mb,vb;

    Adam_SGD(lossFunc *Q, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-8, LD alpha=1e-2):StochasticGradientDescent<LD,lossFunc>(Q){
        this->beta_m=beta_m;
        this->beta_v=beta_v;
        this->epsilon=epsilon;
        this->alpha=alpha;
        
        this->beta_m_ac=beta_m;
        this->beta_v_ac=beta_v;

        this->mw.resize(this->Q->layers-1);
        this->vw.resize(this->Q->layers-1);
        this->mb.resize(this->Q->layers-1);
        this->vb.resize(this->Q->layers-1);

        for(unsigned int l=0; l<this->Q->layers-1; ++l){
            this->mw[l].resize(this->Q->model->nodes[l+1]);
            this->vw[l].resize(this->Q->model->nodes[l+1]);
            this->mb[l].resize(this->Q->model->nodes[l+1]);
            this->vb[l].resize(this->Q->model->nodes[l+1]);
            for(unsigned int j=0; j<this->Q->model->nodes[l+1]; ++j){
                this->mw[l][j].resize(this->Q->model->nodes[l]);
                this->vw[l][j].resize(this->Q->model->nodes[l]);
                this->mb[l][j]=0;
                this->vb[l][j]=0;
                for(unsigned int i=0; i<this->Q->model->nodes[l]; ++i){
                    this->mw[l][j][i]=0;
                    this->vw[l][j][i]=0;
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
        beta_v_ac*=beta_v_ac;

        for(unsigned int l=0; l<this->Q->layers-1; ++l){
            for(unsigned int j=0; j< this->Q->model->nodes[l+1] ; ++j){
                for(unsigned int i=0; i< this->Q->model->nodes[l] ; ++i){
                    this->Q->grad(l,j,i);

                    mw[l][j][i]=beta_m*mw[l][j][i] + (1-beta_m)*this->Q->dQdw;
                    vw[l][j][i]=beta_v*vw[l][j][i] + (1-beta_v)*(this->Q->dQdw)*(this->Q->dQdw);

                    dw=alpha/(std::sqrt(vw[l][j][i]/(1-beta_v_ac) ) + epsilon);  
                    dw*=mw[l][j][i]/(1-beta_m_ac);
            

                    this->Q->model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + std::abs(this->Q->model->get_weight(l,j,i)) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                mb[l][j]=beta_m*mb[l][j] + (1-beta_m)*this->Q->dQdb;
                vb[l][j]=beta_v*vb[l][j] + (1-beta_v)*(this->Q->dQdb)*(this->Q->dQdb);

                dw=alpha/(std::sqrt(vb[l][j]/(1-beta_v_ac) ) + epsilon);  
                dw*=mb[l][j]/(1-beta_m_ac);

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