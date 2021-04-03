from numpy   import sqrt as np_sqrt
from numpy   import max as np_max
from numpy   import abs as np_abs


class AdaMaxGD:
    '''Implementation of AdaMax.'''
    
    def __init__(self,function,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        function: instance of Function
        beta_m: decay parameter for the average m
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate of AdaDelta. 
        '''
        self.function=function
        self.f_min=function(function.x)

        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.steps=[]
        self.steps.append(self.function.x[:])
        self.dim=self.function.dim
        
        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        

        # counters for the decaying means of the gradient         
        self.mE=[0 for _ in range(self.dim)]
        self.v_max=[0 for _ in range(self.dim)]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''

        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        

        _x2=0
        _check=0
        

        self.function.derivative(self.function.x)

        for i in range(self.dim):

            self.mE[i]=self.beta_m*self.mE[i] + (1-self.beta_m)*self.function.grad[i] 
            self.v_max[i]=np_max([self.beta_v*self.v_max[i], np_abs(self.function.grad[i]) ]) 
            dx=self.alpha/(self.v_max[i] + self.epsilon)*self.mE[i]/(1-self.beta_m_ac)
            
            self.function.x[i]=self.function.x[i] - dx
            
            _x2=abs_tol + self.function.x[i] * rel_tol
            _check+=(dx/_x2)*(dx/_x2)

        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.function.x[:])

        tmp_min=self.function(self.function.x)
        if tmp_min<self.f_min:
            self.function.minimum=self.function.x[:]
            self.f_min=tmp_min

        return _check
