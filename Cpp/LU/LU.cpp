#include "include/LU_head.h"
#include <algorithm>

//Solve A*x=c
int main()
{
    //N=# equations
    const int N=500;

    //Coefficient matrix (A)
    double *A=new double[N*N];
    //Unknown vector (x)
    double *x=new double[N];
    //RHS (c)
    double *c=new double[N];

    //fill A and c
    for(int i=0 ;i<N;i++){ for(int j=0 ; j<N; j++){ A[N*i+j]=std::rand()*1.e-6  ;}  }
    for(int i=0 ;i<N;i++) {c[i]= std::rand()*1.e-6 ;  }

    //Define L,U,P matrices
    double *L=new double[N*N];
    double *U=new double[N*N];
    int *P=new int[N*N];

    //Performe LU decomposition
    LUP_dec(A,L,U,P,N,true);

    //Solve A*x=c using L,U,P
    Solve_LU(L,U,P,c,N,x);

    //Print the result
    //PrintMat(x,N);



    //check the result
    //print A*x-c if A*x-c>10^-10
    double *b=new double[N*N];
    dotMV(A,x,b,N);


    //Check the result
    for(int i=0;i<N;i++){
        double kk = b[i]-c[i];
        if (kk>1.e-10){cout << kk<<endl;}
        }

    //the maximums of the inputs are:
    cout << *max_element(c,c+N) <<"\t \t"<< *max_element(A,A+N*N)<< '\n';
    //Remember that c (and A) are pointers. So, c points to the first memory location and c+(N-1) to the last.

    return 0;
}
