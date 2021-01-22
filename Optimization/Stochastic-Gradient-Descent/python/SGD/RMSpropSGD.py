from .StochasticGradientDescent import StochasticGradientDescent

from numpy   import random as np_random
from numpy   import sqrt as np_sqrt



class RMSpropSGD(StochasticGradientDescent):
    '''Implementation of RMSprop.'''

    def __init__(self,loss,data,gamma=0.95,epsilon=1e-6,alpha=1e-3):
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
        self.steps=[self.lossFunc.targetFunc.w[:]]
        
        # counters for the decaying means of the gradient and dw         
        self.gE=[0 for _ in self.lossFunc.targetFunc.w]

    def update(self):
        '''The updating procedure of AdaDelta'''

        index=np_random.randint(self.data_size)
        grad=self.Grad(index)

        
        _g2=0
        _w2=0

        for i,g in enumerate(grad):
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*g**2 
            dw=self.alpha/np_sqrt( (self.gE[i]+self.epsilon)  )*g
            
            
            self.lossFunc.targetFunc.w[i]=self.lossFunc.targetFunc.w[i] - dw
            
            
            _g2+=dw**2
            _w2+=self.lossFunc.targetFunc.w[i]**2
        
        _g2=np_sqrt(_g2/_w2)
        self.steps.append(self.lossFunc.targetFunc.w[:])
        
        return _g2*self.alpha

