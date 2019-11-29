#ifndef Ros_calc_k
#define Ros_calc_k
#include "Ros_class.hpp"
#include "Jacobian/Jacobian.hpp"
#include "LU/LU.hpp"


/*-----------------------Begin: calc_k---------------------------------*/
template<class diffeq, class Array ,class Matrix, class RK_method, class jacobian>
void Ros<diffeq, Array,Matrix, RK_method, jacobian>::calc_k(){
    Array _dfdt;
    Matrix _J;

            
    for(int i=0; i<N_eqs ; i++){yn[i]=solution[i][current_step-1]; }
    Jac(_J,_dfdt,yn,tn);

    std::cout<<tn<<"\n";

    cout<<"----------------------------"<<endl;

    cout<<"dfdt=[";
    for(int i=0; i<N_eqs ; i++){  cout<<_dfdt[i]; if(i!=N_eqs-1){cout<<",";}   }
    cout<<"]"<<endl;


    cout<<"J=["<<endl;

    for (int i = 0; i < N_eqs; i++){
            cout<<"[";
        for (int j = 0; j < N_eqs; j++) {cout<<_J[i][j]; if(j!=N_eqs-1){cout<<",";} }
            cout<<"]";if(i!=N_eqs-1){cout<<",";}cout<<endl;
        
        
    }  
    cout<<"]"<<endl; 
            
          
}
/*-----------------------End: calc_k---------------------------------*/
#endif