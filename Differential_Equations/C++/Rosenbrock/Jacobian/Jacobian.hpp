#ifndef Jac_head
#define Jac_head

template<class diffeq, int n_eqs>
class Jacobian{
    public:
    double h;
    diffeq dydt;

    double y0[n_eqs],y1[n_eqs],dydt0[n_eqs],dydt1[n_eqs];

    Jacobian(){};


    Jacobian(Jacobian<diffeq,n_eqs> &Jac){
        this->dydt=Jac.dydt;
        this->h=Jac.h;

    };
    Jacobian(diffeq dydt, double h=1e-8){
        this->dydt=dydt;
        this->h=h;

    };
    ~Jacobian(){};

    void operator()(double (&J)[n_eqs][n_eqs], double (&dfdt)[n_eqs], double (&y)[n_eqs]  , double t ){

        dydt(dydt0,y,t-h);
        dydt(dydt1,y,t+h);

        for (int i = 0; i < n_eqs; i++){ dfdt[i]=(dydt1[i]-dydt0[i])/(2*h); }
        
        
        for (int i = 0; i < n_eqs; i++){for (int j = 0; j < n_eqs; j++){
            for(int _d = 0; _d < n_eqs; _d++){y0[_d]=y[_d]; y1[_d]=y[_d]; }

            y0[j]=y0[j]-h;
            y1[j]=y1[j]+h;
            dydt(dydt0,y0,t);
            dydt(dydt1,y1,t);

            J[i][j]=(dydt1[i]-dydt0[i])/(2*h);


        }}




    };





};


#endif