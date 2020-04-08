#include<iostream>
#include<cmath>

#include <chrono>

#include"trapz.hpp"
#include"misc.hpp"


#define LD  double


LD func( LD x){
    return pow(x-3 , 2 ) ;
}

int main(){



    int N_points=5000000;
    LD min=5;
    LD max=10;


    auto start = std::chrono::steady_clock::now();
    
    
    //--- use trapezoidal rule with the function---//
    std::cout<< trapezoidal<LD>(func,min,max,N_points) <<std::endl;

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    // define arrays to put the data
    LD *X = new LD[N_points];
    LD *Y = new LD[N_points];

    start = std::chrono::steady_clock::now();

    //--- use trapezoidal rule with linearly spaced points---//
    misc::linspace<LD>(min,max,N_points,X);    
    misc::map<LD>( X, func, N_points , Y);
    std::cout<< trapezoidal<LD>(X,Y,N_points) <<std::endl;

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    start = std::chrono::steady_clock::now();
    
    //--- use trapezoidal rule with log10-spaced points---//
    misc::logspace<LD>(log10(min),log10(max),N_points,X);    
    misc::map<LD>( X, func, N_points , Y);
    std::cout<< trapezoidal<LD>(X,Y,N_points) <<std::endl;
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    start = std::chrono::steady_clock::now();
    
    //--- use trapezoidal rule with log-spaced points---//
    misc::logspace<LD>( exp(1) ,log(min) ,log(max),N_points,X);    
    misc::map<LD>( X, func, N_points , Y);
    std::cout<< trapezoidal<LD>(X,Y,N_points) <<std::endl;
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}