#ifndef LU_class
#define LU_class

#define LU_template template<class LD,int N>

#define LU_namespace LU<LD,N>


LU_template
class LU{
    private:

    public:
    LD M[N][N];
    LD L[N][N];
    LD U[N][N];
    int P[N];

    LU(){};
    LU(LD (&M)[N][N]){ 
        for(int i=0 ; i<N ; ++i){
            for(int j=0 ; j<N ; ++j){
                this->M[i][j]=M[i][j];
            }
        }
     };
    ~LU(){};

    int ind_max(LD  *row, int len);

    // in misc
    void index_swap(LD *A, int index_1, int index_2);
    void index_swap(int *A, int index_1, int index_2);
    void apply_permutations_vector(LD *A,  LD *Ap);
    void dot(LD (&A)[N][N] ,LD (&B)[N][N], LD (&R)[N][N] );
    void dot(LD (&A)[N][N] ,LD (&x)[N], LD (&b)[N] );
    
    // main member functions
    void Dec_LUP( LD _tiny=1e-25);
    void Solve_LUP(LD (&b)[N] , LD (&x)[N] );
    void Inverse_LUP(LD (&invM)[N][N] );




};





#endif