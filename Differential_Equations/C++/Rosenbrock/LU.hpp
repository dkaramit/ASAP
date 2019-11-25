#include<cmath>

/*---------------------Functions I need for LU decomposition-------------------------------------------------*/
int ind_max(double *row , int N){
    /*   
    Find the index of the maximum of a list (row) of lentgth N.
    */
    int _in=0;
    double _max = row[0];

    for (int  i = 1; i < N; i++)
    {
        if(row[i]>_max){_max=row[i]; _in=i; }
    }
    

    return _in;
}





void index_swap(double *A, int index_1, int index_2){

    /* 
        index_swap takes an array and interchanges 
         A[index_1] with A[index_2].
    */
    double tmp=A[index_1];
    A[index_1]=A[index_2];
    A[index_2]=tmp;


}


void index_swap(int *A, int index_1, int index_2){

    /* 
        index_swap takes an array and interchanges 
         A[index_1] with A[index_2].
    */
    int tmp=A[index_1];
    A[index_1]=A[index_2];
    A[index_2]=tmp;


}


void apply_permutations_vector(double *A, int *P, int N, double *Ap){
    /*
    Applies the permutations given by P from LUP
    to a list A of length N, and stores the result to Ap.
    
    Example:
    If we do this:

    double A[]={1,2,5,8,3};
    int P[]={2,4,0,3,1};

    double Ap[5];
    apply_permutations_vector(A,P,5,Ap)

    we get Ap={5,3,1,8,2}
    */

    for (int i = 0; i < N; i++){Ap[i]=A[ P[i] ];}

}

typedef  double (*FuncType)(double);
void Map(FuncType F, double *L, int N, double *FL){
    for (int i = 0; i < N; i++){ FL[i] = F(L[i]); }
    
}

/*--------------------------------------------------------------------------------------------------------------*/

/*-----------------------------LUP decompositioning--------------------------------------------------------*/

template<const int N>
void LUP(double (&M)[N][N], double (&L)[N][N] ,double (&U)[N][N], int (&P)[N], double _tiny=1e-25){
    
    // Initialize LU
    for (int  i = 0; i < N; i++){
        P[i]=i;
        for (int  j = 0; j < N; j++)
        {
        if(i==j){L[i][j]=1;}
        if(i!=j){L[i][j]=0;}
        U[i][j]=M[i][j];
        }
    }
    double _col[N],tmpU[N],tmpL[N];
    int len_col,pivot;
    

    for (int  k = 1; k < N; k++){ for (int  i = k; i < N; i++)
    {   
    
    for (int _r=k-1 ; _r<N ; _r++ ) { _col[_r-(k-1)]=fabs(U[_r][k-1]);  }//we need to convert the index of _col because we start the loop from k-1
    
    
    len_col=N-(k-1);
    pivot=ind_max( _col ,len_col) + k - 1;
    // std::cout<<pivot<<std::endl;

    if (fabs(U[pivot][k-1]) < _tiny)  {break;}

    if (pivot != k-1){ 
            
        index_swap(P,k-1,pivot);
        
        for (int _r=k-1 ; _r<N ; _r++ ) { tmpU[_r-(k-1)]= U[k-1][_r] ; }//we need to convert the index of tmpU because we start the loop from k-1

        for (int _r=k-1 ; _r<N ; _r++ ) { U[k-1][_r]=U[pivot][_r] ; }
        
        for (int _r=k-1 ; _r<N ; _r++ ) { U[pivot][_r]=tmpU[_r-(k-1)] ; }//we need to convert the index of tmpU because we start the loop from k-1

        for (int _r=0 ; _r<k-1 ; _r++ ) {tmpL[_r]= L[k-1][_r] ; }
        
        for (int _r=0 ; _r<k-1 ; _r++ ) {L[k-1][_r]=L[pivot][_r] ; }
        
        for (int _r=0 ; _r<k-1 ; _r++ ) {L[pivot][_r]=tmpL[_r] ; }
    }

    L[i][k-1]=U[i][k-1]/U[k-1][k-1];

    for (int j=k-1 ; j<N ; j++ ) {  U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j] ; }



    }}
    
}
/*-------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------Solve-LU----------------------------------------------------------*/
template<const int N>
void Solve_LU(double (&L)[N][N] ,double (&U)[N][N], int (&P)[N], double (&b)[N] , double (&x)[N] ){
    /*
    This solves M*x=b
    Input:
    L,U,P= LUP decomposition of M, which is the output of the function LUP.

    b=the right hand side of the equation
    N=the number of equations

    x=an array to store the solution of M*x=b
    */    

    double d[N], bp[N];
    double tmps=0;

    apply_permutations_vector(b,P,N,bp);


    d[0]=bp[0];

    for(int i=1; i<N  ; i++){
        tmps=0;
        for (int j = 0; j < i; j++){ tmps +=L[i][j]*d[j]; }
        
        d[i]=bp[i]-tmps;
    }
    


    x[N-1]  = d[N-1]/U[N-1][N-1] ;
    for (int i = N-2; i > -1; i--)
    {
        tmps=0;
        for (int j = i+1; j < N; j++){ tmps += U[i][j]*x[j];  }
        x[i]=(d[i]-tmps )/U[i][i];
    }

}
/*-------------------------------------------------------------------------------------------------------------------*/
