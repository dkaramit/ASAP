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

// #define solve1 //run Solve_LU test

// #define solve2 //run Solve_LU test


int main(){


    #ifdef indmax
        double x[]={2,1,-1,2,50};
        cout<<ind_max(x,5)<<endl;
    #endif

    #ifdef sum
        double x[]={2,1,-1,2,50};
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




    #ifdef solve1
    const int N=5;
    double M[N][N]={
         {0.40159364,  0.32094061,  0.69554368, -1.46788294,  0.31754238},
         {1.30662477, -1.29422933,  0.77316538, -1.83261438, -0.36165635},
         {1.13756882, -0.65142612, -1.23842557,  1.48034819,  0.57225863},
         {1.19055214, -1.52738081, -0.56730578,  1.95834064, -1.35751361},
        {-1.18756365,  0.97853745, -0.20522354,  0.19807196,  0.97076954}
        };

    double b[N]={-6.34562812e-4,  2.12436761e0, -3.78934624e0, -6.31371305e0,-5.12400233e0};


    int P[N];
    double L[N][N], U[N][N],x[N];

    LUP<N>(M,L,U,P);
    Solve_LU<N>(L,U,P,b,x);

    for( double l : x ){ cout<< l <<' ';}
    cout<<endl;
    
    #endif

    #ifdef solve2
    const int N=2;
    double M[N][N]={
        {1.,0.1},
        {1.,0.2}
    };

    double b[N]={1.,.2};


    int P[N];
    double L[N][N], U[N][N],x[N];

    LUP<N>(M,L,U,P);
    Solve_LU<N>(L,U,P,b,x);

    for( double l : x ){ cout<< l <<' ';}
    cout<<endl;
    
    #endif

    

    return 0;
}