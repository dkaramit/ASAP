#ifndef LU_solve
#define LU_solve
#include"LU_Class.hpp"


/*  ------------------------------------------Solve_LUP-------------------------------------------------------------- */

LU_template
void LU_namespace::Solve_LUP(LD (&b)[N] , LD (&x)[N] ){
    /*
    This solves M*x=b
    Input:

    b=the right hand side of the equation

    x=an array to store the solution of M*x=b
    */    

    LD d[N], bp[N];
    LD tmps=0;

    apply_permutations_vector(b,bp);


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


#endif