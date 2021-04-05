from numpy import sqrt as np_sqrt
from numpy import abs as np_abs
from .FFANN_SGD import StochasticGradientDescent

class AdaDeltaSGD(StochasticGradientDescent):
    '''
    AdaDeltaSGD strategy. Better than vanilla, but still not that good
    '''
    def __init__(self,loss,gamma=0.995,epsilon=1e-4,alpha=1):
        '''
        loss: the loss function
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: learning rate
        '''
        StochasticGradientDescent.__init__(self,loss)
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha

        #counters for the decaying means         
        self.mean_dw=[ [[0 for i in range(self.Q.model.nodes[l])] for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]
        self.mean_db=[ [0 for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]      

        self.mean_dQdw=[ [[0 for i in range(self.Q.model.nodes[l])] for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]
        self.mean_dQdb=[ [0 for j in range(self.Q.model.nodes[l+1])]  for l in range(self.Q.model.total_layers-1)]      
        
    def update(self,abs_tol=1e-5, rel_tol=1e-3):
        '''
        during the update step, you calculate the gradient of Q
        and update w and b. 
        '''
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
                    self.mean_dQdw[l][j][i]=self.gamma*self.mean_dQdw[l][j][i] + (1-self.gamma)*self.Q.dQdw**2
                    dw=np_sqrt( (self.mean_dw[l][j][i]+self.epsilon)/(self.mean_dQdw[l][j][i]+self.epsilon))*self.Q.dQdw*self.alpha
            
                    self.mean_dw[l][j][i]=self.gamma*self.mean_dw[l][j][i] + (1-self.gamma)*dw**2

                    
                    
                    #update the weight using loss.dQdw
                    self.Q.model.addToWeight(l,j,i, -dw)

                    _w2=abs_tol + np_abs(self.Q.model.weights[l][j][i]) * rel_tol
                    _check+=(dw/_w2)*(dw/_w2)

                #update the bias using loss.dQdb (it is the same for all i, so don't run loss.grad again).
                self.mean_dQdb[l][j]=self.gamma*self.mean_dQdb[l][j] + (1-self.gamma)*self.Q.dQdb**2
                dw=np_sqrt( (self.mean_db[l][j]+self.epsilon)/(self.mean_dQdb[l][j]+self.epsilon))*self.Q.dQdb*self.alpha
        
                self.mean_db[l][j]=self.gamma*self.mean_db[l][j] + (1-self.gamma)*dw**2
                 
                self.Q.model.addToBias(l,j, -dw)
                
                _w2=abs_tol + np_abs(self.Q.model.biases[l][j]) * rel_tol
                _check+=(dw/_w2)*(dw/_w2)
                
                
        _check=np_sqrt(1./self.Q.N *_check)
        return _check