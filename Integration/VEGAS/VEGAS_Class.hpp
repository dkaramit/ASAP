#ifndef VEGAS_class
#define VEGAS_class


// define some macros
#define VEGAS_Template template<class LD, class Func, int Dim, int Nbins>
#define VEGAS_Namespace VEGAS<LD,Func,Dim,Nbins>



//Pass Dimention and number of bins in template, to make the code clearer (I think its faster than using new).   
VEGAS_Template
class VEGAS{
    public:
        


        Func Integrand;
        LD rel_var, max_iterations;

        int PointsPerBin,NPoints;
        // Notice that N number of bins need N+1 points to be defined
        LD Grid[Dim][Nbins+1];

        std::random_device RndDiv;
        std::default_random_engine RndE;
        std::uniform_real_distribution<LD> UnDist;
        std::uniform_int_distribution<> UnInt;


        VEGAS( Func function, int PointsPerBin ,int NPoints);
        ~VEGAS(){};

        //get a random point in [min,max]
        LD Random(LD min , LD max);
        // get random bin in dimention dim
        int RandomBin(int dim);


        /*----I don't think we'll need  Sample, SampleBin, and Distribution----*/
        //take a sample according to the Grid. Returns the point as an array  point[Dim]
        void Sample(LD point[Dim]);
        //take a sample according to the Grid excluding dim (we could overload Sample, but it is more clear this way). 
        void SampleDim(int dim , LD point[Dim-1]);
        // The Gid defines a distribution. In order to apply Monte Carlo, we need to find the value of this 
        // distribution at a given point.
        LD Distribution( LD point[Dim] );
        /*------------------------------------------------------------------------------*/


        // Calculate the integral in the subvilume volume defined by removing the dimention dim (at a given x for this dim).
        //  Basically this caclulates \int_0^1 d^{dim}t f( \vec{t} )  \delta( t_{dim} - x ) ,  
        LD IntegrateDim(int dim ,   LD x  );
        
        // Calculate the 1-D integral of dim in bin at a given point for the other dimentions 
        LD Integrate1D(int dim , int bin , LD point[Dim] );
        
        // Overloaded Integrate1D.
        // Calculate the 1-D integral of dim at a given point for the other dimentions.
        // Sums all bins  in Integrate1D(int dim , int bin , LD point[Dim] )
        LD Integrate1D(int dim  , LD point[Dim] );

        //---These are for the auxiliary functions. You can remove them with no effect.
        
        // prints binpoints of dim
        void PrintGrid(int dim);
        // prints all binpoints
        void PrintGrid();




};

#endif