#include<iostream>
#include<cmath>
#include<vector>
#include<array>
#include <iomanip>
#include <string>
#include <fstream>



#include"SGD.hpp"
#include"TargetFunc.hpp"




#ifndef LONG
#define LONG long
#endif

#define LD LONG double


using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::vector;
using std::array;


using Func= LD(*)(LD);


LD Q_i(LD signal, LD target){
    return (signal-target)*(signal-target);
}

LD dQds_i(LD signal, LD target){
    return 2*(signal-target);
}


int main(){
   


    vector<vector<LD>> logT;
    vector<vector<LD>> rdofs;
    
    LD tmp1,tmp2;
    std::ifstream data_file("eos2020.dat");


    while (true){
        data_file>>tmp1;
        logT.push_back(vector<LD>{std::log10(tmp1)});
        
        data_file>>tmp1;
        data_file>>tmp2;
        rdofs.push_back(vector<LD>{tmp1,tmp2});

        if (data_file.eof()){
            break;
        }
    }
    
  
    return 0;
}