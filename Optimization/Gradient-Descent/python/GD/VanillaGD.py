from .GradientDescent import GradientDescent

from numpy   import sqrt as np_sqrt

class VanillaGD(GradientDescent):
    def __init__(self,target,x0,alpha=1e-1):
        '''
        target: the target function to be minimized, with target.Gard its gradient
        x0: starting point
        alpha: the alpha parameter
        
        '''
        
        self.target=target
        self.alpha=alpha
        
        self.steps=[]
        self.x=[_ for _ in x0]
        
        
    def update(self):
        '''The updating procedure of GD'''

        grad=self.target.Grad(self.x)
        
        _g2=0
        _w2=0
        for i,g in enumerate(grad):
            self.x[i]=self.x[i]-self.alpha*g
            _g2+=g**2
            _w2=self.x[i]**2

        _g2=np_sqrt(_g2/_w2)
        
        self.steps.append(self.x[:])
        
        
        return _g2*self.alpha
