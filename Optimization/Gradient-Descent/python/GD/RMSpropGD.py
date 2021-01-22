from .GradientDescent import GradientDescent

from numpy   import sqrt as np_sqrt

class RMSpropGD(GradientDescent):
    '''Implementation of RMSprop.'''
    
    def __init__(self,target,x0,gamma=0.95,epsilon=1e-6,alpha=1e-2):
        '''
        target: the target function to be minimized, with target.Gard its gradient
        x0: starting point
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate of AdaDelta. 
        '''
        self.target=target
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.steps=[]
        self.steps.append(x0[:])
        self.x=[_ for _ in x0]
        self.dim=len(x0)
        
        # counters for the decaying means of the gradient and dx         
        self.gE=[0 for _ in self.x]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        grad=self.target.Grad(self.x)

        
        _check=0
        _x2=0

        for i,g in enumerate(grad):
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*g**2 
            self.dx=self.alpha/np.sqrt( (self.gE[i]+self.epsilon)  )*g
            
            
            self.x[i]=self.x[i] - self.dx
            
            
            _x2=abs_tol + self.x[i] * rel_tol
            _check+=(g/_x2)*(g/_x2)
    
    
        _check=np_sqrt(1./self.dim *_check)

        self.steps.append(self.x[:])
        
        return _check
