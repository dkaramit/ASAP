#include<iostream>

#include"FFANN.hpp"


#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;

//both are the same
// typedef LD (*func)(LD) ;
using func= LD (*)(LD);

LD lin(LD x){return x;}


int main(){
    int _inputs=2;
    int _outputs=1;
    std::vector<int> hiddenL{3};

    FFANN<LD,func> brain(_inputs,_outputs,hiddenL,lin,lin);


    // for(int i:brain.nodes){cout<<i<<endl;}

    for(unsigned int  i=0; i<brain.signals.size();i++){
        cout<<i<<": "; for(LD _:brain.signals[i]){cout<<_<<"\t";}cout<<endl;
    }



    return 0;
}