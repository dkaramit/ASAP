#include<iostream>


using namespace std;



int main (int argc, char* argv[]){
    int x=50;
    
    if (argc>1){
        x=atoi(argv[1]);

    }
    
    int y=0;
    for (int i=0 ; i<x*1e7 ; i++){
        y++;
    }

    cout<<x<<"  "<<y<<endl;


    return 0;
}