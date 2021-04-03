from numpy   import abs as np_abs


class Function:
    '''
    A base class for the function that we would like to minimize.
    You should define another class where you overload __call__ (and the Jacobian if you have an analytical form)
    '''
    def __init__(self,x0):
        '''
        x0: initial x
        '''
    
        self.x=[_ for _ in x0]#this is the current pint
        self.minimum=[_ for _ in x0]#this is to hold the absolute minimum in case GD escapes it
        
        self.dim=len(x0)
        
        self.grad=[[0 for _1 in x0] for _2 in x0]
        
    def __call__(self,x):
        pass
    
    def derivative(self,x,h=1e-5):
        
        for i in range(self.dim):
            heff=np_abs(x[i])*h+h
            _x=x[:]
            
            _x[i]-=heff
            f0=self(_x)
            _x[i]+=2*heff
            f1=self(_x)

            self.grad[i]=(f1-f0)/(2*heff)



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