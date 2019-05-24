#ifndef LU_HEADERS_H_INCLUDED
#define LU_HEADERS_H_INCLUDED

#include <iostream>
#include <iomanip>
//#include <complex>
#include <cmath>
#include <cstdlib>
using namespace std;

//================================================================\\

template <class T1>
void PrintMat(T1 * A, int N,int Ncols=1){
    int s=0;
    for(int i=0 ;i<N;i++){
            s++;
            cout<<A[i]<<" ";
            if(s==Ncols){cout<<endl;s=0;}
            }

}
//================================================================\\


//================================================================\\

template <class T1>
int argmax(T1* A, int N ){
    T1 Max=A[0];
    int ArMax=0;
    for(int i=0 ; i<N; i++){
                if(A[i]>Max){Max=A[i]; ArMax=i;}

        }

    return ArMax;
}
//================================================================\\

//================================================================\\

void eye (int *I , int N) {
    int e;
    for(int i=0 ; i<N; i++){
    for(int j=0 ; j<N; j++){
        if (i==j){e=1;}
        if (i!=j){e=0;}
        I[N*i+j]=e;
        }

    }

}
template <class T1>
void zeros (T1 *I , int N) {
    int e;
    for(int i=0 ; i<N; i++){
    for(int j=0 ; j<N; j++){
        I[N*i+j]=(T1)0;
        }

    }

}


template <class T1>
void zerosV (T1 *I , int N) {
    int e;
    for(int i=0 ; i<N; i++){
       I[i]=(T1)0;
     }

}
//================================================================\\


//================================================================\\

template <class T1>
void pivot_matrix(T1 *A, int *P, int N){
    /*Returns the pivoting matrix (P--permutation of rows) for A, so that
    the largest element of each column is in the diagonal.*/

    T1* col = new T1[N];
    eye(P,N);
    for (int c=0 ; c<N; c++){
        for (int j =0 ; j<N; j++){
                if(j<c){col[j]=0;}
                if(j>=c){col[j]=abs(A[N*j+c]);}


            }

            int col_max = argmax(col,N);
            if (c != col_max){
            int tmp[N];
            for(int j =0 ; j<=N; j++){ tmp[j]=P[N*c+j];  }
            for(int j =0 ; j<N; j++){ P[N*c+j]=P[N*col_max+j];   }
            for(int j =0 ; j<N; j++){ P[N*col_max+j]=tmp[j];   }
            }

    }

delete[] col;
}
//================================================================\\

template <class T1, class T2, class T3>
void dot(T1 *A, T2 *B , T3 *R, int N){

    for (int i=0; i<N; i++ ) {
            for (int k=0; k<N; k++ ) {
                T3 s=0;
                for (int j=0; j<N; j++ ) {
                s+=A[N*i+j]*B[N*j+k];
                }
                R[N*i+k]=s;

            }

        }

}
//================================================================\\

template <class T1, class T2, class T3>
void dotMV(T1 *A, T2 *c , T3 *b, int N){

    for (int i=0; i<N; i++ ) {
                T3 s=(T3)0.;
                for (int j=0; j<N; j++ ) {
                    s=s+A[N*i+j]*c[j];

                    }


                b[i]=s;

        }


}


//================================================================\\

template <class T1>
void LUP_dec(T1 *M, T1 *L, T1 *U, int *P, int N, bool pivot=true){

    if (pivot==true){ pivot_matrix(M,P,N); }
    else { eye(P,N); }

    T1 *A= new T1[N*N];

    dot(P,M,A,N);

    zeros(L,N);
    zeros(U,N);
    for (int j=0 ; j<N;j++  ) {
        L[N*j+j] = (T1) 1. ;

        for (int i=0 ; i<j+1 ; i++ ){
            T1  s1= (T1) 0.;
            for (int k=0; k<i; k++ ){  s1+=U[N*k+j] * L[N*i+k]; }
                U[N*i+j] = (A[N*i+j] - s1);

        }

        for (int i=j ; i<N ; i++ ){
            T1  s2= (T1) 0.;
            for (int k=0; k<j;k++ ){ s2+=U[N*k+j] * L[N*i+k]; }
            L[N*i+j] = (A[N*i+j] - s2) / U[N*j+j];

        }


    }

}
//================================================================\\



//================================================================\\

//template <class T1,class T2,class T3>
template <class T1>
void Solve_LU(T1 *L,T1 *U, int *P,T1 *c, int N, T1 *x){
    T1 *b=new T1[N];
    dotMV(P,c,b,N);
    T1 *d=new T1[N];
    zerosV(d,N);


    d[0]=b[0];
    for(int i=0;i<N;i++){
        T1 s= (T1) 0.;
        for (int j=0 ; j<i ; j++){s=s+ L[N*i+j]*d[j]; }
        d[i]=b[i]-s;
    }

    x[N-1]  = d[N-1]/U[N*(N-1)+N-1];
    for(int i=N-2; i>-1; i-- ) {
        T1 s= (T1) 0.;
        for (int j=i+1 ; j<N ; j++){s=s+ U[N*i+j]*x[j] ; }
        x[i]=(d[i] - s )/U[N*i+i];
     }


delete[] b;
delete[] d;

//return x;
}
//================================================================\\




#endif // HEADERS_H_INCLUDED
