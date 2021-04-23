#include<iostream>
#include<vector>
#include<cmath>

#include"DualNumbers.hpp"

using std::cout;
using std::endl;


#ifndef LONG
    #define LONG
#endif

#define LD LONG double




int main(){
    DualNumbers<LD> x(1,std::vector<LD>{1,0});//this is a variable
    DualNumbers<LD> y(2,std::vector<LD>{0,1});//this is another variable
    DualNumbers<LD> u(0,2);//this is a constant
    

    cout<<"----------------------"<<endl;
    cout<<x+y<<endl;
    cout<<x+1.25464565<<endl;
    cout<<1.25464565+x<<endl;


    cout<<"----------------------"<<endl;
    cout<<x-y<<endl;
    cout<<x-1.25464565<<endl;
    cout<<1.25464565-x<<endl;

    cout<<"----------------------"<<endl;
    cout<<x*y<<endl;
    cout<<x*2.5<<endl;
    cout<<2.5*x<<endl;


    
    
    
    cout<<"----------------------"<<endl;
    cout<<1.5+x-y+2+x<<endl;
    cout<<-(1.5+x-y+2+x)<<endl;
    cout<<2*(1.5+2*x-y*3+2+x)*4*x<<endl;

    return 0;
    
}