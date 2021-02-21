from numpy import sqrt as np_sqrt

class RMSpropSGD:
    '''
    RMSpropSGD strategy. Better than vanilla, but still not that good
    '''
    def __init__(self,FFANN,loss,gamma=0.95,epsilon=1e-6,alpha=1e-2):
        '''
        FFANN: the feed-forward neural network
        loss: the loss function
        gamma: the decaying parameter
        epsilon: safety parameter (to avoid division by 0)
        alpha: learning rate

        '''
        self.FFANN=FFANN
        self.loss=loss
        self.gamma=gamma
        self.epsilon=epsilon
        self.alpha=alpha

        #counters for the decaying means         
        self.meanWeights=[ [[0 for i in range(self.FFANN.nodes[l])] for j in range(self.FFANN.nodes[l+1])]  for l in range(self.FFANN.total_layers-1)]
        self.meanBiases=[ [0 for j in range(self.FFANN.nodes[l+1])]  for l in range(self.FFANN.total_layers-1)]      

        
    def update(self, data_out,abs_tol=1e-5, rel_tol=1e-3):
        '''
        during the update step, you calculate the gradient of Q
        and update w and b. 
        '''
        #These are the output signals of FFANN. The update should run after
        #FFANN.feedForward() and FFANN.backPropagation().
        signal_out=self.FFANN.signals[self.FFANN.total_layers-1] 
            
        #these will be used to determine if the stopping conditions are satisfied 
        _w2=0
        _check=0

        
        for l in range(self.FFANN.total_layers-1):
            for j in range(self.FFANN.nodes[l+1]):
                for i in range(self.FFANN.nodes[l]):
                    #get the grad of the loss. The results should be stored in loss.dQdw and loss.dQdb
                    #This way it should be easy to update the weights and biases of FFANN
                    self.loss.grad(l,j,i,signal_out,data_out)
                    
                    
                    self.meanWeights[l][j][i]=self.gamma*self.meanWeights[l][j][i] + (1-self.gamma)*self.loss.dQdw**2 
                    dw=self.alpha/np_sqrt( (self.meanWeights[l][j][i]+self.epsilon)  )*self.loss.dQdw
                    
                    #update the weight using loss.dQdw
                    self.FFANN.addToWeight(l,j,i, -dw)

                    _w2=abs_tol + self.FFANN.weights[l][j][i] * rel_tol
                    _check+=(self.loss.dQdw/_w2)*(self.loss.dQdw/_w2)

                #update the bias using loss.dQdb (it is the same for all i, so don't run loss.grad again).
                self.meanBiases[l][j]=self.gamma*self.meanBiases[l][j] + (1-self.gamma)*self.loss.dQdb**2 
                dw=self.alpha/np_sqrt( (self.meanBiases[l][j]+self.epsilon)  )*self.loss.dQdb
                 
                self.FFANN.addToBias(l,j, -dw)
                
                _w2=abs_tol + self.FFANN.biases[l][j] * rel_tol
                _check+=(self.loss.dQdb/_w2)*(self.loss.dQdb/_w2)
                
                
        _check=np_sqrt(1./self.loss.N *_check)
        return _check