from numpy import sqrt as np_sqrt
from numpy import abs as np_abs
from .FFANN_SGD import StochasticGradientDescent

class NAdamSGD(StochasticGradientDescent):
    '''
    NAdamSGD strategy.
    '''
    def __init__(self,loss,beta_m=1-1e-1,beta_v=1-1e-3,epsilon=1e-8,alpha=1e-2):
        '''
        beta_m: decay parameter for the average m
        beta_v: decay parameter for the average v 
        epsilon: safety parameter (to avoid division by 0)
        alpha: a learning rate that multiplies the rate. 
        '''
        StochasticGradientDescent.__init__(self,loss)
        self.beta_m=beta_m
        self.beta_v=beta_v
        self.epsilon=epsilon
        self.alpha=alpha

        #The "bias corrected" m and v need beta^iteration, so I need something like this
        self.beta_m_ac=beta_m
        self.beta_v_ac=beta_v

        #counters for the decaying means         
        self.mw=[ [[0 for i in range(self.Q.model.nodes[l])] for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]
        self.mb=[ [0 for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]      

        self.vw=[ [[0 for i in range(self.Q.model.nodes[l])] for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]
        self.vb=[ [0 for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]              
   
    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        during the update step, you calculate the gradient of Q
        and update w and b. 
        '''
        # accumulate the decay rates, in order to correct the averages 
        self.beta_m_ac*=self.beta_m_ac
        self.beta_v_ac*=self.beta_v_ac

        #The update should run after
        #FFANN.feedForward() and FFANN.backPropagation().
            
        #these will be used to determine if the stopping conditions are satisfied 
        _w2=0
        _check=0
        self.Q.randomDataPoint()

        
        for l in range(self.Q.model.total_layers-1):
            for j in range(self.Q.model.nodes[l+1]):
                for i in range(self.Q.model.nodes[l]):
                    #get the grad of the loss. The results should be stored in loss.dQdw and loss.dQdb
                    #This way it should be easy to update the weights and biases of FFANN
                    self.Q.grad(l,j,i)
                    self.mw[l][j][i]=self.beta_m*self.mw[l][j][i] + (1-self.beta_m)*self.Q.dQdw
                    self.vw[l][j][i]=self.beta_v*self.vw[l][j][i] + (1-self.beta_v)*self.Q.dQdw**2

                    dw=self.alpha/(np_sqrt(self.vw[l][j][i]/(1-self.beta_v_ac)) + self.epsilon)
                    dw*=(self.beta_m*self.mw[l][j][i] + (1-self.beta_m)*self.Q.dQdw)/(1-self.beta_m_ac)
            
                    
                    #update the weight using loss.dQdw
                    self.Q.model.addToWeight(l,j,i, -dw)

                    _w2=abs_tol + np_abs(self.Q.model.weights[l][j][i]) * rel_tol
                    _check+=(dw/_w2)*(dw/_w2)

                #update the bias using loss.dQdb (it is the same for all i, so don't run loss.grad again).
                self.mb[l][j]=self.beta_m*self.mb[l][j] + (1-self.beta_m)*self.Q.dQdb
                self.vb[l][j]=self.beta_v*self.vb[l][j] + (1-self.beta_v)*self.Q.dQdb**2

                dw=self.alpha/(np_sqrt(self.vb[l][j]/(1-self.beta_v_ac)) + self.epsilon)
                dw*=(self.beta_m*self.mb[l][j] + (1-self.beta_m)*self.Q.dQdb)/(1-self.beta_m_ac)
                
                self.Q.model.addToBias(l,j, -dw)
                
                _w2=abs_tol + np_abs(self.Q.model.biases[l][j]) * rel_tol
                _check+=(dw/_w2)*(dw/_w2)
                
                
        _check=np_sqrt(1./self.Q.N *_check)
        return _check