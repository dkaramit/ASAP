#ifndef Dual_class
#define Dual_class

#include<iostream>
#include<vector>
#include<cmath>

#define Dual_template template<class LD>
#define Dual_namespace DualNumbers<LD>

/*
A class for (hyper) dual numbers. It will be used to get derivatives of functions.
*/
Dual_template
class DualNumbers{
    using vecGrad=std::vector<LD>;
    using unInt=unsigned int;
    public:

    LD value;//the value of the dual number
    vecGrad grad;//variable to hold the gradient

    unInt varN;//the number of variables

    // constructors and distructors
    DualNumbers()=default;
    ~DualNumbers()=default;
    DualNumbers(LD value, unInt varN=0);
    DualNumbers(LD value, vecGrad grad);
    DualNumbers(const DualNumbers& D);


    /*----------------------overload operators----------------------------------------*/
    /* overload + */
    DualNumbers operator+(const DualNumbers &y) const {
        DualNumbers<LD> result(*this);
        result.addToValue(y.getValue());
        for (unsigned int i = 0; i < result.getVarN(); ++i){
            result.addToGrad(i, y.getGrad(i));  
        }
        return  result;
    };

    template<class T>
    DualNumbers operator+(const T &y) const {
        DualNumbers<LD> result(*this);
        result.addToValue(y);
        return  result;
    };

    /* overload - */
    DualNumbers operator-() const {
        DualNumbers y(- this->getValue(),this->getVarN());    
        for(unInt i=0; i<y.getVarN();++i){
            y.setGrad(i,- this->getGrad(i));
        }
        return y;
    };

    DualNumbers operator-(const DualNumbers &y) const {
        return  (*this)+(-y);
    };
    template<class T>
    DualNumbers operator-(const T &y) const {
        return  (*this)+(-y);
    };
    /* overload * */
    DualNumbers operator*(const DualNumbers &y) const {
        DualNumbers<LD> result(0,this->getVarN());

        result.setValue(this->getValue() * y.getValue());

        LD tmpG=0;
        for (unsigned int i = 0; i < result.getVarN(); ++i){
            tmpG=this->getValue()*y.getGrad(i);
            tmpG+=y.getValue()*this->getGrad(i);
            result.setGrad(i, tmpG);  
        }
        return  result;

    };
    template<class T>
    DualNumbers operator*(const T &y) const {
        DualNumbers<LD> result(y,this->getVarN());
        return  (*this)*result;

    };


    /* overload / */
    DualNumbers operator/(const DualNumbers &y) const {
        DualNumbers<LD> result(this->getValue() / y.getValue(),this->getVarN());

        LD tmpG=0;
        for (unsigned int i = 0; i < result.getVarN(); ++i){
            tmpG=(this->getGrad(i) - this->getValue() *y.getGrad(i)/y.getValue())/y.getValue();
            result.setGrad(i, tmpG);  
        }
        return  result;
    };

    template<class T>
    DualNumbers operator/(const T &y) const {
        DualNumbers<LD> result(this->getValue() / y,this->getVarN());
        for (unsigned int i = 0; i < result.getVarN(); ++i){
            result.setGrad(i, this->getGrad(i)/y);  
        }
        return  result;
    };

    // "getters" and "setters"
    unInt  getVarN() const {return this->varN;}
    LD  getValue() const {return this->value;}
    LD  getGrad(unInt i) const {return this->grad[i];}

    void setVarN(unInt N){this->varN = N; this->grad.resize(N); }
    void setValue(LD value){this->value = value;}
    void setGrad(unInt i, LD grad_i){this->grad[i] = grad_i;}

    void addToValue(LD value){this->value += value;}
    void addToGrad(unInt i, LD grad_i){this->grad[i] += grad_i;}



    // overload << for printing easily
    friend std::ostream& operator<<(std::ostream& os, const DualNumbers& x)
    {
        os << x.value ;
        
        unInt i=0;
        os << ", (" ;
        for(LD g:x.grad){
            os << g;
            if(i<x.varN-1){os<<',';}
            ++i;
        }
        os << ')' ;

        return os;
    }

};


#endif