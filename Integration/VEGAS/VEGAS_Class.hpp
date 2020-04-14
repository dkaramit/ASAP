#ifndef VEGAS_class
#define VEGAS_class


// define some macros
#define VEGAS_Template template<class LD, class Func, int Dim, int Nbins, int PointsPerBin>
#define VEGAS_Namespace VEGAS<LD,Func,Dim,Nbins,PointsPerBin>



//Pass Dimention and number of bins in template, to make the code clearer (I think its faster than using new).   
VEGAS_Template
class VEGAS{
    public:
        std::random_device RndDiv;

        std::default_random_engine RndE;
        std::uniform_real_distribution<LD> UnDist;

        LD rel_var, max_iterations;


        int NGridPoints;
        // Notice that N number of bins need N+1 points to be defined
        LD RandPoints[Nbins][PointsPerBin];
        LD Grid[Dim][Nbins+1];

        VEGAS(int NPoints);
        ~VEGAS(){};

        //get a random point in [min,max]
        LD Random(LD min , LD max);
        
        // sample for dimention-dim  
        void RandomGrid(int dim);

        // Calculate the integral of one bin of dim (and in the entire [0,1] for other dims)
        LD BinIntegrate(int dim , int bin);

        //---These are for the auxiliary functions. You can remove them with no effect.
        // prints binpoints of dim
        void PrintGrid(int dim);
        // prints all binpoints
        void PrintGrid();

        void PrintRandomGrid();// Prints RandPoints.
        int last_dim;//get the last  dimention to get RandomGrid
        
        // Calculate the mean of RandPoints[last_dim][bin]
        LD BinMean(int bin);
        void PrintMeans(); // Print the means


};

#endif