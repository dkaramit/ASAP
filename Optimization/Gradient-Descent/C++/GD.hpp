#ifndef GD_head
#define GD_head

#include <cmath>
#include <vector>


#define GD_Template template<class LD>
#define GD_Namespace GradientDescent<LD>


GD_Template
class GradientDescent{
    public:
    
    // constructors and destructor
    GradientDescent(){};
    ~GradientDescent(){};

    virtual LD update(LD abs_tol, LD rel_tol);//this will be overwritten by the derived classes
    
    void run(LD abs_tol=1e-5, LD rel_tol=1e-3, unsigned int step_break=100, unsigned int max_step=5000);
};


GD_Template
void GD_Namespace::run(LD abs_tol, LD rel_tol, unsigned int step_break, unsigned int max_step){
    
    unsigned int _s=0;
    unsigned int count_steps=1;
    
    LD _check;

    while(count_steps<=max_step){
        _check=this->update(abs_tol,rel_tol);

        count_steps++;

        if(_check<1){_s++;}
        else{_s=0;}
        if(_s>step_break){break;}

    }
}




#endif