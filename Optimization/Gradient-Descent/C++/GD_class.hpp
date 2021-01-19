#ifndef GD_calss
#define GD_calss

#define GD_Template template<class LD, class Func>
#define GD_Namespace GradientDescent<LD,Func>


GD_Template
class GradientDescent{
    public:

    // note that target should have member called Grad, 
    // in order to call the gradient of the target function easily. 
    Func target;  
    
    // vector to hold the current and next points
    std::vector<LD> x0,x1;
    
    // parameters that define the "learning rate", and the stopping conditions
    LD alpha, tol, step_break;


    // in order to return the path
    std::vector<std::vector<LD>> points;
    
    // in order to hold the gradient (we use it to determine the stopping condition) 
    std::vector<LD> grad;
    
    // constructors and destructor
    GradientDescent(){};
    ~GradientDescent(){};

    GradientDescent(Func target, std::vector<LD> x0, LD alpha=1e-1, LD tol=1e-8, LD step_break=100);

    void update();
    void run();


};


#endif