#ifndef SA_class
#define SA_class


#define FFANN_Template template<class LD, class Func>
#define FFANN_Namespace FFANN<LD,Func>



FFANN_Template
class FFANN{
    public:

    // number of input and output nodes
    int inputs, outputs;

    // vector with number of hidden nodes in each layer
    std::vector<int> hidden_nodes; 
    
    //We will need the following:

    // We will need the number of hidden layers (the ntotal number of layers is #hidden layers+2)
    int hidden_layers,total_layers;

    //vector that stores the number of nodes in each layer
    std::vector<int> nodes;

    // The biases and activations are defined so that the lth layer element has index l-1 (because they are not defined for l=0)
    //vector that stores the activation functions of each layer 
    std::vector<Func> activations;

    // vectors for signals and biases
    typedef std::vector< std::vector<LD> > vector2;
    vector2 signals,biases;

    // vector for weights
    typedef std::vector< std::vector< std::vector<LD> > > vector3;
    vector3 weights;



    // constructor
    FFANN(){};
    FFANN(int inputs, int outputs, std::vector<int> hidden_nodes, std::vector<Func> activations);
    // destructor
    ~FFANN();

    // initialize weights and biases
    void init_params(LD min=-1, LD max=1);

    // read input
    void input_signal(std::vector<LD> x);
    // calculate signal from neuron
    void calc_signal(int l,int j);
    // feed-forward
    void feed_forward();


    // functions for updating the parameters
    void update_weight(int l, int j, int i, LD value);
    void update_bias(int l, int j, LD value);

    // Functions to read and write parameters in a column vector
    void write_params(std::vector<LD> *X);
    void read_params(std::vector<LD> *X);

    // Functions for checking what happens inside the network (found in FFANN_aux.hpp).
    void print_weights();
    void print_biases();
    void print_signals();

};
 




#endif