#ifndef SA_class
#define SA_class

#define SA_Template template<class LD, class Func>
#define SA_Namespace SimulatedAnnealing<LD,Func>


SA_Template
class SimulatedAnnealing{
    public:
    // These are the inputs
    Func func;
    std::vector<std::array<LD,2>> region;

    std::vector<LD> x, sigma;
    LD  T, k;


    // variables we'll need 
    std::vector<LD> xnew, xmin,_x;
    LD E,Enew,Emin;
    LD AccProb, dx;
    LD T0;
    unsigned int dim;
    
    // define these for monitoring 
    std::vector<LD> ListProb,ListE,ListEmin;
    
    // for random number generation (assume uniform distribution) 
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;
    std::normal_distribution<LD> NGauss;


    SimulatedAnnealing(Func func, std::vector<std::array<LD,2>> region,
    std::vector<LD> x0 ,  LD T0, std::vector<LD> sigma);
    ~SimulatedAnnealing();



    LD  Random(int d);
    LD Random( );
    LD mod(LD x,LD y); //c++ has issues with mod...
    void PickNeighbour();
    void nextT(LD k);
    void runT(int IterationT);
    LD BoltzmannP();
    void InitT(int IterationT, int N0, int k0, LD p0);

    void run(bool CList, LD tol, LD MinT, LD k=1-1e-2,LD Nstar=5000, int IterationT=100,
            int N0=500, int k0=1+1e-2, LD p0=0.8);
 


};












#endif