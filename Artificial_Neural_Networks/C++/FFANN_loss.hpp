#ifndef FFANN_loss
#define FFANN_loss
#include"FFANN.hpp"

template<class LD, class FFANN>
class loss{
    /*
    The loss should look like this.
    
    Q_i: the loss function for one data-point 
        e.g. LD Q_i(LD signal, LD targer) {return (signal-targer)*(signal-targer) } for the square loss.

    Q_i will be called from operator(), which will take the average over all components of the signal.
    
    dQds_i: the derivative of Q_i wrt signal 
    LD dQds_i(LD signal, LD targer) {return 2*(signal-targer)}
    Again it will be averaged over all components of the signal when calling grad().
    
    model: the feed-forward neural network which is going to be used.
    */

    using func= LD (*)(LD,LD);
    public:
    func Q_i, dQds_i;
    LD dQdw,dQdb;
    
    
    FFANN *model;
    unsigned int N;


    loss(){};
    loss(const func &Q_i, const func &dQds_i,FFANN *brain){

        this->model=brain;// don't make copy of FFANN!
        this->N=this->model->nodes[model->nodes.size()-1];
        this->Q_i=Q_i;
        this->dQds_i=dQds_i;

    };

    LD operator()(std::vector<LD> signal, std::vector<LD> target){
        LD sum_Q=0;
        
        for(unsigned int r=0; r<N; ++r){
            sum_Q+=Q_i(signal[r],target[r]); 
        }
        sum_Q=sum_Q/((LD) N);

        return sum_Q;
    }


    void grad(unsigned int l, unsigned int j, unsigned int i, std::vector<LD> signal, std::vector<LD> target){
        /*calculates the derivatives wrt w^{(l)}_{ji} and b^{(l)}_{j}*/
        LD tmp_dQds;

        model->derivative_bw(l,j,i);
        //the derivative in general is 
        //\dfrac{\partial Q}{\partial P} = \dfrac{\partial Q}{\partial signal^{N-1}_{r}}\dfrac{\partial signal^{N-1}_{r}}{\partial P}
        dQdw=0;
        dQdb=0;

        for(unsigned int r=0; r<N; ++r){
            tmp_dQds=dQds_i(signal[r],target[r])/((LD)N);
            dQdw += tmp_dQds*model->dsdw[r];
            dQdb += tmp_dQds*model->dsdb[r];
        }

    }

};


#endif