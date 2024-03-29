from numpy   import sqrt as np_sqrt
from numpy   import abs as np_abs

from .GradientDescent import GradientDescent

class NAdamGD(GradientDescent):
    '''Implementation of NAdam.'''
    def __init__(self,function,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        function: instance of Function
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate of AdaDelta. 
        '''
        GradientDescent.__init__(self,function)

        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha
        
        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        self.beta_v_ac=beta_v

        # counters for the decaying means of the gradient         
        self.mE=[0 for _ in range(self.dim)]
        self.vE=[0 for _ in range(self.dim)]
        
        #lists to store the changes in w         
        self.dx=[0 for _ in range(self.dim)]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''

        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        self.beta_v_ac*=self.beta_v_ac
        
        _x2=0
        _check=0
        
        self.function.derivative(self.function.x)

        for i in range(self.dim):

            self.mE[i]=self.beta_m*self.mE[i] + (1-self.beta_m)*self.function.grad[i]
            self.vE[i]=self.beta_v*self.vE[i] + (1-self.beta_v)*self.function.grad[i]**2

            dx=self.alpha/(np_sqrt(self.vE[i]/(1-self.beta_v_ac)) + self.epsilon)
            dx*=(self.beta_m*self.mE[i] + (1-self.beta_m)*self.function.grad[i])/(1-self.beta_m_ac)
            self.function.x[i]=self.function.x[i] - dx
            
            _x2=abs_tol + np_abs(self.function.x[i]) * rel_tol
            _check+=(dx/_x2)*(dx/_x2)


        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.function.x[:])
        
        tmp_min=self.function(self.function.x)
        if tmp_min<self.f_min:
            self.function.minimum=self.function.x[:]
            self.f_min=tmp_min

        return _check
