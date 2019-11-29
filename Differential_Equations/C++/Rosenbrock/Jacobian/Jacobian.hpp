#ifndef Jac_head
#define Jac_head

template<class diffeq, class Array, class Matrix>
class Jacobian{
    public:
    int dim;
    double h;
    diffeq dydt;

    Array y0,y1,dydt0,dydt1;

    Jacobian(){};


    Jacobian(Jacobian<diffeq, Array, Matrix> &Jac){
        this->dydt=Jac.dydt;
        this->dim=Jac.dydt.n;
        this->h=Jac.h;

    };
    Jacobian(diffeq& dydt, double h=1e-8){
        this->dydt=dydt;
        this->dim=dydt.n;
        this->h=h;

    };
    ~Jacobian(){};
    // void operator()(Array &dfdt,Array &y,double t ){};

    void operator()(Matrix &J, Array &dfdt, Array &y  , double t ){

        dydt(dydt0,y,t-h);
        dydt(dydt1,y,t+h);

        for (int i = 0; i < dim; i++){ dfdt[i]=(dydt1[i]-dydt0[i])/(2*h); }
        
        
        for (int i = 0; i < dim; i++){for (int j = 0; j < dim; j++){
            for(int _d = 0; _d < dim; _d++){y0[_d]=y[_d]; y1[_d]=y[_d]; }

            y0[j]=y0[j]-h;
            y1[j]=y1[j]+h;
            dydt(dydt0,y0,t);
            dydt(dydt1,y1,t);

            J[i][j]=(dydt1[i]-dydt0[i])/(2*h);


        }}




    };





};


#endif