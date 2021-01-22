from .GradientDescent import GradientDescent

from numpy   import sqrt as np_sqrt


class AdaDeltaGD(GradientDescent):
    '''Implementation of AdaDelta.'''
    
    def __init__(self,target,x0,gamma=0.95,epsilon=1e-6,alpha=1):
        '''
        target: the target function to be minimized, with target.Gard its gradient
        x0: starting point
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate of AdaDelta. 
        '''
        self.target=target
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha
        
        self.steps=[]
        self.x=[_ for _ in x0]
        
        # counters for the decaying means of the gradient and dx         
        self.gE=[0 for _ in self.x]
        self.dxE=[0 for _ in self.x]
        
        #lists to store the changes in x         
        self.dx=[0 for _ in self.x]

    def update(self):
        '''The updating procedure of AdaDelta'''
        grad=self.target.Grad(self.x)

        
        _g2=0
        _x2=0

        for i,g in enumerate(grad):
            self.gE[i]=self.gamma*self.gE[i] + (1-self.gamma)*g**2 
            self.dx[i]=np_sqrt( (self.dxE[i]+self.epsilon)/(self.gE[i]+self.epsilon)  )*g*self.alpha
            
            self.dxE[i]=self.gamma*self.dxE[i] + (1-self.gamma)*self.dx[i]**2
            
            self.x[i]=self.x[i] - self.dx[i]
            
            
            _g2+=self.dx[i]**2
            _x2+=self.x[i]**2
        
        _g2=np_sqrt(_g2/_x2)
        self.steps.append(self.x[:])
        
        return _g2*self.alpha
