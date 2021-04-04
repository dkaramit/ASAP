from numpy   import sqrt as np_sqrt

from .GradientDescent import GradientDescent
 
class AdaDeltaGD(GradientDescent):
    '''Implementation of AdaDelta.'''
    
    def __init__(self,function,gamma=0.95,epsilon=1e-6,alpha=1):
        '''
        function: instance of Function
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        '''
        GradientDescent.__init__(self,function)

        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        # counters for the decaying means of the gradient and dx         
        self.gE=[0 for _ in range(self.dim)]
        self.dxE=[0 for _ in range(self.dim)]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        _x2=0
        _check=0

        self.function.derivative(self.function.x)
        
        for i in range(self.dim):
            
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*self.function.grad[i]**2 
            dx=np_sqrt( (self.dxE[i]+self.epsilon)/(self.gE[i]+self.epsilon)  )*self.function.grad[i]*self.alpha
            
            self.dxE[i]=self.gamma*self.dxE[i] + (1-self.gamma)*dx**2
            
            self.function.x[i]=self.function.x[i] - dx
            
            
            _x2=abs_tol + self.function.x[i] * rel_tol
            _check+=(dx/_x2)*(dx/_x2)
            self.function.grad[i]=0

        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.function.x[:])
        
        tmp_min=self.function(self.function.x)
        if tmp_min<self.f_min:
            self.function.minimum=self.function.x[:]
            self.f_min=tmp_min
            
        return _check
