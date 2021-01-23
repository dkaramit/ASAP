#include<iostream>
#include<vector>

// #include"SGD.hpp"

// #include"VanillaGD.hpp"

// #include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;




// using func= vector<LD>& LD(*)(vector<LD> &x);

vector<LD>& f(const vector<LD> &x, vector<LD>& y){    
    y.resize(5);
    y[0]=x[0]+x[1];

    return y;
    }



int main(){

    // targetFunc<LD,func> target(f,{0,1});
    vector<LD> x,y;
    x={0,1};
    
    y=f(x,y);
    
    cout<<y[0]<<endl;
    cout<<y[1]<<endl;
    cout<<y[2]<<endl;
    cout<<y[3]<<endl;
    cout<<y[4]<<endl;

    return 0;
}