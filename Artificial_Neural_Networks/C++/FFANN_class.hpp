#ifndef SA_class
#define SA_class

#include<vector>
#include<array>
// #include"FFANN.hpp"

template<class LD, class Func>
class activationType{
    private:
    Func _function,_derivative;
    
    public:
    activationType(const Func  &function, const Func  &derivative){
        this->_function=function;
        this->_derivative=derivative;
    };
    activationType(){};

    LD operator()(LD x){return _function(x);};
    LD derivative(LD x){return _derivative(x);};

    //just in case
    // activationType& operator=(activationType act)
    // {
    //     std::swap(_function, act._function);
    //     std::swap(_derivative, act._derivative);
    //     return *this;
    // }
};

#define FFANN_Template template<class LD, class Func,  unsigned int total_layers>
#define FFANN_Namespace FFANN<LD, Func, total_layers>



FFANN_Template
class FFANN{
    using actArray=std::array<activationType<LD,Func>,total_layers-1>;
    using nodeArray=std::array<unsigned int ,total_layers>;

    
    public:
    actArray activations;
    nodeArray nodes;
    

    // FFANN(){};
    FFANN(nodeArray &nodes, actArray &activationFunctions){
        this->activations=activationFunctions;
        this->nodes=nodes;

    };
    


};


#endif