#ifndef FFANN_AdaDelta_SGD
#define FFANN_AdaDelta_SGD
#include<cmath>



template<class FFANN, class loss, class LD>
class AdaDelta_SGD{
    using un_int= unsigned int;
    private:
    FFANN *model;
    loss *Q;    
    LD gamma,epsilon,alpha;
    un_int N,layers;

    std::vector<std::vector<std::vector<LD>>> mean_dw,mean_dQdw;
    std::vector<std::vector<LD>> mean_db,mean_dQdb;



    public:

    AdaDelta_SGD(FFANN *brain, loss *Q, LD gamma=0.995, LD epsilon=1e-5, LD alpha=1){
        this->model=brain;
        this->Q=Q;
        this->gamma=gamma;
        this->epsilon=epsilon;
        this->alpha=alpha;

        this->layers=this->model->total_layers;
        this->N=this->model->nodes[this->layers-1];


    this->mean_dw.reserve(this->layers-1);
    this->mean_dQdw.reserve(this->layers-1);
    this->mean_db.reserve(this->layers-1);
    this->mean_dQdb.reserve(this->layers-1);

    for(un_int l=0; l<this->layers-1; ++l){
        this->mean_dw[l].reserve(model->nodes[l+1]);
        this->mean_dQdw[l].reserve(model->nodes[l+1]);
        this->mean_db[l].reserve(model->nodes[l+1]);
        this->mean_dQdb[l].reserve(model->nodes[l+1]);
        for(un_int j=0; j<this->model->nodes[l+1]; ++j){
            this->mean_dw[l][j].reserve(model->nodes[l]);
            this->mean_dQdw[l][j].reserve(model->nodes[l]);
            this->mean_db[l].push_back(0);
            this->mean_dQdb[l].push_back(0);
            for(un_int i=0; i<this->model->nodes[l]; ++i){
                this->mean_dw[l][j].push_back(0);
                this->mean_dQdw[l][j].push_back(0);
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

                    mean_dQdw[l][j][i]=gamma*mean_dQdw[l][j][i] + (1-gamma)*(Q->dQdw)*(Q->dQdw);
                    dw=std::sqrt( (mean_dw[l][j][i]+epsilon)/(mean_dQdw[l][j][i]+epsilon))*(Q->dQdw)*alpha;
                    mean_dw[l][j][i]=gamma*mean_dw[l][j][i] + (1-gamma)*dw*dw;

                    model->addToWeight(l,j,i,  -dw);

                    _w2=abs_tol + model->get_weight(l,j,i) * rel_tol;
                    _check+=(Q->dQdw/_w2)*(Q->dQdw/_w2);

                }
                    mean_dQdb[l][j]=gamma*mean_dQdb[l][j] + (1-gamma)*(Q->dQdb)*(Q->dQdb);
                    dw=std::sqrt( (mean_db[l][j]+epsilon)/(mean_dQdb[l][j]+epsilon))*(Q->dQdb)*alpha;
                    mean_db[l][j]=gamma*mean_db[l][j] + (1-gamma)*dw*dw;

                model->addToBias(l,j,  -dw);
                
                _w2=abs_tol + model->get_bias(l,j) * rel_tol;
                _check+=(Q->dQdb/_w2)*(Q->dQdb/_w2);
            }
        }

        _check=std::sqrt(1./((LD) N) *_check);

        return _check;
    }


};

#endif