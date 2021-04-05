from numpy   import sqrt as np_sqrt
from numpy   import abs as np_abs

from .StochasticGradientDescent import StochasticGradientDescent

class AdaDeltaSGD(StochasticGradientDescent):
    '''Implementation of AdaDelta.'''
    
    def __init__(self,loss,gamma=0.95,epsilon=1e-6,alpha=1):
        '''
        loss: the loss function
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        '''
        StochasticGradientDescent.__init__(self,loss)
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        
        # counters for the decaying means of the gradient and dw         
        self.gE=[0 for _ in self.Q.model.w]
        self.dwE=[0 for _ in self.Q.model.w]
        
    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        self.Q.randomDataPoint()
        
        _w2=0
        _check=0
        for i in range(self.dim):
            self.Q.grad(i)
            
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*self.Q.dQdw**2 
            dw=np_sqrt( (self.dwE[i]+self.epsilon)/(self.gE[i]+self.epsilon)  )*self.Q.dQdw*self.alpha
            
            self.dwE[i]=self.gamma*self.dwE[i] + (1-self.gamma)*dw**2
            
            self.Q.model.w[i]=self.Q.model.w[i] - dw
            
            
            _w2=abs_tol + np_abs(self.Q.model.w[i]) * rel_tol
            _check+=(dw/_w2)*(dw/_w2)

        _check=np_sqrt(1./self.dim *_check)
        
        return _check
