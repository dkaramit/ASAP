// This is an implementation of the Euler algorithm for ODEs.
// I will try to follow the my python code, for consistency,
// but some things may be different. I will put comments  
// around these differences.
#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
// #include <iomanip>
//#include <complex>
// #include <cstdlib>
// using namespace std;

//The idea is to have a class with an overloaded "()" operator to be passed as a variable in the solver.
//So, we need to use a template 
template<class diffeq, class Array> 
class Euler
{
private:
    
public:
    int No_steps, number_of_eqs,current_step;
    bool End;
    double step_size;
    diffeq dydt;
    double* steps;
    
    double** solution;

    Array y0;//this is here to hold the current steps
    Array fy;//this is here to get dydt in each step
    
    Euler(diffeq & dydt, Array  & init_cond , int N ){
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
         


        this->current_step=0;
        this->End=false;
        };
    ~Euler(){
        // std::cout << "I'm done" << std::endl;
        delete[] this->steps;
        delete[] this->solution;
    };


    void next_step(){
        if (this->current_step>= this->No_steps -1 )
        {
            this->End=true;
        } else{

            this->current_step++;
            double t0=this->current_step*this->step_size;
            this->steps[this->current_step]=t0;

            for (int eq = 0; eq < this->number_of_eqs ; eq++){this->y0[eq]=this->solution[eq][this->current_step-1];}

            this->dydt(this->fy,this->y0,t0);
            for (int eq = 0; eq < this->number_of_eqs ; eq++){
                this->solution[eq][this->current_step]=this->solution[eq][this->current_step-1] + this->fy[eq]*this->step_size;
                }
            
        }
        

    }

    void solve(){

        while (not this->End)
        {

            this->next_step();
        }

    }



};


// this is how the diffeq should look like
#define n_eqs 2 //number of equations
typedef std::array<double, n_eqs> Array; //define an array type of length n_eqs

 class diffeq
{
    public:
        int n=n_eqs;//number of equations
        diffeq(){};
        ~diffeq(){};
        
        
        //Overloading the braket operator.
        void operator()( Array &lhs, Array &y  , double t )
        {
            //lhs is an array that gets the return value (the left hand side of the equation)
            //y is an array with values of y
            //t is the value of the variable t
            
            lhs[0]=(-y[0]*y[0]+y[1]*y[1])*2*pow(t,0.1);
            lhs[1]=(y[0]*y[0]-y[1]*y[1])*2*pow(t,0.1);

        }


};



int main(int argc, const char** argv) {
    
    Array lhs;
    Array y0;
    y0[0]=1.2;
    y0[1]=0.6;
    diffeq dydt;

    //dydt(lhs,y0,5.2);
    //std::cout << lhs[1] << std::endl;
    int N=10000;
    Euler<diffeq,Array> System(dydt,y0,N);
    System.solve();

    std::ofstream f1,f2,t;
    f1.open ("data/y1.dat");
    f2.open ("data/y2.dat");
    t.open ("data/t.dat");
    //myfile << "Writing this to a file.\n";
    //myfile.close();


    for (int i = 0; i < N; i++)
    {
        f1 << System.solution[0][i] ;
        f1 << "\n";
        f2 << System.solution[1][i] ;
        f2 << "\n";
        t << System.steps[i] ;
        t << "\n";
        
            }
    
    return 0;
 }