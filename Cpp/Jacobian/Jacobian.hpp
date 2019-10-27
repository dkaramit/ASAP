/*
The class Jacobian can calculate the jacobian of a system of equations.
It is intented to work with a system of equations defined as a class with an overloaded "opreator()",
inspired by how it is used in odeint of the boost library.

Note:
    The derivatives are obtained as f'(x)=(f(x+h)-f(x-h))/(2*h), which has an error of O(h^2).
    This means that for h~10^-8, we approach the round-off error of doubles.

    I could have defined the derivative as f'(x)=Im(f(x+h*1i))/h (since I have used templated, I can do
    this with no problem), but it will not be a lot faster and the error is of the same order.




Personal note:
    It is strange to think of it like that, but as I'm working with it seems more and more convinient,
    considering the alternative. As far as I know, the alternative is to pass functions into other functions
    (i.e. the system of equations to the jacobian), which would complicate the definitions. Honestly, doing
    it this way, I didn't need to spend hours debugging it, because once you have defined everything it just
    works!
*/

#ifndef Jac_head
#define Jac_head

#include <cmath>
// For the matrix
#include <boost/numeric/ublas/matrix.hpp>
typedef  boost::numeric::ublas::matrix< double > Matrix;


template<class SYSTEM>
class Jacobian
{
    public :

        //The default constructor is useless, since we need the jacoobian to be assosiated with a system.
        //We can do this later (with Jac.h=....), but I don't want to allow it.
        // Jacobian()
        // {
              //std::cout << "Jacobian defined. Missing Sys..." << "\n";
        // }

        ~Jacobian()
        {
            // std::cout << "Jacobian out." << "\n";
        }

        double h;//differentiation step
        int dim;//number of equations you have.
        SYSTEM sys;//the system of equations. This should be defined as a class with an overloaded "opreator()".

        Jacobian(SYSTEM &sys_, double h_, int dim_)//The constructor.
        {
            this->h=h_;
            this->sys=sys_;
            this->dim=dim_;
            // std::cout << "Jacobian defined." << "\n";

        }

        template<class P , class T , class F>
        void operator()(const P &x_ , Matrix &J , T t, F &dfdt_)
        {

            F dxdt0,dxdt1;


            //Take the symmetric derivative over time:
            //Calculate dxdt0 and dxdt1 (i.e. dxdt at t-h and t+h)
            this->sys(x_,dxdt0,t-(this->h) );
            this->sys(x_,dxdt1,t+(this->h));

            for (int i = 0; i < this->dim; ++i)
            {
                dfdt_[i]=(dxdt1[i]-dxdt0[i])/(2* (this->h));
            }

            P x0,x1;
            //take the symmetric derivative, and find all elements of the jacobian.
            for (int i = 0; i < this->dim; ++i)
            {

                for (int j = 0; j < this->dim; ++j)
                {
                    //put x0 and x1 to x_.
                    x0=x_;
                    x1=x_;
                    //Change only the j component (remember Jij = dfi/dxj, with fi the i component of the system dxdt).
                    x0[j]=x_[j]-h;
                    x1[j]=x_[j]+h;

                    //Calculate dxdt0 and dxdt1.
                    this->sys(x0,dxdt0,t);
                    this->sys(x1,dxdt1,t);

                    //Calculate the Jacobian element Jij
                    J(i,j)= (dxdt1[i]-dxdt0[i])/(2*(this->h) );

                }
            }


        }



};
#endif
