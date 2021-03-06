def evaluate(self,x):
    '''
    Calculate the output with self.signals[0]=x (without the derivatives).
    The outputs of all nodes are stored in self.signals
    '''
    self.inputSignal(x)
    for l in range(1,self.total_layers):
        for j in range(self.nodes[l]):
            sum_wx = sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
            self.signals[l][j] =  self.activations[l-1]( sum_wx + self.biases[l-1][j]  )




#-------------------------signals--------------------------------------#
def inputSignal(self, x):
    '''
    Read the input (x) and store it in self.signals[0]
    '''
    for j,_ in enumerate(x):
        self.signals[0][j] = _

def calcSignal(self, l,j):
    '''
    Calculate the output of the j node of layer l and 
    the (local) derivatives of s^{l}_{j} with respect s^{l-1}_{i} (far all i).
    we use:
    
    self.derivatives[0][j][i]= \dfrac{\partial s^{1}_{j}}{\partial s^{(0)}_{i}} 
    self.derivatives[1][j][i]= \dfrac{\partial s^{2}_{j}}{\partial s^{(1)}_{i}} 

    self.derivatives[l][j][i]= \dfrac{\partial s^{l+1}_{j}}{\partial s^{(l)}_{i}} 
    

    Note the convention:
    1. \theta^{(l)} =  self.activations[l-1]
    2. b^{(l)} = self.biases[l-1]

    It is intended to be used after the l-1 signals have been calulated
    within the feedForward() call.

    Note that this function is meaningless for l=0, since self.signals[0] is input
    '''

    #Notice that self.biases[l-1][j] correspond to the bias of node j and layer l.
    sum_wx = sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
    self.signals[l][j] =  self.activations[l-1]( sum_wx + self.biases[l-1][j]  )
    
    #fill also the derivatives (does the same thing as self.derivative for all i in self.nodes[l-1])
    arg=sum_wx+self.biases[l-1][j] 
    for i in range(self.nodes[l-1]):
        self.derivatives[l-1][j][i]= self.activations[l-1].derivative(arg) * self.weights[l-1][j][i]
        
    
            

def feedForward(self):
    '''
    Calculate only the output of the network and the local derivatives
    '''
    
    for l in range(1,self.total_layers):
        for j in range(self.nodes[l]):
            self.calcSignal(l,j)


#let's overlaod __call__ for convenience
def call(self,x):
    '''
    Calculates the output and the derivatives of the network with self.signals[0]=x
    '''
    self.inputSignal(x)
    self.feedForward()
    return self.signals[self.total_layers-1]

