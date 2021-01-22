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



#Base class for Stochastic Gradient Descent

class StochasticGradientDescent:    
    '''Base class for SGD. The derivative classes should overide the constructor and the update function'''
    
    def __init__(self):
        pass
    
    def update(self):
        pass
    
    
    def __call__(self,index):
        '''
        Change call so that you calculate the loss of the "index" data-point with the self.targetFuncFunc.w
        set to self.position
        '''
        
        x=self.data[index][0]
        t=self.data[index][1]
        
        return self.lossFunc(x,t)
    
    
    def Grad(self,index,h=1e-5):
        x=self.data[index][0]
        t=self.data[index][1]

        return self.lossFunc.Grad(x,t)
        
        
    
    
    
    def run(self,tol=1e-5, step_break=100,max_step=5000):
        '''        
        tol, step_break: stop when the gradient becomes smaller than tol for step_break consecutive steps
        max_step: maximum number of steps
        '''
        _s=0
        count_steps=1
        
        while count_steps<=max_step:
            _check=self.update()
            
            count_steps+=1             
                
            
            if _check<tol:
                _s+=1
            else:
                _s=0
            
            if _s>step_break:
                break

        return self.lossFunc.targetFunc.w[:]
#---------------------------------------------------------------------------------------#


