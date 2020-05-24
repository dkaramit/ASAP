#ifndef SA_neighbour
#define SA_neighbour
#include"SA.hpp"

SA_Template
LD SA_Namespace::Random(int d ){
        RndE.seed(RndDiv () );
        return (UnDist( RndE )*sigma[d] -sigma[d]/2.)  ;
    }

SA_Template
LD SA_Namespace::Random( ){
        RndE.seed(RndDiv () );
        return UnDist( RndE ) ;
    }


SA_Template
void SA_Namespace:: PickNeighbour(){
    


    for(int d =0 ; d<dim ; ++d){
        // move randomly
        _x[d] = x[d]+Random(d);
        
        // make sure you stay in region (if you leave the boundary, you go to the otherside, like a closed surface)
        dx_max=region[d][1] - _x[d] ;
        dx_min= _x[d] - region[d][0] ;


        if (dx_max<0){ _x[d]= region[d][0] - dx_max ;}
        if (dx_min<0){ _x[d]= region[d][1] + dx_min ;}
        
 
        xnew[d]=_x[d];
    }



}
    

#endif