from numpy   import random as np_random
from numpy   import sqrt as np_sqrt


class VanillaSGD:
    '''Plain SGD, with constant learning rate'''
    
    def __init__(self,loss,data_in,data_out,alpha=1e-2):
        '''
        loss: the loss function
        data_in, data_out: the input, output data to be used in order to minimize the loss
        alpha: the learning rate
        '''
        
        self.Q=loss
        self.data_in=data_in
        self.data_out=data_out
        self.alpha=alpha

        self.data_size=len(self.data_in)
        self.steps=[]
        self.steps.append(self.Q.model.w[:])
        self.dim=self.Q.model.dim

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
        
        _w2=0
        _check=0
        for i in range(self.dim):
            self.Q.grad(i,t)
            dw=self.alpha*self.Q.dQdw
            self.Q.model.w[i]=self.Q.model.w[i]-dw
            
            _w2=abs_tol + self.Q.model.w[i] * rel_tol
            _check+=(dw/_w2)*(dw/_w2)

        _check=np_sqrt(1./self.dim *_check)
        
        self.steps.append(self.Q.model.w[:])
        
        
        return _check