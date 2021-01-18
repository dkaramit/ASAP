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
    
    // output and hidden layer activation
    Func hidden_activation, output_activation;



    //We will need the following:

    // We will need the number of hidden layers (the ntotal number of layers is #hidden layers+2)
    int hidden_layers,total_layers;

    //vector that stores the number of nodes in each layer
    std::vector<int> nodes;
        
    // vectors for signals and biases
    typedef std::vector< std::vector<LD> > vector2;
    vector2 signals,biases;

    // vector for weights
    typedef std::vector< std::vector< std::vector<LD> > > vector3;
    vector3 weights;



    // constructor
    FFANN(){};
    FFANN(int inputs, int outputs, std::vector<int> hidden_nodes, 
                Func hidden_activation, Func output_activation);
    // destructor
    ~FFANN();



};


// for random number generation (for initialization) 
// std::default_random_engine RndE;
// std::uniform_real_distribution<LD> UnDist;




#endif