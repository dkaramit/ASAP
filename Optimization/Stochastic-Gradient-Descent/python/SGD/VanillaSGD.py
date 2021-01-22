from .StochasticGradientDescent import StochasticGradientDescent

from numpy   import random as np_random
from numpy   import sqrt as np_sqrt


class VanillaSGD(StochasticGradientDescent):
    '''Plain SGD, with constant learning rate'''
    
    def __init__(self,loss,data,alpha=1e-2):
        '''
        loss: the loss function
        data: the data to be used in order to minimize the loss
        alpha: the learning rate
        '''
        
        self.lossFunc=loss
        self.data=data
        self.alpha=alpha

        self.data_size=len(self.data)
        self.steps=[self.lossFunc.targetFunc.w[:]]
        

    def update(self):
        '''The updating procedure of SGD'''
        
        
        index=np_random.randint(self.data_size)
        grad=self.Grad(index)            

        _g2=0
        _w2=0
        for i,g in enumerate(grad):
            self.lossFunc.targetFunc.w[i]=self.lossFunc.targetFunc.w[i]-self.alpha*g
            _g2+=g**2
            _w2=self.lossFunc.targetFunc.w[i]**2

        _g2=np_sqrt(_g2/_w2)
        
        self.steps.append(self.lossFunc.targetFunc.w[:])
        
        
        return _g2*self.alpha
