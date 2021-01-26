# Generic classes for the target and loss functions
# If you have analytical forms of the gradients, you can define your own classes.
class targetFunc:
    '''
    This is how the function should look like.
    The key point is to have way to update the parameters w.
    '''
    def __init__(self,func,w0):
        self.f=func
        self.w=w0
        self.dim=len(w0)
    
    
    
    def __call__(self,x):
        return self.f(self,x)
    
        

class lossFunc:
    '''
    This is how the loss function should look like.
    We use a class, in order to encapsulate the gradient within the same object.
    '''
    def __init__(self,loss,target):
        self.Q=loss
        self.targetFunc=target
        
        self.dim=len(self.targetFunc.w)
            
    def __call__(self,x,t):

        return self.Q(self.targetFunc,x,t)
        
 
    
    def Grad(self,x,t,h=1e-5):
        grad=[]
        for dim in range(self.dim):
            
            self.targetFunc.w[dim]-=h
            dQdw0=self(x,t)

            self.targetFunc.w[dim]+=2*h
            dQdw1=self(x,t) 
            
            self.targetFunc.w[dim]-=h

            grad.append((dQdw1-dQdw0)/(2*h))

        return grad
#--------------------------------------------------------------------------------#



#class for Stochastic Gradient Descent
class StochasticGradientDescent:    
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

        return self.strategy.lossFunc.targetFunc.w[:]
#---------------------------------------------------------------------------------------#


