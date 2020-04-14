#ifndef VEGAS_aux
#define VEGAS_aux
#include"VEGAS.hpp"



// Define functions that help with getting some feedback for the Grid
VEGAS_Template
void VEGAS_Namespace::PrintGrid(){
    for( int dim=0 ; dim<Dim ; ++dim ){
        for( int bin=0 ; bin<Nbins+1 ; ++bin ){
            std::cout<<this->Grid[dim][bin]<<" ";
        }
        std::cout<<"\n";
    }

}

VEGAS_Template
void VEGAS_Namespace::PrintGrid(int dim){
    for( int bin=0 ; bin<Nbins+1 ; ++bin ){
        std::cout<<this->Grid[dim][bin]<<" ";
    }
    std::cout<<"\n";

}

VEGAS_Template
void VEGAS_Namespace::PrintRandomGrid(){
        
        for (int bin=0 ; bin< Nbins ; ++bin)
        {
            std::cout<<"in ("<<Grid[last_dim][bin]<<","<<Grid[last_dim][bin+1]<<"): "<<std::endl;
            for(int Rpoint =0; Rpoint < PointsPerBin  ; ++Rpoint)
            {

                std::cout<<RandPoints[bin][ Rpoint]<<" ";
            }
        std::cout<<std::endl;
        }

}





VEGAS_Template
LD VEGAS_Namespace::BinMean(int bin){
        LD _mean=0;
        for(int Rpoint =0; Rpoint < PointsPerBin  ; ++Rpoint)
        {

            _mean+=RandPoints[bin][ Rpoint];
        }
    return _mean/PointsPerBin;
}

VEGAS_Template
void VEGAS_Namespace::PrintMeans(){

    for (int bin=0 ; bin< Nbins ; ++bin)
    {
        std::cout<<"in ("<<Grid[last_dim][bin]<<","<<Grid[last_dim][bin+1]<<"): ";
        std::cout<<BinMean(bin)<<" ";
        std::cout<<std::endl;   
    }


}



#endif