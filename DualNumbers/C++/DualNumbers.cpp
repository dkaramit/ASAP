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
    DualNumbers<LD> x(1.33,vector<LD>{1,0});//this is a variable
    DualNumbers<LD> y(2.5,vector<LD>{0,1});//this is another variable

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
    cout<<dual::sin(x)<<endl;
    cout<<dual::cos(x)<<endl;
    cout<<dual::exp(x)<<endl;
    cout<<dual::log(x)<<endl;
    cout<<dual::log10(x)<<endl;
    cout<<dual::sqrt(x)<<endl;
    cout<<dual::tan(x)<<endl;
    cout<<dual::tanh(x)<<endl;

    cout<<"-----------Pows-----------"<<endl;
    cout<<dual::pow(x,y)<<endl;
    cout<<dual::pow(x,1.25)<<endl;
    cout<<dual::pow(1.25,y)<<endl;

    cout<<"-----------Chaos-----------"<<endl;
    cout<< dual::log10((dual::pow(x*x,dual::sin(y)/x)+x*y+3)*dual::exp(-2*x - dual::pow(y,2.))) <<endl;

    return 0;
}