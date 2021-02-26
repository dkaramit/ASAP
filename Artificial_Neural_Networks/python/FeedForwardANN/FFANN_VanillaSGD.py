from numpy import sqrt as np_sqrt

class VanillaSGD:
    '''
    Not the best (far from it) strategy, but the simplest. Will use it to test if the implementation works.
    '''
    def __init__(self,FFANN,loss,alpha=1e-2):
        self.FFANN=FFANN
        self.loss=loss
        self.alpha=alpha
    
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
                    dw=self.alpha*self.loss.dQdw
                    #update the weight using loss.dQdw
                    self.FFANN.addToWeight(l,j,i, -dw)

                    _w2=abs_tol + self.FFANN.weights[l][j][i] * rel_tol
                    _check+=(dw/_w2)*(dw/_w2)

                dw=self.alpha*self.loss.dQdb
                #update the bias using loss.dQdb (it is the same for all i, so don't run loss.grad again).
                self.FFANN.addToBias(l,j, -dw)
                
                _w2=abs_tol + self.FFANN.biases[l][j] * rel_tol
                _check+=(dw/_w2)*(dw/_w2)
                
                
        _check=np_sqrt(1./self.loss.N *_check)
        return _check