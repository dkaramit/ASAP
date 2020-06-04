#ifndef LU_inv
#define LU_inv
#include"LU_Class.hpp"



/*  ------------------------------------------Inverse_LUP-------------------------------------------------------------- */

LU_template
void LU_namespace::Inverse_LUP(LD (&invM)[N][N] ){
    /*
    Finds the Inverse matrix given its LU decomposition.
    Basically this solves M*M^{-1}=1

    Input:
    L,U,P= LUP decomposition of M, which is the output of the function LUP.

    N=dimension of the matrix (N*N)

    invM=an array to store the solution inverse matrix.
    */    

    //     
    LD e[N];
    for(int i=0 ; i< N ; ++i){ e[i]=0; } 
    LD x[N];

    for(int i=0 ; i< N ; ++i){
        e[i]=1;
        Solve_LUP(e,x);

        for(int j=0 ; j<N ; ++j){
            invM[j][i]=x[j];
        }

        e[i]=0;
    }
}







#endif