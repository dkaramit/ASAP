#include<iostream>
#include "LU.hpp"


using std::cout;
using std::endl;


// #define indmax // run ind_max test

// #define swap //run index_swap test

// #define sum //run Som test

// #define map //run Som test

// #define perm //run permutation test

// #define lup //run LUP test

int main(){

    double x[]={2,1,-1,2,50};

    #ifdef indmax
        cout<<ind_max(x,5)<<endl;
    #endif

    #ifdef sum
    
        cout<<Sum(x,5)<<endl;
    #endif
    
    #ifdef swap
        index_swap(x,4,1);
        for( double i : x ){ cout<<i<<endl;}
    #endif
    

    #ifdef perm
        double A[]={1,2,5,8,3};
        int P[]={2,4,0,3,1};

        double Ap[5];

        apply_permutations_vector(A,P,5,Ap);
        for( int i =0 ; i<5 ; i++){ cout<<A[i]<<" ";}
        cout<<endl;
        for( int i =0 ; i<5 ; i++){ cout<<Ap[i]<<" ";}
        cout<<endl;
    #endif

    #ifdef map
        auto F = [](double X) { return X*X; };
        double L[]={1,2,3,4,5};
        double FL[5];
        Map(F, L, 5, FL);
        for( double i : FL ){ cout<< i <<endl;}
    #endif



    #ifdef lup
    const int N=5;
    double M[N][N]={
    { 0,  2,  2 , 3 , 5},
    {-3, -1,  1 , 5 , 9},
    { 1, -1,  1 , 4 , 7},
    { 1, -1,  1 , 0 , 2},
    { 1, -1,  1 , 0 , 3}
    };


    int P[N];
    double L[N][N], U[N][N];

    LUP<N>(M,L,U,P);

    for( double i : P ){ cout<< i<<' ';}
    cout<<endl;
    cout<<endl;
    cout<<endl;

    for (int i = 0; i < N; i++) {
    
    for (int j = 0; j < N; j++) {
        cout<< U[i][j]<<"\t";

    }
    cout<<endl;
    }
    cout<<endl;
    cout<<endl;

    for (int i = 0; i < N; i++) {
    
    for (int j = 0; j < N; j++) {
        cout<< L[i][j]<<"\t";

    }
    cout<<endl;
    }
    #endif





    

    return 0;
}