def evaluate(self):
    '''
    Calculate the output without the derivatives.
    The outputs of all nored are stored in self.signals
    '''
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
    the derivatives of s^{l}_{j} with respect s^{l-1}_{i} (far all i).
    It is intended to be used after the l-1 signals have been calulated
    within the feedForward() call
    '''
    #for l=0 this function is meaningless as self.signals[0] is input

    #Notice that self.biases[l-1][j] correspond to the bias of node j and layer l.
    sum_wx = sum( [ self.weights[l-1][j][i] * xi for i,xi in enumerate(self.signals[l-1]) ] ) 
    self.signals[l][j] =  self.activations[l-1]( sum_wx + self.biases[l-1][j]  )
    
    #fill also the derivatives (does the same thing as self.derivative for all i in self.nodes[l-1])
    arg=sum_wx+self.biases[l-1][j] 
    for i in range(self.nodes[l-1]):
        self.derivatives[l-1][j][i]= self.activations[l-1].derivative(arg) * self.weights[l-1][j][i]
        
    
            
def mulM(self,l):
    '''
    Matrix multiplication to be used when calculating the derivatives.
    It is intended to be used the feedForward() call
    '''

    if l==1:
        self.totalDerivatives[0]= self.derivatives[0][:]
        return 
    
    for j in range(self.nodes[l]):
        for i in range(self.nodes[0]):
            self.totalDerivatives[l-1][j][i]=0
            for k in range(self.nodes[l-1]):
                self.totalDerivatives[l-1][j][i]+=self.derivatives[l-1][j][k]*self.totalDerivatives[l-2][k][i]


def feedForward(self):
    '''
    Calculate the output and the derivatives of the network
    '''
    
    for l in range(1,self.total_layers):
        for j in range(self.nodes[l]):
            self.calcSignal(l,j)
        self.mulM(l)


#let's overlaod __call__ for convenience
def call(self,x):
    '''
    Calculates the output and the derivatives of the network with self.signals[0]=x
    '''
    self.inputSignal(x)
    self.feedForward()
    # you can return the output and its derivatives
    return self.signals[self.total_layers-1],self.totalDerivatives[self.total_layers-2]

