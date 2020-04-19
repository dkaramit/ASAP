#ifndef VEGAS_class
#define VEGAS_class

// Just a thought: use different number of points for the wheights, and different for the integral.


// for memset:
#include<cstring>

// define some macros


#define VEGAS_Template template<class LD, class Func, int NDim, int NBin>
#define VEGAS_Namespace VEGAS<LD,Func,NDim,NBin>



//Pass Dimention and number of bins in template, to make the code clearer (I think its faster than using new).   
VEGAS_Template
class VEGAS{
    public:
        


        Func Integrand;
        int NPoints,NBatches,NAdapts,AdaptPoints;
        LD  constK, alpha ;

        // Notice that N number of bins need N+1 points to be defined
        LD Grid[NDim][NBin+1];
        LD weights[NDim][NBin];


        std::random_device RndDiv;
        std::default_random_engine RndE;
        std::uniform_real_distribution<LD> UnDist;
        std::uniform_int_distribution<> UnInt;


        VEGAS( Func function, int NPoints, int NBatches, 
        int NAdapts, int AdaptPoints, int constK=1, LD alpha=0.9);
        ~VEGAS(){};

        //get a random point in [min,max]
        LD Random(LD min , LD max);
        // get random bin in NDimention NDim
        int RandomBin();



        // Claculate the partial integrals. Returns \int|f|*NPoints. This is what we need to 
        // get the regulated weights. 
        LD PartialIntegrals();
        // Update the weights
        void UpdateBins();

        // take the integral in [0,1]
        LD IntegrateTot();
        void IntegrateTot(LD *IntMean, LD *IntVariance);

        // Use this to take batches. IntMean is the result, IntSigma is sqrt(Var).
        // It returns chi^2/(NBathes-1) which should be close to 1.
        LD IntegrateBatch(LD *IntMean, LD *IntSigma);

        // Combine everything together. First adapt, and then run  IntegrateBatch
        LD Integrate(LD *IntMean, LD *IntSigma);



        //---These are for the auxiliary functions. You can remove them with no effect.
        
        // prints binpoints of NDim
        void PrintGrid(int dim);
        // prints all binpoints
        void PrintGrid();
        
        // 
        void PrintDist();

        void PrintWeights();
        
        // Calculate the  weights. Just to check that the algorithm works. In practice we only need the partial integrals.
        LD CalculateWeights();
        // check that the sum of wieghts in each dimension is 1; (this is in CalcWeights-Check.hpp)
        void CheckWeights();
};

#endif