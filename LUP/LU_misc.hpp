#ifndef LU_misc
#define LU_misc
#include"LU_Class.hpp"


/*  ------------------------------------------ind_max-------------------------------------------------------------- */
LU_template
int LU_namespace::ind_max(LD *row, int len){
    /*   
    Find the index of the maximum of a list (row) of lentgth N.
    */
    int _in=0;
    LD _max = row[0];

    for (int  i = 1; i < len; i++)
    {
        if(row[i]>_max){_max=row[i]; _in=i; }
    }
    

    return _in;
}


/*  ------------------------------------------index_swap-------------------------------------------------------------- */
LU_template
void LU_namespace::index_swap(LD *A, int index_1, int index_2){

    /* 
        index_swap takes an array and interchanges 
         A[index_1] with A[index_2].
    */
    LD tmp=A[index_1];
    A[index_1]=A[index_2];
    A[index_2]=tmp;


}

/*  ------------------------------------------index_swap (for int)-------------------------------------------------------------- */
LU_template
void LU_namespace::index_swap(int *A, int index_1, int index_2){

    /* 
        index_swap takes an array and interchanges 
         A[index_1] with A[index_2].
    */
    int tmp=A[index_1];
    A[index_1]=A[index_2];
    A[index_2]=tmp;


}



/*  ------------------------------------------apply_permutations_vector-------------------------------------------------------------- */
LU_template
void LU_namespace::apply_permutations_vector(LD *A, LD *Ap){
    /*
    Applies the permutations given by P from LUP
    to a list A of length N, and stores the result to Ap.
    
    Example:
    If we do this:

    LD A[]={1,2,5,8,3};
    int P[]={2,4,0,3,1};

    LD Ap[5];
    apply_permutations_vector(A,P,5,Ap)

    we get Ap={5,3,1,8,2}
    */

    for (int i = 0; i < N; i++){Ap[i]=A[ P[i] ];}

}

/*  ------------------------------------------dot for matrices-------------------------------------------------------------- */
LU_template
void LU_namespace::dot(LD (&A)[N][N] ,LD (&B)[N][N], LD (&R)[N][N] ){
    /*
    Calculates the product of two matrices.
    R=A*B
    */

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            R[i][j]=0;
            for(int l=0; l<N; ++l){
                R[i][j] += A[i][l]*B[l][j];
            }
        }
    }
}

/*  ------------------------------------------dot for vector-------------------------------------------------------------- */
LU_template
void LU_namespace::dot(LD (&A)[N][N] ,LD (&x)[N], LD (&b)[N] ){
    /*
    Calculates the product of  matrix with vector.
    b=A*x
    */

    for(int i=0; i<N; ++i){
        b[i]=0;
        for(int j=0; j<N; ++j){
            b[i] += A[i][j]*x[j];
        }
    }
}






#endif