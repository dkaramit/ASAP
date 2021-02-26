#ifndef SA_class
#define SA_class

#include<vector>
#include<array>

template<class LD, class Func>
class activationType{
    private:
    Func _function,_derivative;
    
    public:
    activationType(const Func  &function, const Func  &derivative){
        this->_function=function;
        this->_derivative=derivative;
    };
    activationType(){};

    LD operator()(LD x){return _function(x);};
    LD derivative(LD x){return _derivative(x);};

    //just in case
    // activationType& operator=(activationType act)
    // {
    //     std::swap(_function, act._function);
    //     std::swap(_derivative, act._derivative);
    //     return *this;
    // }
};

#define FFANN_Template template<class LD, class Func>
#define FFANN_Namespace FFANN<LD, Func>



FFANN_Template
class FFANN{

    using un_int=unsigned int;
    using actArray=std::vector<activationType<LD,Func>>;
    using nodeArray=std::vector<un_int>;

    // This multidimensional arrays do not seem to be the best option.
    // Should represent it as 1D. The problem is that the rows ans comluns
    // are not the same size in all layers, and we would need to store the 
    // sizes in other arrays.  
    using weightArray=std::vector<std::vector<std::vector<LD>>>;

    using biasArray=std::vector<std::vector<LD>>;

    using signalArray=std::vector<std::vector<LD>>;

    using derivativeArray=std::vector<std::vector<std::vector<LD>>>;
    
    using numDerArray=std::vector<std::vector<LD>>;

    using totalDerArray=std::vector<std::vector<std::vector<LD>>>;
    using DeltaArray=std::vector<std::vector<std::vector<LD>>>;

    using dsdwbArray=std::vector<LD>;
    

    public:
    un_int total_layers;

    actArray activations;
    nodeArray nodes;
    
    signalArray signals,_signals;
    weightArray weights;
    
    biasArray biases;

    derivativeArray derivatives;

    totalDerArray totalDerivatives;
    DeltaArray Delta;
    numDerArray numericalDerivatives;

    dsdwbArray dsdw,dsdb,numerical_dsdw,numerical_dsdb;




    /*-------------constructors-------------*/
    FFANN(){};
    FFANN(nodeArray &nodes, actArray &activationFunctions);
    // you can call this as in python (i don't really like it)
    FFANN(un_int inputNodes, un_int outputNodes, std::vector<un_int> &hiddenNodes, 
    actArray &activationFunctions);



    /*-------------functions for assignments-------------*/
    // "setters"
    void update_weight(un_int l, un_int j, un_int i, LD value);
    void update_bias(un_int l, un_int j, LD value);
    // add to the parameters
    void addToWeight(un_int l, un_int j, un_int i, LD value);
    void addToBias(un_int l, un_int j, LD value);
    // "getters"
    LD get_weight(un_int l, un_int j, un_int i);
    LD get_bias(un_int l, un_int j);
    //fill
    void init_weights(LD min_value=-1, LD max_value=1);
    void init_biases(LD min_value=-1, LD max_value=1);
    void fill_weights_with(LD value=0);
    void fill_biases_with(LD value=0);

    /*-------------signal and derivative calculation functions-------------*/
    //set input signal (s^{(0)}_{j})
    void inputSignal(const std::vector<LD> &x);
    //calculate s^{(l)}_{j} and the local derivatives
    void calcSignal(un_int l, un_int j);
    //calculate only s^{(l)}_{j}
    void evaluate(const std::vector<LD> &x);
    //Calculate only the output of the network and the local derivatives
    void feedForward();
    // overlaod operator() for convenience
    std::vector<LD> operator()(const std::vector<LD> &x);

    //back porogation derivatives
    void backPropagation();
    // caclulate derivatives wrt the weights and biases (should be called only after backPropagation())
    void derivative_bw(un_int l,un_int j,un_int i);

    // feed forward derivatives
    //Calculate only the output of the network, the local derivatives, and the total derivatives
    void feedForwardDerivatives();
    //Matrix multiplication to be used when calculating the derivatives.
    // It is intended to be used the feedForwardDerivatives() call.
    void mulM(un_int l);

    // numerical derivatives wrt to a given input node
    void numericalDerivative(un_int input_node, LD h=1e-3);
    // numerical derivatives wrt to all given input nodes
    void totalNumericalDerivative(LD h=1e-3);
    // numerical derivative wrt  w^{(l)}_{ji} and b^{(l+1)}_{j}
    void numericalDerivative_bw(un_int l, un_int j, un_int i, LD h=1e-3);

    //stochastic gradient descent main loop.
    template <class Strategy>
    unsigned int SGD(Strategy *strategy, 
            const std::vector<std::vector<LD>> *data_in, const std::vector<std::vector<LD>> *data_out, 
            LD abs_tol=1e-5, LD rel_tol=1e-3, un_int step_break=100, un_int max_step=5000);


    //Auxilliary functions for printing
    void printWeights();
    void printBiases();
    void printSignals();

    void printDerivatives();
    
    void printTotalDerivatives();
    void printDelta();

    void printNumericalDerivatives();

    void printDerivatives_w();
    void printDerivatives_b();

    void printNumericalDerivatives_w();
    void printNumericalDerivatives_b();
};


#endif