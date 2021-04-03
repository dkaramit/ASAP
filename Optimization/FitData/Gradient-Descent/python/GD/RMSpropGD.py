from numpy   import sqrt as np_sqrt

class RMSpropGD:
    '''Implementation of RMSprop.'''

    def __init__(self,loss,data_in,data_out,gamma=0.95,epsilon=1e-6,alpha=1e-3):
        '''
        loss: the loss function
        data_in, data_out: the input, output data to be used in order to minimize the loss
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: learning rate
        '''
        
        self.Q=loss
        self.data_in=data_in
        self.data_out=data_out
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.data_size=len(self.data_in)
        self.steps=[]
        self.steps.append(self.Q.model.w[:])
        self.dim=self.Q.model.dim
        
        # counters for the decaying means of the gradient and dw         
        self.gE=[0 for _ in self.Q.model.w]
        #we need this to hold the average gadient over all data points
        self.grad=[0 for _ in range(self.dim)]

    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        update should return a number that when it is smaller than 1
        the main loop stops. Here I choose this number to be:
        sqrt(1/dim*sum_{i=0}^{dim}(grad/(abs_tol+x*rel_tol))_i^2)
        '''
        _w2=0
        _check=0
        
        #get the average gradient over all data
        for index in range(self.data_size):
            t=self.data_out[index]
    
            self.Q.model.setInput(self.data_in[index])
            self.Q.model()

            for i in range(self.dim):
                self.Q.grad(i,t)
                self.grad[i]+=self.Q.dQdw/self.data_size

        for i in range(self.dim):
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*self.grad[i]**2 
            dw=self.alpha/np_sqrt( (self.gE[i]+self.epsilon)  )*self.grad[i]
            
            self.Q.model.w[i]=self.Q.model.w[i]-dw

            _w2=abs_tol + self.Q.model.w[i] * rel_tol
            _check+=(dw/_w2)*(dw/_w2)
            self.grad[i]=0

        _check=np_sqrt(1./self.dim *_check)

        self.steps.append(self.Q.model.w[:])
 
        return _check