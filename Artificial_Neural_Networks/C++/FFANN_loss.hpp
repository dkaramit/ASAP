#ifndef FFANN_loss
#define FFANN_loss
#include<random>

template<class LD>
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

    using QFunc= LD (*)(LD, LD);
    using vec2=std::vector<std::vector<LD>>;
    public:
    QFunc Q_i, dQds_i;
    LD dQdw,dQdb;
    
    // pointer to vectors of input and output data
    vec2 *data_in;
    vec2 *data_out;
    
    FFANN<LD> *model;
    unsigned int N,layers;

    // size of data_in and output_data (should be constant, as they are assumed to be inputs)
    unsigned int data_size, dim;
    std::vector<LD> t;
    // set-up a random integer distribution that will randomly choose a data point each time this->update runs 
    std::default_random_engine RndE{std::random_device{}()}; ;
    std::uniform_int_distribution<unsigned int> UnInt;
    


    loss(){};
    loss(vec2 *data_in, vec2 *data_out, const QFunc &Q_i, const QFunc &dQds_i,FFANN<LD> *brain){

        this->model=brain;// don't make copy of FFANN!
        this->layers=this->model->total_layers;
        this->N=this->model->nodes[this->layers-1];        
        
        this->Q_i=Q_i;
        this->dQds_i=dQds_i;

        this->data_in=data_in;
        this->data_out=data_out;
        this->data_size=data_in->size();
        (this->t).resize(this->N);
        this->UnInt=std::uniform_int_distribution<unsigned int>{0,this->data_size -1};
    };


    void randomDataPoint(){
        //get a random data point
        unsigned int index=UnInt(RndE); 
        this->t=data_out->operator[](index);

        // run feedForward and backProp to calculate signals and Deltas 
        model->inputSignal(data_in->operator[](index));
        model->feedForward();
        model->backPropagation();
    }

    LD operator()(std::vector<LD> &signal, std::vector<LD> &target){
        LD sum_Q=0;
        
        for(unsigned int r=0; r<N; ++r){
            sum_Q+=Q_i(signal[r], target[r]); 
        }
        sum_Q=sum_Q/((LD) N);

        return sum_Q;
    }


    void grad(unsigned int l, unsigned int j, unsigned int i){
        /*calculates the derivatives wrt w^{(l)}_{ji} and b^{(l)}_{j}*/
        LD tmp_dQds;
        model->derivative_bw(l,j,i);
        //the derivative in general is 
        //\dfrac{\partial Q}{\partial P} = \dfrac{\partial Q}{\partial signal^{N-1}_{r}}\dfrac{\partial signal^{N-1}_{r}}{\partial P}
        dQdw=0;
        dQdb=0;

        for(unsigned int r=0; r<N; ++r){
            tmp_dQds=dQds_i(model->signals[model->total_layers-1][r], t[r])/((LD)N);
            dQdw += tmp_dQds*model->dsdw[r];
            dQdb += tmp_dQds*model->dsdb[r];
        }

    }

};


#endif