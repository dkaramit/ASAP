#ifndef VEGAS_Rand
#define VEGAS_Rand
#include"VEGAS.hpp"


//This defines a function that retunrs random numbers in the range [min,max].
// You can define your own here! 


VEGAS_Template
LD VEGAS_Namespace::Random(LD min, LD max){
    RndE.seed(RndDiv () );
    return (UnDist( RndE )*(max - min) + min ) ;
}

VEGAS_Template
int VEGAS_Namespace::RandomBin(){
    RndE.seed( RndDiv () );
    return UnInt(RndE);
}


#endif