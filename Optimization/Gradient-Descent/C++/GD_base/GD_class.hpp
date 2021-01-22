#ifndef GD_calss
#define GD_calss

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


#endif