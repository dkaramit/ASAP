from .GradientDescent import GradientDescent

from numpy   import sqrt as np_sqrt

class VanillaGD:
    def __init__(self,target,x0,alpha=1e-1):
        '''
        target: the target function to be minimized, with target.Gard its gradient
        x0: starting point
        alpha: the alpha parameter
        
        '''
        
        self.target=target
        self.alpha=alpha
        
        self.steps=[]
        self.steps.append(x0[:])
        self.x=[_ for _ in x0]
        self.dim=len(x0)
        
    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        grad=self.target.Grad(self.x)
        
        _x2=0
        _check=0
        for i,g in enumerate(grad):
            self.x[i]=self.x[i]-self.alpha*g

            _x2=abs_tol + self.x[i] * rel_tol
            _check+=(g/_x2)*(g/_x2)
    
    
        _check=np_sqrt(1./self.dim *_check)
        
        
        self.steps.append(self.x[:])
        
        return _check
