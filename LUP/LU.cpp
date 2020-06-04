#include<iostream>
#include<cmath>
#include<algorithm>

#include "LU.hpp"


#define LD  long double

using std::cout;
using std::endl;
int main() {
    // dimension of the matrix
    const int N=3;

    // definition of the matrix
    LD M[N][N]={
        {3,0,1},
        {1,2,0},
        {5,2,3}    
    };

    // the coefficient
    LD b[N]={-1,0,2};
    
    // array to hold the solution of M x = b
    LD x[N];

    // array to hold the inverse
    LD invM[N][N];

    LU<LD,N> lup(M);
    
    // first you have to decompose!
    lup.Dec_LUP();

    // then you can do this
    lup.Solve_LUP(b,x);
    lup.Inverse_LUP(invM);


    // print the inverse. it should be:
    // 
    // 
    //    invM={
    //     {0.6, 0.2, -0.2},
    //     {-0.3, 0.4, 0.1},
    //     {-0.8, -0.6, 0.6}
    //     }
    //  
    for (int i = 0 ; i < N; i++){
        for (int j = 0 ; j < N; j++){
            cout<<invM[i][j]<<" ";
        }
        cout<<endl;
    }
    
    // print the solution of M x = b. It should be:
    // 
    // x={ -1, 0.5, 2 } 
    // 
    for(LD _x:x){cout<<_x<<" ";}
    cout<<endl;
    
}