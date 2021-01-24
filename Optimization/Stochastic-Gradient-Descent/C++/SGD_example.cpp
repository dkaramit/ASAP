#include<iostream>
#include<vector>

#include"SGD.hpp"
#include"TargetFunc.hpp"

#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::vector;




using TFunc= void (*)(const vector<LD> &x, const vector<LD> &w, vector<LD> &y);

void testF(const vector<LD> &x, const vector<LD> &w, vector<LD> &y){
    y[0]=w[0]*x[0]+w[1];
    y[1]=w[0]+w[1]*x[1];
}

using QFunc= LD (*)(targetFunc<LD,TFunc> f, const vector<LD> &x, const vector<LD> &y);
LD MSE(targetFunc<LD,TFunc> f, const vector<LD> &x, const vector<LD> &y){
    vector<LD> fx=y;
    f(x,fx);

    LD sum=0;
    for(unsigned int  i=0; i<y.size(); ++i){
        sum+=(fx[i]-y[i])*(fx[i]-y[i]);
    }
    sum=sum/((LD) fx.size());

    return sum;    
}


int main(){
    
    targetFunc<LD,TFunc> target(testF,{1,10});
    lossFunc<LD,QFunc,targetFunc<LD,TFunc> > loss(MSE,target);


    vector<LD> x={0.2,-2.31};
    vector<LD> y={5,15};
    
    
    // cout<<MSE(target,x,y)<<endl;
    cout<<loss(x,y)<<endl;
    
    vector<LD> grad=x;
    loss.Grad(x,y,grad);
    cout<<grad[0]<<endl;
    cout<<grad[1]<<endl;



    return 0;
}