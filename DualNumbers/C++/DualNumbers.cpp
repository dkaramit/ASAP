#include<iostream>
#include<vector>
#include<cmath>

#include"DualNumbers.hpp"

using std::cout;
using std::endl;
using std::vector;



#ifndef LONG
    #define LONG
#endif

#define LD LONG double



int main(){
    DualNumbers<LD> x(1,vector<LD>{1,0});//this is a variable
    DualNumbers<LD> y(2,vector<LD>{0,1});//this is another variable

    cout<<"----------ADD------------"<<endl;
    cout<<x+y<<endl;
    cout<<x+1.25464565<<endl;
    cout<<1.25464565+x<<endl;


    cout<<"-----------SUB-----------"<<endl;
    cout<<x-y<<endl;
    cout<<x-1.25464565<<endl;
    cout<<1.25464565-x<<endl;

    cout<<"----------MUL------------"<<endl;
    cout<<x*y<<endl;
    cout<<x*2.5<<endl;
    cout<<2.5*x<<endl;

    cout<<"-----------DIV-----------"<<endl;
    cout<<x/y<<endl;
    cout<<x/2.5<<endl;
    cout<<2.5/x<<endl;

    cout<<"-----------Func-----------"<<endl;
    cout<<std::sin(std::cos(x))+std::cos(y)<<endl;

    return 0;
    
}