# Generic classes for the target function
# If you have analytical form of the gradient, you can define your own class.

class targetFunc:
    def __init__(self,func,h=1e-5):
        self.function =func
        self.h=h
        
    def __call__(self,x):
        return self.function(x)
    
    def Grad(self,x):
        x0=[_ for _ in x]
        x1=[_ for _ in x]
        
        grad=[]
        for dim in range(len(x)):
            x0[dim]=x[dim]-self.h
            x1[dim]=x[dim]+self.h
            
            dfdx0=self.function(x0) 
            dfdx1=self.function(x1) 

            x0[dim]=x[dim]
            x1[dim]=x[dim]
            
            grad.append((dfdx1-dfdx0)/(2*self.h))
        
        return grad
            
#-----------------------------------------------------------------------#

#The Gradient Descent base class
class GradientDescent:
    
    def __init__(self,strategy):
            self.strategy=strategy
        
    
    def run(self,abs_tol=1e-5, rel_tol=1e-3, step_break=100,max_step=5000):
        '''        
        abs_tol, rel_tol, step_break: stop when _check<1 (_check is what update should return) 
        for step_break consecutive steps
        
        max_step: maximum number of steps
        '''
        _s=0
        count_steps=1
        while count_steps<=max_step:
            _check=self.strategy.update(abs_tol, rel_tol)
            
            count_steps+=1             
                
            
            if _check<1:
                _s+=1
            else:
                _s=0
            
            if _s>step_break:
                break
                
        return self.strategy.x