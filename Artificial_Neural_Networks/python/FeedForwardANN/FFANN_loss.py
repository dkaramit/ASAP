from numpy import random as np_random
class loss:
    def __init__(self,data_in, data_out,Q_i,dQds_i,model):
        '''
        The loss should look like this.
        
        Q_i: the loss function for one data-point (e.g. lambda signal,targer: (signal-targer)**2 for the square loss).
        This will be called from __call__, which will take the average over all components of the signal
        
        dQds_i: the derivative of Q_i wrt signal (e.g. lambda signal,targer: 2*(signal-targer) for the square loss).
        Again it will be averaged over all components of the signal when calling grad().
        
        FFANN: the feed-forward neural network which is going to be used.
        '''

        #size of data
        self.data_size=len(data_in)
        self.data_in=data_in
        self.data_out=data_out

        self.model=model
        self.N=self.model.nodes[self.model.total_layers-1]
        self.Q_i=Q_i
        self.dQds_i=dQds_i
        
        #I will use these to hold the derivatives wrt w and b from FFANN
        self.dQdw=0
        self.dQdb=0

        self.t=[]

        
    def __call__(self,target):
        sum_Q=0
        
        for r in range(self.N):
            sum_Q+=self.Q_i(self.model.signals[self.model.total_layers-1][r], target[r]) 
            
        sum_Q=sum_Q/(float(self.N)) #take the average
        return sum_Q
    
    def randomDataPoint(self):
        #get a random data point (it will be passed to the strategy.update function)
        index=np_random.randint(self.data_size)
        x=self.data_in[index]
        self.t=self.data_out[index]
        #run for x as the input, in order to get the output signal and be prepeared
        #to get its derivatives over the parameters.
        self.model.inputSignal(x)
        self.model.feedForward()
        self.model.backPropagation()

    def grad(self,l,j,i):
        #calculate the derivatives wrt w^{(l)}_{ji} and b^{(l)}_{j}
        
        self.model.derivative_bw(l,j,i)
        #the derivative in general is 
        #\dfrac{\partial Q}{\partial P} = \dfrac{\partial Q}{\partial signal^{N-1}_{r}}\dfrac{\partial signal^{N-1}_{r}}{\partial P}
        self.dQdw=0
        self.dQdb=0
        
        
        for r in range(self.N):
            _dQds=self.dQds_i(self.model.signals[self.model.total_layers-1][r], self.t[r])/(float(self.N))
            
            self.dQdw += _dQds*self.model.dsdw[r]
            self.dQdb += _dQds*self.model.dsdb[r]
            