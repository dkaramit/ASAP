from numpy   import random as np_random
from numpy   import sqrt as np_sqrt


class AdamSGD:
    '''Implementation of Adam.'''
    
    def __init__(self,loss,data,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        loss: the loss function
        data: the data to be used in order to minimize the loss
        beta_m: decay parameter for the average m
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate. 
        '''
        self.lossFunc=loss
        self.data=data

        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.data_size=len(self.data)
        self.steps=[]
        self.steps.append(self.lossFunc.targetFunc.w[:])
        self.dim=self.lossFunc.targetFunc.dim
        
        
        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        self.beta_v_ac=beta_v

        # counters for the decaying means of the gradient         
        self.mE=[0 for _ in self.lossFunc.targetFunc.w]
        self.vE=[0 for _ in self.lossFunc.targetFunc.w]
        
        #lists to store the changes in w         
        self.dw=[0 for _ in self.lossFunc.targetFunc.w]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        index=np_random.randint(self.data_size)
        x=self.data[index][0]
        t=self.data[index][1]
        grad=self.lossFunc.Grad(x,t)            

        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        self.beta_v_ac*=self.beta_v_ac
        
        _w2=0
        _check=0
        for i,g in enumerate(grad):
            self.mE[i]=self.beta_m*self.mE[i] + (1-self.beta_m)*g 
            self.vE[i]=self.beta_v*self.vE[i] + (1-self.beta_v)*g**2

            self.dw[i]=self.alpha/(np_sqrt(self.vE[i]/(1-self.beta_v_ac) ) + self.epsilon)  
            self.dw[i]*=self.mE[i]/(1-self.beta_m_ac)
            
            self.lossFunc.targetFunc.w[i]=self.lossFunc.targetFunc.w[i] - self.dw[i]
            
            _w2=abs_tol + self.lossFunc.targetFunc.w[i] * rel_tol
            _check+=(dw[i]/_w2)*(dw[i]/_w2)

        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.lossFunc.targetFunc.w[:])
        
        return _check




