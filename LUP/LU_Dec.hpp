#ifndef LU_dec
#define LU_dec
#include"LU_Class.hpp"


/*  ------------------------------------------ind_max-------------------------------------------------------------- */
LU_template
void LU_namespace::Dec_LUP( LD _tiny){
    
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
    LD _col[N],tmpU[N],tmpL[N];
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


#endif