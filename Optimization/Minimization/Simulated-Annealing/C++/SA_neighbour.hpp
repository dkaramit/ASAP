#ifndef SA_neighbour
#define SA_neighbour
#include"SA.hpp"

SA_Template
LD SA_Namespace::Random(int d ){
    // return UnDist( RndE )*sigma[d] -sigma[d]/2.  ;
    NGauss=std::normal_distribution<LD>(0,sigma[d]);
    return  NGauss(RndE);
}

SA_Template
LD SA_Namespace::Random( ){
        return UnDist( RndE ) ;
}



// You need a modulus function to make x stay in the search region
SA_Template
LD SA_Namespace::mod(LD x, LD y) {
    return x - (int)(x/y) * y;
}

SA_Template
void SA_Namespace:: PickNeighbour(){

    for(unsigned int d =0 ; d<dim ; ++d){
        // move randomly
        _x[d] = x[d]+Random(d);
        
        // make sure you stay in region (if you leave the boundary, you go to the otherside, like a closed surface)
        if (region[d][1] < _x[d]){ 
            dx=_x[d]-region[d][1];
            dx=mod(dx, region[d][1]- region[d][0]);
            _x[d]= region[d][0] + dx ;
            }
        if (_x[d] < region[d][0] ){
            dx=region[d][0] - _x[d];
            dx=mod(dx, region[d][1]- region[d][0]);
            _x[d]= region[d][1] - dx ;
            }
        
 
        xnew[d]=_x[d];
    }



}
    

#endif