class loss:
    def __init__(self,Q_i,dQds_i,FFANN):
        '''
        The loss should look like this.
        
        Q_i: the loss function for one data-point (e.g. lambda signal,targer: (signal-targer)**2 for the square loss).
        This will be called from __call__, which will take the average over all components of the signal
        
        dQds_i: the derivative of Q_i wrt signal (e.g. lambda signal,targer: 2*(signal-targer) for the square loss).
        Again it will be averaged over all components of the signal when calling grad().
        
        FFANN: the feed-forward neural network which is going to be used.
        '''
        self.FFANN=FFANN
        self.N=self.FFANN.nodes[self.FFANN.total_layers-1]
        self.Q_i=Q_i
        self.dQds_i=dQds_i
        
        #I will use these to hold the derivatives wrt w and b from FFANN
        self.dQdw=0
        self.dQdb=0
        
    def __call__(self,signal,target):
        sum_Q=0
        
        for r in range(self.N):
            sum_Q+=self.Q_i(signal[r],target[r]) 
            
        sum_Q=sum_Q/(float(self.N)) #take the average
        return sum_Q
    
         
    def grad(self,l,j,i,signal_out,data_out):
        #calculate the derivatives wrt w^{(l)}_{ji} and b^{(l)}_{j}
        
        self.FFANN.derivative_bw(l,j,i)
        #the derivative in general is 
        #\dfrac{\partial Q}{\partial P} = \dfrac{\partial Q}{\partial signal^{N-1}_{r}}\dfrac{\partial signal^{N-1}_{r}}{\partial P}
        self.dQdw=0
        self.dQdb=0
        
        
        for r in range(self.N):
            _dQds=self.dQds_i(signal_out[r],data_out[r])/(float(self.N))
            
            self.dQdw += _dQds*self.FFANN.dsdw[r]
            self.dQdb += _dQds*self.FFANN.dsdb[r]
            