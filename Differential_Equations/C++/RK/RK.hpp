//This is a general implementation of explicit RK solver of
// a system of differential equations in the interval [0,1].


template<class diffeq, class Array, class RK_method> //Note that you can use template to pass the method
class RK
{
private:
    
public:
    int No_steps, number_of_eqs,current_step;
    bool End;
    double step_size;
    diffeq dydt;
    double* steps;

    double** solution;

    RK_method method;
    //these are here to hold the k's, sum_i b_i*k_i and sum_j a_{ij}*k_j 
    double* k;
    double* ak;
    double* bk;

    Array y0;//this is here to hold the current steps
    Array fy;//this is here to get dydt in each step
    
    RK(diffeq & dydt, Array  & init_cond , int N=10000){
        this->step_size= 1./(N-1.);

        this->dydt=dydt;
        // std::cout << "Initialize system of "<< this->dydt.n<<" equations" << std::endl;
        this->No_steps=N;
        this->number_of_eqs= this->dydt.n;

        this->steps = new double[this->No_steps];//make a list in which you'll put the steps 

        //define solution[number_of_eqs][No_steps]
        this->solution = new double*[this->number_of_eqs];
        for(int i = 0; i < this->number_of_eqs ;++i) {
                this->solution[i] = new double[ this->No_steps];
                this->solution[i][0]=init_cond[i];//put the initial condition
            } 
        k=new double[this->number_of_eqs];
        ak=new double[this->number_of_eqs];
        bk=new double[this->number_of_eqs];


        this->current_step=0;
        this->End=false;
        };
    ~RK(){
        // std::cout << "I'm done" << std::endl;
        delete[] this->steps;
        delete[] this->solution;
        delete[] this->k;
        delete[] this->ak;
        delete[] this->bk;
    };

    /*-------------------it would be nice to have a way to define these sums more generaly-----------------*/
    void sum_bk(){
        // calculate sum_i b_i*k_i and passit to this->bk 
    }

    void sum_ak(int stage){
        // calculate sum_j a_{ij}*k_j and passit to this->ak
    }
    
    void next_step(){
        if (this->current_step>= this->No_steps -1 )
        {
            this->End=true;
        } else{
            


        }
        

    }

    void solve(){

        while (not this->End)
        {

            this->next_step();
        }

    }



};