#ifndef FFANN_NAdam_SGD
#define FFANN_NAdam_SGD
#include<cmath>



template<class FFANN, class loss, class LD>
class NAdam_SGD{
    using un_int= unsigned int;
    private:
    FFANN *model;
    loss *Q;    
    LD gamma,epsilon,alpha;
    un_int N,layers;

    LD beta_m, beta_v;
    LD beta_m_ac, beta_v_ac;

    std::vector<std::vector<std::vector<LD>>> mw,vw;
    std::vector<std::vector<LD>> mb,vb;



    public:

    NAdam_SGD(FFANN *brain, loss *Q, LD beta_m=1-1e-1, LD beta_v=1-1e-3, LD epsilon=1e-8, LD alpha=1e-2){
        this->model=brain;
        this->Q=Q;

        this->beta_m=beta_m;
        this->beta_v=beta_v;
        this->epsilon=epsilon;
        this->alpha=alpha;
        
        this->beta_m_ac=beta_m;
        this->beta_v_ac=beta_v;


        this->layers=this->model->total_layers;
        this->N=this->model->nodes[this->layers-1];


        this->mw.reserve(this->layers-1);
        this->vw.reserve(this->layers-1);
        this->mb.reserve(this->layers-1);
        this->vb.reserve(this->layers-1);

        for(un_int l=0; l<this->layers-1; ++l){
            this->mw[l].reserve(model->nodes[l+1]);
            this->vw[l].reserve(model->nodes[l+1]);
            this->mb[l].reserve(model->nodes[l+1]);
            this->vb[l].reserve(model->nodes[l+1]);
            for(un_int j=0; j<this->model->nodes[l+1]; ++j){
                this->mw[l][j].reserve(model->nodes[l]);
                this->vw[l][j].reserve(model->nodes[l]);
                this->mb[l].push_back(0);
                this->vb[l].push_back(0);
                for(un_int i=0; i<this->model->nodes[l]; ++i){
                    this->mw[l][j].push_back(0);
                    this->vw[l][j].push_back(0);
                }
            }
        }
    }   


    LD update(std::vector<LD> target, LD abs_tol=1e-5, LD rel_tol=1e-3){
        LD _check=0;
        LD _w2=0;
        LD dw=0;

        beta_m_ac*=beta_m_ac;
        beta_v_ac*=beta_v_ac;

        for(un_int l=0; l<layers-1; ++l){
            for(un_int j=0; j< model->nodes[l+1] ; ++j){
                for(un_int i=0; i< model->nodes[l] ; ++i){
                    Q->grad(l,j,i,model->signals[layers-1],target);

                    mw[l][j][i]=beta_m*mw[l][j][i] + (1-beta_m)*(Q->dQdw);
                    vw[l][j][i]=beta_v*vw[l][j][i] + (1-beta_v)*(Q->dQdw)*(Q->dQdw);

                    dw=alpha/(std::sqrt(vw[l][j][i]/(1-beta_v_ac)) + epsilon);
                    dw*=(beta_m*mw[l][j][i] + (1-beta_m)*(Q->dQdw))/(1-beta_m_ac);
            

                    model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + model->get_weight(l,j,i) * rel_tol;
                    _check+=(dw/_w2)*(dw/_w2);

                }
                mb[l][j]=beta_m*mb[l][j] + (1-beta_m)*(Q->dQdb);
                vb[l][j]=beta_v*vb[l][j] + (1-beta_v)*(Q->dQdb)*(Q->dQdb);

                dw=alpha/(std::sqrt(vb[l][j]/(1-beta_v_ac)) + epsilon);
                dw*=(beta_m*mb[l][j] + (1-beta_m)*(Q->dQdb))/(1-beta_m_ac);

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