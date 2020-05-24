#ifndef SA_class
#define SA_class

#define SA_Template template<class LD, class Func, const int dim>
#define SA_Namespace SimulatedAnnealing<LD,Func,dim>


SA_Template
class SimulatedAnnealing{
    public:
    // These are the inputs
    Func func;
    LD region[dim][2];

    LD x[dim], sigma[dim];
    LD  T, k, MinT,  tol , p0 ,k0;
    int IterationT, N0, Nstar;


    // variables we'll need 
    LD xnew[dim], xmin[dim],_x[dim];
    LD E,Enew,Emin;
    LD AccProb, dx_min,dx_max;
    LD T0;

    // define these for monitoring 
    std::vector<LD> ListProb,ListE,ListEmin;
    
    // not sure if this is helpful
    // std::vector<LD> points[dim];

    // for random number generation (assume uniform distribution) 
    std::random_device RndDiv;
    std::default_random_engine RndE;
    std::uniform_real_distribution<LD> UnDist;


    SimulatedAnnealing(Func func, LD region[dim][2],
    LD x0[dim] ,  LD T0, LD k, int IterationT, LD MinT, LD sigma[dim], LD tol, int Nstar, LD p0, int N0, LD k0 );
    ~SimulatedAnnealing();



    LD  Random(int d);
    LD Random( );
    void PickNeighbour();
    void nextT();
    void runT();
    LD BoltzmannP();
    void InitT();

    void run(bool CList, bool restart);
 


};












#endif