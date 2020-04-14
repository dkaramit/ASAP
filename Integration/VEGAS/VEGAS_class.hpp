#ifndef VEGAS_class
#define VEGAS_class


// define some macros
#define VEGAS_Template template<class LD, class Func, int Dim, int Nbins>
#define VEGAS_Namespace VEGAS<LD,Func,Dim,Nbins>



//Pass Dimention and number of bins in template, to make the code clearer (I think its faster than using new).   
VEGAS_Template
class VEGAS{
    public:
        int Points_per_bin;
        LD Grid[Dim][Nbins];
    VEGAS(int NPoints);
    ~VEGAS(){};




    void PrintGrid(int dim);
    void PrintGrid();
};

#endif