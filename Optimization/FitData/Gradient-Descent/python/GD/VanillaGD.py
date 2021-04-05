from numpy   import sqrt as np_sqrt
from numpy   import abs as np_abs

from .GradientDescent import GradientDescent

class VanillaGD(GradientDescent):
    def __init__(self,loss,alpha=1e-2):
        '''
        loss: the loss function
        alpha: the learning rate
        '''
        GradientDescent.__init__(self,loss)
        self.alpha=alpha

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        
        _w2=0
        _check=0
                
        self.Q.averageGrad()
        
        for i in range(self.dim):
            dw=self.alpha*self.Q.grad[i]
            self.Q.model.w[i]=self.Q.model.w[i]-dw

            _w2=abs_tol + np_abs(self.Q.model.w[i]) * rel_tol
            _check+=(dw/_w2)*(dw/_w2)
            
            self.Q.grad[i]=0

        _check=np_sqrt(1./self.dim *_check)
        
        return _check