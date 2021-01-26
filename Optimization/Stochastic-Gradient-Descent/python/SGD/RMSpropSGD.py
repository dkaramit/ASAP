from numpy   import random as np_random
from numpy   import sqrt as np_sqrt



class RMSpropSGD:
    '''Implementation of RMSprop.'''

    def __init__(self,loss,data,gamma=0.95,epsilon=1e-6,alpha=1e-2):
        '''
        loss: the loss function
        data: the data to be used in order to minimize the loss
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: learning rate
        '''
        
        self.lossFunc=loss
        self.data=data
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.data_size=len(self.data)
        self.steps=[]
        self.steps.append(self.lossFunc.targetFunc.w[:])
        self.dim=self.lossFunc.targetFunc.dim
        
        # counters for the decaying means of the gradient and dw         
        self.gE=[0 for _ in self.lossFunc.targetFunc.w]

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

        
        
        _w2=0
        _check=0
        for i,g in enumerate(grad):
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*g**2 
            dw=self.alpha/np_sqrt( (self.gE[i]+self.epsilon)  )*g
            
            
            self.lossFunc.targetFunc.w[i]=self.lossFunc.targetFunc.w[i] - dw
            
            
            _w2=abs_tol + self.lossFunc.targetFunc.w[i] * rel_tol
            _check+=(g/_w2)*(g/_w2)

        _check=np_sqrt(1./self.dim *_check)
        self.steps.append(self.lossFunc.targetFunc.w[:])
        
        return _check

