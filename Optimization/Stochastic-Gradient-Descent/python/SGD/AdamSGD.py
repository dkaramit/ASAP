from numpy   import random as np_random
from numpy   import sqrt as np_sqrt


class AdamSGD:
    '''Implementation of Adam.'''
    
    def __init__(self,loss,data_in,data_out,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        loss: the loss function
        data_in, data_out: the input, output data to be used in order to minimize the loss
        beta_m: decay parameter for the average m
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate. 
        '''
        self.Q=loss
        self.data_in=data_in
        self.data_out=data_out

        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.data_size=len(self.data_in)
        self.steps=[]
        self.steps.append(self.Q.model.w[:])
        self.dim=self.Q.model.dim
        
        
        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        self.beta_v_ac=beta_v

        # counters for the decaying means of the gradient         
        self.mE=[0 for _ in self.Q.model.w]
        self.vE=[0 for _ in self.Q.model.w]
        

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        index=np_random.randint(self.data_size)
        t=self.data_out[index]

        self.Q.model.setInput(self.data_in[index])
        self.Q.model()

        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        self.beta_v_ac*=self.beta_v_ac
        
        _w2=0
        _check=0
        for i in range(self.dim):
            self.Q.grad(i,t)

            self.mE[i]=self.beta_m*self.mE[i] + (1-self.beta_m)*self.Q.dQdw
            self.vE[i]=self.beta_v*self.vE[i] + (1-self.beta_v)*self.Q.dQdw**2

            dw=self.alpha/(np_sqrt(self.vE[i]/(1-self.beta_v_ac) ) + self.epsilon)  
            dw*=self.mE[i]/(1-self.beta_m_ac)
            
            self.Q.model.w[i]=self.Q.model.w[i] - dw
            
            _w2=abs_tol + self.Q.model.w[i] * rel_tol
            _check+=(dw/_w2)*(dw/_w2)

        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.Q.model.w[:])
        
        return _check




