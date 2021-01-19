#ifndef SA_class
#define SA_class

#define SA_Template template<class LD, class Func>
#define SA_Namespace SimulatedAnnealing<LD,Func>


SA_Template
class SimulatedAnnealing{
    public:
    // These are the inputs
    Func func;
    // LD region[dim][2];
    std::vector<std::array<LD,2>> region;

    std::vector<LD> x, sigma;
    LD  T, k, MinT,  tol , p0 ,k0;
    int IterationT, N0, Nstar;


    // variables we'll need 
    std::vector<LD> xnew, xmin,_x;
    LD E,Enew,Emin;
    LD AccProb, dx;
    LD T0;
    unsigned int dim;
    
    // define these for monitoring 
    std::vector<LD> ListProb,ListE,ListEmin;
    
    // not sure if this is helpful
    // std::vector<LD> points[dim];

    // for random number generation (assume uniform distribution) 
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    std::normal_distribution<LD> NGauss;


    SimulatedAnnealing(Func func, std::vector<std::array<LD,2>> region,
    std::vector<LD> x0 ,  LD T0, LD k, int IterationT, LD MinT, std::vector<LD> sigma, LD tol, int Nstar, 
    LD p0, int N0, LD k0 );
    ~SimulatedAnnealing();



    LD  Random(int d);
    LD Random( );
    LD mod(LD x,LD y); //c++ has issues with mod...
    void PickNeighbour();
    void nextT();
    void runT();
    LD BoltzmannP();
    void InitT();

    void run(bool CList, bool restart);
 


};












#endif