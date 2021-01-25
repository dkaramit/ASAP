from .GradientDescent import GradientDescent

from numpy   import sqrt as np_sqrt


class NAdamGD:
    '''Implementation of NAdam.'''
    
    def __init__(self,target,x0,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        target: the target function to be minimized, with target.Gard its gradient
        x0: starting point
        beta_m: decay parameter for the average m
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate of AdaDelta. 
        '''
        self.target=target
        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.steps=[]
        self.steps.append(x0[:])
        self.x=[_ for _ in x0]
        self.dim=len(x0)

        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        self.beta_v_ac=beta_v
        
        # counters for the decaying means of the gradient         
        self.mE=[0 for _ in self.x]
        self.vE=[0 for _ in self.x]
        
        #lists to store the changes in x         
        self.dx=[0 for _ in self.x]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        grad=self.target.Grad(self.x)

        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        self.beta_v_ac*=self.beta_v_ac
        
        _check=0
        _x2=0

        for i,g in enumerate(grad):
            self.mE[i]=self.beta_m*self.mE[i] + (1-self.beta_m)*g 
            self.vE[i]=self.beta_v*self.vE[i] + (1-self.beta_v)*g**2

            self.dx[i]=self.alpha/(np_sqrt(self.vE[i]/(1-self.beta_v_ac)) + self.epsilon)
            self.dx[i]*=(self.beta_m*self.mE[i] + (1-self.beta_m)*g)/(1-self.beta_m_ac)
            
            self.x[i]=self.x[i] - self.dx[i]
            
            
            _x2=abs_tol + self.x[i] * rel_tol
            _check+=(g/_x2)*(g/_x2)
    
    
        _check=np_sqrt(1./self.dim *_check)

        self.steps.append(self.x[:])
        
        return _check
