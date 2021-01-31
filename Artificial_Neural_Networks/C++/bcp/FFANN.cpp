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
    FFANN<LD,func> brain(2, 1, std::vector<int>{3,4}, std::vector<func>{lin,lin,lin} );
    
    // set all parameters to zero    
    brain.init_params(0,0);


    // set some non-zero weights to check the result
    brain.update_weight(0,2,0,1);
    brain.update_weight(0,1,0,1);
    brain.update_weight(0,0,0,1);
    brain.update_weight(0,1,1,1);
    brain.update_weight(1,0,1,2);
    brain.update_weight(1,1,2,2);
    brain.update_weight(1,1,1,2);
    brain.update_weight(2,0,0,1);

    brain.update_bias(0,2,1);
    brain.update_bias(0,1,1);
    brain.update_bias(1,1,1);
    brain.update_bias(1,0,-2);
    // set the input
    brain.input_signal(std::vector<LD>{1.33,2});
    // feed-foraward
    brain.feed_forward();

    // print the everything
    brain.print_weights();
    cout<<"----------------"<<endl;
    brain.print_biases();
    cout<<"----------------"<<endl;
    brain.print_signals();
    cout<<endl<<"----------------"<<endl;


    // this is how you read and write to vector
    std::vector<LD> X;

    brain.write_params(&X);

    for(auto x:X){cout<<x<<" ";}
    cout<<endl<<"----------------"<<endl;

    X[0]=666;
    X[1]=32;
    X[2]=-32;
    X[3]=-3200;
    X[4]=-0.5;
    X[5]=-368;

    brain.read_params(&X);
    cout<<brain.biases[0][0]<< endl; //X[0]
    
    cout<<brain.weights[0][0][0]<< endl; //X[1]
    cout<<brain.weights[0][0][1]<< endl; //X[2]
    
    cout<<brain.biases[0][1]<< endl; //X[3]

    cout<<brain.weights[0][1][0]<< endl; //X[4]
    cout<<brain.weights[0][1][1]<< endl; //X[5]

    return 0;
}