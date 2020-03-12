#ifndef DE_class
#define DE_class
#include <cmath>

#define pi M_PI
#define Tem template <class func, class LD>



Tem
class DoubleExp
{
public:
    func f;

    LD _exp, _exp_max, h, hmin, rtol, atol, eps;
    int N;
    bool N_init,eval, h_stop;
    LD integral, err, result, error;

    DoubleExp(func F, LD _exp = 5, LD _exp_max = 15, LD rtol = 1e-5, LD atol = 1e-5, int p = 10);
    ~DoubleExp(){};

    LD g(LD t) { return tanh(pi / 2. * sinh(t)); };
    LD dgdt(LD t) { return pi / 2. * cosh(t) / pow(cosh(pi / 2. * sinh(t)), 2.); };
    LD F(LD t) { return this->f(this->g(t)) * this->dgdt(t); };
    LD d2Fdt(LD t, LD _h = 1e-8);

    void N_start();
    LD evaluate();
    void h_control();
    LD integrate();
};
Tem
LD DoubleExp<func, LD>::d2Fdt(LD t, LD _h) { return (F(t + _h) - 2 * F(t) + F(t - _h)) / (_h * _h); }

Tem
DoubleExp<func, LD>::DoubleExp(func f, LD _exp, LD _exp_max, LD rtol, LD atol, int p)
{
    this->f = f;

    this->h = pow(2, -_exp);
    this->hmin = pow(2, -_exp_max);
    this->rtol = rtol;
    this->atol = atol;
    this->eps = pow(10, -p);

    this->N = 2; //it's better to start with N=2, because if N=0 (after N_start), then N can't be updated (N*2=0!) 
    this->N_init=false;//check if N_start() is finished.
    this->eval = true;
    this->h_stop = false;

    this->integral = this->f(this->g(0)) * this->dgdt(0);
    this->err = this->d2Fdt(0);
}

Tem
void DoubleExp<func, LD>::N_start()
{
    int tmp_N = this->N+1;
    LD _x, _w, _f1, _f2;
    while (true)
    {
        _x = this->g(this->h * tmp_N);
        _w = this->dgdt(this->h * tmp_N);
        _f1 = _w * this->f(_x);
        _f2 = _w * this->f(-_x);

        if (fabs(_f1) < this->eps and fabs(_f2) < this->eps)
        {
            this->eval = false;
            N_init=true;
            break;
        }
        else
        {
            this->integral += _f1 + _f2;
            this->err += this->d2Fdt(tmp_N * this->h);
            this->N = tmp_N;
            tmp_N += 1;
        }
    }
}



Tem
LD DoubleExp<func, LD>::evaluate(){

        int j=1;
        LD _x , _w ;
        while (this->eval){
            _x=this->g(this->h*j);
            _w=this->dgdt(this->h*j);

            this->integral+=_w*(this->f(_x) + this->f(-_x)) ; 
            this->err+=this->d2Fdt( j*this->h)+this->d2Fdt( -j*this->h);
            
            j+=2 ;

            if (j>this->N-2){this->eval=false; break;}
        }




}


Tem
void DoubleExp<func, LD>:: h_control(){
    LD abs_err=fabs(this->err*this->h* pow( this->h/(2*pi),2)  );    
    LD _sc=this->atol + this->rtol*fabs(this->integral);
        
    if (abs_err/_sc <1){this->h_stop=true;}
    else{
        if (this->h<this->hmin){this->h_stop=true;}
        else{
            this->h/=2;
            this->N*=2.;
            this->eval=true;
            }
    }
}

Tem
LD DoubleExp<func, LD>::integrate(){
        if (N_init==false){this->N_start();}
        
        while (this->h_stop==false){
            this->h_control();
            this->evaluate();
        }
        this->eval=false;
        this->result = this->integral*this->h;
        this->error =  fabs(this->err*this->h*pow(this->h/(2*pi),2.)  );
}

#endif