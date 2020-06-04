#include<iostream>
#include<cmath>
#include<algorithm>

#include "LU.hpp"


#define LD  long double

using std::cout;
using std::endl;
int main() {

    
    // run "runs" tests of Inverse_LUP and Solve_LUP (of M*x=b) with random M and b of dimension N (and elements between -50 and 50).
    // At the end it prints the maximum error (should be smaller than ~10^-10)   
    int runs=1000;
    const int N=50;


    LD err[runs];
    LD err_inv[runs];


    LD M[N][N], b[N],x[N],invM[N][N],R[N][N];
    LU<LD,N> lup(M);


    LD Unit[N][N]={0};
    for (int i = 0; i < N; i++) { for (int j = 0; j < N; j++)  {Unit[i][i]=1;} } 
    LD tmp[N];        
    LD tmpE,tmpI;

        for(int _r=0; _r<runs ; _r++){
            for (int i = 0; i < N; i++) { for (int j = 0; j < N; j++)  {
                
                lup.M[i][j]= ( rand()/ ((LD) RAND_MAX ) -0.5 ) *100 ;  } 

                b[i]= (rand()/ ((LD) RAND_MAX ) -0.5 ) *100 ;  
            } 
        
            lup.Dec_LUP();
            lup.Solve_LUP(b,x);
            lup.Inverse_LUP(invM);

            err[_r]=0;
            lup.dot(lup.M,x,tmp);
            lup.dot(lup.M,invM,R);


            for (int i = 0; i < N; i++){
                tmpE= fabs((tmp[i] - b[i])/b[i]) ;
                if(tmpE>err[_r] ) {err[_r] = tmpE ;}

            }
            for(int i=0; i<N; ++i){
                for(int j=0; j<N; ++j){
                    tmpI=fabs(R[i][j]-Unit[i][j]);
                    err_inv[_r] = tmpI ;
                }
            }
        
        
        }



        cout<<"Maximum error in Solve_LUP "<<*(std::max_element((err), (err+runs)))<<endl;
        cout<<"Maximum error in Inverse_LUP "<<*(std::max_element((err_inv), (err_inv+runs)))<<endl;



    return 0;
}