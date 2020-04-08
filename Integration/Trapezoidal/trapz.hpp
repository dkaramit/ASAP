#ifndef include_Trapz
#define include_Trapz

//  trapezoidal rule from arrays of data 
template<class LD>
LD trapezoidal(LD* X , LD* Y, int N_points ){
    LD integral=0;

    for( int i=1; i< N_points ; ++i ){
        integral+=0.5*(X[i] - X[i-1])*(Y[i] + Y[i-1]);
    }

    return integral;
}

//  trapezoidal rule from function
template<class LD>
LD trapezoidal(LD (*func)(LD), LD min, LD max , int N_points ){
    LD x0,x1,y0,y1;
    
    LD integral=0;
    
    x0=min;
    y0=func(x0);

    for( int i=1; i< N_points ; ++i ){
        x1=min + i* (max-min)/(N_points-1);
        y1=func(x1);
        integral+=0.5*(x1 - x0)*(y1 + y0 );

        x0=x1;
        y0=y1;
    }

    return integral;
}


#endif